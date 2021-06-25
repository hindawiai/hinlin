<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Core driver पूर्णांकerface to access RICOH_RC5T583 घातer management chip.
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * Based on code
 *      Copyright (C) 2011 RICOH COMPANY,LTD
 */

#अगर_अघोषित __LINUX_MFD_RC5T583_H
#घोषणा __LINUX_MFD_RC5T583_H

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/regmap.h>

/* Maximum number of मुख्य पूर्णांकerrupts */
#घोषणा MAX_MAIN_INTERRUPT		5
#घोषणा RC5T583_MAX_GPEDGE_REG		2
#घोषणा RC5T583_MAX_INTERRUPT_EN_REGS	8
#घोषणा RC5T583_MAX_INTERRUPT_MASK_REGS	9

/* Interrupt enable रेजिस्टर */
#घोषणा RC5T583_INT_EN_SYS1	0x19
#घोषणा RC5T583_INT_EN_SYS2	0x1D
#घोषणा RC5T583_INT_EN_DCDC	0x41
#घोषणा RC5T583_INT_EN_RTC	0xED
#घोषणा RC5T583_INT_EN_ADC1	0x90
#घोषणा RC5T583_INT_EN_ADC2	0x91
#घोषणा RC5T583_INT_EN_ADC3	0x92

/* Interrupt status रेजिस्टरs (monitor regs in Ricoh)*/
#घोषणा RC5T583_INTC_INTPOL	0xAD
#घोषणा RC5T583_INTC_INTEN	0xAE
#घोषणा RC5T583_INTC_INTMON	0xAF

#घोषणा RC5T583_INT_MON_GRP	0xAF
#घोषणा RC5T583_INT_MON_SYS1	0x1B
#घोषणा RC5T583_INT_MON_SYS2	0x1F
#घोषणा RC5T583_INT_MON_DCDC	0x43
#घोषणा RC5T583_INT_MON_RTC	0xEE

/* Interrupt clearing रेजिस्टरs */
#घोषणा RC5T583_INT_IR_SYS1	0x1A
#घोषणा RC5T583_INT_IR_SYS2	0x1E
#घोषणा RC5T583_INT_IR_DCDC	0x42
#घोषणा RC5T583_INT_IR_RTC	0xEE
#घोषणा RC5T583_INT_IR_ADCL	0x94
#घोषणा RC5T583_INT_IR_ADCH	0x95
#घोषणा RC5T583_INT_IR_ADCEND	0x96
#घोषणा RC5T583_INT_IR_GPIOR	0xA9
#घोषणा RC5T583_INT_IR_GPIOF	0xAA

/* Sleep sequence रेजिस्टरs */
#घोषणा RC5T583_SLPSEQ1		0x21
#घोषणा RC5T583_SLPSEQ2		0x22
#घोषणा RC5T583_SLPSEQ3		0x23
#घोषणा RC5T583_SLPSEQ4		0x24
#घोषणा RC5T583_SLPSEQ5		0x25
#घोषणा RC5T583_SLPSEQ6		0x26
#घोषणा RC5T583_SLPSEQ7		0x27
#घोषणा RC5T583_SLPSEQ8		0x28
#घोषणा RC5T583_SLPSEQ9		0x29
#घोषणा RC5T583_SLPSEQ10	0x2A
#घोषणा RC5T583_SLPSEQ11	0x2B

/* Regulator रेजिस्टरs */
#घोषणा RC5T583_REG_DC0CTL	0x30
#घोषणा RC5T583_REG_DC0DAC	0x31
#घोषणा RC5T583_REG_DC0LATCTL	0x32
#घोषणा RC5T583_REG_SR0CTL	0x33

#घोषणा RC5T583_REG_DC1CTL	0x34
#घोषणा RC5T583_REG_DC1DAC	0x35
#घोषणा RC5T583_REG_DC1LATCTL	0x36
#घोषणा RC5T583_REG_SR1CTL	0x37

#घोषणा RC5T583_REG_DC2CTL	0x38
#घोषणा RC5T583_REG_DC2DAC	0x39
#घोषणा RC5T583_REG_DC2LATCTL	0x3A
#घोषणा RC5T583_REG_SR2CTL	0x3B

#घोषणा RC5T583_REG_DC3CTL	0x3C
#घोषणा RC5T583_REG_DC3DAC	0x3D
#घोषणा RC5T583_REG_DC3LATCTL	0x3E
#घोषणा RC5T583_REG_SR3CTL	0x3F


#घोषणा RC5T583_REG_LDOEN1	0x50
#घोषणा RC5T583_REG_LDOEN2	0x51
#घोषणा RC5T583_REG_LDODIS1	0x52
#घोषणा RC5T583_REG_LDODIS2	0x53

#घोषणा RC5T583_REG_LDO0DAC	0x54
#घोषणा RC5T583_REG_LDO1DAC	0x55
#घोषणा RC5T583_REG_LDO2DAC	0x56
#घोषणा RC5T583_REG_LDO3DAC	0x57
#घोषणा RC5T583_REG_LDO4DAC	0x58
#घोषणा RC5T583_REG_LDO5DAC	0x59
#घोषणा RC5T583_REG_LDO6DAC	0x5A
#घोषणा RC5T583_REG_LDO7DAC	0x5B
#घोषणा RC5T583_REG_LDO8DAC	0x5C
#घोषणा RC5T583_REG_LDO9DAC	0x5D

#घोषणा RC5T583_REG_DC0DAC_DS	0x60
#घोषणा RC5T583_REG_DC1DAC_DS	0x61
#घोषणा RC5T583_REG_DC2DAC_DS	0x62
#घोषणा RC5T583_REG_DC3DAC_DS	0x63

#घोषणा RC5T583_REG_LDO0DAC_DS	0x64
#घोषणा RC5T583_REG_LDO1DAC_DS	0x65
#घोषणा RC5T583_REG_LDO2DAC_DS	0x66
#घोषणा RC5T583_REG_LDO3DAC_DS	0x67
#घोषणा RC5T583_REG_LDO4DAC_DS	0x68
#घोषणा RC5T583_REG_LDO5DAC_DS	0x69
#घोषणा RC5T583_REG_LDO6DAC_DS	0x6A
#घोषणा RC5T583_REG_LDO7DAC_DS	0x6B
#घोषणा RC5T583_REG_LDO8DAC_DS	0x6C
#घोषणा RC5T583_REG_LDO9DAC_DS	0x6D

/* GPIO रेजिस्टर base address */
#घोषणा RC5T583_GPIO_IOSEL	0xA0
#घोषणा RC5T583_GPIO_PDEN	0xA1
#घोषणा RC5T583_GPIO_IOOUT	0xA2
#घोषणा RC5T583_GPIO_PGSEL	0xA3
#घोषणा RC5T583_GPIO_GPINV	0xA4
#घोषणा RC5T583_GPIO_GPDEB	0xA5
#घोषणा RC5T583_GPIO_GPEDGE1	0xA6
#घोषणा RC5T583_GPIO_GPEDGE2	0xA7
#घोषणा RC5T583_GPIO_EN_INT	0xA8
#घोषणा RC5T583_GPIO_MON_IOIN	0xAB
#घोषणा RC5T583_GPIO_GPOFUNC	0xAC

/* RTC रेजिस्टरs */
#घोषणा RC5T583_RTC_SEC		0xE0
#घोषणा RC5T583_RTC_MIN		0xE1
#घोषणा RC5T583_RTC_HOUR	0xE2
#घोषणा RC5T583_RTC_WDAY	0xE3
#घोषणा RC5T583_RTC_DAY		0xE4
#घोषणा RC5T583_RTC_MONTH	0xE5
#घोषणा RC5T583_RTC_YEAR	0xE6
#घोषणा RC5T583_RTC_ADJ		0xE7
#घोषणा RC5T583_RTC_AW_MIN	0xE8
#घोषणा RC5T583_RTC_AW_HOUR	0xE9
#घोषणा RC5T583_RTC_AW_WEEK	0xEA
#घोषणा RC5T583_RTC_AD_MIN	0xEB
#घोषणा RC5T583_RTC_AD_HOUR	0xEC
#घोषणा RC5T583_RTC_CTL1	0xED
#घोषणा RC5T583_RTC_CTL2	0xEE
#घोषणा RC5T583_RTC_AY_MIN	0xF0
#घोषणा RC5T583_RTC_AY_HOUR	0xF1
#घोषणा RC5T583_RTC_AY_DAY	0xF2
#घोषणा RC5T583_RTC_AY_MONTH 0xF3
#घोषणा RC5T583_RTC_AY_YEAR	0xF4

#घोषणा RC5T583_MAX_REG		0xF7
#घोषणा RC5T583_NUM_REGS	(RC5T583_MAX_REG + 1)

/* RICOH_RC5T583 IRQ definitions */
क्रमागत अणु
	RC5T583_IRQ_ONKEY,
	RC5T583_IRQ_ACOK,
	RC5T583_IRQ_LIDOPEN,
	RC5T583_IRQ_PREOT,
	RC5T583_IRQ_CLKSTP,
	RC5T583_IRQ_ONKEY_OFF,
	RC5T583_IRQ_WD,
	RC5T583_IRQ_EN_PWRREQ1,
	RC5T583_IRQ_EN_PWRREQ2,
	RC5T583_IRQ_PRE_VINDET,

	RC5T583_IRQ_DC0LIM,
	RC5T583_IRQ_DC1LIM,
	RC5T583_IRQ_DC2LIM,
	RC5T583_IRQ_DC3LIM,

	RC5T583_IRQ_CTC,
	RC5T583_IRQ_YALE,
	RC5T583_IRQ_DALE,
	RC5T583_IRQ_WALE,

	RC5T583_IRQ_AIN1L,
	RC5T583_IRQ_AIN2L,
	RC5T583_IRQ_AIN3L,
	RC5T583_IRQ_VBATL,
	RC5T583_IRQ_VIN3L,
	RC5T583_IRQ_VIN8L,
	RC5T583_IRQ_AIN1H,
	RC5T583_IRQ_AIN2H,
	RC5T583_IRQ_AIN3H,
	RC5T583_IRQ_VBATH,
	RC5T583_IRQ_VIN3H,
	RC5T583_IRQ_VIN8H,
	RC5T583_IRQ_ADCEND,

	RC5T583_IRQ_GPIO0,
	RC5T583_IRQ_GPIO1,
	RC5T583_IRQ_GPIO2,
	RC5T583_IRQ_GPIO3,
	RC5T583_IRQ_GPIO4,
	RC5T583_IRQ_GPIO5,
	RC5T583_IRQ_GPIO6,
	RC5T583_IRQ_GPIO7,

	/* Should be last entry */
	RC5T583_MAX_IRQS,
पूर्ण;

/* Ricoh583 gpio definitions */
क्रमागत अणु
	RC5T583_GPIO0,
	RC5T583_GPIO1,
	RC5T583_GPIO2,
	RC5T583_GPIO3,
	RC5T583_GPIO4,
	RC5T583_GPIO5,
	RC5T583_GPIO6,
	RC5T583_GPIO7,

	/* Should be last entry */
	RC5T583_MAX_GPIO,
पूर्ण;

क्रमागत अणु
	RC5T583_DS_NONE,
	RC5T583_DS_DC0,
	RC5T583_DS_DC1,
	RC5T583_DS_DC2,
	RC5T583_DS_DC3,
	RC5T583_DS_LDO0,
	RC5T583_DS_LDO1,
	RC5T583_DS_LDO2,
	RC5T583_DS_LDO3,
	RC5T583_DS_LDO4,
	RC5T583_DS_LDO5,
	RC5T583_DS_LDO6,
	RC5T583_DS_LDO7,
	RC5T583_DS_LDO8,
	RC5T583_DS_LDO9,
	RC5T583_DS_PSO0,
	RC5T583_DS_PSO1,
	RC5T583_DS_PSO2,
	RC5T583_DS_PSO3,
	RC5T583_DS_PSO4,
	RC5T583_DS_PSO5,
	RC5T583_DS_PSO6,
	RC5T583_DS_PSO7,

	/* Should be last entry */
	RC5T583_DS_MAX,
पूर्ण;

/*
 * Ricoh pmic RC5T583 supports sleep through two बाह्यal controls.
 * The output of gpios and regulator can be enable/disable through
 * this बाह्यal संकेतs.
 */
क्रमागत अणु
	RC5T583_EXT_PWRREQ1_CONTROL = 0x1,
	RC5T583_EXT_PWRREQ2_CONTROL = 0x2,
पूर्ण;

क्रमागत अणु
	RC5T583_REGULATOR_DC0,
	RC5T583_REGULATOR_DC1,
	RC5T583_REGULATOR_DC2,
	RC5T583_REGULATOR_DC3,
	RC5T583_REGULATOR_LDO0,
	RC5T583_REGULATOR_LDO1,
	RC5T583_REGULATOR_LDO2,
	RC5T583_REGULATOR_LDO3,
	RC5T583_REGULATOR_LDO4,
	RC5T583_REGULATOR_LDO5,
	RC5T583_REGULATOR_LDO6,
	RC5T583_REGULATOR_LDO7,
	RC5T583_REGULATOR_LDO8,
	RC5T583_REGULATOR_LDO9,

	/* Should be last entry */
	RC5T583_REGULATOR_MAX,
पूर्ण;

काष्ठा rc5t583 अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*regmap;
	पूर्णांक		chip_irq;
	पूर्णांक		irq_base;
	काष्ठा mutex	irq_lock;
	अचिन्हित दीर्घ	group_irq_en[MAX_MAIN_INTERRUPT];

	/* For मुख्य पूर्णांकerrupt bits in INTC */
	uपूर्णांक8_t		पूर्णांकc_पूर्णांकen_reg;

	/* For group पूर्णांकerrupt bits and address */
	uपूर्णांक8_t		irq_en_reg[RC5T583_MAX_INTERRUPT_EN_REGS];

	/* For gpio edge */
	uपूर्णांक8_t		gpedge_reg[RC5T583_MAX_GPEDGE_REG];
पूर्ण;

/*
 * rc5t583_platक्रमm_data: Platक्रमm data क्रम ricoh rc5t583 pmu.
 * The board specअगरic data is provided through this काष्ठाure.
 * @irq_base: Irq base number on which this device रेजिस्टरs their पूर्णांकerrupts.
 * @gpio_base: GPIO base from which gpio of this device will start.
 * @enable_shutकरोwn: Enable shutकरोwn through the input pin "shutdown".
 * @regulator_deepsleep_slot: The slot number on which device goes to sleep
 *		in device sleep mode.
 * @regulator_ext_pwr_control: External घातer request regulator control. The
 *		regulator output enable/disable is controlled by the बाह्यal
 *		घातer request input state.
 * @reg_init_data: Regulator init data.
 */

काष्ठा rc5t583_platक्रमm_data अणु
	पूर्णांक		irq_base;
	पूर्णांक		gpio_base;
	bool		enable_shutकरोwn;
	पूर्णांक		regulator_deepsleep_slot[RC5T583_REGULATOR_MAX];
	अचिन्हित दीर्घ	regulator_ext_pwr_control[RC5T583_REGULATOR_MAX];
	काष्ठा regulator_init_data *reg_init_data[RC5T583_REGULATOR_MAX];
पूर्ण;

अटल अंतरभूत पूर्णांक rc5t583_ग_लिखो(काष्ठा device *dev, uपूर्णांक8_t reg, uपूर्णांक8_t val)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev);
	वापस regmap_ग_लिखो(rc5t583->regmap, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक rc5t583_पढ़ो(काष्ठा device *dev, uपूर्णांक8_t reg, uपूर्णांक8_t *val)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ival;
	पूर्णांक ret;
	ret = regmap_पढ़ो(rc5t583->regmap, reg, &ival);
	अगर (!ret)
		*val = (uपूर्णांक8_t)ival;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rc5t583_set_bits(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक bit_mask)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev);
	वापस regmap_update_bits(rc5t583->regmap, reg, bit_mask, bit_mask);
पूर्ण

अटल अंतरभूत पूर्णांक rc5t583_clear_bits(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक bit_mask)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev);
	वापस regmap_update_bits(rc5t583->regmap, reg, bit_mask, 0);
पूर्ण

अटल अंतरभूत पूर्णांक rc5t583_update(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev);
	वापस regmap_update_bits(rc5t583->regmap, reg, mask, val);
पूर्ण

पूर्णांक rc5t583_ext_घातer_req_config(काष्ठा device *dev, पूर्णांक deepsleep_id,
	पूर्णांक ext_pwr_req, पूर्णांक deepsleep_slot_nr);
पूर्णांक rc5t583_irq_init(काष्ठा rc5t583 *rc5t583, पूर्णांक irq, पूर्णांक irq_base);
पूर्णांक rc5t583_irq_निकास(काष्ठा rc5t583 *rc5t583);

#पूर्ण_अगर
