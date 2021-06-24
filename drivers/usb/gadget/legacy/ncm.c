<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ncm.c -- NCM gadget driver
 *
 * Copyright (C) 2010 Nokia Corporation
 * Contact: Yauheni Kaliuta <yauheni.kaliuta@nokia.com>
 *
 * The driver borrows from ether.c which is:
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 */

/* #घोषणा DEBUG */
/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/composite.h>

#समावेश "u_ether.h"
#समावेश "u_ncm.h"

#घोषणा DRIVER_DESC		"NCM Gadget"

/*-------------------------------------------------------------------------*/

/* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
 * It's क्रम devices with only CDC Ethernet configurations.
 */
#घोषणा CDC_VENDOR_NUM		0x0525	/* NetChip */
#घोषणा CDC_PRODUCT_NUM		0xa4a1	/* Linux-USB Ethernet Gadget */

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHERNET_MODULE_PARAMETERS();

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

/* string IDs are asचिन्हित dynamically */
अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = DRIVER_DESC,
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

अटल काष्ठा usb_function_instance *f_ncm_inst;
अटल काष्ठा usb_function *f_ncm;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ncm_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_ncm = usb_get_function(f_ncm_inst);
	अगर (IS_ERR(f_ncm))
		वापस PTR_ERR(f_ncm);

	status = usb_add_function(c, f_ncm);
	अगर (status < 0) अणु
		usb_put_function(f_ncm);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usb_configuration ncm_config_driver = अणु
	/* .label = f(hardware) */
	.label			= "CDC Ethernet (NCM)",
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक gncm_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा f_ncm_opts	*ncm_opts;
	पूर्णांक			status;

	f_ncm_inst = usb_get_function_instance("ncm");
	अगर (IS_ERR(f_ncm_inst))
		वापस PTR_ERR(f_ncm_inst);

	ncm_opts = container_of(f_ncm_inst, काष्ठा f_ncm_opts, func_inst);

	gether_set_qmult(ncm_opts->net, qmult);
	अगर (!gether_set_host_addr(ncm_opts->net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(ncm_opts->net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(gadget);
		अगर (!usb_desc) अणु
			status = -ENOMEM;
			जाओ fail;
		पूर्ण
		usb_otg_descriptor_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	status = usb_add_config(cdev, &ncm_config_driver,
				ncm_करो_config);
	अगर (status < 0)
		जाओ fail1;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&gadget->dev, "%s\n", DRIVER_DESC);

	वापस 0;

fail1:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail:
	usb_put_function_instance(f_ncm_inst);
	वापस status;
पूर्ण

अटल पूर्णांक gncm_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (!IS_ERR_OR_शून्य(f_ncm))
		usb_put_function(f_ncm);
	अगर (!IS_ERR_OR_शून्य(f_ncm_inst))
		usb_put_function_instance(f_ncm_inst);
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver ncm_driver = अणु
	.name		= "g_ncm",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= gncm_bind,
	.unbind		= gncm_unbind,
पूर्ण;

module_usb_composite_driver(ncm_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Yauheni Kaliuta");
MODULE_LICENSE("GPL");
