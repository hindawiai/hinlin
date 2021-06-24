<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek RTS51xx USB card पढ़ोer
 *
 * Copyright(c) 2009 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   wwang (wei_wang@realsil.com.cn)
 *   No. 450, Shenhu Road, Suzhou Industry Park, Suzhou, China
 */

#अगर defined(CONFIG_USB_STORAGE_REALTEK) || \
		defined(CONFIG_USB_STORAGE_REALTEK_MODULE)

UNUSUAL_DEV(0x0bda, 0x0138, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0153, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0158, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0159, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0177, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

UNUSUAL_DEV(0x0bda, 0x0184, 0x0000, 0x9999,
		"Realtek",
		"USB Card Reader",
		USB_SC_DEVICE, USB_PR_DEVICE, init_realtek_cr, 0),

#पूर्ण_अगर  /* defined(CONFIG_USB_STORAGE_REALTEK) || ... */
