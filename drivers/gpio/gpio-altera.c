<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Altera Corporation
 * Based on gpio-mpc8xxx.c
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of_gpपन.स> /* For of_mm_gpio_chip */
#समावेश <linux/platक्रमm_device.h>

#घोषणा ALTERA_GPIO_MAX_NGPIO		32
#घोषणा ALTERA_GPIO_DATA		0x0
#घोषणा ALTERA_GPIO_सूची			0x4
#घोषणा ALTERA_GPIO_IRQ_MASK		0x8
#घोषणा ALTERA_GPIO_EDGE_CAP		0xc

/**
* काष्ठा altera_gpio_chip
* @mmchip		: memory mapped chip काष्ठाure.
* @gpio_lock		: synchronization lock so that new irq/set/get requests
*			  will be blocked until the current one completes.
* @पूर्णांकerrupt_trigger	: specअगरies the hardware configured IRQ trigger type
*			  (rising, falling, both, high)
* @mapped_irq		: kernel mapped irq number.
* @irq_chip		: IRQ chip configuration
*/
काष्ठा altera_gpio_chip अणु
	काष्ठा of_mm_gpio_chip mmchip;
	raw_spinlock_t gpio_lock;
	पूर्णांक पूर्णांकerrupt_trigger;
	पूर्णांक mapped_irq;
	काष्ठा irq_chip irq_chip;
पूर्ण;

अटल व्योम altera_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा altera_gpio_chip *altera_gc;
	काष्ठा of_mm_gpio_chip *mm_gc;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकmask;

	altera_gc = gpiochip_get_data(irq_data_get_irq_chip_data(d));
	mm_gc = &altera_gc->mmchip;

	raw_spin_lock_irqsave(&altera_gc->gpio_lock, flags);
	पूर्णांकmask = पढ़ोl(mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	/* Set ALTERA_GPIO_IRQ_MASK bit to unmask */
	पूर्णांकmask |= BIT(irqd_to_hwirq(d));
	ग_लिखोl(पूर्णांकmask, mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	raw_spin_unlock_irqrestore(&altera_gc->gpio_lock, flags);
पूर्ण

अटल व्योम altera_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा altera_gpio_chip *altera_gc;
	काष्ठा of_mm_gpio_chip *mm_gc;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकmask;

	altera_gc = gpiochip_get_data(irq_data_get_irq_chip_data(d));
	mm_gc = &altera_gc->mmchip;

	raw_spin_lock_irqsave(&altera_gc->gpio_lock, flags);
	पूर्णांकmask = पढ़ोl(mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	/* Clear ALTERA_GPIO_IRQ_MASK bit to mask */
	पूर्णांकmask &= ~BIT(irqd_to_hwirq(d));
	ग_लिखोl(पूर्णांकmask, mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	raw_spin_unlock_irqrestore(&altera_gc->gpio_lock, flags);
पूर्ण

/*
 * This controller's IRQ type is synthesized in hardware, so this function
 * just checks अगर the requested set_type matches the synthesized IRQ type
 */
अटल पूर्णांक altera_gpio_irq_set_type(काष्ठा irq_data *d,
				   अचिन्हित पूर्णांक type)
अणु
	काष्ठा altera_gpio_chip *altera_gc;

	altera_gc = gpiochip_get_data(irq_data_get_irq_chip_data(d));

	अगर (type == IRQ_TYPE_NONE) अणु
		irq_set_handler_locked(d, handle_bad_irq);
		वापस 0;
	पूर्ण
	अगर (type == altera_gc->पूर्णांकerrupt_trigger) अणु
		अगर (type == IRQ_TYPE_LEVEL_HIGH)
			irq_set_handler_locked(d, handle_level_irq);
		अन्यथा
			irq_set_handler_locked(d, handle_simple_irq);
		वापस 0;
	पूर्ण
	irq_set_handler_locked(d, handle_bad_irq);
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक altera_gpio_irq_startup(काष्ठा irq_data *d)
अणु
	altera_gpio_irq_unmask(d);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc;

	mm_gc = to_of_mm_gpio_chip(gc);

	वापस !!(पढ़ोl(mm_gc->regs + ALTERA_GPIO_DATA) & BIT(offset));
पूर्ण

अटल व्योम altera_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा altera_gpio_chip *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data_reg;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&chip->gpio_lock, flags);
	data_reg = पढ़ोl(mm_gc->regs + ALTERA_GPIO_DATA);
	अगर (value)
		data_reg |= BIT(offset);
	अन्यथा
		data_reg &= ~BIT(offset);
	ग_लिखोl(data_reg, mm_gc->regs + ALTERA_GPIO_DATA);
	raw_spin_unlock_irqrestore(&chip->gpio_lock, flags);
पूर्ण

अटल पूर्णांक altera_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा altera_gpio_chip *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक gpio_ddr;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&chip->gpio_lock, flags);
	/* Set pin as input, assumes software controlled IP */
	gpio_ddr = पढ़ोl(mm_gc->regs + ALTERA_GPIO_सूची);
	gpio_ddr &= ~BIT(offset);
	ग_लिखोl(gpio_ddr, mm_gc->regs + ALTERA_GPIO_सूची);
	raw_spin_unlock_irqrestore(&chip->gpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_gpio_direction_output(काष्ठा gpio_chip *gc,
		अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा altera_gpio_chip *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data_reg, gpio_ddr;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&chip->gpio_lock, flags);
	/* Sets the GPIO value */
	data_reg = पढ़ोl(mm_gc->regs + ALTERA_GPIO_DATA);
	अगर (value)
		data_reg |= BIT(offset);
	अन्यथा
		data_reg &= ~BIT(offset);
	ग_लिखोl(data_reg, mm_gc->regs + ALTERA_GPIO_DATA);

	/* Set pin as output, assumes software controlled IP */
	gpio_ddr = पढ़ोl(mm_gc->regs + ALTERA_GPIO_सूची);
	gpio_ddr |= BIT(offset);
	ग_लिखोl(gpio_ddr, mm_gc->regs + ALTERA_GPIO_सूची);
	raw_spin_unlock_irqrestore(&chip->gpio_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम altera_gpio_irq_edge_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा altera_gpio_chip *altera_gc;
	काष्ठा irq_chip *chip;
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	अचिन्हित दीर्घ status;
	पूर्णांक i;

	altera_gc = gpiochip_get_data(irq_desc_get_handler_data(desc));
	chip = irq_desc_get_chip(desc);
	mm_gc = &altera_gc->mmchip;
	irqकरोमुख्य = altera_gc->mmchip.gc.irq.करोमुख्य;

	chained_irq_enter(chip, desc);

	जबतक ((status =
	      (पढ़ोl(mm_gc->regs + ALTERA_GPIO_EDGE_CAP) &
	      पढ़ोl(mm_gc->regs + ALTERA_GPIO_IRQ_MASK)))) अणु
		ग_लिखोl(status, mm_gc->regs + ALTERA_GPIO_EDGE_CAP);
		क्रम_each_set_bit(i, &status, mm_gc->gc.ngpio) अणु
			generic_handle_irq(irq_find_mapping(irqकरोमुख्य, i));
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम altera_gpio_irq_leveL_high_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा altera_gpio_chip *altera_gc;
	काष्ठा irq_chip *chip;
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	अचिन्हित दीर्घ status;
	पूर्णांक i;

	altera_gc = gpiochip_get_data(irq_desc_get_handler_data(desc));
	chip = irq_desc_get_chip(desc);
	mm_gc = &altera_gc->mmchip;
	irqकरोमुख्य = altera_gc->mmchip.gc.irq.करोमुख्य;

	chained_irq_enter(chip, desc);

	status = पढ़ोl(mm_gc->regs + ALTERA_GPIO_DATA);
	status &= पढ़ोl(mm_gc->regs + ALTERA_GPIO_IRQ_MASK);

	क्रम_each_set_bit(i, &status, mm_gc->gc.ngpio) अणु
		generic_handle_irq(irq_find_mapping(irqकरोमुख्य, i));
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक altera_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक reg, ret;
	काष्ठा altera_gpio_chip *altera_gc;
	काष्ठा gpio_irq_chip *girq;

	altera_gc = devm_kzalloc(&pdev->dev, माप(*altera_gc), GFP_KERNEL);
	अगर (!altera_gc)
		वापस -ENOMEM;

	raw_spin_lock_init(&altera_gc->gpio_lock);

	अगर (of_property_पढ़ो_u32(node, "altr,ngpio", &reg))
		/* By शेष assume maximum ngpio */
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	अन्यथा
		altera_gc->mmchip.gc.ngpio = reg;

	अगर (altera_gc->mmchip.gc.ngpio > ALTERA_GPIO_MAX_NGPIO) अणु
		dev_warn(&pdev->dev,
			"ngpio is greater than %d, defaulting to %d\n",
			ALTERA_GPIO_MAX_NGPIO, ALTERA_GPIO_MAX_NGPIO);
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	पूर्ण

	altera_gc->mmchip.gc.direction_input	= altera_gpio_direction_input;
	altera_gc->mmchip.gc.direction_output	= altera_gpio_direction_output;
	altera_gc->mmchip.gc.get		= altera_gpio_get;
	altera_gc->mmchip.gc.set		= altera_gpio_set;
	altera_gc->mmchip.gc.owner		= THIS_MODULE;
	altera_gc->mmchip.gc.parent		= &pdev->dev;

	altera_gc->mapped_irq = platक्रमm_get_irq_optional(pdev, 0);

	अगर (altera_gc->mapped_irq < 0)
		जाओ skip_irq;

	अगर (of_property_पढ़ो_u32(node, "altr,interrupt-type", &reg)) अणु
		dev_err(&pdev->dev,
			"altr,interrupt-type value not set in device tree\n");
		वापस -EINVAL;
	पूर्ण
	altera_gc->पूर्णांकerrupt_trigger = reg;

	altera_gc->irq_chip.name = "altera-gpio";
	altera_gc->irq_chip.irq_mask     = altera_gpio_irq_mask;
	altera_gc->irq_chip.irq_unmask   = altera_gpio_irq_unmask;
	altera_gc->irq_chip.irq_set_type = altera_gpio_irq_set_type;
	altera_gc->irq_chip.irq_startup  = altera_gpio_irq_startup;
	altera_gc->irq_chip.irq_shutकरोwn = altera_gpio_irq_mask;

	girq = &altera_gc->mmchip.gc.irq;
	girq->chip = &altera_gc->irq_chip;
	अगर (altera_gc->पूर्णांकerrupt_trigger == IRQ_TYPE_LEVEL_HIGH)
		girq->parent_handler = altera_gpio_irq_leveL_high_handler;
	अन्यथा
		girq->parent_handler = altera_gpio_irq_edge_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = altera_gc->mapped_irq;

skip_irq:
	ret = of_mm_gpiochip_add_data(node, &altera_gc->mmchip, altera_gc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed adding memory mapped gpiochip\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, altera_gc);

	वापस 0;
पूर्ण

अटल पूर्णांक altera_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_gpio_chip *altera_gc = platक्रमm_get_drvdata(pdev);

	of_mm_gpiochip_हटाओ(&altera_gc->mmchip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id altera_gpio_of_match[] = अणु
	अणु .compatible = "altr,pio-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_gpio_of_match);

अटल काष्ठा platक्रमm_driver altera_gpio_driver = अणु
	.driver = अणु
		.name	= "altera_gpio",
		.of_match_table = of_match_ptr(altera_gpio_of_match),
	पूर्ण,
	.probe		= altera_gpio_probe,
	.हटाओ		= altera_gpio_हटाओ,
पूर्ण;

अटल पूर्णांक __init altera_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&altera_gpio_driver);
पूर्ण
subsys_initcall(altera_gpio_init);

अटल व्योम __निकास altera_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&altera_gpio_driver);
पूर्ण
module_निकास(altera_gpio_निकास);

MODULE_AUTHOR("Tien Hock Loh <thloh@altera.com>");
MODULE_DESCRIPTION("Altera GPIO driver");
MODULE_LICENSE("GPL");
