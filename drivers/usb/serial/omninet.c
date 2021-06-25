<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB ZyXEL omni.net driver
 *
 * Copyright (C) 2013,2017 Johan Hovold <johan@kernel.org>
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 * Please report both successes and troubles to the author at omninet@kroah.com
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा DRIVER_AUTHOR "Alessandro Zummo"
#घोषणा DRIVER_DESC "USB ZyXEL omni.net Driver"

#घोषणा ZYXEL_VENDOR_ID		0x0586
#घोषणा ZYXEL_OMNINET_ID	0x1000
#घोषणा ZYXEL_OMNI_56K_PLUS_ID	0x1500
/* This one seems to be a re-bअक्रमed ZyXEL device */
#घोषणा BT_IGNITIONPRO_ID	0x2000

/* function prototypes */
अटल व्योम omninet_process_पढ़ो_urb(काष्ठा urb *urb);
अटल पूर्णांक omninet_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
				व्योम *buf, माप_प्रकार count);
अटल पूर्णांक omninet_calc_num_ports(काष्ठा usb_serial *serial,
				काष्ठा usb_serial_endpoपूर्णांकs *epds);
अटल पूर्णांक omninet_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम omninet_port_हटाओ(काष्ठा usb_serial_port *port);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(ZYXEL_VENDOR_ID, ZYXEL_OMNINET_ID) पूर्ण,
	अणु USB_DEVICE(ZYXEL_VENDOR_ID, ZYXEL_OMNI_56K_PLUS_ID) पूर्ण,
	अणु USB_DEVICE(ZYXEL_VENDOR_ID, BT_IGNITIONPRO_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver zyxel_omninet_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"omninet",
	पूर्ण,
	.description =		"ZyXEL - omni.net usb",
	.id_table =		id_table,
	.num_bulk_out =		2,
	.calc_num_ports =	omninet_calc_num_ports,
	.port_probe =		omninet_port_probe,
	.port_हटाओ =		omninet_port_हटाओ,
	.process_पढ़ो_urb =	omninet_process_पढ़ो_urb,
	.prepare_ग_लिखो_buffer =	omninet_prepare_ग_लिखो_buffer,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&zyxel_omninet_device, शून्य
पूर्ण;


/*
 * The protocol.
 *
 * The omni.net always exchange 64 bytes of data with the host. The first
 * four bytes are the control header.
 *
 * oh_seq is a sequence number. Don't know if/how it's used.
 * oh_len is the length of the data bytes in the packet.
 * oh_xxx Bit-mapped, related to handshaking and status info.
 *	I normally set it to 0x03 in transmitted frames.
 *	7: Active when the TA is in a CONNECTed state.
 *	6: unknown
 *	5: handshaking, unknown
 *	4: handshaking, unknown
 *	3: unknown, usually 0
 *	2: unknown, usually 0
 *	1: handshaking, unknown, usually set to 1 in transmitted frames
 *	0: handshaking, unknown, usually set to 1 in transmitted frames
 * oh_pad Probably a pad byte.
 *
 * After the header you will find data bytes अगर oh_len was greater than zero.
 */
काष्ठा omninet_header अणु
	__u8	oh_seq;
	__u8	oh_len;
	__u8	oh_xxx;
	__u8	oh_pad;
पूर्ण;

काष्ठा omninet_data अणु
	__u8	od_outseq;	/* Sequence number क्रम bulk_out URBs */
पूर्ण;

अटल पूर्णांक omninet_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	/* We need only the second bulk-out क्रम our single-port device. */
	epds->bulk_out[0] = epds->bulk_out[1];
	epds->num_bulk_out = 1;

	वापस 1;
पूर्ण

अटल पूर्णांक omninet_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा omninet_data *od;

	od = kzalloc(माप(*od), GFP_KERNEL);
	अगर (!od)
		वापस -ENOMEM;

	usb_set_serial_port_data(port, od);

	वापस 0;
पूर्ण

अटल व्योम omninet_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा omninet_data *od;

	od = usb_get_serial_port_data(port);
	kमुक्त(od);
पूर्ण

#घोषणा OMNINET_HEADERLEN	4
#घोषणा OMNINET_BULKOUTSIZE	64
#घोषणा OMNINET_PAYLOADSIZE	(OMNINET_BULKOUTSIZE - OMNINET_HEADERLEN)

अटल व्योम omninet_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	स्थिर काष्ठा omninet_header *hdr = urb->transfer_buffer;
	स्थिर अचिन्हित अक्षर *data;
	माप_प्रकार data_len;

	अगर (urb->actual_length <= OMNINET_HEADERLEN || !hdr->oh_len)
		वापस;

	data = (अक्षर *)urb->transfer_buffer + OMNINET_HEADERLEN;
	data_len = min_t(माप_प्रकार, urb->actual_length - OMNINET_HEADERLEN,
								hdr->oh_len);
	tty_insert_flip_string(&port->port, data, data_len);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल पूर्णांक omninet_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
					व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा omninet_data *od = usb_get_serial_port_data(port);
	काष्ठा omninet_header *header = buf;

	count = min_t(माप_प्रकार, count, OMNINET_PAYLOADSIZE);

	count = kfअगरo_out_locked(&port->ग_लिखो_fअगरo, buf + OMNINET_HEADERLEN,
			count, &port->lock);

	header->oh_seq = od->od_outseq++;
	header->oh_len = count;
	header->oh_xxx = 0x03;
	header->oh_pad = 0x00;

	/* always 64 bytes */
	वापस OMNINET_BULKOUTSIZE;
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
