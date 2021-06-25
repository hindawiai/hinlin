<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2004 Simtec Electronics <linux@simtec.co.uk>
 *		http://www.simtec.co.uk/products/SWLINUX/
 *
 * S3C2410 Memory Control रेजिस्टर definitions
 */

#अगर_अघोषित __ARCH_ARM_MACH_S3C24XX_REGS_MEM_H
#घोषणा __ARCH_ARM_MACH_S3C24XX_REGS_MEM_H __खाता__

#समावेश "map-s3c.h"

#घोषणा S3C2410_MEMREG(x)		(S3C24XX_VA_MEMCTRL + (x))

#घोषणा S3C2410_BWSCON			S3C2410_MEMREG(0x00)
#घोषणा S3C2410_BANKCON0		S3C2410_MEMREG(0x04)
#घोषणा S3C2410_BANKCON1		S3C2410_MEMREG(0x08)
#घोषणा S3C2410_BANKCON2		S3C2410_MEMREG(0x0C)
#घोषणा S3C2410_BANKCON3		S3C2410_MEMREG(0x10)
#घोषणा S3C2410_BANKCON4		S3C2410_MEMREG(0x14)
#घोषणा S3C2410_BANKCON5		S3C2410_MEMREG(0x18)
#घोषणा S3C2410_BANKCON6		S3C2410_MEMREG(0x1C)
#घोषणा S3C2410_BANKCON7		S3C2410_MEMREG(0x20)
#घोषणा S3C2410_REFRESH			S3C2410_MEMREG(0x24)
#घोषणा S3C2410_BANKSIZE		S3C2410_MEMREG(0x28)

#घोषणा S3C2410_BWSCON_ST1		(1 << 7)
#घोषणा S3C2410_BWSCON_ST2		(1 << 11)
#घोषणा S3C2410_BWSCON_ST3		(1 << 15)
#घोषणा S3C2410_BWSCON_ST4		(1 << 19)
#घोषणा S3C2410_BWSCON_ST5		(1 << 23)

#घोषणा S3C2410_BWSCON_GET(_bwscon, _bank) (((_bwscon) >> ((_bank) * 4)) & 0xf)

#घोषणा S3C2410_BWSCON_WS		(1 << 2)

#घोषणा S3C2410_BANKCON_PMC16		(0x3)

#घोषणा S3C2410_BANKCON_Tacp_SHIFT	(2)
#घोषणा S3C2410_BANKCON_Tcah_SHIFT	(4)
#घोषणा S3C2410_BANKCON_Tcoh_SHIFT	(6)
#घोषणा S3C2410_BANKCON_Tacc_SHIFT	(8)
#घोषणा S3C2410_BANKCON_Tcos_SHIFT	(11)
#घोषणा S3C2410_BANKCON_Tacs_SHIFT	(13)

#घोषणा S3C2410_BANKCON_SDRAM		(0x3 << 15)

#घोषणा S3C2410_REFRESH_SELF		(1 << 22)

#घोषणा S3C2410_BANKSIZE_MASK		(0x7 << 0)

#पूर्ण_अगर /* __ARCH_ARM_MACH_S3C24XX_REGS_MEM_H */
