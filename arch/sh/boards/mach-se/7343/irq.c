<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hitachi UL SolutionEngine 7343 FPGA IRQ Support.
 *
 * Copyright (C) 2008  Yoshihiro Shimoda
 * Copyright (C) 2012  Paul Mundt
 *
 * Based on linux/arch/sh/boards/se/7343/irq.c
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 */
#घोषणा DRV_NAME "SE7343-FPGA"
#घोषणा pr_fmt(fmt) DRV_NAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>
#समावेश <mach-se/mach/se7343.h>

#घोषणा PA_CPLD_BASE_ADDR	0x11400000
#घोषणा PA_CPLD_ST_REG		0x08	/* CPLD Interrupt status रेजिस्टर */
#घोषणा PA_CPLD_IMSK_REG	0x0a	/* CPLD Interrupt mask रेजिस्टर */

अटल व्योम __iomem *se7343_irq_regs;
काष्ठा irq_करोमुख्य *se7343_irq_करोमुख्य;

अटल व्योम se7343_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	अचिन्हित दीर्घ mask;
	पूर्णांक bit;

	chip->irq_mask_ack(data);

	mask = ioपढ़ो16(se7343_irq_regs + PA_CPLD_ST_REG);

	क्रम_each_set_bit(bit, &mask, SE7343_FPGA_IRQ_NR)
		generic_handle_irq(irq_linear_revmap(se7343_irq_करोमुख्य, bit));

	chip->irq_unmask(data);
पूर्ण

अटल व्योम __init se7343_करोमुख्य_init(व्योम)
अणु
	पूर्णांक i;

	se7343_irq_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, SE7343_FPGA_IRQ_NR,
						  &irq_करोमुख्य_simple_ops, शून्य);
	अगर (unlikely(!se7343_irq_करोमुख्य)) अणु
		prपूर्णांकk("Failed to get IRQ domain\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < SE7343_FPGA_IRQ_NR; i++) अणु
		पूर्णांक irq = irq_create_mapping(se7343_irq_करोमुख्य, i);

		अगर (unlikely(irq == 0)) अणु
			prपूर्णांकk("Failed to allocate IRQ %d\n", i);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init se7343_gc_init(व्योम)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित पूर्णांक irq_base;

	irq_base = irq_linear_revmap(se7343_irq_करोमुख्य, 0);

	gc = irq_alloc_generic_chip(DRV_NAME, 1, irq_base, se7343_irq_regs,
				    handle_level_irq);
	अगर (unlikely(!gc))
		वापस;

	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_set_bit;
	ct->chip.irq_unmask = irq_gc_mask_clr_bit;

	ct->regs.mask = PA_CPLD_IMSK_REG;

	irq_setup_generic_chip(gc, IRQ_MSK(SE7343_FPGA_IRQ_NR),
			       IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	irq_set_chained_handler(IRQ0_IRQ, se7343_irq_demux);
	irq_set_irq_type(IRQ0_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ1_IRQ, se7343_irq_demux);
	irq_set_irq_type(IRQ1_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ4_IRQ, se7343_irq_demux);
	irq_set_irq_type(IRQ4_IRQ, IRQ_TYPE_LEVEL_LOW);

	irq_set_chained_handler(IRQ5_IRQ, se7343_irq_demux);
	irq_set_irq_type(IRQ5_IRQ, IRQ_TYPE_LEVEL_LOW);
पूर्ण

/*
 * Initialize IRQ setting
 */
व्योम __init init_7343se_IRQ(व्योम)
अणु
	se7343_irq_regs = ioremap(PA_CPLD_BASE_ADDR, SZ_16);
	अगर (unlikely(!se7343_irq_regs)) अणु
		pr_err("Failed to remap CPLD\n");
		वापस;
	पूर्ण

	/*
	 * All FPGA IRQs disabled by शेष
	 */
	ioग_लिखो16(0, se7343_irq_regs + PA_CPLD_IMSK_REG);

	__raw_ग_लिखोw(0x2000, 0xb03fffec);	/* mrshpc irq enable */

	se7343_करोमुख्य_init();
	se7343_gc_init();
पूर्ण
