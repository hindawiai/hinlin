<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Wishbone-Serial adapter driver
 *
 * Copyright (C) 2013 Wesley W. Terpstra <w.terpstra@gsi.de>
 * Copyright (C) 2013 GSI Helmholtz Centre क्रम Heavy Ion Research GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>

#घोषणा GSI_VENDOR_OPENCLOSE 0xB0

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1D50, 0x6062, 0xFF, 0xFF, 0xFF) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/*
 * Etherbone must be told that a new stream has begun beक्रमe data arrives.
 * This is necessary to restart the negotiation of Wishbone bus parameters.
 * Similarly, when the stream ends, Etherbone must be told so that the cycle
 * line can be driven low in the हाल that userspace failed to करो so.
 */
अटल पूर्णांक usb_gsi_खोलोबंद(काष्ठा usb_serial_port *port, पूर्णांक value)
अणु
	काष्ठा usb_device *dev = port->serial->dev;

	वापस usb_control_msg(
		dev,
		usb_sndctrlpipe(dev, 0), /* Send to EP0OUT */
		GSI_VENDOR_OPENCLOSE,
		USB_सूची_OUT|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
		value, /* wValue = device is खोलो(1) or बंदd(0) */
		port->serial->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber,
		शून्य, 0,  /* There is no data stage */
		5000); /* Timeout till operation fails */
पूर्ण

अटल पूर्णांक wishbone_serial_खोलो(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port)
अणु
	पूर्णांक retval;

	retval = usb_gsi_खोलोबंद(port, 1);
	अगर (retval) अणु
		dev_err(&port->serial->dev->dev,
		       "Could not mark device as open (%d)\n",
		       retval);
		वापस retval;
	पूर्ण

	retval = usb_serial_generic_खोलो(tty, port);
	अगर (retval)
		usb_gsi_खोलोबंद(port, 0);

	वापस retval;
पूर्ण

अटल व्योम wishbone_serial_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_serial_generic_बंद(port);
	usb_gsi_खोलोबंद(port, 0);
पूर्ण

अटल काष्ठा usb_serial_driver wishbone_serial_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"wishbone_serial",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.खोलो =			&wishbone_serial_खोलो,
	.बंद =		&wishbone_serial_बंद,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&wishbone_serial_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR("Wesley W. Terpstra <w.terpstra@gsi.de>");
MODULE_DESCRIPTION("USB Wishbone-Serial adapter");
MODULE_LICENSE("GPL");
