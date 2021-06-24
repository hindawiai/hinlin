<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 *
 * Refactored from usbip_host_driver.c, which is:
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#अगर_अघोषित __USBIP_HOST_COMMON_H
#घोषणा __USBIP_HOST_COMMON_H

#समावेश <मानक_निवेशt.h>
#समावेश <libudev.h>
#समावेश <त्रुटिसं.स>
#समावेश "list.h"
#समावेश "usbip_common.h"
#समावेश "sysfs_utils.h"

काष्ठा usbip_host_driver;

काष्ठा usbip_host_driver_ops अणु
	पूर्णांक (*खोलो)(काष्ठा usbip_host_driver *hdriver);
	व्योम (*बंद)(काष्ठा usbip_host_driver *hdriver);
	पूर्णांक (*refresh_device_list)(काष्ठा usbip_host_driver *hdriver);
	काष्ठा usbip_exported_device * (*get_device)(
		काष्ठा usbip_host_driver *hdriver, पूर्णांक num);

	पूर्णांक (*पढ़ो_device)(काष्ठा udev_device *sdev,
			   काष्ठा usbip_usb_device *dev);
	पूर्णांक (*पढ़ो_पूर्णांकerface)(काष्ठा usbip_usb_device *udev, पूर्णांक i,
			      काष्ठा usbip_usb_पूर्णांकerface *uinf);
	पूर्णांक (*is_my_device)(काष्ठा udev_device *udev);
पूर्ण;

काष्ठा usbip_host_driver अणु
	पूर्णांक ndevs;
	/* list of exported device */
	काष्ठा list_head edev_list;
	स्थिर अक्षर *udev_subप्रणाली;
	काष्ठा usbip_host_driver_ops ops;
पूर्ण;

काष्ठा usbip_exported_device अणु
	काष्ठा udev_device *sudev;
	पूर्णांक32_t status;
	काष्ठा usbip_usb_device udev;
	काष्ठा list_head node;
	काष्ठा usbip_usb_पूर्णांकerface uinf[];
पूर्ण;

/* External API to access the driver */
अटल अंतरभूत पूर्णांक usbip_driver_खोलो(काष्ठा usbip_host_driver *hdriver)
अणु
	अगर (!hdriver->ops.खोलो)
		वापस -EOPNOTSUPP;
	वापस hdriver->ops.खोलो(hdriver);
पूर्ण

अटल अंतरभूत व्योम usbip_driver_बंद(काष्ठा usbip_host_driver *hdriver)
अणु
	अगर (!hdriver->ops.बंद)
		वापस;
	hdriver->ops.बंद(hdriver);
पूर्ण

अटल अंतरभूत पूर्णांक usbip_refresh_device_list(काष्ठा usbip_host_driver *hdriver)
अणु
	अगर (!hdriver->ops.refresh_device_list)
		वापस -EOPNOTSUPP;
	वापस hdriver->ops.refresh_device_list(hdriver);
पूर्ण

अटल अंतरभूत काष्ठा usbip_exported_device *
usbip_get_device(काष्ठा usbip_host_driver *hdriver, पूर्णांक num)
अणु
	अगर (!hdriver->ops.get_device)
		वापस शून्य;
	वापस hdriver->ops.get_device(hdriver, num);
पूर्ण

/* Helper functions क्रम implementing driver backend */
पूर्णांक usbip_generic_driver_खोलो(काष्ठा usbip_host_driver *hdriver);
व्योम usbip_generic_driver_बंद(काष्ठा usbip_host_driver *hdriver);
पूर्णांक usbip_generic_refresh_device_list(काष्ठा usbip_host_driver *hdriver);
पूर्णांक usbip_export_device(काष्ठा usbip_exported_device *edev, पूर्णांक sockfd);
काष्ठा usbip_exported_device *usbip_generic_get_device(
		काष्ठा usbip_host_driver *hdriver, पूर्णांक num);

#पूर्ण_अगर /* __USBIP_HOST_COMMON_H */
