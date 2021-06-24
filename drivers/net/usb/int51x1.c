<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2009 Peter Holik
 *
 * Intellon usb PLC (Powerline Communications) usb net driver
 *
 * http://www.tandel.be/करोwnloads/INT51X1_Datasheet.pdf
 *
 * Based on the work of Jan 'RedBully' Seअगरfert
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>

#घोषणा INT51X1_VENDOR_ID	0x09e1
#घोषणा INT51X1_PRODUCT_ID	0x5121

#घोषणा INT51X1_HEADER_SIZE	2	/* 2 byte header */

#घोषणा PACKET_TYPE_PROMISCUOUS		(1 << 0)
#घोषणा PACKET_TYPE_ALL_MULTICAST	(1 << 1) /* no filter */
#घोषणा PACKET_TYPE_सूचीECTED		(1 << 2)
#घोषणा PACKET_TYPE_BROADCAST		(1 << 3)
#घोषणा PACKET_TYPE_MULTICAST		(1 << 4) /* filtered */

#घोषणा SET_ETHERNET_PACKET_FILTER	0x43

अटल पूर्णांक पूर्णांक51x1_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len;

	अगर (!(pskb_may_pull(skb, INT51X1_HEADER_SIZE))) अणु
		netdev_err(dev->net, "unexpected tiny rx frame\n");
		वापस 0;
	पूर्ण

	len = le16_to_cpu(*(__le16 *)&skb->data[skb->len - 2]);

	skb_trim(skb, len);

	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *पूर्णांक51x1_tx_fixup(काष्ठा usbnet *dev,
		काष्ठा sk_buff *skb, gfp_t flags)
अणु
	पूर्णांक pack_len = skb->len;
	पूर्णांक pack_with_header_len = pack_len + INT51X1_HEADER_SIZE;
	पूर्णांक headroom = skb_headroom(skb);
	पूर्णांक tailroom = skb_tailroom(skb);
	पूर्णांक need_tail = 0;
	__le16 *len;

	/* अगर packet and our header is smaler than 64 pad to 64 (+ ZLP) */
	अगर ((pack_with_header_len) < dev->maxpacket)
		need_tail = dev->maxpacket - pack_with_header_len + 1;
	/*
	 * usbnet would send a ZLP अगर packetlength mod urbsize == 0 क्रम us,
	 * but we need to know ourself, because this would add to the length
	 * we send करोwn to the device...
	 */
	अन्यथा अगर (!(pack_with_header_len % dev->maxpacket))
		need_tail = 1;

	अगर (!skb_cloned(skb) &&
			(headroom + tailroom >= need_tail + INT51X1_HEADER_SIZE)) अणु
		अगर (headroom < INT51X1_HEADER_SIZE || tailroom < need_tail) अणु
			skb->data = स_हटाओ(skb->head + INT51X1_HEADER_SIZE,
					skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_copy_expand(skb,
				INT51X1_HEADER_SIZE,
				need_tail,
				flags);
		dev_kमुक्त_skb_any(skb);
		अगर (!skb2)
			वापस शून्य;
		skb = skb2;
	पूर्ण

	pack_len += need_tail;
	pack_len &= 0x07ff;

	len = __skb_push(skb, INT51X1_HEADER_SIZE);
	*len = cpu_to_le16(pack_len);

	अगर(need_tail)
		__skb_put_zero(skb, need_tail);

	वापस skb;
पूर्ण

अटल व्योम पूर्णांक51x1_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u16 filter = PACKET_TYPE_सूचीECTED | PACKET_TYPE_BROADCAST;

	अगर (netdev->flags & IFF_PROMISC) अणु
		/* करो not expect to see traffic of other PLCs */
		filter |= PACKET_TYPE_PROMISCUOUS;
		netdev_info(dev->net, "promiscuous mode enabled\n");
	पूर्ण अन्यथा अगर (!netdev_mc_empty(netdev) ||
		  (netdev->flags & IFF_ALLMULTI)) अणु
		filter |= PACKET_TYPE_ALL_MULTICAST;
		netdev_dbg(dev->net, "receive all multicast enabled\n");
	पूर्ण अन्यथा अणु
		/* ~PROMISCUOUS, ~MULTICAST */
		netdev_dbg(dev->net, "receive own packets only\n");
	पूर्ण

	usbnet_ग_लिखो_cmd_async(dev, SET_ETHERNET_PACKET_FILTER,
			       USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			       filter, 0, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा net_device_ops पूर्णांक51x1_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= पूर्णांक51x1_set_multicast,
पूर्ण;

अटल पूर्णांक पूर्णांक51x1_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status = usbnet_get_ethernet_addr(dev, 3);

	अगर (status)
		वापस status;

	dev->net->hard_header_len += INT51X1_HEADER_SIZE;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->net->netdev_ops = &पूर्णांक51x1_netdev_ops;

	वापस usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
पूर्ण

अटल स्थिर काष्ठा driver_info पूर्णांक51x1_info = अणु
	.description = "Intellon usb powerline adapter",
	.bind        = पूर्णांक51x1_bind,
	.rx_fixup    = पूर्णांक51x1_rx_fixup,
	.tx_fixup    = पूर्णांक51x1_tx_fixup,
	.in          = 1,
	.out         = 2,
	.flags       = FLAG_ETHER,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
	USB_DEVICE(INT51X1_VENDOR_ID, INT51X1_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ) &पूर्णांक51x1_info,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver पूर्णांक51x1_driver = अणु
	.name       = "int51x1",
	.id_table   = products,
	.probe      = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend    = usbnet_suspend,
	.resume     = usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(पूर्णांक51x1_driver);

MODULE_AUTHOR("Peter Holik");
MODULE_DESCRIPTION("Intellon usb powerline adapter");
MODULE_LICENSE("GPL");
