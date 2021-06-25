<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
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
#अगर_अघोषित _LINUX_USBDEVICE_FS_H
#घोषणा _LINUX_USBDEVICE_FS_H

#समावेश <uapi/linux/usbdevice_fs.h>

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

काष्ठा usbdevfs_ctrltransfer32 अणु
        u8 bRequestType;
        u8 bRequest;
        u16 wValue;
        u16 wIndex;
        u16 wLength;
        u32 समयout;  /* in milliseconds */
        compat_caddr_t data;
पूर्ण;

काष्ठा usbdevfs_bulktransfer32 अणु
        compat_uपूर्णांक_t ep;
        compat_uपूर्णांक_t len;
        compat_uपूर्णांक_t समयout; /* in milliseconds */
        compat_caddr_t data;
पूर्ण;

काष्ठा usbdevfs_disconnectसंकेत32 अणु
        compat_पूर्णांक_t signr;
        compat_caddr_t context;
पूर्ण;

काष्ठा usbdevfs_urb32 अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर endpoपूर्णांक;
	compat_पूर्णांक_t status;
	compat_uपूर्णांक_t flags;
	compat_caddr_t buffer;
	compat_पूर्णांक_t buffer_length;
	compat_पूर्णांक_t actual_length;
	compat_पूर्णांक_t start_frame;
	compat_पूर्णांक_t number_of_packets;
	compat_पूर्णांक_t error_count;
	compat_uपूर्णांक_t signr;
	compat_caddr_t usercontext; /* unused */
	काष्ठा usbdevfs_iso_packet_desc iso_frame_desc[];
पूर्ण;

काष्ठा usbdevfs_ioctl32 अणु
	s32 अगरno;
	s32 ioctl_code;
	compat_caddr_t data;
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_USBDEVICE_FS_H */
