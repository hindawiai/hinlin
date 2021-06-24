<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2006-2007 Jiri Kosina
 */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */
#अगर_अघोषित _UAPI__HID_H
#घोषणा _UAPI__HID_H



/*
 * USB HID (Human Interface Device) पूर्णांकerface class code
 */

#घोषणा USB_INTERFACE_CLASS_HID		3

/*
 * USB HID पूर्णांकerface subclass and protocol codes
 */

#घोषणा USB_INTERFACE_SUBCLASS_BOOT	1
#घोषणा USB_INTERFACE_PROTOCOL_KEYBOARD	1
#घोषणा USB_INTERFACE_PROTOCOL_MOUSE	2

/*
 * HID class requests
 */

#घोषणा HID_REQ_GET_REPORT		0x01
#घोषणा HID_REQ_GET_IDLE		0x02
#घोषणा HID_REQ_GET_PROTOCOL		0x03
#घोषणा HID_REQ_SET_REPORT		0x09
#घोषणा HID_REQ_SET_IDLE		0x0A
#घोषणा HID_REQ_SET_PROTOCOL		0x0B

/*
 * HID class descriptor types
 */

#घोषणा HID_DT_HID			(USB_TYPE_CLASS | 0x01)
#घोषणा HID_DT_REPORT			(USB_TYPE_CLASS | 0x02)
#घोषणा HID_DT_PHYSICAL			(USB_TYPE_CLASS | 0x03)

#घोषणा HID_MAX_DESCRIPTOR_SIZE		4096


#पूर्ण_अगर /* _UAPI__HID_H */
