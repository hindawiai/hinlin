<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 */

#अगर_अघोषित __ARCH_ARM_MACH_S3C24XX_S3C2412_H
#घोषणा __ARCH_ARM_MACH_S3C24XX_S3C2412_H __खाता__

#समावेश "map-s3c.h"

#घोषणा S3C2412_MEMREG(x)		(S3C24XX_VA_MEMCTRL + (x))
#घोषणा S3C2412_EBIREG(x)		(S3C2412_VA_EBI + (x))

#घोषणा S3C2412_SSMCREG(x)		(S3C2412_VA_SSMC + (x))
#घोषणा S3C2412_SSMC(x, o)		(S3C2412_SSMCREG((x * 0x20) + (o)))

#घोषणा S3C2412_REFRESH			S3C2412_MEMREG(0x10)

#घोषणा S3C2412_EBI_BANKCFG		S3C2412_EBIREG(0x4)

#घोषणा S3C2412_SSMC_BANK(x)		S3C2412_SSMC(x, 0x0)

#पूर्ण_अगर /* __ARCH_ARM_MACH_S3C24XX_S3C2412_H */
