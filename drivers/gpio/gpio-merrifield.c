<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Merrअगरield SoC GPIO driver
 *
 * Copyright (c) 2016 Intel Corporation.
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा GCCR		0x000	/* controller configuration */
#घोषणा GPLR		0x004	/* pin level r/o */
#घोषणा GPDR		0x01c	/* pin direction */
#घोषणा GPSR		0x034	/* pin set w/o */
#घोषणा GPCR		0x04c	/* pin clear w/o */
#घोषणा GRER		0x064	/* rising edge detect */
#घोषणा GFER		0x07c	/* falling edge detect */
#घोषणा GFBR		0x094	/* glitch filter bypass */
#घोषणा GIMR		0x0ac	/* पूर्णांकerrupt mask */
#घोषणा GISR		0x0c4	/* पूर्णांकerrupt source */
#घोषणा GITR		0x300	/* input type */
#घोषणा GLPR		0x318	/* level input polarity */
#घोषणा GWMR		0x400	/* wake mask */
#घोषणा GWSR		0x418	/* wake source */
#घोषणा GSIR		0xc00	/* secure input */

/* Intel Merrअगरield has 192 GPIO pins */
#घोषणा MRFLD_NGPIO	192

काष्ठा mrfld_gpio_pinrange अणु
	अचिन्हित पूर्णांक gpio_base;
	अचिन्हित पूर्णांक pin_base;
	अचिन्हित पूर्णांक npins;
पूर्ण;

#घोषणा GPIO_PINRANGE(gstart, gend, pstart)		\
	अणु						\
		.gpio_base = (gstart),			\
		.pin_base = (pstart),			\
		.npins = (gend) - (gstart) + 1,		\
	पूर्ण

काष्ठा mrfld_gpio अणु
	काष्ठा gpio_chip	chip;
	व्योम __iomem		*reg_base;
	raw_spinlock_t		lock;
	काष्ठा device		*dev;
पूर्ण;

अटल स्थिर काष्ठा mrfld_gpio_pinrange mrfld_gpio_ranges[] = अणु
	GPIO_PINRANGE(0, 11, 146),
	GPIO_PINRANGE(12, 13, 144),
	GPIO_PINRANGE(14, 15, 35),
	GPIO_PINRANGE(16, 16, 164),
	GPIO_PINRANGE(17, 18, 105),
	GPIO_PINRANGE(19, 22, 101),
	GPIO_PINRANGE(23, 30, 107),
	GPIO_PINRANGE(32, 43, 67),
	GPIO_PINRANGE(44, 63, 195),
	GPIO_PINRANGE(64, 67, 140),
	GPIO_PINRANGE(68, 69, 165),
	GPIO_PINRANGE(70, 71, 65),
	GPIO_PINRANGE(72, 76, 228),
	GPIO_PINRANGE(77, 86, 37),
	GPIO_PINRANGE(87, 87, 48),
	GPIO_PINRANGE(88, 88, 47),
	GPIO_PINRANGE(89, 96, 49),
	GPIO_PINRANGE(97, 97, 34),
	GPIO_PINRANGE(102, 119, 83),
	GPIO_PINRANGE(120, 123, 79),
	GPIO_PINRANGE(124, 135, 115),
	GPIO_PINRANGE(137, 142, 158),
	GPIO_PINRANGE(154, 163, 24),
	GPIO_PINRANGE(164, 176, 215),
	GPIO_PINRANGE(177, 189, 127),
	GPIO_PINRANGE(190, 191, 178),
पूर्ण;

अटल व्योम __iomem *gpio_reg(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      अचिन्हित पूर्णांक reg_type_offset)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	u8 reg = offset / 32;

	वापस priv->reg_base + reg_type_offset + reg * 4;
पूर्ण

अटल पूर्णांक mrfld_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *gplr = gpio_reg(chip, offset, GPLR);

	वापस !!(पढ़ोl(gplr) & BIT(offset % 32));
पूर्ण

अटल व्योम mrfld_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	व्योम __iomem *gpsr, *gpcr;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&priv->lock, flags);

	अगर (value) अणु
		gpsr = gpio_reg(chip, offset, GPSR);
		ग_लिखोl(BIT(offset % 32), gpsr);
	पूर्ण अन्यथा अणु
		gpcr = gpio_reg(chip, offset, GPCR);
		ग_लिखोl(BIT(offset % 32), gpcr);
	पूर्ण

	raw_spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक mrfld_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	व्योम __iomem *gpdr = gpio_reg(chip, offset, GPDR);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&priv->lock, flags);

	value = पढ़ोl(gpdr);
	value &= ~BIT(offset % 32);
	ग_लिखोl(value, gpdr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	व्योम __iomem *gpdr = gpio_reg(chip, offset, GPDR);
	अचिन्हित दीर्घ flags;

	mrfld_gpio_set(chip, offset, value);

	raw_spin_lock_irqsave(&priv->lock, flags);

	value = पढ़ोl(gpdr);
	value |= BIT(offset % 32);
	ग_लिखोl(value, gpdr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *gpdr = gpio_reg(chip, offset, GPDR);

	अगर (पढ़ोl(gpdr) & BIT(offset % 32))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक mrfld_gpio_set_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	व्योम __iomem *gfbr = gpio_reg(chip, offset, GFBR);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&priv->lock, flags);

	अगर (debounce)
		value = पढ़ोl(gfbr) & ~BIT(offset % 32);
	अन्यथा
		value = पढ़ोl(gfbr) | BIT(offset % 32);
	ग_लिखोl(value, gfbr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर ((pinconf_to_config_param(config) == PIN_CONFIG_BIAS_DISABLE) ||
	    (pinconf_to_config_param(config) == PIN_CONFIG_BIAS_PULL_UP) ||
	    (pinconf_to_config_param(config) == PIN_CONFIG_BIAS_PULL_DOWN))
		वापस gpiochip_generic_config(chip, offset, config);

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	वापस mrfld_gpio_set_debounce(chip, offset, debounce);
पूर्ण

अटल व्योम mrfld_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा mrfld_gpio *priv = irq_data_get_irq_chip_data(d);
	u32 gpio = irqd_to_hwirq(d);
	व्योम __iomem *gisr = gpio_reg(&priv->chip, gpio, GISR);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&priv->lock, flags);

	ग_लिखोl(BIT(gpio % 32), gisr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम mrfld_irq_unmask_mask(काष्ठा irq_data *d, bool unmask)
अणु
	काष्ठा mrfld_gpio *priv = irq_data_get_irq_chip_data(d);
	u32 gpio = irqd_to_hwirq(d);
	व्योम __iomem *gimr = gpio_reg(&priv->chip, gpio, GIMR);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&priv->lock, flags);

	अगर (unmask)
		value = पढ़ोl(gimr) | BIT(gpio % 32);
	अन्यथा
		value = पढ़ोl(gimr) & ~BIT(gpio % 32);
	ग_लिखोl(value, gimr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम mrfld_irq_mask(काष्ठा irq_data *d)
अणु
	mrfld_irq_unmask_mask(d, false);
पूर्ण

अटल व्योम mrfld_irq_unmask(काष्ठा irq_data *d)
अणु
	mrfld_irq_unmask_mask(d, true);
पूर्ण

अटल पूर्णांक mrfld_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(gc);
	u32 gpio = irqd_to_hwirq(d);
	व्योम __iomem *grer = gpio_reg(&priv->chip, gpio, GRER);
	व्योम __iomem *gfer = gpio_reg(&priv->chip, gpio, GFER);
	व्योम __iomem *gitr = gpio_reg(&priv->chip, gpio, GITR);
	व्योम __iomem *glpr = gpio_reg(&priv->chip, gpio, GLPR);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&priv->lock, flags);

	अगर (type & IRQ_TYPE_EDGE_RISING)
		value = पढ़ोl(grer) | BIT(gpio % 32);
	अन्यथा
		value = पढ़ोl(grer) & ~BIT(gpio % 32);
	ग_लिखोl(value, grer);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		value = पढ़ोl(gfer) | BIT(gpio % 32);
	अन्यथा
		value = पढ़ोl(gfer) & ~BIT(gpio % 32);
	ग_लिखोl(value, gfer);

	/*
	 * To prevent glitches from triggering an unपूर्णांकended level पूर्णांकerrupt,
	 * configure GLPR रेजिस्टर first and then configure GITR.
	 */
	अगर (type & IRQ_TYPE_LEVEL_LOW)
		value = पढ़ोl(glpr) | BIT(gpio % 32);
	अन्यथा
		value = पढ़ोl(glpr) & ~BIT(gpio % 32);
	ग_लिखोl(value, glpr);

	अगर (type & IRQ_TYPE_LEVEL_MASK) अणु
		value = पढ़ोl(gitr) | BIT(gpio % 32);
		ग_लिखोl(value, gitr);

		irq_set_handler_locked(d, handle_level_irq);
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH) अणु
		value = पढ़ोl(gitr) & ~BIT(gpio % 32);
		ग_लिखोl(value, gitr);

		irq_set_handler_locked(d, handle_edge_irq);
	पूर्ण

	raw_spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(gc);
	u32 gpio = irqd_to_hwirq(d);
	व्योम __iomem *gwmr = gpio_reg(&priv->chip, gpio, GWMR);
	व्योम __iomem *gwsr = gpio_reg(&priv->chip, gpio, GWSR);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&priv->lock, flags);

	/* Clear the existing wake status */
	ग_लिखोl(BIT(gpio % 32), gwsr);

	अगर (on)
		value = पढ़ोl(gwmr) | BIT(gpio % 32);
	अन्यथा
		value = पढ़ोl(gwmr) & ~BIT(gpio % 32);
	ग_लिखोl(value, gwmr);

	raw_spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(priv->dev, "%sable wake for gpio %u\n", on ? "en" : "dis", gpio);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mrfld_irqchip = अणु
	.name		= "gpio-merrifield",
	.irq_ack	= mrfld_irq_ack,
	.irq_mask	= mrfld_irq_mask,
	.irq_unmask	= mrfld_irq_unmask,
	.irq_set_type	= mrfld_irq_set_type,
	.irq_set_wake	= mrfld_irq_set_wake,
पूर्ण;

अटल व्योम mrfld_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(gc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ base, gpio;

	chained_irq_enter(irqchip, desc);

	/* Check GPIO controller to check which pin triggered the पूर्णांकerrupt */
	क्रम (base = 0; base < priv->chip.ngpio; base += 32) अणु
		व्योम __iomem *gisr = gpio_reg(&priv->chip, base, GISR);
		व्योम __iomem *gimr = gpio_reg(&priv->chip, base, GIMR);
		अचिन्हित दीर्घ pending, enabled;

		pending = पढ़ोl(gisr);
		enabled = पढ़ोl(gimr);

		/* Only पूर्णांकerrupts that are enabled */
		pending &= enabled;

		क्रम_each_set_bit(gpio, &pending, 32) अणु
			अचिन्हित पूर्णांक irq;

			irq = irq_find_mapping(gc->irq.करोमुख्य, base + gpio);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक mrfld_irq_init_hw(काष्ठा gpio_chip *chip)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक base;

	क्रम (base = 0; base < priv->chip.ngpio; base += 32) अणु
		/* Clear the rising-edge detect रेजिस्टर */
		reg = gpio_reg(&priv->chip, base, GRER);
		ग_लिखोl(0, reg);
		/* Clear the falling-edge detect रेजिस्टर */
		reg = gpio_reg(&priv->chip, base, GFER);
		ग_लिखोl(0, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *mrfld_gpio_get_pinctrl_dev_name(काष्ठा mrfld_gpio *priv)
अणु
	काष्ठा acpi_device *adev;
	स्थिर अक्षर *name;

	adev = acpi_dev_get_first_match_dev("INTC1002", शून्य, -1);
	अगर (adev) अणु
		name = devm_kstrdup(priv->dev, acpi_dev_name(adev), GFP_KERNEL);
		acpi_dev_put(adev);
	पूर्ण अन्यथा अणु
		name = "pinctrl-merrifield";
	पूर्ण

	वापस name;
पूर्ण

अटल पूर्णांक mrfld_gpio_add_pin_ranges(काष्ठा gpio_chip *chip)
अणु
	काष्ठा mrfld_gpio *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा mrfld_gpio_pinrange *range;
	स्थिर अक्षर *pinctrl_dev_name;
	अचिन्हित पूर्णांक i;
	पूर्णांक retval;

	pinctrl_dev_name = mrfld_gpio_get_pinctrl_dev_name(priv);
	क्रम (i = 0; i < ARRAY_SIZE(mrfld_gpio_ranges); i++) अणु
		range = &mrfld_gpio_ranges[i];
		retval = gpiochip_add_pin_range(&priv->chip, pinctrl_dev_name,
						range->gpio_base,
						range->pin_base,
						range->npins);
		अगर (retval) अणु
			dev_err(priv->dev, "failed to add GPIO pin range\n");
			वापस retval;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_gpio_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा gpio_irq_chip *girq;
	काष्ठा mrfld_gpio *priv;
	u32 gpio_base, irq_base;
	व्योम __iomem *base;
	पूर्णांक retval;

	retval = pcim_enable_device(pdev);
	अगर (retval)
		वापस retval;

	retval = pcim_iomap_regions(pdev, BIT(1) | BIT(0), pci_name(pdev));
	अगर (retval) अणु
		dev_err(&pdev->dev, "I/O memory mapping error\n");
		वापस retval;
	पूर्ण

	base = pcim_iomap_table(pdev)[1];

	irq_base = पढ़ोl(base + 0 * माप(u32));
	gpio_base = पढ़ोl(base + 1 * माप(u32));

	/* Release the IO mapping, since we alपढ़ोy get the info from BAR1 */
	pcim_iounmap_regions(pdev, BIT(1));

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->reg_base = pcim_iomap_table(pdev)[0];

	priv->chip.label = dev_name(&pdev->dev);
	priv->chip.parent = &pdev->dev;
	priv->chip.request = gpiochip_generic_request;
	priv->chip.मुक्त = gpiochip_generic_मुक्त;
	priv->chip.direction_input = mrfld_gpio_direction_input;
	priv->chip.direction_output = mrfld_gpio_direction_output;
	priv->chip.get = mrfld_gpio_get;
	priv->chip.set = mrfld_gpio_set;
	priv->chip.get_direction = mrfld_gpio_get_direction;
	priv->chip.set_config = mrfld_gpio_set_config;
	priv->chip.base = gpio_base;
	priv->chip.ngpio = MRFLD_NGPIO;
	priv->chip.can_sleep = false;
	priv->chip.add_pin_ranges = mrfld_gpio_add_pin_ranges;

	raw_spin_lock_init(&priv->lock);

	retval = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (retval < 0)
		वापस retval;

	girq = &priv->chip.irq;
	girq->chip = &mrfld_irqchip;
	girq->init_hw = mrfld_irq_init_hw;
	girq->parent_handler = mrfld_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, girq->num_parents,
				     माप(*girq->parents), GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = pci_irq_vector(pdev, 0);
	girq->first = irq_base;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;

	retval = devm_gpiochip_add_data(&pdev->dev, &priv->chip, priv);
	अगर (retval) अणु
		dev_err(&pdev->dev, "gpiochip_add error %d\n", retval);
		वापस retval;
	पूर्ण

	pci_set_drvdata(pdev, priv);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id mrfld_gpio_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x1199) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, mrfld_gpio_ids);

अटल काष्ठा pci_driver mrfld_gpio_driver = अणु
	.name		= "gpio-merrifield",
	.id_table	= mrfld_gpio_ids,
	.probe		= mrfld_gpio_probe,
पूर्ण;

module_pci_driver(mrfld_gpio_driver);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_DESCRIPTION("Intel Merrifield SoC GPIO driver");
MODULE_LICENSE("GPL v2");
