<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  include/यंत्र-sh/magicpanelr2.h
 *
 *  Copyright (C) 2007  Markus Brunner, Mark Jonas
 *
 *  I/O addresses and biपंचांगasks क्रम Magic Panel Release 2 board
 */

#अगर_अघोषित __ASM_SH_MAGICPANELR2_H
#घोषणा __ASM_SH_MAGICPANELR2_H

#समावेश <linux/gpपन.स>

#घोषणा __IO_PREFIX mpr2
#समावेश <यंत्र/io_generic.h>


#घोषणा SETBITS_OUTB(mask, reg)   __raw_ग_लिखोb(__raw_पढ़ोb(reg) | mask, reg)
#घोषणा SETBITS_OUTW(mask, reg)   __raw_ग_लिखोw(__raw_पढ़ोw(reg) | mask, reg)
#घोषणा SETBITS_OUTL(mask, reg)   __raw_ग_लिखोl(__raw_पढ़ोl(reg) | mask, reg)
#घोषणा CLRBITS_OUTB(mask, reg)   __raw_ग_लिखोb(__raw_पढ़ोb(reg) & ~mask, reg)
#घोषणा CLRBITS_OUTW(mask, reg)   __raw_ग_लिखोw(__raw_पढ़ोw(reg) & ~mask, reg)
#घोषणा CLRBITS_OUTL(mask, reg)   __raw_ग_लिखोl(__raw_पढ़ोl(reg) & ~mask, reg)


#घोषणा PA_LED          PORT_PADR      /* LED */


/* BSC */
#घोषणा CMNCR           0xA4FD0000UL
#घोषणा CS0BCR          0xA4FD0004UL
#घोषणा CS2BCR          0xA4FD0008UL
#घोषणा CS3BCR          0xA4FD000CUL
#घोषणा CS4BCR          0xA4FD0010UL
#घोषणा CS5ABCR         0xA4FD0014UL
#घोषणा CS5BBCR         0xA4FD0018UL
#घोषणा CS6ABCR         0xA4FD001CUL
#घोषणा CS6BBCR         0xA4FD0020UL
#घोषणा CS0WCR          0xA4FD0024UL
#घोषणा CS2WCR          0xA4FD0028UL
#घोषणा CS3WCR          0xA4FD002CUL
#घोषणा CS4WCR          0xA4FD0030UL
#घोषणा CS5AWCR         0xA4FD0034UL
#घोषणा CS5BWCR         0xA4FD0038UL
#घोषणा CS6AWCR         0xA4FD003CUL
#घोषणा CS6BWCR         0xA4FD0040UL


/* usb */

#घोषणा PORT_UTRCTL		0xA405012CUL
#घोषणा PORT_UCLKCR_W		0xA40A0008UL

#घोषणा INTC_ICR0		0xA414FEE0UL
#घोषणा INTC_ICR1		0xA4140010UL
#घोषणा INTC_ICR2		0xA4140012UL

/* MTD */

#घोषणा MPR2_MTD_BOOTLOADER_SIZE	0x00060000UL
#घोषणा MPR2_MTD_KERNEL_SIZE		0x00200000UL

#पूर्ण_अगर  /* __ASM_SH_MAGICPANELR2_H */
