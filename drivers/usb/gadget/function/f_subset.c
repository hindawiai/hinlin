<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_subset.c -- "CDC Subset" Ethernet link function driver
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>

#समावेश "u_ether.h"
#समावेश "u_ether_configfs.h"
#समावेश "u_gether.h"

/*
 * This function packages a simple "CDC Subset" Ethernet port with no real
 * control mechanisms; just raw data transfer over two bulk endpoपूर्णांकs.
 * The data transfer model is exactly that of CDC Ethernet, which is
 * why we call it the "CDC Subset".
 *
 * Because it's not standardized, this has some पूर्णांकeroperability issues.
 * They mostly relate to driver binding, since the data transfer model is
 * so simple (CDC Ethernet).  The original versions of this protocol used
 * specअगरic product/venकरोr IDs:  byteswapped IDs क्रम Digital Equipment's
 * SA-1100 "Itsy" board, which could run Linux 2.4 kernels and supported
 * daughtercards with USB peripheral connectors.  (It was used more often
 * with other boards, using the Itsy identअगरiers.)  Linux hosts recognized
 * this with CONFIG_USB_ARMLINUX; these devices have only one configuration
 * and one पूर्णांकerface.
 *
 * At some poपूर्णांक, MCCI defined a (nonconक्रमmant) CDC MDLM variant called
 * "SAFE", which happens to have a mode which is identical to the "CDC
 * Subset" in terms of data transfer and lack of control model.  This was
 * aकरोpted by later Sharp Zaurus models, and by some other software which
 * Linux hosts recognize with CONFIG_USB_NET_ZAURUS.
 *
 * Because Microsoft's RNDIS drivers are far from robust, we added a few
 * descriptors to the CDC Subset code, making this code look like a SAFE
 * implementation.  This lets you use MCCI's host side MS-Winकरोws drivers
 * अगर you get fed up with RNDIS.  It also makes it easier क्रम composite
 * drivers to work, since they can use class based binding instead of
 * caring about specअगरic product and venकरोr IDs.
 */

काष्ठा f_gether अणु
	काष्ठा gether			port;

	अक्षर				ethaddr[14];
पूर्ण;

अटल अंतरभूत काष्ठा f_gether *func_to_geth(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_gether, port.func);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * "Simple" CDC-subset option is a simple venकरोr-neutral model that most
 * full speed controllers can handle:  one पूर्णांकerface, two bulk endpoपूर्णांकs.
 * To assist host side drivers, we fancy it up a bit, and add descriptors so
 * some host side drivers will understand it as a "SAFE" variant.
 *
 * "SAFE" loosely follows CDC WMC MDLM, violating the spec in various ways.
 * Data endpoपूर्णांकs live in the control पूर्णांकerface, there's no data पूर्णांकerface.
 * And it's not used to talk to a cell phone radio.
 */

/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_descriptor subset_data_पूर्णांकf = अणु
	.bLength =		माप subset_data_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =      USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_MDLM,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_header_desc mdlm_header_desc = अणु
	.bLength =		माप mdlm_header_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,

	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल काष्ठा usb_cdc_mdlm_desc mdlm_desc = अणु
	.bLength =		माप mdlm_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_MDLM_TYPE,

	.bcdVersion =		cpu_to_le16(0x0100),
	.bGUID = अणु
		0x5d, 0x34, 0xcf, 0x66, 0x11, 0x18, 0x11, 0xd6,
		0xa2, 0x1a, 0x00, 0x01, 0x02, 0xca, 0x9a, 0x7f,
	पूर्ण,
पूर्ण;

/* since "usb_cdc_mdlm_detail_desc" is a variable length काष्ठाure, we
 * can't really use its struct.  All we do here is say that we're using
 * the submode of "SAFE" which directly matches the CDC Subset.
 */
अटल u8 mdlm_detail_desc[] = अणु
	6,
	USB_DT_CS_INTERFACE,
	USB_CDC_MDLM_DETAIL_TYPE,

	0,	/* "SAFE" */
	0,	/* network control capabilities (none) */
	0,	/* network data capabilities ("raw" encapsulation) */
पूर्ण;

अटल काष्ठा usb_cdc_ether_desc ether_desc = अणु
	.bLength =		माप ether_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_ETHERNET_TYPE,

	/* this descriptor actually adds value, surprise! */
	/* .iMACAddress = DYNAMIC */
	.bmEthernetStatistics =	cpu_to_le32(0), /* no statistics */
	.wMaxSegmentSize =	cpu_to_le16(ETH_FRAME_LEN),
	.wNumberMCFilters =	cpu_to_le16(0),
	.bNumberPowerFilters =	0,
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_subset_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_subset_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_eth_function[] = अणु
	(काष्ठा usb_descriptor_header *) &subset_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &mdlm_header_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_detail_desc,
	(काष्ठा usb_descriptor_header *) &ether_desc,
	(काष्ठा usb_descriptor_header *) &fs_subset_in_desc,
	(काष्ठा usb_descriptor_header *) &fs_subset_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_subset_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_subset_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_eth_function[] = अणु
	(काष्ठा usb_descriptor_header *) &subset_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &mdlm_header_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_detail_desc,
	(काष्ठा usb_descriptor_header *) &ether_desc,
	(काष्ठा usb_descriptor_header *) &hs_subset_in_desc,
	(काष्ठा usb_descriptor_header *) &hs_subset_out_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_subset_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_subset_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_subset_bulk_comp_desc = अणु
	.bLength =		माप ss_subset_bulk_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 2 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
पूर्ण;

अटल काष्ठा usb_descriptor_header *ss_eth_function[] = अणु
	(काष्ठा usb_descriptor_header *) &subset_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &mdlm_header_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_desc,
	(काष्ठा usb_descriptor_header *) &mdlm_detail_desc,
	(काष्ठा usb_descriptor_header *) &ether_desc,
	(काष्ठा usb_descriptor_header *) &ss_subset_in_desc,
	(काष्ठा usb_descriptor_header *) &ss_subset_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_subset_out_desc,
	(काष्ठा usb_descriptor_header *) &ss_subset_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

अटल काष्ठा usb_string geth_string_defs[] = अणु
	[0].s = "CDC Ethernet Subset/SAFE",
	[1].s = "",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings geth_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		geth_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *geth_strings[] = अणु
	&geth_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक geth_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_gether		*geth = func_to_geth(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा net_device	*net;

	/* we know alt == 0, so this is an activation or a reset */

	अगर (geth->port.in_ep->enabled) अणु
		DBG(cdev, "reset cdc subset\n");
		gether_disconnect(&geth->port);
	पूर्ण

	DBG(cdev, "init + activate cdc subset\n");
	अगर (config_ep_by_speed(cdev->gadget, f, geth->port.in_ep) ||
	    config_ep_by_speed(cdev->gadget, f, geth->port.out_ep)) अणु
		geth->port.in_ep->desc = शून्य;
		geth->port.out_ep->desc = शून्य;
		वापस -EINVAL;
	पूर्ण

	net = gether_connect(&geth->port);
	वापस PTR_ERR_OR_ZERO(net);
पूर्ण

अटल व्योम geth_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_gether	*geth = func_to_geth(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "net deactivated\n");
	gether_disconnect(&geth->port);
पूर्ण

/*-------------------------------------------------------------------------*/

/* serial function driver setup/binding */

अटल पूर्णांक
geth_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_gether		*geth = func_to_geth(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	काष्ठा f_gether_opts	*gether_opts;

	gether_opts = container_of(f->fi, काष्ठा f_gether_opts, func_inst);

	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to gether_opts->bound access
	 */
	अगर (!gether_opts->bound) अणु
		mutex_lock(&gether_opts->lock);
		gether_set_gadget(gether_opts->net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(gether_opts->net);
		mutex_unlock(&gether_opts->lock);
		अगर (status)
			वापस status;
		gether_opts->bound = true;
	पूर्ण

	us = usb_gstrings_attach(cdev, geth_strings,
				 ARRAY_SIZE(geth_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);

	subset_data_पूर्णांकf.iInterface = us[0].id;
	ether_desc.iMACAddress = us[1].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	subset_data_पूर्णांकf.bInterfaceNumber = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_subset_in_desc);
	अगर (!ep)
		जाओ fail;
	geth->port.in_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_subset_out_desc);
	अगर (!ep)
		जाओ fail;
	geth->port.out_ep = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	hs_subset_in_desc.bEndpoपूर्णांकAddress = fs_subset_in_desc.bEndpoपूर्णांकAddress;
	hs_subset_out_desc.bEndpoपूर्णांकAddress =
		fs_subset_out_desc.bEndpoपूर्णांकAddress;

	ss_subset_in_desc.bEndpoपूर्णांकAddress = fs_subset_in_desc.bEndpoपूर्णांकAddress;
	ss_subset_out_desc.bEndpoपूर्णांकAddress =
		fs_subset_out_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, fs_eth_function, hs_eth_function,
			ss_eth_function, ss_eth_function);
	अगर (status)
		जाओ fail;

	/* NOTE:  all that is करोne without knowing or caring about
	 * the network link ... which is unavailable to this code
	 * until we're activated via set_alt().
	 */

	DBG(cdev, "CDC Subset: %s speed IN/%s OUT/%s\n",
			gadget_is_superspeed(c->cdev->gadget) ? "super" :
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			geth->port.in_ep->name, geth->port.out_ep->name);
	वापस 0;

fail:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_gether_opts *to_f_gether_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_gether_opts,
			    func_inst.group);
पूर्ण

/* f_gether_item_ops */
USB_ETHERNET_CONFIGFS_ITEM(gether);

/* f_gether_opts_dev_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(gether);

/* f_gether_opts_host_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(gether);

/* f_gether_opts_qmult */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(gether);

/* f_gether_opts_अगरname */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(gether);

अटल काष्ठा configfs_attribute *gether_attrs[] = अणु
	&gether_opts_attr_dev_addr,
	&gether_opts_attr_host_addr,
	&gether_opts_attr_qmult,
	&gether_opts_attr_अगरname,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type gether_func_type = अणु
	.ct_item_ops	= &gether_item_ops,
	.ct_attrs	= gether_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम geth_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_gether_opts *opts;

	opts = container_of(f, काष्ठा f_gether_opts, func_inst);
	अगर (opts->bound)
		gether_cleanup(netdev_priv(opts->net));
	अन्यथा
		मुक्त_netdev(opts->net);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *geth_alloc_inst(व्योम)
अणु
	काष्ठा f_gether_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = geth_मुक्त_inst;
	opts->net = gether_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण

	config_group_init_type_name(&opts->func_inst.group, "",
				    &gether_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम geth_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_gether *eth;

	eth = func_to_geth(f);
	kमुक्त(eth);
पूर्ण

अटल व्योम geth_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	geth_string_defs[0].id = 0;
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *geth_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_gether	*geth;
	काष्ठा f_gether_opts *opts;
	पूर्णांक status;

	/* allocate and initialize one new instance */
	geth = kzalloc(माप(*geth), GFP_KERNEL);
	अगर (!geth)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_gether_opts, func_inst);

	mutex_lock(&opts->lock);
	opts->refcnt++;
	/* export host's Ethernet address in CDC क्रमmat */
	status = gether_get_host_addr_cdc(opts->net, geth->ethaddr,
					  माप(geth->ethaddr));
	अगर (status < 12) अणु
		kमुक्त(geth);
		mutex_unlock(&opts->lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	geth_string_defs[1].s = geth->ethaddr;

	geth->port.ioport = netdev_priv(opts->net);
	mutex_unlock(&opts->lock);
	geth->port.cdc_filter = DEFAULT_FILTER;

	geth->port.func.name = "cdc_subset";
	geth->port.func.bind = geth_bind;
	geth->port.func.unbind = geth_unbind;
	geth->port.func.set_alt = geth_set_alt;
	geth->port.func.disable = geth_disable;
	geth->port.func.मुक्त_func = geth_मुक्त;

	वापस &geth->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(geth, geth_alloc_inst, geth_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
