<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan u2c-12 USB-I2C adapter
 *
 * Copyright (c) 2010-2011 Ericsson AB
 *
 * Derived from:
 *  i2c-tiny-usb.c
 *  Copyright (C) 2006-2007 Till Harbaum (Till@Harbaum.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>

#घोषणा DRIVER_NAME		"i2c-diolan-u2c"

#घोषणा USB_VENDOR_ID_DIOLAN		0x0abf
#घोषणा USB_DEVICE_ID_DIOLAN_U2C	0x3370


/* commands via USB, must match command ids in the firmware */
#घोषणा CMD_I2C_READ		0x01
#घोषणा CMD_I2C_WRITE		0x02
#घोषणा CMD_I2C_SCAN		0x03	/* Returns list of detected devices */
#घोषणा CMD_I2C_RELEASE_SDA	0x04
#घोषणा CMD_I2C_RELEASE_SCL	0x05
#घोषणा CMD_I2C_DROP_SDA	0x06
#घोषणा CMD_I2C_DROP_SCL	0x07
#घोषणा CMD_I2C_READ_SDA	0x08
#घोषणा CMD_I2C_READ_SCL	0x09
#घोषणा CMD_GET_FW_VERSION	0x0a
#घोषणा CMD_GET_SERIAL		0x0b
#घोषणा CMD_I2C_START		0x0c
#घोषणा CMD_I2C_STOP		0x0d
#घोषणा CMD_I2C_REPEATED_START	0x0e
#घोषणा CMD_I2C_PUT_BYTE	0x0f
#घोषणा CMD_I2C_GET_BYTE	0x10
#घोषणा CMD_I2C_PUT_ACK		0x11
#घोषणा CMD_I2C_GET_ACK		0x12
#घोषणा CMD_I2C_PUT_BYTE_ACK	0x13
#घोषणा CMD_I2C_GET_BYTE_ACK	0x14
#घोषणा CMD_I2C_SET_SPEED	0x1b
#घोषणा CMD_I2C_GET_SPEED	0x1c
#घोषणा CMD_I2C_SET_CLK_SYNC	0x24
#घोषणा CMD_I2C_GET_CLK_SYNC	0x25
#घोषणा CMD_I2C_SET_CLK_SYNC_TO	0x26
#घोषणा CMD_I2C_GET_CLK_SYNC_TO	0x27

#घोषणा RESP_OK			0x00
#घोषणा RESP_FAILED		0x01
#घोषणा RESP_BAD_MEMADDR	0x04
#घोषणा RESP_DATA_ERR		0x05
#घोषणा RESP_NOT_IMPLEMENTED	0x06
#घोषणा RESP_NACK		0x07
#घोषणा RESP_TIMEOUT		0x09

#घोषणा U2C_I2C_SPEED_FAST	0	/* 400 kHz */
#घोषणा U2C_I2C_SPEED_STD	1	/* 100 kHz */
#घोषणा U2C_I2C_SPEED_2KHZ	242	/* 2 kHz, minimum speed */
#घोषणा U2C_I2C_SPEED(f)	((DIV_ROUND_UP(1000000, (f)) - 10) / 2 + 1)

#घोषणा U2C_I2C_FREQ(s)		(1000000 / (2 * (s - 1) + 10))

#घोषणा DIOLAN_USB_TIMEOUT	100	/* in ms */
#घोषणा DIOLAN_SYNC_TIMEOUT	20	/* in ms */

#घोषणा DIOLAN_OUTBUF_LEN	128
#घोषणा DIOLAN_FLUSH_LEN	(DIOLAN_OUTBUF_LEN - 4)
#घोषणा DIOLAN_INBUF_LEN	256	/* Maximum supported receive length */

/* Structure to hold all of our device specअगरic stuff */
काष्ठा i2c_diolan_u2c अणु
	u8 obuffer[DIOLAN_OUTBUF_LEN];	/* output buffer */
	u8 ibuffer[DIOLAN_INBUF_LEN];	/* input buffer */
	पूर्णांक ep_in, ep_out;              /* Endpoपूर्णांकs    */
	काष्ठा usb_device *usb_dev;	/* the usb device क्रम this device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;/* the पूर्णांकerface क्रम this device */
	काष्ठा i2c_adapter adapter;	/* i2c related things */
	पूर्णांक olen;			/* Output buffer length */
	पूर्णांक ocount;			/* Number of enqueued messages */
पूर्ण;

अटल uपूर्णांक frequency = I2C_MAX_STANDARD_MODE_FREQ;	/* I2C घड़ी frequency in Hz */

module_param(frequency, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(frequency, "I2C clock frequency in hertz");

/* usb layer */

/* Send command to device, and get response. */
अटल पूर्णांक diolan_usb_transfer(काष्ठा i2c_diolan_u2c *dev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक actual;
	पूर्णांक i;

	अगर (!dev->olen || !dev->ocount)
		वापस -EINVAL;

	ret = usb_bulk_msg(dev->usb_dev,
			   usb_sndbulkpipe(dev->usb_dev, dev->ep_out),
			   dev->obuffer, dev->olen, &actual,
			   DIOLAN_USB_TIMEOUT);
	अगर (!ret) अणु
		क्रम (i = 0; i < dev->ocount; i++) अणु
			पूर्णांक पंचांगpret;

			पंचांगpret = usb_bulk_msg(dev->usb_dev,
					      usb_rcvbulkpipe(dev->usb_dev,
							      dev->ep_in),
					      dev->ibuffer,
					      माप(dev->ibuffer), &actual,
					      DIOLAN_USB_TIMEOUT);
			/*
			 * Stop command processing अगर a previous command
			 * वापसed an error.
			 * Note that we still need to retrieve all messages.
			 */
			अगर (ret < 0)
				जारी;
			ret = पंचांगpret;
			अगर (ret == 0 && actual > 0) अणु
				चयन (dev->ibuffer[actual - 1]) अणु
				हाल RESP_NACK:
					/*
					 * Return ENXIO अगर NACK was received as
					 * response to the address phase,
					 * EIO otherwise
					 */
					ret = i == 1 ? -ENXIO : -EIO;
					अवरोध;
				हाल RESP_TIMEOUT:
					ret = -ETIMEDOUT;
					अवरोध;
				हाल RESP_OK:
					/* strip off वापस code */
					ret = actual - 1;
					अवरोध;
				शेष:
					ret = -EIO;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	dev->olen = 0;
	dev->ocount = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक diolan_ग_लिखो_cmd(काष्ठा i2c_diolan_u2c *dev, bool flush)
अणु
	अगर (flush || dev->olen >= DIOLAN_FLUSH_LEN)
		वापस diolan_usb_transfer(dev);
	वापस 0;
पूर्ण

/* Send command (no data) */
अटल पूर्णांक diolan_usb_cmd(काष्ठा i2c_diolan_u2c *dev, u8 command, bool flush)
अणु
	dev->obuffer[dev->olen++] = command;
	dev->ocount++;
	वापस diolan_ग_लिखो_cmd(dev, flush);
पूर्ण

/* Send command with one byte of data */
अटल पूर्णांक diolan_usb_cmd_data(काष्ठा i2c_diolan_u2c *dev, u8 command, u8 data,
			       bool flush)
अणु
	dev->obuffer[dev->olen++] = command;
	dev->obuffer[dev->olen++] = data;
	dev->ocount++;
	वापस diolan_ग_लिखो_cmd(dev, flush);
पूर्ण

/* Send command with two bytes of data */
अटल पूर्णांक diolan_usb_cmd_data2(काष्ठा i2c_diolan_u2c *dev, u8 command, u8 d1,
				u8 d2, bool flush)
अणु
	dev->obuffer[dev->olen++] = command;
	dev->obuffer[dev->olen++] = d1;
	dev->obuffer[dev->olen++] = d2;
	dev->ocount++;
	वापस diolan_ग_लिखो_cmd(dev, flush);
पूर्ण

/*
 * Flush input queue.
 * If we करोn't करो this at startup and the controller has queued up
 * messages which were not retrieved, it will stop responding
 * at some poपूर्णांक.
 */
अटल व्योम diolan_flush_input(काष्ठा i2c_diolan_u2c *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		पूर्णांक actual = 0;
		पूर्णांक ret;

		ret = usb_bulk_msg(dev->usb_dev,
				   usb_rcvbulkpipe(dev->usb_dev, dev->ep_in),
				   dev->ibuffer, माप(dev->ibuffer), &actual,
				   DIOLAN_USB_TIMEOUT);
		अगर (ret < 0 || actual == 0)
			अवरोध;
	पूर्ण
	अगर (i == 10)
		dev_err(&dev->पूर्णांकerface->dev, "Failed to flush input buffer\n");
पूर्ण

अटल पूर्णांक diolan_i2c_start(काष्ठा i2c_diolan_u2c *dev)
अणु
	वापस diolan_usb_cmd(dev, CMD_I2C_START, false);
पूर्ण

अटल पूर्णांक diolan_i2c_repeated_start(काष्ठा i2c_diolan_u2c *dev)
अणु
	वापस diolan_usb_cmd(dev, CMD_I2C_REPEATED_START, false);
पूर्ण

अटल पूर्णांक diolan_i2c_stop(काष्ठा i2c_diolan_u2c *dev)
अणु
	वापस diolan_usb_cmd(dev, CMD_I2C_STOP, true);
पूर्ण

अटल पूर्णांक diolan_i2c_get_byte_ack(काष्ठा i2c_diolan_u2c *dev, bool ack,
				   u8 *byte)
अणु
	पूर्णांक ret;

	ret = diolan_usb_cmd_data(dev, CMD_I2C_GET_BYTE_ACK, ack, true);
	अगर (ret > 0)
		*byte = dev->ibuffer[0];
	अन्यथा अगर (ret == 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक diolan_i2c_put_byte_ack(काष्ठा i2c_diolan_u2c *dev, u8 byte)
अणु
	वापस diolan_usb_cmd_data(dev, CMD_I2C_PUT_BYTE_ACK, byte, false);
पूर्ण

अटल पूर्णांक diolan_set_speed(काष्ठा i2c_diolan_u2c *dev, u8 speed)
अणु
	वापस diolan_usb_cmd_data(dev, CMD_I2C_SET_SPEED, speed, true);
पूर्ण

/* Enable or disable घड़ी synchronization (stretching) */
अटल पूर्णांक diolan_set_घड़ी_synch(काष्ठा i2c_diolan_u2c *dev, bool enable)
अणु
	वापस diolan_usb_cmd_data(dev, CMD_I2C_SET_CLK_SYNC, enable, true);
पूर्ण

/* Set घड़ी synchronization समयout in ms */
अटल पूर्णांक diolan_set_घड़ी_synch_समयout(काष्ठा i2c_diolan_u2c *dev, पूर्णांक ms)
अणु
	पूर्णांक to_val = ms * 10;

	वापस diolan_usb_cmd_data2(dev, CMD_I2C_SET_CLK_SYNC_TO,
				    to_val & 0xff, (to_val >> 8) & 0xff, true);
पूर्ण

अटल व्योम diolan_fw_version(काष्ठा i2c_diolan_u2c *dev)
अणु
	पूर्णांक ret;

	ret = diolan_usb_cmd(dev, CMD_GET_FW_VERSION, true);
	अगर (ret >= 2)
		dev_info(&dev->पूर्णांकerface->dev,
			 "Diolan U2C firmware version %u.%u\n",
			 (अचिन्हित पूर्णांक)dev->ibuffer[0],
			 (अचिन्हित पूर्णांक)dev->ibuffer[1]);
पूर्ण

अटल व्योम diolan_get_serial(काष्ठा i2c_diolan_u2c *dev)
अणु
	पूर्णांक ret;
	u32 serial;

	ret = diolan_usb_cmd(dev, CMD_GET_SERIAL, true);
	अगर (ret >= 4) अणु
		serial = le32_to_cpu(*(u32 *)dev->ibuffer);
		dev_info(&dev->पूर्णांकerface->dev,
			 "Diolan U2C serial number %u\n", serial);
	पूर्ण
पूर्ण

अटल पूर्णांक diolan_init(काष्ठा i2c_diolan_u2c *dev)
अणु
	पूर्णांक speed, ret;

	अगर (frequency >= 2 * I2C_MAX_STANDARD_MODE_FREQ) अणु
		speed = U2C_I2C_SPEED_FAST;
		frequency = I2C_MAX_FAST_MODE_FREQ;
	पूर्ण अन्यथा अगर (frequency >= I2C_MAX_STANDARD_MODE_FREQ || frequency == 0) अणु
		speed = U2C_I2C_SPEED_STD;
		frequency = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण अन्यथा अणु
		speed = U2C_I2C_SPEED(frequency);
		अगर (speed > U2C_I2C_SPEED_2KHZ)
			speed = U2C_I2C_SPEED_2KHZ;
		frequency = U2C_I2C_FREQ(speed);
	पूर्ण

	dev_info(&dev->पूर्णांकerface->dev,
		 "Diolan U2C at USB bus %03d address %03d speed %d Hz\n",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum, frequency);

	diolan_flush_input(dev);
	diolan_fw_version(dev);
	diolan_get_serial(dev);

	/* Set I2C speed */
	ret = diolan_set_speed(dev, speed);
	अगर (ret < 0)
		वापस ret;

	/* Configure I2C घड़ी synchronization */
	ret = diolan_set_घड़ी_synch(dev, speed != U2C_I2C_SPEED_FAST);
	अगर (ret < 0)
		वापस ret;

	अगर (speed != U2C_I2C_SPEED_FAST)
		ret = diolan_set_घड़ी_synch_समयout(dev, DIOLAN_SYNC_TIMEOUT);

	वापस ret;
पूर्ण

/* i2c layer */

अटल पूर्णांक diolan_usb_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs,
			   पूर्णांक num)
अणु
	काष्ठा i2c_diolan_u2c *dev = i2c_get_adapdata(adapter);
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i, j;
	पूर्णांक ret, sret;

	ret = diolan_i2c_start(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];
		अगर (i) अणु
			ret = diolan_i2c_repeated_start(dev);
			अगर (ret < 0)
				जाओ पात;
		पूर्ण
		ret = diolan_i2c_put_byte_ack(dev,
					      i2c_8bit_addr_from_msg(pmsg));
		अगर (ret < 0)
			जाओ पात;
		अगर (pmsg->flags & I2C_M_RD) अणु
			क्रम (j = 0; j < pmsg->len; j++) अणु
				u8 byte;
				bool ack = j < pmsg->len - 1;

				/*
				 * Don't send NACK अगर this is the first byte
				 * of a SMBUS_BLOCK message.
				 */
				अगर (j == 0 && (pmsg->flags & I2C_M_RECV_LEN))
					ack = true;

				ret = diolan_i2c_get_byte_ack(dev, ack, &byte);
				अगर (ret < 0)
					जाओ पात;
				/*
				 * Adjust count अगर first received byte is length
				 */
				अगर (j == 0 && (pmsg->flags & I2C_M_RECV_LEN)) अणु
					अगर (byte == 0
					    || byte > I2C_SMBUS_BLOCK_MAX) अणु
						ret = -EPROTO;
						जाओ पात;
					पूर्ण
					pmsg->len += byte;
				पूर्ण
				pmsg->buf[j] = byte;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < pmsg->len; j++) अणु
				ret = diolan_i2c_put_byte_ack(dev,
							      pmsg->buf[j]);
				अगर (ret < 0)
					जाओ पात;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = num;
पात:
	sret = diolan_i2c_stop(dev);
	अगर (sret < 0 && ret >= 0)
		ret = sret;
	वापस ret;
पूर्ण

/*
 * Return list of supported functionality.
 */
अटल u32 diolan_usb_func(काष्ठा i2c_adapter *a)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA | I2C_FUNC_SMBUS_BLOCK_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm diolan_usb_algorithm = अणु
	.master_xfer = diolan_usb_xfer,
	.functionality = diolan_usb_func,
पूर्ण;

/* device layer */

अटल स्थिर काष्ठा usb_device_id diolan_u2c_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_DIOLAN, USB_DEVICE_ID_DIOLAN_U2C) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, diolan_u2c_table);

अटल व्योम diolan_u2c_मुक्त(काष्ठा i2c_diolan_u2c *dev)
अणु
	usb_put_dev(dev->usb_dev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक diolan_u2c_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *hostअगर = पूर्णांकerface->cur_altsetting;
	काष्ठा i2c_diolan_u2c *dev;
	पूर्णांक ret;

	अगर (hostअगर->desc.bInterfaceNumber != 0
	    || hostअगर->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण
	dev->ep_out = hostअगर->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress;
	dev->ep_in = hostअगर->endpoपूर्णांक[1].desc.bEndpoपूर्णांकAddress;

	dev->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = पूर्णांकerface;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* setup i2c adapter description */
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_HWMON;
	dev->adapter.algo = &diolan_usb_algorithm;
	i2c_set_adapdata(&dev->adapter, dev);
	snम_लिखो(dev->adapter.name, माप(dev->adapter.name),
		 DRIVER_NAME " at bus %03d device %03d",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	dev->adapter.dev.parent = &dev->पूर्णांकerface->dev;

	/* initialize diolan i2c पूर्णांकerface */
	ret = diolan_init(dev);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकerface->dev, "failed to initialize adapter\n");
		जाओ error_मुक्त;
	पूर्ण

	/* and finally attach to i2c layer */
	ret = i2c_add_adapter(&dev->adapter);
	अगर (ret < 0)
		जाओ error_मुक्त;

	dev_dbg(&पूर्णांकerface->dev, "connected " DRIVER_NAME "\n");

	वापस 0;

error_मुक्त:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	diolan_u2c_मुक्त(dev);
error:
	वापस ret;
पूर्ण

अटल व्योम diolan_u2c_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा i2c_diolan_u2c *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	i2c_del_adapter(&dev->adapter);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	diolan_u2c_मुक्त(dev);

	dev_dbg(&पूर्णांकerface->dev, "disconnected\n");
पूर्ण

अटल काष्ठा usb_driver diolan_u2c_driver = अणु
	.name = DRIVER_NAME,
	.probe = diolan_u2c_probe,
	.disconnect = diolan_u2c_disconnect,
	.id_table = diolan_u2c_table,
पूर्ण;

module_usb_driver(diolan_u2c_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION(DRIVER_NAME " driver");
MODULE_LICENSE("GPL");
