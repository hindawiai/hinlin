<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Nano River Technologies viperboard driver
 *
 *  This is the core driver क्रम the viperboard. There are cell drivers
 *  available क्रम I2C, ADC and both GPIOs. SPI is not yet supported.
 *  The drivers करो not support all features the board exposes. See user
 *  manual of the viperboard.
 *
 *  (C) 2012 by Lemonage GmbH
 *  Author: Lars Poeschel <poeschel@lemonage.de>
 *  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/viperboard.h>

#समावेश <linux/usb.h>


अटल स्थिर काष्ठा usb_device_id vprbrd_table[] = अणु
	अणु USB_DEVICE(0x2058, 0x1005) पूर्ण,   /* Nano River Technologies */
	अणु पूर्ण                               /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, vprbrd_table);

अटल स्थिर काष्ठा mfd_cell vprbrd_devs[] = अणु
	अणु
		.name = "viperboard-gpio",
	पूर्ण,
	अणु
		.name = "viperboard-i2c",
	पूर्ण,
	अणु
		.name = "viperboard-adc",
	पूर्ण,
पूर्ण;

अटल पूर्णांक vprbrd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा vprbrd *vb;

	u16 version = 0;
	पूर्णांक pipe, ret;

	/* allocate memory क्रम our device state and initialize it */
	vb = kzalloc(माप(*vb), GFP_KERNEL);
	अगर (!vb)
		वापस -ENOMEM;

	mutex_init(&vb->lock);

	vb->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, vb);
	dev_set_drvdata(&vb->pdev.dev, vb);

	/* get version inक्रमmation, major first, minor then */
	pipe = usb_rcvctrlpipe(vb->usb_dev, 0);
	ret = usb_control_msg(vb->usb_dev, pipe, VPRBRD_USB_REQUEST_MAJOR,
		VPRBRD_USB_TYPE_IN, 0x0000, 0x0000, vb->buf, 1,
		VPRBRD_USB_TIMEOUT_MS);
	अगर (ret == 1)
		version = vb->buf[0];

	ret = usb_control_msg(vb->usb_dev, pipe, VPRBRD_USB_REQUEST_MINOR,
		VPRBRD_USB_TYPE_IN, 0x0000, 0x0000, vb->buf, 1,
		VPRBRD_USB_TIMEOUT_MS);
	अगर (ret == 1) अणु
		version <<= 8;
		version = version | vb->buf[0];
	पूर्ण

	dev_info(&पूर्णांकerface->dev,
		 "version %x.%02x found at bus %03d address %03d\n",
		 version >> 8, version & 0xff,
		 vb->usb_dev->bus->busnum, vb->usb_dev->devnum);

	ret = mfd_add_hotplug_devices(&पूर्णांकerface->dev, vprbrd_devs,
				      ARRAY_SIZE(vprbrd_devs));
	अगर (ret != 0) अणु
		dev_err(&पूर्णांकerface->dev, "Failed to add mfd devices to core.");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	अगर (vb) अणु
		usb_put_dev(vb->usb_dev);
		kमुक्त(vb);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vprbrd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा vprbrd *vb = usb_get_पूर्णांकfdata(पूर्णांकerface);

	mfd_हटाओ_devices(&पूर्णांकerface->dev);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	usb_put_dev(vb->usb_dev);
	kमुक्त(vb);

	dev_dbg(&पूर्णांकerface->dev, "disconnected\n");
पूर्ण

अटल काष्ठा usb_driver vprbrd_driver = अणु
	.name		= "viperboard",
	.probe		= vprbrd_probe,
	.disconnect	= vprbrd_disconnect,
	.id_table	= vprbrd_table,
पूर्ण;

module_usb_driver(vprbrd_driver);

MODULE_DESCRIPTION("Nano River Technologies viperboard mfd core driver");
MODULE_AUTHOR("Lars Poeschel <poeschel@lemonage.de>");
MODULE_LICENSE("GPL");
