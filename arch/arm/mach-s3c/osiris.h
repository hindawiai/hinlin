<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2005 Simtec Electronics
 *	http://www.simtec.co.uk/products/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * OSIRIS - CPLD control स्थिरants
 * OSIRIS - Memory map definitions
 */

#अगर_अघोषित __MACH_S3C24XX_OSIRIS_H
#घोषणा __MACH_S3C24XX_OSIRIS_H __खाता__

/* CTRL0 - न_अंकD WP control */

#घोषणा OSIRIS_CTRL0_न_अंकDSEL		(0x3)
#घोषणा OSIRIS_CTRL0_BOOT_INT		(1<<3)
#घोषणा OSIRIS_CTRL0_PCMCIA		(1<<4)
#घोषणा OSIRIS_CTRL0_FIX8		(1<<5)
#घोषणा OSIRIS_CTRL0_PCMCIA_nWAIT	(1<<6)
#घोषणा OSIRIS_CTRL0_PCMCIA_nIOIS16	(1<<7)

#घोषणा OSIRIS_CTRL1_FIX8		(1<<0)

#घोषणा OSIRIS_ID_REVMASK		(0x7)

/* start peripherals off after the S3C2410 */

#घोषणा OSIRIS_IOADDR(x)	(S3C2410_ADDR((x) + 0x04000000))

#घोषणा OSIRIS_PA_CPLD		(S3C2410_CS1 | (1<<26))

/* we put the CPLD रेजिस्टरs next, to get them out of the way */

#घोषणा OSIRIS_VA_CTRL0		OSIRIS_IOADDR(0x00000000)
#घोषणा OSIRIS_PA_CTRL0		(OSIRIS_PA_CPLD)

#घोषणा OSIRIS_VA_CTRL1		OSIRIS_IOADDR(0x00100000)
#घोषणा OSIRIS_PA_CTRL1		(OSIRIS_PA_CPLD + (1<<23))

#घोषणा OSIRIS_VA_CTRL2		OSIRIS_IOADDR(0x00200000)
#घोषणा OSIRIS_PA_CTRL2		(OSIRIS_PA_CPLD + (2<<23))

#घोषणा OSIRIS_VA_CTRL3		OSIRIS_IOADDR(0x00300000)
#घोषणा OSIRIS_PA_CTRL3		(OSIRIS_PA_CPLD + (2<<23))

#घोषणा OSIRIS_VA_IDREG		OSIRIS_IOADDR(0x00700000)
#घोषणा OSIRIS_PA_IDREG		(OSIRIS_PA_CPLD + (7<<23))

#पूर्ण_अगर /* __MACH_S3C24XX_OSIRIS_H */
