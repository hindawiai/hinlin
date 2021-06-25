<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Copyright (C) 2006, 2019 Texas Instruments.
//
// Interrupt handler क्रम DaVinci boards.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/irq-davinci-aपूर्णांकc.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/exception.h>

#घोषणा DAVINCI_AINTC_FIQ_REG0		0x00
#घोषणा DAVINCI_AINTC_FIQ_REG1		0x04
#घोषणा DAVINCI_AINTC_IRQ_REG0		0x08
#घोषणा DAVINCI_AINTC_IRQ_REG1		0x0c
#घोषणा DAVINCI_AINTC_IRQ_IRQENTRY	0x14
#घोषणा DAVINCI_AINTC_IRQ_ENT_REG0	0x18
#घोषणा DAVINCI_AINTC_IRQ_ENT_REG1	0x1c
#घोषणा DAVINCI_AINTC_IRQ_INCTL_REG	0x20
#घोषणा DAVINCI_AINTC_IRQ_EABASE_REG	0x24
#घोषणा DAVINCI_AINTC_IRQ_INTPRI0_REG	0x30
#घोषणा DAVINCI_AINTC_IRQ_INTPRI7_REG	0x4c

अटल व्योम __iomem *davinci_aपूर्णांकc_base;
अटल काष्ठा irq_करोमुख्य *davinci_aपूर्णांकc_irq_करोमुख्य;

अटल अंतरभूत व्योम davinci_aपूर्णांकc_ग_लिखोl(अचिन्हित दीर्घ value, पूर्णांक offset)
अणु
	ग_लिखोl_relaxed(value, davinci_aपूर्णांकc_base + offset);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ davinci_aपूर्णांकc_पढ़ोl(पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(davinci_aपूर्णांकc_base + offset);
पूर्ण

अटल __init व्योम
davinci_aपूर्णांकc_setup_gc(व्योम __iomem *base,
		       अचिन्हित पूर्णांक irq_start, अचिन्हित पूर्णांक num)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	gc = irq_get_करोमुख्य_generic_chip(davinci_aपूर्णांकc_irq_करोमुख्य, irq_start);
	gc->reg_base = base;
	gc->irq_base = irq_start;

	ct = gc->chip_types;
	ct->chip.irq_ack = irq_gc_ack_set_bit;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;

	ct->regs.ack = DAVINCI_AINTC_IRQ_REG0;
	ct->regs.mask = DAVINCI_AINTC_IRQ_ENT_REG0;
	irq_setup_generic_chip(gc, IRQ_MSK(num), IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST | IRQ_NOPROBE, 0);
पूर्ण

अटल यंत्रlinkage व्योम __exception_irq_entry
davinci_aपूर्णांकc_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक irqnr = davinci_aपूर्णांकc_पढ़ोl(DAVINCI_AINTC_IRQ_IRQENTRY);

	/*
	 * Use the क्रमmula क्रम entry vector index generation from section
	 * 8.3.3 of the manual.
	 */
	irqnr >>= 2;
	irqnr -= 1;

	handle_करोमुख्य_irq(davinci_aपूर्णांकc_irq_करोमुख्य, irqnr, regs);
पूर्ण

/* ARM Interrupt Controller Initialization */
व्योम __init davinci_aपूर्णांकc_init(स्थिर काष्ठा davinci_aपूर्णांकc_config *config)
अणु
	अचिन्हित पूर्णांक irq_off, reg_off, prio, shअगरt;
	व्योम __iomem *req;
	पूर्णांक ret, irq_base;
	स्थिर u8 *prios;

	req = request_mem_region(config->reg.start,
				 resource_size(&config->reg),
				 "davinci-cp-intc");
	अगर (!req) अणु
		pr_err("%s: register range busy\n", __func__);
		वापस;
	पूर्ण

	davinci_aपूर्णांकc_base = ioremap(config->reg.start,
				     resource_size(&config->reg));
	अगर (!davinci_aपूर्णांकc_base) अणु
		pr_err("%s: unable to ioremap register range\n", __func__);
		वापस;
	पूर्ण

	/* Clear all पूर्णांकerrupt requests */
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_FIQ_REG0);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_FIQ_REG1);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_IRQ_REG0);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_IRQ_REG1);

	/* Disable all पूर्णांकerrupts */
	davinci_aपूर्णांकc_ग_लिखोl(0x0, DAVINCI_AINTC_IRQ_ENT_REG0);
	davinci_aपूर्णांकc_ग_लिखोl(0x0, DAVINCI_AINTC_IRQ_ENT_REG1);

	/* Interrupts disabled immediately, IRQ entry reflects all */
	davinci_aपूर्णांकc_ग_लिखोl(0x0, DAVINCI_AINTC_IRQ_INCTL_REG);

	/* we करोn't use the hardware vector table, just its entry addresses */
	davinci_aपूर्णांकc_ग_लिखोl(0, DAVINCI_AINTC_IRQ_EABASE_REG);

	/* Clear all पूर्णांकerrupt requests */
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_FIQ_REG0);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_FIQ_REG1);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_IRQ_REG0);
	davinci_aपूर्णांकc_ग_लिखोl(~0x0, DAVINCI_AINTC_IRQ_REG1);

	prios = config->prios;
	क्रम (reg_off = DAVINCI_AINTC_IRQ_INTPRI0_REG;
	     reg_off <= DAVINCI_AINTC_IRQ_INTPRI7_REG; reg_off += 4) अणु
		क्रम (shअगरt = 0, prio = 0; shअगरt < 32; shअगरt += 4, prios++)
			prio |= (*prios & 0x07) << shअगरt;
		davinci_aपूर्णांकc_ग_लिखोl(prio, reg_off);
	पूर्ण

	irq_base = irq_alloc_descs(-1, 0, config->num_irqs, 0);
	अगर (irq_base < 0) अणु
		pr_err("%s: unable to allocate interrupt descriptors: %d\n",
		       __func__, irq_base);
		वापस;
	पूर्ण

	davinci_aपूर्णांकc_irq_करोमुख्य = irq_करोमुख्य_add_legacy(शून्य,
						config->num_irqs, irq_base, 0,
						&irq_करोमुख्य_simple_ops, शून्य);
	अगर (!davinci_aपूर्णांकc_irq_करोमुख्य) अणु
		pr_err("%s: unable to create interrupt domain\n", __func__);
		वापस;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(davinci_aपूर्णांकc_irq_करोमुख्य, 32, 1,
					     "AINTC", handle_edge_irq,
					     IRQ_NOREQUEST | IRQ_NOPROBE, 0, 0);
	अगर (ret) अणु
		pr_err("%s: unable to allocate generic irq chips for domain\n",
		       __func__);
		वापस;
	पूर्ण

	क्रम (irq_off = 0, reg_off = 0;
	     irq_off < config->num_irqs;
	     irq_off += 32, reg_off += 0x04)
		davinci_aपूर्णांकc_setup_gc(davinci_aपूर्णांकc_base + reg_off,
				       irq_base + irq_off, 32);

	set_handle_irq(davinci_aपूर्णांकc_handle_irq);
पूर्ण
