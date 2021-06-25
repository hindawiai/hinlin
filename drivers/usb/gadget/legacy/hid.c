<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * hid.c -- HID Composite driver
 *
 * Based on multi.c
 *
 * Copyright (C) 2010 Fabien Chouteau <fabien.chouteau@barco.com>
 */


#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/g_hid.h>

#घोषणा DRIVER_DESC		"HID Gadget"
#घोषणा DRIVER_VERSION		"2010/03/16"

#समावेश "u_hid.h"

/*-------------------------------------------------------------------------*/

#घोषणा HIDG_VENDOR_NUM		0x0525	/* XXX NetChip */
#घोषणा HIDG_PRODUCT_NUM	0xa4ac	/* Linux-USB HID gadget */

/*-------------------------------------------------------------------------*/

काष्ठा hidg_func_node अणु
	काष्ठा usb_function_instance *fi;
	काष्ठा usb_function *f;
	काष्ठा list_head node;
	काष्ठा hidg_func_descriptor *func;
पूर्ण;

अटल LIST_HEAD(hidg_func_list);

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	/* .bDeviceClass =		USB_CLASS_COMM, */
	/* .bDeviceSubClass =	0, */
	/* .bDeviceProtocol =	0, */
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	/* .bMaxPacketSize0 = f(hardware) */

	/* Venकरोr and product id can be overridden by module parameters.  */
	.idVenकरोr =		cpu_to_le16(HIDG_VENDOR_NUM),
	.idProduct =		cpu_to_le16(HIDG_PRODUCT_NUM),
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



/****************************** Configurations ******************************/

अटल पूर्णांक करो_config(काष्ठा usb_configuration *c)
अणु
	काष्ठा hidg_func_node *e, *n;
	पूर्णांक status = 0;

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

	list_क्रम_each_entry(e, &hidg_func_list, node) अणु
		e->f = usb_get_function(e->fi);
		अगर (IS_ERR(e->f))
			जाओ put;
		status = usb_add_function(c, e->f);
		अगर (status < 0) अणु
			usb_put_function(e->f);
			जाओ put;
		पूर्ण
	पूर्ण

	वापस 0;
put:
	list_क्रम_each_entry(n, &hidg_func_list, node) अणु
		अगर (n == e)
			अवरोध;
		usb_हटाओ_function(c, n->f);
		usb_put_function(n->f);
	पूर्ण
	वापस status;
पूर्ण

अटल काष्ठा usb_configuration config_driver = अणु
	.label			= "HID Gadget",
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/****************************** Gadget Bind ******************************/

अटल पूर्णांक hid_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा list_head *पंचांगp;
	काष्ठा hidg_func_node *n, *m;
	काष्ठा f_hid_opts *hid_opts;
	पूर्णांक status, funcs = 0;

	list_क्रम_each(पंचांगp, &hidg_func_list)
		funcs++;

	अगर (!funcs)
		वापस -ENODEV;

	list_क्रम_each_entry(n, &hidg_func_list, node) अणु
		n->fi = usb_get_function_instance("hid");
		अगर (IS_ERR(n->fi)) अणु
			status = PTR_ERR(n->fi);
			जाओ put;
		पूर्ण
		hid_opts = container_of(n->fi, काष्ठा f_hid_opts, func_inst);
		hid_opts->subclass = n->func->subclass;
		hid_opts->protocol = n->func->protocol;
		hid_opts->report_length = n->func->report_length;
		hid_opts->report_desc_length = n->func->report_desc_length;
		hid_opts->report_desc = n->func->report_desc;
	पूर्ण


	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ put;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(gadget);
		अगर (!usb_desc)
			जाओ put;
		usb_otg_descriptor_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	/* रेजिस्टर our configuration */
	status = usb_add_config(cdev, &config_driver, करो_config);
	अगर (status < 0)
		जाओ मुक्त_otg_desc;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	dev_info(&gadget->dev, DRIVER_DESC ", version: " DRIVER_VERSION "\n");

	वापस 0;

मुक्त_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
put:
	list_क्रम_each_entry(m, &hidg_func_list, node) अणु
		अगर (m == n)
			अवरोध;
		usb_put_function_instance(m->fi);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक hid_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा hidg_func_node *n;

	list_क्रम_each_entry(n, &hidg_func_list, node) अणु
		usb_put_function(n->f);
		usb_put_function_instance(n->fi);
	पूर्ण

	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक hidg_plat_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidg_func_descriptor *func = dev_get_platdata(&pdev->dev);
	काष्ठा hidg_func_node *entry;

	अगर (!func) अणु
		dev_err(&pdev->dev, "Platform data missing\n");
		वापस -ENODEV;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->func = func;
	list_add_tail(&entry->node, &hidg_func_list);

	वापस 0;
पूर्ण

अटल पूर्णांक hidg_plat_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidg_func_node *e, *n;

	list_क्रम_each_entry_safe(e, n, &hidg_func_list, node) अणु
		list_del(&e->node);
		kमुक्त(e);
	पूर्ण

	वापस 0;
पूर्ण


/****************************** Some noise ******************************/


अटल काष्ठा usb_composite_driver hidg_driver = अणु
	.name		= "g_hid",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= hid_bind,
	.unbind		= hid_unbind,
पूर्ण;

अटल काष्ठा platक्रमm_driver hidg_plat_driver = अणु
	.हटाओ		= hidg_plat_driver_हटाओ,
	.driver		= अणु
		.name	= "hidg",
	पूर्ण,
पूर्ण;


MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Fabien Chouteau, Peter Korsgaard");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init hidg_init(व्योम)
अणु
	पूर्णांक status;

	status = platक्रमm_driver_probe(&hidg_plat_driver,
				hidg_plat_driver_probe);
	अगर (status < 0)
		वापस status;

	status = usb_composite_probe(&hidg_driver);
	अगर (status < 0)
		platक्रमm_driver_unरेजिस्टर(&hidg_plat_driver);

	वापस status;
पूर्ण
module_init(hidg_init);

अटल व्योम __निकास hidg_cleanup(व्योम)
अणु
	usb_composite_unरेजिस्टर(&hidg_driver);
	platक्रमm_driver_unरेजिस्टर(&hidg_plat_driver);
पूर्ण
module_निकास(hidg_cleanup);
