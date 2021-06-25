<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Register mappings क्रम Loongson 1
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_LOONGSON1_H
#घोषणा __ASM_MACH_LOONGSON32_LOONGSON1_H

#अगर defined(CONFIG_LOONGSON1_LS1B)
#घोषणा DEFAULT_MEMSIZE			64	/* If no memsize provided */
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
#घोषणा DEFAULT_MEMSIZE			32
#पूर्ण_अगर

/* Loongson 1 Register Bases */
#घोषणा LS1X_MUX_BASE			0x1fd00420
#घोषणा LS1X_INTC_BASE			0x1fd01040
#घोषणा LS1X_GPIO0_BASE			0x1fd010c0
#घोषणा LS1X_GPIO1_BASE			0x1fd010c4
#घोषणा LS1X_DMAC_BASE			0x1fd01160
#घोषणा LS1X_CBUS_BASE			0x1fd011c0
#घोषणा LS1X_EHCI_BASE			0x1fe00000
#घोषणा LS1X_OHCI_BASE			0x1fe08000
#घोषणा LS1X_GMAC0_BASE			0x1fe10000
#घोषणा LS1X_GMAC1_BASE			0x1fe20000

#घोषणा LS1X_UART0_BASE			0x1fe40000
#घोषणा LS1X_UART1_BASE			0x1fe44000
#घोषणा LS1X_UART2_BASE			0x1fe48000
#घोषणा LS1X_UART3_BASE			0x1fe4c000
#घोषणा LS1X_CAN0_BASE			0x1fe50000
#घोषणा LS1X_CAN1_BASE			0x1fe54000
#घोषणा LS1X_I2C0_BASE			0x1fe58000
#घोषणा LS1X_I2C1_BASE			0x1fe68000
#घोषणा LS1X_I2C2_BASE			0x1fe70000
#घोषणा LS1X_PWM0_BASE			0x1fe5c000
#घोषणा LS1X_PWM1_BASE			0x1fe5c010
#घोषणा LS1X_PWM2_BASE			0x1fe5c020
#घोषणा LS1X_PWM3_BASE			0x1fe5c030
#घोषणा LS1X_WDT_BASE			0x1fe5c060
#घोषणा LS1X_RTC_BASE			0x1fe64000
#घोषणा LS1X_AC97_BASE			0x1fe74000
#घोषणा LS1X_न_अंकD_BASE			0x1fe78000
#घोषणा LS1X_CLK_BASE			0x1fe78030

#समावेश <regs-clk.h>
#समावेश <regs-mux.h>
#समावेश <regs-pwm.h>
#समावेश <regs-rtc.h>
#समावेश <regs-wdt.h>

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_LOONGSON1_H */
