<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial "Simple" driver
 *
 * Copyright (C) 2001-2006,2008,2013 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2005 Arthur Huillet (ahuillet@users.sf.net)
 * Copyright (C) 2005 Thomas Hergenhahn <thomas.hergenhahn@suse.de>
 * Copyright (C) 2009 Outpost Embedded, LLC
 * Copyright (C) 2010 Zilogic Systems <code@zilogic.com>
 * Copyright (C) 2013 Wei Shuai <cpuwolf@gmail.com>
 * Copyright (C) 2013 Linux Foundation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा DEVICE_N(venकरोr, IDS, nport)				\
अटल स्थिर काष्ठा usb_device_id venकरोr##_id_table[] = अणु	\
	IDS(),							\
	अणु पूर्ण,							\
पूर्ण;								\
अटल काष्ठा usb_serial_driver venकरोr##_device = अणु		\
	.driver = अणु						\
		.owner =	THIS_MODULE,			\
		.name =		#venकरोr,			\
	पूर्ण,							\
	.id_table =		venकरोr##_id_table,		\
	.num_ports =		nport,				\
पूर्ण;

#घोषणा DEVICE(venकरोr, IDS)	DEVICE_N(venकरोr, IDS, 1)

/* Medtronic CareLink USB driver */
#घोषणा CARELINK_IDS()			\
	अणु USB_DEVICE(0x0a21, 0x8001) पूर्ण	/* MMT-7305WW */
DEVICE(carelink, CARELINK_IDS);

/* ZIO Motherboard USB driver */
#घोषणा ZIO_IDS()			\
	अणु USB_DEVICE(0x1CBE, 0x0103) पूर्ण
DEVICE(zio, ZIO_IDS);

/* Funsoft Serial USB driver */
#घोषणा FUNSOFT_IDS()			\
	अणु USB_DEVICE(0x1404, 0xcddc) पूर्ण
DEVICE(funsoft, FUNSOFT_IDS);

/* Infineon Flashloader driver */
#घोषणा FLASHLOADER_IDS()		\
	अणु USB_DEVICE_INTERFACE_CLASS(0x058b, 0x0041, USB_CLASS_CDC_DATA) पूर्ण, \
	अणु USB_DEVICE(0x8087, 0x0716) पूर्ण, \
	अणु USB_DEVICE(0x8087, 0x0801) पूर्ण
DEVICE(flashloader, FLASHLOADER_IDS);

/* Google Serial USB SubClass */
#घोषणा GOOGLE_IDS()						\
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x18d1,			\
					USB_CLASS_VENDOR_SPEC,	\
					0x50,			\
					0x01) पूर्ण
DEVICE(google, GOOGLE_IDS);

/* Libtransistor USB console */
#घोषणा LIBTRANSISTOR_IDS()			\
	अणु USB_DEVICE(0x1209, 0x8b00) पूर्ण
DEVICE(libtransistor, LIBTRANSISTOR_IDS);

/* ViVOpay USB Serial Driver */
#घोषणा VIVOPAY_IDS()			\
	अणु USB_DEVICE(0x1d5f, 0x1004) पूर्ण	/* ViVOpay 8800 */
DEVICE(vivopay, VIVOPAY_IDS);

/* Motorola USB Phone driver */
#घोषणा MOTO_IDS()			\
	अणु USB_DEVICE(0x05c6, 0x3197) पूर्ण,	/* unknown Motorola phone */	\
	अणु USB_DEVICE(0x0c44, 0x0022) पूर्ण,	/* unknown Motorola phone */	\
	अणु USB_DEVICE(0x22b8, 0x2a64) पूर्ण,	/* Motorola KRZR K1m */		\
	अणु USB_DEVICE(0x22b8, 0x2c84) पूर्ण,	/* Motorola VE240 phone */	\
	अणु USB_DEVICE(0x22b8, 0x2c64) पूर्ण	/* Motorola V950 phone */
DEVICE(moto_modem, MOTO_IDS);

/* Motorola Tetra driver */
#घोषणा MOTOROLA_TETRA_IDS()			\
	अणु USB_DEVICE(0x0cad, 0x9011) पूर्ण,	/* Motorola Solutions TETRA PEI */ \
	अणु USB_DEVICE(0x0cad, 0x9012) पूर्ण,	/* MTP6550 */ \
	अणु USB_DEVICE(0x0cad, 0x9013) पूर्ण,	/* MTP3xxx */ \
	अणु USB_DEVICE(0x0cad, 0x9015) पूर्ण,	/* MTP85xx */ \
	अणु USB_DEVICE(0x0cad, 0x9016) पूर्ण	/* TPG2200 */
DEVICE(motorola_tetra, MOTOROLA_TETRA_IDS);

/* Novatel Wireless GPS driver */
#घोषणा NOVATEL_IDS()			\
	अणु USB_DEVICE(0x09d7, 0x0100) पूर्ण	/* NovAtel FlexPack GPS */
DEVICE_N(novatel_gps, NOVATEL_IDS, 3);

/* HP4x (48/49) Generic Serial driver */
#घोषणा HP4X_IDS()			\
	अणु USB_DEVICE(0x03f0, 0x0121) पूर्ण
DEVICE(hp4x, HP4X_IDS);

/* Suunto ANT+ USB Driver */
#घोषणा SUUNTO_IDS()			\
	अणु USB_DEVICE(0x0fcf, 0x1008) पूर्ण,	\
	अणु USB_DEVICE(0x0fcf, 0x1009) पूर्ण /* Dynastream ANT USB-m Stick */
DEVICE(suunto, SUUNTO_IDS);

/* Siemens USB/MPI adapter */
#घोषणा SIEMENS_IDS()			\
	अणु USB_DEVICE(0x908, 0x0004) पूर्ण
DEVICE(siemens_mpi, SIEMENS_IDS);

/* All of the above काष्ठाures mushed पूर्णांकo two lists */
अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&carelink_device,
	&zio_device,
	&funsoft_device,
	&flashloader_device,
	&google_device,
	&libtransistor_device,
	&vivopay_device,
	&moto_modem_device,
	&motorola_tetra_device,
	&novatel_gps_device,
	&hp4x_device,
	&suunto_device,
	&siemens_mpi_device,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	CARELINK_IDS(),
	ZIO_IDS(),
	FUNSOFT_IDS(),
	FLASHLOADER_IDS(),
	GOOGLE_IDS(),
	LIBTRANSISTOR_IDS(),
	VIVOPAY_IDS(),
	MOTO_IDS(),
	MOTOROLA_TETRA_IDS(),
	NOVATEL_IDS(),
	HP4X_IDS(),
	SUUNTO_IDS(),
	SIEMENS_IDS(),
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

module_usb_serial_driver(serial_drivers, id_table);
MODULE_LICENSE("GPL v2");
