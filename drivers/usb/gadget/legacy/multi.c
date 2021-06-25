<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * multi.c -- Multअगरunction Composite driver
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 * Copyright (C) 2009 Samsung Electronics
 * Author: Michal Nazarewicz (mina86@mina86.com)
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश "u_serial.h"
#अगर defined USB_ETH_RNDIS
#  undef USB_ETH_RNDIS
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_G_MULTI_RNDIS
#  define USB_ETH_RNDIS y
#पूर्ण_अगर


#घोषणा DRIVER_DESC		"Multifunction Composite Gadget"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Michal Nazarewicz");
MODULE_LICENSE("GPL");


#समावेश "f_mass_storage.h"

#समावेश "u_ecm.h"
#अगर_घोषित USB_ETH_RNDIS
#  include "u_rndis.h"
#  include "rndis.h"
#पूर्ण_अगर
#समावेश "u_ether.h"

USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHERNET_MODULE_PARAMETERS();

/***************************** Device Descriptor ****************************/

#घोषणा MULTI_VENDOR_NUM	0x1d6b	/* Linux Foundation */
#घोषणा MULTI_PRODUCT_NUM	0x0104	/* Multअगरunction Composite Gadget */


क्रमागत अणु
	__MULTI_NO_CONFIG,
#अगर_घोषित CONFIG_USB_G_MULTI_RNDIS
	MULTI_RNDIS_CONFIG_NUM,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	MULTI_CDC_CONFIG_NUM,
#पूर्ण_अगर
पूर्ण;


अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceClass =		USB_CLASS_MISC /* 0xEF */,
	.bDeviceSubClass =	2,
	.bDeviceProtocol =	1,

	/* Venकरोr and product id can be overridden by module parameters.  */
	.idVenकरोr =		cpu_to_le16(MULTI_VENDOR_NUM),
	.idProduct =		cpu_to_le16(MULTI_PRODUCT_NUM),
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

क्रमागत अणु
	MULTI_STRING_RNDIS_CONFIG_IDX = USB_GADGET_FIRST_AVAIL_IDX,
	MULTI_STRING_CDC_CONFIG_IDX,
पूर्ण;

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = DRIVER_DESC,
	[USB_GADGET_SERIAL_IDX].s = "",
	[MULTI_STRING_RNDIS_CONFIG_IDX].s = "Multifunction with RNDIS",
	[MULTI_STRING_CDC_CONFIG_IDX].s   = "Multifunction with CDC ECM",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings *dev_strings[] = अणु
	&(काष्ठा usb_gadget_strings)अणु
		.language	= 0x0409,	/* en-us */
		.strings	= strings_dev,
	पूर्ण,
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

अटल काष्ठा usb_function_instance *fi_acm;
अटल काष्ठा usb_function_instance *fi_msg;

/********** RNDIS **********/

#अगर_घोषित USB_ETH_RNDIS
अटल काष्ठा usb_function_instance *fi_rndis;
अटल काष्ठा usb_function *f_acm_rndis;
अटल काष्ठा usb_function *f_rndis;
अटल काष्ठा usb_function *f_msg_rndis;

अटल पूर्णांक rndis_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक ret;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_rndis = usb_get_function(fi_rndis);
	अगर (IS_ERR(f_rndis))
		वापस PTR_ERR(f_rndis);

	ret = usb_add_function(c, f_rndis);
	अगर (ret < 0)
		जाओ err_func_rndis;

	f_acm_rndis = usb_get_function(fi_acm);
	अगर (IS_ERR(f_acm_rndis)) अणु
		ret = PTR_ERR(f_acm_rndis);
		जाओ err_func_acm;
	पूर्ण

	ret = usb_add_function(c, f_acm_rndis);
	अगर (ret)
		जाओ err_conf;

	f_msg_rndis = usb_get_function(fi_msg);
	अगर (IS_ERR(f_msg_rndis)) अणु
		ret = PTR_ERR(f_msg_rndis);
		जाओ err_fsg;
	पूर्ण

	ret = usb_add_function(c, f_msg_rndis);
	अगर (ret)
		जाओ err_run;

	वापस 0;
err_run:
	usb_put_function(f_msg_rndis);
err_fsg:
	usb_हटाओ_function(c, f_acm_rndis);
err_conf:
	usb_put_function(f_acm_rndis);
err_func_acm:
	usb_हटाओ_function(c, f_rndis);
err_func_rndis:
	usb_put_function(f_rndis);
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_config_रेजिस्टर(काष्ठा usb_composite_dev *cdev)
अणु
	अटल काष्ठा usb_configuration config = अणु
		.bConfigurationValue	= MULTI_RNDIS_CONFIG_NUM,
		.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
	पूर्ण;

	config.label          = strings_dev[MULTI_STRING_RNDIS_CONFIG_IDX].s;
	config.iConfiguration = strings_dev[MULTI_STRING_RNDIS_CONFIG_IDX].id;

	वापस usb_add_config(cdev, &config, rndis_करो_config);
पूर्ण

#अन्यथा

अटल पूर्णांक rndis_config_रेजिस्टर(काष्ठा usb_composite_dev *cdev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर


/********** CDC ECM **********/

#अगर_घोषित CONFIG_USB_G_MULTI_CDC
अटल काष्ठा usb_function_instance *fi_ecm;
अटल काष्ठा usb_function *f_acm_multi;
अटल काष्ठा usb_function *f_ecm;
अटल काष्ठा usb_function *f_msg_multi;

अटल पूर्णांक cdc_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक ret;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_ecm = usb_get_function(fi_ecm);
	अगर (IS_ERR(f_ecm))
		वापस PTR_ERR(f_ecm);

	ret = usb_add_function(c, f_ecm);
	अगर (ret < 0)
		जाओ err_func_ecm;

	/* implicit port_num is zero */
	f_acm_multi = usb_get_function(fi_acm);
	अगर (IS_ERR(f_acm_multi)) अणु
		ret = PTR_ERR(f_acm_multi);
		जाओ err_func_acm;
	पूर्ण

	ret = usb_add_function(c, f_acm_multi);
	अगर (ret)
		जाओ err_conf;

	f_msg_multi = usb_get_function(fi_msg);
	अगर (IS_ERR(f_msg_multi)) अणु
		ret = PTR_ERR(f_msg_multi);
		जाओ err_fsg;
	पूर्ण

	ret = usb_add_function(c, f_msg_multi);
	अगर (ret)
		जाओ err_run;

	वापस 0;
err_run:
	usb_put_function(f_msg_multi);
err_fsg:
	usb_हटाओ_function(c, f_acm_multi);
err_conf:
	usb_put_function(f_acm_multi);
err_func_acm:
	usb_हटाओ_function(c, f_ecm);
err_func_ecm:
	usb_put_function(f_ecm);
	वापस ret;
पूर्ण

अटल पूर्णांक cdc_config_रेजिस्टर(काष्ठा usb_composite_dev *cdev)
अणु
	अटल काष्ठा usb_configuration config = अणु
		.bConfigurationValue	= MULTI_CDC_CONFIG_NUM,
		.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
	पूर्ण;

	config.label          = strings_dev[MULTI_STRING_CDC_CONFIG_IDX].s;
	config.iConfiguration = strings_dev[MULTI_STRING_CDC_CONFIG_IDX].id;

	वापस usb_add_config(cdev, &config, cdc_करो_config);
पूर्ण

#अन्यथा

अटल पूर्णांक cdc_config_रेजिस्टर(काष्ठा usb_composite_dev *cdev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर



/****************************** Gadget Bind ******************************/

अटल पूर्णांक multi_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget *gadget = cdev->gadget;
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	काष्ठा f_ecm_opts *ecm_opts;
#पूर्ण_अगर
#अगर_घोषित USB_ETH_RNDIS
	काष्ठा f_rndis_opts *rndis_opts;
#पूर्ण_अगर
	काष्ठा fsg_opts *fsg_opts;
	काष्ठा fsg_config config;
	पूर्णांक status;

	अगर (!can_support_ecm(cdev->gadget)) अणु
		dev_err(&gadget->dev, "controller '%s' not usable\n",
			gadget->name);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	fi_ecm = usb_get_function_instance("ecm");
	अगर (IS_ERR(fi_ecm))
		वापस PTR_ERR(fi_ecm);

	ecm_opts = container_of(fi_ecm, काष्ठा f_ecm_opts, func_inst);

	gether_set_qmult(ecm_opts->net, qmult);
	अगर (!gether_set_host_addr(ecm_opts->net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(ecm_opts->net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);
#पूर्ण_अगर

#अगर_घोषित USB_ETH_RNDIS
	fi_rndis = usb_get_function_instance("rndis");
	अगर (IS_ERR(fi_rndis)) अणु
		status = PTR_ERR(fi_rndis);
		जाओ fail;
	पूर्ण

	rndis_opts = container_of(fi_rndis, काष्ठा f_rndis_opts, func_inst);

	gether_set_qmult(rndis_opts->net, qmult);
	अगर (!gether_set_host_addr(rndis_opts->net, host_addr))
		pr_info("using host ethernet address: %s", host_addr);
	अगर (!gether_set_dev_addr(rndis_opts->net, dev_addr))
		pr_info("using self ethernet address: %s", dev_addr);
#पूर्ण_अगर

#अगर (defined CONFIG_USB_G_MULTI_CDC && defined USB_ETH_RNDIS)
	/*
	 * If both ecm and rndis are selected then:
	 *	1) rndis borrows the net पूर्णांकerface from ecm
	 *	2) since the पूर्णांकerface is shared it must not be bound
	 *	twice - in ecm's _and_ rndis' binds, so करो it here.
	 */
	gether_set_gadget(ecm_opts->net, cdev->gadget);
	status = gether_रेजिस्टर_netdev(ecm_opts->net);
	अगर (status)
		जाओ fail0;

	rndis_borrow_net(fi_rndis, ecm_opts->net);
	ecm_opts->bound = true;
#पूर्ण_अगर

	/* set up serial link layer */
	fi_acm = usb_get_function_instance("acm");
	अगर (IS_ERR(fi_acm)) अणु
		status = PTR_ERR(fi_acm);
		जाओ fail0;
	पूर्ण

	/* set up mass storage function */
	fi_msg = usb_get_function_instance("mass_storage");
	अगर (IS_ERR(fi_msg)) अणु
		status = PTR_ERR(fi_msg);
		जाओ fail1;
	पूर्ण
	fsg_config_from_params(&config, &fsg_mod_data, fsg_num_buffers);
	fsg_opts = fsg_opts_from_func_inst(fi_msg);

	fsg_opts->no_configfs = true;
	status = fsg_common_set_num_buffers(fsg_opts->common, fsg_num_buffers);
	अगर (status)
		जाओ fail2;

	status = fsg_common_set_cdev(fsg_opts->common, cdev, config.can_stall);
	अगर (status)
		जाओ fail_set_cdev;

	fsg_common_set_sysfs(fsg_opts->common, true);
	status = fsg_common_create_luns(fsg_opts->common, &config);
	अगर (status)
		जाओ fail_set_cdev;

	fsg_common_set_inquiry_string(fsg_opts->common, config.venकरोr_name,
				      config.product_name);

	/* allocate string IDs */
	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (unlikely(status < 0))
		जाओ fail_string_ids;
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

	/* रेजिस्टर configurations */
	status = rndis_config_रेजिस्टर(cdev);
	अगर (unlikely(status < 0))
		जाओ fail_otg_desc;

	status = cdc_config_रेजिस्टर(cdev);
	अगर (unlikely(status < 0))
		जाओ fail_otg_desc;
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);

	/* we're करोne */
	dev_info(&gadget->dev, DRIVER_DESC "\n");
	वापस 0;


	/* error recovery */
fail_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail_string_ids:
	fsg_common_हटाओ_luns(fsg_opts->common);
fail_set_cdev:
	fsg_common_मुक्त_buffers(fsg_opts->common);
fail2:
	usb_put_function_instance(fi_msg);
fail1:
	usb_put_function_instance(fi_acm);
fail0:
#अगर_घोषित USB_ETH_RNDIS
	usb_put_function_instance(fi_rndis);
fail:
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	usb_put_function_instance(fi_ecm);
#पूर्ण_अगर
	वापस status;
पूर्ण

अटल पूर्णांक multi_unbind(काष्ठा usb_composite_dev *cdev)
अणु
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	usb_put_function(f_msg_multi);
#पूर्ण_अगर
#अगर_घोषित USB_ETH_RNDIS
	usb_put_function(f_msg_rndis);
#पूर्ण_अगर
	usb_put_function_instance(fi_msg);
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	usb_put_function(f_acm_multi);
#पूर्ण_अगर
#अगर_घोषित USB_ETH_RNDIS
	usb_put_function(f_acm_rndis);
#पूर्ण_अगर
	usb_put_function_instance(fi_acm);
#अगर_घोषित USB_ETH_RNDIS
	usb_put_function(f_rndis);
	usb_put_function_instance(fi_rndis);
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_G_MULTI_CDC
	usb_put_function(f_ecm);
	usb_put_function_instance(fi_ecm);
#पूर्ण_अगर
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण


/****************************** Some noise ******************************/


अटल काष्ठा usb_composite_driver multi_driver = अणु
	.name		= "g_multi",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= multi_bind,
	.unbind		= multi_unbind,
	.needs_serial	= 1,
पूर्ण;

module_usb_composite_driver(multi_driver);
