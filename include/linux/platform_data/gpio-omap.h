<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OMAP GPIO handling defines and functions
 *
 * Copyright (C) 2003-2005 Nokia Corporation
 *
 * Written by Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 */

#अगर_अघोषित __ASM_ARCH_OMAP_GPIO_H
#घोषणा __ASM_ARCH_OMAP_GPIO_H

#अगर_अघोषित __ASSEMBLER__
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#पूर्ण_अगर

#घोषणा OMAP1_MPUIO_BASE			0xfffb5000

/*
 * These are the omap15xx/16xx offsets. The omap7xx offset are
 * OMAP_MPUIO_ / 2 offsets below.
 */
#घोषणा OMAP_MPUIO_INPUT_LATCH		0x00
#घोषणा OMAP_MPUIO_OUTPUT		0x04
#घोषणा OMAP_MPUIO_IO_CNTL		0x08
#घोषणा OMAP_MPUIO_KBR_LATCH		0x10
#घोषणा OMAP_MPUIO_KBC			0x14
#घोषणा OMAP_MPUIO_GPIO_EVENT_MODE	0x18
#घोषणा OMAP_MPUIO_GPIO_INT_EDGE	0x1c
#घोषणा OMAP_MPUIO_KBD_INT		0x20
#घोषणा OMAP_MPUIO_GPIO_INT		0x24
#घोषणा OMAP_MPUIO_KBD_MASKIT		0x28
#घोषणा OMAP_MPUIO_GPIO_MASKIT		0x2c
#घोषणा OMAP_MPUIO_GPIO_DEBOUNCING	0x30
#घोषणा OMAP_MPUIO_LATCH		0x34

#घोषणा OMAP34XX_NR_GPIOS		6

/*
 * OMAP1510 GPIO रेजिस्टरs
 */
#घोषणा OMAP1510_GPIO_DATA_INPUT	0x00
#घोषणा OMAP1510_GPIO_DATA_OUTPUT	0x04
#घोषणा OMAP1510_GPIO_सूची_CONTROL	0x08
#घोषणा OMAP1510_GPIO_INT_CONTROL	0x0c
#घोषणा OMAP1510_GPIO_INT_MASK		0x10
#घोषणा OMAP1510_GPIO_INT_STATUS	0x14
#घोषणा OMAP1510_GPIO_PIN_CONTROL	0x18

#घोषणा OMAP1510_IH_GPIO_BASE		64

/*
 * OMAP1610 specअगरic GPIO रेजिस्टरs
 */
#घोषणा OMAP1610_GPIO_REVISION		0x0000
#घोषणा OMAP1610_GPIO_SYSCONFIG		0x0010
#घोषणा OMAP1610_GPIO_SYSSTATUS		0x0014
#घोषणा OMAP1610_GPIO_IRQSTATUS1	0x0018
#घोषणा OMAP1610_GPIO_IRQENABLE1	0x001c
#घोषणा OMAP1610_GPIO_WAKEUPENABLE	0x0028
#घोषणा OMAP1610_GPIO_DATAIN		0x002c
#घोषणा OMAP1610_GPIO_DATAOUT		0x0030
#घोषणा OMAP1610_GPIO_सूचीECTION		0x0034
#घोषणा OMAP1610_GPIO_EDGE_CTRL1	0x0038
#घोषणा OMAP1610_GPIO_EDGE_CTRL2	0x003c
#घोषणा OMAP1610_GPIO_CLEAR_IRQENABLE1	0x009c
#घोषणा OMAP1610_GPIO_CLEAR_WAKEUPENA	0x00a8
#घोषणा OMAP1610_GPIO_CLEAR_DATAOUT	0x00b0
#घोषणा OMAP1610_GPIO_SET_IRQENABLE1	0x00dc
#घोषणा OMAP1610_GPIO_SET_WAKEUPENA	0x00e8
#घोषणा OMAP1610_GPIO_SET_DATAOUT	0x00f0

/*
 * OMAP7XX specअगरic GPIO रेजिस्टरs
 */
#घोषणा OMAP7XX_GPIO_DATA_INPUT		0x00
#घोषणा OMAP7XX_GPIO_DATA_OUTPUT	0x04
#घोषणा OMAP7XX_GPIO_सूची_CONTROL	0x08
#घोषणा OMAP7XX_GPIO_INT_CONTROL	0x0c
#घोषणा OMAP7XX_GPIO_INT_MASK		0x10
#घोषणा OMAP7XX_GPIO_INT_STATUS		0x14

/*
 * omap2+ specअगरic GPIO रेजिस्टरs
 */
#घोषणा OMAP24XX_GPIO_REVISION		0x0000
#घोषणा OMAP24XX_GPIO_SYSCONFIG		0x0010
#घोषणा OMAP24XX_GPIO_IRQSTATUS1	0x0018
#घोषणा OMAP24XX_GPIO_IRQSTATUS2	0x0028
#घोषणा OMAP24XX_GPIO_IRQENABLE2	0x002c
#घोषणा OMAP24XX_GPIO_IRQENABLE1	0x001c
#घोषणा OMAP24XX_GPIO_WAKE_EN		0x0020
#घोषणा OMAP24XX_GPIO_CTRL		0x0030
#घोषणा OMAP24XX_GPIO_OE		0x0034
#घोषणा OMAP24XX_GPIO_DATAIN		0x0038
#घोषणा OMAP24XX_GPIO_DATAOUT		0x003c
#घोषणा OMAP24XX_GPIO_LEVELDETECT0	0x0040
#घोषणा OMAP24XX_GPIO_LEVELDETECT1	0x0044
#घोषणा OMAP24XX_GPIO_RISINGDETECT	0x0048
#घोषणा OMAP24XX_GPIO_FALLINGDETECT	0x004c
#घोषणा OMAP24XX_GPIO_DEBOUNCE_EN	0x0050
#घोषणा OMAP24XX_GPIO_DEBOUNCE_VAL	0x0054
#घोषणा OMAP24XX_GPIO_CLEARIRQENABLE1	0x0060
#घोषणा OMAP24XX_GPIO_SETIRQENABLE1	0x0064
#घोषणा OMAP24XX_GPIO_CLEARWKUENA	0x0080
#घोषणा OMAP24XX_GPIO_SETWKUENA		0x0084
#घोषणा OMAP24XX_GPIO_CLEARDATAOUT	0x0090
#घोषणा OMAP24XX_GPIO_SETDATAOUT	0x0094

#घोषणा OMAP4_GPIO_REVISION		0x0000
#घोषणा OMAP4_GPIO_SYSCONFIG		0x0010
#घोषणा OMAP4_GPIO_EOI			0x0020
#घोषणा OMAP4_GPIO_IRQSTATUSRAW0	0x0024
#घोषणा OMAP4_GPIO_IRQSTATUSRAW1	0x0028
#घोषणा OMAP4_GPIO_IRQSTATUS0		0x002c
#घोषणा OMAP4_GPIO_IRQSTATUS1		0x0030
#घोषणा OMAP4_GPIO_IRQSTATUSSET0	0x0034
#घोषणा OMAP4_GPIO_IRQSTATUSSET1	0x0038
#घोषणा OMAP4_GPIO_IRQSTATUSCLR0	0x003c
#घोषणा OMAP4_GPIO_IRQSTATUSCLR1	0x0040
#घोषणा OMAP4_GPIO_IRQWAKEN0		0x0044
#घोषणा OMAP4_GPIO_IRQWAKEN1		0x0048
#घोषणा OMAP4_GPIO_IRQENABLE1		0x011c
#घोषणा OMAP4_GPIO_WAKE_EN		0x0120
#घोषणा OMAP4_GPIO_IRQSTATUS2		0x0128
#घोषणा OMAP4_GPIO_IRQENABLE2		0x012c
#घोषणा OMAP4_GPIO_CTRL			0x0130
#घोषणा OMAP4_GPIO_OE			0x0134
#घोषणा OMAP4_GPIO_DATAIN		0x0138
#घोषणा OMAP4_GPIO_DATAOUT		0x013c
#घोषणा OMAP4_GPIO_LEVELDETECT0		0x0140
#घोषणा OMAP4_GPIO_LEVELDETECT1		0x0144
#घोषणा OMAP4_GPIO_RISINGDETECT		0x0148
#घोषणा OMAP4_GPIO_FALLINGDETECT	0x014c
#घोषणा OMAP4_GPIO_DEBOUNCENABLE	0x0150
#घोषणा OMAP4_GPIO_DEBOUNCINGTIME	0x0154
#घोषणा OMAP4_GPIO_CLEARIRQENABLE1	0x0160
#घोषणा OMAP4_GPIO_SETIRQENABLE1	0x0164
#घोषणा OMAP4_GPIO_CLEARWKUENA		0x0180
#घोषणा OMAP4_GPIO_SETWKUENA		0x0184
#घोषणा OMAP4_GPIO_CLEARDATAOUT		0x0190
#घोषणा OMAP4_GPIO_SETDATAOUT		0x0194

#घोषणा OMAP_MAX_GPIO_LINES		192

#घोषणा OMAP_MPUIO(nr)		(OMAP_MAX_GPIO_LINES + (nr))
#घोषणा OMAP_GPIO_IS_MPUIO(nr)	((nr) >= OMAP_MAX_GPIO_LINES)

#अगर_अघोषित __ASSEMBLER__
काष्ठा omap_gpio_reg_offs अणु
	u16 revision;
	u16 sysconfig;
	u16 direction;
	u16 datain;
	u16 dataout;
	u16 set_dataout;
	u16 clr_dataout;
	u16 irqstatus;
	u16 irqstatus2;
	u16 irqstatus_raw0;
	u16 irqstatus_raw1;
	u16 irqenable;
	u16 irqenable2;
	u16 set_irqenable;
	u16 clr_irqenable;
	u16 debounce;
	u16 debounce_en;
	u16 ctrl;
	u16 wkup_en;
	u16 leveldetect0;
	u16 leveldetect1;
	u16 risingdetect;
	u16 fallingdetect;
	u16 irqctrl;
	u16 edgectrl1;
	u16 edgectrl2;
	u16 pinctrl;

	bool irqenable_inv;
पूर्ण;

काष्ठा omap_gpio_platक्रमm_data अणु
	पूर्णांक bank_type;
	पूर्णांक bank_width;		/* GPIO bank width */
	पूर्णांक bank_stride;	/* Only needed क्रम omap1 MPUIO */
	bool dbck_flag;		/* dbck required or not - True क्रम OMAP3&4 */
	bool loses_context;	/* whether the bank would ever lose context */
	bool is_mpuio;		/* whether the bank is of type MPUIO */
	u32 non_wakeup_gpios;

	स्थिर काष्ठा omap_gpio_reg_offs *regs;

	/* Return context loss count due to PM states changing */
	पूर्णांक (*get_context_loss_count)(काष्ठा device *dev);
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLER__ */

#पूर्ण_अगर
