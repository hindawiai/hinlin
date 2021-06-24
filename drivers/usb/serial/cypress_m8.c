<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Cypress M8 driver
 *
 * 	Copyright (C) 2004
 * 	    Lonnie Mendez (dignome@gmail.com)
 *	Copyright (C) 2003,2004
 *	    Neil Whelchel (koyama@firstlight.net)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 * See http://geocities.com/i0xox0i क्रम inक्रमmation on this driver and the
 * earthmate usb device.
 */

/* Thanks to Neil Whelchel क्रम writing the first cypress m8 implementation
   क्रम linux. */
/* Thanks to cypress क्रम providing references क्रम the hid reports. */
/* Thanks to Jiang Zhang क्रम providing links and क्रम general help. */
/* Code originates and was built up from ftdi_sio, belkin, pl2303 and others.*/


#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/serial.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "cypress_m8.h"


अटल bool stats;
अटल पूर्णांक पूर्णांकerval;
अटल bool unstable_bauds;

#घोषणा DRIVER_AUTHOR "Lonnie Mendez <dignome@gmail.com>, Neil Whelchel <koyama@firstlight.net>"
#घोषणा DRIVER_DESC "Cypress USB to Serial Driver"

/* ग_लिखो buffer size defines */
#घोषणा CYPRESS_BUF_SIZE	1024

अटल स्थिर काष्ठा usb_device_id id_table_earthmate[] = अणु
	अणु USB_DEVICE(VENDOR_ID_DELORME, PRODUCT_ID_EARTHMATEUSB) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_DELORME, PRODUCT_ID_EARTHMATEUSB_LT20) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_cyphidcomrs232[] = अणु
	अणु USB_DEVICE(VENDOR_ID_CYPRESS, PRODUCT_ID_CYPHIDCOM) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_SAI, PRODUCT_ID_CYPHIDCOM) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_POWERCOM, PRODUCT_ID_UPS) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_FRWD, PRODUCT_ID_CYPHIDCOM_FRWD) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_nokiaca42v2[] = अणु
	अणु USB_DEVICE(VENDOR_ID_DAZZLE, PRODUCT_ID_CA42) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(VENDOR_ID_DELORME, PRODUCT_ID_EARTHMATEUSB) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_DELORME, PRODUCT_ID_EARTHMATEUSB_LT20) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_CYPRESS, PRODUCT_ID_CYPHIDCOM) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_SAI, PRODUCT_ID_CYPHIDCOM) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_POWERCOM, PRODUCT_ID_UPS) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_FRWD, PRODUCT_ID_CYPHIDCOM_FRWD) पूर्ण,
	अणु USB_DEVICE(VENDOR_ID_DAZZLE, PRODUCT_ID_CA42) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);

क्रमागत packet_क्रमmat अणु
	packet_क्रमmat_1,  /* b0:status, b1:payload count */
	packet_क्रमmat_2   /* b0[7:3]:status, b0[2:0]:payload count */
पूर्ण;

काष्ठा cypress_निजी अणु
	spinlock_t lock;		   /* निजी lock */
	पूर्णांक chiptype;			   /* identअगरier of device, क्रम quirks/etc */
	पूर्णांक bytes_in;			   /* used क्रम statistics */
	पूर्णांक bytes_out;			   /* used क्रम statistics */
	पूर्णांक cmd_count;			   /* used क्रम statistics */
	पूर्णांक cmd_ctrl;			   /* always set this to 1 beक्रमe issuing a command */
	काष्ठा kfअगरo ग_लिखो_fअगरo;	   /* ग_लिखो fअगरo */
	पूर्णांक ग_लिखो_urb_in_use;		   /* ग_लिखो urb in use indicator */
	पूर्णांक ग_लिखो_urb_पूर्णांकerval;            /* पूर्णांकerval to use क्रम ग_लिखो urb */
	पूर्णांक पढ़ो_urb_पूर्णांकerval;             /* पूर्णांकerval to use क्रम पढ़ो urb */
	पूर्णांक comm_is_ok;                    /* true अगर communication is (still) ok */
	__u8 line_control;	   	   /* holds dtr / rts value */
	__u8 current_status;	   	   /* received from last पढ़ो - info on dsr,cts,cd,ri,etc */
	__u8 current_config;	   	   /* stores the current configuration byte */
	__u8 rx_flags;			   /* throttling - used from whiteheat/ftdi_sio */
	क्रमागत packet_क्रमmat pkt_fmt;	   /* क्रमmat to use क्रम packet send / receive */
	पूर्णांक get_cfg_unsafe;		   /* If true, the CYPRESS_GET_CONFIG is unsafe */
	पूर्णांक baud_rate;			   /* stores current baud rate in
					      पूर्णांकeger क्रमm */
	अक्षर prev_status;		   /* used क्रम TIOCMIWAIT */
पूर्ण;

/* function prototypes क्रम the Cypress USB to serial device */
अटल पूर्णांक  cypress_earthmate_port_probe(काष्ठा usb_serial_port *port);
अटल पूर्णांक  cypress_hidcom_port_probe(काष्ठा usb_serial_port *port);
अटल पूर्णांक  cypress_ca42v2_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम cypress_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक  cypress_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम cypress_बंद(काष्ठा usb_serial_port *port);
अटल व्योम cypress_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on);
अटल पूर्णांक  cypress_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
अटल व्योम cypress_send(काष्ठा usb_serial_port *port);
अटल पूर्णांक  cypress_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल व्योम cypress_earthmate_init_termios(काष्ठा tty_काष्ठा *tty);
अटल व्योम cypress_set_termios(काष्ठा tty_काष्ठा *tty,
			काष्ठा usb_serial_port *port, काष्ठा ktermios *old);
अटल पूर्णांक  cypress_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक  cypress_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल पूर्णांक  cypress_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
अटल व्योम cypress_throttle(काष्ठा tty_काष्ठा *tty);
अटल व्योम cypress_unthrottle(काष्ठा tty_काष्ठा *tty);
अटल व्योम cypress_set_dead(काष्ठा usb_serial_port *port);
अटल व्योम cypress_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb);
अटल व्योम cypress_ग_लिखो_पूर्णांक_callback(काष्ठा urb *urb);

अटल काष्ठा usb_serial_driver cypress_earthmate_device = अणु
	.driver = अणु
		.owner =		THIS_MODULE,
		.name =			"earthmate",
	पूर्ण,
	.description =			"DeLorme Earthmate USB",
	.id_table =			id_table_earthmate,
	.num_ports =			1,
	.port_probe =			cypress_earthmate_port_probe,
	.port_हटाओ =			cypress_port_हटाओ,
	.खोलो =				cypress_खोलो,
	.बंद =			cypress_बंद,
	.dtr_rts =			cypress_dtr_rts,
	.ग_लिखो =			cypress_ग_लिखो,
	.ग_लिखो_room =			cypress_ग_लिखो_room,
	.init_termios =			cypress_earthmate_init_termios,
	.set_termios =			cypress_set_termios,
	.tiocmget =			cypress_tiocmget,
	.tiocmset =			cypress_tiocmset,
	.tiocmiरुको =			usb_serial_generic_tiocmiरुको,
	.अक्षरs_in_buffer =		cypress_अक्षरs_in_buffer,
	.throttle =		 	cypress_throttle,
	.unthrottle =			cypress_unthrottle,
	.पढ़ो_पूर्णांक_callback =		cypress_पढ़ो_पूर्णांक_callback,
	.ग_लिखो_पूर्णांक_callback =		cypress_ग_लिखो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver cypress_hidcom_device = अणु
	.driver = अणु
		.owner =		THIS_MODULE,
		.name =			"cyphidcom",
	पूर्ण,
	.description =			"HID->COM RS232 Adapter",
	.id_table =			id_table_cyphidcomrs232,
	.num_ports =			1,
	.port_probe =			cypress_hidcom_port_probe,
	.port_हटाओ =			cypress_port_हटाओ,
	.खोलो =				cypress_खोलो,
	.बंद =			cypress_बंद,
	.dtr_rts =			cypress_dtr_rts,
	.ग_लिखो =			cypress_ग_लिखो,
	.ग_लिखो_room =			cypress_ग_लिखो_room,
	.set_termios =			cypress_set_termios,
	.tiocmget =			cypress_tiocmget,
	.tiocmset =			cypress_tiocmset,
	.tiocmiरुको =			usb_serial_generic_tiocmiरुको,
	.अक्षरs_in_buffer =		cypress_अक्षरs_in_buffer,
	.throttle =			cypress_throttle,
	.unthrottle =			cypress_unthrottle,
	.पढ़ो_पूर्णांक_callback =		cypress_पढ़ो_पूर्णांक_callback,
	.ग_लिखो_पूर्णांक_callback =		cypress_ग_लिखो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver cypress_ca42v2_device = अणु
	.driver = अणु
		.owner =		THIS_MODULE,
		.name =			"nokiaca42v2",
	पूर्ण,
	.description =			"Nokia CA-42 V2 Adapter",
	.id_table =			id_table_nokiaca42v2,
	.num_ports =			1,
	.port_probe =			cypress_ca42v2_port_probe,
	.port_हटाओ =			cypress_port_हटाओ,
	.खोलो =				cypress_खोलो,
	.बंद =			cypress_बंद,
	.dtr_rts =			cypress_dtr_rts,
	.ग_लिखो =			cypress_ग_लिखो,
	.ग_लिखो_room =			cypress_ग_लिखो_room,
	.set_termios =			cypress_set_termios,
	.tiocmget =			cypress_tiocmget,
	.tiocmset =			cypress_tiocmset,
	.tiocmiरुको =			usb_serial_generic_tiocmiरुको,
	.अक्षरs_in_buffer =		cypress_अक्षरs_in_buffer,
	.throttle =			cypress_throttle,
	.unthrottle =			cypress_unthrottle,
	.पढ़ो_पूर्णांक_callback =		cypress_पढ़ो_पूर्णांक_callback,
	.ग_लिखो_पूर्णांक_callback =		cypress_ग_लिखो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&cypress_earthmate_device, &cypress_hidcom_device,
	&cypress_ca42v2_device, शून्य
पूर्ण;

/*****************************************************************************
 * Cypress serial helper functions
 *****************************************************************************/

/* FRWD Dongle hidcom needs to skip reset and speed checks */
अटल अंतरभूत bool is_frwd(काष्ठा usb_device *dev)
अणु
	वापस ((le16_to_cpu(dev->descriptor.idVenकरोr) == VENDOR_ID_FRWD) &&
		(le16_to_cpu(dev->descriptor.idProduct) == PRODUCT_ID_CYPHIDCOM_FRWD));
पूर्ण

अटल पूर्णांक analyze_baud_rate(काष्ठा usb_serial_port *port, speed_t new_rate)
अणु
	काष्ठा cypress_निजी *priv;
	priv = usb_get_serial_port_data(port);

	अगर (unstable_bauds)
		वापस new_rate;

	/* FRWD Dongle uses 115200 bps */
	अगर (is_frwd(port->serial->dev))
		वापस new_rate;

	/*
	 * The general purpose firmware क्रम the Cypress M8 allows क्रम
	 * a maximum speed of 57600bps (I have no idea whether DeLorme
	 * chose to use the general purpose firmware or not), अगर you
	 * need to modअगरy this speed setting क्रम your own project
	 * please add your own chiptype and modअगरy the code likewise.
	 * The Cypress HID->COM device will work successfully up to
	 * 115200bps (but the actual throughput is around 3kBps).
	 */
	अगर (port->serial->dev->speed == USB_SPEED_LOW) अणु
		/*
		 * Mike Isely <isely@pobox.com> 2-Feb-2008: The
		 * Cypress app note that describes this mechanism
		 * states the the low-speed part can't handle more
		 * than 800 bytes/sec, in which हाल 4800 baud is the
		 * safest speed क्रम a part like that.
		 */
		अगर (new_rate > 4800) अणु
			dev_dbg(&port->dev,
				"%s - failed setting baud rate, device incapable speed %d\n",
				__func__, new_rate);
			वापस -1;
		पूर्ण
	पूर्ण
	चयन (priv->chiptype) अणु
	हाल CT_EARTHMATE:
		अगर (new_rate <= 600) अणु
			/* 300 and 600 baud rates are supported under
			 * the generic firmware, but are not used with
			 * NMEA and SiRF protocols */
			dev_dbg(&port->dev,
				"%s - failed setting baud rate, unsupported speed of %d on Earthmate GPS\n",
				__func__, new_rate);
			वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस new_rate;
पूर्ण


/* This function can either set or retrieve the current serial line settings */
अटल पूर्णांक cypress_serial_control(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, speed_t baud_rate, पूर्णांक data_bits,
	पूर्णांक stop_bits, पूर्णांक parity_enable, पूर्णांक parity_type, पूर्णांक reset,
	पूर्णांक cypress_request_type)
अणु
	पूर्णांक new_baudrate = 0, retval = 0, tries = 0;
	काष्ठा cypress_निजी *priv;
	काष्ठा device *dev = &port->dev;
	u8 *feature_buffer;
	स्थिर अचिन्हित पूर्णांक feature_len = 5;
	अचिन्हित दीर्घ flags;

	priv = usb_get_serial_port_data(port);

	अगर (!priv->comm_is_ok)
		वापस -ENODEV;

	feature_buffer = kसुस्मृति(feature_len, माप(u8), GFP_KERNEL);
	अगर (!feature_buffer)
		वापस -ENOMEM;

	चयन (cypress_request_type) अणु
	हाल CYPRESS_SET_CONFIG:
		/* 0 means 'Hang up' so doesn't change the true bit rate */
		new_baudrate = priv->baud_rate;
		अगर (baud_rate && baud_rate != priv->baud_rate) अणु
			dev_dbg(dev, "%s - baud rate is changing\n", __func__);
			retval = analyze_baud_rate(port, baud_rate);
			अगर (retval >= 0) अणु
				new_baudrate = retval;
				dev_dbg(dev, "%s - New baud rate set to %d\n",
					__func__, new_baudrate);
			पूर्ण
		पूर्ण
		dev_dbg(dev, "%s - baud rate is being sent as %d\n", __func__,
			new_baudrate);

		/* fill the feature_buffer with new configuration */
		put_unaligned_le32(new_baudrate, feature_buffer);
		feature_buffer[4] |= data_bits;   /* assign data bits in 2 bit space ( max 3 ) */
		/* 1 bit gap */
		feature_buffer[4] |= (stop_bits << 3);   /* assign stop bits in 1 bit space */
		feature_buffer[4] |= (parity_enable << 4);   /* assign parity flag in 1 bit space */
		feature_buffer[4] |= (parity_type << 5);   /* assign parity type in 1 bit space */
		/* 1 bit gap */
		feature_buffer[4] |= (reset << 7);   /* assign reset at end of byte, 1 bit space */

		dev_dbg(dev, "%s - device is being sent this feature report:\n", __func__);
		dev_dbg(dev, "%s - %02X - %02X - %02X - %02X - %02X\n", __func__,
			feature_buffer[0], feature_buffer[1],
			feature_buffer[2], feature_buffer[3],
			feature_buffer[4]);

		करो अणु
			retval = usb_control_msg(port->serial->dev,
					usb_sndctrlpipe(port->serial->dev, 0),
					HID_REQ_SET_REPORT,
					USB_सूची_OUT | USB_RECIP_INTERFACE | USB_TYPE_CLASS,
					0x0300, 0, feature_buffer,
					feature_len, 500);

			अगर (tries++ >= 3)
				अवरोध;

		पूर्ण जबतक (retval != feature_len &&
			 retval != -ENODEV);

		अगर (retval != feature_len) अणु
			dev_err(dev, "%s - failed sending serial line settings - %d\n",
				__func__, retval);
			cypress_set_dead(port);
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&priv->lock, flags);
			priv->baud_rate = new_baudrate;
			priv->current_config = feature_buffer[4];
			spin_unlock_irqrestore(&priv->lock, flags);
			/* If we asked क्रम a speed change encode it */
			अगर (baud_rate)
				tty_encode_baud_rate(tty,
					new_baudrate, new_baudrate);
		पूर्ण
	अवरोध;
	हाल CYPRESS_GET_CONFIG:
		अगर (priv->get_cfg_unsafe) अणु
			/* Not implemented क्रम this device,
			   and अगर we try to करो it we're likely
			   to crash the hardware. */
			retval = -ENOTTY;
			जाओ out;
		पूर्ण
		dev_dbg(dev, "%s - retrieving serial line settings\n", __func__);
		करो अणु
			retval = usb_control_msg(port->serial->dev,
					usb_rcvctrlpipe(port->serial->dev, 0),
					HID_REQ_GET_REPORT,
					USB_सूची_IN | USB_RECIP_INTERFACE | USB_TYPE_CLASS,
					0x0300, 0, feature_buffer,
					feature_len, 500);

			अगर (tries++ >= 3)
				अवरोध;
		पूर्ण जबतक (retval != feature_len
						&& retval != -ENODEV);

		अगर (retval != feature_len) अणु
			dev_err(dev, "%s - failed to retrieve serial line settings - %d\n",
				__func__, retval);
			cypress_set_dead(port);
			जाओ out;
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&priv->lock, flags);
			/* store the config in one byte, and later
			   use bit masks to check values */
			priv->current_config = feature_buffer[4];
			priv->baud_rate = get_unaligned_le32(feature_buffer);
			spin_unlock_irqrestore(&priv->lock, flags);
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&priv->lock, flags);
	++priv->cmd_count;
	spin_unlock_irqrestore(&priv->lock, flags);
out:
	kमुक्त(feature_buffer);
	वापस retval;
पूर्ण /* cypress_serial_control */


अटल व्योम cypress_set_dead(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (!priv->comm_is_ok) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस;
	पूर्ण
	priv->comm_is_ok = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_err(&port->dev, "cypress_m8 suspending failing port %d - "
		"interval might be too short\n", port->port_number);
पूर्ण


/*****************************************************************************
 * Cypress serial driver functions
 *****************************************************************************/


अटल पूर्णांक cypress_generic_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cypress_निजी *priv;

	अगर (!port->पूर्णांकerrupt_out_urb || !port->पूर्णांकerrupt_in_urb) अणु
		dev_err(&port->dev, "required endpoint is missing\n");
		वापस -ENODEV;
	पूर्ण

	priv = kzalloc(माप(काष्ठा cypress_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->comm_is_ok = !0;
	spin_lock_init(&priv->lock);
	अगर (kfअगरo_alloc(&priv->ग_लिखो_fअगरo, CYPRESS_BUF_SIZE, GFP_KERNEL)) अणु
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	/* Skip reset क्रम FRWD device. It is a workaound:
	   device hangs अगर it receives SET_CONFIGURE in Configured
	   state. */
	अगर (!is_frwd(serial->dev))
		usb_reset_configuration(serial->dev);

	priv->cmd_ctrl = 0;
	priv->line_control = 0;
	priv->rx_flags = 0;
	/* Default packet क्रमmat setting is determined by packet size.
	   Anything with a size larger then 9 must have a separate
	   count field since the 3 bit count field is otherwise too
	   small.  Otherwise we can use the slightly more compact
	   क्रमmat.  This is in accordance with the cypress_m8 serial
	   converter app note. */
	अगर (port->पूर्णांकerrupt_out_size > 9)
		priv->pkt_fmt = packet_क्रमmat_1;
	अन्यथा
		priv->pkt_fmt = packet_क्रमmat_2;

	अगर (पूर्णांकerval > 0) अणु
		priv->ग_लिखो_urb_पूर्णांकerval = पूर्णांकerval;
		priv->पढ़ो_urb_पूर्णांकerval = पूर्णांकerval;
		dev_dbg(&port->dev, "%s - read & write intervals forced to %d\n",
			__func__, पूर्णांकerval);
	पूर्ण अन्यथा अणु
		priv->ग_लिखो_urb_पूर्णांकerval = port->पूर्णांकerrupt_out_urb->पूर्णांकerval;
		priv->पढ़ो_urb_पूर्णांकerval = port->पूर्णांकerrupt_in_urb->पूर्णांकerval;
		dev_dbg(&port->dev, "%s - intervals: read=%d write=%d\n",
			__func__, priv->पढ़ो_urb_पूर्णांकerval,
			priv->ग_लिखो_urb_पूर्णांकerval);
	पूर्ण
	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;

	वापस 0;
पूर्ण


अटल पूर्णांक cypress_earthmate_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cypress_निजी *priv;
	पूर्णांक ret;

	ret = cypress_generic_port_probe(port);
	अगर (ret) अणु
		dev_dbg(&port->dev, "%s - Failed setting up port\n", __func__);
		वापस ret;
	पूर्ण

	priv = usb_get_serial_port_data(port);
	priv->chiptype = CT_EARTHMATE;
	/* All Earthmate devices use the separated-count packet
	   क्रमmat!  Idiotic. */
	priv->pkt_fmt = packet_क्रमmat_1;
	अगर (serial->dev->descriptor.idProduct !=
				cpu_to_le16(PRODUCT_ID_EARTHMATEUSB)) अणु
		/* The old original USB Earthmate seemed able to
		   handle GET_CONFIG requests; everything they've
		   produced since that समय crashes अगर this command is
		   attempted :-( */
		dev_dbg(&port->dev,
			"%s - Marking this device as unsafe for GET_CONFIG commands\n",
			__func__);
		priv->get_cfg_unsafe = !0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_hidcom_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv;
	पूर्णांक ret;

	ret = cypress_generic_port_probe(port);
	अगर (ret) अणु
		dev_dbg(&port->dev, "%s - Failed setting up port\n", __func__);
		वापस ret;
	पूर्ण

	priv = usb_get_serial_port_data(port);
	priv->chiptype = CT_CYPHIDCOM;

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_ca42v2_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv;
	पूर्णांक ret;

	ret = cypress_generic_port_probe(port);
	अगर (ret) अणु
		dev_dbg(&port->dev, "%s - Failed setting up port\n", __func__);
		वापस ret;
	पूर्ण

	priv = usb_get_serial_port_data(port);
	priv->chiptype = CT_CA42V2;

	वापस 0;
पूर्ण

अटल व्योम cypress_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv;

	priv = usb_get_serial_port_data(port);

	kfअगरo_मुक्त(&priv->ग_लिखो_fअगरo);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक cypress_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	अगर (!priv->comm_is_ok)
		वापस -EIO;

	/* clear halts beक्रमe खोलो */
	usb_clear_halt(serial->dev, 0x81);
	usb_clear_halt(serial->dev, 0x02);

	spin_lock_irqsave(&priv->lock, flags);
	/* reset पढ़ो/ग_लिखो statistics */
	priv->bytes_in = 0;
	priv->bytes_out = 0;
	priv->cmd_count = 0;
	priv->rx_flags = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Set termios */
	cypress_send(port);

	अगर (tty)
		cypress_set_termios(tty, port, शून्य);

	/* setup the port and start पढ़ोing from the device */
	usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_in_urb, serial->dev,
		usb_rcvपूर्णांकpipe(serial->dev, port->पूर्णांकerrupt_in_endpoपूर्णांकAddress),
		port->पूर्णांकerrupt_in_urb->transfer_buffer,
		port->पूर्णांकerrupt_in_urb->transfer_buffer_length,
		cypress_पढ़ो_पूर्णांक_callback, port, priv->पढ़ो_urb_पूर्णांकerval);
	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);

	अगर (result) अणु
		dev_err(&port->dev,
			"%s - failed submitting read urb, error %d\n",
							__func__, result);
		cypress_set_dead(port);
	पूर्ण

	वापस result;
पूर्ण /* cypress_खोलो */

अटल व्योम cypress_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	/* drop dtr and rts */
	spin_lock_irq(&priv->lock);
	अगर (on == 0)
		priv->line_control = 0;
	अन्यथा 
		priv->line_control = CONTROL_DTR | CONTROL_RTS;
	priv->cmd_ctrl = 1;
	spin_unlock_irq(&priv->lock);
	cypress_ग_लिखो(शून्य, port, शून्य, 0);
पूर्ण

अटल व्योम cypress_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	kfअगरo_reset_out(&priv->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s - stopping urbs\n", __func__);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	usb_समाप्त_urb(port->पूर्णांकerrupt_out_urb);

	अगर (stats)
		dev_info(&port->dev, "Statistics: %d Bytes In | %d Bytes Out | %d Commands Issued\n",
			priv->bytes_in, priv->bytes_out, priv->cmd_count);
पूर्ण /* cypress_बंद */


अटल पूर्णांक cypress_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);

	dev_dbg(&port->dev, "%s - %d bytes\n", __func__, count);

	/* line control commands, which need to be executed immediately,
	   are not put पूर्णांकo the buffer क्रम obvious reasons.
	 */
	अगर (priv->cmd_ctrl) अणु
		count = 0;
		जाओ finish;
	पूर्ण

	अगर (!count)
		वापस count;

	count = kfअगरo_in_locked(&priv->ग_लिखो_fअगरo, buf, count, &priv->lock);

finish:
	cypress_send(port);

	वापस count;
पूर्ण /* cypress_ग_लिखो */


अटल व्योम cypress_send(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक count = 0, result, offset, actual_size;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	अचिन्हित दीर्घ flags;

	अगर (!priv->comm_is_ok)
		वापस;

	dev_dbg(dev, "%s - interrupt out size is %d\n", __func__,
		port->पूर्णांकerrupt_out_size);

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->ग_लिखो_urb_in_use) अणु
		dev_dbg(dev, "%s - can't write, urb in use\n", __func__);
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	/* clear buffer */
	स_रखो(port->पूर्णांकerrupt_out_urb->transfer_buffer, 0,
						port->पूर्णांकerrupt_out_size);

	spin_lock_irqsave(&priv->lock, flags);
	चयन (priv->pkt_fmt) अणु
	शेष:
	हाल packet_क्रमmat_1:
		/* this is क्रम the CY7C64013... */
		offset = 2;
		port->पूर्णांकerrupt_out_buffer[0] = priv->line_control;
		अवरोध;
	हाल packet_क्रमmat_2:
		/* this is क्रम the CY7C63743... */
		offset = 1;
		port->पूर्णांकerrupt_out_buffer[0] = priv->line_control;
		अवरोध;
	पूर्ण

	अगर (priv->line_control & CONTROL_RESET)
		priv->line_control &= ~CONTROL_RESET;

	अगर (priv->cmd_ctrl) अणु
		priv->cmd_count++;
		dev_dbg(dev, "%s - line control command being issued\n", __func__);
		spin_unlock_irqrestore(&priv->lock, flags);
		जाओ send;
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&priv->lock, flags);

	count = kfअगरo_out_locked(&priv->ग_लिखो_fअगरo,
					&port->पूर्णांकerrupt_out_buffer[offset],
					port->पूर्णांकerrupt_out_size - offset,
					&priv->lock);
	अगर (count == 0)
		वापस;

	चयन (priv->pkt_fmt) अणु
	शेष:
	हाल packet_क्रमmat_1:
		port->पूर्णांकerrupt_out_buffer[1] = count;
		अवरोध;
	हाल packet_क्रमmat_2:
		port->पूर्णांकerrupt_out_buffer[0] |= count;
	पूर्ण

	dev_dbg(dev, "%s - count is %d\n", __func__, count);

send:
	spin_lock_irqsave(&priv->lock, flags);
	priv->ग_लिखो_urb_in_use = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (priv->cmd_ctrl)
		actual_size = 1;
	अन्यथा
		actual_size = count +
			      (priv->pkt_fmt == packet_क्रमmat_1 ? 2 : 1);

	usb_serial_debug_data(dev, __func__, port->पूर्णांकerrupt_out_size,
			      port->पूर्णांकerrupt_out_urb->transfer_buffer);

	usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_out_urb, port->serial->dev,
		usb_sndपूर्णांकpipe(port->serial->dev, port->पूर्णांकerrupt_out_endpoपूर्णांकAddress),
		port->पूर्णांकerrupt_out_buffer, actual_size,
		cypress_ग_लिखो_पूर्णांक_callback, port, priv->ग_लिखो_urb_पूर्णांकerval);
	result = usb_submit_urb(port->पूर्णांकerrupt_out_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_err_console(port,
				"%s - failed submitting write urb, error %d\n",
							__func__, result);
		priv->ग_लिखो_urb_in_use = 0;
		cypress_set_dead(port);
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->cmd_ctrl)
		priv->cmd_ctrl = 0;

	/* करो not count the line control and size bytes */
	priv->bytes_out += count;
	spin_unlock_irqrestore(&priv->lock, flags);

	usb_serial_port_softपूर्णांक(port);
पूर्ण /* cypress_send */


/* वापसs how much space is available in the soft buffer */
अटल पूर्णांक cypress_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक room = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	room = kfअगरo_avail(&priv->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण


अटल पूर्णांक cypress_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	__u8 status, control;
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	control = priv->line_control;
	status = priv->current_status;
	spin_unlock_irqrestore(&priv->lock, flags);

	result = ((control & CONTROL_DTR)        ? TIOCM_DTR : 0)
		| ((control & CONTROL_RTS)       ? TIOCM_RTS : 0)
		| ((status & UART_CTS)        ? TIOCM_CTS : 0)
		| ((status & UART_DSR)        ? TIOCM_DSR : 0)
		| ((status & UART_RI)         ? TIOCM_RI  : 0)
		| ((status & UART_CD)         ? TIOCM_CD  : 0);

	dev_dbg(&port->dev, "%s - result = %x\n", __func__, result);

	वापस result;
पूर्ण


अटल पूर्णांक cypress_tiocmset(काष्ठा tty_काष्ठा *tty,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (set & TIOCM_RTS)
		priv->line_control |= CONTROL_RTS;
	अगर (set & TIOCM_DTR)
		priv->line_control |= CONTROL_DTR;
	अगर (clear & TIOCM_RTS)
		priv->line_control &= ~CONTROL_RTS;
	अगर (clear & TIOCM_DTR)
		priv->line_control &= ~CONTROL_DTR;
	priv->cmd_ctrl = 1;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस cypress_ग_लिखो(tty, port, शून्य, 0);
पूर्ण

अटल व्योम cypress_earthmate_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	tty_encode_baud_rate(tty, 4800, 4800);
पूर्ण

अटल व्योम cypress_set_termios(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	पूर्णांक data_bits, stop_bits, parity_type, parity_enable;
	अचिन्हित पूर्णांक cflag;
	अचिन्हित दीर्घ flags;
	__u8 oldlines;
	पूर्णांक linechange = 0;

	/* Unsupported features need clearing */
	tty->termios.c_cflag &= ~(CMSPAR|CRTSCTS);

	cflag = tty->termios.c_cflag;

	/* set number of data bits, parity, stop bits */
	/* when parity is disabled the parity type bit is ignored */

	/* 1 means 2 stop bits, 0 means 1 stop bit */
	stop_bits = cflag & CSTOPB ? 1 : 0;

	अगर (cflag & PARENB) अणु
		parity_enable = 1;
		/* 1 means odd parity, 0 means even parity */
		parity_type = cflag & PARODD ? 1 : 0;
	पूर्ण अन्यथा
		parity_enable = parity_type = 0;

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		data_bits = 0;
		अवरोध;
	हाल CS6:
		data_bits = 1;
		अवरोध;
	हाल CS7:
		data_bits = 2;
		अवरोध;
	हाल CS8:
		data_bits = 3;
		अवरोध;
	शेष:
		dev_err(dev, "%s - CSIZE was set, but not CS5-CS8\n", __func__);
		data_bits = 3;
	पूर्ण
	spin_lock_irqsave(&priv->lock, flags);
	oldlines = priv->line_control;
	अगर ((cflag & CBAUD) == B0) अणु
		/* drop dtr and rts */
		dev_dbg(dev, "%s - dropping the lines, baud rate 0bps\n", __func__);
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	पूर्ण अन्यथा
		priv->line_control = (CONTROL_DTR | CONTROL_RTS);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(dev, "%s - sending %d stop_bits, %d parity_enable, %d parity_type, %d data_bits (+5)\n",
		__func__, stop_bits, parity_enable, parity_type, data_bits);

	cypress_serial_control(tty, port, tty_get_baud_rate(tty),
			data_bits, stop_bits,
			parity_enable, parity_type,
			0, CYPRESS_SET_CONFIG);

	/* we perक्रमm a CYPRESS_GET_CONFIG so that the current settings are
	 * filled पूर्णांकo the निजी काष्ठाure this should confirm that all is
	 * working अगर it वापसs what we just set */
	cypress_serial_control(tty, port, 0, 0, 0, 0, 0, 0, CYPRESS_GET_CONFIG);

	/* Here we can define custom tty settings क्रम devices; the मुख्य tty
	 * termios flag base comes from empeg.c */

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->chiptype == CT_EARTHMATE && priv->baud_rate == 4800) अणु
		dev_dbg(dev, "Using custom termios settings for a baud rate of 4800bps.\n");
		/* define custom termios settings क्रम NMEA protocol */

		tty->termios.c_अगरlag /* input modes - */
			&= ~(IGNBRK  /* disable ignore अवरोध */
			| BRKINT     /* disable अवरोध causes पूर्णांकerrupt */
			| PARMRK     /* disable mark parity errors */
			| ISTRIP     /* disable clear high bit of input अक्षर */
			| INLCR      /* disable translate NL to CR */
			| IGNCR      /* disable ignore CR */
			| ICRNL      /* disable translate CR to NL */
			| IXON);     /* disable enable XON/XOFF flow control */

		tty->termios.c_oflag /* output modes */
			&= ~OPOST;    /* disable postprocess output अक्षर */

		tty->termios.c_lflag /* line discipline modes */
			&= ~(ECHO     /* disable echo input अक्षरacters */
			| ECHONL      /* disable echo new line */
			| ICANON      /* disable erase, समाप्त, werase, and rprnt
					 special अक्षरacters */
			| ISIG        /* disable पूर्णांकerrupt, quit, and suspend
					 special अक्षरacters */
			| IEXTEN);    /* disable non-POSIX special अक्षरacters */
	पूर्ण /* CT_CYPHIDCOM: Application should handle this क्रम device */

	linechange = (priv->line_control != oldlines);
	spin_unlock_irqrestore(&priv->lock, flags);

	/* अगर necessary, set lines */
	अगर (linechange) अणु
		priv->cmd_ctrl = 1;
		cypress_ग_लिखो(tty, port, शून्य, 0);
	पूर्ण
पूर्ण /* cypress_set_termios */


/* वापसs amount of data still left in soft buffer */
अटल पूर्णांक cypress_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक अक्षरs = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अक्षरs = kfअगरo_len(&priv->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;
पूर्ण


अटल व्योम cypress_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);

	spin_lock_irq(&priv->lock);
	priv->rx_flags = THROTTLED;
	spin_unlock_irq(&priv->lock);
पूर्ण


अटल व्योम cypress_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	पूर्णांक actually_throttled, result;

	spin_lock_irq(&priv->lock);
	actually_throttled = priv->rx_flags & ACTUALLY_THROTTLED;
	priv->rx_flags = 0;
	spin_unlock_irq(&priv->lock);

	अगर (!priv->comm_is_ok)
		वापस;

	अगर (actually_throttled) अणु
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (result) अणु
			dev_err(&port->dev, "%s - failed submitting read urb, "
					"error %d\n", __func__, result);
			cypress_set_dead(port);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम cypress_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &urb->dev->dev;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	अक्षर tty_flag = TTY_NORMAL;
	पूर्णांक bytes = 0;
	पूर्णांक result;
	पूर्णांक i = 0;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0: /* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* precursor to disconnect so just go away */
		वापस;
	हाल -EPIPE:
		/* Can't call usb_clear_halt जबतक in_पूर्णांकerrupt */
		fallthrough;
	शेष:
		/* something ugly is going on... */
		dev_err(dev, "%s - unexpected nonzero read status received: %d\n",
			__func__, status);
		cypress_set_dead(port);
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->rx_flags & THROTTLED) अणु
		dev_dbg(dev, "%s - now throttling\n", __func__);
		priv->rx_flags |= ACTUALLY_THROTTLED;
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	tty = tty_port_tty_get(&port->port);
	अगर (!tty) अणु
		dev_dbg(dev, "%s - bad tty pointer - exiting\n", __func__);
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	result = urb->actual_length;
	चयन (priv->pkt_fmt) अणु
	शेष:
	हाल packet_क्रमmat_1:
		/* This is क्रम the CY7C64013... */
		priv->current_status = data[0] & 0xF8;
		bytes = data[1] + 2;
		i = 2;
		अवरोध;
	हाल packet_क्रमmat_2:
		/* This is क्रम the CY7C63743... */
		priv->current_status = data[0] & 0xF8;
		bytes = (data[0] & 0x07) + 1;
		i = 1;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);
	अगर (result < bytes) अणु
		dev_dbg(dev,
			"%s - wrong packet size - received %d bytes but packet said %d bytes\n",
			__func__, result, bytes);
		जाओ जारी_पढ़ो;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	spin_lock_irqsave(&priv->lock, flags);
	/* check to see अगर status has changed */
	अगर (priv->current_status != priv->prev_status) अणु
		u8 delta = priv->current_status ^ priv->prev_status;

		अगर (delta & UART_MSR_MASK) अणु
			अगर (delta & UART_CTS)
				port->icount.cts++;
			अगर (delta & UART_DSR)
				port->icount.dsr++;
			अगर (delta & UART_RI)
				port->icount.rng++;
			अगर (delta & UART_CD)
				port->icount.dcd++;

			wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
		पूर्ण

		priv->prev_status = priv->current_status;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	/* hangup, as defined in acm.c... this might be a bad place क्रम it
	 * though */
	अगर (tty && !C_CLOCAL(tty) && !(priv->current_status & UART_CD)) अणु
		dev_dbg(dev, "%s - calling hangup\n", __func__);
		tty_hangup(tty);
		जाओ जारी_पढ़ो;
	पूर्ण

	/* There is one error bit... I'm assuming it is a parity error
	 * indicator as the generic firmware will set this bit to 1 अगर a
	 * parity error occurs.
	 * I can not find reference to any other error events. */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->current_status & CYP_ERROR) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		tty_flag = TTY_PARITY;
		dev_dbg(dev, "%s - Parity Error detected\n", __func__);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&priv->lock, flags);

	/* process पढ़ो अगर there is data other than line status */
	अगर (bytes > i) अणु
		tty_insert_flip_string_fixed_flag(&port->port, data + i,
				tty_flag, bytes - i);
		tty_flip_buffer_push(&port->port);
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	/* control and status byte(s) are also counted */
	priv->bytes_in += bytes;
	spin_unlock_irqrestore(&priv->lock, flags);

जारी_पढ़ो:
	tty_kref_put(tty);

	/* Continue trying to always पढ़ो */

	अगर (priv->comm_is_ok) अणु
		usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_in_urb, port->serial->dev,
				usb_rcvपूर्णांकpipe(port->serial->dev,
					port->पूर्णांकerrupt_in_endpoपूर्णांकAddress),
				port->पूर्णांकerrupt_in_urb->transfer_buffer,
				port->पूर्णांकerrupt_in_urb->transfer_buffer_length,
				cypress_पढ़ो_पूर्णांक_callback, port,
				priv->पढ़ो_urb_पूर्णांकerval);
		result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
		अगर (result && result != -EPERM) अणु
			dev_err(dev, "%s - failed resubmitting read urb, error %d\n",
				__func__, result);
			cypress_set_dead(port);
		पूर्ण
	पूर्ण
पूर्ण /* cypress_पढ़ो_पूर्णांक_callback */


अटल व्योम cypress_ग_लिखो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cypress_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा device *dev = &urb->dev->dev;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		priv->ग_लिखो_urb_in_use = 0;
		वापस;
	हाल -EPIPE:
		/* Cannot call usb_clear_halt जबतक in_पूर्णांकerrupt */
		fallthrough;
	शेष:
		dev_err(dev, "%s - unexpected nonzero write status received: %d\n",
			__func__, status);
		cypress_set_dead(port);
		अवरोध;
	पूर्ण
	priv->ग_लिखो_urb_in_use = 0;

	/* send any buffered data */
	cypress_send(port);
पूर्ण

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(stats, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(stats, "Enable statistics or not");
module_param(पूर्णांकerval, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(पूर्णांकerval, "Overrides interrupt interval");
module_param(unstable_bauds, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(unstable_bauds, "Allow unstable baud rates");
