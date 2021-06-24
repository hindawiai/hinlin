<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 SiFive
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>

#घोषणा SIFIVE_GPIO_INPUT_VAL	0x00
#घोषणा SIFIVE_GPIO_INPUT_EN	0x04
#घोषणा SIFIVE_GPIO_OUTPUT_EN	0x08
#घोषणा SIFIVE_GPIO_OUTPUT_VAL	0x0C
#घोषणा SIFIVE_GPIO_RISE_IE	0x18
#घोषणा SIFIVE_GPIO_RISE_IP	0x1C
#घोषणा SIFIVE_GPIO_FALL_IE	0x20
#घोषणा SIFIVE_GPIO_FALL_IP	0x24
#घोषणा SIFIVE_GPIO_HIGH_IE	0x28
#घोषणा SIFIVE_GPIO_HIGH_IP	0x2C
#घोषणा SIFIVE_GPIO_LOW_IE	0x30
#घोषणा SIFIVE_GPIO_LOW_IP	0x34
#घोषणा SIFIVE_GPIO_OUTPUT_XOR	0x40

#घोषणा SIFIVE_GPIO_MAX		32

काष्ठा sअगरive_gpio अणु
	व्योम __iomem		*base;
	काष्ठा gpio_chip	gc;
	काष्ठा regmap		*regs;
	अचिन्हित दीर्घ		irq_state;
	अचिन्हित पूर्णांक		trigger[SIFIVE_GPIO_MAX];
	अचिन्हित पूर्णांक		irq_number[SIFIVE_GPIO_MAX];
पूर्ण;

अटल व्योम sअगरive_gpio_set_ie(काष्ठा sअगरive_gpio *chip, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trigger;

	spin_lock_irqsave(&chip->gc.bgpio_lock, flags);
	trigger = (chip->irq_state & BIT(offset)) ? chip->trigger[offset] : 0;
	regmap_update_bits(chip->regs, SIFIVE_GPIO_RISE_IE, BIT(offset),
			   (trigger & IRQ_TYPE_EDGE_RISING) ? BIT(offset) : 0);
	regmap_update_bits(chip->regs, SIFIVE_GPIO_FALL_IE, BIT(offset),
			   (trigger & IRQ_TYPE_EDGE_FALLING) ? BIT(offset) : 0);
	regmap_update_bits(chip->regs, SIFIVE_GPIO_HIGH_IE, BIT(offset),
			   (trigger & IRQ_TYPE_LEVEL_HIGH) ? BIT(offset) : 0);
	regmap_update_bits(chip->regs, SIFIVE_GPIO_LOW_IE, BIT(offset),
			   (trigger & IRQ_TYPE_LEVEL_LOW) ? BIT(offset) : 0);
	spin_unlock_irqrestore(&chip->gc.bgpio_lock, flags);
पूर्ण

अटल पूर्णांक sअगरive_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक trigger)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sअगरive_gpio *chip = gpiochip_get_data(gc);
	पूर्णांक offset = irqd_to_hwirq(d);

	अगर (offset < 0 || offset >= gc->ngpio)
		वापस -EINVAL;

	chip->trigger[offset] = trigger;
	sअगरive_gpio_set_ie(chip, offset);
	वापस 0;
पूर्ण

अटल व्योम sअगरive_gpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sअगरive_gpio *chip = gpiochip_get_data(gc);
	पूर्णांक offset = irqd_to_hwirq(d) % SIFIVE_GPIO_MAX;
	u32 bit = BIT(offset);
	अचिन्हित दीर्घ flags;

	irq_chip_enable_parent(d);

	/* Switch to input */
	gc->direction_input(gc, offset);

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	/* Clear any sticky pending पूर्णांकerrupts */
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_RISE_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_FALL_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_HIGH_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_LOW_IP, bit);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	/* Enable पूर्णांकerrupts */
	assign_bit(offset, &chip->irq_state, 1);
	sअगरive_gpio_set_ie(chip, offset);
पूर्ण

अटल व्योम sअगरive_gpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sअगरive_gpio *chip = gpiochip_get_data(gc);
	पूर्णांक offset = irqd_to_hwirq(d) % SIFIVE_GPIO_MAX;

	assign_bit(offset, &chip->irq_state, 0);
	sअगरive_gpio_set_ie(chip, offset);
	irq_chip_disable_parent(d);
पूर्ण

अटल व्योम sअगरive_gpio_irq_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sअगरive_gpio *chip = gpiochip_get_data(gc);
	पूर्णांक offset = irqd_to_hwirq(d) % SIFIVE_GPIO_MAX;
	u32 bit = BIT(offset);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	/* Clear all pending पूर्णांकerrupts */
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_RISE_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_FALL_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_HIGH_IP, bit);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_LOW_IP, bit);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	irq_chip_eoi_parent(d);
पूर्ण

अटल पूर्णांक sअगरive_gpio_irq_set_affinity(काष्ठा irq_data *data,
					स्थिर काष्ठा cpumask *dest,
					bool क्रमce)
अणु
	अगर (data->parent_data)
		वापस irq_chip_set_affinity_parent(data, dest, क्रमce);

	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip sअगरive_gpio_irqchip = अणु
	.name		= "sifive-gpio",
	.irq_set_type	= sअगरive_gpio_irq_set_type,
	.irq_mask	= irq_chip_mask_parent,
	.irq_unmask	= irq_chip_unmask_parent,
	.irq_enable	= sअगरive_gpio_irq_enable,
	.irq_disable	= sअगरive_gpio_irq_disable,
	.irq_eoi	= sअगरive_gpio_irq_eoi,
	.irq_set_affinity = sअगरive_gpio_irq_set_affinity,
पूर्ण;

अटल पूर्णांक sअगरive_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *gc,
					     अचिन्हित पूर्णांक child,
					     अचिन्हित पूर्णांक child_type,
					     अचिन्हित पूर्णांक *parent,
					     अचिन्हित पूर्णांक *parent_type)
अणु
	काष्ठा sअगरive_gpio *chip = gpiochip_get_data(gc);
	काष्ठा irq_data *d = irq_get_irq_data(chip->irq_number[child]);

	*parent_type = IRQ_TYPE_NONE;
	*parent = irqd_to_hwirq(d);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config sअगरive_gpio_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
	.disable_locking = true,
पूर्ण;

अटल पूर्णांक sअगरive_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *irq_parent;
	काष्ठा irq_करोमुख्य *parent;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा sअगरive_gpio *chip;
	पूर्णांक ret, ngpio, i;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base)) अणु
		dev_err(dev, "failed to allocate device memory\n");
		वापस PTR_ERR(chip->base);
	पूर्ण

	chip->regs = devm_regmap_init_mmio(dev, chip->base,
					   &sअगरive_gpio_regmap_config);
	अगर (IS_ERR(chip->regs))
		वापस PTR_ERR(chip->regs);

	ngpio = of_irq_count(node);
	अगर (ngpio > SIFIVE_GPIO_MAX) अणु
		dev_err(dev, "Too many GPIO interrupts (max=%d)\n",
			SIFIVE_GPIO_MAX);
		वापस -ENXIO;
	पूर्ण

	irq_parent = of_irq_find_parent(node);
	अगर (!irq_parent) अणु
		dev_err(dev, "no IRQ parent node\n");
		वापस -ENODEV;
	पूर्ण
	parent = irq_find_host(irq_parent);
	अगर (!parent) अणु
		dev_err(dev, "no IRQ parent domain\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ngpio; i++)
		chip->irq_number[i] = platक्रमm_get_irq(pdev, i);

	ret = bgpio_init(&chip->gc, dev, 4,
			 chip->base + SIFIVE_GPIO_INPUT_VAL,
			 chip->base + SIFIVE_GPIO_OUTPUT_VAL,
			 शून्य,
			 chip->base + SIFIVE_GPIO_OUTPUT_EN,
			 chip->base + SIFIVE_GPIO_INPUT_EN,
			 0);
	अगर (ret) अणु
		dev_err(dev, "unable to init generic GPIO\n");
		वापस ret;
	पूर्ण

	/* Disable all GPIO पूर्णांकerrupts beक्रमe enabling parent पूर्णांकerrupts */
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_RISE_IE, 0);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_FALL_IE, 0);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_HIGH_IE, 0);
	regmap_ग_लिखो(chip->regs, SIFIVE_GPIO_LOW_IE, 0);
	chip->irq_state = 0;

	chip->gc.base = -1;
	chip->gc.ngpio = ngpio;
	chip->gc.label = dev_name(dev);
	chip->gc.parent = dev;
	chip->gc.owner = THIS_MODULE;
	girq = &chip->gc.irq;
	girq->chip = &sअगरive_gpio_irqchip;
	girq->fwnode = of_node_to_fwnode(node);
	girq->parent_करोमुख्य = parent;
	girq->child_to_parent_hwirq = sअगरive_gpio_child_to_parent_hwirq;
	girq->handler = handle_bad_irq;
	girq->शेष_type = IRQ_TYPE_NONE;

	platक्रमm_set_drvdata(pdev, chip);
	वापस gpiochip_add_data(&chip->gc, chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id sअगरive_gpio_match[] = अणु
	अणु .compatible = "sifive,gpio0" पूर्ण,
	अणु .compatible = "sifive,fu540-c000-gpio" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sअगरive_gpio_driver = अणु
	.probe		= sअगरive_gpio_probe,
	.driver = अणु
		.name	= "sifive_gpio",
		.of_match_table = of_match_ptr(sअगरive_gpio_match),
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sअगरive_gpio_driver)
