<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the ACCES 104-IDI-48 family
 * Copyright (C) 2015 William Breathitt Gray
 *
 * This driver supports the following ACCES devices: 104-IDI-48A,
 * 104-IDI-48AC, 104-IDI-48B, and 104-IDI-48BC.
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

#घोषणा IDI_48_EXTENT 8
#घोषणा MAX_NUM_IDI_48 max_num_isa_dev(IDI_48_EXTENT)

अटल अचिन्हित पूर्णांक base[MAX_NUM_IDI_48];
अटल अचिन्हित पूर्णांक num_idi_48;
module_param_hw_array(base, uपूर्णांक, ioport, &num_idi_48, 0);
MODULE_PARM_DESC(base, "ACCES 104-IDI-48 base addresses");

अटल अचिन्हित पूर्णांक irq[MAX_NUM_IDI_48];
module_param_hw_array(irq, uपूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "ACCES 104-IDI-48 interrupt line numbers");

/**
 * काष्ठा idi_48_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @lock:	synchronization lock to prevent I/O race conditions
 * @ack_lock:	synchronization lock to prevent IRQ handler race conditions
 * @irq_mask:	input bits affected by पूर्णांकerrupts
 * @base:	base port address of the GPIO device
 * @cos_enb:	Change-Of-State IRQ enable boundaries mask
 */
काष्ठा idi_48_gpio अणु
	काष्ठा gpio_chip chip;
	raw_spinlock_t lock;
	spinlock_t ack_lock;
	अचिन्हित अक्षर irq_mask[6];
	अचिन्हित base;
	अचिन्हित अक्षर cos_enb;
पूर्ण;

अटल पूर्णांक idi_48_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक idi_48_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक idi_48_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा idi_48_gpio *स्थिर idi48gpio = gpiochip_get_data(chip);
	अचिन्हित i;
	अटल स्थिर अचिन्हित पूर्णांक रेजिस्टर_offset[6] = अणु 0, 1, 2, 4, 5, 6 पूर्ण;
	अचिन्हित base_offset;
	अचिन्हित mask;

	क्रम (i = 0; i < 48; i += 8)
		अगर (offset < i + 8) अणु
			base_offset = रेजिस्टर_offset[i / 8];
			mask = BIT(offset - i);

			वापस !!(inb(idi48gpio->base + base_offset) & mask);
		पूर्ण

	/* The following line should never execute since offset < 48 */
	वापस 0;
पूर्ण

अटल पूर्णांक idi_48_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idi_48_gpio *स्थिर idi48gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	अटल स्थिर माप_प्रकार ports[] = अणु 0, 1, 2, 4, 5, 6 पूर्ण;
	अचिन्हित पूर्णांक port_addr;
	अचिन्हित दीर्घ port_state;

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		port_addr = idi48gpio->base + ports[offset / 8];
		port_state = inb(port_addr) & gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idi_48_irq_ack(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम idi_48_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा idi_48_gpio *स्थिर idi48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित offset = irqd_to_hwirq(data);
	अचिन्हित i;
	अचिन्हित mask;
	अचिन्हित boundary;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < 48; i += 8)
		अगर (offset < i + 8) अणु
			mask = BIT(offset - i);
			boundary = i / 8;

			idi48gpio->irq_mask[boundary] &= ~mask;

			अगर (!idi48gpio->irq_mask[boundary]) अणु
				idi48gpio->cos_enb &= ~BIT(boundary);

				raw_spin_lock_irqsave(&idi48gpio->lock, flags);

				outb(idi48gpio->cos_enb, idi48gpio->base + 7);

				raw_spin_unlock_irqrestore(&idi48gpio->lock, flags);
			पूर्ण

			वापस;
		पूर्ण
पूर्ण

अटल व्योम idi_48_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा idi_48_gpio *स्थिर idi48gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित offset = irqd_to_hwirq(data);
	अचिन्हित i;
	अचिन्हित mask;
	अचिन्हित boundary;
	अचिन्हित prev_irq_mask;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < 48; i += 8)
		अगर (offset < i + 8) अणु
			mask = BIT(offset - i);
			boundary = i / 8;
			prev_irq_mask = idi48gpio->irq_mask[boundary];

			idi48gpio->irq_mask[boundary] |= mask;

			अगर (!prev_irq_mask) अणु
				idi48gpio->cos_enb |= BIT(boundary);

				raw_spin_lock_irqsave(&idi48gpio->lock, flags);

				outb(idi48gpio->cos_enb, idi48gpio->base + 7);

				raw_spin_unlock_irqrestore(&idi48gpio->lock, flags);
			पूर्ण

			वापस;
		पूर्ण
पूर्ण

अटल पूर्णांक idi_48_irq_set_type(काष्ठा irq_data *data, अचिन्हित flow_type)
अणु
	/* The only valid irq types are none and both-edges */
	अगर (flow_type != IRQ_TYPE_NONE &&
		(flow_type & IRQ_TYPE_EDGE_BOTH) != IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip idi_48_irqchip = अणु
	.name = "104-idi-48",
	.irq_ack = idi_48_irq_ack,
	.irq_mask = idi_48_irq_mask,
	.irq_unmask = idi_48_irq_unmask,
	.irq_set_type = idi_48_irq_set_type
पूर्ण;

अटल irqवापस_t idi_48_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idi_48_gpio *स्थिर idi48gpio = dev_id;
	अचिन्हित दीर्घ cos_status;
	अचिन्हित दीर्घ boundary;
	अचिन्हित दीर्घ irq_mask;
	अचिन्हित दीर्घ bit_num;
	अचिन्हित दीर्घ gpio;
	काष्ठा gpio_chip *स्थिर chip = &idi48gpio->chip;

	spin_lock(&idi48gpio->ack_lock);

	raw_spin_lock(&idi48gpio->lock);

	cos_status = inb(idi48gpio->base + 7);

	raw_spin_unlock(&idi48gpio->lock);

	/* IRQ Status (bit 6) is active low (0 = IRQ generated by device) */
	अगर (cos_status & BIT(6)) अणु
		spin_unlock(&idi48gpio->ack_lock);
		वापस IRQ_NONE;
	पूर्ण

	/* Bit 0-5 indicate which Change-Of-State boundary triggered the IRQ */
	cos_status &= 0x3F;

	क्रम_each_set_bit(boundary, &cos_status, 6) अणु
		irq_mask = idi48gpio->irq_mask[boundary];

		क्रम_each_set_bit(bit_num, &irq_mask, 8) अणु
			gpio = bit_num + boundary * 8;

			generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य,
				gpio));
		पूर्ण
	पूर्ण

	spin_unlock(&idi48gpio->ack_lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा IDI48_NGPIO 48
अटल स्थिर अक्षर *idi48_names[IDI48_NGPIO] = अणु
	"Bit 0 A", "Bit 1 A", "Bit 2 A", "Bit 3 A", "Bit 4 A", "Bit 5 A",
	"Bit 6 A", "Bit 7 A", "Bit 8 A", "Bit 9 A", "Bit 10 A", "Bit 11 A",
	"Bit 12 A", "Bit 13 A", "Bit 14 A", "Bit 15 A",	"Bit 16 A", "Bit 17 A",
	"Bit 18 A", "Bit 19 A", "Bit 20 A", "Bit 21 A", "Bit 22 A", "Bit 23 A",
	"Bit 0 B", "Bit 1 B", "Bit 2 B", "Bit 3 B", "Bit 4 B", "Bit 5 B",
	"Bit 6 B", "Bit 7 B", "Bit 8 B", "Bit 9 B", "Bit 10 B", "Bit 11 B",
	"Bit 12 B", "Bit 13 B", "Bit 14 B", "Bit 15 B",	"Bit 16 B", "Bit 17 B",
	"Bit 18 B", "Bit 19 B", "Bit 20 B", "Bit 21 B", "Bit 22 B", "Bit 23 B"
पूर्ण;

अटल पूर्णांक idi_48_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा idi_48_gpio *स्थिर idi48gpio = gpiochip_get_data(gc);

	/* Disable IRQ by शेष */
	outb(0, idi48gpio->base + 7);
	inb(idi48gpio->base + 7);

	वापस 0;
पूर्ण

अटल पूर्णांक idi_48_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा idi_48_gpio *idi48gpio;
	स्थिर अक्षर *स्थिर name = dev_name(dev);
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	idi48gpio = devm_kzalloc(dev, माप(*idi48gpio), GFP_KERNEL);
	अगर (!idi48gpio)
		वापस -ENOMEM;

	अगर (!devm_request_region(dev, base[id], IDI_48_EXTENT, name)) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + IDI_48_EXTENT);
		वापस -EBUSY;
	पूर्ण

	idi48gpio->chip.label = name;
	idi48gpio->chip.parent = dev;
	idi48gpio->chip.owner = THIS_MODULE;
	idi48gpio->chip.base = -1;
	idi48gpio->chip.ngpio = IDI48_NGPIO;
	idi48gpio->chip.names = idi48_names;
	idi48gpio->chip.get_direction = idi_48_gpio_get_direction;
	idi48gpio->chip.direction_input = idi_48_gpio_direction_input;
	idi48gpio->chip.get = idi_48_gpio_get;
	idi48gpio->chip.get_multiple = idi_48_gpio_get_multiple;
	idi48gpio->base = base[id];

	girq = &idi48gpio->chip.irq;
	girq->chip = &idi_48_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;
	girq->init_hw = idi_48_irq_init_hw;

	raw_spin_lock_init(&idi48gpio->lock);
	spin_lock_init(&idi48gpio->ack_lock);

	err = devm_gpiochip_add_data(dev, &idi48gpio->chip, idi48gpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, irq[id], idi_48_irq_handler, IRQF_SHARED,
		name, idi48gpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा isa_driver idi_48_driver = अणु
	.probe = idi_48_probe,
	.driver = अणु
		.name = "104-idi-48"
	पूर्ण,
पूर्ण;
module_isa_driver(idi_48_driver, num_idi_48);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES 104-IDI-48 GPIO driver");
MODULE_LICENSE("GPL v2");
