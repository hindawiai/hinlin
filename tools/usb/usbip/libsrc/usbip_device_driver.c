<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 *		 2015 Samsung Electronics
 * Author:	 Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *
 * Based on tools/usb/usbip/libsrc/usbip_host_driver.c, which is:
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <linux/usb/ch9.h>

#समावेश <unistd.h>

#समावेश "usbip_host_common.h"
#समावेश "usbip_device_driver.h"

#अघोषित  PROGNAME
#घोषणा PROGNAME "libusbip"

#घोषणा copy_descr_attr16(dev, descr, attr)			\
		((dev)->attr = le16toh((descr)->attr))		\

#घोषणा copy_descr_attr(dev, descr, attr)			\
		((dev)->attr = (descr)->attr)			\

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

अटल काष्ठा अणु
	क्रमागत usb_device_speed speed;
	स्थिर अक्षर *name;
पूर्ण speed_names[] = अणु
	अणु
		.speed = USB_SPEED_UNKNOWN,
		.name = "UNKNOWN",
	पूर्ण,
	अणु
		.speed = USB_SPEED_LOW,
		.name = "low-speed",
	पूर्ण,
	अणु
		.speed = USB_SPEED_FULL,
		.name = "full-speed",
	पूर्ण,
	अणु
		.speed = USB_SPEED_HIGH,
		.name = "high-speed",
	पूर्ण,
	अणु
		.speed = USB_SPEED_WIRELESS,
		.name = "wireless",
	पूर्ण,
	अणु
		.speed = USB_SPEED_SUPER,
		.name = "super-speed",
	पूर्ण,
पूर्ण;

अटल
पूर्णांक पढ़ो_usb_vudc_device(काष्ठा udev_device *sdev, काष्ठा usbip_usb_device *dev)
अणु
	स्थिर अक्षर *path, *name;
	अक्षर filepath[SYSFS_PATH_MAX];
	काष्ठा usb_device_descriptor descr;
	अचिन्हित पूर्णांक i;
	खाता *fd = शून्य;
	काष्ठा udev_device *plat;
	स्थिर अक्षर *speed;
	माप_प्रकार ret;

	plat = udev_device_get_parent(sdev);
	path = udev_device_get_syspath(plat);
	snम_लिखो(filepath, SYSFS_PATH_MAX, "%s/%s",
		 path, VUDC_DEVICE_DESCR_खाता);
	fd = ख_खोलो(filepath, "r");
	अगर (!fd)
		वापस -1;
	ret = ख_पढ़ो((अक्षर *) &descr, माप(descr), 1, fd);
	अगर (ret != 1) अणु
		err("Cannot read vudc device descr file: %s", म_त्रुटि(त्रुटि_सं));
		जाओ err;
	पूर्ण
	ख_बंद(fd);

	copy_descr_attr(dev, &descr, bDeviceClass);
	copy_descr_attr(dev, &descr, bDeviceSubClass);
	copy_descr_attr(dev, &descr, bDeviceProtocol);
	copy_descr_attr(dev, &descr, bNumConfigurations);
	copy_descr_attr16(dev, &descr, idVenकरोr);
	copy_descr_attr16(dev, &descr, idProduct);
	copy_descr_attr16(dev, &descr, bcdDevice);

	म_नकलन(dev->path, path, SYSFS_PATH_MAX - 1);
	dev->path[SYSFS_PATH_MAX - 1] = '\0';

	dev->speed = USB_SPEED_UNKNOWN;
	speed = udev_device_get_sysattr_value(sdev, "current_speed");
	अगर (speed) अणु
		क्रम (i = 0; i < ARRAY_SIZE(speed_names); i++) अणु
			अगर (!म_भेद(speed_names[i].name, speed)) अणु
				dev->speed = speed_names[i].speed;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Only used क्रम user output, little sense to output them in general */
	dev->bNumInterfaces = 0;
	dev->bConfigurationValue = 0;
	dev->busnum = 0;

	name = udev_device_get_sysname(plat);
	म_नकलन(dev->busid, name, SYSFS_BUS_ID_SIZE - 1);
	dev->busid[SYSFS_BUS_ID_SIZE - 1] = '\0';
	वापस 0;
err:
	ख_बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक is_my_device(काष्ठा udev_device *dev)
अणु
	स्थिर अक्षर *driver;

	driver = udev_device_get_property_value(dev, "USB_UDC_NAME");
	वापस driver != शून्य && !म_भेद(driver, USBIP_DEVICE_DRV_NAME);
पूर्ण

अटल पूर्णांक usbip_device_driver_खोलो(काष्ठा usbip_host_driver *hdriver)
अणु
	पूर्णांक ret;

	hdriver->ndevs = 0;
	INIT_LIST_HEAD(&hdriver->edev_list);

	ret = usbip_generic_driver_खोलो(hdriver);
	अगर (ret)
		err("please load " USBIP_CORE_MOD_NAME ".ko and "
		    USBIP_DEVICE_DRV_NAME ".ko!");

	वापस ret;
पूर्ण

काष्ठा usbip_host_driver device_driver = अणु
	.edev_list = LIST_HEAD_INIT(device_driver.edev_list),
	.udev_subप्रणाली = "udc",
	.ops = अणु
		.खोलो = usbip_device_driver_खोलो,
		.बंद = usbip_generic_driver_बंद,
		.refresh_device_list = usbip_generic_refresh_device_list,
		.get_device = usbip_generic_get_device,
		.पढ़ो_device = पढ़ो_usb_vudc_device,
		.is_my_device = is_my_device,
	पूर्ण,
पूर्ण;
