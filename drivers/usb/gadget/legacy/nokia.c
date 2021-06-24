<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nokia.c -- Nokia Composite Gadget Driver
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 * Contact: Felipe Balbi <felipe.balbi@nokia.com>
 *
 * This gadget driver borrows from serial.c which is:
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>

#समावेश "u_serial.h"
#समावेश "u_ether.h"
#समावेश "u_phonet.h"
#समावेश "u_ecm.h"
#समावेश "f_mass_storage.h"

/* Defines */

#घोषणा NOKIA_VERSION_NUM		0x0211
#घोषणा NOKIA_LONG_NAME			"N900 (PC-Suite Mode)"

USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHERNET_MODULE_PARAMETERS();

अटल काष्ठा fsg_module_parameters fsg_mod_data = अणु
	.stall = 0,
	.luns = 2,
	.removable_count = 2,
	.removable = अणु 1, 1, पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल अचिन्हित पूर्णांक fsg_num_buffers = CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS;

#अन्यथा

/*
 * Number of buffers we will use.
 * 2 is usually enough क्रम good buffering pipeline
 */
#घोषणा fsg_num_buffers	CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS

#पूर्ण_अगर /* CONFIG_USB_DEBUG */

FSG_MODULE_PARAMETERS(/* no prefix */, fsg_mod_data);

#घोषणा NOKIA_VENDOR_ID			0x0421	/* Nokia */
#घोषणा NOKIA_PRODUCT_ID		0x01c8	/* Nokia Gadget */

/* string IDs are asचिन्हित dynamically */

#घोषणा STRING_DESCRIPTION_IDX		USB_GADGET_FIRST_AVAIL_IDX

अटल अक्षर manufacturer_nokia[] = "Nokia";
अटल स्थिर अक्षर description_nokia[] = "PC-Suite Configuration";

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = manufacturer_nokia,
	[USB_GADGET_PRODUCT_IDX].s = NOKIA_LONG_NAME,
	[USB_GADGET_SERIAL_IDX].s = "",
	[STRING_DESCRIPTION_IDX].s = description_nokia,
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

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength		= USB_DT_DEVICE_SIZE,
	.bDescriptorType	= USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceClass		= USB_CLASS_COMM,
	.idVenकरोr		= cpu_to_le16(NOKIA_VENDOR_ID),
	.idProduct		= cpu_to_le16(NOKIA_PRODUCT_ID),
	.bcdDevice		= cpu_to_le16(NOKIA_VERSION_NUM),
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	.bNumConfigurations =	1,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Module */
MODULE_DESCRIPTION("Nokia composite gadget driver for N900");
MODULE_AUTHOR("Felipe Balbi");
MODULE_LICENSE("GPL");

/*-------------------------------------------------------------------------*/
अटल काष्ठा usb_function *f_acm_cfg1;
अटल काष्ठा usb_function *f_acm_cfg2;
अटल काष्ठा usb_function *f_ecm_cfg1;
अटल काष्ठा usb_function *f_ecm_cfg2;
अटल काष्ठा usb_function *f_obex1_cfg1;
अटल काष्ठा usb_function *f_obex2_cfg1;
अटल काष्ठा usb_function *f_obex1_cfg2;
अटल काष्ठा usb_function *f_obex2_cfg2;
अटल काष्ठा usb_function *f_phonet_cfg1;
अटल काष्ठा usb_function *f_phonet_cfg2;
अटल काष्ठा usb_function *f_msg_cfg1;
अटल काष्ठा usb_function *f_msg_cfg2;


अटल काष्ठा usb_configuration nokia_config_500ma_driver = अणु
	.label		= "Bus Powered",
	.bConfigurationValue = 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_ONE,
	.MaxPower	= 500,
पूर्ण;

अटल काष्ठा usb_configuration nokia_config_100ma_driver = अणु
	.label		= "Self Powered",
	.bConfigurationValue = 2,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
	.MaxPower	= 100,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_acm;
अटल काष्ठा usb_function_instance *fi_ecm;
अटल काष्ठा usb_function_instance *fi_obex1;
अटल काष्ठा usb_function_instance *fi_obex2;
अटल काष्ठा usb_function_instance *fi_phonet;
अटल काष्ठा usb_function_instance *fi_msg;

अटल पूर्णांक nokia_bind_config(काष्ठा usb_configuration *c)
अणु
	काष्ठा usb_function *f_acm;
	काष्ठा usb_function *f_phonet = शून्य;
	काष्ठा usb_function *f_obex1 = शून्य;
	काष्ठा usb_function *f_ecm;
	काष्ठा usb_function *f_obex2 = शून्य;
	काष्ठा usb_function *f_msg;
	पूर्णांक status = 0;
	पूर्णांक obex1_stat = -1;
	पूर्णांक obex2_stat = -1;
	पूर्णांक phonet_stat = -1;

	अगर (!IS_ERR(fi_phonet)) अणु
		f_phonet = usb_get_function(fi_phonet);
		अगर (IS_ERR(f_phonet))
			pr_debug("could not get phonet function\n");
	पूर्ण

	अगर (!IS_ERR(fi_obex1)) अणु
		f_obex1 = usb_get_function(fi_obex1);
		अगर (IS_ERR(f_obex1))
			pr_debug("could not get obex function 0\n");
	पूर्ण

	अगर (!IS_ERR(fi_obex2)) अणु
		f_obex2 = usb_get_function(fi_obex2);
		अगर (IS_ERR(f_obex2))
			pr_debug("could not get obex function 1\n");
	पूर्ण

	f_acm = usb_get_function(fi_acm);
	अगर (IS_ERR(f_acm)) अणु
		status = PTR_ERR(f_acm);
		जाओ err_get_acm;
	पूर्ण

	f_ecm = usb_get_function(fi_ecm);
	अगर (IS_ERR(f_ecm)) अणु
		status = PTR_ERR(f_ecm);
		जाओ err_get_ecm;
	पूर्ण

	f_msg = usb_get_function(fi_msg);
	अगर (IS_ERR(f_msg)) अणु
		status = PTR_ERR(f_msg);
		जाओ err_get_msg;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(f_phonet)) अणु
		phonet_stat = usb_add_function(c, f_phonet);
		अगर (phonet_stat)
			pr_debug("could not add phonet function\n");
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(f_obex1)) अणु
		obex1_stat = usb_add_function(c, f_obex1);
		अगर (obex1_stat)
			pr_debug("could not add obex function 0\n");
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(f_obex2)) अणु
		obex2_stat = usb_add_function(c, f_obex2);
		अगर (obex2_stat)
			pr_debug("could not add obex function 1\n");
	पूर्ण

	status = usb_add_function(c, f_acm);
	अगर (status)
		जाओ err_conf;

	status = usb_add_function(c, f_ecm);
	अगर (status) अणु
		pr_debug("could not bind ecm config %d\n", status);
		जाओ err_ecm;
	पूर्ण

	status = usb_add_function(c, f_msg);
	अगर (status)
		जाओ err_msg;

	अगर (c == &nokia_config_500ma_driver) अणु
		f_acm_cfg1 = f_acm;
		f_ecm_cfg1 = f_ecm;
		f_phonet_cfg1 = f_phonet;
		f_obex1_cfg1 = f_obex1;
		f_obex2_cfg1 = f_obex2;
		f_msg_cfg1 = f_msg;
	पूर्ण अन्यथा अणु
		f_acm_cfg2 = f_acm;
		f_ecm_cfg2 = f_ecm;
		f_phonet_cfg2 = f_phonet;
		f_obex1_cfg2 = f_obex1;
		f_obex2_cfg2 = f_obex2;
		f_msg_cfg2 = f_msg;
	पूर्ण

	वापस status;
err_msg:
	usb_हटाओ_function(c, f_ecm);
err_ecm:
	usb_हटाओ_function(c, f_acm);
err_conf:
	अगर (!obex2_stat)
		usb_हटाओ_function(c, f_obex2);
	अगर (!obex1_stat)
		usb_हटाओ_function(c, f_obex1);
	अगर (!phonet_stat)
		usb_हटाओ_function(c, f_phonet);
	usb_put_function(f_msg);
err_get_msg:
	usb_put_function(f_ecm);
err_get_ecm:
	usb_put_function(f_acm);
err_get_acm:
	अगर (!IS_ERR_OR_शून्य(f_obex2))
		usb_put_function(f_obex2);
	अगर (!IS_ERR_OR_शून्य(f_obex1))
		usb_put_function(f_obex1);
	अगर (!IS_ERR_OR_शून्य(f_phonet))
		usb_put_function(f_phonet);
	वापस status;
पूर्ण

अटल पूर्णांक nokia_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा fsg_opts		*fsg_opts;
	काष्ठा fsg_config	fsg_config;
	पूर्णांक			status;

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ err_usb;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	status = strings_dev[STRING_DESCRIPTION_IDX].id;
	nokia_config_500ma_driver.iConfiguration = status;
	nokia_config_100ma_driver.iConfiguration = status;

	अगर (!gadget_is_altset_supported(gadget)) अणु
		status = -ENODEV;
		जाओ err_usb;
	पूर्ण

	fi_phonet = usb_get_function_instance("phonet");
	अगर (IS_ERR(fi_phonet))
		pr_debug("could not find phonet function\n");

	fi_obex1 = usb_get_function_instance("obex");
	अगर (IS_ERR(fi_obex1))
		pr_debug("could not find obex function 1\n");

	fi_obex2 = usb_get_function_instance("obex");
	अगर (IS_ERR(fi_obex2))
		pr_debug("could not find obex function 2\n");

	fi_acm = usb_get_function_instance("acm");
	अगर (IS_ERR(fi_acm)) अणु
		status = PTR_ERR(fi_acm);
		जाओ err_obex2_inst;
	पूर्ण

	fi_ecm = usb_get_function_instance("ecm");
	अगर (IS_ERR(fi_ecm)) अणु
		status = PTR_ERR(fi_ecm);
		जाओ err_acm_inst;
	पूर्ण

	fi_msg = usb_get_function_instance("mass_storage");
	अगर (IS_ERR(fi_msg)) अणु
		status = PTR_ERR(fi_msg);
		जाओ err_ecm_inst;
	पूर्ण

	/* set up mass storage function */
	fsg_config_from_params(&fsg_config, &fsg_mod_data, fsg_num_buffers);
	fsg_config.venकरोr_name = "Nokia";
	fsg_config.product_name = "N900";

	fsg_opts = fsg_opts_from_func_inst(fi_msg);
	fsg_opts->no_configfs = true;

	status = fsg_common_set_num_buffers(fsg_opts->common, fsg_num_buffers);
	अगर (status)
		जाओ err_msg_inst;

	status = fsg_common_set_cdev(fsg_opts->common, cdev, fsg_config.can_stall);
	अगर (status)
		जाओ err_msg_buf;

	fsg_common_set_sysfs(fsg_opts->common, true);

	status = fsg_common_create_luns(fsg_opts->common, &fsg_config);
	अगर (status)
		जाओ err_msg_buf;

	fsg_common_set_inquiry_string(fsg_opts->common, fsg_config.venकरोr_name,
				      fsg_config.product_name);

	/* finally रेजिस्टर the configuration */
	status = usb_add_config(cdev, &nokia_config_500ma_driver,
			nokia_bind_config);
	अगर (status < 0)
		जाओ err_msg_luns;

	status = usb_add_config(cdev, &nokia_config_100ma_driver,
			nokia_bind_config);
	अगर (status < 0)
		जाओ err_put_cfg1;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&gadget->dev, "%s\n", NOKIA_LONG_NAME);

	वापस 0;

err_put_cfg1:
	usb_put_function(f_acm_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	usb_put_function(f_ecm_cfg1);
err_msg_luns:
	fsg_common_हटाओ_luns(fsg_opts->common);
err_msg_buf:
	fsg_common_मुक्त_buffers(fsg_opts->common);
err_msg_inst:
	usb_put_function_instance(fi_msg);
err_ecm_inst:
	usb_put_function_instance(fi_ecm);
err_acm_inst:
	usb_put_function_instance(fi_acm);
err_obex2_inst:
	अगर (!IS_ERR(fi_obex2))
		usb_put_function_instance(fi_obex2);
	अगर (!IS_ERR(fi_obex1))
		usb_put_function_instance(fi_obex1);
	अगर (!IS_ERR(fi_phonet))
		usb_put_function_instance(fi_phonet);
err_usb:
	वापस status;
पूर्ण

अटल पूर्णांक nokia_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (!IS_ERR_OR_शून्य(f_obex1_cfg2))
		usb_put_function(f_obex1_cfg2);
	अगर (!IS_ERR_OR_शून्य(f_obex2_cfg2))
		usb_put_function(f_obex2_cfg2);
	अगर (!IS_ERR_OR_शून्य(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	अगर (!IS_ERR_OR_शून्य(f_phonet_cfg2))
		usb_put_function(f_phonet_cfg2);
	usb_put_function(f_acm_cfg1);
	usb_put_function(f_acm_cfg2);
	usb_put_function(f_ecm_cfg1);
	usb_put_function(f_ecm_cfg2);
	usb_put_function(f_msg_cfg1);
	usb_put_function(f_msg_cfg2);

	usb_put_function_instance(fi_msg);
	usb_put_function_instance(fi_ecm);
	अगर (!IS_ERR(fi_obex2))
		usb_put_function_instance(fi_obex2);
	अगर (!IS_ERR(fi_obex1))
		usb_put_function_instance(fi_obex1);
	अगर (!IS_ERR(fi_phonet))
		usb_put_function_instance(fi_phonet);
	usb_put_function_instance(fi_acm);

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver nokia_driver = अणु
	.name		= "g_nokia",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= nokia_bind,
	.unbind		= nokia_unbind,
पूर्ण;

module_usb_composite_driver(nokia_driver);
