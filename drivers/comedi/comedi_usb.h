<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* comedi_usb.h
 * header file क्रम USB Comedi drivers
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDI_USB_H
#घोषणा _COMEDI_USB_H

#समावेश <linux/usb.h>

#समावेश "comedidev.h"

काष्ठा usb_पूर्णांकerface *comedi_to_usb_पूर्णांकerface(काष्ठा comedi_device *dev);
काष्ठा usb_device *comedi_to_usb_dev(काष्ठा comedi_device *dev);

पूर्णांक comedi_usb_स्वतः_config(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   काष्ठा comedi_driver *driver, अचिन्हित दीर्घ context);
व्योम comedi_usb_स्वतः_unconfig(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

पूर्णांक comedi_usb_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
			       काष्ठा usb_driver *usb_driver);
व्योम comedi_usb_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा usb_driver *usb_driver);

/**
 * module_comedi_usb_driver() - Helper macro क्रम रेजिस्टरing a comedi USB driver
 * @__comedi_driver: comedi_driver काष्ठा
 * @__usb_driver: usb_driver काष्ठा
 *
 * Helper macro क्रम comedi USB drivers which करो not करो anything special
 * in module init/निकास. This eliminates a lot of boilerplate. Each
 * module may only use this macro once, and calling it replaces
 * module_init() and module_निकास()
 */
#घोषणा module_comedi_usb_driver(__comedi_driver, __usb_driver) \
	module_driver(__comedi_driver, comedi_usb_driver_रेजिस्टर, \
			comedi_usb_driver_unरेजिस्टर, &(__usb_driver))

#पूर्ण_अगर /* _COMEDI_USB_H */
