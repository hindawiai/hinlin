<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Unusual Devices File क्रम SanDisk SDDR-55 SmartMedia पढ़ोer
 */

#अगर defined(CONFIG_USB_STORAGE_SDDR55) || \
		defined(CONFIG_USB_STORAGE_SDDR55_MODULE)

/* Contributed by Peter Waechtler */
UNUSUAL_DEV( 0x07c4, 0xa103, 0x0000, 0x9999,
		"Datafab",
		"MDSM-B reader",
		USB_SC_SCSI, USB_PR_SDDR55, शून्य,
		US_FL_FIX_INQUIRY),

/* SM part - aeb <Andries.Brouwer@cwi.nl> */
UNUSUAL_DEV(  0x07c4, 0xa109, 0x0000, 0xffff,
		"Datafab Systems, Inc.",
		"USB to CF + SM Combo (LC1)",
		USB_SC_SCSI, USB_PR_SDDR55, शून्य, 0),

UNUSUAL_DEV( 0x0c0b, 0xa109, 0x0000, 0xffff,
		"Acomdata",
		"SM",
		USB_SC_SCSI, USB_PR_SDDR55, शून्य, 0),

UNUSUAL_DEV(  0x55aa, 0xa103, 0x0000, 0x9999,
		"Sandisk",
		"ImageMate SDDR55",
		USB_SC_SCSI, USB_PR_SDDR55, शून्य, 0),

#पूर्ण_अगर /* defined(CONFIG_USB_STORAGE_SDDR55) || ... */
