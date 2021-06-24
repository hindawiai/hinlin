<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the Diamond Systems GPIO-MM
 * Copyright (C) 2016 William Breathitt Gray
 *
 * This driver supports the following Diamond Systems devices: GPIO-MM and
 * GPIO-MM-12.
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>

#घोषणा GPIOMM_EXTENT 8
#घोषणा MAX_NUM_GPIOMM max_num_isa_dev(GPIOMM_EXTENT)

अटल अचिन्हित पूर्णांक base[MAX_NUM_GPIOMM];
अटल अचिन्हित पूर्णांक num_gpiomm;
module_param_hw_array(base, uपूर्णांक, ioport, &num_gpiomm, 0);
MODULE_PARM_DESC(base, "Diamond Systems GPIO-MM base addresses");

/**
 * काष्ठा gpiomm_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @io_state:	bit I/O state (whether bit is set to input or output)
 * @out_state:	output bits state
 * @control:	Control रेजिस्टरs state
 * @lock:	synchronization lock to prevent I/O race conditions
 * @base:	base port address of the GPIO device
 */
काष्ठा gpiomm_gpio अणु
	काष्ठा gpio_chip chip;
	अचिन्हित अक्षर io_state[6];
	अचिन्हित अक्षर out_state[6];
	अचिन्हित अक्षर control[2];
	spinlock_t lock;
	अचिन्हित पूर्णांक base;
पूर्ण;

अटल पूर्णांक gpiomm_gpio_get_direction(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);

	अगर (gpiommgpio->io_state[port] & mask)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक gpiomm_gpio_direction_input(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक io_port = offset / 8;
	स्थिर अचिन्हित पूर्णांक control_port = io_port / 3;
	स्थिर अचिन्हित पूर्णांक control_addr = gpiommgpio->base + 3 + control_port*4;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक control;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	/* Check अगर configuring Port C */
	अगर (io_port == 2 || io_port == 5) अणु
		/* Port C can be configured by nibble */
		अगर (offset % 8 > 3) अणु
			gpiommgpio->io_state[io_port] |= 0xF0;
			gpiommgpio->control[control_port] |= BIT(3);
		पूर्ण अन्यथा अणु
			gpiommgpio->io_state[io_port] |= 0x0F;
			gpiommgpio->control[control_port] |= BIT(0);
		पूर्ण
	पूर्ण अन्यथा अणु
		gpiommgpio->io_state[io_port] |= 0xFF;
		अगर (io_port == 0 || io_port == 3)
			gpiommgpio->control[control_port] |= BIT(4);
		अन्यथा
			gpiommgpio->control[control_port] |= BIT(1);
	पूर्ण

	control = BIT(7) | gpiommgpio->control[control_port];
	outb(control, control_addr);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gpiomm_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक io_port = offset / 8;
	स्थिर अचिन्हित पूर्णांक control_port = io_port / 3;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक control_addr = gpiommgpio->base + 3 + control_port*4;
	स्थिर अचिन्हित पूर्णांक out_port = (io_port > 2) ? io_port + 1 : io_port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक control;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	/* Check अगर configuring Port C */
	अगर (io_port == 2 || io_port == 5) अणु
		/* Port C can be configured by nibble */
		अगर (offset % 8 > 3) अणु
			gpiommgpio->io_state[io_port] &= 0x0F;
			gpiommgpio->control[control_port] &= ~BIT(3);
		पूर्ण अन्यथा अणु
			gpiommgpio->io_state[io_port] &= 0xF0;
			gpiommgpio->control[control_port] &= ~BIT(0);
		पूर्ण
	पूर्ण अन्यथा अणु
		gpiommgpio->io_state[io_port] &= 0x00;
		अगर (io_port == 0 || io_port == 3)
			gpiommgpio->control[control_port] &= ~BIT(4);
		अन्यथा
			gpiommgpio->control[control_port] &= ~BIT(1);
	पूर्ण

	अगर (value)
		gpiommgpio->out_state[io_port] |= mask;
	अन्यथा
		gpiommgpio->out_state[io_port] &= ~mask;

	control = BIT(7) | gpiommgpio->control[control_port];
	outb(control, control_addr);

	outb(gpiommgpio->out_state[io_port], gpiommgpio->base + out_port);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gpiomm_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक in_port = (port > 2) ? port + 1 : port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक port_state;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	/* ensure that GPIO is set क्रम input */
	अगर (!(gpiommgpio->io_state[port] & mask)) अणु
		spin_unlock_irqrestore(&gpiommgpio->lock, flags);
		वापस -EINVAL;
	पूर्ण

	port_state = inb(gpiommgpio->base + in_port);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);

	वापस !!(port_state & mask);
पूर्ण

अटल स्थिर माप_प्रकार ports[] = अणु 0, 1, 2, 4, 5, 6 पूर्ण;

अटल पूर्णांक gpiomm_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ port_state;

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		port_addr = gpiommgpio->base + ports[offset / 8];
		port_state = inb(port_addr) & gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpiomm_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
	पूर्णांक value)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित पूर्णांक port = offset / 8;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	स्थिर अचिन्हित पूर्णांक out_port = (port > 2) ? port + 1 : port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	अगर (value)
		gpiommgpio->out_state[port] |= mask;
	अन्यथा
		gpiommgpio->out_state[port] &= ~mask;

	outb(gpiommgpio->out_state[port], gpiommgpio->base + out_port);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);
पूर्ण

अटल व्योम gpiomm_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpiomm_gpio *स्थिर gpiommgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	माप_प्रकार index;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		index = offset / 8;
		port_addr = gpiommgpio->base + ports[index];

		biपंचांगask = biपंचांगap_get_value8(bits, offset) & gpio_mask;

		spin_lock_irqsave(&gpiommgpio->lock, flags);

		/* update output state data and set device gpio रेजिस्टर */
		gpiommgpio->out_state[index] &= ~gpio_mask;
		gpiommgpio->out_state[index] |= biपंचांगask;
		outb(gpiommgpio->out_state[index], port_addr);

		spin_unlock_irqrestore(&gpiommgpio->lock, flags);
	पूर्ण
पूर्ण

#घोषणा GPIOMM_NGPIO 48
अटल स्थिर अक्षर *gpiomm_names[GPIOMM_NGPIO] = अणु
	"Port 1A0", "Port 1A1", "Port 1A2", "Port 1A3", "Port 1A4", "Port 1A5",
	"Port 1A6", "Port 1A7", "Port 1B0", "Port 1B1", "Port 1B2", "Port 1B3",
	"Port 1B4", "Port 1B5", "Port 1B6", "Port 1B7", "Port 1C0", "Port 1C1",
	"Port 1C2", "Port 1C3", "Port 1C4", "Port 1C5", "Port 1C6", "Port 1C7",
	"Port 2A0", "Port 2A1", "Port 2A2", "Port 2A3", "Port 2A4", "Port 2A5",
	"Port 2A6", "Port 2A7", "Port 2B0", "Port 2B1", "Port 2B2", "Port 2B3",
	"Port 2B4", "Port 2B5", "Port 2B6", "Port 2B7", "Port 2C0", "Port 2C1",
	"Port 2C2", "Port 2C3", "Port 2C4", "Port 2C5", "Port 2C6", "Port 2C7",
पूर्ण;

अटल पूर्णांक gpiomm_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा gpiomm_gpio *gpiommgpio;
	स्थिर अक्षर *स्थिर name = dev_name(dev);
	पूर्णांक err;

	gpiommgpio = devm_kzalloc(dev, माप(*gpiommgpio), GFP_KERNEL);
	अगर (!gpiommgpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], GPIOMM_EXTENT, name)) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + GPIOMM_EXTENT);
		वापस -EBUSY;
	पूर्ण

	gpiommgpio->chip.label = name;
	gpiommgpio->chip.parent = dev;
	gpiommgpio->chip.owner = THIS_MODULE;
	gpiommgpio->chip.base = -1;
	gpiommgpio->chip.ngpio = GPIOMM_NGPIO;
	gpiommgpio->chip.names = gpiomm_names;
	gpiommgpio->chip.get_direction = gpiomm_gpio_get_direction;
	gpiommgpio->chip.direction_input = gpiomm_gpio_direction_input;
	gpiommgpio->chip.direction_output = gpiomm_gpio_direction_output;
	gpiommgpio->chip.get = gpiomm_gpio_get;
	gpiommgpio->chip.get_multiple = gpiomm_gpio_get_multiple;
	gpiommgpio->chip.set = gpiomm_gpio_set;
	gpiommgpio->chip.set_multiple = gpiomm_gpio_set_multiple;
	gpiommgpio->base = base[id];

	spin_lock_init(&gpiommgpio->lock);

	err = devm_gpiochip_add_data(dev, &gpiommgpio->chip, gpiommgpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	/* initialize all GPIO as output */
	outb(0x80, base[id] + 3);
	outb(0x00, base[id]);
	outb(0x00, base[id] + 1);
	outb(0x00, base[id] + 2);
	outb(0x80, base[id] + 7);
	outb(0x00, base[id] + 4);
	outb(0x00, base[id] + 5);
	outb(0x00, base[id] + 6);

	वापस 0;
पूर्ण

अटल काष्ठा isa_driver gpiomm_driver = अणु
	.probe = gpiomm_probe,
	.driver = अणु
		.name = "gpio-mm"
	पूर्ण,
पूर्ण;

module_isa_driver(gpiomm_driver, num_gpiomm);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("Diamond Systems GPIO-MM GPIO driver");
MODULE_LICENSE("GPL v2");
