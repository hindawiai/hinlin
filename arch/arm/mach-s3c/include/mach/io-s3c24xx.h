<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-s3c2410/include/mach/पन.स
 *  from arch/arm/mach-rpc/include/mach/पन.स
 *
 * Copyright (C) 1997 Russell King
 *	     (C) 2003 Simtec Electronics
*/

#अगर_अघोषित __ASM_ARM_ARCH_IO_S3C24XX_H
#घोषणा __ASM_ARM_ARCH_IO_S3C24XX_H

#समावेश <mach/map-base.h>

/*
 * ISA style IO, क्रम each machine to sort out mappings क्रम,
 * अगर it implements it. We reserve two 16M regions क्रम ISA,
 * so the PC/104 can use separate addresses क्रम 8-bit and
 * 16-bit port I/O.
 */
#घोषणा PCIO_BASE		S3C_ADDR(0x02000000)
#घोषणा IO_SPACE_LIMIT		0x00ffffff
#घोषणा S3C24XX_VA_ISA_WORD	(PCIO_BASE)
#घोषणा S3C24XX_VA_ISA_BYTE	(PCIO_BASE + 0x01000000)

#अगर_घोषित CONFIG_ISA

#घोषणा inb(p)		पढ़ोb(S3C24XX_VA_ISA_BYTE + (p))
#घोषणा inw(p)		पढ़ोw(S3C24XX_VA_ISA_WORD + (p))
#घोषणा inl(p)		पढ़ोl(S3C24XX_VA_ISA_WORD + (p))

#घोषणा outb(v,p)	ग_लिखोb((v), S3C24XX_VA_ISA_BYTE + (p))
#घोषणा outw(v,p)	ग_लिखोw((v), S3C24XX_VA_ISA_WORD + (p))
#घोषणा outl(v,p)	ग_लिखोl((v), S3C24XX_VA_ISA_WORD + (p))

#घोषणा insb(p,d,l)	पढ़ोsb(S3C24XX_VA_ISA_BYTE + (p),d,l)
#घोषणा insw(p,d,l)	पढ़ोsw(S3C24XX_VA_ISA_WORD + (p),d,l)
#घोषणा insl(p,d,l)	पढ़ोsl(S3C24XX_VA_ISA_WORD + (p),d,l)

#घोषणा outsb(p,d,l)	ग_लिखोsb(S3C24XX_VA_ISA_BYTE + (p),d,l)
#घोषणा outsw(p,d,l)	ग_लिखोsw(S3C24XX_VA_ISA_WORD + (p),d,l)
#घोषणा outsl(p,d,l)	ग_लिखोsl(S3C24XX_VA_ISA_WORD + (p),d,l)

#अन्यथा

#घोषणा __io(x) (PCIO_BASE + (x))

#पूर्ण_अगर

#पूर्ण_अगर
