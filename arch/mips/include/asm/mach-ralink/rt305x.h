<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Parts of this file are based on Ralink's 2.6.21 BSP
 *
 * Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _RT305X_REGS_H_
#घोषणा _RT305X_REGS_H_

बाह्य क्रमागत ralink_soc_type ralink_soc;

अटल अंतरभूत पूर्णांक soc_is_rt3050(व्योम)
अणु
	वापस ralink_soc == RT305X_SOC_RT3050;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_rt3052(व्योम)
अणु
	वापस ralink_soc == RT305X_SOC_RT3052;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_rt305x(व्योम)
अणु
	वापस soc_is_rt3050() || soc_is_rt3052();
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_rt3350(व्योम)
अणु
	वापस ralink_soc == RT305X_SOC_RT3350;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_rt3352(व्योम)
अणु
	वापस ralink_soc == RT305X_SOC_RT3352;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_rt5350(व्योम)
अणु
	वापस ralink_soc == RT305X_SOC_RT5350;
पूर्ण

#घोषणा RT305X_SYSC_BASE		0x10000000

#घोषणा SYSC_REG_CHIP_NAME0		0x00
#घोषणा SYSC_REG_CHIP_NAME1		0x04
#घोषणा SYSC_REG_CHIP_ID		0x0c
#घोषणा SYSC_REG_SYSTEM_CONFIG		0x10

#घोषणा RT3052_CHIP_NAME0		0x30335452
#घोषणा RT3052_CHIP_NAME1		0x20203235

#घोषणा RT3350_CHIP_NAME0		0x33335452
#घोषणा RT3350_CHIP_NAME1		0x20203035

#घोषणा RT3352_CHIP_NAME0		0x33335452
#घोषणा RT3352_CHIP_NAME1		0x20203235

#घोषणा RT5350_CHIP_NAME0		0x33355452
#घोषणा RT5350_CHIP_NAME1		0x20203035

#घोषणा CHIP_ID_ID_MASK			0xff
#घोषणा CHIP_ID_ID_SHIFT		8
#घोषणा CHIP_ID_REV_MASK		0xff

#घोषणा RT305X_SYSCFG_CPUCLK_SHIFT		18
#घोषणा RT305X_SYSCFG_CPUCLK_MASK		0x1
#घोषणा RT305X_SYSCFG_CPUCLK_LOW		0x0
#घोषणा RT305X_SYSCFG_CPUCLK_HIGH		0x1

#घोषणा RT305X_SYSCFG_SRAM_CS0_MODE_SHIFT	2
#घोषणा RT305X_SYSCFG_CPUCLK_MASK		0x1
#घोषणा RT305X_SYSCFG_SRAM_CS0_MODE_WDT		0x1

#घोषणा RT3352_SYSCFG0_CPUCLK_SHIFT	8
#घोषणा RT3352_SYSCFG0_CPUCLK_MASK	0x1
#घोषणा RT3352_SYSCFG0_CPUCLK_LOW	0x0
#घोषणा RT3352_SYSCFG0_CPUCLK_HIGH	0x1

#घोषणा RT5350_SYSCFG0_CPUCLK_SHIFT	8
#घोषणा RT5350_SYSCFG0_CPUCLK_MASK	0x3
#घोषणा RT5350_SYSCFG0_CPUCLK_360	0x0
#घोषणा RT5350_SYSCFG0_CPUCLK_320	0x2
#घोषणा RT5350_SYSCFG0_CPUCLK_300	0x3

#घोषणा RT5350_SYSCFG0_DRAM_SIZE_SHIFT  12
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_MASK   7
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_2M     0
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_8M     1
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_16M    2
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_32M    3
#घोषणा RT5350_SYSCFG0_DRAM_SIZE_64M    4

/* multi function gpio pins */
#घोषणा RT305X_GPIO_I2C_SD		1
#घोषणा RT305X_GPIO_I2C_SCLK		2
#घोषणा RT305X_GPIO_SPI_EN		3
#घोषणा RT305X_GPIO_SPI_CLK		4
/* GPIO 7-14 is shared between UART0, PCM  and I2S पूर्णांकerfaces */
#घोषणा RT305X_GPIO_7			7
#घोषणा RT305X_GPIO_10			10
#घोषणा RT305X_GPIO_14			14
#घोषणा RT305X_GPIO_UART1_TXD		15
#घोषणा RT305X_GPIO_UART1_RXD		16
#घोषणा RT305X_GPIO_JTAG_TDO		17
#घोषणा RT305X_GPIO_JTAG_TDI		18
#घोषणा RT305X_GPIO_MDIO_MDC		22
#घोषणा RT305X_GPIO_MDIO_MDIO		23
#घोषणा RT305X_GPIO_SDRAM_MD16		24
#घोषणा RT305X_GPIO_SDRAM_MD31		39
#घोषणा RT305X_GPIO_GE0_TXD0		40
#घोषणा RT305X_GPIO_GE0_RXCLK		51

#घोषणा RT305X_GPIO_MODE_UART0_SHIFT	2
#घोषणा RT305X_GPIO_MODE_UART0_MASK	0x7
#घोषणा RT305X_GPIO_MODE_UART0(x)	((x) << RT305X_GPIO_MODE_UART0_SHIFT)
#घोषणा RT305X_GPIO_MODE_UARTF		0
#घोषणा RT305X_GPIO_MODE_PCM_UARTF	1
#घोषणा RT305X_GPIO_MODE_PCM_I2S	2
#घोषणा RT305X_GPIO_MODE_I2S_UARTF	3
#घोषणा RT305X_GPIO_MODE_PCM_GPIO	4
#घोषणा RT305X_GPIO_MODE_GPIO_UARTF	5
#घोषणा RT305X_GPIO_MODE_GPIO_I2S	6
#घोषणा RT305X_GPIO_MODE_GPIO		7

#घोषणा RT305X_GPIO_MODE_I2C		0
#घोषणा RT305X_GPIO_MODE_SPI		1
#घोषणा RT305X_GPIO_MODE_UART1		5
#घोषणा RT305X_GPIO_MODE_JTAG		6
#घोषणा RT305X_GPIO_MODE_MDIO		7
#घोषणा RT305X_GPIO_MODE_SDRAM		8
#घोषणा RT305X_GPIO_MODE_RGMII		9
#घोषणा RT5350_GPIO_MODE_PHY_LED	14
#घोषणा RT5350_GPIO_MODE_SPI_CS1	21
#घोषणा RT3352_GPIO_MODE_LNA		18
#घोषणा RT3352_GPIO_MODE_PA		20

#घोषणा RT3352_SYSC_REG_SYSCFG0		0x010
#घोषणा RT3352_SYSC_REG_SYSCFG1         0x014
#घोषणा RT3352_SYSC_REG_CLKCFG1         0x030
#घोषणा RT3352_SYSC_REG_RSTCTRL         0x034
#घोषणा RT3352_SYSC_REG_USB_PS          0x05c

#घोषणा RT3352_CLKCFG0_XTAL_SEL		BIT(20)
#घोषणा RT3352_CLKCFG1_UPHY0_CLK_EN	BIT(18)
#घोषणा RT3352_CLKCFG1_UPHY1_CLK_EN	BIT(20)
#घोषणा RT3352_RSTCTRL_UHST		BIT(22)
#घोषणा RT3352_RSTCTRL_UDEV		BIT(25)
#घोषणा RT3352_SYSCFG1_USB0_HOST_MODE	BIT(10)

#घोषणा RT305X_SDRAM_BASE		0x00000000
#घोषणा RT305X_MEM_SIZE_MIN		2
#घोषणा RT305X_MEM_SIZE_MAX		64
#घोषणा RT3352_MEM_SIZE_MIN		2
#घोषणा RT3352_MEM_SIZE_MAX		256

#पूर्ण_अगर
