<शैली गुरु>
/*
 * Support क्रम hardware-managed IRQ स्वतः-distribution.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश "internals.h"

अटल अचिन्हित दीर्घ dist_handle[INTC_NR_IRQS];

व्योम पूर्णांकc_balancing_enable(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित दीर्घ handle = dist_handle[irq];
	अचिन्हित दीर्घ addr;

	अगर (irq_balancing_disabled(irq) || !handle)
		वापस;

	addr = INTC_REG(d, _INTC_ADDR_D(handle), 0);
	पूर्णांकc_reg_fns[_INTC_FN(handle)](addr, handle, 1);
पूर्ण

व्योम पूर्णांकc_balancing_disable(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित दीर्घ handle = dist_handle[irq];
	अचिन्हित दीर्घ addr;

	अगर (irq_balancing_disabled(irq) || !handle)
		वापस;

	addr = INTC_REG(d, _INTC_ADDR_D(handle), 0);
	पूर्णांकc_reg_fns[_INTC_FN(handle)](addr, handle, 0);
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकc_dist_data(काष्ठा पूर्णांकc_desc *desc,
				   काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				   पूर्णांकc_क्रमागत क्रमागत_id)
अणु
	काष्ठा पूर्णांकc_mask_reg *mr = desc->hw.mask_regs;
	अचिन्हित पूर्णांक i, j, fn, mode;
	अचिन्हित दीर्घ reg_e, reg_d;

	क्रम (i = 0; mr && क्रमागत_id && i < desc->hw.nr_mask_regs; i++) अणु
		mr = desc->hw.mask_regs + i;

		/*
		 * Skip this entry अगर there's no स्वतः-distribution
		 * रेजिस्टर associated with it.
		 */
		अगर (!mr->dist_reg)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(mr->क्रमागत_ids); j++) अणु
			अगर (mr->क्रमागत_ids[j] != क्रमागत_id)
				जारी;

			fn = REG_FN_MODIFY_BASE;
			mode = MODE_ENABLE_REG;
			reg_e = mr->dist_reg;
			reg_d = mr->dist_reg;

			fn += (mr->reg_width >> 3) - 1;
			वापस _INTC_MK(fn, mode,
					पूर्णांकc_get_reg(d, reg_e),
					पूर्णांकc_get_reg(d, reg_d),
					1,
					(mr->reg_width - 1) - j);
		पूर्ण
	पूर्ण

	/*
	 * It's possible we've gotten here with no distribution options
	 * available क्रम the IRQ in question, so we just skip over those.
	 */
	वापस 0;
पूर्ण

व्योम पूर्णांकc_set_dist_handle(अचिन्हित पूर्णांक irq, काष्ठा पूर्णांकc_desc *desc,
			  काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत id)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Nothing to करो क्रम this IRQ.
	 */
	अगर (!desc->hw.mask_regs)
		वापस;

	raw_spin_lock_irqsave(&पूर्णांकc_big_lock, flags);
	dist_handle[irq] = पूर्णांकc_dist_data(desc, d, id);
	raw_spin_unlock_irqrestore(&पूर्णांकc_big_lock, flags);
पूर्ण
