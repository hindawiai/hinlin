<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  User level driver support क्रम input subप्रणाली
 *
 * Heavily based on evdev.c by Vojtech Pavlik
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Author: Aristeu Sergio Rozanski Filho <aris@cathedralद_असल.org>
 *
 * Changes/Revisions:
 *	0.5	08/13/2015 (David Herrmann <dh.herrmann@gmail.com> &
 *			    Benjamin Tissoires <benjamin.tissoires@redhat.com>)
 *		- add UI_DEV_SETUP ioctl
 *		- add UI_ABS_SETUP ioctl
 *		- add UI_GET_VERSION ioctl
 *	0.4	01/09/2014 (Benjamin Tissoires <benjamin.tissoires@redhat.com>)
 *		- add UI_GET_SYSNAME ioctl
 *	0.3	24/05/2006 (Anssi Hannula <anssi.hannulagmail.com>)
 *		- update ff support क्रम the changes in kernel पूर्णांकerface
 *		- add UINPUT_VERSION
 *	0.2	16/10/2004 (Micah Dowty <micah@navi.cx>)
 *		- added क्रमce feedback support
 *             - added UI_SET_PHYS
 *	0.1	20/06/2002
 *		- first खुला version
 */
#अगर_अघोषित _UAPI__UINPUT_H_
#घोषणा _UAPI__UINPUT_H_

#समावेश <linux/types.h>
#समावेश <linux/input.h>

#घोषणा UINPUT_VERSION		5
#घोषणा UINPUT_MAX_NAME_SIZE	80

काष्ठा uinput_ff_upload अणु
	__u32			request_id;
	__s32			retval;
	काष्ठा ff_effect	effect;
	काष्ठा ff_effect	old;
पूर्ण;

काष्ठा uinput_ff_erase अणु
	__u32			request_id;
	__s32			retval;
	__u32			effect_id;
पूर्ण;

/* ioctl */
#घोषणा UINPUT_IOCTL_BASE	'U'
#घोषणा UI_DEV_CREATE		_IO(UINPUT_IOCTL_BASE, 1)
#घोषणा UI_DEV_DESTROY		_IO(UINPUT_IOCTL_BASE, 2)

काष्ठा uinput_setup अणु
	काष्ठा input_id id;
	अक्षर name[UINPUT_MAX_NAME_SIZE];
	__u32 ff_effects_max;
पूर्ण;

/**
 * UI_DEV_SETUP - Set device parameters क्रम setup
 *
 * This ioctl sets parameters क्रम the input device to be created.  It
 * supersedes the old "struct uinput_user_dev" method, which wrote this data
 * via ग_लिखो(). To actually set the असलolute axes UI_ABS_SETUP should be
 * used.
 *
 * The ioctl takes a "struct uinput_setup" object as argument. The fields of
 * this object are as follows:
 *              id: See the description of "struct input_id". This field is
 *                  copied unchanged पूर्णांकo the new device.
 *            name: This is used unchanged as name क्रम the new device.
 *  ff_effects_max: This limits the maximum numbers of क्रमce-feedback effects.
 *                  See below क्रम a description of FF with uinput.
 *
 * This ioctl can be called multiple बार and will overग_लिखो previous values.
 * If this ioctl fails with -EINVAL, it is recommended to use the old
 * "uinput_user_dev" method via ग_लिखो() as a fallback, in हाल you run on an
 * old kernel that करोes not support this ioctl.
 *
 * This ioctl may fail with -EINVAL अगर it is not supported or अगर you passed
 * incorrect values, -ENOMEM अगर the kernel runs out of memory or -EFAULT अगर the
 * passed uinput_setup object cannot be पढ़ो/written.
 * If this call fails, partial data may have alपढ़ोy been applied to the
 * पूर्णांकernal device.
 */
#घोषणा UI_DEV_SETUP _IOW(UINPUT_IOCTL_BASE, 3, काष्ठा uinput_setup)

काष्ठा uinput_असल_setup अणु
	__u16  code; /* axis code */
	/* __u16 filler; */
	काष्ठा input_असलinfo असलinfo;
पूर्ण;

/**
 * UI_ABS_SETUP - Set असलolute axis inक्रमmation क्रम the device to setup
 *
 * This ioctl sets one असलolute axis inक्रमmation क्रम the input device to be
 * created. It supersedes the old "struct uinput_user_dev" method, which wrote
 * part of this data and the content of UI_DEV_SETUP via ग_लिखो().
 *
 * The ioctl takes a "struct uinput_abs_setup" object as argument. The fields
 * of this object are as follows:
 *            code: The corresponding input code associated with this axis
 *                  (ABS_X, ABS_Y, etc...)
 *         असलinfo: See "struct input_absinfo" क्रम a description of this field.
 *                  This field is copied unchanged पूर्णांकo the kernel क्रम the
 *                  specअगरied axis. If the axis is not enabled via
 *                  UI_SET_ABSBIT, this ioctl will enable it.
 *
 * This ioctl can be called multiple बार and will overग_लिखो previous values.
 * If this ioctl fails with -EINVAL, it is recommended to use the old
 * "uinput_user_dev" method via ग_लिखो() as a fallback, in हाल you run on an
 * old kernel that करोes not support this ioctl.
 *
 * This ioctl may fail with -EINVAL अगर it is not supported or अगर you passed
 * incorrect values, -ENOMEM अगर the kernel runs out of memory or -EFAULT अगर the
 * passed uinput_setup object cannot be पढ़ो/written.
 * If this call fails, partial data may have alपढ़ोy been applied to the
 * पूर्णांकernal device.
 */
#घोषणा UI_ABS_SETUP _IOW(UINPUT_IOCTL_BASE, 4, काष्ठा uinput_असल_setup)

#घोषणा UI_SET_EVBIT		_IOW(UINPUT_IOCTL_BASE, 100, पूर्णांक)
#घोषणा UI_SET_KEYBIT		_IOW(UINPUT_IOCTL_BASE, 101, पूर्णांक)
#घोषणा UI_SET_RELBIT		_IOW(UINPUT_IOCTL_BASE, 102, पूर्णांक)
#घोषणा UI_SET_ABSBIT		_IOW(UINPUT_IOCTL_BASE, 103, पूर्णांक)
#घोषणा UI_SET_MSCBIT		_IOW(UINPUT_IOCTL_BASE, 104, पूर्णांक)
#घोषणा UI_SET_LEDBIT		_IOW(UINPUT_IOCTL_BASE, 105, पूर्णांक)
#घोषणा UI_SET_SNDBIT		_IOW(UINPUT_IOCTL_BASE, 106, पूर्णांक)
#घोषणा UI_SET_FFBIT		_IOW(UINPUT_IOCTL_BASE, 107, पूर्णांक)
#घोषणा UI_SET_PHYS		_IOW(UINPUT_IOCTL_BASE, 108, अक्षर*)
#घोषणा UI_SET_SWBIT		_IOW(UINPUT_IOCTL_BASE, 109, पूर्णांक)
#घोषणा UI_SET_PROPBIT		_IOW(UINPUT_IOCTL_BASE, 110, पूर्णांक)

#घोषणा UI_BEGIN_FF_UPLOAD	_IOWR(UINPUT_IOCTL_BASE, 200, काष्ठा uinput_ff_upload)
#घोषणा UI_END_FF_UPLOAD	_IOW(UINPUT_IOCTL_BASE, 201, काष्ठा uinput_ff_upload)
#घोषणा UI_BEGIN_FF_ERASE	_IOWR(UINPUT_IOCTL_BASE, 202, काष्ठा uinput_ff_erase)
#घोषणा UI_END_FF_ERASE		_IOW(UINPUT_IOCTL_BASE, 203, काष्ठा uinput_ff_erase)

/**
 * UI_GET_SYSNAME - get the sysfs name of the created uinput device
 *
 * @वापस the sysfs name of the created भव input device.
 * The complete sysfs path is then /sys/devices/भव/input/--NAME--
 * Usually, it is in the क्रमm "inputN"
 */
#घोषणा UI_GET_SYSNAME(len)	_IOC(_IOC_READ, UINPUT_IOCTL_BASE, 44, len)

/**
 * UI_GET_VERSION - Return version of uinput protocol
 *
 * This ग_लिखोs uinput protocol version implemented by the kernel पूर्णांकo
 * the पूर्णांकeger poपूर्णांकed to by the ioctl argument. The protocol version
 * is hard-coded in the kernel and is independent of the uinput device.
 */
#घोषणा UI_GET_VERSION		_IOR(UINPUT_IOCTL_BASE, 45, अचिन्हित पूर्णांक)

/*
 * To ग_लिखो a क्रमce-feedback-capable driver, the upload_effect
 * and erase_effect callbacks in input_dev must be implemented.
 * The uinput driver will generate a fake input event when one of
 * these callbacks are invoked. The userspace code then uses
 * ioctls to retrieve additional parameters and send the वापस code.
 * The callback blocks until this वापस code is sent.
 *
 * The described callback mechanism is only used अगर ff_effects_max
 * is set.
 *
 * To implement upload_effect():
 *   1. Wait क्रम an event with type == EV_UINPUT and code == UI_FF_UPLOAD.
 *      A request ID will be given in 'value'.
 *   2. Allocate a uinput_ff_upload काष्ठा, fill in request_id with
 *      the 'value' from the EV_UINPUT event.
 *   3. Issue a UI_BEGIN_FF_UPLOAD ioctl, giving it the
 *      uinput_ff_upload काष्ठा. It will be filled in with the
 *      ff_effects passed to upload_effect().
 *   4. Perक्रमm the effect upload, and place a वापस code back पूर्णांकo
        the uinput_ff_upload काष्ठा.
 *   5. Issue a UI_END_FF_UPLOAD ioctl, also giving it the
 *      uinput_ff_upload_effect काष्ठा. This will complete execution
 *      of our upload_effect() handler.
 *
 * To implement erase_effect():
 *   1. Wait क्रम an event with type == EV_UINPUT and code == UI_FF_ERASE.
 *      A request ID will be given in 'value'.
 *   2. Allocate a uinput_ff_erase काष्ठा, fill in request_id with
 *      the 'value' from the EV_UINPUT event.
 *   3. Issue a UI_BEGIN_FF_ERASE ioctl, giving it the
 *      uinput_ff_erase काष्ठा. It will be filled in with the
 *      effect ID passed to erase_effect().
 *   4. Perक्रमm the effect erasure, and place a वापस code back
 *      पूर्णांकo the uinput_ff_erase काष्ठा.
 *   5. Issue a UI_END_FF_ERASE ioctl, also giving it the
 *      uinput_ff_erase_effect काष्ठा. This will complete execution
 *      of our erase_effect() handler.
 */

/*
 * This is the new event type, used only by uinput.
 * 'code' is UI_FF_UPLOAD or UI_FF_ERASE, and 'value'
 * is the unique request ID. This number was picked
 * arbitrarily, above EV_MAX (since the input प्रणाली
 * never sees it) but in the range of a 16-bit पूर्णांक.
 */
#घोषणा EV_UINPUT		0x0101
#घोषणा UI_FF_UPLOAD		1
#घोषणा UI_FF_ERASE		2

काष्ठा uinput_user_dev अणु
	अक्षर name[UINPUT_MAX_NAME_SIZE];
	काष्ठा input_id id;
	__u32 ff_effects_max;
	__s32 असलmax[ABS_CNT];
	__s32 असलmin[ABS_CNT];
	__s32 असलfuzz[ABS_CNT];
	__s32 असलflat[ABS_CNT];
पूर्ण;
#पूर्ण_अगर /* _UAPI__UINPUT_H_ */
