<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * acm_ms.c -- Composite driver, with ACM and mass storage support
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 * Author: David Brownell
 * Modअगरied: Klaus Schwarzkopf <schwarzkopf@sensortherm.de>
 *
 * Heavily based on multi.c and cdc2.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "u_serial.h"

#घोषणा DRIVER_DESC		"Composite Gadget (ACM + MS)"
#घोषणा DRIVER_VERSION		"2011/10/10"

/*-------------------------------------------------------------------------*/

/*
 * DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#घोषणा ACM_MS_VENDOR_NUM	0x1d6b	/* Linux Foundation */
#घोषणा ACM_MS_PRODUCT_NUM	0x0106	/* Composite Gadget: ACM + MS*/

#समावेश "f_mass_storage.h"

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceClass =		USB_CLASS_MISC /* 0xEF */,
	.bDeviceSubClass =	2,
	.bDeviceProtocol =	1,

	/* .bMaxPacketSize0 = f(hardware) */

	/* Venकरोr and product id can be overridden by module parameters.  */
	.idVenकरोr =		cpu_to_le16(ACM_MS_VENDOR_NUM),
	.idProduct =		cpu_to_le16(ACM_MS_PRODUCT_NUM),
	/* .bcdDevice = f(hardware) */
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	/* NO SERIAL NUMBER */
	/*.bNumConfigurations =	DYNAMIC*/
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

/****************************** Configurations ******************************/

अटल काष्ठा fsg_module_parameters fsg_mod_data = अणु .stall = 1 पूर्ण;
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल अचिन्हित पूर्णांक fsg_num_buffers = CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS;

#अन्यथा

/*
 * Number of buffers we will use.
 * 2 is usually enough क्रम good buffering pipeline
 */
#घोषणा fsg_num_buffers	CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_खाताS */

FSG_MODULE_PARAMETERS(/* no prefix */, fsg_mod_data);

/*-------------------------------------------------------------------------*/
अटल काष्ठा usb_function *f_acm;
अटल काष्ठा usb_function_instance *f_acm_inst;

अटल काष्ठा usb_function_instance *fi_msg;
अटल काष्ठा usb_function *f_msg;

/*
 * We _always_ have both ACM and mass storage functions.
 */
अटल पूर्णांक acm_ms_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक	status;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_acm = usb_get_function(f_acm_inst);
	अगर (IS_ERR(f_acm))
		वापस PTR_ERR(f_acm);

	f_msg = usb_get_function(fi_msg);
	अगर (IS_ERR(f_msg)) अणु
		status = PTR_ERR(f_msg);
		जाओ put_acm;
	पूर्ण

	status = usb_add_function(c, f_acm);
	अगर (status < 0)
		जाओ put_msg;

	status = usb_add_function(c, f_msg);
	अगर (status)
		जाओ हटाओ_acm;

	वापस 0;
हटाओ_acm:
	usb_हटाओ_function(c, f_acm);
put_msg:
	usb_put_function(f_msg);
put_acm:
	usb_put_function(f_acm);
	वापस status;
पूर्ण

अटल काष्ठा usb_configuration acm_ms_config_driver = अणु
	.label			= DRIVER_DESC,
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक acm_ms_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा fsg_opts		*opts;
	काष्ठा fsg_config	config;
	पूर्णांक			status;

	f_acm_inst = usb_get_function_instance("acm");
	अगर (IS_ERR(f_acm_inst))
		वापस PTR_ERR(f_acm_inst);

	fi_msg = usb_get_function_instance("mass_storage");
	अगर (IS_ERR(fi_msg)) अणु
		status = PTR_ERR(fi_msg);
		जाओ fail_get_msg;
	पूर्ण

	/* set up mass storage function */
	fsg_config_from_params(&config, &fsg_mod_data, fsg_num_buffers);
	opts = fsg_opts_from_func_inst(fi_msg);

	opts->no_configfs = true;
	status = fsg_common_set_num_buffers(opts->common, fsg_num_buffers);
	अगर (status)
		जाओ fail;

	status = fsg_common_set_cdev(opts->common, cdev, config.can_stall);
	अगर (status)
		जाओ fail_set_cdev;

	fsg_common_set_sysfs(opts->common, true);
	status = fsg_common_create_luns(opts->common, &config);
	अगर (status)
		जाओ fail_set_cdev;

	fsg_common_set_inquiry_string(opts->common, config.venकरोr_name,
				      config.product_name);
	/*
	 * Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */
	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail_string_ids;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(gadget);
		अगर (!usb_desc) अणु
			status = -ENOMEM;
			जाओ fail_string_ids;
		पूर्ण
		usb_otg_descriptor_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	/* रेजिस्टर our configuration */
	status = usb_add_config(cdev, &acm_ms_config_driver, acm_ms_करो_config);
	अगर (status < 0)
		जाओ fail_otg_desc;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&gadget->dev, "%s, version: " DRIVER_VERSION "\n",
			DRIVER_DESC);
	वापस 0;

	/* error recovery */
fail_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail_string_ids:
	fsg_common_हटाओ_luns(opts->common);
fail_set_cdev:
	fsg_common_मुक्त_buffers(opts->common);
fail:
	usb_put_function_instance(fi_msg);
fail_get_msg:
	usb_put_function_instance(f_acm_inst);
	वापस status;
पूर्ण

अटल पूर्णांक acm_ms_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	usb_put_function(f_msg);
	usb_put_function_instance(fi_msg);
	usb_put_function(f_acm);
	usb_put_function_instance(f_acm_inst);
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver acm_ms_driver = अणु
	.name		= "g_acm_ms",
	.dev		= &device_desc,
	.max_speed	= USB_SPEED_SUPER,
	.strings	= dev_strings,
	.bind		= acm_ms_bind,
	.unbind		= acm_ms_unbind,
पूर्ण;

module_usb_composite_driver(acm_ms_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Klaus Schwarzkopf <schwarzkopf@sensortherm.de>");
MODULE_LICENSE("GPL v2");
