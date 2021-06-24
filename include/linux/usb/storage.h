<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __LINUX_USB_STORAGE_H
#घोषणा __LINUX_USB_STORAGE_H

/*
 * linux/usb/storage.h
 *
 * Copyright Matthew Wilcox क्रम Intel Corp, 2010
 *
 * This file contains definitions taken from the
 * USB Mass Storage Class Specअगरication Overview
 *
 * Distributed under the terms of the GNU GPL, version two.
 */

/* Storage subclass codes */

#घोषणा USB_SC_RBC	0x01		/* Typically, flash devices */
#घोषणा USB_SC_8020	0x02		/* CD-ROM */
#घोषणा USB_SC_QIC	0x03		/* QIC-157 Tapes */
#घोषणा USB_SC_UFI	0x04		/* Floppy */
#घोषणा USB_SC_8070	0x05		/* Removable media */
#घोषणा USB_SC_SCSI	0x06		/* Transparent */
#घोषणा USB_SC_LOCKABLE	0x07		/* Password-रक्षित */

#घोषणा USB_SC_ISD200	0xf0		/* ISD200 ATA */
#घोषणा USB_SC_CYP_ATACB	0xf1	/* Cypress ATACB */
#घोषणा USB_SC_DEVICE	0xff		/* Use device's value */

/* Storage protocol codes */

#घोषणा USB_PR_CBI	0x00		/* Control/Bulk/Interrupt */
#घोषणा USB_PR_CB	0x01		/* Control/Bulk w/o पूर्णांकerrupt */
#घोषणा USB_PR_BULK	0x50		/* bulk only */
#घोषणा USB_PR_UAS	0x62		/* USB Attached SCSI */

#घोषणा USB_PR_USBAT	0x80		/* SCM-ATAPI bridge */
#घोषणा USB_PR_EUSB_SDDR09	0x81	/* SCM-SCSI bridge क्रम SDDR-09 */
#घोषणा USB_PR_SDDR55	0x82		/* SDDR-55 (made up) */
#घोषणा USB_PR_DPCM_USB	0xf0		/* Combination CB/SDDR09 */
#घोषणा USB_PR_FREECOM	0xf1		/* Freecom */
#घोषणा USB_PR_DATAFAB	0xf2		/* Datafab chipsets */
#घोषणा USB_PR_JUMPSHOT	0xf3		/* Lexar Jumpshot */
#घोषणा USB_PR_ALAUDA	0xf4		/* Alauda chipsets */
#घोषणा USB_PR_KARMA	0xf5		/* Rio Karma */

#घोषणा USB_PR_DEVICE	0xff		/* Use device's value */

/*
 * Bulk only data काष्ठाures
 */

/* command block wrapper */
काष्ठा bulk_cb_wrap अणु
	__le32	Signature;		/* contains 'USBC' */
	__u32	Tag;			/* unique per command id */
	__le32	DataTransferLength;	/* size of data */
	__u8	Flags;			/* direction in bit 0 */
	__u8	Lun;			/* LUN normally 0 */
	__u8	Length;			/* length of the CDB */
	__u8	CDB[16];		/* max command */
पूर्ण;

#घोषणा US_BULK_CB_WRAP_LEN	31
#घोषणा US_BULK_CB_SIGN		0x43425355	/* spells out 'USBC' */
#घोषणा US_BULK_FLAG_IN		(1 << 7)
#घोषणा US_BULK_FLAG_OUT	0

/* command status wrapper */
काष्ठा bulk_cs_wrap अणु
	__le32	Signature;	/* contains 'USBS' */
	__u32	Tag;		/* same as original command */
	__le32	Residue;	/* amount not transferred */
	__u8	Status;		/* see below */
पूर्ण;

#घोषणा US_BULK_CS_WRAP_LEN	13
#घोषणा US_BULK_CS_SIGN		0x53425355      /* spells out 'USBS' */
#घोषणा US_BULK_STAT_OK		0
#घोषणा US_BULK_STAT_FAIL	1
#घोषणा US_BULK_STAT_PHASE	2

/* bulk-only class specअगरic requests */
#घोषणा US_BULK_RESET_REQUEST   0xff
#घोषणा US_BULK_GET_MAX_LUN     0xfe

#पूर्ण_अगर
