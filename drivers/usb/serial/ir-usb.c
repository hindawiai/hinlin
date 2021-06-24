<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB IR Dongle driver
 *
 *	Copyright (C) 2001-2002	Greg Kroah-Harपंचांगan (greg@kroah.com)
 *	Copyright (C) 2002	Gary Brubaker (xavyer@ix.netcom.com)
 *	Copyright (C) 2010	Johan Hovold (jhovold@gmail.com)
 *
 * This driver allows a USB IrDA device to be used as a "dumb" serial device.
 * This can be useful अगर you करो not have access to a full IrDA stack on the
 * other side of the connection.  If you करो have an IrDA stack on both devices,
 * please use the usb-irda driver, as it contains the proper error checking and
 * other goodness of a full IrDA stack.
 *
 * Portions of this driver were taken from drivers/net/irda/irda-usb.c, which
 * was written by Roman Weissgaerber <weissg@vienna.at>, Dag Brattli
 * <dag@brattli.net>, and Jean Tourrilhes <jt@hpl.hp.com>
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/usb/irda.h>

#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com>, Johan Hovold <jhovold@gmail.com>"
#घोषणा DRIVER_DESC "USB IR Dongle driver"

/* अगर overridden by the user, then use their value क्रम the size of the पढ़ो and
 * ग_लिखो urbs */
अटल पूर्णांक buffer_size;

/* अगर overridden by the user, then use the specअगरied number of XBOFs */
अटल पूर्णांक xbof = -1;

अटल पूर्णांक  ir_startup (काष्ठा usb_serial *serial);
अटल पूर्णांक ir_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल पूर्णांक ir_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल व्योम ir_ग_लिखो_bulk_callback(काष्ठा urb *urb);
अटल व्योम ir_process_पढ़ो_urb(काष्ठा urb *urb);
अटल व्योम ir_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios);

/* Not that this lot means you can only have one per प्रणाली */
अटल u8 ir_baud;
अटल u8 ir_xbof;
अटल u8 ir_add_bof;

अटल स्थिर काष्ठा usb_device_id ir_id_table[] = अणु
	अणु USB_DEVICE(0x050f, 0x0180) पूर्ण,		/* KC Technology, KC-180 */
	अणु USB_DEVICE(0x08e9, 0x0100) पूर्ण,		/* XTNDAccess */
	अणु USB_DEVICE(0x09c4, 0x0011) पूर्ण,		/* ACTiSys ACT-IR2000U */
	अणु USB_INTERFACE_INFO(USB_CLASS_APP_SPEC, USB_SUBCLASS_IRDA, 0) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ir_id_table);

अटल काष्ठा usb_serial_driver ir_device = अणु
	.driver	= अणु
		.owner	= THIS_MODULE,
		.name	= "ir-usb",
	पूर्ण,
	.description		= "IR Dongle",
	.id_table		= ir_id_table,
	.num_ports		= 1,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.set_termios		= ir_set_termios,
	.attach			= ir_startup,
	.ग_लिखो			= ir_ग_लिखो,
	.ग_लिखो_room		= ir_ग_लिखो_room,
	.ग_लिखो_bulk_callback	= ir_ग_लिखो_bulk_callback,
	.process_पढ़ो_urb	= ir_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ir_device, शून्य
पूर्ण;

अटल अंतरभूत व्योम irda_usb_dump_class_desc(काष्ठा usb_serial *serial,
					    काष्ठा usb_irda_cs_descriptor *desc)
अणु
	काष्ठा device *dev = &serial->dev->dev;

	dev_dbg(dev, "bLength=%x\n", desc->bLength);
	dev_dbg(dev, "bDescriptorType=%x\n", desc->bDescriptorType);
	dev_dbg(dev, "bcdSpecRevision=%x\n", __le16_to_cpu(desc->bcdSpecRevision));
	dev_dbg(dev, "bmDataSize=%x\n", desc->bmDataSize);
	dev_dbg(dev, "bmWindowSize=%x\n", desc->bmWinकरोwSize);
	dev_dbg(dev, "bmMinTurnaroundTime=%d\n", desc->bmMinTurnaroundTime);
	dev_dbg(dev, "wBaudRate=%x\n", __le16_to_cpu(desc->wBaudRate));
	dev_dbg(dev, "bmAdditionalBOFs=%x\n", desc->bmAdditionalBOFs);
	dev_dbg(dev, "bIrdaRateSniff=%x\n", desc->bIrdaRateSnअगरf);
	dev_dbg(dev, "bMaxUnicastList=%x\n", desc->bMaxUnicastList);
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Function irda_usb_find_class_desc(dev, अगरnum)
 *
 *    Returns instance of IrDA class descriptor, or शून्य अगर not found
 *
 * The class descriptor is some extra info that IrDA USB devices will
 * offer to us, describing their IrDA अक्षरacteristics. We will use that in
 * irda_usb_init_qos()
 *
 * Based on the same function in drivers/net/irda/irda-usb.c
 */
अटल काष्ठा usb_irda_cs_descriptor *
irda_usb_find_class_desc(काष्ठा usb_serial *serial, अचिन्हित पूर्णांक अगरnum)
अणु
	काष्ठा usb_device *dev = serial->dev;
	काष्ठा usb_irda_cs_descriptor *desc;
	पूर्णांक ret;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			USB_REQ_CS_IRDA_GET_CLASS_DESC,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			0, अगरnum, desc, माप(*desc), 1000);

	dev_dbg(&serial->dev->dev, "%s -  ret=%d\n", __func__, ret);
	अगर (ret < (पूर्णांक)माप(*desc)) अणु
		dev_dbg(&serial->dev->dev,
			"%s - class descriptor read %s (%d)\n", __func__,
			(ret < 0) ? "failed" : "too short", ret);
		जाओ error;
	पूर्ण
	अगर (desc->bDescriptorType != USB_DT_CS_IRDA) अणु
		dev_dbg(&serial->dev->dev, "%s - bad class descriptor type\n",
			__func__);
		जाओ error;
	पूर्ण

	irda_usb_dump_class_desc(serial, desc);
	वापस desc;

error:
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल u8 ir_xbof_change(u8 xbof)
अणु
	u8 result;

	/* reference irda-usb.c */
	चयन (xbof) अणु
	हाल 48:
		result = 0x10;
		अवरोध;
	हाल 28:
	हाल 24:
		result = 0x20;
		अवरोध;
	शेष:
	हाल 12:
		result = 0x30;
		अवरोध;
	हाल  5:
	हाल  6:
		result = 0x40;
		अवरोध;
	हाल  3:
		result = 0x50;
		अवरोध;
	हाल  2:
		result = 0x60;
		अवरोध;
	हाल  1:
		result = 0x70;
		अवरोध;
	हाल  0:
		result = 0x80;
		अवरोध;
	पूर्ण

	वापस(result);
पूर्ण

अटल पूर्णांक ir_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_irda_cs_descriptor *irda_desc;
	पूर्णांक rates;

	irda_desc = irda_usb_find_class_desc(serial, 0);
	अगर (!irda_desc) अणु
		dev_err(&serial->dev->dev,
			"IRDA class descriptor not found, device not bound\n");
		वापस -ENODEV;
	पूर्ण

	rates = le16_to_cpu(irda_desc->wBaudRate);

	dev_dbg(&serial->dev->dev,
		"%s - Baud rates supported:%s%s%s%s%s%s%s%s%s\n",
		__func__,
		(rates & USB_IRDA_BR_2400) ? " 2400" : "",
		(rates & USB_IRDA_BR_9600) ? " 9600" : "",
		(rates & USB_IRDA_BR_19200) ? " 19200" : "",
		(rates & USB_IRDA_BR_38400) ? " 38400" : "",
		(rates & USB_IRDA_BR_57600) ? " 57600" : "",
		(rates & USB_IRDA_BR_115200) ? " 115200" : "",
		(rates & USB_IRDA_BR_576000) ? " 576000" : "",
		(rates & USB_IRDA_BR_1152000) ? " 1152000" : "",
		(rates & USB_IRDA_BR_4000000) ? " 4000000" : "");

	चयन (irda_desc->bmAdditionalBOFs) अणु
	हाल USB_IRDA_AB_48:
		ir_add_bof = 48;
		अवरोध;
	हाल USB_IRDA_AB_24:
		ir_add_bof = 24;
		अवरोध;
	हाल USB_IRDA_AB_12:
		ir_add_bof = 12;
		अवरोध;
	हाल USB_IRDA_AB_6:
		ir_add_bof = 6;
		अवरोध;
	हाल USB_IRDA_AB_3:
		ir_add_bof = 3;
		अवरोध;
	हाल USB_IRDA_AB_2:
		ir_add_bof = 2;
		अवरोध;
	हाल USB_IRDA_AB_1:
		ir_add_bof = 1;
		अवरोध;
	हाल USB_IRDA_AB_0:
		ir_add_bof = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(irda_desc);

	वापस 0;
पूर्ण

अटल पूर्णांक ir_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा urb *urb = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (port->bulk_out_size == 0)
		वापस -EINVAL;

	अगर (count == 0)
		वापस 0;

	count = min(count, port->bulk_out_size - 1);

	spin_lock_irqsave(&port->lock, flags);
	अगर (__test_and_clear_bit(0, &port->ग_लिखो_urbs_मुक्त)) अणु
		urb = port->ग_लिखो_urbs[0];
		port->tx_bytes += count;
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (!urb)
		वापस 0;

	/*
	 * The first byte of the packet we send to the device contains an
	 * outbound header which indicates an additional number of BOFs and
	 * a baud rate change.
	 *
	 * See section 5.4.2.2 of the USB IrDA spec.
	 */
	*(u8 *)urb->transfer_buffer = ir_xbof | ir_baud;

	स_नकल(urb->transfer_buffer + 1, buf, count);

	urb->transfer_buffer_length = count + 1;
	urb->transfer_flags = URB_ZERO_PACKET;

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to submit write urb: %d\n", ret);

		spin_lock_irqsave(&port->lock, flags);
		__set_bit(0, &port->ग_लिखो_urbs_मुक्त);
		port->tx_bytes -= count;
		spin_unlock_irqrestore(&port->lock, flags);

		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम ir_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	__set_bit(0, &port->ग_लिखो_urbs_मुक्त);
	port->tx_bytes -= urb->transfer_buffer_length - 1;
	spin_unlock_irqrestore(&port->lock, flags);

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&port->dev, "write urb stopped: %d\n", status);
		वापस;
	हाल -EPIPE:
		dev_err(&port->dev, "write urb stopped: %d\n", status);
		वापस;
	शेष:
		dev_err(&port->dev, "nonzero write-urb status: %d\n", status);
		अवरोध;
	पूर्ण

	usb_serial_port_softपूर्णांक(port);
पूर्ण

अटल पूर्णांक ir_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक count = 0;

	अगर (port->bulk_out_size == 0)
		वापस 0;

	अगर (test_bit(0, &port->ग_लिखो_urbs_मुक्त))
		count = port->bulk_out_size - 1;

	वापस count;
पूर्ण

अटल व्योम ir_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;

	अगर (!urb->actual_length)
		वापस;
	/*
	 * The first byte of the packet we get from the device
	 * contains a busy indicator and baud rate change.
	 * See section 5.4.1.2 of the USB IrDA spec.
	 */
	अगर (*data & 0x0f)
		ir_baud = *data & 0x0f;

	अगर (urb->actual_length == 1)
		वापस;

	tty_insert_flip_string(&port->port, data + 1, urb->actual_length - 1);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम ir_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	अचिन्हित अक्षर *transfer_buffer;
	पूर्णांक actual_length;
	speed_t baud;
	पूर्णांक ir_baud;
	पूर्णांक ret;

	baud = tty_get_baud_rate(tty);

	/*
	 * FIXME, we should compare the baud request against the
	 * capability stated in the IR header that we got in the
	 * startup function.
	 */

	चयन (baud) अणु
	हाल 2400:
		ir_baud = USB_IRDA_LS_2400;
		अवरोध;
	हाल 9600:
		ir_baud = USB_IRDA_LS_9600;
		अवरोध;
	हाल 19200:
		ir_baud = USB_IRDA_LS_19200;
		अवरोध;
	हाल 38400:
		ir_baud = USB_IRDA_LS_38400;
		अवरोध;
	हाल 57600:
		ir_baud = USB_IRDA_LS_57600;
		अवरोध;
	हाल 115200:
		ir_baud = USB_IRDA_LS_115200;
		अवरोध;
	हाल 576000:
		ir_baud = USB_IRDA_LS_576000;
		अवरोध;
	हाल 1152000:
		ir_baud = USB_IRDA_LS_1152000;
		अवरोध;
	हाल 4000000:
		ir_baud = USB_IRDA_LS_4000000;
		अवरोध;
	शेष:
		ir_baud = USB_IRDA_LS_9600;
		baud = 9600;
	पूर्ण

	अगर (xbof == -1)
		ir_xbof = ir_xbof_change(ir_add_bof);
	अन्यथा
		ir_xbof = ir_xbof_change(xbof) ;

	/* Only speed changes are supported */
	tty_termios_copy_hw(&tty->termios, old_termios);
	tty_encode_baud_rate(tty, baud, baud);

	/*
	 * send the baud change out on an "empty" data packet
	 */
	transfer_buffer = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस;

	*transfer_buffer = ir_xbof | ir_baud;

	ret = usb_bulk_msg(udev,
			usb_sndbulkpipe(udev, port->bulk_out_endpoपूर्णांकAddress),
			transfer_buffer, 1, &actual_length, 5000);
	अगर (ret || actual_length != 1) अणु
		अगर (!ret)
			ret = -EIO;
		dev_err(&port->dev, "failed to change line speed: %d\n", ret);
	पूर्ण

	kमुक्त(transfer_buffer);
पूर्ण

अटल पूर्णांक __init ir_init(व्योम)
अणु
	अगर (buffer_size) अणु
		ir_device.bulk_in_size = buffer_size;
		ir_device.bulk_out_size = buffer_size;
	पूर्ण

	वापस usb_serial_रेजिस्टर_drivers(serial_drivers, KBUILD_MODNAME, ir_id_table);
पूर्ण

अटल व्योम __निकास ir_निकास(व्योम)
अणु
	usb_serial_deरेजिस्टर_drivers(serial_drivers);
पूर्ण


module_init(ir_init);
module_निकास(ir_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(xbof, पूर्णांक, 0);
MODULE_PARM_DESC(xbof, "Force specific number of XBOFs");
module_param(buffer_size, पूर्णांक, 0);
MODULE_PARM_DESC(buffer_size, "Size of the transfer buffers");

