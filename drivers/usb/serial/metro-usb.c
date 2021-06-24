<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
  Some of this code is credited to Linux USB खोलो source files that are
  distributed with Linux.

  Copyright:	2007 Metrologic Instruments. All rights reserved.
  Copyright:	2011 Azimut Ltd. <http://azimutrzn.ru/>
*/

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb/serial.h>

#घोषणा DRIVER_DESC "Metrologic Instruments Inc. - USB-POS driver"

/* Product inक्रमmation. */
#घोषणा FOCUS_VENDOR_ID			0x0C2E
#घोषणा FOCUS_PRODUCT_ID_BI		0x0720
#घोषणा FOCUS_PRODUCT_ID_UNI		0x0700

#घोषणा METROUSB_SET_REQUEST_TYPE	0x40
#घोषणा METROUSB_SET_MODEM_CTRL_REQUEST	10
#घोषणा METROUSB_SET_BREAK_REQUEST	0x40
#घोषणा METROUSB_MCR_NONE		0x08	/* Deactivate DTR and RTS. */
#घोषणा METROUSB_MCR_RTS		0x0a	/* Activate RTS. */
#घोषणा METROUSB_MCR_DTR		0x09	/* Activate DTR. */
#घोषणा WDR_TIMEOUT			5000	/* शेष urb समयout. */

/* Private data काष्ठाure. */
काष्ठा metrousb_निजी अणु
	spinlock_t lock;
	पूर्णांक throttled;
	अचिन्हित दीर्घ control_state;
पूर्ण;

/* Device table list. */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(FOCUS_VENDOR_ID, FOCUS_PRODUCT_ID_BI) पूर्ण,
	अणु USB_DEVICE(FOCUS_VENDOR_ID, FOCUS_PRODUCT_ID_UNI) पूर्ण,
	अणु USB_DEVICE_INTERFACE_CLASS(0x0c2e, 0x0730, 0xff) पूर्ण,	/* MS7820 */
	अणु पूर्ण, /* Terminating entry. */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* UNI-Directional mode commands क्रम device configure */
#घोषणा UNI_CMD_OPEN	0x80
#घोषणा UNI_CMD_CLOSE	0xFF

अटल पूर्णांक metrousb_is_unidirectional_mode(काष्ठा usb_serial *serial)
अणु
	u16 product_id = le16_to_cpu(serial->dev->descriptor.idProduct);

	वापस product_id == FOCUS_PRODUCT_ID_UNI;
पूर्ण

अटल पूर्णांक metrousb_calc_num_ports(काष्ठा usb_serial *serial,
				   काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	अगर (metrousb_is_unidirectional_mode(serial)) अणु
		अगर (epds->num_पूर्णांकerrupt_out == 0) अणु
			dev_err(&serial->पूर्णांकerface->dev, "interrupt-out endpoint missing\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक metrousb_send_unidirectional_cmd(u8 cmd, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक ret;
	पूर्णांक actual_len;
	u8 *buffer_cmd = शून्य;

	अगर (!metrousb_is_unidirectional_mode(port->serial))
		वापस 0;

	buffer_cmd = kzalloc(माप(cmd), GFP_KERNEL);
	अगर (!buffer_cmd)
		वापस -ENOMEM;

	*buffer_cmd = cmd;

	ret = usb_पूर्णांकerrupt_msg(port->serial->dev,
		usb_sndपूर्णांकpipe(port->serial->dev, port->पूर्णांकerrupt_out_endpoपूर्णांकAddress),
		buffer_cmd, माप(cmd),
		&actual_len, USB_CTRL_SET_TIMEOUT);

	kमुक्त(buffer_cmd);

	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (actual_len != माप(cmd))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल व्योम metrousb_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक throttled = 0;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ flags = 0;

	dev_dbg(&port->dev, "%s\n", __func__);

	चयन (urb->status) अणु
	हाल 0:
		/* Success status, पढ़ो from the port. */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* urb has been terminated. */
		dev_dbg(&port->dev,
			"%s - urb shutting down, error code=%d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&port->dev,
			"%s - non-zero urb received, error code=%d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण


	/* Set the data पढ़ो from the usb port पूर्णांकo the serial port buffer. */
	अगर (urb->actual_length) अणु
		/* Loop through the data copying each byte to the tty layer. */
		tty_insert_flip_string(&port->port, data, urb->actual_length);

		/* Force the data to the tty layer. */
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* Set any port variables. */
	spin_lock_irqsave(&metro_priv->lock, flags);
	throttled = metro_priv->throttled;
	spin_unlock_irqrestore(&metro_priv->lock, flags);

	अगर (throttled)
		वापस;
निकास:
	/* Try to resubmit the urb. */
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&port->dev,
			"%s - failed submitting interrupt in urb, error code=%d\n",
			__func__, result);
पूर्ण

अटल व्योम metrousb_cleanup(काष्ठा usb_serial_port *port)
अणु
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	metrousb_send_unidirectional_cmd(UNI_CMD_CLOSE, port);
पूर्ण

अटल पूर्णांक metrousb_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक result = 0;

	/* Set the निजी data inक्रमmation क्रम the port. */
	spin_lock_irqsave(&metro_priv->lock, flags);
	metro_priv->control_state = 0;
	metro_priv->throttled = 0;
	spin_unlock_irqrestore(&metro_priv->lock, flags);

	/* Clear the urb pipe. */
	usb_clear_halt(serial->dev, port->पूर्णांकerrupt_in_urb->pipe);

	/* Start पढ़ोing from the device */
	usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_in_urb, serial->dev,
			  usb_rcvपूर्णांकpipe(serial->dev, port->पूर्णांकerrupt_in_endpoपूर्णांकAddress),
			   port->पूर्णांकerrupt_in_urb->transfer_buffer,
			   port->पूर्णांकerrupt_in_urb->transfer_buffer_length,
			   metrousb_पढ़ो_पूर्णांक_callback, port, 1);
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);

	अगर (result) अणु
		dev_err(&port->dev,
			"%s - failed submitting interrupt in urb, error code=%d\n",
			__func__, result);
		वापस result;
	पूर्ण

	/* Send activate cmd to device */
	result = metrousb_send_unidirectional_cmd(UNI_CMD_OPEN, port);
	अगर (result) अणु
		dev_err(&port->dev,
			"%s - failed to configure device, error code=%d\n",
			__func__, result);
		जाओ err_समाप्त_urb;
	पूर्ण

	वापस 0;

err_समाप्त_urb:
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	वापस result;
पूर्ण

अटल पूर्णांक metrousb_set_modem_ctrl(काष्ठा usb_serial *serial, अचिन्हित पूर्णांक control_state)
अणु
	पूर्णांक retval = 0;
	अचिन्हित अक्षर mcr = METROUSB_MCR_NONE;

	dev_dbg(&serial->dev->dev, "%s - control state = %d\n",
		__func__, control_state);

	/* Set the modem control value. */
	अगर (control_state & TIOCM_DTR)
		mcr |= METROUSB_MCR_DTR;
	अगर (control_state & TIOCM_RTS)
		mcr |= METROUSB_MCR_RTS;

	/* Send the command to the usb port. */
	retval = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				METROUSB_SET_REQUEST_TYPE, METROUSB_SET_MODEM_CTRL_REQUEST,
				control_state, 0, शून्य, 0, WDR_TIMEOUT);
	अगर (retval < 0)
		dev_err(&serial->dev->dev,
			"%s - set modem ctrl=0x%x failed, error code=%d\n",
			__func__, mcr, retval);

	वापस retval;
पूर्ण

अटल पूर्णांक metrousb_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा metrousb_निजी *metro_priv;

	metro_priv = kzalloc(माप(*metro_priv), GFP_KERNEL);
	अगर (!metro_priv)
		वापस -ENOMEM;

	spin_lock_init(&metro_priv->lock);

	usb_set_serial_port_data(port, metro_priv);

	वापस 0;
पूर्ण

अटल व्योम metrousb_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा metrousb_निजी *metro_priv;

	metro_priv = usb_get_serial_port_data(port);
	kमुक्त(metro_priv);
पूर्ण

अटल व्योम metrousb_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;

	/* Set the निजी inक्रमmation क्रम the port to stop पढ़ोing data. */
	spin_lock_irqsave(&metro_priv->lock, flags);
	metro_priv->throttled = 1;
	spin_unlock_irqrestore(&metro_priv->lock, flags);
पूर्ण

अटल पूर्णांक metrousb_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ control_state = 0;
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&metro_priv->lock, flags);
	control_state = metro_priv->control_state;
	spin_unlock_irqrestore(&metro_priv->lock, flags);

	वापस control_state;
पूर्ण

अटल पूर्णांक metrousb_tiocmset(काष्ठा tty_काष्ठा *tty,
			     अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ control_state = 0;

	dev_dbg(&port->dev, "%s - set=%d, clear=%d\n", __func__, set, clear);

	spin_lock_irqsave(&metro_priv->lock, flags);
	control_state = metro_priv->control_state;

	/* Set the RTS and DTR values. */
	अगर (set & TIOCM_RTS)
		control_state |= TIOCM_RTS;
	अगर (set & TIOCM_DTR)
		control_state |= TIOCM_DTR;
	अगर (clear & TIOCM_RTS)
		control_state &= ~TIOCM_RTS;
	अगर (clear & TIOCM_DTR)
		control_state &= ~TIOCM_DTR;

	metro_priv->control_state = control_state;
	spin_unlock_irqrestore(&metro_priv->lock, flags);
	वापस metrousb_set_modem_ctrl(serial, control_state);
पूर्ण

अटल व्योम metrousb_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा metrousb_निजी *metro_priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक result = 0;

	/* Set the निजी inक्रमmation क्रम the port to resume पढ़ोing data. */
	spin_lock_irqsave(&metro_priv->lock, flags);
	metro_priv->throttled = 0;
	spin_unlock_irqrestore(&metro_priv->lock, flags);

	/* Submit the urb to पढ़ो from the port. */
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&port->dev,
			"failed submitting interrupt in urb error code=%d\n",
			result);
पूर्ण

अटल काष्ठा usb_serial_driver metrousb_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"metro-usb",
	पूर्ण,
	.description		= "Metrologic USB to Serial",
	.id_table		= id_table,
	.num_पूर्णांकerrupt_in	= 1,
	.calc_num_ports		= metrousb_calc_num_ports,
	.खोलो			= metrousb_खोलो,
	.बंद			= metrousb_cleanup,
	.पढ़ो_पूर्णांक_callback	= metrousb_पढ़ो_पूर्णांक_callback,
	.port_probe		= metrousb_port_probe,
	.port_हटाओ		= metrousb_port_हटाओ,
	.throttle		= metrousb_throttle,
	.unthrottle		= metrousb_unthrottle,
	.tiocmget		= metrousb_tiocmget,
	.tiocmset		= metrousb_tiocmset,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&metrousb_device,
	शून्य,
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Philip Nicastro");
MODULE_AUTHOR("Aleksey Babahin <tamerlan311@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
