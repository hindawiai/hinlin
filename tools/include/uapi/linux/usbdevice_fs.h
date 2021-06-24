<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*****************************************************************************/

/*
 *	usbdevice_fs.h  --  USB device file प्रणाली.
 *
 *	Copyright (C) 2000
 *          Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *	This program is मुक्त software; you can redistribute it and/or modअगरy
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License क्रम more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  History:
 *   0.1  04.01.2000  Created
 */

/*****************************************************************************/

#अगर_अघोषित _UAPI_LINUX_USBDEVICE_FS_H
#घोषणा _UAPI_LINUX_USBDEVICE_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/* --------------------------------------------------------------------- */

/* usbdevfs ioctl codes */

काष्ठा usbdevfs_ctrltransfer अणु
	__u8 bRequestType;
	__u8 bRequest;
	__u16 wValue;
	__u16 wIndex;
	__u16 wLength;
	__u32 समयout;  /* in milliseconds */
 	व्योम __user *data;
पूर्ण;

काष्ठा usbdevfs_bulktransfer अणु
	अचिन्हित पूर्णांक ep;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक समयout; /* in milliseconds */
	व्योम __user *data;
पूर्ण;

काष्ठा usbdevfs_setपूर्णांकerface अणु
	अचिन्हित पूर्णांक पूर्णांकerface;
	अचिन्हित पूर्णांक altsetting;
पूर्ण;

काष्ठा usbdevfs_disconnectसंकेत अणु
	अचिन्हित पूर्णांक signr;
	व्योम __user *context;
पूर्ण;

#घोषणा USBDEVFS_MAXDRIVERNAME 255

काष्ठा usbdevfs_getdriver अणु
	अचिन्हित पूर्णांक पूर्णांकerface;
	अक्षर driver[USBDEVFS_MAXDRIVERNAME + 1];
पूर्ण;

काष्ठा usbdevfs_connectinfo अणु
	अचिन्हित पूर्णांक devnum;
	अचिन्हित अक्षर slow;
पूर्ण;

काष्ठा usbdevfs_conninfo_ex अणु
	__u32 size;		/* Size of the काष्ठाure from the kernel's */
				/* poपूर्णांक of view. Can be used by userspace */
				/* to determine how much data can be       */
				/* used/trusted.                           */
	__u32 busnum;           /* USB bus number, as क्रमागतerated by the    */
				/* kernel, the device is connected to.     */
	__u32 devnum;           /* Device address on the bus.              */
	__u32 speed;		/* USB_SPEED_* स्थिरants from ch9.h        */
	__u8 num_ports;		/* Number of ports the device is connected */
				/* to on the way to the root hub. It may   */
				/* be bigger than size of 'ports' array so */
				/* userspace can detect overflows.         */
	__u8 ports[7];		/* List of ports on the way from the root  */
				/* hub to the device. Current limit in     */
				/* USB specअगरication is 7 tiers (root hub, */
				/* 5 पूर्णांकermediate hubs, device), which     */
				/* gives at most 6 port entries.           */
पूर्ण;

#घोषणा USBDEVFS_URB_SHORT_NOT_OK	0x01
#घोषणा USBDEVFS_URB_ISO_ASAP		0x02
#घोषणा USBDEVFS_URB_BULK_CONTINUATION	0x04
#घोषणा USBDEVFS_URB_NO_FSBR		0x20	/* Not used */
#घोषणा USBDEVFS_URB_ZERO_PACKET	0x40
#घोषणा USBDEVFS_URB_NO_INTERRUPT	0x80

#घोषणा USBDEVFS_URB_TYPE_ISO		   0
#घोषणा USBDEVFS_URB_TYPE_INTERRUPT	   1
#घोषणा USBDEVFS_URB_TYPE_CONTROL	   2
#घोषणा USBDEVFS_URB_TYPE_BULK		   3

काष्ठा usbdevfs_iso_packet_desc अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक actual_length;
	अचिन्हित पूर्णांक status;
पूर्ण;

काष्ठा usbdevfs_urb अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर endpoपूर्णांक;
	पूर्णांक status;
	अचिन्हित पूर्णांक flags;
	व्योम __user *buffer;
	पूर्णांक buffer_length;
	पूर्णांक actual_length;
	पूर्णांक start_frame;
	जोड़ अणु
		पूर्णांक number_of_packets;	/* Only used क्रम isoc urbs */
		अचिन्हित पूर्णांक stream_id;	/* Only used with bulk streams */
	पूर्ण;
	पूर्णांक error_count;
	अचिन्हित पूर्णांक signr;	/* संकेत to be sent on completion,
				  or 0 अगर none should be sent. */
	व्योम __user *usercontext;
	काष्ठा usbdevfs_iso_packet_desc iso_frame_desc[0];
पूर्ण;

/* ioctls क्रम talking directly to drivers */
काष्ठा usbdevfs_ioctl अणु
	पूर्णांक	अगरno;		/* पूर्णांकerface 0..N ; negative numbers reserved */
	पूर्णांक	ioctl_code;	/* MUST encode size + direction of data so the
				 * macros in <यंत्र/ioctl.h> give correct values */
	व्योम __user *data;	/* param buffer (in, or out) */
पूर्ण;

/* You can करो most things with hubs just through control messages,
 * except find out what device connects to what port. */
काष्ठा usbdevfs_hub_portinfo अणु
	अक्षर nports;		/* number of करोwnstream ports in this hub */
	अक्षर port [127];	/* e.g. port 3 connects to device 27 */
पूर्ण;

/* System and bus capability flags */
#घोषणा USBDEVFS_CAP_ZERO_PACKET		0x01
#घोषणा USBDEVFS_CAP_BULK_CONTINUATION		0x02
#घोषणा USBDEVFS_CAP_NO_PACKET_SIZE_LIM		0x04
#घोषणा USBDEVFS_CAP_BULK_SCATTER_GATHER	0x08
#घोषणा USBDEVFS_CAP_REAP_AFTER_DISCONNECT	0x10
#घोषणा USBDEVFS_CAP_MMAP			0x20
#घोषणा USBDEVFS_CAP_DROP_PRIVILEGES		0x40
#घोषणा USBDEVFS_CAP_CONNINFO_EX		0x80
#घोषणा USBDEVFS_CAP_SUSPEND			0x100

/* USBDEVFS_DISCONNECT_CLAIM flags & काष्ठा */

/* disconnect-and-claim अगर the driver matches the driver field */
#घोषणा USBDEVFS_DISCONNECT_CLAIM_IF_DRIVER	0x01
/* disconnect-and-claim except when the driver matches the driver field */
#घोषणा USBDEVFS_DISCONNECT_CLAIM_EXCEPT_DRIVER	0x02

काष्ठा usbdevfs_disconnect_claim अणु
	अचिन्हित पूर्णांक पूर्णांकerface;
	अचिन्हित पूर्णांक flags;
	अक्षर driver[USBDEVFS_MAXDRIVERNAME + 1];
पूर्ण;

काष्ठा usbdevfs_streams अणु
	अचिन्हित पूर्णांक num_streams; /* Not used by USBDEVFS_FREE_STREAMS */
	अचिन्हित पूर्णांक num_eps;
	अचिन्हित अक्षर eps[0];
पूर्ण;

/*
 * USB_SPEED_* values वापसed by USBDEVFS_GET_SPEED are defined in
 * linux/usb/ch9.h
 */

#घोषणा USBDEVFS_CONTROL           _IOWR('U', 0, काष्ठा usbdevfs_ctrltransfer)
#घोषणा USBDEVFS_CONTROL32           _IOWR('U', 0, काष्ठा usbdevfs_ctrltransfer32)
#घोषणा USBDEVFS_BULK              _IOWR('U', 2, काष्ठा usbdevfs_bulktransfer)
#घोषणा USBDEVFS_BULK32              _IOWR('U', 2, काष्ठा usbdevfs_bulktransfer32)
#घोषणा USBDEVFS_RESETEP           _IOR('U', 3, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_SETINTERFACE      _IOR('U', 4, काष्ठा usbdevfs_setपूर्णांकerface)
#घोषणा USBDEVFS_SETCONFIGURATION  _IOR('U', 5, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_GETDRIVER         _IOW('U', 8, काष्ठा usbdevfs_getdriver)
#घोषणा USBDEVFS_SUBMITURB         _IOR('U', 10, काष्ठा usbdevfs_urb)
#घोषणा USBDEVFS_SUBMITURB32       _IOR('U', 10, काष्ठा usbdevfs_urb32)
#घोषणा USBDEVFS_DISCARDURB        _IO('U', 11)
#घोषणा USBDEVFS_REAPURB           _IOW('U', 12, व्योम *)
#घोषणा USBDEVFS_REAPURB32         _IOW('U', 12, __u32)
#घोषणा USBDEVFS_REAPURBNDELAY     _IOW('U', 13, व्योम *)
#घोषणा USBDEVFS_REAPURBNDELAY32   _IOW('U', 13, __u32)
#घोषणा USBDEVFS_DISCSIGNAL        _IOR('U', 14, काष्ठा usbdevfs_disconnectसंकेत)
#घोषणा USBDEVFS_DISCSIGNAL32      _IOR('U', 14, काष्ठा usbdevfs_disconnectसंकेत32)
#घोषणा USBDEVFS_CLAIMINTERFACE    _IOR('U', 15, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_RELEASEINTERFACE  _IOR('U', 16, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_CONNECTINFO       _IOW('U', 17, काष्ठा usbdevfs_connectinfo)
#घोषणा USBDEVFS_IOCTL             _IOWR('U', 18, काष्ठा usbdevfs_ioctl)
#घोषणा USBDEVFS_IOCTL32           _IOWR('U', 18, काष्ठा usbdevfs_ioctl32)
#घोषणा USBDEVFS_HUB_PORTINFO      _IOR('U', 19, काष्ठा usbdevfs_hub_portinfo)
#घोषणा USBDEVFS_RESET             _IO('U', 20)
#घोषणा USBDEVFS_CLEAR_HALT        _IOR('U', 21, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_DISCONNECT        _IO('U', 22)
#घोषणा USBDEVFS_CONNECT           _IO('U', 23)
#घोषणा USBDEVFS_CLAIM_PORT        _IOR('U', 24, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_RELEASE_PORT      _IOR('U', 25, अचिन्हित पूर्णांक)
#घोषणा USBDEVFS_GET_CAPABILITIES  _IOR('U', 26, __u32)
#घोषणा USBDEVFS_DISCONNECT_CLAIM  _IOR('U', 27, काष्ठा usbdevfs_disconnect_claim)
#घोषणा USBDEVFS_ALLOC_STREAMS     _IOR('U', 28, काष्ठा usbdevfs_streams)
#घोषणा USBDEVFS_FREE_STREAMS      _IOR('U', 29, काष्ठा usbdevfs_streams)
#घोषणा USBDEVFS_DROP_PRIVILEGES   _IOW('U', 30, __u32)
#घोषणा USBDEVFS_GET_SPEED         _IO('U', 31)
/*
 * Returns काष्ठा usbdevfs_conninfo_ex; length is variable to allow
 * extending size of the data वापसed.
 */
#घोषणा USBDEVFS_CONNINFO_EX(len)  _IOC(_IOC_READ, 'U', 32, len)
#घोषणा USBDEVFS_FORBID_SUSPEND    _IO('U', 33)
#घोषणा USBDEVFS_ALLOW_SUSPEND     _IO('U', 34)
#घोषणा USBDEVFS_WAIT_FOR_RESUME   _IO('U', 35)

#पूर्ण_अगर /* _UAPI_LINUX_USBDEVICE_FS_H */
