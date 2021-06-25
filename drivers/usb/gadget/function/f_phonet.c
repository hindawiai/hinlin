<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f_phonet.c -- USB CDC Phonet function
 *
 * Copyright (C) 2007-2008 Nokia Corporation. All rights reserved.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_phonet.h>
#समावेश <linux/अगर_arp.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/composite.h>

#समावेश "u_phonet.h"
#समावेश "u_ether.h"

#घोषणा PN_MEDIA_USB	0x1B
#घोषणा MAXPACKET	512
#अगर (PAGE_SIZE % MAXPACKET)
#त्रुटि MAXPACKET must भागide PAGE_SIZE!
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

काष्ठा phonet_port अणु
	काष्ठा f_phonet			*usb;
	spinlock_t			lock;
पूर्ण;

काष्ठा f_phonet अणु
	काष्ठा usb_function		function;
	काष्ठा अणु
		काष्ठा sk_buff		*skb;
		spinlock_t		lock;
	पूर्ण rx;
	काष्ठा net_device		*dev;
	काष्ठा usb_ep			*in_ep, *out_ep;

	काष्ठा usb_request		*in_req;
	काष्ठा usb_request		*out_reqv[];
पूर्ण;

अटल पूर्णांक phonet_rxq_size = 17;

अटल अंतरभूत काष्ठा f_phonet *func_to_pn(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_phonet, function);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा USB_CDC_SUBCLASS_PHONET	0xfe
#घोषणा USB_CDC_PHONET_TYPE	0xab

अटल काष्ठा usb_पूर्णांकerface_descriptor
pn_control_पूर्णांकf_desc = अणु
	.bLength =		माप pn_control_पूर्णांकf_desc,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber =	DYNAMIC, */
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_PHONET,
पूर्ण;

अटल स्थिर काष्ठा usb_cdc_header_desc
pn_header_desc = अणु
	.bLength =		माप pn_header_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,
	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल स्थिर काष्ठा usb_cdc_header_desc
pn_phonet_desc = अणु
	.bLength =		माप pn_phonet_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_PHONET_TYPE,
	.bcdCDC =		cpu_to_le16(0x1505), /* ??? */
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc
pn_जोड़_desc = अणु
	.bLength =		माप pn_जोड़_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_UNION_TYPE,

	/* .bMasterInterface0 =	DYNAMIC, */
	/* .bSlaveInterface0 =	DYNAMIC, */
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor
pn_data_nop_पूर्णांकf_desc = अणु
	.bLength =		माप pn_data_nop_पूर्णांकf_desc,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber =	DYNAMIC, */
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor
pn_data_पूर्णांकf_desc = अणु
	.bLength =		माप pn_data_पूर्णांकf_desc,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber =	DYNAMIC, */
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor
pn_fs_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor
pn_hs_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(MAXPACKET),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor
pn_fs_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor
pn_hs_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_pn_function[] = अणु
	(काष्ठा usb_descriptor_header *) &pn_control_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_header_desc,
	(काष्ठा usb_descriptor_header *) &pn_phonet_desc,
	(काष्ठा usb_descriptor_header *) &pn_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &pn_data_nop_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_data_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_fs_sink_desc,
	(काष्ठा usb_descriptor_header *) &pn_fs_source_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_pn_function[] = अणु
	(काष्ठा usb_descriptor_header *) &pn_control_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_header_desc,
	(काष्ठा usb_descriptor_header *) &pn_phonet_desc,
	(काष्ठा usb_descriptor_header *) &pn_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &pn_data_nop_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_data_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &pn_hs_sink_desc,
	(काष्ठा usb_descriptor_header *) &pn_hs_source_desc,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pn_net_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pn_net_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल व्योम pn_tx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_phonet *fp = ep->driver_data;
	काष्ठा net_device *dev = fp->dev;
	काष्ठा sk_buff *skb = req->context;

	चयन (req->status) अणु
	हाल 0:
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
		अवरोध;

	हाल -ESHUTDOWN: /* disconnected */
	हाल -ECONNRESET: /* disabled */
		dev->stats.tx_पातed_errors++;
		fallthrough;
	शेष:
		dev->stats.tx_errors++;
	पूर्ण

	dev_kमुक्त_skb_any(skb);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t pn_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा phonet_port *port = netdev_priv(dev);
	काष्ठा f_phonet *fp;
	काष्ठा usb_request *req;
	अचिन्हित दीर्घ flags;

	अगर (skb->protocol != htons(ETH_P_PHONET))
		जाओ out;

	spin_lock_irqsave(&port->lock, flags);
	fp = port->usb;
	अगर (unlikely(!fp)) /* race with carrier loss */
		जाओ out_unlock;

	req = fp->in_req;
	req->buf = skb->data;
	req->length = skb->len;
	req->complete = pn_tx_complete;
	req->zero = 1;
	req->context = skb;

	अगर (unlikely(usb_ep_queue(fp->in_ep, req, GFP_ATOMIC)))
		जाओ out_unlock;

	netअगर_stop_queue(dev);
	skb = शून्य;

out_unlock:
	spin_unlock_irqrestore(&port->lock, flags);
out:
	अगर (unlikely(skb)) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops pn_netdev_ops = अणु
	.nकरो_खोलो	= pn_net_खोलो,
	.nकरो_stop	= pn_net_बंद,
	.nकरो_start_xmit	= pn_net_xmit,
पूर्ण;

अटल व्योम pn_net_setup(काष्ठा net_device *dev)
अणु
	dev->features		= 0;
	dev->type		= ARPHRD_PHONET;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= PHONET_DEV_MTU;
	dev->min_mtu		= PHONET_MIN_MTU;
	dev->max_mtu		= PHONET_MAX_MTU;
	dev->hard_header_len	= 1;
	dev->dev_addr[0]	= PN_MEDIA_USB;
	dev->addr_len		= 1;
	dev->tx_queue_len	= 1;

	dev->netdev_ops		= &pn_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->header_ops		= &phonet_header_ops;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Queue buffer क्रम data from the host
 */
अटल पूर्णांक
pn_rx_submit(काष्ठा f_phonet *fp, काष्ठा usb_request *req, gfp_t gfp_flags)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	page = __dev_alloc_page(gfp_flags | __GFP_NOMEMALLOC);
	अगर (!page)
		वापस -ENOMEM;

	req->buf = page_address(page);
	req->length = PAGE_SIZE;
	req->context = page;

	err = usb_ep_queue(fp->out_ep, req, gfp_flags);
	अगर (unlikely(err))
		put_page(page);
	वापस err;
पूर्ण

अटल व्योम pn_rx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_phonet *fp = ep->driver_data;
	काष्ठा net_device *dev = fp->dev;
	काष्ठा page *page = req->context;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = req->status;

	चयन (status) अणु
	हाल 0:
		spin_lock_irqsave(&fp->rx.lock, flags);
		skb = fp->rx.skb;
		अगर (!skb)
			skb = fp->rx.skb = netdev_alloc_skb(dev, 12);
		अगर (req->actual < req->length) /* Last fragment */
			fp->rx.skb = शून्य;
		spin_unlock_irqrestore(&fp->rx.lock, flags);

		अगर (unlikely(!skb))
			अवरोध;

		अगर (skb->len == 0) अणु /* First fragment */
			skb->protocol = htons(ETH_P_PHONET);
			skb_reset_mac_header(skb);
			/* Can't use pskb_pull() on page in IRQ */
			skb_put_data(skb, page_address(page), 1);
		पूर्ण

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
				skb->len <= 1, req->actual, PAGE_SIZE);
		page = शून्य;

		अगर (req->actual < req->length) अणु /* Last fragment */
			skb->dev = dev;
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += skb->len;

			netअगर_rx(skb);
		पूर्ण
		अवरोध;

	/* Do not resubmit in these हालs: */
	हाल -ESHUTDOWN: /* disconnect */
	हाल -ECONNABORTED: /* hw reset */
	हाल -ECONNRESET: /* dequeued (unlink or netअगर करोwn) */
		req = शून्य;
		अवरोध;

	/* Do resubmit in these हालs: */
	हाल -EOVERFLOW: /* request buffer overflow */
		dev->stats.rx_over_errors++;
		fallthrough;
	शेष:
		dev->stats.rx_errors++;
		अवरोध;
	पूर्ण

	अगर (page)
		put_page(page);
	अगर (req)
		pn_rx_submit(fp, req, GFP_ATOMIC);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम __pn_reset(काष्ठा usb_function *f)
अणु
	काष्ठा f_phonet *fp = func_to_pn(f);
	काष्ठा net_device *dev = fp->dev;
	काष्ठा phonet_port *port = netdev_priv(dev);

	netअगर_carrier_off(dev);
	port->usb = शून्य;

	usb_ep_disable(fp->out_ep);
	usb_ep_disable(fp->in_ep);
	अगर (fp->rx.skb) अणु
		dev_kमुक्त_skb_irq(fp->rx.skb);
		fp->rx.skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक pn_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_phonet *fp = func_to_pn(f);
	काष्ठा usb_gadget *gadget = fp->function.config->cdev->gadget;

	अगर (पूर्णांकf == pn_control_पूर्णांकf_desc.bInterfaceNumber)
		/* control पूर्णांकerface, no altsetting */
		वापस (alt > 0) ? -EINVAL : 0;

	अगर (पूर्णांकf == pn_data_पूर्णांकf_desc.bInterfaceNumber) अणु
		काष्ठा net_device *dev = fp->dev;
		काष्ठा phonet_port *port = netdev_priv(dev);

		/* data पूर्णांकf (0: inactive, 1: active) */
		अगर (alt > 1)
			वापस -EINVAL;

		spin_lock(&port->lock);

		अगर (fp->in_ep->enabled)
			__pn_reset(f);

		अगर (alt == 1) अणु
			पूर्णांक i;

			अगर (config_ep_by_speed(gadget, f, fp->in_ep) ||
			    config_ep_by_speed(gadget, f, fp->out_ep)) अणु
				fp->in_ep->desc = शून्य;
				fp->out_ep->desc = शून्य;
				spin_unlock(&port->lock);
				वापस -EINVAL;
			पूर्ण
			usb_ep_enable(fp->out_ep);
			usb_ep_enable(fp->in_ep);

			port->usb = fp;
			fp->out_ep->driver_data = fp;
			fp->in_ep->driver_data = fp;

			netअगर_carrier_on(dev);
			क्रम (i = 0; i < phonet_rxq_size; i++)
				pn_rx_submit(fp, fp->out_reqv[i], GFP_ATOMIC);
		पूर्ण
		spin_unlock(&port->lock);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pn_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_phonet *fp = func_to_pn(f);

	अगर (पूर्णांकf == pn_control_पूर्णांकf_desc.bInterfaceNumber)
		वापस 0;

	अगर (पूर्णांकf == pn_data_पूर्णांकf_desc.bInterfaceNumber) अणु
		काष्ठा phonet_port *port = netdev_priv(fp->dev);
		u8 alt;

		spin_lock(&port->lock);
		alt = port->usb != शून्य;
		spin_unlock(&port->lock);
		वापस alt;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम pn_disconnect(काष्ठा usb_function *f)
अणु
	काष्ठा f_phonet *fp = func_to_pn(f);
	काष्ठा phonet_port *port = netdev_priv(fp->dev);
	अचिन्हित दीर्घ flags;

	/* reमुख्य disabled until set_alt */
	spin_lock_irqsave(&port->lock, flags);
	__pn_reset(f);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pn_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा f_phonet *fp = func_to_pn(f);
	काष्ठा usb_ep *ep;
	पूर्णांक status, i;

	काष्ठा f_phonet_opts *phonet_opts;

	phonet_opts = container_of(f->fi, काष्ठा f_phonet_opts, func_inst);

	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to phonet_opts->bound access
	 */
	अगर (!phonet_opts->bound) अणु
		gphonet_set_gadget(phonet_opts->net, gadget);
		status = gphonet_रेजिस्टर_netdev(phonet_opts->net);
		अगर (status)
			वापस status;
		phonet_opts->bound = true;
	पूर्ण

	/* Reserve पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ err;
	pn_control_पूर्णांकf_desc.bInterfaceNumber = status;
	pn_जोड़_desc.bMasterInterface0 = status;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ err;
	pn_data_nop_पूर्णांकf_desc.bInterfaceNumber = status;
	pn_data_पूर्णांकf_desc.bInterfaceNumber = status;
	pn_जोड़_desc.bSlaveInterface0 = status;

	/* Reserve endpoपूर्णांकs */
	status = -ENODEV;
	ep = usb_ep_स्वतःconfig(gadget, &pn_fs_sink_desc);
	अगर (!ep)
		जाओ err;
	fp->out_ep = ep;

	ep = usb_ep_स्वतःconfig(gadget, &pn_fs_source_desc);
	अगर (!ep)
		जाओ err;
	fp->in_ep = ep;

	pn_hs_sink_desc.bEndpoपूर्णांकAddress = pn_fs_sink_desc.bEndpoपूर्णांकAddress;
	pn_hs_source_desc.bEndpoपूर्णांकAddress = pn_fs_source_desc.bEndpoपूर्णांकAddress;

	/* Do not try to bind Phonet twice... */
	status = usb_assign_descriptors(f, fs_pn_function, hs_pn_function,
			शून्य, शून्य);
	अगर (status)
		जाओ err;

	/* Incoming USB requests */
	status = -ENOMEM;
	क्रम (i = 0; i < phonet_rxq_size; i++) अणु
		काष्ठा usb_request *req;

		req = usb_ep_alloc_request(fp->out_ep, GFP_KERNEL);
		अगर (!req)
			जाओ err_req;

		req->complete = pn_rx_complete;
		fp->out_reqv[i] = req;
	पूर्ण

	/* Outgoing USB requests */
	fp->in_req = usb_ep_alloc_request(fp->in_ep, GFP_KERNEL);
	अगर (!fp->in_req)
		जाओ err_req;

	INFO(cdev, "USB CDC Phonet function\n");
	INFO(cdev, "using %s, OUT %s, IN %s\n", cdev->gadget->name,
		fp->out_ep->name, fp->in_ep->name);
	वापस 0;

err_req:
	क्रम (i = 0; i < phonet_rxq_size && fp->out_reqv[i]; i++)
		usb_ep_मुक्त_request(fp->out_ep, fp->out_reqv[i]);
	usb_मुक्त_all_descriptors(f);
err:
	ERROR(cdev, "USB CDC Phonet: cannot autoconfigure\n");
	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_phonet_opts *to_f_phonet_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_phonet_opts,
			func_inst.group);
पूर्ण

अटल व्योम phonet_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_phonet_opts *opts = to_f_phonet_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations phonet_item_ops = अणु
	.release		= phonet_attr_release,
पूर्ण;

अटल sमाप_प्रकार f_phonet_अगरname_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस gether_get_अगरname(to_f_phonet_opts(item)->net, page, PAGE_SIZE);
पूर्ण

CONFIGFS_ATTR_RO(f_phonet_, अगरname);

अटल काष्ठा configfs_attribute *phonet_attrs[] = अणु
	&f_phonet_attr_अगरname,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type phonet_func_type = अणु
	.ct_item_ops	= &phonet_item_ops,
	.ct_attrs	= phonet_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम phonet_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_phonet_opts *opts;

	opts = container_of(f, काष्ठा f_phonet_opts, func_inst);
	अगर (opts->bound)
		gphonet_cleanup(opts->net);
	अन्यथा
		मुक्त_netdev(opts->net);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *phonet_alloc_inst(व्योम)
अणु
	काष्ठा f_phonet_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	opts->func_inst.मुक्त_func_inst = phonet_मुक्त_inst;
	opts->net = gphonet_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण

	config_group_init_type_name(&opts->func_inst.group, "",
			&phonet_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम phonet_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_phonet *phonet;

	phonet = func_to_pn(f);
	kमुक्त(phonet);
पूर्ण

अटल व्योम pn_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_phonet *fp = func_to_pn(f);
	पूर्णांक i;

	/* We are alपढ़ोy disconnected */
	अगर (fp->in_req)
		usb_ep_मुक्त_request(fp->in_ep, fp->in_req);
	क्रम (i = 0; i < phonet_rxq_size; i++)
		अगर (fp->out_reqv[i])
			usb_ep_मुक्त_request(fp->out_ep, fp->out_reqv[i]);

	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *phonet_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_phonet *fp;
	काष्ठा f_phonet_opts *opts;
	पूर्णांक size;

	size = माप(*fp) + (phonet_rxq_size * माप(काष्ठा usb_request *));
	fp = kzalloc(size, GFP_KERNEL);
	अगर (!fp)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_phonet_opts, func_inst);

	fp->dev = opts->net;
	fp->function.name = "phonet";
	fp->function.bind = pn_bind;
	fp->function.unbind = pn_unbind;
	fp->function.set_alt = pn_set_alt;
	fp->function.get_alt = pn_get_alt;
	fp->function.disable = pn_disconnect;
	fp->function.मुक्त_func = phonet_मुक्त;
	spin_lock_init(&fp->rx.lock);

	वापस &fp->function;
पूर्ण

काष्ठा net_device *gphonet_setup_शेष(व्योम)
अणु
	काष्ठा net_device *dev;
	काष्ठा phonet_port *port;

	/* Create net device */
	dev = alloc_netdev(माप(*port), "upnlink%d", NET_NAME_UNKNOWN,
			   pn_net_setup);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	port = netdev_priv(dev);
	spin_lock_init(&port->lock);
	netअगर_carrier_off(dev);

	वापस dev;
पूर्ण

व्योम gphonet_set_gadget(काष्ठा net_device *net, काष्ठा usb_gadget *g)
अणु
	SET_NETDEV_DEV(net, &g->dev);
पूर्ण

पूर्णांक gphonet_रेजिस्टर_netdev(काष्ठा net_device *net)
अणु
	पूर्णांक status;

	status = रेजिस्टर_netdev(net);
	अगर (status)
		मुक्त_netdev(net);

	वापस status;
पूर्ण

व्योम gphonet_cleanup(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_netdev(dev);
पूर्ण

DECLARE_USB_FUNCTION_INIT(phonet, phonet_alloc_inst, phonet_alloc);
MODULE_AUTHOR("Rथऊmi Denis-Courmont");
MODULE_LICENSE("GPL");
