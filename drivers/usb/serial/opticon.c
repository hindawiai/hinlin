<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Opticon USB barcode to serial driver
 *
 * Copyright (C) 2011 - 2012 Johan Hovold <jhovold@gmail.com>
 * Copyright (C) 2011 Martin Jansen <martin.jansen@opticon.com>
 * Copyright (C) 2008 - 2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (C) 2008 - 2009 Novell Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>

#घोषणा CONTROL_RTS			0x02
#घोषणा RESEND_CTS_STATE	0x03

/* max number of ग_लिखो urbs in flight */
#घोषणा URB_UPPER_LIMIT	8

/* This driver works क्रम the Opticon 1D barcode पढ़ोer
 * an examples of 1D barcode types are EAN, UPC, Code39, IATA etc.. */
#घोषणा DRIVER_DESC	"Opticon USB barcode to serial driver (1D)"

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x065a, 0x0009) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* This काष्ठाure holds all of the inभागidual device inक्रमmation */
काष्ठा opticon_निजी अणु
	spinlock_t lock;	/* protects the following flags */
	bool rts;
	bool cts;
	पूर्णांक outstanding_urbs;
	पूर्णांक outstanding_bytes;

	काष्ठा usb_anchor anchor;
पूर्ण;


अटल व्योम opticon_process_data_packet(काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	tty_insert_flip_string(&port->port, buf, len);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम opticon_process_status_packet(काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (buf[0] == 0x00)
		priv->cts = false;
	अन्यथा
		priv->cts = true;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम opticon_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	स्थिर अचिन्हित अक्षर *hdr = urb->transfer_buffer;
	स्थिर अचिन्हित अक्षर *data = hdr + 2;
	माप_प्रकार data_len = urb->actual_length - 2;

	अगर (urb->actual_length <= 2) अणु
		dev_dbg(&port->dev, "malformed packet received: %d bytes\n",
							urb->actual_length);
		वापस;
	पूर्ण
	/*
	 * Data from the device comes with a 2 byte header:
	 *
	 * <0x00><0x00>data...
	 *      This is real data to be sent to the tty layer
	 * <0x00><0x01>level
	 *      This is a CTS level change, the third byte is the CTS
	 *      value (0 क्रम low, 1 क्रम high).
	 */
	अगर ((hdr[0] == 0x00) && (hdr[1] == 0x00)) अणु
		opticon_process_data_packet(port, data, data_len);
	पूर्ण अन्यथा अगर ((hdr[0] == 0x00) && (hdr[1] == 0x01)) अणु
		opticon_process_status_packet(port, data, data_len);
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "unknown packet received: %02x %02x\n",
							hdr[0], hdr[1]);
	पूर्ण
पूर्ण

अटल पूर्णांक send_control_msg(काष्ठा usb_serial_port *port, u8 requesttype,
				u8 val)
अणु
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक retval;
	u8 *buffer;

	buffer = kzalloc(1, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer[0] = val;
	/* Send the message to the venकरोr control endpoपूर्णांक
	 * of the connected device */
	retval = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				requesttype,
				USB_सूची_OUT|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
				0, 0, buffer, 1, USB_CTRL_SET_TIMEOUT);
	kमुक्त(buffer);

	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल पूर्णांक opticon_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&priv->lock, flags);
	priv->rts = false;
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Clear RTS line */
	send_control_msg(port, CONTROL_RTS, 0);

	/* clear the halt status of the endpoपूर्णांक */
	usb_clear_halt(port->serial->dev, port->पढ़ो_urb->pipe);

	res = usb_serial_generic_खोलो(tty, port);
	अगर (res)
		वापस res;

	/* Request CTS line state, someबार during खोलोing the current
	 * CTS state can be missed. */
	send_control_msg(port, RESEND_CTS_STATE, 1);

	वापस res;
पूर्ण

अटल व्योम opticon_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);

	usb_समाप्त_anchored_urbs(&priv->anchor);

	usb_serial_generic_बंद(port);
पूर्ण

अटल व्योम opticon_ग_लिखो_control_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	/* मुक्त up the transfer buffer, as usb_मुक्त_urb() करोes not करो this */
	kमुक्त(urb->transfer_buffer);

	/* setup packet may be set अगर we're using it क्रम writing */
	kमुक्त(urb->setup_packet);

	अगर (status)
		dev_dbg(&port->dev,
			"%s - non-zero urb status received: %d\n",
			__func__, status);

	spin_lock_irqsave(&priv->lock, flags);
	--priv->outstanding_urbs;
	priv->outstanding_bytes -= urb->transfer_buffer_length;
	spin_unlock_irqrestore(&priv->lock, flags);

	usb_serial_port_softपूर्णांक(port);
पूर्ण

अटल पूर्णांक opticon_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buffer;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_ctrlrequest *dr;
	पूर्णांक ret = -ENOMEM;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->outstanding_urbs > URB_UPPER_LIMIT) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&port->dev, "%s - write limit hit\n", __func__);
		वापस 0;
	पूर्ण
	priv->outstanding_urbs++;
	priv->outstanding_bytes += count;
	spin_unlock_irqrestore(&priv->lock, flags);

	buffer = kदो_स्मृति(count, GFP_ATOMIC);
	अगर (!buffer)
		जाओ error_no_buffer;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ error_no_urb;

	स_नकल(buffer, buf, count);

	usb_serial_debug_data(&port->dev, __func__, count, buffer);

	/* The connected devices करो not have a bulk ग_लिखो endpoपूर्णांक,
	 * to transmit data to de barcode device the control endpoपूर्णांक is used */
	dr = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_ATOMIC);
	अगर (!dr)
		जाओ error_no_dr;

	dr->bRequestType = USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT;
	dr->bRequest = 0x01;
	dr->wValue = 0;
	dr->wIndex = 0;
	dr->wLength = cpu_to_le16(count);

	usb_fill_control_urb(urb, serial->dev,
		usb_sndctrlpipe(serial->dev, 0),
		(अचिन्हित अक्षर *)dr, buffer, count,
		opticon_ग_लिखो_control_callback, port);

	usb_anchor_urb(urb, &priv->anchor);

	/* send it करोwn the pipe */
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to submit write urb: %d\n", ret);
		usb_unanchor_urb(urb);
		जाओ error;
	पूर्ण

	/* we are करोne with this urb, so let the host driver
	 * really मुक्त it when it is finished with it */
	usb_मुक्त_urb(urb);

	वापस count;
error:
	kमुक्त(dr);
error_no_dr:
	usb_मुक्त_urb(urb);
error_no_urb:
	kमुक्त(buffer);
error_no_buffer:
	spin_lock_irqsave(&priv->lock, flags);
	--priv->outstanding_urbs;
	priv->outstanding_bytes -= count;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक opticon_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	/*
	 * We really can take almost anything the user throws at us
	 * but let's pick a nice big number to tell the tty
	 * layer that we have lots of मुक्त space, unless we करोn't.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->outstanding_urbs > URB_UPPER_LIMIT * 2 / 3) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		dev_dbg(&port->dev, "%s - write limit hit\n", __func__);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 2048;
पूर्ण

अटल पूर्णांक opticon_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	spin_lock_irqsave(&priv->lock, flags);
	count = priv->outstanding_bytes;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक opticon_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->rts)
		result |= TIOCM_RTS;
	अगर (priv->cts)
		result |= TIOCM_CTS;
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s - %x\n", __func__, result);
	वापस result;
पूर्ण

अटल पूर्णांक opticon_tiocmset(काष्ठा tty_काष्ठा *tty,
			   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	bool rts;
	bool changed = false;
	पूर्णांक ret;

	/* We only support RTS so we only handle that */
	spin_lock_irqsave(&priv->lock, flags);

	rts = priv->rts;
	अगर (set & TIOCM_RTS)
		priv->rts = true;
	अगर (clear & TIOCM_RTS)
		priv->rts = false;
	changed = rts ^ priv->rts;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (!changed)
		वापस 0;

	ret = send_control_msg(port, CONTROL_RTS, !rts);
	अगर (ret)
		वापस usb_translate_errors(ret);

	वापस 0;
पूर्ण

अटल पूर्णांक opticon_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा opticon_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	init_usb_anchor(&priv->anchor);

	usb_set_serial_port_data(port, priv);

	वापस 0;
पूर्ण

अटल व्योम opticon_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा opticon_निजी *priv = usb_get_serial_port_data(port);

	kमुक्त(priv);
पूर्ण

अटल काष्ठा usb_serial_driver opticon_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"opticon",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.num_bulk_in =		1,
	.bulk_in_size =		256,
	.port_probe =		opticon_port_probe,
	.port_हटाओ =		opticon_port_हटाओ,
	.खोलो =			opticon_खोलो,
	.बंद =		opticon_बंद,
	.ग_लिखो =		opticon_ग_लिखो,
	.ग_लिखो_room = 		opticon_ग_लिखो_room,
	.अक्षरs_in_buffer =	opticon_अक्षरs_in_buffer,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.tiocmget =		opticon_tiocmget,
	.tiocmset =		opticon_tiocmset,
	.process_पढ़ो_urb =	opticon_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&opticon_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
