<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GeneSys GL620USB-A based links
 * Copyright (C) 2001 by Jiun-Jie Huang <huangjj@genesyslogic.com.tw>
 * Copyright (C) 2001 by Stanislav Brabec <utx@penguin.cz>
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/gfp.h>


/*
 * GeneSys GL620USB-A (www.genesyslogic.com.tw)
 *
 * ... should partially पूर्णांकerop with the Win32 driver क्रम this hardware.
 * The GeneSys करोcs imply there's some NDIS issue motivating this framing.
 *
 * Some info from GeneSys:
 *  - GL620USB-A is full duplex; GL620USB is only half duplex क्रम bulk.
 *    (Some cables, like the BAFO-100c, use the half duplex version.)
 *  - For the full duplex model, the low bit of the version code says
 *    which side is which ("left/right").
 *  - For the half duplex type, a control/पूर्णांकerrupt handshake settles
 *    the transfer direction.  (That's disabled here, partially coded.)
 *    A control URB would block until other side ग_लिखोs an पूर्णांकerrupt.
 *
 * Original code from Jiun-Jie Huang <huangjj@genesyslogic.com.tw>
 * and merged पूर्णांकo "usbnet" by Stanislav Brabec <utx@penguin.cz>.
 */

// control msg ग_लिखो command
#घोषणा GENELINK_CONNECT_WRITE			0xF0
// पूर्णांकerrupt pipe index
#घोषणा GENELINK_INTERRUPT_PIPE			0x03
// पूर्णांकerrupt पढ़ो buffer size
#घोषणा INTERRUPT_बफ_मानE			0x08
// पूर्णांकerrupt pipe पूर्णांकerval value
#घोषणा GENELINK_INTERRUPT_INTERVAL		0x10
// max transmit packet number per transmit
#घोषणा GL_MAX_TRANSMIT_PACKETS			32
// max packet length
#घोषणा GL_MAX_PACKET_LEN			1514
// max receive buffer size
#घोषणा GL_RCV_BUF_SIZE		\
	(((GL_MAX_PACKET_LEN + 4) * GL_MAX_TRANSMIT_PACKETS) + 4)

काष्ठा gl_packet अणु
	__le32		packet_length;
	अक्षर		packet_data [1];
पूर्ण;

काष्ठा gl_header अणु
	__le32			packet_count;
	काष्ठा gl_packet	packets;
पूर्ण;

अटल पूर्णांक genelink_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा gl_header	*header;
	काष्ठा gl_packet	*packet;
	काष्ठा sk_buff		*gl_skb;
	u32			size;
	u32			count;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	header = (काष्ठा gl_header *) skb->data;

	// get the packet count of the received skb
	count = le32_to_cpu(header->packet_count);
	अगर (count > GL_MAX_TRANSMIT_PACKETS) अणु
		netdev_dbg(dev->net,
			   "genelink: invalid received packet count %u\n",
			   count);
		वापस 0;
	पूर्ण

	// set the current packet poपूर्णांकer to the first packet
	packet = &header->packets;

	// decrement the length क्रम the packet count size 4 bytes
	skb_pull(skb, 4);

	जबतक (count > 1) अणु
		// get the packet length
		size = le32_to_cpu(packet->packet_length);

		// this may be a broken packet
		अगर (size > GL_MAX_PACKET_LEN) अणु
			netdev_dbg(dev->net, "genelink: invalid rx length %d\n",
				   size);
			वापस 0;
		पूर्ण

		// allocate the skb क्रम the inभागidual packet
		gl_skb = alloc_skb(size, GFP_ATOMIC);
		अगर (gl_skb) अणु

			// copy the packet data to the new skb
			skb_put_data(gl_skb, packet->packet_data, size);
			usbnet_skb_वापस(dev, gl_skb);
		पूर्ण

		// advance to the next packet
		packet = (काष्ठा gl_packet *)&packet->packet_data[size];
		count--;

		// shअगरt the data poपूर्णांकer to the next gl_packet
		skb_pull(skb, size + 4);
	पूर्ण

	// skip the packet length field 4 bytes
	skb_pull(skb, 4);

	अगर (skb->len > GL_MAX_PACKET_LEN) अणु
		netdev_dbg(dev->net, "genelink: invalid rx length %d\n",
			   skb->len);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *
genelink_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	पूर्णांक 	padlen;
	पूर्णांक	length = skb->len;
	पूर्णांक	headroom = skb_headroom(skb);
	पूर्णांक	tailroom = skb_tailroom(skb);
	__le32	*packet_count;
	__le32	*packet_len;

	// FIXME:  magic numbers, bleech
	padlen = ((skb->len + (4 + 4*1)) % 64) ? 0 : 1;

	अगर ((!skb_cloned(skb))
			&& ((headroom + tailroom) >= (padlen + (4 + 4*1)))) अणु
		अगर ((headroom < (4 + 4*1)) || (tailroom < padlen)) अणु
			skb->data = स_हटाओ(skb->head + (4 + 4*1),
					     skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff	*skb2;
		skb2 = skb_copy_expand(skb, (4 + 4*1) , padlen, flags);
		dev_kमुक्त_skb_any(skb);
		skb = skb2;
		अगर (!skb)
			वापस शून्य;
	पूर्ण

	// attach the packet count to the header
	packet_count = skb_push(skb, (4 + 4 * 1));
	packet_len = packet_count + 1;

	*packet_count = cpu_to_le32(1);
	*packet_len = cpu_to_le32(length);

	// add padding byte
	अगर ((skb->len % dev->maxpacket) == 0)
		skb_put(skb, 1);

	वापस skb;
पूर्ण

अटल पूर्णांक genelink_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	dev->hard_mtu = GL_RCV_BUF_SIZE;
	dev->net->hard_header_len += 4;
	dev->in = usb_rcvbulkpipe(dev->udev, dev->driver_info->in);
	dev->out = usb_sndbulkpipe(dev->udev, dev->driver_info->out);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info	genelink_info = अणु
	.description =	"Genesys GeneLink",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_GL | FLAG_NO_SETINT,
	.bind =		genelink_bind,
	.rx_fixup =	genelink_rx_fixup,
	.tx_fixup =	genelink_tx_fixup,

	.in = 1, .out = 2,

#अगर_घोषित	GENELINK_ACK
	.check_connect =genelink_check_connect,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा usb_device_id	products [] = अणु

अणु
	USB_DEVICE(0x05e3, 0x0502),	// GL620USB-A
	.driver_info =	(अचिन्हित दीर्घ) &genelink_info,
पूर्ण,
	/* NOT: USB_DEVICE(0x05e3, 0x0501),	// GL620USB
	 * that's half duplex, not currently supported
	 */
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver gl620a_driver = अणु
	.name =		"gl620a",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(gl620a_driver);

MODULE_AUTHOR("Jiun-Jie Huang");
MODULE_DESCRIPTION("GL620-USB-A Host-to-Host Link cables");
MODULE_LICENSE("GPL");

