<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIOs and पूर्णांकerrupts क्रम Palm Tungsten|T5 Handheld Computer
 *
 * Authors:	Ales Snuparek <snuparek@atlas.cz>
 *		Marek Vasut <marek.vasut@gmail.com>
 *		Justin Kendrick <twilightsentry@gmail.com>
 *		Riअक्षरdT5 <riअक्षरd_t5@users.sourceक्रमge.net>
 */

#अगर_अघोषित _INCLUDE_PALMT5_H_
#घोषणा _INCLUDE_PALMT5_H_

#समावेश <mach/irqs.h> /* PXA_GPIO_TO_IRQ */

/** HERE ARE GPIOs **/

/* GPIOs */
#घोषणा GPIO_NR_PALMT5_GPIO_RESET		1

#घोषणा GPIO_NR_PALMT5_POWER_DETECT		90
#घोषणा GPIO_NR_PALMT5_HOTSYNC_BUTTON_N		10
#घोषणा GPIO_NR_PALMT5_EARPHONE_DETECT		107

/* SD/MMC */
#घोषणा GPIO_NR_PALMT5_SD_DETECT_N		14
#घोषणा GPIO_NR_PALMT5_SD_POWER			114
#घोषणा GPIO_NR_PALMT5_SD_READONLY		115

/* TOUCHSCREEN */
#घोषणा GPIO_NR_PALMT5_WM9712_IRQ		27

/* IRDA - disable GPIO connected to SD pin of tranceiver (TFBS4710?) ? */
#घोषणा GPIO_NR_PALMT5_IR_DISABLE		40

/* USB */
#घोषणा GPIO_NR_PALMT5_USB_DETECT_N		15
#घोषणा GPIO_NR_PALMT5_USB_PULLUP		93

/* LCD/BACKLIGHT */
#घोषणा GPIO_NR_PALMT5_BL_POWER			84
#घोषणा GPIO_NR_PALMT5_LCD_POWER		96

/* BLUETOOTH */
#घोषणा GPIO_NR_PALMT5_BT_POWER			17
#घोषणा GPIO_NR_PALMT5_BT_RESET			83

/* INTERRUPTS */
#घोषणा IRQ_GPIO_PALMT5_SD_DETECT_N	PXA_GPIO_TO_IRQ(GPIO_NR_PALMT5_SD_DETECT_N)
#घोषणा IRQ_GPIO_PALMT5_WM9712_IRQ	PXA_GPIO_TO_IRQ(GPIO_NR_PALMT5_WM9712_IRQ)
#घोषणा IRQ_GPIO_PALMT5_USB_DETECT	PXA_GPIO_TO_IRQ(GPIO_NR_PALMT5_USB_DETECT)
#घोषणा IRQ_GPIO_PALMT5_GPIO_RESET	PXA_GPIO_TO_IRQ(GPIO_NR_PALMT5_GPIO_RESET)

/** HERE ARE INIT VALUES **/

/* Various addresses  */
#घोषणा PALMT5_PHYS_RAM_START	0xa0000000
#घोषणा PALMT5_PHYS_IO_START	0x40000000
#घोषणा PALMT5_STR_BASE		0xa0200000

/* TOUCHSCREEN */
#घोषणा AC97_LINK_FRAME		21

/* BATTERY */
#घोषणा PALMT5_BAT_MAX_VOLTAGE		4000	/* 4.00v current voltage */
#घोषणा PALMT5_BAT_MIN_VOLTAGE		3550	/* 3.55v critical voltage */
#घोषणा PALMT5_BAT_MAX_CURRENT		0	/* unknown */
#घोषणा PALMT5_BAT_MIN_CURRENT		0	/* unknown */
#घोषणा PALMT5_BAT_MAX_CHARGE		1	/* unknown */
#घोषणा PALMT5_BAT_MIN_CHARGE		1	/* unknown */
#घोषणा PALMT5_MAX_LIFE_MINS		360    /* on-lअगरe in minutes */

#घोषणा PALMT5_BAT_MEASURE_DELAY	(HZ * 1)

/* BACKLIGHT */
#घोषणा PALMT5_MAX_INTENSITY		0xFE
#घोषणा PALMT5_DEFAULT_INTENSITY	0x7E
#घोषणा PALMT5_LIMIT_MASK		0x7F
#घोषणा PALMT5_PRESCALER		0x3F
#घोषणा PALMT5_PERIOD_NS		3500

#पूर्ण_अगर
