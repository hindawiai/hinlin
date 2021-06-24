<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xsens MT USB driver
 *
 * Copyright (C) 2013 Xsens <info@xsens.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>

#घोषणा XSENS_VID 0x2639

#घोषणा MTi_10_IMU_PID		0x0001
#घोषणा MTi_20_VRU_PID		0x0002
#घोषणा MTi_30_AHRS_PID		0x0003

#घोषणा MTi_100_IMU_PID		0x0011
#घोषणा MTi_200_VRU_PID		0x0012
#घोषणा MTi_300_AHRS_PID	0x0013

#घोषणा MTi_G_700_GPS_INS_PID	0x0017

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(XSENS_VID, MTi_10_IMU_PID) पूर्ण,
	अणु USB_DEVICE(XSENS_VID, MTi_20_VRU_PID) पूर्ण,
	अणु USB_DEVICE(XSENS_VID, MTi_30_AHRS_PID) पूर्ण,

	अणु USB_DEVICE(XSENS_VID, MTi_100_IMU_PID) पूर्ण,
	अणु USB_DEVICE(XSENS_VID, MTi_200_VRU_PID) पूर्ण,
	अणु USB_DEVICE(XSENS_VID, MTi_300_AHRS_PID) पूर्ण,

	अणु USB_DEVICE(XSENS_VID, MTi_G_700_GPS_INS_PID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक xsens_mt_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (serial->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber == 1)
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल काष्ठा usb_serial_driver xsens_mt_device = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "xsens_mt",
	पूर्ण,
	.id_table = id_table,
	.num_ports = 1,

	.probe = xsens_mt_probe,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&xsens_mt_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR("Frans Klaver <frans.klaver@xsens.com>");
MODULE_DESCRIPTION("USB-serial driver for Xsens motion trackers");
MODULE_LICENSE("GPL v2");
