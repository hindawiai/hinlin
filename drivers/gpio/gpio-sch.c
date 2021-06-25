<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO पूर्णांकerface क्रम Intel Poulsbo SCH
 *
 *  Copyright (c) 2010 CompuLab Ltd
 *  Author: Denis Turischev <denis@compulab.co.il>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#घोषणा GEN	0x00
#घोषणा GIO	0x04
#घोषणा GLV	0x08
#घोषणा GTPE	0x0c
#घोषणा GTNE	0x10
#घोषणा GGPE	0x14
#घोषणा GSMI	0x18
#घोषणा GTS	0x1c

#घोषणा CORE_BANK_OFFSET	0x00
#घोषणा RESUME_BANK_OFFSET	0x20

/*
 * iLB datasheet describes GPE0BLK रेजिस्टरs, in particular GPE0E.GPIO bit.
 * Document Number: 328195-001
 */
#घोषणा GPE0E_GPIO	14

काष्ठा sch_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irqchip;
	spinlock_t lock;
	अचिन्हित लघु iobase;
	अचिन्हित लघु resume_base;

	/* GPE handling */
	u32 gpe;
	acpi_gpe_handler gpe_handler;
पूर्ण;

अटल अचिन्हित पूर्णांक sch_gpio_offset(काष्ठा sch_gpio *sch, अचिन्हित पूर्णांक gpio,
				अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक base = CORE_BANK_OFFSET;

	अगर (gpio >= sch->resume_base) अणु
		gpio -= sch->resume_base;
		base = RESUME_BANK_OFFSET;
	पूर्ण

	वापस base + reg + gpio / 8;
पूर्ण

अटल अचिन्हित पूर्णांक sch_gpio_bit(काष्ठा sch_gpio *sch, अचिन्हित पूर्णांक gpio)
अणु
	अगर (gpio >= sch->resume_base)
		gpio -= sch->resume_base;
	वापस gpio % 8;
पूर्ण

अटल पूर्णांक sch_gpio_reg_get(काष्ठा sch_gpio *sch, अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित लघु offset, bit;
	u8 reg_val;

	offset = sch_gpio_offset(sch, gpio, reg);
	bit = sch_gpio_bit(sch, gpio);

	reg_val = !!(inb(sch->iobase + offset) & BIT(bit));

	वापस reg_val;
पूर्ण

अटल व्योम sch_gpio_reg_set(काष्ठा sch_gpio *sch, अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक reg,
			     पूर्णांक val)
अणु
	अचिन्हित लघु offset, bit;
	u8 reg_val;

	offset = sch_gpio_offset(sch, gpio, reg);
	bit = sch_gpio_bit(sch, gpio);

	reg_val = inb(sch->iobase + offset);

	अगर (val)
		outb(reg_val | BIT(bit), sch->iobase + offset);
	अन्यथा
		outb((reg_val & ~BIT(bit)), sch->iobase + offset);
पूर्ण

अटल पूर्णांक sch_gpio_direction_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio_num)
अणु
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sch->lock, flags);
	sch_gpio_reg_set(sch, gpio_num, GIO, 1);
	spin_unlock_irqrestore(&sch->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक sch_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio_num)
अणु
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);

	वापस sch_gpio_reg_get(sch, gpio_num, GLV);
पूर्ण

अटल व्योम sch_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio_num, पूर्णांक val)
अणु
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sch->lock, flags);
	sch_gpio_reg_set(sch, gpio_num, GLV, val);
	spin_unlock_irqrestore(&sch->lock, flags);
पूर्ण

अटल पूर्णांक sch_gpio_direction_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio_num,
				  पूर्णांक val)
अणु
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sch->lock, flags);
	sch_gpio_reg_set(sch, gpio_num, GIO, 0);
	spin_unlock_irqrestore(&sch->lock, flags);

	/*
	 * according to the datasheet, writing to the level रेजिस्टर has no
	 * effect when GPIO is programmed as input.
	 * Actually the the level रेजिस्टर is पढ़ो-only when configured as input.
	 * Thus presetting the output level beक्रमe चयनing to output is _NOT_ possible.
	 * Hence we set the level after configuring the GPIO as output.
	 * But we cannot prevent a लघु low pulse अगर direction is set to high
	 * and an बाह्यal pull-up is connected.
	 */
	sch_gpio_set(gc, gpio_num, val);
	वापस 0;
पूर्ण

अटल पूर्णांक sch_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio_num)
अणु
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);

	अगर (sch_gpio_reg_get(sch, gpio_num, GIO))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल स्थिर काष्ठा gpio_chip sch_gpio_chip = अणु
	.label			= "sch_gpio",
	.owner			= THIS_MODULE,
	.direction_input	= sch_gpio_direction_in,
	.get			= sch_gpio_get,
	.direction_output	= sch_gpio_direction_out,
	.set			= sch_gpio_set,
	.get_direction		= sch_gpio_get_direction,
पूर्ण;

अटल पूर्णांक sch_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	irq_hw_number_t gpio_num = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	पूर्णांक rising, falling;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		rising = 1;
		falling = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		rising = 0;
		falling = 1;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		rising = 1;
		falling = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&sch->lock, flags);

	sch_gpio_reg_set(sch, gpio_num, GTPE, rising);
	sch_gpio_reg_set(sch, gpio_num, GTNE, falling);

	irq_set_handler_locked(d, handle_edge_irq);

	spin_unlock_irqrestore(&sch->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sch_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	irq_hw_number_t gpio_num = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sch->lock, flags);
	sch_gpio_reg_set(sch, gpio_num, GTS, 1);
	spin_unlock_irqrestore(&sch->lock, flags);
पूर्ण

अटल व्योम sch_irq_mask_unmask(काष्ठा irq_data *d, पूर्णांक val)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sch_gpio *sch = gpiochip_get_data(gc);
	irq_hw_number_t gpio_num = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sch->lock, flags);
	sch_gpio_reg_set(sch, gpio_num, GGPE, val);
	spin_unlock_irqrestore(&sch->lock, flags);
पूर्ण

अटल व्योम sch_irq_mask(काष्ठा irq_data *d)
अणु
	sch_irq_mask_unmask(d, 0);
पूर्ण

अटल व्योम sch_irq_unmask(काष्ठा irq_data *d)
अणु
	sch_irq_mask_unmask(d, 1);
पूर्ण

अटल u32 sch_gpio_gpe_handler(acpi_handle gpe_device, u32 gpe, व्योम *context)
अणु
	काष्ठा sch_gpio *sch = context;
	काष्ठा gpio_chip *gc = &sch->chip;
	अचिन्हित दीर्घ core_status, resume_status;
	अचिन्हित दीर्घ pending;
	अचिन्हित दीर्घ flags;
	पूर्णांक offset;
	u32 ret;

	spin_lock_irqsave(&sch->lock, flags);

	core_status = inl(sch->iobase + CORE_BANK_OFFSET + GTS);
	resume_status = inl(sch->iobase + RESUME_BANK_OFFSET + GTS);

	spin_unlock_irqrestore(&sch->lock, flags);

	pending = (resume_status << sch->resume_base) | core_status;
	क्रम_each_set_bit(offset, &pending, sch->chip.ngpio)
		generic_handle_irq(irq_find_mapping(gc->irq.करोमुख्य, offset));

	/* Set वापसing value depending on whether we handled an पूर्णांकerrupt */
	ret = pending ? ACPI_INTERRUPT_HANDLED : ACPI_INTERRUPT_NOT_HANDLED;

	/* Acknowledge GPE to ACPICA */
	ret |= ACPI_REENABLE_GPE;

	वापस ret;
पूर्ण

अटल व्योम sch_gpio_हटाओ_gpe_handler(व्योम *data)
अणु
	काष्ठा sch_gpio *sch = data;

	acpi_disable_gpe(शून्य, sch->gpe);
	acpi_हटाओ_gpe_handler(शून्य, sch->gpe, sch->gpe_handler);
पूर्ण

अटल पूर्णांक sch_gpio_install_gpe_handler(काष्ठा sch_gpio *sch)
अणु
	काष्ठा device *dev = sch->chip.parent;
	acpi_status status;

	status = acpi_install_gpe_handler(शून्य, sch->gpe, ACPI_GPE_LEVEL_TRIGGERED,
					  sch->gpe_handler, sch);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Failed to install GPE handler for %u: %s\n",
			sch->gpe, acpi_क्रमmat_exception(status));
		वापस -ENODEV;
	पूर्ण

	status = acpi_enable_gpe(शून्य, sch->gpe);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Failed to enable GPE handler for %u: %s\n",
			sch->gpe, acpi_क्रमmat_exception(status));
		acpi_हटाओ_gpe_handler(शून्य, sch->gpe, sch->gpe_handler);
		वापस -ENODEV;
	पूर्ण

	वापस devm_add_action_or_reset(dev, sch_gpio_हटाओ_gpe_handler, sch);
पूर्ण

अटल पूर्णांक sch_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_irq_chip *girq;
	काष्ठा sch_gpio *sch;
	काष्ठा resource *res;
	पूर्णांक ret;

	sch = devm_kzalloc(&pdev->dev, माप(*sch), GFP_KERNEL);
	अगर (!sch)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res)
		वापस -EBUSY;

	अगर (!devm_request_region(&pdev->dev, res->start, resource_size(res),
				 pdev->name))
		वापस -EBUSY;

	spin_lock_init(&sch->lock);
	sch->iobase = res->start;
	sch->chip = sch_gpio_chip;
	sch->chip.label = dev_name(&pdev->dev);
	sch->chip.parent = &pdev->dev;

	चयन (pdev->id) अणु
	हाल PCI_DEVICE_ID_INTEL_SCH_LPC:
		sch->resume_base = 10;
		sch->chip.ngpio = 14;

		/*
		 * GPIO[6:0] enabled by शेष
		 * GPIO7 is configured by the CMC as SLPIOVR
		 * Enable GPIO[9:8] core घातered gpios explicitly
		 */
		sch_gpio_reg_set(sch, 8, GEN, 1);
		sch_gpio_reg_set(sch, 9, GEN, 1);
		/*
		 * SUS_GPIO[2:0] enabled by शेष
		 * Enable SUS_GPIO3 resume घातered gpio explicitly
		 */
		sch_gpio_reg_set(sch, 13, GEN, 1);
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_ITC_LPC:
		sch->resume_base = 5;
		sch->chip.ngpio = 14;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_CENTERTON_ILB:
		sch->resume_base = 21;
		sch->chip.ngpio = 30;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_QUARK_X1000_ILB:
		sch->resume_base = 2;
		sch->chip.ngpio = 8;
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sch);

	sch->irqchip.name = "sch_gpio";
	sch->irqchip.irq_ack = sch_irq_ack;
	sch->irqchip.irq_mask = sch_irq_mask;
	sch->irqchip.irq_unmask = sch_irq_unmask;
	sch->irqchip.irq_set_type = sch_irq_type;

	girq = &sch->chip.irq;
	girq->chip = &sch->irqchip;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->parent_handler = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;

	/* GPE setup is optional */
	sch->gpe = GPE0E_GPIO;
	sch->gpe_handler = sch_gpio_gpe_handler;

	ret = sch_gpio_install_gpe_handler(sch);
	अगर (ret)
		dev_warn(&pdev->dev, "Can't setup GPE, no IRQ support\n");

	वापस devm_gpiochip_add_data(&pdev->dev, &sch->chip, sch);
पूर्ण

अटल काष्ठा platक्रमm_driver sch_gpio_driver = अणु
	.driver = अणु
		.name = "sch_gpio",
	पूर्ण,
	.probe		= sch_gpio_probe,
पूर्ण;

module_platक्रमm_driver(sch_gpio_driver);

MODULE_AUTHOR("Denis Turischev <denis@compulab.co.il>");
MODULE_DESCRIPTION("GPIO interface for Intel Poulsbo SCH");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sch_gpio");
