<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम USB Attached SCSI devices - Unusual Devices File
 *
 *   (c) 2013 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on the same file क्रम the usb-storage driver, which is:
 *   (c) 2000-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *   (c) 2000 Adam J. Richter (adam@yggdrasil.com), Yggdrasil Computing, Inc.
 */

/*
 * IMPORTANT NOTE: This file must be included in another file which defines
 * a UNUSUAL_DEV macro beक्रमe this file is included.
 */

/*
 * If you edit this file, please try to keep it sorted first by VenकरोrID,
 * then by ProductID.
 *
 * If you want to add an entry क्रम this file, be sure to include the
 * following inक्रमmation:
 *	- a patch that adds the entry क्रम your device, including your
 *	  email address right above the entry (plus maybe a brief
 *	  explanation of the reason क्रम the entry),
 *	- lsusb -v output क्रम the device
 * Send your submission to Hans de Goede <hdegoede@redhat.com>
 * and करोn't क्रमget to CC: the USB development list <linux-usb@vger.kernel.org>
 */

/* Reported-by: Till Dथघrges <करोerges@pre-sense.de> */
UNUSUAL_DEV(0x054c, 0x087d, 0x0000, 0x9999,
		"Sony",
		"PSZ-HA*",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_OPCODES),

/*
 *  Initially Reported-by: Julian Groथ <julian.g@posteo.de>
 *  Further reports David C. Partridge <david.partridge@perdrix.co.uk>
 */
UNUSUAL_DEV(0x059f, 0x105f, 0x0000, 0x9999,
		"LaCie",
		"2Big Quadra USB3",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_OPCODES | US_FL_NO_SAME),

/*
 * Apricorn USB3 करोngle someबार वापसs "USBSUSBSUSBS" in response to SCSI
 * commands in UAS mode.  Observed with the 1.28 firmware; are there others?
 */
UNUSUAL_DEV(0x0984, 0x0301, 0x0128, 0x0128,
		"Apricorn",
		"",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_IGNORE_UAS),

/* Reported-by: David Webb <djw@noc.ac.uk> */
UNUSUAL_DEV(0x0bc2, 0x331a, 0x0000, 0x9999,
		"Seagate",
		"Expansion Desk",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_LUNS),

/* Reported-by: Benjamin Tissoires <benjamin.tissoires@redhat.com> */
UNUSUAL_DEV(0x13fd, 0x3940, 0x0000, 0x9999,
		"Initio Corporation",
		"INIC-3069",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_ATA_1X | US_FL_IGNORE_RESIDUE),

/* Reported-by: Tom Arild Naess <tanaess@gmail.com> */
UNUSUAL_DEV(0x152d, 0x0539, 0x0000, 0x9999,
		"JMicron",
		"JMS539",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_OPCODES),

/* Reported-by: Claudio Bizzarri <claudio.bizzarri@gmail.com> */
UNUSUAL_DEV(0x152d, 0x0567, 0x0000, 0x9999,
		"JMicron",
		"JMS567",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_BROKEN_FUA | US_FL_NO_REPORT_OPCODES),

/* Reported-by: David Kozub <zub@linux.fjfi.cvut.cz> */
UNUSUAL_DEV(0x152d, 0x0578, 0x0000, 0x9999,
		"JMicron",
		"JMS567",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_BROKEN_FUA),

/* Reported-by: Thinh Nguyen <thinhn@synopsys.com> */
UNUSUAL_DEV(0x154b, 0xf00b, 0x0000, 0x9999,
		"PNY",
		"Pro Elite SSD",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_ATA_1X),

/* Reported-by: Thinh Nguyen <thinhn@synopsys.com> */
UNUSUAL_DEV(0x154b, 0xf00d, 0x0000, 0x9999,
		"PNY",
		"Pro Elite SSD",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_ATA_1X),

/* Reported-by: Hans de Goede <hdegoede@redhat.com> */
UNUSUAL_DEV(0x2109, 0x0711, 0x0000, 0x9999,
		"VIA",
		"VL711",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_ATA_1X),

/* Reported-by: Icenowy Zheng <icenowy@aosc.io> */
UNUSUAL_DEV(0x2537, 0x1068, 0x0000, 0x9999,
		"Norelsys",
		"NS1068X",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_IGNORE_UAS),

/*
 * Initially Reported-by: Takeo Nakayama <javhera@gmx.com>
 * UAS Ignore Reported by Steven Ellis <sellis@redhat.com>
 */
UNUSUAL_DEV(0x357d, 0x7788, 0x0000, 0x9999,
		"JMicron",
		"JMS566",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_OPCODES | US_FL_IGNORE_UAS),

/* Reported-by: Hans de Goede <hdegoede@redhat.com> */
UNUSUAL_DEV(0x4971, 0x1012, 0x0000, 0x9999,
		"Hitachi",
		"External HDD",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_IGNORE_UAS),

/* Reported-by: Riअक्षरd Henderson <rth@redhat.com> */
UNUSUAL_DEV(0x4971, 0x8017, 0x0000, 0x9999,
		"SimpleTech",
		"External HDD",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_NO_REPORT_OPCODES),

/* "G-DRIVE" बाह्यal HDD hangs on ग_लिखो without these.
 * Patch submitted by Alexander Kappner <agk@godking.net>
 */
UNUSUAL_DEV(0x4971, 0x8024, 0x0000, 0x9999,
		"SimpleTech",
		"External HDD",
		USB_SC_DEVICE, USB_PR_DEVICE, शून्य,
		US_FL_ALWAYS_SYNC),
