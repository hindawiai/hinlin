<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Debug cable driver
 *
 * Copyright (C) 2006 Greg Kroah-Harपंचांगan <greg@kroah.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा USB_DEBUG_MAX_PACKET_SIZE	8
#घोषणा USB_DEBUG_BRK_SIZE		8
अटल स्थिर अक्षर USB_DEBUG_BRK[USB_DEBUG_BRK_SIZE] = अणु
	0x00,
	0xff,
	0x01,
	0xfe,
	0x00,
	0xfe,
	0x01,
	0xff,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x0525, 0x127a) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id dbc_id_table[] = अणु
	अणु USB_DEVICE(0x1d6b, 0x0010) पूर्ण,
	अणु USB_DEVICE(0x1d6b, 0x0011) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(0x0525, 0x127a) पूर्ण,
	अणु USB_DEVICE(0x1d6b, 0x0010) पूर्ण,
	अणु USB_DEVICE(0x1d6b, 0x0011) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table_combined);

/* This HW really करोes not support a serial अवरोध, so one will be
 * emulated when ever the अवरोध state is set to true.
 */
अटल व्योम usb_debug_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अगर (!अवरोध_state)
		वापस;
	usb_serial_generic_ग_लिखो(tty, port, USB_DEBUG_BRK, USB_DEBUG_BRK_SIZE);
पूर्ण

अटल व्योम usb_debug_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;

	अगर (urb->actual_length == USB_DEBUG_BRK_SIZE &&
		स_भेद(urb->transfer_buffer, USB_DEBUG_BRK,
						USB_DEBUG_BRK_SIZE) == 0) अणु
		usb_serial_handle_अवरोध(port);
		वापस;
	पूर्ण

	usb_serial_generic_process_पढ़ो_urb(urb);
पूर्ण

अटल काष्ठा usb_serial_driver debug_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"debug",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.bulk_out_size =	USB_DEBUG_MAX_PACKET_SIZE,
	.अवरोध_ctl =		usb_debug_अवरोध_ctl,
	.process_पढ़ो_urb =	usb_debug_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver dbc_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"xhci_dbc",
	पूर्ण,
	.id_table =		dbc_id_table,
	.num_ports =		1,
	.अवरोध_ctl =		usb_debug_अवरोध_ctl,
	.process_पढ़ो_urb =	usb_debug_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&debug_device, &dbc_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table_combined);
MODULE_LICENSE("GPL v2");
