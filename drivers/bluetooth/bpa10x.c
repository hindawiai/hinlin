<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Digianswer Bluetooth USB driver
 *
 *  Copyright (C) 2004-2007  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>

#समावेश <linux/usb.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "h4_recv.h"

#घोषणा VERSION "0.11"

अटल स्थिर काष्ठा usb_device_id bpa10x_table[] = अणु
	/* Tektronix BPA 100/105 (Digianswer) */
	अणु USB_DEVICE(0x08fd, 0x0002) पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, bpa10x_table);

काष्ठा bpa10x_data अणु
	काष्ठा hci_dev    *hdev;
	काष्ठा usb_device *udev;

	काष्ठा usb_anchor tx_anchor;
	काष्ठा usb_anchor rx_anchor;

	काष्ठा sk_buff *rx_skb[2];
पूर्ण;

अटल व्योम bpa10x_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा hci_dev *hdev = (काष्ठा hci_dev *) skb->dev;

	BT_DBG("%s urb %p status %d count %d", hdev->name,
					urb, urb->status, urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		जाओ करोne;

	अगर (!urb->status)
		hdev->stat.byte_tx += urb->transfer_buffer_length;
	अन्यथा
		hdev->stat.err_tx++;

करोne:
	kमुक्त(urb->setup_packet);

	kमुक्त_skb(skb);
पूर्ण

#घोषणा HCI_VENDOR_HDR_SIZE 5

#घोषणा HCI_RECV_VENDOR \
	.type = HCI_VENDOR_PKT, \
	.hlen = HCI_VENDOR_HDR_SIZE, \
	.loff = 3, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE

अटल स्थिर काष्ठा h4_recv_pkt bpa10x_recv_pkts[] = अणु
	अणु H4_RECV_ACL,     .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,     .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT,   .recv = hci_recv_frame पूर्ण,
	अणु HCI_RECV_VENDOR, .recv = hci_recv_diag  पूर्ण,
पूर्ण;

अटल व्योम bpa10x_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s urb %p status %d count %d", hdev->name,
					urb, urb->status, urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस;

	अगर (urb->status == 0) अणु
		bool idx = usb_pipebulk(urb->pipe);

		data->rx_skb[idx] = h4_recv_buf(hdev, data->rx_skb[idx],
						urb->transfer_buffer,
						urb->actual_length,
						bpa10x_recv_pkts,
						ARRAY_SIZE(bpa10x_recv_pkts));
		अगर (IS_ERR(data->rx_skb[idx])) अणु
			bt_dev_err(hdev, "corrupted event packet");
			hdev->stat.err_rx++;
			data->rx_skb[idx] = शून्य;
		पूर्ण
	पूर्ण

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "urb %p failed to resubmit (%d)", urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक bpa10x_submit_पूर्णांकr_urb(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size = 16;

	BT_DBG("%s", hdev->name);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvपूर्णांकpipe(data->udev, 0x81);

	usb_fill_पूर्णांक_urb(urb, data->udev, pipe, buf, size,
						bpa10x_rx_complete, hdev, 1);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "urb %p submission failed (%d)", urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक bpa10x_submit_bulk_urb(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size = 64;

	BT_DBG("%s", hdev->name);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvbulkpipe(data->udev, 0x82);

	usb_fill_bulk_urb(urb, data->udev, pipe,
					buf, size, bpa10x_rx_complete, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "urb %p submission failed (%d)", urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल पूर्णांक bpa10x_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	err = bpa10x_submit_पूर्णांकr_urb(hdev);
	अगर (err < 0)
		जाओ error;

	err = bpa10x_submit_bulk_urb(hdev);
	अगर (err < 0)
		जाओ error;

	वापस 0;

error:
	usb_समाप्त_anchored_urbs(&data->rx_anchor);

	वापस err;
पूर्ण

अटल पूर्णांक bpa10x_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_समाप्त_anchored_urbs(&data->rx_anchor);

	वापस 0;
पूर्ण

अटल पूर्णांक bpa10x_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_समाप्त_anchored_urbs(&data->tx_anchor);

	वापस 0;
पूर्ण

अटल पूर्णांक bpa10x_setup(काष्ठा hci_dev *hdev)
अणु
	अटल स्थिर u8 req[] = अणु 0x07 पूर्ण;
	काष्ठा sk_buff *skb;

	BT_DBG("%s", hdev->name);

	/* Read revision string */
	skb = __hci_cmd_sync(hdev, 0xfc0e, माप(req), req, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (अक्षर *)(skb->data + 1));

	hci_set_fw_info(hdev, "%s", skb->data + 1);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक bpa10x_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bpa10x_data *data = hci_get_drvdata(hdev);
	काष्ठा usb_ctrlrequest *dr;
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	skb->dev = (व्योम *) hdev;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	/* Prepend skb with frame type */
	*(u8 *)skb_push(skb, 1) = hci_skb_pkt_type(skb);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		dr = kदो_स्मृति(माप(*dr), GFP_KERNEL);
		अगर (!dr) अणु
			usb_मुक्त_urb(urb);
			वापस -ENOMEM;
		पूर्ण

		dr->bRequestType = USB_TYPE_VENDOR;
		dr->bRequest     = 0;
		dr->wIndex       = 0;
		dr->wValue       = 0;
		dr->wLength      = __cpu_to_le16(skb->len);

		pipe = usb_sndctrlpipe(data->udev, 0x00);

		usb_fill_control_urb(urb, data->udev, pipe, (व्योम *) dr,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.cmd_tx++;
		अवरोध;

	हाल HCI_ACLDATA_PKT:
		pipe = usb_sndbulkpipe(data->udev, 0x02);

		usb_fill_bulk_urb(urb, data->udev, pipe,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.acl_tx++;
		अवरोध;

	हाल HCI_SCODATA_PKT:
		pipe = usb_sndbulkpipe(data->udev, 0x02);

		usb_fill_bulk_urb(urb, data->udev, pipe,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.sco_tx++;
		अवरोध;

	शेष:
		usb_मुक्त_urb(urb);
		वापस -EILSEQ;
	पूर्ण

	usb_anchor_urb(urb, &data->tx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "urb %p submission failed", urb);
		kमुक्त(urb->setup_packet);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल पूर्णांक bpa10x_set_diag(काष्ठा hci_dev *hdev, bool enable)
अणु
	स्थिर u8 req[] = अणु 0x00, enable पूर्ण;
	काष्ठा sk_buff *skb;

	BT_DBG("%s", hdev->name);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस -ENETDOWN;

	/* Enable snअगरfer operation */
	skb = __hci_cmd_sync(hdev, 0xfc0e, माप(req), req, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक bpa10x_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा bpa10x_data *data;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	BT_DBG("intf %p id %p", पूर्णांकf, id);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
		वापस -ENODEV;

	data = devm_kzalloc(&पूर्णांकf->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	init_usb_anchor(&data->tx_anchor);
	init_usb_anchor(&data->rx_anchor);

	hdev = hci_alloc_dev();
	अगर (!hdev)
		वापस -ENOMEM;

	hdev->bus = HCI_USB;
	hci_set_drvdata(hdev, data);

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &पूर्णांकf->dev);

	hdev->खोलो     = bpa10x_खोलो;
	hdev->बंद    = bpa10x_बंद;
	hdev->flush    = bpa10x_flush;
	hdev->setup    = bpa10x_setup;
	hdev->send     = bpa10x_send_frame;
	hdev->set_diag = bpa10x_set_diag;

	set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		hci_मुक्त_dev(hdev);
		वापस err;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, data);

	वापस 0;
पूर्ण

अटल व्योम bpa10x_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा bpa10x_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);

	BT_DBG("intf %p", पूर्णांकf);

	अगर (!data)
		वापस;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	hci_unरेजिस्टर_dev(data->hdev);

	hci_मुक्त_dev(data->hdev);
	kमुक्त_skb(data->rx_skb[0]);
	kमुक्त_skb(data->rx_skb[1]);
पूर्ण

अटल काष्ठा usb_driver bpa10x_driver = अणु
	.name		= "bpa10x",
	.probe		= bpa10x_probe,
	.disconnect	= bpa10x_disconnect,
	.id_table	= bpa10x_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(bpa10x_driver);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Digianswer Bluetooth USB driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
