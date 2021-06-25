<शैली गुरु>
/*
 * Copyright (C) 2015-2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

क्रमागत gio_reg_index अणु
	GIO_REG_ODEN = 0,
	GIO_REG_DATA,
	GIO_REG_IOसूची,
	GIO_REG_EC,
	GIO_REG_EI,
	GIO_REG_MASK,
	GIO_REG_LEVEL,
	GIO_REG_STAT,
	NUMBER_OF_GIO_REGISTERS
पूर्ण;

#घोषणा GIO_BANK_SIZE           (NUMBER_OF_GIO_REGISTERS * माप(u32))
#घोषणा GIO_BANK_OFF(bank, off)	(((bank) * GIO_BANK_SIZE) + (off * माप(u32)))
#घोषणा GIO_ODEN(bank)          GIO_BANK_OFF(bank, GIO_REG_ODEN)
#घोषणा GIO_DATA(bank)          GIO_BANK_OFF(bank, GIO_REG_DATA)
#घोषणा GIO_IOसूची(bank)         GIO_BANK_OFF(bank, GIO_REG_IOसूची)
#घोषणा GIO_EC(bank)            GIO_BANK_OFF(bank, GIO_REG_EC)
#घोषणा GIO_EI(bank)            GIO_BANK_OFF(bank, GIO_REG_EI)
#घोषणा GIO_MASK(bank)          GIO_BANK_OFF(bank, GIO_REG_MASK)
#घोषणा GIO_LEVEL(bank)         GIO_BANK_OFF(bank, GIO_REG_LEVEL)
#घोषणा GIO_STAT(bank)          GIO_BANK_OFF(bank, GIO_REG_STAT)

काष्ठा brcmstb_gpio_bank अणु
	काष्ठा list_head node;
	पूर्णांक id;
	काष्ठा gpio_chip gc;
	काष्ठा brcmstb_gpio_priv *parent_priv;
	u32 width;
	u32 wake_active;
	u32 saved_regs[GIO_REG_STAT]; /* Don't save and restore GIO_REG_STAT */
पूर्ण;

काष्ठा brcmstb_gpio_priv अणु
	काष्ठा list_head bank_list;
	व्योम __iomem *reg_base;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा irq_chip irq_chip;
	पूर्णांक parent_irq;
	पूर्णांक gpio_base;
	पूर्णांक num_gpios;
	पूर्णांक parent_wake_irq;
पूर्ण;

#घोषणा MAX_GPIO_PER_BANK       32
#घोषणा GPIO_BANK(gpio)         ((gpio) >> 5)
/* assumes MAX_GPIO_PER_BANK is a multiple of 2 */
#घोषणा GPIO_BIT(gpio)          ((gpio) & (MAX_GPIO_PER_BANK - 1))

अटल अंतरभूत काष्ठा brcmstb_gpio_priv *
brcmstb_gpio_gc_to_priv(काष्ठा gpio_chip *gc)
अणु
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	वापस bank->parent_priv;
पूर्ण

अटल अचिन्हित दीर्घ
__brcmstb_gpio_get_active_irqs(काष्ठा brcmstb_gpio_bank *bank)
अणु
	व्योम __iomem *reg_base = bank->parent_priv->reg_base;

	वापस bank->gc.पढ़ो_reg(reg_base + GIO_STAT(bank->id)) &
	       bank->gc.पढ़ो_reg(reg_base + GIO_MASK(bank->id));
पूर्ण

अटल अचिन्हित दीर्घ
brcmstb_gpio_get_active_irqs(काष्ठा brcmstb_gpio_bank *bank)
अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bank->gc.bgpio_lock, flags);
	status = __brcmstb_gpio_get_active_irqs(bank);
	spin_unlock_irqrestore(&bank->gc.bgpio_lock, flags);

	वापस status;
पूर्ण

अटल पूर्णांक brcmstb_gpio_hwirq_to_offset(irq_hw_number_t hwirq,
					काष्ठा brcmstb_gpio_bank *bank)
अणु
	वापस hwirq - (bank->gc.base - bank->parent_priv->gpio_base);
पूर्ण

अटल व्योम brcmstb_gpio_set_imask(काष्ठा brcmstb_gpio_bank *bank,
		अचिन्हित पूर्णांक hwirq, bool enable)
अणु
	काष्ठा gpio_chip *gc = &bank->gc;
	काष्ठा brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(hwirq, bank));
	u32 imask;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	imask = gc->पढ़ो_reg(priv->reg_base + GIO_MASK(bank->id));
	अगर (enable)
		imask |= mask;
	अन्यथा
		imask &= ~mask;
	gc->ग_लिखो_reg(priv->reg_base + GIO_MASK(bank->id), imask);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल पूर्णांक brcmstb_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा brcmstb_gpio_priv *priv = brcmstb_gpio_gc_to_priv(gc);
	/* gc_offset is relative to this gpio_chip; want real offset */
	पूर्णांक hwirq = offset + (gc->base - priv->gpio_base);

	अगर (hwirq >= priv->num_gpios)
		वापस -ENXIO;
	वापस irq_create_mapping(priv->irq_करोमुख्य, hwirq);
पूर्ण

/* -------------------- IRQ chip functions -------------------- */

अटल व्योम brcmstb_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);

	brcmstb_gpio_set_imask(bank, d->hwirq, false);
पूर्ण

अटल व्योम brcmstb_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);

	brcmstb_gpio_set_imask(bank, d->hwirq, true);
पूर्ण

अटल व्योम brcmstb_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(d->hwirq, bank));

	gc->ग_लिखो_reg(priv->reg_base + GIO_STAT(bank->id), mask);
पूर्ण

अटल पूर्णांक brcmstb_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(d->hwirq, bank));
	u32 edge_insensitive, iedge_insensitive;
	u32 edge_config, iedge_config;
	u32 level, ilevel;
	अचिन्हित दीर्घ flags;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		level = mask;
		edge_config = 0;
		edge_insensitive = 0;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		level = mask;
		edge_config = mask;
		edge_insensitive = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		level = 0;
		edge_config = 0;
		edge_insensitive = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		level = 0;
		edge_config = mask;
		edge_insensitive = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		level = 0;
		edge_config = 0;  /* करोn't care, but want known value */
		edge_insensitive = mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&bank->gc.bgpio_lock, flags);

	iedge_config = bank->gc.पढ़ो_reg(priv->reg_base +
			GIO_EC(bank->id)) & ~mask;
	iedge_insensitive = bank->gc.पढ़ो_reg(priv->reg_base +
			GIO_EI(bank->id)) & ~mask;
	ilevel = bank->gc.पढ़ो_reg(priv->reg_base +
			GIO_LEVEL(bank->id)) & ~mask;

	bank->gc.ग_लिखो_reg(priv->reg_base + GIO_EC(bank->id),
			iedge_config | edge_config);
	bank->gc.ग_लिखो_reg(priv->reg_base + GIO_EI(bank->id),
			iedge_insensitive | edge_insensitive);
	bank->gc.ग_लिखो_reg(priv->reg_base + GIO_LEVEL(bank->id),
			ilevel | level);

	spin_unlock_irqrestore(&bank->gc.bgpio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_gpio_priv_set_wake(काष्ठा brcmstb_gpio_priv *priv,
		अचिन्हित पूर्णांक enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable)
		ret = enable_irq_wake(priv->parent_wake_irq);
	अन्यथा
		ret = disable_irq_wake(priv->parent_wake_irq);
	अगर (ret)
		dev_err(&priv->pdev->dev, "failed to %s wake-up interrupt\n",
				enable ? "enable" : "disable");
	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(d->hwirq, bank));

	/*
	 * Do not करो anything specअगरic क्रम now, suspend/resume callbacks will
	 * configure the पूर्णांकerrupt mask appropriately
	 */
	अगर (enable)
		bank->wake_active |= mask;
	अन्यथा
		bank->wake_active &= ~mask;

	वापस brcmstb_gpio_priv_set_wake(priv, enable);
पूर्ण

अटल irqवापस_t brcmstb_gpio_wake_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmstb_gpio_priv *priv = data;

	अगर (!priv || irq != priv->parent_wake_irq)
		वापस IRQ_NONE;

	/* Nothing to करो */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम brcmstb_gpio_irq_bank_handler(काष्ठा brcmstb_gpio_bank *bank)
अणु
	काष्ठा brcmstb_gpio_priv *priv = bank->parent_priv;
	काष्ठा irq_करोमुख्य *करोमुख्य = priv->irq_करोमुख्य;
	पूर्णांक hwbase = bank->gc.base - priv->gpio_base;
	अचिन्हित दीर्घ status;

	जबतक ((status = brcmstb_gpio_get_active_irqs(bank))) अणु
		अचिन्हित पूर्णांक irq, offset;

		क्रम_each_set_bit(offset, &status, 32) अणु
			अगर (offset >= bank->width)
				dev_warn(&priv->pdev->dev,
					 "IRQ for invalid GPIO (bank=%d, offset=%d)\n",
					 bank->id, offset);
			irq = irq_linear_revmap(करोमुख्य, hwbase + offset);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण
पूर्ण

/* Each UPG GIO block has one IRQ क्रम all banks */
अटल व्योम brcmstb_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा brcmstb_gpio_priv *priv = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा brcmstb_gpio_bank *bank;

	/* Interrupts weren't properly cleared during probe */
	BUG_ON(!priv || !chip);

	chained_irq_enter(chip, desc);
	list_क्रम_each_entry(bank, &priv->bank_list, node)
		brcmstb_gpio_irq_bank_handler(bank);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल काष्ठा brcmstb_gpio_bank *brcmstb_gpio_hwirq_to_bank(
		काष्ठा brcmstb_gpio_priv *priv, irq_hw_number_t hwirq)
अणु
	काष्ठा brcmstb_gpio_bank *bank;
	पूर्णांक i = 0;

	/* banks are in descending order */
	list_क्रम_each_entry_reverse(bank, &priv->bank_list, node) अणु
		i += bank->gc.ngpio;
		अगर (hwirq < i)
			वापस bank;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * This lock class tells lockdep that GPIO irqs are in a dअगरferent
 * category than their parents, so it won't report false recursion.
 */
अटल काष्ठा lock_class_key brcmstb_gpio_irq_lock_class;
अटल काष्ठा lock_class_key brcmstb_gpio_irq_request_class;


अटल पूर्णांक brcmstb_gpio_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		irq_hw_number_t hwirq)
अणु
	काष्ठा brcmstb_gpio_priv *priv = d->host_data;
	काष्ठा brcmstb_gpio_bank *bank =
		brcmstb_gpio_hwirq_to_bank(priv, hwirq);
	काष्ठा platक्रमm_device *pdev = priv->pdev;
	पूर्णांक ret;

	अगर (!bank)
		वापस -EINVAL;

	dev_dbg(&pdev->dev, "Mapping irq %d for gpio line %d (bank %d)\n",
		irq, (पूर्णांक)hwirq, bank->id);
	ret = irq_set_chip_data(irq, &bank->gc);
	अगर (ret < 0)
		वापस ret;
	irq_set_lockdep_class(irq, &brcmstb_gpio_irq_lock_class,
			      &brcmstb_gpio_irq_request_class);
	irq_set_chip_and_handler(irq, &priv->irq_chip, handle_level_irq);
	irq_set_noprobe(irq);
	वापस 0;
पूर्ण

अटल व्योम brcmstb_gpio_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops brcmstb_gpio_irq_करोमुख्य_ops = अणु
	.map = brcmstb_gpio_irq_map,
	.unmap = brcmstb_gpio_irq_unmap,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

/* Make sure that the number of banks matches up between properties */
अटल पूर्णांक brcmstb_gpio_sanity_check_banks(काष्ठा device *dev,
		काष्ठा device_node *np, काष्ठा resource *res)
अणु
	पूर्णांक res_num_banks = resource_size(res) / GIO_BANK_SIZE;
	पूर्णांक num_banks =
		of_property_count_u32_elems(np, "brcm,gpio-bank-widths");

	अगर (res_num_banks != num_banks) अणु
		dev_err(dev, "Mismatch in banks: res had %d, bank-widths had %d\n",
				res_num_banks, num_banks);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक brcmstb_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_gpio_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा brcmstb_gpio_bank *bank;
	पूर्णांक offset, ret = 0, virq;

	अगर (!priv) अणु
		dev_err(&pdev->dev, "called %s without drvdata!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (priv->parent_irq > 0)
		irq_set_chained_handler_and_data(priv->parent_irq, शून्य, शून्य);

	/* Remove all IRQ mappings and delete the करोमुख्य */
	अगर (priv->irq_करोमुख्य) अणु
		क्रम (offset = 0; offset < priv->num_gpios; offset++) अणु
			virq = irq_find_mapping(priv->irq_करोमुख्य, offset);
			irq_dispose_mapping(virq);
		पूर्ण
		irq_करोमुख्य_हटाओ(priv->irq_करोमुख्य);
	पूर्ण

	/*
	 * You can lose वापस values below, but we report all errors, and it's
	 * more important to actually perक्रमm all of the steps.
	 */
	list_क्रम_each_entry(bank, &priv->bank_list, node)
		gpiochip_हटाओ(&bank->gc);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_gpio_of_xlate(काष्ठा gpio_chip *gc,
		स्थिर काष्ठा of_phandle_args *gpiospec, u32 *flags)
अणु
	काष्ठा brcmstb_gpio_priv *priv = brcmstb_gpio_gc_to_priv(gc);
	काष्ठा brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	पूर्णांक offset;

	अगर (gc->of_gpio_n_cells != 2) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		वापस -EINVAL;

	offset = gpiospec->args[0] - (gc->base - priv->gpio_base);
	अगर (offset >= gc->ngpio || offset < 0)
		वापस -EINVAL;

	अगर (unlikely(offset >= bank->width)) अणु
		dev_warn_ratelimited(&priv->pdev->dev,
			"Received request for invalid GPIO offset %d\n",
			gpiospec->args[0]);
	पूर्ण

	अगर (flags)
		*flags = gpiospec->args[1];

	वापस offset;
पूर्ण

/* priv->parent_irq and priv->num_gpios must be set beक्रमe calling */
अटल पूर्णांक brcmstb_gpio_irq_setup(काष्ठा platक्रमm_device *pdev,
		काष्ठा brcmstb_gpio_priv *priv)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err;

	priv->irq_करोमुख्य =
		irq_करोमुख्य_add_linear(np, priv->num_gpios,
				      &brcmstb_gpio_irq_करोमुख्य_ops,
				      priv);
	अगर (!priv->irq_करोमुख्य) अणु
		dev_err(dev, "Couldn't allocate IRQ domain\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "wakeup-source")) अणु
		priv->parent_wake_irq = platक्रमm_get_irq(pdev, 1);
		अगर (priv->parent_wake_irq < 0) अणु
			priv->parent_wake_irq = 0;
			dev_warn(dev,
				"Couldn't get wake IRQ - GPIOs will not be able to wake from sleep");
		पूर्ण अन्यथा अणु
			/*
			 * Set wakeup capability so we can process boot-समय
			 * "wakeups" (e.g., from S5 cold boot)
			 */
			device_set_wakeup_capable(dev, true);
			device_wakeup_enable(dev);
			err = devm_request_irq(dev, priv->parent_wake_irq,
					       brcmstb_gpio_wake_irq_handler,
					       IRQF_SHARED,
					       "brcmstb-gpio-wake", priv);

			अगर (err < 0) अणु
				dev_err(dev, "Couldn't request wake IRQ");
				जाओ out_मुक्त_करोमुख्य;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->irq_chip.name = dev_name(dev);
	priv->irq_chip.irq_disable = brcmstb_gpio_irq_mask;
	priv->irq_chip.irq_mask = brcmstb_gpio_irq_mask;
	priv->irq_chip.irq_unmask = brcmstb_gpio_irq_unmask;
	priv->irq_chip.irq_ack = brcmstb_gpio_irq_ack;
	priv->irq_chip.irq_set_type = brcmstb_gpio_irq_set_type;

	अगर (priv->parent_wake_irq)
		priv->irq_chip.irq_set_wake = brcmstb_gpio_irq_set_wake;

	irq_set_chained_handler_and_data(priv->parent_irq,
					 brcmstb_gpio_irq_handler, priv);
	irq_set_status_flags(priv->parent_irq, IRQ_DISABLE_UNLAZY);

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(priv->irq_करोमुख्य);

	वापस err;
पूर्ण

अटल व्योम brcmstb_gpio_bank_save(काष्ठा brcmstb_gpio_priv *priv,
				   काष्ठा brcmstb_gpio_bank *bank)
अणु
	काष्ठा gpio_chip *gc = &bank->gc;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < GIO_REG_STAT; i++)
		bank->saved_regs[i] = gc->पढ़ो_reg(priv->reg_base +
						   GIO_BANK_OFF(bank->id, i));
पूर्ण

अटल व्योम brcmstb_gpio_quiesce(काष्ठा device *dev, bool save)
अणु
	काष्ठा brcmstb_gpio_priv *priv = dev_get_drvdata(dev);
	काष्ठा brcmstb_gpio_bank *bank;
	काष्ठा gpio_chip *gc;
	u32 imask;

	/* disable non-wake पूर्णांकerrupt */
	अगर (priv->parent_irq >= 0)
		disable_irq(priv->parent_irq);

	list_क्रम_each_entry(bank, &priv->bank_list, node) अणु
		gc = &bank->gc;

		अगर (save)
			brcmstb_gpio_bank_save(priv, bank);

		/* Unmask GPIOs which have been flagged as wake-up sources */
		अगर (priv->parent_wake_irq)
			imask = bank->wake_active;
		अन्यथा
			imask = 0;
		gc->ग_लिखो_reg(priv->reg_base + GIO_MASK(bank->id),
			       imask);
	पूर्ण
पूर्ण

अटल व्योम brcmstb_gpio_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/* Enable GPIO क्रम S5 cold boot */
	brcmstb_gpio_quiesce(&pdev->dev, false);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम brcmstb_gpio_bank_restore(काष्ठा brcmstb_gpio_priv *priv,
				      काष्ठा brcmstb_gpio_bank *bank)
अणु
	काष्ठा gpio_chip *gc = &bank->gc;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < GIO_REG_STAT; i++)
		gc->ग_लिखो_reg(priv->reg_base + GIO_BANK_OFF(bank->id, i),
			      bank->saved_regs[i]);
पूर्ण

अटल पूर्णांक brcmstb_gpio_suspend(काष्ठा device *dev)
अणु
	brcmstb_gpio_quiesce(dev, true);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_gpio_priv *priv = dev_get_drvdata(dev);
	काष्ठा brcmstb_gpio_bank *bank;
	bool need_wakeup_event = false;

	list_क्रम_each_entry(bank, &priv->bank_list, node) अणु
		need_wakeup_event |= !!__brcmstb_gpio_get_active_irqs(bank);
		brcmstb_gpio_bank_restore(priv, bank);
	पूर्ण

	अगर (priv->parent_wake_irq && need_wakeup_event)
		pm_wakeup_event(dev, 0);

	/* enable non-wake पूर्णांकerrupt */
	अगर (priv->parent_irq >= 0)
		enable_irq(priv->parent_irq);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा brcmstb_gpio_suspend	शून्य
#घोषणा brcmstb_gpio_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops brcmstb_gpio_pm_ops = अणु
	.suspend_noirq	= brcmstb_gpio_suspend,
	.resume_noirq = brcmstb_gpio_resume,
पूर्ण;

अटल व्योम brcmstb_gpio_set_names(काष्ठा device *dev,
				   काष्ठा brcmstb_gpio_bank *bank)
अणु
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर **names;
	पूर्णांक nstrings, base;
	अचिन्हित पूर्णांक i;

	base = bank->id * MAX_GPIO_PER_BANK;

	nstrings = of_property_count_strings(np, "gpio-line-names");
	अगर (nstrings <= base)
		/* Line names not present */
		वापस;

	names = devm_kसुस्मृति(dev, MAX_GPIO_PER_BANK, माप(*names),
			     GFP_KERNEL);
	अगर (!names)
		वापस;

	/*
	 * Make sure to not index beyond the end of the number of descriptors
	 * of the GPIO device.
	 */
	क्रम (i = 0; i < bank->width; i++) अणु
		स्थिर अक्षर *name;
		पूर्णांक ret;

		ret = of_property_पढ़ो_string_index(np, "gpio-line-names",
						    base + i, &name);
		अगर (ret) अणु
			अगर (ret != -ENODATA)
				dev_err(dev, "unable to name line %d: %d\n",
					base + i, ret);
			अवरोध;
		पूर्ण
		अगर (*name)
			names[i] = name;
	पूर्ण

	bank->gc.names = names;
पूर्ण

अटल पूर्णांक brcmstb_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	व्योम __iomem *reg_base;
	काष्ठा brcmstb_gpio_priv *priv;
	काष्ठा resource *res;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u32 bank_width;
	पूर्णांक num_banks = 0;
	पूर्णांक err;
	अटल पूर्णांक gpio_base;
	अचिन्हित दीर्घ flags = 0;
	bool need_wakeup_event = false;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);
	INIT_LIST_HEAD(&priv->bank_list);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	priv->gpio_base = gpio_base;
	priv->reg_base = reg_base;
	priv->pdev = pdev;

	अगर (of_property_पढ़ो_bool(np, "interrupt-controller")) अणु
		priv->parent_irq = platक्रमm_get_irq(pdev, 0);
		अगर (priv->parent_irq <= 0)
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		priv->parent_irq = -ENOENT;
	पूर्ण

	अगर (brcmstb_gpio_sanity_check_banks(dev, np, res))
		वापस -EINVAL;

	/*
	 * MIPS endianness is configured by boot strap, which also reverses all
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Other architectures (e.g., ARM) either करो not support big endian, or
	 * अन्यथा leave I/O in little endian mode.
	 */
#अगर defined(CONFIG_MIPS) && defined(__BIG_ENDIAN)
	flags = BGPIOF_BIG_ENDIAN_BYTE_ORDER;
#पूर्ण_अगर

	of_property_क्रम_each_u32(np, "brcm,gpio-bank-widths", prop, p,
			bank_width) अणु
		काष्ठा brcmstb_gpio_bank *bank;
		काष्ठा gpio_chip *gc;

		/*
		 * If bank_width is 0, then there is an empty bank in the
		 * रेजिस्टर block. Special handling क्रम this हाल.
		 */
		अगर (bank_width == 0) अणु
			dev_dbg(dev, "Width 0 found: Empty bank @ %d\n",
				num_banks);
			num_banks++;
			gpio_base += MAX_GPIO_PER_BANK;
			जारी;
		पूर्ण

		bank = devm_kzalloc(dev, माप(*bank), GFP_KERNEL);
		अगर (!bank) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		bank->parent_priv = priv;
		bank->id = num_banks;
		अगर (bank_width <= 0 || bank_width > MAX_GPIO_PER_BANK) अणु
			dev_err(dev, "Invalid bank width %d\n", bank_width);
			err = -EINVAL;
			जाओ fail;
		पूर्ण अन्यथा अणु
			bank->width = bank_width;
		पूर्ण

		/*
		 * Regs are 4 bytes wide, have data reg, no set/clear regs,
		 * and direction bits have 0 = output and 1 = input
		 */
		gc = &bank->gc;
		err = bgpio_init(gc, dev, 4,
				reg_base + GIO_DATA(bank->id),
				शून्य, शून्य, शून्य,
				reg_base + GIO_IOसूची(bank->id), flags);
		अगर (err) अणु
			dev_err(dev, "bgpio_init() failed\n");
			जाओ fail;
		पूर्ण

		gc->of_node = np;
		gc->owner = THIS_MODULE;
		gc->label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOF", dev->of_node);
		अगर (!gc->label) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण
		gc->base = gpio_base;
		gc->of_gpio_n_cells = 2;
		gc->of_xlate = brcmstb_gpio_of_xlate;
		/* not all ngpio lines are valid, will use bank width later */
		gc->ngpio = MAX_GPIO_PER_BANK;
		अगर (priv->parent_irq > 0)
			gc->to_irq = brcmstb_gpio_to_irq;

		/*
		 * Mask all पूर्णांकerrupts by शेष, since wakeup पूर्णांकerrupts may
		 * be retained from S5 cold boot
		 */
		need_wakeup_event |= !!__brcmstb_gpio_get_active_irqs(bank);
		gc->ग_लिखो_reg(reg_base + GIO_MASK(bank->id), 0);

		brcmstb_gpio_set_names(dev, bank);
		err = gpiochip_add_data(gc, bank);
		अगर (err) अणु
			dev_err(dev, "Could not add gpiochip for bank %d\n",
					bank->id);
			जाओ fail;
		पूर्ण
		gpio_base += gc->ngpio;

		dev_dbg(dev, "bank=%d, base=%d, ngpio=%d, width=%d\n", bank->id,
			gc->base, gc->ngpio, bank->width);

		/* Everything looks good, so add bank to list */
		list_add(&bank->node, &priv->bank_list);

		num_banks++;
	पूर्ण

	priv->num_gpios = gpio_base - priv->gpio_base;
	अगर (priv->parent_irq > 0) अणु
		err = brcmstb_gpio_irq_setup(pdev, priv);
		अगर (err)
			जाओ fail;
	पूर्ण

	अगर (priv->parent_wake_irq && need_wakeup_event)
		pm_wakeup_event(dev, 0);

	वापस 0;

fail:
	(व्योम) brcmstb_gpio_हटाओ(pdev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id brcmstb_gpio_of_match[] = अणु
	अणु .compatible = "brcm,brcmstb-gpio" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, brcmstb_gpio_of_match);

अटल काष्ठा platक्रमm_driver brcmstb_gpio_driver = अणु
	.driver = अणु
		.name = "brcmstb-gpio",
		.of_match_table = brcmstb_gpio_of_match,
		.pm = &brcmstb_gpio_pm_ops,
	पूर्ण,
	.probe = brcmstb_gpio_probe,
	.हटाओ = brcmstb_gpio_हटाओ,
	.shutकरोwn = brcmstb_gpio_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(brcmstb_gpio_driver);

MODULE_AUTHOR("Gregory Fong");
MODULE_DESCRIPTION("Driver for Broadcom BRCMSTB SoC UPG GPIO");
MODULE_LICENSE("GPL v2");
