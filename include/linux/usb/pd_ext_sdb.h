<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2017 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __LINUX_USB_PD_EXT_SDB_H
#घोषणा __LINUX_USB_PD_EXT_SDB_H

/* SDB : Status Data Block */
क्रमागत usb_pd_ext_sdb_fields अणु
	USB_PD_EXT_SDB_INTERNAL_TEMP = 0,
	USB_PD_EXT_SDB_PRESENT_INPUT,
	USB_PD_EXT_SDB_PRESENT_BATT_INPUT,
	USB_PD_EXT_SDB_EVENT_FLAGS,
	USB_PD_EXT_SDB_TEMP_STATUS,
	USB_PD_EXT_SDB_DATA_SIZE,
पूर्ण;

/* Event Flags */
#घोषणा USB_PD_EXT_SDB_EVENT_OCP		BIT(1)
#घोषणा USB_PD_EXT_SDB_EVENT_OTP		BIT(2)
#घोषणा USB_PD_EXT_SDB_EVENT_OVP		BIT(3)
#घोषणा USB_PD_EXT_SDB_EVENT_CF_CV_MODE		BIT(4)

#पूर्ण_अगर /* __LINUX_USB_PD_EXT_SDB_H */
