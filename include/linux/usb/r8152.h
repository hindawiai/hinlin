<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (c) 2020 Realtek Semiconductor Corp. All rights reserved.
 */

#अगर_अघोषित	__LINUX_R8152_H
#घोषणा __LINUX_R8152_H

#घोषणा RTL8152_REQT_READ		0xc0
#घोषणा RTL8152_REQT_WRITE		0x40
#घोषणा RTL8152_REQ_GET_REGS		0x05
#घोषणा RTL8152_REQ_SET_REGS		0x05

#घोषणा BYTE_EN_DWORD			0xff
#घोषणा BYTE_EN_WORD			0x33
#घोषणा BYTE_EN_BYTE			0x11
#घोषणा BYTE_EN_SIX_BYTES		0x3f
#घोषणा BYTE_EN_START_MASK		0x0f
#घोषणा BYTE_EN_END_MASK		0xf0

#घोषणा MCU_TYPE_PLA			0x0100
#घोषणा MCU_TYPE_USB			0x0000

/* Define these values to match your device */
#घोषणा VENDOR_ID_REALTEK		0x0bda
#घोषणा VENDOR_ID_MICROSOFT		0x045e
#घोषणा VENDOR_ID_SAMSUNG		0x04e8
#घोषणा VENDOR_ID_LENOVO		0x17ef
#घोषणा VENDOR_ID_LINKSYS		0x13b1
#घोषणा VENDOR_ID_NVIDIA		0x0955
#घोषणा VENDOR_ID_TPLINK		0x2357

#अगर IS_REACHABLE(CONFIG_USB_RTL8152)
बाह्य u8 rtl8152_get_version(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_R8152_H */
