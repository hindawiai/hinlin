<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  AVM BlueFRITZ! USB driver
 *
 *  Copyright (C) 2003-2006  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>

#समावेश <linux/usb.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#घोषणा VERSION "1.2"

अटल काष्ठा usb_driver bfusb_driver;

अटल स्थिर काष्ठा usb_device_id bfusb_table[] = अणु
	/* AVM BlueFRITZ! USB */
	अणु USB_DEVICE(0x057c, 0x2200) पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, bfusb_table);

#घोषणा BFUSB_MAX_BLOCK_SIZE	256

#घोषणा BFUSB_BLOCK_TIMEOUT	3000

#घोषणा BFUSB_TX_PROCESS	1
#घोषणा BFUSB_TX_WAKEUP		2

#घोषणा BFUSB_MAX_BULK_TX	2
#घोषणा BFUSB_MAX_BULK_RX	2

काष्ठा bfusb_data अणु
	काष्ठा hci_dev		*hdev;

	अचिन्हित दीर्घ		state;

	काष्ठा usb_device	*udev;

	अचिन्हित पूर्णांक		bulk_in_ep;
	अचिन्हित पूर्णांक		bulk_out_ep;
	अचिन्हित पूर्णांक		bulk_pkt_size;

	rwlock_t		lock;

	काष्ठा sk_buff_head	transmit_q;

	काष्ठा sk_buff		*reassembly;

	atomic_t		pending_tx;
	काष्ठा sk_buff_head	pending_q;
	काष्ठा sk_buff_head	completed_q;
पूर्ण;

काष्ठा bfusb_data_scb अणु
	काष्ठा urb *urb;
पूर्ण;

अटल व्योम bfusb_tx_complete(काष्ठा urb *urb);
अटल व्योम bfusb_rx_complete(काष्ठा urb *urb);

अटल काष्ठा urb *bfusb_get_completed(काष्ठा bfusb_data *data)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा urb *urb = शून्य;

	BT_DBG("bfusb %p", data);

	skb = skb_dequeue(&data->completed_q);
	अगर (skb) अणु
		urb = ((काष्ठा bfusb_data_scb *) skb->cb)->urb;
		kमुक्त_skb(skb);
	पूर्ण

	वापस urb;
पूर्ण

अटल व्योम bfusb_unlink_urbs(काष्ठा bfusb_data *data)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा urb *urb;

	BT_DBG("bfusb %p", data);

	जबतक ((skb = skb_dequeue(&data->pending_q))) अणु
		urb = ((काष्ठा bfusb_data_scb *) skb->cb)->urb;
		usb_समाप्त_urb(urb);
		skb_queue_tail(&data->completed_q, skb);
	पूर्ण

	जबतक ((urb = bfusb_get_completed(data)))
		usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक bfusb_send_bulk(काष्ठा bfusb_data *data, काष्ठा sk_buff *skb)
अणु
	काष्ठा bfusb_data_scb *scb = (व्योम *) skb->cb;
	काष्ठा urb *urb = bfusb_get_completed(data);
	पूर्णांक err, pipe;

	BT_DBG("bfusb %p skb %p len %d", data, skb, skb->len);

	अगर (!urb) अणु
		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!urb)
			वापस -ENOMEM;
	पूर्ण

	pipe = usb_sndbulkpipe(data->udev, data->bulk_out_ep);

	usb_fill_bulk_urb(urb, data->udev, pipe, skb->data, skb->len,
			bfusb_tx_complete, skb);

	scb->urb = urb;

	skb_queue_tail(&data->pending_q, skb);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		bt_dev_err(data->hdev, "bulk tx submit failed urb %p err %d",
			   urb, err);
		skb_unlink(skb, &data->pending_q);
		usb_मुक्त_urb(urb);
	पूर्ण अन्यथा
		atomic_inc(&data->pending_tx);

	वापस err;
पूर्ण

अटल व्योम bfusb_tx_wakeup(काष्ठा bfusb_data *data)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("bfusb %p", data);

	अगर (test_and_set_bit(BFUSB_TX_PROCESS, &data->state)) अणु
		set_bit(BFUSB_TX_WAKEUP, &data->state);
		वापस;
	पूर्ण

	करो अणु
		clear_bit(BFUSB_TX_WAKEUP, &data->state);

		जबतक ((atomic_पढ़ो(&data->pending_tx) < BFUSB_MAX_BULK_TX) &&
				(skb = skb_dequeue(&data->transmit_q))) अणु
			अगर (bfusb_send_bulk(data, skb) < 0) अणु
				skb_queue_head(&data->transmit_q, skb);
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण जबतक (test_bit(BFUSB_TX_WAKEUP, &data->state));

	clear_bit(BFUSB_TX_PROCESS, &data->state);
पूर्ण

अटल व्योम bfusb_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *) urb->context;
	काष्ठा bfusb_data *data = (काष्ठा bfusb_data *) skb->dev;

	BT_DBG("bfusb %p urb %p skb %p len %d", data, urb, skb, skb->len);

	atomic_dec(&data->pending_tx);

	अगर (!test_bit(HCI_RUNNING, &data->hdev->flags))
		वापस;

	अगर (!urb->status)
		data->hdev->stat.byte_tx += skb->len;
	अन्यथा
		data->hdev->stat.err_tx++;

	पढ़ो_lock(&data->lock);

	skb_unlink(skb, &data->pending_q);
	skb_queue_tail(&data->completed_q, skb);

	bfusb_tx_wakeup(data);

	पढ़ो_unlock(&data->lock);
पूर्ण


अटल पूर्णांक bfusb_rx_submit(काष्ठा bfusb_data *data, काष्ठा urb *urb)
अणु
	काष्ठा bfusb_data_scb *scb;
	काष्ठा sk_buff *skb;
	पूर्णांक err, pipe, size = HCI_MAX_FRAME_SIZE + 32;

	BT_DBG("bfusb %p urb %p", data, urb);

	अगर (!urb) अणु
		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!urb)
			वापस -ENOMEM;
	पूर्ण

	skb = bt_skb_alloc(size, GFP_ATOMIC);
	अगर (!skb) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	skb->dev = (व्योम *) data;

	scb = (काष्ठा bfusb_data_scb *) skb->cb;
	scb->urb = urb;

	pipe = usb_rcvbulkpipe(data->udev, data->bulk_in_ep);

	usb_fill_bulk_urb(urb, data->udev, pipe, skb->data, size,
			bfusb_rx_complete, skb);

	skb_queue_tail(&data->pending_q, skb);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		bt_dev_err(data->hdev, "bulk rx submit failed urb %p err %d",
			   urb, err);
		skb_unlink(skb, &data->pending_q);
		kमुक्त_skb(skb);
		usb_मुक्त_urb(urb);
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक bfusb_recv_block(काष्ठा bfusb_data *data, पूर्णांक hdr, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	BT_DBG("bfusb %p hdr 0x%02x data %p len %d", data, hdr, buf, len);

	अगर (hdr & 0x10) अणु
		bt_dev_err(data->hdev, "error in block");
		kमुक्त_skb(data->reassembly);
		data->reassembly = शून्य;
		वापस -EIO;
	पूर्ण

	अगर (hdr & 0x04) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित अक्षर pkt_type;
		पूर्णांक pkt_len = 0;

		अगर (data->reassembly) अणु
			bt_dev_err(data->hdev, "unexpected start block");
			kमुक्त_skb(data->reassembly);
			data->reassembly = शून्य;
		पूर्ण

		अगर (len < 1) अणु
			bt_dev_err(data->hdev, "no packet type found");
			वापस -EPROTO;
		पूर्ण

		pkt_type = *buf++; len--;

		चयन (pkt_type) अणु
		हाल HCI_EVENT_PKT:
			अगर (len >= HCI_EVENT_HDR_SIZE) अणु
				काष्ठा hci_event_hdr *hdr = (काष्ठा hci_event_hdr *) buf;
				pkt_len = HCI_EVENT_HDR_SIZE + hdr->plen;
			पूर्ण अन्यथा अणु
				bt_dev_err(data->hdev, "event block is too short");
				वापस -EILSEQ;
			पूर्ण
			अवरोध;

		हाल HCI_ACLDATA_PKT:
			अगर (len >= HCI_ACL_HDR_SIZE) अणु
				काष्ठा hci_acl_hdr *hdr = (काष्ठा hci_acl_hdr *) buf;
				pkt_len = HCI_ACL_HDR_SIZE + __le16_to_cpu(hdr->dlen);
			पूर्ण अन्यथा अणु
				bt_dev_err(data->hdev, "data block is too short");
				वापस -EILSEQ;
			पूर्ण
			अवरोध;

		हाल HCI_SCODATA_PKT:
			अगर (len >= HCI_SCO_HDR_SIZE) अणु
				काष्ठा hci_sco_hdr *hdr = (काष्ठा hci_sco_hdr *) buf;
				pkt_len = HCI_SCO_HDR_SIZE + hdr->dlen;
			पूर्ण अन्यथा अणु
				bt_dev_err(data->hdev, "audio block is too short");
				वापस -EILSEQ;
			पूर्ण
			अवरोध;
		पूर्ण

		skb = bt_skb_alloc(pkt_len, GFP_ATOMIC);
		अगर (!skb) अणु
			bt_dev_err(data->hdev, "no memory for the packet");
			वापस -ENOMEM;
		पूर्ण

		hci_skb_pkt_type(skb) = pkt_type;

		data->reassembly = skb;
	पूर्ण अन्यथा अणु
		अगर (!data->reassembly) अणु
			bt_dev_err(data->hdev, "unexpected continuation block");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (len > 0)
		skb_put_data(data->reassembly, buf, len);

	अगर (hdr & 0x08) अणु
		hci_recv_frame(data->hdev, data->reassembly);
		data->reassembly = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bfusb_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *) urb->context;
	काष्ठा bfusb_data *data = (काष्ठा bfusb_data *) skb->dev;
	अचिन्हित अक्षर *buf = urb->transfer_buffer;
	पूर्णांक count = urb->actual_length;
	पूर्णांक err, hdr, len;

	BT_DBG("bfusb %p urb %p skb %p len %d", data, urb, skb, skb->len);

	पढ़ो_lock(&data->lock);

	अगर (!test_bit(HCI_RUNNING, &data->hdev->flags))
		जाओ unlock;

	अगर (urb->status || !count)
		जाओ resubmit;

	data->hdev->stat.byte_rx += count;

	skb_put(skb, count);

	जबतक (count) अणु
		hdr = buf[0] | (buf[1] << 8);

		अगर (hdr & 0x4000) अणु
			len = 0;
			count -= 2;
			buf   += 2;
		पूर्ण अन्यथा अणु
			len = (buf[2] == 0) ? 256 : buf[2];
			count -= 3;
			buf   += 3;
		पूर्ण

		अगर (count < len) अणु
			bt_dev_err(data->hdev, "block extends over URB buffer ranges");
		पूर्ण

		अगर ((hdr & 0xe1) == 0xc1)
			bfusb_recv_block(data, hdr, buf, len);

		count -= len;
		buf   += len;
	पूर्ण

	skb_unlink(skb, &data->pending_q);
	kमुक्त_skb(skb);

	bfusb_rx_submit(data, urb);

	पढ़ो_unlock(&data->lock);

	वापस;

resubmit:
	urb->dev = data->udev;

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		bt_dev_err(data->hdev, "bulk resubmit failed urb %p err %d",
			   urb, err);
	पूर्ण

unlock:
	पढ़ो_unlock(&data->lock);
पूर्ण

अटल पूर्णांक bfusb_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bfusb_data *data = hci_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	ग_लिखो_lock_irqsave(&data->lock, flags);

	err = bfusb_rx_submit(data, शून्य);
	अगर (!err) अणु
		क्रम (i = 1; i < BFUSB_MAX_BULK_RX; i++)
			bfusb_rx_submit(data, शून्य);
	पूर्ण

	ग_लिखो_unlock_irqrestore(&data->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक bfusb_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bfusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("hdev %p bfusb %p", hdev, data);

	skb_queue_purge(&data->transmit_q);

	वापस 0;
पूर्ण

अटल पूर्णांक bfusb_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bfusb_data *data = hci_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	ग_लिखो_lock_irqsave(&data->lock, flags);
	ग_लिखो_unlock_irqrestore(&data->lock, flags);

	bfusb_unlink_urbs(data);
	bfusb_flush(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक bfusb_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bfusb_data *data = hci_get_drvdata(hdev);
	काष्ठा sk_buff *nskb;
	अचिन्हित अक्षर buf[3];
	पूर्णांक sent = 0, size, count;

	BT_DBG("hdev %p skb %p type %d len %d", hdev, skb,
	       hci_skb_pkt_type(skb), skb->len);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		अवरोध;
	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		अवरोध;
	पूर्ण

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	count = skb->len;

	/* Max HCI frame size seems to be 1511 + 1 */
	nskb = bt_skb_alloc(count + 32, GFP_KERNEL);
	अगर (!nskb) अणु
		bt_dev_err(hdev, "Can't allocate memory for new packet");
		वापस -ENOMEM;
	पूर्ण

	nskb->dev = (व्योम *) data;

	जबतक (count) अणु
		size = min_t(uपूर्णांक, count, BFUSB_MAX_BLOCK_SIZE);

		buf[0] = 0xc1 | ((sent == 0) ? 0x04 : 0) | ((count == size) ? 0x08 : 0);
		buf[1] = 0x00;
		buf[2] = (size == BFUSB_MAX_BLOCK_SIZE) ? 0 : size;

		skb_put_data(nskb, buf, 3);
		skb_copy_from_linear_data_offset(skb, sent, skb_put(nskb, size), size);

		sent  += size;
		count -= size;
	पूर्ण

	/* Don't send frame with multiple size of bulk max packet */
	अगर ((nskb->len % data->bulk_pkt_size) == 0) अणु
		buf[0] = 0xdd;
		buf[1] = 0x00;
		skb_put_data(nskb, buf, 2);
	पूर्ण

	पढ़ो_lock(&data->lock);

	skb_queue_tail(&data->transmit_q, nskb);
	bfusb_tx_wakeup(data);

	पढ़ो_unlock(&data->lock);

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक bfusb_load_firmware(काष्ठा bfusb_data *data,
			       स्थिर अचिन्हित अक्षर *firmware, पूर्णांक count)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक err, pipe, len, size, sent = 0;

	BT_DBG("bfusb %p udev %p", data, data->udev);

	BT_INFO("BlueFRITZ! USB loading firmware");

	buf = kदो_स्मृति(BFUSB_MAX_BLOCK_SIZE + 3, GFP_KERNEL);
	अगर (!buf) अणु
		BT_ERR("Can't allocate memory chunk for firmware");
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_sndctrlpipe(data->udev, 0);

	अगर (usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 1, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT) < 0) अणु
		BT_ERR("Can't change to loading configuration");
		kमुक्त(buf);
		वापस -EBUSY;
	पूर्ण

	data->udev->toggle[0] = data->udev->toggle[1] = 0;

	pipe = usb_sndbulkpipe(data->udev, data->bulk_out_ep);

	जबतक (count) अणु
		size = min_t(uपूर्णांक, count, BFUSB_MAX_BLOCK_SIZE + 3);

		स_नकल(buf, firmware + sent, size);

		err = usb_bulk_msg(data->udev, pipe, buf, size,
					&len, BFUSB_BLOCK_TIMEOUT);

		अगर (err || (len != size)) अणु
			BT_ERR("Error in firmware loading");
			जाओ error;
		पूर्ण

		sent  += size;
		count -= size;
	पूर्ण

	err = usb_bulk_msg(data->udev, pipe, शून्य, 0,
					&len, BFUSB_BLOCK_TIMEOUT);
	अगर (err < 0) अणु
		BT_ERR("Error in null packet request");
		जाओ error;
	पूर्ण

	pipe = usb_sndctrlpipe(data->udev, 0);

	err = usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 2, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (err < 0) अणु
		BT_ERR("Can't change to running configuration");
		जाओ error;
	पूर्ण

	data->udev->toggle[0] = data->udev->toggle[1] = 0;

	BT_INFO("BlueFRITZ! USB device ready");

	kमुक्त(buf);
	वापस 0;

error:
	kमुक्त(buf);

	pipe = usb_sndctrlpipe(data->udev, 0);

	usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 0, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);

	वापस err;
पूर्ण

अटल पूर्णांक bfusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_endpoपूर्णांक *bulk_out_ep;
	काष्ठा usb_host_endpoपूर्णांक *bulk_in_ep;
	काष्ठा hci_dev *hdev;
	काष्ठा bfusb_data *data;

	BT_DBG("intf %p id %p", पूर्णांकf, id);

	/* Check number of endpoपूर्णांकs */
	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 2)
		वापस -EIO;

	bulk_out_ep = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[0];
	bulk_in_ep  = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[1];

	अगर (!bulk_out_ep || !bulk_in_ep) अणु
		BT_ERR("Bulk endpoints not found");
		जाओ करोne;
	पूर्ण

	/* Initialize control काष्ठाure and load firmware */
	data = devm_kzalloc(&पूर्णांकf->dev, माप(काष्ठा bfusb_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->udev = udev;
	data->bulk_in_ep    = bulk_in_ep->desc.bEndpoपूर्णांकAddress;
	data->bulk_out_ep   = bulk_out_ep->desc.bEndpoपूर्णांकAddress;
	data->bulk_pkt_size = le16_to_cpu(bulk_out_ep->desc.wMaxPacketSize);

	rwlock_init(&data->lock);

	data->reassembly = शून्य;

	skb_queue_head_init(&data->transmit_q);
	skb_queue_head_init(&data->pending_q);
	skb_queue_head_init(&data->completed_q);

	अगर (request_firmware(&firmware, "bfubase.frm", &udev->dev) < 0) अणु
		BT_ERR("Firmware request failed");
		जाओ करोne;
	पूर्ण

	BT_DBG("firmware data %p size %zu", firmware->data, firmware->size);

	अगर (bfusb_load_firmware(data, firmware->data, firmware->size) < 0) अणु
		BT_ERR("Firmware loading failed");
		जाओ release;
	पूर्ण

	release_firmware(firmware);

	/* Initialize and रेजिस्टर HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Can't allocate HCI device");
		जाओ करोne;
	पूर्ण

	data->hdev = hdev;

	hdev->bus = HCI_USB;
	hci_set_drvdata(hdev, data);
	SET_HCIDEV_DEV(hdev, &पूर्णांकf->dev);

	hdev->खोलो  = bfusb_खोलो;
	hdev->बंद = bfusb_बंद;
	hdev->flush = bfusb_flush;
	hdev->send  = bfusb_send_frame;

	set_bit(HCI_QUIRK_BROKEN_LOCAL_COMMANDS, &hdev->quirks);

	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		hci_मुक्त_dev(hdev);
		जाओ करोne;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, data);

	वापस 0;

release:
	release_firmware(firmware);

करोne:
	वापस -EIO;
पूर्ण

अटल व्योम bfusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा bfusb_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा hci_dev *hdev = data->hdev;

	BT_DBG("intf %p", पूर्णांकf);

	अगर (!hdev)
		वापस;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	bfusb_बंद(hdev);

	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);
पूर्ण

अटल काष्ठा usb_driver bfusb_driver = अणु
	.name		= "bfusb",
	.probe		= bfusb_probe,
	.disconnect	= bfusb_disconnect,
	.id_table	= bfusb_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(bfusb_driver);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("BlueFRITZ! USB driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("bfubase.frm");
