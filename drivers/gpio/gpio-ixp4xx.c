<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// IXP4 GPIO driver
// Copyright (C) 2019 Linus Walleij <linus.walleij@linaro.org>
//
// based on previous work and know-how from:
// Deepak Saxena <dsaxena@plनिकासy.net>

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
/* Include that go away with DT transition */
#समावेश <linux/irqchip/irq-ixp4xx.h>

#समावेश <यंत्र/mach-types.h>

#घोषणा IXP4XX_REG_GPOUT	0x00
#घोषणा IXP4XX_REG_GPOE		0x04
#घोषणा IXP4XX_REG_GPIN		0x08
#घोषणा IXP4XX_REG_GPIS		0x0C
#घोषणा IXP4XX_REG_GPIT1	0x10
#घोषणा IXP4XX_REG_GPIT2	0x14
#घोषणा IXP4XX_REG_GPCLK	0x18
#घोषणा IXP4XX_REG_GPDBSEL	0x1C

/*
 * The hardware uses 3 bits to indicate पूर्णांकerrupt "style".
 * we clear and set these three bits accordingly. The lower 24
 * bits in two रेजिस्टरs (GPIT1 and GPIT2) are used to set up
 * the style क्रम 8 lines each क्रम a total of 16 GPIO lines.
 */
#घोषणा IXP4XX_GPIO_STYLE_ACTIVE_HIGH	0x0
#घोषणा IXP4XX_GPIO_STYLE_ACTIVE_LOW	0x1
#घोषणा IXP4XX_GPIO_STYLE_RISING_EDGE	0x2
#घोषणा IXP4XX_GPIO_STYLE_FALLING_EDGE	0x3
#घोषणा IXP4XX_GPIO_STYLE_TRANSITIONAL	0x4
#घोषणा IXP4XX_GPIO_STYLE_MASK		GENMASK(2, 0)
#घोषणा IXP4XX_GPIO_STYLE_SIZE		3

/**
 * काष्ठा ixp4xx_gpio - IXP4 GPIO state container
 * @dev: containing device क्रम this instance
 * @fwnode: the fwnode क्रम this GPIO chip
 * @gc: gpiochip क्रम this instance
 * @base: remapped I/O-memory base
 * @irq_edge: Each bit represents an IRQ: 1: edge-triggered,
 * 0: level triggered
 */
काष्ठा ixp4xx_gpio अणु
	काष्ठा device *dev;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा gpio_chip gc;
	व्योम __iomem *base;
	अचिन्हित दीर्घ दीर्घ irq_edge;
पूर्ण;

अटल व्योम ixp4xx_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ixp4xx_gpio *g = gpiochip_get_data(gc);

	__raw_ग_लिखोl(BIT(d->hwirq), g->base + IXP4XX_REG_GPIS);
पूर्ण

अटल व्योम ixp4xx_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ixp4xx_gpio *g = gpiochip_get_data(gc);

	/* ACK when unmasking अगर not edge-triggered */
	अगर (!(g->irq_edge & BIT(d->hwirq)))
		ixp4xx_gpio_irq_ack(d);

	irq_chip_unmask_parent(d);
पूर्ण

अटल पूर्णांक ixp4xx_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ixp4xx_gpio *g = gpiochip_get_data(gc);
	पूर्णांक line = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांक_style;
	u32 पूर्णांक_reg;
	u32 val;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(d, handle_edge_irq);
		पूर्णांक_style = IXP4XX_GPIO_STYLE_TRANSITIONAL;
		g->irq_edge |= BIT(d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_edge_irq);
		पूर्णांक_style = IXP4XX_GPIO_STYLE_RISING_EDGE;
		g->irq_edge |= BIT(d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_edge_irq);
		पूर्णांक_style = IXP4XX_GPIO_STYLE_FALLING_EDGE;
		g->irq_edge |= BIT(d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		पूर्णांक_style = IXP4XX_GPIO_STYLE_ACTIVE_HIGH;
		g->irq_edge &= ~BIT(d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		पूर्णांक_style = IXP4XX_GPIO_STYLE_ACTIVE_LOW;
		g->irq_edge &= ~BIT(d->hwirq);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (line >= 8) अणु
		/* pins 8-15 */
		line -= 8;
		पूर्णांक_reg = IXP4XX_REG_GPIT2;
	पूर्ण अन्यथा अणु
		/* pins 0-7 */
		पूर्णांक_reg = IXP4XX_REG_GPIT1;
	पूर्ण

	spin_lock_irqsave(&g->gc.bgpio_lock, flags);

	/* Clear the style क्रम the appropriate pin */
	val = __raw_पढ़ोl(g->base + पूर्णांक_reg);
	val &= ~(IXP4XX_GPIO_STYLE_MASK << (line * IXP4XX_GPIO_STYLE_SIZE));
	__raw_ग_लिखोl(val, g->base + पूर्णांक_reg);

	__raw_ग_लिखोl(BIT(line), g->base + IXP4XX_REG_GPIS);

	/* Set the new style */
	val = __raw_पढ़ोl(g->base + पूर्णांक_reg);
	val |= (पूर्णांक_style << (line * IXP4XX_GPIO_STYLE_SIZE));
	__raw_ग_लिखोl(val, g->base + पूर्णांक_reg);

	/* Force-configure this line as an input */
	val = __raw_पढ़ोl(g->base + IXP4XX_REG_GPOE);
	val |= BIT(d->hwirq);
	__raw_ग_लिखोl(val, g->base + IXP4XX_REG_GPOE);

	spin_unlock_irqrestore(&g->gc.bgpio_lock, flags);

	/* This parent only accept level high (निश्चितed) */
	वापस irq_chip_set_type_parent(d, IRQ_TYPE_LEVEL_HIGH);
पूर्ण

अटल काष्ठा irq_chip ixp4xx_gpio_irqchip = अणु
	.name = "IXP4GPIO",
	.irq_ack = ixp4xx_gpio_irq_ack,
	.irq_mask = irq_chip_mask_parent,
	.irq_unmask = ixp4xx_gpio_irq_unmask,
	.irq_set_type = ixp4xx_gpio_irq_set_type,
पूर्ण;

अटल पूर्णांक ixp4xx_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *gc,
					     अचिन्हित पूर्णांक child,
					     अचिन्हित पूर्णांक child_type,
					     अचिन्हित पूर्णांक *parent,
					     अचिन्हित पूर्णांक *parent_type)
अणु
	/* All these पूर्णांकerrupts are level high in the CPU */
	*parent_type = IRQ_TYPE_LEVEL_HIGH;

	/* GPIO lines 0..12 have dedicated IRQs */
	अगर (child == 0) अणु
		*parent = 6;
		वापस 0;
	पूर्ण
	अगर (child == 1) अणु
		*parent = 7;
		वापस 0;
	पूर्ण
	अगर (child >= 2 && child <= 12) अणु
		*parent = child + 17;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ixp4xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा irq_करोमुख्य *parent;
	काष्ठा resource *res;
	काष्ठा ixp4xx_gpio *g;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret;

	g = devm_kzalloc(dev, माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस -ENOMEM;
	g->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	g->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(g->base))
		वापस PTR_ERR(g->base);

	/*
	 * When we convert to device tree we will simply look up the
	 * parent irqकरोमुख्य using irq_find_host(parent) as parent comes
	 * from IRQCHIP_DECLARE(), then use of_node_to_fwnode() to get
	 * the fwnode. For now we need this boardfile style code.
	 */
	अगर (np) अणु
		काष्ठा device_node *irq_parent;

		irq_parent = of_irq_find_parent(np);
		अगर (!irq_parent) अणु
			dev_err(dev, "no IRQ parent node\n");
			वापस -ENODEV;
		पूर्ण
		parent = irq_find_host(irq_parent);
		अगर (!parent) अणु
			dev_err(dev, "no IRQ parent domain\n");
			वापस -ENODEV;
		पूर्ण
		g->fwnode = of_node_to_fwnode(np);
	पूर्ण अन्यथा अणु
		parent = ixp4xx_get_irq_करोमुख्य();
		g->fwnode = irq_करोमुख्य_alloc_fwnode(&res->start);
		अगर (!g->fwnode) अणु
			dev_err(dev, "no domain base\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Make sure GPIO 14 and 15 are NOT used as घड़ीs but GPIO on
	 * specअगरic machines.
	 */
	अगर (machine_is_dsmg600() || machine_is_nas100d())
		__raw_ग_लिखोl(0x0, g->base + IXP4XX_REG_GPCLK);

	/*
	 * This is a very special big-endian ARM issue: when the IXP4xx is
	 * run in big endian mode, all रेजिस्टरs in the machine are चयनed
	 * around to the CPU-native endianness. As you see mostly in the
	 * driver we use __raw_पढ़ोl()/__raw_ग_लिखोl() to access the रेजिस्टरs
	 * in the appropriate order. With the GPIO library we need to specअगरy
	 * byte order explicitly, so this flag needs to be set when compiling
	 * क्रम big endian.
	 */
#अगर defined(CONFIG_CPU_BIG_ENDIAN)
	flags = BGPIOF_BIG_ENDIAN_BYTE_ORDER;
#अन्यथा
	flags = 0;
#पूर्ण_अगर

	/* Populate and रेजिस्टर gpio chip */
	ret = bgpio_init(&g->gc, dev, 4,
			 g->base + IXP4XX_REG_GPIN,
			 g->base + IXP4XX_REG_GPOUT,
			 शून्य,
			 शून्य,
			 g->base + IXP4XX_REG_GPOE,
			 flags);
	अगर (ret) अणु
		dev_err(dev, "unable to init generic GPIO\n");
		वापस ret;
	पूर्ण
	g->gc.ngpio = 16;
	g->gc.label = "IXP4XX_GPIO_CHIP";
	/*
	 * TODO: when we have migrated to device tree and all GPIOs
	 * are fetched using phandles, set this to -1 to get rid of
	 * the fixed gpiochip base.
	 */
	g->gc.base = 0;
	g->gc.parent = &pdev->dev;
	g->gc.owner = THIS_MODULE;

	girq = &g->gc.irq;
	girq->chip = &ixp4xx_gpio_irqchip;
	girq->fwnode = g->fwnode;
	girq->parent_करोमुख्य = parent;
	girq->child_to_parent_hwirq = ixp4xx_gpio_child_to_parent_hwirq;
	girq->handler = handle_bad_irq;
	girq->शेष_type = IRQ_TYPE_NONE;

	ret = devm_gpiochip_add_data(dev, &g->gc, g);
	अगर (ret) अणु
		dev_err(dev, "failed to add SoC gpiochip\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, g);
	dev_info(dev, "IXP4 GPIO registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ixp4xx_gpio_of_match[] = अणु
	अणु
		.compatible = "intel,ixp4xx-gpio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;


अटल काष्ठा platक्रमm_driver ixp4xx_gpio_driver = अणु
	.driver = अणु
		.name		= "ixp4xx-gpio",
		.of_match_table = of_match_ptr(ixp4xx_gpio_of_match),
	पूर्ण,
	.probe = ixp4xx_gpio_probe,
पूर्ण;
builtin_platक्रमm_driver(ixp4xx_gpio_driver);
