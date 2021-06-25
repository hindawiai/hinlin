<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Spपढ़ोtrum Communications Inc.
 * Copyright (C) 2018 Linaro Ltd.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* EIC रेजिस्टरs definition */
#घोषणा SPRD_PMIC_EIC_DATA		0x0
#घोषणा SPRD_PMIC_EIC_DMSK		0x4
#घोषणा SPRD_PMIC_EIC_IEV		0x14
#घोषणा SPRD_PMIC_EIC_IE		0x18
#घोषणा SPRD_PMIC_EIC_RIS		0x1c
#घोषणा SPRD_PMIC_EIC_MIS		0x20
#घोषणा SPRD_PMIC_EIC_IC		0x24
#घोषणा SPRD_PMIC_EIC_TRIG		0x28
#घोषणा SPRD_PMIC_EIC_CTRL0		0x40

/*
 * The PMIC EIC controller only has one bank, and each bank now can contain
 * 16 EICs.
 */
#घोषणा SPRD_PMIC_EIC_PER_BANK_NR	16
#घोषणा SPRD_PMIC_EIC_NR		SPRD_PMIC_EIC_PER_BANK_NR
#घोषणा SPRD_PMIC_EIC_DATA_MASK		GENMASK(15, 0)
#घोषणा SPRD_PMIC_EIC_BIT(x)		((x) & (SPRD_PMIC_EIC_PER_BANK_NR - 1))
#घोषणा SPRD_PMIC_EIC_DBNC_MASK		GENMASK(11, 0)

/*
 * These रेजिस्टरs are modअगरied under the irq bus lock and cached to aव्योम
 * unnecessary ग_लिखोs in bus_sync_unlock.
 */
क्रमागत अणु
	REG_IEV,
	REG_IE,
	REG_TRIG,
	CACHE_NR_REGS
पूर्ण;

/**
 * काष्ठा sprd_pmic_eic - PMIC EIC controller
 * @chip: the gpio_chip काष्ठाure.
 * @पूर्णांकc: the irq_chip काष्ठाure.
 * @map:  the regmap from the parent device.
 * @offset: the EIC controller's offset address of the PMIC.
 * @reg: the array to cache the EIC रेजिस्टरs.
 * @buslock: क्रम bus lock/sync and unlock.
 * @irq: the पूर्णांकerrupt number of the PMIC EIC conteroller.
 */
काष्ठा sprd_pmic_eic अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip पूर्णांकc;
	काष्ठा regmap *map;
	u32 offset;
	u8 reg[CACHE_NR_REGS];
	काष्ठा mutex buslock;
	पूर्णांक irq;
पूर्ण;

अटल व्योम sprd_pmic_eic_update(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 u16 reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 shअगरt = SPRD_PMIC_EIC_BIT(offset);

	regmap_update_bits(pmic_eic->map, pmic_eic->offset + reg,
			   BIT(shअगरt), val << shअगरt);
पूर्ण

अटल पूर्णांक sprd_pmic_eic_पढ़ो(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      u16 reg)
अणु
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pmic_eic->map, pmic_eic->offset + reg, &value);
	अगर (ret)
		वापस ret;

	वापस !!(value & BIT(SPRD_PMIC_EIC_BIT(offset)));
पूर्ण

अटल पूर्णांक sprd_pmic_eic_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_DMSK, 1);
	वापस 0;
पूर्ण

अटल व्योम sprd_pmic_eic_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_DMSK, 0);
पूर्ण

अटल पूर्णांक sprd_pmic_eic_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस sprd_pmic_eic_पढ़ो(chip, offset, SPRD_PMIC_EIC_DATA);
पूर्ण

अटल पूर्णांक sprd_pmic_eic_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset)
अणु
	/* EICs are always input, nothing need to करो here. */
	वापस 0;
पूर्ण

अटल व्योम sprd_pmic_eic_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      पूर्णांक value)
अणु
	/* EICs are always input, nothing need to करो here. */
पूर्ण

अटल पूर्णांक sprd_pmic_eic_set_debounce(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset,
				      अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 reg, value;
	पूर्णांक ret;

	reg = SPRD_PMIC_EIC_CTRL0 + SPRD_PMIC_EIC_BIT(offset) * 0x4;
	ret = regmap_पढ़ो(pmic_eic->map, pmic_eic->offset + reg, &value);
	अगर (ret)
		वापस ret;

	value &= ~SPRD_PMIC_EIC_DBNC_MASK;
	value |= (debounce / 1000) & SPRD_PMIC_EIC_DBNC_MASK;
	वापस regmap_ग_लिखो(pmic_eic->map, pmic_eic->offset + reg, value);
पूर्ण

अटल पूर्णांक sprd_pmic_eic_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);

	अगर (param == PIN_CONFIG_INPUT_DEBOUNCE)
		वापस sprd_pmic_eic_set_debounce(chip, offset, arg);

	वापस -ENOTSUPP;
पूर्ण

अटल व्योम sprd_pmic_eic_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);

	pmic_eic->reg[REG_IE] = 0;
	pmic_eic->reg[REG_TRIG] = 0;
पूर्ण

अटल व्योम sprd_pmic_eic_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);

	pmic_eic->reg[REG_IE] = 1;
	pmic_eic->reg[REG_TRIG] = 1;
पूर्ण

अटल पूर्णांक sprd_pmic_eic_irq_set_type(काष्ठा irq_data *data,
				      अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);

	चयन (flow_type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		pmic_eic->reg[REG_IEV] = 1;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		pmic_eic->reg[REG_IEV] = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		/*
		 * Will set the trigger level according to current EIC level
		 * in irq_bus_sync_unlock() पूर्णांकerface, so here nothing to करो.
		 */
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_pmic_eic_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);

	mutex_lock(&pmic_eic->buslock);
पूर्ण

अटल व्योम sprd_pmic_eic_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 trigger = irqd_get_trigger_type(data);
	u32 offset = irqd_to_hwirq(data);
	पूर्णांक state;

	/* Set irq type */
	अगर (trigger & IRQ_TYPE_EDGE_BOTH) अणु
		state = sprd_pmic_eic_get(chip, offset);
		अगर (state)
			sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 0);
		अन्यथा
			sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 1);
	पूर्ण अन्यथा अणु
		sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV,
				     pmic_eic->reg[REG_IEV]);
	पूर्ण

	/* Set irq unmask */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IE,
			     pmic_eic->reg[REG_IE]);
	/* Generate trigger start pulse क्रम debounce EIC */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_TRIG,
			     pmic_eic->reg[REG_TRIG]);

	mutex_unlock(&pmic_eic->buslock);
पूर्ण

अटल व्योम sprd_pmic_eic_toggle_trigger(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक offset)
अणु
	u32 trigger = irq_get_trigger_type(irq);
	पूर्णांक state, post_state;

	अगर (!(trigger & IRQ_TYPE_EDGE_BOTH))
		वापस;

	state = sprd_pmic_eic_get(chip, offset);
retry:
	अगर (state)
		sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 0);
	अन्यथा
		sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 1);

	post_state = sprd_pmic_eic_get(chip, offset);
	अगर (state != post_state) अणु
		dev_warn(chip->parent, "PMIC EIC level was changed.\n");
		state = post_state;
		जाओ retry;
	पूर्ण

	/* Set irq unmask */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IE, 1);
	/* Generate trigger start pulse क्रम debounce EIC */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_TRIG, 1);
पूर्ण

अटल irqवापस_t sprd_pmic_eic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sprd_pmic_eic *pmic_eic = data;
	काष्ठा gpio_chip *chip = &pmic_eic->chip;
	अचिन्हित दीर्घ status;
	u32 n, girq, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pmic_eic->map, pmic_eic->offset + SPRD_PMIC_EIC_MIS,
			  &val);
	अगर (ret)
		वापस IRQ_RETVAL(ret);

	status = val & SPRD_PMIC_EIC_DATA_MASK;

	क्रम_each_set_bit(n, &status, chip->ngpio) अणु
		/* Clear the पूर्णांकerrupt */
		sprd_pmic_eic_update(chip, n, SPRD_PMIC_EIC_IC, 1);

		girq = irq_find_mapping(chip->irq.करोमुख्य, n);
		handle_nested_irq(girq);

		/*
		 * The PMIC EIC can only support level trigger, so we can
		 * toggle the level trigger to emulate the edge trigger.
		 */
		sprd_pmic_eic_toggle_trigger(chip, girq, n);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sprd_pmic_eic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_irq_chip *irq;
	काष्ठा sprd_pmic_eic *pmic_eic;
	पूर्णांक ret;

	pmic_eic = devm_kzalloc(&pdev->dev, माप(*pmic_eic), GFP_KERNEL);
	अगर (!pmic_eic)
		वापस -ENOMEM;

	mutex_init(&pmic_eic->buslock);

	pmic_eic->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pmic_eic->irq < 0)
		वापस pmic_eic->irq;

	pmic_eic->map = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!pmic_eic->map)
		वापस -ENODEV;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "reg", &pmic_eic->offset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get PMIC EIC base address.\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, pmic_eic->irq, शून्य,
					sprd_pmic_eic_irq_handler,
					IRQF_ONESHOT | IRQF_NO_SUSPEND,
					dev_name(&pdev->dev), pmic_eic);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request PMIC EIC IRQ.\n");
		वापस ret;
	पूर्ण

	pmic_eic->chip.label = dev_name(&pdev->dev);
	pmic_eic->chip.ngpio = SPRD_PMIC_EIC_NR;
	pmic_eic->chip.base = -1;
	pmic_eic->chip.parent = &pdev->dev;
	pmic_eic->chip.of_node = pdev->dev.of_node;
	pmic_eic->chip.direction_input = sprd_pmic_eic_direction_input;
	pmic_eic->chip.request = sprd_pmic_eic_request;
	pmic_eic->chip.मुक्त = sprd_pmic_eic_मुक्त;
	pmic_eic->chip.set_config = sprd_pmic_eic_set_config;
	pmic_eic->chip.set = sprd_pmic_eic_set;
	pmic_eic->chip.get = sprd_pmic_eic_get;

	pmic_eic->पूर्णांकc.name = dev_name(&pdev->dev);
	pmic_eic->पूर्णांकc.irq_mask = sprd_pmic_eic_irq_mask;
	pmic_eic->पूर्णांकc.irq_unmask = sprd_pmic_eic_irq_unmask;
	pmic_eic->पूर्णांकc.irq_set_type = sprd_pmic_eic_irq_set_type;
	pmic_eic->पूर्णांकc.irq_bus_lock = sprd_pmic_eic_bus_lock;
	pmic_eic->पूर्णांकc.irq_bus_sync_unlock = sprd_pmic_eic_bus_sync_unlock;
	pmic_eic->पूर्णांकc.flags = IRQCHIP_SKIP_SET_WAKE;

	irq = &pmic_eic->chip.irq;
	irq->chip = &pmic_eic->पूर्णांकc;
	irq->thपढ़ोed = true;

	ret = devm_gpiochip_add_data(&pdev->dev, &pmic_eic->chip, pmic_eic);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip %d.\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmic_eic);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_pmic_eic_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-eic", पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_pmic_eic_of_match);

अटल काष्ठा platक्रमm_driver sprd_pmic_eic_driver = अणु
	.probe = sprd_pmic_eic_probe,
	.driver = अणु
		.name = "sprd-pmic-eic",
		.of_match_table	= sprd_pmic_eic_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_pmic_eic_driver);

MODULE_DESCRIPTION("Spreadtrum PMIC EIC driver");
MODULE_LICENSE("GPL v2");
