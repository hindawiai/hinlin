<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIOs and पूर्णांकerrupts क्रम Palm T|X Handheld Computer
 *
 * Based on palmld-gpपन.स by Alex Osborne
 *
 * Authors:	Marek Vasut <marek.vasut@gmail.com>
 *		Cristiano P. <cristianop@users.sourceक्रमge.net>
 *		Jan Herman <2hp@seznam.cz>
 */

#अगर_अघोषित _INCLUDE_PALMTX_H_
#घोषणा _INCLUDE_PALMTX_H_

#समावेश "irqs.h" /* PXA_GPIO_TO_IRQ */

/** HERE ARE GPIOs **/

/* GPIOs */
#घोषणा GPIO_NR_PALMTX_GPIO_RESET		1

#घोषणा GPIO_NR_PALMTX_POWER_DETECT		12 /* 90 */
#घोषणा GPIO_NR_PALMTX_HOTSYNC_BUTTON_N		10
#घोषणा GPIO_NR_PALMTX_EARPHONE_DETECT		107

/* SD/MMC */
#घोषणा GPIO_NR_PALMTX_SD_DETECT_N		14
#घोषणा GPIO_NR_PALMTX_SD_POWER			114 /* probably */
#घोषणा GPIO_NR_PALMTX_SD_READONLY		115 /* probably */

/* TOUCHSCREEN */
#घोषणा GPIO_NR_PALMTX_WM9712_IRQ		27

/* IRDA -  disable GPIO connected to SD pin of tranceiver (TFBS4710?) ? */
#घोषणा GPIO_NR_PALMTX_IR_DISABLE		40

/* USB */
#घोषणा GPIO_NR_PALMTX_USB_DETECT_N		13
#घोषणा GPIO_NR_PALMTX_USB_PULLUP		93

/* LCD/BACKLIGHT */
#घोषणा GPIO_NR_PALMTX_BL_POWER			84
#घोषणा GPIO_NR_PALMTX_LCD_POWER		96

/* LCD BORDER */
#घोषणा GPIO_NR_PALMTX_BORDER_SWITCH		98
#घोषणा GPIO_NR_PALMTX_BORDER_SELECT		22

/* BLUETOOTH */
#घोषणा GPIO_NR_PALMTX_BT_POWER			17
#घोषणा GPIO_NR_PALMTX_BT_RESET			83

/* PCMCIA (WiFi) */
#घोषणा GPIO_NR_PALMTX_PCMCIA_POWER1		94
#घोषणा GPIO_NR_PALMTX_PCMCIA_POWER2		108
#घोषणा GPIO_NR_PALMTX_PCMCIA_RESET		79
#घोषणा GPIO_NR_PALMTX_PCMCIA_READY		116

/* न_अंकD Flash ... this GPIO may be incorrect! */
#घोषणा GPIO_NR_PALMTX_न_अंकD_BUFFER_सूची		79

/* INTERRUPTS */
#घोषणा IRQ_GPIO_PALMTX_SD_DETECT_N	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTX_SD_DETECT_N)
#घोषणा IRQ_GPIO_PALMTX_WM9712_IRQ	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTX_WM9712_IRQ)
#घोषणा IRQ_GPIO_PALMTX_USB_DETECT	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTX_USB_DETECT)
#घोषणा IRQ_GPIO_PALMTX_GPIO_RESET	PXA_GPIO_TO_IRQ(GPIO_NR_PALMTX_GPIO_RESET)

/** HERE ARE INIT VALUES **/

/* Various addresses  */
#घोषणा PALMTX_PCMCIA_PHYS	0x28000000
#घोषणा PALMTX_PCMCIA_VIRT	IOMEM(0xf0000000)
#घोषणा PALMTX_PCMCIA_SIZE	0x100000

#घोषणा PALMTX_PHYS_RAM_START	0xa0000000
#घोषणा PALMTX_PHYS_IO_START	0x40000000

#घोषणा PALMTX_STR_BASE		0xa0200000

#घोषणा PALMTX_PHYS_FLASH_START	PXA_CS0_PHYS	/* ChipSelect 0 */
#घोषणा PALMTX_PHYS_न_अंकD_START	PXA_CS1_PHYS	/* ChipSelect 1 */

#घोषणा PALMTX_न_अंकD_ALE_PHYS	(PALMTX_PHYS_न_अंकD_START | (1 << 24))
#घोषणा PALMTX_न_अंकD_CLE_PHYS	(PALMTX_PHYS_न_अंकD_START | (1 << 25))
#घोषणा PALMTX_न_अंकD_ALE_VIRT	IOMEM(0xff100000)
#घोषणा PALMTX_न_अंकD_CLE_VIRT	IOMEM(0xff200000)

/* TOUCHSCREEN */
#घोषणा AC97_LINK_FRAME			21


/* BATTERY */
#घोषणा PALMTX_BAT_MAX_VOLTAGE		4000	/* 4.00v current voltage */
#घोषणा PALMTX_BAT_MIN_VOLTAGE		3550	/* 3.55v critical voltage */
#घोषणा PALMTX_BAT_MAX_CURRENT		0	/* unknown */
#घोषणा PALMTX_BAT_MIN_CURRENT		0	/* unknown */
#घोषणा PALMTX_BAT_MAX_CHARGE		1	/* unknown */
#घोषणा PALMTX_BAT_MIN_CHARGE		1	/* unknown */
#घोषणा PALMTX_MAX_LIFE_MINS		360	/* on-lअगरe in minutes */

#घोषणा PALMTX_BAT_MEASURE_DELAY	(HZ * 1)

/* BACKLIGHT */
#घोषणा PALMTX_MAX_INTENSITY		0xFE
#घोषणा PALMTX_DEFAULT_INTENSITY	0x7E
#घोषणा PALMTX_LIMIT_MASK		0x7F
#घोषणा PALMTX_PRESCALER		0x3F
#घोषणा PALMTX_PERIOD_NS		3500

#पूर्ण_अगर
