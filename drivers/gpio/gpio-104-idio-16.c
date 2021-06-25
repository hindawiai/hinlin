<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the ACCES 104-IDIO-16 family
 * Copyright (C) 2015 William Breathitt Gray
 *
 * This driver supports the following ACCES devices: 104-IDIO-16,
 * 104-IDIO-16E, 104-IDO-16, 104-IDIO-8, 104-IDIO-8E, and 104-IDO-8.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/isa.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>

#घोषणा IDIO_16_EXTENT 8
#घोषणा MAX_NUM_IDIO_16 max_num_isa_dev(IDIO_16_EXTENT)

अटल अचिन्हित पूर्णांक base[MAX_NUM_IDIO_16];
अटल अचिन्हित पूर्णांक num_idio_16;
module_param_hw_array(base, uपूर्णांक, ioport, &num_idio_16, 0);
MODULE_PARM_DESC(base, "ACCES 104-IDIO-16 base addresses");

अटल अचिन्हित पूर्णांक irq[MAX_NUM_IDIO_16];
module_param_hw_array(irq, uपूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "ACCES 104-IDIO-16 interrupt line numbers");

/**
 * काष्ठा idio_16_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @lock:	synchronization lock to prevent I/O race conditions
 * @irq_mask:	I/O bits affected by पूर्णांकerrupts
 * @base:	base port address of the GPIO device
 * @out_state:	output bits state
 */
काष्ठा idio_16_gpio अणु
	काष्ठा gpio_chip chip;
	raw_spinlock_t lock;
	अचिन्हित दीर्घ irq_mask;
	अचिन्हित base;
	अचिन्हित out_state;
पूर्ण;

अटल पूर्णांक idio_16_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset > 15)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक idio_16_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित offset, पूर्णांक value)
अणु
	chip->set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित mask = BIT(offset-16);

	अगर (offset < 16)
		वापस -EINVAL;

	अगर (offset < 24)
		वापस !!(inb(idio16gpio->base + 1) & mask);

	वापस !!(inb(idio16gpio->base + 5) & (mask>>8));
पूर्ण

अटल पूर्णांक idio_16_gpio_get_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);

	*bits = 0;
	अगर (*mask & GENMASK(23, 16))
		*bits |= (अचिन्हित दीर्घ)inb(idio16gpio->base + 1) << 16;
	अगर (*mask & GENMASK(31, 24))
		*bits |= (अचिन्हित दीर्घ)inb(idio16gpio->base + 5) << 24;

	वापस 0;
पूर्ण

अटल व्योम idio_16_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित mask = BIT(offset);
	अचिन्हित दीर्घ flags;

	अगर (offset > 15)
		वापस;

	raw_spin_lock_irqsave(&idio16gpio->lock, flags);

	अगर (value)
		idio16gpio->out_state |= mask;
	अन्यथा
		idio16gpio->out_state &= ~mask;

	अगर (offset > 7)
		outb(idio16gpio->out_state >> 8, idio16gpio->base + 4);
	अन्यथा
		outb(idio16gpio->out_state, idio16gpio->base);

	raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
पूर्ण

अटल व्योम idio_16_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&idio16gpio->lock, flags);

	idio16gpio->out_state &= ~*mask;
	idio16gpio->out_state |= *mask & *bits;

	अगर (*mask & 0xFF)
		outb(idio16gpio->out_state, idio16gpio->base);
	अगर ((*mask >> 8) & 0xFF)
		outb(idio16gpio->out_state >> 8, idio16gpio->base + 4);

	raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
पूर्ण

अटल व्योम idio_16_irq_ack(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम idio_16_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ mask = BIT(irqd_to_hwirq(data));
	अचिन्हित दीर्घ flags;

	idio16gpio->irq_mask &= ~mask;

	अगर (!idio16gpio->irq_mask) अणु
		raw_spin_lock_irqsave(&idio16gpio->lock, flags);

		outb(0, idio16gpio->base + 2);

		raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम idio_16_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ mask = BIT(irqd_to_hwirq(data));
	स्थिर अचिन्हित दीर्घ prev_irq_mask = idio16gpio->irq_mask;
	अचिन्हित दीर्घ flags;

	idio16gpio->irq_mask |= mask;

	अगर (!prev_irq_mask) अणु
		raw_spin_lock_irqsave(&idio16gpio->lock, flags);

		inb(idio16gpio->base + 2);

		raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक idio_16_irq_set_type(काष्ठा irq_data *data, अचिन्हित flow_type)
अणु
	/* The only valid irq types are none and both-edges */
	अगर (flow_type != IRQ_TYPE_NONE &&
		(flow_type & IRQ_TYPE_EDGE_BOTH) != IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip idio_16_irqchip = अणु
	.name = "104-idio-16",
	.irq_ack = idio_16_irq_ack,
	.irq_mask = idio_16_irq_mask,
	.irq_unmask = idio_16_irq_unmask,
	.irq_set_type = idio_16_irq_set_type
पूर्ण;

अटल irqवापस_t idio_16_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = dev_id;
	काष्ठा gpio_chip *स्थिर chip = &idio16gpio->chip;
	पूर्णांक gpio;

	क्रम_each_set_bit(gpio, &idio16gpio->irq_mask, chip->ngpio)
		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य, gpio));

	raw_spin_lock(&idio16gpio->lock);

	outb(0, idio16gpio->base + 1);

	raw_spin_unlock(&idio16gpio->lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा IDIO_16_NGPIO 32
अटल स्थिर अक्षर *idio_16_names[IDIO_16_NGPIO] = अणु
	"OUT0", "OUT1", "OUT2", "OUT3", "OUT4", "OUT5", "OUT6", "OUT7",
	"OUT8", "OUT9", "OUT10", "OUT11", "OUT12", "OUT13", "OUT14", "OUT15",
	"IIN0", "IIN1", "IIN2", "IIN3", "IIN4", "IIN5", "IIN6", "IIN7",
	"IIN8", "IIN9", "IIN10", "IIN11", "IIN12", "IIN13", "IIN14", "IIN15"
पूर्ण;

अटल पूर्णांक idio_16_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(gc);

	/* Disable IRQ by शेष */
	outb(0, idio16gpio->base + 2);
	outb(0, idio16gpio->base + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा idio_16_gpio *idio16gpio;
	स्थिर अक्षर *स्थिर name = dev_name(dev);
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	idio16gpio = devm_kzalloc(dev, माप(*idio16gpio), GFP_KERNEL);
	अगर (!idio16gpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], IDIO_16_EXTENT, name)) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + IDIO_16_EXTENT);
		वापस -EBUSY;
	पूर्ण

	idio16gpio->chip.label = name;
	idio16gpio->chip.parent = dev;
	idio16gpio->chip.owner = THIS_MODULE;
	idio16gpio->chip.base = -1;
	idio16gpio->chip.ngpio = IDIO_16_NGPIO;
	idio16gpio->chip.names = idio_16_names;
	idio16gpio->chip.get_direction = idio_16_gpio_get_direction;
	idio16gpio->chip.direction_input = idio_16_gpio_direction_input;
	idio16gpio->chip.direction_output = idio_16_gpio_direction_output;
	idio16gpio->chip.get = idio_16_gpio_get;
	idio16gpio->chip.get_multiple = idio_16_gpio_get_multiple;
	idio16gpio->chip.set = idio_16_gpio_set;
	idio16gpio->chip.set_multiple = idio_16_gpio_set_multiple;
	idio16gpio->base = base[id];
	idio16gpio->out_state = 0xFFFF;

	girq = &idio16gpio->chip.irq;
	girq->chip = &idio_16_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;
	girq->init_hw = idio_16_irq_init_hw;

	raw_spin_lock_init(&idio16gpio->lock);

	err = devm_gpiochip_add_data(dev, &idio16gpio->chip, idio16gpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, irq[id], idio_16_irq_handler, 0, name,
		idio16gpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा isa_driver idio_16_driver = अणु
	.probe = idio_16_probe,
	.driver = अणु
		.name = "104-idio-16"
	पूर्ण,
पूर्ण;

module_isa_driver(idio_16_driver, num_idio_16);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES 104-IDIO-16 GPIO driver");
MODULE_LICENSE("GPL v2");
