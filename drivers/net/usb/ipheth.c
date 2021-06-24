<शैली गुरु>
/*
 * ipheth.c - Apple iPhone USB Ethernet driver
 *
 * Copyright (c) 2009 Diego Giagio <diego@giagio.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of GIAGIO.COM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 *
 * Attention: iPhone device must be paired, otherwise it won't respond to our
 * driver. For more info: http://giagio.com/wiki/moin.cgi/iPhoneEthernetDriver
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>

#घोषणा USB_VENDOR_APPLE        0x05ac

#घोषणा IPHETH_USBINTF_CLASS    255
#घोषणा IPHETH_USBINTF_SUBCLASS 253
#घोषणा IPHETH_USBINTF_PROTO    1

#घोषणा IPHETH_BUF_SIZE         1514
#घोषणा IPHETH_IP_ALIGN		2	/* padding at front of URB */
#घोषणा IPHETH_TX_TIMEOUT       (5 * HZ)

#घोषणा IPHETH_INTFNUM          2
#घोषणा IPHETH_ALT_INTFNUM      1

#घोषणा IPHETH_CTRL_ENDP        0x00
#घोषणा IPHETH_CTRL_BUF_SIZE    0x40
#घोषणा IPHETH_CTRL_TIMEOUT     (5 * HZ)

#घोषणा IPHETH_CMD_GET_MACADDR   0x00
#घोषणा IPHETH_CMD_CARRIER_CHECK 0x45

#घोषणा IPHETH_CARRIER_CHECK_TIMEOUT round_jअगरfies_relative(1 * HZ)
#घोषणा IPHETH_CARRIER_ON       0x04

अटल स्थिर काष्ठा usb_device_id ipheth_table[] = अणु
	अणु USB_VENDOR_AND_INTERFACE_INFO(USB_VENDOR_APPLE, IPHETH_USBINTF_CLASS,
					IPHETH_USBINTF_SUBCLASS,
					IPHETH_USBINTF_PROTO) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ipheth_table);

काष्ठा ipheth_device अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा net_device *net;
	काष्ठा urb *tx_urb;
	काष्ठा urb *rx_urb;
	अचिन्हित अक्षर *tx_buf;
	अचिन्हित अक्षर *rx_buf;
	अचिन्हित अक्षर *ctrl_buf;
	u8 bulk_in;
	u8 bulk_out;
	काष्ठा delayed_work carrier_work;
	bool confirmed_pairing;
पूर्ण;

अटल पूर्णांक ipheth_rx_submit(काष्ठा ipheth_device *dev, gfp_t mem_flags);

अटल पूर्णांक ipheth_alloc_urbs(काष्ठा ipheth_device *iphone)
अणु
	काष्ठा urb *tx_urb = शून्य;
	काष्ठा urb *rx_urb = शून्य;
	u8 *tx_buf = शून्य;
	u8 *rx_buf = शून्य;

	tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (tx_urb == शून्य)
		जाओ error_nomem;

	rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (rx_urb == शून्य)
		जाओ मुक्त_tx_urb;

	tx_buf = usb_alloc_coherent(iphone->udev, IPHETH_BUF_SIZE,
				    GFP_KERNEL, &tx_urb->transfer_dma);
	अगर (tx_buf == शून्य)
		जाओ मुक्त_rx_urb;

	rx_buf = usb_alloc_coherent(iphone->udev, IPHETH_BUF_SIZE,
				    GFP_KERNEL, &rx_urb->transfer_dma);
	अगर (rx_buf == शून्य)
		जाओ मुक्त_tx_buf;


	iphone->tx_urb = tx_urb;
	iphone->rx_urb = rx_urb;
	iphone->tx_buf = tx_buf;
	iphone->rx_buf = rx_buf;
	वापस 0;

मुक्त_tx_buf:
	usb_मुक्त_coherent(iphone->udev, IPHETH_BUF_SIZE, tx_buf,
			  tx_urb->transfer_dma);
मुक्त_rx_urb:
	usb_मुक्त_urb(rx_urb);
मुक्त_tx_urb:
	usb_मुक्त_urb(tx_urb);
error_nomem:
	वापस -ENOMEM;
पूर्ण

अटल व्योम ipheth_मुक्त_urbs(काष्ठा ipheth_device *iphone)
अणु
	usb_मुक्त_coherent(iphone->udev, IPHETH_BUF_SIZE, iphone->rx_buf,
			  iphone->rx_urb->transfer_dma);
	usb_मुक्त_coherent(iphone->udev, IPHETH_BUF_SIZE, iphone->tx_buf,
			  iphone->tx_urb->transfer_dma);
	usb_मुक्त_urb(iphone->rx_urb);
	usb_मुक्त_urb(iphone->tx_urb);
पूर्ण

अटल व्योम ipheth_समाप्त_urbs(काष्ठा ipheth_device *dev)
अणु
	usb_समाप्त_urb(dev->tx_urb);
	usb_समाप्त_urb(dev->rx_urb);
पूर्ण

अटल व्योम ipheth_rcvbulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा ipheth_device *dev;
	काष्ठा sk_buff *skb;
	पूर्णांक status;
	अक्षर *buf;
	पूर्णांक len;

	dev = urb->context;
	अगर (dev == शून्य)
		वापस;

	status = urb->status;
	चयन (status) अणु
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
	हाल -EPROTO:
		वापस;
	हाल 0:
		अवरोध;
	शेष:
		dev_err(&dev->पूर्णांकf->dev, "%s: urb status: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length <= IPHETH_IP_ALIGN) अणु
		dev->net->stats.rx_length_errors++;
		वापस;
	पूर्ण
	len = urb->actual_length - IPHETH_IP_ALIGN;
	buf = urb->transfer_buffer + IPHETH_IP_ALIGN;

	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		dev_err(&dev->पूर्णांकf->dev, "%s: dev_alloc_skb: -ENOMEM\n",
			__func__);
		dev->net->stats.rx_dropped++;
		वापस;
	पूर्ण

	skb_put_data(skb, buf, len);
	skb->dev = dev->net;
	skb->protocol = eth_type_trans(skb, dev->net);

	dev->net->stats.rx_packets++;
	dev->net->stats.rx_bytes += len;
	dev->confirmed_pairing = true;
	netअगर_rx(skb);
	ipheth_rx_submit(dev, GFP_ATOMIC);
पूर्ण

अटल व्योम ipheth_sndbulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा ipheth_device *dev;
	पूर्णांक status = urb->status;

	dev = urb->context;
	अगर (dev == शून्य)
		वापस;

	अगर (status != 0 &&
	    status != -ENOENT &&
	    status != -ECONNRESET &&
	    status != -ESHUTDOWN)
		dev_err(&dev->पूर्णांकf->dev, "%s: urb status: %d\n",
		__func__, status);

	अगर (status == 0)
		netअगर_wake_queue(dev->net);
	अन्यथा
		// on URB error, trigger immediate poll
		schedule_delayed_work(&dev->carrier_work, 0);
पूर्ण

अटल पूर्णांक ipheth_carrier_set(काष्ठा ipheth_device *dev)
अणु
	काष्ठा usb_device *udev;
	पूर्णांक retval;

	अगर (!dev->confirmed_pairing)
		वापस 0;

	udev = dev->udev;
	retval = usb_control_msg(udev,
			usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
			IPHETH_CMD_CARRIER_CHECK, /* request */
			0xc0, /* request type */
			0x00, /* value */
			0x02, /* index */
			dev->ctrl_buf, IPHETH_CTRL_BUF_SIZE,
			IPHETH_CTRL_TIMEOUT);
	अगर (retval < 0) अणु
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
		वापस retval;
	पूर्ण

	अगर (dev->ctrl_buf[0] == IPHETH_CARRIER_ON) अणु
		netअगर_carrier_on(dev->net);
		अगर (dev->tx_urb->status != -EINPROGRESS)
			netअगर_wake_queue(dev->net);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev->net);
		netअगर_stop_queue(dev->net);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ipheth_carrier_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipheth_device *dev = container_of(work, काष्ठा ipheth_device,
						 carrier_work.work);

	ipheth_carrier_set(dev);
	schedule_delayed_work(&dev->carrier_work, IPHETH_CARRIER_CHECK_TIMEOUT);
पूर्ण

अटल पूर्णांक ipheth_get_macaddr(काष्ठा ipheth_device *dev)
अणु
	काष्ठा usb_device *udev = dev->udev;
	काष्ठा net_device *net = dev->net;
	पूर्णांक retval;

	retval = usb_control_msg(udev,
				 usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
				 IPHETH_CMD_GET_MACADDR, /* request */
				 0xc0, /* request type */
				 0x00, /* value */
				 0x02, /* index */
				 dev->ctrl_buf,
				 IPHETH_CTRL_BUF_SIZE,
				 IPHETH_CTRL_TIMEOUT);
	अगर (retval < 0) अणु
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
	पूर्ण अन्यथा अगर (retval < ETH_ALEN) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"%s: usb_control_msg: short packet: %d bytes\n",
			__func__, retval);
		retval = -EINVAL;
	पूर्ण अन्यथा अणु
		स_नकल(net->dev_addr, dev->ctrl_buf, ETH_ALEN);
		retval = 0;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक ipheth_rx_submit(काष्ठा ipheth_device *dev, gfp_t mem_flags)
अणु
	काष्ठा usb_device *udev = dev->udev;
	पूर्णांक retval;

	usb_fill_bulk_urb(dev->rx_urb, udev,
			  usb_rcvbulkpipe(udev, dev->bulk_in),
			  dev->rx_buf, IPHETH_BUF_SIZE,
			  ipheth_rcvbulk_callback,
			  dev);
	dev->rx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	retval = usb_submit_urb(dev->rx_urb, mem_flags);
	अगर (retval)
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_submit_urb: %d\n",
			__func__, retval);
	वापस retval;
पूर्ण

अटल पूर्णांक ipheth_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा ipheth_device *dev = netdev_priv(net);
	काष्ठा usb_device *udev = dev->udev;
	पूर्णांक retval = 0;

	usb_set_पूर्णांकerface(udev, IPHETH_INTFNUM, IPHETH_ALT_INTFNUM);

	retval = ipheth_carrier_set(dev);
	अगर (retval)
		वापस retval;

	retval = ipheth_rx_submit(dev, GFP_KERNEL);
	अगर (retval)
		वापस retval;

	schedule_delayed_work(&dev->carrier_work, IPHETH_CARRIER_CHECK_TIMEOUT);
	वापस retval;
पूर्ण

अटल पूर्णांक ipheth_बंद(काष्ठा net_device *net)
अणु
	काष्ठा ipheth_device *dev = netdev_priv(net);

	cancel_delayed_work_sync(&dev->carrier_work);
	netअगर_stop_queue(net);
	वापस 0;
पूर्ण

अटल netdev_tx_t ipheth_tx(काष्ठा sk_buff *skb, काष्ठा net_device *net)
अणु
	काष्ठा ipheth_device *dev = netdev_priv(net);
	काष्ठा usb_device *udev = dev->udev;
	पूर्णांक retval;

	/* Paranoid */
	अगर (skb->len > IPHETH_BUF_SIZE) अणु
		WARN(1, "%s: skb too large: %d bytes\n", __func__, skb->len);
		dev->net->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	स_नकल(dev->tx_buf, skb->data, skb->len);
	अगर (skb->len < IPHETH_BUF_SIZE)
		स_रखो(dev->tx_buf + skb->len, 0, IPHETH_BUF_SIZE - skb->len);

	usb_fill_bulk_urb(dev->tx_urb, udev,
			  usb_sndbulkpipe(udev, dev->bulk_out),
			  dev->tx_buf, IPHETH_BUF_SIZE,
			  ipheth_sndbulk_callback,
			  dev);
	dev->tx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	netअगर_stop_queue(net);
	retval = usb_submit_urb(dev->tx_urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_submit_urb: %d\n",
			__func__, retval);
		dev->net->stats.tx_errors++;
		dev_kमुक्त_skb_any(skb);
		netअगर_wake_queue(net);
	पूर्ण अन्यथा अणु
		dev->net->stats.tx_packets++;
		dev->net->stats.tx_bytes += skb->len;
		dev_consume_skb_any(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ipheth_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ipheth_device *dev = netdev_priv(net);

	dev_err(&dev->पूर्णांकf->dev, "%s: TX timeout\n", __func__);
	dev->net->stats.tx_errors++;
	usb_unlink_urb(dev->tx_urb);
पूर्ण

अटल u32 ipheth_ethtool_op_get_link(काष्ठा net_device *net)
अणु
	काष्ठा ipheth_device *dev = netdev_priv(net);
	वापस netअगर_carrier_ok(dev->net);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_link = ipheth_ethtool_op_get_link
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ipheth_netdev_ops = अणु
	.nकरो_खोलो = ipheth_खोलो,
	.nकरो_stop = ipheth_बंद,
	.nकरो_start_xmit = ipheth_tx,
	.nकरो_tx_समयout = ipheth_tx_समयout,
पूर्ण;

अटल पूर्णांक ipheth_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *hपूर्णांकf;
	काष्ठा usb_endpoपूर्णांक_descriptor *endp;
	काष्ठा ipheth_device *dev;
	काष्ठा net_device *netdev;
	पूर्णांक i;
	पूर्णांक retval;

	netdev = alloc_etherdev(माप(काष्ठा ipheth_device));
	अगर (!netdev)
		वापस -ENOMEM;

	netdev->netdev_ops = &ipheth_netdev_ops;
	netdev->watchकरोg_समयo = IPHETH_TX_TIMEOUT;
	म_नकल(netdev->name, "eth%d");

	dev = netdev_priv(netdev);
	dev->udev = udev;
	dev->net = netdev;
	dev->पूर्णांकf = पूर्णांकf;
	dev->confirmed_pairing = false;
	/* Set up endpoपूर्णांकs */
	hपूर्णांकf = usb_altnum_to_altsetting(पूर्णांकf, IPHETH_ALT_INTFNUM);
	अगर (hपूर्णांकf == शून्य) अणु
		retval = -ENODEV;
		dev_err(&पूर्णांकf->dev, "Unable to find alternate settings interface\n");
		जाओ err_endpoपूर्णांकs;
	पूर्ण

	क्रम (i = 0; i < hपूर्णांकf->desc.bNumEndpoपूर्णांकs; i++) अणु
		endp = &hपूर्णांकf->endpoपूर्णांक[i].desc;
		अगर (usb_endpoपूर्णांक_is_bulk_in(endp))
			dev->bulk_in = endp->bEndpoपूर्णांकAddress;
		अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(endp))
			dev->bulk_out = endp->bEndpoपूर्णांकAddress;
	पूर्ण
	अगर (!(dev->bulk_in && dev->bulk_out)) अणु
		retval = -ENODEV;
		dev_err(&पूर्णांकf->dev, "Unable to find endpoints\n");
		जाओ err_endpoपूर्णांकs;
	पूर्ण

	dev->ctrl_buf = kदो_स्मृति(IPHETH_CTRL_BUF_SIZE, GFP_KERNEL);
	अगर (dev->ctrl_buf == शून्य) अणु
		retval = -ENOMEM;
		जाओ err_alloc_ctrl_buf;
	पूर्ण

	retval = ipheth_get_macaddr(dev);
	अगर (retval)
		जाओ err_get_macaddr;

	INIT_DELAYED_WORK(&dev->carrier_work, ipheth_carrier_check_work);

	retval = ipheth_alloc_urbs(dev);
	अगर (retval) अणु
		dev_err(&पूर्णांकf->dev, "error allocating urbs: %d\n", retval);
		जाओ err_alloc_urbs;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	netdev->ethtool_ops = &ops;

	retval = रेजिस्टर_netdev(netdev);
	अगर (retval) अणु
		dev_err(&पूर्णांकf->dev, "error registering netdev: %d\n", retval);
		retval = -EIO;
		जाओ err_रेजिस्टर_netdev;
	पूर्ण
	// carrier करोwn and transmit queues stopped until packet from device
	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);
	dev_info(&पूर्णांकf->dev, "Apple iPhone USB Ethernet device attached\n");
	वापस 0;

err_रेजिस्टर_netdev:
	ipheth_मुक्त_urbs(dev);
err_alloc_urbs:
err_get_macaddr:
err_alloc_ctrl_buf:
	kमुक्त(dev->ctrl_buf);
err_endpoपूर्णांकs:
	मुक्त_netdev(netdev);
	वापस retval;
पूर्ण

अटल व्योम ipheth_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ipheth_device *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (dev != शून्य) अणु
		unरेजिस्टर_netdev(dev->net);
		ipheth_समाप्त_urbs(dev);
		ipheth_मुक्त_urbs(dev);
		kमुक्त(dev->ctrl_buf);
		मुक्त_netdev(dev->net);
	पूर्ण
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	dev_info(&पूर्णांकf->dev, "Apple iPhone USB Ethernet now disconnected\n");
पूर्ण

अटल काष्ठा usb_driver ipheth_driver = अणु
	.name =		"ipheth",
	.probe =	ipheth_probe,
	.disconnect =	ipheth_disconnect,
	.id_table =	ipheth_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(ipheth_driver);

MODULE_AUTHOR("Diego Giagio <diego@giagio.com>");
MODULE_DESCRIPTION("Apple iPhone USB Ethernet driver");
MODULE_LICENSE("Dual BSD/GPL");
