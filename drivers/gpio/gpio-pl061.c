<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, 2009 Provigent Ltd.
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Driver क्रम the ARM PrimeCell(पंचांग) General Purpose Input/Output (PL061)
 *
 * Data sheet: ARM DDI 0190B, September 2000
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/slab.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm.h>

#घोषणा GPIOसूची 0x400
#घोषणा GPIOIS  0x404
#घोषणा GPIOIBE 0x408
#घोषणा GPIOIEV 0x40C
#घोषणा GPIOIE  0x410
#घोषणा GPIORIS 0x414
#घोषणा GPIOMIS 0x418
#घोषणा GPIOIC  0x41C

#घोषणा PL061_GPIO_NR	8

#अगर_घोषित CONFIG_PM
काष्ठा pl061_context_save_regs अणु
	u8 gpio_data;
	u8 gpio_dir;
	u8 gpio_is;
	u8 gpio_ibe;
	u8 gpio_iev;
	u8 gpio_ie;
पूर्ण;
#पूर्ण_अगर

काष्ठा pl061 अणु
	raw_spinlock_t		lock;

	व्योम __iomem		*base;
	काष्ठा gpio_chip	gc;
	काष्ठा irq_chip		irq_chip;
	पूर्णांक			parent_irq;

#अगर_घोषित CONFIG_PM
	काष्ठा pl061_context_save_regs csave_regs;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक pl061_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);

	अगर (पढ़ोb(pl061->base + GPIOसूची) & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक pl061_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर gpiodir;

	raw_spin_lock_irqsave(&pl061->lock, flags);
	gpiodir = पढ़ोb(pl061->base + GPIOसूची);
	gpiodir &= ~(BIT(offset));
	ग_लिखोb(gpiodir, pl061->base + GPIOसूची);
	raw_spin_unlock_irqrestore(&pl061->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pl061_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
		पूर्णांक value)
अणु
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर gpiodir;

	raw_spin_lock_irqsave(&pl061->lock, flags);
	ग_लिखोb(!!value << offset, pl061->base + (BIT(offset + 2)));
	gpiodir = पढ़ोb(pl061->base + GPIOसूची);
	gpiodir |= BIT(offset);
	ग_लिखोb(gpiodir, pl061->base + GPIOसूची);

	/*
	 * gpio value is set again, because pl061 करोesn't allow to set value of
	 * a gpio pin beक्रमe configuring it in OUT mode.
	 */
	ग_लिखोb(!!value << offset, pl061->base + (BIT(offset + 2)));
	raw_spin_unlock_irqrestore(&pl061->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pl061_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);

	वापस !!पढ़ोb(pl061->base + (BIT(offset + 2)));
पूर्ण

अटल व्योम pl061_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);

	ग_लिखोb(!!value << offset, pl061->base + (BIT(offset + 2)));
पूर्ण

अटल पूर्णांक pl061_irq_type(काष्ठा irq_data *d, अचिन्हित trigger)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	पूर्णांक offset = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u8 gpiois, gpioibe, gpioiev;
	u8 bit = BIT(offset);

	अगर (offset < 0 || offset >= PL061_GPIO_NR)
		वापस -EINVAL;

	अगर ((trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) &&
	    (trigger & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING)))
	अणु
		dev_err(gc->parent,
			"trying to configure line %d for both level and edge "
			"detection, choose one!\n",
			offset);
		वापस -EINVAL;
	पूर्ण


	raw_spin_lock_irqsave(&pl061->lock, flags);

	gpioiev = पढ़ोb(pl061->base + GPIOIEV);
	gpiois = पढ़ोb(pl061->base + GPIOIS);
	gpioibe = पढ़ोb(pl061->base + GPIOIBE);

	अगर (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) अणु
		bool polarity = trigger & IRQ_TYPE_LEVEL_HIGH;

		/* Disable edge detection */
		gpioibe &= ~bit;
		/* Enable level detection */
		gpiois |= bit;
		/* Select polarity */
		अगर (polarity)
			gpioiev |= bit;
		अन्यथा
			gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_level_irq);
		dev_dbg(gc->parent, "line %d: IRQ on %s level\n",
			offset,
			polarity ? "HIGH" : "LOW");
	पूर्ण अन्यथा अगर ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) अणु
		/* Disable level detection */
		gpiois &= ~bit;
		/* Select both edges, setting this makes GPIOEV be ignored */
		gpioibe |= bit;
		irq_set_handler_locked(d, handle_edge_irq);
		dev_dbg(gc->parent, "line %d: IRQ on both edges\n", offset);
	पूर्ण अन्यथा अगर ((trigger & IRQ_TYPE_EDGE_RISING) ||
		   (trigger & IRQ_TYPE_EDGE_FALLING)) अणु
		bool rising = trigger & IRQ_TYPE_EDGE_RISING;

		/* Disable level detection */
		gpiois &= ~bit;
		/* Clear detection on both edges */
		gpioibe &= ~bit;
		/* Select edge */
		अगर (rising)
			gpioiev |= bit;
		अन्यथा
			gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_edge_irq);
		dev_dbg(gc->parent, "line %d: IRQ on %s edge\n",
			offset,
			rising ? "RISING" : "FALLING");
	पूर्ण अन्यथा अणु
		/* No trigger: disable everything */
		gpiois &= ~bit;
		gpioibe &= ~bit;
		gpioiev &= ~bit;
		irq_set_handler_locked(d, handle_bad_irq);
		dev_warn(gc->parent, "no trigger selected for line %d\n",
			 offset);
	पूर्ण

	ग_लिखोb(gpiois, pl061->base + GPIOIS);
	ग_लिखोb(gpioibe, pl061->base + GPIOIBE);
	ग_लिखोb(gpioiev, pl061->base + GPIOIEV);

	raw_spin_unlock_irqrestore(&pl061->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pl061_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित दीर्घ pending;
	पूर्णांक offset;
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);

	chained_irq_enter(irqchip, desc);

	pending = पढ़ोb(pl061->base + GPIOMIS);
	अगर (pending) अणु
		क्रम_each_set_bit(offset, &pending, PL061_GPIO_NR)
			generic_handle_irq(irq_find_mapping(gc->irq.करोमुख्य,
							    offset));
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल व्योम pl061_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	u8 mask = BIT(irqd_to_hwirq(d) % PL061_GPIO_NR);
	u8 gpioie;

	raw_spin_lock(&pl061->lock);
	gpioie = पढ़ोb(pl061->base + GPIOIE) & ~mask;
	ग_लिखोb(gpioie, pl061->base + GPIOIE);
	raw_spin_unlock(&pl061->lock);
पूर्ण

अटल व्योम pl061_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	u8 mask = BIT(irqd_to_hwirq(d) % PL061_GPIO_NR);
	u8 gpioie;

	raw_spin_lock(&pl061->lock);
	gpioie = पढ़ोb(pl061->base + GPIOIE) | mask;
	ग_लिखोb(gpioie, pl061->base + GPIOIE);
	raw_spin_unlock(&pl061->lock);
पूर्ण

/**
 * pl061_irq_ack() - ACK an edge IRQ
 * @d: IRQ data क्रम this IRQ
 *
 * This माला_लो called from the edge IRQ handler to ACK the edge IRQ
 * in the GPIOIC (पूर्णांकerrupt-clear) रेजिस्टर. For level IRQs this is
 * not needed: these go away when the level संकेत goes away.
 */
अटल व्योम pl061_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);
	u8 mask = BIT(irqd_to_hwirq(d) % PL061_GPIO_NR);

	raw_spin_lock(&pl061->lock);
	ग_लिखोb(mask, pl061->base + GPIOIC);
	raw_spin_unlock(&pl061->lock);
पूर्ण

अटल पूर्णांक pl061_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक state)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pl061 *pl061 = gpiochip_get_data(gc);

	वापस irq_set_irq_wake(pl061->parent_irq, state);
पूर्ण

अटल पूर्णांक pl061_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा pl061 *pl061;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret, irq;

	pl061 = devm_kzalloc(dev, माप(*pl061), GFP_KERNEL);
	अगर (pl061 == शून्य)
		वापस -ENOMEM;

	pl061->base = devm_ioremap_resource(dev, &adev->res);
	अगर (IS_ERR(pl061->base))
		वापस PTR_ERR(pl061->base);

	raw_spin_lock_init(&pl061->lock);
	pl061->gc.request = gpiochip_generic_request;
	pl061->gc.मुक्त = gpiochip_generic_मुक्त;
	pl061->gc.base = -1;
	pl061->gc.get_direction = pl061_get_direction;
	pl061->gc.direction_input = pl061_direction_input;
	pl061->gc.direction_output = pl061_direction_output;
	pl061->gc.get = pl061_get_value;
	pl061->gc.set = pl061_set_value;
	pl061->gc.ngpio = PL061_GPIO_NR;
	pl061->gc.label = dev_name(dev);
	pl061->gc.parent = dev;
	pl061->gc.owner = THIS_MODULE;

	/*
	 * irq_chip support
	 */
	pl061->irq_chip.name = dev_name(dev);
	pl061->irq_chip.irq_ack	= pl061_irq_ack;
	pl061->irq_chip.irq_mask = pl061_irq_mask;
	pl061->irq_chip.irq_unmask = pl061_irq_unmask;
	pl061->irq_chip.irq_set_type = pl061_irq_type;
	pl061->irq_chip.irq_set_wake = pl061_irq_set_wake;

	ग_लिखोb(0, pl061->base + GPIOIE); /* disable irqs */
	irq = adev->irq[0];
	अगर (!irq)
		dev_warn(&adev->dev, "IRQ support disabled\n");
	pl061->parent_irq = irq;

	girq = &pl061->gc.irq;
	girq->chip = &pl061->irq_chip;
	girq->parent_handler = pl061_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;

	ret = devm_gpiochip_add_data(dev, &pl061->gc, pl061);
	अगर (ret)
		वापस ret;

	amba_set_drvdata(adev, pl061);
	dev_info(dev, "PL061 GPIO chip registered\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pl061_suspend(काष्ठा device *dev)
अणु
	काष्ठा pl061 *pl061 = dev_get_drvdata(dev);
	पूर्णांक offset;

	pl061->csave_regs.gpio_data = 0;
	pl061->csave_regs.gpio_dir = पढ़ोb(pl061->base + GPIOसूची);
	pl061->csave_regs.gpio_is = पढ़ोb(pl061->base + GPIOIS);
	pl061->csave_regs.gpio_ibe = पढ़ोb(pl061->base + GPIOIBE);
	pl061->csave_regs.gpio_iev = पढ़ोb(pl061->base + GPIOIEV);
	pl061->csave_regs.gpio_ie = पढ़ोb(pl061->base + GPIOIE);

	क्रम (offset = 0; offset < PL061_GPIO_NR; offset++) अणु
		अगर (pl061->csave_regs.gpio_dir & (BIT(offset)))
			pl061->csave_regs.gpio_data |=
				pl061_get_value(&pl061->gc, offset) << offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl061_resume(काष्ठा device *dev)
अणु
	काष्ठा pl061 *pl061 = dev_get_drvdata(dev);
	पूर्णांक offset;

	क्रम (offset = 0; offset < PL061_GPIO_NR; offset++) अणु
		अगर (pl061->csave_regs.gpio_dir & (BIT(offset)))
			pl061_direction_output(&pl061->gc, offset,
					pl061->csave_regs.gpio_data &
					(BIT(offset)));
		अन्यथा
			pl061_direction_input(&pl061->gc, offset);
	पूर्ण

	ग_लिखोb(pl061->csave_regs.gpio_is, pl061->base + GPIOIS);
	ग_लिखोb(pl061->csave_regs.gpio_ibe, pl061->base + GPIOIBE);
	ग_लिखोb(pl061->csave_regs.gpio_iev, pl061->base + GPIOIEV);
	ग_लिखोb(pl061->csave_regs.gpio_ie, pl061->base + GPIOIE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pl061_dev_pm_ops = अणु
	.suspend = pl061_suspend,
	.resume = pl061_resume,
	.मुक्तze = pl061_suspend,
	.restore = pl061_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा amba_id pl061_ids[] = अणु
	अणु
		.id	= 0x00041061,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, pl061_ids);

अटल काष्ठा amba_driver pl061_gpio_driver = अणु
	.drv = अणु
		.name	= "pl061_gpio",
#अगर_घोषित CONFIG_PM
		.pm	= &pl061_dev_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.id_table	= pl061_ids,
	.probe		= pl061_probe,
पूर्ण;
module_amba_driver(pl061_gpio_driver);

MODULE_LICENSE("GPL v2");
