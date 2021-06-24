<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * serial.c -- USB gadget serial driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश "u_serial.h"


/* Defines */

#घोषणा GS_VERSION_STR			"v2.4"
#घोषणा GS_VERSION_NUM			0x2400

#घोषणा GS_LONG_NAME			"Gadget Serial"
#घोषणा GS_VERSION_NAME			GS_LONG_NAME " " GS_VERSION_STR

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
*
* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
* Instead:  allocate your own, using normal USB-IF procedures.
*/
#घोषणा GS_VENDOR_ID			0x0525	/* NetChip */
#घोषणा GS_PRODUCT_ID			0xa4a6	/* Linux-USB Serial Gadget */
#घोषणा GS_CDC_PRODUCT_ID		0xa4a7	/* ... as CDC-ACM */
#घोषणा GS_CDC_OBEX_PRODUCT_ID		0xa4a9	/* ... as CDC-OBEX */

/* string IDs are asचिन्हित dynamically */

#घोषणा STRING_DESCRIPTION_IDX		USB_GADGET_FIRST_AVAIL_IDX

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = GS_VERSION_NAME,
	[USB_GADGET_SERIAL_IDX].s = "",
	[STRING_DESCRIPTION_IDX].s = शून्य /* updated; f(use_acm) */,
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
	.bLength =		USB_DT_DEVICE_SIZE,
	.bDescriptorType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	/* .bDeviceClass = f(use_acm) */
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	/* .bMaxPacketSize0 = f(hardware) */
	.idVenकरोr =		cpu_to_le16(GS_VENDOR_ID),
	/* .idProduct =	f(use_acm) */
	.bcdDevice = cpu_to_le16(GS_VERSION_NUM),
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	.bNumConfigurations =	1,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

/*-------------------------------------------------------------------------*/

/* Module */
MODULE_DESCRIPTION(GS_VERSION_NAME);
MODULE_AUTHOR("Al Borchers");
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");

अटल bool use_acm = true;
module_param(use_acm, bool, 0);
MODULE_PARM_DESC(use_acm, "Use CDC ACM, default=yes");

अटल bool use_obex = false;
module_param(use_obex, bool, 0);
MODULE_PARM_DESC(use_obex, "Use CDC OBEX, default=no");

अटल अचिन्हित n_ports = 1;
module_param(n_ports, uपूर्णांक, 0);
MODULE_PARM_DESC(n_ports, "number of ports to create, default=1");

अटल bool enable = true;

अटल पूर्णांक चयन_gserial_enable(bool करो_enable);

अटल पूर्णांक enable_set(स्थिर अक्षर *s, स्थिर काष्ठा kernel_param *kp)
अणु
	bool करो_enable;
	पूर्णांक ret;

	अगर (!s)	/* called क्रम no-arg enable == शेष */
		वापस 0;

	ret = strtobool(s, &करो_enable);
	अगर (ret || enable == करो_enable)
		वापस ret;

	ret = चयन_gserial_enable(करो_enable);
	अगर (!ret)
		enable = करो_enable;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops enable_ops = अणु
	.set = enable_set,
	.get = param_get_bool,
पूर्ण;

module_param_cb(enable, &enable_ops, &enable, 0644);

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_configuration serial_config_driver = अणु
	/* .label = f(use_acm) */
	/* .bConfigurationValue = f(use_acm) */
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_serial[MAX_U_SERIAL_PORTS];
अटल काष्ठा usb_function *f_serial[MAX_U_SERIAL_PORTS];

अटल पूर्णांक serial_रेजिस्टर_ports(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_configuration *c, स्थिर अक्षर *f_name)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = usb_add_config_only(cdev, c);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < n_ports; i++) अणु

		fi_serial[i] = usb_get_function_instance(f_name);
		अगर (IS_ERR(fi_serial[i])) अणु
			ret = PTR_ERR(fi_serial[i]);
			जाओ fail;
		पूर्ण

		f_serial[i] = usb_get_function(fi_serial[i]);
		अगर (IS_ERR(f_serial[i])) अणु
			ret = PTR_ERR(f_serial[i]);
			जाओ err_get_func;
		पूर्ण

		ret = usb_add_function(c, f_serial[i]);
		अगर (ret)
			जाओ err_add_func;
	पूर्ण

	वापस 0;

err_add_func:
	usb_put_function(f_serial[i]);
err_get_func:
	usb_put_function_instance(fi_serial[i]);

fail:
	i--;
	जबतक (i >= 0) अणु
		usb_हटाओ_function(c, f_serial[i]);
		usb_put_function(f_serial[i]);
		usb_put_function_instance(fi_serial[i]);
		i--;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक gs_bind(काष्ठा usb_composite_dev *cdev)
अणु
	पूर्णांक			status;

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	status = strings_dev[STRING_DESCRIPTION_IDX].id;
	serial_config_driver.iConfiguration = status;

	अगर (gadget_is_otg(cdev->gadget)) अणु
		अगर (!otg_desc[0]) अणु
			काष्ठा usb_descriptor_header *usb_desc;

			usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
			अगर (!usb_desc) अणु
				status = -ENOMEM;
				जाओ fail;
			पूर्ण
			usb_otg_descriptor_init(cdev->gadget, usb_desc);
			otg_desc[0] = usb_desc;
			otg_desc[1] = शून्य;
		पूर्ण
		serial_config_driver.descriptors = otg_desc;
		serial_config_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	/* रेजिस्टर our configuration */
	अगर (use_acm) अणु
		status  = serial_रेजिस्टर_ports(cdev, &serial_config_driver,
				"acm");
		usb_ep_स्वतःconfig_reset(cdev->gadget);
	पूर्ण अन्यथा अगर (use_obex)
		status = serial_रेजिस्टर_ports(cdev, &serial_config_driver,
				"obex");
	अन्यथा अणु
		status = serial_रेजिस्टर_ports(cdev, &serial_config_driver,
				"gser");
	पूर्ण
	अगर (status < 0)
		जाओ fail1;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	INFO(cdev, "%s\n", GS_VERSION_NAME);

	वापस 0;
fail1:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail:
	वापस status;
पूर्ण

अटल पूर्णांक gs_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_ports; i++) अणु
		usb_put_function(f_serial[i]);
		usb_put_function_instance(fi_serial[i]);
	पूर्ण

	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver gserial_driver = अणु
	.name		= "g_serial",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= gs_bind,
	.unbind		= gs_unbind,
पूर्ण;

अटल पूर्णांक चयन_gserial_enable(bool करो_enable)
अणु
	अगर (!serial_config_driver.label)
		/* init() was not called, yet */
		वापस 0;

	अगर (करो_enable)
		वापस usb_composite_probe(&gserial_driver);

	usb_composite_unरेजिस्टर(&gserial_driver);
	वापस 0;
पूर्ण

अटल पूर्णांक __init init(व्योम)
अणु
	/* We *could* export two configs; that'd be much cleaner...
	 * but neither of these product IDs was defined that way.
	 */
	अगर (use_acm) अणु
		serial_config_driver.label = "CDC ACM config";
		serial_config_driver.bConfigurationValue = 2;
		device_desc.bDeviceClass = USB_CLASS_COMM;
		device_desc.idProduct =
				cpu_to_le16(GS_CDC_PRODUCT_ID);
	पूर्ण अन्यथा अगर (use_obex) अणु
		serial_config_driver.label = "CDC OBEX config";
		serial_config_driver.bConfigurationValue = 3;
		device_desc.bDeviceClass = USB_CLASS_COMM;
		device_desc.idProduct =
			cpu_to_le16(GS_CDC_OBEX_PRODUCT_ID);
	पूर्ण अन्यथा अणु
		serial_config_driver.label = "Generic Serial config";
		serial_config_driver.bConfigurationValue = 1;
		device_desc.bDeviceClass = USB_CLASS_VENDOR_SPEC;
		device_desc.idProduct =
				cpu_to_le16(GS_PRODUCT_ID);
	पूर्ण
	strings_dev[STRING_DESCRIPTION_IDX].s = serial_config_driver.label;

	अगर (!enable)
		वापस 0;

	वापस usb_composite_probe(&gserial_driver);
पूर्ण
module_init(init);

अटल व्योम __निकास cleanup(व्योम)
अणु
	अगर (enable)
		usb_composite_unरेजिस्टर(&gserial_driver);
पूर्ण
module_निकास(cleanup);
