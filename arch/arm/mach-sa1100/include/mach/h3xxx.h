<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम Compaq iPAQ H3100 and H3600 handheld computers
 *
 * (c) 2000 Compaq Computer Corporation. (Author: Jamey Hicks)
 * (c) 2009 Dmitry Artamonow <mad_soft@inbox.ru>
 */

#अगर_अघोषित _INCLUDE_H3XXX_H_
#घोषणा _INCLUDE_H3XXX_H_

#समावेश "hardware.h" /* Gives GPIO_MAX */

/* Physical memory regions corresponding to chip selects */
#घोषणा H3600_EGPIO_PHYS	(SA1100_CS5_PHYS + 0x01000000)
#घोषणा H3600_BANK_2_PHYS	SA1100_CS2_PHYS
#घोषणा H3600_BANK_4_PHYS	SA1100_CS4_PHYS

/* Virtual memory regions corresponding to chip selects 2 & 4 (used on sleeves) */
#घोषणा H3600_EGPIO_VIRT	0xf0000000
#घोषणा H3600_BANK_2_VIRT	0xf1000000
#घोषणा H3600_BANK_4_VIRT	0xf3800000

/*
 * gpiolib numbers क्रम all iPAQs
 */
#घोषणा H3XXX_GPIO_PWR_BUTTON		0
#घोषणा H3XXX_GPIO_PCMCIA_CD1		10
#घोषणा H3XXX_GPIO_PCMCIA_IRQ1		11
#घोषणा H3XXX_GPIO_PCMCIA_CD0		17
#घोषणा H3XXX_GPIO_ACTION_BUTTON	18
#घोषणा H3XXX_GPIO_SYS_CLK		19
#घोषणा H3XXX_GPIO_PCMCIA_IRQ0		21
#घोषणा H3XXX_GPIO_COM_DCD		23
#घोषणा H3XXX_GPIO_OPTION		24
#घोषणा H3XXX_GPIO_COM_CTS		25
#घोषणा H3XXX_GPIO_COM_RTS		26

/* machine-specअगरic gpios */

#घोषणा H3100_GPIO_BT_ON		2
#घोषणा H3100_GPIO_QMUTE		4
#घोषणा H3100_GPIO_LCD_3V_ON		5
#घोषणा H3100_GPIO_AUD_ON		6
#घोषणा H3100_GPIO_AUD_PWR_ON		7
#घोषणा H3100_GPIO_IR_ON		8
#घोषणा H3100_GPIO_IR_FSEL		9

#घोषणा H3600_GPIO_CLK_SET0		12	/* audio sample rate घड़ी generator */
#घोषणा H3600_GPIO_CLK_SET1		13
#घोषणा H3600_GPIO_SOFT_RESET		20	/* also known as BATT_FAULT */
#घोषणा H3600_GPIO_OPT_LOCK		22
#घोषणा H3600_GPIO_OPT_DET		27


/* H3100 / 3600 EGPIO pins */
#घोषणा H3XXX_EGPIO_BASE		(GPIO_MAX + 1)

#घोषणा H3XXX_EGPIO_VPP_ON		(H3XXX_EGPIO_BASE + 0)
#घोषणा H3XXX_EGPIO_CARD_RESET		(H3XXX_EGPIO_BASE + 1) /* reset the attached pcmcia/compactflash card.  active high. */
#घोषणा H3XXX_EGPIO_OPT_RESET		(H3XXX_EGPIO_BASE + 2) /* reset the attached option pack.  active high. */
#घोषणा H3XXX_EGPIO_CODEC_NRESET	(H3XXX_EGPIO_BASE + 3) /* reset the onboard UDA1341.  active low. */
#घोषणा H3XXX_EGPIO_OPT_NVRAM_ON	(H3XXX_EGPIO_BASE + 4) /* apply घातer to optionpack nvram, active high. */
#घोषणा H3XXX_EGPIO_OPT_ON		(H3XXX_EGPIO_BASE + 5) /* full घातer to option pack.  active high. */
#घोषणा H3XXX_EGPIO_LCD_ON		(H3XXX_EGPIO_BASE + 6) /* enable 3.3V to LCD.  active high. */
#घोषणा H3XXX_EGPIO_RS232_ON		(H3XXX_EGPIO_BASE + 7) /* UART3 transceiver क्रमce on.  Active high. */

/* H3600 only EGPIO pins */
#घोषणा H3600_EGPIO_LCD_PCI		(H3XXX_EGPIO_BASE + 8) /* LCD control IC enable.  active high. */
#घोषणा H3600_EGPIO_IR_ON		(H3XXX_EGPIO_BASE + 9) /* apply घातer to IR module.  active high. */
#घोषणा H3600_EGPIO_AUD_AMP_ON		(H3XXX_EGPIO_BASE + 10) /* apply घातer to audio घातer amp.  active high. */
#घोषणा H3600_EGPIO_AUD_PWR_ON		(H3XXX_EGPIO_BASE + 11) /* apply घातer to reset of audio circuit.  active high. */
#घोषणा H3600_EGPIO_QMUTE		(H3XXX_EGPIO_BASE + 12) /* mute control क्रम onboard UDA1341.  active high. */
#घोषणा H3600_EGPIO_IR_FSEL		(H3XXX_EGPIO_BASE + 13) /* IR speed select: 1->fast, 0->slow */
#घोषणा H3600_EGPIO_LCD_5V_ON		(H3XXX_EGPIO_BASE + 14) /* enable 5V to LCD. active high. */
#घोषणा H3600_EGPIO_LVDD_ON		(H3XXX_EGPIO_BASE + 15) /* enable 9V and -6.5V to LCD. */

व्योम __init h3xxx_map_io(व्योम);
व्योम __init h3xxx_mach_init(व्योम);

#पूर्ण_अगर /* _INCLUDE_H3XXX_H_ */
