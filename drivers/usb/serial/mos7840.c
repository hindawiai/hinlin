<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Clean ups from Moschip version and a few ioctl implementations by:
 *	Paul B Schroeder <pschroeder "at" uplogix "dot" com>
 *
 * Originally based on drivers/usb/serial/io_edgeport.c which is:
 *      Copyright (C) 2000 Inside Out Networks, All rights reserved.
 *      Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/serial.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>

#घोषणा DRIVER_DESC "Moschip 7840/7820 USB Serial Driver"

/*
 * 16C50 UART रेजिस्टर defines
 */

#घोषणा LCR_BITS_5             0x00	/* 5 bits/अक्षर */
#घोषणा LCR_BITS_6             0x01	/* 6 bits/अक्षर */
#घोषणा LCR_BITS_7             0x02	/* 7 bits/अक्षर */
#घोषणा LCR_BITS_8             0x03	/* 8 bits/अक्षर */
#घोषणा LCR_BITS_MASK          0x03	/* Mask क्रम bits/अक्षर field */

#घोषणा LCR_STOP_1             0x00	/* 1 stop bit */
#घोषणा LCR_STOP_1_5           0x04	/* 1.5 stop bits (अगर 5   bits/अक्षर) */
#घोषणा LCR_STOP_2             0x04	/* 2 stop bits   (अगर 6-8 bits/अक्षर) */
#घोषणा LCR_STOP_MASK          0x04	/* Mask क्रम stop bits field */

#घोषणा LCR_PAR_NONE           0x00	/* No parity */
#घोषणा LCR_PAR_ODD            0x08	/* Odd parity */
#घोषणा LCR_PAR_EVEN           0x18	/* Even parity */
#घोषणा LCR_PAR_MARK           0x28	/* Force parity bit to 1 */
#घोषणा LCR_PAR_SPACE          0x38	/* Force parity bit to 0 */
#घोषणा LCR_PAR_MASK           0x38	/* Mask क्रम parity field */

#घोषणा LCR_SET_BREAK          0x40	/* Set Break condition */
#घोषणा LCR_DL_ENABLE          0x80	/* Enable access to भागisor latch */

#घोषणा MCR_DTR                0x01	/* Assert DTR */
#घोषणा MCR_RTS                0x02	/* Assert RTS */
#घोषणा MCR_OUT1               0x04	/* Loopback only: Sets state of RI */
#घोषणा MCR_MASTER_IE          0x08	/* Enable पूर्णांकerrupt outमाला_दो */
#घोषणा MCR_LOOPBACK           0x10	/* Set पूर्णांकernal (digital) loopback mode */
#घोषणा MCR_XON_ANY            0x20	/* Enable any अक्षर to निकास XOFF mode */

#घोषणा MOS7840_MSR_CTS        0x10	/* Current state of CTS */
#घोषणा MOS7840_MSR_DSR        0x20	/* Current state of DSR */
#घोषणा MOS7840_MSR_RI         0x40	/* Current state of RI */
#घोषणा MOS7840_MSR_CD         0x80	/* Current state of CD */

/*
 * Defines used क्रम sending commands to port
 */

#घोषणा MOS_WDR_TIMEOUT		5000	/* शेष urb समयout */

#घोषणा MOS_PORT1       0x0200
#घोषणा MOS_PORT2       0x0300
#घोषणा MOS_VENREG      0x0000
#घोषणा MOS_MAX_PORT	0x02
#घोषणा MOS_WRITE       0x0E
#घोषणा MOS_READ        0x0D

/* Requests */
#घोषणा MCS_RD_RTYPE    0xC0
#घोषणा MCS_WR_RTYPE    0x40
#घोषणा MCS_RDREQ       0x0D
#घोषणा MCS_WRREQ       0x0E
#घोषणा MCS_CTRL_TIMEOUT        500
#घोषणा VENDOR_READ_LENGTH      (0x01)

#घोषणा MAX_NAME_LEN    64

#घोषणा ZLP_REG1  0x3A		/* Zero_Flag_Reg1    58 */
#घोषणा ZLP_REG5  0x3E		/* Zero_Flag_Reg5    62 */

/* For higher baud Rates use TIOCEXBAUD */
#घोषणा TIOCEXBAUD     0x5462

/*
 * Venकरोr id and device id defines
 *
 * NOTE: Do not add new defines, add entries directly to the id_table instead.
 */
#घोषणा USB_VENDOR_ID_BANDB              0x0856
#घोषणा BANDB_DEVICE_ID_USO9ML2_2        0xAC22
#घोषणा BANDB_DEVICE_ID_USO9ML2_2P       0xBC00
#घोषणा BANDB_DEVICE_ID_USO9ML2_4        0xAC24
#घोषणा BANDB_DEVICE_ID_USO9ML2_4P       0xBC01
#घोषणा BANDB_DEVICE_ID_US9ML2_2         0xAC29
#घोषणा BANDB_DEVICE_ID_US9ML2_4         0xAC30
#घोषणा BANDB_DEVICE_ID_USPTL4_2         0xAC31
#घोषणा BANDB_DEVICE_ID_USPTL4_4         0xAC32
#घोषणा BANDB_DEVICE_ID_USOPTL4_2        0xAC42
#घोषणा BANDB_DEVICE_ID_USOPTL4_2P       0xBC02
#घोषणा BANDB_DEVICE_ID_USOPTL4_4        0xAC44
#घोषणा BANDB_DEVICE_ID_USOPTL4_4P       0xBC03
#घोषणा BANDB_DEVICE_ID_USOPTL2_4        0xAC24

/* Interrupt Routine Defines    */

#घोषणा SERIAL_IIR_RLS      0x06
#घोषणा SERIAL_IIR_MS       0x00

/*
 *  Emulation of the bit mask on the LINE STATUS REGISTER.
 */
#घोषणा SERIAL_LSR_DR       0x0001
#घोषणा SERIAL_LSR_OE       0x0002
#घोषणा SERIAL_LSR_PE       0x0004
#घोषणा SERIAL_LSR_FE       0x0008
#घोषणा SERIAL_LSR_BI       0x0010

#घोषणा MOS_MSR_DELTA_CTS   0x10
#घोषणा MOS_MSR_DELTA_DSR   0x20
#घोषणा MOS_MSR_DELTA_RI    0x40
#घोषणा MOS_MSR_DELTA_CD    0x80

/* Serial Port रेजिस्टर Address */
#घोषणा INTERRUPT_ENABLE_REGISTER  ((__u16)(0x01))
#घोषणा FIFO_CONTROL_REGISTER      ((__u16)(0x02))
#घोषणा LINE_CONTROL_REGISTER      ((__u16)(0x03))
#घोषणा MODEM_CONTROL_REGISTER     ((__u16)(0x04))
#घोषणा LINE_STATUS_REGISTER       ((__u16)(0x05))
#घोषणा MODEM_STATUS_REGISTER      ((__u16)(0x06))
#घोषणा SCRATCH_PAD_REGISTER       ((__u16)(0x07))
#घोषणा DIVISOR_LATCH_LSB          ((__u16)(0x00))
#घोषणा DIVISOR_LATCH_MSB          ((__u16)(0x01))

#घोषणा CLK_MULTI_REGISTER         ((__u16)(0x02))
#घोषणा CLK_START_VALUE_REGISTER   ((__u16)(0x03))
#घोषणा GPIO_REGISTER              ((__u16)(0x07))

#घोषणा SERIAL_LCR_DLAB            ((__u16)(0x0080))

/*
 * URB POOL related defines
 */
#घोषणा NUM_URBS                        16	/* URB Count */
#घोषणा URB_TRANSFER_BUFFER_SIZE        32	/* URB Size  */

/* LED on/off milliseconds*/
#घोषणा LED_ON_MS	500
#घोषणा LED_OFF_MS	500

क्रमागत mos7840_flag अणु
	MOS7840_FLAG_LED_BUSY,
पूर्ण;

#घोषणा MCS_PORT_MASK	GENMASK(2, 0)
#घोषणा MCS_PORTS(nr)	((nr) & MCS_PORT_MASK)
#घोषणा MCS_LED		BIT(3)

#घोषणा MCS_DEVICE(vid, pid, flags) \
		USB_DEVICE((vid), (pid)), .driver_info = (flags)

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु MCS_DEVICE(0x0557, 0x2011, MCS_PORTS(4)) पूर्ण,	/* ATEN UC2324 */
	अणु MCS_DEVICE(0x0557, 0x7820, MCS_PORTS(2)) पूर्ण,	/* ATEN UC2322 */
	अणु MCS_DEVICE(0x110a, 0x2210, MCS_PORTS(2)) पूर्ण,	/* Moxa UPort 2210 */
	अणु MCS_DEVICE(0x9710, 0x7810, MCS_PORTS(1) | MCS_LED) पूर्ण, /* ASIX MCS7810 */
	अणु MCS_DEVICE(0x9710, 0x7820, MCS_PORTS(2)) पूर्ण,	/* MosChip MCS7820 */
	अणु MCS_DEVICE(0x9710, 0x7840, MCS_PORTS(4)) पूर्ण,	/* MosChip MCS7840 */
	अणु MCS_DEVICE(0x9710, 0x7843, MCS_PORTS(3)) पूर्ण,	/* ASIX MCS7840 3 port */
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USO9ML2_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USO9ML2_2P) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USO9ML2_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USO9ML2_4P) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_US9ML2_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_US9ML2_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USPTL4_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USPTL4_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USOPTL4_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USOPTL4_2P) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USOPTL4_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USOPTL4_4P) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_BANDB, BANDB_DEVICE_ID_USOPTL2_4) पूर्ण,
	अणुपूर्ण			/* terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* This काष्ठाure holds all of the local port inक्रमmation */

काष्ठा moschip_port अणु
	पूर्णांक port_num;		/*Actual port number in the device(1,2,etc) */
	काष्ठा urb *पढ़ो_urb;	/* पढ़ो URB क्रम this port */
	__u8 shaकरोwLCR;		/* last LCR value received */
	__u8 shaकरोwMCR;		/* last MCR value received */
	काष्ठा usb_serial_port *port;	/* loop back to the owner of this object */

	/* Offsets */
	__u8 SpRegOffset;
	__u8 ControlRegOffset;
	__u8 DcrRegOffset;

	spinlock_t pool_lock;
	काष्ठा urb *ग_लिखो_urb_pool[NUM_URBS];
	अक्षर busy[NUM_URBS];
	bool पढ़ो_urb_busy;

	/* For device(s) with LED indicator */
	bool has_led;
	काष्ठा समयr_list led_समयr1;	/* Timer क्रम LED on */
	काष्ठा समयr_list led_समयr2;	/* Timer क्रम LED off */
	काष्ठा urb *led_urb;
	काष्ठा usb_ctrlrequest *led_dr;

	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * mos7840_set_reg_sync
 * 	To set the Control रेजिस्टर by calling usb_fill_control_urb function
 *	by passing usb_sndctrlpipe function as parameter.
 */

अटल पूर्णांक mos7840_set_reg_sync(काष्ठा usb_serial_port *port, __u16 reg,
				__u16 val)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	val = val & 0x00ff;
	dev_dbg(&port->dev, "mos7840_set_reg_sync offset is %x, value %x\n", reg, val);

	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0), MCS_WRREQ,
			       MCS_WR_RTYPE, val, reg, शून्य, 0,
			       MOS_WDR_TIMEOUT);
पूर्ण

/*
 * mos7840_get_reg_sync
 * 	To set the Uart रेजिस्टर by calling usb_fill_control_urb function by
 *	passing usb_rcvctrlpipe function as parameter.
 */

अटल पूर्णांक mos7840_get_reg_sync(काष्ठा usb_serial_port *port, __u16 reg,
				__u16 *val)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	पूर्णांक ret = 0;
	u8 *buf;

	buf = kदो_स्मृति(VENDOR_READ_LENGTH, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), MCS_RDREQ,
			      MCS_RD_RTYPE, 0, reg, buf, VENDOR_READ_LENGTH,
			      MOS_WDR_TIMEOUT);
	अगर (ret < VENDOR_READ_LENGTH) अणु
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण

	*val = buf[0];
	dev_dbg(&port->dev, "%s offset is %x, return val %x\n", __func__, reg, *val);
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * mos7840_set_uart_reg
 *	To set the Uart रेजिस्टर by calling usb_fill_control_urb function by
 *	passing usb_sndctrlpipe function as parameter.
 */

अटल पूर्णांक mos7840_set_uart_reg(काष्ठा usb_serial_port *port, __u16 reg,
				__u16 val)
अणु

	काष्ठा usb_device *dev = port->serial->dev;
	val = val & 0x00ff;
	/* For the UART control रेजिस्टरs, the application number need
	   to be Or'ed */
	अगर (port->serial->num_ports == 2 && port->port_number != 0)
		val |= ((__u16)port->port_number + 2) << 8;
	अन्यथा
		val |= ((__u16)port->port_number + 1) << 8;
	dev_dbg(&port->dev, "%s application number is %x\n", __func__, val);
	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0), MCS_WRREQ,
			       MCS_WR_RTYPE, val, reg, शून्य, 0,
			       MOS_WDR_TIMEOUT);

पूर्ण

/*
 * mos7840_get_uart_reg
 *	To set the Control रेजिस्टर by calling usb_fill_control_urb function
 *	by passing usb_rcvctrlpipe function as parameter.
 */
अटल पूर्णांक mos7840_get_uart_reg(काष्ठा usb_serial_port *port, __u16 reg,
				__u16 *val)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	पूर्णांक ret = 0;
	__u16 Wval;
	u8 *buf;

	buf = kदो_स्मृति(VENDOR_READ_LENGTH, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Wval  is same as application number */
	अगर (port->serial->num_ports == 2 && port->port_number != 0)
		Wval = ((__u16)port->port_number + 2) << 8;
	अन्यथा
		Wval = ((__u16)port->port_number + 1) << 8;
	dev_dbg(&port->dev, "%s application number is %x\n", __func__, Wval);
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), MCS_RDREQ,
			      MCS_RD_RTYPE, Wval, reg, buf, VENDOR_READ_LENGTH,
			      MOS_WDR_TIMEOUT);
	अगर (ret < VENDOR_READ_LENGTH) अणु
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out;
	पूर्ण
	*val = buf[0];
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम mos7840_dump_serial_port(काष्ठा usb_serial_port *port,
				     काष्ठा moschip_port *mos7840_port)
अणु

	dev_dbg(&port->dev, "SpRegOffset is %2x\n", mos7840_port->SpRegOffset);
	dev_dbg(&port->dev, "ControlRegOffset is %2x\n", mos7840_port->ControlRegOffset);
	dev_dbg(&port->dev, "DCRRegOffset is %2x\n", mos7840_port->DcrRegOffset);

पूर्ण

/************************************************************************/
/************************************************************************/
/*            U S B  C A L L B A C K   F U N C T I O N S                */
/*            U S B  C A L L B A C K   F U N C T I O N S                */
/************************************************************************/
/************************************************************************/

अटल व्योम mos7840_set_led_callback(काष्ठा urb *urb)
अणु
	चयन (urb->status) अणु
	हाल 0:
		/* Success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* This urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down: %d\n",
			__func__, urb->status);
		अवरोध;
	शेष:
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status: %d\n",
			__func__, urb->status);
	पूर्ण
पूर्ण

अटल व्योम mos7840_set_led_async(काष्ठा moschip_port *mcs, __u16 wval,
				__u16 reg)
अणु
	काष्ठा usb_device *dev = mcs->port->serial->dev;
	काष्ठा usb_ctrlrequest *dr = mcs->led_dr;

	dr->bRequestType = MCS_WR_RTYPE;
	dr->bRequest = MCS_WRREQ;
	dr->wValue = cpu_to_le16(wval);
	dr->wIndex = cpu_to_le16(reg);
	dr->wLength = cpu_to_le16(0);

	usb_fill_control_urb(mcs->led_urb, dev, usb_sndctrlpipe(dev, 0),
		(अचिन्हित अक्षर *)dr, शून्य, 0, mos7840_set_led_callback, शून्य);

	usb_submit_urb(mcs->led_urb, GFP_ATOMIC);
पूर्ण

अटल व्योम mos7840_set_led_sync(काष्ठा usb_serial_port *port, __u16 reg,
				__u16 val)
अणु
	काष्ठा usb_device *dev = port->serial->dev;

	usb_control_msg(dev, usb_sndctrlpipe(dev, 0), MCS_WRREQ, MCS_WR_RTYPE,
			val, reg, शून्य, 0, MOS_WDR_TIMEOUT);
पूर्ण

अटल व्योम mos7840_led_off(काष्ठा समयr_list *t)
अणु
	काष्ठा moschip_port *mcs = from_समयr(mcs, t, led_समयr1);

	/* Turn off LED */
	mos7840_set_led_async(mcs, 0x0300, MODEM_CONTROL_REGISTER);
	mod_समयr(&mcs->led_समयr2,
				jअगरfies + msecs_to_jअगरfies(LED_OFF_MS));
पूर्ण

अटल व्योम mos7840_led_flag_off(काष्ठा समयr_list *t)
अणु
	काष्ठा moschip_port *mcs = from_समयr(mcs, t, led_समयr2);

	clear_bit_unlock(MOS7840_FLAG_LED_BUSY, &mcs->flags);
पूर्ण

अटल व्योम mos7840_led_activity(काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);

	अगर (test_and_set_bit_lock(MOS7840_FLAG_LED_BUSY, &mos7840_port->flags))
		वापस;

	mos7840_set_led_async(mos7840_port, 0x0301, MODEM_CONTROL_REGISTER);
	mod_समयr(&mos7840_port->led_समयr1,
				jअगरfies + msecs_to_jअगरfies(LED_ON_MS));
पूर्ण

/*****************************************************************************
 * mos7840_bulk_in_callback
 *	this is the callback function क्रम when we have received data on the
 *	bulk in endpoपूर्णांक.
 *****************************************************************************/

अटल व्योम mos7840_bulk_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा moschip_port *mos7840_port = urb->context;
	काष्ठा usb_serial_port *port = mos7840_port->port;
	पूर्णांक retval;
	अचिन्हित अक्षर *data;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "nonzero read bulk status received: %d\n", status);
		mos7840_port->पढ़ो_urb_busy = false;
		वापस;
	पूर्ण

	data = urb->transfer_buffer;
	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	अगर (urb->actual_length) अणु
		काष्ठा tty_port *tport = &mos7840_port->port->port;
		tty_insert_flip_string(tport, data, urb->actual_length);
		tty_flip_buffer_push(tport);
		port->icount.rx += urb->actual_length;
		dev_dbg(&port->dev, "icount.rx is %d:\n", port->icount.rx);
	पूर्ण

	अगर (mos7840_port->has_led)
		mos7840_led_activity(port);

	mos7840_port->पढ़ो_urb_busy = true;
	retval = usb_submit_urb(mos7840_port->पढ़ो_urb, GFP_ATOMIC);

	अगर (retval) अणु
		dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, retval = %d\n", retval);
		mos7840_port->पढ़ो_urb_busy = false;
	पूर्ण
पूर्ण

/*****************************************************************************
 * mos7840_bulk_out_data_callback
 *	this is the callback function क्रम when we have finished sending
 *	serial data on the bulk out endpoपूर्णांक.
 *****************************************************************************/

अटल व्योम mos7840_bulk_out_data_callback(काष्ठा urb *urb)
अणु
	काष्ठा moschip_port *mos7840_port = urb->context;
	काष्ठा usb_serial_port *port = mos7840_port->port;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mos7840_port->pool_lock, flags);
	क्रम (i = 0; i < NUM_URBS; i++) अणु
		अगर (urb == mos7840_port->ग_लिखो_urb_pool[i]) अणु
			mos7840_port->busy[i] = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mos7840_port->pool_lock, flags);

	अगर (status) अणु
		dev_dbg(&port->dev, "nonzero write bulk status received:%d\n", status);
		वापस;
	पूर्ण

	tty_port_tty_wakeup(&port->port);

पूर्ण

/************************************************************************/
/*       D R I V E R  T T Y  I N T E R F A C E  F U N C T I O N S       */
/************************************************************************/

/*****************************************************************************
 * mos7840_खोलो
 *	this function is called by the tty driver when a port is खोलोed
 *	If successful, we वापस 0
 *	Otherwise we वापस a negative error number.
 *****************************************************************************/

अटल पूर्णांक mos7840_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक response;
	पूर्णांक j;
	काष्ठा urb *urb;
	__u16 Data;
	पूर्णांक status;

	usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);

	/* Initialising the ग_लिखो urb pool */
	क्रम (j = 0; j < NUM_URBS; ++j) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		mos7840_port->ग_लिखो_urb_pool[j] = urb;
		अगर (!urb)
			जारी;

		urb->transfer_buffer = kदो_स्मृति(URB_TRANSFER_BUFFER_SIZE,
								GFP_KERNEL);
		अगर (!urb->transfer_buffer) अणु
			usb_मुक्त_urb(urb);
			mos7840_port->ग_लिखो_urb_pool[j] = शून्य;
			जारी;
		पूर्ण
	पूर्ण

/*****************************************************************************
 * Initialize MCS7840 -- Write Init values to corresponding Registers
 *
 * Register Index
 * 1 : IER
 * 2 : FCR
 * 3 : LCR
 * 4 : MCR
 *
 * 0x08 : SP1/2 Control Reg
 *****************************************************************************/

	/* NEED to check the following Block */

	Data = 0x0;
	status = mos7840_get_reg_sync(port, mos7840_port->SpRegOffset, &Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Reading Spreg failed\n");
		जाओ err;
	पूर्ण
	Data |= 0x80;
	status = mos7840_set_reg_sync(port, mos7840_port->SpRegOffset, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "writing Spreg failed\n");
		जाओ err;
	पूर्ण

	Data &= ~0x80;
	status = mos7840_set_reg_sync(port, mos7840_port->SpRegOffset, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "writing Spreg failed\n");
		जाओ err;
	पूर्ण
	/* End of block to be checked */

	Data = 0x0;
	status = mos7840_get_reg_sync(port, mos7840_port->ControlRegOffset,
									&Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Reading Controlreg failed\n");
		जाओ err;
	पूर्ण
	Data |= 0x08;		/* Driver करोne bit */
	Data |= 0x20;		/* rx_disable */
	status = mos7840_set_reg_sync(port,
				mos7840_port->ControlRegOffset, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "writing Controlreg failed\n");
		जाओ err;
	पूर्ण
	/* करो रेजिस्टर settings here */
	/* Set all regs to the device शेष values. */
	/***********************************
	 * First Disable all पूर्णांकerrupts.
	 ***********************************/
	Data = 0x00;
	status = mos7840_set_uart_reg(port, INTERRUPT_ENABLE_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "disabling interrupts failed\n");
		जाओ err;
	पूर्ण
	/* Set FIFO_CONTROL_REGISTER to the शेष value */
	Data = 0x00;
	status = mos7840_set_uart_reg(port, FIFO_CONTROL_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing FIFO_CONTROL_REGISTER  failed\n");
		जाओ err;
	पूर्ण

	Data = 0xcf;
	status = mos7840_set_uart_reg(port, FIFO_CONTROL_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing FIFO_CONTROL_REGISTER  failed\n");
		जाओ err;
	पूर्ण

	Data = 0x03;
	status = mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);
	mos7840_port->shaकरोwLCR = Data;

	Data = 0x0b;
	status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, Data);
	mos7840_port->shaकरोwMCR = Data;

	Data = 0x00;
	status = mos7840_get_uart_reg(port, LINE_CONTROL_REGISTER, &Data);
	mos7840_port->shaकरोwLCR = Data;

	Data |= SERIAL_LCR_DLAB;	/* data latch enable in LCR 0x80 */
	status = mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);

	Data = 0x0c;
	status = mos7840_set_uart_reg(port, DIVISOR_LATCH_LSB, Data);

	Data = 0x0;
	status = mos7840_set_uart_reg(port, DIVISOR_LATCH_MSB, Data);

	Data = 0x00;
	status = mos7840_get_uart_reg(port, LINE_CONTROL_REGISTER, &Data);

	Data = Data & ~SERIAL_LCR_DLAB;
	status = mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);
	mos7840_port->shaकरोwLCR = Data;

	/* clearing Bulkin and Bulkout Fअगरo */
	Data = 0x0;
	status = mos7840_get_reg_sync(port, mos7840_port->SpRegOffset, &Data);

	Data = Data | 0x0c;
	status = mos7840_set_reg_sync(port, mos7840_port->SpRegOffset, Data);

	Data = Data & ~0x0c;
	status = mos7840_set_reg_sync(port, mos7840_port->SpRegOffset, Data);
	/* Finally enable all पूर्णांकerrupts */
	Data = 0x0c;
	status = mos7840_set_uart_reg(port, INTERRUPT_ENABLE_REGISTER, Data);

	/* clearing rx_disable */
	Data = 0x0;
	status = mos7840_get_reg_sync(port, mos7840_port->ControlRegOffset,
									&Data);
	Data = Data & ~0x20;
	status = mos7840_set_reg_sync(port, mos7840_port->ControlRegOffset,
									Data);

	/* rx_negate */
	Data = 0x0;
	status = mos7840_get_reg_sync(port, mos7840_port->ControlRegOffset,
									&Data);
	Data = Data | 0x10;
	status = mos7840_set_reg_sync(port, mos7840_port->ControlRegOffset,
									Data);

	dev_dbg(&port->dev, "port number is %d\n", port->port_number);
	dev_dbg(&port->dev, "minor number is %d\n", port->minor);
	dev_dbg(&port->dev, "Bulkin endpoint is %d\n", port->bulk_in_endpoपूर्णांकAddress);
	dev_dbg(&port->dev, "BulkOut endpoint is %d\n", port->bulk_out_endpoपूर्णांकAddress);
	dev_dbg(&port->dev, "Interrupt endpoint is %d\n", port->पूर्णांकerrupt_in_endpoपूर्णांकAddress);
	dev_dbg(&port->dev, "port's number in the device is %d\n", mos7840_port->port_num);
	mos7840_port->पढ़ो_urb = port->पढ़ो_urb;

	/* set up our bulk in urb */
	अगर ((serial->num_ports == 2) && (((__u16)port->port_number % 2) != 0)) अणु
		usb_fill_bulk_urb(mos7840_port->पढ़ो_urb,
			serial->dev,
			usb_rcvbulkpipe(serial->dev,
				(port->bulk_in_endpoपूर्णांकAddress) + 2),
			port->bulk_in_buffer,
			mos7840_port->पढ़ो_urb->transfer_buffer_length,
			mos7840_bulk_in_callback, mos7840_port);
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(mos7840_port->पढ़ो_urb,
			serial->dev,
			usb_rcvbulkpipe(serial->dev,
				port->bulk_in_endpoपूर्णांकAddress),
			port->bulk_in_buffer,
			mos7840_port->पढ़ो_urb->transfer_buffer_length,
			mos7840_bulk_in_callback, mos7840_port);
	पूर्ण

	dev_dbg(&port->dev, "%s: bulkin endpoint is %d\n", __func__, port->bulk_in_endpoपूर्णांकAddress);
	mos7840_port->पढ़ो_urb_busy = true;
	response = usb_submit_urb(mos7840_port->पढ़ो_urb, GFP_KERNEL);
	अगर (response) अणु
		dev_err(&port->dev, "%s - Error %d submitting control urb\n",
			__func__, response);
		mos7840_port->पढ़ो_urb_busy = false;
	पूर्ण

	/* initialize our port settings */
	/* Must set to enable पूर्णांकs! */
	mos7840_port->shaकरोwMCR = MCR_MASTER_IE;

	वापस 0;
err:
	क्रम (j = 0; j < NUM_URBS; ++j) अणु
		urb = mos7840_port->ग_लिखो_urb_pool[j];
		अगर (!urb)
			जारी;
		kमुक्त(urb->transfer_buffer);
		usb_मुक्त_urb(urb);
	पूर्ण
	वापस status;
पूर्ण

/*****************************************************************************
 * mos7840_अक्षरs_in_buffer
 *	this function is called by the tty driver when it wants to know how many
 *	bytes of data we currently have outstanding in the port (data that has
 *	been written, but hasn't made it out the port yet)
 *	If successful, we वापस the number of bytes left to be written in the
 *	प्रणाली,
 *	Otherwise we वापस zero.
 *****************************************************************************/

अटल पूर्णांक mos7840_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक i;
	पूर्णांक अक्षरs = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mos7840_port->pool_lock, flags);
	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (mos7840_port->busy[i]) अणु
			काष्ठा urb *urb = mos7840_port->ग_लिखो_urb_pool[i];
			अक्षरs += urb->transfer_buffer_length;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mos7840_port->pool_lock, flags);
	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;

पूर्ण

/*****************************************************************************
 * mos7840_बंद
 *	this function is called by the tty driver when a port is बंदd
 *****************************************************************************/

अटल व्योम mos7840_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक j;
	__u16 Data;

	क्रम (j = 0; j < NUM_URBS; ++j)
		usb_समाप्त_urb(mos7840_port->ग_लिखो_urb_pool[j]);

	/* Freeing Write URBs */
	क्रम (j = 0; j < NUM_URBS; ++j) अणु
		अगर (mos7840_port->ग_लिखो_urb_pool[j]) अणु
			kमुक्त(mos7840_port->ग_लिखो_urb_pool[j]->transfer_buffer);
			usb_मुक्त_urb(mos7840_port->ग_लिखो_urb_pool[j]);
		पूर्ण
	पूर्ण

	usb_समाप्त_urb(mos7840_port->पढ़ो_urb);
	mos7840_port->पढ़ो_urb_busy = false;

	Data = 0x0;
	mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, Data);

	Data = 0x00;
	mos7840_set_uart_reg(port, INTERRUPT_ENABLE_REGISTER, Data);
पूर्ण

/*****************************************************************************
 * mos7840_अवरोध
 *	this function sends a अवरोध to the port
 *****************************************************************************/
अटल व्योम mos7840_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	अचिन्हित अक्षर data;

	अगर (अवरोध_state == -1)
		data = mos7840_port->shaकरोwLCR | LCR_SET_BREAK;
	अन्यथा
		data = mos7840_port->shaकरोwLCR & ~LCR_SET_BREAK;

	/* FIXME: no locking on shaकरोwLCR anywhere in driver */
	mos7840_port->shaकरोwLCR = data;
	dev_dbg(&port->dev, "%s mos7840_port->shadowLCR is %x\n", __func__, mos7840_port->shaकरोwLCR);
	mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER,
			     mos7840_port->shaकरोwLCR);
पूर्ण

/*****************************************************************************
 * mos7840_ग_लिखो_room
 *	this function is called by the tty driver when it wants to know how many
 *	bytes of data we can accept क्रम a specअगरic port.
 *	If successful, we वापस the amount of room that we have क्रम this port
 *	Otherwise we वापस a negative error number.
 *****************************************************************************/

अटल पूर्णांक mos7840_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक i;
	पूर्णांक room = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mos7840_port->pool_lock, flags);
	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (!mos7840_port->busy[i])
			room += URB_TRANSFER_BUFFER_SIZE;
	पूर्ण
	spin_unlock_irqrestore(&mos7840_port->pool_lock, flags);

	room = (room == 0) ? 0 : room - URB_TRANSFER_BUFFER_SIZE + 1;
	dev_dbg(&mos7840_port->port->dev, "%s - returns %d\n", __func__, room);
	वापस room;

पूर्ण

/*****************************************************************************
 * mos7840_ग_लिखो
 *	this function is called by the tty driver when data should be written to
 *	the port.
 *	If successful, we वापस the number of bytes written, otherwise we
 *      वापस a negative error number.
 *****************************************************************************/

अटल पूर्णांक mos7840_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			 स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक status;
	पूर्णांक i;
	पूर्णांक bytes_sent = 0;
	पूर्णांक transfer_size;
	अचिन्हित दीर्घ flags;
	काष्ठा urb *urb;
	/* __u16 Data; */
	स्थिर अचिन्हित अक्षर *current_position = data;

	/* try to find a मुक्त urb in the list */
	urb = शून्य;

	spin_lock_irqsave(&mos7840_port->pool_lock, flags);
	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (!mos7840_port->busy[i]) अणु
			mos7840_port->busy[i] = 1;
			urb = mos7840_port->ग_लिखो_urb_pool[i];
			dev_dbg(&port->dev, "URB:%d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mos7840_port->pool_lock, flags);

	अगर (urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - no more free urbs\n", __func__);
		जाओ निकास;
	पूर्ण

	अगर (urb->transfer_buffer == शून्य) अणु
		urb->transfer_buffer = kदो_स्मृति(URB_TRANSFER_BUFFER_SIZE,
					       GFP_ATOMIC);
		अगर (!urb->transfer_buffer) अणु
			bytes_sent = -ENOMEM;
			जाओ निकास;
		पूर्ण
	पूर्ण
	transfer_size = min(count, URB_TRANSFER_BUFFER_SIZE);

	स_नकल(urb->transfer_buffer, current_position, transfer_size);

	/* fill urb with data and submit  */
	अगर ((serial->num_ports == 2) && (((__u16)port->port_number % 2) != 0)) अणु
		usb_fill_bulk_urb(urb,
			serial->dev,
			usb_sndbulkpipe(serial->dev,
				(port->bulk_out_endpoपूर्णांकAddress) + 2),
			urb->transfer_buffer,
			transfer_size,
			mos7840_bulk_out_data_callback, mos7840_port);
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(urb,
			serial->dev,
			usb_sndbulkpipe(serial->dev,
				port->bulk_out_endpoपूर्णांकAddress),
			urb->transfer_buffer,
			transfer_size,
			mos7840_bulk_out_data_callback, mos7840_port);
	पूर्ण

	dev_dbg(&port->dev, "bulkout endpoint is %d\n", port->bulk_out_endpoपूर्णांकAddress);

	अगर (mos7840_port->has_led)
		mos7840_led_activity(port);

	/* send it करोwn the pipe */
	status = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (status) अणु
		mos7840_port->busy[i] = 0;
		dev_err_console(port, "%s - usb_submit_urb(write bulk) failed "
			"with status = %d\n", __func__, status);
		bytes_sent = status;
		जाओ निकास;
	पूर्ण
	bytes_sent = transfer_size;
	port->icount.tx += transfer_size;
	dev_dbg(&port->dev, "icount.tx is %d:\n", port->icount.tx);
निकास:
	वापस bytes_sent;

पूर्ण

/*****************************************************************************
 * mos7840_throttle
 *	this function is called by the tty driver when it wants to stop the data
 *	being पढ़ो from the port.
 *****************************************************************************/

अटल व्योम mos7840_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	/* अगर we are implementing XON/XOFF, send the stop अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर stop_अक्षर = STOP_CHAR(tty);
		status = mos7840_ग_लिखो(tty, port, &stop_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण
	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		mos7840_port->shaकरोwMCR &= ~MCR_RTS;
		status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER,
					 mos7840_port->shaकरोwMCR);
		अगर (status < 0)
			वापस;
	पूर्ण
पूर्ण

/*****************************************************************************
 * mos7840_unthrottle
 *	this function is called by the tty driver when it wants to resume
 *	the data being पढ़ो from the port (called after mos7840_throttle is
 *	called)
 *****************************************************************************/
अटल व्योम mos7840_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	/* अगर we are implementing XON/XOFF, send the start अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर start_अक्षर = START_CHAR(tty);
		status = mos7840_ग_लिखो(tty, port, &start_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण

	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		mos7840_port->shaकरोwMCR |= MCR_RTS;
		status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER,
					 mos7840_port->shaकरोwMCR);
		अगर (status < 0)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक mos7840_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक result;
	__u16 msr;
	__u16 mcr;
	पूर्णांक status;

	status = mos7840_get_uart_reg(port, MODEM_STATUS_REGISTER, &msr);
	अगर (status < 0)
		वापस -EIO;
	status = mos7840_get_uart_reg(port, MODEM_CONTROL_REGISTER, &mcr);
	अगर (status < 0)
		वापस -EIO;
	result = ((mcr & MCR_DTR) ? TIOCM_DTR : 0)
	    | ((mcr & MCR_RTS) ? TIOCM_RTS : 0)
	    | ((mcr & MCR_LOOPBACK) ? TIOCM_LOOP : 0)
	    | ((msr & MOS7840_MSR_CTS) ? TIOCM_CTS : 0)
	    | ((msr & MOS7840_MSR_CD) ? TIOCM_CAR : 0)
	    | ((msr & MOS7840_MSR_RI) ? TIOCM_RI : 0)
	    | ((msr & MOS7840_MSR_DSR) ? TIOCM_DSR : 0);

	dev_dbg(&port->dev, "%s - 0x%04X\n", __func__, result);

	वापस result;
पूर्ण

अटल पूर्णांक mos7840_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक mcr;
	पूर्णांक status;

	/* FIXME: What locks the port रेजिस्टरs ? */
	mcr = mos7840_port->shaकरोwMCR;
	अगर (clear & TIOCM_RTS)
		mcr &= ~MCR_RTS;
	अगर (clear & TIOCM_DTR)
		mcr &= ~MCR_DTR;
	अगर (clear & TIOCM_LOOP)
		mcr &= ~MCR_LOOPBACK;

	अगर (set & TIOCM_RTS)
		mcr |= MCR_RTS;
	अगर (set & TIOCM_DTR)
		mcr |= MCR_DTR;
	अगर (set & TIOCM_LOOP)
		mcr |= MCR_LOOPBACK;

	mos7840_port->shaकरोwMCR = mcr;

	status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, mcr);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "setting MODEM_CONTROL_REGISTER Failed\n");
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/*****************************************************************************
 * mos7840_calc_baud_rate_भागisor
 *	this function calculates the proper baud rate भागisor क्रम the specअगरied
 *	baud rate.
 *****************************************************************************/
अटल पूर्णांक mos7840_calc_baud_rate_भागisor(काष्ठा usb_serial_port *port,
					  पूर्णांक baudRate, पूर्णांक *भागisor,
					  __u16 *clk_sel_val)
अणु
	dev_dbg(&port->dev, "%s - %d\n", __func__, baudRate);

	अगर (baudRate <= 115200) अणु
		*भागisor = 115200 / baudRate;
		*clk_sel_val = 0x0;
	पूर्ण
	अगर ((baudRate > 115200) && (baudRate <= 230400)) अणु
		*भागisor = 230400 / baudRate;
		*clk_sel_val = 0x10;
	पूर्ण अन्यथा अगर ((baudRate > 230400) && (baudRate <= 403200)) अणु
		*भागisor = 403200 / baudRate;
		*clk_sel_val = 0x20;
	पूर्ण अन्यथा अगर ((baudRate > 403200) && (baudRate <= 460800)) अणु
		*भागisor = 460800 / baudRate;
		*clk_sel_val = 0x30;
	पूर्ण अन्यथा अगर ((baudRate > 460800) && (baudRate <= 806400)) अणु
		*भागisor = 806400 / baudRate;
		*clk_sel_val = 0x40;
	पूर्ण अन्यथा अगर ((baudRate > 806400) && (baudRate <= 921600)) अणु
		*भागisor = 921600 / baudRate;
		*clk_sel_val = 0x50;
	पूर्ण अन्यथा अगर ((baudRate > 921600) && (baudRate <= 1572864)) अणु
		*भागisor = 1572864 / baudRate;
		*clk_sel_val = 0x60;
	पूर्ण अन्यथा अगर ((baudRate > 1572864) && (baudRate <= 3145728)) अणु
		*भागisor = 3145728 / baudRate;
		*clk_sel_val = 0x70;
	पूर्ण
	वापस 0;
पूर्ण

/*****************************************************************************
 * mos7840_send_cmd_ग_लिखो_baud_rate
 *	this function sends the proper command to change the baud rate of the
 *	specअगरied port.
 *****************************************************************************/

अटल पूर्णांक mos7840_send_cmd_ग_लिखो_baud_rate(काष्ठा moschip_port *mos7840_port,
					    पूर्णांक baudRate)
अणु
	काष्ठा usb_serial_port *port = mos7840_port->port;
	पूर्णांक भागisor = 0;
	पूर्णांक status;
	__u16 Data;
	__u16 clk_sel_val;

	dev_dbg(&port->dev, "%s - baud = %d\n", __func__, baudRate);
	/* reset clk_uart_sel in spregOffset */
	अगर (baudRate > 115200) अणु
#अगर_घोषित HW_flow_control
		/* NOTE: need to see the pther रेजिस्टर to modअगरy */
		/* setting h/w flow control bit to 1 */
		Data = 0x2b;
		mos7840_port->shaकरोwMCR = Data;
		status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER,
									Data);
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "Writing spreg failed in set_serial_baud\n");
			वापस -1;
		पूर्ण
#पूर्ण_अगर

	पूर्ण अन्यथा अणु
#अगर_घोषित HW_flow_control
		/* setting h/w flow control bit to 0 */
		Data = 0xb;
		mos7840_port->shaकरोwMCR = Data;
		status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER,
									Data);
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "Writing spreg failed in set_serial_baud\n");
			वापस -1;
		पूर्ण
#पूर्ण_अगर

	पूर्ण

	अगर (1) अणु		/* baudRate <= 115200) */
		clk_sel_val = 0x0;
		Data = 0x0;
		status = mos7840_calc_baud_rate_भागisor(port, baudRate, &भागisor,
						   &clk_sel_val);
		status = mos7840_get_reg_sync(port, mos7840_port->SpRegOffset,
								 &Data);
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "reading spreg failed in set_serial_baud\n");
			वापस -1;
		पूर्ण
		Data = (Data & 0x8f) | clk_sel_val;
		status = mos7840_set_reg_sync(port, mos7840_port->SpRegOffset,
								Data);
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "Writing spreg failed in set_serial_baud\n");
			वापस -1;
		पूर्ण
		/* Calculate the Divisor */

		अगर (status) अणु
			dev_err(&port->dev, "%s - bad baud rate\n", __func__);
			वापस status;
		पूर्ण
		/* Enable access to भागisor latch */
		Data = mos7840_port->shaकरोwLCR | SERIAL_LCR_DLAB;
		mos7840_port->shaकरोwLCR = Data;
		mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);

		/* Write the भागisor */
		Data = (अचिन्हित अक्षर)(भागisor & 0xff);
		dev_dbg(&port->dev, "set_serial_baud Value to write DLL is %x\n", Data);
		mos7840_set_uart_reg(port, DIVISOR_LATCH_LSB, Data);

		Data = (अचिन्हित अक्षर)((भागisor & 0xff00) >> 8);
		dev_dbg(&port->dev, "set_serial_baud Value to write DLM is %x\n", Data);
		mos7840_set_uart_reg(port, DIVISOR_LATCH_MSB, Data);

		/* Disable access to भागisor latch */
		Data = mos7840_port->shaकरोwLCR & ~SERIAL_LCR_DLAB;
		mos7840_port->shaकरोwLCR = Data;
		mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);

	पूर्ण
	वापस status;
पूर्ण

/*****************************************************************************
 * mos7840_change_port_settings
 *	This routine is called to set the UART on the device to match
 *      the specअगरied new settings.
 *****************************************************************************/

अटल व्योम mos7840_change_port_settings(काष्ठा tty_काष्ठा *tty,
	काष्ठा moschip_port *mos7840_port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial_port *port = mos7840_port->port;
	पूर्णांक baud;
	अचिन्हित cflag;
	__u8 lData;
	__u8 lParity;
	__u8 lStop;
	पूर्णांक status;
	__u16 Data;

	lData = LCR_BITS_8;
	lStop = LCR_STOP_1;
	lParity = LCR_PAR_NONE;

	cflag = tty->termios.c_cflag;

	/* Change the number of bits */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		lData = LCR_BITS_5;
		अवरोध;

	हाल CS6:
		lData = LCR_BITS_6;
		अवरोध;

	हाल CS7:
		lData = LCR_BITS_7;
		अवरोध;

	शेष:
	हाल CS8:
		lData = LCR_BITS_8;
		अवरोध;
	पूर्ण

	/* Change the Parity bit */
	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD) अणु
			lParity = LCR_PAR_ODD;
			dev_dbg(&port->dev, "%s - parity = odd\n", __func__);
		पूर्ण अन्यथा अणु
			lParity = LCR_PAR_EVEN;
			dev_dbg(&port->dev, "%s - parity = even\n", __func__);
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - parity = none\n", __func__);
	पूर्ण

	अगर (cflag & CMSPAR)
		lParity = lParity | 0x20;

	/* Change the Stop bit */
	अगर (cflag & CSTOPB) अणु
		lStop = LCR_STOP_2;
		dev_dbg(&port->dev, "%s - stop bits = 2\n", __func__);
	पूर्ण अन्यथा अणु
		lStop = LCR_STOP_1;
		dev_dbg(&port->dev, "%s - stop bits = 1\n", __func__);
	पूर्ण

	/* Update the LCR with the correct value */
	mos7840_port->shaकरोwLCR &=
	    ~(LCR_BITS_MASK | LCR_STOP_MASK | LCR_PAR_MASK);
	mos7840_port->shaकरोwLCR |= (lData | lParity | lStop);

	dev_dbg(&port->dev, "%s - mos7840_port->shadowLCR is %x\n", __func__,
		mos7840_port->shaकरोwLCR);
	/* Disable Interrupts */
	Data = 0x00;
	mos7840_set_uart_reg(port, INTERRUPT_ENABLE_REGISTER, Data);

	Data = 0x00;
	mos7840_set_uart_reg(port, FIFO_CONTROL_REGISTER, Data);

	Data = 0xcf;
	mos7840_set_uart_reg(port, FIFO_CONTROL_REGISTER, Data);

	/* Send the updated LCR value to the mos7840 */
	Data = mos7840_port->shaकरोwLCR;

	mos7840_set_uart_reg(port, LINE_CONTROL_REGISTER, Data);

	Data = 0x00b;
	mos7840_port->shaकरोwMCR = Data;
	mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, Data);
	Data = 0x00b;
	mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, Data);

	/* set up the MCR रेजिस्टर and send it to the mos7840 */

	mos7840_port->shaकरोwMCR = MCR_MASTER_IE;
	अगर (cflag & CBAUD)
		mos7840_port->shaकरोwMCR |= (MCR_DTR | MCR_RTS);

	अगर (cflag & CRTSCTS)
		mos7840_port->shaकरोwMCR |= (MCR_XON_ANY);
	अन्यथा
		mos7840_port->shaकरोwMCR &= ~(MCR_XON_ANY);

	Data = mos7840_port->shaकरोwMCR;
	mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, Data);

	/* Determine भागisor based on baud rate */
	baud = tty_get_baud_rate(tty);

	अगर (!baud) अणु
		/* pick a शेष, any शेष... */
		dev_dbg(&port->dev, "%s", "Picked default baud...\n");
		baud = 9600;
	पूर्ण

	dev_dbg(&port->dev, "%s - baud rate = %d\n", __func__, baud);
	status = mos7840_send_cmd_ग_लिखो_baud_rate(mos7840_port, baud);

	/* Enable Interrupts */
	Data = 0x0c;
	mos7840_set_uart_reg(port, INTERRUPT_ENABLE_REGISTER, Data);

	अगर (!mos7840_port->पढ़ो_urb_busy) अणु
		mos7840_port->पढ़ो_urb_busy = true;
		status = usb_submit_urb(mos7840_port->पढ़ो_urb, GFP_KERNEL);
		अगर (status) अणु
			dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, status = %d\n",
			    status);
			mos7840_port->पढ़ो_urb_busy = false;
		पूर्ण
	पूर्ण
	dev_dbg(&port->dev, "%s - mos7840_port->shadowLCR is End %x\n", __func__,
		mos7840_port->shaकरोwLCR);
पूर्ण

/*****************************************************************************
 * mos7840_set_termios
 *	this function is called by the tty driver when it wants to change
 *	the termios काष्ठाure
 *****************************************************************************/

अटल व्योम mos7840_set_termios(काष्ठा tty_काष्ठा *tty,
				काष्ठा usb_serial_port *port,
				काष्ठा ktermios *old_termios)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	/* change the port settings to the new ones specअगरied */

	mos7840_change_port_settings(tty, mos7840_port, old_termios);

	अगर (!mos7840_port->पढ़ो_urb_busy) अणु
		mos7840_port->पढ़ो_urb_busy = true;
		status = usb_submit_urb(mos7840_port->पढ़ो_urb, GFP_KERNEL);
		अगर (status) अणु
			dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, status = %d\n",
			    status);
			mos7840_port->पढ़ो_urb_busy = false;
		पूर्ण
	पूर्ण
पूर्ण

/*****************************************************************************
 * mos7840_get_lsr_info - get line status रेजिस्टर info
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 * 	    is emptied.  On bus types like RS485, the transmitter must
 * 	    release the bus after transmitting. This must be करोne when
 * 	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 * 	    transmit holding रेजिस्टर is empty.  This functionality
 * 	    allows an RS485 driver to be written in user space.
 *****************************************************************************/

अटल पूर्णांक mos7840_get_lsr_info(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक __user *value)
अणु
	पूर्णांक count;
	अचिन्हित पूर्णांक result = 0;

	count = mos7840_अक्षरs_in_buffer(tty);
	अगर (count == 0)
		result = TIOCSER_TEMT;

	अगर (copy_to_user(value, &result, माप(पूर्णांक)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*****************************************************************************
 * SerialIoctl
 *	this function handles any ioctl calls to the driver
 *****************************************************************************/

अटल पूर्णांक mos7840_ioctl(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
		/* वापस number of bytes available */

	हाल TIOCSERGETLSR:
		dev_dbg(&port->dev, "%s TIOCSERGETLSR\n", __func__);
		वापस mos7840_get_lsr_info(tty, argp);

	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

/*
 * Check अगर GPO (pin 42) is connected to GPI (pin 33) as recommended by ASIX
 * क्रम MCS7810 by bit-banging a 16-bit word.
 *
 * Note that GPO is really RTS of the third port so this will toggle RTS of
 * port two or three on two- and four-port devices.
 */
अटल पूर्णांक mos7810_check(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i, pass_count = 0;
	u8 *buf;
	__u16 data = 0, mcr_data = 0;
	__u16 test_pattern = 0x55AA;
	पूर्णांक res;

	buf = kदो_स्मृति(VENDOR_READ_LENGTH, GFP_KERNEL);
	अगर (!buf)
		वापस 0;	/* failed to identअगरy 7810 */

	/* Store MCR setting */
	res = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
		MCS_RDREQ, MCS_RD_RTYPE, 0x0300, MODEM_CONTROL_REGISTER,
		buf, VENDOR_READ_LENGTH, MOS_WDR_TIMEOUT);
	अगर (res == VENDOR_READ_LENGTH)
		mcr_data = *buf;

	क्रम (i = 0; i < 16; i++) अणु
		/* Send the 1-bit test pattern out to MCS7810 test pin */
		usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			MCS_WRREQ, MCS_WR_RTYPE,
			(0x0300 | (((test_pattern >> i) & 0x0001) << 1)),
			MODEM_CONTROL_REGISTER, शून्य, 0, MOS_WDR_TIMEOUT);

		/* Read the test pattern back */
		res = usb_control_msg(serial->dev,
				usb_rcvctrlpipe(serial->dev, 0), MCS_RDREQ,
				MCS_RD_RTYPE, 0, GPIO_REGISTER, buf,
				VENDOR_READ_LENGTH, MOS_WDR_TIMEOUT);
		अगर (res == VENDOR_READ_LENGTH)
			data = *buf;

		/* If this is a MCS7810 device, both test patterns must match */
		अगर (((test_pattern >> i) ^ (~data >> 1)) & 0x0001)
			अवरोध;

		pass_count++;
	पूर्ण

	/* Restore MCR setting */
	usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0), MCS_WRREQ,
		MCS_WR_RTYPE, 0x0300 | mcr_data, MODEM_CONTROL_REGISTER, शून्य,
		0, MOS_WDR_TIMEOUT);

	kमुक्त(buf);

	अगर (pass_count == 16)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mos7840_probe(काष्ठा usb_serial *serial,
				स्थिर काष्ठा usb_device_id *id)
अणु
	अचिन्हित दीर्घ device_flags = id->driver_info;
	u8 *buf;

	/* Skip device-type detection अगर we alपढ़ोy have device flags. */
	अगर (device_flags)
		जाओ out;

	buf = kzalloc(VENDOR_READ_LENGTH, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			MCS_RDREQ, MCS_RD_RTYPE, 0, GPIO_REGISTER, buf,
			VENDOR_READ_LENGTH, MOS_WDR_TIMEOUT);

	/* For a MCS7840 device GPIO0 must be set to 1 */
	अगर (buf[0] & 0x01)
		device_flags = MCS_PORTS(4);
	अन्यथा अगर (mos7810_check(serial))
		device_flags = MCS_PORTS(1) | MCS_LED;
	अन्यथा
		device_flags = MCS_PORTS(2);

	kमुक्त(buf);
out:
	usb_set_serial_data(serial, (व्योम *)device_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mos7840_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	अचिन्हित दीर्घ device_flags = (अचिन्हित दीर्घ)usb_get_serial_data(serial);
	पूर्णांक num_ports = MCS_PORTS(device_flags);

	अगर (num_ports == 0 || num_ports > 4)
		वापस -ENODEV;

	अगर (epds->num_bulk_in < num_ports || epds->num_bulk_out < num_ports) अणु
		dev_err(&serial->पूर्णांकerface->dev, "missing endpoints\n");
		वापस -ENODEV;
	पूर्ण

	वापस num_ports;
पूर्ण

अटल पूर्णांक mos7840_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	पूर्णांक status;
	u16 val;

	/* Zero Length flag enable */
	val = 0x0f;
	status = mos7840_set_reg_sync(serial->port[0], ZLP_REG5, val);
	अगर (status < 0)
		dev_dbg(dev, "Writing ZLP_REG5 failed status-0x%x\n", status);
	अन्यथा
		dev_dbg(dev, "ZLP_REG5 Writing success status%d\n", status);

	वापस status;
पूर्ण

अटल पूर्णांक mos7840_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	अचिन्हित दीर्घ device_flags = (अचिन्हित दीर्घ)usb_get_serial_data(serial);
	काष्ठा moschip_port *mos7840_port;
	पूर्णांक status;
	पूर्णांक pnum;
	__u16 Data;

	/* we set up the poपूर्णांकers to the endpoपूर्णांकs in the mos7840_खोलो *
	 * function, as the काष्ठाures aren't created yet.             */

	pnum = port->port_number;

	dev_dbg(&port->dev, "mos7840_startup: configuring port %d\n", pnum);
	mos7840_port = kzalloc(माप(काष्ठा moschip_port), GFP_KERNEL);
	अगर (!mos7840_port)
		वापस -ENOMEM;

	/* Initialize all port पूर्णांकerrupt end poपूर्णांक to port 0 पूर्णांक
	 * endpoपूर्णांक. Our device has only one पूर्णांकerrupt end poपूर्णांक
	 * common to all port */

	mos7840_port->port = port;
	spin_lock_init(&mos7840_port->pool_lock);

	/* minor is not initialised until later by
	 * usb-serial.c:get_मुक्त_serial() and cannot thereक्रमe be used
	 * to index device instances */
	mos7840_port->port_num = pnum + 1;
	dev_dbg(&port->dev, "port->minor = %d\n", port->minor);
	dev_dbg(&port->dev, "mos7840_port->port_num = %d\n", mos7840_port->port_num);

	अगर (mos7840_port->port_num == 1) अणु
		mos7840_port->SpRegOffset = 0x0;
		mos7840_port->ControlRegOffset = 0x1;
		mos7840_port->DcrRegOffset = 0x4;
	पूर्ण अन्यथा अणु
		u8 phy_num = mos7840_port->port_num;

		/* Port 2 in the 2-port हाल uses रेजिस्टरs of port 3 */
		अगर (serial->num_ports == 2)
			phy_num = 3;

		mos7840_port->SpRegOffset = 0x8 + 2 * (phy_num - 2);
		mos7840_port->ControlRegOffset = 0x9 + 2 * (phy_num - 2);
		mos7840_port->DcrRegOffset = 0x16 + 3 * (phy_num - 2);
	पूर्ण
	mos7840_dump_serial_port(port, mos7840_port);
	usb_set_serial_port_data(port, mos7840_port);

	/* enable rx_disable bit in control रेजिस्टर */
	status = mos7840_get_reg_sync(port,
			mos7840_port->ControlRegOffset, &Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Reading ControlReg failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "ControlReg Reading success val is %x, status%d\n", Data, status);
	Data |= 0x08;	/* setting driver करोne bit */
	Data |= 0x04;	/* sp1_bit to have cts change reflect in
			   modem status reg */

	/* Data |= 0x20; //rx_disable bit */
	status = mos7840_set_reg_sync(port,
			mos7840_port->ControlRegOffset, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing ControlReg failed(rx_disable) status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "ControlReg Writing success(rx_disable) status%d\n", status);

	/* Write शेष values in DCR (i.e 0x01 in DCR0, 0x05 in DCR2
	   and 0x24 in DCR3 */
	Data = 0x01;
	status = mos7840_set_reg_sync(port,
			(__u16) (mos7840_port->DcrRegOffset + 0), Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing DCR0 failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "DCR0 Writing success status%d\n", status);

	Data = 0x05;
	status = mos7840_set_reg_sync(port,
			(__u16) (mos7840_port->DcrRegOffset + 1), Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing DCR1 failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "DCR1 Writing success status%d\n", status);

	Data = 0x24;
	status = mos7840_set_reg_sync(port,
			(__u16) (mos7840_port->DcrRegOffset + 2), Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing DCR2 failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "DCR2 Writing success status%d\n", status);

	/* ग_लिखो values in clkstart0x0 and clkmulti 0x20 */
	Data = 0x0;
	status = mos7840_set_reg_sync(port, CLK_START_VALUE_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing CLK_START_VALUE_REGISTER failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "CLK_START_VALUE_REGISTER Writing success status%d\n", status);

	Data = 0x20;
	status = mos7840_set_reg_sync(port, CLK_MULTI_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing CLK_MULTI_REGISTER failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "CLK_MULTI_REGISTER Writing success status%d\n", status);

	/* ग_लिखो value 0x0 to scratchpad रेजिस्टर */
	Data = 0x00;
	status = mos7840_set_uart_reg(port, SCRATCH_PAD_REGISTER, Data);
	अगर (status < 0) अणु
		dev_dbg(&port->dev, "Writing SCRATCH_PAD_REGISTER failed status-0x%x\n", status);
		जाओ error;
	पूर्ण अन्यथा
		dev_dbg(&port->dev, "SCRATCH_PAD_REGISTER Writing success status%d\n", status);

	/* Zero Length flag रेजिस्टर */
	अगर ((mos7840_port->port_num != 1) && (serial->num_ports == 2)) अणु
		Data = 0xff;
		status = mos7840_set_reg_sync(port,
				(__u16) (ZLP_REG1 +
					((__u16)mos7840_port->port_num)), Data);
		dev_dbg(&port->dev, "ZLIP offset %x\n",
				(__u16)(ZLP_REG1 + ((__u16) mos7840_port->port_num)));
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "Writing ZLP_REG%d failed status-0x%x\n", pnum + 2, status);
			जाओ error;
		पूर्ण अन्यथा
			dev_dbg(&port->dev, "ZLP_REG%d Writing success status%d\n", pnum + 2, status);
	पूर्ण अन्यथा अणु
		Data = 0xff;
		status = mos7840_set_reg_sync(port,
				(__u16) (ZLP_REG1 +
					((__u16)mos7840_port->port_num) - 0x1), Data);
		dev_dbg(&port->dev, "ZLIP offset %x\n",
				(__u16)(ZLP_REG1 + ((__u16) mos7840_port->port_num) - 0x1));
		अगर (status < 0) अणु
			dev_dbg(&port->dev, "Writing ZLP_REG%d failed status-0x%x\n", pnum + 1, status);
			जाओ error;
		पूर्ण अन्यथा
			dev_dbg(&port->dev, "ZLP_REG%d Writing success status%d\n", pnum + 1, status);

	पूर्ण

	mos7840_port->has_led = device_flags & MCS_LED;

	/* Initialize LED समयrs */
	अगर (mos7840_port->has_led) अणु
		mos7840_port->led_urb = usb_alloc_urb(0, GFP_KERNEL);
		mos7840_port->led_dr = kदो_स्मृति(माप(*mos7840_port->led_dr),
								GFP_KERNEL);
		अगर (!mos7840_port->led_urb || !mos7840_port->led_dr) अणु
			status = -ENOMEM;
			जाओ error;
		पूर्ण

		समयr_setup(&mos7840_port->led_समयr1, mos7840_led_off, 0);
		mos7840_port->led_समयr1.expires =
			jअगरfies + msecs_to_jअगरfies(LED_ON_MS);
		समयr_setup(&mos7840_port->led_समयr2, mos7840_led_flag_off,
			    0);
		mos7840_port->led_समयr2.expires =
			jअगरfies + msecs_to_jअगरfies(LED_OFF_MS);

		/* Turn off LED */
		mos7840_set_led_sync(port, MODEM_CONTROL_REGISTER, 0x0300);
	पूर्ण

	वापस 0;
error:
	kमुक्त(mos7840_port->led_dr);
	usb_मुक्त_urb(mos7840_port->led_urb);
	kमुक्त(mos7840_port);

	वापस status;
पूर्ण

अटल व्योम mos7840_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7840_port = usb_get_serial_port_data(port);

	अगर (mos7840_port->has_led) अणु
		/* Turn off LED */
		mos7840_set_led_sync(port, MODEM_CONTROL_REGISTER, 0x0300);

		del_समयr_sync(&mos7840_port->led_समयr1);
		del_समयr_sync(&mos7840_port->led_समयr2);

		usb_समाप्त_urb(mos7840_port->led_urb);
		usb_मुक्त_urb(mos7840_port->led_urb);
		kमुक्त(mos7840_port->led_dr);
	पूर्ण

	kमुक्त(mos7840_port);
पूर्ण

अटल काष्ठा usb_serial_driver moschip7840_4port_device = अणु
	.driver = अणु
		   .owner = THIS_MODULE,
		   .name = "mos7840",
		   पूर्ण,
	.description = DRIVER_DESC,
	.id_table = id_table,
	.num_पूर्णांकerrupt_in = 1,
	.खोलो = mos7840_खोलो,
	.बंद = mos7840_बंद,
	.ग_लिखो = mos7840_ग_लिखो,
	.ग_लिखो_room = mos7840_ग_लिखो_room,
	.अक्षरs_in_buffer = mos7840_अक्षरs_in_buffer,
	.throttle = mos7840_throttle,
	.unthrottle = mos7840_unthrottle,
	.calc_num_ports = mos7840_calc_num_ports,
	.probe = mos7840_probe,
	.attach = mos7840_attach,
	.ioctl = mos7840_ioctl,
	.set_termios = mos7840_set_termios,
	.अवरोध_ctl = mos7840_अवरोध,
	.tiocmget = mos7840_tiocmget,
	.tiocmset = mos7840_tiocmset,
	.get_icount = usb_serial_generic_get_icount,
	.port_probe = mos7840_port_probe,
	.port_हटाओ = mos7840_port_हटाओ,
	.पढ़ो_bulk_callback = mos7840_bulk_in_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&moschip7840_4port_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
