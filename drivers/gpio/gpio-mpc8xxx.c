<शैली गुरु>
/*
 * GPIOs on MPC512x/8349/8572/8610/QorIQ and compatible
 *
 * Copyright (C) 2008 Peter Korsgaard <jacmet@sunsite.dk>
 * Copyright (C) 2016 Freescale Semiconductor Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/property.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा MPC8XXX_GPIO_PINS	32

#घोषणा GPIO_सूची		0x00
#घोषणा GPIO_ODR		0x04
#घोषणा GPIO_DAT		0x08
#घोषणा GPIO_IER		0x0c
#घोषणा GPIO_IMR		0x10
#घोषणा GPIO_ICR		0x14
#घोषणा GPIO_ICR2		0x18
#घोषणा GPIO_IBE		0x18

काष्ठा mpc8xxx_gpio_chip अणु
	काष्ठा gpio_chip	gc;
	व्योम __iomem *regs;
	raw_spinlock_t lock;

	पूर्णांक (*direction_output)(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक value);

	काष्ठा irq_करोमुख्य *irq;
	अचिन्हित पूर्णांक irqn;
पूर्ण;

/*
 * This hardware has a big endian bit assignment such that GPIO line 0 is
 * connected to bit 31, line 1 to bit 30 ... line 31 to bit 0.
 * This अंतरभूत helper give the right biपंचांगask क्रम a certain line.
 */
अटल अंतरभूत u32 mpc_pin2mask(अचिन्हित पूर्णांक offset)
अणु
	वापस BIT(31 - offset);
पूर्ण

/* Workaround GPIO 1 errata on MPC8572/MPC8536. The status of GPIOs
 * defined as output cannot be determined by पढ़ोing GPDAT रेजिस्टर,
 * so we use shaकरोw data रेजिस्टर instead. The status of input pins
 * is determined by पढ़ोing GPDAT रेजिस्टर.
 */
अटल पूर्णांक mpc8572_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	u32 val;
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	u32 out_mask, out_shaकरोw;

	out_mask = gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_सूची);
	val = gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_DAT) & ~out_mask;
	out_shaकरोw = gc->bgpio_data & out_mask;

	वापस !!((val | out_shaकरोw) & mpc_pin2mask(gpio));
पूर्ण

अटल पूर्णांक mpc5121_gpio_dir_out(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	/* GPIO 28..31 are input only on MPC5121 */
	अगर (gpio >= 28)
		वापस -EINVAL;

	वापस mpc8xxx_gc->direction_output(gc, gpio, val);
पूर्ण

अटल पूर्णांक mpc5125_gpio_dir_out(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	/* GPIO 0..3 are input only on MPC5125 */
	अगर (gpio <= 3)
		वापस -EINVAL;

	वापस mpc8xxx_gc->direction_output(gc, gpio, val);
पूर्ण

अटल पूर्णांक mpc8xxx_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);

	अगर (mpc8xxx_gc->irq && offset < MPC8XXX_GPIO_PINS)
		वापस irq_create_mapping(mpc8xxx_gc->irq, offset);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल irqवापस_t mpc8xxx_gpio_irq_cascade(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = data;
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;
	अचिन्हित दीर्घ mask;
	पूर्णांक i;

	mask = gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_IER)
		& gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_IMR);
	क्रम_each_set_bit(i, &mask, 32)
		generic_handle_irq(irq_linear_revmap(mpc8xxx_gc->irq, 31 - i));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mpc8xxx_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);

	gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IMR,
		gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_IMR)
		| mpc_pin2mask(irqd_to_hwirq(d)));

	raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
पूर्ण

अटल व्योम mpc8xxx_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);

	gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IMR,
		gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_IMR)
		& ~mpc_pin2mask(irqd_to_hwirq(d)));

	raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
पूर्ण

अटल व्योम mpc8xxx_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;

	gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IER,
		      mpc_pin2mask(irqd_to_hwirq(d)));
पूर्ण

अटल पूर्णांक mpc8xxx_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;
	अचिन्हित दीर्घ flags;

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);
		gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_ICR,
			gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_ICR)
			| mpc_pin2mask(irqd_to_hwirq(d)));
		raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);
		gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_ICR,
			gc->पढ़ो_reg(mpc8xxx_gc->regs + GPIO_ICR)
			& ~mpc_pin2mask(irqd_to_hwirq(d)));
		raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpc512x_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gc = &mpc8xxx_gc->gc;
	अचिन्हित दीर्घ gpio = irqd_to_hwirq(d);
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित दीर्घ flags;

	अगर (gpio < 16) अणु
		reg = mpc8xxx_gc->regs + GPIO_ICR;
		shअगरt = (15 - gpio) * 2;
	पूर्ण अन्यथा अणु
		reg = mpc8xxx_gc->regs + GPIO_ICR2;
		shअगरt = (15 - (gpio % 16)) * 2;
	पूर्ण

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_LEVEL_LOW:
		raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);
		gc->ग_लिखो_reg(reg, (gc->पढ़ो_reg(reg) & ~(3 << shअगरt))
			| (2 << shअगरt));
		raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);
		gc->ग_लिखो_reg(reg, (gc->पढ़ो_reg(reg) & ~(3 << shअगरt))
			| (1 << shअगरt));
		raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);
		gc->ग_लिखो_reg(reg, (gc->पढ़ो_reg(reg) & ~(3 << shअगरt)));
		raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mpc8xxx_irq_chip = अणु
	.name		= "mpc8xxx-gpio",
	.irq_unmask	= mpc8xxx_irq_unmask,
	.irq_mask	= mpc8xxx_irq_mask,
	.irq_ack	= mpc8xxx_irq_ack,
	/* this might get overwritten in mpc8xxx_probe() */
	.irq_set_type	= mpc8xxx_irq_set_type,
पूर्ण;

अटल पूर्णांक mpc8xxx_gpio_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, h->host_data);
	irq_set_chip_and_handler(irq, &mpc8xxx_irq_chip, handle_edge_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mpc8xxx_gpio_irq_ops = अणु
	.map	= mpc8xxx_gpio_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

काष्ठा mpc8xxx_gpio_devtype अणु
	पूर्णांक (*gpio_dir_out)(काष्ठा gpio_chip *, अचिन्हित पूर्णांक, पूर्णांक);
	पूर्णांक (*gpio_get)(काष्ठा gpio_chip *, अचिन्हित पूर्णांक);
	पूर्णांक (*irq_set_type)(काष्ठा irq_data *, अचिन्हित पूर्णांक);
पूर्ण;

अटल स्थिर काष्ठा mpc8xxx_gpio_devtype mpc512x_gpio_devtype = अणु
	.gpio_dir_out = mpc5121_gpio_dir_out,
	.irq_set_type = mpc512x_irq_set_type,
पूर्ण;

अटल स्थिर काष्ठा mpc8xxx_gpio_devtype mpc5125_gpio_devtype = अणु
	.gpio_dir_out = mpc5125_gpio_dir_out,
	.irq_set_type = mpc512x_irq_set_type,
पूर्ण;

अटल स्थिर काष्ठा mpc8xxx_gpio_devtype mpc8572_gpio_devtype = अणु
	.gpio_get = mpc8572_gpio_get,
पूर्ण;

अटल स्थिर काष्ठा mpc8xxx_gpio_devtype mpc8xxx_gpio_devtype_शेष = अणु
	.irq_set_type = mpc8xxx_irq_set_type,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mpc8xxx_gpio_ids[] = अणु
	अणु .compatible = "fsl,mpc8349-gpio", पूर्ण,
	अणु .compatible = "fsl,mpc8572-gpio", .data = &mpc8572_gpio_devtype, पूर्ण,
	अणु .compatible = "fsl,mpc8610-gpio", पूर्ण,
	अणु .compatible = "fsl,mpc5121-gpio", .data = &mpc512x_gpio_devtype, पूर्ण,
	अणु .compatible = "fsl,mpc5125-gpio", .data = &mpc5125_gpio_devtype, पूर्ण,
	अणु .compatible = "fsl,pq3-gpio",     पूर्ण,
	अणु .compatible = "fsl,ls1028a-gpio", पूर्ण,
	अणु .compatible = "fsl,ls1088a-gpio", पूर्ण,
	अणु .compatible = "fsl,qoriq-gpio",   पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक mpc8xxx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc;
	काष्ठा gpio_chip	*gc;
	स्थिर काष्ठा mpc8xxx_gpio_devtype *devtype = शून्य;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	mpc8xxx_gc = devm_kzalloc(&pdev->dev, माप(*mpc8xxx_gc), GFP_KERNEL);
	अगर (!mpc8xxx_gc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mpc8xxx_gc);

	raw_spin_lock_init(&mpc8xxx_gc->lock);

	mpc8xxx_gc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mpc8xxx_gc->regs))
		वापस PTR_ERR(mpc8xxx_gc->regs);

	gc = &mpc8xxx_gc->gc;
	gc->parent = &pdev->dev;

	अगर (device_property_पढ़ो_bool(&pdev->dev, "little-endian")) अणु
		ret = bgpio_init(gc, &pdev->dev, 4,
				 mpc8xxx_gc->regs + GPIO_DAT,
				 शून्य, शून्य,
				 mpc8xxx_gc->regs + GPIO_सूची, शून्य,
				 BGPIOF_BIG_ENDIAN);
		अगर (ret)
			जाओ err;
		dev_dbg(&pdev->dev, "GPIO registers are LITTLE endian\n");
	पूर्ण अन्यथा अणु
		ret = bgpio_init(gc, &pdev->dev, 4,
				 mpc8xxx_gc->regs + GPIO_DAT,
				 शून्य, शून्य,
				 mpc8xxx_gc->regs + GPIO_सूची, शून्य,
				 BGPIOF_BIG_ENDIAN
				 | BGPIOF_BIG_ENDIAN_BYTE_ORDER);
		अगर (ret)
			जाओ err;
		dev_dbg(&pdev->dev, "GPIO registers are BIG endian\n");
	पूर्ण

	mpc8xxx_gc->direction_output = gc->direction_output;

	devtype = device_get_match_data(&pdev->dev);
	अगर (!devtype)
		devtype = &mpc8xxx_gpio_devtype_शेष;

	/*
	 * It's assumed that only a single type of gpio controller is available
	 * on the current machine, so overwriting global data is fine.
	 */
	अगर (devtype->irq_set_type)
		mpc8xxx_irq_chip.irq_set_type = devtype->irq_set_type;

	अगर (devtype->gpio_dir_out)
		gc->direction_output = devtype->gpio_dir_out;
	अगर (devtype->gpio_get)
		gc->get = devtype->gpio_get;

	gc->to_irq = mpc8xxx_gpio_to_irq;

	/*
	 * The GPIO Input Buffer Enable रेजिस्टर(GPIO_IBE) is used to control
	 * the input enable of each inभागidual GPIO port.  When an inभागidual
	 * GPIO portै s direction is set to input (GPIO_GPसूची[DRn=0]), the
	 * associated input enable must be set (GPIOxGPIE[IEn]=1) to propagate
	 * the port value to the GPIO Data Register.
	 */
	fwnode = dev_fwnode(&pdev->dev);
	अगर (of_device_is_compatible(np, "fsl,qoriq-gpio") ||
	    of_device_is_compatible(np, "fsl,ls1028a-gpio") ||
	    of_device_is_compatible(np, "fsl,ls1088a-gpio") ||
	    is_acpi_node(fwnode))
		gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IBE, 0xffffffff);

	ret = gpiochip_add_data(gc, mpc8xxx_gc);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"GPIO chip registration failed with status %d\n", ret);
		जाओ err;
	पूर्ण

	mpc8xxx_gc->irqn = platक्रमm_get_irq(pdev, 0);
	अगर (!mpc8xxx_gc->irqn)
		वापस 0;

	mpc8xxx_gc->irq = irq_करोमुख्य_create_linear(fwnode,
						   MPC8XXX_GPIO_PINS,
						   &mpc8xxx_gpio_irq_ops,
						   mpc8xxx_gc);

	अगर (!mpc8xxx_gc->irq)
		वापस 0;

	/* ack and mask all irqs */
	gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IER, 0xffffffff);
	gc->ग_लिखो_reg(mpc8xxx_gc->regs + GPIO_IMR, 0);

	ret = devm_request_irq(&pdev->dev, mpc8xxx_gc->irqn,
			       mpc8xxx_gpio_irq_cascade,
			       IRQF_SHARED, "gpio-cascade",
			       mpc8xxx_gc);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to devm_request_irq(%d), ret = %d\n",
			mpc8xxx_gc->irqn, ret);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	iounmap(mpc8xxx_gc->regs);
	वापस ret;
पूर्ण

अटल पूर्णांक mpc8xxx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mpc8xxx_gpio_chip *mpc8xxx_gc = platक्रमm_get_drvdata(pdev);

	अगर (mpc8xxx_gc->irq) अणु
		irq_set_chained_handler_and_data(mpc8xxx_gc->irqn, शून्य, शून्य);
		irq_करोमुख्य_हटाओ(mpc8xxx_gc->irq);
	पूर्ण

	gpiochip_हटाओ(&mpc8xxx_gc->gc);
	iounmap(mpc8xxx_gc->regs);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id gpio_acpi_ids[] = अणु
	अणु"NXP0031",पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, gpio_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mpc8xxx_plat_driver = अणु
	.probe		= mpc8xxx_probe,
	.हटाओ		= mpc8xxx_हटाओ,
	.driver		= अणु
		.name = "gpio-mpc8xxx",
		.of_match_table	= mpc8xxx_gpio_ids,
		.acpi_match_table = ACPI_PTR(gpio_acpi_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mpc8xxx_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpc8xxx_plat_driver);
पूर्ण

arch_initcall(mpc8xxx_init);
