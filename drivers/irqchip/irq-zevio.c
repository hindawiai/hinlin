<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/irqchip/irq-zevio.c
 *
 *  Copyright (C) 2013 Daniel Tang <tangrs@tangrs.id.au>
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/exception.h>

#घोषणा IO_STATUS	0x000
#घोषणा IO_RAW_STATUS	0x004
#घोषणा IO_ENABLE	0x008
#घोषणा IO_DISABLE	0x00C
#घोषणा IO_CURRENT	0x020
#घोषणा IO_RESET	0x028
#घोषणा IO_MAX_PRIOTY	0x02C

#घोषणा IO_IRQ_BASE	0x000
#घोषणा IO_FIQ_BASE	0x100

#घोषणा IO_INVERT_SEL	0x200
#घोषणा IO_STICKY_SEL	0x204
#घोषणा IO_PRIORITY_SEL	0x300

#घोषणा MAX_INTRS	32
#घोषणा FIQ_START	MAX_INTRS

अटल काष्ठा irq_करोमुख्य *zevio_irq_करोमुख्य;
अटल व्योम __iomem *zevio_irq_io;

अटल व्योम zevio_irq_ack(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा irq_chip_regs *regs = &irq_data_get_chip_type(irqd)->regs;

	पढ़ोl(gc->reg_base + regs->ack);
पूर्ण

अटल व्योम __exception_irq_entry zevio_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक irqnr;

	जबतक (पढ़ोl(zevio_irq_io + IO_STATUS)) अणु
		irqnr = पढ़ोl(zevio_irq_io + IO_CURRENT);
		handle_करोमुख्य_irq(zevio_irq_करोमुख्य, irqnr, regs);
	पूर्ण
पूर्ण

अटल व्योम __init zevio_init_irq_base(व्योम __iomem *base)
अणु
	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(~0, base + IO_DISABLE);

	/* Accept पूर्णांकerrupts of all priorities */
	ग_लिखोl(0xF, base + IO_MAX_PRIOTY);

	/* Reset existing पूर्णांकerrupts */
	पढ़ोl(base + IO_RESET);
पूर्ण

अटल पूर्णांक __init zevio_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक ret;

	अगर (WARN_ON(zevio_irq_io || zevio_irq_करोमुख्य))
		वापस -EBUSY;

	zevio_irq_io = of_iomap(node, 0);
	BUG_ON(!zevio_irq_io);

	/* Do not invert पूर्णांकerrupt status bits */
	ग_लिखोl(~0, zevio_irq_io + IO_INVERT_SEL);

	/* Disable sticky पूर्णांकerrupts */
	ग_लिखोl(0, zevio_irq_io + IO_STICKY_SEL);

	/* We करोn't use IRQ priorities. Set each IRQ to highest priority. */
	स_रखो_io(zevio_irq_io + IO_PRIORITY_SEL, 0, MAX_INTRS * माप(u32));

	/* Init IRQ and FIQ */
	zevio_init_irq_base(zevio_irq_io + IO_IRQ_BASE);
	zevio_init_irq_base(zevio_irq_io + IO_FIQ_BASE);

	zevio_irq_करोमुख्य = irq_करोमुख्य_add_linear(node, MAX_INTRS,
						 &irq_generic_chip_ops, शून्य);
	BUG_ON(!zevio_irq_करोमुख्य);

	ret = irq_alloc_करोमुख्य_generic_chips(zevio_irq_करोमुख्य, MAX_INTRS, 1,
					     "zevio_intc", handle_level_irq,
					     clr, 0, IRQ_GC_INIT_MASK_CACHE);
	BUG_ON(ret);

	gc = irq_get_करोमुख्य_generic_chip(zevio_irq_करोमुख्य, 0);
	gc->reg_base				= zevio_irq_io;
	gc->chip_types[0].chip.irq_ack		= zevio_irq_ack;
	gc->chip_types[0].chip.irq_mask		= irq_gc_mask_disable_reg;
	gc->chip_types[0].chip.irq_unmask	= irq_gc_unmask_enable_reg;
	gc->chip_types[0].regs.mask		= IO_IRQ_BASE + IO_ENABLE;
	gc->chip_types[0].regs.enable		= IO_IRQ_BASE + IO_ENABLE;
	gc->chip_types[0].regs.disable		= IO_IRQ_BASE + IO_DISABLE;
	gc->chip_types[0].regs.ack		= IO_IRQ_BASE + IO_RESET;

	set_handle_irq(zevio_handle_irq);

	pr_info("TI-NSPIRE classic IRQ controller\n");
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(zevio_irq, "lsi,zevio-intc", zevio_of_init);
