<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71XX/AR724X/AR913X GPIO API support
 *
 *  Copyright (C) 2015 Alban Bedel <albeu@मुक्त.fr>
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_data/gpio-ath79.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>

#घोषणा AR71XX_GPIO_REG_OE		0x00
#घोषणा AR71XX_GPIO_REG_IN		0x04
#घोषणा AR71XX_GPIO_REG_SET		0x0c
#घोषणा AR71XX_GPIO_REG_CLEAR		0x10

#घोषणा AR71XX_GPIO_REG_INT_ENABLE	0x14
#घोषणा AR71XX_GPIO_REG_INT_TYPE	0x18
#घोषणा AR71XX_GPIO_REG_INT_POLARITY	0x1c
#घोषणा AR71XX_GPIO_REG_INT_PENDING	0x20
#घोषणा AR71XX_GPIO_REG_INT_MASK	0x24

काष्ठा ath79_gpio_ctrl अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *base;
	raw_spinlock_t lock;
	अचिन्हित दीर्घ both_edges;
पूर्ण;

अटल काष्ठा ath79_gpio_ctrl *irq_data_to_ath79_gpio(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);

	वापस container_of(gc, काष्ठा ath79_gpio_ctrl, gc);
पूर्ण

अटल u32 ath79_gpio_पढ़ो(काष्ठा ath79_gpio_ctrl *ctrl, अचिन्हित reg)
अणु
	वापस पढ़ोl(ctrl->base + reg);
पूर्ण

अटल व्योम ath79_gpio_ग_लिखो(काष्ठा ath79_gpio_ctrl *ctrl,
			अचिन्हित reg, u32 val)
अणु
	ग_लिखोl(val, ctrl->base + reg);
पूर्ण

अटल bool ath79_gpio_update_bits(
	काष्ठा ath79_gpio_ctrl *ctrl, अचिन्हित reg, u32 mask, u32 bits)
अणु
	u32 old_val, new_val;

	old_val = ath79_gpio_पढ़ो(ctrl, reg);
	new_val = (old_val & ~mask) | (bits & mask);

	अगर (new_val != old_val)
		ath79_gpio_ग_लिखो(ctrl, reg, new_val);

	वापस new_val != old_val;
पूर्ण

अटल व्योम ath79_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_MASK, mask, mask);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल व्योम ath79_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_MASK, mask, 0);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल व्योम ath79_gpio_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_ENABLE, mask, mask);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_MASK, mask, mask);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल व्योम ath79_gpio_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_MASK, mask, 0);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_ENABLE, mask, 0);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल पूर्णांक ath79_gpio_irq_set_type(काष्ठा irq_data *data,
				अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	u32 type = 0, polarity = 0;
	अचिन्हित दीर्घ flags;
	bool disabled;

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		polarity |= mask;
		fallthrough;
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		polarity |= mask;
		fallthrough;
	हाल IRQ_TYPE_LEVEL_LOW:
		type |= mask;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&ctrl->lock, flags);

	अगर (flow_type == IRQ_TYPE_EDGE_BOTH) अणु
		ctrl->both_edges |= mask;
		polarity = ~ath79_gpio_पढ़ो(ctrl, AR71XX_GPIO_REG_IN);
	पूर्ण अन्यथा अणु
		ctrl->both_edges &= ~mask;
	पूर्ण

	/* As the IRQ configuration can't be loaded atomically we
	 * have to disable the पूर्णांकerrupt जबतक the configuration state
	 * is invalid.
	 */
	disabled = ath79_gpio_update_bits(
		ctrl, AR71XX_GPIO_REG_INT_ENABLE, mask, 0);

	ath79_gpio_update_bits(
		ctrl, AR71XX_GPIO_REG_INT_TYPE, mask, type);
	ath79_gpio_update_bits(
		ctrl, AR71XX_GPIO_REG_INT_POLARITY, mask, polarity);

	अगर (disabled)
		ath79_gpio_update_bits(
			ctrl, AR71XX_GPIO_REG_INT_ENABLE, mask, mask);

	raw_spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ath79_gpio_irqchip = अणु
	.name = "gpio-ath79",
	.irq_enable = ath79_gpio_irq_enable,
	.irq_disable = ath79_gpio_irq_disable,
	.irq_mask = ath79_gpio_irq_mask,
	.irq_unmask = ath79_gpio_irq_unmask,
	.irq_set_type = ath79_gpio_irq_set_type,
पूर्ण;

अटल व्योम ath79_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	काष्ठा ath79_gpio_ctrl *ctrl =
		container_of(gc, काष्ठा ath79_gpio_ctrl, gc);
	अचिन्हित दीर्घ flags, pending;
	u32 both_edges, state;
	पूर्णांक irq;

	chained_irq_enter(irqchip, desc);

	raw_spin_lock_irqsave(&ctrl->lock, flags);

	pending = ath79_gpio_पढ़ो(ctrl, AR71XX_GPIO_REG_INT_PENDING);

	/* Update the polarity of the both edges irqs */
	both_edges = ctrl->both_edges & pending;
	अगर (both_edges) अणु
		state = ath79_gpio_पढ़ो(ctrl, AR71XX_GPIO_REG_IN);
		ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_POLARITY,
				both_edges, ~state);
	पूर्ण

	raw_spin_unlock_irqrestore(&ctrl->lock, flags);

	अगर (pending) अणु
		क्रम_each_set_bit(irq, &pending, gc->ngpio)
			generic_handle_irq(
				irq_linear_revmap(gc->irq.करोमुख्य, irq));
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल स्थिर काष्ठा of_device_id ath79_gpio_of_match[] = अणु
	अणु .compatible = "qca,ar7100-gpio" पूर्ण,
	अणु .compatible = "qca,ar9340-gpio" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ath79_gpio_of_match);

अटल पूर्णांक ath79_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath79_gpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ath79_gpio_ctrl *ctrl;
	काष्ठा gpio_irq_chip *girq;
	u32 ath79_gpio_count;
	bool oe_inverted;
	पूर्णांक err;

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, ctrl);

	अगर (np) अणु
		err = of_property_पढ़ो_u32(np, "ngpios", &ath79_gpio_count);
		अगर (err) अणु
			dev_err(dev, "ngpios property is not valid\n");
			वापस err;
		पूर्ण
		oe_inverted = of_device_is_compatible(np, "qca,ar9340-gpio");
	पूर्ण अन्यथा अगर (pdata) अणु
		ath79_gpio_count = pdata->ngpios;
		oe_inverted = pdata->oe_inverted;
	पूर्ण अन्यथा अणु
		dev_err(dev, "No DT node or platform data found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ath79_gpio_count >= 32) अणु
		dev_err(dev, "ngpios must be less than 32\n");
		वापस -EINVAL;
	पूर्ण

	ctrl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	raw_spin_lock_init(&ctrl->lock);
	err = bgpio_init(&ctrl->gc, dev, 4,
			ctrl->base + AR71XX_GPIO_REG_IN,
			ctrl->base + AR71XX_GPIO_REG_SET,
			ctrl->base + AR71XX_GPIO_REG_CLEAR,
			oe_inverted ? शून्य : ctrl->base + AR71XX_GPIO_REG_OE,
			oe_inverted ? ctrl->base + AR71XX_GPIO_REG_OE : शून्य,
			0);
	अगर (err) अणु
		dev_err(dev, "bgpio_init failed\n");
		वापस err;
	पूर्ण
	/* Use base 0 to stay compatible with legacy platक्रमms */
	ctrl->gc.base = 0;

	/* Optional पूर्णांकerrupt setup */
	अगर (!np || of_property_पढ़ो_bool(np, "interrupt-controller")) अणु
		girq = &ctrl->gc.irq;
		girq->chip = &ath79_gpio_irqchip;
		girq->parent_handler = ath79_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = platक्रमm_get_irq(pdev, 0);
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
	पूर्ण

	err = devm_gpiochip_add_data(dev, &ctrl->gc, ctrl);
	अगर (err) अणु
		dev_err(dev,
			"cannot add AR71xx GPIO chip, error=%d", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ath79_gpio_driver = अणु
	.driver = अणु
		.name = "ath79-gpio",
		.of_match_table	= ath79_gpio_of_match,
	पूर्ण,
	.probe = ath79_gpio_probe,
पूर्ण;

module_platक्रमm_driver(ath79_gpio_driver);

MODULE_DESCRIPTION("Atheros AR71XX/AR724X/AR913X GPIO API support");
MODULE_LICENSE("GPL v2");
