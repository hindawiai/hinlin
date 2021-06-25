<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * i8k.h -- Linux driver क्रम accessing the SMM BIOS on Dell laptops
 *
 * Copyright (C) 2001  Massimo Dal Zotto <dz@debian.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#अगर_अघोषित _LINUX_I8K_H
#घोषणा _LINUX_I8K_H

#घोषणा I8K_PROC		"/proc/i8k"
#घोषणा I8K_PROC_FMT		"1.0"

#घोषणा I8K_BIOS_VERSION	_IOR ('i', 0x80, पूर्णांक)	/* broken: meant 4 bytes */
#घोषणा I8K_MACHINE_ID		_IOR ('i', 0x81, पूर्णांक)	/* broken: meant 16 bytes */
#घोषणा I8K_POWER_STATUS	_IOR ('i', 0x82, माप_प्रकार)
#घोषणा I8K_FN_STATUS		_IOR ('i', 0x83, माप_प्रकार)
#घोषणा I8K_GET_TEMP		_IOR ('i', 0x84, माप_प्रकार)
#घोषणा I8K_GET_SPEED		_IOWR('i', 0x85, माप_प्रकार)
#घोषणा I8K_GET_FAN		_IOWR('i', 0x86, माप_प्रकार)
#घोषणा I8K_SET_FAN		_IOWR('i', 0x87, माप_प्रकार)

#घोषणा I8K_FAN_LEFT		1
#घोषणा I8K_FAN_RIGHT		0
#घोषणा I8K_FAN_OFF		0
#घोषणा I8K_FAN_LOW		1
#घोषणा I8K_FAN_HIGH		2
#घोषणा I8K_FAN_TURBO		3
#घोषणा I8K_FAN_MAX		I8K_FAN_TURBO

#घोषणा I8K_VOL_UP		1
#घोषणा I8K_VOL_DOWN		2
#घोषणा I8K_VOL_MUTE		4

#घोषणा I8K_AC			1
#घोषणा I8K_BATTERY		0

#पूर्ण_अगर
