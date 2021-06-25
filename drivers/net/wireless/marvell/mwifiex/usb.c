<शैली गुरु>
/*
 * NXP Wireless LAN device driver: USB specअगरic handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "main.h"
#समावेश "usb.h"

#घोषणा USB_VERSION	"1.0"

अटल काष्ठा mwअगरiex_अगर_ops usb_ops;

अटल स्थिर काष्ठा usb_device_id mwअगरiex_usb_table[] = अणु
	/* 8766 */
	अणुUSB_DEVICE(USB8XXX_VID, USB8766_PID_1)पूर्ण,
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB8XXX_VID, USB8766_PID_2,
				       USB_CLASS_VENDOR_SPEC,
				       USB_SUBCLASS_VENDOR_SPEC, 0xff)पूर्ण,
	/* 8797 */
	अणुUSB_DEVICE(USB8XXX_VID, USB8797_PID_1)पूर्ण,
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB8XXX_VID, USB8797_PID_2,
				       USB_CLASS_VENDOR_SPEC,
				       USB_SUBCLASS_VENDOR_SPEC, 0xff)पूर्ण,
	/* 8801 */
	अणुUSB_DEVICE(USB8XXX_VID, USB8801_PID_1)पूर्ण,
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB8XXX_VID, USB8801_PID_2,
				       USB_CLASS_VENDOR_SPEC,
				       USB_SUBCLASS_VENDOR_SPEC, 0xff)पूर्ण,
	/* 8997 */
	अणुUSB_DEVICE(USB8XXX_VID, USB8997_PID_1)पूर्ण,
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB8XXX_VID, USB8997_PID_2,
				       USB_CLASS_VENDOR_SPEC,
				       USB_SUBCLASS_VENDOR_SPEC, 0xff)पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, mwअगरiex_usb_table);

अटल पूर्णांक mwअगरiex_usb_submit_rx_urb(काष्ठा urb_context *ctx, पूर्णांक size);

/* This function handles received packet. Necessary action is taken based on
 * cmd/event/data.
 */
अटल पूर्णांक mwअगरiex_usb_recv(काष्ठा mwअगरiex_adapter *adapter,
			    काष्ठा sk_buff *skb, u8 ep)
अणु
	u32 recv_type;
	__le32 पंचांगp;
	पूर्णांक ret;

	अगर (adapter->hs_activated)
		mwअगरiex_process_hs_config(adapter);

	अगर (skb->len < INTF_HEADER_LEN) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: invalid skb->len\n", __func__);
		वापस -1;
	पूर्ण

	चयन (ep) अणु
	हाल MWIFIEX_USB_EP_CMD_EVENT:
		mwअगरiex_dbg(adapter, EVENT,
			    "%s: EP_CMD_EVENT\n", __func__);
		skb_copy_from_linear_data(skb, &पंचांगp, INTF_HEADER_LEN);
		recv_type = le32_to_cpu(पंचांगp);
		skb_pull(skb, INTF_HEADER_LEN);

		चयन (recv_type) अणु
		हाल MWIFIEX_USB_TYPE_CMD:
			अगर (skb->len > MWIFIEX_SIZE_OF_CMD_BUFFER) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "CMD: skb->len too large\n");
				ret = -1;
				जाओ निकास_restore_skb;
			पूर्ण अन्यथा अगर (!adapter->curr_cmd) अणु
				mwअगरiex_dbg(adapter, WARN, "CMD: no curr_cmd\n");
				अगर (adapter->ps_state == PS_STATE_SLEEP_CFM) अणु
					mwअगरiex_process_sleep_confirm_resp(
							adapter, skb->data,
							skb->len);
					ret = 0;
					जाओ निकास_restore_skb;
				पूर्ण
				ret = -1;
				जाओ निकास_restore_skb;
			पूर्ण

			adapter->curr_cmd->resp_skb = skb;
			adapter->cmd_resp_received = true;
			अवरोध;
		हाल MWIFIEX_USB_TYPE_EVENT:
			अगर (skb->len < माप(u32)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "EVENT: skb->len too small\n");
				ret = -1;
				जाओ निकास_restore_skb;
			पूर्ण
			skb_copy_from_linear_data(skb, &पंचांगp, माप(u32));
			adapter->event_cause = le32_to_cpu(पंचांगp);
			mwअगरiex_dbg(adapter, EVENT,
				    "event_cause %#x\n", adapter->event_cause);

			अगर (skb->len > MAX_EVENT_SIZE) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "EVENT: event body too large\n");
				ret = -1;
				जाओ निकास_restore_skb;
			पूर्ण

			स_नकल(adapter->event_body, skb->data +
			       MWIFIEX_EVENT_HEADER_LEN, skb->len);

			adapter->event_received = true;
			adapter->event_skb = skb;
			अवरोध;
		शेष:
			mwअगरiex_dbg(adapter, ERROR,
				    "unknown recv_type %#x\n", recv_type);
			वापस -1;
		पूर्ण
		अवरोध;
	हाल MWIFIEX_USB_EP_DATA:
		mwअगरiex_dbg(adapter, DATA, "%s: EP_DATA\n", __func__);
		अगर (skb->len > MWIFIEX_RX_DATA_BUF_SIZE) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "DATA: skb->len too large\n");
			वापस -1;
		पूर्ण

		skb_queue_tail(&adapter->rx_data_q, skb);
		adapter->data_received = true;
		atomic_inc(&adapter->rx_pending);
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: unknown endport %#x\n", __func__, ep);
		वापस -1;
	पूर्ण

	वापस -EINPROGRESS;

निकास_restore_skb:
	/* The buffer will be reused क्रम further cmds/events */
	skb_push(skb, INTF_HEADER_LEN);

	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_usb_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा urb_context *context = (काष्ठा urb_context *)urb->context;
	काष्ठा mwअगरiex_adapter *adapter = context->adapter;
	काष्ठा sk_buff *skb = context->skb;
	काष्ठा usb_card_rec *card;
	पूर्णांक recv_length = urb->actual_length;
	पूर्णांक size, status;

	अगर (!adapter || !adapter->card) अणु
		pr_err("mwifiex adapter or card structure is not valid\n");
		वापस;
	पूर्ण

	card = (काष्ठा usb_card_rec *)adapter->card;
	अगर (card->rx_cmd_ep == context->ep)
		atomic_dec(&card->rx_cmd_urb_pending);
	अन्यथा
		atomic_dec(&card->rx_data_urb_pending);

	अगर (recv_length) अणु
		अगर (urb->status ||
		    test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "URB status is failed: %d\n", urb->status);
			/* Do not मुक्त skb in हाल of command ep */
			अगर (card->rx_cmd_ep != context->ep)
				dev_kमुक्त_skb_any(skb);
			जाओ setup_क्रम_next;
		पूर्ण
		अगर (skb->len > recv_length)
			skb_trim(skb, recv_length);
		अन्यथा
			skb_put(skb, recv_length - skb->len);

		status = mwअगरiex_usb_recv(adapter, skb, context->ep);

		mwअगरiex_dbg(adapter, INFO,
			    "info: recv_length=%d, status=%d\n",
			    recv_length, status);
		अगर (status == -EINPROGRESS) अणु
			mwअगरiex_queue_मुख्य_work(adapter);

			/* urb क्रम data_ep is re-submitted now;
			 * urb क्रम cmd_ep will be re-submitted in callback
			 * mwअगरiex_usb_recv_complete
			 */
			अगर (card->rx_cmd_ep == context->ep)
				वापस;
		पूर्ण अन्यथा अणु
			अगर (status == -1)
				mwअगरiex_dbg(adapter, ERROR,
					    "received data processing failed!\n");

			/* Do not मुक्त skb in हाल of command ep */
			अगर (card->rx_cmd_ep != context->ep)
				dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण अन्यथा अगर (urb->status) अणु
		अगर (!test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
			mwअगरiex_dbg(adapter, FATAL,
				    "Card is removed: %d\n", urb->status);
			set_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);
		पूर्ण
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण अन्यथा अणु
		/* Do not मुक्त skb in हाल of command ep */
		अगर (card->rx_cmd_ep != context->ep)
			dev_kमुक्त_skb_any(skb);

		/* fall through setup_क्रम_next */
	पूर्ण

setup_क्रम_next:
	अगर (card->rx_cmd_ep == context->ep)
		size = MWIFIEX_RX_CMD_BUF_SIZE;
	अन्यथा
		size = MWIFIEX_RX_DATA_BUF_SIZE;

	अगर (card->rx_cmd_ep == context->ep) अणु
		mwअगरiex_usb_submit_rx_urb(context, size);
	पूर्ण अन्यथा अणु
		अगर (atomic_पढ़ो(&adapter->rx_pending) <= HIGH_RX_PENDING) अणु
			mwअगरiex_usb_submit_rx_urb(context, size);
		पूर्ण अन्यथा अणु
			context->skb = शून्य;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल व्योम mwअगरiex_usb_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा urb_context *context = (काष्ठा urb_context *)(urb->context);
	काष्ठा mwअगरiex_adapter *adapter = context->adapter;
	काष्ठा usb_card_rec *card = adapter->card;
	काष्ठा usb_tx_data_port *port;
	पूर्णांक i;

	mwअगरiex_dbg(adapter, INFO,
		    "%s: status: %d\n", __func__, urb->status);

	अगर (context->ep == card->tx_cmd_ep) अणु
		mwअगरiex_dbg(adapter, CMD,
			    "%s: CMD\n", __func__);
		atomic_dec(&card->tx_cmd_urb_pending);
		adapter->cmd_sent = false;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, DATA,
			    "%s: DATA\n", __func__);
		mwअगरiex_ग_लिखो_data_complete(adapter, context->skb, 0,
					    urb->status ? -1 : 0);
		क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
			port = &card->port[i];
			अगर (context->ep == port->tx_data_ep) अणु
				atomic_dec(&port->tx_data_urb_pending);
				port->block_status = false;
				अवरोध;
			पूर्ण
		पूर्ण
		adapter->data_sent = false;
	पूर्ण

	अगर (card->mc_resync_flag)
		mwअगरiex_multi_chan_resync(adapter);

	mwअगरiex_queue_मुख्य_work(adapter);

	वापस;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_submit_rx_urb(काष्ठा urb_context *ctx, पूर्णांक size)
अणु
	काष्ठा mwअगरiex_adapter *adapter = ctx->adapter;
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;

	अगर (test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		अगर (card->rx_cmd_ep == ctx->ep) अणु
			mwअगरiex_dbg(adapter, INFO, "%s: free rx_cmd skb\n",
				    __func__);
			dev_kमुक्त_skb_any(ctx->skb);
			ctx->skb = शून्य;
		पूर्ण
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: card removed/suspended, EP %d rx_cmd URB submit skipped\n",
			    __func__, ctx->ep);
		वापस -1;
	पूर्ण

	अगर (card->rx_cmd_ep != ctx->ep) अणु
		ctx->skb = dev_alloc_skb(size);
		अगर (!ctx->skb) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: dev_alloc_skb failed\n", __func__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (card->rx_cmd_ep == ctx->ep &&
	    card->rx_cmd_ep_type == USB_ENDPOINT_XFER_INT)
		usb_fill_पूर्णांक_urb(ctx->urb, card->udev,
				 usb_rcvपूर्णांकpipe(card->udev, ctx->ep),
				 ctx->skb->data, size, mwअगरiex_usb_rx_complete,
				 (व्योम *)ctx, card->rx_cmd_पूर्णांकerval);
	अन्यथा
		usb_fill_bulk_urb(ctx->urb, card->udev,
				  usb_rcvbulkpipe(card->udev, ctx->ep),
				  ctx->skb->data, size, mwअगरiex_usb_rx_complete,
				  (व्योम *)ctx);

	अगर (card->rx_cmd_ep == ctx->ep)
		atomic_inc(&card->rx_cmd_urb_pending);
	अन्यथा
		atomic_inc(&card->rx_data_urb_pending);

	अगर (usb_submit_urb(ctx->urb, GFP_ATOMIC)) अणु
		mwअगरiex_dbg(adapter, ERROR, "usb_submit_urb failed\n");
		dev_kमुक्त_skb_any(ctx->skb);
		ctx->skb = शून्य;

		अगर (card->rx_cmd_ep == ctx->ep)
			atomic_dec(&card->rx_cmd_urb_pending);
		अन्यथा
			atomic_dec(&card->rx_data_urb_pending);

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_usb_मुक्त(काष्ठा usb_card_rec *card)
अणु
	काष्ठा usb_tx_data_port *port;
	पूर्णांक i, j;

	अगर (atomic_पढ़ो(&card->rx_cmd_urb_pending) && card->rx_cmd.urb)
		usb_समाप्त_urb(card->rx_cmd.urb);

	usb_मुक्त_urb(card->rx_cmd.urb);
	card->rx_cmd.urb = शून्य;

	अगर (atomic_पढ़ो(&card->rx_data_urb_pending))
		क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++)
			अगर (card->rx_data_list[i].urb)
				usb_समाप्त_urb(card->rx_data_list[i].urb);

	क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++) अणु
		usb_मुक्त_urb(card->rx_data_list[i].urb);
		card->rx_data_list[i].urb = शून्य;
	पूर्ण

	क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
		port = &card->port[i];
		क्रम (j = 0; j < MWIFIEX_TX_DATA_URB; j++) अणु
			usb_समाप्त_urb(port->tx_data_list[j].urb);
			usb_मुक्त_urb(port->tx_data_list[j].urb);
			port->tx_data_list[j].urb = शून्य;
		पूर्ण
	पूर्ण

	usb_मुक्त_urb(card->tx_cmd.urb);
	card->tx_cmd.urb = शून्य;

	वापस;
पूर्ण

/* This function probes an mwअगरiex device and रेजिस्टरs it. It allocates
 * the card काष्ठाure, initiates the device registration and initialization
 * procedure by adding a logical पूर्णांकerface.
 */
अटल पूर्णांक mwअगरiex_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक ret, i;
	काष्ठा usb_card_rec *card;
	u16 id_venकरोr, id_product, bcd_device;

	card = devm_kzalloc(&पूर्णांकf->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	init_completion(&card->fw_करोne);

	id_venकरोr = le16_to_cpu(udev->descriptor.idVenकरोr);
	id_product = le16_to_cpu(udev->descriptor.idProduct);
	bcd_device = le16_to_cpu(udev->descriptor.bcdDevice);
	pr_debug("info: VID/PID = %X/%X, Boot2 version = %X\n",
		 id_venकरोr, id_product, bcd_device);

	/* PID_1 is used क्रम firmware करोwnloading only */
	चयन (id_product) अणु
	हाल USB8766_PID_1:
	हाल USB8797_PID_1:
	हाल USB8801_PID_1:
	हाल USB8997_PID_1:
		card->usb_boot_state = USB8XXX_FW_DNLD;
		अवरोध;
	हाल USB8766_PID_2:
	हाल USB8797_PID_2:
	हाल USB8801_PID_2:
	हाल USB8997_PID_2:
		card->usb_boot_state = USB8XXX_FW_READY;
		अवरोध;
	शेष:
		pr_warn("unknown id_product %#x\n", id_product);
		card->usb_boot_state = USB8XXX_FW_DNLD;
		अवरोध;
	पूर्ण

	card->udev = udev;
	card->पूर्णांकf = पूर्णांकf;

	pr_debug("info: bcdUSB=%#x Device Class=%#x SubClass=%#x Protocol=%#x\n",
		 le16_to_cpu(udev->descriptor.bcdUSB),
		 udev->descriptor.bDeviceClass,
		 udev->descriptor.bDeviceSubClass,
		 udev->descriptor.bDeviceProtocol);

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		epd = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (usb_endpoपूर्णांक_dir_in(epd) &&
		    usb_endpoपूर्णांक_num(epd) == MWIFIEX_USB_EP_CMD_EVENT &&
		    (usb_endpoपूर्णांक_xfer_bulk(epd) ||
		     usb_endpoपूर्णांक_xfer_पूर्णांक(epd))) अणु
			card->rx_cmd_ep_type = usb_endpoपूर्णांक_type(epd);
			card->rx_cmd_पूर्णांकerval = epd->bInterval;
			pr_debug("info: Rx CMD/EVT:: max pkt size: %d, addr: %d, ep_type: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress, card->rx_cmd_ep_type);
			card->rx_cmd_ep = usb_endpoपूर्णांक_num(epd);
			atomic_set(&card->rx_cmd_urb_pending, 0);
		पूर्ण
		अगर (usb_endpoपूर्णांक_dir_in(epd) &&
		    usb_endpoपूर्णांक_num(epd) == MWIFIEX_USB_EP_DATA &&
		    usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
			pr_debug("info: bulk IN: max pkt size: %d, addr: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress);
			card->rx_data_ep = usb_endpoपूर्णांक_num(epd);
			atomic_set(&card->rx_data_urb_pending, 0);
		पूर्ण
		अगर (usb_endpoपूर्णांक_dir_out(epd) &&
		    usb_endpoपूर्णांक_num(epd) == MWIFIEX_USB_EP_DATA &&
		    usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
			pr_debug("info: bulk OUT: max pkt size: %d, addr: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress);
			card->port[0].tx_data_ep = usb_endpoपूर्णांक_num(epd);
			atomic_set(&card->port[0].tx_data_urb_pending, 0);
		पूर्ण
		अगर (usb_endpoपूर्णांक_dir_out(epd) &&
		    usb_endpoपूर्णांक_num(epd) == MWIFIEX_USB_EP_DATA_CH2 &&
		    usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
			pr_debug("info: bulk OUT chan2:\t"
				 "max pkt size: %d, addr: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress);
			card->port[1].tx_data_ep = usb_endpoपूर्णांक_num(epd);
			atomic_set(&card->port[1].tx_data_urb_pending, 0);
		पूर्ण
		अगर (usb_endpoपूर्णांक_dir_out(epd) &&
		    usb_endpoपूर्णांक_num(epd) == MWIFIEX_USB_EP_CMD_EVENT &&
		    (usb_endpoपूर्णांक_xfer_bulk(epd) ||
		     usb_endpoपूर्णांक_xfer_पूर्णांक(epd))) अणु
			card->tx_cmd_ep_type = usb_endpoपूर्णांक_type(epd);
			card->tx_cmd_पूर्णांकerval = epd->bInterval;
			pr_debug("info: bulk OUT: max pkt size: %d, addr: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress);
			pr_debug("info: Tx CMD:: max pkt size: %d, addr: %d, ep_type: %d\n",
				 le16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpoपूर्णांकAddress, card->tx_cmd_ep_type);
			card->tx_cmd_ep = usb_endpoपूर्णांक_num(epd);
			atomic_set(&card->tx_cmd_urb_pending, 0);
			card->bulk_out_maxpktsize =
					le16_to_cpu(epd->wMaxPacketSize);
		पूर्ण
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, card);

	ret = mwअगरiex_add_card(card, &card->fw_करोne, &usb_ops,
			       MWIFIEX_USB, &card->udev->dev);
	अगर (ret) अणु
		pr_err("%s: mwifiex_add_card failed: %d\n", __func__, ret);
		usb_reset_device(udev);
		वापस ret;
	पूर्ण

	usb_get_dev(udev);

	वापस 0;
पूर्ण

/* Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not suspended, this function allocates and sends a
 * 'host sleep activate' request to the firmware and turns off the traffic.
 */
अटल पूर्णांक mwअगरiex_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_card_rec *card = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा usb_tx_data_port *port;
	पूर्णांक i, j;

	/* Might still be loading firmware */
	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter) अणु
		dev_err(&पूर्णांकf->dev, "card is not valid\n");
		वापस 0;
	पूर्ण

	अगर (unlikely(test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)))
		mwअगरiex_dbg(adapter, WARN,
			    "Device already suspended\n");

	/* Enable the Host Sleep */
	अगर (!mwअगरiex_enable_hs(adapter)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cmd: failed to suspend\n");
		clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
		वापस -EFAULT;
	पूर्ण


	/* 'MWIFIEX_IS_SUSPENDED' bit indicates device is suspended.
	 * It must be set here beक्रमe the usb_समाप्त_urb() calls. Reason
	 * is in the complete handlers, urb->status(= -ENOENT) and
	 * this flag is used in combination to distinguish between a
	 * 'suspended' state and a 'disconnect' one.
	 */
	set_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);

	अगर (atomic_पढ़ो(&card->rx_cmd_urb_pending) && card->rx_cmd.urb)
		usb_समाप्त_urb(card->rx_cmd.urb);

	अगर (atomic_पढ़ो(&card->rx_data_urb_pending))
		क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++)
			अगर (card->rx_data_list[i].urb)
				usb_समाप्त_urb(card->rx_data_list[i].urb);

	क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
		port = &card->port[i];
		क्रम (j = 0; j < MWIFIEX_TX_DATA_URB; j++) अणु
			अगर (port->tx_data_list[j].urb)
				usb_समाप्त_urb(port->tx_data_list[j].urb);
		पूर्ण
	पूर्ण

	अगर (card->tx_cmd.urb)
		usb_समाप्त_urb(card->tx_cmd.urb);

	वापस 0;
पूर्ण

/* Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not resumed, this function turns on the traffic and
 * sends a 'host sleep cancel' request to the firmware.
 */
अटल पूर्णांक mwअगरiex_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_card_rec *card = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा mwअगरiex_adapter *adapter;
	पूर्णांक i;

	अगर (!card->adapter) अणु
		dev_err(&पूर्णांकf->dev, "%s: card->adapter is NULL\n",
			__func__);
		वापस 0;
	पूर्ण
	adapter = card->adapter;

	अगर (unlikely(!test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags))) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "Device already resumed\n");
		वापस 0;
	पूर्ण

	/* Indicate device resumed. The netdev queue will be resumed only
	 * after the urbs have been re-submitted
	 */
	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);

	अगर (!atomic_पढ़ो(&card->rx_data_urb_pending))
		क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++)
			mwअगरiex_usb_submit_rx_urb(&card->rx_data_list[i],
						  MWIFIEX_RX_DATA_BUF_SIZE);

	अगर (!atomic_पढ़ो(&card->rx_cmd_urb_pending)) अणु
		card->rx_cmd.skb = dev_alloc_skb(MWIFIEX_RX_CMD_BUF_SIZE);
		अगर (card->rx_cmd.skb)
			mwअगरiex_usb_submit_rx_urb(&card->rx_cmd,
						  MWIFIEX_RX_CMD_BUF_SIZE);
	पूर्ण

	/* Disable Host Sleep */
	अगर (adapter->hs_activated)
		mwअगरiex_cancel_hs(mwअगरiex_get_priv(adapter,
						   MWIFIEX_BSS_ROLE_ANY),
				  MWIFIEX_ASYNC_CMD);

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_card_rec *card = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा mwअगरiex_adapter *adapter;

	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter || !adapter->priv_num)
		वापस;

	अगर (card->udev->state != USB_STATE_NOTATTACHED && !adapter->mfg_mode) अणु
		mwअगरiex_deauthenticate_all(adapter);

		mwअगरiex_init_shutकरोwn_fw(mwअगरiex_get_priv(adapter,
							  MWIFIEX_BSS_ROLE_ANY),
					 MWIFIEX_FUNC_SHUTDOWN);
	पूर्ण

	mwअगरiex_dbg(adapter, FATAL,
		    "%s: removing card\n", __func__);
	mwअगरiex_हटाओ_card(adapter);

	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
पूर्ण

अटल व्योम mwअगरiex_usb_coredump(काष्ठा device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_card_rec *card = usb_get_पूर्णांकfdata(पूर्णांकf);

	mwअगरiex_fw_dump_event(mwअगरiex_get_priv(card->adapter,
					       MWIFIEX_BSS_ROLE_ANY));
पूर्ण

अटल काष्ठा usb_driver mwअगरiex_usb_driver = अणु
	.name = "mwifiex_usb",
	.probe = mwअगरiex_usb_probe,
	.disconnect = mwअगरiex_usb_disconnect,
	.id_table = mwअगरiex_usb_table,
	.suspend = mwअगरiex_usb_suspend,
	.resume = mwअगरiex_usb_resume,
	.soft_unbind = 1,
	.drvwrap.driver = अणु
		.coredump = mwअगरiex_usb_coredump,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mwअगरiex_ग_लिखो_data_sync(काष्ठा mwअगरiex_adapter *adapter, u8 *pbuf,
				   u32 *len, u8 ep, u32 समयout)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	पूर्णांक actual_length, ret;

	अगर (!(*len % card->bulk_out_maxpktsize))
		(*len)++;

	/* Send the data block */
	ret = usb_bulk_msg(card->udev, usb_sndbulkpipe(card->udev, ep), pbuf,
			   *len, &actual_length, समयout);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "usb_bulk_msg for tx failed: %d\n", ret);
		वापस ret;
	पूर्ण

	*len = actual_length;

	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_पढ़ो_data_sync(काष्ठा mwअगरiex_adapter *adapter, u8 *pbuf,
				  u32 *len, u8 ep, u32 समयout)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	पूर्णांक actual_length, ret;

	/* Receive the data response */
	ret = usb_bulk_msg(card->udev, usb_rcvbulkpipe(card->udev, ep), pbuf,
			   *len, &actual_length, समयout);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "usb_bulk_msg for rx failed: %d\n", ret);
		वापस ret;
	पूर्ण

	*len = actual_length;

	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_usb_port_resync(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	u8 active_port = MWIFIEX_USB_EP_DATA;
	काष्ठा mwअगरiex_निजी *priv = शून्य;
	पूर्णांक i;

	अगर (adapter->usb_mc_status) अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (!priv)
				जारी;
			अगर ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP &&
			     !priv->bss_started) ||
			    (priv->bss_role == MWIFIEX_BSS_ROLE_STA &&
			     !priv->media_connected))
				priv->usb_port = MWIFIEX_USB_EP_DATA;
		पूर्ण
		क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++)
			card->port[i].block_status = false;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (!priv)
				जारी;
			अगर ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP &&
			     priv->bss_started) ||
			    (priv->bss_role == MWIFIEX_BSS_ROLE_STA &&
			     priv->media_connected)) अणु
				active_port = priv->usb_port;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (priv)
				priv->usb_port = active_port;
		पूर्ण
		क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
			अगर (active_port == card->port[i].tx_data_ep)
				card->port[i].block_status = false;
			अन्यथा
				card->port[i].block_status = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool mwअगरiex_usb_is_port_पढ़ोy(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा usb_card_rec *card = priv->adapter->card;
	पूर्णांक idx;

	क्रम (idx = 0; idx < MWIFIEX_TX_DATA_PORT; idx++) अणु
		अगर (priv->usb_port == card->port[idx].tx_data_ep)
			वापस !card->port[idx].block_status;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत u8 mwअगरiex_usb_data_sent(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	पूर्णांक i;

	क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++)
		अगर (!card->port[i].block_status)
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_स्थिरruct_send_urb(काष्ठा mwअगरiex_adapter *adapter,
					  काष्ठा usb_tx_data_port *port, u8 ep,
					  काष्ठा urb_context *context,
					  काष्ठा sk_buff *skb_send)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	पूर्णांक ret = -EINPROGRESS;
	काष्ठा urb *tx_urb;

	context->adapter = adapter;
	context->ep = ep;
	context->skb = skb_send;
	tx_urb = context->urb;

	अगर (ep == card->tx_cmd_ep &&
	    card->tx_cmd_ep_type == USB_ENDPOINT_XFER_INT)
		usb_fill_पूर्णांक_urb(tx_urb, card->udev,
				 usb_sndपूर्णांकpipe(card->udev, ep), skb_send->data,
				 skb_send->len, mwअगरiex_usb_tx_complete,
				 (व्योम *)context, card->tx_cmd_पूर्णांकerval);
	अन्यथा
		usb_fill_bulk_urb(tx_urb, card->udev,
				  usb_sndbulkpipe(card->udev, ep),
				  skb_send->data, skb_send->len,
				  mwअगरiex_usb_tx_complete, (व्योम *)context);

	tx_urb->transfer_flags |= URB_ZERO_PACKET;

	अगर (ep == card->tx_cmd_ep)
		atomic_inc(&card->tx_cmd_urb_pending);
	अन्यथा
		atomic_inc(&port->tx_data_urb_pending);

	अगर (ep != card->tx_cmd_ep &&
	    atomic_पढ़ो(&port->tx_data_urb_pending) ==
					MWIFIEX_TX_DATA_URB) अणु
		port->block_status = true;
		adapter->data_sent = mwअगरiex_usb_data_sent(adapter);
		ret = -ENOSR;
	पूर्ण

	अगर (usb_submit_urb(tx_urb, GFP_ATOMIC)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: usb_submit_urb failed\n", __func__);
		अगर (ep == card->tx_cmd_ep) अणु
			atomic_dec(&card->tx_cmd_urb_pending);
		पूर्ण अन्यथा अणु
			atomic_dec(&port->tx_data_urb_pending);
			port->block_status = false;
			adapter->data_sent = false;
			अगर (port->tx_data_ix)
				port->tx_data_ix--;
			अन्यथा
				port->tx_data_ix = MWIFIEX_TX_DATA_URB;
		पूर्ण
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_prepare_tx_aggr_skb(काष्ठा mwअगरiex_adapter *adapter,
					   काष्ठा usb_tx_data_port *port,
					   काष्ठा sk_buff **skb_send)
अणु
	काष्ठा sk_buff *skb_aggr, *skb_पंचांगp;
	u8 *payload, pad;
	u16 align = adapter->bus_aggr.tx_aggr_align;
	काष्ठा mwअगरiex_txinfo *tx_info = शून्य;
	bool is_txinfo_set = false;

	/* Packets in aggr_list will be send in either skb_aggr or
	 * ग_लिखो complete, delete the tx_aggr समयr
	 */
	अगर (port->tx_aggr.समयr_cnxt.is_hold_समयr_set) अणु
		del_समयr(&port->tx_aggr.समयr_cnxt.hold_समयr);
		port->tx_aggr.समयr_cnxt.is_hold_समयr_set = false;
		port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs = 0;
	पूर्ण

	skb_aggr = mwअगरiex_alloc_dma_align_buf(port->tx_aggr.aggr_len,
					       GFP_ATOMIC);
	अगर (!skb_aggr) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: alloc skb_aggr failed\n", __func__);

		जबतक ((skb_पंचांगp = skb_dequeue(&port->tx_aggr.aggr_list)))
			mwअगरiex_ग_लिखो_data_complete(adapter, skb_पंचांगp, 0, -1);

		port->tx_aggr.aggr_num = 0;
		port->tx_aggr.aggr_len = 0;
		वापस -EBUSY;
	पूर्ण

	tx_info = MWIFIEX_SKB_TXCB(skb_aggr);
	स_रखो(tx_info, 0, माप(*tx_info));

	जबतक ((skb_पंचांगp = skb_dequeue(&port->tx_aggr.aggr_list))) अणु
		/* padding क्रम aligning next packet header*/
		pad = (align - (skb_पंचांगp->len & (align - 1))) % align;
		payload = skb_put(skb_aggr, skb_पंचांगp->len + pad);
		स_नकल(payload, skb_पंचांगp->data, skb_पंचांगp->len);
		अगर (skb_queue_empty(&port->tx_aggr.aggr_list)) अणु
			/* करो not padding क्रम last packet*/
			*(u16 *)payload = cpu_to_le16(skb_पंचांगp->len);
			*(u16 *)&payload[2] =
				cpu_to_le16(MWIFIEX_TYPE_AGGR_DATA_V2 | 0x80);
			skb_trim(skb_aggr, skb_aggr->len - pad);
		पूर्ण अन्यथा अणु
			/* add aggregation पूर्णांकerface header */
			*(u16 *)payload = cpu_to_le16(skb_पंचांगp->len + pad);
			*(u16 *)&payload[2] =
				cpu_to_le16(MWIFIEX_TYPE_AGGR_DATA_V2);
		पूर्ण

		अगर (!is_txinfo_set) अणु
			tx_info->bss_num = MWIFIEX_SKB_TXCB(skb_पंचांगp)->bss_num;
			tx_info->bss_type = MWIFIEX_SKB_TXCB(skb_पंचांगp)->bss_type;
			is_txinfo_set = true;
		पूर्ण

		port->tx_aggr.aggr_num--;
		port->tx_aggr.aggr_len -= (skb_पंचांगp->len + pad);
		mwअगरiex_ग_लिखो_data_complete(adapter, skb_पंचांगp, 0, 0);
	पूर्ण

	tx_info->pkt_len = skb_aggr->len -
			(माप(काष्ठा txpd) + adapter->पूर्णांकf_hdr_len);
	tx_info->flags |= MWIFIEX_BUF_FLAG_AGGR_PKT;

	port->tx_aggr.aggr_num = 0;
	port->tx_aggr.aggr_len = 0;
	*skb_send = skb_aggr;

	वापस 0;
पूर्ण

/* This function prepare data packet to be send under usb tx aggregation
 * protocol, check current usb aggregation status, link packet to aggrgation
 * list अगर possible, work flow as below:
 * (1) अगर only 1 packet available, add usb tx aggregation header and send.
 * (2) अगर packet is able to aggregated, link it to current aggregation list.
 * (3) अगर packet is not able to aggregated, aggregate and send exist packets
 *     in aggrgation list. Then, link packet in the list अगर there is more
 *     packet in transmit queue, otherwise try to transmit single packet.
 */
अटल पूर्णांक mwअगरiex_usb_aggr_tx_data(काष्ठा mwअगरiex_adapter *adapter, u8 ep,
				    काष्ठा sk_buff *skb,
				    काष्ठा mwअगरiex_tx_param *tx_param,
				    काष्ठा usb_tx_data_port *port)
अणु
	u8 *payload, pad;
	u16 align = adapter->bus_aggr.tx_aggr_align;
	काष्ठा sk_buff *skb_send = शून्य;
	काष्ठा urb_context *context = शून्य;
	काष्ठा txpd *local_tx_pd =
		(काष्ठा txpd *)((u8 *)skb->data + adapter->पूर्णांकf_hdr_len);
	u8 f_send_aggr_buf = 0;
	u8 f_send_cur_buf = 0;
	u8 f_precopy_cur_buf = 0;
	u8 f_postcopy_cur_buf = 0;
	u32 समयout;
	पूर्णांक ret;

	/* padding to ensure each packet alginment */
	pad = (align - (skb->len & (align - 1))) % align;

	अगर (tx_param && tx_param->next_pkt_len) अणु
		/* next packet available in tx queue*/
		अगर (port->tx_aggr.aggr_len + skb->len + pad >
		    adapter->bus_aggr.tx_aggr_max_size) अणु
			f_send_aggr_buf = 1;
			f_postcopy_cur_buf = 1;
		पूर्ण अन्यथा अणु
			/* current packet could be aggregated*/
			f_precopy_cur_buf = 1;

			अगर (port->tx_aggr.aggr_len + skb->len + pad +
			    tx_param->next_pkt_len >
			    adapter->bus_aggr.tx_aggr_max_size ||
			    port->tx_aggr.aggr_num + 2 >
			    adapter->bus_aggr.tx_aggr_max_num) अणु
			    /* next packet could not be aggregated
			     * send current aggregation buffer
			     */
				f_send_aggr_buf = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* last packet in tx queue */
		अगर (port->tx_aggr.aggr_num > 0) अणु
			/* pending packets in aggregation buffer*/
			अगर (port->tx_aggr.aggr_len + skb->len + pad >
			    adapter->bus_aggr.tx_aggr_max_size) अणु
				/* current packet not be able to aggregated,
				 * send aggr buffer first, then send packet.
				 */
				f_send_cur_buf = 1;
			पूर्ण अन्यथा अणु
				/* last packet, Aggregation and send */
				f_precopy_cur_buf = 1;
			पूर्ण

			f_send_aggr_buf = 1;
		पूर्ण अन्यथा अणु
			/* no pending packets in aggregation buffer,
			 * send current packet immediately
			 */
			 f_send_cur_buf = 1;
		पूर्ण
	पूर्ण

	अगर (local_tx_pd->flags & MWIFIEX_TxPD_POWER_MGMT_शून्य_PACKET) अणु
		/* Send शून्य packet immediately*/
		अगर (f_precopy_cur_buf) अणु
			अगर (skb_queue_empty(&port->tx_aggr.aggr_list)) अणु
				f_precopy_cur_buf = 0;
				f_send_aggr_buf = 0;
				f_send_cur_buf = 1;
			पूर्ण अन्यथा अणु
				f_send_aggr_buf = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (f_postcopy_cur_buf) अणु
			f_send_cur_buf = 1;
			f_postcopy_cur_buf = 0;
		पूर्ण
	पूर्ण

	अगर (f_precopy_cur_buf) अणु
		skb_queue_tail(&port->tx_aggr.aggr_list, skb);
		port->tx_aggr.aggr_len += (skb->len + pad);
		port->tx_aggr.aggr_num++;
		अगर (f_send_aggr_buf)
			जाओ send_aggr_buf;

		/* packet will not been send immediately,
		 * set a समयr to make sure it will be sent under
		 * strict समय limit. Dynamically fit the समयout
		 * value, according to packets number in aggr_list
		 */
		अगर (!port->tx_aggr.समयr_cnxt.is_hold_समयr_set) अणु
			port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs =
					MWIFIEX_USB_TX_AGGR_TMO_MIN;
			समयout =
				port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs;
			mod_समयr(&port->tx_aggr.समयr_cnxt.hold_समयr,
				  jअगरfies + msecs_to_jअगरfies(समयout));
			port->tx_aggr.समयr_cnxt.is_hold_समयr_set = true;
		पूर्ण अन्यथा अणु
			अगर (port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs <
			    MWIFIEX_USB_TX_AGGR_TMO_MAX) अणु
				/* Dyanmic fit समयout */
				समयout =
				++port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs;
				mod_समयr(&port->tx_aggr.समयr_cnxt.hold_समयr,
					  jअगरfies + msecs_to_jअगरfies(समयout));
			पूर्ण
		पूर्ण
	पूर्ण

send_aggr_buf:
	अगर (f_send_aggr_buf) अणु
		ret = mwअगरiex_usb_prepare_tx_aggr_skb(adapter, port, &skb_send);
		अगर (!ret) अणु
			context = &port->tx_data_list[port->tx_data_ix++];
			ret = mwअगरiex_usb_स्थिरruct_send_urb(adapter, port, ep,
							     context, skb_send);
			अगर (ret == -1)
				mwअगरiex_ग_लिखो_data_complete(adapter, skb_send,
							    0, -1);
		पूर्ण
	पूर्ण

	अगर (f_send_cur_buf) अणु
		अगर (f_send_aggr_buf) अणु
			अगर (atomic_पढ़ो(&port->tx_data_urb_pending) >=
			    MWIFIEX_TX_DATA_URB) अणु
				port->block_status = true;
				adapter->data_sent =
					mwअगरiex_usb_data_sent(adapter);
				/* no available urb, postcopy packet*/
				f_postcopy_cur_buf = 1;
				जाओ postcopy_cur_buf;
			पूर्ण

			अगर (port->tx_data_ix >= MWIFIEX_TX_DATA_URB)
				port->tx_data_ix = 0;
		पूर्ण

		payload = skb->data;
		*(u16 *)&payload[2] =
			cpu_to_le16(MWIFIEX_TYPE_AGGR_DATA_V2 | 0x80);
		*(u16 *)payload = cpu_to_le16(skb->len);
		skb_send = skb;
		context = &port->tx_data_list[port->tx_data_ix++];
		वापस mwअगरiex_usb_स्थिरruct_send_urb(adapter, port, ep,
						      context, skb_send);
	पूर्ण

postcopy_cur_buf:
	अगर (f_postcopy_cur_buf) अणु
		skb_queue_tail(&port->tx_aggr.aggr_list, skb);
		port->tx_aggr.aggr_len += (skb->len + pad);
		port->tx_aggr.aggr_num++;
		/* New aggregation begin, start समयr */
		अगर (!port->tx_aggr.समयr_cnxt.is_hold_समयr_set) अणु
			port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs =
					MWIFIEX_USB_TX_AGGR_TMO_MIN;
			समयout = port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs;
			mod_समयr(&port->tx_aggr.समयr_cnxt.hold_समयr,
				  jअगरfies + msecs_to_jअगरfies(समयout));
			port->tx_aggr.समयr_cnxt.is_hold_समयr_set = true;
		पूर्ण
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

अटल व्योम mwअगरiex_usb_tx_aggr_पंचांगo(काष्ठा समयr_list *t)
अणु
	काष्ठा urb_context *urb_cnxt = शून्य;
	काष्ठा sk_buff *skb_send = शून्य;
	काष्ठा tx_aggr_पंचांगr_cnxt *समयr_context =
		from_समयr(समयr_context, t, hold_समयr);
	काष्ठा mwअगरiex_adapter *adapter = समयr_context->adapter;
	काष्ठा usb_tx_data_port *port = समयr_context->port;
	पूर्णांक err = 0;

	spin_lock_bh(&port->tx_aggr_lock);
	err = mwअगरiex_usb_prepare_tx_aggr_skb(adapter, port, &skb_send);
	अगर (err) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "prepare tx aggr skb failed, err=%d\n", err);
		जाओ unlock;
	पूर्ण

	अगर (atomic_पढ़ो(&port->tx_data_urb_pending) >=
	    MWIFIEX_TX_DATA_URB) अणु
		port->block_status = true;
		adapter->data_sent =
			mwअगरiex_usb_data_sent(adapter);
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (port->tx_data_ix >= MWIFIEX_TX_DATA_URB)
		port->tx_data_ix = 0;

	urb_cnxt = &port->tx_data_list[port->tx_data_ix++];
	err = mwअगरiex_usb_स्थिरruct_send_urb(adapter, port, port->tx_data_ep,
					     urb_cnxt, skb_send);
करोne:
	अगर (err == -1)
		mwअगरiex_ग_लिखो_data_complete(adapter, skb_send, 0, -1);
unlock:
	spin_unlock_bh(&port->tx_aggr_lock);
पूर्ण

/* This function ग_लिखो a command/data packet to card. */
अटल पूर्णांक mwअगरiex_usb_host_to_card(काष्ठा mwअगरiex_adapter *adapter, u8 ep,
				    काष्ठा sk_buff *skb,
				    काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	काष्ठा usb_card_rec *card = adapter->card;
	काष्ठा urb_context *context = शून्य;
	काष्ठा usb_tx_data_port *port = शून्य;
	पूर्णांक idx, ret;

	अगर (test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: not allowed while suspended\n", __func__);
		वापस -1;
	पूर्ण

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR, "%s: device removed\n", __func__);
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO, "%s: ep=%d\n", __func__, ep);

	अगर (ep == card->tx_cmd_ep) अणु
		context = &card->tx_cmd;
	पूर्ण अन्यथा अणु
		/* get the data port काष्ठाure क्रम endpoपूर्णांक */
		क्रम (idx = 0; idx < MWIFIEX_TX_DATA_PORT; idx++) अणु
			अगर (ep == card->port[idx].tx_data_ep) अणु
				port = &card->port[idx];
				अगर (atomic_पढ़ो(&port->tx_data_urb_pending)
				    >= MWIFIEX_TX_DATA_URB) अणु
					port->block_status = true;
					adapter->data_sent =
						mwअगरiex_usb_data_sent(adapter);
					वापस -EBUSY;
				पूर्ण
				अगर (port->tx_data_ix >= MWIFIEX_TX_DATA_URB)
					port->tx_data_ix = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!port) अणु
			mwअगरiex_dbg(adapter, ERROR, "Wrong usb tx data port\n");
			वापस -1;
		पूर्ण

		अगर (adapter->bus_aggr.enable) अणु
			spin_lock_bh(&port->tx_aggr_lock);
			ret =  mwअगरiex_usb_aggr_tx_data(adapter, ep, skb,
							tx_param, port);
			spin_unlock_bh(&port->tx_aggr_lock);
			वापस ret;
		पूर्ण

		context = &port->tx_data_list[port->tx_data_ix++];
	पूर्ण

	वापस mwअगरiex_usb_स्थिरruct_send_urb(adapter, port, ep, context, skb);
पूर्ण

अटल पूर्णांक mwअगरiex_usb_tx_init(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;
	काष्ठा usb_tx_data_port *port;
	पूर्णांक i, j;

	card->tx_cmd.adapter = adapter;
	card->tx_cmd.ep = card->tx_cmd_ep;

	card->tx_cmd.urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!card->tx_cmd.urb)
		वापस -ENOMEM;

	क्रम (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) अणु
		port = &card->port[i];
		अगर (!port->tx_data_ep)
			जारी;
		port->tx_data_ix = 0;
		skb_queue_head_init(&port->tx_aggr.aggr_list);
		अगर (port->tx_data_ep == MWIFIEX_USB_EP_DATA)
			port->block_status = false;
		अन्यथा
			port->block_status = true;
		क्रम (j = 0; j < MWIFIEX_TX_DATA_URB; j++) अणु
			port->tx_data_list[j].adapter = adapter;
			port->tx_data_list[j].ep = port->tx_data_ep;
			port->tx_data_list[j].urb =
					usb_alloc_urb(0, GFP_KERNEL);
			अगर (!port->tx_data_list[j].urb)
				वापस -ENOMEM;
		पूर्ण

		port->tx_aggr.समयr_cnxt.adapter = adapter;
		port->tx_aggr.समयr_cnxt.port = port;
		port->tx_aggr.समयr_cnxt.is_hold_समयr_set = false;
		port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs = 0;
		समयr_setup(&port->tx_aggr.समयr_cnxt.hold_समयr,
			    mwअगरiex_usb_tx_aggr_पंचांगo, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_rx_init(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;
	पूर्णांक i;

	card->rx_cmd.adapter = adapter;
	card->rx_cmd.ep = card->rx_cmd_ep;

	card->rx_cmd.urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!card->rx_cmd.urb)
		वापस -ENOMEM;

	card->rx_cmd.skb = dev_alloc_skb(MWIFIEX_RX_CMD_BUF_SIZE);
	अगर (!card->rx_cmd.skb)
		वापस -ENOMEM;

	अगर (mwअगरiex_usb_submit_rx_urb(&card->rx_cmd, MWIFIEX_RX_CMD_BUF_SIZE))
		वापस -1;

	क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++) अणु
		card->rx_data_list[i].adapter = adapter;
		card->rx_data_list[i].ep = card->rx_data_ep;

		card->rx_data_list[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!card->rx_data_list[i].urb)
			वापस -1;
		अगर (mwअगरiex_usb_submit_rx_urb(&card->rx_data_list[i],
					      MWIFIEX_RX_DATA_BUF_SIZE))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* This function रेजिस्टर usb device and initialize parameter. */
अटल पूर्णांक mwअगरiex_रेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;

	card->adapter = adapter;

	चयन (le16_to_cpu(card->udev->descriptor.idProduct)) अणु
	हाल USB8997_PID_1:
	हाल USB8997_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K;
		म_नकल(adapter->fw_name, USB8997_DEFAULT_FW_NAME);
		adapter->ext_scan = true;
		अवरोध;
	हाल USB8766_PID_1:
	हाल USB8766_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		म_नकल(adapter->fw_name, USB8766_DEFAULT_FW_NAME);
		adapter->ext_scan = true;
		अवरोध;
	हाल USB8801_PID_1:
	हाल USB8801_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		म_नकल(adapter->fw_name, USB8801_DEFAULT_FW_NAME);
		adapter->ext_scan = false;
		अवरोध;
	हाल USB8797_PID_1:
	हाल USB8797_PID_2:
	शेष:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		म_नकल(adapter->fw_name, USB8797_DEFAULT_FW_NAME);
		अवरोध;
	पूर्ण

	adapter->usb_mc_status = false;
	adapter->usb_mc_setup = false;

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_usb_cleanup_tx_aggr(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;
	काष्ठा usb_tx_data_port *port;
	काष्ठा sk_buff *skb_पंचांगp;
	पूर्णांक idx;

	क्रम (idx = 0; idx < MWIFIEX_TX_DATA_PORT; idx++) अणु
		port = &card->port[idx];
		अगर (adapter->bus_aggr.enable)
			जबतक ((skb_पंचांगp =
				skb_dequeue(&port->tx_aggr.aggr_list)))
				mwअगरiex_ग_लिखो_data_complete(adapter, skb_पंचांगp,
							    0, -1);
		अगर (port->tx_aggr.समयr_cnxt.hold_समयr.function)
			del_समयr_sync(&port->tx_aggr.समयr_cnxt.hold_समयr);
		port->tx_aggr.समयr_cnxt.is_hold_समयr_set = false;
		port->tx_aggr.समयr_cnxt.hold_पंचांगo_msecs = 0;
	पूर्ण
पूर्ण

अटल व्योम mwअगरiex_unरेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;

	mwअगरiex_usb_मुक्त(card);

	mwअगरiex_usb_cleanup_tx_aggr(adapter);

	card->adapter = शून्य;
पूर्ण

अटल पूर्णांक mwअगरiex_prog_fw_w_helper(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा mwअगरiex_fw_image *fw)
अणु
	पूर्णांक ret = 0;
	u8 *firmware = fw->fw_buf, *recv_buff;
	u32 retries = USB8XXX_FW_MAX_RETRY + 1;
	u32 dlen;
	u32 fw_seqnum = 0, tlen = 0, dnld_cmd = 0;
	काष्ठा fw_data *fwdata;
	काष्ठा fw_sync_header sync_fw;
	u8 check_winner = 1;

	अगर (!firmware) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "No firmware image found! Terminating download\n");
		ret = -1;
		जाओ fw_निकास;
	पूर्ण

	/* Allocate memory क्रम transmit */
	fwdata = kzalloc(FW_DNLD_TX_BUF_SIZE, GFP_KERNEL);
	अगर (!fwdata) अणु
		ret = -ENOMEM;
		जाओ fw_निकास;
	पूर्ण

	/* Allocate memory क्रम receive */
	recv_buff = kzalloc(FW_DNLD_RX_BUF_SIZE, GFP_KERNEL);
	अगर (!recv_buff) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	करो अणु
		/* Send pseuकरो data to check winner status first */
		अगर (check_winner) अणु
			स_रखो(&fwdata->fw_hdr, 0, माप(काष्ठा fw_header));
			dlen = 0;
		पूर्ण अन्यथा अणु
			/* copy the header of the fw_data to get the length */
			स_नकल(&fwdata->fw_hdr, &firmware[tlen],
			       माप(काष्ठा fw_header));

			dlen = le32_to_cpu(fwdata->fw_hdr.data_len);
			dnld_cmd = le32_to_cpu(fwdata->fw_hdr.dnld_cmd);
			tlen += माप(काष्ठा fw_header);

			/* Command 7 करोesn't have data length field */
			अगर (dnld_cmd == FW_CMD_7)
				dlen = 0;

			स_नकल(fwdata->data, &firmware[tlen], dlen);

			fwdata->seq_num = cpu_to_le32(fw_seqnum);
			tlen += dlen;
		पूर्ण

		/* If the send/receive fails or CRC occurs then retry */
		जबतक (--retries) अणु
			u8 *buf = (u8 *)fwdata;
			u32 len = FW_DATA_XMIT_SIZE;

			/* send the firmware block */
			ret = mwअगरiex_ग_लिखो_data_sync(adapter, buf, &len,
						MWIFIEX_USB_EP_CMD_EVENT,
						MWIFIEX_USB_TIMEOUT);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "write_data_sync: failed: %d\n",
					    ret);
				जारी;
			पूर्ण

			buf = recv_buff;
			len = FW_DNLD_RX_BUF_SIZE;

			/* Receive the firmware block response */
			ret = mwअगरiex_पढ़ो_data_sync(adapter, buf, &len,
						MWIFIEX_USB_EP_CMD_EVENT,
						MWIFIEX_USB_TIMEOUT);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "read_data_sync: failed: %d\n",
					    ret);
				जारी;
			पूर्ण

			स_नकल(&sync_fw, recv_buff,
			       माप(काष्ठा fw_sync_header));

			/* check 1st firmware block resp क्रम highest bit set */
			अगर (check_winner) अणु
				अगर (le32_to_cpu(sync_fw.cmd) & 0x80000000) अणु
					mwअगरiex_dbg(adapter, WARN,
						    "USB is not the winner %#x\n",
						    sync_fw.cmd);

					/* वापसing success */
					ret = 0;
					जाओ cleanup;
				पूर्ण

				mwअगरiex_dbg(adapter, MSG,
					    "start to download FW...\n");

				check_winner = 0;
				अवरोध;
			पूर्ण

			/* check the firmware block response क्रम CRC errors */
			अगर (sync_fw.cmd) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "FW received block with CRC %#x\n",
					    sync_fw.cmd);
				ret = -1;
				जारी;
			पूर्ण

			retries = USB8XXX_FW_MAX_RETRY + 1;
			अवरोध;
		पूर्ण
		fw_seqnum++;
	पूर्ण जबतक ((dnld_cmd != FW_HAS_LAST_BLOCK) && retries);

cleanup:
	mwअगरiex_dbg(adapter, MSG,
		    "info: FW download over, size %d bytes\n", tlen);

	kमुक्त(recv_buff);
	kमुक्त(fwdata);

	अगर (retries)
		ret = 0;
fw_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_dnld_fw(काष्ठा mwअगरiex_adapter *adapter,
			काष्ठा mwअगरiex_fw_image *fw)
अणु
	पूर्णांक ret;
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;

	अगर (card->usb_boot_state == USB8XXX_FW_DNLD) अणु
		ret = mwअगरiex_prog_fw_w_helper(adapter, fw);
		अगर (ret)
			वापस -1;

		/* Boot state changes after successful firmware करोwnload */
		अगर (card->usb_boot_state == USB8XXX_FW_DNLD)
			वापस -1;
	पूर्ण

	ret = mwअगरiex_usb_rx_init(adapter);
	अगर (!ret)
		ret = mwअगरiex_usb_tx_init(adapter);

	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_submit_rx_urb(काष्ठा mwअगरiex_adapter *adapter, u8 ep)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;

	skb_push(card->rx_cmd.skb, INTF_HEADER_LEN);
	अगर ((ep == card->rx_cmd_ep) &&
	    (!atomic_पढ़ो(&card->rx_cmd_urb_pending)))
		mwअगरiex_usb_submit_rx_urb(&card->rx_cmd,
					  MWIFIEX_RX_CMD_BUF_SIZE);

	वापस;
पूर्ण

अटल पूर्णांक mwअगरiex_usb_cmd_event_complete(काष्ठा mwअगरiex_adapter *adapter,
				       काष्ठा sk_buff *skb)
अणु
	mwअगरiex_submit_rx_urb(adapter, MWIFIEX_USB_EP_CMD_EVENT);

	वापस 0;
पूर्ण

/* This function wakes up the card. */
अटल पूर्णांक mwअगरiex_pm_wakeup_card(काष्ठा mwअगरiex_adapter *adapter)
अणु
	/* Simulation of HS_AWAKE event */
	adapter->pm_wakeup_fw_try = false;
	del_समयr(&adapter->wakeup_समयr);
	adapter->pm_wakeup_card_req = false;
	adapter->ps_state = PS_STATE_AWAKE;

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_usb_submit_rem_rx_urbs(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा usb_card_rec *card = (काष्ठा usb_card_rec *)adapter->card;
	पूर्णांक i;
	काष्ठा urb_context *ctx;

	क्रम (i = 0; i < MWIFIEX_RX_DATA_URB; i++) अणु
		अगर (card->rx_data_list[i].skb)
			जारी;
		ctx = &card->rx_data_list[i];
		mwअगरiex_usb_submit_rx_urb(ctx, MWIFIEX_RX_DATA_BUF_SIZE);
	पूर्ण
पूर्ण

/* This function is called after the card has woken up. */
अटल अंतरभूत पूर्णांक
mwअगरiex_pm_wakeup_card_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा mwअगरiex_अगर_ops usb_ops = अणु
	.रेजिस्टर_dev =		mwअगरiex_रेजिस्टर_dev,
	.unरेजिस्टर_dev =	mwअगरiex_unरेजिस्टर_dev,
	.wakeup =		mwअगरiex_pm_wakeup_card,
	.wakeup_complete =	mwअगरiex_pm_wakeup_card_complete,

	/* USB specअगरic */
	.dnld_fw =		mwअगरiex_usb_dnld_fw,
	.cmdrsp_complete =	mwअगरiex_usb_cmd_event_complete,
	.event_complete =	mwअगरiex_usb_cmd_event_complete,
	.host_to_card =		mwअगरiex_usb_host_to_card,
	.submit_rem_rx_urbs =	mwअगरiex_usb_submit_rem_rx_urbs,
	.multi_port_resync =	mwअगरiex_usb_port_resync,
	.is_port_पढ़ोy =	mwअगरiex_usb_is_port_पढ़ोy,
पूर्ण;

module_usb_driver(mwअगरiex_usb_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell WiFi-Ex USB Driver version" USB_VERSION);
MODULE_VERSION(USB_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(USB8766_DEFAULT_FW_NAME);
MODULE_FIRMWARE(USB8797_DEFAULT_FW_NAME);
MODULE_FIRMWARE(USB8801_DEFAULT_FW_NAME);
MODULE_FIRMWARE(USB8997_DEFAULT_FW_NAME);
