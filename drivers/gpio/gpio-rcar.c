<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car GPIO Support
 *
 *  Copyright (C) 2014 Renesas Electronics Corporation
 *  Copyright (C) 2013 Magnus Damm
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>

काष्ठा gpio_rcar_bank_info अणु
	u32 ioपूर्णांकsel;
	u32 inoutsel;
	u32 outdt;
	u32 posneg;
	u32 edglevel;
	u32 bothedge;
	u32 पूर्णांकmsk;
पूर्ण;

काष्ठा gpio_rcar_info अणु
	bool has_outdtsel;
	bool has_both_edge_trigger;
	bool has_always_in;
	bool has_inen;
पूर्ण;

काष्ठा gpio_rcar_priv अणु
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा device *dev;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
	अचिन्हित पूर्णांक irq_parent;
	atomic_t wakeup_path;
	काष्ठा gpio_rcar_info info;
	काष्ठा gpio_rcar_bank_info bank_info;
पूर्ण;

#घोषणा IOINTSEL	0x00	/* General IO/Interrupt Switching Register */
#घोषणा INOUTSEL	0x04	/* General Input/Output Switching Register */
#घोषणा OUTDT		0x08	/* General Output Register */
#घोषणा INDT		0x0c	/* General Input Register */
#घोषणा INTDT		0x10	/* Interrupt Display Register */
#घोषणा INTCLR		0x14	/* Interrupt Clear Register */
#घोषणा INTMSK		0x18	/* Interrupt Mask Register */
#घोषणा MSKCLR		0x1c	/* Interrupt Mask Clear Register */
#घोषणा POSNEG		0x20	/* Positive/Negative Logic Select Register */
#घोषणा EDGLEVEL	0x24	/* Edge/level Select Register */
#घोषणा FILONOFF	0x28	/* Chattering Prevention On/Off Register */
#घोषणा OUTDTSEL	0x40	/* Output Data Select Register */
#घोषणा BOTHEDGE	0x4c	/* One Edge/Both Edge Select Register */
#घोषणा INEN		0x50	/* General Input Enable Register */

#घोषणा RCAR_MAX_GPIO_PER_BANK		32

अटल अंतरभूत u32 gpio_rcar_पढ़ो(काष्ठा gpio_rcar_priv *p, पूर्णांक offs)
अणु
	वापस ioपढ़ो32(p->base + offs);
पूर्ण

अटल अंतरभूत व्योम gpio_rcar_ग_लिखो(काष्ठा gpio_rcar_priv *p, पूर्णांक offs,
				   u32 value)
अणु
	ioग_लिखो32(value, p->base + offs);
पूर्ण

अटल व्योम gpio_rcar_modअगरy_bit(काष्ठा gpio_rcar_priv *p, पूर्णांक offs,
				 पूर्णांक bit, bool value)
अणु
	u32 पंचांगp = gpio_rcar_पढ़ो(p, offs);

	अगर (value)
		पंचांगp |= BIT(bit);
	अन्यथा
		पंचांगp &= ~BIT(bit);

	gpio_rcar_ग_लिखो(p, offs, पंचांगp);
पूर्ण

अटल व्योम gpio_rcar_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(gc);

	gpio_rcar_ग_लिखो(p, INTMSK, ~BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम gpio_rcar_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(gc);

	gpio_rcar_ग_लिखो(p, MSKCLR, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम gpio_rcar_config_पूर्णांकerrupt_input_mode(काष्ठा gpio_rcar_priv *p,
						  अचिन्हित पूर्णांक hwirq,
						  bool active_high_rising_edge,
						  bool level_trigger,
						  bool both)
अणु
	अचिन्हित दीर्घ flags;

	/* follow steps in the GPIO करोcumentation क्रम
	 * "Setting Edge-Sensitive Interrupt Input Mode" and
	 * "Setting Level-Sensitive Interrupt Input Mode"
	 */

	spin_lock_irqsave(&p->lock, flags);

	/* Configure positive or negative logic in POSNEG */
	gpio_rcar_modअगरy_bit(p, POSNEG, hwirq, !active_high_rising_edge);

	/* Configure edge or level trigger in EDGLEVEL */
	gpio_rcar_modअगरy_bit(p, EDGLEVEL, hwirq, !level_trigger);

	/* Select one edge or both edges in BOTHEDGE */
	अगर (p->info.has_both_edge_trigger)
		gpio_rcar_modअगरy_bit(p, BOTHEDGE, hwirq, both);

	/* Select "Interrupt Input Mode" in IOINTSEL */
	gpio_rcar_modअगरy_bit(p, IOINTSEL, hwirq, true);

	/* Write INTCLR in हाल of edge trigger */
	अगर (!level_trigger)
		gpio_rcar_ग_लिखो(p, INTCLR, BIT(hwirq));

	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल पूर्णांक gpio_rcar_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);

	dev_dbg(p->dev, "sense irq = %d, type = %d\n", hwirq, type);

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		gpio_rcar_config_पूर्णांकerrupt_input_mode(p, hwirq, true, true,
						      false);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		gpio_rcar_config_पूर्णांकerrupt_input_mode(p, hwirq, false, true,
						      false);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		gpio_rcar_config_पूर्णांकerrupt_input_mode(p, hwirq, true, false,
						      false);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		gpio_rcar_config_पूर्णांकerrupt_input_mode(p, hwirq, false, false,
						      false);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		अगर (!p->info.has_both_edge_trigger)
			वापस -EINVAL;
		gpio_rcar_config_पूर्णांकerrupt_input_mode(p, hwirq, true, false,
						      true);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_rcar_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(gc);
	पूर्णांक error;

	अगर (p->irq_parent) अणु
		error = irq_set_irq_wake(p->irq_parent, on);
		अगर (error) अणु
			dev_dbg(p->dev, "irq %u doesn't support irq_set_wake\n",
				p->irq_parent);
			p->irq_parent = 0;
		पूर्ण
	पूर्ण

	अगर (on)
		atomic_inc(&p->wakeup_path);
	अन्यथा
		atomic_dec(&p->wakeup_path);

	वापस 0;
पूर्ण

अटल irqवापस_t gpio_rcar_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gpio_rcar_priv *p = dev_id;
	u32 pending;
	अचिन्हित पूर्णांक offset, irqs_handled = 0;

	जबतक ((pending = gpio_rcar_पढ़ो(p, INTDT) &
			  gpio_rcar_पढ़ो(p, INTMSK))) अणु
		offset = __ffs(pending);
		gpio_rcar_ग_लिखो(p, INTCLR, BIT(offset));
		generic_handle_irq(irq_find_mapping(p->gpio_chip.irq.करोमुख्य,
						    offset));
		irqs_handled++;
	पूर्ण

	वापस irqs_handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम gpio_rcar_config_general_input_output_mode(काष्ठा gpio_chip *chip,
						       अचिन्हित पूर्णांक gpio,
						       bool output)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	/* follow steps in the GPIO करोcumentation क्रम
	 * "Setting General Output Mode" and
	 * "Setting General Input Mode"
	 */

	spin_lock_irqsave(&p->lock, flags);

	/* Configure positive logic in POSNEG */
	gpio_rcar_modअगरy_bit(p, POSNEG, gpio, false);

	/* Select "General Input/Output Mode" in IOINTSEL */
	gpio_rcar_modअगरy_bit(p, IOINTSEL, gpio, false);

	/* Select Input Mode or Output Mode in INOUTSEL */
	gpio_rcar_modअगरy_bit(p, INOUTSEL, gpio, output);

	/* Select General Output Register to output data in OUTDTSEL */
	अगर (p->info.has_outdtsel && output)
		gpio_rcar_modअगरy_bit(p, OUTDTSEL, gpio, false);

	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल पूर्णांक gpio_rcar_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	पूर्णांक error;

	error = pm_runसमय_get_sync(p->dev);
	अगर (error < 0) अणु
		pm_runसमय_put(p->dev);
		वापस error;
	पूर्ण

	error = pinctrl_gpio_request(chip->base + offset);
	अगर (error)
		pm_runसमय_put(p->dev);

	वापस error;
पूर्ण

अटल व्योम gpio_rcar_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);

	pinctrl_gpio_मुक्त(chip->base + offset);

	/*
	 * Set the GPIO as an input to ensure that the next GPIO request won't
	 * drive the GPIO pin as an output.
	 */
	gpio_rcar_config_general_input_output_mode(chip, offset, false);

	pm_runसमय_put(p->dev);
पूर्ण

अटल पूर्णांक gpio_rcar_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);

	अगर (gpio_rcar_पढ़ो(p, INOUTSEL) & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक gpio_rcar_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	gpio_rcar_config_general_input_output_mode(chip, offset, false);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_rcar_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	u32 bit = BIT(offset);

	/*
	 * Beक्रमe R-Car Gen3, INDT करोes not show correct pin state when
	 * configured as output, so use OUTDT in हाल of output pins
	 */
	अगर (!p->info.has_always_in && (gpio_rcar_पढ़ो(p, INOUTSEL) & bit))
		वापस !!(gpio_rcar_पढ़ो(p, OUTDT) & bit);
	अन्यथा
		वापस !!(gpio_rcar_पढ़ो(p, INDT) & bit);
पूर्ण

अटल पूर्णांक gpio_rcar_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	u32 bankmask, outमाला_दो, m, val = 0;
	अचिन्हित दीर्घ flags;

	bankmask = mask[0] & GENMASK(chip->ngpio - 1, 0);
	अगर (chip->valid_mask)
		bankmask &= chip->valid_mask[0];

	अगर (!bankmask)
		वापस 0;

	अगर (p->info.has_always_in) अणु
		bits[0] = gpio_rcar_पढ़ो(p, INDT) & bankmask;
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&p->lock, flags);
	outमाला_दो = gpio_rcar_पढ़ो(p, INOUTSEL);
	m = outमाला_दो & bankmask;
	अगर (m)
		val |= gpio_rcar_पढ़ो(p, OUTDT) & m;

	m = ~outमाला_दो & bankmask;
	अगर (m)
		val |= gpio_rcar_पढ़ो(p, INDT) & m;
	spin_unlock_irqrestore(&p->lock, flags);

	bits[0] = val;
	वापस 0;
पूर्ण

अटल व्योम gpio_rcar_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->lock, flags);
	gpio_rcar_modअगरy_bit(p, OUTDT, offset, value);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल व्योम gpio_rcar_set_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				   अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_rcar_priv *p = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 val, bankmask;

	bankmask = mask[0] & GENMASK(chip->ngpio - 1, 0);
	अगर (chip->valid_mask)
		bankmask &= chip->valid_mask[0];

	अगर (!bankmask)
		वापस;

	spin_lock_irqsave(&p->lock, flags);
	val = gpio_rcar_पढ़ो(p, OUTDT);
	val &= ~bankmask;
	val |= (bankmask & bits[0]);
	gpio_rcar_ग_लिखो(p, OUTDT, val);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल पूर्णांक gpio_rcar_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				      पूर्णांक value)
अणु
	/* ग_लिखो GPIO value to output beक्रमe selecting output mode of pin */
	gpio_rcar_set(chip, offset, value);
	gpio_rcar_config_general_input_output_mode(chip, offset, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_rcar_info gpio_rcar_info_gen1 = अणु
	.has_outdtsel = false,
	.has_both_edge_trigger = false,
	.has_always_in = false,
	.has_inen = false,
पूर्ण;

अटल स्थिर काष्ठा gpio_rcar_info gpio_rcar_info_gen2 = अणु
	.has_outdtsel = true,
	.has_both_edge_trigger = true,
	.has_always_in = false,
	.has_inen = false,
पूर्ण;

अटल स्थिर काष्ठा gpio_rcar_info gpio_rcar_info_gen3 = अणु
	.has_outdtsel = true,
	.has_both_edge_trigger = true,
	.has_always_in = true,
	.has_inen = false,
पूर्ण;

अटल स्थिर काष्ठा gpio_rcar_info gpio_rcar_info_v3u = अणु
	.has_outdtsel = true,
	.has_both_edge_trigger = true,
	.has_always_in = true,
	.has_inen = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gpio_rcar_of_table[] = अणु
	अणु
		.compatible = "renesas,gpio-r8a779a0",
		.data = &gpio_rcar_info_v3u,
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen1-gpio",
		.data = &gpio_rcar_info_gen1,
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen2-gpio",
		.data = &gpio_rcar_info_gen2,
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen3-gpio",
		.data = &gpio_rcar_info_gen3,
	पूर्ण, अणु
		.compatible = "renesas,gpio-rcar",
		.data = &gpio_rcar_info_gen1,
	पूर्ण, अणु
		/* Terminator */
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, gpio_rcar_of_table);

अटल पूर्णांक gpio_rcar_parse_dt(काष्ठा gpio_rcar_priv *p, अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा device_node *np = p->dev->of_node;
	स्थिर काष्ठा gpio_rcar_info *info;
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	info = of_device_get_match_data(p->dev);
	p->info = *info;

	ret = of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3, 0, &args);
	*npins = ret == 0 ? args.args[2] : RCAR_MAX_GPIO_PER_BANK;

	अगर (*npins == 0 || *npins > RCAR_MAX_GPIO_PER_BANK) अणु
		dev_warn(p->dev, "Invalid number of gpio lines %u, using %u\n",
			 *npins, RCAR_MAX_GPIO_PER_BANK);
		*npins = RCAR_MAX_GPIO_PER_BANK;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpio_rcar_enable_inमाला_दो(काष्ठा gpio_rcar_priv *p)
अणु
	u32 mask = GENMASK(p->gpio_chip.ngpio - 1, 0);

	/* Select "Input Enable" in INEN */
	अगर (p->gpio_chip.valid_mask)
		mask &= p->gpio_chip.valid_mask[0];
	अगर (mask)
		gpio_rcar_ग_लिखो(p, INEN, gpio_rcar_पढ़ो(p, INEN) | mask);
पूर्ण

अटल पूर्णांक gpio_rcar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_rcar_priv *p;
	काष्ठा resource *irq;
	काष्ठा gpio_chip *gpio_chip;
	काष्ठा irq_chip *irq_chip;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *name = dev_name(dev);
	अचिन्हित पूर्णांक npins;
	पूर्णांक ret;

	p = devm_kzalloc(dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->dev = dev;
	spin_lock_init(&p->lock);

	/* Get device configuration from DT node */
	ret = gpio_rcar_parse_dt(p, &npins);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, p);

	pm_runसमय_enable(dev);

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(dev, "missing IRQ\n");
		ret = -EINVAL;
		जाओ err0;
	पूर्ण

	p->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->base)) अणु
		ret = PTR_ERR(p->base);
		जाओ err0;
	पूर्ण

	gpio_chip = &p->gpio_chip;
	gpio_chip->request = gpio_rcar_request;
	gpio_chip->मुक्त = gpio_rcar_मुक्त;
	gpio_chip->get_direction = gpio_rcar_get_direction;
	gpio_chip->direction_input = gpio_rcar_direction_input;
	gpio_chip->get = gpio_rcar_get;
	gpio_chip->get_multiple = gpio_rcar_get_multiple;
	gpio_chip->direction_output = gpio_rcar_direction_output;
	gpio_chip->set = gpio_rcar_set;
	gpio_chip->set_multiple = gpio_rcar_set_multiple;
	gpio_chip->label = name;
	gpio_chip->parent = dev;
	gpio_chip->owner = THIS_MODULE;
	gpio_chip->base = -1;
	gpio_chip->ngpio = npins;

	irq_chip = &p->irq_chip;
	irq_chip->name = "gpio-rcar";
	irq_chip->parent_device = dev;
	irq_chip->irq_mask = gpio_rcar_irq_disable;
	irq_chip->irq_unmask = gpio_rcar_irq_enable;
	irq_chip->irq_set_type = gpio_rcar_irq_set_type;
	irq_chip->irq_set_wake = gpio_rcar_irq_set_wake;
	irq_chip->flags = IRQCHIP_SET_TYPE_MASKED | IRQCHIP_MASK_ON_SUSPEND;

	girq = &gpio_chip->irq;
	girq->chip = irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	ret = gpiochip_add_data(gpio_chip, p);
	अगर (ret) अणु
		dev_err(dev, "failed to add GPIO controller\n");
		जाओ err0;
	पूर्ण

	p->irq_parent = irq->start;
	अगर (devm_request_irq(dev, irq->start, gpio_rcar_irq_handler,
			     IRQF_SHARED, name, p)) अणु
		dev_err(dev, "failed to request IRQ\n");
		ret = -ENOENT;
		जाओ err1;
	पूर्ण

	अगर (p->info.has_inen) अणु
		pm_runसमय_get_sync(p->dev);
		gpio_rcar_enable_inमाला_दो(p);
		pm_runसमय_put(p->dev);
	पूर्ण

	dev_info(dev, "driving %d GPIOs\n", npins);

	वापस 0;

err1:
	gpiochip_हटाओ(gpio_chip);
err0:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक gpio_rcar_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_rcar_priv *p = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&p->gpio_chip);

	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpio_rcar_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_rcar_priv *p = dev_get_drvdata(dev);

	p->bank_info.ioपूर्णांकsel = gpio_rcar_पढ़ो(p, IOINTSEL);
	p->bank_info.inoutsel = gpio_rcar_पढ़ो(p, INOUTSEL);
	p->bank_info.outdt = gpio_rcar_पढ़ो(p, OUTDT);
	p->bank_info.पूर्णांकmsk = gpio_rcar_पढ़ो(p, INTMSK);
	p->bank_info.posneg = gpio_rcar_पढ़ो(p, POSNEG);
	p->bank_info.edglevel = gpio_rcar_पढ़ो(p, EDGLEVEL);
	अगर (p->info.has_both_edge_trigger)
		p->bank_info.bothedge = gpio_rcar_पढ़ो(p, BOTHEDGE);

	अगर (atomic_पढ़ो(&p->wakeup_path))
		device_set_wakeup_path(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_rcar_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_rcar_priv *p = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक offset;
	u32 mask;

	क्रम (offset = 0; offset < p->gpio_chip.ngpio; offset++) अणु
		अगर (!gpiochip_line_is_valid(&p->gpio_chip, offset))
			जारी;

		mask = BIT(offset);
		/* I/O pin */
		अगर (!(p->bank_info.ioपूर्णांकsel & mask)) अणु
			अगर (p->bank_info.inoutsel & mask)
				gpio_rcar_direction_output(
					&p->gpio_chip, offset,
					!!(p->bank_info.outdt & mask));
			अन्यथा
				gpio_rcar_direction_input(&p->gpio_chip,
							  offset);
		पूर्ण अन्यथा अणु
			/* Interrupt pin */
			gpio_rcar_config_पूर्णांकerrupt_input_mode(
				p,
				offset,
				!(p->bank_info.posneg & mask),
				!(p->bank_info.edglevel & mask),
				!!(p->bank_info.bothedge & mask));

			अगर (p->bank_info.पूर्णांकmsk & mask)
				gpio_rcar_ग_लिखो(p, MSKCLR, mask);
		पूर्ण
	पूर्ण

	अगर (p->info.has_inen)
		gpio_rcar_enable_inमाला_दो(p);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP*/

अटल SIMPLE_DEV_PM_OPS(gpio_rcar_pm_ops, gpio_rcar_suspend, gpio_rcar_resume);

अटल काष्ठा platक्रमm_driver gpio_rcar_device_driver = अणु
	.probe		= gpio_rcar_probe,
	.हटाओ		= gpio_rcar_हटाओ,
	.driver		= अणु
		.name	= "gpio_rcar",
		.pm     = &gpio_rcar_pm_ops,
		.of_match_table = of_match_ptr(gpio_rcar_of_table),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(gpio_rcar_device_driver);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas R-Car GPIO Driver");
MODULE_LICENSE("GPL v2");
