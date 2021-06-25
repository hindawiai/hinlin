<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * All the USB notअगरy logic
 *
 * (C) Copyright 2005 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *
 * notअगरier functions originally based on those in kernel/sys.c
 * but fixed up to not be so broken.
 *
 * Released under the GPLv2 only.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश "usb.h"

अटल BLOCKING_NOTIFIER_HEAD(usb_notअगरier_list);

/**
 * usb_रेजिस्टर_notअगरy - रेजिस्टर a notअगरier callback whenever a usb change happens
 * @nb: poपूर्णांकer to the notअगरier block क्रम the callback events.
 *
 * These changes are either USB devices or busses being added or हटाओd.
 */
व्योम usb_रेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_रेजिस्टर(&usb_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(usb_रेजिस्टर_notअगरy);

/**
 * usb_unरेजिस्टर_notअगरy - unरेजिस्टर a notअगरier callback
 * @nb: poपूर्णांकer to the notअगरier block क्रम the callback events.
 *
 * usb_रेजिस्टर_notअगरy() must have been previously called क्रम this function
 * to work properly.
 */
व्योम usb_unरेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&usb_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unरेजिस्टर_notअगरy);


व्योम usb_notअगरy_add_device(काष्ठा usb_device *udev)
अणु
	blocking_notअगरier_call_chain(&usb_notअगरier_list, USB_DEVICE_ADD, udev);
पूर्ण

व्योम usb_notअगरy_हटाओ_device(काष्ठा usb_device *udev)
अणु
	blocking_notअगरier_call_chain(&usb_notअगरier_list,
			USB_DEVICE_REMOVE, udev);
पूर्ण

व्योम usb_notअगरy_add_bus(काष्ठा usb_bus *ubus)
अणु
	blocking_notअगरier_call_chain(&usb_notअगरier_list, USB_BUS_ADD, ubus);
पूर्ण

व्योम usb_notअगरy_हटाओ_bus(काष्ठा usb_bus *ubus)
अणु
	blocking_notअगरier_call_chain(&usb_notअगरier_list, USB_BUS_REMOVE, ubus);
पूर्ण
