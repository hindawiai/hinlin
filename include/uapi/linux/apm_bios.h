<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Include file क्रम the पूर्णांकerface to an APM BIOS
 * Copyright 1994-2001 Stephen Rothwell (sfr@canb.auug.org.au)
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
#अगर_अघोषित _UAPI_LINUX_APM_H
#घोषणा _UAPI_LINUX_APM_H


#समावेश <linux/types.h>

प्रकार अचिन्हित लघु	apm_event_t;
प्रकार अचिन्हित लघु	apm_eventinfo_t;

काष्ठा apm_bios_info अणु
	__u16	version;
	__u16	cseg;
	__u32	offset;
	__u16	cseg_16;
	__u16	dseg;
	__u16	flags;
	__u16	cseg_len;
	__u16	cseg_16_len;
	__u16	dseg_len;
पूर्ण;


/*
 * Power states
 */
#घोषणा APM_STATE_READY		0x0000
#घोषणा APM_STATE_STANDBY	0x0001
#घोषणा APM_STATE_SUSPEND	0x0002
#घोषणा APM_STATE_OFF		0x0003
#घोषणा APM_STATE_BUSY		0x0004
#घोषणा APM_STATE_REJECT	0x0005
#घोषणा APM_STATE_OEM_SYS	0x0020
#घोषणा APM_STATE_OEM_DEV	0x0040

#घोषणा APM_STATE_DISABLE	0x0000
#घोषणा APM_STATE_ENABLE	0x0001

#घोषणा APM_STATE_DISENGAGE	0x0000
#घोषणा APM_STATE_ENGAGE	0x0001

/*
 * Events (results of Get PM Event)
 */
#घोषणा APM_SYS_STANDBY		0x0001
#घोषणा APM_SYS_SUSPEND		0x0002
#घोषणा APM_NORMAL_RESUME	0x0003
#घोषणा APM_CRITICAL_RESUME	0x0004
#घोषणा APM_LOW_BATTERY		0x0005
#घोषणा APM_POWER_STATUS_CHANGE	0x0006
#घोषणा APM_UPDATE_TIME		0x0007
#घोषणा APM_CRITICAL_SUSPEND	0x0008
#घोषणा APM_USER_STANDBY	0x0009
#घोषणा APM_USER_SUSPEND	0x000a
#घोषणा APM_STANDBY_RESUME	0x000b
#घोषणा APM_CAPABILITY_CHANGE	0x000c
#घोषणा APM_USER_HIBERNATION	0x000d
#घोषणा APM_HIBERNATION_RESUME	0x000e

/*
 * Error codes
 */
#घोषणा APM_SUCCESS		0x00
#घोषणा APM_DISABLED		0x01
#घोषणा APM_CONNECTED		0x02
#घोषणा APM_NOT_CONNECTED	0x03
#घोषणा APM_16_CONNECTED	0x05
#घोषणा APM_16_UNSUPPORTED	0x06
#घोषणा APM_32_CONNECTED	0x07
#घोषणा APM_32_UNSUPPORTED	0x08
#घोषणा APM_BAD_DEVICE		0x09
#घोषणा APM_BAD_PARAM		0x0a
#घोषणा APM_NOT_ENGAGED		0x0b
#घोषणा APM_BAD_FUNCTION	0x0c
#घोषणा APM_RESUME_DISABLED	0x0d
#घोषणा APM_NO_ERROR		0x53
#घोषणा APM_BAD_STATE		0x60
#घोषणा APM_NO_EVENTS		0x80
#घोषणा APM_NOT_PRESENT		0x86

/*
 * APM Device IDs
 */
#घोषणा APM_DEVICE_BIOS		0x0000
#घोषणा APM_DEVICE_ALL		0x0001
#घोषणा APM_DEVICE_DISPLAY	0x0100
#घोषणा APM_DEVICE_STORAGE	0x0200
#घोषणा APM_DEVICE_PARALLEL	0x0300
#घोषणा APM_DEVICE_SERIAL	0x0400
#घोषणा APM_DEVICE_NETWORK	0x0500
#घोषणा APM_DEVICE_PCMCIA	0x0600
#घोषणा APM_DEVICE_BATTERY	0x8000
#घोषणा APM_DEVICE_OEM		0xe000
#घोषणा APM_DEVICE_OLD_ALL	0xffff
#घोषणा APM_DEVICE_CLASS	0x00ff
#घोषणा APM_DEVICE_MASK		0xff00


/*
 * Battery status
 */
#घोषणा APM_MAX_BATTERIES	2

/*
 * APM defined capability bit flags
 */
#घोषणा APM_CAP_GLOBAL_STANDBY		0x0001
#घोषणा APM_CAP_GLOBAL_SUSPEND		0x0002
#घोषणा APM_CAP_RESUME_STANDBY_TIMER	0x0004 /* Timer resume from standby */
#घोषणा APM_CAP_RESUME_SUSPEND_TIMER	0x0008 /* Timer resume from suspend */
#घोषणा APM_CAP_RESUME_STANDBY_RING	0x0010 /* Resume on Ring fr standby */
#घोषणा APM_CAP_RESUME_SUSPEND_RING	0x0020 /* Resume on Ring fr suspend */
#घोषणा APM_CAP_RESUME_STANDBY_PCMCIA	0x0040 /* Resume on PCMCIA Ring	*/
#घोषणा APM_CAP_RESUME_SUSPEND_PCMCIA	0x0080 /* Resume on PCMCIA Ring	*/

/*
 * ioctl operations
 */
#समावेश <linux/ioctl.h>

#घोषणा APM_IOC_STANDBY		_IO('A', 1)
#घोषणा APM_IOC_SUSPEND		_IO('A', 2)

#पूर्ण_अगर /* _UAPI_LINUX_APM_H */
