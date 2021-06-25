<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * zero.c -- Gadget Zero, क्रम USB development
 *
 * Copyright (C) 2003-2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

/*
 * Gadget Zero only needs two bulk endpoपूर्णांकs, and is an example of how you
 * can ग_लिखो a hardware-agnostic gadget driver running inside a USB device.
 * Some hardware details are visible, but करोn't affect most of the driver.
 *
 * Use it with the Linux host side "usbtest" driver to get a basic functional
 * test of your device-side usb stack, or with "usb-skeleton".
 *
 * It supports two similar configurations.  One sinks whatever the usb host
 * ग_लिखोs, and in वापस sources zeroes.  The other loops whatever the host
 * ग_लिखोs back, so the host can पढ़ो it.
 *
 * Many drivers will only have one configuration, letting them be much
 * simpler अगर they also करोn't support high speed operation (like this
 * driver करोes).
 *
 * Why is *this* driver using two configurations, rather than setting up
 * two पूर्णांकerfaces with dअगरferent functions?  To help verअगरy that multiple
 * configuration infraकाष्ठाure is working correctly; also, so that it can
 * work with low capability USB controllers without four bulk endpoपूर्णांकs.
 */

/*
 * driver assumes self-घातered hardware, and
 * has no way क्रम users to trigger remote wakeup.
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/composite.h>

#समावेश "g_zero.h"
/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

#घोषणा DRIVER_VERSION		"Cinco de Mayo 2008"

अटल स्थिर अक्षर दीर्घname[] = "Gadget Zero";

/*
 * Normally the "loopback" configuration is second (index 1) so
 * it's not the default.  Here's where to change that order, to
 * work better with hosts where config changes are problematic or
 * controllers (like original superh) that only support one config.
 */
अटल bool loopशेष = 0;
module_param(loopशेष, bool, S_IRUGO|S_IWUSR);

अटल काष्ठा usb_zero_options gzero_options = अणु
	.isoc_पूर्णांकerval = GZERO_ISOC_INTERVAL,
	.isoc_maxpacket = GZERO_ISOC_MAXPACKET,
	.bulk_buflen = GZERO_BULK_BUFLEN,
	.qlen = GZERO_QLEN,
	.ss_bulk_qlen = GZERO_SS_BULK_QLEN,
	.ss_iso_qlen = GZERO_SS_ISO_QLEN,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
 *
 * DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#अगर_अघोषित	CONFIG_USB_ZERO_HNPTEST
#घोषणा DRIVER_VENDOR_NUM	0x0525		/* NetChip */
#घोषणा DRIVER_PRODUCT_NUM	0xa4a0		/* Linux-USB "Gadget Zero" */
#घोषणा DEFAULT_AUTORESUME	0
#अन्यथा
#घोषणा DRIVER_VENDOR_NUM	0x1a0a		/* OTG test device IDs */
#घोषणा DRIVER_PRODUCT_NUM	0xbadd
#घोषणा DEFAULT_AUTORESUME	5
#पूर्ण_अगर

/* If the optional "autoresume" mode is enabled, it provides good
 * functional coverage क्रम the "USBCV" test harness from USB-IF.
 * It's always set अगर OTG mode is enabled.
 */
अटल अचिन्हित स्वतःresume = DEFAULT_AUTORESUME;
module_param(स्वतःresume, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(स्वतःresume, "zero, or seconds before remote wakeup");

/* Maximum Autoresume समय */
अटल अचिन्हित max_स्वतःresume;
module_param(max_स्वतःresume, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_स्वतःresume, "maximum seconds before remote wakeup");

/* Interval between two remote wakeups */
अटल अचिन्हित स्वतःresume_पूर्णांकerval_ms;
module_param(स्वतःresume_पूर्णांकerval_ms, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(स्वतःresume_पूर्णांकerval_ms,
		"milliseconds to increase successive wakeup delays");

अटल अचिन्हित स्वतःresume_step_ms;
/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceClass =		USB_CLASS_VENDOR_SPEC,

	.idVenकरोr =		cpu_to_le16(DRIVER_VENDOR_NUM),
	.idProduct =		cpu_to_le16(DRIVER_PRODUCT_NUM),
	.bNumConfigurations =	2,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

/* string IDs are asचिन्हित dynamically */
/* शेष serial number takes at least two packets */
अटल अक्षर serial[] = "0123456789.0123456789.0123456789";

#घोषणा USB_GZERO_SS_DESC	(USB_GADGET_FIRST_AVAIL_IDX + 0)
#घोषणा USB_GZERO_LB_DESC	(USB_GADGET_FIRST_AVAIL_IDX + 1)

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = दीर्घname,
	[USB_GADGET_SERIAL_IDX].s = serial,
	[USB_GZERO_SS_DESC].s	= "source and sink data",
	[USB_GZERO_LB_DESC].s	= "loop input to output",
	अणु  पूर्ण			/* end of list */
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

अटल काष्ठा समयr_list	स्वतःresume_समयr;
अटल काष्ठा usb_composite_dev *स्वतःresume_cdev;

अटल व्योम zero_स्वतःresume(काष्ठा समयr_list *unused)
अणु
	काष्ठा usb_composite_dev	*cdev = स्वतःresume_cdev;
	काष्ठा usb_gadget		*g = cdev->gadget;

	/* unconfigured devices can't issue wakeups */
	अगर (!cdev->config)
		वापस;

	/* Normally the host would be woken up क्रम something
	 * more signअगरicant than just a समयr firing; likely
	 * because of some direct user request.
	 */
	अगर (g->speed != USB_SPEED_UNKNOWN) अणु
		पूर्णांक status = usb_gadget_wakeup(g);
		INFO(cdev, "%s --> %d\n", __func__, status);
	पूर्ण
पूर्ण

अटल व्योम zero_suspend(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (cdev->gadget->speed == USB_SPEED_UNKNOWN)
		वापस;

	अगर (स्वतःresume) अणु
		अगर (max_स्वतःresume &&
			(स्वतःresume_step_ms > max_स्वतःresume * 1000))
				स्वतःresume_step_ms = स्वतःresume * 1000;

		mod_समयr(&स्वतःresume_समयr, jअगरfies +
			msecs_to_jअगरfies(स्वतःresume_step_ms));
		DBG(cdev, "suspend, wakeup in %d milliseconds\n",
			स्वतःresume_step_ms);

		स्वतःresume_step_ms += स्वतःresume_पूर्णांकerval_ms;
	पूर्ण अन्यथा
		DBG(cdev, "%s\n", __func__);
पूर्ण

अटल व्योम zero_resume(काष्ठा usb_composite_dev *cdev)
अणु
	DBG(cdev, "%s\n", __func__);
	del_समयr(&स्वतःresume_समयr);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_configuration loopback_driver = अणु
	.label          = "loopback",
	.bConfigurationValue = 2,
	.bmAttributes   = USB_CONFIG_ATT_SELFPOWER,
	/* .iConfiguration = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_function *func_ss;
अटल काष्ठा usb_function_instance *func_inst_ss;

अटल पूर्णांक ss_config_setup(काष्ठा usb_configuration *c,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	चयन (ctrl->bRequest) अणु
	हाल 0x5b:
	हाल 0x5c:
		वापस func_ss->setup(func_ss, ctrl);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल काष्ठा usb_configuration sourcesink_driver = अणु
	.label                  = "source/sink",
	.setup                  = ss_config_setup,
	.bConfigurationValue    = 3,
	.bmAttributes           = USB_CONFIG_ATT_SELFPOWER,
	/* .iConfiguration      = DYNAMIC */
पूर्ण;

module_param_named(buflen, gzero_options.bulk_buflen, uपूर्णांक, 0);
module_param_named(pattern, gzero_options.pattern, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(pattern, "0 = all zeroes, 1 = mod63, 2 = none");

module_param_named(isoc_पूर्णांकerval, gzero_options.isoc_पूर्णांकerval, uपूर्णांक,
		S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(isoc_पूर्णांकerval, "1 - 16");

module_param_named(isoc_maxpacket, gzero_options.isoc_maxpacket, uपूर्णांक,
		S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(isoc_maxpacket, "0 - 1023 (fs), 0 - 1024 (hs/ss)");

module_param_named(isoc_mult, gzero_options.isoc_mult, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(isoc_mult, "0 - 2 (hs/ss only)");

module_param_named(isoc_maxburst, gzero_options.isoc_maxburst, uपूर्णांक,
		S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(isoc_maxburst, "0 - 15 (ss only)");

अटल काष्ठा usb_function *func_lb;
अटल काष्ठा usb_function_instance *func_inst_lb;

module_param_named(qlen, gzero_options.qlen, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(qlen, "depth of loopback queue");

module_param_named(ss_bulk_qlen, gzero_options.ss_bulk_qlen, uपूर्णांक,
		S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(bulk_qlen, "depth of sourcesink queue for bulk transfer");

module_param_named(ss_iso_qlen, gzero_options.ss_iso_qlen, uपूर्णांक,
		S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(iso_qlen, "depth of sourcesink queue for iso transfer");

अटल पूर्णांक zero_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा f_ss_opts	*ss_opts;
	काष्ठा f_lb_opts	*lb_opts;
	पूर्णांक			status;

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */
	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		वापस status;

	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	device_desc.iSerialNumber = strings_dev[USB_GADGET_SERIAL_IDX].id;

	स्वतःresume_cdev = cdev;
	समयr_setup(&स्वतःresume_समयr, zero_स्वतःresume, 0);

	func_inst_ss = usb_get_function_instance("SourceSink");
	अगर (IS_ERR(func_inst_ss))
		वापस PTR_ERR(func_inst_ss);

	ss_opts =  container_of(func_inst_ss, काष्ठा f_ss_opts, func_inst);
	ss_opts->pattern = gzero_options.pattern;
	ss_opts->isoc_पूर्णांकerval = gzero_options.isoc_पूर्णांकerval;
	ss_opts->isoc_maxpacket = gzero_options.isoc_maxpacket;
	ss_opts->isoc_mult = gzero_options.isoc_mult;
	ss_opts->isoc_maxburst = gzero_options.isoc_maxburst;
	ss_opts->bulk_buflen = gzero_options.bulk_buflen;
	ss_opts->bulk_qlen = gzero_options.ss_bulk_qlen;
	ss_opts->iso_qlen = gzero_options.ss_iso_qlen;

	func_ss = usb_get_function(func_inst_ss);
	अगर (IS_ERR(func_ss)) अणु
		status = PTR_ERR(func_ss);
		जाओ err_put_func_inst_ss;
	पूर्ण

	func_inst_lb = usb_get_function_instance("Loopback");
	अगर (IS_ERR(func_inst_lb)) अणु
		status = PTR_ERR(func_inst_lb);
		जाओ err_put_func_ss;
	पूर्ण

	lb_opts = container_of(func_inst_lb, काष्ठा f_lb_opts, func_inst);
	lb_opts->bulk_buflen = gzero_options.bulk_buflen;
	lb_opts->qlen = gzero_options.qlen;

	func_lb = usb_get_function(func_inst_lb);
	अगर (IS_ERR(func_lb)) अणु
		status = PTR_ERR(func_lb);
		जाओ err_put_func_inst_lb;
	पूर्ण

	sourcesink_driver.iConfiguration = strings_dev[USB_GZERO_SS_DESC].id;
	loopback_driver.iConfiguration = strings_dev[USB_GZERO_LB_DESC].id;

	/* support स्वतःresume क्रम remote wakeup testing */
	sourcesink_driver.bmAttributes &= ~USB_CONFIG_ATT_WAKEUP;
	loopback_driver.bmAttributes &= ~USB_CONFIG_ATT_WAKEUP;
	sourcesink_driver.descriptors = शून्य;
	loopback_driver.descriptors = शून्य;
	अगर (स्वतःresume) अणु
		sourcesink_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
		loopback_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
		स्वतःresume_step_ms = स्वतःresume * 1000;
	पूर्ण

	/* support OTG प्रणालीs */
	अगर (gadget_is_otg(cdev->gadget)) अणु
		अगर (!otg_desc[0]) अणु
			काष्ठा usb_descriptor_header *usb_desc;

			usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
			अगर (!usb_desc) अणु
				status = -ENOMEM;
				जाओ err_conf_flb;
			पूर्ण
			usb_otg_descriptor_init(cdev->gadget, usb_desc);
			otg_desc[0] = usb_desc;
			otg_desc[1] = शून्य;
		पूर्ण
		sourcesink_driver.descriptors = otg_desc;
		sourcesink_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
		loopback_driver.descriptors = otg_desc;
		loopback_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	/* Register primary, then secondary configuration.  Note that
	 * SH3 only allows one config...
	 */
	अगर (loopशेष) अणु
		usb_add_config_only(cdev, &loopback_driver);
		usb_add_config_only(cdev, &sourcesink_driver);
	पूर्ण अन्यथा अणु
		usb_add_config_only(cdev, &sourcesink_driver);
		usb_add_config_only(cdev, &loopback_driver);
	पूर्ण
	status = usb_add_function(&sourcesink_driver, func_ss);
	अगर (status)
		जाओ err_मुक्त_otg_desc;

	usb_ep_स्वतःconfig_reset(cdev->gadget);
	status = usb_add_function(&loopback_driver, func_lb);
	अगर (status)
		जाओ err_मुक्त_otg_desc;

	usb_ep_स्वतःconfig_reset(cdev->gadget);
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);

	INFO(cdev, "%s, version: " DRIVER_VERSION "\n", दीर्घname);

	वापस 0;

err_मुक्त_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
err_conf_flb:
	usb_put_function(func_lb);
	func_lb = शून्य;
err_put_func_inst_lb:
	usb_put_function_instance(func_inst_lb);
	func_inst_lb = शून्य;
err_put_func_ss:
	usb_put_function(func_ss);
	func_ss = शून्य;
err_put_func_inst_ss:
	usb_put_function_instance(func_inst_ss);
	func_inst_ss = शून्य;
	वापस status;
पूर्ण

अटल पूर्णांक zero_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	del_समयr_sync(&स्वतःresume_समयr);
	अगर (!IS_ERR_OR_शून्य(func_ss))
		usb_put_function(func_ss);
	usb_put_function_instance(func_inst_ss);
	अगर (!IS_ERR_OR_शून्य(func_lb))
		usb_put_function(func_lb);
	usb_put_function_instance(func_inst_lb);
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver zero_driver = अणु
	.name		= "zero",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= zero_bind,
	.unbind		= zero_unbind,
	.suspend	= zero_suspend,
	.resume		= zero_resume,
पूर्ण;

module_usb_composite_driver(zero_driver);

MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
