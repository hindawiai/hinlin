<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (c) 1999-2000 Vojtech Pavlik
 *
 *  Sponsored by SuSE
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
 * e-mail - mail your message to <vojtech@suse.cz>, or by paper mail:
 * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Reखुला
 */
#अगर_अघोषित _UAPI_HIDDEV_H
#घोषणा _UAPI_HIDDEV_H



#समावेश <linux/types.h>

/*
 * The event काष्ठाure itself
 */

काष्ठा hiddev_event अणु
	अचिन्हित hid;
	चिन्हित पूर्णांक value;
पूर्ण;

काष्ठा hiddev_devinfo अणु
	__u32 bustype;
	__u32 busnum;
	__u32 devnum;
	__u32 अगरnum;
	__s16 venकरोr;
	__s16 product;
	__s16 version;
	__u32 num_applications;
पूर्ण;

काष्ठा hiddev_collection_info अणु
	__u32 index;
	__u32 type;
	__u32 usage;
	__u32 level;
पूर्ण;

#घोषणा HID_STRING_SIZE 256
काष्ठा hiddev_string_descriptor अणु
	__s32 index;
	अक्षर value[HID_STRING_SIZE];
पूर्ण;

काष्ठा hiddev_report_info अणु
	__u32 report_type;
	__u32 report_id;
	__u32 num_fields;
पूर्ण;

/* To करो a GUSAGE/SUSAGE, fill in at least usage_code,  report_type and 
 * report_id.  Set report_id to REPORT_ID_UNKNOWN अगर the rest of the fields 
 * are unknown.  Otherwise use a usage_ref काष्ठा filled in from a previous 
 * successful GUSAGE call to save समय.  To actually send a value to the
 * device, perक्रमm a SUSAGE first, followed by a SREPORT.  An INITREPORT or a
 * GREPORT isn't necessary क्रम a GUSAGE to वापस valid data.
 */
#घोषणा HID_REPORT_ID_UNKNOWN 0xffffffff
#घोषणा HID_REPORT_ID_FIRST   0x00000100
#घोषणा HID_REPORT_ID_NEXT    0x00000200
#घोषणा HID_REPORT_ID_MASK    0x000000ff
#घोषणा HID_REPORT_ID_MAX     0x000000ff

#घोषणा HID_REPORT_TYPE_INPUT	1
#घोषणा HID_REPORT_TYPE_OUTPUT	2
#घोषणा HID_REPORT_TYPE_FEATURE	3
#घोषणा HID_REPORT_TYPE_MIN     1
#घोषणा HID_REPORT_TYPE_MAX     3

काष्ठा hiddev_field_info अणु
	__u32 report_type;
	__u32 report_id;
	__u32 field_index;
	__u32 maxusage;
	__u32 flags;
	__u32 physical;		/* physical usage क्रम this field */
	__u32 logical;		/* logical usage क्रम this field */
	__u32 application;		/* application usage क्रम this field */
	__s32 logical_minimum;
	__s32 logical_maximum;
	__s32 physical_minimum;
	__s32 physical_maximum;
	__u32 unit_exponent;
	__u32 unit;
पूर्ण;

/* Fill in report_type, report_id and field_index to get the inक्रमmation on a
 * field.
 */
#घोषणा HID_FIELD_CONSTANT		0x001
#घोषणा HID_FIELD_VARIABLE		0x002
#घोषणा HID_FIELD_RELATIVE		0x004
#घोषणा HID_FIELD_WRAP			0x008	
#घोषणा HID_FIELD_NONLINEAR		0x010
#घोषणा HID_FIELD_NO_PREFERRED		0x020
#घोषणा HID_FIELD_शून्य_STATE		0x040
#घोषणा HID_FIELD_VOLATILE		0x080
#घोषणा HID_FIELD_BUFFERED_BYTE		0x100

काष्ठा hiddev_usage_ref अणु
	__u32 report_type;
	__u32 report_id;
	__u32 field_index;
	__u32 usage_index;
	__u32 usage_code;
	__s32 value;
पूर्ण;

/* hiddev_usage_ref_multi is used क्रम sending multiple bytes to a control.
 * It really manअगरests itself as setting the value of consecutive usages */
#घोषणा HID_MAX_MULTI_USAGES 1024
काष्ठा hiddev_usage_ref_multi अणु
	काष्ठा hiddev_usage_ref uref;
	__u32 num_values;
	__s32 values[HID_MAX_MULTI_USAGES];
पूर्ण;

/* FIELD_INDEX_NONE is वापसed in पढ़ो() data from the kernel when flags
 * is set to (HIDDEV_FLAG_UREF | HIDDEV_FLAG_REPORT) and a new report has
 * been sent by the device 
 */
#घोषणा HID_FIELD_INDEX_NONE 0xffffffff

/*
 * Protocol version.
 */

#घोषणा HID_VERSION		0x010004

/*
 * IOCTLs (0x00 - 0x7f)
 */

#घोषणा HIDIOCGVERSION		_IOR('H', 0x01, पूर्णांक)
#घोषणा HIDIOCAPPLICATION	_IO('H', 0x02)
#घोषणा HIDIOCGDEVINFO		_IOR('H', 0x03, काष्ठा hiddev_devinfo)
#घोषणा HIDIOCGSTRING		_IOR('H', 0x04, काष्ठा hiddev_string_descriptor)
#घोषणा HIDIOCINITREPORT	_IO('H', 0x05)
#घोषणा HIDIOCGNAME(len)	_IOC(_IOC_READ, 'H', 0x06, len)
#घोषणा HIDIOCGREPORT		_IOW('H', 0x07, काष्ठा hiddev_report_info)
#घोषणा HIDIOCSREPORT		_IOW('H', 0x08, काष्ठा hiddev_report_info)
#घोषणा HIDIOCGREPORTINFO	_IOWR('H', 0x09, काष्ठा hiddev_report_info)
#घोषणा HIDIOCGFIELDINFO	_IOWR('H', 0x0A, काष्ठा hiddev_field_info)
#घोषणा HIDIOCGUSAGE		_IOWR('H', 0x0B, काष्ठा hiddev_usage_ref)
#घोषणा HIDIOCSUSAGE		_IOW('H', 0x0C, काष्ठा hiddev_usage_ref)
#घोषणा HIDIOCGUCODE		_IOWR('H', 0x0D, काष्ठा hiddev_usage_ref)
#घोषणा HIDIOCGFLAG		_IOR('H', 0x0E, पूर्णांक)
#घोषणा HIDIOCSFLAG		_IOW('H', 0x0F, पूर्णांक)
#घोषणा HIDIOCGCOLLECTIONINDEX	_IOW('H', 0x10, काष्ठा hiddev_usage_ref)
#घोषणा HIDIOCGCOLLECTIONINFO	_IOWR('H', 0x11, काष्ठा hiddev_collection_info)
#घोषणा HIDIOCGPHYS(len)	_IOC(_IOC_READ, 'H', 0x12, len)

/* For writing/पढ़ोing to multiple/consecutive usages */
#घोषणा HIDIOCGUSAGES		_IOWR('H', 0x13, काष्ठा hiddev_usage_ref_multi)
#घोषणा HIDIOCSUSAGES		_IOW('H', 0x14, काष्ठा hiddev_usage_ref_multi)

/* 
 * Flags to be used in HIDIOCSFLAG
 */
#घोषणा HIDDEV_FLAG_UREF	0x1
#घोषणा HIDDEV_FLAG_REPORT	0x2
#घोषणा HIDDEV_FLAGS		0x3

/* To traverse the input report descriptor info क्रम a HID device, perक्रमm the 
 * following:
 *
 * rinfo.report_type = HID_REPORT_TYPE_INPUT;
 * rinfo.report_id = HID_REPORT_ID_FIRST;
 * ret = ioctl(fd, HIDIOCGREPORTINFO, &rinfo);
 *
 * जबतक (ret >= 0) अणु
 * 	क्रम (i = 0; i < rinfo.num_fields; i++) अणु
 * 		finfo.report_type = rinfo.report_type;
 * 		finfo.report_id = rinfo.report_id;
 * 		finfo.field_index = i;
 * 		ioctl(fd, HIDIOCGFIELDINFO, &finfo);
 * 		क्रम (j = 0; j < finfo.maxusage; j++) अणु
 * 			uref.report_type = rinfo.report_type;
 * 			uref.report_id = rinfo.report_id;
 * 			uref.field_index = i;
 * 			uref.usage_index = j;
 * 			ioctl(fd, HIDIOCGUCODE, &uref);
 * 			ioctl(fd, HIDIOCGUSAGE, &uref);
 * 		पूर्ण
 * 	पूर्ण
 * 	rinfo.report_id |= HID_REPORT_ID_NEXT;
 * 	ret = ioctl(fd, HIDIOCGREPORTINFO, &rinfo);
 * पूर्ण
 */


#पूर्ण_अगर /* _UAPI_HIDDEV_H */
