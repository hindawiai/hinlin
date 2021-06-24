<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * irqchip क्रम the Faraday Technology FTINTC010 Copyright (C) 2017 Linus
 * Walleij <linus.walleij@linaro.org>
 *
 * Based on arch/arm/mach-gemini/irq.c
 * Copyright (C) 2001-2006 Storlink, Corp.
 * Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@gmail.com>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/versatile-fpga.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#घोषणा FT010_NUM_IRQS 32

#घोषणा FT010_IRQ_SOURCE(base_addr)	(base_addr + 0x00)
#घोषणा FT010_IRQ_MASK(base_addr)	(base_addr + 0x04)
#घोषणा FT010_IRQ_CLEAR(base_addr)	(base_addr + 0x08)
/* Selects level- or edge-triggered */
#घोषणा FT010_IRQ_MODE(base_addr)	(base_addr + 0x0C)
/* Selects active low/high or falling/rising edge */
#घोषणा FT010_IRQ_POLARITY(base_addr)	(base_addr + 0x10)
#घोषणा FT010_IRQ_STATUS(base_addr)	(base_addr + 0x14)
#घोषणा FT010_FIQ_SOURCE(base_addr)	(base_addr + 0x20)
#घोषणा FT010_FIQ_MASK(base_addr)	(base_addr + 0x24)
#घोषणा FT010_FIQ_CLEAR(base_addr)	(base_addr + 0x28)
#घोषणा FT010_FIQ_MODE(base_addr)	(base_addr + 0x2C)
#घोषणा FT010_FIQ_POLARITY(base_addr)	(base_addr + 0x30)
#घोषणा FT010_FIQ_STATUS(base_addr)	(base_addr + 0x34)

/**
 * काष्ठा ft010_irq_data - irq data container क्रम the Faraday IRQ controller
 * @base: memory offset in भव memory
 * @chip: chip container क्रम this instance
 * @करोमुख्य: IRQ करोमुख्य क्रम this instance
 */
काष्ठा ft010_irq_data अणु
	व्योम __iomem *base;
	काष्ठा irq_chip chip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

अटल व्योम ft010_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ft010_irq_data *f = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask;

	mask = पढ़ोl(FT010_IRQ_MASK(f->base));
	mask &= ~BIT(irqd_to_hwirq(d));
	ग_लिखोl(mask, FT010_IRQ_MASK(f->base));
पूर्ण

अटल व्योम ft010_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ft010_irq_data *f = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask;

	mask = पढ़ोl(FT010_IRQ_MASK(f->base));
	mask |= BIT(irqd_to_hwirq(d));
	ग_लिखोl(mask, FT010_IRQ_MASK(f->base));
पूर्ण

अटल व्योम ft010_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा ft010_irq_data *f = irq_data_get_irq_chip_data(d);

	ग_लिखोl(BIT(irqd_to_hwirq(d)), FT010_IRQ_CLEAR(f->base));
पूर्ण

अटल पूर्णांक ft010_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक trigger)
अणु
	काष्ठा ft010_irq_data *f = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = irqd_to_hwirq(d);
	u32 mode, polarity;

	mode = पढ़ोl(FT010_IRQ_MODE(f->base));
	polarity = पढ़ोl(FT010_IRQ_POLARITY(f->base));

	अगर (trigger & (IRQ_TYPE_LEVEL_LOW)) अणु
		irq_set_handler_locked(d, handle_level_irq);
		mode &= ~BIT(offset);
		polarity |= BIT(offset);
	पूर्ण अन्यथा अगर (trigger & (IRQ_TYPE_LEVEL_HIGH)) अणु
		irq_set_handler_locked(d, handle_level_irq);
		mode &= ~BIT(offset);
		polarity &= ~BIT(offset);
	पूर्ण अन्यथा अगर (trigger & IRQ_TYPE_EDGE_FALLING) अणु
		irq_set_handler_locked(d, handle_edge_irq);
		mode |= BIT(offset);
		polarity |= BIT(offset);
	पूर्ण अन्यथा अगर (trigger & IRQ_TYPE_EDGE_RISING) अणु
		irq_set_handler_locked(d, handle_edge_irq);
		mode |= BIT(offset);
		polarity &= ~BIT(offset);
	पूर्ण अन्यथा अणु
		irq_set_handler_locked(d, handle_bad_irq);
		pr_warn("Faraday IRQ: no supported trigger selected for line %d\n",
			offset);
	पूर्ण

	ग_लिखोl(mode, FT010_IRQ_MODE(f->base));
	ग_लिखोl(polarity, FT010_IRQ_POLARITY(f->base));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ft010_irq_chip = अणु
	.name		= "FTINTC010",
	.irq_ack	= ft010_irq_ack,
	.irq_mask	= ft010_irq_mask,
	.irq_unmask	= ft010_irq_unmask,
	.irq_set_type	= ft010_irq_set_type,
पूर्ण;

/* Local अटल क्रम the IRQ entry call */
अटल काष्ठा ft010_irq_data firq;

यंत्रlinkage व्योम __exception_irq_entry ft010_irqchip_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा ft010_irq_data *f = &firq;
	पूर्णांक irq;
	u32 status;

	जबतक ((status = पढ़ोl(FT010_IRQ_STATUS(f->base)))) अणु
		irq = ffs(status) - 1;
		handle_करोमुख्य_irq(f->करोमुख्य, irq, regs);
	पूर्ण
पूर्ण

अटल पूर्णांक ft010_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	काष्ठा ft010_irq_data *f = d->host_data;

	irq_set_chip_data(irq, f);
	/* All IRQs should set up their type, flags as bad by शेष */
	irq_set_chip_and_handler(irq, &ft010_irq_chip, handle_bad_irq);
	irq_set_probe(irq);

	वापस 0;
पूर्ण

अटल व्योम ft010_irqकरोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ft010_irqकरोमुख्य_ops = अणु
	.map = ft010_irqकरोमुख्य_map,
	.unmap = ft010_irqकरोमुख्य_unmap,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

पूर्णांक __init ft010_of_init_irq(काष्ठा device_node *node,
			      काष्ठा device_node *parent)
अणु
	काष्ठा ft010_irq_data *f = &firq;

	/*
	 * Disable the idle handler by शेष since it is buggy
	 * For more info see arch/arm/mach-gemini/idle.c
	 */
	cpu_idle_poll_ctrl(true);

	f->base = of_iomap(node, 0);
	WARN(!f->base, "unable to map gemini irq registers\n");

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(0, FT010_IRQ_MASK(f->base));
	ग_लिखोl(0, FT010_FIQ_MASK(f->base));

	f->करोमुख्य = irq_करोमुख्य_add_simple(node, FT010_NUM_IRQS, 0,
					  &ft010_irqकरोमुख्य_ops, f);
	set_handle_irq(ft010_irqchip_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(faraday, "faraday,ftintc010",
		ft010_of_init_irq);
IRQCHIP_DECLARE(gemini, "cortina,gemini-interrupt-controller",
		ft010_of_init_irq);
IRQCHIP_DECLARE(moxa, "moxa,moxart-ic",
		ft010_of_init_irq);
