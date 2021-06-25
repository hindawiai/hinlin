<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIOs and पूर्णांकerrupts क्रम Palm Zire72 Handheld Computer
 *
 * Authors:	Alex Osborne <bobofकरोom@gmail.com>
 *		Jan Herman <2hp@seznam.cz>
 *		Sergey Lapin <slapin@ossfans.org>
 */

#अगर_अघोषित _INCLUDE_PALMZ72_H_
#घोषणा _INCLUDE_PALMZ72_H_

/* Power and control */
#घोषणा GPIO_NR_PALMZ72_GPIO_RESET		1
#घोषणा GPIO_NR_PALMZ72_POWER_DETECT		0

/* SD/MMC */
#घोषणा GPIO_NR_PALMZ72_SD_DETECT_N		14
#घोषणा GPIO_NR_PALMZ72_SD_POWER_N		98
#घोषणा GPIO_NR_PALMZ72_SD_RO			115

/* Touchscreen */
#घोषणा GPIO_NR_PALMZ72_WM9712_IRQ		27

/* IRDA -  disable GPIO connected to SD pin of tranceiver (TFBS4710?) ? */
#घोषणा GPIO_NR_PALMZ72_IR_DISABLE		49

/* USB */
#घोषणा GPIO_NR_PALMZ72_USB_DETECT_N		15
#घोषणा GPIO_NR_PALMZ72_USB_PULLUP		95

/* LCD/Backlight */
#घोषणा GPIO_NR_PALMZ72_BL_POWER		20
#घोषणा GPIO_NR_PALMZ72_LCD_POWER		96

/* LED */
#घोषणा GPIO_NR_PALMZ72_LED_GREEN		88

/* Bluetooth */
#घोषणा GPIO_NR_PALMZ72_BT_POWER		17
#घोषणा GPIO_NR_PALMZ72_BT_RESET		83

/* Camera */
#घोषणा GPIO_NR_PALMZ72_CAM_PWDN		56
#घोषणा GPIO_NR_PALMZ72_CAM_RESET		57
#घोषणा GPIO_NR_PALMZ72_CAM_POWER		91

/** Initial values **/

/* Battery */
#घोषणा PALMZ72_BAT_MAX_VOLTAGE		4000	/* 4.00v current voltage */
#घोषणा PALMZ72_BAT_MIN_VOLTAGE		3550	/* 3.55v critical voltage */
#घोषणा PALMZ72_BAT_MAX_CURRENT		0	/* unknown */
#घोषणा PALMZ72_BAT_MIN_CURRENT		0	/* unknown */
#घोषणा PALMZ72_BAT_MAX_CHARGE		1	/* unknown */
#घोषणा PALMZ72_BAT_MIN_CHARGE		1	/* unknown */
#घोषणा PALMZ72_MAX_LIFE_MINS		360	/* on-lअगरe in minutes */

/* Backlight */
#घोषणा PALMZ72_MAX_INTENSITY		0xFE
#घोषणा PALMZ72_DEFAULT_INTENSITY	0x7E
#घोषणा PALMZ72_LIMIT_MASK		0x7F
#घोषणा PALMZ72_PRESCALER		0x3F
#घोषणा PALMZ72_PERIOD_NS		3500

#अगर_घोषित CONFIG_PM
काष्ठा palmz72_resume_info अणु
	u32 magic0;		/* 0x0 */
	u32 magic1;		/* 0x4 */
	u32 resume_addr;	/* 0x8 */
	u32 pad[11];		/* 0xc..0x37 */
	u32 arm_control;	/* 0x38 */
	u32 aux_control;	/* 0x3c */
	u32 ttb;		/* 0x40 */
	u32 करोमुख्य_access;	/* 0x44 */
	u32 process_id;		/* 0x48 */
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

