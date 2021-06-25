<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TQ-Systems TQMx86 PLD GPIO driver
 *
 * Based on venकरोr driver by:
 *   Vadim V.Vlasov <vvlasov@dev.rtsoft.ru>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#घोषणा TQMX86_NGPIO	8
#घोषणा TQMX86_NGPO	4	/* 0-3 - output */
#घोषणा TQMX86_NGPI	4	/* 4-7 - input */
#घोषणा TQMX86_सूची_INPUT_MASK	0xf0	/* 0-3 - output, 4-7 - input */

#घोषणा TQMX86_GPIODD	0	/* GPIO Data Direction Register */
#घोषणा TQMX86_GPIOD	1	/* GPIO Data Register */
#घोषणा TQMX86_GPIIC	3	/* GPI Interrupt Configuration Register */
#घोषणा TQMX86_GPIIS	4	/* GPI Interrupt Status Register */

#घोषणा TQMX86_GPII_FALLING	BIT(0)
#घोषणा TQMX86_GPII_RISING	BIT(1)
#घोषणा TQMX86_GPII_MASK	(BIT(0) | BIT(1))
#घोषणा TQMX86_GPII_BITS	2

काष्ठा tqmx86_gpio_data अणु
	काष्ठा gpio_chip	chip;
	काष्ठा irq_chip		irq_chip;
	व्योम __iomem		*io_base;
	पूर्णांक			irq;
	raw_spinlock_t		spinlock;
	u8			irq_type[TQMX86_NGPI];
पूर्ण;

अटल u8 tqmx86_gpio_पढ़ो(काष्ठा tqmx86_gpio_data *gd, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो8(gd->io_base + reg);
पूर्ण

अटल व्योम tqmx86_gpio_ग_लिखो(काष्ठा tqmx86_gpio_data *gd, u8 val,
			      अचिन्हित पूर्णांक reg)
अणु
	ioग_लिखो8(val, gd->io_base + reg);
पूर्ण

अटल पूर्णांक tqmx86_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(chip);

	वापस !!(tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIOD) & BIT(offset));
पूर्ण

अटल व्योम tqmx86_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u8 val;

	raw_spin_lock_irqsave(&gpio->spinlock, flags);
	val = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIOD);
	अगर (value)
		val |= BIT(offset);
	अन्यथा
		val &= ~BIT(offset);
	tqmx86_gpio_ग_लिखो(gpio, val, TQMX86_GPIOD);
	raw_spin_unlock_irqrestore(&gpio->spinlock, flags);
पूर्ण

अटल पूर्णांक tqmx86_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	/* Direction cannot be changed. Validate is an input. */
	अगर (BIT(offset) & TQMX86_सूची_INPUT_MASK)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक tqmx86_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset,
					पूर्णांक value)
अणु
	/* Direction cannot be changed, validate is an output */
	अगर (BIT(offset) & TQMX86_सूची_INPUT_MASK)
		वापस -EINVAL;

	tqmx86_gpio_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक tqmx86_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	अगर (TQMX86_सूची_INPUT_MASK & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल व्योम tqmx86_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक offset = (data->hwirq - TQMX86_NGPO);
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(
		irq_data_get_irq_chip_data(data));
	अचिन्हित दीर्घ flags;
	u8 gpiic, mask;

	mask = TQMX86_GPII_MASK << (offset * TQMX86_GPII_BITS);

	raw_spin_lock_irqsave(&gpio->spinlock, flags);
	gpiic = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIIC);
	gpiic &= ~mask;
	tqmx86_gpio_ग_लिखो(gpio, gpiic, TQMX86_GPIIC);
	raw_spin_unlock_irqrestore(&gpio->spinlock, flags);
पूर्ण

अटल व्योम tqmx86_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक offset = (data->hwirq - TQMX86_NGPO);
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(
		irq_data_get_irq_chip_data(data));
	अचिन्हित दीर्घ flags;
	u8 gpiic, mask;

	mask = TQMX86_GPII_MASK << (offset * TQMX86_GPII_BITS);

	raw_spin_lock_irqsave(&gpio->spinlock, flags);
	gpiic = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIIC);
	gpiic &= ~mask;
	gpiic |= gpio->irq_type[offset] << (offset * TQMX86_GPII_BITS);
	tqmx86_gpio_ग_लिखो(gpio, gpiic, TQMX86_GPIIC);
	raw_spin_unlock_irqrestore(&gpio->spinlock, flags);
पूर्ण

अटल पूर्णांक tqmx86_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(
		irq_data_get_irq_chip_data(data));
	अचिन्हित पूर्णांक offset = (data->hwirq - TQMX86_NGPO);
	अचिन्हित पूर्णांक edge_type = type & IRQF_TRIGGER_MASK;
	अचिन्हित दीर्घ flags;
	u8 new_type, gpiic;

	चयन (edge_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		new_type = TQMX86_GPII_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		new_type = TQMX86_GPII_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		new_type = TQMX86_GPII_FALLING | TQMX86_GPII_RISING;
		अवरोध;
	शेष:
		वापस -EINVAL; /* not supported */
	पूर्ण

	gpio->irq_type[offset] = new_type;

	raw_spin_lock_irqsave(&gpio->spinlock, flags);
	gpiic = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIIC);
	gpiic &= ~((TQMX86_GPII_MASK) << (offset * TQMX86_GPII_BITS));
	gpiic |= new_type << (offset * TQMX86_GPII_BITS);
	tqmx86_gpio_ग_लिखो(gpio, gpiic, TQMX86_GPIIC);
	raw_spin_unlock_irqrestore(&gpio->spinlock, flags);

	वापस 0;
पूर्ण

अटल व्योम tqmx86_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा tqmx86_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा irq_chip *irq_chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ irq_bits;
	पूर्णांक i = 0, child_irq;
	u8 irq_status;

	chained_irq_enter(irq_chip, desc);

	irq_status = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIIS);
	tqmx86_gpio_ग_लिखो(gpio, irq_status, TQMX86_GPIIS);

	irq_bits = irq_status;
	क्रम_each_set_bit(i, &irq_bits, TQMX86_NGPI) अणु
		child_irq = irq_find_mapping(gpio->chip.irq.करोमुख्य,
					     i + TQMX86_NGPO);
		generic_handle_irq(child_irq);
	पूर्ण

	chained_irq_निकास(irq_chip, desc);
पूर्ण

/* Minimal runसमय PM is needed by the IRQ subप्रणाली */
अटल पूर्णांक __maybe_unused tqmx86_gpio_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tqmx86_gpio_runसमय_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tqmx86_gpio_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tqmx86_gpio_runसमय_suspend,
			   tqmx86_gpio_runसमय_resume, शून्य)
पूर्ण;

अटल व्योम tqmx86_init_irq_valid_mask(काष्ठा gpio_chip *chip,
				       अचिन्हित दीर्घ *valid_mask,
				       अचिन्हित पूर्णांक ngpios)
अणु
	/* Only GPIOs 4-7 are valid क्रम पूर्णांकerrupts. Clear the others */
	clear_bit(0, valid_mask);
	clear_bit(1, valid_mask);
	clear_bit(2, valid_mask);
	clear_bit(3, valid_mask);
पूर्ण

अटल पूर्णांक tqmx86_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tqmx86_gpio_data *gpio;
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *girq;
	व्योम __iomem *io_base;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Cannot get I/O\n");
		वापस -ENODEV;
	पूर्ण

	io_base = devm_ioport_map(&pdev->dev, res->start, resource_size(res));
	अगर (!io_base)
		वापस -ENOMEM;

	gpio = devm_kzalloc(dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	raw_spin_lock_init(&gpio->spinlock);
	gpio->io_base = io_base;

	tqmx86_gpio_ग_लिखो(gpio, (u8)~TQMX86_सूची_INPUT_MASK, TQMX86_GPIODD);

	platक्रमm_set_drvdata(pdev, gpio);

	chip = &gpio->chip;
	chip->label = "gpio-tqmx86";
	chip->owner = THIS_MODULE;
	chip->can_sleep = false;
	chip->base = -1;
	chip->direction_input = tqmx86_gpio_direction_input;
	chip->direction_output = tqmx86_gpio_direction_output;
	chip->get_direction = tqmx86_gpio_get_direction;
	chip->get = tqmx86_gpio_get;
	chip->set = tqmx86_gpio_set;
	chip->ngpio = TQMX86_NGPIO;
	chip->parent = pdev->dev.parent;

	pm_runसमय_enable(&pdev->dev);

	अगर (irq) अणु
		काष्ठा irq_chip *irq_chip = &gpio->irq_chip;
		u8 irq_status;

		irq_chip->name = chip->label;
		irq_chip->parent_device = &pdev->dev;
		irq_chip->irq_mask = tqmx86_gpio_irq_mask;
		irq_chip->irq_unmask = tqmx86_gpio_irq_unmask;
		irq_chip->irq_set_type = tqmx86_gpio_irq_set_type;

		/* Mask all पूर्णांकerrupts */
		tqmx86_gpio_ग_लिखो(gpio, 0, TQMX86_GPIIC);

		/* Clear all pending पूर्णांकerrupts */
		irq_status = tqmx86_gpio_पढ़ो(gpio, TQMX86_GPIIS);
		tqmx86_gpio_ग_लिखो(gpio, irq_status, TQMX86_GPIIS);

		girq = &chip->irq;
		girq->chip = irq_chip;
		girq->parent_handler = tqmx86_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents) अणु
			ret = -ENOMEM;
			जाओ out_pm_dis;
		पूर्ण
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		girq->init_valid_mask = tqmx86_init_irq_valid_mask;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, chip, gpio);
	अगर (ret) अणु
		dev_err(dev, "Could not register GPIO chip\n");
		जाओ out_pm_dis;
	पूर्ण

	dev_info(dev, "GPIO functionality initialized with %d pins\n",
		 chip->ngpio);

	वापस 0;

out_pm_dis:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver tqmx86_gpio_driver = अणु
	.driver = अणु
		.name = "tqmx86-gpio",
		.pm = &tqmx86_gpio_dev_pm_ops,
	पूर्ण,
	.probe		= tqmx86_gpio_probe,
पूर्ण;

module_platक्रमm_driver(tqmx86_gpio_driver);

MODULE_DESCRIPTION("TQMx86 PLD GPIO Driver");
MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tqmx86-gpio");
