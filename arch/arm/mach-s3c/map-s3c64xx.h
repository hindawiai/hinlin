<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C64XX - Memory map definitions
 */

#अगर_अघोषित __ASM_ARCH_MAP_H
#घोषणा __ASM_ARCH_MAP_H __खाता__

#समावेश <mach/map-base.h>
#समावेश "map-s3c.h"

/*
 * Post-mux Chip Select Regions Xm0CSn_
 * These may be used by SROM, न_अंकD or CF depending on settings
 */

#घोषणा S3C64XX_PA_XM0CSN0 (0x10000000)
#घोषणा S3C64XX_PA_XM0CSN1 (0x18000000)
#घोषणा S3C64XX_PA_XM0CSN2 (0x20000000)
#घोषणा S3C64XX_PA_XM0CSN3 (0x28000000)
#घोषणा S3C64XX_PA_XM0CSN4 (0x30000000)
#घोषणा S3C64XX_PA_XM0CSN5 (0x38000000)

/* HSMMC units */
#घोषणा S3C64XX_PA_HSMMC(x)	(0x7C200000 + ((x) * 0x100000))
#घोषणा S3C64XX_PA_HSMMC0	S3C64XX_PA_HSMMC(0)
#घोषणा S3C64XX_PA_HSMMC1	S3C64XX_PA_HSMMC(1)
#घोषणा S3C64XX_PA_HSMMC2	S3C64XX_PA_HSMMC(2)

#घोषणा S3C_PA_UART		(0x7F005000)
#घोषणा S3C_PA_UART0		(S3C_PA_UART + 0x00)
#घोषणा S3C_PA_UART1		(S3C_PA_UART + 0x400)
#घोषणा S3C_PA_UART2		(S3C_PA_UART + 0x800)
#घोषणा S3C_PA_UART3		(S3C_PA_UART + 0xC00)
#घोषणा S3C_UART_OFFSET		(0x400)

/* See notes on UART VA mapping in debug-macro.S */
#घोषणा S3C_VA_UARTx(x)	(S3C_VA_UART + (S3C_PA_UART & 0xfffff) + ((x) * S3C_UART_OFFSET))

#घोषणा S3C_VA_UART0		S3C_VA_UARTx(0)
#घोषणा S3C_VA_UART1		S3C_VA_UARTx(1)
#घोषणा S3C_VA_UART2		S3C_VA_UARTx(2)
#घोषणा S3C_VA_UART3		S3C_VA_UARTx(3)

#घोषणा S3C64XX_PA_SROM		(0x70000000)

#घोषणा S3C64XX_PA_ONEन_अंकD0	(0x70100000)
#घोषणा S3C64XX_PA_ONEन_अंकD0_BUF	(0x20000000)
#घोषणा S3C64XX_SZ_ONEन_अंकD0_BUF (SZ_64M)

/* न_अंकD and Oneन_अंकD1 controllers occupy the same रेजिस्टर region
   (depending on SoC POP version) */
#घोषणा S3C64XX_PA_ONEन_अंकD1	(0x70200000)
#घोषणा S3C64XX_PA_ONEन_अंकD1_BUF	(0x28000000)
#घोषणा S3C64XX_SZ_ONEन_अंकD1_BUF	(SZ_64M)

#घोषणा S3C64XX_PA_न_अंकD		(0x70200000)
#घोषणा S3C64XX_PA_FB		(0x77100000)
#घोषणा S3C64XX_PA_USB_HSOTG	(0x7C000000)
#घोषणा S3C64XX_PA_WATCHDOG	(0x7E004000)
#घोषणा S3C64XX_PA_RTC		(0x7E005000)
#घोषणा S3C64XX_PA_KEYPAD	(0x7E00A000)
#घोषणा S3C64XX_PA_ADC		(0x7E00B000)
#घोषणा S3C64XX_PA_SYSCON	(0x7E00F000)
#घोषणा S3C64XX_PA_AC97		(0x7F001000)
#घोषणा S3C64XX_PA_IIS0		(0x7F002000)
#घोषणा S3C64XX_PA_IIS1		(0x7F003000)
#घोषणा S3C64XX_PA_TIMER	(0x7F006000)
#घोषणा S3C64XX_PA_IIC0		(0x7F004000)
#घोषणा S3C64XX_PA_SPI0		(0x7F00B000)
#घोषणा S3C64XX_PA_SPI1		(0x7F00C000)
#घोषणा S3C64XX_PA_PCM0		(0x7F009000)
#घोषणा S3C64XX_PA_PCM1		(0x7F00A000)
#घोषणा S3C64XX_PA_IISV4	(0x7F00D000)
#घोषणा S3C64XX_PA_IIC1		(0x7F00F000)

#घोषणा S3C64XX_PA_GPIO		(0x7F008000)
#घोषणा S3C64XX_SZ_GPIO		SZ_4K

#घोषणा S3C64XX_PA_SDRAM	(0x50000000)

#घोषणा S3C64XX_PA_CFCON	(0x70300000)

#घोषणा S3C64XX_PA_VIC0		(0x71200000)
#घोषणा S3C64XX_PA_VIC1		(0x71300000)

#घोषणा S3C64XX_PA_MODEM	(0x74108000)

#घोषणा S3C64XX_PA_USBHOST	(0x74300000)

#घोषणा S3C64XX_PA_USB_HSPHY	(0x7C100000)

/* compatibility defines. */
#घोषणा S3C_PA_TIMER		S3C64XX_PA_TIMER
#घोषणा S3C_PA_HSMMC0		S3C64XX_PA_HSMMC0
#घोषणा S3C_PA_HSMMC1		S3C64XX_PA_HSMMC1
#घोषणा S3C_PA_HSMMC2		S3C64XX_PA_HSMMC2
#घोषणा S3C_PA_IIC		S3C64XX_PA_IIC0
#घोषणा S3C_PA_IIC1		S3C64XX_PA_IIC1
#घोषणा S3C_PA_न_अंकD		S3C64XX_PA_न_अंकD
#घोषणा S3C_PA_ONEन_अंकD		S3C64XX_PA_ONEन_अंकD0
#घोषणा S3C_PA_ONEन_अंकD_BUF	S3C64XX_PA_ONEन_अंकD0_BUF
#घोषणा S3C_SZ_ONEन_अंकD_BUF	S3C64XX_SZ_ONEन_अंकD0_BUF
#घोषणा S3C_PA_FB		S3C64XX_PA_FB
#घोषणा S3C_PA_USBHOST		S3C64XX_PA_USBHOST
#घोषणा S3C_PA_USB_HSOTG	S3C64XX_PA_USB_HSOTG
#घोषणा S3C_PA_RTC		S3C64XX_PA_RTC
#घोषणा S3C_PA_WDT		S3C64XX_PA_WATCHDOG
#घोषणा S3C_PA_SPI0		S3C64XX_PA_SPI0
#घोषणा S3C_PA_SPI1		S3C64XX_PA_SPI1

#घोषणा SAMSUNG_PA_ADC		S3C64XX_PA_ADC
#घोषणा SAMSUNG_PA_CFCON	S3C64XX_PA_CFCON
#घोषणा SAMSUNG_PA_KEYPAD	S3C64XX_PA_KEYPAD
#घोषणा SAMSUNG_PA_TIMER	S3C64XX_PA_TIMER

#पूर्ण_अगर /* __ASM_ARCH_6400_MAP_H */
