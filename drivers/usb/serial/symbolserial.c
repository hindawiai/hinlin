<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Symbol USB barcode to serial driver
 *
 * Copyright (C) 2013 Johan Hovold <jhovold@gmail.com>
 * Copyright (C) 2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (C) 2009 Novell Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x05e0, 0x0600) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा symbol_निजी अणु
	spinlock_t lock;	/* protects the following flags */
	bool throttled;
	bool actually_throttled;
पूर्ण;

अटल व्योम symbol_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा symbol_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक data_length;

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

	/*
	 * Data from the device comes with a 1 byte header:
	 *
	 * <size of data> <data>...
	 */
	अगर (urb->actual_length > 1) अणु
		data_length = data[0];
		अगर (data_length > (urb->actual_length - 1))
			data_length = urb->actual_length - 1;
		tty_insert_flip_string(&port->port, &data[1], data_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - short packet\n", __func__);
	पूर्ण

निकास:
	spin_lock_irqsave(&priv->lock, flags);

	/* Continue trying to always पढ़ो अगर we should */
	अगर (!priv->throttled) अणु
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
		अगर (result)
			dev_err(&port->dev,
			    "%s - failed resubmitting read urb, error %d\n",
							__func__, result);
	पूर्ण अन्यथा
		priv->actually_throttled = true;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक symbol_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा symbol_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	spin_lock_irqsave(&priv->lock, flags);
	priv->throttled = false;
	priv->actually_throttled = false;
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Start पढ़ोing from the device */
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result)
		dev_err(&port->dev,
			"%s - failed resubmitting read urb, error %d\n",
			__func__, result);
	वापस result;
पूर्ण

अटल व्योम symbol_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण

अटल व्योम symbol_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा symbol_निजी *priv = usb_get_serial_port_data(port);

	spin_lock_irq(&priv->lock);
	priv->throttled = true;
	spin_unlock_irq(&priv->lock);
पूर्ण

अटल व्योम symbol_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा symbol_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक result;
	bool was_throttled;

	spin_lock_irq(&priv->lock);
	priv->throttled = false;
	was_throttled = priv->actually_throttled;
	priv->actually_throttled = false;
	spin_unlock_irq(&priv->lock);

	अगर (was_throttled) अणु
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (result)
			dev_err(&port->dev,
				"%s - failed submitting read urb, error %d\n",
							__func__, result);
	पूर्ण
पूर्ण

अटल पूर्णांक symbol_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा symbol_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम symbol_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा symbol_निजी *priv = usb_get_serial_port_data(port);

	kमुक्त(priv);
पूर्ण

अटल काष्ठा usb_serial_driver symbol_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"symbol",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.num_पूर्णांकerrupt_in =	1,
	.port_probe =		symbol_port_probe,
	.port_हटाओ =		symbol_port_हटाओ,
	.खोलो =			symbol_खोलो,
	.बंद =		symbol_बंद,
	.throttle = 		symbol_throttle,
	.unthrottle =		symbol_unthrottle,
	.पढ़ो_पूर्णांक_callback =	symbol_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&symbol_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL v2");
