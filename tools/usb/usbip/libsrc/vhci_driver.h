<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#अगर_अघोषित __VHCI_DRIVER_H
#घोषणा __VHCI_DRIVER_H

#समावेश <libudev.h>
#समावेश <मानक_निवेशt.h>

#समावेश "usbip_common.h"

#घोषणा USBIP_VHCI_BUS_TYPE "platform"
#घोषणा USBIP_VHCI_DEVICE_NAME "vhci_hcd.0"

क्रमागत hub_speed अणु
	HUB_SPEED_HIGH = 0,
	HUB_SPEED_SUPER,
पूर्ण;

काष्ठा usbip_imported_device अणु
	क्रमागत hub_speed hub;
	uपूर्णांक8_t port;
	uपूर्णांक32_t status;

	uपूर्णांक32_t devid;

	uपूर्णांक8_t busnum;
	uपूर्णांक8_t devnum;

	/* usbip_class_device list */
	काष्ठा usbip_usb_device udev;
पूर्ण;

काष्ठा usbip_vhci_driver अणु

	/* /sys/devices/platक्रमm/vhci_hcd */
	काष्ठा udev_device *hc_device;

	पूर्णांक ncontrollers;
	पूर्णांक nports;
	काष्ठा usbip_imported_device idev[];
पूर्ण;


बाह्य काष्ठा usbip_vhci_driver *vhci_driver;

पूर्णांक usbip_vhci_driver_खोलो(व्योम);
व्योम usbip_vhci_driver_बंद(व्योम);

पूर्णांक  usbip_vhci_refresh_device_list(व्योम);


पूर्णांक usbip_vhci_get_मुक्त_port(uपूर्णांक32_t speed);
पूर्णांक usbip_vhci_attach_device2(uपूर्णांक8_t port, पूर्णांक sockfd, uपूर्णांक32_t devid,
		uपूर्णांक32_t speed);

/* will be हटाओd */
पूर्णांक usbip_vhci_attach_device(uपूर्णांक8_t port, पूर्णांक sockfd, uपूर्णांक8_t busnum,
		uपूर्णांक8_t devnum, uपूर्णांक32_t speed);

पूर्णांक usbip_vhci_detach_device(uपूर्णांक8_t port);

पूर्णांक usbip_vhci_imported_device_dump(काष्ठा usbip_imported_device *idev);

#पूर्ण_अगर /* __VHCI_DRIVER_H */
