<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/gpio.c
 *
 * Generic SA-1100 GPIO handling
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>
#समावेश <soc/sa1100/pwer.h>
#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

काष्ठा sa1100_gpio_chip अणु
	काष्ठा gpio_chip chip;
	व्योम __iomem *membase;
	पूर्णांक irqbase;
	u32 irqmask;
	u32 irqrising;
	u32 irqfalling;
	u32 irqwake;
पूर्ण;

#घोषणा sa1100_gpio_chip(x) container_of(x, काष्ठा sa1100_gpio_chip, chip)

क्रमागत अणु
	R_GPLR = 0x00,
	R_GPDR = 0x04,
	R_GPSR = 0x08,
	R_GPCR = 0x0c,
	R_GRER = 0x10,
	R_GFER = 0x14,
	R_GEDR = 0x18,
	R_GAFR = 0x1c,
पूर्ण;

अटल पूर्णांक sa1100_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस पढ़ोl_relaxed(sa1100_gpio_chip(chip)->membase + R_GPLR) &
		BIT(offset);
पूर्ण

अटल व्योम sa1100_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	पूर्णांक reg = value ? R_GPSR : R_GPCR;

	ग_लिखोl_relaxed(BIT(offset), sa1100_gpio_chip(chip)->membase + reg);
पूर्ण

अटल पूर्णांक sa1100_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	व्योम __iomem *gpdr = sa1100_gpio_chip(chip)->membase + R_GPDR;

	अगर (पढ़ोl_relaxed(gpdr) & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक sa1100_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	व्योम __iomem *gpdr = sa1100_gpio_chip(chip)->membase + R_GPDR;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(gpdr) & ~BIT(offset), gpdr);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	व्योम __iomem *gpdr = sa1100_gpio_chip(chip)->membase + R_GPDR;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sa1100_gpio_set(chip, offset, value);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(gpdr) | BIT(offset), gpdr);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस sa1100_gpio_chip(chip)->irqbase + offset;
पूर्ण

अटल काष्ठा sa1100_gpio_chip sa1100_gpio_chip = अणु
	.chip = अणु
		.label			= "gpio",
		.get_direction		= sa1100_get_direction,
		.direction_input	= sa1100_direction_input,
		.direction_output	= sa1100_direction_output,
		.set			= sa1100_gpio_set,
		.get			= sa1100_gpio_get,
		.to_irq			= sa1100_to_irq,
		.base			= 0,
		.ngpio			= GPIO_MAX + 1,
	पूर्ण,
	.membase = (व्योम *)&GPLR,
	.irqbase = IRQ_GPIO0,
पूर्ण;

/*
 * SA1100 GPIO edge detection क्रम IRQs:
 * IRQs are generated on Falling-Edge, Rising-Edge, or both.
 * Use this instead of directly setting GRER/GFER.
 */
अटल व्योम sa1100_update_edge_regs(काष्ठा sa1100_gpio_chip *sgc)
अणु
	व्योम *base = sgc->membase;
	u32 grer, gfer;

	grer = sgc->irqrising & sgc->irqmask;
	gfer = sgc->irqfalling & sgc->irqmask;

	ग_लिखोl_relaxed(grer, base + R_GRER);
	ग_लिखोl_relaxed(gfer, base + R_GFER);
पूर्ण

अटल पूर्णांक sa1100_gpio_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask = BIT(d->hwirq);

	अगर (type == IRQ_TYPE_PROBE) अणु
		अगर ((sgc->irqrising | sgc->irqfalling) & mask)
			वापस 0;
		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	पूर्ण

	अगर (type & IRQ_TYPE_EDGE_RISING)
		sgc->irqrising |= mask;
	अन्यथा
		sgc->irqrising &= ~mask;
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		sgc->irqfalling |= mask;
	अन्यथा
		sgc->irqfalling &= ~mask;

	sa1100_update_edge_regs(sgc);

	वापस 0;
पूर्ण

/*
 * GPIO IRQs must be acknowledged.
 */
अटल व्योम sa1100_gpio_ack(काष्ठा irq_data *d)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);

	ग_लिखोl_relaxed(BIT(d->hwirq), sgc->membase + R_GEDR);
पूर्ण

अटल व्योम sa1100_gpio_mask(काष्ठा irq_data *d)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask = BIT(d->hwirq);

	sgc->irqmask &= ~mask;

	sa1100_update_edge_regs(sgc);
पूर्ण

अटल व्योम sa1100_gpio_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask = BIT(d->hwirq);

	sgc->irqmask |= mask;

	sa1100_update_edge_regs(sgc);
पूर्ण

अटल पूर्णांक sa1100_gpio_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	पूर्णांक ret = sa11x0_gpio_set_wake(d->hwirq, on);
	अगर (!ret) अणु
		अगर (on)
			sgc->irqwake |= BIT(d->hwirq);
		अन्यथा
			sgc->irqwake &= ~BIT(d->hwirq);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This is क्रम GPIO IRQs
 */
अटल काष्ठा irq_chip sa1100_gpio_irq_chip = अणु
	.name		= "GPIO",
	.irq_ack	= sa1100_gpio_ack,
	.irq_mask	= sa1100_gpio_mask,
	.irq_unmask	= sa1100_gpio_unmask,
	.irq_set_type	= sa1100_gpio_type,
	.irq_set_wake	= sa1100_gpio_wake,
पूर्ण;

अटल पूर्णांक sa1100_gpio_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d,
		अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	काष्ठा sa1100_gpio_chip *sgc = d->host_data;

	irq_set_chip_data(irq, sgc);
	irq_set_chip_and_handler(irq, &sa1100_gpio_irq_chip, handle_edge_irq);
	irq_set_probe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sa1100_gpio_irqकरोमुख्य_ops = अणु
	.map = sa1100_gpio_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *sa1100_gpio_irqकरोमुख्य;

/*
 * IRQ 0-11 (GPIO) handler.  We enter here with the
 * irq_controller_lock held, and IRQs disabled.  Decode the IRQ
 * and call the handler.
 */
अटल व्योम sa1100_gpio_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा sa1100_gpio_chip *sgc = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक irq, mask;
	व्योम __iomem *gedr = sgc->membase + R_GEDR;

	mask = पढ़ोl_relaxed(gedr);
	करो अणु
		/*
		 * clear करोwn all currently active IRQ sources.
		 * We will be processing them all.
		 */
		ग_लिखोl_relaxed(mask, gedr);

		irq = sgc->irqbase;
		करो अणु
			अगर (mask & 1)
				generic_handle_irq(irq);
			mask >>= 1;
			irq++;
		पूर्ण जबतक (mask);

		mask = पढ़ोl_relaxed(gedr);
	पूर्ण जबतक (mask);
पूर्ण

अटल पूर्णांक sa1100_gpio_suspend(व्योम)
अणु
	काष्ठा sa1100_gpio_chip *sgc = &sa1100_gpio_chip;

	/*
	 * Set the appropriate edges क्रम wakeup.
	 */
	ग_लिखोl_relaxed(sgc->irqwake & sgc->irqrising, sgc->membase + R_GRER);
	ग_लिखोl_relaxed(sgc->irqwake & sgc->irqfalling, sgc->membase + R_GFER);

	/*
	 * Clear any pending GPIO पूर्णांकerrupts.
	 */
	ग_लिखोl_relaxed(पढ़ोl_relaxed(sgc->membase + R_GEDR),
		       sgc->membase + R_GEDR);

	वापस 0;
पूर्ण

अटल व्योम sa1100_gpio_resume(व्योम)
अणु
	sa1100_update_edge_regs(&sa1100_gpio_chip);
पूर्ण

अटल काष्ठा syscore_ops sa1100_gpio_syscore_ops = अणु
	.suspend	= sa1100_gpio_suspend,
	.resume		= sa1100_gpio_resume,
पूर्ण;

अटल पूर्णांक __init sa1100_gpio_init_devicefs(व्योम)
अणु
	रेजिस्टर_syscore_ops(&sa1100_gpio_syscore_ops);
	वापस 0;
पूर्ण

device_initcall(sa1100_gpio_init_devicefs);

अटल स्थिर पूर्णांक sa1100_gpio_irqs[] __initस्थिर = अणु
	/* Install handlers क्रम GPIO 0-10 edge detect पूर्णांकerrupts */
	IRQ_GPIO0_SC,
	IRQ_GPIO1_SC,
	IRQ_GPIO2_SC,
	IRQ_GPIO3_SC,
	IRQ_GPIO4_SC,
	IRQ_GPIO5_SC,
	IRQ_GPIO6_SC,
	IRQ_GPIO7_SC,
	IRQ_GPIO8_SC,
	IRQ_GPIO9_SC,
	IRQ_GPIO10_SC,
	/* Install handler क्रम GPIO 11-27 edge detect पूर्णांकerrupts */
	IRQ_GPIO11_27,
पूर्ण;

व्योम __init sa1100_init_gpio(व्योम)
अणु
	काष्ठा sa1100_gpio_chip *sgc = &sa1100_gpio_chip;
	पूर्णांक i;

	/* clear all GPIO edge detects */
	ग_लिखोl_relaxed(0, sgc->membase + R_GFER);
	ग_लिखोl_relaxed(0, sgc->membase + R_GRER);
	ग_लिखोl_relaxed(-1, sgc->membase + R_GEDR);

	gpiochip_add_data(&sa1100_gpio_chip.chip, शून्य);

	sa1100_gpio_irqकरोमुख्य = irq_करोमुख्य_add_simple(शून्य,
			28, IRQ_GPIO0,
			&sa1100_gpio_irqकरोमुख्य_ops, sgc);

	क्रम (i = 0; i < ARRAY_SIZE(sa1100_gpio_irqs); i++)
		irq_set_chained_handler_and_data(sa1100_gpio_irqs[i],
						 sa1100_gpio_handler, sgc);
पूर्ण
