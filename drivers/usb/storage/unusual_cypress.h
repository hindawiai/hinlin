<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Unusual Devices File क्रम devices based on the Cypress USB/ATA bridge
 *	with support क्रम ATACB
 */

#अगर defined(CONFIG_USB_STORAGE_CYPRESS_ATACB) || \
		defined(CONFIG_USB_STORAGE_CYPRESS_ATACB_MODULE)

/* CY7C68300 : support atacb */
UNUSUAL_DEV(  0x04b4, 0x6830, 0x0000, 0x9999,
		"Cypress",
		"Cypress AT2LP",
		USB_SC_CYP_ATACB, USB_PR_DEVICE, शून्य, 0),

/* CY7C68310 : support atacb and atacb2 */
UNUSUAL_DEV(  0x04b4, 0x6831, 0x0000, 0x9999,
		"Cypress",
		"Cypress ISD-300LP",
		USB_SC_CYP_ATACB, USB_PR_DEVICE, शून्य, 0),

UNUSUAL_DEV( 0x14cd, 0x6116, 0x0160, 0x0160,
		"Super Top",
		"USB 2.0  SATA BRIDGE",
		USB_SC_CYP_ATACB, USB_PR_DEVICE, शून्य, 0),

#पूर्ण_अगर /* defined(CONFIG_USB_STORAGE_CYPRESS_ATACB) || ... */
