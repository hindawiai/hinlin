<शैली गुरु>
/*
 * arch/arm/plat-orion/irq.c
 *
 * Marvell Orion SoC IRQ handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <plat/irq.h>
#समावेश <plat/orion-gpपन.स>

व्योम __init orion_irq_init(अचिन्हित पूर्णांक irq_start, व्योम __iomem *maskaddr)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	/*
	 * Mask all पूर्णांकerrupts initially.
	 */
	ग_लिखोl(0, maskaddr);

	gc = irq_alloc_generic_chip("orion_irq", 1, irq_start, maskaddr,
				    handle_level_irq);
	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	irq_setup_generic_chip(gc, IRQ_MSK(32), IRQ_GC_INIT_MASK_CACHE,
			       IRQ_NOREQUEST, IRQ_LEVEL | IRQ_NOPROBE);
पूर्ण
