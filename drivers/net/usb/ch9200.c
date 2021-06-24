<शैली गुरु>
/*
 * USB 10M/100M ethernet adapter
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>

#घोषणा CH9200_VID		0x1A86
#घोषणा CH9200_PID_E092		0xE092

#घोषणा CTRL_TIMEOUT_MS		1000

#घोषणा CONTROL_TIMEOUT_MS 1000

#घोषणा REQUEST_READ	0x0E
#घोषणा REQUEST_WRITE	0x0F

/* Address space:
 * 00-63 : MII
 * 64-128: MAC
 *
 * Note: all accesses must be 16-bit
 */

#घोषणा MAC_REG_CTRL 64
#घोषणा MAC_REG_STATUS 66
#घोषणा MAC_REG_INTERRUPT_MASK 68
#घोषणा MAC_REG_PHY_COMMAND 70
#घोषणा MAC_REG_PHY_DATA 72
#घोषणा MAC_REG_STATION_L 74
#घोषणा MAC_REG_STATION_M 76
#घोषणा MAC_REG_STATION_H 78
#घोषणा MAC_REG_HASH_L 80
#घोषणा MAC_REG_HASH_M1 82
#घोषणा MAC_REG_HASH_M2 84
#घोषणा MAC_REG_HASH_H 86
#घोषणा MAC_REG_THRESHOLD 88
#घोषणा MAC_REG_FIFO_DEPTH 90
#घोषणा MAC_REG_PAUSE 92
#घोषणा MAC_REG_FLOW_CONTROL 94

/* Control रेजिस्टर bits
 *
 * Note: bits 13 and 15 are reserved
 */
#घोषणा LOOPBACK		(0x01 << 14)
#घोषणा BASE100X		(0x01 << 12)
#घोषणा MBPS_10			(0x01 << 11)
#घोषणा DUPLEX_MODE		(0x01 << 10)
#घोषणा PAUSE_FRAME		(0x01 << 9)
#घोषणा PROMISCUOUS		(0x01 << 8)
#घोषणा MULTICAST		(0x01 << 7)
#घोषणा BROADCAST		(0x01 << 6)
#घोषणा HASH			(0x01 << 5)
#घोषणा APPEND_PAD		(0x01 << 4)
#घोषणा APPEND_CRC		(0x01 << 3)
#घोषणा TRANSMITTER_ACTION	(0x01 << 2)
#घोषणा RECEIVER_ACTION		(0x01 << 1)
#घोषणा DMA_ACTION		(0x01 << 0)

/* Status रेजिस्टर bits
 *
 * Note: bits 7-15 are reserved
 */
#घोषणा ALIGNMENT		(0x01 << 6)
#घोषणा FIFO_OVER_RUN		(0x01 << 5)
#घोषणा FIFO_UNDER_RUN		(0x01 << 4)
#घोषणा RX_ERROR		(0x01 << 3)
#घोषणा RX_COMPLETE		(0x01 << 2)
#घोषणा TX_ERROR		(0x01 << 1)
#घोषणा TX_COMPLETE		(0x01 << 0)

/* FIFO depth रेजिस्टर bits
 *
 * Note: bits 6 and 14 are reserved
 */

#घोषणा ETH_TXBD		(0x01 << 15)
#घोषणा ETN_TX_FIFO_DEPTH	(0x01 << 8)
#घोषणा ETH_RXBD		(0x01 << 7)
#घोषणा ETH_RX_FIFO_DEPTH	(0x01 << 0)

अटल पूर्णांक control_पढ़ो(काष्ठा usbnet *dev,
			अचिन्हित अक्षर request, अचिन्हित लघु value,
			अचिन्हित लघु index, व्योम *data, अचिन्हित लघु size,
			पूर्णांक समयout)
अणु
	अचिन्हित अक्षर *buf = शून्य;
	अचिन्हित अक्षर request_type;
	पूर्णांक err = 0;

	अगर (request == REQUEST_READ)
		request_type = (USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER);
	अन्यथा
		request_type = (USB_सूची_IN | USB_TYPE_VENDOR |
				USB_RECIP_DEVICE);

	netdev_dbg(dev->net, "%s() index=0x%02x size=%d\n",
		   __func__, index, size);

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	err = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      request, request_type, value, index, buf, size,
			      समयout);
	अगर (err == size)
		स_नकल(data, buf, size);
	अन्यथा अगर (err >= 0)
		err = -EINVAL;
	kमुक्त(buf);

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक control_ग_लिखो(काष्ठा usbnet *dev, अचिन्हित अक्षर request,
			 अचिन्हित लघु value, अचिन्हित लघु index,
			 व्योम *data, अचिन्हित लघु size, पूर्णांक समयout)
अणु
	अचिन्हित अक्षर *buf = शून्य;
	अचिन्हित अक्षर request_type;
	पूर्णांक err = 0;

	अगर (request == REQUEST_WRITE)
		request_type = (USB_सूची_OUT | USB_TYPE_VENDOR |
				USB_RECIP_OTHER);
	अन्यथा
		request_type = (USB_सूची_OUT | USB_TYPE_VENDOR |
				USB_RECIP_DEVICE);

	netdev_dbg(dev->net, "%s() index=0x%02x size=%d\n",
		   __func__, index, size);

	अगर (data) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण

	err = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      request, request_type, value, index, buf, size,
			      समयout);
	अगर (err >= 0 && err < size)
		err = -EINVAL;
	kमुक्त(buf);

	वापस 0;

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक ch9200_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	अचिन्हित अक्षर buff[2];

	netdev_dbg(netdev, "%s phy_id:%02x loc:%02x\n",
		   __func__, phy_id, loc);

	अगर (phy_id != 0)
		वापस -ENODEV;

	control_पढ़ो(dev, REQUEST_READ, 0, loc * 2, buff, 0x02,
		     CONTROL_TIMEOUT_MS);

	वापस (buff[0] | buff[1] << 8);
पूर्ण

अटल व्योम ch9200_mdio_ग_लिखो(काष्ठा net_device *netdev,
			      पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	अचिन्हित अक्षर buff[2];

	netdev_dbg(netdev, "%s() phy_id=%02x loc:%02x\n",
		   __func__, phy_id, loc);

	अगर (phy_id != 0)
		वापस;

	buff[0] = (अचिन्हित अक्षर)val;
	buff[1] = (अचिन्हित अक्षर)(val >> 8);

	control_ग_लिखो(dev, REQUEST_WRITE, 0, loc * 2, buff, 0x02,
		      CONTROL_TIMEOUT_MS);
पूर्ण

अटल पूर्णांक ch9200_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा ethtool_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "%s() speed:%d duplex:%d\n",
		   __func__, ecmd.speed, ecmd.duplex);

	वापस 0;
पूर्ण

अटल व्योम ch9200_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	पूर्णांक link;
	अचिन्हित अक्षर *buf;

	अगर (urb->actual_length < 16)
		वापस;

	buf = urb->transfer_buffer;
	link = !!(buf[0] & 0x01);

	अगर (link) अणु
		netअगर_carrier_on(dev->net);
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev->net);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *ch9200_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	पूर्णांक i = 0;
	पूर्णांक len = 0;
	पूर्णांक tx_overhead = 0;

	tx_overhead = 0x40;

	len = skb->len;
	अगर (skb_cow_head(skb, tx_overhead)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	__skb_push(skb, tx_overhead);
	/* usbnet adds padding अगर length is a multiple of packet size
	 * अगर so, adjust length value in header
	 */
	अगर ((skb->len % dev->maxpacket) == 0)
		len++;

	skb->data[0] = len;
	skb->data[1] = len >> 8;
	skb->data[2] = 0x00;
	skb->data[3] = 0x80;

	क्रम (i = 4; i < 48; i++)
		skb->data[i] = 0x00;

	skb->data[48] = len;
	skb->data[49] = len >> 8;
	skb->data[50] = 0x00;
	skb->data[51] = 0x80;

	क्रम (i = 52; i < 64; i++)
		skb->data[i] = 0x00;

	वापस skb;
पूर्ण

अटल पूर्णांक ch9200_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = 0;
	पूर्णांक rx_overhead = 0;

	rx_overhead = 64;

	अगर (unlikely(skb->len < rx_overhead)) अणु
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		वापस 0;
	पूर्ण

	len = (skb->data[skb->len - 16] | skb->data[skb->len - 15] << 8);
	skb_trim(skb, len);

	वापस 1;
पूर्ण

अटल पूर्णांक get_mac_address(काष्ठा usbnet *dev, अचिन्हित अक्षर *data)
अणु
	पूर्णांक err = 0;
	अचिन्हित अक्षर mac_addr[0x06];
	पूर्णांक rd_mac_len = 0;

	netdev_dbg(dev->net, "%s:\n\tusbnet VID:%0x PID:%0x\n", __func__,
		   le16_to_cpu(dev->udev->descriptor.idVenकरोr),
		   le16_to_cpu(dev->udev->descriptor.idProduct));

	स_रखो(mac_addr, 0, माप(mac_addr));
	rd_mac_len = control_पढ़ो(dev, REQUEST_READ, 0,
				  MAC_REG_STATION_L, mac_addr, 0x02,
				  CONTROL_TIMEOUT_MS);
	rd_mac_len += control_पढ़ो(dev, REQUEST_READ, 0, MAC_REG_STATION_M,
				   mac_addr + 2, 0x02, CONTROL_TIMEOUT_MS);
	rd_mac_len += control_पढ़ो(dev, REQUEST_READ, 0, MAC_REG_STATION_H,
				   mac_addr + 4, 0x02, CONTROL_TIMEOUT_MS);
	अगर (rd_mac_len != ETH_ALEN)
		err = -EINVAL;

	data[0] = mac_addr[5];
	data[1] = mac_addr[4];
	data[2] = mac_addr[3];
	data[3] = mac_addr[2];
	data[4] = mac_addr[1];
	data[5] = mac_addr[0];

	वापस err;
पूर्ण

अटल पूर्णांक ch9200_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक retval = 0;
	अचिन्हित अक्षर data[2];

	retval = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (retval)
		वापस retval;

	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = ch9200_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = ch9200_mdio_ग_लिखो;
	dev->mii.reg_num_mask = 0x1f;

	dev->mii.phy_id_mask = 0x1f;

	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->rx_urb_size = 24 * 64 + 16;
	mii_nway_restart(&dev->mii);

	data[0] = 0x01;
	data[1] = 0x0F;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, MAC_REG_THRESHOLD, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0xA0;
	data[1] = 0x90;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, MAC_REG_FIFO_DEPTH, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x30;
	data[1] = 0x00;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, MAC_REG_PAUSE, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x17;
	data[1] = 0xD8;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, MAC_REG_FLOW_CONTROL,
			       data, 0x02, CONTROL_TIMEOUT_MS);

	/* Unकरोcumented रेजिस्टर */
	data[0] = 0x01;
	data[1] = 0x00;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, 254, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	data[0] = 0x5F;
	data[1] = 0x0D;
	retval = control_ग_लिखो(dev, REQUEST_WRITE, 0, MAC_REG_CTRL, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	retval = get_mac_address(dev, dev->net->dev_addr);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा driver_info ch9200_info = अणु
	.description = "CH9200 USB to Network Adaptor",
	.flags = FLAG_ETHER,
	.bind = ch9200_bind,
	.rx_fixup = ch9200_rx_fixup,
	.tx_fixup = ch9200_tx_fixup,
	.status = ch9200_status,
	.link_reset = ch9200_link_reset,
	.reset = ch9200_link_reset,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ch9200_products[] = अणु
	अणु
	 USB_DEVICE(0x1A86, 0xE092),
	 .driver_info = (अचिन्हित दीर्घ)&ch9200_info,
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, ch9200_products);

अटल काष्ठा usb_driver ch9200_driver = अणु
	.name = "ch9200",
	.id_table = ch9200_products,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
पूर्ण;

module_usb_driver(ch9200_driver);

MODULE_DESCRIPTION("QinHeng CH9200 USB Network device");
MODULE_LICENSE("GPL");
