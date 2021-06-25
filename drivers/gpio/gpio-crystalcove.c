<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Crystal Cove GPIO Driver
 *
 * Copyright (C) 2012, 2014 Intel Corporation. All rights reserved.
 *
 * Author: Yang, Bin <bin.yang@पूर्णांकel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/seq_file.h>

#घोषणा CRYSTALCOVE_GPIO_NUM	16
#घोषणा CRYSTALCOVE_VGPIO_NUM	95

#घोषणा UPDATE_IRQ_TYPE		BIT(0)
#घोषणा UPDATE_IRQ_MASK		BIT(1)

#घोषणा GPIO0IRQ		0x0b
#घोषणा GPIO1IRQ		0x0c
#घोषणा MGPIO0IRQS0		0x19
#घोषणा MGPIO1IRQS0		0x1a
#घोषणा MGPIO0IRQSX		0x1b
#घोषणा MGPIO1IRQSX		0x1c
#घोषणा GPIO0P0CTLO		0x2b
#घोषणा GPIO0P0CTLI		0x33
#घोषणा GPIO1P0CTLO		0x3b
#घोषणा GPIO1P0CTLI		0x43
#घोषणा GPIOPANELCTL		0x52

#घोषणा CTLI_INTCNT_DIS		(0)
#घोषणा CTLI_INTCNT_NE		(1 << 1)
#घोषणा CTLI_INTCNT_PE		(2 << 1)
#घोषणा CTLI_INTCNT_BE		(3 << 1)

#घोषणा CTLO_सूची_IN		(0)
#घोषणा CTLO_सूची_OUT		(1 << 5)

#घोषणा CTLO_DRV_CMOS		(0)
#घोषणा CTLO_DRV_OD		(1 << 4)

#घोषणा CTLO_DRV_REN		(1 << 3)

#घोषणा CTLO_RVAL_2KDW		(0)
#घोषणा CTLO_RVAL_2KUP		(1 << 1)
#घोषणा CTLO_RVAL_50KDW		(2 << 1)
#घोषणा CTLO_RVAL_50KUP		(3 << 1)

#घोषणा CTLO_INPUT_SET	(CTLO_DRV_CMOS | CTLO_DRV_REN | CTLO_RVAL_2KUP)
#घोषणा CTLO_OUTPUT_SET	(CTLO_सूची_OUT | CTLO_INPUT_SET)

क्रमागत ctrl_रेजिस्टर अणु
	CTRL_IN,
	CTRL_OUT,
पूर्ण;

/**
 * काष्ठा crystalcove_gpio - Crystal Cove GPIO controller
 * @buslock: क्रम bus lock/sync and unlock.
 * @chip: the असलtract gpio_chip काष्ठाure.
 * @regmap: the regmap from the parent device.
 * @update: pending IRQ setting update, to be written to the chip upon unlock.
 * @पूर्णांकcnt_value: the Interrupt Detect value to be written.
 * @set_irq_mask: true अगर the IRQ mask needs to be set, false to clear.
 */
काष्ठा crystalcove_gpio अणु
	काष्ठा mutex buslock; /* irq_bus_lock */
	काष्ठा gpio_chip chip;
	काष्ठा regmap *regmap;
	पूर्णांक update;
	पूर्णांक पूर्णांकcnt_value;
	bool set_irq_mask;
पूर्ण;

अटल अंतरभूत पूर्णांक to_reg(पूर्णांक gpio, क्रमागत ctrl_रेजिस्टर reg_type)
अणु
	पूर्णांक reg;

	अगर (gpio >= CRYSTALCOVE_GPIO_NUM) अणु
		/*
		 * Virtual GPIO called from ACPI, क्रम now we only support
		 * the panel ctl.
		 */
		चयन (gpio) अणु
		हाल 0x5e:
			वापस GPIOPANELCTL;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (reg_type == CTRL_IN) अणु
		अगर (gpio < 8)
			reg = GPIO0P0CTLI;
		अन्यथा
			reg = GPIO1P0CTLI;
	पूर्ण अन्यथा अणु
		अगर (gpio < 8)
			reg = GPIO0P0CTLO;
		अन्यथा
			reg = GPIO1P0CTLO;
	पूर्ण

	वापस reg + gpio % 8;
पूर्ण

अटल व्योम crystalcove_update_irq_mask(काष्ठा crystalcove_gpio *cg,
					पूर्णांक gpio)
अणु
	u8 mirqs0 = gpio < 8 ? MGPIO0IRQS0 : MGPIO1IRQS0;
	पूर्णांक mask = BIT(gpio % 8);

	अगर (cg->set_irq_mask)
		regmap_update_bits(cg->regmap, mirqs0, mask, mask);
	अन्यथा
		regmap_update_bits(cg->regmap, mirqs0, mask, 0);
पूर्ण

अटल व्योम crystalcove_update_irq_ctrl(काष्ठा crystalcove_gpio *cg, पूर्णांक gpio)
अणु
	पूर्णांक reg = to_reg(gpio, CTRL_IN);

	regmap_update_bits(cg->regmap, reg, CTLI_INTCNT_BE, cg->पूर्णांकcnt_value);
पूर्ण

अटल पूर्णांक crystalcove_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा crystalcove_gpio *cg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस 0;

	वापस regmap_ग_लिखो(cg->regmap, reg, CTLO_INPUT_SET);
पूर्ण

अटल पूर्णांक crystalcove_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				    पूर्णांक value)
अणु
	काष्ठा crystalcove_gpio *cg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस 0;

	वापस regmap_ग_लिखो(cg->regmap, reg, CTLO_OUTPUT_SET | value);
पूर्ण

अटल पूर्णांक crystalcove_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा crystalcove_gpio *cg = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, reg = to_reg(gpio, CTRL_IN);

	अगर (reg < 0)
		वापस 0;

	ret = regmap_पढ़ो(cg->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	वापस val & 0x1;
पूर्ण

अटल व्योम crystalcove_gpio_set(काष्ठा gpio_chip *chip,
				 अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा crystalcove_gpio *cg = gpiochip_get_data(chip);
	पूर्णांक reg = to_reg(gpio, CTRL_OUT);

	अगर (reg < 0)
		वापस;

	अगर (value)
		regmap_update_bits(cg->regmap, reg, 1, 1);
	अन्यथा
		regmap_update_bits(cg->regmap, reg, 1, 0);
पूर्ण

अटल पूर्णांक crystalcove_irq_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	अगर (data->hwirq >= CRYSTALCOVE_GPIO_NUM)
		वापस 0;

	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		cg->पूर्णांकcnt_value = CTLI_INTCNT_DIS;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		cg->पूर्णांकcnt_value = CTLI_INTCNT_BE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		cg->पूर्णांकcnt_value = CTLI_INTCNT_PE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		cg->पूर्णांकcnt_value = CTLI_INTCNT_NE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cg->update |= UPDATE_IRQ_TYPE;

	वापस 0;
पूर्ण

अटल व्योम crystalcove_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	mutex_lock(&cg->buslock);
पूर्ण

अटल व्योम crystalcove_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	पूर्णांक gpio = data->hwirq;

	अगर (cg->update & UPDATE_IRQ_TYPE)
		crystalcove_update_irq_ctrl(cg, gpio);
	अगर (cg->update & UPDATE_IRQ_MASK)
		crystalcove_update_irq_mask(cg, gpio);
	cg->update = 0;

	mutex_unlock(&cg->buslock);
पूर्ण

अटल व्योम crystalcove_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	अगर (data->hwirq < CRYSTALCOVE_GPIO_NUM) अणु
		cg->set_irq_mask = false;
		cg->update |= UPDATE_IRQ_MASK;
	पूर्ण
पूर्ण

अटल व्योम crystalcove_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	अगर (data->hwirq < CRYSTALCOVE_GPIO_NUM) अणु
		cg->set_irq_mask = true;
		cg->update |= UPDATE_IRQ_MASK;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip crystalcove_irqchip = अणु
	.name			= "Crystal Cove",
	.irq_mask		= crystalcove_irq_mask,
	.irq_unmask		= crystalcove_irq_unmask,
	.irq_set_type		= crystalcove_irq_type,
	.irq_bus_lock		= crystalcove_bus_lock,
	.irq_bus_sync_unlock	= crystalcove_bus_sync_unlock,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल irqवापस_t crystalcove_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा crystalcove_gpio *cg = data;
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक p0, p1;
	पूर्णांक gpio;
	अचिन्हित पूर्णांक virq;

	अगर (regmap_पढ़ो(cg->regmap, GPIO0IRQ, &p0) ||
	    regmap_पढ़ो(cg->regmap, GPIO1IRQ, &p1))
		वापस IRQ_NONE;

	regmap_ग_लिखो(cg->regmap, GPIO0IRQ, p0);
	regmap_ग_लिखो(cg->regmap, GPIO1IRQ, p1);

	pending = p0 | p1 << 8;

	क्रम_each_set_bit(gpio, &pending, CRYSTALCOVE_GPIO_NUM) अणु
		virq = irq_find_mapping(cg->chip.irq.करोमुख्य, gpio);
		handle_nested_irq(virq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम crystalcove_gpio_dbg_show(काष्ठा seq_file *s,
				      काष्ठा gpio_chip *chip)
अणु
	काष्ठा crystalcove_gpio *cg = gpiochip_get_data(chip);
	पूर्णांक gpio, offset;
	अचिन्हित पूर्णांक ctlo, ctli, mirqs0, mirqsx, irq;

	क्रम (gpio = 0; gpio < CRYSTALCOVE_GPIO_NUM; gpio++) अणु
		regmap_पढ़ो(cg->regmap, to_reg(gpio, CTRL_OUT), &ctlo);
		regmap_पढ़ो(cg->regmap, to_reg(gpio, CTRL_IN), &ctli);
		regmap_पढ़ो(cg->regmap, gpio < 8 ? MGPIO0IRQS0 : MGPIO1IRQS0,
			    &mirqs0);
		regmap_पढ़ो(cg->regmap, gpio < 8 ? MGPIO0IRQSX : MGPIO1IRQSX,
			    &mirqsx);
		regmap_पढ़ो(cg->regmap, gpio < 8 ? GPIO0IRQ : GPIO1IRQ,
			    &irq);

		offset = gpio % 8;
		seq_म_लिखो(s, " gpio-%-2d %s %s %s %s ctlo=%2x,%s %s %s\n",
			   gpio, ctlo & CTLO_सूची_OUT ? "out" : "in ",
			   ctli & 0x1 ? "hi" : "lo",
			   ctli & CTLI_INTCNT_NE ? "fall" : "    ",
			   ctli & CTLI_INTCNT_PE ? "rise" : "    ",
			   ctlo,
			   mirqs0 & BIT(offset) ? "s0 mask  " : "s0 unmask",
			   mirqsx & BIT(offset) ? "sx mask  " : "sx unmask",
			   irq & BIT(offset) ? "pending" : "       ");
	पूर्ण
पूर्ण

अटल पूर्णांक crystalcove_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	काष्ठा crystalcove_gpio *cg;
	पूर्णांक retval;
	काष्ठा device *dev = pdev->dev.parent;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);
	काष्ठा gpio_irq_chip *girq;

	अगर (irq < 0)
		वापस irq;

	cg = devm_kzalloc(&pdev->dev, माप(*cg), GFP_KERNEL);
	अगर (!cg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cg);

	mutex_init(&cg->buslock);
	cg->chip.label = KBUILD_MODNAME;
	cg->chip.direction_input = crystalcove_gpio_dir_in;
	cg->chip.direction_output = crystalcove_gpio_dir_out;
	cg->chip.get = crystalcove_gpio_get;
	cg->chip.set = crystalcove_gpio_set;
	cg->chip.base = -1;
	cg->chip.ngpio = CRYSTALCOVE_VGPIO_NUM;
	cg->chip.can_sleep = true;
	cg->chip.parent = dev;
	cg->chip.dbg_show = crystalcove_gpio_dbg_show;
	cg->regmap = pmic->regmap;

	girq = &cg->chip.irq;
	girq->chip = &crystalcove_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;
	girq->thपढ़ोed = true;

	retval = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					   crystalcove_gpio_irq_handler,
					   IRQF_ONESHOT, KBUILD_MODNAME, cg);
	अगर (retval) अणु
		dev_warn(&pdev->dev, "request irq failed: %d\n", retval);
		वापस retval;
	पूर्ण

	retval = devm_gpiochip_add_data(&pdev->dev, &cg->chip, cg);
	अगर (retval) अणु
		dev_warn(&pdev->dev, "add gpio chip error: %d\n", retval);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver crystalcove_gpio_driver = अणु
	.probe = crystalcove_gpio_probe,
	.driver = अणु
		.name = "crystal_cove_gpio",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(crystalcove_gpio_driver);

MODULE_AUTHOR("Yang, Bin <bin.yang@intel.com>");
MODULE_DESCRIPTION("Intel Crystal Cove GPIO Driver");
MODULE_LICENSE("GPL v2");
