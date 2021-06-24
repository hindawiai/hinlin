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

#अगर_अघोषित _RT288X_REGS_H_
#घोषणा _RT288X_REGS_H_

#घोषणा RT2880_SYSC_BASE		0x00300000

#घोषणा SYSC_REG_CHIP_NAME0		0x00
#घोषणा SYSC_REG_CHIP_NAME1		0x04
#घोषणा SYSC_REG_CHIP_ID		0x0c
#घोषणा SYSC_REG_SYSTEM_CONFIG		0x10
#घोषणा SYSC_REG_CLKCFG			0x30

#घोषणा RT2880_CHIP_NAME0		0x38325452
#घोषणा RT2880_CHIP_NAME1		0x20203038

#घोषणा CHIP_ID_ID_MASK			0xff
#घोषणा CHIP_ID_ID_SHIFT		8
#घोषणा CHIP_ID_REV_MASK		0xff

#घोषणा SYSTEM_CONFIG_CPUCLK_SHIFT	20
#घोषणा SYSTEM_CONFIG_CPUCLK_MASK	0x3
#घोषणा SYSTEM_CONFIG_CPUCLK_250	0x0
#घोषणा SYSTEM_CONFIG_CPUCLK_266	0x1
#घोषणा SYSTEM_CONFIG_CPUCLK_280	0x2
#घोषणा SYSTEM_CONFIG_CPUCLK_300	0x3

#घोषणा RT2880_GPIO_MODE_I2C		BIT(0)
#घोषणा RT2880_GPIO_MODE_UART0		BIT(1)
#घोषणा RT2880_GPIO_MODE_SPI		BIT(2)
#घोषणा RT2880_GPIO_MODE_UART1		BIT(3)
#घोषणा RT2880_GPIO_MODE_JTAG		BIT(4)
#घोषणा RT2880_GPIO_MODE_MDIO		BIT(5)
#घोषणा RT2880_GPIO_MODE_SDRAM		BIT(6)
#घोषणा RT2880_GPIO_MODE_PCI		BIT(7)

#घोषणा CLKCFG_SRAM_CS_N_WDT		BIT(9)

#घोषणा RT2880_SDRAM_BASE		0x08000000
#घोषणा RT2880_MEM_SIZE_MIN		2
#घोषणा RT2880_MEM_SIZE_MAX		128

#पूर्ण_अगर
