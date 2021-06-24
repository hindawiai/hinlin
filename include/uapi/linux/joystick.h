<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (C) 1996-2000 Vojtech Pavlik
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
 */
#अगर_अघोषित _UAPI_LINUX_JOYSTICK_H
#घोषणा _UAPI_LINUX_JOYSTICK_H



#समावेश <linux/types.h>
#समावेश <linux/input.h>

/*
 * Version
 */

#घोषणा JS_VERSION		0x020100

/*
 * Types and स्थिरants क्रम पढ़ोing from /dev/js
 */

#घोषणा JS_EVENT_BUTTON		0x01	/* button pressed/released */
#घोषणा JS_EVENT_AXIS		0x02	/* joystick moved */
#घोषणा JS_EVENT_INIT		0x80	/* initial state of device */

काष्ठा js_event अणु
	__u32 समय;	/* event बारtamp in milliseconds */
	__s16 value;	/* value */
	__u8 type;	/* event type */
	__u8 number;	/* axis/button number */
पूर्ण;

/*
 * IOCTL commands क्रम joystick driver
 */

#घोषणा JSIOCGVERSION		_IOR('j', 0x01, __u32)				/* get driver version */

#घोषणा JSIOCGAXES		_IOR('j', 0x11, __u8)				/* get number of axes */
#घोषणा JSIOCGBUTTONS		_IOR('j', 0x12, __u8)				/* get number of buttons */
#घोषणा JSIOCGNAME(len)		_IOC(_IOC_READ, 'j', 0x13, len)			/* get identअगरier string */

#घोषणा JSIOCSCORR		_IOW('j', 0x21, काष्ठा js_corr)			/* set correction values */
#घोषणा JSIOCGCORR		_IOR('j', 0x22, काष्ठा js_corr)			/* get correction values */

#घोषणा JSIOCSAXMAP		_IOW('j', 0x31, __u8[ABS_CNT])			/* set axis mapping */
#घोषणा JSIOCGAXMAP		_IOR('j', 0x32, __u8[ABS_CNT])			/* get axis mapping */
#घोषणा JSIOCSBTNMAP		_IOW('j', 0x33, __u16[KEY_MAX - BTN_MISC + 1])	/* set button mapping */
#घोषणा JSIOCGBTNMAP		_IOR('j', 0x34, __u16[KEY_MAX - BTN_MISC + 1])	/* get button mapping */

/*
 * Types and स्थिरants क्रम get/set correction
 */

#घोषणा JS_CORR_NONE		0x00	/* वापसs raw values */
#घोषणा JS_CORR_BROKEN		0x01	/* broken line */

काष्ठा js_corr अणु
	__s32 coef[8];
	__s16 prec;
	__u16 type;
पूर्ण;

/*
 * v0.x compatibility definitions
 */

#घोषणा JS_RETURN		माप(काष्ठा JS_DATA_TYPE)
#घोषणा JS_TRUE			1
#घोषणा JS_FALSE		0
#घोषणा JS_X_0			0x01
#घोषणा JS_Y_0			0x02
#घोषणा JS_X_1			0x04
#घोषणा JS_Y_1			0x08
#घोषणा JS_MAX			2

#घोषणा JS_DEF_TIMEOUT		0x1300
#घोषणा JS_DEF_CORR		0
#घोषणा JS_DEF_TIMELIMIT	10L

#घोषणा JS_SET_CAL		1
#घोषणा JS_GET_CAL		2
#घोषणा JS_SET_TIMEOUT		3
#घोषणा JS_GET_TIMEOUT		4
#घोषणा JS_SET_TIMELIMIT	5
#घोषणा JS_GET_TIMELIMIT	6
#घोषणा JS_GET_ALL		7
#घोषणा JS_SET_ALL		8

काष्ठा JS_DATA_TYPE अणु
	__s32 buttons;
	__s32 x;
	__s32 y;
पूर्ण;

काष्ठा JS_DATA_SAVE_TYPE_32 अणु
	__s32 JS_TIMEOUT;
	__s32 BUSY;
	__s32 JS_EXPIRETIME;
	__s32 JS_TIMELIMIT;
	काष्ठा JS_DATA_TYPE JS_SAVE;
	काष्ठा JS_DATA_TYPE JS_CORR;
पूर्ण;

काष्ठा JS_DATA_SAVE_TYPE_64 अणु
	__s32 JS_TIMEOUT;
	__s32 BUSY;
	__s64 JS_EXPIRETIME;
	__s64 JS_TIMELIMIT;
	काष्ठा JS_DATA_TYPE JS_SAVE;
	काष्ठा JS_DATA_TYPE JS_CORR;
पूर्ण;


#पूर्ण_अगर /* _UAPI_LINUX_JOYSTICK_H */
