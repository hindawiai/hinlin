<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Loongson 1 MUX Register Definitions.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_REGS_MUX_H
#घोषणा __ASM_MACH_LOONGSON32_REGS_MUX_H

#घोषणा LS1X_MUX_REG(x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_MUX_BASE + (x)))

#घोषणा LS1X_MUX_CTRL0			LS1X_MUX_REG(0x0)
#घोषणा LS1X_MUX_CTRL1			LS1X_MUX_REG(0x4)

#अगर defined(CONFIG_LOONGSON1_LS1B)
/* MUX CTRL0 Register Bits */
#घोषणा UART0_USE_PWM23			BIT(28)
#घोषणा UART0_USE_PWM01			BIT(27)
#घोषणा UART1_USE_LCD0_5_6_11		BIT(26)
#घोषणा I2C2_USE_CAN1			BIT(25)
#घोषणा I2C1_USE_CAN0			BIT(24)
#घोषणा न_अंकD3_USE_UART5			BIT(23)
#घोषणा न_अंकD3_USE_UART4			BIT(22)
#घोषणा न_अंकD3_USE_UART1_DAT		BIT(21)
#घोषणा न_अंकD3_USE_UART1_CTS		BIT(20)
#घोषणा न_अंकD3_USE_PWM23			BIT(19)
#घोषणा न_अंकD3_USE_PWM01			BIT(18)
#घोषणा न_अंकD2_USE_UART5			BIT(17)
#घोषणा न_अंकD2_USE_UART4			BIT(16)
#घोषणा न_अंकD2_USE_UART1_DAT		BIT(15)
#घोषणा न_अंकD2_USE_UART1_CTS		BIT(14)
#घोषणा न_अंकD2_USE_PWM23			BIT(13)
#घोषणा न_अंकD2_USE_PWM01			BIT(12)
#घोषणा न_अंकD1_USE_UART5			BIT(11)
#घोषणा न_अंकD1_USE_UART4			BIT(10)
#घोषणा न_अंकD1_USE_UART1_DAT		BIT(9)
#घोषणा न_अंकD1_USE_UART1_CTS		BIT(8)
#घोषणा न_अंकD1_USE_PWM23			BIT(7)
#घोषणा न_अंकD1_USE_PWM01			BIT(6)
#घोषणा GMAC1_USE_UART1			BIT(4)
#घोषणा GMAC1_USE_UART0			BIT(3)
#घोषणा LCD_USE_UART0_DAT		BIT(2)
#घोषणा LCD_USE_UART15			BIT(1)
#घोषणा LCD_USE_UART0			BIT(0)

/* MUX CTRL1 Register Bits */
#घोषणा USB_RESET			BIT(31)
#घोषणा SPI1_CS_USE_PWM01		BIT(24)
#घोषणा SPI1_USE_CAN			BIT(23)
#घोषणा DISABLE_DDR_CONFSPACE		BIT(20)
#घोषणा DDR32TO16EN			BIT(16)
#घोषणा GMAC1_SHUT			BIT(13)
#घोषणा GMAC0_SHUT			BIT(12)
#घोषणा USB_SHUT			BIT(11)
#घोषणा UART1_3_USE_CAN1		BIT(5)
#घोषणा UART1_2_USE_CAN0		BIT(4)
#घोषणा GMAC1_USE_TXCLK			BIT(3)
#घोषणा GMAC0_USE_TXCLK			BIT(2)
#घोषणा GMAC1_USE_PWM23			BIT(1)
#घोषणा GMAC0_USE_PWM01			BIT(0)

#या_अगर defined(CONFIG_LOONGSON1_LS1C)

/* SHUT_CTRL Register Bits */
#घोषणा UART_SPLIT			GENMASK(31, 30)
#घोषणा OUTPUT_CLK			GENMASK(29, 26)
#घोषणा ADC_SHUT			BIT(25)
#घोषणा SDIO_SHUT			BIT(24)
#घोषणा DMA2_SHUT			BIT(23)
#घोषणा DMA1_SHUT			BIT(22)
#घोषणा DMA0_SHUT			BIT(21)
#घोषणा SPI1_SHUT			BIT(20)
#घोषणा SPI0_SHUT			BIT(19)
#घोषणा I2C2_SHUT			BIT(18)
#घोषणा I2C1_SHUT			BIT(17)
#घोषणा I2C0_SHUT			BIT(16)
#घोषणा AC97_SHUT			BIT(15)
#घोषणा I2S_SHUT			BIT(14)
#घोषणा UART3_SHUT			BIT(13)
#घोषणा UART2_SHUT			BIT(12)
#घोषणा UART1_SHUT			BIT(11)
#घोषणा UART0_SHUT			BIT(10)
#घोषणा CAN1_SHUT			BIT(9)
#घोषणा CAN0_SHUT			BIT(8)
#घोषणा ECC_SHUT			BIT(7)
#घोषणा GMAC_SHUT			BIT(6)
#घोषणा USBHOST_SHUT			BIT(5)
#घोषणा USBOTG_SHUT			BIT(4)
#घोषणा SDRAM_SHUT			BIT(3)
#घोषणा SRAM_SHUT			BIT(2)
#घोषणा CAM_SHUT			BIT(1)
#घोषणा LCD_SHUT			BIT(0)

#घोषणा UART_SPLIT_SHIFT                        30
#घोषणा OUTPUT_CLK_SHIFT                        26

/* MISC_CTRL Register Bits */
#घोषणा USBHOST_RSTN			BIT(31)
#घोषणा PHY_INTF_SELI			GENMASK(30, 28)
#घोषणा AC97_EN				BIT(25)
#घोषणा SDIO_DMA_EN			GENMASK(24, 23)
#घोषणा ADC_DMA_EN			BIT(22)
#घोषणा SDIO_USE_SPI1			BIT(17)
#घोषणा SDIO_USE_SPI0			BIT(16)
#घोषणा SRAM_CTRL			GENMASK(15, 0)

#घोषणा PHY_INTF_SELI_SHIFT                     28
#घोषणा SDIO_DMA_EN_SHIFT                       23
#घोषणा SRAM_CTRL_SHIFT				0

#घोषणा LS1X_CBUS_REG(n, x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_CBUS_BASE + (n * 0x04) + (x)))

#घोषणा LS1X_CBUS_FIRST(n)		LS1X_CBUS_REG(n, 0x00)
#घोषणा LS1X_CBUS_SECOND(n)		LS1X_CBUS_REG(n, 0x10)
#घोषणा LS1X_CBUS_THIRD(n)		LS1X_CBUS_REG(n, 0x20)
#घोषणा LS1X_CBUS_FOURTHT(n)		LS1X_CBUS_REG(n, 0x30)
#घोषणा LS1X_CBUS_FIFTHT(n)		LS1X_CBUS_REG(n, 0x40)

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_REGS_MUX_H */
