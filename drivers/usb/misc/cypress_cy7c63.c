<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* cypress_cy7c63.c
*
* Copyright (c) 2006-2007 Oliver Bock (bock@tfh-berlin.de)
*
*	This driver is based on the Cypress USB Driver by Marcus Maul
*	(cyport) and the 2.0 version of Greg Kroah-Harपंचांगan's
*	USB Skeleton driver.
*
*	This is a generic driver क्रम the Cypress CY7C63xxx family.
*	For the समय being it enables you to पढ़ो from and ग_लिखो to
*	the single I/O ports of the device.
*
*	Supported venकरोrs:	AK Modul-Bus Computer GmbH
*				(Firmware "Port-Chip")
*
*	Supported devices:	CY7C63001A-PC
*				CY7C63001C-PXC
*				CY7C63001C-SXC
*
*	Supported functions:	Read/Write Ports
*
*
*	For up-to-date inक्रमmation please visit:
*	http://www.obock.de/kernel/cypress
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#घोषणा DRIVER_AUTHOR		"Oliver Bock (bock@tfh-berlin.de)"
#घोषणा DRIVER_DESC		"Cypress CY7C63xxx USB driver"

#घोषणा CYPRESS_VENDOR_ID	0xa2c
#घोषणा CYPRESS_PRODUCT_ID	0x8

#घोषणा CYPRESS_READ_PORT	0x4
#घोषणा CYPRESS_WRITE_PORT	0x5

#घोषणा CYPRESS_READ_RAM	0x2
#घोषणा CYPRESS_WRITE_RAM	0x3
#घोषणा CYPRESS_READ_ROM	0x1

#घोषणा CYPRESS_READ_PORT_ID0	0
#घोषणा CYPRESS_WRITE_PORT_ID0	0
#घोषणा CYPRESS_READ_PORT_ID1	0x2
#घोषणा CYPRESS_WRITE_PORT_ID1	1

#घोषणा CYPRESS_MAX_REQSIZE	8


/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id cypress_table[] = अणु
	अणु USB_DEVICE(CYPRESS_VENDOR_ID, CYPRESS_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, cypress_table);

/* काष्ठाure to hold all of our device specअगरic stuff */
काष्ठा cypress अणु
	काष्ठा usb_device *	udev;
	अचिन्हित अक्षर		port[2];
पूर्ण;

/* used to send usb control messages to device */
अटल पूर्णांक venकरोr_command(काष्ठा cypress *dev, अचिन्हित अक्षर request,
			  अचिन्हित अक्षर address, अचिन्हित अक्षर data)
अणु
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक pipe;
	अचिन्हित अक्षर *iobuf;

	/* allocate some memory क्रम the i/o buffer*/
	iobuf = kzalloc(CYPRESS_MAX_REQSIZE, GFP_KERNEL);
	अगर (!iobuf) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	dev_dbg(&dev->udev->dev, "Sending usb_control_msg (data: %d)\n", data);

	/* prepare usb control message and send it upstream */
	pipe = usb_rcvctrlpipe(dev->udev, 0);
	retval = usb_control_msg(dev->udev, pipe, request,
				 USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				 address, data, iobuf, CYPRESS_MAX_REQSIZE,
				 USB_CTRL_GET_TIMEOUT);

	/* store वापसed data (more READs to be added) */
	चयन (request) अणु
		हाल CYPRESS_READ_PORT:
			अगर (address == CYPRESS_READ_PORT_ID0) अणु
				dev->port[0] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"READ_PORT0 returned: %d\n",
					dev->port[0]);
			पूर्ण
			अन्यथा अगर (address == CYPRESS_READ_PORT_ID1) अणु
				dev->port[1] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"READ_PORT1 returned: %d\n",
					dev->port[1]);
			पूर्ण
			अवरोध;
	पूर्ण

	kमुक्त(iobuf);
error:
	वापस retval;
पूर्ण

/* ग_लिखो port value */
अटल sमाप_प्रकार ग_लिखो_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count,
			  पूर्णांक port_num, पूर्णांक ग_लिखो_id)
अणु
	पूर्णांक value = -1;
	पूर्णांक result = 0;

	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा cypress *cyp = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&cyp->udev->dev, "WRITE_PORT%d called\n", port_num);

	/* validate input data */
	अगर (माला_पूछो(buf, "%d", &value) < 1) अणु
		result = -EINVAL;
		जाओ error;
	पूर्ण
	अगर (value < 0 || value > 255) अणु
		result = -EINVAL;
		जाओ error;
	पूर्ण

	result = venकरोr_command(cyp, CYPRESS_WRITE_PORT, ग_लिखो_id,
				(अचिन्हित अक्षर)value);

	dev_dbg(&cyp->udev->dev, "Result of vendor_command: %d\n\n", result);
error:
	वापस result < 0 ? result : count;
पूर्ण

/* attribute callback handler (ग_लिखो) */
अटल sमाप_प्रकार port0_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस ग_लिखो_port(dev, attr, buf, count, 0, CYPRESS_WRITE_PORT_ID0);
पूर्ण

/* attribute callback handler (ग_लिखो) */
अटल sमाप_प्रकार port1_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस ग_लिखो_port(dev, attr, buf, count, 1, CYPRESS_WRITE_PORT_ID1);
पूर्ण

/* पढ़ो port value */
अटल sमाप_प्रकार पढ़ो_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf, पूर्णांक port_num, पूर्णांक पढ़ो_id)
अणु
	पूर्णांक result = 0;

	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा cypress *cyp = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&cyp->udev->dev, "READ_PORT%d called\n", port_num);

	result = venकरोr_command(cyp, CYPRESS_READ_PORT, पढ़ो_id, 0);

	dev_dbg(&cyp->udev->dev, "Result of vendor_command: %d\n\n", result);

	वापस प्र_लिखो(buf, "%d", cyp->port[port_num]);
पूर्ण

/* attribute callback handler (पढ़ो) */
अटल sमाप_प्रकार port0_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस पढ़ो_port(dev, attr, buf, 0, CYPRESS_READ_PORT_ID0);
पूर्ण
अटल DEVICE_ATTR_RW(port0);

/* attribute callback handler (पढ़ो) */
अटल sमाप_प्रकार port1_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस पढ़ो_port(dev, attr, buf, 1, CYPRESS_READ_PORT_ID1);
पूर्ण
अटल DEVICE_ATTR_RW(port1);

अटल काष्ठा attribute *cypress_attrs[] = अणु
	&dev_attr_port0.attr,
	&dev_attr_port1.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cypress);

अटल पूर्णांक cypress_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cypress *dev = शून्य;
	पूर्णांक retval = -ENOMEM;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ error_mem;

	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* let the user know that the device is now attached */
	dev_info(&पूर्णांकerface->dev,
		 "Cypress CY7C63xxx device now attached\n");
	वापस 0;

error_mem:
	वापस retval;
पूर्ण

अटल व्योम cypress_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा cypress *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	/* the पूर्णांकfdata can be set to शून्य only after the
	 * device files have been हटाओd */
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	usb_put_dev(dev->udev);

	dev_info(&पूर्णांकerface->dev,
		 "Cypress CY7C63xxx device now disconnected\n");

	kमुक्त(dev);
पूर्ण

अटल काष्ठा usb_driver cypress_driver = अणु
	.name = "cypress_cy7c63",
	.probe = cypress_probe,
	.disconnect = cypress_disconnect,
	.id_table = cypress_table,
	.dev_groups = cypress_groups,
पूर्ण;

module_usb_driver(cypress_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_LICENSE("GPL");
