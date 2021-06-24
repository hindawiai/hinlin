<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cdc2.c -- CDC Composite driver, with ECM and ACM support
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "u_ether.h"
#समावेश "u_serial.h"
#समावेश "u_ecm.h"


#घोषणा DRIVER_DESC		"CDC Composite Gadget"
#घोषणा DRIVER_VERSION		"King Kamehameha Day 2008"

/*-------------------------------------------------------------------------*/

/* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
 * It's क्रम devices with only this composite CDC configuration.
 */
#घोषणा CDC_VENDOR_NUM		0x0525	/* NetChip */
#घोषणा CDC_PRODUCT_NUM		0xa4aa	/* CDC Composite: ECM + ACM */

USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHERNET_MODULE_PARAMETERS();

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceClass =		USB_CLASS_COMM,
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	/* .bMaxPacketSize0 = f(hardware) */

	/* Venकरोr and product id can be overridden by module parameters.  */
	.idVenकरोr =		cpu_to_le16(CDC_VENDOR_NUM),
	.idProduct =		cpu_to_le16(CDC_PRODUCT_NUM),
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

/*-------------------------------------------------------------------------*/
अटल काष्ठा usb_function *f_acm;
अटल काष्ठा usb_function_instance *fi_serial;

अटल काष्ठा usb_function *f_ecm;
अटल काष्ठा usb_function_instance *fi_ecm;

/*
 * We _always_ have both CDC ECM and CDC ACM functions.
 */
अटल पूर्णांक cdc_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक	status;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_ecm = usb_get_function(fi_ecm);
	अगर (IS_ERR(f_ecm)) अणु
		status = PTR_ERR(f_ecm);
		जाओ err_get_ecm;
	पूर्ण

	status = usb_add_function(c, f_ecm);
	अगर (status)
		जाओ err_add_ecm;

	f_acm = usb_get_function(fi_serial);
	अगर (IS_ERR(f_acm)) अणु
		status = PTR_ERR(f_acm);
		जाओ err_get_acm;
	पूर्ण

	status = usb_add_function(c, f_acm);
	अगर (status)
		जाओ err_add_acm;
	वापस 0;

err_add_acm:
	usb_put_function(f_acm);
err_get_acm:
	usb_हटाओ_function(c, f_ecm);
err_add_ecm:
	usb_put_function(f_ecm);
err_get_ecm:
	वापस status;
पूर्ण

अटल काष्ठा usb_configuration cdc_config_driver = अणु
	.label			= "CDC Composite (ECM + ACM)",
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक cdc_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा f_ecm_opts	*ecm_opts;
	पूर्णांक			status;

	अगर (!can_support_ecm(cdev->gadget)) अणु
		dev_err(&gadget->dev, "controller '%s' not usable\n",
				gadget->name);
		वापस -EINVAL;
	पूर्ण

	fi_ecm = usb_get_function_instance("ecm");
	अगर (IS_ERR(fi_ecm))
		वापस PTR_ERR(fi_ecm);

	ecm_opts = container_of(fi_ecm, काष्ठा f_ecm_opts, func_inst);

	gether_set_qmult(ecm_opts->net, qmult);
	अगर (!gether_set_host_addr(ecm_opts->net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(ecm_opts->net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);

	fi_serial = usb_get_function_instance("acm");
	अगर (IS_ERR(fi_serial)) अणु
		status = PTR_ERR(fi_serial);
		जाओ fail;
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

	/* रेजिस्टर our configuration */
	status = usb_add_config(cdev, &cdc_config_driver, cdc_करो_config);
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
	usb_put_function_instance(fi_serial);
fail:
	usb_put_function_instance(fi_ecm);
	वापस status;
पूर्ण

अटल पूर्णांक cdc_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	usb_put_function(f_acm);
	usb_put_function_instance(fi_serial);
	अगर (!IS_ERR_OR_शून्य(f_ecm))
		usb_put_function(f_ecm);
	अगर (!IS_ERR_OR_शून्य(fi_ecm))
		usb_put_function_instance(fi_ecm);
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver cdc_driver = अणु
	.name		= "g_cdc",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= cdc_bind,
	.unbind		= cdc_unbind,
पूर्ण;

module_usb_composite_driver(cdc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
