<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB network पूर्णांकerface driver क्रम Samsung Kalmia based LTE USB modem like the
 * Samsung GT-B3730 and GT-B3710.
 *
 * Copyright (C) 2011 Marius Bjoernstad Kotsbak <marius@kotsbak.com>
 *
 * Sponsored by Quicklink Video Distribution Services Ltd.
 *
 * Based on the cdc_eem module.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/gfp.h>

/*
 * The Samsung Kalmia based LTE USB modems have a CDC ACM port क्रम modem control
 * handled by the "option" module and an ethernet data port handled by this
 * module.
 *
 * The stick must first be चयनed पूर्णांकo modem mode by usb_modeचयन
 * or similar tool. Then the modem माला_लो sent two initialization packets by
 * this module, which gives the MAC address of the device. User space can then
 * connect the modem using AT commands through the ACM port and then use
 * DHCP on the network पूर्णांकerface exposed by this module. Network packets are
 * sent to and from the modem in a proprietary क्रमmat discovered after watching
 * the behavior of the winकरोws driver क्रम the modem.
 *
 * More inक्रमmation about the use of the modem is available in usb_modeचयन
 * क्रमum and the project page:
 *
 * http://www.draisberghof.de/usb_modeचयन/bb/viewtopic.php?t=465
 * https://github.com/mkotsbak/Samsung-GT-B3730-linux-driver
 */

/* #घोषणा	DEBUG */
/* #घोषणा	VERBOSE */

#घोषणा KALMIA_HEADER_LENGTH 6
#घोषणा KALMIA_ALIGN_SIZE 4
#घोषणा KALMIA_USB_TIMEOUT 10000

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
kalmia_send_init_packet(काष्ठा usbnet *dev, u8 *init_msg, u8 init_msg_len,
	u8 *buffer, u8 expected_len)
अणु
	पूर्णांक act_len;
	पूर्णांक status;

	netdev_dbg(dev->net, "Sending init packet");

	status = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 0x02),
		init_msg, init_msg_len, &act_len, KALMIA_USB_TIMEOUT);
	अगर (status != 0) अणु
		netdev_err(dev->net,
			"Error sending init packet. Status %i, length %i\n",
			status, act_len);
		वापस status;
	पूर्ण
	अन्यथा अगर (act_len != init_msg_len) अणु
		netdev_err(dev->net,
			"Did not send all of init packet. Bytes sent: %i",
			act_len);
	पूर्ण
	अन्यथा अणु
		netdev_dbg(dev->net, "Successfully sent init packet.");
	पूर्ण

	status = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, 0x81),
		buffer, expected_len, &act_len, KALMIA_USB_TIMEOUT);

	अगर (status != 0)
		netdev_err(dev->net,
			"Error receiving init result. Status %i, length %i\n",
			status, act_len);
	अन्यथा अगर (act_len != expected_len)
		netdev_err(dev->net, "Unexpected init result length: %i\n",
			act_len);

	वापस status;
पूर्ण

अटल पूर्णांक
kalmia_init_and_get_ethernet_addr(काष्ठा usbnet *dev, u8 *ethernet_addr)
अणु
	अटल स्थिर अक्षर init_msg_1[] =
		अणु 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x00 पूर्ण;
	अटल स्थिर अक्षर init_msg_2[] =
		अणु 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xf4,
		0x00, 0x00 पूर्ण;
	अटल स्थिर पूर्णांक buflen = 28;
	अक्षर *usb_buf;
	पूर्णांक status;

	usb_buf = kदो_स्मृति(buflen, GFP_DMA | GFP_KERNEL);
	अगर (!usb_buf)
		वापस -ENOMEM;

	स_नकल(usb_buf, init_msg_1, 12);
	status = kalmia_send_init_packet(dev, usb_buf, ARRAY_SIZE(init_msg_1),
					 usb_buf, 24);
	अगर (status != 0)
		जाओ out;

	स_नकल(usb_buf, init_msg_2, 12);
	status = kalmia_send_init_packet(dev, usb_buf, ARRAY_SIZE(init_msg_2),
					 usb_buf, 28);
	अगर (status != 0)
		जाओ out;

	स_नकल(ethernet_addr, usb_buf + 10, ETH_ALEN);
out:
	kमुक्त(usb_buf);
	वापस status;
पूर्ण

अटल पूर्णांक
kalmia_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status;
	u8 ethernet_addr[ETH_ALEN];

	/* Don't bind to AT command पूर्णांकerface */
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC)
		वापस -EINVAL;

	dev->in = usb_rcvbulkpipe(dev->udev, 0x81 & USB_ENDPOINT_NUMBER_MASK);
	dev->out = usb_sndbulkpipe(dev->udev, 0x02 & USB_ENDPOINT_NUMBER_MASK);
	dev->status = शून्य;

	dev->net->hard_header_len += KALMIA_HEADER_LENGTH;
	dev->hard_mtu = 1400;
	dev->rx_urb_size = dev->hard_mtu * 10; // Found as optimal after testing

	status = kalmia_init_and_get_ethernet_addr(dev, ethernet_addr);
	अगर (status)
		वापस status;

	स_नकल(dev->net->dev_addr, ethernet_addr, ETH_ALEN);

	वापस status;
पूर्ण

अटल काष्ठा sk_buff *
kalmia_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sk_buff *skb2 = शून्य;
	u16 content_len;
	अचिन्हित अक्षर *header_start;
	अचिन्हित अक्षर ether_type_1, ether_type_2;
	u8 reमुख्यder, padlen = 0;

	अगर (!skb_cloned(skb)) अणु
		पूर्णांक headroom = skb_headroom(skb);
		पूर्णांक tailroom = skb_tailroom(skb);

		अगर ((tailroom >= KALMIA_ALIGN_SIZE) && (headroom
			>= KALMIA_HEADER_LENGTH))
			जाओ करोne;

		अगर ((headroom + tailroom) > (KALMIA_HEADER_LENGTH
			+ KALMIA_ALIGN_SIZE)) अणु
			skb->data = स_हटाओ(skb->head + KALMIA_HEADER_LENGTH,
				skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
			जाओ करोne;
		पूर्ण
	पूर्ण

	skb2 = skb_copy_expand(skb, KALMIA_HEADER_LENGTH,
		KALMIA_ALIGN_SIZE, flags);
	अगर (!skb2)
		वापस शून्य;

	dev_kमुक्त_skb_any(skb);
	skb = skb2;

करोne:
	header_start = skb_push(skb, KALMIA_HEADER_LENGTH);
	ether_type_1 = header_start[KALMIA_HEADER_LENGTH + 12];
	ether_type_2 = header_start[KALMIA_HEADER_LENGTH + 13];

	netdev_dbg(dev->net, "Sending etherType: %02x%02x", ether_type_1,
		ether_type_2);

	/* According to empiric data क्रम data packages */
	header_start[0] = 0x57;
	header_start[1] = 0x44;
	content_len = skb->len - KALMIA_HEADER_LENGTH;

	put_unaligned_le16(content_len, &header_start[2]);
	header_start[4] = ether_type_1;
	header_start[5] = ether_type_2;

	/* Align to 4 bytes by padding with zeros */
	reमुख्यder = skb->len % KALMIA_ALIGN_SIZE;
	अगर (reमुख्यder > 0) अणु
		padlen = KALMIA_ALIGN_SIZE - reमुख्यder;
		skb_put_zero(skb, padlen);
	पूर्ण

	netdev_dbg(dev->net,
		"Sending package with length %i and padding %i. Header: %6phC.",
		content_len, padlen, header_start);

	वापस skb;
पूर्ण

अटल पूर्णांक
kalmia_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	/*
	 * Our task here is to strip off framing, leaving skb with one
	 * data frame क्रम the usbnet framework code to process.
	 */
	अटल स्थिर u8 HEADER_END_OF_USB_PACKET[] =
		अणु 0x57, 0x5a, 0x00, 0x00, 0x08, 0x00 पूर्ण;
	अटल स्थिर u8 EXPECTED_UNKNOWN_HEADER_1[] =
		अणु 0x57, 0x43, 0x1e, 0x00, 0x15, 0x02 पूर्ण;
	अटल स्थिर u8 EXPECTED_UNKNOWN_HEADER_2[] =
		अणु 0x57, 0x50, 0x0e, 0x00, 0x00, 0x00 पूर्ण;
	पूर्णांक i = 0;

	/* incomplete header? */
	अगर (skb->len < KALMIA_HEADER_LENGTH)
		वापस 0;

	करो अणु
		काष्ठा sk_buff *skb2 = शून्य;
		u8 *header_start;
		u16 usb_packet_length, ether_packet_length;
		पूर्णांक is_last;

		header_start = skb->data;

		अगर (unlikely(header_start[0] != 0x57 || header_start[1] != 0x44)) अणु
			अगर (!स_भेद(header_start, EXPECTED_UNKNOWN_HEADER_1,
				माप(EXPECTED_UNKNOWN_HEADER_1)) || !स_भेद(
				header_start, EXPECTED_UNKNOWN_HEADER_2,
				माप(EXPECTED_UNKNOWN_HEADER_2))) अणु
				netdev_dbg(dev->net,
					"Received expected unknown frame header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
			पूर्ण
			अन्यथा अणु
				netdev_err(dev->net,
					"Received unknown frame header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
				वापस 0;
			पूर्ण
		पूर्ण
		अन्यथा
			netdev_dbg(dev->net,
				"Received header: %6phC. Package length: %i\n",
				header_start, skb->len - KALMIA_HEADER_LENGTH);

		/* subtract start header and end header */
		usb_packet_length = skb->len - (2 * KALMIA_HEADER_LENGTH);
		ether_packet_length = get_unaligned_le16(&header_start[2]);
		skb_pull(skb, KALMIA_HEADER_LENGTH);

		/* Some small packets misses end marker */
		अगर (usb_packet_length < ether_packet_length) अणु
			ether_packet_length = usb_packet_length
				+ KALMIA_HEADER_LENGTH;
			is_last = true;
		पूर्ण
		अन्यथा अणु
			netdev_dbg(dev->net, "Correct package length #%i", i
				+ 1);

			is_last = (स_भेद(skb->data + ether_packet_length,
				HEADER_END_OF_USB_PACKET,
				माप(HEADER_END_OF_USB_PACKET)) == 0);
			अगर (!is_last) अणु
				header_start = skb->data + ether_packet_length;
				netdev_dbg(dev->net,
					"End header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
			पूर्ण
		पूर्ण

		अगर (is_last) अणु
			skb2 = skb;
		पूर्ण
		अन्यथा अणु
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (unlikely(!skb2))
				वापस 0;
		पूर्ण

		skb_trim(skb2, ether_packet_length);

		अगर (is_last) अणु
			वापस 1;
		पूर्ण
		अन्यथा अणु
			usbnet_skb_वापस(dev, skb2);
			skb_pull(skb, ether_packet_length);
		पूर्ण

		i++;
	पूर्ण
	जबतक (skb->len);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा driver_info kalmia_info = अणु
	.description = "Samsung Kalmia LTE USB dongle",
	.flags = FLAG_WWAN,
	.bind = kalmia_bind,
	.rx_fixup = kalmia_rx_fixup,
	.tx_fixup = kalmia_tx_fixup
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	/* The unचयनed USB ID, to get the module स्वतः loaded: */
	अणु USB_DEVICE(0x04e8, 0x689a) पूर्ण,
	/* The stick चयनed पूर्णांकo modem (by e.g. usb_modeचयन): */
	अणु USB_DEVICE(0x04e8, 0x6889),
		.driver_info = (अचिन्हित दीर्घ) &kalmia_info, पूर्ण,
	अणु /* EMPTY == end of list */पूर्ण पूर्ण;
MODULE_DEVICE_TABLE( usb, products);

अटल काष्ठा usb_driver kalmia_driver = अणु
	.name = "kalmia",
	.id_table = products,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(kalmia_driver);

MODULE_AUTHOR("Marius Bjoernstad Kotsbak <marius@kotsbak.com>");
MODULE_DESCRIPTION("Samsung Kalmia USB network driver");
MODULE_LICENSE("GPL");
