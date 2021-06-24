<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_serial.c - generic USB serial function driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>

#समावेश "u_serial.h"


/*
 * This function packages a simple "generic serial" port with no real
 * control mechanisms, just raw data transfer over two bulk endpoपूर्णांकs.
 *
 * Because it's not standardized, this isn't as पूर्णांकeroperable as the
 * CDC ACM driver.  However, क्रम many purposes it's just as functional
 * अगर you can arrange appropriate host side drivers.
 */

काष्ठा f_gser अणु
	काष्ठा gserial			port;
	u8				data_id;
	u8				port_num;
पूर्ण;

अटल अंतरभूत काष्ठा f_gser *func_to_gser(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_gser, port.func);
पूर्ण

/*-------------------------------------------------------------------------*/

/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_descriptor gser_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_fs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_fs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *gser_fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &gser_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &gser_fs_in_desc,
	(काष्ठा usb_descriptor_header *) &gser_fs_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_hs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_hs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *gser_hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &gser_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &gser_hs_in_desc,
	(काष्ठा usb_descriptor_header *) &gser_hs_out_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_ss_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor gser_ss_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor gser_ss_bulk_comp_desc = अणु
	.bLength =              माप gser_ss_bulk_comp_desc,
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_descriptor_header *gser_ss_function[] = अणु
	(काष्ठा usb_descriptor_header *) &gser_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &gser_ss_in_desc,
	(काष्ठा usb_descriptor_header *) &gser_ss_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &gser_ss_out_desc,
	(काष्ठा usb_descriptor_header *) &gser_ss_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

अटल काष्ठा usb_string gser_string_defs[] = अणु
	[0].s = "Generic Serial",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings gser_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		gser_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *gser_strings[] = अणु
	&gser_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक gser_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_gser		*gser = func_to_gser(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* we know alt == 0, so this is an activation or a reset */

	अगर (gser->port.in->enabled) अणु
		dev_dbg(&cdev->gadget->dev,
			"reset generic ttyGS%d\n", gser->port_num);
		gserial_disconnect(&gser->port);
	पूर्ण
	अगर (!gser->port.in->desc || !gser->port.out->desc) अणु
		dev_dbg(&cdev->gadget->dev,
			"activate generic ttyGS%d\n", gser->port_num);
		अगर (config_ep_by_speed(cdev->gadget, f, gser->port.in) ||
		    config_ep_by_speed(cdev->gadget, f, gser->port.out)) अणु
			gser->port.in->desc = शून्य;
			gser->port.out->desc = शून्य;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	gserial_connect(&gser->port, gser->port_num);
	वापस 0;
पूर्ण

अटल व्योम gser_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_gser	*gser = func_to_gser(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev,
		"generic ttyGS%d deactivated\n", gser->port_num);
	gserial_disconnect(&gser->port);
पूर्ण

/*-------------------------------------------------------------------------*/

/* serial function driver setup/binding */

अटल पूर्णांक gser_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_gser		*gser = func_to_gser(f);
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	/* REVISIT might want instance-specअगरic strings to help
	 * distinguish instances ...
	 */

	/* maybe allocate device-global string ID */
	अगर (gser_string_defs[0].id == 0) अणु
		status = usb_string_id(c->cdev);
		अगर (status < 0)
			वापस status;
		gser_string_defs[0].id = status;
	पूर्ण

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	gser->data_id = status;
	gser_पूर्णांकerface_desc.bInterfaceNumber = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &gser_fs_in_desc);
	अगर (!ep)
		जाओ fail;
	gser->port.in = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &gser_fs_out_desc);
	अगर (!ep)
		जाओ fail;
	gser->port.out = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	gser_hs_in_desc.bEndpoपूर्णांकAddress = gser_fs_in_desc.bEndpoपूर्णांकAddress;
	gser_hs_out_desc.bEndpoपूर्णांकAddress = gser_fs_out_desc.bEndpoपूर्णांकAddress;

	gser_ss_in_desc.bEndpoपूर्णांकAddress = gser_fs_in_desc.bEndpoपूर्णांकAddress;
	gser_ss_out_desc.bEndpoपूर्णांकAddress = gser_fs_out_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, gser_fs_function, gser_hs_function,
			gser_ss_function, gser_ss_function);
	अगर (status)
		जाओ fail;
	dev_dbg(&cdev->gadget->dev, "generic ttyGS%d: %s speed IN/%s OUT/%s\n",
		gser->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		gser->port.in->name, gser->port.out->name);
	वापस 0;

fail:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_serial_opts *to_f_serial_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_serial_opts,
			    func_inst.group);
पूर्ण

अटल व्योम serial_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_serial_opts *opts = to_f_serial_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations serial_item_ops = अणु
	.release	= serial_attr_release,
पूर्ण;

#अगर_घोषित CONFIG_U_SERIAL_CONSOLE

अटल sमाप_प्रकार f_serial_console_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस gserial_set_console(to_f_serial_opts(item)->port_num,
				   page, count);
पूर्ण

अटल sमाप_प्रकार f_serial_console_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस gserial_get_console(to_f_serial_opts(item)->port_num, page);
पूर्ण

CONFIGFS_ATTR(f_serial_, console);

#पूर्ण_अगर /* CONFIG_U_SERIAL_CONSOLE */

अटल sमाप_प्रकार f_serial_port_num_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_f_serial_opts(item)->port_num);
पूर्ण

CONFIGFS_ATTR_RO(f_serial_, port_num);

अटल काष्ठा configfs_attribute *acm_attrs[] = अणु
#अगर_घोषित CONFIG_U_SERIAL_CONSOLE
	&f_serial_attr_console,
#पूर्ण_अगर
	&f_serial_attr_port_num,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type serial_func_type = अणु
	.ct_item_ops	= &serial_item_ops,
	.ct_attrs	= acm_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम gser_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_serial_opts *opts;

	opts = container_of(f, काष्ठा f_serial_opts, func_inst);
	gserial_मुक्त_line(opts->port_num);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *gser_alloc_inst(व्योम)
अणु
	काष्ठा f_serial_opts *opts;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	opts->func_inst.मुक्त_func_inst = gser_मुक्त_inst;
	ret = gserial_alloc_line(&opts->port_num);
	अगर (ret) अणु
		kमुक्त(opts);
		वापस ERR_PTR(ret);
	पूर्ण
	config_group_init_type_name(&opts->func_inst.group, "",
				    &serial_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम gser_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_gser *serial;

	serial = func_to_gser(f);
	kमुक्त(serial);
पूर्ण

अटल व्योम gser_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल व्योम gser_resume(काष्ठा usb_function *f)
अणु
	काष्ठा f_gser *gser = func_to_gser(f);

	gserial_resume(&gser->port);
पूर्ण

अटल व्योम gser_suspend(काष्ठा usb_function *f)
अणु
	काष्ठा f_gser *gser = func_to_gser(f);

	gserial_suspend(&gser->port);
पूर्ण

अटल काष्ठा usb_function *gser_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_gser	*gser;
	काष्ठा f_serial_opts *opts;

	/* allocate and initialize one new instance */
	gser = kzalloc(माप(*gser), GFP_KERNEL);
	अगर (!gser)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_serial_opts, func_inst);

	gser->port_num = opts->port_num;

	gser->port.func.name = "gser";
	gser->port.func.strings = gser_strings;
	gser->port.func.bind = gser_bind;
	gser->port.func.unbind = gser_unbind;
	gser->port.func.set_alt = gser_set_alt;
	gser->port.func.disable = gser_disable;
	gser->port.func.मुक्त_func = gser_मुक्त;
	gser->port.func.resume = gser_resume;
	gser->port.func.suspend = gser_suspend;

	वापस &gser->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(gser, gser_alloc_inst, gser_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Al Borchers");
MODULE_AUTHOR("David Brownell");
