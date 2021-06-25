<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/mach-x3proto/gpio.c
 *
 * Renesas SH-X3 Prototype Baseboard GPIO Support.
 *
 * Copyright (C) 2010 - 2012  Paul Mundt
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <mach/ilsel.h>
#समावेश <mach/hardware.h>

#घोषणा KEYCTLR	0xb81c0000
#घोषणा KEYOUTR	0xb81c0002
#घोषणा KEYDETR 0xb81c0004

अटल DEFINE_SPINLOCK(x3proto_gpio_lock);
अटल काष्ठा irq_करोमुख्य *x3proto_irq_करोमुख्य;

अटल पूर्णांक x3proto_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data;

	spin_lock_irqsave(&x3proto_gpio_lock, flags);
	data = __raw_पढ़ोw(KEYCTLR);
	data |= (1 << gpio);
	__raw_ग_लिखोw(data, KEYCTLR);
	spin_unlock_irqrestore(&x3proto_gpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक x3proto_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस !!(__raw_पढ़ोw(KEYDETR) & (1 << gpio));
पूर्ण

अटल पूर्णांक x3proto_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	पूर्णांक virq;

	अगर (gpio < chip->ngpio)
		virq = irq_create_mapping(x3proto_irq_करोमुख्य, gpio);
	अन्यथा
		virq = -ENXIO;

	वापस virq;
पूर्ण

अटल व्योम x3proto_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	अचिन्हित दीर्घ mask;
	पूर्णांक pin;

	chip->irq_mask_ack(data);

	mask = __raw_पढ़ोw(KEYDETR);
	क्रम_each_set_bit(pin, &mask, NR_BASEBOARD_GPIOS)
		generic_handle_irq(irq_linear_revmap(x3proto_irq_करोमुख्य, pin));

	chip->irq_unmask(data);
पूर्ण

काष्ठा gpio_chip x3proto_gpio_chip = अणु
	.label			= "x3proto-gpio",
	.direction_input	= x3proto_gpio_direction_input,
	.get			= x3proto_gpio_get,
	.to_irq			= x3proto_gpio_to_irq,
	.base			= -1,
	.ngpio			= NR_BASEBOARD_GPIOS,
पूर्ण;

अटल पूर्णांक x3proto_gpio_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler_name(virq, &dummy_irq_chip, handle_simple_irq,
				      "gpio");

	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops x3proto_gpio_irq_ops = अणु
	.map	= x3proto_gpio_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

पूर्णांक __init x3proto_gpio_setup(व्योम)
अणु
	पूर्णांक ilsel, ret;

	ilsel = ilsel_enable(ILSEL_KEY);
	अगर (unlikely(ilsel < 0))
		वापस ilsel;

	ret = gpiochip_add_data(&x3proto_gpio_chip, शून्य);
	अगर (unlikely(ret))
		जाओ err_gpio;

	x3proto_irq_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, NR_BASEBOARD_GPIOS,
						   &x3proto_gpio_irq_ops, शून्य);
	अगर (unlikely(!x3proto_irq_करोमुख्य))
		जाओ err_irq;

	pr_info("registering '%s' support, handling GPIOs %u -> %u, "
		"bound to IRQ %u\n",
		x3proto_gpio_chip.label, x3proto_gpio_chip.base,
		x3proto_gpio_chip.base + x3proto_gpio_chip.ngpio,
		ilsel);

	irq_set_chained_handler(ilsel, x3proto_gpio_irq_handler);
	irq_set_irq_wake(ilsel, 1);

	वापस 0;

err_irq:
	gpiochip_हटाओ(&x3proto_gpio_chip);
	ret = 0;
err_gpio:
	synchronize_irq(ilsel);

	ilsel_disable(ILSEL_KEY);

	वापस ret;
पूर्ण
