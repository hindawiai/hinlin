<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Navman Serial USB driver
 *
 * Copyright (C) 2006 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *
 * TODO:
 *	Add termios method that uses copy_hw but also समाप्तs all echo
 *	flags as the navman is rx only so cannot echo.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x0a99, 0x0001) पूर्ण,	/* Talon Technology device */
	अणु USB_DEVICE(0x0df7, 0x0900) पूर्ण,	/* Mobile Action i-gotU */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल व्योम navman_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;
	पूर्णांक result;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&port->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	अगर (urb->actual_length) अणु
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण

निकास:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&urb->dev->dev,
			"%s - Error %d submitting interrupt urb\n",
			__func__, result);
पूर्ण

अटल पूर्णांक navman_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक result = 0;

	अगर (port->पूर्णांकerrupt_in_urb) अणु
		dev_dbg(&port->dev, "%s - adding interrupt input for treo\n",
			__func__);
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (result)
			dev_err(&port->dev,
				"%s - failed submitting interrupt urb, error %d\n",
				__func__, result);
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम navman_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल पूर्णांक navman_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	/*
	 * This device can't ग_लिखो any data, only पढ़ो from the device
	 */
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा usb_serial_driver navman_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"navman",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.खोलो =			navman_खोलो,
	.बंद = 		navman_बंद,
	.ग_लिखो = 		navman_ग_लिखो,
	.पढ़ो_पूर्णांक_callback =	navman_पढ़ो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&navman_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL v2");
