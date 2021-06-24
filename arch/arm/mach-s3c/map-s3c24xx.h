<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 - Memory map definitions
 */

#अगर_अघोषित __ASM_ARCH_MAP_H
#घोषणा __ASM_ARCH_MAP_H

#समावेश <mach/map-base.h>
#समावेश "map-s3c.h"

/*
 * पूर्णांकerrupt controller is the first thing we put in, to make
 * the assembly code क्रम the irq detection easier
 */
#घोषणा S3C2410_PA_IRQ		(0x4A000000)
#घोषणा S3C24XX_SZ_IRQ		SZ_1M

/* memory controller रेजिस्टरs */
#घोषणा S3C2410_PA_MEMCTRL	(0x48000000)
#घोषणा S3C24XX_SZ_MEMCTRL	SZ_1M

/* Timers */
#घोषणा S3C2410_PA_TIMER	(0x51000000)
#घोषणा S3C24XX_SZ_TIMER	SZ_1M

/* Clock and Power management */
#घोषणा S3C24XX_SZ_CLKPWR	SZ_1M

/* USB Device port */
#घोषणा S3C2410_PA_USBDEV	(0x52000000)
#घोषणा S3C24XX_SZ_USBDEV	SZ_1M

/* Watchकरोg */
#घोषणा S3C2410_PA_WATCHDOG	(0x53000000)
#घोषणा S3C24XX_SZ_WATCHDOG	SZ_1M

/* Standard size definitions क्रम peripheral blocks. */

#घोषणा S3C24XX_SZ_UART		SZ_1M
#घोषणा S3C24XX_SZ_IIS		SZ_1M
#घोषणा S3C24XX_SZ_ADC		SZ_1M
#घोषणा S3C24XX_SZ_SPI		SZ_1M
#घोषणा S3C24XX_SZ_SDI		SZ_1M
#घोषणा S3C24XX_SZ_न_अंकD		SZ_1M
#घोषणा S3C24XX_SZ_GPIO		SZ_1M

/* USB host controller */
#घोषणा S3C2410_PA_USBHOST (0x49000000)

/* S3C2416/S3C2443/S3C2450 High-Speed USB Gadget */
#घोषणा S3C2416_PA_HSUDC	(0x49800000)
#घोषणा S3C2416_SZ_HSUDC	(SZ_4K)

/* DMA controller */
#घोषणा S3C2410_PA_DMA	   (0x4B000000)
#घोषणा S3C24XX_SZ_DMA	   SZ_1M

/* Clock and Power management */
#घोषणा S3C2410_PA_CLKPWR  (0x4C000000)

/* LCD controller */
#घोषणा S3C2410_PA_LCD	   (0x4D000000)
#घोषणा S3C24XX_SZ_LCD	   SZ_1M

/* न_अंकD flash controller */
#घोषणा S3C2410_PA_न_अंकD	   (0x4E000000)

/* IIC hardware controller */
#घोषणा S3C2410_PA_IIC	   (0x54000000)

/* IIS controller */
#घोषणा S3C2410_PA_IIS	   (0x55000000)

/* RTC */
#घोषणा S3C2410_PA_RTC	   (0x57000000)
#घोषणा S3C24XX_SZ_RTC	   SZ_1M

/* ADC */
#घोषणा S3C2410_PA_ADC	   (0x58000000)

/* SPI */
#घोषणा S3C2410_PA_SPI	   (0x59000000)
#घोषणा S3C2443_PA_SPI0		(0x52000000)
#घोषणा S3C2443_PA_SPI1		S3C2410_PA_SPI
#घोषणा S3C2410_SPI1		(0x20)
#घोषणा S3C2412_SPI1		(0x100)

/* SDI */
#घोषणा S3C2410_PA_SDI	   (0x5A000000)

/* CAMIF */
#घोषणा S3C2440_PA_CAMIF   (0x4F000000)
#घोषणा S3C2440_SZ_CAMIF   SZ_1M

/* AC97 */

#घोषणा S3C2440_PA_AC97	   (0x5B000000)
#घोषणा S3C2440_SZ_AC97	   SZ_1M

/* S3C2443/S3C2416 High-speed SD/MMC */
#घोषणा S3C2443_PA_HSMMC   (0x4A800000)
#घोषणा S3C2416_PA_HSMMC0  (0x4AC00000)

#घोषणा	S3C2443_PA_FB	(0x4C800000)

/* S3C2412 memory and IO controls */
#घोषणा S3C2412_PA_SSMC	(0x4F000000)

#घोषणा S3C2412_PA_EBI	(0x48800000)

/* physical addresses of all the chip-select areas */

#घोषणा S3C2410_CS0 (0x00000000)
#घोषणा S3C2410_CS1 (0x08000000)
#घोषणा S3C2410_CS2 (0x10000000)
#घोषणा S3C2410_CS3 (0x18000000)
#घोषणा S3C2410_CS4 (0x20000000)
#घोषणा S3C2410_CS5 (0x28000000)
#घोषणा S3C2410_CS6 (0x30000000)
#घोषणा S3C2410_CS7 (0x38000000)

#घोषणा S3C2410_SDRAM_PA    (S3C2410_CS6)

/* Use a single पूर्णांकerface क्रम common resources between S3C24XX cpus */

#घोषणा S3C24XX_PA_IRQ      S3C2410_PA_IRQ
#घोषणा S3C24XX_PA_MEMCTRL  S3C2410_PA_MEMCTRL
#घोषणा S3C24XX_PA_DMA      S3C2410_PA_DMA
#घोषणा S3C24XX_PA_CLKPWR   S3C2410_PA_CLKPWR
#घोषणा S3C24XX_PA_LCD      S3C2410_PA_LCD
#घोषणा S3C24XX_PA_TIMER    S3C2410_PA_TIMER
#घोषणा S3C24XX_PA_USBDEV   S3C2410_PA_USBDEV
#घोषणा S3C24XX_PA_WATCHDOG S3C2410_PA_WATCHDOG
#घोषणा S3C24XX_PA_IIS      S3C2410_PA_IIS
#घोषणा S3C24XX_PA_RTC      S3C2410_PA_RTC
#घोषणा S3C24XX_PA_ADC      S3C2410_PA_ADC
#घोषणा S3C24XX_PA_SPI      S3C2410_PA_SPI
#घोषणा S3C24XX_PA_SPI1		(S3C2410_PA_SPI + S3C2410_SPI1)
#घोषणा S3C24XX_PA_SDI      S3C2410_PA_SDI
#घोषणा S3C24XX_PA_न_अंकD	    S3C2410_PA_न_अंकD

#घोषणा S3C_PA_FB	    S3C2443_PA_FB
#घोषणा S3C_PA_IIC          S3C2410_PA_IIC
#घोषणा S3C_PA_USBHOST	S3C2410_PA_USBHOST
#घोषणा S3C_PA_HSMMC0	    S3C2416_PA_HSMMC0
#घोषणा S3C_PA_HSMMC1	    S3C2443_PA_HSMMC
#घोषणा S3C_PA_WDT	    S3C2410_PA_WATCHDOG
#घोषणा S3C_PA_न_अंकD	    S3C24XX_PA_न_अंकD

#घोषणा S3C_PA_SPI0		S3C2443_PA_SPI0
#घोषणा S3C_PA_SPI1		S3C2443_PA_SPI1

#घोषणा SAMSUNG_PA_TIMER	S3C2410_PA_TIMER

#पूर्ण_अगर /* __ASM_ARCH_MAP_H */
