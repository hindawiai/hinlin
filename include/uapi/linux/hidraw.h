<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  Copyright (c) 2007 Jiri Kosina
 */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 */
#अगर_अघोषित _UAPI_HIDRAW_H
#घोषणा _UAPI_HIDRAW_H



#समावेश <linux/hid.h>
#समावेश <linux/types.h>

काष्ठा hidraw_report_descriptor अणु
	__u32 size;
	__u8 value[HID_MAX_DESCRIPTOR_SIZE];
पूर्ण;

काष्ठा hidraw_devinfo अणु
	__u32 bustype;
	__s16 venकरोr;
	__s16 product;
पूर्ण;

/* ioctl पूर्णांकerface */
#घोषणा HIDIOCGRDESCSIZE	_IOR('H', 0x01, पूर्णांक)
#घोषणा HIDIOCGRDESC		_IOR('H', 0x02, काष्ठा hidraw_report_descriptor)
#घोषणा HIDIOCGRAWINFO		_IOR('H', 0x03, काष्ठा hidraw_devinfo)
#घोषणा HIDIOCGRAWNAME(len)     _IOC(_IOC_READ, 'H', 0x04, len)
#घोषणा HIDIOCGRAWPHYS(len)     _IOC(_IOC_READ, 'H', 0x05, len)
/* The first byte of SFEATURE and GFEATURE is the report number */
#घोषणा HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
#घोषणा HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
#घोषणा HIDIOCGRAWUNIQ(len)     _IOC(_IOC_READ, 'H', 0x08, len)
/* The first byte of SINPUT and GINPUT is the report number */
#घोषणा HIDIOCSINPUT(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x09, len)
#घोषणा HIDIOCGINPUT(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x0A, len)
/* The first byte of SOUTPUT and GOUTPUT is the report number */
#घोषणा HIDIOCSOUTPUT(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x0B, len)
#घोषणा HIDIOCGOUTPUT(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x0C, len)

#घोषणा HIDRAW_FIRST_MINOR 0
#घोषणा HIDRAW_MAX_DEVICES 64
/* number of reports to buffer */
#घोषणा HIDRAW_BUFFER_SIZE 64


/* kernel-only API declarations */

#पूर्ण_अगर /* _UAPI_HIDRAW_H */
