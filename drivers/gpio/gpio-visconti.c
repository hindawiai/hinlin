<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Toshiba Visconti GPIO Support
 *
 * (C) Copyright 2020 Toshiba Electronic Devices & Storage Corporation
 * (C) Copyright 2020 TOSHIBA CORPORATION
 *
 * Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>

/* रेजिस्टर offset */
#घोषणा GPIO_सूची	0x00
#घोषणा GPIO_IDATA	0x08
#घोषणा GPIO_ODATA	0x10
#घोषणा GPIO_OSET	0x18
#घोषणा GPIO_OCLR	0x20
#घोषणा GPIO_INTMODE	0x30

#घोषणा BASE_HW_IRQ 24

काष्ठा visconti_gpio अणु
	व्योम __iomem *base;
	spinlock_t lock; /* protect gpio रेजिस्टर */
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
पूर्ण;

अटल पूर्णांक visconti_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा visconti_gpio *priv = gpiochip_get_data(gc);
	u32 offset = irqd_to_hwirq(d);
	u32 bit = BIT(offset);
	u32 पूर्णांकc_type = IRQ_TYPE_EDGE_RISING;
	u32 पूर्णांकmode, odata;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	odata = पढ़ोl(priv->base + GPIO_ODATA);
	पूर्णांकmode = पढ़ोl(priv->base + GPIO_INTMODE);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		odata &= ~bit;
		पूर्णांकmode &= ~bit;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		odata |= bit;
		पूर्णांकmode &= ~bit;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		पूर्णांकmode |= bit;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		पूर्णांकc_type = IRQ_TYPE_LEVEL_HIGH;
		odata &= ~bit;
		पूर्णांकmode &= ~bit;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		पूर्णांकc_type = IRQ_TYPE_LEVEL_HIGH;
		odata |= bit;
		पूर्णांकmode &= ~bit;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ग_लिखोl(odata, priv->base + GPIO_ODATA);
	ग_लिखोl(पूर्णांकmode, priv->base + GPIO_INTMODE);
	irq_set_irq_type(offset, पूर्णांकc_type);

	ret = irq_chip_set_type_parent(d, type);
err:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक visconti_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *gc,
					       अचिन्हित पूर्णांक child,
					       अचिन्हित पूर्णांक child_type,
					       अचिन्हित पूर्णांक *parent,
					       अचिन्हित पूर्णांक *parent_type)
अणु
	/* Interrupts 0..15 mapped to पूर्णांकerrupts 24..39 on the GIC */
	अगर (child < 16) अणु
		/* All these पूर्णांकerrupts are level high in the CPU */
		*parent_type = IRQ_TYPE_LEVEL_HIGH;
		*parent = child + BASE_HW_IRQ;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम *visconti_gpio_populate_parent_fwspec(काष्ठा gpio_chip *chip,
						  अचिन्हित पूर्णांक parent_hwirq,
						  अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = chip->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 3;
	fwspec->param[0] = 0;
	fwspec->param[1] = parent_hwirq;
	fwspec->param[2] = parent_type;

	वापस fwspec;
पूर्ण

अटल पूर्णांक visconti_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा visconti_gpio *priv;
	काष्ठा irq_chip *irq_chip;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा irq_करोमुख्य *parent;
	काष्ठा device_node *irq_parent;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	irq_parent = of_irq_find_parent(dev->of_node);
	अगर (!irq_parent) अणु
		dev_err(dev, "No IRQ parent node\n");
		वापस -ENODEV;
	पूर्ण

	parent = irq_find_host(irq_parent);
	अगर (!parent) अणु
		dev_err(dev, "No IRQ parent domain\n");
		वापस -ENODEV;
	पूर्ण

	fwnode = of_node_to_fwnode(irq_parent);
	of_node_put(irq_parent);

	ret = bgpio_init(&priv->gpio_chip, dev, 4,
			 priv->base + GPIO_IDATA,
			 priv->base + GPIO_OSET,
			 priv->base + GPIO_OCLR,
			 priv->base + GPIO_सूची,
			 शून्य,
			 0);
	अगर (ret) अणु
		dev_err(dev, "unable to init generic GPIO\n");
		वापस ret;
	पूर्ण

	irq_chip = &priv->irq_chip;
	irq_chip->name = dev_name(dev);
	irq_chip->irq_mask = irq_chip_mask_parent;
	irq_chip->irq_unmask = irq_chip_unmask_parent;
	irq_chip->irq_eoi = irq_chip_eoi_parent;
	irq_chip->irq_set_type = visconti_gpio_irq_set_type;
	irq_chip->flags = IRQCHIP_SET_TYPE_MASKED | IRQCHIP_MASK_ON_SUSPEND;

	girq = &priv->gpio_chip.irq;
	girq->chip = irq_chip;
	girq->fwnode = fwnode;
	girq->parent_करोमुख्य = parent;
	girq->child_to_parent_hwirq = visconti_gpio_child_to_parent_hwirq;
	girq->populate_parent_alloc_arg = visconti_gpio_populate_parent_fwspec;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	ret = devm_gpiochip_add_data(dev, &priv->gpio_chip, priv);
	अगर (ret) अणु
		dev_err(dev, "failed to add GPIO chip\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id visconti_gpio_of_match[] = अणु
	अणु .compatible = "toshiba,gpio-tmpv7708", पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, visconti_gpio_of_match);

अटल काष्ठा platक्रमm_driver visconti_gpio_driver = अणु
	.probe		= visconti_gpio_probe,
	.driver		= अणु
		.name	= "visconti_gpio",
		.of_match_table = of_match_ptr(visconti_gpio_of_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(visconti_gpio_driver);

MODULE_AUTHOR("Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>");
MODULE_DESCRIPTION("Toshiba Visconti GPIO Driver");
MODULE_LICENSE("GPL v2");
