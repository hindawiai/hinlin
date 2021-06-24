<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C64XX प्रणाली रेजिस्टर definitions
*/

#अगर_अघोषित __MACH_S3C64XX_REGS_SYS_H
#घोषणा __MACH_S3C64XX_REGS_SYS_H __खाता__

#घोषणा S3C_SYSREG(x)			(S3C_VA_SYS + (x))

#घोषणा S3C64XX_AHB_CON0		S3C_SYSREG(0x100)
#घोषणा S3C64XX_AHB_CON1		S3C_SYSREG(0x104)
#घोषणा S3C64XX_AHB_CON2		S3C_SYSREG(0x108)

#घोषणा S3C64XX_SDMA_SEL		S3C_SYSREG(0x110)

#घोषणा S3C64XX_OTHERS			S3C_SYSREG(0x900)

#घोषणा S3C64XX_OTHERS_USBMASK		(1 << 16)
#घोषणा S3C64XX_OTHERS_SYNCMUXSEL	(1 << 6)

#पूर्ण_अगर /* __MACH_S3C64XX_REGS_SYS_H */
