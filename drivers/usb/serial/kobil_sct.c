<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  KOBIL USB Smart Card Terminal Driver
 *
 *  Copyright (C) 2002  KOBIL Systems GmbH
 *  Author: Thomas Wahrenbruch
 *
 *  Contact: linuxusb@kobil.de
 *
 *  This program is largely derived from work by the linux-usb group
 *  and associated source files.  Please see the usb/serial files क्रम
 *  inभागidual credits and copyrights.
 *
 *  Thanks to Greg Kroah-Harपंचांगan (greg@kroah.com) क्रम his help and
 *  patience.
 *
 * Supported पढ़ोers: USB TWIN, KAAN Standard Plus and SecOVID Reader Plus
 * (Adapter K), B1 Professional and KAAN Professional (Adapter B)
 */


#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/ioctl.h>
#समावेश "kobil_sct.h"

#घोषणा DRIVER_AUTHOR "KOBIL Systems GmbH - http://www.kobil.com"
#घोषणा DRIVER_DESC "KOBIL USB Smart Card Terminal Driver (experimental)"

#घोषणा KOBIL_VENDOR_ID			0x0D46
#घोषणा KOBIL_ADAPTER_B_PRODUCT_ID	0x2011
#घोषणा KOBIL_ADAPTER_K_PRODUCT_ID	0x2012
#घोषणा KOBIL_USBTWIN_PRODUCT_ID	0x0078
#घोषणा KOBIL_KAAN_SIM_PRODUCT_ID       0x0081

#घोषणा KOBIL_TIMEOUT		500
#घोषणा KOBIL_BUF_LENGTH	300


/* Function prototypes */
अटल पूर्णांक kobil_port_probe(काष्ठा usb_serial_port *probe);
अटल व्योम kobil_port_हटाओ(काष्ठा usb_serial_port *probe);
अटल पूर्णांक  kobil_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम kobil_बंद(काष्ठा usb_serial_port *port);
अटल पूर्णांक  kobil_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल पूर्णांक  kobil_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  kobil_ioctl(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक  kobil_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  kobil_tiocmset(काष्ठा tty_काष्ठा *tty,
			   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम kobil_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम kobil_ग_लिखो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम kobil_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल व्योम kobil_init_termios(काष्ठा tty_काष्ठा *tty);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(KOBIL_VENDOR_ID, KOBIL_ADAPTER_B_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KOBIL_VENDOR_ID, KOBIL_ADAPTER_K_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KOBIL_VENDOR_ID, KOBIL_USBTWIN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(KOBIL_VENDOR_ID, KOBIL_KAAN_SIM_PRODUCT_ID) पूर्ण,
	अणु पूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver kobil_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"kobil",
	पूर्ण,
	.description =		"KOBIL USB smart card terminal",
	.id_table =		id_table,
	.num_ports =		1,
	.num_पूर्णांकerrupt_out =	1,
	.port_probe =		kobil_port_probe,
	.port_हटाओ =		kobil_port_हटाओ,
	.ioctl =		kobil_ioctl,
	.set_termios =		kobil_set_termios,
	.init_termios =		kobil_init_termios,
	.tiocmget =		kobil_tiocmget,
	.tiocmset =		kobil_tiocmset,
	.खोलो =			kobil_खोलो,
	.बंद =		kobil_बंद,
	.ग_लिखो =		kobil_ग_लिखो,
	.ग_लिखो_room =		kobil_ग_लिखो_room,
	.पढ़ो_पूर्णांक_callback =	kobil_पढ़ो_पूर्णांक_callback,
	.ग_लिखो_पूर्णांक_callback =	kobil_ग_लिखो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&kobil_device, शून्य
पूर्ण;

काष्ठा kobil_निजी अणु
	अचिन्हित अक्षर buf[KOBIL_BUF_LENGTH]; /* buffer क्रम the APDU to send */
	पूर्णांक filled;  /* index of the last अक्षर in buf */
	पूर्णांक cur_pos; /* index of the next अक्षर to send in buf */
	__u16 device_type;
पूर्ण;


अटल पूर्णांक kobil_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा kobil_निजी *priv;

	priv = kदो_स्मृति(माप(काष्ठा kobil_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->filled = 0;
	priv->cur_pos = 0;
	priv->device_type = le16_to_cpu(serial->dev->descriptor.idProduct);

	चयन (priv->device_type) अणु
	हाल KOBIL_ADAPTER_B_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL B1 PRO / KAAN PRO detected\n");
		अवरोध;
	हाल KOBIL_ADAPTER_K_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL KAAN Standard Plus / SecOVID Reader Plus detected\n");
		अवरोध;
	हाल KOBIL_USBTWIN_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL USBTWIN detected\n");
		अवरोध;
	हाल KOBIL_KAAN_SIM_PRODUCT_ID:
		dev_dbg(&serial->dev->dev, "KOBIL KAAN SIM detected\n");
		अवरोध;
	पूर्ण
	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण


अटल व्योम kobil_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा kobil_निजी *priv;

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल व्योम kobil_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	/* Default to echo off and other sane device settings */
	tty->termios.c_lflag = 0;
	tty->termios.c_अगरlag &= ~(ISIG | ICANON | ECHO | IEXTEN | XCASE);
	tty->termios.c_अगरlag |= IGNBRK | IGNPAR | IXOFF;
	/* करो NOT translate CR to CR-NL (0x0A -> 0x0A 0x0D) */
	tty->termios.c_oflag &= ~ONLCR;
पूर्ण

अटल पूर्णांक kobil_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा device *dev = &port->dev;
	पूर्णांक result = 0;
	काष्ठा kobil_निजी *priv;
	अचिन्हित अक्षर *transfer_buffer;
	पूर्णांक transfer_buffer_length = 8;

	priv = usb_get_serial_port_data(port);

	/* allocate memory क्रम transfer buffer */
	transfer_buffer = kzalloc(transfer_buffer_length, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	/* get hardware version */
	result = usb_control_msg(port->serial->dev,
			  usb_rcvctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_GetMisc,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_IN,
			  SUSBCR_MSC_GetHWVersion,
			  0,
			  transfer_buffer,
			  transfer_buffer_length,
			  KOBIL_TIMEOUT
	);
	dev_dbg(dev, "%s - Send get_HW_version URB returns: %i\n", __func__, result);
	अगर (result >= 3) अणु
		dev_dbg(dev, "Hardware version: %i.%i.%i\n", transfer_buffer[0],
				transfer_buffer[1], transfer_buffer[2]);
	पूर्ण

	/* get firmware version */
	result = usb_control_msg(port->serial->dev,
			  usb_rcvctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_GetMisc,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_IN,
			  SUSBCR_MSC_GetFWVersion,
			  0,
			  transfer_buffer,
			  transfer_buffer_length,
			  KOBIL_TIMEOUT
	);
	dev_dbg(dev, "%s - Send get_FW_version URB returns: %i\n", __func__, result);
	अगर (result >= 3) अणु
		dev_dbg(dev, "Firmware version: %i.%i.%i\n", transfer_buffer[0],
				transfer_buffer[1], transfer_buffer[2]);
	पूर्ण

	अगर (priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID ||
			priv->device_type == KOBIL_ADAPTER_K_PRODUCT_ID) अणु
		/* Setting Baudrate, Parity and Stopbits */
		result = usb_control_msg(port->serial->dev,
			  usb_sndctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_SetBaudRateParityAndStopBits,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			  SUSBCR_SBR_9600 | SUSBCR_SPASB_EvenParity |
							SUSBCR_SPASB_1StopBit,
			  0,
			  शून्य,
			  0,
			  KOBIL_TIMEOUT
		);
		dev_dbg(dev, "%s - Send set_baudrate URB returns: %i\n", __func__, result);

		/* reset all queues */
		result = usb_control_msg(port->serial->dev,
			  usb_sndctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_Misc,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			  SUSBCR_MSC_ResetAllQueues,
			  0,
			  शून्य,
			  0,
			  KOBIL_TIMEOUT
		);
		dev_dbg(dev, "%s - Send reset_all_queues URB returns: %i\n", __func__, result);
	पूर्ण
	अगर (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID ||
	    priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID ||
	    priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID) अणु
		/* start पढ़ोing (Adapter B 'cause PNP string) */
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		dev_dbg(dev, "%s - Send read URB returns: %i\n", __func__, result);
	पूर्ण

	kमुक्त(transfer_buffer);
	वापस 0;
पूर्ण


अटल व्योम kobil_बंद(काष्ठा usb_serial_port *port)
अणु
	/* FIXME: Add rts/dtr methods */
	usb_समाप्त_urb(port->पूर्णांकerrupt_out_urb);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
पूर्ण


अटल व्योम kobil_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	पूर्णांक result;
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&port->dev, "%s - Read int status not zero: %d\n", __func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length) अणु
		usb_serial_debug_data(&port->dev, __func__, urb->actual_length,
									data);
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण

	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	dev_dbg(&port->dev, "%s - Send read URB returns: %i\n", __func__, result);
पूर्ण


अटल व्योम kobil_ग_लिखो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
पूर्ण


अटल पूर्णांक kobil_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक length = 0;
	पूर्णांक result = 0;
	पूर्णांक toकरो = 0;
	काष्ठा kobil_निजी *priv;

	अगर (count == 0) अणु
		dev_dbg(&port->dev, "%s - write request of 0 bytes\n", __func__);
		वापस 0;
	पूर्ण

	priv = usb_get_serial_port_data(port);

	अगर (count > (KOBIL_BUF_LENGTH - priv->filled)) अणु
		dev_dbg(&port->dev, "%s - Error: write request bigger than buffer size\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* Copy data to buffer */
	स_नकल(priv->buf + priv->filled, buf, count);
	usb_serial_debug_data(&port->dev, __func__, count, priv->buf + priv->filled);
	priv->filled = priv->filled + count;

	/* only send complete block. TWIN, KAAN SIM and adapter K
	   use the same protocol. */
	अगर (((priv->device_type != KOBIL_ADAPTER_B_PRODUCT_ID) && (priv->filled > 2) && (priv->filled >= (priv->buf[1] + 3))) ||
	     ((priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID) && (priv->filled > 3) && (priv->filled >= (priv->buf[2] + 4)))) अणु
		/* stop पढ़ोing (except TWIN and KAAN SIM) */
		अगर ((priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID)
			|| (priv->device_type == KOBIL_ADAPTER_K_PRODUCT_ID))
			usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

		toकरो = priv->filled - priv->cur_pos;

		जबतक (toकरो > 0) अणु
			/* max 8 byte in one urb (endpoपूर्णांक size) */
			length = min(toकरो, port->पूर्णांकerrupt_out_size);
			/* copy data to transfer buffer */
			स_नकल(port->पूर्णांकerrupt_out_buffer,
					priv->buf + priv->cur_pos, length);
			port->पूर्णांकerrupt_out_urb->transfer_buffer_length = length;

			priv->cur_pos = priv->cur_pos + length;
			result = usb_submit_urb(port->पूर्णांकerrupt_out_urb,
					GFP_ATOMIC);
			dev_dbg(&port->dev, "%s - Send write URB returns: %i\n", __func__, result);
			toकरो = priv->filled - priv->cur_pos;

			अगर (toकरो > 0)
				msleep(24);
		पूर्ण

		priv->filled = 0;
		priv->cur_pos = 0;

		/* start पढ़ोing (except TWIN and KAAN SIM) */
		अगर (priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID ||
			priv->device_type == KOBIL_ADAPTER_K_PRODUCT_ID) अणु
			result = usb_submit_urb(port->पूर्णांकerrupt_in_urb,
					GFP_ATOMIC);
			dev_dbg(&port->dev, "%s - Send read URB returns: %i\n", __func__, result);
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण


अटल पूर्णांक kobil_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	/* FIXME */
	वापस 8;
पूर्ण


अटल पूर्णांक kobil_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा kobil_निजी *priv;
	पूर्णांक result;
	अचिन्हित अक्षर *transfer_buffer;
	पूर्णांक transfer_buffer_length = 8;

	priv = usb_get_serial_port_data(port);
	अगर (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID
			|| priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID) अणु
		/* This device करोesn't support ioctl calls */
		वापस -EINVAL;
	पूर्ण

	/* allocate memory क्रम transfer buffer */
	transfer_buffer = kzalloc(transfer_buffer_length, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	result = usb_control_msg(port->serial->dev,
			  usb_rcvctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_GetStatusLineState,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_IN,
			  0,
			  0,
			  transfer_buffer,
			  transfer_buffer_length,
			  KOBIL_TIMEOUT);

	dev_dbg(&port->dev, "Send get_status_line_state URB returns: %i\n",
			result);
	अगर (result < 1) अणु
		अगर (result >= 0)
			result = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	dev_dbg(&port->dev, "Statusline: %02x\n", transfer_buffer[0]);

	result = 0;
	अगर ((transfer_buffer[0] & SUSBCR_GSL_DSR) != 0)
		result = TIOCM_DSR;
out_मुक्त:
	kमुक्त(transfer_buffer);
	वापस result;
पूर्ण

अटल पूर्णांक kobil_tiocmset(काष्ठा tty_काष्ठा *tty,
			   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा device *dev = &port->dev;
	काष्ठा kobil_निजी *priv;
	पूर्णांक result;
	पूर्णांक dtr = 0;
	पूर्णांक rts = 0;

	/* FIXME: locking ? */
	priv = usb_get_serial_port_data(port);
	अगर (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID
		|| priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID) अणु
		/* This device करोesn't support ioctl calls */
		वापस -EINVAL;
	पूर्ण

	अगर (set & TIOCM_RTS)
		rts = 1;
	अगर (set & TIOCM_DTR)
		dtr = 1;
	अगर (clear & TIOCM_RTS)
		rts = 0;
	अगर (clear & TIOCM_DTR)
		dtr = 0;

	अगर (priv->device_type == KOBIL_ADAPTER_B_PRODUCT_ID) अणु
		अगर (dtr != 0)
			dev_dbg(dev, "%s - Setting DTR\n", __func__);
		अन्यथा
			dev_dbg(dev, "%s - Clearing DTR\n", __func__);
		result = usb_control_msg(port->serial->dev,
			  usb_sndctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_SetStatusLinesOrQueues,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			  ((dtr != 0) ? SUSBCR_SSL_SETDTR : SUSBCR_SSL_CLRDTR),
			  0,
			  शून्य,
			  0,
			  KOBIL_TIMEOUT);
	पूर्ण अन्यथा अणु
		अगर (rts != 0)
			dev_dbg(dev, "%s - Setting RTS\n", __func__);
		अन्यथा
			dev_dbg(dev, "%s - Clearing RTS\n", __func__);
		result = usb_control_msg(port->serial->dev,
			usb_sndctrlpipe(port->serial->dev, 0),
			SUSBCRequest_SetStatusLinesOrQueues,
			USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			((rts != 0) ? SUSBCR_SSL_SETRTS : SUSBCR_SSL_CLRRTS),
			0,
			शून्य,
			0,
			KOBIL_TIMEOUT);
	पूर्ण
	dev_dbg(dev, "%s - Send set_status_line URB returns: %i\n", __func__, result);
	वापस (result < 0) ? result : 0;
पूर्ण

अटल व्योम kobil_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old)
अणु
	काष्ठा kobil_निजी *priv;
	पूर्णांक result;
	अचिन्हित लघु urb_val = 0;
	पूर्णांक c_cflag = tty->termios.c_cflag;
	speed_t speed;

	priv = usb_get_serial_port_data(port);
	अगर (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID ||
			priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID) अणु
		/* This device करोesn't support ioctl calls */
		tty_termios_copy_hw(&tty->termios, old);
		वापस;
	पूर्ण

	speed = tty_get_baud_rate(tty);
	चयन (speed) अणु
	हाल 1200:
		urb_val = SUSBCR_SBR_1200;
		अवरोध;
	शेष:
		speed = 9600;
		fallthrough;
	हाल 9600:
		urb_val = SUSBCR_SBR_9600;
		अवरोध;
	पूर्ण
	urb_val |= (c_cflag & CSTOPB) ? SUSBCR_SPASB_2StopBits :
							SUSBCR_SPASB_1StopBit;
	अगर (c_cflag & PARENB) अणु
		अगर  (c_cflag & PARODD)
			urb_val |= SUSBCR_SPASB_OddParity;
		अन्यथा
			urb_val |= SUSBCR_SPASB_EvenParity;
	पूर्ण अन्यथा
		urb_val |= SUSBCR_SPASB_NoParity;
	tty->termios.c_cflag &= ~CMSPAR;
	tty_encode_baud_rate(tty, speed, speed);

	result = usb_control_msg(port->serial->dev,
		  usb_sndctrlpipe(port->serial->dev, 0),
		  SUSBCRequest_SetBaudRateParityAndStopBits,
		  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
		  urb_val,
		  0,
		  शून्य,
		  0,
		  KOBIL_TIMEOUT
		);
	अगर (result) अणु
		dev_err(&port->dev, "failed to update line settings: %d\n",
				result);
	पूर्ण
पूर्ण

अटल पूर्णांक kobil_ioctl(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा kobil_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक result;

	अगर (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID ||
			priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID)
		/* This device करोesn't support ioctl calls */
		वापस -ENOIOCTLCMD;

	चयन (cmd) अणु
	हाल TCFLSH:
		result = usb_control_msg(port->serial->dev,
			  usb_sndctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_Misc,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			  SUSBCR_MSC_ResetAllQueues,
			  0,
			  शून्य,
			  0,
			  KOBIL_TIMEOUT
			);

		dev_dbg(&port->dev,
			"%s - Send reset_all_queues (FLUSH) URB returns: %i\n",
			__func__, result);
		वापस (result < 0) ? -EIO: 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
