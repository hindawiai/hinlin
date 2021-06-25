<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm USB Auxiliary Serial Port driver
 *
 * Copyright (C) 2008 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2010 Dan Williams <dcbw@redhat.com>
 *
 * Devices listed here usually provide a CDC ACM port on which normal modem
 * AT commands and PPP can be used.  But when that port is in-use by PPP it
 * cannot be used simultaneously क्रम status or संकेत strength.  Instead, the
 * ports here can be queried क्रम that inक्रमmation using the Qualcomm DM
 * protocol.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

/* NOTE: क्रम now, only use this driver क्रम devices that provide a CDC-ACM port
 * क्रम normal AT commands, but also provide secondary USB पूर्णांकerfaces क्रम the
 * QCDM-capable ports.  Devices that करो not provide a CDC-ACM port should
 * probably be driven by option.ko.
 */

/* UTStarcom/Pantech/Curitel devices */
#घोषणा UTSTARCOM_VENDOR_ID			0x106c
#घोषणा UTSTARCOM_PRODUCT_PC5740		0x3701
#घोषणा UTSTARCOM_PRODUCT_PC5750		0x3702 /* aka Pantech PX-500 */
#घोषणा UTSTARCOM_PRODUCT_UM150			0x3711
#घोषणा UTSTARCOM_PRODUCT_UM175_V1		0x3712
#घोषणा UTSTARCOM_PRODUCT_UM175_V2		0x3714
#घोषणा UTSTARCOM_PRODUCT_UM175_ALLTEL		0x3715

/* CMOTECH devices */
#घोषणा CMOTECH_VENDOR_ID			0x16d8
#घोषणा CMOTECH_PRODUCT_CDU550			0x5553
#घोषणा CMOTECH_PRODUCT_CDX650			0x6512

/* LG devices */
#घोषणा LG_VENDOR_ID				0x1004
#घोषणा LG_PRODUCT_VX4400_6000			0x6000 /* VX4400/VX6000/Rumor */

/* Sanyo devices */
#घोषणा SANYO_VENDOR_ID				0x0474
#घोषणा SANYO_PRODUCT_KATANA_LX			0x0754 /* SCP-3800 (Katana LX) */

/* Samsung devices */
#घोषणा SAMSUNG_VENDOR_ID			0x04e8
#घोषणा SAMSUNG_PRODUCT_U520			0x6640 /* SCH-U520 */

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_PC5740, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_PC5750, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM150, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_V1, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_V2, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_ALLTEL, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(CMOTECH_VENDOR_ID, CMOTECH_PRODUCT_CDU550, 0xff, 0xff, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(CMOTECH_VENDOR_ID, CMOTECH_PRODUCT_CDX650, 0xff, 0xff, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(LG_VENDOR_ID, LG_PRODUCT_VX4400_6000, 0xff, 0xff, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(SANYO_VENDOR_ID, SANYO_PRODUCT_KATANA_LX, 0xff, 0xff, 0x00) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(SAMSUNG_VENDOR_ID, SAMSUNG_PRODUCT_U520, 0xff, 0x00, 0x00) पूर्ण,
	अणु USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xfd, 0xff) पूर्ण,  /* NMEA */
	अणु USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xfe, 0xff) पूर्ण,  /* WMC */
	अणु USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xff, 0xff) पूर्ण,  /* DIAG */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1fac, 0x0151, 0xff, 0xff, 0xff) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver qcaux_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"qcaux",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&qcaux_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);
MODULE_LICENSE("GPL v2");
