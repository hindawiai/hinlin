<शैली गुरु>
/*
 * SPEAr platक्रमm PLGPIO driver
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <viresh.kumar@linaro.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/spinlock.h>

#घोषणा MAX_GPIO_PER_REG		32
#घोषणा PIN_OFFSET(pin)			(pin % MAX_GPIO_PER_REG)
#घोषणा REG_OFFSET(base, reg, pin)	(base + reg + (pin / MAX_GPIO_PER_REG) \
							* माप(पूर्णांक *))

/*
 * plgpio pins in all machines are not one to one mapped, bitwise with रेजिस्टरs
 * bits. These set of macros define रेजिस्टर masks क्रम which below functions
 * (pin_to_offset and offset_to_pin) are required to be called.
 */
#घोषणा PTO_ENB_REG		0x001
#घोषणा PTO_WDATA_REG		0x002
#घोषणा PTO_सूची_REG		0x004
#घोषणा PTO_IE_REG		0x008
#घोषणा PTO_RDATA_REG		0x010
#घोषणा PTO_MIS_REG		0x020

काष्ठा plgpio_regs अणु
	u32 enb;		/* enable रेजिस्टर */
	u32 wdata;		/* ग_लिखो data रेजिस्टर */
	u32 dir;		/* direction set रेजिस्टर */
	u32 rdata;		/* पढ़ो data रेजिस्टर */
	u32 ie;			/* पूर्णांकerrupt enable रेजिस्टर */
	u32 mis;		/* mask पूर्णांकerrupt status रेजिस्टर */
	u32 eit;		/* edge पूर्णांकerrupt type */
पूर्ण;

/*
 * काष्ठा plgpio: plgpio driver specअगरic काष्ठाure
 *
 * lock: lock क्रम guarding gpio रेजिस्टरs
 * base: base address of plgpio block
 * chip: gpio framework specअगरic chip inक्रमmation काष्ठाure
 * p2o: function ptr क्रम pin to offset conversion. This is required only क्रम
 *	machines where mapping b/w pin and offset is not 1-to-1.
 * o2p: function ptr क्रम offset to pin conversion. This is required only क्रम
 *	machines where mapping b/w pin and offset is not 1-to-1.
 * p2o_regs: mask of रेजिस्टरs क्रम which p2o and o2p are applicable
 * regs: रेजिस्टर offsets
 * csave_regs: context save रेजिस्टरs क्रम standby/sleep/hibernate हालs
 */
काष्ठा plgpio अणु
	spinlock_t		lock;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा gpio_chip	chip;
	पूर्णांक			(*p2o)(पूर्णांक pin);	/* pin_to_offset */
	पूर्णांक			(*o2p)(पूर्णांक offset);	/* offset_to_pin */
	u32			p2o_regs;
	काष्ठा plgpio_regs	regs;
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा plgpio_regs	*csave_regs;
#पूर्ण_अगर
पूर्ण;

/* रेजिस्टर manipulation अंतरभूत functions */
अटल अंतरभूत u32 is_plgpio_set(व्योम __iomem *base, u32 pin, u32 reg)
अणु
	u32 offset = PIN_OFFSET(pin);
	व्योम __iomem *reg_off = REG_OFFSET(base, reg, pin);
	u32 val = पढ़ोl_relaxed(reg_off);

	वापस !!(val & (1 << offset));
पूर्ण

अटल अंतरभूत व्योम plgpio_reg_set(व्योम __iomem *base, u32 pin, u32 reg)
अणु
	u32 offset = PIN_OFFSET(pin);
	व्योम __iomem *reg_off = REG_OFFSET(base, reg, pin);
	u32 val = पढ़ोl_relaxed(reg_off);

	ग_लिखोl_relaxed(val | (1 << offset), reg_off);
पूर्ण

अटल अंतरभूत व्योम plgpio_reg_reset(व्योम __iomem *base, u32 pin, u32 reg)
अणु
	u32 offset = PIN_OFFSET(pin);
	व्योम __iomem *reg_off = REG_OFFSET(base, reg, pin);
	u32 val = पढ़ोl_relaxed(reg_off);

	ग_लिखोl_relaxed(val & ~(1 << offset), reg_off);
पूर्ण

/* gpio framework specअगरic routines */
अटल पूर्णांक plgpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_सूची_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_set(plgpio->base, offset, plgpio->regs.dir);
	spin_unlock_irqrestore(&plgpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक plgpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
		पूर्णांक value)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित dir_offset = offset, wdata_offset = offset, पंचांगp;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & (PTO_सूची_REG | PTO_WDATA_REG))) अणु
		पंचांगp = plgpio->p2o(offset);
		अगर (पंचांगp == -1)
			वापस -EINVAL;

		अगर (plgpio->p2o_regs & PTO_सूची_REG)
			dir_offset = पंचांगp;
		अगर (plgpio->p2o_regs & PTO_WDATA_REG)
			wdata_offset = पंचांगp;
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	अगर (value)
		plgpio_reg_set(plgpio->base, wdata_offset,
				plgpio->regs.wdata);
	अन्यथा
		plgpio_reg_reset(plgpio->base, wdata_offset,
				plgpio->regs.wdata);

	plgpio_reg_reset(plgpio->base, dir_offset, plgpio->regs.dir);
	spin_unlock_irqrestore(&plgpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक plgpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);

	अगर (offset >= chip->ngpio)
		वापस -EINVAL;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_RDATA_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस -EINVAL;
	पूर्ण

	वापस is_plgpio_set(plgpio->base, offset, plgpio->regs.rdata);
पूर्ण

अटल व्योम plgpio_set_value(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);

	अगर (offset >= chip->ngpio)
		वापस;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_WDATA_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस;
	पूर्ण

	अगर (value)
		plgpio_reg_set(plgpio->base, offset, plgpio->regs.wdata);
	अन्यथा
		plgpio_reg_reset(plgpio->base, offset, plgpio->regs.wdata);
पूर्ण

अटल पूर्णांक plgpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);
	पूर्णांक gpio = chip->base + offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (offset >= chip->ngpio)
		वापस -EINVAL;

	ret = pinctrl_gpio_request(gpio);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(plgpio->clk)) अणु
		ret = clk_enable(plgpio->clk);
		अगर (ret)
			जाओ err0;
	पूर्ण

	अगर (plgpio->regs.enb == -1)
		वापस 0;

	/*
	 * put gpio in IN mode beक्रमe enabling it. This make enabling gpio safe
	 */
	ret = plgpio_direction_input(chip, offset);
	अगर (ret)
		जाओ err1;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_ENB_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1) अणु
			ret = -EINVAL;
			जाओ err1;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_set(plgpio->base, offset, plgpio->regs.enb);
	spin_unlock_irqrestore(&plgpio->lock, flags);
	वापस 0;

err1:
	अगर (!IS_ERR(plgpio->clk))
		clk_disable(plgpio->clk);
err0:
	pinctrl_gpio_मुक्त(gpio);
	वापस ret;
पूर्ण

अटल व्योम plgpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा plgpio *plgpio = gpiochip_get_data(chip);
	पूर्णांक gpio = chip->base + offset;
	अचिन्हित दीर्घ flags;

	अगर (offset >= chip->ngpio)
		वापस;

	अगर (plgpio->regs.enb == -1)
		जाओ disable_clk;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_ENB_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस;
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_reset(plgpio->base, offset, plgpio->regs.enb);
	spin_unlock_irqrestore(&plgpio->lock, flags);

disable_clk:
	अगर (!IS_ERR(plgpio->clk))
		clk_disable(plgpio->clk);

	pinctrl_gpio_मुक्त(gpio);
पूर्ण

/* PLGPIO IRQ */
अटल व्योम plgpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा plgpio *plgpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	अचिन्हित दीर्घ flags;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_IE_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस;
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_set(plgpio->base, offset, plgpio->regs.ie);
	spin_unlock_irqrestore(&plgpio->lock, flags);
पूर्ण

अटल व्योम plgpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा plgpio *plgpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	अचिन्हित दीर्घ flags;

	/* get correct offset क्रम "offset" pin */
	अगर (plgpio->p2o && (plgpio->p2o_regs & PTO_IE_REG)) अणु
		offset = plgpio->p2o(offset);
		अगर (offset == -1)
			वापस;
	पूर्ण

	spin_lock_irqsave(&plgpio->lock, flags);
	plgpio_reg_reset(plgpio->base, offset, plgpio->regs.ie);
	spin_unlock_irqrestore(&plgpio->lock, flags);
पूर्ण

अटल पूर्णांक plgpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित trigger)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा plgpio *plgpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	व्योम __iomem *reg_off;
	अचिन्हित पूर्णांक supported_type = 0, val;

	अगर (offset >= plgpio->chip.ngpio)
		वापस -EINVAL;

	अगर (plgpio->regs.eit == -1)
		supported_type = IRQ_TYPE_LEVEL_HIGH;
	अन्यथा
		supported_type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;

	अगर (!(trigger & supported_type))
		वापस -EINVAL;

	अगर (plgpio->regs.eit == -1)
		वापस 0;

	reg_off = REG_OFFSET(plgpio->base, plgpio->regs.eit, offset);
	val = पढ़ोl_relaxed(reg_off);

	offset = PIN_OFFSET(offset);
	अगर (trigger & IRQ_TYPE_EDGE_RISING)
		ग_लिखोl_relaxed(val | (1 << offset), reg_off);
	अन्यथा
		ग_लिखोl_relaxed(val & ~(1 << offset), reg_off);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip plgpio_irqchip = अणु
	.name		= "PLGPIO",
	.irq_enable	= plgpio_irq_enable,
	.irq_disable	= plgpio_irq_disable,
	.irq_set_type	= plgpio_irq_set_type,
पूर्ण;

अटल व्योम plgpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा plgpio *plgpio = gpiochip_get_data(gc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	पूर्णांक regs_count, count, pin, offset, i = 0;
	अचिन्हित दीर्घ pending;

	count = plgpio->chip.ngpio;
	regs_count = DIV_ROUND_UP(count, MAX_GPIO_PER_REG);

	chained_irq_enter(irqchip, desc);
	/* check all plgpio MIS रेजिस्टरs क्रम a possible पूर्णांकerrupt */
	क्रम (; i < regs_count; i++) अणु
		pending = पढ़ोl_relaxed(plgpio->base + plgpio->regs.mis +
				i * माप(पूर्णांक *));
		अगर (!pending)
			जारी;

		/* clear पूर्णांकerrupts */
		ग_लिखोl_relaxed(~pending, plgpio->base + plgpio->regs.mis +
				i * माप(पूर्णांक *));
		/*
		 * clear extra bits in last रेजिस्टर having gpios < MAX/REG
		 * ex: Suppose there are max 102 plgpios. then last रेजिस्टर
		 * must have only (102 - MAX_GPIO_PER_REG * 3) = 6 relevant bits
		 * so, we must not take other 28 bits पूर्णांकo consideration क्रम
		 * checking पूर्णांकerrupt. so clear those bits.
		 */
		count = count - i * MAX_GPIO_PER_REG;
		अगर (count < MAX_GPIO_PER_REG)
			pending &= (1 << count) - 1;

		क्रम_each_set_bit(offset, &pending, MAX_GPIO_PER_REG) अणु
			/* get correct pin क्रम "offset" */
			अगर (plgpio->o2p && (plgpio->p2o_regs & PTO_MIS_REG)) अणु
				pin = plgpio->o2p(offset);
				अगर (pin == -1)
					जारी;
			पूर्ण अन्यथा
				pin = offset;

			/* get correct irq line number */
			pin = i * MAX_GPIO_PER_REG + pin;
			generic_handle_irq(
				irq_find_mapping(gc->irq.करोमुख्य, pin));
		पूर्ण
	पूर्ण
	chained_irq_निकास(irqchip, desc);
पूर्ण

/*
 * pin to offset and offset to pin converter functions
 *
 * In spear310 there is inconsistency among bit positions in plgpio regiseters,
 * क्रम dअगरferent plgpio pins. For example: क्रम pin 27, bit offset is 23, pin
 * 28-33 are not supported, pin 95 has offset bit 95, bit 100 has offset bit 1
 */
अटल पूर्णांक spear310_p2o(पूर्णांक pin)
अणु
	पूर्णांक offset = pin;

	अगर (pin <= 27)
		offset += 4;
	अन्यथा अगर (pin <= 33)
		offset = -1;
	अन्यथा अगर (pin <= 97)
		offset -= 2;
	अन्यथा अगर (pin <= 101)
		offset = 101 - pin;
	अन्यथा
		offset = -1;

	वापस offset;
पूर्ण

अटल पूर्णांक spear310_o2p(पूर्णांक offset)
अणु
	अगर (offset <= 3)
		वापस 101 - offset;
	अन्यथा अगर (offset <= 31)
		वापस offset - 4;
	अन्यथा
		वापस offset + 2;
पूर्ण

अटल पूर्णांक plgpio_probe_dt(काष्ठा platक्रमm_device *pdev, काष्ठा plgpio *plgpio)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret = -EINVAL;
	u32 val;

	अगर (of_machine_is_compatible("st,spear310")) अणु
		plgpio->p2o = spear310_p2o;
		plgpio->o2p = spear310_o2p;
		plgpio->p2o_regs = PTO_WDATA_REG | PTO_सूची_REG | PTO_IE_REG |
			PTO_RDATA_REG | PTO_MIS_REG;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,ngpio", &val)) अणु
		plgpio->chip.ngpio = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid ngpio field\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,enb-reg", &val))
		plgpio->regs.enb = val;
	अन्यथा
		plgpio->regs.enb = -1;

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,wdata-reg", &val)) अणु
		plgpio->regs.wdata = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid wdata reg\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,dir-reg", &val)) अणु
		plgpio->regs.dir = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid dir reg\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,ie-reg", &val)) अणु
		plgpio->regs.ie = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid ie reg\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,rdata-reg", &val)) अणु
		plgpio->regs.rdata = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid rdata reg\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,mis-reg", &val)) अणु
		plgpio->regs.mis = val;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT: Invalid mis reg\n");
		जाओ end;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "st-plgpio,eit-reg", &val))
		plgpio->regs.eit = val;
	अन्यथा
		plgpio->regs.eit = -1;

	वापस 0;

end:
	वापस ret;
पूर्ण
अटल पूर्णांक plgpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plgpio *plgpio;
	पूर्णांक ret, irq;

	plgpio = devm_kzalloc(&pdev->dev, माप(*plgpio), GFP_KERNEL);
	अगर (!plgpio)
		वापस -ENOMEM;

	plgpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(plgpio->base))
		वापस PTR_ERR(plgpio->base);

	ret = plgpio_probe_dt(pdev, plgpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "DT probe failed\n");
		वापस ret;
	पूर्ण

	plgpio->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(plgpio->clk))
		dev_warn(&pdev->dev, "clk_get() failed, work without it\n");

#अगर_घोषित CONFIG_PM_SLEEP
	plgpio->csave_regs = devm_kसुस्मृति(&pdev->dev,
			DIV_ROUND_UP(plgpio->chip.ngpio, MAX_GPIO_PER_REG),
			माप(*plgpio->csave_regs),
			GFP_KERNEL);
	अगर (!plgpio->csave_regs)
		वापस -ENOMEM;
#पूर्ण_अगर

	platक्रमm_set_drvdata(pdev, plgpio);
	spin_lock_init(&plgpio->lock);

	plgpio->chip.base = -1;
	plgpio->chip.request = plgpio_request;
	plgpio->chip.मुक्त = plgpio_मुक्त;
	plgpio->chip.direction_input = plgpio_direction_input;
	plgpio->chip.direction_output = plgpio_direction_output;
	plgpio->chip.get = plgpio_get_value;
	plgpio->chip.set = plgpio_set_value;
	plgpio->chip.label = dev_name(&pdev->dev);
	plgpio->chip.parent = &pdev->dev;
	plgpio->chip.owner = THIS_MODULE;
	plgpio->chip.of_node = pdev->dev.of_node;

	अगर (!IS_ERR(plgpio->clk)) अणु
		ret = clk_prepare(plgpio->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "clk prepare failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		girq = &plgpio->chip.irq;
		girq->chip = &plgpio_irqchip;
		girq->parent_handler = plgpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		dev_info(&pdev->dev, "PLGPIO registering with IRQs\n");
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "PLGPIO registering without IRQs\n");
	पूर्ण

	ret = gpiochip_add_data(&plgpio->chip, plgpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add gpio chip\n");
		जाओ unprepare_clk;
	पूर्ण

	वापस 0;

unprepare_clk:
	अगर (!IS_ERR(plgpio->clk))
		clk_unprepare(plgpio->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक plgpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा plgpio *plgpio = dev_get_drvdata(dev);
	पूर्णांक i, reg_count = DIV_ROUND_UP(plgpio->chip.ngpio, MAX_GPIO_PER_REG);
	व्योम __iomem *off;

	क्रम (i = 0; i < reg_count; i++) अणु
		off = plgpio->base + i * माप(पूर्णांक *);

		अगर (plgpio->regs.enb != -1)
			plgpio->csave_regs[i].enb =
				पढ़ोl_relaxed(plgpio->regs.enb + off);
		अगर (plgpio->regs.eit != -1)
			plgpio->csave_regs[i].eit =
				पढ़ोl_relaxed(plgpio->regs.eit + off);
		plgpio->csave_regs[i].wdata = पढ़ोl_relaxed(plgpio->regs.wdata +
				off);
		plgpio->csave_regs[i].dir = पढ़ोl_relaxed(plgpio->regs.dir +
				off);
		plgpio->csave_regs[i].ie = पढ़ोl_relaxed(plgpio->regs.ie + off);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This is used to correct the values in end रेजिस्टरs. End रेजिस्टरs contain
 * extra bits that might be used क्रम other purpose in platक्रमm. So, we shouldn't
 * overग_लिखो these bits. This macro, पढ़ोs given रेजिस्टर again, preserves other
 * bit values (non-plgpio bits), and retain captured value (plgpio bits).
 */
#घोषणा plgpio_prepare_reg(__reg, _off, _mask, _पंचांगp)		\
अणु								\
	_पंचांगp = पढ़ोl_relaxed(plgpio->regs.__reg + _off);		\
	_पंचांगp &= ~_mask;						\
	plgpio->csave_regs[i].__reg =				\
		_पंचांगp | (plgpio->csave_regs[i].__reg & _mask);	\
पूर्ण

अटल पूर्णांक plgpio_resume(काष्ठा device *dev)
अणु
	काष्ठा plgpio *plgpio = dev_get_drvdata(dev);
	पूर्णांक i, reg_count = DIV_ROUND_UP(plgpio->chip.ngpio, MAX_GPIO_PER_REG);
	व्योम __iomem *off;
	u32 mask, पंचांगp;

	क्रम (i = 0; i < reg_count; i++) अणु
		off = plgpio->base + i * माप(पूर्णांक *);

		अगर (i == reg_count - 1) अणु
			mask = (1 << (plgpio->chip.ngpio - i *
						MAX_GPIO_PER_REG)) - 1;

			अगर (plgpio->regs.enb != -1)
				plgpio_prepare_reg(enb, off, mask, पंचांगp);

			अगर (plgpio->regs.eit != -1)
				plgpio_prepare_reg(eit, off, mask, पंचांगp);

			plgpio_prepare_reg(wdata, off, mask, पंचांगp);
			plgpio_prepare_reg(dir, off, mask, पंचांगp);
			plgpio_prepare_reg(ie, off, mask, पंचांगp);
		पूर्ण

		ग_लिखोl_relaxed(plgpio->csave_regs[i].wdata, plgpio->regs.wdata +
				off);
		ग_लिखोl_relaxed(plgpio->csave_regs[i].dir, plgpio->regs.dir +
				off);

		अगर (plgpio->regs.eit != -1)
			ग_लिखोl_relaxed(plgpio->csave_regs[i].eit,
					plgpio->regs.eit + off);

		ग_लिखोl_relaxed(plgpio->csave_regs[i].ie, plgpio->regs.ie + off);

		अगर (plgpio->regs.enb != -1)
			ग_लिखोl_relaxed(plgpio->csave_regs[i].enb,
					plgpio->regs.enb + off);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(plgpio_dev_pm_ops, plgpio_suspend, plgpio_resume);

अटल स्थिर काष्ठा of_device_id plgpio_of_match[] = अणु
	अणु .compatible = "st,spear-plgpio" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver plgpio_driver = अणु
	.probe = plgpio_probe,
	.driver = अणु
		.name = "spear-plgpio",
		.pm = &plgpio_dev_pm_ops,
		.of_match_table = plgpio_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init plgpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&plgpio_driver);
पूर्ण
subsys_initcall(plgpio_init);
