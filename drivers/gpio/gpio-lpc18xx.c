<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO driver क्रम NXP LPC18xx/43xx.
 *
 * Copyright (C) 2018 Vladimir Zapolskiy <vz@mleia.com>
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>

/* LPC18xx GPIO रेजिस्टर offsets */
#घोषणा LPC18XX_REG_सूची(n)	(0x2000 + n * माप(u32))

#घोषणा LPC18XX_MAX_PORTS	8
#घोषणा LPC18XX_PINS_PER_PORT	32

/* LPC18xx GPIO pin पूर्णांकerrupt controller रेजिस्टर offsets */
#घोषणा LPC18XX_GPIO_PIN_IC_ISEL	0x00
#घोषणा LPC18XX_GPIO_PIN_IC_IENR	0x04
#घोषणा LPC18XX_GPIO_PIN_IC_SIENR	0x08
#घोषणा LPC18XX_GPIO_PIN_IC_CIENR	0x0c
#घोषणा LPC18XX_GPIO_PIN_IC_IENF	0x10
#घोषणा LPC18XX_GPIO_PIN_IC_SIENF	0x14
#घोषणा LPC18XX_GPIO_PIN_IC_CIENF	0x18
#घोषणा LPC18XX_GPIO_PIN_IC_RISE	0x1c
#घोषणा LPC18XX_GPIO_PIN_IC_FALL	0x20
#घोषणा LPC18XX_GPIO_PIN_IC_IST		0x24

#घोषणा NR_LPC18XX_GPIO_PIN_IC_IRQS	8

काष्ठा lpc18xx_gpio_pin_ic अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा raw_spinlock lock;
पूर्ण;

काष्ठा lpc18xx_gpio_chip अणु
	काष्ठा gpio_chip gpio;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा lpc18xx_gpio_pin_ic *pin_ic;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत व्योम lpc18xx_gpio_pin_ic_isel(काष्ठा lpc18xx_gpio_pin_ic *ic,
					    u32 pin, bool set)
अणु
	u32 val = पढ़ोl_relaxed(ic->base + LPC18XX_GPIO_PIN_IC_ISEL);

	अगर (set)
		val &= ~BIT(pin);
	अन्यथा
		val |= BIT(pin);

	ग_लिखोl_relaxed(val, ic->base + LPC18XX_GPIO_PIN_IC_ISEL);
पूर्ण

अटल अंतरभूत व्योम lpc18xx_gpio_pin_ic_set(काष्ठा lpc18xx_gpio_pin_ic *ic,
					   u32 pin, u32 reg)
अणु
	ग_लिखोl_relaxed(BIT(pin), ic->base + reg);
पूर्ण

अटल व्योम lpc18xx_gpio_pin_ic_mask(काष्ठा irq_data *d)
अणु
	काष्ठा lpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = irqd_get_trigger_type(d);

	raw_spin_lock(&ic->lock);

	अगर (type & IRQ_TYPE_LEVEL_MASK || type & IRQ_TYPE_EDGE_RISING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_CIENR);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_CIENF);

	raw_spin_unlock(&ic->lock);

	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम lpc18xx_gpio_pin_ic_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा lpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = irqd_get_trigger_type(d);

	raw_spin_lock(&ic->lock);

	अगर (type & IRQ_TYPE_LEVEL_MASK || type & IRQ_TYPE_EDGE_RISING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENR);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENF);

	raw_spin_unlock(&ic->lock);

	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम lpc18xx_gpio_pin_ic_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा lpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = irqd_get_trigger_type(d);

	raw_spin_lock(&ic->lock);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_IST);

	raw_spin_unlock(&ic->lock);

	irq_chip_eoi_parent(d);
पूर्ण

अटल पूर्णांक lpc18xx_gpio_pin_ic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा lpc18xx_gpio_pin_ic *ic = d->chip_data;

	raw_spin_lock(&ic->lock);

	अगर (type & IRQ_TYPE_LEVEL_HIGH) अणु
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, true);
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENF);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_LEVEL_LOW) अणु
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, true);
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_CIENF);
	पूर्ण अन्यथा अणु
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, false);
	पूर्ण

	raw_spin_unlock(&ic->lock);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip lpc18xx_gpio_pin_ic = अणु
	.name		= "LPC18xx GPIO pin",
	.irq_mask	= lpc18xx_gpio_pin_ic_mask,
	.irq_unmask	= lpc18xx_gpio_pin_ic_unmask,
	.irq_eoi	= lpc18xx_gpio_pin_ic_eoi,
	.irq_set_type	= lpc18xx_gpio_pin_ic_set_type,
	.flags		= IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल पूर्णांक lpc18xx_gpio_pin_ic_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					    अचिन्हित पूर्णांक virq,
					    अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec parent_fwspec, *fwspec = data;
	काष्ठा lpc18xx_gpio_pin_ic *ic = करोमुख्य->host_data;
	irq_hw_number_t hwirq;
	पूर्णांक ret;

	अगर (nr_irqs != 1)
		वापस -EINVAL;

	hwirq = fwspec->param[0];
	अगर (hwirq >= NR_LPC18XX_GPIO_PIN_IC_IRQS)
		वापस -EINVAL;

	/*
	 * All LPC18xx/LPC43xx GPIO pin hardware पूर्णांकerrupts are translated
	 * पूर्णांकo edge पूर्णांकerrupts 32...39 on parent Cortex-M3/M4 NVIC
	 */
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 1;
	parent_fwspec.param[0] = hwirq + 32;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &parent_fwspec);
	अगर (ret < 0) अणु
		pr_err("failed to allocate parent irq %u: %d\n",
		       parent_fwspec.param[0], ret);
		वापस ret;
	पूर्ण

	वापस irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					     &lpc18xx_gpio_pin_ic, ic);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops lpc18xx_gpio_pin_ic_करोमुख्य_ops = अणु
	.alloc	= lpc18xx_gpio_pin_ic_करोमुख्य_alloc,
	.xlate	= irq_करोमुख्य_xlate_twocell,
	.मुक्त	= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक lpc18xx_gpio_pin_ic_probe(काष्ठा lpc18xx_gpio_chip *gc)
अणु
	काष्ठा device *dev = gc->gpio.parent;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा device_node *parent_node;
	काष्ठा lpc18xx_gpio_pin_ic *ic;
	काष्ठा resource res;
	पूर्णांक ret, index;

	parent_node = of_irq_find_parent(dev->of_node);
	अगर (!parent_node)
		वापस -ENXIO;

	parent_करोमुख्य = irq_find_host(parent_node);
	of_node_put(parent_node);
	अगर (!parent_करोमुख्य)
		वापस -ENXIO;

	ic = devm_kzalloc(dev, माप(*ic), GFP_KERNEL);
	अगर (!ic)
		वापस -ENOMEM;

	index = of_property_match_string(dev->of_node, "reg-names",
					 "gpio-pin-ic");
	अगर (index < 0) अणु
		ret = -ENODEV;
		जाओ मुक्त_ic;
	पूर्ण

	ret = of_address_to_resource(dev->of_node, index, &res);
	अगर (ret < 0)
		जाओ मुक्त_ic;

	ic->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(ic->base)) अणु
		ret = PTR_ERR(ic->base);
		जाओ मुक्त_ic;
	पूर्ण

	raw_spin_lock_init(&ic->lock);

	ic->करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0,
					      NR_LPC18XX_GPIO_PIN_IC_IRQS,
					      dev->of_node,
					      &lpc18xx_gpio_pin_ic_करोमुख्य_ops,
					      ic);
	अगर (!ic->करोमुख्य) अणु
		pr_err("unable to add irq domain\n");
		ret = -ENODEV;
		जाओ मुक्त_iomap;
	पूर्ण

	gc->pin_ic = ic;

	वापस 0;

मुक्त_iomap:
	devm_iounmap(dev, ic->base);
मुक्त_ic:
	devm_kमुक्त(dev, ic);

	वापस ret;
पूर्ण

अटल व्योम lpc18xx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा lpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	ग_लिखोb(value ? 1 : 0, gc->base + offset);
पूर्ण

अटल पूर्णांक lpc18xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	वापस !!पढ़ोb(gc->base + offset);
पूर्ण

अटल पूर्णांक lpc18xx_gpio_direction(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  bool out)
अणु
	काष्ठा lpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 port, pin, dir;

	port = offset / LPC18XX_PINS_PER_PORT;
	pin  = offset % LPC18XX_PINS_PER_PORT;

	spin_lock_irqsave(&gc->lock, flags);
	dir = पढ़ोl(gc->base + LPC18XX_REG_सूची(port));
	अगर (out)
		dir |= BIT(pin);
	अन्यथा
		dir &= ~BIT(pin);
	ग_लिखोl(dir, gc->base + LPC18XX_REG_सूची(port));
	spin_unlock_irqrestore(&gc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	वापस lpc18xx_gpio_direction(chip, offset, false);
पूर्ण

अटल पूर्णांक lpc18xx_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित offset, पूर्णांक value)
अणु
	lpc18xx_gpio_set(chip, offset, value);
	वापस lpc18xx_gpio_direction(chip, offset, true);
पूर्ण

अटल स्थिर काष्ठा gpio_chip lpc18xx_chip = अणु
	.label			= "lpc18xx/43xx-gpio",
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.direction_input	= lpc18xx_gpio_direction_input,
	.direction_output	= lpc18xx_gpio_direction_output,
	.set			= lpc18xx_gpio_set,
	.get			= lpc18xx_gpio_get,
	.ngpio			= LPC18XX_MAX_PORTS * LPC18XX_PINS_PER_PORT,
	.owner			= THIS_MODULE,
पूर्ण;

अटल पूर्णांक lpc18xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lpc18xx_gpio_chip *gc;
	पूर्णांक index, ret;

	gc = devm_kzalloc(dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	gc->gpio = lpc18xx_chip;
	platक्रमm_set_drvdata(pdev, gc);

	index = of_property_match_string(dev->of_node, "reg-names", "gpio");
	अगर (index < 0) अणु
		/* To support backward compatibility take the first resource */
		gc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	पूर्ण अन्यथा अणु
		काष्ठा resource res;

		ret = of_address_to_resource(dev->of_node, index, &res);
		अगर (ret < 0)
			वापस ret;

		gc->base = devm_ioremap_resource(dev, &res);
	पूर्ण
	अगर (IS_ERR(gc->base))
		वापस PTR_ERR(gc->base);

	gc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(gc->clk)) अणु
		dev_err(dev, "input clock not found\n");
		वापस PTR_ERR(gc->clk);
	पूर्ण

	ret = clk_prepare_enable(gc->clk);
	अगर (ret) अणु
		dev_err(dev, "unable to enable clock\n");
		वापस ret;
	पूर्ण

	spin_lock_init(&gc->lock);

	gc->gpio.parent = dev;

	ret = devm_gpiochip_add_data(dev, &gc->gpio, gc);
	अगर (ret) अणु
		dev_err(dev, "failed to add gpio chip\n");
		clk_disable_unprepare(gc->clk);
		वापस ret;
	पूर्ण

	/* On error GPIO pin पूर्णांकerrupt controller just won't be रेजिस्टरed */
	lpc18xx_gpio_pin_ic_probe(gc);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_gpio_chip *gc = platक्रमm_get_drvdata(pdev);

	अगर (gc->pin_ic)
		irq_करोमुख्य_हटाओ(gc->pin_ic->करोमुख्य);

	clk_disable_unprepare(gc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_gpio_match[] = अणु
	अणु .compatible = "nxp,lpc1850-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_gpio_match);

अटल काष्ठा platक्रमm_driver lpc18xx_gpio_driver = अणु
	.probe	= lpc18xx_gpio_probe,
	.हटाओ	= lpc18xx_gpio_हटाओ,
	.driver	= अणु
		.name		= "lpc18xx-gpio",
		.of_match_table	= lpc18xx_gpio_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_gpio_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_AUTHOR("Vladimir Zapolskiy <vz@mleia.com>");
MODULE_DESCRIPTION("GPIO driver for LPC18xx/43xx");
MODULE_LICENSE("GPL v2");
