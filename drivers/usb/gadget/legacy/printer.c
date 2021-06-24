<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * prपूर्णांकer.c -- Prपूर्णांकer gadget driver
 *
 * Copyright (C) 2003-2005 David Brownell
 * Copyright (C) 2006 Craig W. Nadler
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/g_prपूर्णांकer.h>

USB_GADGET_COMPOSITE_OPTIONS();

#घोषणा DRIVER_DESC		"Printer Gadget"
#घोषणा DRIVER_VERSION		"2015 FEB 17"

अटल स्थिर अक्षर लघुname [] = "printer";

#समावेश "u_printer.h"

/*-------------------------------------------------------------------------*/

/* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */

/* Thanks to NetChip Technologies क्रम करोnating this product ID.
 */
#घोषणा PRINTER_VENDOR_NUM	0x0525		/* NetChip */
#घोषणा PRINTER_PRODUCT_NUM	0xa4a8		/* Linux-USB Prपूर्णांकer Gadget */

/* Some प्रणालीs will want dअगरferent product identअगरiers published in the
 * device descriptor, either numbers or strings or both.  These string
 * parameters are in UTF-8 (superset of ASCII's 7 bit अक्षरacters).
 */

module_param_named(iSerialNum, coverग_लिखो.serial_number, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(iSerialNum, "1");

अटल अक्षर *iPNPstring;
module_param(iPNPstring, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(iPNPstring, "MFG:linux;MDL:g_printer;CLS:PRINTER;SN:1;");

/* Number of requests to allocate per endpoपूर्णांक, not used क्रम ep0. */
अटल अचिन्हित qlen = 10;
module_param(qlen, uपूर्णांक, S_IRUGO|S_IWUSR);

#घोषणा QLEN	qlen

अटल काष्ठा usb_function_instance *fi_prपूर्णांकer;
अटल काष्ठा usb_function *f_prपूर्णांकer;

/*-------------------------------------------------------------------------*/

/*
 * DESCRIPTORS ... most are अटल, but strings and (full) configuration
 * descriptors are built on demand.
 */

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	.idVenकरोr =		cpu_to_le16(PRINTER_VENDOR_NUM),
	.idProduct =		cpu_to_le16(PRINTER_PRODUCT_NUM),
	.bNumConfigurations =	1
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

/*-------------------------------------------------------------------------*/

/* descriptors that are built on-demand */

अटल अक्षर				product_desc [40] = DRIVER_DESC;
अटल अक्षर				serial_num [40] = "1";
अटल अक्षर				*pnp_string =
	"MFG:linux;MDL:g_printer;CLS:PRINTER;SN:1;";

/* अटल strings, in UTF-8 */
अटल काष्ठा usb_string		strings [] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = product_desc,
	[USB_GADGET_SERIAL_IDX].s =	serial_num,
	अणु  पूर्ण		/* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings	stringtab_dev = अणु
	.language	= 0x0409,	/* en-us */
	.strings	= strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *dev_strings[] = अणु
	&stringtab_dev,
	शून्य,
पूर्ण;

अटल काष्ठा usb_configuration prपूर्णांकer_cfg_driver = अणु
	.label			= "printer",
	.bConfigurationValue	= 1,
	.bmAttributes		= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

अटल पूर्णांक prपूर्णांकer_करो_config(काष्ठा usb_configuration *c)
अणु
	काष्ठा usb_gadget	*gadget = c->cdev->gadget;
	पूर्णांक			status = 0;

	usb_ep_स्वतःconfig_reset(gadget);

	usb_gadget_set_selfघातered(gadget);

	अगर (gadget_is_otg(gadget)) अणु
		prपूर्णांकer_cfg_driver.descriptors = otg_desc;
		prपूर्णांकer_cfg_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	f_prपूर्णांकer = usb_get_function(fi_prपूर्णांकer);
	अगर (IS_ERR(f_prपूर्णांकer))
		वापस PTR_ERR(f_prपूर्णांकer);

	status = usb_add_function(c, f_prपूर्णांकer);
	अगर (status < 0)
		usb_put_function(f_prपूर्णांकer);

	वापस status;
पूर्ण

अटल पूर्णांक prपूर्णांकer_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts;
	पूर्णांक ret;

	fi_prपूर्णांकer = usb_get_function_instance("printer");
	अगर (IS_ERR(fi_prपूर्णांकer))
		वापस PTR_ERR(fi_prपूर्णांकer);

	opts = container_of(fi_prपूर्णांकer, काष्ठा f_prपूर्णांकer_opts, func_inst);
	opts->minor = 0;
	opts->q_len = QLEN;
	अगर (iPNPstring) अणु
		opts->pnp_string = kstrdup(iPNPstring, GFP_KERNEL);
		अगर (!opts->pnp_string) अणु
			ret = -ENOMEM;
			जाओ fail_put_func_inst;
		पूर्ण
		opts->pnp_string_allocated = true;
		/*
		 * we करोn't मुक्त this memory in हाल of error
		 * as prपूर्णांकer cleanup func will करो this क्रम us
		 */
	पूर्ण अन्यथा अणु
		opts->pnp_string = pnp_string;
	पूर्ण

	ret = usb_string_ids_tab(cdev, strings);
	अगर (ret < 0)
		जाओ fail_put_func_inst;

	device_desc.iManufacturer = strings[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings[USB_GADGET_PRODUCT_IDX].id;
	device_desc.iSerialNumber = strings[USB_GADGET_SERIAL_IDX].id;

	अगर (gadget_is_otg(cdev->gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
		अगर (!usb_desc) अणु
			ret = -ENOMEM;
			जाओ fail_put_func_inst;
		पूर्ण
		usb_otg_descriptor_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	ret = usb_add_config(cdev, &prपूर्णांकer_cfg_driver, prपूर्णांकer_करो_config);
	अगर (ret)
		जाओ fail_मुक्त_otg_desc;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	वापस ret;

fail_मुक्त_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail_put_func_inst:
	usb_put_function_instance(fi_prपूर्णांकer);
	वापस ret;
पूर्ण

अटल पूर्णांक prपूर्णांकer_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	usb_put_function(f_prपूर्णांकer);
	usb_put_function_instance(fi_prपूर्णांकer);

	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver prपूर्णांकer_driver = अणु
	.name           = लघुname,
	.dev            = &device_desc,
	.strings        = dev_strings,
	.max_speed      = USB_SPEED_SUPER,
	.bind		= prपूर्णांकer_bind,
	.unbind		= prपूर्णांकer_unbind,
पूर्ण;

module_usb_composite_driver(prपूर्णांकer_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Craig Nadler");
MODULE_LICENSE("GPL");
