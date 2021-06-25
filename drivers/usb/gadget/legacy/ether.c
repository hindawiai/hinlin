<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ether.c -- Ethernet gadget driver, with CDC and non-CDC options
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#अगर defined USB_ETH_RNDIS
#  undef USB_ETH_RNDIS
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_ETH_RNDIS
#  define USB_ETH_RNDIS y
#पूर्ण_अगर

#समावेश "u_ether.h"


/*
 * Ethernet gadget driver -- with CDC and non-CDC options
 * Builds on hardware support क्रम a full duplex link.
 *
 * CDC Ethernet is the standard USB solution क्रम sending Ethernet frames
 * using USB.  Real hardware tends to use the same framing protocol but look
 * dअगरferent क्रम control features.  This driver strongly prefers to use
 * this USB-IF standard as its खोलो-प्रणालीs पूर्णांकeroperability solution;
 * most host side USB stacks (except from Microsoft) support it.
 *
 * This is someबार called "CDC ECM" (Ethernet Control Model) to support
 * TLA-soup.  "CDC ACM" (Abstract Control Model) is क्रम modems, and a new
 * "CDC EEM" (Ethernet Emulation Model) is starting to spपढ़ो.
 *
 * There's some hardware that can't talk CDC ECM.  We make that hardware
 * implement a "minimalist" venकरोr-agnostic CDC core:  same framing, but
 * link-level setup only requires activating the configuration.  Only the
 * endpoपूर्णांक descriptors, and product/venकरोr IDs, are relevant; no control
 * operations are available.  Linux supports it, but other host operating
 * प्रणालीs may not.  (This is a subset of CDC Ethernet.)
 *
 * It turns out that अगर you add a few descriptors to that "CDC Subset",
 * (Winकरोws) host side drivers from MCCI can treat it as one submode of
 * a proprietary scheme called "SAFE" ... without needing to know about
 * specअगरic product/venकरोr IDs.  So we करो that, making it easier to use
 * those MS-Winकरोws drivers.  Those added descriptors make it resemble a
 * CDC MDLM device, but they करोn't change device behavior at all.  (See
 * MCCI Engineering report 950198 "SAFE Networking Functions".)
 *
 * A third option is also in use.  Rather than CDC Ethernet, or something
 * simpler, Microsoft pushes their own approach: RNDIS.  The published
 * RNDIS specs are ambiguous and appear to be incomplete, and are also
 * needlessly complex.  They borrow more from CDC ACM than CDC ECM.
 */

#घोषणा DRIVER_DESC		"Ethernet Gadget"
#घोषणा DRIVER_VERSION		"Memorial Day 2008"

#अगर_घोषित USB_ETH_RNDIS
#घोषणा PREFIX			"RNDIS/"
#अन्यथा
#घोषणा PREFIX			""
#पूर्ण_अगर

/*
 * This driver aims क्रम पूर्णांकeroperability by using CDC ECM unless
 *
 *		can_support_ecm()
 *
 * वापसs false, in which हाल it supports the CDC Subset.  By शेष,
 * that वापसs true; most hardware has no problems with CDC ECM, that's
 * a good शेष.  Previous versions of this driver had no शेष; this
 * version changes that, removing overhead क्रम new controller support.
 *
 *	IF YOUR HARDWARE CAN'T SUPPORT CDC ECM, UPDATE THAT ROUTINE!
 */

अटल अंतरभूत bool has_rndis(व्योम)
अणु
#अगर_घोषित	USB_ETH_RNDIS
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#समावेश <linux/module.h>

#समावेश "u_ecm.h"
#समावेश "u_gether.h"
#अगर_घोषित	USB_ETH_RNDIS
#समावेश "u_rndis.h"
#समावेश "rndis.h"
#अन्यथा
#घोषणा rndis_borrow_net(...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#समावेश "u_eem.h"

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHERNET_MODULE_PARAMETERS();

/* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
 * It's क्रम devices with only CDC Ethernet configurations.
 */
#घोषणा CDC_VENDOR_NUM		0x0525	/* NetChip */
#घोषणा CDC_PRODUCT_NUM		0xa4a1	/* Linux-USB Ethernet Gadget */

/* For hardware that can't talk CDC, we use the same venकरोr ID that
 * ARM Linux has used क्रम ethernet-over-usb, both with sa1100 and
 * with pxa250.  We're protocol-compatible, अगर the host-side drivers
 * use the endpoपूर्णांक descriptors.  bcdDevice (version) is nonzero, so
 * drivers that need to hard-wire endpoपूर्णांक numbers have a hook.
 *
 * The protocol is a minimal subset of CDC Ether, which works on any bulk
 * hardware that's not deeply broken ... even on hardware that can't talk
 * RNDIS (like SA-1100, with no पूर्णांकerrupt endpoपूर्णांक, or anything that
 * करोesn't handle control-OUT).
 */
#घोषणा	SIMPLE_VENDOR_NUM	0x049f
#घोषणा	SIMPLE_PRODUCT_NUM	0x505a

/* For hardware that can talk RNDIS and either of the above protocols,
 * use this ID ... the winकरोws INF files will know it.  Unless it's
 * used with CDC Ethernet, Linux 2.4 hosts will need updates to choose
 * the non-RNDIS configuration.
 */
#घोषणा RNDIS_VENDOR_NUM	0x0525	/* NetChip */
#घोषणा RNDIS_PRODUCT_NUM	0xa4a2	/* Ethernet/RNDIS Gadget */

/* For EEM gadमाला_लो */
#घोषणा EEM_VENDOR_NUM		0x1d6b	/* Linux Foundation */
#घोषणा EEM_PRODUCT_NUM		0x0102	/* EEM Gadget */

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceClass =		USB_CLASS_COMM,
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	/* .bMaxPacketSize0 = f(hardware) */

	/* Venकरोr and product id शेषs change according to what configs
	 * we support.  (As करोes bNumConfigurations.)  These values can
	 * also be overridden by module parameters.
	 */
	.idVenकरोr =		cpu_to_le16 (CDC_VENDOR_NUM),
	.idProduct =		cpu_to_le16 (CDC_PRODUCT_NUM),
	/* .bcdDevice = f(hardware) */
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	/* NO SERIAL NUMBER */
	.bNumConfigurations =	1,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = PREFIX DRIVER_DESC,
	[USB_GADGET_SERIAL_IDX].s = "",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings stringtab_dev = अणु
	.language	= 0x0409,	/* en-us */
	.strings	= strings_dev,
पूर्ण;

अटल काष्ठा usb_gadget_strings *dev_strings[] = अणु
	&stringtab_dev,
	शून्य,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_ecm;
अटल काष्ठा usb_function *f_ecm;

अटल काष्ठा usb_function_instance *fi_eem;
अटल काष्ठा usb_function *f_eem;

अटल काष्ठा usb_function_instance *fi_geth;
अटल काष्ठा usb_function *f_geth;

अटल काष्ठा usb_function_instance *fi_rndis;
अटल काष्ठा usb_function *f_rndis;

/*-------------------------------------------------------------------------*/

/*
 * We may not have an RNDIS configuration, but अगर we करो it needs to be
 * the first one present.  That's to make Microsoft's drivers happy,
 * and to follow DOCSIS 1.0 (cable modem standard).
 */
अटल पूर्णांक rndis_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_rndis = usb_get_function(fi_rndis);
	अगर (IS_ERR(f_rndis))
		वापस PTR_ERR(f_rndis);

	status = usb_add_function(c, f_rndis);
	अगर (status < 0)
		usb_put_function(f_rndis);

	वापस status;
पूर्ण

अटल काष्ठा usb_configuration rndis_config_driver = अणु
	.label			= "RNDIS",
	.bConfigurationValue	= 2,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_USB_ETH_EEM
अटल bool use_eem = 1;
#अन्यथा
अटल bool use_eem;
#पूर्ण_अगर
module_param(use_eem, bool, 0);
MODULE_PARM_DESC(use_eem, "use CDC EEM mode");

/*
 * We _always_ have an ECM, CDC Subset, or EEM configuration.
 */
अटल पूर्णांक eth_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status = 0;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	अगर (use_eem) अणु
		f_eem = usb_get_function(fi_eem);
		अगर (IS_ERR(f_eem))
			वापस PTR_ERR(f_eem);

		status = usb_add_function(c, f_eem);
		अगर (status < 0)
			usb_put_function(f_eem);

		वापस status;
	पूर्ण अन्यथा अगर (can_support_ecm(c->cdev->gadget)) अणु
		f_ecm = usb_get_function(fi_ecm);
		अगर (IS_ERR(f_ecm))
			वापस PTR_ERR(f_ecm);

		status = usb_add_function(c, f_ecm);
		अगर (status < 0)
			usb_put_function(f_ecm);

		वापस status;
	पूर्ण अन्यथा अणु
		f_geth = usb_get_function(fi_geth);
		अगर (IS_ERR(f_geth))
			वापस PTR_ERR(f_geth);

		status = usb_add_function(c, f_geth);
		अगर (status < 0)
			usb_put_function(f_geth);

		वापस status;
	पूर्ण

पूर्ण

अटल काष्ठा usb_configuration eth_config_driver = अणु
	/* .label = f(hardware) */
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक eth_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा f_eem_opts	*eem_opts = शून्य;
	काष्ठा f_ecm_opts	*ecm_opts = शून्य;
	काष्ठा f_gether_opts	*geth_opts = शून्य;
	काष्ठा net_device	*net;
	पूर्णांक			status;

	/* set up मुख्य config label and device descriptor */
	अगर (use_eem) अणु
		/* EEM */
		fi_eem = usb_get_function_instance("eem");
		अगर (IS_ERR(fi_eem))
			वापस PTR_ERR(fi_eem);

		eem_opts = container_of(fi_eem, काष्ठा f_eem_opts, func_inst);

		net = eem_opts->net;

		eth_config_driver.label = "CDC Ethernet (EEM)";
		device_desc.idVenकरोr = cpu_to_le16(EEM_VENDOR_NUM);
		device_desc.idProduct = cpu_to_le16(EEM_PRODUCT_NUM);
	पूर्ण अन्यथा अगर (can_support_ecm(gadget)) अणु
		/* ECM */

		fi_ecm = usb_get_function_instance("ecm");
		अगर (IS_ERR(fi_ecm))
			वापस PTR_ERR(fi_ecm);

		ecm_opts = container_of(fi_ecm, काष्ठा f_ecm_opts, func_inst);

		net = ecm_opts->net;

		eth_config_driver.label = "CDC Ethernet (ECM)";
	पूर्ण अन्यथा अणु
		/* CDC Subset */

		fi_geth = usb_get_function_instance("geth");
		अगर (IS_ERR(fi_geth))
			वापस PTR_ERR(fi_geth);

		geth_opts = container_of(fi_geth, काष्ठा f_gether_opts,
					 func_inst);

		net = geth_opts->net;

		eth_config_driver.label = "CDC Subset/SAFE";

		device_desc.idVenकरोr = cpu_to_le16(SIMPLE_VENDOR_NUM);
		device_desc.idProduct = cpu_to_le16(SIMPLE_PRODUCT_NUM);
		अगर (!has_rndis())
			device_desc.bDeviceClass = USB_CLASS_VENDOR_SPEC;
	पूर्ण

	gether_set_qmult(net, qmult);
	अगर (!gether_set_host_addr(net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);

	अगर (has_rndis()) अणु
		/* RNDIS plus ECM-or-Subset */
		gether_set_gadget(net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(net);
		अगर (status)
			जाओ fail;

		अगर (use_eem)
			eem_opts->bound = true;
		अन्यथा अगर (can_support_ecm(gadget))
			ecm_opts->bound = true;
		अन्यथा
			geth_opts->bound = true;

		fi_rndis = usb_get_function_instance("rndis");
		अगर (IS_ERR(fi_rndis)) अणु
			status = PTR_ERR(fi_rndis);
			जाओ fail;
		पूर्ण

		rndis_borrow_net(fi_rndis, net);

		device_desc.idVenकरोr = cpu_to_le16(RNDIS_VENDOR_NUM);
		device_desc.idProduct = cpu_to_le16(RNDIS_PRODUCT_NUM);
		device_desc.bNumConfigurations = 2;
	पूर्ण

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail1;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(gadget);
		अगर (!usb_desc) अणु
			status = -ENOMEM;
			जाओ fail1;
		पूर्ण
		usb_otg_descriptor_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	/* रेजिस्टर our configuration(s); RNDIS first, अगर it's used */
	अगर (has_rndis()) अणु
		status = usb_add_config(cdev, &rndis_config_driver,
				rndis_करो_config);
		अगर (status < 0)
			जाओ fail2;
	पूर्ण

	status = usb_add_config(cdev, &eth_config_driver, eth_करो_config);
	अगर (status < 0)
		जाओ fail2;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&gadget->dev, "%s, version: " DRIVER_VERSION "\n",
			DRIVER_DESC);

	वापस 0;

fail2:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail1:
	अगर (has_rndis())
		usb_put_function_instance(fi_rndis);
fail:
	अगर (use_eem)
		usb_put_function_instance(fi_eem);
	अन्यथा अगर (can_support_ecm(gadget))
		usb_put_function_instance(fi_ecm);
	अन्यथा
		usb_put_function_instance(fi_geth);
	वापस status;
पूर्ण

अटल पूर्णांक eth_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (has_rndis()) अणु
		usb_put_function(f_rndis);
		usb_put_function_instance(fi_rndis);
	पूर्ण
	अगर (use_eem) अणु
		usb_put_function(f_eem);
		usb_put_function_instance(fi_eem);
	पूर्ण अन्यथा अगर (can_support_ecm(cdev->gadget)) अणु
		usb_put_function(f_ecm);
		usb_put_function_instance(fi_ecm);
	पूर्ण अन्यथा अणु
		usb_put_function(f_geth);
		usb_put_function_instance(fi_geth);
	पूर्ण
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver eth_driver = अणु
	.name		= "g_ether",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= eth_bind,
	.unbind		= eth_unbind,
पूर्ण;

module_usb_composite_driver(eth_driver);

MODULE_DESCRIPTION(PREFIX DRIVER_DESC);
MODULE_AUTHOR("David Brownell, Benedikt Spanger");
MODULE_LICENSE("GPL");
