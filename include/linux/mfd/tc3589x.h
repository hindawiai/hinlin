<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 */

#अगर_अघोषित __LINUX_MFD_TC3589x_H
#घोषणा __LINUX_MFD_TC3589x_H

काष्ठा device;

क्रमागत tx3589x_block अणु
	TC3589x_BLOCK_GPIO        = 1 << 0,
	TC3589x_BLOCK_KEYPAD      = 1 << 1,
पूर्ण;

#घोषणा TC3589x_RSTCTRL_IRQRST	(1 << 4)
#घोषणा TC3589x_RSTCTRL_TIMRST	(1 << 3)
#घोषणा TC3589x_RSTCTRL_ROTRST	(1 << 2)
#घोषणा TC3589x_RSTCTRL_KBDRST	(1 << 1)
#घोषणा TC3589x_RSTCTRL_GPIRST	(1 << 0)

#घोषणा TC3589x_DKBDMSK_ELINT	(1 << 1)
#घोषणा TC3589x_DKBDMSK_EINT	(1 << 0)

/* Keyboard Configuration Registers */
#घोषणा TC3589x_KBDSETTLE_REG   0x01
#घोषणा TC3589x_KBDBOUNCE       0x02
#घोषणा TC3589x_KBDSIZE         0x03
#घोषणा TC3589x_KBCFG_LSB       0x04
#घोषणा TC3589x_KBCFG_MSB       0x05
#घोषणा TC3589x_KBDIC           0x08
#घोषणा TC3589x_KBDMSK          0x09
#घोषणा TC3589x_EVTCODE_FIFO    0x10
#घोषणा TC3589x_KBDMFS		0x8F

#घोषणा TC3589x_IRQST		0x91

#घोषणा TC3589x_MANFCODE_MAGIC	0x03
#घोषणा TC3589x_MANFCODE	0x80
#घोषणा TC3589x_VERSION		0x81
#घोषणा TC3589x_IOCFG		0xA7

#घोषणा TC3589x_CLKMODE		0x88
#घोषणा TC3589x_CLKCFG		0x89
#घोषणा TC3589x_CLKEN		0x8A

#घोषणा TC3589x_RSTCTRL		0x82
#घोषणा TC3589x_EXTRSTN		0x83
#घोषणा TC3589x_RSTINTCLR	0x84

/* Pull up/करोwn configuration रेजिस्टरs */
#घोषणा TC3589x_IOCFG           0xA7
#घोषणा TC3589x_IOPULLCFG0_LSB  0xAA
#घोषणा TC3589x_IOPULLCFG0_MSB  0xAB
#घोषणा TC3589x_IOPULLCFG1_LSB  0xAC
#घोषणा TC3589x_IOPULLCFG1_MSB  0xAD
#घोषणा TC3589x_IOPULLCFG2_LSB  0xAE

#घोषणा TC3589x_GPIOIS0		0xC9
#घोषणा TC3589x_GPIOIS1		0xCA
#घोषणा TC3589x_GPIOIS2		0xCB
#घोषणा TC3589x_GPIOIBE0	0xCC
#घोषणा TC3589x_GPIOIBE1	0xCD
#घोषणा TC3589x_GPIOIBE2	0xCE
#घोषणा TC3589x_GPIOIEV0	0xCF
#घोषणा TC3589x_GPIOIEV1	0xD0
#घोषणा TC3589x_GPIOIEV2	0xD1
#घोषणा TC3589x_GPIOIE0		0xD2
#घोषणा TC3589x_GPIOIE1		0xD3
#घोषणा TC3589x_GPIOIE2		0xD4
#घोषणा TC3589x_GPIORIS0	0xD6
#घोषणा TC3589x_GPIORIS1	0xD7
#घोषणा TC3589x_GPIORIS2	0xD8
#घोषणा TC3589x_GPIOMIS0	0xD9
#घोषणा TC3589x_GPIOMIS1	0xDA
#घोषणा TC3589x_GPIOMIS2	0xDB
#घोषणा TC3589x_GPIOIC0		0xDC
#घोषणा TC3589x_GPIOIC1		0xDD
#घोषणा TC3589x_GPIOIC2		0xDE

#घोषणा TC3589x_GPIODATA0	0xC0
#घोषणा TC3589x_GPIOMASK0	0xc1
#घोषणा TC3589x_GPIODATA1	0xC2
#घोषणा TC3589x_GPIOMASK1	0xc3
#घोषणा TC3589x_GPIODATA2	0xC4
#घोषणा TC3589x_GPIOMASK2	0xC5

#घोषणा TC3589x_GPIOसूची0	0xC6
#घोषणा TC3589x_GPIOसूची1	0xC7
#घोषणा TC3589x_GPIOसूची2	0xC8

#घोषणा TC3589x_GPIOSYNC0	0xE6
#घोषणा TC3589x_GPIOSYNC1	0xE7
#घोषणा TC3589x_GPIOSYNC2	0xE8

#घोषणा TC3589x_GPIOWAKE0	0xE9
#घोषणा TC3589x_GPIOWAKE1	0xEA
#घोषणा TC3589x_GPIOWAKE2	0xEB

#घोषणा TC3589x_GPIOODM0	0xE0
#घोषणा TC3589x_GPIOODE0	0xE1
#घोषणा TC3589x_GPIOODM1	0xE2
#घोषणा TC3589x_GPIOODE1	0xE3
#घोषणा TC3589x_GPIOODM2	0xE4
#घोषणा TC3589x_GPIOODE2	0xE5

#घोषणा TC3589x_सूचीECT0		0xEC
#घोषणा TC3589x_DKBDMSK		0xF3

#घोषणा TC3589x_INT_GPIIRQ	0
#घोषणा TC3589x_INT_TI0IRQ	1
#घोषणा TC3589x_INT_TI1IRQ	2
#घोषणा TC3589x_INT_TI2IRQ	3
#घोषणा TC3589x_INT_ROTIRQ	5
#घोषणा TC3589x_INT_KBसूचीQ	6
#घोषणा TC3589x_INT_PORIRQ	7

#घोषणा TC3589x_NR_INTERNAL_IRQS	8

काष्ठा tc3589x अणु
	काष्ठा mutex lock;
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	पूर्णांक irq_base;
	पूर्णांक num_gpio;
	काष्ठा tc3589x_platक्रमm_data *pdata;
पूर्ण;

बाह्य पूर्णांक tc3589x_reg_ग_लिखो(काष्ठा tc3589x *tc3589x, u8 reg, u8 data);
बाह्य पूर्णांक tc3589x_reg_पढ़ो(काष्ठा tc3589x *tc3589x, u8 reg);
बाह्य पूर्णांक tc3589x_block_पढ़ो(काष्ठा tc3589x *tc3589x, u8 reg, u8 length,
			      u8 *values);
बाह्य पूर्णांक tc3589x_block_ग_लिखो(काष्ठा tc3589x *tc3589x, u8 reg, u8 length,
			       स्थिर u8 *values);
बाह्य पूर्णांक tc3589x_set_bits(काष्ठा tc3589x *tc3589x, u8 reg, u8 mask, u8 val);

/*
 * Keypad related platक्रमm specअगरic स्थिरants
 * These values may be modअगरied क्रम fine tuning
 */
#घोषणा TC_KPD_ROWS             0x8
#घोषणा TC_KPD_COLUMNS          0x8
#घोषणा TC_KPD_DEBOUNCE_PERIOD  0xA3
#घोषणा TC_KPD_SETTLE_TIME      0xA3


/**
 * काष्ठा tc3589x_platक्रमm_data - TC3589x platक्रमm data
 * @block: biपंचांगask of blocks to enable (use TC3589x_BLOCK_*)
 */
काष्ठा tc3589x_platक्रमm_data अणु
	अचिन्हित पूर्णांक block;
पूर्ण;

#पूर्ण_अगर
