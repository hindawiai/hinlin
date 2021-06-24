<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2003, 2004, 2005  Andriy Skulysh
 */
#अगर_अघोषित __ASM_SH_HP6XX_H
#घोषणा __ASM_SH_HP6XX_H

#समावेश <linux/sh_पूर्णांकc.h>

#घोषणा HP680_BTN_IRQ		evt2irq(0x600)	/* IRQ0_IRQ */
#घोषणा HP680_TS_IRQ		evt2irq(0x660)	/* IRQ3_IRQ */
#घोषणा HP680_HD64461_IRQ	evt2irq(0x680)	/* IRQ4_IRQ */

#घोषणा DAC_LCD_BRIGHTNESS	0
#घोषणा DAC_SPEAKER_VOLUME	1

#घोषणा PGDR_OPENED		0x01
#घोषणा PGDR_MAIN_BATTERY_OUT	0x04
#घोषणा PGDR_PLAY_BUTTON	0x08
#घोषणा PGDR_REWIND_BUTTON	0x10
#घोषणा PGDR_RECORD_BUTTON	0x20

#घोषणा PHDR_TS_PEN_DOWN	0x08

#घोषणा PJDR_LED_BLINK		0x02

#घोषणा PKDR_LED_GREEN		0x10

/* HP Palmtop 620lx/660lx speaker on/off */
#घोषणा PKDR_SPEAKER		0x20

#घोषणा SCPDR_TS_SCAN_ENABLE	0x20
#घोषणा SCPDR_TS_SCAN_Y		0x02
#घोषणा SCPDR_TS_SCAN_X		0x01

#घोषणा SCPCR_TS_ENABLE		0x405
#घोषणा SCPCR_TS_MASK		0xc0f

#घोषणा ADC_CHANNEL_TS_Y	1
#घोषणा ADC_CHANNEL_TS_X	2
#घोषणा ADC_CHANNEL_BATTERY	3
#घोषणा ADC_CHANNEL_BACKUP	4
#घोषणा ADC_CHANNEL_CHARGE	5

/* HP Jornada 680/690 speaker on/off */
#घोषणा HD64461_GPADR_SPEAKER	0x01
#घोषणा HD64461_GPADR_PCMCIA0	(0x02|0x08)

#घोषणा HD64461_GPBDR_LCDOFF	0x01
#घोषणा HD64461_GPBDR_LCD_CONTRAST_MASK	0x78
#घोषणा HD64461_GPBDR_LED_RED	0x80

#समावेश <यंत्र/hd64461.h>
#समावेश <यंत्र/पन.स>

#घोषणा PJDR	0xa4000130
#घोषणा PKDR	0xa4000132

#पूर्ण_अगर /* __ASM_SH_HP6XX_H */
