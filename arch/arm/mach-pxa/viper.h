<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-pxa/include/mach/viper.h
 *
 * Author:	Ian Campbell
 * Created:	Feb 03, 2003
 * Copyright:	Arcom Control Systems.
 *
 * Maपूर्णांकained by Marc Zyngier <maz@misterjones.org>
 *			      <marc.zyngier@altran.com>
 *
 * Created based on lubbock.h:
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */

#अगर_अघोषित ARCH_VIPER_H
#घोषणा ARCH_VIPER_H

#घोषणा VIPER_BOOT_PHYS		PXA_CS0_PHYS
#घोषणा VIPER_FLASH_PHYS	PXA_CS1_PHYS
#घोषणा VIPER_ETH_PHYS		PXA_CS2_PHYS
#घोषणा VIPER_USB_PHYS		PXA_CS3_PHYS
#घोषणा VIPER_ETH_DATA_PHYS	PXA_CS4_PHYS
#घोषणा VIPER_CPLD_PHYS		PXA_CS5_PHYS

#घोषणा VIPER_CPLD_BASE		(0xf0000000)
#घोषणा VIPER_PC104IO_BASE	(0xf1000000)
#घोषणा VIPER_USB_BASE		(0xf1800000)

#घोषणा VIPER_ETH_GPIO		(0)
#घोषणा VIPER_CPLD_GPIO		(1)
#घोषणा VIPER_USB_GPIO		(2)
#घोषणा VIPER_UARTA_GPIO	(4)
#घोषणा VIPER_UARTB_GPIO	(3)
#घोषणा VIPER_CF_CD_GPIO	(32)
#घोषणा VIPER_CF_RDY_GPIO	(8)
#घोषणा VIPER_BCKLIGHT_EN_GPIO	(9)
#घोषणा VIPER_LCD_EN_GPIO	(10)
#घोषणा VIPER_PSU_DATA_GPIO	(6)
#घोषणा VIPER_PSU_CLK_GPIO	(11)
#घोषणा VIPER_UART_SHDN_GPIO	(12)
#घोषणा VIPER_BRIGHTNESS_GPIO	(16)
#घोषणा VIPER_PSU_nCS_LD_GPIO	(19)
#घोषणा VIPER_UPS_GPIO		(20)
#घोषणा VIPER_CF_POWER_GPIO	(82)
#घोषणा VIPER_TPM_I2C_SDA_GPIO	(26)
#घोषणा VIPER_TPM_I2C_SCL_GPIO	(27)
#घोषणा VIPER_RTC_I2C_SDA_GPIO	(83)
#घोषणा VIPER_RTC_I2C_SCL_GPIO	(84)

#घोषणा VIPER_CPLD_P2V(x)	((x) - VIPER_CPLD_PHYS + VIPER_CPLD_BASE)
#घोषणा VIPER_CPLD_V2P(x)	((x) - VIPER_CPLD_BASE + VIPER_CPLD_PHYS)

#अगर_अघोषित __ASSEMBLY__
#  define __VIPER_CPLD_REG(x)	(*((अस्थिर u16 *)VIPER_CPLD_P2V(x)))
#पूर्ण_अगर

/* board level रेजिस्टरs in the CPLD: (offsets from CPLD_BASE) ... */

/* ... Physical addresses */
#घोषणा _VIPER_LO_IRQ_STATUS	(VIPER_CPLD_PHYS + 0x100000)
#घोषणा _VIPER_ICR_PHYS		(VIPER_CPLD_PHYS + 0x100002)
#घोषणा _VIPER_HI_IRQ_STATUS	(VIPER_CPLD_PHYS + 0x100004)
#घोषणा _VIPER_VERSION_PHYS	(VIPER_CPLD_PHYS + 0x100006)
#घोषणा VIPER_UARTA_PHYS	(VIPER_CPLD_PHYS + 0x300010)
#घोषणा VIPER_UARTB_PHYS	(VIPER_CPLD_PHYS + 0x300000)
#घोषणा _VIPER_SRAM_BASE	(VIPER_CPLD_PHYS + 0x800000)

/* ... Virtual addresses */
#घोषणा VIPER_LO_IRQ_STATUS	__VIPER_CPLD_REG(_VIPER_LO_IRQ_STATUS)
#घोषणा VIPER_HI_IRQ_STATUS	__VIPER_CPLD_REG(_VIPER_HI_IRQ_STATUS)
#घोषणा VIPER_VERSION		__VIPER_CPLD_REG(_VIPER_VERSION_PHYS)
#घोषणा VIPER_ICR		__VIPER_CPLD_REG(_VIPER_ICR_PHYS)

/* Decode VIPER_VERSION रेजिस्टर */
#घोषणा VIPER_CPLD_REVISION(x)	(((x) >> 5) & 0x7)
#घोषणा VIPER_BOARD_VERSION(x)	(((x) >> 3) & 0x3)
#घोषणा VIPER_BOARD_ISSUE(x)	(((x) >> 0) & 0x7)

/* Interrupt and Configuration Register (VIPER_ICR) */
/* This is a ग_लिखो only रेजिस्टर. Only CF_RST is used under Linux */

#घोषणा VIPER_ICR_RETRIG	(1 << 0)
#घोषणा VIPER_ICR_AUTO_CLR	(1 << 1)
#घोषणा VIPER_ICR_R_DIS		(1 << 2)
#घोषणा VIPER_ICR_CF_RST	(1 << 3)

#पूर्ण_अगर

