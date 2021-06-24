<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/include/यंत्र-arm/arch-pxa/palmtc-gpपन.स
 *
 * GPIOs and पूर्णांकerrupts क्रम Palm Tungsten|C Handheld Computer
 *
 * Authors:	Alex Osborne <bobofकरोom@gmail.com>
 *		Marek Vasut <marek.vasut@gmail.com>
 *		Holger Bocklet <bitz.email@gmx.net>
 */

#अगर_अघोषित _INCLUDE_PALMTC_H_
#घोषणा _INCLUDE_PALMTC_H_

#समावेश "irqs.h" /* PXA_GPIO_TO_IRQ */

/** HERE ARE GPIOs **/

/* GPIOs */
#घोषणा GPIO_NR_PALMTC_EARPHONE_DETECT	2
#घोषणा GPIO_NR_PALMTC_CRADLE_DETECT	5
#घोषणा GPIO_NR_PALMTC_HOTSYNC_BUTTON	7

/* SD/MMC */
#घोषणा GPIO_NR_PALMTC_SD_DETECT_N	12
#घोषणा GPIO_NR_PALMTC_SD_POWER		32
#घोषणा GPIO_NR_PALMTC_SD_READONLY	54

/* WLAN */
#घोषणा GPIO_NR_PALMTC_PCMCIA_READY	13
#घोषणा GPIO_NR_PALMTC_PCMCIA_PWRREADY	14
#घोषणा GPIO_NR_PALMTC_PCMCIA_POWER1	15
#घोषणा GPIO_NR_PALMTC_PCMCIA_POWER2	33
#घोषणा GPIO_NR_PALMTC_PCMCIA_POWER3	55
#घोषणा GPIO_NR_PALMTC_PCMCIA_RESET	78

/* UDC */
#घोषणा GPIO_NR_PALMTC_USB_DETECT_N	4
#घोषणा GPIO_NR_PALMTC_USB_POWER	36

/* LCD/BACKLIGHT */
#घोषणा GPIO_NR_PALMTC_BL_POWER		16
#घोषणा GPIO_NR_PALMTC_LCD_POWER	44
#घोषणा GPIO_NR_PALMTC_LCD_BLANK	38

/* UART */
#घोषणा GPIO_NR_PALMTC_RS232_POWER	37

/* IRDA */
#घोषणा GPIO_NR_PALMTC_IR_DISABLE	45

/* IRQs */
#घोषणा IRQ_GPIO_PALMTC_SD_DETECT_N	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTC_SD_DETECT_N)
#घोषणा IRQ_GPIO_PALMTC_WLAN_READY	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTC_WLAN_READY)

/* UCB1400 GPIOs */
#घोषणा GPIO_NR_PALMTC_POWER_DETECT	(0x80 | 0x00)
#घोषणा GPIO_NR_PALMTC_HEADPHONE_DETECT	(0x80 | 0x01)
#घोषणा GPIO_NR_PALMTC_SPEAKER_ENABLE	(0x80 | 0x03)
#घोषणा GPIO_NR_PALMTC_VIBRA_POWER	(0x80 | 0x05)
#घोषणा GPIO_NR_PALMTC_LED_POWER	(0x80 | 0x07)

/** HERE ARE INIT VALUES **/
#घोषणा PALMTC_UCB1400_GPIO_OFFSET	0x80

/* BATTERY */
#घोषणा PALMTC_BAT_MAX_VOLTAGE		4000	/* 4.00V maximum voltage */
#घोषणा PALMTC_BAT_MIN_VOLTAGE		3550	/* 3.55V critical voltage */
#घोषणा PALMTC_BAT_MAX_CURRENT		0	/* unknown */
#घोषणा PALMTC_BAT_MIN_CURRENT		0	/* unknown */
#घोषणा PALMTC_BAT_MAX_CHARGE		1	/* unknown */
#घोषणा PALMTC_BAT_MIN_CHARGE		1	/* unknown */
#घोषणा PALMTC_MAX_LIFE_MINS		240	/* on-lअगरe in minutes */

#घोषणा PALMTC_BAT_MEASURE_DELAY	(HZ * 1)

/* BACKLIGHT */
#घोषणा PALMTC_MAX_INTENSITY		0xFE
#घोषणा PALMTC_DEFAULT_INTENSITY	0x7E
#घोषणा PALMTC_LIMIT_MASK		0x7F
#घोषणा PALMTC_PRESCALER		0x3F
#घोषणा PALMTC_PERIOD_NS		3500

#पूर्ण_अगर
