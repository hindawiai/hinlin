<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_obex.c -- USB CDC OBEX function driver
 *
 * Copyright (C) 2008 Nokia Corporation
 * Contact: Felipe Balbi <felipe.balbi@nokia.com>
 *
 * Based on f_acm.c by Al Borchers and David Brownell.
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश "u_serial.h"


/*
 * This CDC OBEX function support just packages a TTY-ish byte stream.
 * A user mode server will put it पूर्णांकo "raw" mode and handle all the
 * relevant protocol details ... this is just a kernel passthrough.
 * When possible, we prevent gadget क्रमागतeration until that server is
 * पढ़ोy to handle the commands.
 */

काष्ठा f_obex अणु
	काष्ठा gserial			port;
	u8				ctrl_id;
	u8				data_id;
	u8				cur_alt;
	u8				port_num;
पूर्ण;

अटल अंतरभूत काष्ठा f_obex *func_to_obex(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_obex, port.func);
पूर्ण

अटल अंतरभूत काष्ठा f_obex *port_to_obex(काष्ठा gserial *p)
अणु
	वापस container_of(p, काष्ठा f_obex, port);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा OBEX_CTRL_IDX	0
#घोषणा OBEX_DATA_IDX	1

अटल काष्ठा usb_string obex_string_defs[] = अणु
	[OBEX_CTRL_IDX].s	= "CDC Object Exchange (OBEX)",
	[OBEX_DATA_IDX].s	= "CDC OBEX Data",
	अणु  पूर्ण,	/* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings obex_string_table = अणु
	.language		= 0x0409,	/* en-US */
	.strings		= obex_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *obex_strings[] = अणु
	&obex_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_पूर्णांकerface_descriptor obex_control_पूर्णांकf = अणु
	.bLength		= माप(obex_control_पूर्णांकf),
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= 0,

	.bAlternateSetting	= 0,
	.bNumEndpoपूर्णांकs		= 0,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_OBEX,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor obex_data_nop_पूर्णांकf = अणु
	.bLength		= माप(obex_data_nop_पूर्णांकf),
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= 1,

	.bAlternateSetting	= 0,
	.bNumEndpoपूर्णांकs		= 0,
	.bInterfaceClass	= USB_CLASS_CDC_DATA,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor obex_data_पूर्णांकf = अणु
	.bLength		= माप(obex_data_पूर्णांकf),
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= 2,

	.bAlternateSetting	= 1,
	.bNumEndpoपूर्णांकs		= 2,
	.bInterfaceClass	= USB_CLASS_CDC_DATA,
पूर्ण;

अटल काष्ठा usb_cdc_header_desc obex_cdc_header_desc = अणु
	.bLength		= माप(obex_cdc_header_desc),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= USB_CDC_HEADER_TYPE,
	.bcdCDC			= cpu_to_le16(0x0120),
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc obex_cdc_जोड़_desc = अणु
	.bLength		= माप(obex_cdc_जोड़_desc),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= USB_CDC_UNION_TYPE,
	.bMasterInterface0	= 1,
	.bSlaveInterface0	= 2,
पूर्ण;

अटल काष्ठा usb_cdc_obex_desc obex_desc = अणु
	.bLength		= माप(obex_desc),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= USB_CDC_OBEX_TYPE,
	.bcdVersion		= cpu_to_le16(0x0100),
पूर्ण;

/* High-Speed Support */

अटल काष्ठा usb_endpoपूर्णांक_descriptor obex_hs_ep_out_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize		= cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor obex_hs_ep_in_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize		= cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &obex_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_cdc_header_desc,
	(काष्ठा usb_descriptor_header *) &obex_desc,
	(काष्ठा usb_descriptor_header *) &obex_cdc_जोड़_desc,

	(काष्ठा usb_descriptor_header *) &obex_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_hs_ep_in_desc,
	(काष्ठा usb_descriptor_header *) &obex_hs_ep_out_desc,
	शून्य,
पूर्ण;

/* Full-Speed Support */

अटल काष्ठा usb_endpoपूर्णांक_descriptor obex_fs_ep_in_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor obex_fs_ep_out_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &obex_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_cdc_header_desc,
	(काष्ठा usb_descriptor_header *) &obex_desc,
	(काष्ठा usb_descriptor_header *) &obex_cdc_जोड़_desc,

	(काष्ठा usb_descriptor_header *) &obex_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &obex_fs_ep_in_desc,
	(काष्ठा usb_descriptor_header *) &obex_fs_ep_out_desc,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक obex_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_obex		*obex = func_to_obex(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	अगर (पूर्णांकf == obex->ctrl_id) अणु
		अगर (alt != 0)
			जाओ fail;
		/* NOP */
		dev_dbg(&cdev->gadget->dev,
			"reset obex ttyGS%d control\n", obex->port_num);

	पूर्ण अन्यथा अगर (पूर्णांकf == obex->data_id) अणु
		अगर (alt > 1)
			जाओ fail;

		अगर (obex->port.in->enabled) अणु
			dev_dbg(&cdev->gadget->dev,
				"reset obex ttyGS%d\n", obex->port_num);
			gserial_disconnect(&obex->port);
		पूर्ण

		अगर (!obex->port.in->desc || !obex->port.out->desc) अणु
			dev_dbg(&cdev->gadget->dev,
				"init obex ttyGS%d\n", obex->port_num);
			अगर (config_ep_by_speed(cdev->gadget, f,
					       obex->port.in) ||
			    config_ep_by_speed(cdev->gadget, f,
					       obex->port.out)) अणु
				obex->port.out->desc = शून्य;
				obex->port.in->desc = शून्य;
				जाओ fail;
			पूर्ण
		पूर्ण

		अगर (alt == 1) अणु
			dev_dbg(&cdev->gadget->dev,
				"activate obex ttyGS%d\n", obex->port_num);
			gserial_connect(&obex->port, obex->port_num);
		पूर्ण

	पूर्ण अन्यथा
		जाओ fail;

	obex->cur_alt = alt;

	वापस 0;

fail:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक obex_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_obex		*obex = func_to_obex(f);

	वापस obex->cur_alt;
पूर्ण

अटल व्योम obex_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_obex	*obex = func_to_obex(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev, "obex ttyGS%d disable\n", obex->port_num);
	gserial_disconnect(&obex->port);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम obex_connect(काष्ठा gserial *g)
अणु
	काष्ठा f_obex		*obex = port_to_obex(g);
	काष्ठा usb_composite_dev *cdev = g->func.config->cdev;
	पूर्णांक			status;

	status = usb_function_activate(&g->func);
	अगर (status)
		dev_dbg(&cdev->gadget->dev,
			"obex ttyGS%d function activate --> %d\n",
			obex->port_num, status);
पूर्ण

अटल व्योम obex_disconnect(काष्ठा gserial *g)
अणु
	काष्ठा f_obex		*obex = port_to_obex(g);
	काष्ठा usb_composite_dev *cdev = g->func.config->cdev;
	पूर्णांक			status;

	status = usb_function_deactivate(&g->func);
	अगर (status)
		dev_dbg(&cdev->gadget->dev,
			"obex ttyGS%d function deactivate --> %d\n",
			obex->port_num, status);
पूर्ण

/*-------------------------------------------------------------------------*/

/* Some controllers can't support CDC OBEX ... */
अटल अंतरभूत bool can_support_obex(काष्ठा usb_configuration *c)
अणु
	/* Since the first पूर्णांकerface is a NOP, we can ignore the
	 * issue of multi-पूर्णांकerface support on most controllers.
	 *
	 * Altsettings are mandatory, however...
	 */
	अगर (!gadget_is_altset_supported(c->cdev->gadget))
		वापस false;

	/* everything अन्यथा is *probably* fine ... */
	वापस true;
पूर्ण

अटल पूर्णांक obex_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_obex		*obex = func_to_obex(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	अगर (!can_support_obex(c))
		वापस -EINVAL;

	us = usb_gstrings_attach(cdev, obex_strings,
				 ARRAY_SIZE(obex_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	obex_control_पूर्णांकf.iInterface = us[OBEX_CTRL_IDX].id;
	obex_data_nop_पूर्णांकf.iInterface = us[OBEX_DATA_IDX].id;
	obex_data_पूर्णांकf.iInterface = us[OBEX_DATA_IDX].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs, and patch descriptors */

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	obex->ctrl_id = status;

	obex_control_पूर्णांकf.bInterfaceNumber = status;
	obex_cdc_जोड़_desc.bMasterInterface0 = status;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	obex->data_id = status;

	obex_data_nop_पूर्णांकf.bInterfaceNumber = status;
	obex_data_पूर्णांकf.bInterfaceNumber = status;
	obex_cdc_जोड़_desc.bSlaveInterface0 = status;

	/* allocate instance-specअगरic endpoपूर्णांकs */

	status = -ENODEV;
	ep = usb_ep_स्वतःconfig(cdev->gadget, &obex_fs_ep_in_desc);
	अगर (!ep)
		जाओ fail;
	obex->port.in = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &obex_fs_ep_out_desc);
	अगर (!ep)
		जाओ fail;
	obex->port.out = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */

	obex_hs_ep_in_desc.bEndpoपूर्णांकAddress =
		obex_fs_ep_in_desc.bEndpoपूर्णांकAddress;
	obex_hs_ep_out_desc.bEndpoपूर्णांकAddress =
		obex_fs_ep_out_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, fs_function, hs_function, शून्य,
					शून्य);
	अगर (status)
		जाओ fail;

	dev_dbg(&cdev->gadget->dev, "obex ttyGS%d: %s speed IN/%s OUT/%s\n",
		obex->port_num,
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		obex->port.in->name, obex->port.out->name);

	वापस 0;

fail:
	ERROR(cdev, "%s/%p: can't bind, err %d\n", f->name, f, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_serial_opts *to_f_serial_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_serial_opts,
			    func_inst.group);
पूर्ण

अटल व्योम obex_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_serial_opts *opts = to_f_serial_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations obex_item_ops = अणु
	.release	= obex_attr_release,
पूर्ण;

अटल sमाप_प्रकार f_obex_port_num_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_f_serial_opts(item)->port_num);
पूर्ण

CONFIGFS_ATTR_RO(f_obex_, port_num);

अटल काष्ठा configfs_attribute *acm_attrs[] = अणु
	&f_obex_attr_port_num,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type obex_func_type = अणु
	.ct_item_ops	= &obex_item_ops,
	.ct_attrs	= acm_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम obex_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_serial_opts *opts;

	opts = container_of(f, काष्ठा f_serial_opts, func_inst);
	gserial_मुक्त_line(opts->port_num);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *obex_alloc_inst(व्योम)
अणु
	काष्ठा f_serial_opts *opts;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	opts->func_inst.मुक्त_func_inst = obex_मुक्त_inst;
	ret = gserial_alloc_line_no_console(&opts->port_num);
	अगर (ret) अणु
		kमुक्त(opts);
		वापस ERR_PTR(ret);
	पूर्ण
	config_group_init_type_name(&opts->func_inst.group, "",
				    &obex_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम obex_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_obex *obex;

	obex = func_to_obex(f);
	kमुक्त(obex);
पूर्ण

अटल व्योम obex_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *obex_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_obex	*obex;
	काष्ठा f_serial_opts *opts;

	/* allocate and initialize one new instance */
	obex = kzalloc(माप(*obex), GFP_KERNEL);
	अगर (!obex)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_serial_opts, func_inst);

	obex->port_num = opts->port_num;

	obex->port.connect = obex_connect;
	obex->port.disconnect = obex_disconnect;

	obex->port.func.name = "obex";
	/* descriptors are per-instance copies */
	obex->port.func.bind = obex_bind;
	obex->port.func.unbind = obex_unbind;
	obex->port.func.set_alt = obex_set_alt;
	obex->port.func.get_alt = obex_get_alt;
	obex->port.func.disable = obex_disable;
	obex->port.func.मुक्त_func = obex_मुक्त;
	obex->port.func.bind_deactivated = true;

	वापस &obex->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(obex, obex_alloc_inst, obex_alloc);
MODULE_AUTHOR("Felipe Balbi");
MODULE_LICENSE("GPL");
