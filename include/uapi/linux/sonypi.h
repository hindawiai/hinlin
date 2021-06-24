<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Sony Programmable I/O Control Device driver क्रम VAIO
 *
 * Copyright (C) 2001-2005 Stelian Pop <stelian@popies.net>
 *
 * Copyright (C) 2005 Narayanan R S <nars@kadamba.org>

 * Copyright (C) 2001-2002 Alcथखve <www.alcove.com>
 *
 * Copyright (C) 2001 Michael Ashley <m.ashley@unsw.edu.au>
 *
 * Copyright (C) 2001 Junichi Morita <jun1m@mars.dti.ne.jp>
 *
 * Copyright (C) 2000 Takaya Kinjo <t-kinjo@tc4.so-net.ne.jp>
 *
 * Copyright (C) 2000 Andrew Tridgell <tridge@valinux.com>
 *
 * Earlier work by Werner Almesberger, Paul `Rusty' Russell and Paul Mackerras.
 *
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#अगर_अघोषित _UAPI_SONYPI_H_
#घोषणा _UAPI_SONYPI_H_

#समावेश <linux/types.h>

/* events the user application पढ़ोing /dev/sonypi can use */

#घोषणा SONYPI_EVENT_IGNORE			 0
#घोषणा SONYPI_EVENT_JOGDIAL_DOWN		 1
#घोषणा SONYPI_EVENT_JOGDIAL_UP			 2
#घोषणा SONYPI_EVENT_JOGDIAL_DOWN_PRESSED	 3
#घोषणा SONYPI_EVENT_JOGDIAL_UP_PRESSED		 4
#घोषणा SONYPI_EVENT_JOGDIAL_PRESSED		 5
#घोषणा SONYPI_EVENT_JOGDIAL_RELEASED		 6	/* obsolete */
#घोषणा SONYPI_EVENT_CAPTURE_PRESSED		 7
#घोषणा SONYPI_EVENT_CAPTURE_RELEASED		 8	/* obsolete */
#घोषणा SONYPI_EVENT_CAPTURE_PARTIALPRESSED	 9
#घोषणा SONYPI_EVENT_CAPTURE_PARTIALRELEASED	10
#घोषणा SONYPI_EVENT_FNKEY_ESC			11
#घोषणा SONYPI_EVENT_FNKEY_F1			12
#घोषणा SONYPI_EVENT_FNKEY_F2			13
#घोषणा SONYPI_EVENT_FNKEY_F3			14
#घोषणा SONYPI_EVENT_FNKEY_F4			15
#घोषणा SONYPI_EVENT_FNKEY_F5			16
#घोषणा SONYPI_EVENT_FNKEY_F6			17
#घोषणा SONYPI_EVENT_FNKEY_F7			18
#घोषणा SONYPI_EVENT_FNKEY_F8			19
#घोषणा SONYPI_EVENT_FNKEY_F9			20
#घोषणा SONYPI_EVENT_FNKEY_F10			21
#घोषणा SONYPI_EVENT_FNKEY_F11			22
#घोषणा SONYPI_EVENT_FNKEY_F12			23
#घोषणा SONYPI_EVENT_FNKEY_1			24
#घोषणा SONYPI_EVENT_FNKEY_2			25
#घोषणा SONYPI_EVENT_FNKEY_D			26
#घोषणा SONYPI_EVENT_FNKEY_E			27
#घोषणा SONYPI_EVENT_FNKEY_F			28
#घोषणा SONYPI_EVENT_FNKEY_S			29
#घोषणा SONYPI_EVENT_FNKEY_B			30
#घोषणा SONYPI_EVENT_BLUETOOTH_PRESSED		31
#घोषणा SONYPI_EVENT_PKEY_P1			32
#घोषणा SONYPI_EVENT_PKEY_P2			33
#घोषणा SONYPI_EVENT_PKEY_P3			34
#घोषणा SONYPI_EVENT_BACK_PRESSED		35
#घोषणा SONYPI_EVENT_LID_CLOSED			36
#घोषणा SONYPI_EVENT_LID_OPENED			37
#घोषणा SONYPI_EVENT_BLUETOOTH_ON		38
#घोषणा SONYPI_EVENT_BLUETOOTH_OFF		39
#घोषणा SONYPI_EVENT_HELP_PRESSED		40
#घोषणा SONYPI_EVENT_FNKEY_ONLY			41
#घोषणा SONYPI_EVENT_JOGDIAL_FAST_DOWN		42
#घोषणा SONYPI_EVENT_JOGDIAL_FAST_UP		43
#घोषणा SONYPI_EVENT_JOGDIAL_FAST_DOWN_PRESSED	44
#घोषणा SONYPI_EVENT_JOGDIAL_FAST_UP_PRESSED	45
#घोषणा SONYPI_EVENT_JOGDIAL_VFAST_DOWN		46
#घोषणा SONYPI_EVENT_JOGDIAL_VFAST_UP		47
#घोषणा SONYPI_EVENT_JOGDIAL_VFAST_DOWN_PRESSED	48
#घोषणा SONYPI_EVENT_JOGDIAL_VFAST_UP_PRESSED	49
#घोषणा SONYPI_EVENT_ZOOM_PRESSED		50
#घोषणा SONYPI_EVENT_THUMBPHRASE_PRESSED	51
#घोषणा SONYPI_EVENT_MEYE_FACE			52
#घोषणा SONYPI_EVENT_MEYE_OPPOSITE		53
#घोषणा SONYPI_EVENT_MEMORYSTICK_INSERT		54
#घोषणा SONYPI_EVENT_MEMORYSTICK_EJECT		55
#घोषणा SONYPI_EVENT_ANYBUTTON_RELEASED		56
#घोषणा SONYPI_EVENT_BATTERY_INSERT		57
#घोषणा SONYPI_EVENT_BATTERY_REMOVE		58
#घोषणा SONYPI_EVENT_FNKEY_RELEASED		59
#घोषणा SONYPI_EVENT_WIRELESS_ON		60
#घोषणा SONYPI_EVENT_WIRELESS_OFF		61
#घोषणा SONYPI_EVENT_ZOOM_IN_PRESSED		62
#घोषणा SONYPI_EVENT_ZOOM_OUT_PRESSED		63
#घोषणा SONYPI_EVENT_CD_EJECT_PRESSED		64
#घोषणा SONYPI_EVENT_MODEKEY_PRESSED		65
#घोषणा SONYPI_EVENT_PKEY_P4			66
#घोषणा SONYPI_EVENT_PKEY_P5			67
#घोषणा SONYPI_EVENT_SETTINGKEY_PRESSED		68
#घोषणा SONYPI_EVENT_VOLUME_INC_PRESSED		69
#घोषणा SONYPI_EVENT_VOLUME_DEC_PRESSED		70
#घोषणा SONYPI_EVENT_BRIGHTNESS_PRESSED		71
#घोषणा SONYPI_EVENT_MEDIA_PRESSED		72
#घोषणा SONYPI_EVENT_VENDOR_PRESSED		73

/* get/set brightness */
#घोषणा SONYPI_IOCGBRT		_IOR('v', 0, __u8)
#घोषणा SONYPI_IOCSBRT		_IOW('v', 0, __u8)

/* get battery full capacity/reमुख्यing capacity */
#घोषणा SONYPI_IOCGBAT1CAP	_IOR('v', 2, __u16)
#घोषणा SONYPI_IOCGBAT1REM	_IOR('v', 3, __u16)
#घोषणा SONYPI_IOCGBAT2CAP	_IOR('v', 4, __u16)
#घोषणा SONYPI_IOCGBAT2REM	_IOR('v', 5, __u16)

/* get battery flags: battery1/battery2/ac adapter present */
#घोषणा SONYPI_BFLAGS_B1	0x01
#घोषणा SONYPI_BFLAGS_B2	0x02
#घोषणा SONYPI_BFLAGS_AC	0x04
#घोषणा SONYPI_IOCGBATFLAGS	_IOR('v', 7, __u8)

/* get/set bluetooth subप्रणाली state on/off */
#घोषणा SONYPI_IOCGBLUE		_IOR('v', 8, __u8)
#घोषणा SONYPI_IOCSBLUE		_IOW('v', 9, __u8)

/* get/set fan state on/off */
#घोषणा SONYPI_IOCGFAN		_IOR('v', 10, __u8)
#घोषणा SONYPI_IOCSFAN		_IOW('v', 11, __u8)

/* get temperature (C) */
#घोषणा SONYPI_IOCGTEMP		_IOR('v', 12, __u8)


#पूर्ण_अगर /* _UAPI_SONYPI_H_ */
