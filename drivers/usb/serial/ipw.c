<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IPWireless 3G UMTS TDD Modem driver (USB connected)
 *
 *   Copyright (C) 2004 Roelf Diedericks <roelfd@inet.co.za>
 *   Copyright (C) 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 * All inक्रमmation about the device was acquired using SnoopyPro
 * on MSFT's O/S, and examing the MSFT drivers' debug output
 * (insanely left _on_ in the enduser version)
 *
 * It was written out of frustration with the IPWireless USB modem
 * supplied by Axity3G/Sentech South Africa not supporting
 * Linux whatsoever.
 *
 * Nobody provided any proprietary inक्रमmation that was not alपढ़ोy
 * available क्रम this device.
 *
 * The modem adheres to the "3GPP TS  27.007 AT command set क्रम 3G
 * User Equipment (UE)" standard, available from
 * http://www.3gpp.org/ftp/Specs/hपंचांगl-info/27007.hपंचांग
 *
 * The code was only tested the IPWireless handheld modem distributed
 * in South Africa by Sentech.
 *
 * It may work क्रम Woosh Inc in .nz too, as it appears they use the
 * same kit.
 *
 * There is still some work to be करोne in terms of handling
 * DCD, DTR, RTS, CTS which are currently faked.
 * It's good enough for PPP at this point. It's based off all kinds of
 * code found in usb/serial and usb/class
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>
#समावेश "usb-wwan.h"

#घोषणा DRIVER_AUTHOR	"Roelf Diedericks"
#घोषणा DRIVER_DESC	"IPWireless tty driver"

#घोषणा IPW_TTY_MAJOR	240	/* real device node major id, experimental range */
#घोषणा IPW_TTY_MINORS	256	/* we support 256 devices, dunno why, it'd be insane :) */

#घोषणा USB_IPW_MAGIC	0x6d02	/* magic number क्रम ipw काष्ठा */


/* Message sizes */
#घोषणा EVENT_BUFFER_SIZE	0xFF
#घोषणा CHAR2INT16(c1, c0)	(((u32)((c1) & 0xff) << 8) + (u32)((c0) & 0xff))

/* venकरोr/product pairs that are known work with this driver*/
#घोषणा IPW_VID		0x0bc3
#घोषणा IPW_PID		0x0001


/* Venकरोr commands: */

/* baud rates */
क्रमागत अणु
	ipw_sio_b256000 = 0x000e,
	ipw_sio_b128000 = 0x001d,
	ipw_sio_b115200 = 0x0020,
	ipw_sio_b57600  = 0x0040,
	ipw_sio_b56000  = 0x0042,
	ipw_sio_b38400  = 0x0060,
	ipw_sio_b19200  = 0x00c0,
	ipw_sio_b14400  = 0x0100,
	ipw_sio_b9600   = 0x0180,
	ipw_sio_b4800   = 0x0300,
	ipw_sio_b2400   = 0x0600,
	ipw_sio_b1200   = 0x0c00,
	ipw_sio_b600    = 0x1800
पूर्ण;

/* data bits */
#घोषणा ipw_dtb_7		0x700
#घोषणा ipw_dtb_8		0x810	/* ok so the define is misleading, I know, but क्रमces 8,n,1 */
					/* I mean, is there a poपूर्णांक to any other setting these days? :) */

/* usb control request types : */
#घोषणा IPW_SIO_RXCTL		0x00	/* control bulk rx channel transmissions, value=1/0 (on/off) */
#घोषणा IPW_SIO_SET_BAUD	0x01	/* set baud, value=requested ipw_sio_bxxxx */
#घोषणा IPW_SIO_SET_LINE	0x03	/* set databits, parity. value=ipw_dtb_x */
#घोषणा IPW_SIO_SET_PIN		0x03	/* set/clear dtr/rts value=ipw_pin_xxx */
#घोषणा IPW_SIO_POLL		0x08	/* get serial port status byte, call with value=0 */
#घोषणा IPW_SIO_INIT		0x11	/* initializes ? value=0 (appears as first thing toकरो on खोलो) */
#घोषणा IPW_SIO_PURGE		0x12	/* purge all transmissions?, call with value=numअक्षर_to_purge */
#घोषणा IPW_SIO_HANDFLOW	0x13	/* set xon/xoff limits value=0, and a buffer of 0x10 bytes */
#घोषणा IPW_SIO_SETCHARS	0x13	/* set the flowcontrol special अक्षरs, value=0, buf=6 bytes, */
					/* last 2 bytes contain flowcontrol अक्षरs e.g. 00 00 00 00 11 13 */

/* values used क्रम request IPW_SIO_SET_PIN */
#घोषणा IPW_PIN_SETDTR		0x101
#घोषणा IPW_PIN_SETRTS		0x202
#घोषणा IPW_PIN_CLRDTR		0x100
#घोषणा IPW_PIN_CLRRTS		0x200 /* unconfirmed */

/* values used क्रम request IPW_SIO_RXCTL */
#घोषणा IPW_RXBULK_ON		1
#घोषणा IPW_RXBULK_OFF		0

/* various 16 byte hardcoded transferbuffers used by flow control */
#घोषणा IPW_BYTES_FLOWINIT	अणु 0x01, 0, 0, 0, 0x40, 0, 0, 0, \
					0, 0, 0, 0, 0, 0, 0, 0 पूर्ण

/* Interpretation of modem status lines */
/* These need sorting out by inभागidually connecting pins and checking
 * results. FIXME!
 * When data is being sent we see 0x30 in the lower byte; this must
 * contain DSR and CTS ...
 */
#घोषणा IPW_DSR			((1<<4) | (1<<5))
#घोषणा IPW_CTS			((1<<5) | (1<<4))

#घोषणा IPW_WANTS_TO_SEND	0x30

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(IPW_VID, IPW_PID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक ipw_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	काष्ठा device *dev = &port->dev;
	u8 buf_flow_अटल[16] = IPW_BYTES_FLOWINIT;
	u8 *buf_flow_init;
	पूर्णांक result;

	buf_flow_init = kmemdup(buf_flow_अटल, 16, GFP_KERNEL);
	अगर (!buf_flow_init)
		वापस -ENOMEM;

	/* --1: Tell the modem to initialize (we think) From snअगरfs this is
	 *	always the first thing that माला_लो sent to the modem during
	 *	खोलोing of the device */
	dev_dbg(dev, "%s: Sending SIO_INIT (we guess)\n", __func__);
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_INIT,
			 USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			 0,
			 0, /* index */
			 शून्य,
			 0,
			 100000);
	अगर (result < 0)
		dev_err(dev, "Init of modem failed (error = %d)\n", result);

	/* reset the bulk pipes */
	usb_clear_halt(udev, usb_rcvbulkpipe(udev, port->bulk_in_endpoपूर्णांकAddress));
	usb_clear_halt(udev, usb_sndbulkpipe(udev, port->bulk_out_endpoपूर्णांकAddress));

	/*--2: Start पढ़ोing from the device */
	dev_dbg(dev, "%s: setting up bulk read callback\n", __func__);
	usb_wwan_खोलो(tty, port);

	/*--3: Tell the modem to खोलो the floodgates on the rx bulk channel */
	dev_dbg(dev, "%s:asking modem for RxRead (RXBULK_ON)\n", __func__);
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_RXCTL,
			 USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			 IPW_RXBULK_ON,
			 0, /* index */
			 शून्य,
			 0,
			 100000);
	अगर (result < 0)
		dev_err(dev, "Enabling bulk RxRead failed (error = %d)\n", result);

	/*--4: setup the initial flowcontrol */
	dev_dbg(dev, "%s:setting init flowcontrol (%s)\n", __func__, buf_flow_init);
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_HANDFLOW,
			 USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			 0,
			 0,
			 buf_flow_init,
			 0x10,
			 200000);
	अगर (result < 0)
		dev_err(dev, "initial flowcontrol failed (error = %d)\n", result);

	kमुक्त(buf_flow_init);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_attach(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_wwan_पूर्णांकf_निजी *data;

	data = kzalloc(माप(काष्ठा usb_wwan_पूर्णांकf_निजी), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&data->susp_lock);
	usb_set_serial_data(serial, data);
	वापस 0;
पूर्ण

अटल व्योम ipw_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_wwan_पूर्णांकf_निजी *data = usb_get_serial_data(serial);

	usb_set_serial_data(serial, शून्य);
	kमुक्त(data);
पूर्ण

अटल व्योम ipw_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	काष्ठा device *dev = &port->dev;
	पूर्णांक result;

	dev_dbg(dev, "%s: on = %d\n", __func__, on);

	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_SET_PIN,
			 USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			 on ? IPW_PIN_SETDTR : IPW_PIN_CLRDTR,
			 0,
			 शून्य,
			 0,
			 200000);
	अगर (result < 0)
		dev_err(dev, "setting dtr failed (error = %d)\n", result);

	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_SET_PIN, USB_TYPE_VENDOR |
					USB_RECIP_INTERFACE | USB_सूची_OUT,
			 on ? IPW_PIN_SETRTS : IPW_PIN_CLRRTS,
			 0,
			 शून्य,
			 0,
			 200000);
	अगर (result < 0)
		dev_err(dev, "setting rts failed (error = %d)\n", result);
पूर्ण

अटल व्योम ipw_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	काष्ठा device *dev = &port->dev;
	पूर्णांक result;

	/*--3: purge */
	dev_dbg(dev, "%s:sending purge\n", __func__);
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_PURGE, USB_TYPE_VENDOR |
			 		USB_RECIP_INTERFACE | USB_सूची_OUT,
			 0x03,
			 0,
			 शून्य,
			 0,
			 200000);
	अगर (result < 0)
		dev_err(dev, "purge failed (error = %d)\n", result);


	/* send RXBULK_off (tell modem to stop transmitting bulk data on
	   rx chan) */
	result = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			 IPW_SIO_RXCTL,
			 USB_TYPE_VENDOR | USB_RECIP_INTERFACE | USB_सूची_OUT,
			 IPW_RXBULK_OFF,
			 0, /* index */
			 शून्य,
			 0,
			 100000);

	अगर (result < 0)
		dev_err(dev, "Disabling bulk RxRead failed (error = %d)\n", result);

	usb_wwan_बंद(port);
पूर्ण

अटल काष्ठा usb_serial_driver ipw_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"ipw",
	पूर्ण,
	.description =		"IPWireless converter",
	.id_table =		id_table,
	.num_ports =		1,
	.खोलो =			ipw_खोलो,
	.बंद =		ipw_बंद,
	.attach =		ipw_attach,
	.release =		ipw_release,
	.port_probe =		usb_wwan_port_probe,
	.port_हटाओ =		usb_wwan_port_हटाओ,
	.dtr_rts =		ipw_dtr_rts,
	.ग_लिखो =		usb_wwan_ग_लिखो,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ipw_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

/* Module inक्रमmation */
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
