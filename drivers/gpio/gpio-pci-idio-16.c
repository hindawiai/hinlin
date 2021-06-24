<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the ACCES PCI-IDIO-16
 * Copyright (C) 2017 William Breathitt Gray
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/**
 * काष्ठा idio_16_gpio_reg - GPIO device रेजिस्टरs काष्ठाure
 * @out0_7:	Read: FET Drive Outमाला_दो 0-7
 *		Write: FET Drive Outमाला_दो 0-7
 * @in0_7:	Read: Isolated Inमाला_दो 0-7
 *		Write: Clear Interrupt
 * @irq_ctl:	Read: Enable IRQ
 *		Write: Disable IRQ
 * @filter_ctl:	Read: Activate Input Filters 0-15
 *		Write: Deactivate Input Filters 0-15
 * @out8_15:	Read: FET Drive Outमाला_दो 8-15
 *		Write: FET Drive Outमाला_दो 8-15
 * @in8_15:	Read: Isolated Inमाला_दो 8-15
 *		Write: Unused
 * @irq_status:	Read: Interrupt status
 *		Write: Unused
 */
काष्ठा idio_16_gpio_reg अणु
	u8 out0_7;
	u8 in0_7;
	u8 irq_ctl;
	u8 filter_ctl;
	u8 out8_15;
	u8 in8_15;
	u8 irq_status;
पूर्ण;

/**
 * काष्ठा idio_16_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @lock:	synchronization lock to prevent I/O race conditions
 * @reg:	I/O address offset क्रम the GPIO device रेजिस्टरs
 * @irq_mask:	I/O bits affected by पूर्णांकerrupts
 */
काष्ठा idio_16_gpio अणु
	काष्ठा gpio_chip chip;
	raw_spinlock_t lock;
	काष्ठा idio_16_gpio_reg __iomem *reg;
	अचिन्हित दीर्घ irq_mask;
पूर्ण;

अटल पूर्णांक idio_16_gpio_get_direction(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	अगर (offset > 15)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक idio_16_gpio_direction_input(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	chip->set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ mask = BIT(offset);

	अगर (offset < 8)
		वापस !!(ioपढ़ो8(&idio16gpio->reg->out0_7) & mask);

	अगर (offset < 16)
		वापस !!(ioपढ़ो8(&idio16gpio->reg->out8_15) & (mask >> 8));

	अगर (offset < 24)
		वापस !!(ioपढ़ो8(&idio16gpio->reg->in0_7) & (mask >> 16));

	वापस !!(ioपढ़ो8(&idio16gpio->reg->in8_15) & (mask >> 24));
पूर्ण

अटल पूर्णांक idio_16_gpio_get_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	व्योम __iomem *ports[] = अणु
		&idio16gpio->reg->out0_7, &idio16gpio->reg->out8_15,
		&idio16gpio->reg->in0_7, &idio16gpio->reg->in8_15,
	पूर्ण;
	व्योम __iomem *port_addr;
	अचिन्हित दीर्घ port_state;

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		port_addr = ports[offset / 8];
		port_state = ioपढ़ो8(port_addr) & gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idio_16_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
	पूर्णांक value)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक mask = BIT(offset);
	व्योम __iomem *base;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक out_state;

	अगर (offset > 15)
		वापस;

	अगर (offset > 7) अणु
		mask >>= 8;
		base = &idio16gpio->reg->out8_15;
	पूर्ण अन्यथा
		base = &idio16gpio->reg->out0_7;

	raw_spin_lock_irqsave(&idio16gpio->lock, flags);

	अगर (value)
		out_state = ioपढ़ो8(base) | mask;
	अन्यथा
		out_state = ioपढ़ो8(base) & ~mask;

	ioग_लिखो8(out_state, base);

	raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
पूर्ण

अटल व्योम idio_16_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	व्योम __iomem *ports[] = अणु
		&idio16gpio->reg->out0_7, &idio16gpio->reg->out8_15,
	पूर्ण;
	माप_प्रकार index;
	व्योम __iomem *port_addr;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ out_state;

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		index = offset / 8;
		port_addr = ports[index];

		biपंचांगask = biपंचांगap_get_value8(bits, offset) & gpio_mask;

		raw_spin_lock_irqsave(&idio16gpio->lock, flags);

		out_state = ioपढ़ो8(port_addr) & ~gpio_mask;
		out_state |= biपंचांगask;
		ioग_लिखो8(out_state, port_addr);

		raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
	पूर्ण
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

		ioग_लिखो8(0, &idio16gpio->reg->irq_ctl);

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

		ioपढ़ो8(&idio16gpio->reg->irq_ctl);

		raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक idio_16_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	/* The only valid irq types are none and both-edges */
	अगर (flow_type != IRQ_TYPE_NONE &&
		(flow_type & IRQ_TYPE_EDGE_BOTH) != IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip idio_16_irqchip = अणु
	.name = "pci-idio-16",
	.irq_ack = idio_16_irq_ack,
	.irq_mask = idio_16_irq_mask,
	.irq_unmask = idio_16_irq_unmask,
	.irq_set_type = idio_16_irq_set_type
पूर्ण;

अटल irqवापस_t idio_16_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idio_16_gpio *स्थिर idio16gpio = dev_id;
	अचिन्हित पूर्णांक irq_status;
	काष्ठा gpio_chip *स्थिर chip = &idio16gpio->chip;
	पूर्णांक gpio;

	raw_spin_lock(&idio16gpio->lock);

	irq_status = ioपढ़ो8(&idio16gpio->reg->irq_status);

	raw_spin_unlock(&idio16gpio->lock);

	/* Make sure our device generated IRQ */
	अगर (!(irq_status & 0x3) || !(irq_status & 0x4))
		वापस IRQ_NONE;

	क्रम_each_set_bit(gpio, &idio16gpio->irq_mask, chip->ngpio)
		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य, gpio));

	raw_spin_lock(&idio16gpio->lock);

	/* Clear पूर्णांकerrupt */
	ioग_लिखो8(0, &idio16gpio->reg->in0_7);

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

	/* Disable IRQ by शेष and clear any pending पूर्णांकerrupt */
	ioग_लिखो8(0, &idio16gpio->reg->irq_ctl);
	ioग_लिखो8(0, &idio16gpio->reg->in0_7);

	वापस 0;
पूर्ण

अटल पूर्णांक idio_16_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *स्थिर dev = &pdev->dev;
	काष्ठा idio_16_gpio *idio16gpio;
	पूर्णांक err;
	स्थिर माप_प्रकार pci_bar_index = 2;
	स्थिर अक्षर *स्थिर name = pci_name(pdev);
	काष्ठा gpio_irq_chip *girq;

	idio16gpio = devm_kzalloc(dev, माप(*idio16gpio), GFP_KERNEL);
	अगर (!idio16gpio)
		वापस -ENOMEM;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device (%d)\n", err);
		वापस err;
	पूर्ण

	err = pcim_iomap_regions(pdev, BIT(pci_bar_index), name);
	अगर (err) अणु
		dev_err(dev, "Unable to map PCI I/O addresses (%d)\n", err);
		वापस err;
	पूर्ण

	idio16gpio->reg = pcim_iomap_table(pdev)[pci_bar_index];

	/* Deactivate input filters */
	ioग_लिखो8(0, &idio16gpio->reg->filter_ctl);

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

	err = devm_request_irq(dev, pdev->irq, idio_16_irq_handler, IRQF_SHARED,
		name, idio16gpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id idio_16_pci_dev_id[] = अणु
	अणु PCI_DEVICE(0x494F, 0x0DC8) पूर्ण, अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, idio_16_pci_dev_id);

अटल काष्ठा pci_driver idio_16_driver = अणु
	.name = "pci-idio-16",
	.id_table = idio_16_pci_dev_id,
	.probe = idio_16_probe
पूर्ण;

module_pci_driver(idio_16_driver);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES PCI-IDIO-16 GPIO driver");
MODULE_LICENSE("GPL v2");
