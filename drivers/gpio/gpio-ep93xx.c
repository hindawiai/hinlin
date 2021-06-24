<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic EP93xx GPIO handling
 *
 * Copyright (c) 2008 Ryan Mallon
 * Copyright (c) 2011 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on code originally from:
 *  linux/arch/arm/mach-ep93xx/core.c
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>

#घोषणा EP93XX_GPIO_F_INT_STATUS 0x5c
#घोषणा EP93XX_GPIO_A_INT_STATUS 0xa0
#घोषणा EP93XX_GPIO_B_INT_STATUS 0xbc

/* Maximum value क्रम gpio line identअगरiers */
#घोषणा EP93XX_GPIO_LINE_MAX 63

/* Number of GPIO chips in EP93XX */
#घोषणा EP93XX_GPIO_CHIP_NUM 8

/* Maximum value क्रम irq capable line identअगरiers */
#घोषणा EP93XX_GPIO_LINE_MAX_IRQ 23

#घोषणा EP93XX_GPIO_A_IRQ_BASE 64
#घोषणा EP93XX_GPIO_B_IRQ_BASE 72
/*
 * Static mapping of GPIO bank F IRQS:
 * F0..F7 (16..24) to irq 80..87.
 */
#घोषणा EP93XX_GPIO_F_IRQ_BASE 80

काष्ठा ep93xx_gpio_irq_chip अणु
	काष्ठा irq_chip ic;
	u8 irq_offset;
	u8 पूर्णांक_unmasked;
	u8 पूर्णांक_enabled;
	u8 पूर्णांक_type1;
	u8 पूर्णांक_type2;
	u8 पूर्णांक_debounce;
पूर्ण;

काष्ठा ep93xx_gpio_chip अणु
	काष्ठा gpio_chip		gc;
	काष्ठा ep93xx_gpio_irq_chip	*eic;
पूर्ण;

काष्ठा ep93xx_gpio अणु
	व्योम __iomem		*base;
	काष्ठा ep93xx_gpio_chip	gc[EP93XX_GPIO_CHIP_NUM];
पूर्ण;

#घोषणा to_ep93xx_gpio_chip(x) container_of(x, काष्ठा ep93xx_gpio_chip, gc)

अटल काष्ठा ep93xx_gpio_irq_chip *to_ep93xx_gpio_irq_chip(काष्ठा gpio_chip *gc)
अणु
	काष्ठा ep93xx_gpio_chip *egc = to_ep93xx_gpio_chip(gc);

	वापस egc->eic;
पूर्ण

/*************************************************************************
 * Interrupt handling क्रम EP93xx on-chip GPIOs
 *************************************************************************/
#घोषणा EP93XX_INT_TYPE1_OFFSET		0x00
#घोषणा EP93XX_INT_TYPE2_OFFSET		0x04
#घोषणा EP93XX_INT_EOI_OFFSET		0x08
#घोषणा EP93XX_INT_EN_OFFSET		0x0c
#घोषणा EP93XX_INT_STATUS_OFFSET	0x10
#घोषणा EP93XX_INT_RAW_STATUS_OFFSET	0x14
#घोषणा EP93XX_INT_DEBOUNCE_OFFSET	0x18

अटल व्योम ep93xx_gpio_update_पूर्णांक_params(काष्ठा ep93xx_gpio *epg,
					  काष्ठा ep93xx_gpio_irq_chip *eic)
अणु
	ग_लिखोb_relaxed(0, epg->base + eic->irq_offset + EP93XX_INT_EN_OFFSET);

	ग_लिखोb_relaxed(eic->पूर्णांक_type2,
		       epg->base + eic->irq_offset + EP93XX_INT_TYPE2_OFFSET);

	ग_लिखोb_relaxed(eic->पूर्णांक_type1,
		       epg->base + eic->irq_offset + EP93XX_INT_TYPE1_OFFSET);

	ग_लिखोb_relaxed(eic->पूर्णांक_unmasked & eic->पूर्णांक_enabled,
		       epg->base + eic->irq_offset + EP93XX_INT_EN_OFFSET);
पूर्ण

अटल व्योम ep93xx_gpio_पूर्णांक_debounce(काष्ठा gpio_chip *gc,
				     अचिन्हित पूर्णांक offset, bool enable)
अणु
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	पूर्णांक port_mask = BIT(offset);

	अगर (enable)
		eic->पूर्णांक_debounce |= port_mask;
	अन्यथा
		eic->पूर्णांक_debounce &= ~port_mask;

	ग_लिखोb(eic->पूर्णांक_debounce,
	       epg->base + eic->irq_offset + EP93XX_INT_DEBOUNCE_OFFSET);
पूर्ण

अटल व्योम ep93xx_gpio_ab_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ stat;
	पूर्णांक offset;

	chained_irq_enter(irqchip, desc);

	/*
	 * Dispatch the IRQs to the irqकरोमुख्य of each A and B
	 * gpiochip irqकरोमुख्यs depending on what has fired.
	 * The tricky part is that the IRQ line is shared
	 * between bank A and B and each has their own gpiochip.
	 */
	stat = पढ़ोb(epg->base + EP93XX_GPIO_A_INT_STATUS);
	क्रम_each_set_bit(offset, &stat, 8)
		generic_handle_irq(irq_find_mapping(epg->gc[0].gc.irq.करोमुख्य,
						    offset));

	stat = पढ़ोb(epg->base + EP93XX_GPIO_B_INT_STATUS);
	क्रम_each_set_bit(offset, &stat, 8)
		generic_handle_irq(irq_find_mapping(epg->gc[1].gc.irq.करोमुख्य,
						    offset));

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल व्योम ep93xx_gpio_f_irq_handler(काष्ठा irq_desc *desc)
अणु
	/*
	 * map discontiguous hw irq range to continuous sw irq range:
	 *
	 *  IRQ_EP93XX_GPIOअणु0..7पूर्णMUX -> EP93XX_GPIO_LINE_Fअणु0..7पूर्ण
	 */
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	पूर्णांक port_f_idx = ((irq + 1) & 7) ^ 4; /* अणु19..22,47..50पूर्ण -> अणु0..7पूर्ण */
	पूर्णांक gpio_irq = EP93XX_GPIO_F_IRQ_BASE + port_f_idx;

	chained_irq_enter(irqchip, desc);
	generic_handle_irq(gpio_irq);
	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल व्योम ep93xx_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);
	पूर्णांक port_mask = BIT(d->irq & 7);

	अगर (irqd_get_trigger_type(d) == IRQ_TYPE_EDGE_BOTH) अणु
		eic->पूर्णांक_type2 ^= port_mask; /* चयन edge direction */
		ep93xx_gpio_update_पूर्णांक_params(epg, eic);
	पूर्ण

	ग_लिखोb(port_mask, epg->base + eic->irq_offset + EP93XX_INT_EOI_OFFSET);
पूर्ण

अटल व्योम ep93xx_gpio_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);
	पूर्णांक port_mask = BIT(d->irq & 7);

	अगर (irqd_get_trigger_type(d) == IRQ_TYPE_EDGE_BOTH)
		eic->पूर्णांक_type2 ^= port_mask; /* चयन edge direction */

	eic->पूर्णांक_unmasked &= ~port_mask;
	ep93xx_gpio_update_पूर्णांक_params(epg, eic);

	ग_लिखोb(port_mask, epg->base + eic->irq_offset + EP93XX_INT_EOI_OFFSET);
पूर्ण

अटल व्योम ep93xx_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);

	eic->पूर्णांक_unmasked &= ~BIT(d->irq & 7);
	ep93xx_gpio_update_पूर्णांक_params(epg, eic);
पूर्ण

अटल व्योम ep93xx_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);

	eic->पूर्णांक_unmasked |= BIT(d->irq & 7);
	ep93xx_gpio_update_पूर्णांक_params(epg, eic);
पूर्ण

/*
 * gpio_पूर्णांक_type1 controls whether the पूर्णांकerrupt is level (0) or
 * edge (1) triggered, जबतक gpio_पूर्णांक_type2 controls whether it
 * triggers on low/falling (0) or high/rising (1).
 */
अटल पूर्णांक ep93xx_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ep93xx_gpio_irq_chip *eic = to_ep93xx_gpio_irq_chip(gc);
	काष्ठा ep93xx_gpio *epg = gpiochip_get_data(gc);
	पूर्णांक offset = d->irq & 7;
	पूर्णांक port_mask = BIT(offset);
	irq_flow_handler_t handler;

	gc->direction_input(gc, offset);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		eic->पूर्णांक_type1 |= port_mask;
		eic->पूर्णांक_type2 |= port_mask;
		handler = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		eic->पूर्णांक_type1 |= port_mask;
		eic->पूर्णांक_type2 &= ~port_mask;
		handler = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		eic->पूर्णांक_type1 &= ~port_mask;
		eic->पूर्णांक_type2 |= port_mask;
		handler = handle_level_irq;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		eic->पूर्णांक_type1 &= ~port_mask;
		eic->पूर्णांक_type2 &= ~port_mask;
		handler = handle_level_irq;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		eic->पूर्णांक_type1 |= port_mask;
		/* set initial polarity based on current input level */
		अगर (gc->get(gc, offset))
			eic->पूर्णांक_type2 &= ~port_mask; /* falling */
		अन्यथा
			eic->पूर्णांक_type2 |= port_mask; /* rising */
		handler = handle_edge_irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_set_handler_locked(d, handler);

	eic->पूर्णांक_enabled |= port_mask;

	ep93xx_gpio_update_पूर्णांक_params(epg, eic);

	वापस 0;
पूर्ण

/*************************************************************************
 * gpiolib पूर्णांकerface क्रम EP93xx on-chip GPIOs
 *************************************************************************/
काष्ठा ep93xx_gpio_bank अणु
	स्थिर अक्षर	*label;
	पूर्णांक		data;
	पूर्णांक		dir;
	पूर्णांक		irq;
	पूर्णांक		base;
	bool		has_irq;
	bool		has_hierarchical_irq;
	अचिन्हित पूर्णांक	irq_base;
पूर्ण;

#घोषणा EP93XX_GPIO_BANK(_label, _data, _dir, _irq, _base, _has_irq, _has_hier, _irq_base) \
	अणु							\
		.label		= _label,			\
		.data		= _data,			\
		.dir		= _dir,				\
		.irq		= _irq,				\
		.base		= _base,			\
		.has_irq	= _has_irq,			\
		.has_hierarchical_irq = _has_hier,		\
		.irq_base	= _irq_base,			\
	पूर्ण

अटल काष्ठा ep93xx_gpio_bank ep93xx_gpio_banks[] = अणु
	/* Bank A has 8 IRQs */
	EP93XX_GPIO_BANK("A", 0x00, 0x10, 0x90, 0, true, false, EP93XX_GPIO_A_IRQ_BASE),
	/* Bank B has 8 IRQs */
	EP93XX_GPIO_BANK("B", 0x04, 0x14, 0xac, 8, true, false, EP93XX_GPIO_B_IRQ_BASE),
	EP93XX_GPIO_BANK("C", 0x08, 0x18, 0x00, 40, false, false, 0),
	EP93XX_GPIO_BANK("D", 0x0c, 0x1c, 0x00, 24, false, false, 0),
	EP93XX_GPIO_BANK("E", 0x20, 0x24, 0x00, 32, false, false, 0),
	/* Bank F has 8 IRQs */
	EP93XX_GPIO_BANK("F", 0x30, 0x34, 0x4c, 16, false, true, EP93XX_GPIO_F_IRQ_BASE),
	EP93XX_GPIO_BANK("G", 0x38, 0x3c, 0x00, 48, false, false, 0),
	EP93XX_GPIO_BANK("H", 0x40, 0x44, 0x00, 56, false, false, 0),
पूर्ण;

अटल पूर्णांक ep93xx_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
				  अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	ep93xx_gpio_पूर्णांक_debounce(gc, offset, debounce ? true : false);

	वापस 0;
पूर्ण

अटल व्योम ep93xx_init_irq_chip(काष्ठा device *dev, काष्ठा irq_chip *ic)
अणु
	ic->irq_ack = ep93xx_gpio_irq_ack;
	ic->irq_mask_ack = ep93xx_gpio_irq_mask_ack;
	ic->irq_mask = ep93xx_gpio_irq_mask;
	ic->irq_unmask = ep93xx_gpio_irq_unmask;
	ic->irq_set_type = ep93xx_gpio_irq_type;
पूर्ण

अटल पूर्णांक ep93xx_gpio_add_bank(काष्ठा ep93xx_gpio_chip *egc,
				काष्ठा platक्रमm_device *pdev,
				काष्ठा ep93xx_gpio *epg,
				काष्ठा ep93xx_gpio_bank *bank)
अणु
	व्योम __iomem *data = epg->base + bank->data;
	व्योम __iomem *dir = epg->base + bank->dir;
	काष्ठा gpio_chip *gc = &egc->gc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	err = bgpio_init(gc, dev, 1, data, शून्य, शून्य, dir, शून्य, 0);
	अगर (err)
		वापस err;

	gc->label = bank->label;
	gc->base = bank->base;

	girq = &gc->irq;
	अगर (bank->has_irq || bank->has_hierarchical_irq) अणु
		काष्ठा irq_chip *ic;

		gc->set_config = ep93xx_gpio_set_config;
		egc->eic = devm_kसुस्मृति(dev, 1,
					माप(*egc->eic),
					GFP_KERNEL);
		अगर (!egc->eic)
			वापस -ENOMEM;
		egc->eic->irq_offset = bank->irq;
		ic = &egc->eic->ic;
		ic->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "gpio-irq-%s", bank->label);
		अगर (!ic->name)
			वापस -ENOMEM;
		ep93xx_init_irq_chip(dev, ic);
		girq->chip = ic;
	पूर्ण

	अगर (bank->has_irq) अणु
		पूर्णांक ab_parent_irq = platक्रमm_get_irq(pdev, 0);

		girq->parent_handler = ep93xx_gpio_ab_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, girq->num_parents,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
		girq->parents[0] = ab_parent_irq;
		girq->first = bank->irq_base;
	पूर्ण

	/* Only bank F has especially funky IRQ handling */
	अगर (bank->has_hierarchical_irq) अणु
		पूर्णांक gpio_irq;
		पूर्णांक i;

		/*
		 * FIXME: convert this to use hierarchical IRQ support!
		 * this requires fixing the root irqchip to be hierarchical.
		 */
		girq->parent_handler = ep93xx_gpio_f_irq_handler;
		girq->num_parents = 8;
		girq->parents = devm_kसुस्मृति(dev, girq->num_parents,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		/* Pick resources 1..8 क्रम these IRQs */
		क्रम (i = 0; i < girq->num_parents; i++) अणु
			girq->parents[i] = platक्रमm_get_irq(pdev, i + 1);
			gpio_irq = bank->irq_base + i;
			irq_set_chip_data(gpio_irq, &epg->gc[5]);
			irq_set_chip_and_handler(gpio_irq,
						 girq->chip,
						 handle_level_irq);
			irq_clear_status_flags(gpio_irq, IRQ_NOREQUEST);
		पूर्ण
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
		girq->first = bank->irq_base;
	पूर्ण

	वापस devm_gpiochip_add_data(dev, gc, epg);
पूर्ण

अटल पूर्णांक ep93xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_gpio *epg;
	पूर्णांक i;

	epg = devm_kzalloc(&pdev->dev, माप(*epg), GFP_KERNEL);
	अगर (!epg)
		वापस -ENOMEM;

	epg->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(epg->base))
		वापस PTR_ERR(epg->base);

	क्रम (i = 0; i < ARRAY_SIZE(ep93xx_gpio_banks); i++) अणु
		काष्ठा ep93xx_gpio_chip *gc = &epg->gc[i];
		काष्ठा ep93xx_gpio_bank *bank = &ep93xx_gpio_banks[i];

		अगर (ep93xx_gpio_add_bank(gc, pdev, epg, bank))
			dev_warn(&pdev->dev, "Unable to add gpio bank %s\n",
				 bank->label);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_gpio_driver = अणु
	.driver		= अणु
		.name	= "gpio-ep93xx",
	पूर्ण,
	.probe		= ep93xx_gpio_probe,
पूर्ण;

अटल पूर्णांक __init ep93xx_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ep93xx_gpio_driver);
पूर्ण
postcore_initcall(ep93xx_gpio_init);

MODULE_AUTHOR("Ryan Mallon <ryan@bluewatersys.com> "
		"H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("EP93XX GPIO driver");
MODULE_LICENSE("GPL");
