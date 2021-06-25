<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (C) 2005-2007 Jiri Slaby <jirislaby@gmail.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 */

#अगर_अघोषित __PHANTOM_H
#घोषणा __PHANTOM_H

#समावेश <linux/types.h>

/* PHN_(G/S)ET_REG param */
काष्ठा phm_reg अणु
	__u32 reg;
	__u32 value;
पूर्ण;

/* PHN_(G/S)ET_REGS param */
काष्ठा phm_regs अणु
	__u32 count;
	__u32 mask;
	__u32 values[8];
पूर्ण;

#घोषणा PH_IOC_MAGIC		'p'
#घोषणा PHN_GET_REG		_IOWR(PH_IOC_MAGIC, 0, काष्ठा phm_reg *)
#घोषणा PHN_SET_REG		_IOW(PH_IOC_MAGIC, 1, काष्ठा phm_reg *)
#घोषणा PHN_GET_REGS		_IOWR(PH_IOC_MAGIC, 2, काष्ठा phm_regs *)
#घोषणा PHN_SET_REGS		_IOW(PH_IOC_MAGIC, 3, काष्ठा phm_regs *)
/* this ioctl tells the driver, that the caller is not OpenHaptics and might
 * use improved रेजिस्टरs update (no more phantom चयनoffs when using
 * libphantom) */
#घोषणा PHN_NOT_OH		_IO(PH_IOC_MAGIC, 4)
#घोषणा PHN_GETREG		_IOWR(PH_IOC_MAGIC, 5, काष्ठा phm_reg)
#घोषणा PHN_SETREG		_IOW(PH_IOC_MAGIC, 6, काष्ठा phm_reg)
#घोषणा PHN_GETREGS		_IOWR(PH_IOC_MAGIC, 7, काष्ठा phm_regs)
#घोषणा PHN_SETREGS		_IOW(PH_IOC_MAGIC, 8, काष्ठा phm_regs)

#घोषणा PHN_CONTROL		0x6     /* control byte in iaddr space */
#घोषणा PHN_CTL_AMP		0x1     /*   चयन after torques change */
#घोषणा PHN_CTL_BUT		0x2     /*   is button चयनed */
#घोषणा PHN_CTL_IRQ		0x10    /*   is irq enabled */

#घोषणा PHN_ZERO_FORCE		2048	/* zero torque on motor */

#पूर्ण_अगर
