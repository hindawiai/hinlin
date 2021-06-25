<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Whiskey Cove PMIC GPIO Driver
 *
 * This driver is written based on gpio-crystalcove.c
 *
 * Copyright (C) 2016 Intel Corporation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/seq_file.h>

/*
 * Whiskey Cove PMIC has 13 physical GPIO pins भागided पूर्णांकo 3 banks:
 * Bank 0: Pin  0 - 6
 * Bank 1: Pin  7 - 10
 * Bank 2: Pin 11 - 12
 * Each pin has one output control रेजिस्टर and one input control रेजिस्टर.
 */
#घोषणा BANK0_NR_PINS		7
#घोषणा BANK1_NR_PINS		4
#घोषणा BANK2_NR_PINS		2
#घोषणा WCOVE_GPIO_NUM		(BANK0_NR_PINS + BANK1_NR_PINS + BANK2_NR_PINS)
#घोषणा WCOVE_VGPIO_NUM		94
/* GPIO output control रेजिस्टरs (one per pin): 0x4e44 - 0x4e50 */
#घोषणा GPIO_OUT_CTRL_BASE	0x4e44
/* GPIO input control रेजिस्टरs (one per pin): 0x4e51 - 0x4e5d */
#घोषणा GPIO_IN_CTRL_BASE	0x4e51

/*
 * GPIO पूर्णांकerrupts are organized in two groups:
 * Group 0: Bank 0 pins (Pin 0 - 6)
 * Group 1: Bank 1 and Bank 2 pins (Pin 7 - 12)
 * Each group has two रेजिस्टरs (one bit per pin): status and mask.
 */
#घोषणा GROUP0_NR_IRQS		7
#घोषणा GROUP1_NR_IRQS		6
#घोषणा IRQ_MASK_BASE		0x4e19
#घोषणा IRQ_STATUS_BASE		0x4e0b
#घोषणा GPIO_IRQ0_MASK		GENMASK(6, 0)
#घोषणा GPIO_IRQ1_MASK		GENMASK(5, 0)
#घोषणा UPDATE_IRQ_TYPE		BIT(0)
#घोषणा UPDATE_IRQ_MASK		BIT(1)

#घोषणा CTLI_INTCNT_DIS		(0 << 1)
#घोषणा CTLI_INTCNT_NE		(1 << 1)
#घोषणा CTLI_INTCNT_PE		(2 << 1)
#घोषणा CTLI_INTCNT_BE		(3 << 1)

#घोषणा CTLO_सूची_IN		(0 << 5)
#घोषणा CTLO_सूची_OUT		(1 << 5)

#घोषणा CTLO_DRV_MASK		(1 << 4)
#घोषणा CTLO_DRV_OD		(0 << 4)
#घोषणा CTLO_DRV_CMOS		(1 << 4)

#घोषणा CTLO_DRV_REN		(1 << 3)

#घोषणा CTLO_RVAL_2KDOWN	(0 << 1)
#घोषणा CTLO_RVAL_2KUP		(1 << 1)
#घोषणा CTLO_RVAL_50KDOWN	(2 << 1)
#घोषणा CTLO_RVAL_50KUP		(3 << 1)

#घोषणा CTLO_INPUT_SET		(CTLO_DRV_CMOS | CTLO_DRV_REN | CTLO_RVAL_2KUP)
#घोषणा CTLO_OUTPUT_SET		(CTLO_सूची_OUT | CTLO_INPUT_SET)

क्रमागत ctrl_रेजिस्टर अणु
	CTRL_IN,
	CTRL_OUT,
	IRQ_STATUS,
	IRQ_MASK,
पूर्ण;

/*
 * काष्ठा wcove_gpio - Whiskey Cove GPIO controller
 * @buslock: क्रम bus lock/sync and unlock.
 * @chip: the असलtract gpio_chip काष्ठाure.
 * @dev: the gpio device
 * @regmap: the regmap from the parent device.
 * @regmap_irq_chip: the regmap of the gpio irq chip.
 * @update: pending IRQ setting update, to be written to the chip upon unlock.
 * @पूर्णांकcnt: the Interrupt Detect value to be written.
 * @set_irq_mask: true अगर the IRQ mask needs to be set, false to clear.
 */
काष्ठा wcove_gpio अणु
	काष्ठा mutex buslock;
	काष्ठा gpio_chip chip;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *regmap_irq_chip;
	पूर्णांक update;
	पूर्णांक पूर्णांकcnt;
	bool set_irq_mask;
पूर्ण;

अटल अंतरभूत पूर्णांक to_reg(पूर्णांक gpio, क्रमागत ctrl_रेजिस्टर reg_type)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (gpio >= WCOVE_GPIO_NUM)
		वापस -EOPNOTSUPP;

	अगर (reg_type == CTRL_IN)
		reg = GPIO_IN_CTRL_BASE + gpio;
	अन्यथा
		reg = GPIO_OUT_CTRL_BASE + gpio;

	वापस reg;
पूर्ण

अटल अंतरभूत पूर्णांक to_ireg(पूर्णांक gpio, क्रमागत ctrl_रेजिस्टर type, अचिन्हित पूर्णांक *mask)
अणु
	अचिन्हित पूर्णांक reg = type == IRQ_STATUS ? IRQ_STATUS_BASE : IRQ_MASK_BASE;

	अगर (gpio < GROUP0_NR_IRQS) अणु
		reg += 0;
		*mask = BIT(gpio);
	पूर्ण अन्यथा अणु
		reg += 1;
		*mask = BIT(gpio - GROUP0_NR_IRQS);
	पूर्ण

	वापस reg;
पूर्ण

अटल व्योम wcove_update_irq_mask(काष्ठा wcove_gpio *wg, पूर्णांक gpio)
अणु
	अचिन्हित पूर्णांक mask, reg = to_ireg(gpio, IRQ_MASK, &mask);

	अगर (wg->set_irq_mask)
		regmap_set_bits(wg->regmap, reg, mask);
	अन्यथा
		regmap_clear_bits(wg->regmap, reg, mask);
पूर्ण

अटल व्योम wcove_update_irq_ctrl(काष्ठा wcove_gpio *wg, पूर्णांक gpio)
अणु
	पूर्णांक reg = to_reg(gpio, CTRL_IN);

	अगर (reg < 0)
		वापस;

	regmap_update_bits(wg->regmap, reg, CTLI_INTCNT_BE, wg->पूर्णांकcnt);
पूर्ण

अटल पूर्णांक wcove_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस 0;

	वापस regmap_ग_लिखो(wg->regmap, reg, CTLO_INPUT_SET);
पूर्ण

अटल पूर्णांक wcove_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				    पूर्णांक value)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस 0;

	वापस regmap_ग_लिखो(wg->regmap, reg, CTLO_OUTPUT_SET | value);
पूर्ण

अटल पूर्णांक wcove_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस GPIO_LINE_सूचीECTION_OUT;

	ret = regmap_पढ़ो(wg->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (val & CTLO_सूची_OUT)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक wcove_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, reg = to_reg(gpio, CTRL_IN);

	अगर (reg < 0)
		वापस 0;

	ret = regmap_पढ़ो(wg->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	वापस val & 0x1;
पूर्ण

अटल व्योम wcove_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस;

	अगर (value)
		regmap_set_bits(wg->regmap, reg, 1);
	अन्यथा
		regmap_clear_bits(wg->regmap, reg, 1);
पूर्ण

अटल पूर्णांक wcove_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				 अचिन्हित दीर्घ config)
अणु
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस 0;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(wg->regmap, reg, CTLO_DRV_MASK,
					  CTLO_DRV_OD);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(wg->regmap, reg, CTLO_DRV_MASK,
					  CTLO_DRV_CMOS);
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक wcove_irq_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);

	अगर (data->hwirq >= WCOVE_GPIO_NUM)
		वापस 0;

	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		wg->पूर्णांकcnt = CTLI_INTCNT_DIS;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		wg->पूर्णांकcnt = CTLI_INTCNT_BE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		wg->पूर्णांकcnt = CTLI_INTCNT_PE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		wg->पूर्णांकcnt = CTLI_INTCNT_NE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wg->update |= UPDATE_IRQ_TYPE;

	वापस 0;
पूर्ण

अटल व्योम wcove_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);

	mutex_lock(&wg->buslock);
पूर्ण

अटल व्योम wcove_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक gpio = data->hwirq;

	अगर (wg->update & UPDATE_IRQ_TYPE)
		wcove_update_irq_ctrl(wg, gpio);
	अगर (wg->update & UPDATE_IRQ_MASK)
		wcove_update_irq_mask(wg, gpio);
	wg->update = 0;

	mutex_unlock(&wg->buslock);
पूर्ण

अटल व्योम wcove_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);

	अगर (data->hwirq >= WCOVE_GPIO_NUM)
		वापस;

	wg->set_irq_mask = false;
	wg->update |= UPDATE_IRQ_MASK;
पूर्ण

अटल व्योम wcove_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);

	अगर (data->hwirq >= WCOVE_GPIO_NUM)
		वापस;

	wg->set_irq_mask = true;
	wg->update |= UPDATE_IRQ_MASK;
पूर्ण

अटल काष्ठा irq_chip wcove_irqchip = अणु
	.name			= "Whiskey Cove",
	.irq_mask		= wcove_irq_mask,
	.irq_unmask		= wcove_irq_unmask,
	.irq_set_type		= wcove_irq_type,
	.irq_bus_lock		= wcove_bus_lock,
	.irq_bus_sync_unlock	= wcove_bus_sync_unlock,
पूर्ण;

अटल irqवापस_t wcove_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wcove_gpio *wg = (काष्ठा wcove_gpio *)data;
	अचिन्हित पूर्णांक virq, gpio;
	अचिन्हित दीर्घ pending;
	u8 p[2];

	अगर (regmap_bulk_पढ़ो(wg->regmap, IRQ_STATUS_BASE, p, 2)) अणु
		dev_err(wg->dev, "Failed to read irq status register\n");
		वापस IRQ_NONE;
	पूर्ण

	pending = (p[0] & GPIO_IRQ0_MASK) | ((p[1] & GPIO_IRQ1_MASK) << 7);
	अगर (!pending)
		वापस IRQ_NONE;

	/* Iterate until no पूर्णांकerrupt is pending */
	जबतक (pending) अणु
		/* One iteration is क्रम all pending bits */
		क्रम_each_set_bit(gpio, &pending, WCOVE_GPIO_NUM) अणु
			अचिन्हित पूर्णांक mask, reg = to_ireg(gpio, IRQ_STATUS, &mask);

			virq = irq_find_mapping(wg->chip.irq.करोमुख्य, gpio);
			handle_nested_irq(virq);
			regmap_set_bits(wg->regmap, reg, mask);
		पूर्ण

		/* Next iteration */
		अगर (regmap_bulk_पढ़ो(wg->regmap, IRQ_STATUS_BASE, p, 2)) अणु
			dev_err(wg->dev, "Failed to read irq status\n");
			अवरोध;
		पूर्ण

		pending = (p[0] & GPIO_IRQ0_MASK) | ((p[1] & GPIO_IRQ1_MASK) << 7);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wcove_gpio_dbg_show(काष्ठा seq_file *s,
				      काष्ठा gpio_chip *chip)
अणु
	अचिन्हित पूर्णांक ctlo, ctli, irq_mask, irq_status;
	काष्ठा wcove_gpio *wg = gpiochip_get_data(chip);
	पूर्णांक gpio, mask, ret = 0;

	क्रम (gpio = 0; gpio < WCOVE_GPIO_NUM; gpio++) अणु
		ret += regmap_पढ़ो(wg->regmap, to_reg(gpio, CTRL_OUT), &ctlo);
		ret += regmap_पढ़ो(wg->regmap, to_reg(gpio, CTRL_IN), &ctli);
		ret += regmap_पढ़ो(wg->regmap, to_ireg(gpio, IRQ_MASK, &mask), &irq_mask);
		ret += regmap_पढ़ो(wg->regmap, to_ireg(gpio, IRQ_STATUS, &mask), &irq_status);
		अगर (ret) अणु
			pr_err("Failed to read registers: ctrl out/in or irq status/mask\n");
			अवरोध;
		पूर्ण

		seq_म_लिखो(s, " gpio-%-2d %s %s %s %s ctlo=%2x,%s %s\n",
			   gpio, ctlo & CTLO_सूची_OUT ? "out" : "in ",
			   ctli & 0x1 ? "hi" : "lo",
			   ctli & CTLI_INTCNT_NE ? "fall" : "    ",
			   ctli & CTLI_INTCNT_PE ? "rise" : "    ",
			   ctlo,
			   irq_mask & mask ? "mask  " : "unmask",
			   irq_status & mask ? "pending" : "       ");
	पूर्ण
पूर्ण

अटल पूर्णांक wcove_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	काष्ठा wcove_gpio *wg;
	पूर्णांक virq, ret, irq;
	काष्ठा device *dev;
	काष्ठा gpio_irq_chip *girq;

	/*
	 * This gpio platक्रमm device is created by a mfd device (see
	 * drivers/mfd/पूर्णांकel_soc_pmic_bxtwc.c क्रम details). Inक्रमmation
	 * shared by all sub-devices created by the mfd device, the regmap
	 * poपूर्णांकer क्रम instance, is stored as driver data of the mfd device
	 * driver.
	 */
	pmic = dev_get_drvdata(pdev->dev.parent);
	अगर (!pmic)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	dev = &pdev->dev;

	wg = devm_kzalloc(dev, माप(*wg), GFP_KERNEL);
	अगर (!wg)
		वापस -ENOMEM;

	wg->regmap_irq_chip = pmic->irq_chip_data;

	platक्रमm_set_drvdata(pdev, wg);

	mutex_init(&wg->buslock);
	wg->chip.label = KBUILD_MODNAME;
	wg->chip.direction_input = wcove_gpio_dir_in;
	wg->chip.direction_output = wcove_gpio_dir_out;
	wg->chip.get_direction = wcove_gpio_get_direction;
	wg->chip.get = wcove_gpio_get;
	wg->chip.set = wcove_gpio_set;
	wg->chip.set_config = wcove_gpio_set_config;
	wg->chip.base = -1;
	wg->chip.ngpio = WCOVE_VGPIO_NUM;
	wg->chip.can_sleep = true;
	wg->chip.parent = pdev->dev.parent;
	wg->chip.dbg_show = wcove_gpio_dbg_show;
	wg->dev = dev;
	wg->regmap = pmic->regmap;

	virq = regmap_irq_get_virq(wg->regmap_irq_chip, irq);
	अगर (virq < 0) अणु
		dev_err(dev, "Failed to get virq by irq %d\n", irq);
		वापस virq;
	पूर्ण

	girq = &wg->chip.irq;
	girq->chip = &wcove_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;
	girq->thपढ़ोed = true;

	ret = devm_request_thपढ़ोed_irq(dev, virq, शून्य, wcove_gpio_irq_handler,
					IRQF_ONESHOT, pdev->name, wg);
	अगर (ret) अणु
		dev_err(dev, "Failed to request irq %d\n", virq);
		वापस ret;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &wg->chip, wg);
	अगर (ret) अणु
		dev_err(dev, "Failed to add gpiochip: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable GPIO0 पूर्णांकerrupts */
	ret = regmap_clear_bits(wg->regmap, IRQ_MASK_BASE + 0, GPIO_IRQ0_MASK);
	अगर (ret)
		वापस ret;

	/* Enable GPIO1 पूर्णांकerrupts */
	ret = regmap_clear_bits(wg->regmap, IRQ_MASK_BASE + 1, GPIO_IRQ1_MASK);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Whiskey Cove PMIC itself is a analog device(but with digital control
 * पूर्णांकerface) providing घातer management support क्रम other devices in
 * the accompanied SoC, so we have no .pm क्रम Whiskey Cove GPIO driver.
 */
अटल काष्ठा platक्रमm_driver wcove_gpio_driver = अणु
	.driver = अणु
		.name = "bxt_wcove_gpio",
	पूर्ण,
	.probe = wcove_gpio_probe,
पूर्ण;

module_platक्रमm_driver(wcove_gpio_driver);

MODULE_AUTHOR("Ajay Thomas <ajay.thomas.david.rajamanickam@intel.com>");
MODULE_AUTHOR("Bin Gao <bin.gao@intel.com>");
MODULE_DESCRIPTION("Intel Whiskey Cove GPIO Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bxt_wcove_gpio");
