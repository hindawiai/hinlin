<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8997-irq.c - Interrupt controller support क्रम MAX8997
//
// Copyright (C) 2011 Samsung Electronics Co.Ltd
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This driver is based on max8998-irq.c

#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>

अटल स्थिर u8 max8997_mask_reg[] = अणु
	[PMIC_INT1] = MAX8997_REG_INT1MSK,
	[PMIC_INT2] = MAX8997_REG_INT2MSK,
	[PMIC_INT3] = MAX8997_REG_INT3MSK,
	[PMIC_INT4] = MAX8997_REG_INT4MSK,
	[FUEL_GAUGE] = MAX8997_REG_INVALID,
	[MUIC_INT1] = MAX8997_MUIC_REG_INTMASK1,
	[MUIC_INT2] = MAX8997_MUIC_REG_INTMASK2,
	[MUIC_INT3] = MAX8997_MUIC_REG_INTMASK3,
	[GPIO_LOW] = MAX8997_REG_INVALID,
	[GPIO_HI] = MAX8997_REG_INVALID,
	[FLASH_STATUS] = MAX8997_REG_INVALID,
पूर्ण;

अटल काष्ठा i2c_client *get_i2c(काष्ठा max8997_dev *max8997,
				क्रमागत max8997_irq_source src)
अणु
	चयन (src) अणु
	हाल PMIC_INT1 ... PMIC_INT4:
		वापस max8997->i2c;
	हाल FUEL_GAUGE:
		वापस शून्य;
	हाल MUIC_INT1 ... MUIC_INT3:
		वापस max8997->muic;
	हाल GPIO_LOW ... GPIO_HI:
		वापस max8997->i2c;
	हाल FLASH_STATUS:
		वापस max8997->i2c;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

काष्ठा max8997_irq_data अणु
	पूर्णांक mask;
	क्रमागत max8997_irq_source group;
पूर्ण;

#घोषणा DECLARE_IRQ(idx, _group, _mask)		\
	[(idx)] = अणु .group = (_group), .mask = (_mask) पूर्ण
अटल स्थिर काष्ठा max8997_irq_data max8997_irqs[] = अणु
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRONR,	PMIC_INT1, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRONF,	PMIC_INT1, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRON1SEC,	PMIC_INT1, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGONR,	PMIC_INT1, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGONF,	PMIC_INT1, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_LOWBAT2,	PMIC_INT1, 1 << 6),
	DECLARE_IRQ(MAX8997_PMICIRQ_LOWBAT1,	PMIC_INT1, 1 << 7),

	DECLARE_IRQ(MAX8997_PMICIRQ_JIGR,	PMIC_INT2, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGF,	PMIC_INT2, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_MR,		PMIC_INT2, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS1OK,	PMIC_INT2, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS2OK,	PMIC_INT2, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS3OK,	PMIC_INT2, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS4OK,	PMIC_INT2, 1 << 6),

	DECLARE_IRQ(MAX8997_PMICIRQ_CHGINS,	PMIC_INT3, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_CHGRM,	PMIC_INT3, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_DCINOVP,	PMIC_INT3, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_TOPOFFR,	PMIC_INT3, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_CHGRSTF,	PMIC_INT3, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_MBCHGTMEXPD,	PMIC_INT3, 1 << 7),

	DECLARE_IRQ(MAX8997_PMICIRQ_RTC60S,	PMIC_INT4, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTCA1,	PMIC_INT4, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTCA2,	PMIC_INT4, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_SMPL_INT,	PMIC_INT4, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTC1S,	PMIC_INT4, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_WTSR,	PMIC_INT4, 1 << 5),

	DECLARE_IRQ(MAX8997_MUICIRQ_ADCError,	MUIC_INT1, 1 << 2),
	DECLARE_IRQ(MAX8997_MUICIRQ_ADCLow,	MUIC_INT1, 1 << 1),
	DECLARE_IRQ(MAX8997_MUICIRQ_ADC,	MUIC_INT1, 1 << 0),

	DECLARE_IRQ(MAX8997_MUICIRQ_VBVolt,	MUIC_INT2, 1 << 4),
	DECLARE_IRQ(MAX8997_MUICIRQ_DBChg,	MUIC_INT2, 1 << 3),
	DECLARE_IRQ(MAX8997_MUICIRQ_DCDTmr,	MUIC_INT2, 1 << 2),
	DECLARE_IRQ(MAX8997_MUICIRQ_ChgDetRun,	MUIC_INT2, 1 << 1),
	DECLARE_IRQ(MAX8997_MUICIRQ_ChgTyp,	MUIC_INT2, 1 << 0),

	DECLARE_IRQ(MAX8997_MUICIRQ_OVP,	MUIC_INT3, 1 << 2),
पूर्ण;

अटल व्योम max8997_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा max8997_dev *max8997 = irq_data_get_irq_chip_data(data);

	mutex_lock(&max8997->irqlock);
पूर्ण

अटल व्योम max8997_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा max8997_dev *max8997 = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < MAX8997_IRQ_GROUP_NR; i++) अणु
		u8 mask_reg = max8997_mask_reg[i];
		काष्ठा i2c_client *i2c = get_i2c(max8997, i);

		अगर (mask_reg == MAX8997_REG_INVALID ||
				IS_ERR_OR_शून्य(i2c))
			जारी;
		max8997->irq_masks_cache[i] = max8997->irq_masks_cur[i];

		max8997_ग_लिखो_reg(i2c, max8997_mask_reg[i],
				max8997->irq_masks_cur[i]);
	पूर्ण

	mutex_unlock(&max8997->irqlock);
पूर्ण

अंतरभूत अटल स्थिर काष्ठा max8997_irq_data *
irq_to_max8997_irq(काष्ठा max8997_dev *max8997, काष्ठा irq_data *data)
अणु
	वापस &max8997_irqs[data->hwirq];
पूर्ण

अटल व्योम max8997_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा max8997_dev *max8997 = irq_data_get_irq_chip_data(data);
	स्थिर काष्ठा max8997_irq_data *irq_data = irq_to_max8997_irq(max8997,
								     data);

	max8997->irq_masks_cur[irq_data->group] |= irq_data->mask;
पूर्ण

अटल व्योम max8997_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा max8997_dev *max8997 = irq_data_get_irq_chip_data(data);
	स्थिर काष्ठा max8997_irq_data *irq_data = irq_to_max8997_irq(max8997,
								     data);

	max8997->irq_masks_cur[irq_data->group] &= ~irq_data->mask;
पूर्ण

अटल काष्ठा irq_chip max8997_irq_chip = अणु
	.name			= "max8997",
	.irq_bus_lock		= max8997_irq_lock,
	.irq_bus_sync_unlock	= max8997_irq_sync_unlock,
	.irq_mask		= max8997_irq_mask,
	.irq_unmask		= max8997_irq_unmask,
पूर्ण;

#घोषणा MAX8997_IRQSRC_PMIC		(1 << 1)
#घोषणा MAX8997_IRQSRC_FUELGAUGE	(1 << 2)
#घोषणा MAX8997_IRQSRC_MUIC		(1 << 3)
#घोषणा MAX8997_IRQSRC_GPIO		(1 << 4)
#घोषणा MAX8997_IRQSRC_FLASH		(1 << 5)
अटल irqवापस_t max8997_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8997_dev *max8997 = data;
	u8 irq_reg[MAX8997_IRQ_GROUP_NR] = अणुपूर्ण;
	u8 irq_src;
	पूर्णांक ret;
	पूर्णांक i, cur_irq;

	ret = max8997_पढ़ो_reg(max8997->i2c, MAX8997_REG_INTSRC, &irq_src);
	अगर (ret < 0) अणु
		dev_err(max8997->dev, "Failed to read interrupt source: %d\n",
				ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_src & MAX8997_IRQSRC_PMIC) अणु
		/* PMIC INT1 ~ INT4 */
		max8997_bulk_पढ़ो(max8997->i2c, MAX8997_REG_INT1, 4,
				&irq_reg[PMIC_INT1]);
	पूर्ण
	अगर (irq_src & MAX8997_IRQSRC_FUELGAUGE) अणु
		/*
		 * TODO: FUEL GAUGE
		 *
		 * This is to be supported by Max17042 driver. When
		 * an पूर्णांकerrupt incurs here, it should be relayed to a
		 * Max17042 device that is connected (probably by
		 * platक्रमm-data). However, we करो not have पूर्णांकerrupt
		 * handling in Max17042 driver currently. The Max17042 IRQ
		 * driver should be पढ़ोy to be used as a stand-alone device and
		 * a Max8997-dependent device. Because it is not पढ़ोy in
		 * Max17042-side and it is not too critical in operating
		 * Max8997, we करो not implement this in initial releases.
		 */
		irq_reg[FUEL_GAUGE] = 0;
	पूर्ण
	अगर (irq_src & MAX8997_IRQSRC_MUIC) अणु
		/* MUIC INT1 ~ INT3 */
		max8997_bulk_पढ़ो(max8997->muic, MAX8997_MUIC_REG_INT1, 3,
				&irq_reg[MUIC_INT1]);
	पूर्ण
	अगर (irq_src & MAX8997_IRQSRC_GPIO) अणु
		/* GPIO Interrupt */
		u8 gpio_info[MAX8997_NUM_GPIO];

		irq_reg[GPIO_LOW] = 0;
		irq_reg[GPIO_HI] = 0;

		max8997_bulk_पढ़ो(max8997->i2c, MAX8997_REG_GPIOCNTL1,
				MAX8997_NUM_GPIO, gpio_info);
		क्रम (i = 0; i < MAX8997_NUM_GPIO; i++) अणु
			bool पूर्णांकerrupt = false;

			चयन (gpio_info[i] & MAX8997_GPIO_INT_MASK) अणु
			हाल MAX8997_GPIO_INT_BOTH:
				अगर (max8997->gpio_status[i] != gpio_info[i])
					पूर्णांकerrupt = true;
				अवरोध;
			हाल MAX8997_GPIO_INT_RISE:
				अगर ((max8997->gpio_status[i] != gpio_info[i]) &&
				    (gpio_info[i] & MAX8997_GPIO_DATA_MASK))
					पूर्णांकerrupt = true;
				अवरोध;
			हाल MAX8997_GPIO_INT_FALL:
				अगर ((max8997->gpio_status[i] != gpio_info[i]) &&
				    !(gpio_info[i] & MAX8997_GPIO_DATA_MASK))
					पूर्णांकerrupt = true;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			अगर (पूर्णांकerrupt) अणु
				अगर (i < 8)
					irq_reg[GPIO_LOW] |= (1 << i);
				अन्यथा
					irq_reg[GPIO_HI] |= (1 << (i - 8));
			पूर्ण

		पूर्ण
	पूर्ण
	अगर (irq_src & MAX8997_IRQSRC_FLASH) अणु
		/* Flash Status Interrupt */
		ret = max8997_पढ़ो_reg(max8997->i2c, MAX8997_REG_FLASHSTATUS,
				&irq_reg[FLASH_STATUS]);
	पूर्ण

	/* Apply masking */
	क्रम (i = 0; i < MAX8997_IRQ_GROUP_NR; i++)
		irq_reg[i] &= ~max8997->irq_masks_cur[i];

	/* Report */
	क्रम (i = 0; i < MAX8997_IRQ_NR; i++) अणु
		अगर (irq_reg[max8997_irqs[i].group] & max8997_irqs[i].mask) अणु
			cur_irq = irq_find_mapping(max8997->irq_करोमुख्य, i);
			अगर (cur_irq)
				handle_nested_irq(cur_irq);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक max8997_irq_resume(काष्ठा max8997_dev *max8997)
अणु
	अगर (max8997->irq && max8997->irq_करोमुख्य)
		max8997_irq_thपढ़ो(0, max8997);
	वापस 0;
पूर्ण

अटल पूर्णांक max8997_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
					irq_hw_number_t hw)
अणु
	काष्ठा max8997_dev *max8997 = d->host_data;

	irq_set_chip_data(irq, max8997);
	irq_set_chip_and_handler(irq, &max8997_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops max8997_irq_करोमुख्य_ops = अणु
	.map = max8997_irq_करोमुख्य_map,
पूर्ण;

पूर्णांक max8997_irq_init(काष्ठा max8997_dev *max8997)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक i;
	पूर्णांक ret;
	u8 val;

	अगर (!max8997->irq) अणु
		dev_warn(max8997->dev, "No interrupt specified.\n");
		वापस 0;
	पूर्ण

	mutex_init(&max8997->irqlock);

	/* Mask inभागidual पूर्णांकerrupt sources */
	क्रम (i = 0; i < MAX8997_IRQ_GROUP_NR; i++) अणु
		काष्ठा i2c_client *i2c;

		max8997->irq_masks_cur[i] = 0xff;
		max8997->irq_masks_cache[i] = 0xff;
		i2c = get_i2c(max8997, i);

		अगर (IS_ERR_OR_शून्य(i2c))
			जारी;
		अगर (max8997_mask_reg[i] == MAX8997_REG_INVALID)
			जारी;

		max8997_ग_लिखो_reg(i2c, max8997_mask_reg[i], 0xff);
	पूर्ण

	क्रम (i = 0; i < MAX8997_NUM_GPIO; i++) अणु
		max8997->gpio_status[i] = (max8997_पढ़ो_reg(max8997->i2c,
						MAX8997_REG_GPIOCNTL1 + i,
						&val)
					& MAX8997_GPIO_DATA_MASK) ?
					true : false;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(शून्य, MAX8997_IRQ_NR,
					&max8997_irq_करोमुख्य_ops, max8997);
	अगर (!करोमुख्य) अणु
		dev_err(max8997->dev, "could not create irq domain\n");
		वापस -ENODEV;
	पूर्ण
	max8997->irq_करोमुख्य = करोमुख्य;

	ret = request_thपढ़ोed_irq(max8997->irq, शून्य, max8997_irq_thपढ़ो,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"max8997-irq", max8997);

	अगर (ret) अणु
		dev_err(max8997->dev, "Failed to request IRQ %d: %d\n",
				max8997->irq, ret);
		वापस ret;
	पूर्ण

	अगर (!max8997->ono)
		वापस 0;

	ret = request_thपढ़ोed_irq(max8997->ono, शून्य, max8997_irq_thपढ़ो,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT, "max8997-ono", max8997);

	अगर (ret)
		dev_err(max8997->dev, "Failed to request ono-IRQ %d: %d\n",
				max8997->ono, ret);

	वापस 0;
पूर्ण

व्योम max8997_irq_निकास(काष्ठा max8997_dev *max8997)
अणु
	अगर (max8997->ono)
		मुक्त_irq(max8997->ono, max8997);

	अगर (max8997->irq)
		मुक्त_irq(max8997->irq, max8997);
पूर्ण
