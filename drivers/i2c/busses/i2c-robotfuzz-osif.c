<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम RobotFuzz OSIF
 *
 * Copyright (c) 2013 Andrew Lunn <andrew@lunn.ch>
 * Copyright (c) 2007 Barry Carter <Barry.Carter@robotfuzz.com>
 *
 * Based on the i2c-tiny-usb by
 *
 * Copyright (C) 2006 Til Harbaum (Till@Harbaum.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#घोषणा OSIFI2C_READ		20
#घोषणा OSIFI2C_WRITE		21
#घोषणा OSIFI2C_STOP		22
#घोषणा OSIFI2C_STATUS		23
#घोषणा OSIFI2C_SET_BIT_RATE	24

#घोषणा STATUS_ADDRESS_ACK	0
#घोषणा STATUS_ADDRESS_NAK	2

काष्ठा osअगर_priv अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा i2c_adapter adapter;
	अचिन्हित अक्षर status;
पूर्ण;

अटल पूर्णांक osअगर_usb_पढ़ो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
			 पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len)
अणु
	काष्ठा osअगर_priv *priv = adapter->algo_data;

	वापस usb_control_msg(priv->usb_dev, usb_rcvctrlpipe(priv->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE |
			       USB_सूची_IN, value, index, data, len, 2000);
पूर्ण

अटल पूर्णांक osअगर_usb_ग_लिखो(काष्ठा i2c_adapter *adapter, पूर्णांक cmd,
			  पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक len)
अणु

	काष्ठा osअगर_priv *priv = adapter->algo_data;

	वापस usb_control_msg(priv->usb_dev, usb_sndctrlpipe(priv->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			       value, index, data, len, 2000);
पूर्ण

अटल पूर्णांक osअगर_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs,
			 पूर्णांक num)
अणु
	काष्ठा osअगर_priv *priv = adapter->algo_data;
	काष्ठा i2c_msg *pmsg;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];

		अगर (pmsg->flags & I2C_M_RD) अणु
			ret = osअगर_usb_पढ़ो(adapter, OSIFI2C_READ,
					    pmsg->flags, pmsg->addr,
					    pmsg->buf, pmsg->len);
			अगर (ret != pmsg->len) अणु
				dev_err(&adapter->dev, "failure reading data\n");
				वापस -EREMOTEIO;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = osअगर_usb_ग_लिखो(adapter, OSIFI2C_WRITE,
					     pmsg->flags, pmsg->addr,
					     pmsg->buf, pmsg->len);
			अगर (ret != pmsg->len) अणु
				dev_err(&adapter->dev, "failure writing data\n");
				वापस -EREMOTEIO;
			पूर्ण
		पूर्ण

		ret = osअगर_usb_पढ़ो(adapter, OSIFI2C_STOP, 0, 0, शून्य, 0);
		अगर (ret) अणु
			dev_err(&adapter->dev, "failure sending STOP\n");
			वापस -EREMOTEIO;
		पूर्ण

		/* पढ़ो status */
		ret = osअगर_usb_पढ़ो(adapter, OSIFI2C_STATUS, 0, 0,
				    &priv->status, 1);
		अगर (ret != 1) अणु
			dev_err(&adapter->dev, "failure reading status\n");
			वापस -EREMOTEIO;
		पूर्ण

		अगर (priv->status != STATUS_ADDRESS_ACK) अणु
			dev_dbg(&adapter->dev, "status = %d\n", priv->status);
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

अटल u32 osअगर_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm osअगर_algorithm = अणु
	.master_xfer	= osअगर_xfer,
	.functionality	= osअगर_func,
पूर्ण;

#घोषणा USB_OSIF_VENDOR_ID	0x1964
#घोषणा USB_OSIF_PRODUCT_ID	0x0001

अटल स्थिर काष्ठा usb_device_id osअगर_table[] = अणु
	अणु USB_DEVICE(USB_OSIF_VENDOR_ID, USB_OSIF_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, osअगर_table);

अटल पूर्णांक osअगर_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा osअगर_priv *priv;
	u16 version;

	priv = devm_kzalloc(&पूर्णांकerface->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	priv->पूर्णांकerface = पूर्णांकerface;

	usb_set_पूर्णांकfdata(पूर्णांकerface, priv);

	priv->adapter.owner = THIS_MODULE;
	priv->adapter.class = I2C_CLASS_HWMON;
	priv->adapter.algo = &osअगर_algorithm;
	priv->adapter.algo_data = priv;
	snम_लिखो(priv->adapter.name, माप(priv->adapter.name),
		 "OSIF at bus %03d device %03d",
		 priv->usb_dev->bus->busnum, priv->usb_dev->devnum);

	/*
	 * Set bus frequency. The frequency is:
	 * 120,000,000 / ( 16 + 2 * भाग * 4^prescale).
	 * Using dev = 52, prescale = 0 give 100KHz */
	ret = osअगर_usb_पढ़ो(&priv->adapter, OSIFI2C_SET_BIT_RATE, 52, 0,
			    शून्य, 0);
	अगर (ret) अणु
		dev_err(&पूर्णांकerface->dev, "failure sending bit rate");
		usb_put_dev(priv->usb_dev);
		वापस ret;
	पूर्ण

	i2c_add_adapter(&(priv->adapter));

	version = le16_to_cpu(priv->usb_dev->descriptor.bcdDevice);
	dev_info(&पूर्णांकerface->dev,
		 "version %x.%02x found at bus %03d address %03d",
		 version >> 8, version & 0xff,
		 priv->usb_dev->bus->busnum, priv->usb_dev->devnum);

	वापस 0;
पूर्ण

अटल व्योम osअगर_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा osअगर_priv *priv = usb_get_पूर्णांकfdata(पूर्णांकerface);

	i2c_del_adapter(&(priv->adapter));
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	usb_put_dev(priv->usb_dev);
पूर्ण

अटल काष्ठा usb_driver osअगर_driver = अणु
	.name		= "RobotFuzz Open Source InterFace, OSIF",
	.probe		= osअगर_probe,
	.disconnect	= osअगर_disconnect,
	.id_table	= osअगर_table,
पूर्ण;

module_usb_driver(osअगर_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_AUTHOR("Barry Carter <barry.carter@robotfuzz.com>");
MODULE_DESCRIPTION("RobotFuzz OSIF driver");
MODULE_LICENSE("GPL v2");
