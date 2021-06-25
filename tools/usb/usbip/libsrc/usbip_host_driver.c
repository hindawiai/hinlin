<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <unistd.h>
#समावेश <libudev.h>

#समावेश "usbip_host_common.h"
#समावेश "usbip_host_driver.h"

#अघोषित  PROGNAME
#घोषणा PROGNAME "libusbip"

अटल पूर्णांक is_my_device(काष्ठा udev_device *dev)
अणु
	स्थिर अक्षर *driver;

	driver = udev_device_get_driver(dev);
	वापस driver != शून्य && !म_भेद(driver, USBIP_HOST_DRV_NAME);
पूर्ण

अटल पूर्णांक usbip_host_driver_खोलो(काष्ठा usbip_host_driver *hdriver)
अणु
	पूर्णांक ret;

	hdriver->ndevs = 0;
	INIT_LIST_HEAD(&hdriver->edev_list);

	ret = usbip_generic_driver_खोलो(hdriver);
	अगर (ret)
		err("please load " USBIP_CORE_MOD_NAME ".ko and "
		    USBIP_HOST_DRV_NAME ".ko!");
	वापस ret;
पूर्ण

काष्ठा usbip_host_driver host_driver = अणु
	.edev_list = LIST_HEAD_INIT(host_driver.edev_list),
	.udev_subप्रणाली = "usb",
	.ops = अणु
		.खोलो = usbip_host_driver_खोलो,
		.बंद = usbip_generic_driver_बंद,
		.refresh_device_list = usbip_generic_refresh_device_list,
		.get_device = usbip_generic_get_device,
		.पढ़ो_device = पढ़ो_usb_device,
		.पढ़ो_पूर्णांकerface = पढ़ो_usb_पूर्णांकerface,
		.is_my_device = is_my_device,
	पूर्ण,
पूर्ण;
