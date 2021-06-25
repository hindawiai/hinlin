<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AIRcable USB Bluetooth Dongle Driver.
 *
 * Copyright (C) 2010 Johan Hovold <jhovold@gmail.com>
 * Copyright (C) 2006 Manuel Francisco Naranjo (naranjo.manuel@gmail.com)
 *
 * The device works as an standard CDC device, it has 2 पूर्णांकerfaces, the first
 * one is क्रम firmware access and the second is the serial one.
 * The protocol is very simply, there are two possibilities पढ़ोing or writing.
 * When writing the first urb must have a Header that starts with 0x20 0x29 the
 * next two bytes must say how much data will be sent.
 * When पढ़ोing the process is almost equal except that the header starts with
 * 0x00 0x20.
 *
 * The device simply need some stuff to understand data coming from the usb
 * buffer: The First and Second byte is used क्रम a Header, the Third and Fourth
 * tells the  device the amount of inक्रमmation the package holds.
 * Packages are 60 bytes दीर्घ Header Stuff.
 * When writing to the device the first two bytes of the header are 0x20 0x29
 * When पढ़ोing the bytes are 0x00 0x20, or 0x00 0x10, there is an strange
 * situation, when too much data arrives to the device because it sends the data
 * but with out the header. I will use a simply hack to override this situation,
 * अगर there is data coming that करोes not contain any header, then that is data
 * that must go directly to the tty, as there is no करोcumentation about अगर there
 * is any other control code, I will simply check क्रम the first
 * one.
 *
 * I have taken some info from a Greg Kroah-Harपंचांगan article:
 * http://www.linuxjournal.com/article/6573
 * And from Linux Device Driver Kit CD, which is a great work, the authors taken
 * the work to recompile lots of inक्रमmation an knowledge in drivers development
 * and made it all available inside a cd.
 * URL: http://kernel.org/pub/linux/kernel/people/gregkh/ddk/
 *
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

/* Venकरोr and Product ID */
#घोषणा AIRCABLE_VID		0x16CA
#घोषणा AIRCABLE_USB_PID	0x1502

/* Protocol Stuff */
#घोषणा HCI_HEADER_LENGTH	0x4
#घोषणा TX_HEADER_0		0x20
#घोषणा TX_HEADER_1		0x29
#घोषणा RX_HEADER_0		0x00
#घोषणा RX_HEADER_1		0x20
#घोषणा HCI_COMPLETE_FRAME	64

/* rx_flags */
#घोषणा THROTTLED		0x01
#घोषणा ACTUALLY_THROTTLED	0x02

#घोषणा DRIVER_AUTHOR "Naranjo, Manuel Francisco <naranjo.manuel@gmail.com>, Johan Hovold <jhovold@gmail.com>"
#घोषणा DRIVER_DESC "AIRcable USB Driver"

/* ID table that will be रेजिस्टरed with USB core */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(AIRCABLE_VID, AIRCABLE_USB_PID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक aircable_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
						व्योम *dest, माप_प्रकार size)
अणु
	पूर्णांक count;
	अचिन्हित अक्षर *buf = dest;

	count = kfअगरo_out_locked(&port->ग_लिखो_fअगरo, buf + HCI_HEADER_LENGTH,
					size - HCI_HEADER_LENGTH, &port->lock);
	buf[0] = TX_HEADER_0;
	buf[1] = TX_HEADER_1;
	put_unaligned_le16(count, &buf[2]);

	वापस count + HCI_HEADER_LENGTH;
पूर्ण

अटल पूर्णांक aircable_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	/* Ignore the first पूर्णांकerface, which has no bulk endpoपूर्णांकs. */
	अगर (epds->num_bulk_out == 0) अणु
		dev_dbg(&serial->पूर्णांकerface->dev,
			"ignoring interface with no bulk-out endpoints\n");
		वापस -ENODEV;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक aircable_process_packet(काष्ठा usb_serial_port *port,
		पूर्णांक has_headers, अक्षर *packet, पूर्णांक len)
अणु
	अगर (has_headers) अणु
		len -= HCI_HEADER_LENGTH;
		packet += HCI_HEADER_LENGTH;
	पूर्ण
	अगर (len <= 0) अणु
		dev_dbg(&port->dev, "%s - malformed packet\n", __func__);
		वापस 0;
	पूर्ण

	tty_insert_flip_string(&port->port, packet, len);

	वापस len;
पूर्ण

अटल व्योम aircable_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अक्षर *data = urb->transfer_buffer;
	पूर्णांक has_headers;
	पूर्णांक count;
	पूर्णांक len;
	पूर्णांक i;

	has_headers = (urb->actual_length > 2 && data[0] == RX_HEADER_0);

	count = 0;
	क्रम (i = 0; i < urb->actual_length; i += HCI_COMPLETE_FRAME) अणु
		len = min_t(पूर्णांक, urb->actual_length - i, HCI_COMPLETE_FRAME);
		count += aircable_process_packet(port, has_headers,
								&data[i], len);
	पूर्ण

	अगर (count)
		tty_flip_buffer_push(&port->port);
पूर्ण

अटल काष्ठा usb_serial_driver aircable_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"aircable",
	पूर्ण,
	.id_table = 		id_table,
	.bulk_out_size =	HCI_COMPLETE_FRAME,
	.calc_num_ports =	aircable_calc_num_ports,
	.process_पढ़ो_urb =	aircable_process_पढ़ो_urb,
	.prepare_ग_लिखो_buffer =	aircable_prepare_ग_लिखो_buffer,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&aircable_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
