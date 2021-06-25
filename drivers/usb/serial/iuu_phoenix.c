<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Infinity Unlimited USB Phoenix driver
 *
 * Copyright (C) 2010 James Courtier-Dutton (James@superbug.co.uk)

 * Copyright (C) 2007 Alain Degreffe (eczema@ecze.com)
 *
 * Original code taken from iuutool (Copyright (C) 2006 Juan Carlos Borrथतँs)
 *
 *  And tested with help of WB Electronics
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश "iuu_phoenix.h"
#समावेश <linux/अक्रमom.h>

#घोषणा DRIVER_DESC "Infinity USB Unlimited Phoenix driver"

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणुUSB_DEVICE(IUU_USB_VENDOR_ID, IUU_USB_PRODUCT_ID)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* turbo parameter */
अटल पूर्णांक boost = 100;
अटल पूर्णांक घड़ीmode = 1;
अटल पूर्णांक cdmode = 1;
अटल पूर्णांक iuu_cardin;
अटल पूर्णांक iuu_carकरोut;
अटल bool xmas;
अटल पूर्णांक vcc_शेष = 5;

अटल पूर्णांक iuu_create_sysfs_attrs(काष्ठा usb_serial_port *port);
अटल पूर्णांक iuu_हटाओ_sysfs_attrs(काष्ठा usb_serial_port *port);
अटल व्योम पढ़ो_rxcmd_callback(काष्ठा urb *urb);

काष्ठा iuu_निजी अणु
	spinlock_t lock;	/* store irq state */
	u8 line_status;
	पूर्णांक tiostatus;		/* store IUART SIGNAL क्रम tiocmget call */
	u8 reset;		/* अगर 1 reset is needed */
	पूर्णांक poll;		/* number of poll */
	u8 *ग_लिखोbuf;		/* buffer क्रम writing to device */
	पूर्णांक ग_लिखोlen;		/* num of byte to ग_लिखो to device */
	u8 *buf;		/* used क्रम initialize speed */
	u8 len;
	पूर्णांक vcc;		/* vcc (either 3 or 5 V) */
	u32 boost;
	u32 clk;
पूर्ण;

अटल पूर्णांक iuu_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा iuu_निजी *priv;
	पूर्णांक ret;

	priv = kzalloc(माप(काष्ठा iuu_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->buf = kzalloc(256, GFP_KERNEL);
	अगर (!priv->buf) अणु
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	priv->ग_लिखोbuf = kzalloc(256, GFP_KERNEL);
	अगर (!priv->ग_लिखोbuf) अणु
		kमुक्त(priv->buf);
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	priv->vcc = vcc_शेष;
	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	ret = iuu_create_sysfs_attrs(port);
	अगर (ret) अणु
		kमुक्त(priv->ग_लिखोbuf);
		kमुक्त(priv->buf);
		kमुक्त(priv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iuu_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);

	iuu_हटाओ_sysfs_attrs(port);
	kमुक्त(priv->ग_लिखोbuf);
	kमुक्त(priv->buf);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक iuu_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	/* FIXME: locking on tiomstatus */
	dev_dbg(&port->dev, "%s msg : SET = 0x%04x, CLEAR = 0x%04x\n",
		__func__, set, clear);

	spin_lock_irqsave(&priv->lock, flags);

	अगर ((set & TIOCM_RTS) && !(priv->tiostatus == TIOCM_RTS)) अणु
		dev_dbg(&port->dev, "%s TIOCMSET RESET called !!!\n", __func__);
		priv->reset = 1;
	पूर्ण
	अगर (set & TIOCM_RTS)
		priv->tiostatus = TIOCM_RTS;

	spin_unlock_irqrestore(&priv->lock, flags);
	वापस 0;
पूर्ण

/* This is used to provide a carrier detect mechanism
 * When a card is present, the response is 0x00
 * When no card , the पढ़ोer respond with TIOCM_CD
 * This is known as CD स्वतःdetect mechanism
 */
अटल पूर्णांक iuu_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&priv->lock, flags);
	rc = priv->tiostatus;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस rc;
पूर्ण

अटल व्योम iuu_rxcmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&port->dev, "%s - status = %d\n", __func__, status);
		/* error stop all */
		वापस;
	पूर्ण


	स_रखो(port->ग_लिखो_urb->transfer_buffer, IUU_UART_RX, 1);
	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 1,
			  पढ़ो_rxcmd_callback, port);
	usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक iuu_reset(काष्ठा usb_serial_port *port, u8 wt)
अणु
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक result;
	अक्षर *buf_ptr = port->ग_लिखो_urb->transfer_buffer;

	/* Prepare the reset sequence */

	*buf_ptr++ = IUU_RST_SET;
	*buf_ptr++ = IUU_DELAY_MS;
	*buf_ptr++ = wt;
	*buf_ptr = IUU_RST_CLEAR;

	/* send the sequence */

	usb_fill_bulk_urb(port->ग_लिखो_urb,
			  port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 4, iuu_rxcmd, port);
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	priv->reset = 0;
	वापस result;
पूर्ण

/* Status Function
 * Return value is
 * 0x00 = no card
 * 0x01 = smartcard
 * 0x02 = sim card
 */
अटल व्योम iuu_update_status_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	u8 *st;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&port->dev, "%s - status = %d\n", __func__, status);
		/* error stop all */
		वापस;
	पूर्ण

	st = urb->transfer_buffer;
	dev_dbg(&port->dev, "%s - enter\n", __func__);
	अगर (urb->actual_length == 1) अणु
		चयन (st[0]) अणु
		हाल 0x1:
			priv->tiostatus = iuu_carकरोut;
			अवरोध;
		हाल 0x0:
			priv->tiostatus = iuu_cardin;
			अवरोध;
		शेष:
			priv->tiostatus = iuu_cardin;
		पूर्ण
	पूर्ण
	iuu_rxcmd(urb);
पूर्ण

अटल व्योम iuu_status_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;

	dev_dbg(&port->dev, "%s - status = %d\n", __func__, status);
	usb_fill_bulk_urb(port->पढ़ो_urb, port->serial->dev,
			  usb_rcvbulkpipe(port->serial->dev,
					  port->bulk_in_endpoपूर्णांकAddress),
			  port->पढ़ो_urb->transfer_buffer, 256,
			  iuu_update_status_callback, port);
	usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक iuu_status(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक result;

	स_रखो(port->ग_लिखो_urb->transfer_buffer, IUU_GET_STATE_REGISTER, 1);
	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 1,
			  iuu_status_callback, port);
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	वापस result;

पूर्ण

अटल पूर्णांक bulk_immediate(काष्ठा usb_serial_port *port, u8 *buf, u8 count)
अणु
	पूर्णांक status;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक actual = 0;

	/* send the data out the bulk port */

	status =
	    usb_bulk_msg(serial->dev,
			 usb_sndbulkpipe(serial->dev,
					 port->bulk_out_endpoपूर्णांकAddress), buf,
			 count, &actual, 1000);

	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - error = %2x\n", __func__, status);
	अन्यथा
		dev_dbg(&port->dev, "%s - write OK !\n", __func__);
	वापस status;
पूर्ण

अटल पूर्णांक पढ़ो_immediate(काष्ठा usb_serial_port *port, u8 *buf, u8 count)
अणु
	पूर्णांक status;
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक actual = 0;

	/* send the data out the bulk port */
	status =
	    usb_bulk_msg(serial->dev,
			 usb_rcvbulkpipe(serial->dev,
					 port->bulk_in_endpoपूर्णांकAddress), buf,
			 count, &actual, 1000);

	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - error = %2x\n", __func__, status);
	अन्यथा
		dev_dbg(&port->dev, "%s - read OK !\n", __func__);
	वापस status;
पूर्ण

अटल पूर्णांक iuu_led(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक R,
		   अचिन्हित पूर्णांक G, अचिन्हित पूर्णांक B, u8 f)
अणु
	पूर्णांक status;
	u8 *buf;
	buf = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = IUU_SET_LED;
	buf[1] = R & 0xFF;
	buf[2] = (R >> 8) & 0xFF;
	buf[3] = G & 0xFF;
	buf[4] = (G >> 8) & 0xFF;
	buf[5] = B & 0xFF;
	buf[6] = (B >> 8) & 0xFF;
	buf[7] = f;
	status = bulk_immediate(port, buf, 8);
	kमुक्त(buf);
	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - led error status = %2x\n", __func__, status);
	अन्यथा
		dev_dbg(&port->dev, "%s - led OK !\n", __func__);
	वापस IUU_OPERATION_OK;
पूर्ण

अटल व्योम iuu_rgbf_fill_buffer(u8 *buf, u8 r1, u8 r2, u8 g1, u8 g2, u8 b1,
				 u8 b2, u8 freq)
अणु
	*buf++ = IUU_SET_LED;
	*buf++ = r1;
	*buf++ = r2;
	*buf++ = g1;
	*buf++ = g2;
	*buf++ = b1;
	*buf++ = b2;
	*buf = freq;
पूर्ण

अटल व्योम iuu_led_activity_on(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अक्षर *buf_ptr = port->ग_लिखो_urb->transfer_buffer;

	अगर (xmas) अणु
		buf_ptr[0] = IUU_SET_LED;
		get_अक्रमom_bytes(buf_ptr + 1, 6);
		buf_ptr[7] = 1;
	पूर्ण अन्यथा अणु
		iuu_rgbf_fill_buffer(buf_ptr, 255, 255, 0, 0, 0, 0, 255);
	पूर्ण

	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 8 ,
			  iuu_rxcmd, port);
	usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
पूर्ण

अटल व्योम iuu_led_activity_off(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अक्षर *buf_ptr = port->ग_लिखो_urb->transfer_buffer;

	अगर (xmas) अणु
		iuu_rxcmd(urb);
		वापस;
	पूर्ण

	iuu_rgbf_fill_buffer(buf_ptr, 0, 0, 255, 255, 0, 0, 255);

	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 8 ,
			  iuu_rxcmd, port);
	usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
पूर्ण



अटल पूर्णांक iuu_clk(काष्ठा usb_serial_port *port, पूर्णांक dwFrq)
अणु
	पूर्णांक status;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक Count = 0;
	u8 FrqGenAdr = 0x69;
	u8 DIV = 0;		/* 8bit */
	u8 XDRV = 0;		/* 8bit */
	u8 PUMP = 0;		/* 3bit */
	u8 PBmsb = 0;		/* 2bit */
	u8 PBlsb = 0;		/* 8bit */
	u8 PO = 0;		/* 1bit */
	u8 Q = 0;		/* 7bit */
	/* 24bit = 3bytes */
	अचिन्हित पूर्णांक P = 0;
	अचिन्हित पूर्णांक P2 = 0;
	पूर्णांक frq = (पूर्णांक)dwFrq;

	अगर (frq == 0) अणु
		priv->buf[Count++] = IUU_UART_WRITE_I2C;
		priv->buf[Count++] = FrqGenAdr << 1;
		priv->buf[Count++] = 0x09;
		priv->buf[Count++] = 0x00;

		status = bulk_immediate(port, (u8 *) priv->buf, Count);
		अगर (status != 0) अणु
			dev_dbg(&port->dev, "%s - write error\n", __func__);
			वापस status;
		पूर्ण
	पूर्ण अन्यथा अगर (frq == 3579000) अणु
		DIV = 100;
		P = 1193;
		Q = 40;
		XDRV = 0;
	पूर्ण अन्यथा अगर (frq == 3680000) अणु
		DIV = 105;
		P = 161;
		Q = 5;
		XDRV = 0;
	पूर्ण अन्यथा अगर (frq == 6000000) अणु
		DIV = 66;
		P = 66;
		Q = 2;
		XDRV = 0x28;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक result = 0;
		अचिन्हित पूर्णांक पंचांगp = 0;
		अचिन्हित पूर्णांक check;
		अचिन्हित पूर्णांक check2;
		अक्षर found = 0x00;
		अचिन्हित पूर्णांक lQ = 2;
		अचिन्हित पूर्णांक lP = 2055;
		अचिन्हित पूर्णांक lDiv = 4;

		क्रम (lQ = 2; lQ <= 47 && !found; lQ++)
			क्रम (lP = 2055; lP >= 8 && !found; lP--)
				क्रम (lDiv = 4; lDiv <= 127 && !found; lDiv++) अणु
					पंचांगp = (12000000 / lDiv) * (lP / lQ);
					अगर (असल((पूर्णांक)(पंचांगp - frq)) <
					    असल((पूर्णांक)(frq - result))) अणु
						check2 = (12000000 / lQ);
						अगर (check2 < 250000)
							जारी;
						check = (12000000 / lQ) * lP;
						अगर (check > 400000000)
							जारी;
						अगर (check < 100000000)
							जारी;
						अगर (lDiv < 4 || lDiv > 127)
							जारी;
						result = पंचांगp;
						P = lP;
						DIV = lDiv;
						Q = lQ;
						अगर (result == frq)
							found = 0x01;
					पूर्ण
				पूर्ण
	पूर्ण
	P2 = ((P - PO) / 2) - 4;
	PUMP = 0x04;
	PBmsb = (P2 >> 8 & 0x03);
	PBlsb = P2 & 0xFF;
	PO = (P >> 10) & 0x01;
	Q = Q - 2;

	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/* 0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x09;
	priv->buf[Count++] = 0x20;	/* Adr = 0x09 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/* 0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x0C;
	priv->buf[Count++] = DIV;	/* Adr = 0x0C */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/* 0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x12;
	priv->buf[Count++] = XDRV;	/* Adr = 0x12 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x13;
	priv->buf[Count++] = 0x6B;	/* Adr = 0x13 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x40;
	priv->buf[Count++] = (0xC0 | ((PUMP & 0x07) << 2)) |
			     (PBmsb & 0x03);	/* Adr = 0x40 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x41;
	priv->buf[Count++] = PBlsb;	/* Adr = 0x41 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x42;
	priv->buf[Count++] = Q | (((PO & 0x01) << 7));	/* Adr = 0x42 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x44;
	priv->buf[Count++] = (अक्षर)0xFF;	/* Adr = 0x44 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x45;
	priv->buf[Count++] = (अक्षर)0xFE;	/* Adr = 0x45 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x46;
	priv->buf[Count++] = 0x7F;	/* Adr = 0x46 */
	priv->buf[Count++] = IUU_UART_WRITE_I2C;	/*  0x4C */
	priv->buf[Count++] = FrqGenAdr << 1;
	priv->buf[Count++] = 0x47;
	priv->buf[Count++] = (अक्षर)0x84;	/* Adr = 0x47 */

	status = bulk_immediate(port, (u8 *) priv->buf, Count);
	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - write error\n", __func__);
	वापस status;
पूर्ण

अटल पूर्णांक iuu_uart_flush(काष्ठा usb_serial_port *port)
अणु
	काष्ठा device *dev = &port->dev;
	पूर्णांक i;
	पूर्णांक status;
	u8 *rxcmd;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);

	अगर (iuu_led(port, 0xF000, 0, 0, 0xFF) < 0)
		वापस -EIO;

	rxcmd = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!rxcmd)
		वापस -ENOMEM;

	rxcmd[0] = IUU_UART_RX;

	क्रम (i = 0; i < 2; i++) अणु
		status = bulk_immediate(port, rxcmd, 1);
		अगर (status != IUU_OPERATION_OK) अणु
			dev_dbg(dev, "%s - uart_flush_write error\n", __func__);
			जाओ out_मुक्त;
		पूर्ण

		status = पढ़ो_immediate(port, &priv->len, 1);
		अगर (status != IUU_OPERATION_OK) अणु
			dev_dbg(dev, "%s - uart_flush_read error\n", __func__);
			जाओ out_मुक्त;
		पूर्ण

		अगर (priv->len > 0) अणु
			dev_dbg(dev, "%s - uart_flush datalen is : %i\n", __func__, priv->len);
			status = पढ़ो_immediate(port, priv->buf, priv->len);
			अगर (status != IUU_OPERATION_OK) अणु
				dev_dbg(dev, "%s - uart_flush_read error\n", __func__);
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_dbg(dev, "%s - uart_flush_read OK!\n", __func__);
	iuu_led(port, 0, 0xF000, 0, 0xFF);

out_मुक्त:
	kमुक्त(rxcmd);

	वापस status;
पूर्ण

अटल व्योम पढ़ो_buf_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		अगर (status == -EPROTO) अणु
			/* reschedule needed */
		पूर्ण
		वापस;
	पूर्ण

	dev_dbg(&port->dev, "%s - %i chars to write\n", __func__, urb->actual_length);

	अगर (urb->actual_length) अणु
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण
	iuu_led_activity_on(urb);
पूर्ण

अटल पूर्णांक iuu_bulk_ग_लिखो(काष्ठा usb_serial_port *port)
अणु
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक buf_len;
	अक्षर *buf_ptr = port->ग_लिखो_urb->transfer_buffer;

	spin_lock_irqsave(&priv->lock, flags);
	*buf_ptr++ = IUU_UART_ESC;
	*buf_ptr++ = IUU_UART_TX;
	*buf_ptr++ = priv->ग_लिखोlen;

	स_नकल(buf_ptr, priv->ग_लिखोbuf, priv->ग_लिखोlen);
	buf_len = priv->ग_लिखोlen;
	priv->ग_लिखोlen = 0;
	spin_unlock_irqrestore(&priv->lock, flags);
	dev_dbg(&port->dev, "%s - writing %i chars : %*ph\n", __func__,
		buf_len, buf_len, buf_ptr);
	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, buf_len + 3,
			  iuu_rxcmd, port);
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	usb_serial_port_softपूर्णांक(port);
	वापस result;
पूर्ण

अटल पूर्णांक iuu_पढ़ो_buf(काष्ठा usb_serial_port *port, पूर्णांक len)
अणु
	पूर्णांक result;

	usb_fill_bulk_urb(port->पढ़ो_urb, port->serial->dev,
			  usb_rcvbulkpipe(port->serial->dev,
					  port->bulk_in_endpoपूर्णांकAddress),
			  port->पढ़ो_urb->transfer_buffer, len,
			  पढ़ो_buf_callback, port);
	result = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
	वापस result;
पूर्ण

अटल व्योम iuu_uart_पढ़ो_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;
	पूर्णांक len = 0;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	priv->poll++;

	अगर (status) अणु
		dev_dbg(&port->dev, "%s - status = %d\n", __func__, status);
		/* error stop all */
		वापस;
	पूर्ण

	अगर (urb->actual_length == 1)
		len = (पूर्णांक) data[0];

	अगर (urb->actual_length > 1) अणु
		dev_dbg(&port->dev, "%s - urb->actual_length = %i\n", __func__,
		    urb->actual_length);
		वापस;
	पूर्ण
	/* अगर len > 0 call पढ़ोbuf */

	अगर (len > 0) अणु
		dev_dbg(&port->dev, "%s - call read buf - len to read is %i\n",
			__func__, len);
		status = iuu_पढ़ो_buf(port, len);
		वापस;
	पूर्ण
	/* need to update status  ? */
	अगर (priv->poll > 99) अणु
		status = iuu_status(port);
		priv->poll = 0;
		वापस;
	पूर्ण

	/* reset रुकोing ? */

	अगर (priv->reset == 1) अणु
		status = iuu_reset(port, 0xC);
		वापस;
	पूर्ण
	/* Writebuf is रुकोing */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->ग_लिखोlen > 0) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		status = iuu_bulk_ग_लिखो(port);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);
	/* अगर nothing to ग_लिखो call again rxcmd */
	dev_dbg(&port->dev, "%s - rxcmd recall\n", __func__);
	iuu_led_activity_off(urb);
पूर्ण

अटल पूर्णांक iuu_uart_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			  स्थिर u8 *buf, पूर्णांक count)
अणु
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	count = min(count, 256 - priv->ग_लिखोlen);
	अगर (count == 0)
		जाओ out;

	/* fill the buffer */
	स_नकल(priv->ग_लिखोbuf + priv->ग_लिखोlen, buf, count);
	priv->ग_लिखोlen += count;
out:
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस count;
पूर्ण

अटल व्योम पढ़ो_rxcmd_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक result;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		/* error stop all */
		वापस;
	पूर्ण

	usb_fill_bulk_urb(port->पढ़ो_urb, port->serial->dev,
			  usb_rcvbulkpipe(port->serial->dev,
					  port->bulk_in_endpoपूर्णांकAddress),
			  port->पढ़ो_urb->transfer_buffer, 256,
			  iuu_uart_पढ़ो_callback, port);
	result = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
	dev_dbg(&port->dev, "%s - submit result = %d\n", __func__, result);
पूर्ण

अटल पूर्णांक iuu_uart_on(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	u8 *buf;

	buf = kदो_स्मृति(4, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = IUU_UART_ENABLE;
	buf[1] = (u8) ((IUU_BAUD_9600 >> 8) & 0x00FF);
	buf[2] = (u8) (0x00FF & IUU_BAUD_9600);
	buf[3] = (u8) (0x0F0 & IUU_ONE_STOP_BIT) | (0x07 & IUU_PARITY_EVEN);

	status = bulk_immediate(port, buf, 4);
	अगर (status != IUU_OPERATION_OK) अणु
		dev_dbg(&port->dev, "%s - uart_on error\n", __func__);
		जाओ uart_enable_failed;
	पूर्ण
	/*  iuu_reset() the card after iuu_uart_on() */
	status = iuu_uart_flush(port);
	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - uart_flush error\n", __func__);
uart_enable_failed:
	kमुक्त(buf);
	वापस status;
पूर्ण

/*  Disables the IUU UART (a.k.a. the Phoenix व्योमerface) */
अटल पूर्णांक iuu_uart_off(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	u8 *buf;
	buf = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	buf[0] = IUU_UART_DISABLE;

	status = bulk_immediate(port, buf, 1);
	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - uart_off error\n", __func__);

	kमुक्त(buf);
	वापस status;
पूर्ण

अटल पूर्णांक iuu_uart_baud(काष्ठा usb_serial_port *port, u32 baud_base,
			 u32 *actual, u8 parity)
अणु
	पूर्णांक status;
	u32 baud;
	u8 *dataout;
	u8 DataCount = 0;
	u8 T1Frekvens = 0;
	u8 T1reload = 0;
	अचिन्हित पूर्णांक T1FrekvensHZ = 0;

	dev_dbg(&port->dev, "%s - enter baud_base=%d\n", __func__, baud_base);
	dataout = kदो_स्मृति(5, GFP_KERNEL);

	अगर (!dataout)
		वापस -ENOMEM;
	/*baud = (((priv->clk / 35) * baud_base) / 100000); */
	baud = baud_base;

	अगर (baud < 1200 || baud > 230400) अणु
		kमुक्त(dataout);
		वापस IUU_INVALID_PARAMETER;
	पूर्ण
	अगर (baud > 977) अणु
		T1Frekvens = 3;
		T1FrekvensHZ = 500000;
	पूर्ण

	अगर (baud > 3906) अणु
		T1Frekvens = 2;
		T1FrekvensHZ = 2000000;
	पूर्ण

	अगर (baud > 11718) अणु
		T1Frekvens = 1;
		T1FrekvensHZ = 6000000;
	पूर्ण

	अगर (baud > 46875) अणु
		T1Frekvens = 0;
		T1FrekvensHZ = 24000000;
	पूर्ण

	T1reload = 256 - (u8) (T1FrekvensHZ / (baud * 2));

	/*  magic number here:  ENTER_FIRMWARE_UPDATE; */
	dataout[DataCount++] = IUU_UART_ESC;
	/*  magic number here:  CHANGE_BAUD; */
	dataout[DataCount++] = IUU_UART_CHANGE;
	dataout[DataCount++] = T1Frekvens;
	dataout[DataCount++] = T1reload;

	*actual = (T1FrekvensHZ / (256 - T1reload)) / 2;

	चयन (parity & 0x0F) अणु
	हाल IUU_PARITY_NONE:
		dataout[DataCount++] = 0x00;
		अवरोध;
	हाल IUU_PARITY_EVEN:
		dataout[DataCount++] = 0x01;
		अवरोध;
	हाल IUU_PARITY_ODD:
		dataout[DataCount++] = 0x02;
		अवरोध;
	हाल IUU_PARITY_MARK:
		dataout[DataCount++] = 0x03;
		अवरोध;
	हाल IUU_PARITY_SPACE:
		dataout[DataCount++] = 0x04;
		अवरोध;
	शेष:
		kमुक्त(dataout);
		वापस IUU_INVALID_PARAMETER;
	पूर्ण

	चयन (parity & 0xF0) अणु
	हाल IUU_ONE_STOP_BIT:
		dataout[DataCount - 1] |= IUU_ONE_STOP_BIT;
		अवरोध;

	हाल IUU_TWO_STOP_BITS:
		dataout[DataCount - 1] |= IUU_TWO_STOP_BITS;
		अवरोध;
	शेष:
		kमुक्त(dataout);
		वापस IUU_INVALID_PARAMETER;
	पूर्ण

	status = bulk_immediate(port, dataout, DataCount);
	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - uart_off error\n", __func__);
	kमुक्त(dataout);
	वापस status;
पूर्ण

अटल व्योम iuu_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	स्थिर u32 supported_mask = CMSPAR|PARENB|PARODD;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक cflag = tty->termios.c_cflag;
	पूर्णांक status;
	u32 actual;
	u32 parity;
	पूर्णांक csize = CS7;
	पूर्णांक baud;
	u32 newval = cflag & supported_mask;

	/* Just use the ospeed. ispeed should be the same. */
	baud = tty->termios.c_ospeed;

	dev_dbg(&port->dev, "%s - enter c_ospeed or baud=%d\n", __func__, baud);

	/* compute the parity parameter */
	parity = 0;
	अगर (cflag & CMSPAR) अणु	/* Using mark space */
		अगर (cflag & PARODD)
			parity |= IUU_PARITY_SPACE;
		अन्यथा
			parity |= IUU_PARITY_MARK;
	पूर्ण अन्यथा अगर (!(cflag & PARENB)) अणु
		parity |= IUU_PARITY_NONE;
		csize = CS8;
	पूर्ण अन्यथा अगर (cflag & PARODD)
		parity |= IUU_PARITY_ODD;
	अन्यथा
		parity |= IUU_PARITY_EVEN;

	parity |= (cflag & CSTOPB ? IUU_TWO_STOP_BITS : IUU_ONE_STOP_BIT);

	/* set it */
	status = iuu_uart_baud(port,
			baud * priv->boost / 100,
			&actual, parity);

	/* set the termios value to the real one, so the user now what has
	 * changed. We support few fields so its easies to copy the old hw
	 * settings back over and then adjust them
	 */
	अगर (old_termios)
		tty_termios_copy_hw(&tty->termios, old_termios);
	अगर (status != 0)	/* Set failed - वापस old bits */
		वापस;
	/* Re-encode speed, parity and csize */
	tty_encode_baud_rate(tty, baud, baud);
	tty->termios.c_cflag &= ~(supported_mask|CSIZE);
	tty->termios.c_cflag |= newval | csize;
पूर्ण

अटल व्योम iuu_बंद(काष्ठा usb_serial_port *port)
अणु
	/* iuu_led (port,255,0,0,0); */

	iuu_uart_off(port);

	usb_समाप्त_urb(port->ग_लिखो_urb);
	usb_समाप्त_urb(port->पढ़ो_urb);

	iuu_led(port, 0, 0, 0xF000, 0xFF);
पूर्ण

अटल व्योम iuu_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	tty->termios.c_cflag = B9600 | CS8 | CSTOPB | CREAD | PARENB | CLOCAL;
	tty->termios.c_ispeed = 9600;
	tty->termios.c_ospeed = 9600;
	tty->termios.c_lflag = 0;
	tty->termios.c_oflag = 0;
	tty->termios.c_अगरlag = 0;
पूर्ण

अटल पूर्णांक iuu_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा device *dev = &port->dev;
	पूर्णांक result;
	पूर्णांक baud;
	u32 actual;
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);

	baud = tty->termios.c_ospeed;

	dev_dbg(dev, "%s - baud %d\n", __func__, baud);
	usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);

	priv->poll = 0;

#घोषणा SOUP(a, b, c, d)  करो अणु \
	result = usb_control_msg(port->serial->dev,	\
				usb_sndctrlpipe(port->serial->dev, 0),	\
				b, a, c, d, शून्य, 0, 1000); \
	dev_dbg(dev, "0x%x:0x%x:0x%x:0x%x  %d\n", a, b, c, d, result); पूर्ण जबतक (0)

	/*  This is not UART related but IUU USB driver related or something */
	/*  like that. Basically no IUU will accept any commands from the USB */
	/*  host unless it has received the following message */
	/* प्र_लिखो(buf ,"%c%c%c%c",0x03,0x02,0x02,0x0); */

	SOUP(0x03, 0x02, 0x02, 0x0);

	iuu_led(port, 0xF000, 0xF000, 0, 0xFF);
	iuu_uart_on(port);
	अगर (boost < 100)
		boost = 100;
	priv->boost = boost;
	चयन (घड़ीmode) अणु
	हाल 2:		/*  3.680 Mhz */
		priv->clk = IUU_CLK_3680000;
		iuu_clk(port, IUU_CLK_3680000 * boost / 100);
		result =
		    iuu_uart_baud(port, baud * boost / 100, &actual,
				  IUU_PARITY_EVEN);
		अवरोध;
	हाल 3:		/*  6.00 Mhz */
		iuu_clk(port, IUU_CLK_6000000 * boost / 100);
		priv->clk = IUU_CLK_6000000;
		/* Ratio of 6000000 to 3500000 क्रम baud 9600 */
		result =
		    iuu_uart_baud(port, 16457 * boost / 100, &actual,
				  IUU_PARITY_EVEN);
		अवरोध;
	शेष:		/*  3.579 Mhz */
		iuu_clk(port, IUU_CLK_3579000 * boost / 100);
		priv->clk = IUU_CLK_3579000;
		result =
		    iuu_uart_baud(port, baud * boost / 100, &actual,
				  IUU_PARITY_EVEN);
	पूर्ण

	/* set the cardin carकरोut संकेतs */
	चयन (cdmode) अणु
	हाल 0:
		iuu_cardin = 0;
		iuu_carकरोut = 0;
		अवरोध;
	हाल 1:
		iuu_cardin = TIOCM_CD;
		iuu_carकरोut =  0;
		अवरोध;
	हाल 2:
		iuu_cardin = 0;
		iuu_carकरोut = TIOCM_CD;
		अवरोध;
	हाल 3:
		iuu_cardin = TIOCM_DSR;
		iuu_carकरोut = 0;
		अवरोध;
	हाल 4:
		iuu_cardin = 0;
		iuu_carकरोut = TIOCM_DSR;
		अवरोध;
	हाल 5:
		iuu_cardin = TIOCM_CTS;
		iuu_carकरोut = 0;
		अवरोध;
	हाल 6:
		iuu_cardin = 0;
		iuu_carकरोut = TIOCM_CTS;
		अवरोध;
	हाल 7:
		iuu_cardin = TIOCM_RNG;
		iuu_carकरोut = 0;
		अवरोध;
	हाल 8:
		iuu_cardin = 0;
		iuu_carकरोut = TIOCM_RNG;
	पूर्ण

	iuu_uart_flush(port);

	dev_dbg(dev, "%s - initialization done\n", __func__);

	स_रखो(port->ग_लिखो_urb->transfer_buffer, IUU_UART_RX, 1);
	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpoपूर्णांकAddress),
			  port->ग_लिखो_urb->transfer_buffer, 1,
			  पढ़ो_rxcmd_callback, port);
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_KERNEL);
	अगर (result) अणु
		dev_err(dev, "%s - failed submitting read urb, error %d\n", __func__, result);
		iuu_बंद(port);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s - rxcmd OK\n", __func__);
	पूर्ण

	वापस result;
पूर्ण

/* how to change VCC */
अटल पूर्णांक iuu_vcc_set(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक vcc)
अणु
	पूर्णांक status;
	u8 *buf;

	buf = kदो_स्मृति(5, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = IUU_SET_VCC;
	buf[1] = vcc & 0xFF;
	buf[2] = (vcc >> 8) & 0xFF;
	buf[3] = (vcc >> 16) & 0xFF;
	buf[4] = (vcc >> 24) & 0xFF;

	status = bulk_immediate(port, buf, 5);
	kमुक्त(buf);

	अगर (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - vcc error status = %2x\n", __func__, status);
	अन्यथा
		dev_dbg(&port->dev, "%s - vcc OK !\n", __func__);

	वापस status;
पूर्ण

/*
 * Sysfs Attributes
 */

अटल sमाप_प्रकार vcc_mode_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);

	वापस प्र_लिखो(buf, "%d\n", priv->vcc);
पूर्ण

अटल sमाप_प्रकार vcc_mode_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा iuu_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ v;

	अगर (kम_से_अदीर्घ(buf, 10, &v)) अणु
		dev_err(dev, "%s - vcc_mode: %s is not a unsigned long\n",
				__func__, buf);
		जाओ fail_store_vcc_mode;
	पूर्ण

	dev_dbg(dev, "%s: setting vcc_mode = %ld\n", __func__, v);

	अगर ((v != 3) && (v != 5)) अणु
		dev_err(dev, "%s - vcc_mode %ld is invalid\n", __func__, v);
	पूर्ण अन्यथा अणु
		iuu_vcc_set(port, v);
		priv->vcc = v;
	पूर्ण
fail_store_vcc_mode:
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(vcc_mode);

अटल पूर्णांक iuu_create_sysfs_attrs(काष्ठा usb_serial_port *port)
अणु
	वापस device_create_file(&port->dev, &dev_attr_vcc_mode);
पूर्ण

अटल पूर्णांक iuu_हटाओ_sysfs_attrs(काष्ठा usb_serial_port *port)
अणु
	device_हटाओ_file(&port->dev, &dev_attr_vcc_mode);
	वापस 0;
पूर्ण

/*
 * End Sysfs Attributes
 */

अटल काष्ठा usb_serial_driver iuu_device = अणु
	.driver = अणु
		   .owner = THIS_MODULE,
		   .name = "iuu_phoenix",
		   पूर्ण,
	.id_table = id_table,
	.num_ports = 1,
	.num_bulk_in = 1,
	.num_bulk_out = 1,
	.bulk_in_size = 512,
	.bulk_out_size = 512,
	.खोलो = iuu_खोलो,
	.बंद = iuu_बंद,
	.ग_लिखो = iuu_uart_ग_लिखो,
	.पढ़ो_bulk_callback = iuu_uart_पढ़ो_callback,
	.tiocmget = iuu_tiocmget,
	.tiocmset = iuu_tiocmset,
	.set_termios = iuu_set_termios,
	.init_termios = iuu_init_termios,
	.port_probe = iuu_port_probe,
	.port_हटाओ = iuu_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&iuu_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR("Alain Degreffe eczema@ecze.com");

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(xmas, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(xmas, "Xmas colors enabled or not");

module_param(boost, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(boost, "Card overclock boost (in percent 100-500)");

module_param(घड़ीmode, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(घड़ीmode, "Card clock mode (1=3.579 MHz, 2=3.680 MHz, "
		"3=6 Mhz)");

module_param(cdmode, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(cdmode, "Card detect mode (0=none, 1=CD, 2=!CD, 3=DSR, "
		 "4=!DSR, 5=CTS, 6=!CTS, 7=RING, 8=!RING)");

module_param(vcc_शेष, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(vcc_शेष, "Set default VCC (either 3 for 3.3V or 5 "
		"for 5V). Default to 5.");
