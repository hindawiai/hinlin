<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the WinSystems WS16C48
 * Copyright (C) 2016 William Breathitt Gray
 */
#समावेश <linux/biपंचांगap.h>
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

#घोषणा WS16C48_EXTENT 16
#घोषणा MAX_NUM_WS16C48 max_num_isa_dev(WS16C48_EXTENT)

अटल अचिन्हित पूर्णांक base[MAX_NUM_WS16C48];
अटल अचिन्हित पूर्णांक num_ws16c48;
module_param_hw_array(base, uपूर्णांक, ioport, &num_ws16c48, 0);
MODULE_PARM_DESC(base, "WinSystems WS16C48 base addresses");

अटल अचिन्हित पूर्णांक irq[MAX_NUM_WS16C48];
module_param_hw_array(irq, uपूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "WinSystems WS16C48 interrupt line numbers");

/**
 * काष्ठा ws16c48_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @io_state:	bit I/O state (whether bit is set to input or output)
 * @out_state:	output bits state
 * @lock:	synchronization lock to prevent I/O race conditions
 * @irq_mask:	I/O bits affected by पूर्णांकerrupts
 * @flow_mask:	IRQ flow type mask क्रम the respective I/O bits
 * @base:	base port address of the GPIO device
 */
काष्ठा ws16c48_gpio अणु
	काष्ठा gpio_chip chip;
	अचिन्हित अक्षर io_state[6];
	अचिन्हित अक्षर out_state[6];
	raw_spinlock_t lock;
	अचिन्हित दीर्घ irq_mask;
	अचिन्हित दीर्घ flow_mask;
	अचिन्हित base;
पूर्ण;

अटल पूर्णांक ws16c48_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);

	अगर (ws16c48gpio->io_state[port] & mask)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक ws16c48_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	ws16c48gpio->io_state[port] |= mask;
	ws16c48gpio->out_state[port] &= ~mask;
	outb(ws16c48gpio->out_state[port], ws16c48gpio->base + port);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ws16c48_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	ws16c48gpio->io_state[port] &= ~mask;
	अगर (value)
		ws16c48gpio->out_state[port] |= mask;
	अन्यथा
		ws16c48gpio->out_state[port] &= ~mask;
	outb(ws16c48gpio->out_state[port], ws16c48gpio->base + port);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ws16c48_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;
	अचिन्हित port_state;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	/* ensure that GPIO is set क्रम input */
	अगर (!(ws16c48gpio->io_state[port] & mask)) अणु
		raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
		वापस -EINVAL;
	पूर्ण

	port_state = inb(ws16c48gpio->base + port);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);

	वापस !!(port_state & mask);
पूर्ण

अटल पूर्णांक ws16c48_gpio_get_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ port_state;

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, chip->ngpio) अणु
		port_addr = ws16c48gpio->base + offset / 8;
		port_state = inb(port_addr) & gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ws16c48_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	/* ensure that GPIO is set क्रम output */
	अगर (ws16c48gpio->io_state[port] & mask) अणु
		raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
		वापस;
	पूर्ण

	अगर (value)
		ws16c48gpio->out_state[port] |= mask;
	अन्यथा
		ws16c48gpio->out_state[port] &= ~mask;
	outb(ws16c48gpio->out_state[port], ws16c48gpio->base + port);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
पूर्ण

अटल व्योम ws16c48_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	माप_प्रकार index;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_clump8(offset, gpio_mask, mask, chip->ngpio) अणु
		index = offset / 8;
		port_addr = ws16c48gpio->base + index;

		/* mask out GPIO configured क्रम input */
		gpio_mask &= ~ws16c48gpio->io_state[index];
		biपंचांगask = biपंचांगap_get_value8(bits, offset) & gpio_mask;

		raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

		/* update output state data and set device gpio रेजिस्टर */
		ws16c48gpio->out_state[index] &= ~gpio_mask;
		ws16c48gpio->out_state[index] |= biपंचांगask;
		outb(ws16c48gpio->out_state[index], port_addr);

		raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम ws16c48_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	स्थिर अचिन्हित port = offset / 8;
	स्थिर अचिन्हित mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;
	अचिन्हित port_state;

	/* only the first 3 ports support पूर्णांकerrupts */
	अगर (port > 2)
		वापस;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	port_state = ws16c48gpio->irq_mask >> (8*port);

	outb(0x80, ws16c48gpio->base + 7);
	outb(port_state & ~mask, ws16c48gpio->base + 8 + port);
	outb(port_state | mask, ws16c48gpio->base + 8 + port);
	outb(0xC0, ws16c48gpio->base + 7);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
पूर्ण

अटल व्योम ws16c48_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	स्थिर अचिन्हित दीर्घ mask = BIT(offset);
	स्थिर अचिन्हित port = offset / 8;
	अचिन्हित दीर्घ flags;

	/* only the first 3 ports support पूर्णांकerrupts */
	अगर (port > 2)
		वापस;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	ws16c48gpio->irq_mask &= ~mask;

	outb(0x80, ws16c48gpio->base + 7);
	outb(ws16c48gpio->irq_mask >> (8*port), ws16c48gpio->base + 8 + port);
	outb(0xC0, ws16c48gpio->base + 7);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
पूर्ण

अटल व्योम ws16c48_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	स्थिर अचिन्हित दीर्घ mask = BIT(offset);
	स्थिर अचिन्हित port = offset / 8;
	अचिन्हित दीर्घ flags;

	/* only the first 3 ports support पूर्णांकerrupts */
	अगर (port > 2)
		वापस;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	ws16c48gpio->irq_mask |= mask;

	outb(0x80, ws16c48gpio->base + 7);
	outb(ws16c48gpio->irq_mask >> (8*port), ws16c48gpio->base + 8 + port);
	outb(0xC0, ws16c48gpio->base + 7);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
पूर्ण

अटल पूर्णांक ws16c48_irq_set_type(काष्ठा irq_data *data, अचिन्हित flow_type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	स्थिर अचिन्हित दीर्घ mask = BIT(offset);
	स्थिर अचिन्हित port = offset / 8;
	अचिन्हित दीर्घ flags;

	/* only the first 3 ports support पूर्णांकerrupts */
	अगर (port > 2)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

	चयन (flow_type) अणु
	हाल IRQ_TYPE_NONE:
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		ws16c48gpio->flow_mask |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		ws16c48gpio->flow_mask &= ~mask;
		अवरोध;
	शेष:
		raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);
		वापस -EINVAL;
	पूर्ण

	outb(0x40, ws16c48gpio->base + 7);
	outb(ws16c48gpio->flow_mask >> (8*port), ws16c48gpio->base + 8 + port);
	outb(0xC0, ws16c48gpio->base + 7);

	raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ws16c48_irqchip = अणु
	.name = "ws16c48",
	.irq_ack = ws16c48_irq_ack,
	.irq_mask = ws16c48_irq_mask,
	.irq_unmask = ws16c48_irq_unmask,
	.irq_set_type = ws16c48_irq_set_type
पूर्ण;

अटल irqवापस_t ws16c48_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = dev_id;
	काष्ठा gpio_chip *स्थिर chip = &ws16c48gpio->chip;
	अचिन्हित दीर्घ पूर्णांक_pending;
	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ पूर्णांक_id;
	अचिन्हित दीर्घ gpio;

	पूर्णांक_pending = inb(ws16c48gpio->base + 6) & 0x7;
	अगर (!पूर्णांक_pending)
		वापस IRQ_NONE;

	/* loop until all pending पूर्णांकerrupts are handled */
	करो अणु
		क्रम_each_set_bit(port, &पूर्णांक_pending, 3) अणु
			पूर्णांक_id = inb(ws16c48gpio->base + 8 + port);
			क्रम_each_set_bit(gpio, &पूर्णांक_id, 8)
				generic_handle_irq(irq_find_mapping(
					chip->irq.करोमुख्य, gpio + 8*port));
		पूर्ण

		पूर्णांक_pending = inb(ws16c48gpio->base + 6) & 0x7;
	पूर्ण जबतक (पूर्णांक_pending);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा WS16C48_NGPIO 48
अटल स्थिर अक्षर *ws16c48_names[WS16C48_NGPIO] = अणु
	"Port 0 Bit 0", "Port 0 Bit 1", "Port 0 Bit 2", "Port 0 Bit 3",
	"Port 0 Bit 4", "Port 0 Bit 5", "Port 0 Bit 6", "Port 0 Bit 7",
	"Port 1 Bit 0", "Port 1 Bit 1", "Port 1 Bit 2", "Port 1 Bit 3",
	"Port 1 Bit 4", "Port 1 Bit 5", "Port 1 Bit 6", "Port 1 Bit 7",
	"Port 2 Bit 0", "Port 2 Bit 1", "Port 2 Bit 2", "Port 2 Bit 3",
	"Port 2 Bit 4", "Port 2 Bit 5", "Port 2 Bit 6", "Port 2 Bit 7",
	"Port 3 Bit 0", "Port 3 Bit 1", "Port 3 Bit 2", "Port 3 Bit 3",
	"Port 3 Bit 4", "Port 3 Bit 5", "Port 3 Bit 6", "Port 3 Bit 7",
	"Port 4 Bit 0", "Port 4 Bit 1", "Port 4 Bit 2", "Port 4 Bit 3",
	"Port 4 Bit 4", "Port 4 Bit 5", "Port 4 Bit 6", "Port 4 Bit 7",
	"Port 5 Bit 0", "Port 5 Bit 1", "Port 5 Bit 2", "Port 5 Bit 3",
	"Port 5 Bit 4", "Port 5 Bit 5", "Port 5 Bit 6", "Port 5 Bit 7"
पूर्ण;

अटल पूर्णांक ws16c48_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा ws16c48_gpio *स्थिर ws16c48gpio = gpiochip_get_data(gc);

	/* Disable IRQ by शेष */
	outb(0x80, ws16c48gpio->base + 7);
	outb(0, ws16c48gpio->base + 8);
	outb(0, ws16c48gpio->base + 9);
	outb(0, ws16c48gpio->base + 10);
	outb(0xC0, ws16c48gpio->base + 7);

	वापस 0;
पूर्ण

अटल पूर्णांक ws16c48_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा ws16c48_gpio *ws16c48gpio;
	स्थिर अक्षर *स्थिर name = dev_name(dev);
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	ws16c48gpio = devm_kzalloc(dev, माप(*ws16c48gpio), GFP_KERNEL);
	अगर (!ws16c48gpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], WS16C48_EXTENT, name)) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + WS16C48_EXTENT);
		वापस -EBUSY;
	पूर्ण

	ws16c48gpio->chip.label = name;
	ws16c48gpio->chip.parent = dev;
	ws16c48gpio->chip.owner = THIS_MODULE;
	ws16c48gpio->chip.base = -1;
	ws16c48gpio->chip.ngpio = WS16C48_NGPIO;
	ws16c48gpio->chip.names = ws16c48_names;
	ws16c48gpio->chip.get_direction = ws16c48_gpio_get_direction;
	ws16c48gpio->chip.direction_input = ws16c48_gpio_direction_input;
	ws16c48gpio->chip.direction_output = ws16c48_gpio_direction_output;
	ws16c48gpio->chip.get = ws16c48_gpio_get;
	ws16c48gpio->chip.get_multiple = ws16c48_gpio_get_multiple;
	ws16c48gpio->chip.set = ws16c48_gpio_set;
	ws16c48gpio->chip.set_multiple = ws16c48_gpio_set_multiple;
	ws16c48gpio->base = base[id];

	girq = &ws16c48gpio->chip.irq;
	girq->chip = &ws16c48_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;
	girq->init_hw = ws16c48_irq_init_hw;

	raw_spin_lock_init(&ws16c48gpio->lock);

	err = devm_gpiochip_add_data(dev, &ws16c48gpio->chip, ws16c48gpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, irq[id], ws16c48_irq_handler, IRQF_SHARED,
		name, ws16c48gpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा isa_driver ws16c48_driver = अणु
	.probe = ws16c48_probe,
	.driver = अणु
		.name = "ws16c48"
	पूर्ण,
पूर्ण;

module_isa_driver(ws16c48_driver, num_ws16c48);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("WinSystems WS16C48 GPIO driver");
MODULE_LICENSE("GPL v2");
