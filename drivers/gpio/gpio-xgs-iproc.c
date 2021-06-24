<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Broadcom
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा IPROC_CCA_INT_F_GPIOINT		BIT(0)
#घोषणा IPROC_CCA_INT_STS		0x20
#घोषणा IPROC_CCA_INT_MASK		0x24

#घोषणा IPROC_GPIO_CCA_DIN		0x0
#घोषणा IPROC_GPIO_CCA_DOUT		0x4
#घोषणा IPROC_GPIO_CCA_OUT_EN		0x8
#घोषणा IPROC_GPIO_CCA_INT_LEVEL	0x10
#घोषणा IPROC_GPIO_CCA_INT_LEVEL_MASK	0x14
#घोषणा IPROC_GPIO_CCA_INT_EVENT	0x18
#घोषणा IPROC_GPIO_CCA_INT_EVENT_MASK	0x1C
#घोषणा IPROC_GPIO_CCA_INT_EDGE		0x24

काष्ठा iproc_gpio_chip अणु
	काष्ठा irq_chip irqchip;
	काष्ठा gpio_chip gc;
	spinlock_t lock;
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *पूर्णांकr;
पूर्ण;

अटल अंतरभूत काष्ठा iproc_gpio_chip *
to_iproc_gpio(काष्ठा gpio_chip *gc)
अणु
	वापस container_of(gc, काष्ठा iproc_gpio_chip, gc);
पूर्ण

अटल व्योम iproc_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio_chip *chip = to_iproc_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 irq = d->irq;
	u32 irq_type, event_status = 0;

	spin_lock_irqsave(&chip->lock, flags);
	irq_type = irq_get_trigger_type(irq);
	अगर (irq_type & IRQ_TYPE_EDGE_BOTH) अणु
		event_status |= BIT(pin);
		ग_लिखोl_relaxed(event_status,
			       chip->base + IPROC_GPIO_CCA_INT_EVENT);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम iproc_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio_chip *chip = to_iproc_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 irq = d->irq;
	u32 पूर्णांक_mask, irq_type, event_mask;

	spin_lock_irqsave(&chip->lock, flags);
	irq_type = irq_get_trigger_type(irq);
	event_mask = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EVENT_MASK);
	पूर्णांक_mask = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL_MASK);

	अगर (irq_type & IRQ_TYPE_EDGE_BOTH) अणु
		event_mask |= 1 << pin;
		ग_लिखोl_relaxed(event_mask,
			       chip->base + IPROC_GPIO_CCA_INT_EVENT_MASK);
	पूर्ण अन्यथा अणु
		पूर्णांक_mask |= 1 << pin;
		ग_लिखोl_relaxed(पूर्णांक_mask,
			       chip->base + IPROC_GPIO_CCA_INT_LEVEL_MASK);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम iproc_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio_chip *chip = to_iproc_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 irq = d->irq;
	u32 irq_type, पूर्णांक_mask, event_mask;

	spin_lock_irqsave(&chip->lock, flags);
	irq_type = irq_get_trigger_type(irq);
	event_mask = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EVENT_MASK);
	पूर्णांक_mask = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL_MASK);

	अगर (irq_type & IRQ_TYPE_EDGE_BOTH) अणु
		event_mask &= ~BIT(pin);
		ग_लिखोl_relaxed(event_mask,
			       chip->base + IPROC_GPIO_CCA_INT_EVENT_MASK);
	पूर्ण अन्यथा अणु
		पूर्णांक_mask &= ~BIT(pin);
		ग_लिखोl_relaxed(पूर्णांक_mask,
			       chip->base + IPROC_GPIO_CCA_INT_LEVEL_MASK);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक iproc_gpio_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा iproc_gpio_chip *chip = to_iproc_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 irq = d->irq;
	u32 event_pol, पूर्णांक_pol;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&chip->lock, flags);
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		event_pol = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EDGE);
		event_pol &= ~BIT(pin);
		ग_लिखोl_relaxed(event_pol, chip->base + IPROC_GPIO_CCA_INT_EDGE);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		event_pol = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EDGE);
		event_pol |= BIT(pin);
		ग_लिखोl_relaxed(event_pol, chip->base + IPROC_GPIO_CCA_INT_EDGE);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		पूर्णांक_pol = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL);
		पूर्णांक_pol &= ~BIT(pin);
		ग_लिखोl_relaxed(पूर्णांक_pol, chip->base + IPROC_GPIO_CCA_INT_LEVEL);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		पूर्णांक_pol = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL);
		पूर्णांक_pol |= BIT(pin);
		ग_लिखोl_relaxed(पूर्णांक_pol, chip->base + IPROC_GPIO_CCA_INT_LEVEL);
		अवरोध;
	शेष:
		/* should not come here */
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(irq_get_irq_data(irq), handle_level_irq);
	अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(irq_get_irq_data(irq), handle_edge_irq);

out_unlock:
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस ret;
पूर्ण

अटल irqवापस_t iproc_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gpio_chip *gc = (काष्ठा gpio_chip *)data;
	काष्ठा iproc_gpio_chip *chip = to_iproc_gpio(gc);
	पूर्णांक bit;
	अचिन्हित दीर्घ पूर्णांक_bits = 0;
	u32 पूर्णांक_status;

	/* go through the entire GPIOs and handle all पूर्णांकerrupts */
	पूर्णांक_status = पढ़ोl_relaxed(chip->पूर्णांकr + IPROC_CCA_INT_STS);
	अगर (पूर्णांक_status & IPROC_CCA_INT_F_GPIOINT) अणु
		u32 event, level;

		/* Get level and edge पूर्णांकerrupts */
		event =
		    पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EVENT_MASK);
		event &= पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_EVENT);
		level = पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_DIN);
		level ^= पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL);
		level &=
		    पढ़ोl_relaxed(chip->base + IPROC_GPIO_CCA_INT_LEVEL_MASK);
		पूर्णांक_bits = level | event;

		क्रम_each_set_bit(bit, &पूर्णांक_bits, gc->ngpio)
			generic_handle_irq(irq_linear_revmap(gc->irq.करोमुख्य, bit));
	पूर्ण

	वापस पूर्णांक_bits ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक iproc_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा iproc_gpio_chip *chip;
	u32 num_gpios;
	पूर्णांक irq, ret;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = dev;
	platक्रमm_set_drvdata(pdev, chip);
	spin_lock_init(&chip->lock);

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base))
		वापस PTR_ERR(chip->base);

	ret = bgpio_init(&chip->gc, dev, 4,
			 chip->base + IPROC_GPIO_CCA_DIN,
			 chip->base + IPROC_GPIO_CCA_DOUT,
			 शून्य,
			 chip->base + IPROC_GPIO_CCA_OUT_EN,
			 शून्य,
			 0);
	अगर (ret) अणु
		dev_err(dev, "unable to init GPIO chip\n");
		वापस ret;
	पूर्ण

	chip->gc.label = dev_name(dev);
	अगर (of_property_पढ़ो_u32(dn, "ngpios", &num_gpios))
		chip->gc.ngpio = num_gpios;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;
		काष्ठा irq_chip *irqc;
		u32 val;

		irqc = &chip->irqchip;
		irqc->name = dev_name(dev);
		irqc->irq_ack = iproc_gpio_irq_ack;
		irqc->irq_mask = iproc_gpio_irq_mask;
		irqc->irq_unmask = iproc_gpio_irq_unmask;
		irqc->irq_set_type = iproc_gpio_irq_set_type;

		chip->पूर्णांकr = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(chip->पूर्णांकr))
			वापस PTR_ERR(chip->पूर्णांकr);

		/* Enable GPIO पूर्णांकerrupts क्रम CCA GPIO */
		val = पढ़ोl_relaxed(chip->पूर्णांकr + IPROC_CCA_INT_MASK);
		val |= IPROC_CCA_INT_F_GPIOINT;
		ग_लिखोl_relaxed(val, chip->पूर्णांकr + IPROC_CCA_INT_MASK);

		/*
		 * Directly request the irq here instead of passing
		 * a flow-handler because the irq is shared.
		 */
		ret = devm_request_irq(dev, irq, iproc_gpio_irq_handler,
				       IRQF_SHARED, chip->gc.label, &chip->gc);
		अगर (ret) अणु
			dev_err(dev, "Fail to request IRQ%d: %d\n", irq, ret);
			वापस ret;
		पूर्ण

		girq = &chip->gc.irq;
		girq->chip = irqc;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &chip->gc, chip);
	अगर (ret) अणु
		dev_err(dev, "unable to add GPIO chip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_gpio_chip *chip;

	chip = platक्रमm_get_drvdata(pdev);
	अगर (!chip)
		वापस -ENODEV;

	अगर (chip->पूर्णांकr) अणु
		u32 val;

		val = पढ़ोl_relaxed(chip->पूर्णांकr + IPROC_CCA_INT_MASK);
		val &= ~IPROC_CCA_INT_F_GPIOINT;
		ग_लिखोl_relaxed(val, chip->पूर्णांकr + IPROC_CCA_INT_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_iproc_gpio_of_match[] = अणु
	अणु .compatible = "brcm,iproc-gpio-cca" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_iproc_gpio_of_match);

अटल काष्ठा platक्रमm_driver bcm_iproc_gpio_driver = अणु
	.driver = अणु
		.name = "iproc-xgs-gpio",
		.of_match_table = bcm_iproc_gpio_of_match,
	पूर्ण,
	.probe = iproc_gpio_probe,
	.हटाओ = iproc_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm_iproc_gpio_driver);

MODULE_DESCRIPTION("XGS IPROC GPIO driver");
MODULE_LICENSE("GPL v2");
