<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RDA Micro GPIO driver
 *
 * Copyright (C) 2012 RDA Micro Inc.
 * Copyright (C) 2019 Manivannan Sadhasivam
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा RDA_GPIO_OEN_VAL		0x00
#घोषणा RDA_GPIO_OEN_SET_OUT		0x04
#घोषणा RDA_GPIO_OEN_SET_IN		0x08
#घोषणा RDA_GPIO_VAL			0x0c
#घोषणा RDA_GPIO_SET			0x10
#घोषणा RDA_GPIO_CLR			0x14
#घोषणा RDA_GPIO_INT_CTRL_SET		0x18
#घोषणा RDA_GPIO_INT_CTRL_CLR		0x1c
#घोषणा RDA_GPIO_INT_CLR		0x20
#घोषणा RDA_GPIO_INT_STATUS		0x24

#घोषणा RDA_GPIO_IRQ_RISE_SHIFT		0
#घोषणा RDA_GPIO_IRQ_FALL_SHIFT		8
#घोषणा RDA_GPIO_DEBOUCE_SHIFT		16
#घोषणा RDA_GPIO_LEVEL_SHIFT		24

#घोषणा RDA_GPIO_IRQ_MASK		0xff

/* Each bank consists of 32 GPIOs */
#घोषणा RDA_GPIO_BANK_NR	32

काष्ठा rda_gpio अणु
	काष्ठा gpio_chip chip;
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा irq_chip irq_chip;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत व्योम rda_gpio_update(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   u16 reg, पूर्णांक val)
अणु
	काष्ठा rda_gpio *rda_gpio = gpiochip_get_data(chip);
	व्योम __iomem *base = rda_gpio->base;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&rda_gpio->lock, flags);
	पंचांगp = पढ़ोl_relaxed(base + reg);

	अगर (val)
		पंचांगp |= BIT(offset);
	अन्यथा
		पंचांगp &= ~BIT(offset);

	ग_लिखोl_relaxed(पंचांगp, base + reg);
	spin_unlock_irqrestore(&rda_gpio->lock, flags);
पूर्ण

अटल व्योम rda_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा rda_gpio *rda_gpio = gpiochip_get_data(chip);
	व्योम __iomem *base = rda_gpio->base;
	u32 offset = irqd_to_hwirq(data);
	u32 value;

	value = BIT(offset) << RDA_GPIO_IRQ_RISE_SHIFT;
	value |= BIT(offset) << RDA_GPIO_IRQ_FALL_SHIFT;

	ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_CLR);
पूर्ण

अटल व्योम rda_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);

	rda_gpio_update(chip, offset, RDA_GPIO_INT_CLR, 1);
पूर्ण

अटल पूर्णांक rda_gpio_set_irq(काष्ठा gpio_chip *chip, u32 offset,
			    अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा rda_gpio *rda_gpio = gpiochip_get_data(chip);
	व्योम __iomem *base = rda_gpio->base;
	u32 value;

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		/* Set rising edge trigger */
		value = BIT(offset) << RDA_GPIO_IRQ_RISE_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_SET);

		/* Switch to edge trigger पूर्णांकerrupt */
		value = BIT(offset) << RDA_GPIO_LEVEL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_CLR);
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		/* Set falling edge trigger */
		value = BIT(offset) << RDA_GPIO_IRQ_FALL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_SET);

		/* Switch to edge trigger पूर्णांकerrupt */
		value = BIT(offset) << RDA_GPIO_LEVEL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_CLR);
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		/* Set both edge trigger */
		value = BIT(offset) << RDA_GPIO_IRQ_RISE_SHIFT;
		value |= BIT(offset) << RDA_GPIO_IRQ_FALL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_SET);

		/* Switch to edge trigger पूर्णांकerrupt */
		value = BIT(offset) << RDA_GPIO_LEVEL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_CLR);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		/* Set high level trigger */
		value = BIT(offset) << RDA_GPIO_IRQ_RISE_SHIFT;

		/* Switch to level trigger पूर्णांकerrupt */
		value |= BIT(offset) << RDA_GPIO_LEVEL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_SET);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		/* Set low level trigger */
		value = BIT(offset) << RDA_GPIO_IRQ_FALL_SHIFT;

		/* Switch to level trigger पूर्णांकerrupt */
		value |= BIT(offset) << RDA_GPIO_LEVEL_SHIFT;
		ग_लिखोl_relaxed(value, base + RDA_GPIO_INT_CTRL_SET);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rda_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);
	u32 trigger = irqd_get_trigger_type(data);

	rda_gpio_set_irq(chip, offset, trigger);
पूर्ण

अटल पूर्णांक rda_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);
	पूर्णांक ret;

	ret = rda_gpio_set_irq(chip, offset, flow_type);
	अगर (ret)
		वापस ret;

	अगर (flow_type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(data, handle_level_irq);
	अन्यथा अगर (flow_type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		irq_set_handler_locked(data, handle_edge_irq);

	वापस 0;
पूर्ण

अटल व्योम rda_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	काष्ठा rda_gpio *rda_gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ status;
	u32 n, girq;

	chained_irq_enter(ic, desc);

	status = पढ़ोl_relaxed(rda_gpio->base + RDA_GPIO_INT_STATUS);
	/* Only lower 8 bits are capable of generating पूर्णांकerrupts */
	status &= RDA_GPIO_IRQ_MASK;

	क्रम_each_set_bit(n, &status, RDA_GPIO_BANK_NR) अणु
		girq = irq_find_mapping(chip->irq.करोमुख्य, n);
		generic_handle_irq(girq);
	पूर्ण

	chained_irq_निकास(ic, desc);
पूर्ण

अटल पूर्णांक rda_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा rda_gpio *rda_gpio;
	u32 ngpios;
	पूर्णांक ret;

	rda_gpio = devm_kzalloc(dev, माप(*rda_gpio), GFP_KERNEL);
	अगर (!rda_gpio)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32(dev, "ngpios", &ngpios);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Not all ports have पूर्णांकerrupt capability. For instance, on
	 * RDA8810PL, GPIOC करोesn't support पूर्णांकerrupt. So we must handle
	 * those also.
	 */
	rda_gpio->irq = platक्रमm_get_irq(pdev, 0);

	rda_gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rda_gpio->base))
		वापस PTR_ERR(rda_gpio->base);

	spin_lock_init(&rda_gpio->lock);

	ret = bgpio_init(&rda_gpio->chip, dev, 4,
			 rda_gpio->base + RDA_GPIO_VAL,
			 rda_gpio->base + RDA_GPIO_SET,
			 rda_gpio->base + RDA_GPIO_CLR,
			 rda_gpio->base + RDA_GPIO_OEN_SET_OUT,
			 rda_gpio->base + RDA_GPIO_OEN_SET_IN,
			 BGPIOF_READ_OUTPUT_REG_SET);
	अगर (ret) अणु
		dev_err(dev, "bgpio_init failed\n");
		वापस ret;
	पूर्ण

	rda_gpio->chip.label = dev_name(dev);
	rda_gpio->chip.ngpio = ngpios;
	rda_gpio->chip.base = -1;
	rda_gpio->chip.parent = dev;
	rda_gpio->chip.of_node = np;

	अगर (rda_gpio->irq >= 0) अणु
		rda_gpio->irq_chip.name = "rda-gpio",
		rda_gpio->irq_chip.irq_ack = rda_gpio_irq_ack,
		rda_gpio->irq_chip.irq_mask = rda_gpio_irq_mask,
		rda_gpio->irq_chip.irq_unmask = rda_gpio_irq_unmask,
		rda_gpio->irq_chip.irq_set_type = rda_gpio_irq_set_type,
		rda_gpio->irq_chip.flags = IRQCHIP_SKIP_SET_WAKE,

		girq = &rda_gpio->chip.irq;
		girq->chip = &rda_gpio->irq_chip;
		girq->handler = handle_bad_irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->parent_handler = rda_gpio_irq_handler;
		girq->parent_handler_data = rda_gpio;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = rda_gpio->irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rda_gpio);

	वापस devm_gpiochip_add_data(dev, &rda_gpio->chip, rda_gpio);
पूर्ण

अटल स्थिर काष्ठा of_device_id rda_gpio_of_match[] = अणु
	अणु .compatible = "rda,8810pl-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rda_gpio_of_match);

अटल काष्ठा platक्रमm_driver rda_gpio_driver = अणु
	.probe = rda_gpio_probe,
	.driver = अणु
		.name = "rda-gpio",
		.of_match_table	= rda_gpio_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(rda_gpio_driver, rda_gpio_probe);

MODULE_DESCRIPTION("RDA Micro GPIO driver");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_LICENSE("GPL v2");
