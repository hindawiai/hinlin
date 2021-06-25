<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI DaVinci GPIO Support
 *
 * Copyright (c) 2006-2007 David Brownell
 * Copyright (c) 2007, MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र-generic/gpपन.स>

#घोषणा MAX_REGS_BANKS 5
#घोषणा MAX_INT_PER_BANK 32

काष्ठा davinci_gpio_regs अणु
	u32	dir;
	u32	out_data;
	u32	set_data;
	u32	clr_data;
	u32	in_data;
	u32	set_rising;
	u32	clr_rising;
	u32	set_falling;
	u32	clr_falling;
	u32	पूर्णांकstat;
पूर्ण;

प्रकार काष्ठा irq_chip *(*gpio_get_irq_chip_cb_t)(अचिन्हित पूर्णांक irq);

#घोषणा BINTEN	0x8 /* GPIO Interrupt Per-Bank Enable Register */

अटल व्योम __iomem *gpio_base;
अटल अचिन्हित पूर्णांक offset_array[5] = अणु0x10, 0x38, 0x60, 0x88, 0xb0पूर्ण;

काष्ठा davinci_gpio_irq_data अणु
	व्योम __iomem			*regs;
	काष्ठा davinci_gpio_controller	*chip;
	पूर्णांक				bank_num;
पूर्ण;

काष्ठा davinci_gpio_controller अणु
	काष्ठा gpio_chip	chip;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	/* Serialize access to GPIO रेजिस्टरs */
	spinlock_t		lock;
	व्योम __iomem		*regs[MAX_REGS_BANKS];
	पूर्णांक			gpio_unbanked;
	पूर्णांक			irqs[MAX_INT_PER_BANK];
पूर्ण;

अटल अंतरभूत u32 __gpio_mask(अचिन्हित gpio)
अणु
	वापस 1 << (gpio % 32);
पूर्ण

अटल अंतरभूत काष्ठा davinci_gpio_regs __iomem *irq2regs(काष्ठा irq_data *d)
अणु
	काष्ठा davinci_gpio_regs __iomem *g;

	g = (__क्रमce काष्ठा davinci_gpio_regs __iomem *)irq_data_get_irq_chip_data(d);

	वापस g;
पूर्ण

अटल पूर्णांक davinci_gpio_irq_setup(काष्ठा platक्रमm_device *pdev);

/*--------------------------------------------------------------------------*/

/* board setup code *MUST* setup pinmux and enable the GPIO घड़ी. */
अटल अंतरभूत पूर्णांक __davinci_direction(काष्ठा gpio_chip *chip,
			अचिन्हित offset, bool out, पूर्णांक value)
अणु
	काष्ठा davinci_gpio_controller *d = gpiochip_get_data(chip);
	काष्ठा davinci_gpio_regs __iomem *g;
	अचिन्हित दीर्घ flags;
	u32 temp;
	पूर्णांक bank = offset / 32;
	u32 mask = __gpio_mask(offset);

	g = d->regs[bank];
	spin_lock_irqsave(&d->lock, flags);
	temp = पढ़ोl_relaxed(&g->dir);
	अगर (out) अणु
		temp &= ~mask;
		ग_लिखोl_relaxed(mask, value ? &g->set_data : &g->clr_data);
	पूर्ण अन्यथा अणु
		temp |= mask;
	पूर्ण
	ग_लिखोl_relaxed(temp, &g->dir);
	spin_unlock_irqrestore(&d->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस __davinci_direction(chip, offset, false, 0);
पूर्ण

अटल पूर्णांक
davinci_direction_out(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	वापस __davinci_direction(chip, offset, true, value);
पूर्ण

/*
 * Read the pin's value (works even if it's set up as output);
 * वापसs zero/nonzero.
 *
 * Note that changes are synched to the GPIO घड़ी, so पढ़ोing values back
 * right after you've set them may give old values.
 */
अटल पूर्णांक davinci_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_gpio_controller *d = gpiochip_get_data(chip);
	काष्ठा davinci_gpio_regs __iomem *g;
	पूर्णांक bank = offset / 32;

	g = d->regs[bank];

	वापस !!(__gpio_mask(offset) & पढ़ोl_relaxed(&g->in_data));
पूर्ण

/*
 * Assuming the pin is muxed as a gpio output, set its output value.
 */
अटल व्योम
davinci_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा davinci_gpio_controller *d = gpiochip_get_data(chip);
	काष्ठा davinci_gpio_regs __iomem *g;
	पूर्णांक bank = offset / 32;

	g = d->regs[bank];

	ग_लिखोl_relaxed(__gpio_mask(offset),
		       value ? &g->set_data : &g->clr_data);
पूर्ण

अटल काष्ठा davinci_gpio_platक्रमm_data *
davinci_gpio_get_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा davinci_gpio_platक्रमm_data *pdata;
	पूर्णांक ret;
	u32 val;

	अगर (!IS_ENABLED(CONFIG_OF) || !pdev->dev.of_node)
		वापस dev_get_platdata(&pdev->dev);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	ret = of_property_पढ़ो_u32(dn, "ti,ngpio", &val);
	अगर (ret)
		जाओ of_err;

	pdata->ngpio = val;

	ret = of_property_पढ़ो_u32(dn, "ti,davinci-gpio-unbanked", &val);
	अगर (ret)
		जाओ of_err;

	pdata->gpio_unbanked = val;

	वापस pdata;

of_err:
	dev_err(&pdev->dev, "Populating pdata from DT failed: err %d\n", ret);
	वापस शून्य;
पूर्ण

अटल पूर्णांक davinci_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक bank, i, ret = 0;
	अचिन्हित पूर्णांक ngpio, nbank, nirq;
	काष्ठा davinci_gpio_controller *chips;
	काष्ठा davinci_gpio_platक्रमm_data *pdata;
	काष्ठा device *dev = &pdev->dev;

	pdata = davinci_gpio_get_pdata(pdev);
	अगर (!pdata) अणु
		dev_err(dev, "No platform data found\n");
		वापस -EINVAL;
	पूर्ण

	dev->platक्रमm_data = pdata;

	/*
	 * The gpio banks conceptually expose a segmented biपंचांगap,
	 * and "ngpio" is one more than the largest zero-based
	 * bit index that's valid.
	 */
	ngpio = pdata->ngpio;
	अगर (ngpio == 0) अणु
		dev_err(dev, "How many GPIOs?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(ARCH_NR_GPIOS < ngpio))
		ngpio = ARCH_NR_GPIOS;

	/*
	 * If there are unbanked पूर्णांकerrupts then the number of
	 * पूर्णांकerrupts is equal to number of gpios अन्यथा all are banked so
	 * number of पूर्णांकerrupts is equal to number of banks(each with 16 gpios)
	 */
	अगर (pdata->gpio_unbanked)
		nirq = pdata->gpio_unbanked;
	अन्यथा
		nirq = DIV_ROUND_UP(ngpio, 16);

	chips = devm_kzalloc(dev, माप(*chips), GFP_KERNEL);
	अगर (!chips)
		वापस -ENOMEM;

	gpio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio_base))
		वापस PTR_ERR(gpio_base);

	क्रम (i = 0; i < nirq; i++) अणु
		chips->irqs[i] = platक्रमm_get_irq(pdev, i);
		अगर (chips->irqs[i] < 0)
			वापस dev_err_probe(dev, chips->irqs[i], "IRQ not populated\n");
	पूर्ण

	chips->chip.label = dev_name(dev);

	chips->chip.direction_input = davinci_direction_in;
	chips->chip.get = davinci_gpio_get;
	chips->chip.direction_output = davinci_direction_out;
	chips->chip.set = davinci_gpio_set;

	chips->chip.ngpio = ngpio;
	chips->chip.base = pdata->no_स्वतः_base ? pdata->base : -1;

#अगर_घोषित CONFIG_OF_GPIO
	chips->chip.of_gpio_n_cells = 2;
	chips->chip.parent = dev;
	chips->chip.of_node = dev->of_node;
	chips->chip.request = gpiochip_generic_request;
	chips->chip.मुक्त = gpiochip_generic_मुक्त;
#पूर्ण_अगर
	spin_lock_init(&chips->lock);

	nbank = DIV_ROUND_UP(ngpio, 32);
	क्रम (bank = 0; bank < nbank; bank++)
		chips->regs[bank] = gpio_base + offset_array[bank];

	ret = devm_gpiochip_add_data(dev, &chips->chip, chips);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, chips);
	ret = davinci_gpio_irq_setup(pdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*--------------------------------------------------------------------------*/
/*
 * We expect irqs will normally be set up as input pins, but they can also be
 * used as output pins ... which is convenient क्रम testing.
 *
 * NOTE:  The first few GPIOs also have direct INTC hookups in addition
 * to their GPIOBNK0 irq, with a bit less overhead.
 *
 * All those INTC hookups (direct, plus several IRQ banks) can also
 * serve as EDMA event triggers.
 */

अटल व्योम gpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा davinci_gpio_regs __iomem *g = irq2regs(d);
	uपूर्णांकptr_t mask = (uपूर्णांकptr_t)irq_data_get_irq_handler_data(d);

	ग_लिखोl_relaxed(mask, &g->clr_falling);
	ग_लिखोl_relaxed(mask, &g->clr_rising);
पूर्ण

अटल व्योम gpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा davinci_gpio_regs __iomem *g = irq2regs(d);
	uपूर्णांकptr_t mask = (uपूर्णांकptr_t)irq_data_get_irq_handler_data(d);
	अचिन्हित status = irqd_get_trigger_type(d);

	status &= IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING;
	अगर (!status)
		status = IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING;

	अगर (status & IRQ_TYPE_EDGE_FALLING)
		ग_लिखोl_relaxed(mask, &g->set_falling);
	अगर (status & IRQ_TYPE_EDGE_RISING)
		ग_लिखोl_relaxed(mask, &g->set_rising);
पूर्ण

अटल पूर्णांक gpio_irq_type(काष्ठा irq_data *d, अचिन्हित trigger)
अणु
	अगर (trigger & ~(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip gpio_irqchip = अणु
	.name		= "GPIO",
	.irq_enable	= gpio_irq_enable,
	.irq_disable	= gpio_irq_disable,
	.irq_set_type	= gpio_irq_type,
	.flags		= IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल व्योम gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा davinci_gpio_regs __iomem *g;
	u32 mask = 0xffff;
	पूर्णांक bank_num;
	काष्ठा davinci_gpio_controller *d;
	काष्ठा davinci_gpio_irq_data *irqdata;

	irqdata = (काष्ठा davinci_gpio_irq_data *)irq_desc_get_handler_data(desc);
	bank_num = irqdata->bank_num;
	g = irqdata->regs;
	d = irqdata->chip;

	/* we only care about one bank */
	अगर ((bank_num % 2) == 1)
		mask <<= 16;

	/* temporarily mask (level sensitive) parent IRQ */
	chained_irq_enter(irq_desc_get_chip(desc), desc);
	जबतक (1) अणु
		u32		status;
		पूर्णांक		bit;
		irq_hw_number_t hw_irq;

		/* ack any irqs */
		status = पढ़ोl_relaxed(&g->पूर्णांकstat) & mask;
		अगर (!status)
			अवरोध;
		ग_लिखोl_relaxed(status, &g->पूर्णांकstat);

		/* now demux them to the right lowlevel handler */

		जबतक (status) अणु
			bit = __ffs(status);
			status &= ~BIT(bit);
			/* Max number of gpios per controller is 144 so
			 * hw_irq will be in [0..143]
			 */
			hw_irq = (bank_num / 2) * 32 + bit;

			generic_handle_irq(
				irq_find_mapping(d->irq_करोमुख्य, hw_irq));
		पूर्ण
	पूर्ण
	chained_irq_निकास(irq_desc_get_chip(desc), desc);
	/* now it may re-trigger */
पूर्ण

अटल पूर्णांक gpio_to_irq_banked(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_gpio_controller *d = gpiochip_get_data(chip);

	अगर (d->irq_करोमुख्य)
		वापस irq_create_mapping(d->irq_करोमुख्य, offset);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल पूर्णांक gpio_to_irq_unbanked(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा davinci_gpio_controller *d = gpiochip_get_data(chip);

	/*
	 * NOTE:  we assume क्रम now that only irqs in the first gpio_chip
	 * can provide direct-mapped IRQs to AINTC (up to 32 GPIOs).
	 */
	अगर (offset < d->gpio_unbanked)
		वापस d->irqs[offset];
	अन्यथा
		वापस -ENODEV;
पूर्ण

अटल पूर्णांक gpio_irq_type_unbanked(काष्ठा irq_data *data, अचिन्हित trigger)
अणु
	काष्ठा davinci_gpio_controller *d;
	काष्ठा davinci_gpio_regs __iomem *g;
	u32 mask, i;

	d = (काष्ठा davinci_gpio_controller *)irq_data_get_irq_handler_data(data);
	g = (काष्ठा davinci_gpio_regs __iomem *)d->regs[0];
	क्रम (i = 0; i < MAX_INT_PER_BANK; i++)
		अगर (data->irq == d->irqs[i])
			अवरोध;

	अगर (i == MAX_INT_PER_BANK)
		वापस -EINVAL;

	mask = __gpio_mask(i);

	अगर (trigger & ~(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		वापस -EINVAL;

	ग_लिखोl_relaxed(mask, (trigger & IRQ_TYPE_EDGE_FALLING)
		     ? &g->set_falling : &g->clr_falling);
	ग_लिखोl_relaxed(mask, (trigger & IRQ_TYPE_EDGE_RISING)
		     ? &g->set_rising : &g->clr_rising);

	वापस 0;
पूर्ण

अटल पूर्णांक
davinci_gpio_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		     irq_hw_number_t hw)
अणु
	काष्ठा davinci_gpio_controller *chips =
				(काष्ठा davinci_gpio_controller *)d->host_data;
	काष्ठा davinci_gpio_regs __iomem *g = chips->regs[hw / 32];

	irq_set_chip_and_handler_name(irq, &gpio_irqchip, handle_simple_irq,
				"davinci_gpio");
	irq_set_irq_type(irq, IRQ_TYPE_NONE);
	irq_set_chip_data(irq, (__क्रमce व्योम *)g);
	irq_set_handler_data(irq, (व्योम *)(uपूर्णांकptr_t)__gpio_mask(hw));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops davinci_gpio_irq_ops = अणु
	.map = davinci_gpio_irq_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल काष्ठा irq_chip *davinci_gpio_get_irq_chip(अचिन्हित पूर्णांक irq)
अणु
	अटल काष्ठा irq_chip_type gpio_unbanked;

	gpio_unbanked = *irq_data_get_chip_type(irq_get_irq_data(irq));

	वापस &gpio_unbanked.chip;
पूर्ण;

अटल काष्ठा irq_chip *keystone_gpio_get_irq_chip(अचिन्हित पूर्णांक irq)
अणु
	अटल काष्ठा irq_chip gpio_unbanked;

	gpio_unbanked = *irq_get_chip(irq);
	वापस &gpio_unbanked;
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_gpio_ids[];

/*
 * NOTE:  क्रम suspend/resume, probably best to make a platक्रमm_device with
 * suspend_late/resume_resume calls hooking पूर्णांकo results of the set_wake()
 * calls ... so अगर no gpios are wakeup events the घड़ी can be disabled,
 * with outमाला_दो left at previously set levels, and so that VDD3P3V.IOPWDN0
 * (dm6446) can be set appropriately क्रम GPIOV33 pins.
 */

अटल पूर्णांक davinci_gpio_irq_setup(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित	gpio, bank;
	पूर्णांक		irq;
	पूर्णांक		ret;
	काष्ठा clk	*clk;
	u32		bपूर्णांकen = 0;
	अचिन्हित	ngpio;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा davinci_gpio_controller *chips = platक्रमm_get_drvdata(pdev);
	काष्ठा davinci_gpio_platक्रमm_data *pdata = dev->platक्रमm_data;
	काष्ठा davinci_gpio_regs __iomem *g;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य = शून्य;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा irq_chip *irq_chip;
	काष्ठा davinci_gpio_irq_data *irqdata;
	gpio_get_irq_chip_cb_t gpio_get_irq_chip;

	/*
	 * Use davinci_gpio_get_irq_chip by शेष to handle non DT हालs
	 */
	gpio_get_irq_chip = davinci_gpio_get_irq_chip;
	match = of_match_device(of_match_ptr(davinci_gpio_ids),
				dev);
	अगर (match)
		gpio_get_irq_chip = (gpio_get_irq_chip_cb_t)match->data;

	ngpio = pdata->ngpio;

	clk = devm_clk_get(dev, "gpio");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Error %ld getting gpio clock\n", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	अगर (!pdata->gpio_unbanked) अणु
		irq = devm_irq_alloc_descs(dev, -1, 0, ngpio, 0);
		अगर (irq < 0) अणु
			dev_err(dev, "Couldn't allocate IRQ numbers\n");
			clk_disable_unprepare(clk);
			वापस irq;
		पूर्ण

		irq_करोमुख्य = irq_करोमुख्य_add_legacy(dev->of_node, ngpio, irq, 0,
							&davinci_gpio_irq_ops,
							chips);
		अगर (!irq_करोमुख्य) अणु
			dev_err(dev, "Couldn't register an IRQ domain\n");
			clk_disable_unprepare(clk);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Arrange gpio_to_irq() support, handling either direct IRQs or
	 * banked IRQs.  Having GPIOs in the first GPIO bank use direct
	 * IRQs, जबतक the others use banked IRQs, would need some setup
	 * tweaks to recognize hardware which can करो that.
	 */
	chips->chip.to_irq = gpio_to_irq_banked;
	chips->irq_करोमुख्य = irq_करोमुख्य;

	/*
	 * AINTC can handle direct/unbanked IRQs क्रम GPIOs, with the GPIO
	 * controller only handling trigger modes.  We currently assume no
	 * IRQ mux conflicts; gpio_irq_type_unbanked() is only क्रम GPIOs.
	 */
	अगर (pdata->gpio_unbanked) अणु
		/* pass "bank 0" GPIO IRQs to AINTC */
		chips->chip.to_irq = gpio_to_irq_unbanked;
		chips->gpio_unbanked = pdata->gpio_unbanked;
		bपूर्णांकen = GENMASK(pdata->gpio_unbanked / 16, 0);

		/* AINTC handles mask/unmask; GPIO handles triggering */
		irq = chips->irqs[0];
		irq_chip = gpio_get_irq_chip(irq);
		irq_chip->name = "GPIO-AINTC";
		irq_chip->irq_set_type = gpio_irq_type_unbanked;

		/* शेष trigger: both edges */
		g = chips->regs[0];
		ग_लिखोl_relaxed(~0, &g->set_falling);
		ग_लिखोl_relaxed(~0, &g->set_rising);

		/* set the direct IRQs up to use that irqchip */
		क्रम (gpio = 0; gpio < pdata->gpio_unbanked; gpio++) अणु
			irq_set_chip(chips->irqs[gpio], irq_chip);
			irq_set_handler_data(chips->irqs[gpio], chips);
			irq_set_status_flags(chips->irqs[gpio],
					     IRQ_TYPE_EDGE_BOTH);
		पूर्ण

		जाओ करोne;
	पूर्ण

	/*
	 * Or, AINTC can handle IRQs क्रम banks of 16 GPIO IRQs, which we
	 * then chain through our own handler.
	 */
	क्रम (gpio = 0, bank = 0; gpio < ngpio; bank++, gpio += 16) अणु
		/* disabled by शेष, enabled only as needed
		 * There are रेजिस्टर sets क्रम 32 GPIOs. 2 banks of 16
		 * GPIOs are covered by each set of रेजिस्टरs hence भागide by 2
		 */
		g = chips->regs[bank / 2];
		ग_लिखोl_relaxed(~0, &g->clr_falling);
		ग_लिखोl_relaxed(~0, &g->clr_rising);

		/*
		 * Each chip handles 32 gpios, and each irq bank consists of 16
		 * gpio irqs. Pass the irq bank's corresponding controller to
		 * the chained irq handler.
		 */
		irqdata = devm_kzalloc(&pdev->dev,
				       माप(काष्ठा
					      davinci_gpio_irq_data),
					      GFP_KERNEL);
		अगर (!irqdata) अणु
			clk_disable_unprepare(clk);
			वापस -ENOMEM;
		पूर्ण

		irqdata->regs = g;
		irqdata->bank_num = bank;
		irqdata->chip = chips;

		irq_set_chained_handler_and_data(chips->irqs[bank],
						 gpio_irq_handler, irqdata);

		bपूर्णांकen |= BIT(bank);
	पूर्ण

करोne:
	/*
	 * BINTEN -- per-bank पूर्णांकerrupt enable. genirq would also let these
	 * bits be set/cleared dynamically.
	 */
	ग_लिखोl_relaxed(bपूर्णांकen, gpio_base + BINTEN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id davinci_gpio_ids[] = अणु
	अणु .compatible = "ti,keystone-gpio", keystone_gpio_get_irq_chipपूर्ण,
	अणु .compatible = "ti,am654-gpio", keystone_gpio_get_irq_chipपूर्ण,
	अणु .compatible = "ti,dm6441-gpio", davinci_gpio_get_irq_chipपूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_gpio_ids);

अटल काष्ठा platक्रमm_driver davinci_gpio_driver = अणु
	.probe		= davinci_gpio_probe,
	.driver		= अणु
		.name		= "davinci_gpio",
		.of_match_table	= of_match_ptr(davinci_gpio_ids),
	पूर्ण,
पूर्ण;

/**
 * GPIO driver registration needs to be करोne beक्रमe machine_init functions
 * access GPIO. Hence davinci_gpio_drv_reg() is a postcore_initcall.
 */
अटल पूर्णांक __init davinci_gpio_drv_reg(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_gpio_driver);
पूर्ण
postcore_initcall(davinci_gpio_drv_reg);
