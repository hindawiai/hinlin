<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम USB Mass Storage devices
 * Usual Tables File क्रम usb-storage and libusual
 *
 * Copyright (C) 2009 Alan Stern (stern@rowland.harvard.edu)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb_usual.h>


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

#घोषणा COMPLIANT_DEV	UNUSUAL_DEV

#घोषणा USUAL_DEV(useProto, useTrans) \
अणु USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, useProto, useTrans) पूर्ण

/* Define the device is matched with Venकरोr ID and पूर्णांकerface descriptors */
#घोषणा UNUSUAL_VENDOR_INTF(id_venकरोr, cl, sc, pr, \
			venकरोrName, productName, useProtocol, useTransport, \
			initFunction, flags) \
अणु \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO \
				| USB_DEVICE_ID_MATCH_VENDOR, \
	.idVenकरोr    = (id_venकरोr), \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), \
	.bInterfaceProtocol = (pr), \
	.driver_info = (flags) \
पूर्ण

स्थिर काष्ठा usb_device_id usb_storage_usb_ids[] = अणु
#	include "unusual_devs.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usb_storage_usb_ids);

#अघोषित UNUSUAL_DEV
#अघोषित COMPLIANT_DEV
#अघोषित USUAL_DEV
#अघोषित UNUSUAL_VENDOR_INTF

/*
 * The table of devices to ignore
 */
काष्ठा ignore_entry अणु
	u16	vid, pid, bcdmin, bcdmax;
पूर्ण;

#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु					\
	.vid	= id_venकरोr,		\
	.pid 	= id_product,		\
	.bcdmin	= bcdDeviceMin,		\
	.bcdmax = bcdDeviceMax,		\
पूर्ण

अटल स्थिर काष्ठा ignore_entry ignore_ids[] = अणु
#	include "unusual_alauda.h"
#	include "unusual_cypress.h"
#	include "unusual_datafab.h"
#	include "unusual_ene_ub6250.h"
#	include "unusual_freecom.h"
#	include "unusual_isd200.h"
#	include "unusual_jumpshot.h"
#	include "unusual_karma.h"
#	include "unusual_onetouch.h"
#	include "unusual_realtek.h"
#	include "unusual_sddr09.h"
#	include "unusual_sddr55.h"
#	include "unusual_usbat.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV

/* Return an error अगर a device is in the ignore_ids list */
पूर्णांक usb_usual_ignore_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev;
	अचिन्हित vid, pid, bcd;
	स्थिर काष्ठा ignore_entry *p;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	vid = le16_to_cpu(udev->descriptor.idVenकरोr);
	pid = le16_to_cpu(udev->descriptor.idProduct);
	bcd = le16_to_cpu(udev->descriptor.bcdDevice);

	क्रम (p = ignore_ids; p->vid; ++p) अणु
		अगर (p->vid == vid && p->pid == pid &&
				p->bcdmin <= bcd && p->bcdmax >= bcd)
			वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण
