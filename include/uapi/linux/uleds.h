<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Userspace driver support क्रम the LED subप्रणाली
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
 */
#अगर_अघोषित _UAPI__ULEDS_H_
#घोषणा _UAPI__ULEDS_H_

#घोषणा LED_MAX_NAME_SIZE	64

काष्ठा uleds_user_dev अणु
	अक्षर name[LED_MAX_NAME_SIZE];
	पूर्णांक max_brightness;
पूर्ण;

#पूर्ण_अगर /* _UAPI__ULEDS_H_ */
