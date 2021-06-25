<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the ACCES 104-DIO-48E series
 * Copyright (C) 2016 William Breathitt Gray
 *
 * This driver supports the following ACCES devices: 104-DIO-48E and
 * 104-DIO-24E.
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

#घोषणा DIO48E_EXTENT 16
#घोषणा MAX_NUM_DIO48E max_num_isa_dev(DIO48E_EXTENT)

अटल अचिन्हित पूर्णांक base[MAX_NUM_DIO48E];
अटल अचिन्हित पूर्णांक num_dio48e;
module_param_hw_array(base, uपूर्णांक, ioport, &num_dio48e, 0);
MODULE_PARM_DESC(base, "ACCES 104-DIO-48E base addresses");

अटल अचिन्हित पूर्णांक irq[MAX_NUM_DIO48E];
module_param_hw_array(irq, uपूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "ACCES 104-DIO-48E interrupt line numbers");

/**
 * काष्ठा dio48e_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @io_state:	bit I/O state (whether bit is set to input or output)
 * @out_state:	output bits state
 * @control:	Control रेजिस्टरs state
 * @lock:	synchronization lock to prevent I/O race conditions
 * @base:	base port address of the GPIO device
 * @irq_mask:	I/O bits affected by पूर्णांकerrupts
 */
काष्ठा dio48e_gpio अणु
	काष्ठा gpio_chip chip;
	अचिन्हित अक्षर io_state[6];
	अचिन्हित अक्षर out_state[6];
	अचिन्हित अक्षर control[2];
	raw_spinlock_t lock;
	अचिन्हित पूर्णांक base;
	अचिन्हित अक्षर irq_mask;
पूर्ण;

अटल पूर्णांक dio48e_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);

	अगर (dio48egpio->io_state[port] & mask)
		वापस  GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक dio48e_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक io_port = offset / 8;
	स्थिर अचिन्हित पूर्णांक control_port = io_port / 3;
	स्थिर अचिन्हित पूर्णांक control_addr = dio48egpio->base + 3 + control_port * 4;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक control;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	/* Check अगर configuring Port C */
	अगर (io_port == 2 || io_port == 5) अणु
		/* Port C can be configured by nibble */
		अगर (offset % 8 > 3) अणु
			dio48egpio->io_state[io_port] |= 0xF0;
			dio48egpio->control[control_port] |= BIT(3);
		पूर्ण अन्यथा अणु
			dio48egpio->io_state[io_port] |= 0x0F;
			dio48egpio->control[control_port] |= BIT(0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dio48egpio->io_state[io_port] |= 0xFF;
		अगर (io_port == 0 || io_port == 3)
			dio48egpio->control[control_port] |= BIT(4);
		अन्यथा
			dio48egpio->control[control_port] |= BIT(1);
	पूर्ण

	control = BIT(7) | dio48egpio->control[control_port];
	outb(control, control_addr);
	control &= ~BIT(7);
	outb(control, control_addr);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dio48e_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
					पूर्णांक value)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक io_port = offset / 8;
	स्थिर अचिन्हित पूर्णांक control_port = io_port / 3;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक control_addr = dio48egpio->base + 3 + control_port * 4;
	स्थिर अचिन्हित पूर्णांक out_port = (io_port > 2) ? io_port + 1 : io_port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक control;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	/* Check अगर configuring Port C */
	अगर (io_port == 2 || io_port == 5) अणु
		/* Port C can be configured by nibble */
		अगर (offset % 8 > 3) अणु
			dio48egpio->io_state[io_port] &= 0x0F;
			dio48egpio->control[control_port] &= ~BIT(3);
		पूर्ण अन्यथा अणु
			dio48egpio->io_state[io_port] &= 0xF0;
			dio48egpio->control[control_port] &= ~BIT(0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dio48egpio->io_state[io_port] &= 0x00;
		अगर (io_port == 0 || io_port == 3)
			dio48egpio->control[control_port] &= ~BIT(4);
		अन्यथा
			dio48egpio->control[control_port] &= ~BIT(1);
	पूर्ण

	अगर (value)
		dio48egpio->out_state[io_port] |= mask;
	अन्यथा
		dio48egpio->out_state[io_port] &= ~mask;

	control = BIT(7) | dio48egpio->control[control_port];
	outb(control, control_addr);

	outb(dio48egpio->out_state[io_port], dio48egpio->base + out_port);

	control &= ~BIT(7);
	outb(control, control_addr);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dio48e_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक in_port = (port > 2) ? port + 1 : port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक port_state;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	/* ensure that GPIO is set क्रम input */
	अगर (!(dio48egpio->io_state[port] & mask)) अणु
		raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
		वापस -EINVAL;
	पूर्ण

	port_state = inb(dio48egpio->base + in_port);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);

	वापस !!(port_state & mask);
पूर्ण

अटल स्थिर माप_प्रकार ports[] = अणु 0, 1, 2, 4, 5, 6 पूर्ण;

अटल पूर्णांक dio48e_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ port_state;

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		port_addr = dio48egpio->base + ports[offset / 8];
		port_state = inb(port_addr) & gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dio48e_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक out_port = (port > 2) ? port + 1 : port;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	अगर (value)
		dio48egpio->out_state[port] |= mask;
	अन्यथा
		dio48egpio->out_state[port] &= ~mask;

	outb(dio48egpio->out_state[port], dio48egpio->base + out_port);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
पूर्ण

अटल व्योम dio48e_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	माप_प्रकार index;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		index = offset / 8;
		port_addr = dio48egpio->base + ports[index];

		biपंचांगask = biपंचांगap_get_value8(bits, offset) & gpio_mask;

		raw_spin_lock_irqsave(&dio48egpio->lock, flags);

		/* update output state data and set device gpio रेजिस्टर */
		dio48egpio->out_state[index] &= ~gpio_mask;
		dio48egpio->out_state[index] |= biपंचांगask;
		outb(dio48egpio->out_state[index], port_addr);

		raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम dio48e_irq_ack(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम dio48e_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	अचिन्हित दीर्घ flags;

	/* only bit 3 on each respective Port C supports पूर्णांकerrupts */
	अगर (offset != 19 && offset != 43)
		वापस;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	अगर (offset == 19)
		dio48egpio->irq_mask &= ~BIT(0);
	अन्यथा
		dio48egpio->irq_mask &= ~BIT(1);

	अगर (!dio48egpio->irq_mask)
		/* disable पूर्णांकerrupts */
		inb(dio48egpio->base + 0xB);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
पूर्ण

अटल व्योम dio48e_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);
	अचिन्हित दीर्घ flags;

	/* only bit 3 on each respective Port C supports पूर्णांकerrupts */
	अगर (offset != 19 && offset != 43)
		वापस;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	अगर (!dio48egpio->irq_mask) अणु
		/* enable पूर्णांकerrupts */
		outb(0x00, dio48egpio->base + 0xF);
		outb(0x00, dio48egpio->base + 0xB);
	पूर्ण

	अगर (offset == 19)
		dio48egpio->irq_mask |= BIT(0);
	अन्यथा
		dio48egpio->irq_mask |= BIT(1);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
पूर्ण

अटल पूर्णांक dio48e_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	स्थिर अचिन्हित दीर्घ offset = irqd_to_hwirq(data);

	/* only bit 3 on each respective Port C supports पूर्णांकerrupts */
	अगर (offset != 19 && offset != 43)
		वापस -EINVAL;

	अगर (flow_type != IRQ_TYPE_NONE && flow_type != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip dio48e_irqchip = अणु
	.name = "104-dio-48e",
	.irq_ack = dio48e_irq_ack,
	.irq_mask = dio48e_irq_mask,
	.irq_unmask = dio48e_irq_unmask,
	.irq_set_type = dio48e_irq_set_type
पूर्ण;

अटल irqवापस_t dio48e_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = dev_id;
	काष्ठा gpio_chip *स्थिर chip = &dio48egpio->chip;
	स्थिर अचिन्हित दीर्घ irq_mask = dio48egpio->irq_mask;
	अचिन्हित दीर्घ gpio;

	क्रम_each_set_bit(gpio, &irq_mask, 2)
		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य,
			19 + gpio*24));

	raw_spin_lock(&dio48egpio->lock);

	outb(0x00, dio48egpio->base + 0xF);

	raw_spin_unlock(&dio48egpio->lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा DIO48E_NGPIO 48
अटल स्थिर अक्षर *dio48e_names[DIO48E_NGPIO] = अणु
	"PPI Group 0 Port A 0", "PPI Group 0 Port A 1", "PPI Group 0 Port A 2",
	"PPI Group 0 Port A 3", "PPI Group 0 Port A 4", "PPI Group 0 Port A 5",
	"PPI Group 0 Port A 6", "PPI Group 0 Port A 7",	"PPI Group 0 Port B 0",
	"PPI Group 0 Port B 1", "PPI Group 0 Port B 2", "PPI Group 0 Port B 3",
	"PPI Group 0 Port B 4", "PPI Group 0 Port B 5", "PPI Group 0 Port B 6",
	"PPI Group 0 Port B 7", "PPI Group 0 Port C 0", "PPI Group 0 Port C 1",
	"PPI Group 0 Port C 2", "PPI Group 0 Port C 3", "PPI Group 0 Port C 4",
	"PPI Group 0 Port C 5", "PPI Group 0 Port C 6", "PPI Group 0 Port C 7",
	"PPI Group 1 Port A 0", "PPI Group 1 Port A 1", "PPI Group 1 Port A 2",
	"PPI Group 1 Port A 3", "PPI Group 1 Port A 4", "PPI Group 1 Port A 5",
	"PPI Group 1 Port A 6", "PPI Group 1 Port A 7",	"PPI Group 1 Port B 0",
	"PPI Group 1 Port B 1", "PPI Group 1 Port B 2", "PPI Group 1 Port B 3",
	"PPI Group 1 Port B 4", "PPI Group 1 Port B 5", "PPI Group 1 Port B 6",
	"PPI Group 1 Port B 7", "PPI Group 1 Port C 0", "PPI Group 1 Port C 1",
	"PPI Group 1 Port C 2", "PPI Group 1 Port C 3", "PPI Group 1 Port C 4",
	"PPI Group 1 Port C 5", "PPI Group 1 Port C 6", "PPI Group 1 Port C 7"
पूर्ण;

अटल पूर्णांक dio48e_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा dio48e_gpio *स्थिर dio48egpio = gpiochip_get_data(gc);

	/* Disable IRQ by शेष */
	inb(dio48egpio->base + 0xB);

	वापस 0;
पूर्ण

अटल पूर्णांक dio48e_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा dio48e_gpio *dio48egpio;
	स्थिर अक्षर *स्थिर name = dev_name(dev);
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	dio48egpio = devm_kzalloc(dev, माप(*dio48egpio), GFP_KERNEL);
	अगर (!dio48egpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], DIO48E_EXTENT, name)) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + DIO48E_EXTENT);
		वापस -EBUSY;
	पूर्ण

	dio48egpio->chip.label = name;
	dio48egpio->chip.parent = dev;
	dio48egpio->chip.owner = THIS_MODULE;
	dio48egpio->chip.base = -1;
	dio48egpio->chip.ngpio = DIO48E_NGPIO;
	dio48egpio->chip.names = dio48e_names;
	dio48egpio->chip.get_direction = dio48e_gpio_get_direction;
	dio48egpio->chip.direction_input = dio48e_gpio_direction_input;
	dio48egpio->chip.direction_output = dio48e_gpio_direction_output;
	dio48egpio->chip.get = dio48e_gpio_get;
	dio48egpio->chip.get_multiple = dio48e_gpio_get_multiple;
	dio48egpio->chip.set = dio48e_gpio_set;
	dio48egpio->chip.set_multiple = dio48e_gpio_set_multiple;
	dio48egpio->base = base[id];

	girq = &dio48egpio->chip.irq;
	girq->chip = &dio48e_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;
	girq->init_hw = dio48e_irq_init_hw;

	raw_spin_lock_init(&dio48egpio->lock);

	/* initialize all GPIO as output */
	outb(0x80, base[id] + 3);
	outb(0x00, base[id]);
	outb(0x00, base[id] + 1);
	outb(0x00, base[id] + 2);
	outb(0x00, base[id] + 3);
	outb(0x80, base[id] + 7);
	outb(0x00, base[id] + 4);
	outb(0x00, base[id] + 5);
	outb(0x00, base[id] + 6);
	outb(0x00, base[id] + 7);

	err = devm_gpiochip_add_data(dev, &dio48egpio->chip, dio48egpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, irq[id], dio48e_irq_handler, 0, name,
		dio48egpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा isa_driver dio48e_driver = अणु
	.probe = dio48e_probe,
	.driver = अणु
		.name = "104-dio-48e"
	पूर्ण,
पूर्ण;
module_isa_driver(dio48e_driver, num_dio48e);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES 104-DIO-48E GPIO driver");
MODULE_LICENSE("GPL v2");
