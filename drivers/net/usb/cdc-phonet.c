<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * phonet.c -- USB CDC Phonet host driver
 *
 * Copyright (C) 2008-2009 Nokia Corporation. All rights reserved.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_phonet.h>
#समावेश <linux/phonet.h>

#घोषणा PN_MEDIA_USB	0x1B

अटल स्थिर अचिन्हित rxq_size = 17;

काष्ठा usbpn_dev अणु
	काष्ठा net_device	*dev;

	काष्ठा usb_पूर्णांकerface	*पूर्णांकf, *data_पूर्णांकf;
	काष्ठा usb_device	*usb;
	अचिन्हित पूर्णांक		tx_pipe, rx_pipe;
	u8 active_setting;
	u8 disconnected;

	अचिन्हित		tx_queue;
	spinlock_t		tx_lock;

	spinlock_t		rx_lock;
	काष्ठा sk_buff		*rx_skb;
	काष्ठा urb		*urbs[];
पूर्ण;

अटल व्योम tx_complete(काष्ठा urb *req);
अटल व्योम rx_complete(काष्ठा urb *req);

/*
 * Network device callbacks
 */
अटल netdev_tx_t usbpn_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा usbpn_dev *pnd = netdev_priv(dev);
	काष्ठा urb *req = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (skb->protocol != htons(ETH_P_PHONET))
		जाओ drop;

	req = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!req)
		जाओ drop;
	usb_fill_bulk_urb(req, pnd->usb, pnd->tx_pipe, skb->data, skb->len,
				tx_complete, skb);
	req->transfer_flags = URB_ZERO_PACKET;
	err = usb_submit_urb(req, GFP_ATOMIC);
	अगर (err) अणु
		usb_मुक्त_urb(req);
		जाओ drop;
	पूर्ण

	spin_lock_irqsave(&pnd->tx_lock, flags);
	pnd->tx_queue++;
	अगर (pnd->tx_queue >= dev->tx_queue_len)
		netअगर_stop_queue(dev);
	spin_unlock_irqrestore(&pnd->tx_lock, flags);
	वापस NETDEV_TX_OK;

drop:
	dev_kमुक्त_skb(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम tx_complete(काष्ठा urb *req)
अणु
	काष्ठा sk_buff *skb = req->context;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा usbpn_dev *pnd = netdev_priv(dev);
	पूर्णांक status = req->status;
	अचिन्हित दीर्घ flags;

	चयन (status) अणु
	हाल 0:
		dev->stats.tx_bytes += skb->len;
		अवरोध;

	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev->stats.tx_पातed_errors++;
		fallthrough;
	शेष:
		dev->stats.tx_errors++;
		dev_dbg(&dev->dev, "TX error (%d)\n", status);
	पूर्ण
	dev->stats.tx_packets++;

	spin_lock_irqsave(&pnd->tx_lock, flags);
	pnd->tx_queue--;
	netअगर_wake_queue(dev);
	spin_unlock_irqrestore(&pnd->tx_lock, flags);

	dev_kमुक्त_skb_any(skb);
	usb_मुक्त_urb(req);
पूर्ण

अटल पूर्णांक rx_submit(काष्ठा usbpn_dev *pnd, काष्ठा urb *req, gfp_t gfp_flags)
अणु
	काष्ठा net_device *dev = pnd->dev;
	काष्ठा page *page;
	पूर्णांक err;

	page = __dev_alloc_page(gfp_flags | __GFP_NOMEMALLOC);
	अगर (!page)
		वापस -ENOMEM;

	usb_fill_bulk_urb(req, pnd->usb, pnd->rx_pipe, page_address(page),
				PAGE_SIZE, rx_complete, dev);
	req->transfer_flags = 0;
	err = usb_submit_urb(req, gfp_flags);
	अगर (unlikely(err)) अणु
		dev_dbg(&dev->dev, "RX submit error (%d)\n", err);
		put_page(page);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम rx_complete(काष्ठा urb *req)
अणु
	काष्ठा net_device *dev = req->context;
	काष्ठा usbpn_dev *pnd = netdev_priv(dev);
	काष्ठा page *page = virt_to_page(req->transfer_buffer);
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = req->status;

	चयन (status) अणु
	हाल 0:
		spin_lock_irqsave(&pnd->rx_lock, flags);
		skb = pnd->rx_skb;
		अगर (!skb) अणु
			skb = pnd->rx_skb = netdev_alloc_skb(dev, 12);
			अगर (likely(skb)) अणु
				/* Can't use pskb_pull() on page in IRQ */
				skb_put_data(skb, page_address(page), 1);
				skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
						page, 1, req->actual_length,
						PAGE_SIZE);
				page = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
					page, 0, req->actual_length,
					PAGE_SIZE);
			page = शून्य;
		पूर्ण
		अगर (req->actual_length < PAGE_SIZE)
			pnd->rx_skb = शून्य; /* Last fragment */
		अन्यथा
			skb = शून्य;
		spin_unlock_irqrestore(&pnd->rx_lock, flags);
		अगर (skb) अणु
			skb->protocol = htons(ETH_P_PHONET);
			skb_reset_mac_header(skb);
			__skb_pull(skb, 1);
			skb->dev = dev;
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += skb->len;

			netअगर_rx(skb);
		पूर्ण
		जाओ resubmit;

	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		req = शून्य;
		अवरोध;

	हाल -EOVERFLOW:
		dev->stats.rx_over_errors++;
		dev_dbg(&dev->dev, "RX overflow\n");
		अवरोध;

	हाल -EILSEQ:
		dev->stats.rx_crc_errors++;
		अवरोध;
	पूर्ण

	dev->stats.rx_errors++;
resubmit:
	अगर (page)
		put_page(page);
	अगर (req)
		rx_submit(pnd, req, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक usbpn_बंद(काष्ठा net_device *dev);

अटल पूर्णांक usbpn_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा usbpn_dev *pnd = netdev_priv(dev);
	पूर्णांक err;
	अचिन्हित i;
	अचिन्हित num = pnd->data_पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	err = usb_set_पूर्णांकerface(pnd->usb, num, pnd->active_setting);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < rxq_size; i++) अणु
		काष्ठा urb *req = usb_alloc_urb(0, GFP_KERNEL);

		अगर (!req || rx_submit(pnd, req, GFP_KERNEL)) अणु
			usb_मुक्त_urb(req);
			usbpn_बंद(dev);
			वापस -ENOMEM;
		पूर्ण
		pnd->urbs[i] = req;
	पूर्ण

	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक usbpn_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा usbpn_dev *pnd = netdev_priv(dev);
	अचिन्हित i;
	अचिन्हित num = pnd->data_पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	netअगर_stop_queue(dev);

	क्रम (i = 0; i < rxq_size; i++) अणु
		काष्ठा urb *req = pnd->urbs[i];

		अगर (!req)
			जारी;
		usb_समाप्त_urb(req);
		usb_मुक्त_urb(req);
		pnd->urbs[i] = शून्य;
	पूर्ण

	वापस usb_set_पूर्णांकerface(pnd->usb, num, !pnd->active_setting);
पूर्ण

अटल पूर्णांक usbpn_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा अगर_phonet_req *req = (काष्ठा अगर_phonet_req *)अगरr;

	चयन (cmd) अणु
	हाल SIOCPNGAUTOCONF:
		req->अगरr_phonet_स्वतःconf.device = PN_DEV_PC;
		वापस 0;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा net_device_ops usbpn_ops = अणु
	.nकरो_खोलो	= usbpn_खोलो,
	.nकरो_stop	= usbpn_बंद,
	.nकरो_start_xmit = usbpn_xmit,
	.nकरो_करो_ioctl	= usbpn_ioctl,
पूर्ण;

अटल व्योम usbpn_setup(काष्ठा net_device *dev)
अणु
	dev->features		= 0;
	dev->netdev_ops		= &usbpn_ops;
	dev->header_ops		= &phonet_header_ops;
	dev->type		= ARPHRD_PHONET;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= PHONET_MAX_MTU;
	dev->min_mtu		= PHONET_MIN_MTU;
	dev->max_mtu		= PHONET_MAX_MTU;
	dev->hard_header_len	= 1;
	dev->dev_addr[0]	= PN_MEDIA_USB;
	dev->addr_len		= 1;
	dev->tx_queue_len	= 3;

	dev->needs_मुक्त_netdev	= true;
पूर्ण

/*
 * USB driver callbacks
 */
अटल स्थिर काष्ठा usb_device_id usbpn_ids[] = अणु
	अणु
		.match_flags = USB_DEVICE_ID_MATCH_VENDOR
			| USB_DEVICE_ID_MATCH_INT_CLASS
			| USB_DEVICE_ID_MATCH_INT_SUBCLASS,
		.idVenकरोr = 0x0421, /* Nokia */
		.bInterfaceClass = USB_CLASS_COMM,
		.bInterfaceSubClass = 0xFE,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, usbpn_ids);

अटल काष्ठा usb_driver usbpn_driver;

अटल पूर्णांक usbpn_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	अटल स्थिर अक्षर अगरname[] = "usbpn%d";
	स्थिर काष्ठा usb_cdc_जोड़_desc *जोड़_header = शून्य;
	स्थिर काष्ठा usb_host_पूर्णांकerface *data_desc;
	काष्ठा usb_पूर्णांकerface *data_पूर्णांकf;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा net_device *dev;
	काष्ठा usbpn_dev *pnd;
	u8 *data;
	पूर्णांक phonet = 0;
	पूर्णांक len, err;
	काष्ठा usb_cdc_parsed_header hdr;

	data = पूर्णांकf->altsetting->extra;
	len = पूर्णांकf->altsetting->extralen;
	cdc_parse_cdc_header(&hdr, पूर्णांकf, data, len);
	जोड़_header = hdr.usb_cdc_जोड़_desc;
	phonet = hdr.phonet_magic_present;

	अगर (!जोड़_header || !phonet)
		वापस -EINVAL;

	data_पूर्णांकf = usb_अगरnum_to_अगर(usbdev, जोड़_header->bSlaveInterface0);
	अगर (data_पूर्णांकf == शून्य)
		वापस -ENODEV;
	/* Data पूर्णांकerface has one inactive and one active setting */
	अगर (data_पूर्णांकf->num_altsetting != 2)
		वापस -EINVAL;
	अगर (data_पूर्णांकf->altsetting[0].desc.bNumEndpoपूर्णांकs == 0 &&
	    data_पूर्णांकf->altsetting[1].desc.bNumEndpoपूर्णांकs == 2)
		data_desc = data_पूर्णांकf->altsetting + 1;
	अन्यथा
	अगर (data_पूर्णांकf->altsetting[0].desc.bNumEndpoपूर्णांकs == 2 &&
	    data_पूर्णांकf->altsetting[1].desc.bNumEndpoपूर्णांकs == 0)
		data_desc = data_पूर्णांकf->altsetting;
	अन्यथा
		वापस -EINVAL;

	dev = alloc_netdev(काष्ठा_size(pnd, urbs, rxq_size), अगरname,
			   NET_NAME_UNKNOWN, usbpn_setup);
	अगर (!dev)
		वापस -ENOMEM;

	pnd = netdev_priv(dev);
	SET_NETDEV_DEV(dev, &पूर्णांकf->dev);

	pnd->dev = dev;
	pnd->usb = usbdev;
	pnd->पूर्णांकf = पूर्णांकf;
	pnd->data_पूर्णांकf = data_पूर्णांकf;
	spin_lock_init(&pnd->tx_lock);
	spin_lock_init(&pnd->rx_lock);
	/* Endpoपूर्णांकs */
	अगर (usb_pipein(data_desc->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress)) अणु
		pnd->rx_pipe = usb_rcvbulkpipe(usbdev,
			data_desc->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress);
		pnd->tx_pipe = usb_sndbulkpipe(usbdev,
			data_desc->endpoपूर्णांक[1].desc.bEndpoपूर्णांकAddress);
	पूर्ण अन्यथा अणु
		pnd->rx_pipe = usb_rcvbulkpipe(usbdev,
			data_desc->endpoपूर्णांक[1].desc.bEndpoपूर्णांकAddress);
		pnd->tx_pipe = usb_sndbulkpipe(usbdev,
			data_desc->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress);
	पूर्ण
	pnd->active_setting = data_desc - data_पूर्णांकf->altsetting;

	err = usb_driver_claim_पूर्णांकerface(&usbpn_driver, data_पूर्णांकf, pnd);
	अगर (err)
		जाओ out;

	/* Force inactive mode until the network device is brought UP */
	usb_set_पूर्णांकerface(usbdev, जोड़_header->bSlaveInterface0,
				!pnd->active_setting);
	usb_set_पूर्णांकfdata(पूर्णांकf, pnd);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		/* Set disconnected flag so that disconnect() वापसs early. */
		pnd->disconnected = 1;
		usb_driver_release_पूर्णांकerface(&usbpn_driver, data_पूर्णांकf);
		जाओ out;
	पूर्ण

	dev_dbg(&dev->dev, "USB CDC Phonet device found\n");
	वापस 0;

out:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल व्योम usbpn_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbpn_dev *pnd = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (pnd->disconnected)
		वापस;

	pnd->disconnected = 1;
	usb_driver_release_पूर्णांकerface(&usbpn_driver,
			(pnd->पूर्णांकf == पूर्णांकf) ? pnd->data_पूर्णांकf : pnd->पूर्णांकf);
	unरेजिस्टर_netdev(pnd->dev);
पूर्ण

अटल काष्ठा usb_driver usbpn_driver = अणु
	.name =		"cdc_phonet",
	.probe =	usbpn_probe,
	.disconnect =	usbpn_disconnect,
	.id_table =	usbpn_ids,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(usbpn_driver);

MODULE_AUTHOR("Remi Denis-Courmont");
MODULE_DESCRIPTION("USB CDC Phonet host interface");
MODULE_LICENSE("GPL");
