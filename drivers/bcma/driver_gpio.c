<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * GPIO driver
 *
 * Copyright 2011, Broadcom Corporation
 * Copyright 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>

#समावेश "bcma_private.h"

#घोषणा BCMA_GPIO_MAX_PINS	32

अटल पूर्णांक bcma_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	वापस !!bcma_chipco_gpio_in(cc, 1 << gpio);
पूर्ण

अटल व्योम bcma_gpio_set_value(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				पूर्णांक value)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	bcma_chipco_gpio_out(cc, 1 << gpio, value ? 1 << gpio : 0);
पूर्ण

अटल पूर्णांक bcma_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	bcma_chipco_gpio_outen(cc, 1 << gpio, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक bcma_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				      पूर्णांक value)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	bcma_chipco_gpio_outen(cc, 1 << gpio, 1 << gpio);
	bcma_chipco_gpio_out(cc, 1 << gpio, value ? 1 << gpio : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक bcma_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	bcma_chipco_gpio_control(cc, 1 << gpio, 0);
	/* clear pullकरोwn */
	bcma_chipco_gpio_pullकरोwn(cc, 1 << gpio, 0);
	/* Set pullup */
	bcma_chipco_gpio_pullup(cc, 1 << gpio, 1 << gpio);

	वापस 0;
पूर्ण

अटल व्योम bcma_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(chip);

	/* clear pullup */
	bcma_chipco_gpio_pullup(cc, 1 << gpio, 0);
पूर्ण

#अगर IS_BUILTIN(CONFIG_BCM47XX) || IS_BUILTIN(CONFIG_ARCH_BCM_5301X)

अटल व्योम bcma_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(gc);
	पूर्णांक gpio = irqd_to_hwirq(d);
	u32 val = bcma_chipco_gpio_in(cc, BIT(gpio));

	bcma_chipco_gpio_polarity(cc, BIT(gpio), val);
	bcma_chipco_gpio_पूर्णांकmask(cc, BIT(gpio), BIT(gpio));
पूर्ण

अटल व्योम bcma_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा bcma_drv_cc *cc = gpiochip_get_data(gc);
	पूर्णांक gpio = irqd_to_hwirq(d);

	bcma_chipco_gpio_पूर्णांकmask(cc, BIT(gpio), 0);
पूर्ण

अटल काष्ठा irq_chip bcma_gpio_irq_chip = अणु
	.name		= "BCMA-GPIO",
	.irq_mask	= bcma_gpio_irq_mask,
	.irq_unmask	= bcma_gpio_irq_unmask,
पूर्ण;

अटल irqवापस_t bcma_gpio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcma_drv_cc *cc = dev_id;
	काष्ठा gpio_chip *gc = &cc->gpio;
	u32 val = bcma_cc_पढ़ो32(cc, BCMA_CC_GPIOIN);
	u32 mask = bcma_cc_पढ़ो32(cc, BCMA_CC_GPIOIRQ);
	u32 pol = bcma_cc_पढ़ो32(cc, BCMA_CC_GPIOPOL);
	अचिन्हित दीर्घ irqs = (val ^ pol) & mask;
	पूर्णांक gpio;

	अगर (!irqs)
		वापस IRQ_NONE;

	क्रम_each_set_bit(gpio, &irqs, gc->ngpio)
		generic_handle_irq(irq_find_mapping(gc->irq.करोमुख्य, gpio));
	bcma_chipco_gpio_polarity(cc, irqs, val & irqs);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcma_gpio_irq_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा gpio_chip *chip = &cc->gpio;
	काष्ठा gpio_irq_chip *girq = &chip->irq;
	पूर्णांक hwirq, err;

	अगर (cc->core->bus->hosttype != BCMA_HOSTTYPE_SOC)
		वापस 0;

	hwirq = bcma_core_irq(cc->core, 0);
	err = request_irq(hwirq, bcma_gpio_irq_handler, IRQF_SHARED, "gpio",
			  cc);
	अगर (err)
		वापस err;

	bcma_chipco_gpio_पूर्णांकmask(cc, ~0, 0);
	bcma_cc_set32(cc, BCMA_CC_IRQMASK, BCMA_CC_IRQ_GPIO);

	girq->chip = &bcma_gpio_irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;

	वापस 0;
पूर्ण

अटल व्योम bcma_gpio_irq_निकास(काष्ठा bcma_drv_cc *cc)
अणु
	अगर (cc->core->bus->hosttype != BCMA_HOSTTYPE_SOC)
		वापस;

	bcma_cc_mask32(cc, BCMA_CC_IRQMASK, ~BCMA_CC_IRQ_GPIO);
	मुक्त_irq(bcma_core_irq(cc->core, 0), cc);
पूर्ण
#अन्यथा
अटल पूर्णांक bcma_gpio_irq_init(काष्ठा bcma_drv_cc *cc)
अणु
	वापस 0;
पूर्ण

अटल व्योम bcma_gpio_irq_निकास(काष्ठा bcma_drv_cc *cc)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक bcma_gpio_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	काष्ठा gpio_chip *chip = &cc->gpio;
	पूर्णांक err;

	chip->label		= "bcma_gpio";
	chip->owner		= THIS_MODULE;
	chip->request		= bcma_gpio_request;
	chip->मुक्त		= bcma_gpio_मुक्त;
	chip->get		= bcma_gpio_get_value;
	chip->set		= bcma_gpio_set_value;
	chip->direction_input	= bcma_gpio_direction_input;
	chip->direction_output	= bcma_gpio_direction_output;
	chip->owner		= THIS_MODULE;
	chip->parent		= bus->dev;
#अगर IS_BUILTIN(CONFIG_OF)
	chip->of_node		= cc->core->dev.of_node;
#पूर्ण_अगर
	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4707:
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM53572:
	हाल BCMA_CHIP_ID_BCM53573:
	हाल BCMA_CHIP_ID_BCM47094:
		chip->ngpio	= 32;
		अवरोध;
	शेष:
		chip->ngpio	= 16;
	पूर्ण

	/*
	 * Register SoC GPIO devices with असलolute GPIO pin base.
	 * On MIPS, we करोn't have Device Tree and we can't use relative (per chip)
	 * GPIO numbers.
	 * On some ARM devices, user space may want to access some प्रणाली GPIO
	 * pins directly, which is easier to करो with a predictable GPIO base.
	 */
	अगर (IS_BUILTIN(CONFIG_BCM47XX) ||
	    cc->core->bus->hosttype == BCMA_HOSTTYPE_SOC)
		chip->base		= bus->num * BCMA_GPIO_MAX_PINS;
	अन्यथा
		chip->base		= -1;

	err = bcma_gpio_irq_init(cc);
	अगर (err)
		वापस err;

	err = gpiochip_add_data(chip, cc);
	अगर (err) अणु
		bcma_gpio_irq_निकास(cc);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bcma_gpio_unरेजिस्टर(काष्ठा bcma_drv_cc *cc)
अणु
	bcma_gpio_irq_निकास(cc);
	gpiochip_हटाओ(&cc->gpio);
	वापस 0;
पूर्ण
