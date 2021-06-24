<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics ConneXt (STA2X11) GPIO driver
 *
 * Copyright 2012 ST Microelectronics (Alessandro Rubini)
 * Based on gpio-ml-ioh.c, Copyright 2010 OKI Semiconductors Ltd.
 * Also based on previous sta2x11 work, Copyright 2011 Wind River Systems, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/sta2x11-mfd.h>

काष्ठा gsta_regs अणु
	u32 dat;		/* 0x00 */
	u32 dats;
	u32 datc;
	u32 pdis;
	u32 dir;		/* 0x10 */
	u32 dirs;
	u32 dirc;
	u32 unused_1c;
	u32 afsela;		/* 0x20 */
	u32 unused_24[7];
	u32 rimsc;		/* 0x40 */
	u32 fimsc;
	u32 is;
	u32 ic;
पूर्ण;

काष्ठा gsta_gpio अणु
	spinlock_t			lock;
	काष्ठा device			*dev;
	व्योम __iomem			*reg_base;
	काष्ठा gsta_regs __iomem	*regs[GSTA_NR_BLOCKS];
	काष्ठा gpio_chip		gpio;
	पूर्णांक				irq_base;
	/* FIXME: save the whole config here (AF, ...) */
	अचिन्हित			irq_type[GSTA_NR_GPIO];
पूर्ण;

/*
 * gpio methods
 */

अटल व्योम gsta_gpio_set(काष्ठा gpio_chip *gpio, अचिन्हित nr, पूर्णांक val)
अणु
	काष्ठा gsta_gpio *chip = gpiochip_get_data(gpio);
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);

	अगर (val)
		ग_लिखोl(bit, &regs->dats);
	अन्यथा
		ग_लिखोl(bit, &regs->datc);
पूर्ण

अटल पूर्णांक gsta_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा gsta_gpio *chip = gpiochip_get_data(gpio);
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);

	वापस !!(पढ़ोl(&regs->dat) & bit);
पूर्ण

अटल पूर्णांक gsta_gpio_direction_output(काष्ठा gpio_chip *gpio, अचिन्हित nr,
				      पूर्णांक val)
अणु
	काष्ठा gsta_gpio *chip = gpiochip_get_data(gpio);
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);

	ग_लिखोl(bit, &regs->dirs);
	/* Data रेजिस्टर after direction, otherwise pullup/करोwn is selected */
	अगर (val)
		ग_लिखोl(bit, &regs->dats);
	अन्यथा
		ग_लिखोl(bit, &regs->datc);
	वापस 0;
पूर्ण

अटल पूर्णांक gsta_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा gsta_gpio *chip = gpiochip_get_data(gpio);
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);

	ग_लिखोl(bit, &regs->dirc);
	वापस 0;
पूर्ण

अटल पूर्णांक gsta_gpio_to_irq(काष्ठा gpio_chip *gpio, अचिन्हित offset)
अणु
	काष्ठा gsta_gpio *chip = gpiochip_get_data(gpio);
	वापस chip->irq_base + offset;
पूर्ण

अटल व्योम gsta_gpio_setup(काष्ठा gsta_gpio *chip) /* called from probe */
अणु
	काष्ठा gpio_chip *gpio = &chip->gpio;

	/*
	 * ARCH_NR_GPIOS is currently 256 and dynamic allocation starts
	 * from the end. However, क्रम compatibility, we need the first
	 * ConneXt device to start from gpio 0: it's the मुख्य chipset
	 * on most boards so करोcuments and drivers assume gpio0..gpio127
	 */
	अटल पूर्णांक gpio_base;

	gpio->label = dev_name(chip->dev);
	gpio->owner = THIS_MODULE;
	gpio->direction_input = gsta_gpio_direction_input;
	gpio->get = gsta_gpio_get;
	gpio->direction_output = gsta_gpio_direction_output;
	gpio->set = gsta_gpio_set;
	gpio->dbg_show = शून्य;
	gpio->base = gpio_base;
	gpio->ngpio = GSTA_NR_GPIO;
	gpio->can_sleep = false;
	gpio->to_irq = gsta_gpio_to_irq;

	/*
	 * After the first device, turn to dynamic gpio numbers.
	 * For example, with ARCH_NR_GPIOS = 256 we can fit two cards
	 */
	अगर (!gpio_base)
		gpio_base = -1;
पूर्ण

/*
 * Special method: alternate functions and pullup/pullकरोwn. This is only
 * invoked on startup to configure gpio's according to platक्रमm data.
 * FIXME : this functionality shall be managed (and exported to other drivers)
 * via the pin control subप्रणाली.
 */
अटल व्योम gsta_set_config(काष्ठा gsta_gpio *chip, पूर्णांक nr, अचिन्हित cfg)
अणु
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	अचिन्हित दीर्घ flags;
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);
	u32 val;
	पूर्णांक err = 0;

	pr_info("%s: %p %i %i\n", __func__, chip, nr, cfg);

	अगर (cfg == PINMUX_TYPE_NONE)
		वापस;

	/* Alternate function or not? */
	spin_lock_irqsave(&chip->lock, flags);
	val = पढ़ोl(&regs->afsela);
	अगर (cfg == PINMUX_TYPE_FUNCTION)
		val |= bit;
	अन्यथा
		val &= ~bit;
	ग_लिखोl(val | bit, &regs->afsela);
	अगर (cfg == PINMUX_TYPE_FUNCTION) अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		वापस;
	पूर्ण

	/* not alternate function: set details */
	चयन (cfg) अणु
	हाल PINMUX_TYPE_OUTPUT_LOW:
		ग_लिखोl(bit, &regs->dirs);
		ग_लिखोl(bit, &regs->datc);
		अवरोध;
	हाल PINMUX_TYPE_OUTPUT_HIGH:
		ग_लिखोl(bit, &regs->dirs);
		ग_लिखोl(bit, &regs->dats);
		अवरोध;
	हाल PINMUX_TYPE_INPUT:
		ग_लिखोl(bit, &regs->dirc);
		val = पढ़ोl(&regs->pdis) | bit;
		ग_लिखोl(val, &regs->pdis);
		अवरोध;
	हाल PINMUX_TYPE_INPUT_PULLUP:
		ग_लिखोl(bit, &regs->dirc);
		val = पढ़ोl(&regs->pdis) & ~bit;
		ग_लिखोl(val, &regs->pdis);
		ग_लिखोl(bit, &regs->dats);
		अवरोध;
	हाल PINMUX_TYPE_INPUT_PULLDOWN:
		ग_लिखोl(bit, &regs->dirc);
		val = पढ़ोl(&regs->pdis) & ~bit;
		ग_लिखोl(val, &regs->pdis);
		ग_लिखोl(bit, &regs->datc);
		अवरोध;
	शेष:
		err = 1;
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
	अगर (err)
		pr_err("%s: chip %p, pin %i, cfg %i is invalid\n",
		       __func__, chip, nr, cfg);
पूर्ण

/*
 * Irq methods
 */

अटल व्योम gsta_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा gsta_gpio *chip = gc->निजी;
	पूर्णांक nr = data->irq - chip->irq_base;
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	अगर (chip->irq_type[nr] & IRQ_TYPE_EDGE_RISING) अणु
		val = पढ़ोl(&regs->rimsc) & ~bit;
		ग_लिखोl(val, &regs->rimsc);
	पूर्ण
	अगर (chip->irq_type[nr] & IRQ_TYPE_EDGE_FALLING) अणु
		val = पढ़ोl(&regs->fimsc) & ~bit;
		ग_लिखोl(val, &regs->fimsc);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस;
पूर्ण

अटल व्योम gsta_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा gsta_gpio *chip = gc->निजी;
	पूर्णांक nr = data->irq - chip->irq_base;
	काष्ठा gsta_regs __iomem *regs = chip->regs[nr / GSTA_GPIO_PER_BLOCK];
	u32 bit = BIT(nr % GSTA_GPIO_PER_BLOCK);
	u32 val;
	पूर्णांक type;
	अचिन्हित दीर्घ flags;

	type = chip->irq_type[nr];

	spin_lock_irqsave(&chip->lock, flags);
	val = पढ़ोl(&regs->rimsc);
	अगर (type & IRQ_TYPE_EDGE_RISING)
		ग_लिखोl(val | bit, &regs->rimsc);
	अन्यथा
		ग_लिखोl(val & ~bit, &regs->rimsc);
	val = पढ़ोl(&regs->rimsc);
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		ग_लिखोl(val | bit, &regs->fimsc);
	अन्यथा
		ग_लिखोl(val & ~bit, &regs->fimsc);
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस;
पूर्ण

अटल पूर्णांक gsta_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा gsta_gpio *chip = gc->निजी;
	पूर्णांक nr = d->irq - chip->irq_base;

	/* We only support edge पूर्णांकerrupts */
	अगर (!(type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))) अणु
		pr_debug("%s: unsupported type 0x%x\n", __func__, type);
		वापस -EINVAL;
	पूर्ण

	chip->irq_type[nr] = type; /* used क्रम enable/disable */

	gsta_irq_enable(d);
	वापस 0;
पूर्ण

अटल irqवापस_t gsta_gpio_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gsta_gpio *chip = dev_id;
	काष्ठा gsta_regs __iomem *regs;
	u32 is;
	पूर्णांक i, nr, base;
	irqवापस_t ret = IRQ_NONE;

	क्रम (i = 0; i < GSTA_NR_BLOCKS; i++) अणु
		regs = chip->regs[i];
		base = chip->irq_base + i * GSTA_GPIO_PER_BLOCK;
		जबतक ((is = पढ़ोl(&regs->is))) अणु
			nr = __ffs(is);
			irq = base + nr;
			generic_handle_irq(irq);
			ग_लिखोl(1 << nr, &regs->ic);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gsta_alloc_irq_chip(काष्ठा gsta_gpio *chip)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, KBUILD_MODNAME, 1,
					 chip->irq_base,
					 chip->reg_base, handle_simple_irq);
	अगर (!gc)
		वापस -ENOMEM;

	gc->निजी = chip;
	ct = gc->chip_types;

	ct->chip.irq_set_type = gsta_irq_type;
	ct->chip.irq_disable = gsta_irq_disable;
	ct->chip.irq_enable = gsta_irq_enable;

	/* FIXME: this makes at most 32 पूर्णांकerrupts. Request 0 by now */
	rv = devm_irq_setup_generic_chip(chip->dev, gc,
					 0 /* IRQ_MSK(GSTA_GPIO_PER_BLOCK) */,
					 0, IRQ_NOREQUEST | IRQ_NOPROBE, 0);
	अगर (rv)
		वापस rv;

	/* Set up all all 128 पूर्णांकerrupts: code from setup_generic_chip */
	अणु
		काष्ठा irq_chip_type *ct = gc->chip_types;
		पूर्णांक i, j;
		क्रम (j = 0; j < GSTA_NR_GPIO; j++) अणु
			i = chip->irq_base + j;
			irq_set_chip_and_handler(i, &ct->chip, ct->handler);
			irq_set_chip_data(i, gc);
			irq_clear_status_flags(i, IRQ_NOREQUEST | IRQ_NOPROBE);
		पूर्ण
		gc->irq_cnt = i - gc->irq_base;
	पूर्ण

	वापस 0;
पूर्ण

/* The platक्रमm device used here is instantiated by the MFD device */
अटल पूर्णांक gsta_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i, err;
	काष्ठा pci_dev *pdev;
	काष्ठा sta2x11_gpio_pdata *gpio_pdata;
	काष्ठा gsta_gpio *chip;

	pdev = *(काष्ठा pci_dev **)dev_get_platdata(&dev->dev);
	gpio_pdata = dev_get_platdata(&pdev->dev);

	अगर (gpio_pdata == शून्य)
		dev_err(&dev->dev, "no gpio config\n");
	pr_debug("gpio config: %p\n", gpio_pdata);

	chip = devm_kzalloc(&dev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;
	chip->dev = &dev->dev;
	chip->reg_base = devm_platक्रमm_ioremap_resource(dev, 0);
	अगर (IS_ERR(chip->reg_base))
		वापस PTR_ERR(chip->reg_base);

	क्रम (i = 0; i < GSTA_NR_BLOCKS; i++) अणु
		chip->regs[i] = chip->reg_base + i * 4096;
		/* disable all irqs */
		ग_लिखोl(0, &chip->regs[i]->rimsc);
		ग_लिखोl(0, &chip->regs[i]->fimsc);
		ग_लिखोl(~0, &chip->regs[i]->ic);
	पूर्ण
	spin_lock_init(&chip->lock);
	gsta_gpio_setup(chip);
	अगर (gpio_pdata)
		क्रम (i = 0; i < GSTA_NR_GPIO; i++)
			gsta_set_config(chip, i, gpio_pdata->pinconfig[i]);

	/* 384 was used in previous code: be compatible क्रम other drivers */
	err = devm_irq_alloc_descs(&dev->dev, -1, 384,
				   GSTA_NR_GPIO, NUMA_NO_NODE);
	अगर (err < 0) अणु
		dev_warn(&dev->dev, "sta2x11 gpio: Can't get irq base (%i)\n",
			 -err);
		वापस err;
	पूर्ण
	chip->irq_base = err;

	err = gsta_alloc_irq_chip(chip);
	अगर (err)
		वापस err;

	err = devm_request_irq(&dev->dev, pdev->irq, gsta_gpio_handler,
			       IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (err < 0) अणु
		dev_err(&dev->dev, "sta2x11 gpio: Can't request irq (%i)\n",
			-err);
		वापस err;
	पूर्ण

	err = devm_gpiochip_add_data(&dev->dev, &chip->gpio, chip);
	अगर (err < 0) अणु
		dev_err(&dev->dev, "sta2x11 gpio: Can't register (%i)\n",
			-err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(dev, chip);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sta2x11_gpio_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "sta2x11-gpio",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = gsta_probe,
पूर्ण;
builtin_platक्रमm_driver(sta2x11_gpio_platक्रमm_driver);
