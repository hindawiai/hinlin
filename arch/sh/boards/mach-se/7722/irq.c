<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hitachi UL SolutionEngine 7722 FPGA IRQ Support.
 *
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 * Copyright (C) 2012  Paul Mundt
 */
#घोषणा DRV_NAME "SE7722-FPGA"
#घोषणा pr_fmt(fmt) DRV_NAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/sizes.h>
#समावेश <mach-se/mach/se7722.h>

#घोषणा IRQ01_BASE_ADDR	0x11800000
#घोषणा IRQ01_MODE_REG	0
#घोषणा IRQ01_STS_REG	4
#घोषणा IRQ01_MASK_REG	8

अटल व्योम __iomem *se7722_irq_regs;
काष्ठा irq_करोमुख्य *se7722_irq_करोमुख्य;

अटल व्योम se7722_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	अचिन्हित दीर्घ mask;
	पूर्णांक bit;

	chip->irq_mask_ack(data);

	mask = ioपढ़ो16(se7722_irq_regs + IRQ01_STS_REG);

	क्रम_each_set_bit(bit, &mask, SE7722_FPGA_IRQ_NR)
		generic_handle_irq(irq_linear_revmap(se7722_irq_करोमुख्य, bit));

	chip->irq_unmask(data);
पूर्ण

अटल व्योम __init se7722_करोमुख्य_init(व्योम)
अणु
	पूर्णांक i;

	se7722_irq_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, SE7722_FPGA_IRQ_NR,
						  &irq_करोमुख्य_simple_ops, शून्य);
	अगर (unlikely(!se7722_irq_करोमुख्य)) अणु
		prपूर्णांकk("Failed to get IRQ domain\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < SE7722_FPGA_IRQ_NR; i++) अणु
		पूर्णांक irq = irq_create_mapping(se7722_irq_करोमुख्य, i);

		अगर (unlikely(irq == 0)) अणु
			prपूर्णांकk("Failed to allocate IRQ %d\n", i);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init se7722_gc_init(व्योम)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित पूर्णांक irq_base;

	irq_base = irq_linear_revmap(se7722_irq_करोमुख्य, 0);

	gc = irq_alloc_generic_chip(DRV_NAME, 1, irq_base, se7722_irq_regs,
				    handle_level_irq);
	अगर (unlikely(!gc))
		वापस;

	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_set_bit;
	ct->chip.irq_unmask = irq_gc_mask_clr_bit;

	ct->regs.mask = IRQ01_MASK_REG;

	irq_setup_generic_chip(gc, IRQ_MSK(SE7722_FPGA_IRQ_NR),
			       IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	irq_set_chained_handler(IRQ0_IRQ, se7722_irq_demux);
	irq_set_irq_type(IRQ0_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ1_IRQ, se7722_irq_demux);
	irq_set_irq_type(IRQ1_IRQ, IRQ_TYPE_LEVEL_LOW);
पूर्ण

/*
 * Initialize FPGA IRQs
 */
व्योम __init init_se7722_IRQ(व्योम)
अणु
	se7722_irq_regs = ioremap(IRQ01_BASE_ADDR, SZ_16);
	अगर (unlikely(!se7722_irq_regs)) अणु
		prपूर्णांकk("Failed to remap IRQ01 regs\n");
		वापस;
	पूर्ण

	/*
	 * All FPGA IRQs disabled by शेष
	 */
	ioग_लिखो16(0, se7722_irq_regs + IRQ01_MASK_REG);

	__raw_ग_लिखोw(0x2000, 0xb03fffec);  /* mrshpc irq enable */

	se7722_करोमुख्य_init();
	se7722_gc_init();
पूर्ण
