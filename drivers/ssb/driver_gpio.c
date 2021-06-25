<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * GPIO driver
 *
 * Copyright 2011, Broadcom Corporation
 * Copyright 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/export.h>
#समावेश <linux/ssb/ssb.h>


/**************************************************
 * Shared
 **************************************************/

#अगर IS_ENABLED(CONFIG_SSB_EMBEDDED)
अटल पूर्णांक ssb_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	अगर (bus->bustype == SSB_BUSTYPE_SSB)
		वापस irq_find_mapping(bus->irq_करोमुख्य, gpio);
	अन्यथा
		वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/**************************************************
 * ChipCommon
 **************************************************/

अटल पूर्णांक ssb_gpio_chipco_get_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	वापस !!ssb_chipco_gpio_in(&bus->chipco, 1 << gpio);
पूर्ण

अटल व्योम ssb_gpio_chipco_set_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				      पूर्णांक value)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_out(&bus->chipco, 1 << gpio, value ? 1 << gpio : 0);
पूर्ण

अटल पूर्णांक ssb_gpio_chipco_direction_input(काष्ठा gpio_chip *chip,
					   अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_outen(&bus->chipco, 1 << gpio, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ssb_gpio_chipco_direction_output(काष्ठा gpio_chip *chip,
					    अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_outen(&bus->chipco, 1 << gpio, 1 << gpio);
	ssb_chipco_gpio_out(&bus->chipco, 1 << gpio, value ? 1 << gpio : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ssb_gpio_chipco_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_chipco_gpio_control(&bus->chipco, 1 << gpio, 0);
	/* clear pullकरोwn */
	ssb_chipco_gpio_pullकरोwn(&bus->chipco, 1 << gpio, 0);
	/* Set pullup */
	ssb_chipco_gpio_pullup(&bus->chipco, 1 << gpio, 1 << gpio);

	वापस 0;
पूर्ण

अटल व्योम ssb_gpio_chipco_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	/* clear pullup */
	ssb_chipco_gpio_pullup(&bus->chipco, 1 << gpio, 0);
पूर्ण

#अगर IS_ENABLED(CONFIG_SSB_EMBEDDED)
अटल व्योम ssb_gpio_irq_chipco_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ssb_bus *bus = irq_data_get_irq_chip_data(d);
	पूर्णांक gpio = irqd_to_hwirq(d);

	ssb_chipco_gpio_पूर्णांकmask(&bus->chipco, BIT(gpio), 0);
पूर्ण

अटल व्योम ssb_gpio_irq_chipco_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ssb_bus *bus = irq_data_get_irq_chip_data(d);
	पूर्णांक gpio = irqd_to_hwirq(d);
	u32 val = ssb_chipco_gpio_in(&bus->chipco, BIT(gpio));

	ssb_chipco_gpio_polarity(&bus->chipco, BIT(gpio), val);
	ssb_chipco_gpio_पूर्णांकmask(&bus->chipco, BIT(gpio), BIT(gpio));
पूर्ण

अटल काष्ठा irq_chip ssb_gpio_irq_chipco_chip = अणु
	.name		= "SSB-GPIO-CC",
	.irq_mask	= ssb_gpio_irq_chipco_mask,
	.irq_unmask	= ssb_gpio_irq_chipco_unmask,
पूर्ण;

अटल irqवापस_t ssb_gpio_irq_chipco_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ssb_bus *bus = dev_id;
	काष्ठा ssb_chipcommon *chipco = &bus->chipco;
	u32 val = chipco_पढ़ो32(chipco, SSB_CHIPCO_GPIOIN);
	u32 mask = chipco_पढ़ो32(chipco, SSB_CHIPCO_GPIOIRQ);
	u32 pol = chipco_पढ़ो32(chipco, SSB_CHIPCO_GPIOPOL);
	अचिन्हित दीर्घ irqs = (val ^ pol) & mask;
	पूर्णांक gpio;

	अगर (!irqs)
		वापस IRQ_NONE;

	क्रम_each_set_bit(gpio, &irqs, bus->gpio.ngpio)
		generic_handle_irq(ssb_gpio_to_irq(&bus->gpio, gpio));
	ssb_chipco_gpio_polarity(chipco, irqs, val & irqs);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ssb_gpio_irq_chipco_करोमुख्य_init(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_chipcommon *chipco = &bus->chipco;
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक gpio, hwirq, err;

	अगर (bus->bustype != SSB_BUSTYPE_SSB)
		वापस 0;

	bus->irq_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, chip->ngpio,
						&irq_करोमुख्य_simple_ops, chipco);
	अगर (!bus->irq_करोमुख्य) अणु
		err = -ENODEV;
		जाओ err_irq_करोमुख्य;
	पूर्ण
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_create_mapping(bus->irq_करोमुख्य, gpio);

		irq_set_chip_data(irq, bus);
		irq_set_chip_and_handler(irq, &ssb_gpio_irq_chipco_chip,
					 handle_simple_irq);
	पूर्ण

	hwirq = ssb_mips_irq(bus->chipco.dev) + 2;
	err = request_irq(hwirq, ssb_gpio_irq_chipco_handler, IRQF_SHARED,
			  "gpio", bus);
	अगर (err)
		जाओ err_req_irq;

	ssb_chipco_gpio_पूर्णांकmask(&bus->chipco, ~0, 0);
	chipco_set32(chipco, SSB_CHIPCO_IRQMASK, SSB_CHIPCO_IRQ_GPIO);

	वापस 0;

err_req_irq:
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_find_mapping(bus->irq_करोमुख्य, gpio);

		irq_dispose_mapping(irq);
	पूर्ण
	irq_करोमुख्य_हटाओ(bus->irq_करोमुख्य);
err_irq_करोमुख्य:
	वापस err;
पूर्ण

अटल व्योम ssb_gpio_irq_chipco_करोमुख्य_निकास(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_chipcommon *chipco = &bus->chipco;
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक gpio;

	अगर (bus->bustype != SSB_BUSTYPE_SSB)
		वापस;

	chipco_mask32(chipco, SSB_CHIPCO_IRQMASK, ~SSB_CHIPCO_IRQ_GPIO);
	मुक्त_irq(ssb_mips_irq(bus->chipco.dev) + 2, chipco);
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_find_mapping(bus->irq_करोमुख्य, gpio);

		irq_dispose_mapping(irq);
	पूर्ण
	irq_करोमुख्य_हटाओ(bus->irq_करोमुख्य);
पूर्ण
#अन्यथा
अटल पूर्णांक ssb_gpio_irq_chipco_करोमुख्य_init(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण

अटल व्योम ssb_gpio_irq_chipco_करोमुख्य_निकास(काष्ठा ssb_bus *bus)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ssb_gpio_chipco_init(काष्ठा ssb_bus *bus)
अणु
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक err;

	chip->label		= "ssb_chipco_gpio";
	chip->owner		= THIS_MODULE;
	chip->request		= ssb_gpio_chipco_request;
	chip->मुक्त		= ssb_gpio_chipco_मुक्त;
	chip->get		= ssb_gpio_chipco_get_value;
	chip->set		= ssb_gpio_chipco_set_value;
	chip->direction_input	= ssb_gpio_chipco_direction_input;
	chip->direction_output	= ssb_gpio_chipco_direction_output;
#अगर IS_ENABLED(CONFIG_SSB_EMBEDDED)
	chip->to_irq		= ssb_gpio_to_irq;
#पूर्ण_अगर
	chip->ngpio		= 16;
	/* There is just one SoC in one device and its GPIO addresses should be
	 * deterministic to address them more easily. The other buses could get
	 * a अक्रमom base number. */
	अगर (bus->bustype == SSB_BUSTYPE_SSB)
		chip->base		= 0;
	अन्यथा
		chip->base		= -1;

	err = ssb_gpio_irq_chipco_करोमुख्य_init(bus);
	अगर (err)
		वापस err;

	err = gpiochip_add_data(chip, bus);
	अगर (err) अणु
		ssb_gpio_irq_chipco_करोमुख्य_निकास(bus);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**************************************************
 * EXTIF
 **************************************************/

#अगर_घोषित CONFIG_SSB_DRIVER_EXTIF

अटल पूर्णांक ssb_gpio_extअगर_get_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	वापस !!ssb_extअगर_gpio_in(&bus->extअगर, 1 << gpio);
पूर्ण

अटल व्योम ssb_gpio_extअगर_set_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				     पूर्णांक value)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extअगर_gpio_out(&bus->extअगर, 1 << gpio, value ? 1 << gpio : 0);
पूर्ण

अटल पूर्णांक ssb_gpio_extअगर_direction_input(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extअगर_gpio_outen(&bus->extअगर, 1 << gpio, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ssb_gpio_extअगर_direction_output(काष्ठा gpio_chip *chip,
					   अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा ssb_bus *bus = gpiochip_get_data(chip);

	ssb_extअगर_gpio_outen(&bus->extअगर, 1 << gpio, 1 << gpio);
	ssb_extअगर_gpio_out(&bus->extअगर, 1 << gpio, value ? 1 << gpio : 0);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SSB_EMBEDDED)
अटल व्योम ssb_gpio_irq_extअगर_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ssb_bus *bus = irq_data_get_irq_chip_data(d);
	पूर्णांक gpio = irqd_to_hwirq(d);

	ssb_extअगर_gpio_पूर्णांकmask(&bus->extअगर, BIT(gpio), 0);
पूर्ण

अटल व्योम ssb_gpio_irq_extअगर_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ssb_bus *bus = irq_data_get_irq_chip_data(d);
	पूर्णांक gpio = irqd_to_hwirq(d);
	u32 val = ssb_extअगर_gpio_in(&bus->extअगर, BIT(gpio));

	ssb_extअगर_gpio_polarity(&bus->extअगर, BIT(gpio), val);
	ssb_extअगर_gpio_पूर्णांकmask(&bus->extअगर, BIT(gpio), BIT(gpio));
पूर्ण

अटल काष्ठा irq_chip ssb_gpio_irq_extअगर_chip = अणु
	.name		= "SSB-GPIO-EXTIF",
	.irq_mask	= ssb_gpio_irq_extअगर_mask,
	.irq_unmask	= ssb_gpio_irq_extअगर_unmask,
पूर्ण;

अटल irqवापस_t ssb_gpio_irq_extअगर_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ssb_bus *bus = dev_id;
	काष्ठा ssb_extअगर *extअगर = &bus->extअगर;
	u32 val = ssb_पढ़ो32(extअगर->dev, SSB_EXTIF_GPIO_IN);
	u32 mask = ssb_पढ़ो32(extअगर->dev, SSB_EXTIF_GPIO_INTMASK);
	u32 pol = ssb_पढ़ो32(extअगर->dev, SSB_EXTIF_GPIO_INTPOL);
	अचिन्हित दीर्घ irqs = (val ^ pol) & mask;
	पूर्णांक gpio;

	अगर (!irqs)
		वापस IRQ_NONE;

	क्रम_each_set_bit(gpio, &irqs, bus->gpio.ngpio)
		generic_handle_irq(ssb_gpio_to_irq(&bus->gpio, gpio));
	ssb_extअगर_gpio_polarity(extअगर, irqs, val & irqs);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ssb_gpio_irq_extअगर_करोमुख्य_init(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_extअगर *extअगर = &bus->extअगर;
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक gpio, hwirq, err;

	अगर (bus->bustype != SSB_BUSTYPE_SSB)
		वापस 0;

	bus->irq_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, chip->ngpio,
						&irq_करोमुख्य_simple_ops, extअगर);
	अगर (!bus->irq_करोमुख्य) अणु
		err = -ENODEV;
		जाओ err_irq_करोमुख्य;
	पूर्ण
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_create_mapping(bus->irq_करोमुख्य, gpio);

		irq_set_chip_data(irq, bus);
		irq_set_chip_and_handler(irq, &ssb_gpio_irq_extअगर_chip,
					 handle_simple_irq);
	पूर्ण

	hwirq = ssb_mips_irq(bus->extअगर.dev) + 2;
	err = request_irq(hwirq, ssb_gpio_irq_extअगर_handler, IRQF_SHARED,
			  "gpio", bus);
	अगर (err)
		जाओ err_req_irq;

	ssb_extअगर_gpio_पूर्णांकmask(&bus->extअगर, ~0, 0);

	वापस 0;

err_req_irq:
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_find_mapping(bus->irq_करोमुख्य, gpio);

		irq_dispose_mapping(irq);
	पूर्ण
	irq_करोमुख्य_हटाओ(bus->irq_करोमुख्य);
err_irq_करोमुख्य:
	वापस err;
पूर्ण

अटल व्योम ssb_gpio_irq_extअगर_करोमुख्य_निकास(काष्ठा ssb_bus *bus)
अणु
	काष्ठा ssb_extअगर *extअगर = &bus->extअगर;
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक gpio;

	अगर (bus->bustype != SSB_BUSTYPE_SSB)
		वापस;

	मुक्त_irq(ssb_mips_irq(bus->extअगर.dev) + 2, extअगर);
	क्रम (gpio = 0; gpio < chip->ngpio; gpio++) अणु
		पूर्णांक irq = irq_find_mapping(bus->irq_करोमुख्य, gpio);

		irq_dispose_mapping(irq);
	पूर्ण
	irq_करोमुख्य_हटाओ(bus->irq_करोमुख्य);
पूर्ण
#अन्यथा
अटल पूर्णांक ssb_gpio_irq_extअगर_करोमुख्य_init(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण

अटल व्योम ssb_gpio_irq_extअगर_करोमुख्य_निकास(काष्ठा ssb_bus *bus)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ssb_gpio_extअगर_init(काष्ठा ssb_bus *bus)
अणु
	काष्ठा gpio_chip *chip = &bus->gpio;
	पूर्णांक err;

	chip->label		= "ssb_extif_gpio";
	chip->owner		= THIS_MODULE;
	chip->get		= ssb_gpio_extअगर_get_value;
	chip->set		= ssb_gpio_extअगर_set_value;
	chip->direction_input	= ssb_gpio_extअगर_direction_input;
	chip->direction_output	= ssb_gpio_extअगर_direction_output;
#अगर IS_ENABLED(CONFIG_SSB_EMBEDDED)
	chip->to_irq		= ssb_gpio_to_irq;
#पूर्ण_अगर
	chip->ngpio		= 5;
	/* There is just one SoC in one device and its GPIO addresses should be
	 * deterministic to address them more easily. The other buses could get
	 * a अक्रमom base number. */
	अगर (bus->bustype == SSB_BUSTYPE_SSB)
		chip->base		= 0;
	अन्यथा
		chip->base		= -1;

	err = ssb_gpio_irq_extअगर_करोमुख्य_init(bus);
	अगर (err)
		वापस err;

	err = gpiochip_add_data(chip, bus);
	अगर (err) अणु
		ssb_gpio_irq_extअगर_करोमुख्य_निकास(bus);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक ssb_gpio_extअगर_init(काष्ठा ssb_bus *bus)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

/**************************************************
 * Init
 **************************************************/

पूर्णांक ssb_gpio_init(काष्ठा ssb_bus *bus)
अणु
	अगर (ssb_chipco_available(&bus->chipco))
		वापस ssb_gpio_chipco_init(bus);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		वापस ssb_gpio_extअगर_init(bus);
	वापस -1;
पूर्ण

पूर्णांक ssb_gpio_unरेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	अगर (ssb_chipco_available(&bus->chipco) ||
	    ssb_extअगर_available(&bus->extअगर)) अणु
		gpiochip_हटाओ(&bus->gpio);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
