<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  REINER SCT cyberJack pinpad/e-com USB Chipcard Reader Driver
 *
 *  Copyright (C) 2001  REINER SCT
 *  Author: Matthias Bruestle
 *
 *  Contact: support@reiner-sct.com (see MAINTAINERS)
 *
 *  This program is largely derived from work by the linux-usb group
 *  and associated source files.  Please see the usb/serial files क्रम
 *  inभागidual credits and copyrights.
 *
 *  Thanks to Greg Kroah-Harपंचांगan (greg@kroah.com) क्रम his help and
 *  patience.
 *
 *  In हाल of problems, please ग_लिखो to the contact e-mail address
 *  mentioned above.
 *
 *  Please note that later models of the cyberjack पढ़ोer family are
 *  supported by a libusb-based userspace device driver.
 *
 *  Homepage: http://www.reiner-sct.de/support/treiber_cyberjack.php#linux
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

#घोषणा CYBERJACK_LOCAL_BUF_SIZE 32

#घोषणा DRIVER_AUTHOR "Matthias Bruestle"
#घोषणा DRIVER_DESC "REINER SCT cyberJack pinpad/e-com USB Chipcard Reader Driver"


#घोषणा CYBERJACK_VENDOR_ID	0x0C4B
#घोषणा CYBERJACK_PRODUCT_ID	0x0100

/* Function prototypes */
अटल पूर्णांक cyberjack_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम cyberjack_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक  cyberjack_खोलो(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port);
अटल व्योम cyberjack_बंद(काष्ठा usb_serial_port *port);
अटल पूर्णांक cyberjack_ग_लिखो(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल पूर्णांक cyberjack_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल व्योम cyberjack_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम cyberjack_पढ़ो_bulk_callback(काष्ठा urb *urb);
अटल व्योम cyberjack_ग_लिखो_bulk_callback(काष्ठा urb *urb);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(CYBERJACK_VENDOR_ID, CYBERJACK_PRODUCT_ID) पूर्ण,
	अणु पूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver cyberjack_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"cyberjack",
	पूर्ण,
	.description =		"Reiner SCT Cyberjack USB card reader",
	.id_table =		id_table,
	.num_ports =		1,
	.num_bulk_out =		1,
	.port_probe =		cyberjack_port_probe,
	.port_हटाओ =		cyberjack_port_हटाओ,
	.खोलो =			cyberjack_खोलो,
	.बंद =		cyberjack_बंद,
	.ग_लिखो =		cyberjack_ग_लिखो,
	.ग_लिखो_room =		cyberjack_ग_लिखो_room,
	.पढ़ो_पूर्णांक_callback =	cyberjack_पढ़ो_पूर्णांक_callback,
	.पढ़ो_bulk_callback =	cyberjack_पढ़ो_bulk_callback,
	.ग_लिखो_bulk_callback =	cyberjack_ग_लिखो_bulk_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&cyberjack_device, शून्य
पूर्ण;

काष्ठा cyberjack_निजी अणु
	spinlock_t	lock;		/* Lock क्रम SMP */
	लघु		rdtoकरो;		/* Bytes still to पढ़ो */
	अचिन्हित अक्षर	wrbuf[5*64];	/* Buffer क्रम collecting data to ग_लिखो */
	लघु		wrfilled;	/* Overall data size we alपढ़ोy got */
	लघु		wrsent;		/* Data alपढ़ोy sent */
पूर्ण;

अटल पूर्णांक cyberjack_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cyberjack_निजी *priv;
	पूर्णांक result;

	priv = kदो_स्मृति(माप(काष्ठा cyberjack_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	priv->rdtoकरो = 0;
	priv->wrfilled = 0;
	priv->wrsent = 0;

	usb_set_serial_port_data(port, priv);

	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result)
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");

	वापस 0;
पूर्ण

अटल व्योम cyberjack_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cyberjack_निजी *priv;

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	priv = usb_get_serial_port_data(port);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक  cyberjack_खोलो(काष्ठा tty_काष्ठा *tty,
					काष्ठा usb_serial_port *port)
अणु
	काष्ठा cyberjack_निजी *priv;
	अचिन्हित दीर्घ flags;

	dev_dbg(&port->dev, "%s - usb_clear_halt\n", __func__);
	usb_clear_halt(port->serial->dev, port->ग_लिखो_urb->pipe);

	priv = usb_get_serial_port_data(port);
	spin_lock_irqsave(&priv->lock, flags);
	priv->rdtoकरो = 0;
	priv->wrfilled = 0;
	priv->wrsent = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम cyberjack_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_समाप्त_urb(port->ग_लिखो_urb);
	usb_समाप्त_urb(port->पढ़ो_urb);
पूर्ण

अटल पूर्णांक cyberjack_ग_लिखो(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा device *dev = &port->dev;
	काष्ठा cyberjack_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक wrexpected;

	अगर (count == 0) अणु
		dev_dbg(dev, "%s - write request of 0 bytes\n", __func__);
		वापस 0;
	पूर्ण

	अगर (!test_and_clear_bit(0, &port->ग_लिखो_urbs_मुक्त)) अणु
		dev_dbg(dev, "%s - already writing\n", __func__);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	अगर (count+priv->wrfilled > माप(priv->wrbuf)) अणु
		/* To much data क्रम buffer. Reset buffer. */
		priv->wrfilled = 0;
		spin_unlock_irqrestore(&priv->lock, flags);
		set_bit(0, &port->ग_लिखो_urbs_मुक्त);
		वापस 0;
	पूर्ण

	/* Copy data */
	स_नकल(priv->wrbuf + priv->wrfilled, buf, count);

	usb_serial_debug_data(dev, __func__, count, priv->wrbuf + priv->wrfilled);
	priv->wrfilled += count;

	अगर (priv->wrfilled >= 3) अणु
		wrexpected = ((पूर्णांक)priv->wrbuf[2]<<8)+priv->wrbuf[1]+3;
		dev_dbg(dev, "%s - expected data: %d\n", __func__, wrexpected);
	पूर्ण अन्यथा
		wrexpected = माप(priv->wrbuf);

	अगर (priv->wrfilled >= wrexpected) अणु
		/* We have enough data to begin transmission */
		पूर्णांक length;

		dev_dbg(dev, "%s - transmitting data (frame 1)\n", __func__);
		length = (wrexpected > port->bulk_out_size) ?
					port->bulk_out_size : wrexpected;

		स_नकल(port->ग_लिखो_urb->transfer_buffer, priv->wrbuf, length);
		priv->wrsent = length;

		/* set up our urb */
		port->ग_लिखो_urb->transfer_buffer_length = length;

		/* send the data out the bulk port */
		result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (result) अणु
			dev_err(&port->dev,
				"%s - failed submitting write urb, error %d\n",
				__func__, result);
			/* Throw away data. No better idea what to करो with it. */
			priv->wrfilled = 0;
			priv->wrsent = 0;
			spin_unlock_irqrestore(&priv->lock, flags);
			set_bit(0, &port->ग_लिखो_urbs_मुक्त);
			वापस 0;
		पूर्ण

		dev_dbg(dev, "%s - priv->wrsent=%d\n", __func__, priv->wrsent);
		dev_dbg(dev, "%s - priv->wrfilled=%d\n", __func__, priv->wrfilled);

		अगर (priv->wrsent >= priv->wrfilled) अणु
			dev_dbg(dev, "%s - buffer cleaned\n", __func__);
			स_रखो(priv->wrbuf, 0, माप(priv->wrbuf));
			priv->wrfilled = 0;
			priv->wrsent = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक cyberjack_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	/* FIXME: .... */
	वापस CYBERJACK_LOCAL_BUF_SIZE;
पूर्ण

अटल व्योम cyberjack_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cyberjack_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	/* the urb might have been समाप्तed. */
	अगर (status)
		वापस;

	usb_serial_debug_data(dev, __func__, urb->actual_length, data);

	/* React only to पूर्णांकerrupts संकेतing a bulk_in transfer */
	अगर (urb->actual_length == 4 && data[0] == 0x01) अणु
		लघु old_rdtoकरो;

		/* This is a announcement of coming bulk_ins. */
		अचिन्हित लघु size = ((अचिन्हित लघु)data[3]<<8)+data[2]+3;

		spin_lock_irqsave(&priv->lock, flags);

		old_rdtoकरो = priv->rdtoकरो;

		अगर (old_rdtoकरो > लघु_उच्च - size) अणु
			dev_dbg(dev, "Too many bulk_in urbs to do.\n");
			spin_unlock_irqrestore(&priv->lock, flags);
			जाओ resubmit;
		पूर्ण

		/* "+=" is probably more fault tolerant than "=" */
		priv->rdtoकरो += size;

		dev_dbg(dev, "%s - rdtodo: %d\n", __func__, priv->rdtoकरो);

		spin_unlock_irqrestore(&priv->lock, flags);

		अगर (!old_rdtoकरो) अणु
			result = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
			अगर (result)
				dev_err(dev, "%s - failed resubmitting read urb, error %d\n",
					__func__, result);
			dev_dbg(dev, "%s - usb_submit_urb(read urb)\n", __func__);
		पूर्ण
	पूर्ण

resubmit:
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");
	dev_dbg(dev, "%s - usb_submit_urb(int urb)\n", __func__);
पूर्ण

अटल व्योम cyberjack_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cyberjack_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	लघु toकरो;
	पूर्णांक result;
	पूर्णांक status = urb->status;

	usb_serial_debug_data(dev, __func__, urb->actual_length, data);
	अगर (status) अणु
		dev_dbg(dev, "%s - nonzero read bulk status received: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length) अणु
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	/* Reduce urbs to करो by one. */
	priv->rdtoकरो -= urb->actual_length;
	/* Just to be sure */
	अगर (priv->rdtoकरो < 0)
		priv->rdtoकरो = 0;
	toकरो = priv->rdtoकरो;

	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(dev, "%s - rdtodo: %d\n", __func__, toकरो);

	/* Continue to पढ़ो अगर we have still urbs to करो. */
	अगर (toकरो /* || (urb->actual_length==port->bulk_in_endpoपूर्णांकAddress)*/) अणु
		result = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
		अगर (result)
			dev_err(dev, "%s - failed resubmitting read urb, error %d\n",
				__func__, result);
		dev_dbg(dev, "%s - usb_submit_urb(read urb)\n", __func__);
	पूर्ण
पूर्ण

अटल व्योम cyberjack_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cyberjack_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	bool resubmitted = false;

	अगर (status) अणु
		dev_dbg(dev, "%s - nonzero write bulk status received: %d\n",
			__func__, status);
		set_bit(0, &port->ग_लिखो_urbs_मुक्त);
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	/* only करो something अगर we have more data to send */
	अगर (priv->wrfilled) अणु
		पूर्णांक length, blksize, result;

		dev_dbg(dev, "%s - transmitting data (frame n)\n", __func__);

		length = ((priv->wrfilled - priv->wrsent) > port->bulk_out_size) ?
			port->bulk_out_size : (priv->wrfilled - priv->wrsent);

		स_नकल(port->ग_लिखो_urb->transfer_buffer,
					priv->wrbuf + priv->wrsent, length);
		priv->wrsent += length;

		/* set up our urb */
		port->ग_लिखो_urb->transfer_buffer_length = length;

		/* send the data out the bulk port */
		result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
		अगर (result) अणु
			dev_err(dev, "%s - failed submitting write urb, error %d\n",
				__func__, result);
			/* Throw away data. No better idea what to करो with it. */
			priv->wrfilled = 0;
			priv->wrsent = 0;
			जाओ निकास;
		पूर्ण

		resubmitted = true;

		dev_dbg(dev, "%s - priv->wrsent=%d\n", __func__, priv->wrsent);
		dev_dbg(dev, "%s - priv->wrfilled=%d\n", __func__, priv->wrfilled);

		blksize = ((पूर्णांक)priv->wrbuf[2]<<8)+priv->wrbuf[1]+3;

		अगर (priv->wrsent >= priv->wrfilled ||
					priv->wrsent >= blksize) अणु
			dev_dbg(dev, "%s - buffer cleaned\n", __func__);
			स_रखो(priv->wrbuf, 0, माप(priv->wrbuf));
			priv->wrfilled = 0;
			priv->wrsent = 0;
		पूर्ण
	पूर्ण

निकास:
	spin_unlock_irqrestore(&priv->lock, flags);
	अगर (!resubmitted)
		set_bit(0, &port->ग_लिखो_urbs_मुक्त);
	usb_serial_port_softपूर्णांक(port);
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
