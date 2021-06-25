<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * gmidi.c -- USB MIDI Gadget Driver
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed क्रम Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * This code is based in part on:
 *
 * Gadget Zero driver, Copyright (C) 2003-2004 David Brownell.
 * USB Audio driver, Copyright (C) 2002 by Takashi Iwai.
 * USB MIDI driver, Copyright (C) 2002-2005 Clemens Ladisch.
 *
 * Refer to the USB Device Class Definition क्रम MIDI Devices:
 * http://www.usb.org/developers/devclass_करोcs/midi10.pdf
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <sound/initval.h>

#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>

#समावेश "u_midi.h"

/*-------------------------------------------------------------------------*/

MODULE_AUTHOR("Ben Williamson");
MODULE_LICENSE("GPL v2");

अटल स्थिर अक्षर दीर्घname[] = "MIDI Gadget";

USB_GADGET_COMPOSITE_OPTIONS();

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;
module_param(index, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(index, "Index value for the USB MIDI Gadget adapter.");

अटल अक्षर *id = SNDRV_DEFAULT_STR1;
module_param(id, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(id, "ID string for the USB MIDI Gadget adapter.");

अटल अचिन्हित पूर्णांक buflen = 512;
module_param(buflen, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(buflen, "MIDI buffer length");

अटल अचिन्हित पूर्णांक qlen = 32;
module_param(qlen, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(qlen, "USB read and write request queue length");

अटल अचिन्हित पूर्णांक in_ports = 1;
module_param(in_ports, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(in_ports, "Number of MIDI input ports");

अटल अचिन्हित पूर्णांक out_ports = 1;
module_param(out_ports, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(out_ports, "Number of MIDI output ports");

/* Thanks to Grey Innovation क्रम करोnating this product ID.
 *
 * DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#घोषणा DRIVER_VENDOR_NUM	0x17b3		/* Grey Innovation */
#घोषणा DRIVER_PRODUCT_NUM	0x0004		/* Linux-USB "MIDI Gadget" */

/* string IDs are asचिन्हित dynamically */

#घोषणा STRING_DESCRIPTION_IDX		USB_GADGET_FIRST_AVAIL_IDX

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		USB_DT_DEVICE_SIZE,
	.bDescriptorType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.idVenकरोr =		cpu_to_le16(DRIVER_VENDOR_NUM),
	.idProduct =		cpu_to_le16(DRIVER_PRODUCT_NUM),
	/* .iManufacturer =	DYNAMIC */
	/* .iProduct =		DYNAMIC */
	.bNumConfigurations =	1,
पूर्ण;

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s	= "Grey Innovation",
	[USB_GADGET_PRODUCT_IDX].s	= "MIDI Gadget",
	[USB_GADGET_SERIAL_IDX].s	= "",
	[STRING_DESCRIPTION_IDX].s	= "MIDI",
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

अटल काष्ठा usb_function_instance *fi_midi;
अटल काष्ठा usb_function *f_midi;

अटल पूर्णांक midi_unbind(काष्ठा usb_composite_dev *dev)
अणु
	usb_put_function(f_midi);
	usb_put_function_instance(fi_midi);
	वापस 0;
पूर्ण

अटल काष्ठा usb_configuration midi_config = अणु
	.label		= "MIDI Gadget",
	.bConfigurationValue = 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_ONE,
	.MaxPower	= CONFIG_USB_GADGET_VBUS_DRAW,
पूर्ण;

अटल पूर्णांक midi_bind_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status;

	f_midi = usb_get_function(fi_midi);
	अगर (IS_ERR(f_midi))
		वापस PTR_ERR(f_midi);

	status = usb_add_function(c, f_midi);
	अगर (status < 0) अणु
		usb_put_function(f_midi);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midi_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा f_midi_opts *midi_opts;
	पूर्णांक status;

	fi_midi = usb_get_function_instance("midi");
	अगर (IS_ERR(fi_midi))
		वापस PTR_ERR(fi_midi);

	midi_opts = container_of(fi_midi, काष्ठा f_midi_opts, func_inst);
	midi_opts->index = index;
	midi_opts->id = id;
	midi_opts->in_ports = in_ports;
	midi_opts->out_ports = out_ports;
	midi_opts->buflen = buflen;
	midi_opts->qlen = qlen;

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ put;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	midi_config.iConfiguration = strings_dev[STRING_DESCRIPTION_IDX].id;

	status = usb_add_config(cdev, &midi_config, midi_bind_config);
	अगर (status < 0)
		जाओ put;
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	pr_info("%s\n", दीर्घname);
	वापस 0;
put:
	usb_put_function_instance(fi_midi);
	वापस status;
पूर्ण

अटल काष्ठा usb_composite_driver midi_driver = अणु
	.name		= दीर्घname,
	.dev		= &device_desc,
	.strings	= dev_strings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= midi_bind,
	.unbind		= midi_unbind,
पूर्ण;

module_usb_composite_driver(midi_driver);
