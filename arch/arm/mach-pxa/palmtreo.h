<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIOs and पूर्णांकerrupts क्रम Palm Treo smartphones
 *
 * currently supported:
 *     Palm Treo 680 (GSM)
 *     Palm Centro 685 (GSM)
 *
 * Author:     Tomas Cech <sleep_walker@suse.cz>
 *
 * find more info at www.hackndev.com
 */

#अगर_अघोषित _INCLUDE_TREO_H_
#घोषणा _INCLUDE_TREO_H_

/* GPIOs */
#घोषणा GPIO_NR_TREO_POWER_DETECT	0
#घोषणा GPIO_NR_TREO_AMP_EN		27
#घोषणा GPIO_NR_TREO_GREEN_LED	20
#घोषणा GPIO_NR_TREO_RED_LED		79
#घोषणा GPIO_NR_TREO_SD_DETECT_N	113
#घोषणा GPIO_NR_TREO_EP_DETECT_N	116
#घोषणा GPIO_NR_TREO_USB_DETECT	1
#घोषणा GPIO_NR_TREO_USB_PULLUP	114
#घोषणा GPIO_NR_TREO_GSM_POWER	40
#घोषणा GPIO_NR_TREO_GSM_RESET	87
#घोषणा GPIO_NR_TREO_GSM_WAKE	57
#घोषणा GPIO_NR_TREO_GSM_HOST_WAKE	14
#घोषणा GPIO_NR_TREO_GSM_TRIGGER	10
#घोषणा GPIO_NR_TREO_IR_EN		115
#घोषणा GPIO_NR_TREO_IR_TXD		47
#घोषणा GPIO_NR_TREO_BL_POWER	38
#घोषणा GPIO_NR_TREO_LCD_POWER	25

/* Treo680 specअगरic GPIOs */
#घोषणा GPIO_NR_TREO680_SD_READONLY	33
#घोषणा GPIO_NR_TREO680_SD_POWER	42
#घोषणा GPIO_NR_TREO680_VIBRATE_EN	44
#घोषणा GPIO_NR_TREO680_KEYB_BL		24
#घोषणा GPIO_NR_TREO680_BT_EN		43
#घोषणा GPIO_NR_TREO680_LCD_POWER	77
#घोषणा GPIO_NR_TREO680_LCD_EN		86
#घोषणा GPIO_NR_TREO680_LCD_EN_N	25

/* Centro685 specअगरic GPIOs */
#घोषणा GPIO_NR_CENTRO_SD_POWER		21
#घोषणा GPIO_NR_CENTRO_VIBRATE_EN	22
#घोषणा GPIO_NR_CENTRO_KEYB_BL		33
#घोषणा GPIO_NR_CENTRO_BT_EN		80

/* Various addresses  */
#घोषणा TREO_PHYS_RAM_START	0xa0000000
#घोषणा TREO_PHYS_IO_START	0x40000000
#घोषणा TREO_STR_BASE	0xa2000000

/* BACKLIGHT */
#घोषणा TREO_MAX_INTENSITY		254
#घोषणा TREO_DEFAULT_INTENSITY	160
#घोषणा TREO_LIMIT_MASK		0x7F
#घोषणा TREO_PRESCALER		63
#घोषणा TREO_PERIOD_NS		3500

#पूर्ण_अगर
