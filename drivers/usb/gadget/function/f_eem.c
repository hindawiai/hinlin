<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_eem.c -- USB CDC Ethernet (EEM) link function driver
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 * Copyright (C) 2009 EF Johnson Technologies
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>

#समावेश "u_ether.h"
#समावेश "u_ether_configfs.h"
#समावेश "u_eem.h"

#घोषणा EEM_HLEN 2

/*
 * This function is a "CDC Ethernet Emulation Model" (CDC EEM)
 * Ethernet link.
 */

काष्ठा f_eem अणु
	काष्ठा gether			port;
	u8				ctrl_id;
पूर्ण;

अटल अंतरभूत काष्ठा f_eem *func_to_eem(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_eem, port.func);
पूर्ण

/*-------------------------------------------------------------------------*/

/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_descriptor eem_पूर्णांकf = अणु
	.bLength =		माप eem_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_EEM,
	.bInterfaceProtocol =	USB_CDC_PROTO_EEM,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_fs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_fs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *eem_fs_function[] = अणु
	/* CDC EEM control descriptors */
	(काष्ठा usb_descriptor_header *) &eem_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &eem_fs_in_desc,
	(काष्ठा usb_descriptor_header *) &eem_fs_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_hs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_hs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *eem_hs_function[] = अणु
	/* CDC EEM control descriptors */
	(काष्ठा usb_descriptor_header *) &eem_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &eem_hs_in_desc,
	(काष्ठा usb_descriptor_header *) &eem_hs_out_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_ss_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor eem_ss_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor eem_ss_bulk_comp_desc = अणु
	.bLength =		माप eem_ss_bulk_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 2 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
पूर्ण;

अटल काष्ठा usb_descriptor_header *eem_ss_function[] = अणु
	/* CDC EEM control descriptors */
	(काष्ठा usb_descriptor_header *) &eem_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &eem_ss_in_desc,
	(काष्ठा usb_descriptor_header *) &eem_ss_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &eem_ss_out_desc,
	(काष्ठा usb_descriptor_header *) &eem_ss_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

अटल काष्ठा usb_string eem_string_defs[] = अणु
	[0].s = "CDC Ethernet Emulation Model (EEM)",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings eem_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		eem_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *eem_strings[] = अणु
	&eem_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक eem_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	DBG(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
		ctrl->bRequestType, ctrl->bRequest,
		w_value, w_index, w_length);

	/* device either stalls (value < 0) or reports success */
	वापस -EOPNOTSUPP;
पूर्ण


अटल पूर्णांक eem_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_eem		*eem = func_to_eem(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा net_device	*net;

	/* we know alt == 0, so this is an activation or a reset */
	अगर (alt != 0)
		जाओ fail;

	अगर (पूर्णांकf == eem->ctrl_id) अणु
		DBG(cdev, "reset eem\n");
		gether_disconnect(&eem->port);

		अगर (!eem->port.in_ep->desc || !eem->port.out_ep->desc) अणु
			DBG(cdev, "init eem\n");
			अगर (config_ep_by_speed(cdev->gadget, f,
					       eem->port.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       eem->port.out_ep)) अणु
				eem->port.in_ep->desc = शून्य;
				eem->port.out_ep->desc = शून्य;
				जाओ fail;
			पूर्ण
		पूर्ण

		/* zlps should not occur because zero-length EEM packets
		 * will be inserted in those हालs where they would occur
		 */
		eem->port.is_zlp_ok = 1;
		eem->port.cdc_filter = DEFAULT_FILTER;
		DBG(cdev, "activate eem\n");
		net = gether_connect(&eem->port);
		अगर (IS_ERR(net))
			वापस PTR_ERR(net);
	पूर्ण अन्यथा
		जाओ fail;

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण

अटल व्योम eem_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_eem		*eem = func_to_eem(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "eem deactivated\n");

	अगर (eem->port.in_ep->enabled)
		gether_disconnect(&eem->port);
पूर्ण

/*-------------------------------------------------------------------------*/

/* EEM function driver setup/binding */

अटल पूर्णांक eem_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_eem		*eem = func_to_eem(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	काष्ठा f_eem_opts	*eem_opts;

	eem_opts = container_of(f->fi, काष्ठा f_eem_opts, func_inst);
	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to eem_opts->bound access
	 */
	अगर (!eem_opts->bound) अणु
		mutex_lock(&eem_opts->lock);
		gether_set_gadget(eem_opts->net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(eem_opts->net);
		mutex_unlock(&eem_opts->lock);
		अगर (status)
			वापस status;
		eem_opts->bound = true;
	पूर्ण

	us = usb_gstrings_attach(cdev, eem_strings,
				 ARRAY_SIZE(eem_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	eem_पूर्णांकf.iInterface = us[0].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	eem->ctrl_id = status;
	eem_पूर्णांकf.bInterfaceNumber = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &eem_fs_in_desc);
	अगर (!ep)
		जाओ fail;
	eem->port.in_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &eem_fs_out_desc);
	अगर (!ep)
		जाओ fail;
	eem->port.out_ep = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	eem_hs_in_desc.bEndpoपूर्णांकAddress = eem_fs_in_desc.bEndpoपूर्णांकAddress;
	eem_hs_out_desc.bEndpoपूर्णांकAddress = eem_fs_out_desc.bEndpoपूर्णांकAddress;

	eem_ss_in_desc.bEndpoपूर्णांकAddress = eem_fs_in_desc.bEndpoपूर्णांकAddress;
	eem_ss_out_desc.bEndpoपूर्णांकAddress = eem_fs_out_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, eem_fs_function, eem_hs_function,
			eem_ss_function, eem_ss_function);
	अगर (status)
		जाओ fail;

	DBG(cdev, "CDC Ethernet (EEM): %s speed IN/%s OUT/%s\n",
			gadget_is_superspeed(c->cdev->gadget) ? "super" :
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			eem->port.in_ep->name, eem->port.out_ep->name);
	वापस 0;

fail:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल व्योम eem_cmd_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)req->context;

	dev_kमुक्त_skb_any(skb);
पूर्ण

/*
 * Add the EEM header and ethernet checksum.
 * We currently करो not attempt to put multiple ethernet frames
 * पूर्णांकo a single USB transfer
 */
अटल काष्ठा sk_buff *eem_wrap(काष्ठा gether *port, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff	*skb2 = शून्य;
	काष्ठा usb_ep	*in = port->in_ep;
	पूर्णांक		headroom, tailroom, padlen = 0;
	u16		len;

	अगर (!skb)
		वापस शून्य;

	len = skb->len;
	headroom = skb_headroom(skb);
	tailroom = skb_tailroom(skb);

	/* When (len + EEM_HLEN + ETH_FCS_LEN) % in->maxpacket) is 0,
	 * stick two bytes of zero-length EEM packet on the end.
	 */
	अगर (((len + EEM_HLEN + ETH_FCS_LEN) % in->maxpacket) == 0)
		padlen += 2;

	अगर ((tailroom >= (ETH_FCS_LEN + padlen)) &&
			(headroom >= EEM_HLEN) && !skb_cloned(skb))
		जाओ करोne;

	skb2 = skb_copy_expand(skb, EEM_HLEN, ETH_FCS_LEN + padlen, GFP_ATOMIC);
	dev_kमुक्त_skb_any(skb);
	skb = skb2;
	अगर (!skb)
		वापस skb;

करोne:
	/* use the "no CRC" option */
	put_unaligned_be32(0xdeadbeef, skb_put(skb, 4));

	/* EEM packet header क्रमmat:
	 * b0..13:	length of ethernet frame
	 * b14:		bmCRC (0 == sentinel CRC)
	 * b15:		bmType (0 == data)
	 */
	len = skb->len;
	put_unaligned_le16(len & 0x3FFF, skb_push(skb, 2));

	/* add a zero-length EEM packet, अगर needed */
	अगर (padlen)
		put_unaligned_le16(0, skb_put(skb, 2));

	वापस skb;
पूर्ण

/*
 * Remove the EEM header.  Note that there can be many EEM packets in a single
 * USB transfer, so we need to अवरोध them out and handle them independently.
 */
अटल पूर्णांक eem_unwrap(काष्ठा gether *port,
			काष्ठा sk_buff *skb,
			काष्ठा sk_buff_head *list)
अणु
	काष्ठा usb_composite_dev	*cdev = port->func.config->cdev;
	पूर्णांक				status = 0;

	करो अणु
		काष्ठा sk_buff	*skb2;
		u16		header;
		u16		len = 0;

		अगर (skb->len < EEM_HLEN) अणु
			status = -EINVAL;
			DBG(cdev, "invalid EEM header\n");
			जाओ error;
		पूर्ण

		/* हटाओ the EEM header */
		header = get_unaligned_le16(skb->data);
		skb_pull(skb, EEM_HLEN);

		/* EEM packet header क्रमmat:
		 * b0..14:	EEM type dependent (data or command)
		 * b15:		bmType (0 == data, 1 == command)
		 */
		अगर (header & BIT(15)) अणु
			काष्ठा usb_request	*req = cdev->req;
			u16			bmEEMCmd;

			/* EEM command packet क्रमmat:
			 * b0..10:	bmEEMCmdParam
			 * b11..13:	bmEEMCmd
			 * b14:		reserved (must be zero)
			 * b15:		bmType (1 == command)
			 */
			अगर (header & BIT(14))
				जारी;

			bmEEMCmd = (header >> 11) & 0x7;
			चयन (bmEEMCmd) अणु
			हाल 0: /* echo */
				len = header & 0x7FF;
				अगर (skb->len < len) अणु
					status = -EOVERFLOW;
					जाओ error;
				पूर्ण

				skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (unlikely(!skb2)) अणु
					DBG(cdev, "EEM echo response error\n");
					जाओ next;
				पूर्ण
				skb_trim(skb2, len);
				put_unaligned_le16(BIT(15) | BIT(11) | len,
							skb_push(skb2, 2));
				skb_copy_bits(skb2, 0, req->buf, skb2->len);
				req->length = skb2->len;
				req->complete = eem_cmd_complete;
				req->zero = 1;
				req->context = skb2;
				अगर (usb_ep_queue(port->in_ep, req, GFP_ATOMIC))
					DBG(cdev, "echo response queue fail\n");
				अवरोध;

			हाल 1:  /* echo response */
			हाल 2:  /* suspend hपूर्णांक */
			हाल 3:  /* response hपूर्णांक */
			हाल 4:  /* response complete hपूर्णांक */
			हाल 5:  /* tickle */
			शेष: /* reserved */
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32		crc, crc2;
			काष्ठा sk_buff	*skb3;

			/* check क्रम zero-length EEM packet */
			अगर (header == 0)
				जारी;

			/* EEM data packet क्रमmat:
			 * b0..13:	length of ethernet frame
			 * b14:		bmCRC (0 == sentinel, 1 == calculated)
			 * b15:		bmType (0 == data)
			 */
			len = header & 0x3FFF;
			अगर ((skb->len < len)
					|| (len < (ETH_HLEN + ETH_FCS_LEN))) अणु
				status = -EINVAL;
				जाओ error;
			पूर्ण

			/* validate CRC */
			अगर (header & BIT(14)) अणु
				crc = get_unaligned_le32(skb->data + len
							- ETH_FCS_LEN);
				crc2 = ~crc32_le(~0,
						skb->data, len - ETH_FCS_LEN);
			पूर्ण अन्यथा अणु
				crc = get_unaligned_be32(skb->data + len
							- ETH_FCS_LEN);
				crc2 = 0xdeadbeef;
			पूर्ण
			अगर (crc != crc2) अणु
				DBG(cdev, "invalid EEM CRC\n");
				जाओ next;
			पूर्ण

			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (unlikely(!skb2)) अणु
				DBG(cdev, "unable to unframe EEM packet\n");
				जाओ next;
			पूर्ण
			skb_trim(skb2, len - ETH_FCS_LEN);

			skb3 = skb_copy_expand(skb2,
						NET_IP_ALIGN,
						0,
						GFP_ATOMIC);
			अगर (unlikely(!skb3)) अणु
				dev_kमुक्त_skb_any(skb2);
				जाओ next;
			पूर्ण
			dev_kमुक्त_skb_any(skb2);
			skb_queue_tail(list, skb3);
		पूर्ण
next:
		skb_pull(skb, len);
	पूर्ण जबतक (skb->len);

error:
	dev_kमुक्त_skb_any(skb);
	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_eem_opts *to_f_eem_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_eem_opts,
			    func_inst.group);
पूर्ण

/* f_eem_item_ops */
USB_ETHERNET_CONFIGFS_ITEM(eem);

/* f_eem_opts_dev_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(eem);

/* f_eem_opts_host_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(eem);

/* f_eem_opts_qmult */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(eem);

/* f_eem_opts_अगरname */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(eem);

अटल काष्ठा configfs_attribute *eem_attrs[] = अणु
	&eem_opts_attr_dev_addr,
	&eem_opts_attr_host_addr,
	&eem_opts_attr_qmult,
	&eem_opts_attr_अगरname,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type eem_func_type = अणु
	.ct_item_ops	= &eem_item_ops,
	.ct_attrs	= eem_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम eem_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_eem_opts *opts;

	opts = container_of(f, काष्ठा f_eem_opts, func_inst);
	अगर (opts->bound)
		gether_cleanup(netdev_priv(opts->net));
	अन्यथा
		मुक्त_netdev(opts->net);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *eem_alloc_inst(व्योम)
अणु
	काष्ठा f_eem_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = eem_मुक्त_inst;
	opts->net = gether_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण

	config_group_init_type_name(&opts->func_inst.group, "", &eem_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम eem_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_eem *eem;
	काष्ठा f_eem_opts *opts;

	eem = func_to_eem(f);
	opts = container_of(f->fi, काष्ठा f_eem_opts, func_inst);
	kमुक्त(eem);
	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम eem_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	DBG(c->cdev, "eem unbind\n");

	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *eem_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_eem	*eem;
	काष्ठा f_eem_opts *opts;

	/* allocate and initialize one new instance */
	eem = kzalloc(माप(*eem), GFP_KERNEL);
	अगर (!eem)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_eem_opts, func_inst);
	mutex_lock(&opts->lock);
	opts->refcnt++;

	eem->port.ioport = netdev_priv(opts->net);
	mutex_unlock(&opts->lock);
	eem->port.cdc_filter = DEFAULT_FILTER;

	eem->port.func.name = "cdc_eem";
	/* descriptors are per-instance copies */
	eem->port.func.bind = eem_bind;
	eem->port.func.unbind = eem_unbind;
	eem->port.func.set_alt = eem_set_alt;
	eem->port.func.setup = eem_setup;
	eem->port.func.disable = eem_disable;
	eem->port.func.मुक्त_func = eem_मुक्त;
	eem->port.wrap = eem_wrap;
	eem->port.unwrap = eem_unwrap;
	eem->port.header_len = EEM_HLEN;

	वापस &eem->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(eem, eem_alloc_inst, eem_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
