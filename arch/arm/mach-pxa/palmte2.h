<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIOs and पूर्णांकerrupts क्रम Palm Tungsten|E2 Handheld Computer
 *
 * Author:
 *		Carlos Eduarकरो Medaglia Dyonisio <cadu@nerdfeliz.com>
 */

#अगर_अघोषित _INCLUDE_PALMTE2_H_
#घोषणा _INCLUDE_PALMTE2_H_

/** HERE ARE GPIOs **/

/* GPIOs */
#घोषणा GPIO_NR_PALMTE2_POWER_DETECT		9
#घोषणा GPIO_NR_PALMTE2_HOTSYNC_BUTTON_N	4
#घोषणा GPIO_NR_PALMTE2_EARPHONE_DETECT		15

/* SD/MMC */
#घोषणा GPIO_NR_PALMTE2_SD_DETECT_N		10
#घोषणा GPIO_NR_PALMTE2_SD_POWER		55
#घोषणा GPIO_NR_PALMTE2_SD_READONLY		51

/* IRDA -  disable GPIO connected to SD pin of tranceiver (TFBS4710?) ? */
#घोषणा GPIO_NR_PALMTE2_IR_DISABLE		48

/* USB */
#घोषणा GPIO_NR_PALMTE2_USB_DETECT_N		35
#घोषणा GPIO_NR_PALMTE2_USB_PULLUP		53

/* LCD/BACKLIGHT */
#घोषणा GPIO_NR_PALMTE2_BL_POWER		56
#घोषणा GPIO_NR_PALMTE2_LCD_POWER		37

/* KEYS */
#घोषणा GPIO_NR_PALMTE2_KEY_NOTES	5
#घोषणा GPIO_NR_PALMTE2_KEY_TASKS	7
#घोषणा GPIO_NR_PALMTE2_KEY_CALENDAR	11
#घोषणा GPIO_NR_PALMTE2_KEY_CONTACTS	13
#घोषणा GPIO_NR_PALMTE2_KEY_CENTER	14
#घोषणा GPIO_NR_PALMTE2_KEY_LEFT	19
#घोषणा GPIO_NR_PALMTE2_KEY_RIGHT	20
#घोषणा GPIO_NR_PALMTE2_KEY_DOWN	21
#घोषणा GPIO_NR_PALMTE2_KEY_UP		22

/** HERE ARE INIT VALUES **/

/* BACKLIGHT */
#घोषणा PALMTE2_MAX_INTENSITY		0xFE
#घोषणा PALMTE2_DEFAULT_INTENSITY	0x7E
#घोषणा PALMTE2_LIMIT_MASK		0x7F
#घोषणा PALMTE2_PRESCALER		0x3F
#घोषणा PALMTE2_PERIOD_NS		3500

/* BATTERY */
#घोषणा PALMTE2_BAT_MAX_VOLTAGE		4000	/* 4.00v current voltage */
#घोषणा PALMTE2_BAT_MIN_VOLTAGE		3550	/* 3.55v critical voltage */
#घोषणा PALMTE2_BAT_MAX_CURRENT		0	/* unknown */
#घोषणा PALMTE2_BAT_MIN_CURRENT		0	/* unknown */
#घोषणा PALMTE2_BAT_MAX_CHARGE		1	/* unknown */
#घोषणा PALMTE2_BAT_MIN_CHARGE		1	/* unknown */
#घोषणा PALMTE2_MAX_LIFE_MINS		360	/* on-lअगरe in minutes */

#पूर्ण_अगर
