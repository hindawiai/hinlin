<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Unusual Devices File क्रम the Freecom USB/IDE adaptor
 */

#अगर defined(CONFIG_USB_STORAGE_FREECOM) || \
		defined(CONFIG_USB_STORAGE_FREECOM_MODULE)

UNUSUAL_DEV(  0x07ab, 0xfc01, 0x0000, 0x9999,
		"Freecom",
		"USB-IDE",
		USB_SC_QIC, USB_PR_FREECOM, init_मुक्तcom, 0),

#पूर्ण_अगर /* defined(CONFIG_USB_STORAGE_FREECOM) || ... */
