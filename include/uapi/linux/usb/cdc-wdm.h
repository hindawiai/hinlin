<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * USB CDC Device Management userspace API definitions
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#अगर_अघोषित _UAPI__LINUX_USB_CDC_WDM_H
#घोषणा _UAPI__LINUX_USB_CDC_WDM_H

#समावेश <linux/types.h>

/*
 * This IOCTL is used to retrieve the wMaxCommand क्रम the device,
 * defining the message limit क्रम both पढ़ोing and writing.
 *
 * For CDC WDM functions this will be the wMaxCommand field of the
 * Device Management Functional Descriptor.
 */
#घोषणा IOCTL_WDM_MAX_COMMAND _IOR('H', 0xA0, __u16)

#पूर्ण_अगर /* _UAPI__LINUX_USB_CDC_WDM_H */
