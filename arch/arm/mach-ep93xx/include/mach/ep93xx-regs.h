<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-ep93xx/include/mach/ep93xx-regs.h
 */

#अगर_अघोषित __ASM_ARCH_EP93XX_REGS_H
#घोषणा __ASM_ARCH_EP93XX_REGS_H

/*
 * EP93xx linux memory map:
 *
 * virt		phys		size
 * fe800000			5M		per-platक्रमm mappings
 * fed00000	80800000	2M		APB
 * fef00000	80000000	1M		AHB
 */

#घोषणा EP93XX_AHB_PHYS_BASE		0x80000000
#घोषणा EP93XX_AHB_VIRT_BASE		0xfef00000
#घोषणा EP93XX_AHB_SIZE			0x00100000

#घोषणा EP93XX_AHB_PHYS(x)		(EP93XX_AHB_PHYS_BASE + (x))
#घोषणा EP93XX_AHB_IOMEM(x)		IOMEM(EP93XX_AHB_VIRT_BASE + (x))

#घोषणा EP93XX_APB_PHYS_BASE		0x80800000
#घोषणा EP93XX_APB_VIRT_BASE		0xfed00000
#घोषणा EP93XX_APB_SIZE			0x00200000

#घोषणा EP93XX_APB_PHYS(x)		(EP93XX_APB_PHYS_BASE + (x))
#घोषणा EP93XX_APB_IOMEM(x)		IOMEM(EP93XX_APB_VIRT_BASE + (x))

/* APB UARTs */
#घोषणा EP93XX_UART1_PHYS_BASE		EP93XX_APB_PHYS(0x000c0000)
#घोषणा EP93XX_UART1_BASE		EP93XX_APB_IOMEM(0x000c0000)

#घोषणा EP93XX_UART2_PHYS_BASE		EP93XX_APB_PHYS(0x000d0000)
#घोषणा EP93XX_UART2_BASE		EP93XX_APB_IOMEM(0x000d0000)

#घोषणा EP93XX_UART3_PHYS_BASE		EP93XX_APB_PHYS(0x000e0000)
#घोषणा EP93XX_UART3_BASE		EP93XX_APB_IOMEM(0x000e0000)

#पूर्ण_अगर
