<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Interrupt driver क्रम RICOH583 घातer management chip.
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * based on code
 *      Copyright (C) 2011 RICOH COMPANY,LTD
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/rc5t583.h>

क्रमागत पूर्णांक_type अणु
	SYS_INT  = 0x1,
	DCDC_INT = 0x2,
	RTC_INT  = 0x4,
	ADC_INT  = 0x8,
	GPIO_INT = 0x10,
पूर्ण;

अटल पूर्णांक gpedge_add[] = अणु
	RC5T583_GPIO_GPEDGE2,
	RC5T583_GPIO_GPEDGE2
पूर्ण;

अटल पूर्णांक irq_en_add[] = अणु
	RC5T583_INT_EN_SYS1,
	RC5T583_INT_EN_SYS2,
	RC5T583_INT_EN_DCDC,
	RC5T583_INT_EN_RTC,
	RC5T583_INT_EN_ADC1,
	RC5T583_INT_EN_ADC2,
	RC5T583_INT_EN_ADC3,
	RC5T583_GPIO_EN_INT
पूर्ण;

अटल पूर्णांक irq_mon_add[] = अणु
	RC5T583_INT_MON_SYS1,
	RC5T583_INT_MON_SYS2,
	RC5T583_INT_MON_DCDC,
	RC5T583_INT_MON_RTC,
	RC5T583_INT_IR_ADCL,
	RC5T583_INT_IR_ADCH,
	RC5T583_INT_IR_ADCEND,
	RC5T583_INT_IR_GPIOF,
	RC5T583_INT_IR_GPIOR
पूर्ण;

अटल पूर्णांक irq_clr_add[] = अणु
	RC5T583_INT_IR_SYS1,
	RC5T583_INT_IR_SYS2,
	RC5T583_INT_IR_DCDC,
	RC5T583_INT_IR_RTC,
	RC5T583_INT_IR_ADCL,
	RC5T583_INT_IR_ADCH,
	RC5T583_INT_IR_ADCEND,
	RC5T583_INT_IR_GPIOF,
	RC5T583_INT_IR_GPIOR
पूर्ण;

अटल पूर्णांक मुख्य_पूर्णांक_type[] = अणु
	SYS_INT,
	SYS_INT,
	DCDC_INT,
	RTC_INT,
	ADC_INT,
	ADC_INT,
	ADC_INT,
	GPIO_INT,
	GPIO_INT,
पूर्ण;

काष्ठा rc5t583_irq_data अणु
	u8	पूर्णांक_type;
	u8	master_bit;
	u8	पूर्णांक_en_bit;
	u8	mask_reg_index;
	पूर्णांक	grp_index;
पूर्ण;

#घोषणा RC5T583_IRQ(_पूर्णांक_type, _master_bit, _grp_index, \
			_पूर्णांक_bit, _mask_ind)		\
	अणु						\
		.पूर्णांक_type	= _पूर्णांक_type,		\
		.master_bit	= _master_bit,		\
		.grp_index	= _grp_index,		\
		.पूर्णांक_en_bit	= _पूर्णांक_bit,		\
		.mask_reg_index	= _mask_ind,		\
	पूर्ण

अटल स्थिर काष्ठा rc5t583_irq_data rc5t583_irqs[RC5T583_MAX_IRQS] = अणु
	[RC5T583_IRQ_ONKEY]		= RC5T583_IRQ(SYS_INT,  0, 0, 0, 0),
	[RC5T583_IRQ_ACOK]		= RC5T583_IRQ(SYS_INT,  0, 1, 1, 0),
	[RC5T583_IRQ_LIDOPEN]		= RC5T583_IRQ(SYS_INT,  0, 2, 2, 0),
	[RC5T583_IRQ_PREOT]		= RC5T583_IRQ(SYS_INT,  0, 3, 3, 0),
	[RC5T583_IRQ_CLKSTP]		= RC5T583_IRQ(SYS_INT,  0, 4, 4, 0),
	[RC5T583_IRQ_ONKEY_OFF]		= RC5T583_IRQ(SYS_INT,  0, 5, 5, 0),
	[RC5T583_IRQ_WD]		= RC5T583_IRQ(SYS_INT,  0, 7, 7, 0),
	[RC5T583_IRQ_EN_PWRREQ1]	= RC5T583_IRQ(SYS_INT,  0, 8, 0, 1),
	[RC5T583_IRQ_EN_PWRREQ2]	= RC5T583_IRQ(SYS_INT,  0, 9, 1, 1),
	[RC5T583_IRQ_PRE_VINDET]	= RC5T583_IRQ(SYS_INT,  0, 10, 2, 1),

	[RC5T583_IRQ_DC0LIM]		= RC5T583_IRQ(DCDC_INT, 1, 0, 0, 2),
	[RC5T583_IRQ_DC1LIM]		= RC5T583_IRQ(DCDC_INT, 1, 1, 1, 2),
	[RC5T583_IRQ_DC2LIM]		= RC5T583_IRQ(DCDC_INT, 1, 2, 2, 2),
	[RC5T583_IRQ_DC3LIM]		= RC5T583_IRQ(DCDC_INT, 1, 3, 3, 2),

	[RC5T583_IRQ_CTC]		= RC5T583_IRQ(RTC_INT,  2, 0, 0, 3),
	[RC5T583_IRQ_YALE]		= RC5T583_IRQ(RTC_INT,  2, 5, 5, 3),
	[RC5T583_IRQ_DALE]		= RC5T583_IRQ(RTC_INT,  2, 6, 6, 3),
	[RC5T583_IRQ_WALE]		= RC5T583_IRQ(RTC_INT,  2, 7, 7, 3),

	[RC5T583_IRQ_AIN1L]		= RC5T583_IRQ(ADC_INT,  3, 0, 0, 4),
	[RC5T583_IRQ_AIN2L]		= RC5T583_IRQ(ADC_INT,  3, 1, 1, 4),
	[RC5T583_IRQ_AIN3L]		= RC5T583_IRQ(ADC_INT,  3, 2, 2, 4),
	[RC5T583_IRQ_VBATL]		= RC5T583_IRQ(ADC_INT,  3, 3, 3, 4),
	[RC5T583_IRQ_VIN3L]		= RC5T583_IRQ(ADC_INT,  3, 4, 4, 4),
	[RC5T583_IRQ_VIN8L]		= RC5T583_IRQ(ADC_INT,  3, 5, 5, 4),
	[RC5T583_IRQ_AIN1H]		= RC5T583_IRQ(ADC_INT,  3, 6, 0, 5),
	[RC5T583_IRQ_AIN2H]		= RC5T583_IRQ(ADC_INT,  3, 7, 1, 5),
	[RC5T583_IRQ_AIN3H]		= RC5T583_IRQ(ADC_INT,  3, 8, 2, 5),
	[RC5T583_IRQ_VBATH]		= RC5T583_IRQ(ADC_INT,  3, 9, 3, 5),
	[RC5T583_IRQ_VIN3H]		= RC5T583_IRQ(ADC_INT,  3, 10, 4, 5),
	[RC5T583_IRQ_VIN8H]		= RC5T583_IRQ(ADC_INT,  3, 11, 5, 5),
	[RC5T583_IRQ_ADCEND]		= RC5T583_IRQ(ADC_INT,  3, 12, 0, 6),

	[RC5T583_IRQ_GPIO0]		= RC5T583_IRQ(GPIO_INT, 4, 0, 0, 7),
	[RC5T583_IRQ_GPIO1]		= RC5T583_IRQ(GPIO_INT, 4, 1, 1, 7),
	[RC5T583_IRQ_GPIO2]		= RC5T583_IRQ(GPIO_INT, 4, 2, 2, 7),
	[RC5T583_IRQ_GPIO3]		= RC5T583_IRQ(GPIO_INT, 4, 3, 3, 7),
	[RC5T583_IRQ_GPIO4]		= RC5T583_IRQ(GPIO_INT, 4, 4, 4, 7),
	[RC5T583_IRQ_GPIO5]		= RC5T583_IRQ(GPIO_INT, 4, 5, 5, 7),
	[RC5T583_IRQ_GPIO6]		= RC5T583_IRQ(GPIO_INT, 4, 6, 6, 7),
	[RC5T583_IRQ_GPIO7]		= RC5T583_IRQ(GPIO_INT, 4, 7, 7, 7),
पूर्ण;

अटल व्योम rc5t583_irq_lock(काष्ठा irq_data *irq_data)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	mutex_lock(&rc5t583->irq_lock);
पूर्ण

अटल व्योम rc5t583_irq_unmask(काष्ठा irq_data *irq_data)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	अचिन्हित पूर्णांक __irq = irq_data->irq - rc5t583->irq_base;
	स्थिर काष्ठा rc5t583_irq_data *data = &rc5t583_irqs[__irq];

	rc5t583->group_irq_en[data->grp_index] |= 1 << data->grp_index;
	rc5t583->पूर्णांकc_पूर्णांकen_reg |= 1 << data->master_bit;
	rc5t583->irq_en_reg[data->mask_reg_index] |= 1 << data->पूर्णांक_en_bit;
पूर्ण

अटल व्योम rc5t583_irq_mask(काष्ठा irq_data *irq_data)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	अचिन्हित पूर्णांक __irq = irq_data->irq - rc5t583->irq_base;
	स्थिर काष्ठा rc5t583_irq_data *data = &rc5t583_irqs[__irq];

	rc5t583->group_irq_en[data->grp_index] &= ~(1 << data->grp_index);
	अगर (!rc5t583->group_irq_en[data->grp_index])
		rc5t583->पूर्णांकc_पूर्णांकen_reg &= ~(1 << data->master_bit);

	rc5t583->irq_en_reg[data->mask_reg_index] &= ~(1 << data->पूर्णांक_en_bit);
पूर्ण

अटल पूर्णांक rc5t583_irq_set_type(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	अचिन्हित पूर्णांक __irq = irq_data->irq - rc5t583->irq_base;
	स्थिर काष्ठा rc5t583_irq_data *data = &rc5t583_irqs[__irq];
	पूर्णांक val = 0;
	पूर्णांक gpedge_index;
	पूर्णांक gpedge_bit_pos;

	/* Supporting only trigger level inetrrupt */
	अगर ((data->पूर्णांक_type & GPIO_INT) && (type & IRQ_TYPE_EDGE_BOTH)) अणु
		gpedge_index = data->पूर्णांक_en_bit / 4;
		gpedge_bit_pos = data->पूर्णांक_en_bit % 4;

		अगर (type & IRQ_TYPE_EDGE_FALLING)
			val |= 0x2;

		अगर (type & IRQ_TYPE_EDGE_RISING)
			val |= 0x1;

		rc5t583->gpedge_reg[gpedge_index] &= ~(3 << gpedge_bit_pos);
		rc5t583->gpedge_reg[gpedge_index] |= (val << gpedge_bit_pos);
		rc5t583_irq_unmask(irq_data);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम rc5t583_irq_sync_unlock(काष्ठा irq_data *irq_data)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(rc5t583->gpedge_reg); i++) अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, gpedge_add[i],
				rc5t583->gpedge_reg[i]);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				gpedge_add[i], ret);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rc5t583->irq_en_reg); i++) अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, irq_en_add[i],
					rc5t583->irq_en_reg[i]);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				irq_en_add[i], ret);
	पूर्ण

	ret = rc5t583_ग_लिखो(rc5t583->dev, RC5T583_INTC_INTEN,
				rc5t583->पूर्णांकc_पूर्णांकen_reg);
	अगर (ret < 0)
		dev_warn(rc5t583->dev,
			"Error in writing reg 0x%02x error: %d\n",
			RC5T583_INTC_INTEN, ret);

	mutex_unlock(&rc5t583->irq_lock);
पूर्ण
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rc5t583_irq_set_wake(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा rc5t583 *rc5t583 = irq_data_get_irq_chip_data(irq_data);
	वापस irq_set_irq_wake(rc5t583->chip_irq, on);
पूर्ण
#अन्यथा
#घोषणा rc5t583_irq_set_wake शून्य
#पूर्ण_अगर

अटल irqवापस_t rc5t583_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rc5t583 *rc5t583 = data;
	uपूर्णांक8_t पूर्णांक_sts[RC5T583_MAX_INTERRUPT_MASK_REGS];
	uपूर्णांक8_t master_पूर्णांक = 0;
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक rtc_पूर्णांक_sts = 0;

	/* Clear the status */
	क्रम (i = 0; i < RC5T583_MAX_INTERRUPT_MASK_REGS; i++)
		पूर्णांक_sts[i] = 0;

	ret  = rc5t583_पढ़ो(rc5t583->dev, RC5T583_INTC_INTMON, &master_पूर्णांक);
	अगर (ret < 0) अणु
		dev_err(rc5t583->dev,
			"Error in reading reg 0x%02x error: %d\n",
			RC5T583_INTC_INTMON, ret);
		वापस IRQ_HANDLED;
	पूर्ण

	क्रम (i = 0; i < RC5T583_MAX_INTERRUPT_MASK_REGS; ++i) अणु
		अगर (!(master_पूर्णांक & मुख्य_पूर्णांक_type[i]))
			जारी;

		ret = rc5t583_पढ़ो(rc5t583->dev, irq_mon_add[i], &पूर्णांक_sts[i]);
		अगर (ret < 0) अणु
			dev_warn(rc5t583->dev,
				"Error in reading reg 0x%02x error: %d\n",
				irq_mon_add[i], ret);
			पूर्णांक_sts[i] = 0;
			जारी;
		पूर्ण

		अगर (मुख्य_पूर्णांक_type[i] & RTC_INT) अणु
			rtc_पूर्णांक_sts = 0;
			अगर (पूर्णांक_sts[i] & 0x1)
				rtc_पूर्णांक_sts |= BIT(6);
			अगर (पूर्णांक_sts[i] & 0x2)
				rtc_पूर्णांक_sts |= BIT(7);
			अगर (पूर्णांक_sts[i] & 0x4)
				rtc_पूर्णांक_sts |= BIT(0);
			अगर (पूर्णांक_sts[i] & 0x8)
				rtc_पूर्णांक_sts |= BIT(5);
		पूर्ण

		ret = rc5t583_ग_लिखो(rc5t583->dev, irq_clr_add[i],
				~पूर्णांक_sts[i]);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in reading reg 0x%02x error: %d\n",
				irq_clr_add[i], ret);

		अगर (मुख्य_पूर्णांक_type[i] & RTC_INT)
			पूर्णांक_sts[i] = rtc_पूर्णांक_sts;
	पूर्ण

	/* Merge gpio पूर्णांकerrupts क्रम rising and falling हाल*/
	पूर्णांक_sts[7] |= पूर्णांक_sts[8];

	/* Call पूर्णांकerrupt handler अगर enabled */
	क्रम (i = 0; i < RC5T583_MAX_IRQS; ++i) अणु
		स्थिर काष्ठा rc5t583_irq_data *data = &rc5t583_irqs[i];
		अगर ((पूर्णांक_sts[data->mask_reg_index] & (1 << data->पूर्णांक_en_bit)) &&
			(rc5t583->group_irq_en[data->master_bit] &
					(1 << data->grp_index)))
			handle_nested_irq(rc5t583->irq_base + i);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा irq_chip rc5t583_irq_chip = अणु
	.name = "rc5t583-irq",
	.irq_mask = rc5t583_irq_mask,
	.irq_unmask = rc5t583_irq_unmask,
	.irq_bus_lock = rc5t583_irq_lock,
	.irq_bus_sync_unlock = rc5t583_irq_sync_unlock,
	.irq_set_type = rc5t583_irq_set_type,
	.irq_set_wake = rc5t583_irq_set_wake,
पूर्ण;

पूर्णांक rc5t583_irq_init(काष्ठा rc5t583 *rc5t583, पूर्णांक irq, पूर्णांक irq_base)
अणु
	पूर्णांक i, ret;

	अगर (!irq_base) अणु
		dev_warn(rc5t583->dev, "No interrupt support on IRQ base\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&rc5t583->irq_lock);

	/* Initailize all पूर्णांक रेजिस्टर to 0 */
	क्रम (i = 0; i < RC5T583_MAX_INTERRUPT_EN_REGS; i++)  अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, irq_en_add[i],
				rc5t583->irq_en_reg[i]);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				irq_en_add[i], ret);
	पूर्ण

	क्रम (i = 0; i < RC5T583_MAX_GPEDGE_REG; i++)  अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, gpedge_add[i],
				rc5t583->gpedge_reg[i]);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				gpedge_add[i], ret);
	पूर्ण

	ret = rc5t583_ग_लिखो(rc5t583->dev, RC5T583_INTC_INTEN, 0x0);
	अगर (ret < 0)
		dev_warn(rc5t583->dev,
			"Error in writing reg 0x%02x error: %d\n",
			RC5T583_INTC_INTEN, ret);

	/* Clear all पूर्णांकerrupts in हाल they woke up active. */
	क्रम (i = 0; i < RC5T583_MAX_INTERRUPT_MASK_REGS; i++)  अणु
		ret = rc5t583_ग_लिखो(rc5t583->dev, irq_clr_add[i], 0);
		अगर (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				irq_clr_add[i], ret);
	पूर्ण

	rc5t583->irq_base = irq_base;
	rc5t583->chip_irq = irq;

	क्रम (i = 0; i < RC5T583_MAX_IRQS; i++) अणु
		पूर्णांक __irq = i + rc5t583->irq_base;
		irq_set_chip_data(__irq, rc5t583);
		irq_set_chip_and_handler(__irq, &rc5t583_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thपढ़ो(__irq, 1);
		irq_clear_status_flags(__irq, IRQ_NOREQUEST);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(rc5t583->dev, irq, शून्य, rc5t583_irq,
					IRQF_ONESHOT, "rc5t583", rc5t583);
	अगर (ret < 0)
		dev_err(rc5t583->dev,
			"Error in registering interrupt error: %d\n", ret);
	वापस ret;
पूर्ण
