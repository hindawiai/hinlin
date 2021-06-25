<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/zeus.h
 *
 *  Author:	David Vrabel
 *  Created:	Sept 28, 2005
 *  Copyright:	Arcom Control Systems Ltd.
 *
 *  Maपूर्णांकained by: Marc Zyngier <maz@misterjones.org>
 */

#अगर_अघोषित _MACH_ZEUS_H
#घोषणा _MACH_ZEUS_H

#घोषणा ZEUS_NR_IRQS		(IRQ_BOARD_START + 48)

/* Physical addresses */
#घोषणा ZEUS_FLASH_PHYS		PXA_CS0_PHYS
#घोषणा ZEUS_ETH0_PHYS		PXA_CS1_PHYS
#घोषणा ZEUS_ETH1_PHYS		PXA_CS2_PHYS
#घोषणा ZEUS_CPLD_PHYS		(PXA_CS4_PHYS+0x2000000)
#घोषणा ZEUS_SRAM_PHYS		PXA_CS5_PHYS
#घोषणा ZEUS_PC104IO_PHYS	(0x30000000)

#घोषणा ZEUS_CPLD_VERSION_PHYS	(ZEUS_CPLD_PHYS + 0x00000000)
#घोषणा ZEUS_CPLD_ISA_IRQ_PHYS	(ZEUS_CPLD_PHYS + 0x00800000)
#घोषणा ZEUS_CPLD_CONTROL_PHYS	(ZEUS_CPLD_PHYS + 0x01000000)
#घोषणा ZEUS_CPLD_EXTWDOG_PHYS	(ZEUS_CPLD_PHYS + 0x01800000)

/* GPIOs */
#घोषणा ZEUS_AC97_GPIO		0
#घोषणा ZEUS_WAKEUP_GPIO	1
#घोषणा ZEUS_UARTA_GPIO		9
#घोषणा ZEUS_UARTB_GPIO		10
#घोषणा ZEUS_UARTC_GPIO		12
#घोषणा ZEUS_UARTD_GPIO		11
#घोषणा ZEUS_ETH0_GPIO		14
#घोषणा ZEUS_ISA_GPIO		17
#घोषणा ZEUS_BKLEN_GPIO		19
#घोषणा ZEUS_USB2_PWREN_GPIO	22
#घोषणा ZEUS_PTT_GPIO		27
#घोषणा ZEUS_CF_CD_GPIO         35
#घोषणा ZEUS_MMC_WP_GPIO        52
#घोषणा ZEUS_MMC_CD_GPIO        53
#घोषणा ZEUS_EXTGPIO_GPIO	91
#घोषणा ZEUS_CF_PWEN_GPIO       97
#घोषणा ZEUS_CF_RDY_GPIO        99
#घोषणा ZEUS_LCD_EN_GPIO	101
#घोषणा ZEUS_ETH1_GPIO		113
#घोषणा ZEUS_CAN_GPIO		116

#घोषणा ZEUS_EXT0_GPIO_BASE	128
#घोषणा ZEUS_EXT1_GPIO_BASE	160
#घोषणा ZEUS_USER_GPIO_BASE	192

#घोषणा ZEUS_EXT0_GPIO(x)	(ZEUS_EXT0_GPIO_BASE + (x))
#घोषणा ZEUS_EXT1_GPIO(x)	(ZEUS_EXT1_GPIO_BASE + (x))
#घोषणा ZEUS_USER_GPIO(x)	(ZEUS_USER_GPIO_BASE + (x))

#घोषणा	ZEUS_CAN_SHDN_GPIO	ZEUS_EXT1_GPIO(2)

/*
 * CPLD रेजिस्टरs:
 * Only 4 रेजिस्टरs, but spपढ़ो over a 32MB address space.
 * Be gentle, and remap that over 32kB...
 */

#घोषणा ZEUS_CPLD		IOMEM(0xf0000000)
#घोषणा ZEUS_CPLD_VERSION	(ZEUS_CPLD + 0x0000)
#घोषणा ZEUS_CPLD_ISA_IRQ	(ZEUS_CPLD + 0x1000)
#घोषणा ZEUS_CPLD_CONTROL	(ZEUS_CPLD + 0x2000)

/* CPLD रेजिस्टर bits */
#घोषणा ZEUS_CPLD_CONTROL_CF_RST        0x01

#घोषणा ZEUS_PC104IO		IOMEM(0xf1000000)

#घोषणा ZEUS_SRAM_SIZE		(256 * 1024)

#पूर्ण_अगर


