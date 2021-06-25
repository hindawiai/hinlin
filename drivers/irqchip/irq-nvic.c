<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/irq/irq-nvic.c
 *
 * Copyright (C) 2008 ARM Limited, All Rights Reserved.
 * Copyright (C) 2013 Pengutronix
 *
 * Support क्रम the Nested Vectored Interrupt Controller found on the
 * ARMv7-M CPUs (Cortex-M3/M4)
 */
#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/v7m.h>
#समावेश <यंत्र/exception.h>

#घोषणा NVIC_ISER		0x000
#घोषणा NVIC_ICER		0x080
#घोषणा NVIC_IPR		0x300

#घोषणा NVIC_MAX_BANKS		16
/*
 * Each bank handles 32 irqs. Only the 16th (= last) bank handles only
 * 16 irqs.
 */
#घोषणा NVIC_MAX_IRQ		((NVIC_MAX_BANKS - 1) * 32 + 16)

अटल काष्ठा irq_करोमुख्य *nvic_irq_करोमुख्य;

यंत्रlinkage व्योम __exception_irq_entry
nvic_handle_irq(irq_hw_number_t hwirq, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक irq = irq_linear_revmap(nvic_irq_करोमुख्य, hwirq);

	handle_IRQ(irq, regs);
पूर्ण

अटल पूर्णांक nvic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i, ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = arg;

	ret = irq_करोमुख्य_translate_onecell(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_map_generic_chip(करोमुख्य, virq + i, hwirq + i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops nvic_irq_करोमुख्य_ops = अणु
	.translate = irq_करोमुख्य_translate_onecell,
	.alloc = nvic_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_top,
पूर्ण;

अटल पूर्णांक __init nvic_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	अचिन्हित पूर्णांक irqs, i, ret, numbanks;
	व्योम __iomem *nvic_base;

	numbanks = (पढ़ोl_relaxed(V7M_SCS_ICTR) &
		    V7M_SCS_ICTR_INTLINESNUM_MASK) + 1;

	nvic_base = of_iomap(node, 0);
	अगर (!nvic_base) अणु
		pr_warn("unable to map nvic registers\n");
		वापस -ENOMEM;
	पूर्ण

	irqs = numbanks * 32;
	अगर (irqs > NVIC_MAX_IRQ)
		irqs = NVIC_MAX_IRQ;

	nvic_irq_करोमुख्य =
		irq_करोमुख्य_add_linear(node, irqs, &nvic_irq_करोमुख्य_ops, शून्य);

	अगर (!nvic_irq_करोमुख्य) अणु
		pr_warn("Failed to allocate irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(nvic_irq_करोमुख्य, 32, 1,
					     "nvic_irq", handle_fasteoi_irq,
					     clr, 0, IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_warn("Failed to allocate irq chips\n");
		irq_करोमुख्य_हटाओ(nvic_irq_करोमुख्य);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < numbanks; ++i) अणु
		काष्ठा irq_chip_generic *gc;

		gc = irq_get_करोमुख्य_generic_chip(nvic_irq_करोमुख्य, 32 * i);
		gc->reg_base = nvic_base + 4 * i;
		gc->chip_types[0].regs.enable = NVIC_ISER;
		gc->chip_types[0].regs.disable = NVIC_ICER;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_disable_reg;
		gc->chip_types[0].chip.irq_unmask = irq_gc_unmask_enable_reg;
		/* This is a no-op as end of पूर्णांकerrupt is संकेतed by the
		 * exception वापस sequence.
		 */
		gc->chip_types[0].chip.irq_eoi = irq_gc_noop;

		/* disable पूर्णांकerrupts */
		ग_लिखोl_relaxed(~0, gc->reg_base + NVIC_ICER);
	पूर्ण

	/* Set priority on all पूर्णांकerrupts */
	क्रम (i = 0; i < irqs; i += 4)
		ग_लिखोl_relaxed(0, nvic_base + NVIC_IPR + i);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(armv7m_nvic, "arm,armv7m-nvic", nvic_of_init);
