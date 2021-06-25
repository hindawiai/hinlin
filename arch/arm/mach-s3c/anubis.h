<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2005 Simtec Electronics
 *	http://www.simtec.co.uk/products/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * ANUBIS - CPLD control स्थिरants
 * ANUBIS - IRQ Number definitions
 * ANUBIS - Memory map definitions
 */

#अगर_अघोषित __MACH_S3C24XX_ANUBIS_H
#घोषणा __MACH_S3C24XX_ANUBIS_H __खाता__

/* CTRL2 - न_अंकD WP control, IDE Reset निश्चित/check */

#घोषणा ANUBIS_CTRL1_न_अंकDSEL		(0x3)

/* IDREG - revision */

#घोषणा ANUBIS_IDREG_REVMASK		(0x7)

/* irq */

#घोषणा ANUBIS_IRQ_IDE0			IRQ_EINT2
#घोषणा ANUBIS_IRQ_IDE1			IRQ_EINT3
#घोषणा ANUBIS_IRQ_ASIX			IRQ_EINT1

/* map */

/* start peripherals off after the S3C2410 */

#घोषणा ANUBIS_IOADDR(x)		(S3C2410_ADDR((x) + 0x01800000))

#घोषणा ANUBIS_PA_CPLD			(S3C2410_CS1 | (1<<26))

/* we put the CPLD रेजिस्टरs next, to get them out of the way */

#घोषणा ANUBIS_VA_CTRL1			ANUBIS_IOADDR(0x00000000)
#घोषणा ANUBIS_PA_CTRL1			ANUBIS_PA_CPLD

#घोषणा ANUBIS_VA_IDREG			ANUBIS_IOADDR(0x00300000)
#घोषणा ANUBIS_PA_IDREG			(ANUBIS_PA_CPLD + (3 << 23))

#घोषणा ANUBIS_IDEPRI			ANUBIS_IOADDR(0x01000000)
#घोषणा ANUBIS_IDEPRIAUX		ANUBIS_IOADDR(0x01100000)
#घोषणा ANUBIS_IDESEC			ANUBIS_IOADDR(0x01200000)
#घोषणा ANUBIS_IDESECAUX		ANUBIS_IOADDR(0x01300000)

#पूर्ण_अगर /* __MACH_S3C24XX_ANUBIS_H */
