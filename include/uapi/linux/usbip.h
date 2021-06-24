<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	usbip.h
 *
 *	USBIP uapi defines and function prototypes etc.
*/

#अगर_अघोषित _UAPI_LINUX_USBIP_H
#घोषणा _UAPI_LINUX_USBIP_H

/* usbip device status - exported in usbip device sysfs status */
क्रमागत usbip_device_status अणु
	/* sdev is available. */
	SDEV_ST_AVAILABLE = 0x01,
	/* sdev is now used. */
	SDEV_ST_USED,
	/* sdev is unusable because of a fatal error. */
	SDEV_ST_ERROR,

	/* vdev करोes not connect a remote device. */
	VDEV_ST_शून्य,
	/* vdev is used, but the USB address is not asचिन्हित yet */
	VDEV_ST_NOTASSIGNED,
	VDEV_ST_USED,
	VDEV_ST_ERROR
पूर्ण;
#पूर्ण_अगर /* _UAPI_LINUX_USBIP_H */
