<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#अगर_अघोषित __STMPE_H
#घोषणा __STMPE_H

#समावेश <linux/device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/sपंचांगpe.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/types.h>

बाह्य स्थिर काष्ठा dev_pm_ops sपंचांगpe_dev_pm_ops;

#अगर_घोषित STMPE_DUMP_BYTES
अटल अंतरभूत व्योम sपंचांगpe_dump_bytes(स्थिर अक्षर *str, स्थिर व्योम *buf,
				    माप_प्रकार len)
अणु
	prपूर्णांक_hex_dump_bytes(str, DUMP_PREFIX_OFFSET, buf, len);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम sपंचांगpe_dump_bytes(स्थिर अक्षर *str, स्थिर व्योम *buf,
				    माप_प्रकार len)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा sपंचांगpe_variant_block - inक्रमmation about block
 * @cell:	base mfd cell
 * @irq:	पूर्णांकerrupt number to be added to each IORESOURCE_IRQ
 *		in the cell
 * @block:	block id; used क्रम identअगरication with platक्रमm data and क्रम
 *		enable and altfunc callbacks
 */
काष्ठा sपंचांगpe_variant_block अणु
	स्थिर काष्ठा mfd_cell	*cell;
	पूर्णांक			irq;
	क्रमागत sपंचांगpe_block	block;
पूर्ण;

/**
 * काष्ठा sपंचांगpe_variant_info - variant-specअगरic inक्रमmation
 * @name:	part name
 * @id_val:	content of CHIPID रेजिस्टर
 * @id_mask:	bits valid in CHIPID रेजिस्टर क्रम comparison with id_val
 * @num_gpios:	number of GPIOS
 * @af_bits:	number of bits used to specअगरy the alternate function
 * @regs: variant specअगरic रेजिस्टरs.
 * @blocks:	list of blocks present on this device
 * @num_blocks:	number of blocks present on this device
 * @num_irqs:	number of पूर्णांकernal IRQs available on this device
 * @enable:	callback to enable the specअगरied blocks.
 *		Called with the I/O lock held.
 * @get_altfunc: callback to get the alternate function number क्रम the
 *		 specअगरic block
 * @enable_स्वतःsleep: callback to configure स्वतःsleep with specअगरied समयout
 */
काष्ठा sपंचांगpe_variant_info अणु
	स्थिर अक्षर *name;
	u16 id_val;
	u16 id_mask;
	पूर्णांक num_gpios;
	पूर्णांक af_bits;
	स्थिर u8 *regs;
	काष्ठा sपंचांगpe_variant_block *blocks;
	पूर्णांक num_blocks;
	पूर्णांक num_irqs;
	पूर्णांक (*enable)(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks, bool enable);
	पूर्णांक (*get_altfunc)(काष्ठा sपंचांगpe *sपंचांगpe, क्रमागत sपंचांगpe_block block);
	पूर्णांक (*enable_स्वतःsleep)(काष्ठा sपंचांगpe *sपंचांगpe, पूर्णांक स्वतःsleep_समयout);
पूर्ण;

/**
 * काष्ठा sपंचांगpe_client_info - i2c or spi specअगरic routines/info
 * @data: client specअगरic data
 * @पढ़ो_byte: पढ़ो single byte
 * @ग_लिखो_byte: ग_लिखो single byte
 * @पढ़ो_block: पढ़ो block or multiple bytes
 * @ग_लिखो_block: ग_लिखो block or multiple bytes
 * @init: client init routine, called during probe
 */
काष्ठा sपंचांगpe_client_info अणु
	व्योम *data;
	पूर्णांक irq;
	व्योम *client;
	काष्ठा device *dev;
	पूर्णांक (*पढ़ो_byte)(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg);
	पूर्णांक (*ग_लिखो_byte)(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 val);
	पूर्णांक (*पढ़ो_block)(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 len, u8 *values);
	पूर्णांक (*ग_लिखो_block)(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 len,
			स्थिर u8 *values);
	व्योम (*init)(काष्ठा sपंचांगpe *sपंचांगpe);
पूर्ण;

पूर्णांक sपंचांगpe_probe(काष्ठा sपंचांगpe_client_info *ci, क्रमागत sपंचांगpe_partnum partnum);
पूर्णांक sपंचांगpe_हटाओ(काष्ठा sपंचांगpe *sपंचांगpe);

#घोषणा STMPE_ICR_LSB_HIGH	(1 << 2)
#घोषणा STMPE_ICR_LSB_EDGE	(1 << 1)
#घोषणा STMPE_ICR_LSB_GIM	(1 << 0)

#घोषणा STMPE_SYS_CTRL_RESET	(1 << 7)
#घोषणा STMPE_SYS_CTRL_INT_EN	(1 << 2)
#घोषणा STMPE_SYS_CTRL_INT_HI	(1 << 0)

/*
 * STMPE801
 */
#घोषणा STMPE801_ID			0x0108
#घोषणा STMPE801_NR_INTERNAL_IRQS	1

#घोषणा STMPE801_REG_CHIP_ID		0x00
#घोषणा STMPE801_REG_VERSION_ID		0x02
#घोषणा STMPE801_REG_SYS_CTRL		0x04
#घोषणा STMPE801_REG_GPIO_INT_EN	0x08
#घोषणा STMPE801_REG_GPIO_INT_STA	0x09
#घोषणा STMPE801_REG_GPIO_MP_STA	0x10
#घोषणा STMPE801_REG_GPIO_SET_PIN	0x11
#घोषणा STMPE801_REG_GPIO_सूची		0x12

/*
 * STMPE811
 */
#घोषणा STMPE811_ID			0x0811

#घोषणा STMPE811_IRQ_TOUCH_DET		0
#घोषणा STMPE811_IRQ_FIFO_TH		1
#घोषणा STMPE811_IRQ_FIFO_OFLOW		2
#घोषणा STMPE811_IRQ_FIFO_FULL		3
#घोषणा STMPE811_IRQ_FIFO_EMPTY		4
#घोषणा STMPE811_IRQ_TEMP_SENS		5
#घोषणा STMPE811_IRQ_ADC		6
#घोषणा STMPE811_IRQ_GPIOC		7
#घोषणा STMPE811_NR_INTERNAL_IRQS	8

#घोषणा STMPE811_REG_CHIP_ID		0x00
#घोषणा STMPE811_REG_SYS_CTRL		0x03
#घोषणा STMPE811_REG_SYS_CTRL2		0x04
#घोषणा STMPE811_REG_SPI_CFG		0x08
#घोषणा STMPE811_REG_INT_CTRL		0x09
#घोषणा STMPE811_REG_INT_EN		0x0A
#घोषणा STMPE811_REG_INT_STA		0x0B
#घोषणा STMPE811_REG_GPIO_INT_EN	0x0C
#घोषणा STMPE811_REG_GPIO_INT_STA	0x0D
#घोषणा STMPE811_REG_GPIO_SET_PIN	0x10
#घोषणा STMPE811_REG_GPIO_CLR_PIN	0x11
#घोषणा STMPE811_REG_GPIO_MP_STA	0x12
#घोषणा STMPE811_REG_GPIO_सूची		0x13
#घोषणा STMPE811_REG_GPIO_ED		0x14
#घोषणा STMPE811_REG_GPIO_RE		0x15
#घोषणा STMPE811_REG_GPIO_FE		0x16
#घोषणा STMPE811_REG_GPIO_AF		0x17

#घोषणा STMPE811_SYS_CTRL_RESET		(1 << 1)

#घोषणा STMPE811_SYS_CTRL2_ADC_OFF	(1 << 0)
#घोषणा STMPE811_SYS_CTRL2_TSC_OFF	(1 << 1)
#घोषणा STMPE811_SYS_CTRL2_GPIO_OFF	(1 << 2)
#घोषणा STMPE811_SYS_CTRL2_TS_OFF	(1 << 3)

/*
 * STMPE1600
 */
#घोषणा STMPE1600_ID			0x0016
#घोषणा STMPE1600_NR_INTERNAL_IRQS	16

#घोषणा STMPE1600_REG_CHIP_ID		0x00
#घोषणा STMPE1600_REG_SYS_CTRL		0x03
#घोषणा STMPE1600_REG_IEGPIOR_LSB	0x08
#घोषणा STMPE1600_REG_IEGPIOR_MSB	0x09
#घोषणा STMPE1600_REG_ISGPIOR_LSB	0x0A
#घोषणा STMPE1600_REG_ISGPIOR_MSB	0x0B
#घोषणा STMPE1600_REG_GPMR_LSB		0x10
#घोषणा STMPE1600_REG_GPMR_MSB		0x11
#घोषणा STMPE1600_REG_GPSR_LSB		0x12
#घोषणा STMPE1600_REG_GPSR_MSB		0x13
#घोषणा STMPE1600_REG_GPDR_LSB		0x14
#घोषणा STMPE1600_REG_GPDR_MSB		0x15
#घोषणा STMPE1600_REG_GPPIR_LSB		0x16
#घोषणा STMPE1600_REG_GPPIR_MSB		0x17

/*
 * STMPE1601
 */

#घोषणा STMPE1601_IRQ_GPIOC		8
#घोषणा STMPE1601_IRQ_PWM3		7
#घोषणा STMPE1601_IRQ_PWM2		6
#घोषणा STMPE1601_IRQ_PWM1		5
#घोषणा STMPE1601_IRQ_PWM0		4
#घोषणा STMPE1601_IRQ_KEYPAD_OVER	2
#घोषणा STMPE1601_IRQ_KEYPAD		1
#घोषणा STMPE1601_IRQ_WAKEUP		0
#घोषणा STMPE1601_NR_INTERNAL_IRQS	9

#घोषणा STMPE1601_REG_SYS_CTRL			0x02
#घोषणा STMPE1601_REG_SYS_CTRL2			0x03
#घोषणा STMPE1601_REG_ICR_MSB			0x10
#घोषणा STMPE1601_REG_ICR_LSB			0x11
#घोषणा STMPE1601_REG_IER_MSB			0x12
#घोषणा STMPE1601_REG_IER_LSB			0x13
#घोषणा STMPE1601_REG_ISR_MSB			0x14
#घोषणा STMPE1601_REG_ISR_LSB			0x15
#घोषणा STMPE1601_REG_INT_EN_GPIO_MASK_MSB	0x16
#घोषणा STMPE1601_REG_INT_EN_GPIO_MASK_LSB	0x17
#घोषणा STMPE1601_REG_INT_STA_GPIO_MSB		0x18
#घोषणा STMPE1601_REG_INT_STA_GPIO_LSB		0x19
#घोषणा STMPE1601_REG_CHIP_ID			0x80
#घोषणा STMPE1601_REG_GPIO_SET_MSB		0x82
#घोषणा STMPE1601_REG_GPIO_SET_LSB		0x83
#घोषणा STMPE1601_REG_GPIO_CLR_MSB		0x84
#घोषणा STMPE1601_REG_GPIO_CLR_LSB		0x85
#घोषणा STMPE1601_REG_GPIO_MP_MSB		0x86
#घोषणा STMPE1601_REG_GPIO_MP_LSB		0x87
#घोषणा STMPE1601_REG_GPIO_SET_सूची_MSB		0x88
#घोषणा STMPE1601_REG_GPIO_SET_सूची_LSB		0x89
#घोषणा STMPE1601_REG_GPIO_ED_MSB		0x8A
#घोषणा STMPE1601_REG_GPIO_ED_LSB		0x8B
#घोषणा STMPE1601_REG_GPIO_RE_MSB		0x8C
#घोषणा STMPE1601_REG_GPIO_RE_LSB		0x8D
#घोषणा STMPE1601_REG_GPIO_FE_MSB		0x8E
#घोषणा STMPE1601_REG_GPIO_FE_LSB		0x8F
#घोषणा STMPE1601_REG_GPIO_PU_MSB		0x90
#घोषणा STMPE1601_REG_GPIO_PU_LSB		0x91
#घोषणा STMPE1601_REG_GPIO_AF_U_MSB		0x92

#घोषणा STMPE1601_SYS_CTRL_ENABLE_GPIO		(1 << 3)
#घोषणा STMPE1601_SYS_CTRL_ENABLE_KPC		(1 << 1)
#घोषणा STMPE1601_SYS_CTRL_ENABLE_SPWM		(1 << 0)

/* The 1601/2403 share the same masks */
#घोषणा STMPE1601_AUTOSLEEP_TIMEOUT_MASK	(0x7)
#घोषणा STPME1601_AUTOSLEEP_ENABLE		(1 << 3)

/*
 * STMPE1801
 */
#घोषणा STMPE1801_ID			0xc110
#घोषणा STMPE1801_NR_INTERNAL_IRQS	5
#घोषणा STMPE1801_IRQ_KEYPAD_COMBI	4
#घोषणा STMPE1801_IRQ_GPIOC		3
#घोषणा STMPE1801_IRQ_KEYPAD_OVER	2
#घोषणा STMPE1801_IRQ_KEYPAD		1
#घोषणा STMPE1801_IRQ_WAKEUP		0

#घोषणा STMPE1801_REG_CHIP_ID			0x00
#घोषणा STMPE1801_REG_SYS_CTRL			0x02
#घोषणा STMPE1801_REG_INT_CTRL_LOW		0x04
#घोषणा STMPE1801_REG_INT_EN_MASK_LOW		0x06
#घोषणा STMPE1801_REG_INT_STA_LOW		0x08
#घोषणा STMPE1801_REG_INT_EN_GPIO_MASK_LOW	0x0A
#घोषणा STMPE1801_REG_INT_EN_GPIO_MASK_MID	0x0B
#घोषणा STMPE1801_REG_INT_EN_GPIO_MASK_HIGH	0x0C
#घोषणा STMPE1801_REG_INT_STA_GPIO_LOW		0x0D
#घोषणा STMPE1801_REG_INT_STA_GPIO_MID		0x0E
#घोषणा STMPE1801_REG_INT_STA_GPIO_HIGH		0x0F
#घोषणा STMPE1801_REG_GPIO_SET_LOW		0x10
#घोषणा STMPE1801_REG_GPIO_SET_MID		0x11
#घोषणा STMPE1801_REG_GPIO_SET_HIGH		0x12
#घोषणा STMPE1801_REG_GPIO_CLR_LOW		0x13
#घोषणा STMPE1801_REG_GPIO_CLR_MID		0x14
#घोषणा STMPE1801_REG_GPIO_CLR_HIGH		0x15
#घोषणा STMPE1801_REG_GPIO_MP_LOW		0x16
#घोषणा STMPE1801_REG_GPIO_MP_MID		0x17
#घोषणा STMPE1801_REG_GPIO_MP_HIGH		0x18
#घोषणा STMPE1801_REG_GPIO_SET_सूची_LOW		0x19
#घोषणा STMPE1801_REG_GPIO_SET_सूची_MID		0x1A
#घोषणा STMPE1801_REG_GPIO_SET_सूची_HIGH		0x1B
#घोषणा STMPE1801_REG_GPIO_RE_LOW		0x1C
#घोषणा STMPE1801_REG_GPIO_RE_MID		0x1D
#घोषणा STMPE1801_REG_GPIO_RE_HIGH		0x1E
#घोषणा STMPE1801_REG_GPIO_FE_LOW		0x1F
#घोषणा STMPE1801_REG_GPIO_FE_MID		0x20
#घोषणा STMPE1801_REG_GPIO_FE_HIGH		0x21
#घोषणा STMPE1801_REG_GPIO_PULL_UP_LOW		0x22
#घोषणा STMPE1801_REG_GPIO_PULL_UP_MID		0x23
#घोषणा STMPE1801_REG_GPIO_PULL_UP_HIGH		0x24

#घोषणा STMPE1801_MSK_INT_EN_KPC		(1 << 1)
#घोषणा STMPE1801_MSK_INT_EN_GPIO		(1 << 3)

/*
 * STMPE24xx
 */

#घोषणा STMPE24XX_IRQ_GPIOC		8
#घोषणा STMPE24XX_IRQ_PWM2		7
#घोषणा STMPE24XX_IRQ_PWM1		6
#घोषणा STMPE24XX_IRQ_PWM0		5
#घोषणा STMPE24XX_IRQ_ROT_OVER		4
#घोषणा STMPE24XX_IRQ_ROT		3
#घोषणा STMPE24XX_IRQ_KEYPAD_OVER	2
#घोषणा STMPE24XX_IRQ_KEYPAD		1
#घोषणा STMPE24XX_IRQ_WAKEUP		0
#घोषणा STMPE24XX_NR_INTERNAL_IRQS	9

#घोषणा STMPE24XX_REG_SYS_CTRL		0x02
#घोषणा STMPE24XX_REG_SYS_CTRL2		0x03
#घोषणा STMPE24XX_REG_ICR_MSB		0x10
#घोषणा STMPE24XX_REG_ICR_LSB		0x11
#घोषणा STMPE24XX_REG_IER_MSB		0x12
#घोषणा STMPE24XX_REG_IER_LSB		0x13
#घोषणा STMPE24XX_REG_ISR_MSB		0x14
#घोषणा STMPE24XX_REG_ISR_LSB		0x15
#घोषणा STMPE24XX_REG_IEGPIOR_MSB	0x16
#घोषणा STMPE24XX_REG_IEGPIOR_CSB	0x17
#घोषणा STMPE24XX_REG_IEGPIOR_LSB	0x18
#घोषणा STMPE24XX_REG_ISGPIOR_MSB	0x19
#घोषणा STMPE24XX_REG_ISGPIOR_CSB	0x1A
#घोषणा STMPE24XX_REG_ISGPIOR_LSB	0x1B
#घोषणा STMPE24XX_REG_CHIP_ID		0x80
#घोषणा STMPE24XX_REG_GPSR_MSB		0x83
#घोषणा STMPE24XX_REG_GPSR_CSB		0x84
#घोषणा STMPE24XX_REG_GPSR_LSB		0x85
#घोषणा STMPE24XX_REG_GPCR_MSB		0x86
#घोषणा STMPE24XX_REG_GPCR_CSB		0x87
#घोषणा STMPE24XX_REG_GPCR_LSB		0x88
#घोषणा STMPE24XX_REG_GPDR_MSB		0x89
#घोषणा STMPE24XX_REG_GPDR_CSB		0x8A
#घोषणा STMPE24XX_REG_GPDR_LSB		0x8B
#घोषणा STMPE24XX_REG_GPEDR_MSB		0x8C
#घोषणा STMPE24XX_REG_GPEDR_CSB		0x8D
#घोषणा STMPE24XX_REG_GPEDR_LSB		0x8E
#घोषणा STMPE24XX_REG_GPRER_MSB		0x8F
#घोषणा STMPE24XX_REG_GPRER_CSB		0x90
#घोषणा STMPE24XX_REG_GPRER_LSB		0x91
#घोषणा STMPE24XX_REG_GPFER_MSB		0x92
#घोषणा STMPE24XX_REG_GPFER_CSB		0x93
#घोषणा STMPE24XX_REG_GPFER_LSB		0x94
#घोषणा STMPE24XX_REG_GPPUR_MSB		0x95
#घोषणा STMPE24XX_REG_GPPUR_CSB		0x96
#घोषणा STMPE24XX_REG_GPPUR_LSB		0x97
#घोषणा STMPE24XX_REG_GPPDR_MSB		0x98
#घोषणा STMPE24XX_REG_GPPDR_CSB		0x99
#घोषणा STMPE24XX_REG_GPPDR_LSB		0x9A
#घोषणा STMPE24XX_REG_GPAFR_U_MSB	0x9B
#घोषणा STMPE24XX_REG_GPMR_MSB		0xA2
#घोषणा STMPE24XX_REG_GPMR_CSB		0xA3
#घोषणा STMPE24XX_REG_GPMR_LSB		0xA4
#घोषणा STMPE24XX_SYS_CTRL_ENABLE_GPIO		(1 << 3)
#घोषणा STMPE24XX_SYSCON_ENABLE_PWM		(1 << 2)
#घोषणा STMPE24XX_SYS_CTRL_ENABLE_KPC		(1 << 1)
#घोषणा STMPE24XX_SYSCON_ENABLE_ROT		(1 << 0)

#पूर्ण_अगर
