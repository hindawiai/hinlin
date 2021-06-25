<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम USB ethernet port of Conexant CX82310-based ADSL routers
 * Copyright (C) 2010 by Ondrej Zary
 * some parts inspired by the cxacru driver
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>

क्रमागत cx82310_cmd अणु
	CMD_START		= 0x84,	/* no effect? */
	CMD_STOP		= 0x85,	/* no effect? */
	CMD_GET_STATUS		= 0x90,	/* वापसs nothing? */
	CMD_GET_MAC_ADDR	= 0x91,	/* पढ़ो MAC address */
	CMD_GET_LINK_STATUS	= 0x92,	/* not useful, link is always up */
	CMD_ETHERNET_MODE	= 0x99,	/* unknown, needed during init */
पूर्ण;

क्रमागत cx82310_status अणु
	STATUS_UNDEFINED,
	STATUS_SUCCESS,
	STATUS_ERROR,
	STATUS_UNSUPPORTED,
	STATUS_UNIMPLEMENTED,
	STATUS_PARAMETER_ERROR,
	STATUS_DBG_LOOPBACK,
पूर्ण;

#घोषणा CMD_PACKET_SIZE	64
#घोषणा CMD_TIMEOUT	100
#घोषणा CMD_REPLY_RETRY 5

#घोषणा CX82310_MTU	1514
#घोषणा CMD_EP		0x01

काष्ठा cx82310_priv अणु
	काष्ठा work_काष्ठा reenable_work;
	काष्ठा usbnet *dev;
पूर्ण;

/*
 * execute control command
 *  - optionally send some data (command parameters)
 *  - optionally रुको क्रम the reply
 *  - optionally पढ़ो some data from the reply
 */
अटल पूर्णांक cx82310_cmd(काष्ठा usbnet *dev, क्रमागत cx82310_cmd cmd, bool reply,
		       u8 *wdata, पूर्णांक wlen, u8 *rdata, पूर्णांक rlen)
अणु
	पूर्णांक actual_len, retries, ret;
	काष्ठा usb_device *udev = dev->udev;
	u8 *buf = kzalloc(CMD_PACKET_SIZE, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	/* create command packet */
	buf[0] = cmd;
	अगर (wdata)
		स_नकल(buf + 4, wdata, min_t(पूर्णांक, wlen, CMD_PACKET_SIZE - 4));

	/* send command packet */
	ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, CMD_EP), buf,
			   CMD_PACKET_SIZE, &actual_len, CMD_TIMEOUT);
	अगर (ret < 0) अणु
		अगर (cmd != CMD_GET_LINK_STATUS)
			netdev_err(dev->net, "send command %#x: error %d\n",
				   cmd, ret);
		जाओ end;
	पूर्ण

	अगर (reply) अणु
		/* रुको क्रम reply, retry अगर it's empty */
		क्रम (retries = 0; retries < CMD_REPLY_RETRY; retries++) अणु
			ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, CMD_EP),
					   buf, CMD_PACKET_SIZE, &actual_len,
					   CMD_TIMEOUT);
			अगर (ret < 0) अणु
				अगर (cmd != CMD_GET_LINK_STATUS)
					netdev_err(dev->net, "reply receive error %d\n",
						   ret);
				जाओ end;
			पूर्ण
			अगर (actual_len > 0)
				अवरोध;
		पूर्ण
		अगर (actual_len == 0) अणु
			netdev_err(dev->net, "no reply to command %#x\n", cmd);
			ret = -EIO;
			जाओ end;
		पूर्ण
		अगर (buf[0] != cmd) अणु
			netdev_err(dev->net, "got reply to command %#x, expected: %#x\n",
				   buf[0], cmd);
			ret = -EIO;
			जाओ end;
		पूर्ण
		अगर (buf[1] != STATUS_SUCCESS) अणु
			netdev_err(dev->net, "command %#x failed: %#x\n", cmd,
				   buf[1]);
			ret = -EIO;
			जाओ end;
		पूर्ण
		अगर (rdata)
			स_नकल(rdata, buf + 4,
			       min_t(पूर्णांक, rlen, CMD_PACKET_SIZE - 4));
	पूर्ण
end:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक cx82310_enable_ethernet(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret = cx82310_cmd(dev, CMD_ETHERNET_MODE, true, "\x01", 1, शून्य, 0);

	अगर (ret)
		netdev_err(dev->net, "unable to enable ethernet mode: %d\n",
			   ret);
	वापस ret;
पूर्ण

अटल व्योम cx82310_reenable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx82310_priv *priv = container_of(work, काष्ठा cx82310_priv,
						 reenable_work);
	cx82310_enable_ethernet(priv->dev);
पूर्ण

#घोषणा partial_len	data[0]		/* length of partial packet data */
#घोषणा partial_rem	data[1]		/* reमुख्यing (missing) data length */
#घोषणा partial_data	data[2]		/* partial packet data */

अटल पूर्णांक cx82310_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;
	अक्षर buf[15];
	काष्ठा usb_device *udev = dev->udev;
	u8 link[3];
	पूर्णांक समयout = 50;
	काष्ठा cx82310_priv *priv;

	/* aव्योम ADSL modems - जारी only अगर iProduct is "USB NET CARD" */
	अगर (usb_string(udev, udev->descriptor.iProduct, buf, माप(buf)) > 0
	    && म_भेद(buf, "USB NET CARD")) अणु
		dev_info(&udev->dev, "ignoring: probably an ADSL modem\n");
		वापस -ENODEV;
	पूर्ण

	ret = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (ret)
		वापस ret;

	/*
	 * this must not include ethernet header as the device can send partial
	 * packets with no header (and someबार even empty URBs)
	 */
	dev->net->hard_header_len = 0;
	/* we can send at most 1514 bytes of data (+ 2-byte header) per URB */
	dev->hard_mtu = CX82310_MTU + 2;
	/* we can receive URBs up to 4KB from the device */
	dev->rx_urb_size = 4096;

	dev->partial_data = (अचिन्हित दीर्घ) kदो_स्मृति(dev->hard_mtu, GFP_KERNEL);
	अगर (!dev->partial_data)
		वापस -ENOMEM;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ err_partial;
	पूर्ण
	dev->driver_priv = priv;
	INIT_WORK(&priv->reenable_work, cx82310_reenable_work);
	priv->dev = dev;

	/* रुको क्रम firmware to become पढ़ोy (indicated by the link being up) */
	जबतक (--समयout) अणु
		ret = cx82310_cmd(dev, CMD_GET_LINK_STATUS, true, शून्य, 0,
				  link, माप(link));
		/* the command can समय out during boot - it's not an error */
		अगर (!ret && link[0] == 1 && link[2] == 1)
			अवरोध;
		msleep(500);
	पूर्ण
	अगर (!समयout) अणु
		netdev_err(dev->net, "firmware not ready in time\n");
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	/* enable ethernet mode (?) */
	ret = cx82310_enable_ethernet(dev);
	अगर (ret)
		जाओ err;

	/* get the MAC address */
	ret = cx82310_cmd(dev, CMD_GET_MAC_ADDR, true, शून्य, 0,
			  dev->net->dev_addr, ETH_ALEN);
	अगर (ret) अणु
		netdev_err(dev->net, "unable to read MAC address: %d\n", ret);
		जाओ err;
	पूर्ण

	/* start (करोes not seem to have any effect?) */
	ret = cx82310_cmd(dev, CMD_START, false, शून्य, 0, शून्य, 0);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	kमुक्त(dev->driver_priv);
err_partial:
	kमुक्त((व्योम *)dev->partial_data);
	वापस ret;
पूर्ण

अटल व्योम cx82310_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cx82310_priv *priv = dev->driver_priv;

	kमुक्त((व्योम *)dev->partial_data);
	cancel_work_sync(&priv->reenable_work);
	kमुक्त(dev->driver_priv);
पूर्ण

/*
 * RX is NOT easy - we can receive multiple packets per skb, each having 2-byte
 * packet length at the beginning.
 * The last packet might be incomplete (when it crosses the 4KB URB size),
 * continuing in the next skb (without any headers).
 * If a packet has odd length, there is one extra byte at the end (beक्रमe next
 * packet or at the end of the URB).
 */
अटल पूर्णांक cx82310_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len;
	काष्ठा sk_buff *skb2;
	काष्ठा cx82310_priv *priv = dev->driver_priv;

	/*
	 * If the last skb ended with an incomplete packet, this skb contains
	 * end of that packet at the beginning.
	 */
	अगर (dev->partial_rem) अणु
		len = dev->partial_len + dev->partial_rem;
		skb2 = alloc_skb(len, GFP_ATOMIC);
		अगर (!skb2)
			वापस 0;
		skb_put(skb2, len);
		स_नकल(skb2->data, (व्योम *)dev->partial_data,
		       dev->partial_len);
		स_नकल(skb2->data + dev->partial_len, skb->data,
		       dev->partial_rem);
		usbnet_skb_वापस(dev, skb2);
		skb_pull(skb, (dev->partial_rem + 1) & ~1);
		dev->partial_rem = 0;
		अगर (skb->len < 2)
			वापस 1;
	पूर्ण

	/* a skb can contain multiple packets */
	जबतक (skb->len > 1) अणु
		/* first two bytes are packet length */
		len = skb->data[0] | (skb->data[1] << 8);
		skb_pull(skb, 2);

		/* अगर last packet in the skb, let usbnet to process it */
		अगर (len == skb->len || len + 1 == skb->len) अणु
			skb_trim(skb, len);
			अवरोध;
		पूर्ण

		अगर (len == 0xffff) अणु
			netdev_info(dev->net, "router was rebooted, re-enabling ethernet mode");
			schedule_work(&priv->reenable_work);
		पूर्ण अन्यथा अगर (len > CX82310_MTU) अणु
			netdev_err(dev->net, "RX packet too long: %d B\n", len);
			वापस 0;
		पूर्ण

		/* incomplete packet, save it क्रम the next skb */
		अगर (len > skb->len) अणु
			dev->partial_len = skb->len;
			dev->partial_rem = len - skb->len;
			स_नकल((व्योम *)dev->partial_data, skb->data,
			       dev->partial_len);
			skb_pull(skb, skb->len);
			अवरोध;
		पूर्ण

		skb2 = alloc_skb(len, GFP_ATOMIC);
		अगर (!skb2)
			वापस 0;
		skb_put(skb2, len);
		स_नकल(skb2->data, skb->data, len);
		/* process the packet */
		usbnet_skb_वापस(dev, skb2);

		skb_pull(skb, (len + 1) & ~1);
	पूर्ण

	/* let usbnet process the last packet */
	वापस 1;
पूर्ण

/* TX is easy, just add 2 bytes of length at the beginning */
अटल काष्ठा sk_buff *cx82310_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	पूर्णांक len = skb->len;

	अगर (skb_cow_head(skb, 2)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण
	skb_push(skb, 2);

	skb->data[0] = len;
	skb->data[1] = len >> 8;

	वापस skb;
पूर्ण


अटल स्थिर काष्ठा driver_info	cx82310_info = अणु
	.description	= "Conexant CX82310 USB ethernet",
	.flags		= FLAG_ETHER,
	.bind		= cx82310_bind,
	.unbind		= cx82310_unbind,
	.rx_fixup	= cx82310_rx_fixup,
	.tx_fixup	= cx82310_tx_fixup,
पूर्ण;

#घोषणा USB_DEVICE_CLASS(vend, prod, cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_DEV_INFO, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bDeviceClass = (cl), \
	.bDeviceSubClass = (sc), \
	.bDeviceProtocol = (pr)

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		USB_DEVICE_CLASS(0x0572, 0xcb01, 0xff, 0, 0),
		.driver_info = (अचिन्हित दीर्घ) &cx82310_info
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver cx82310_driver = अणु
	.name		= "cx82310_eth",
	.id_table	= products,
	.probe		= usbnet_probe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.resume		= usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(cx82310_driver);

MODULE_AUTHOR("Ondrej Zary");
MODULE_DESCRIPTION("Conexant CX82310-based ADSL router USB ethernet driver");
MODULE_LICENSE("GPL");
