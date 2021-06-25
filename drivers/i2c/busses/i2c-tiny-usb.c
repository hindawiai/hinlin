<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * driver क्रम the i2c-tiny-usb adapter - 1.0
 * http://www.harbaum.org/till/i2c_tiny_usb
 *
 * Copyright (C) 2006-2007 Till Harbaum (Till@Harbaum.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/* include पूर्णांकerfaces to usb layer */
#समावेश <linux/usb.h>

/* include पूर्णांकerface to i2c layer */
#समावेश <linux/i2c.h>

/* commands via USB, must match command ids in the firmware */
#घोषणा CMD_ECHO		0
#घोषणा CMD_GET_FUNC		1
#घोषणा CMD_SET_DELAY		2
#घोषणा CMD_GET_STATUS		3

#घोषणा CMD_I2C_IO		4
#घोषणा CMD_I2C_IO_BEGIN	(1<<0)
#घोषणा CMD_I2C_IO_END		(1<<1)

/* i2c bit delay, शेष is 10us -> 100kHz max
   (in practice, due to additional delays in the i2c bitbanging
   code this results in a i2c घड़ी of about 50kHz) */
अटल अचिन्हित लघु delay = 10;
module_param(delay, uलघु, 0);
MODULE_PARM_DESC(delay, "bit delay in microseconds "
		 "(default is 10us for 100kHz max)");

अटल पूर्णांक usb_पढ़ो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
		    पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len);

अटल पूर्णांक usb_ग_लिखो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
		     पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len);

/* ----- begin of i2c layer ---------------------------------------------- */

#घोषणा STATUS_IDLE		0
#घोषणा STATUS_ADDRESS_ACK	1
#घोषणा STATUS_ADDRESS_NAK	2

अटल पूर्णांक usb_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	अचिन्हित अक्षर *pstatus;
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i, ret;

	dev_dbg(&adapter->dev, "master xfer %d messages:\n", num);

	pstatus = kदो_स्मृति(माप(*pstatus), GFP_KERNEL);
	अगर (!pstatus)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < num ; i++) अणु
		पूर्णांक cmd = CMD_I2C_IO;

		अगर (i == 0)
			cmd |= CMD_I2C_IO_BEGIN;

		अगर (i == num-1)
			cmd |= CMD_I2C_IO_END;

		pmsg = &msgs[i];

		dev_dbg(&adapter->dev,
			"  %d: %s (flags %d) %d bytes to 0x%02x\n",
			i, pmsg->flags & I2C_M_RD ? "read" : "write",
			pmsg->flags, pmsg->len, pmsg->addr);

		/* and directly send the message */
		अगर (pmsg->flags & I2C_M_RD) अणु
			/* पढ़ो data */
			अगर (usb_पढ़ो(adapter, cmd,
				     pmsg->flags, pmsg->addr,
				     pmsg->buf, pmsg->len) != pmsg->len) अणु
				dev_err(&adapter->dev,
					"failure reading data\n");
				ret = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ग_लिखो data */
			अगर (usb_ग_लिखो(adapter, cmd,
				      pmsg->flags, pmsg->addr,
				      pmsg->buf, pmsg->len) != pmsg->len) अणु
				dev_err(&adapter->dev,
					"failure writing data\n");
				ret = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण

		/* पढ़ो status */
		अगर (usb_पढ़ो(adapter, CMD_GET_STATUS, 0, 0, pstatus, 1) != 1) अणु
			dev_err(&adapter->dev, "failure reading status\n");
			ret = -EIO;
			जाओ out;
		पूर्ण

		dev_dbg(&adapter->dev, "  status = %d\n", *pstatus);
		अगर (*pstatus == STATUS_ADDRESS_NAK) अणु
			ret = -ENXIO;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = i;
out:
	kमुक्त(pstatus);
	वापस ret;
पूर्ण

अटल u32 usb_func(काष्ठा i2c_adapter *adapter)
अणु
	__le32 *pfunc;
	u32 ret;

	pfunc = kदो_स्मृति(माप(*pfunc), GFP_KERNEL);

	/* get functionality from adapter */
	अगर (!pfunc || usb_पढ़ो(adapter, CMD_GET_FUNC, 0, 0, pfunc,
			       माप(*pfunc)) != माप(*pfunc)) अणु
		dev_err(&adapter->dev, "failure reading functionality\n");
		ret = 0;
		जाओ out;
	पूर्ण

	ret = le32_to_cpup(pfunc);
out:
	kमुक्त(pfunc);
	वापस ret;
पूर्ण

/* This is the actual algorithm we define */
अटल स्थिर काष्ठा i2c_algorithm usb_algorithm = अणु
	.master_xfer	= usb_xfer,
	.functionality	= usb_func,
पूर्ण;

/* ----- end of i2c layer ------------------------------------------------ */

/* ----- begin of usb layer ---------------------------------------------- */

/*
 * Initially the usb i2c पूर्णांकerface uses a vid/pid pair करोnated by
 * Future Technology Devices International Ltd., later a pair was
 * bought from EZPrototypes
 */
अटल स्थिर काष्ठा usb_device_id i2c_tiny_usb_table[] = अणु
	अणु USB_DEVICE(0x0403, 0xc631) पूर्ण,   /* FTDI */
	अणु USB_DEVICE(0x1c40, 0x0534) पूर्ण,   /* EZPrototypes */
	अणु पूर्ण                               /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, i2c_tiny_usb_table);

/* Structure to hold all of our device specअगरic stuff */
काष्ठा i2c_tiny_usb अणु
	काष्ठा usb_device *usb_dev; /* the usb device क्रम this device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface; /* the पूर्णांकerface क्रम this device */
	काष्ठा i2c_adapter adapter; /* i2c related things */
पूर्ण;

अटल पूर्णांक usb_पढ़ो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
		    पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len)
अणु
	काष्ठा i2c_tiny_usb *dev = (काष्ठा i2c_tiny_usb *)adapter->algo_data;
	व्योम *dmadata = kदो_स्मृति(len, GFP_KERNEL);
	पूर्णांक ret;

	अगर (!dmadata)
		वापस -ENOMEM;

	/* करो control transfer */
	ret = usb_control_msg(dev->usb_dev, usb_rcvctrlpipe(dev->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE |
			       USB_सूची_IN, value, index, dmadata, len, 2000);

	स_नकल(data, dmadata, len);
	kमुक्त(dmadata);
	वापस ret;
पूर्ण

अटल पूर्णांक usb_ग_लिखो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
		     पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len)
अणु
	काष्ठा i2c_tiny_usb *dev = (काष्ठा i2c_tiny_usb *)adapter->algo_data;
	व्योम *dmadata = kmemdup(data, len, GFP_KERNEL);
	पूर्णांक ret;

	अगर (!dmadata)
		वापस -ENOMEM;

	/* करो control transfer */
	ret = usb_control_msg(dev->usb_dev, usb_sndctrlpipe(dev->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			       value, index, dmadata, len, 2000);

	kमुक्त(dmadata);
	वापस ret;
पूर्ण

अटल व्योम i2c_tiny_usb_मुक्त(काष्ठा i2c_tiny_usb *dev)
अणु
	usb_put_dev(dev->usb_dev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक i2c_tiny_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा i2c_tiny_usb *dev;
	पूर्णांक retval = -ENOMEM;
	u16 version;

	dev_dbg(&पूर्णांकerface->dev, "probing usb device\n");

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		dev_err(&पूर्णांकerface->dev, "Out of memory\n");
		जाओ error;
	पूर्ण

	dev->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = पूर्णांकerface;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	version = le16_to_cpu(dev->usb_dev->descriptor.bcdDevice);
	dev_info(&पूर्णांकerface->dev,
		 "version %x.%02x found at bus %03d address %03d\n",
		 version >> 8, version & 0xff,
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	/* setup i2c adapter description */
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_HWMON;
	dev->adapter.algo = &usb_algorithm;
	dev->adapter.algo_data = dev;
	snम_लिखो(dev->adapter.name, माप(dev->adapter.name),
		 "i2c-tiny-usb at bus %03d device %03d",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	अगर (usb_ग_लिखो(&dev->adapter, CMD_SET_DELAY, delay, 0, शून्य, 0) != 0) अणु
		dev_err(&dev->adapter.dev,
			"failure setting delay to %dus\n", delay);
		retval = -EIO;
		जाओ error;
	पूर्ण

	dev->adapter.dev.parent = &dev->पूर्णांकerface->dev;

	/* and finally attach to i2c layer */
	i2c_add_adapter(&dev->adapter);

	/* inक्रमm user about successful attachment to i2c layer */
	dev_info(&dev->adapter.dev, "connected i2c-tiny-usb device\n");

	वापस 0;

 error:
	अगर (dev)
		i2c_tiny_usb_मुक्त(dev);

	वापस retval;
पूर्ण

अटल व्योम i2c_tiny_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा i2c_tiny_usb *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	i2c_del_adapter(&dev->adapter);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	i2c_tiny_usb_मुक्त(dev);

	dev_dbg(&पूर्णांकerface->dev, "disconnected\n");
पूर्ण

अटल काष्ठा usb_driver i2c_tiny_usb_driver = अणु
	.name		= "i2c-tiny-usb",
	.probe		= i2c_tiny_usb_probe,
	.disconnect	= i2c_tiny_usb_disconnect,
	.id_table	= i2c_tiny_usb_table,
पूर्ण;

module_usb_driver(i2c_tiny_usb_driver);

/* ----- end of usb layer ------------------------------------------------ */

MODULE_AUTHOR("Till Harbaum <Till@Harbaum.org>");
MODULE_DESCRIPTION("i2c-tiny-usb driver v1.0");
MODULE_LICENSE("GPL");
