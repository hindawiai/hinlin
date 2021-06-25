<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Unusual Devices File क्रम the Lexar "Jumpshot" Compact Flash पढ़ोer
 */

#अगर defined(CONFIG_USB_STORAGE_JUMPSHOT) || \
		defined(CONFIG_USB_STORAGE_JUMPSHOT_MODULE)

UNUSUAL_DEV(  0x05dc, 0x0001, 0x0000, 0x0001,
		"Lexar",
		"Jumpshot USB CF Reader",
		USB_SC_SCSI, USB_PR_JUMPSHOT, शून्य,
		US_FL_NEED_OVERRIDE),

#पूर्ण_अगर /* defined(CONFIG_USB_STORAGE_JUMPSHOT) || ... */
