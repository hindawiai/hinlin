<शैली गुरु>
/*
 * IRQ करोमुख्य support क्रम SH INTC subप्रणाली
 *
 * Copyright (C) 2012  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "intc: " fmt

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/export.h>
#समावेश "internals.h"

/**
 * पूर्णांकc_irq_करोमुख्य_evt_xlate() - Generic xlate क्रम vectored IRQs.
 *
 * This takes care of exception vector to hwirq translation through
 * by way of evt2irq() translation.
 *
 * Note: For platक्रमms that use a flat vector space without INTEVT this
 * basically just mimics irq_करोमुख्य_xlate_onecell() by way of a nopped
 * out evt2irq() implementation.
 */
अटल पूर्णांक पूर्णांकc_evt_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			  स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			  अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 1))
		वापस -EINVAL;

	*out_hwirq = evt2irq(पूर्णांकspec[0]);
	*out_type = IRQ_TYPE_NONE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकc_evt_ops = अणु
	.xlate		= पूर्णांकc_evt_xlate,
पूर्ण;

व्योम __init पूर्णांकc_irq_करोमुख्य_init(काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				 काष्ठा पूर्णांकc_hw_desc *hw)
अणु
	अचिन्हित पूर्णांक irq_base, irq_end;

	/*
	 * Quick linear revmap check
	 */
	irq_base = evt2irq(hw->vectors[0].vect);
	irq_end = evt2irq(hw->vectors[hw->nr_vectors - 1].vect);

	/*
	 * Linear करोमुख्यs have a hard-wired निश्चितion that IRQs start at
	 * 0 in order to make some perक्रमmance optimizations. Lamely
	 * restrict the linear हाल to these conditions here, taking the
	 * tree penalty क्रम linear हालs with non-zero hwirq bases.
	 */
	अगर (irq_base == 0 && irq_end == (irq_base + hw->nr_vectors - 1))
		d->करोमुख्य = irq_करोमुख्य_add_linear(शून्य, hw->nr_vectors,
						  &पूर्णांकc_evt_ops, शून्य);
	अन्यथा
		d->करोमुख्य = irq_करोमुख्य_add_tree(शून्य, &पूर्णांकc_evt_ops, शून्य);

	BUG_ON(!d->करोमुख्य);
पूर्ण
