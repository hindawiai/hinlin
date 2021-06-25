<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Faraday Technolog FTGPIO010 gpiochip and पूर्णांकerrupt routines
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on arch/arm/mach-gemini/gpio.c:
 * Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 *
 * Based on plat-mxc/gpio.c:
 * MXC GPIO support. (c) 2008 Daniel Mack <daniel@caiaq.de>
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>

/* GPIO रेजिस्टरs definition */
#घोषणा GPIO_DATA_OUT		0x00
#घोषणा GPIO_DATA_IN		0x04
#घोषणा GPIO_सूची		0x08
#घोषणा GPIO_BYPASS_IN		0x0C
#घोषणा GPIO_DATA_SET		0x10
#घोषणा GPIO_DATA_CLR		0x14
#घोषणा GPIO_PULL_EN		0x18
#घोषणा GPIO_PULL_TYPE		0x1C
#घोषणा GPIO_INT_EN		0x20
#घोषणा GPIO_INT_STAT_RAW	0x24
#घोषणा GPIO_INT_STAT_MASKED	0x28
#घोषणा GPIO_INT_MASK		0x2C
#घोषणा GPIO_INT_CLR		0x30
#घोषणा GPIO_INT_TYPE		0x34
#घोषणा GPIO_INT_BOTH_EDGE	0x38
#घोषणा GPIO_INT_LEVEL		0x3C
#घोषणा GPIO_DEBOUNCE_EN	0x40
#घोषणा GPIO_DEBOUNCE_PRESCALE	0x44

/**
 * काष्ठा ftgpio_gpio - Gemini GPIO state container
 * @dev: containing device क्रम this instance
 * @gc: gpiochip क्रम this instance
 * @irq: irqchip क्रम this instance
 * @base: remapped I/O-memory base
 * @clk: silicon घड़ी
 */
काष्ठा ftgpio_gpio अणु
	काष्ठा device *dev;
	काष्ठा gpio_chip gc;
	काष्ठा irq_chip irq;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम ftgpio_gpio_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);

	ग_लिखोl(BIT(irqd_to_hwirq(d)), g->base + GPIO_INT_CLR);
पूर्ण

अटल व्योम ftgpio_gpio_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 val;

	val = पढ़ोl(g->base + GPIO_INT_EN);
	val &= ~BIT(irqd_to_hwirq(d));
	ग_लिखोl(val, g->base + GPIO_INT_EN);
पूर्ण

अटल व्योम ftgpio_gpio_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 val;

	val = पढ़ोl(g->base + GPIO_INT_EN);
	val |= BIT(irqd_to_hwirq(d));
	ग_लिखोl(val, g->base + GPIO_INT_EN);
पूर्ण

अटल पूर्णांक ftgpio_gpio_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 mask = BIT(irqd_to_hwirq(d));
	u32 reg_both, reg_level, reg_type;

	reg_type = पढ़ोl(g->base + GPIO_INT_TYPE);
	reg_level = पढ़ोl(g->base + GPIO_INT_LEVEL);
	reg_both = पढ़ोl(g->base + GPIO_INT_BOTH_EDGE);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both &= ~mask;
		reg_level &= ~mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both &= ~mask;
		reg_level |= mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		reg_type |= mask;
		reg_level &= ~mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		reg_type |= mask;
		reg_level |= mask;
		अवरोध;
	शेष:
		irq_set_handler_locked(d, handle_bad_irq);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(reg_type, g->base + GPIO_INT_TYPE);
	ग_लिखोl(reg_level, g->base + GPIO_INT_LEVEL);
	ग_लिखोl(reg_both, g->base + GPIO_INT_BOTH_EDGE);

	ftgpio_gpio_ack_irq(d);

	वापस 0;
पूर्ण

अटल व्योम ftgpio_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	पूर्णांक offset;
	अचिन्हित दीर्घ stat;

	chained_irq_enter(irqchip, desc);

	stat = पढ़ोl(g->base + GPIO_INT_STAT_RAW);
	अगर (stat)
		क्रम_each_set_bit(offset, &stat, gc->ngpio)
			generic_handle_irq(irq_find_mapping(gc->irq.करोमुख्य,
							    offset));

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक ftgpio_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);
	काष्ठा ftgpio_gpio *g = gpiochip_get_data(gc);
	अचिन्हित दीर्घ pclk_freq;
	u32 deb_भाग;
	u32 val;

	अगर (param != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	/*
	 * Debounce only works अगर पूर्णांकerrupts are enabled. The manual
	 * states that अगर PCLK is 66 MHz, and this is set to 0x7D0, then
	 * PCLK is भागided करोwn to 33 kHz क्रम the debounce समयr. 0x7D0 is
	 * 2000 decimal, so what they mean is simply that the PCLK is
	 * भागided by this value.
	 *
	 * As we get a debounce setting in microseconds, we calculate the
	 * desired period समय and see अगर we can get a suitable debounce
	 * समय.
	 */
	pclk_freq = clk_get_rate(g->clk);
	deb_भाग = DIV_ROUND_CLOSEST(pclk_freq, arg);

	/* This रेजिस्टर is only 24 bits wide */
	अगर (deb_भाग > (1 << 24))
		वापस -ENOTSUPP;

	dev_dbg(g->dev, "prescale divisor: %08x, resulting frequency %lu Hz\n",
		deb_भाग, (pclk_freq/deb_भाग));

	val = पढ़ोl(g->base + GPIO_DEBOUNCE_PRESCALE);
	अगर (val == deb_भाग) अणु
		/*
		 * The debounce समयr happens to alपढ़ोy be set to the
		 * desirable value, what a coincidence! We can just enable
		 * debounce on this GPIO line and वापस. This happens more
		 * often than you think, क्रम example when all GPIO keys
		 * on a प्रणाली are requesting the same debounce पूर्णांकerval.
		 */
		val = पढ़ोl(g->base + GPIO_DEBOUNCE_EN);
		val |= BIT(offset);
		ग_लिखोl(val, g->base + GPIO_DEBOUNCE_EN);
		वापस 0;
	पूर्ण

	val = पढ़ोl(g->base + GPIO_DEBOUNCE_EN);
	अगर (val) अणु
		/*
		 * Oh no! Someone is alपढ़ोy using the debounce with
		 * another setting than what we need. Bummer.
		 */
		वापस -ENOTSUPP;
	पूर्ण

	/* First come, first serve */
	ग_लिखोl(deb_भाग, g->base + GPIO_DEBOUNCE_PRESCALE);
	/* Enable debounce */
	val |= BIT(offset);
	ग_लिखोl(val, g->base + GPIO_DEBOUNCE_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक ftgpio_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ftgpio_gpio *g;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक irq;
	पूर्णांक ret;

	g = devm_kzalloc(dev, माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस -ENOMEM;

	g->dev = dev;

	g->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(g->base))
		वापस PTR_ERR(g->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq ? irq : -EINVAL;

	g->clk = devm_clk_get(dev, शून्य);
	अगर (!IS_ERR(g->clk)) अणु
		ret = clk_prepare_enable(g->clk);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (PTR_ERR(g->clk) == -EPROBE_DEFER) अणु
		/*
		 * Percolate deferrals, क्रम anything अन्यथा,
		 * just live without the घड़ीing.
		 */
		वापस PTR_ERR(g->clk);
	पूर्ण

	ret = bgpio_init(&g->gc, dev, 4,
			 g->base + GPIO_DATA_IN,
			 g->base + GPIO_DATA_SET,
			 g->base + GPIO_DATA_CLR,
			 g->base + GPIO_सूची,
			 शून्य,
			 0);
	अगर (ret) अणु
		dev_err(dev, "unable to init generic GPIO\n");
		जाओ dis_clk;
	पूर्ण
	g->gc.label = "FTGPIO010";
	g->gc.base = -1;
	g->gc.parent = dev;
	g->gc.owner = THIS_MODULE;
	/* ngpio is set by bgpio_init() */

	/* We need a silicon घड़ी to करो debounce */
	अगर (!IS_ERR(g->clk))
		g->gc.set_config = ftgpio_gpio_set_config;

	g->irq.name = "FTGPIO010";
	g->irq.irq_ack = ftgpio_gpio_ack_irq;
	g->irq.irq_mask = ftgpio_gpio_mask_irq;
	g->irq.irq_unmask = ftgpio_gpio_unmask_irq;
	g->irq.irq_set_type = ftgpio_gpio_set_irq_type;

	girq = &g->gc.irq;
	girq->chip = &g->irq;
	girq->parent_handler = ftgpio_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents) अणु
		ret = -ENOMEM;
		जाओ dis_clk;
	पूर्ण
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = irq;

	/* Disable, unmask and clear all पूर्णांकerrupts */
	ग_लिखोl(0x0, g->base + GPIO_INT_EN);
	ग_लिखोl(0x0, g->base + GPIO_INT_MASK);
	ग_लिखोl(~0x0, g->base + GPIO_INT_CLR);

	/* Clear any use of debounce */
	ग_लिखोl(0x0, g->base + GPIO_DEBOUNCE_EN);

	ret = devm_gpiochip_add_data(dev, &g->gc, g);
	अगर (ret)
		जाओ dis_clk;

	platक्रमm_set_drvdata(pdev, g);
	dev_info(dev, "FTGPIO010 @%p registered\n", g->base);

	वापस 0;

dis_clk:
	अगर (!IS_ERR(g->clk))
		clk_disable_unprepare(g->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ftgpio_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ftgpio_gpio *g = platक्रमm_get_drvdata(pdev);

	अगर (!IS_ERR(g->clk))
		clk_disable_unprepare(g->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ftgpio_gpio_of_match[] = अणु
	अणु
		.compatible = "cortina,gemini-gpio",
	पूर्ण,
	अणु
		.compatible = "moxa,moxart-gpio",
	पूर्ण,
	अणु
		.compatible = "faraday,ftgpio010",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ftgpio_gpio_driver = अणु
	.driver = अणु
		.name		= "ftgpio010-gpio",
		.of_match_table = of_match_ptr(ftgpio_gpio_of_match),
	पूर्ण,
	.probe = ftgpio_gpio_probe,
	.हटाओ = ftgpio_gpio_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(ftgpio_gpio_driver);
