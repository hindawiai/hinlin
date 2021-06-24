<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * IRQ mappings क्रम Loongson 1
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_IRQ_H
#घोषणा __ASM_MACH_LOONGSON32_IRQ_H

/*
 * CPU core Interrupt Numbers
 */
#घोषणा MIPS_CPU_IRQ_BASE		0
#घोषणा MIPS_CPU_IRQ(x)			(MIPS_CPU_IRQ_BASE + (x))

#घोषणा SOFTINT0_IRQ			MIPS_CPU_IRQ(0)
#घोषणा SOFTINT1_IRQ			MIPS_CPU_IRQ(1)
#घोषणा INT0_IRQ			MIPS_CPU_IRQ(2)
#घोषणा INT1_IRQ			MIPS_CPU_IRQ(3)
#घोषणा INT2_IRQ			MIPS_CPU_IRQ(4)
#घोषणा INT3_IRQ			MIPS_CPU_IRQ(5)
#घोषणा INT4_IRQ			MIPS_CPU_IRQ(6)
#घोषणा TIMER_IRQ			MIPS_CPU_IRQ(7)		/* cpu समयr */

#घोषणा MIPS_CPU_IRQS		(MIPS_CPU_IRQ(7) + 1 - MIPS_CPU_IRQ_BASE)

/*
 * INT0~3 Interrupt Numbers
 */
#घोषणा LS1X_IRQ_BASE			MIPS_CPU_IRQS
#घोषणा LS1X_IRQ(n, x)			(LS1X_IRQ_BASE + (n << 5) + (x))

#घोषणा LS1X_UART0_IRQ			LS1X_IRQ(0, 2)
#अगर defined(CONFIG_LOONGSON1_LS1B)
#घोषणा LS1X_UART1_IRQ			LS1X_IRQ(0, 3)
#घोषणा LS1X_UART2_IRQ			LS1X_IRQ(0, 4)
#घोषणा LS1X_UART3_IRQ			LS1X_IRQ(0, 5)
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा LS1X_UART1_IRQ			LS1X_IRQ(0, 4)
#घोषणा LS1X_UART2_IRQ			LS1X_IRQ(0, 5)
#पूर्ण_अगर
#घोषणा LS1X_CAN0_IRQ			LS1X_IRQ(0, 6)
#घोषणा LS1X_CAN1_IRQ			LS1X_IRQ(0, 7)
#घोषणा LS1X_SPI0_IRQ			LS1X_IRQ(0, 8)
#घोषणा LS1X_SPI1_IRQ			LS1X_IRQ(0, 9)
#घोषणा LS1X_AC97_IRQ			LS1X_IRQ(0, 10)
#घोषणा LS1X_DMA0_IRQ			LS1X_IRQ(0, 13)
#घोषणा LS1X_DMA1_IRQ			LS1X_IRQ(0, 14)
#घोषणा LS1X_DMA2_IRQ			LS1X_IRQ(0, 15)
#अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा LS1X_न_अंकD_IRQ			LS1X_IRQ(0, 16)
#पूर्ण_अगर
#घोषणा LS1X_PWM0_IRQ			LS1X_IRQ(0, 17)
#घोषणा LS1X_PWM1_IRQ			LS1X_IRQ(0, 18)
#घोषणा LS1X_PWM2_IRQ			LS1X_IRQ(0, 19)
#घोषणा LS1X_PWM3_IRQ			LS1X_IRQ(0, 20)
#घोषणा LS1X_RTC_INT0_IRQ		LS1X_IRQ(0, 21)
#घोषणा LS1X_RTC_INT1_IRQ		LS1X_IRQ(0, 22)
#घोषणा LS1X_RTC_INT2_IRQ		LS1X_IRQ(0, 23)
#अगर defined(CONFIG_LOONGSON1_LS1B)
#घोषणा LS1X_TOY_INT0_IRQ		LS1X_IRQ(0, 24)
#घोषणा LS1X_TOY_INT1_IRQ		LS1X_IRQ(0, 25)
#घोषणा LS1X_TOY_INT2_IRQ		LS1X_IRQ(0, 26)
#घोषणा LS1X_RTC_TICK_IRQ		LS1X_IRQ(0, 27)
#घोषणा LS1X_TOY_TICK_IRQ		LS1X_IRQ(0, 28)
#घोषणा LS1X_UART4_IRQ			LS1X_IRQ(0, 29)
#घोषणा LS1X_UART5_IRQ			LS1X_IRQ(0, 30)
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा LS1X_UART3_IRQ			LS1X_IRQ(0, 29)
#घोषणा LS1X_ADC_IRQ			LS1X_IRQ(0, 30)
#घोषणा LS1X_SDIO_IRQ			LS1X_IRQ(0, 31)
#पूर्ण_अगर

#घोषणा LS1X_EHCI_IRQ			LS1X_IRQ(1, 0)
#घोषणा LS1X_OHCI_IRQ			LS1X_IRQ(1, 1)
#अगर defined(CONFIG_LOONGSON1_LS1B)
#घोषणा LS1X_GMAC0_IRQ			LS1X_IRQ(1, 2)
#घोषणा LS1X_GMAC1_IRQ			LS1X_IRQ(1, 3)
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा LS1X_OTG_IRQ			LS1X_IRQ(1, 2)
#घोषणा LS1X_GMAC0_IRQ			LS1X_IRQ(1, 3)
#घोषणा LS1X_CAM_IRQ			LS1X_IRQ(1, 4)
#घोषणा LS1X_UART4_IRQ			LS1X_IRQ(1, 5)
#घोषणा LS1X_UART5_IRQ			LS1X_IRQ(1, 6)
#घोषणा LS1X_UART6_IRQ			LS1X_IRQ(1, 7)
#घोषणा LS1X_UART7_IRQ			LS1X_IRQ(1, 8)
#घोषणा LS1X_UART8_IRQ			LS1X_IRQ(1, 9)
#घोषणा LS1X_UART9_IRQ			LS1X_IRQ(1, 13)
#घोषणा LS1X_UART10_IRQ			LS1X_IRQ(1, 14)
#घोषणा LS1X_UART11_IRQ			LS1X_IRQ(1, 15)
#घोषणा LS1X_I2C0_IRQ			LS1X_IRQ(1, 17)
#घोषणा LS1X_I2C1_IRQ			LS1X_IRQ(1, 18)
#घोषणा LS1X_I2C2_IRQ			LS1X_IRQ(1, 19)
#पूर्ण_अगर

#अगर defined(CONFIG_LOONGSON1_LS1B)
#घोषणा INTN	4
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा INTN	5
#पूर्ण_अगर

#घोषणा LS1X_IRQS		(LS1X_IRQ(INTN, 31) + 1 - LS1X_IRQ_BASE)

#घोषणा NR_IRQS			(MIPS_CPU_IRQS + LS1X_IRQS)

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_IRQ_H */
