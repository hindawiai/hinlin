<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Unusual Devices File क्रम the Maxtor OneTouch USB hard drive's button
 */

#अगर defined(CONFIG_USB_STORAGE_ONETOUCH) || \
		defined(CONFIG_USB_STORAGE_ONETOUCH_MODULE)

/*
 * Submitted by: Nick Sillik <n.sillik@temple.edu>
 * Needed क्रम OneTouch extension to usb-storage
 */
UNUSUAL_DEV(  0x0d49, 0x7000, 0x0000, 0x9999,
		"Maxtor",
		"OneTouch External Harddrive",
		USB_SC_DEVICE, USB_PR_DEVICE, onetouch_connect_input,
		0),

UNUSUAL_DEV(  0x0d49, 0x7010, 0x0000, 0x9999,
		"Maxtor",
		"OneTouch External Harddrive",
		USB_SC_DEVICE, USB_PR_DEVICE, onetouch_connect_input,
		0),

#पूर्ण_अगर /* defined(CONFIG_USB_STORAGE_ONETOUCH) || ... */
