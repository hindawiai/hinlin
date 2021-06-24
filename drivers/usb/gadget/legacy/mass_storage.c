<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * mass_storage.c -- Mass Storage USB Gadget
 *
 * Copyright (C) 2003-2008 Alan Stern
 * Copyright (C) 2009 Samsung Electronics
 *                    Author: Michal Nazarewicz <mina86@mina86.com>
 * All rights reserved.
 */


/*
 * The Mass Storage Gadget acts as a USB Mass Storage device,
 * appearing to the host as a disk drive or as a CD-ROM drive.  In
 * addition to providing an example of a genuinely useful gadget
 * driver क्रम a USB device, it also illustrates a technique of
 * द्विगुन-buffering क्रम increased throughput.  Last but not least, it
 * gives an easy way to probe the behavior of the Mass Storage drivers
 * in a USB host.
 *
 * Since this file serves only administrative purposes and all the
 * business logic is implemented in f_mass_storage.* file.  Read
 * comments in this file क्रम more detailed description.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/module.h>

/*-------------------------------------------------------------------------*/

#घोषणा DRIVER_DESC		"Mass Storage Gadget"
#घोषणा DRIVER_VERSION		"2009/09/11"

/*
 * Thanks to NetChip Technologies क्रम करोnating this product ID.
 *
 * DO NOT REUSE THESE IDs with any other driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#घोषणा FSG_VENDOR_ID	0x0525	/* NetChip */
#घोषणा FSG_PRODUCT_ID	0xa4a5	/* Linux-USB File-backed Storage Gadget */

#समावेश "f_mass_storage.h"

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

अटल काष्ठा usb_device_descriptor msg_device_desc = अणु
	.bLength =		माप msg_device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,

	/* Venकरोr and product id can be overridden by module parameters.  */
	.idVenकरोr =		cpu_to_le16(FSG_VENDOR_ID),
	.idProduct =		cpu_to_le16(FSG_PRODUCT_ID),
	.bNumConfigurations =	1,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = DRIVER_DESC,
	[USB_GADGET_SERIAL_IDX].s = "",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings stringtab_dev = अणु
	.language       = 0x0409,       /* en-us */
	.strings        = strings_dev,
पूर्ण;

अटल काष्ठा usb_gadget_strings *dev_strings[] = अणु
	&stringtab_dev,
	शून्य,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_msg;
अटल काष्ठा usb_function *f_msg;

/****************************** Configurations ******************************/

अटल काष्ठा fsg_module_parameters mod_data = अणु
	.stall = 1
पूर्ण;
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल अचिन्हित पूर्णांक fsg_num_buffers = CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS;

#अन्यथा

/*
 * Number of buffers we will use.
 * 2 is usually enough क्रम good buffering pipeline
 */
#घोषणा fsg_num_buffers	CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_खाताS */

FSG_MODULE_PARAMETERS(/* no prefix */, mod_data);

अटल पूर्णांक msg_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक ret;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_msg = usb_get_function(fi_msg);
	अगर (IS_ERR(f_msg))
		वापस PTR_ERR(f_msg);

	ret = usb_add_function(c, f_msg);
	अगर (ret)
		जाओ put_func;

	वापस 0;

put_func:
	usb_put_function(f_msg);
	वापस ret;
पूर्ण

अटल काष्ठा usb_configuration msg_config_driver = अणु
	.label			= "Linux File-Backed Storage",
	.bConfigurationValue	= 1,
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;


/****************************** Gadget Bind ******************************/

अटल पूर्णांक msg_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा fsg_opts *opts;
	काष्ठा fsg_config config;
	पूर्णांक status;

	fi_msg = usb_get_function_instance("mass_storage");
	अगर (IS_ERR(fi_msg))
		वापस PTR_ERR(fi_msg);

	fsg_config_from_params(&config, &mod_data, fsg_num_buffers);
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

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail_string_ids;
	msg_device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(cdev->gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
		अगर (!usb_desc) अणु
			status = -ENOMEM;
			जाओ fail_string_ids;
		पूर्ण
		usb_otg_descriptor_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	status = usb_add_config(cdev, &msg_config_driver, msg_करो_config);
	अगर (status < 0)
		जाओ fail_otg_desc;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&cdev->gadget->dev,
		 DRIVER_DESC ", version: " DRIVER_VERSION "\n");
	वापस 0;

fail_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail_string_ids:
	fsg_common_हटाओ_luns(opts->common);
fail_set_cdev:
	fsg_common_मुक्त_buffers(opts->common);
fail:
	usb_put_function_instance(fi_msg);
	वापस status;
पूर्ण

अटल पूर्णांक msg_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (!IS_ERR(f_msg))
		usb_put_function(f_msg);

	अगर (!IS_ERR(fi_msg))
		usb_put_function_instance(fi_msg);

	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

/****************************** Some noise ******************************/

अटल काष्ठा usb_composite_driver msg_driver = अणु
	.name		= "g_mass_storage",
	.dev		= &msg_device_desc,
	.max_speed	= USB_SPEED_SUPER_PLUS,
	.needs_serial	= 1,
	.strings	= dev_strings,
	.bind		= msg_bind,
	.unbind		= msg_unbind,
पूर्ण;

module_usb_composite_driver(msg_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Michal Nazarewicz");
MODULE_LICENSE("GPL");
