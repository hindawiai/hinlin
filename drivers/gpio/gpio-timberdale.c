<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Timberdale FPGA GPIO driver
 * Author: Mocean Laboratories
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA GPIO
 */

#समावेश <linux/init.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/timb_gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#घोषणा DRIVER_NAME "timb-gpio"

#घोषणा TGPIOVAL	0x00
#घोषणा TGPIOसूची	0x04
#घोषणा TGPIO_IER	0x08
#घोषणा TGPIO_ISR	0x0c
#घोषणा TGPIO_IPR	0x10
#घोषणा TGPIO_ICR	0x14
#घोषणा TGPIO_FLR	0x18
#घोषणा TGPIO_LVR	0x1c
#घोषणा TGPIO_VER	0x20
#घोषणा TGPIO_BFLR	0x24

काष्ठा timbgpio अणु
	व्योम __iomem		*membase;
	spinlock_t		lock; /* mutual exclusion */
	काष्ठा gpio_chip	gpio;
	पूर्णांक			irq_base;
	अचिन्हित दीर्घ		last_ier;
पूर्ण;

अटल पूर्णांक timbgpio_update_bit(काष्ठा gpio_chip *gpio, अचिन्हित index,
	अचिन्हित offset, bool enabled)
अणु
	काष्ठा timbgpio *tgpio = gpiochip_get_data(gpio);
	u32 reg;

	spin_lock(&tgpio->lock);
	reg = ioपढ़ो32(tgpio->membase + offset);

	अगर (enabled)
		reg |= (1 << index);
	अन्यथा
		reg &= ~(1 << index);

	ioग_लिखो32(reg, tgpio->membase + offset);
	spin_unlock(&tgpio->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक timbgpio_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	वापस timbgpio_update_bit(gpio, nr, TGPIOसूची, true);
पूर्ण

अटल पूर्णांक timbgpio_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा timbgpio *tgpio = gpiochip_get_data(gpio);
	u32 value;

	value = ioपढ़ो32(tgpio->membase + TGPIOVAL);
	वापस (value & (1 << nr)) ? 1 : 0;
पूर्ण

अटल पूर्णांक timbgpio_gpio_direction_output(काष्ठा gpio_chip *gpio,
						अचिन्हित nr, पूर्णांक val)
अणु
	वापस timbgpio_update_bit(gpio, nr, TGPIOसूची, false);
पूर्ण

अटल व्योम timbgpio_gpio_set(काष्ठा gpio_chip *gpio,
				अचिन्हित nr, पूर्णांक val)
अणु
	timbgpio_update_bit(gpio, nr, TGPIOVAL, val != 0);
पूर्ण

अटल पूर्णांक timbgpio_to_irq(काष्ठा gpio_chip *gpio, अचिन्हित offset)
अणु
	काष्ठा timbgpio *tgpio = gpiochip_get_data(gpio);

	अगर (tgpio->irq_base <= 0)
		वापस -EINVAL;

	वापस tgpio->irq_base + offset;
पूर्ण

/*
 * GPIO IRQ
 */
अटल व्योम timbgpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा timbgpio *tgpio = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = d->irq - tgpio->irq_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgpio->lock, flags);
	tgpio->last_ier &= ~(1UL << offset);
	ioग_लिखो32(tgpio->last_ier, tgpio->membase + TGPIO_IER);
	spin_unlock_irqrestore(&tgpio->lock, flags);
पूर्ण

अटल व्योम timbgpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा timbgpio *tgpio = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = d->irq - tgpio->irq_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgpio->lock, flags);
	tgpio->last_ier |= 1UL << offset;
	ioग_लिखो32(tgpio->last_ier, tgpio->membase + TGPIO_IER);
	spin_unlock_irqrestore(&tgpio->lock, flags);
पूर्ण

अटल पूर्णांक timbgpio_irq_type(काष्ठा irq_data *d, अचिन्हित trigger)
अणु
	काष्ठा timbgpio *tgpio = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = d->irq - tgpio->irq_base;
	अचिन्हित दीर्घ flags;
	u32 lvr, flr, bflr = 0;
	u32 ver;
	पूर्णांक ret = 0;

	अगर (offset < 0 || offset > tgpio->gpio.ngpio)
		वापस -EINVAL;

	ver = ioपढ़ो32(tgpio->membase + TGPIO_VER);

	spin_lock_irqsave(&tgpio->lock, flags);

	lvr = ioपढ़ो32(tgpio->membase + TGPIO_LVR);
	flr = ioपढ़ो32(tgpio->membase + TGPIO_FLR);
	अगर (ver > 2)
		bflr = ioपढ़ो32(tgpio->membase + TGPIO_BFLR);

	अगर (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) अणु
		bflr &= ~(1 << offset);
		flr &= ~(1 << offset);
		अगर (trigger & IRQ_TYPE_LEVEL_HIGH)
			lvr |= 1 << offset;
		अन्यथा
			lvr &= ~(1 << offset);
	पूर्ण

	अगर ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) अणु
		अगर (ver < 3) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण अन्यथा अणु
			flr |= 1 << offset;
			bflr |= 1 << offset;
		पूर्ण
	पूर्ण अन्यथा अणु
		bflr &= ~(1 << offset);
		flr |= 1 << offset;
		अगर (trigger & IRQ_TYPE_EDGE_FALLING)
			lvr &= ~(1 << offset);
		अन्यथा
			lvr |= 1 << offset;
	पूर्ण

	ioग_लिखो32(lvr, tgpio->membase + TGPIO_LVR);
	ioग_लिखो32(flr, tgpio->membase + TGPIO_FLR);
	अगर (ver > 2)
		ioग_लिखो32(bflr, tgpio->membase + TGPIO_BFLR);

	ioग_लिखो32(1 << offset, tgpio->membase + TGPIO_ICR);

out:
	spin_unlock_irqrestore(&tgpio->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम timbgpio_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा timbgpio *tgpio = irq_desc_get_handler_data(desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	अचिन्हित दीर्घ ipr;
	पूर्णांक offset;

	data->chip->irq_ack(data);
	ipr = ioपढ़ो32(tgpio->membase + TGPIO_IPR);
	ioग_लिखो32(ipr, tgpio->membase + TGPIO_ICR);

	/*
	 * Some versions of the hardware trash the IER रेजिस्टर अगर more than
	 * one पूर्णांकerrupt is received simultaneously.
	 */
	ioग_लिखो32(0, tgpio->membase + TGPIO_IER);

	क्रम_each_set_bit(offset, &ipr, tgpio->gpio.ngpio)
		generic_handle_irq(timbgpio_to_irq(&tgpio->gpio, offset));

	ioग_लिखो32(tgpio->last_ier, tgpio->membase + TGPIO_IER);
पूर्ण

अटल काष्ठा irq_chip timbgpio_irqchip = अणु
	.name		= "GPIO",
	.irq_enable	= timbgpio_irq_enable,
	.irq_disable	= timbgpio_irq_disable,
	.irq_set_type	= timbgpio_irq_type,
पूर्ण;

अटल पूर्णांक timbgpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err, i;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_chip *gc;
	काष्ठा timbgpio *tgpio;
	काष्ठा timbgpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (!pdata || pdata->nr_pins > 32) अणु
		dev_err(dev, "Invalid platform data\n");
		वापस -EINVAL;
	पूर्ण

	tgpio = devm_kzalloc(dev, माप(*tgpio), GFP_KERNEL);
	अगर (!tgpio)
		वापस -EINVAL;

	tgpio->irq_base = pdata->irq_base;

	spin_lock_init(&tgpio->lock);

	tgpio->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tgpio->membase))
		वापस PTR_ERR(tgpio->membase);

	gc = &tgpio->gpio;

	gc->label = dev_name(&pdev->dev);
	gc->owner = THIS_MODULE;
	gc->parent = &pdev->dev;
	gc->direction_input = timbgpio_gpio_direction_input;
	gc->get = timbgpio_gpio_get;
	gc->direction_output = timbgpio_gpio_direction_output;
	gc->set = timbgpio_gpio_set;
	gc->to_irq = (irq >= 0 && tgpio->irq_base > 0) ? timbgpio_to_irq : शून्य;
	gc->dbg_show = शून्य;
	gc->base = pdata->gpio_base;
	gc->ngpio = pdata->nr_pins;
	gc->can_sleep = false;

	err = devm_gpiochip_add_data(&pdev->dev, gc, tgpio);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, tgpio);

	/* make sure to disable पूर्णांकerrupts */
	ioग_लिखो32(0x0, tgpio->membase + TGPIO_IER);

	अगर (irq < 0 || tgpio->irq_base <= 0)
		वापस 0;

	क्रम (i = 0; i < pdata->nr_pins; i++) अणु
		irq_set_chip_and_handler(tgpio->irq_base + i,
			&timbgpio_irqchip, handle_simple_irq);
		irq_set_chip_data(tgpio->irq_base + i, tgpio);
		irq_clear_status_flags(tgpio->irq_base + i, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_chained_handler_and_data(irq, timbgpio_irq, tgpio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver timbgpio_platक्रमm_driver = अणु
	.driver = अणु
		.name			= DRIVER_NAME,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= timbgpio_probe,
पूर्ण;

/*--------------------------------------------------------------------------*/

builtin_platक्रमm_driver(timbgpio_platक्रमm_driver);
