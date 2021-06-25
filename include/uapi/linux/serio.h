<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 1999-2002 Vojtech Pavlik
*
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_SERIO_H
#घोषणा _UAPI_SERIO_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/ioctl.h>

#घोषणा SPIOCSTYPE	_IOW('q', 0x01, अचिन्हित दीर्घ)


/*
 * bit masks क्रम use in "interrupt" flags (3rd argument)
 */
#घोषणा SERIO_TIMEOUT	_BITUL(0)
#घोषणा SERIO_PARITY	_BITUL(1)
#घोषणा SERIO_FRAME	_BITUL(2)
#घोषणा SERIO_OOB_DATA	_BITUL(3)

/*
 * Serio types
 */
#घोषणा SERIO_XT	0x00
#घोषणा SERIO_8042	0x01
#घोषणा SERIO_RS232	0x02
#घोषणा SERIO_HIL_MLC	0x03
#घोषणा SERIO_PS_PSTHRU	0x05
#घोषणा SERIO_8042_XL	0x06

/*
 * Serio protocols
 */
#घोषणा SERIO_UNKNOWN	0x00
#घोषणा SERIO_MSC	0x01
#घोषणा SERIO_SUN	0x02
#घोषणा SERIO_MS	0x03
#घोषणा SERIO_MP	0x04
#घोषणा SERIO_MZ	0x05
#घोषणा SERIO_MZP	0x06
#घोषणा SERIO_MZPP	0x07
#घोषणा SERIO_VSXXXAA	0x08
#घोषणा SERIO_SUNKBD	0x10
#घोषणा SERIO_WARRIOR	0x18
#घोषणा SERIO_SPACEORB	0x19
#घोषणा SERIO_MAGELLAN	0x1a
#घोषणा SERIO_SPACEBALL	0x1b
#घोषणा SERIO_GUNZE	0x1c
#घोषणा SERIO_IFORCE	0x1d
#घोषणा SERIO_STINGER	0x1e
#घोषणा SERIO_NEWTON	0x1f
#घोषणा SERIO_STOWAWAY	0x20
#घोषणा SERIO_H3600	0x21
#घोषणा SERIO_PS2SER	0x22
#घोषणा SERIO_TWIDKBD	0x23
#घोषणा SERIO_TWIDJOY	0x24
#घोषणा SERIO_HIL	0x25
#घोषणा SERIO_SNES232	0x26
#घोषणा SERIO_SEMTECH	0x27
#घोषणा SERIO_LKKBD	0x28
#घोषणा SERIO_ELO	0x29
#घोषणा SERIO_MICROTOUCH	0x30
#घोषणा SERIO_PENMOUNT	0x31
#घोषणा SERIO_TOUCHRIGHT	0x32
#घोषणा SERIO_TOUCHWIN	0x33
#घोषणा SERIO_TAOSEVM	0x34
#घोषणा SERIO_FUJITSU	0x35
#घोषणा SERIO_ZHENHUA	0x36
#घोषणा SERIO_INEXIO	0x37
#घोषणा SERIO_TOUCHIT213	0x38
#घोषणा SERIO_W8001	0x39
#घोषणा SERIO_DYNAPRO	0x3a
#घोषणा SERIO_HAMPSHIRE	0x3b
#घोषणा SERIO_PS2MULT	0x3c
#घोषणा SERIO_TSC40	0x3d
#घोषणा SERIO_WACOM_IV	0x3e
#घोषणा SERIO_EGALAX	0x3f
#घोषणा SERIO_PULSE8_CEC	0x40
#घोषणा SERIO_RAINSHADOW_CEC	0x41
#घोषणा SERIO_FSIA6B	0x42

#पूर्ण_अगर /* _UAPI_SERIO_H */
