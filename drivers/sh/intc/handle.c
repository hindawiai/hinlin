<शैली गुरु>
/*
 * Shared पूर्णांकerrupt handling code क्रम IPR and INTC2 types of IRQs.
 *
 * Copyright (C) 2007, 2008 Magnus Damm
 * Copyright (C) 2009, 2010 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश "internals.h"

अटल अचिन्हित दीर्घ ack_handle[INTC_NR_IRQS];

अटल पूर्णांकc_क्रमागत __init पूर्णांकc_grp_id(काष्ठा पूर्णांकc_desc *desc,
				    पूर्णांकc_क्रमागत क्रमागत_id)
अणु
	काष्ठा पूर्णांकc_group *g = desc->hw.groups;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; g && क्रमागत_id && i < desc->hw.nr_groups; i++) अणु
		g = desc->hw.groups + i;

		क्रम (j = 0; g->क्रमागत_ids[j]; j++) अणु
			अगर (g->क्रमागत_ids[j] != क्रमागत_id)
				जारी;

			वापस g->क्रमागत_id;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __init _पूर्णांकc_mask_data(काष्ठा पूर्णांकc_desc *desc,
					   काष्ठा पूर्णांकc_desc_पूर्णांक *d,
					   पूर्णांकc_क्रमागत क्रमागत_id,
					   अचिन्हित पूर्णांक *reg_idx,
					   अचिन्हित पूर्णांक *fld_idx)
अणु
	काष्ठा पूर्णांकc_mask_reg *mr = desc->hw.mask_regs;
	अचिन्हित पूर्णांक fn, mode;
	अचिन्हित दीर्घ reg_e, reg_d;

	जबतक (mr && क्रमागत_id && *reg_idx < desc->hw.nr_mask_regs) अणु
		mr = desc->hw.mask_regs + *reg_idx;

		क्रम (; *fld_idx < ARRAY_SIZE(mr->क्रमागत_ids); (*fld_idx)++) अणु
			अगर (mr->क्रमागत_ids[*fld_idx] != क्रमागत_id)
				जारी;

			अगर (mr->set_reg && mr->clr_reg) अणु
				fn = REG_FN_WRITE_BASE;
				mode = MODE_DUAL_REG;
				reg_e = mr->clr_reg;
				reg_d = mr->set_reg;
			पूर्ण अन्यथा अणु
				fn = REG_FN_MODIFY_BASE;
				अगर (mr->set_reg) अणु
					mode = MODE_ENABLE_REG;
					reg_e = mr->set_reg;
					reg_d = mr->set_reg;
				पूर्ण अन्यथा अणु
					mode = MODE_MASK_REG;
					reg_e = mr->clr_reg;
					reg_d = mr->clr_reg;
				पूर्ण
			पूर्ण

			fn += (mr->reg_width >> 3) - 1;
			वापस _INTC_MK(fn, mode,
					पूर्णांकc_get_reg(d, reg_e),
					पूर्णांकc_get_reg(d, reg_d),
					1,
					(mr->reg_width - 1) - *fld_idx);
		पूर्ण

		*fld_idx = 0;
		(*reg_idx)++;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक __init
पूर्णांकc_get_mask_handle(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d,
		     पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक करो_grps)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक j = 0;
	अचिन्हित पूर्णांक ret;

	ret = _पूर्णांकc_mask_data(desc, d, क्रमागत_id, &i, &j);
	अगर (ret)
		वापस ret;

	अगर (करो_grps)
		वापस पूर्णांकc_get_mask_handle(desc, d, पूर्णांकc_grp_id(desc, क्रमागत_id), 0);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __init _पूर्णांकc_prio_data(काष्ठा पूर्णांकc_desc *desc,
					   काष्ठा पूर्णांकc_desc_पूर्णांक *d,
					   पूर्णांकc_क्रमागत क्रमागत_id,
					   अचिन्हित पूर्णांक *reg_idx,
					   अचिन्हित पूर्णांक *fld_idx)
अणु
	काष्ठा पूर्णांकc_prio_reg *pr = desc->hw.prio_regs;
	अचिन्हित पूर्णांक fn, n, mode, bit;
	अचिन्हित दीर्घ reg_e, reg_d;

	जबतक (pr && क्रमागत_id && *reg_idx < desc->hw.nr_prio_regs) अणु
		pr = desc->hw.prio_regs + *reg_idx;

		क्रम (; *fld_idx < ARRAY_SIZE(pr->क्रमागत_ids); (*fld_idx)++) अणु
			अगर (pr->क्रमागत_ids[*fld_idx] != क्रमागत_id)
				जारी;

			अगर (pr->set_reg && pr->clr_reg) अणु
				fn = REG_FN_WRITE_BASE;
				mode = MODE_PCLR_REG;
				reg_e = pr->set_reg;
				reg_d = pr->clr_reg;
			पूर्ण अन्यथा अणु
				fn = REG_FN_MODIFY_BASE;
				mode = MODE_PRIO_REG;
				अगर (!pr->set_reg)
					BUG();
				reg_e = pr->set_reg;
				reg_d = pr->set_reg;
			पूर्ण

			fn += (pr->reg_width >> 3) - 1;
			n = *fld_idx + 1;

			BUG_ON(n * pr->field_width > pr->reg_width);

			bit = pr->reg_width - (n * pr->field_width);

			वापस _INTC_MK(fn, mode,
					पूर्णांकc_get_reg(d, reg_e),
					पूर्णांकc_get_reg(d, reg_d),
					pr->field_width, bit);
		पूर्ण

		*fld_idx = 0;
		(*reg_idx)++;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक __init
पूर्णांकc_get_prio_handle(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d,
		     पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक करो_grps)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक j = 0;
	अचिन्हित पूर्णांक ret;

	ret = _पूर्णांकc_prio_data(desc, d, क्रमागत_id, &i, &j);
	अगर (ret)
		वापस ret;

	अगर (करो_grps)
		वापस पूर्णांकc_get_prio_handle(desc, d, पूर्णांकc_grp_id(desc, क्रमागत_id), 0);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकc_ack_data(काष्ठा पूर्णांकc_desc *desc,
				  काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत क्रमागत_id)
अणु
	काष्ठा पूर्णांकc_mask_reg *mr = desc->hw.ack_regs;
	अचिन्हित पूर्णांक i, j, fn, mode;
	अचिन्हित दीर्घ reg_e, reg_d;

	क्रम (i = 0; mr && क्रमागत_id && i < desc->hw.nr_ack_regs; i++) अणु
		mr = desc->hw.ack_regs + i;

		क्रम (j = 0; j < ARRAY_SIZE(mr->क्रमागत_ids); j++) अणु
			अगर (mr->क्रमागत_ids[j] != क्रमागत_id)
				जारी;

			fn = REG_FN_MODIFY_BASE;
			mode = MODE_ENABLE_REG;
			reg_e = mr->set_reg;
			reg_d = mr->set_reg;

			fn += (mr->reg_width >> 3) - 1;
			वापस _INTC_MK(fn, mode,
					पूर्णांकc_get_reg(d, reg_e),
					पूर्णांकc_get_reg(d, reg_d),
					1,
					(mr->reg_width - 1) - j);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकc_enable_disable(काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				अचिन्हित दीर्घ handle, पूर्णांक करो_enable)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		   अचिन्हित दीर्घ (*)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				     अचिन्हित दीर्घ),
		   अचिन्हित पूर्णांक);

	अगर (करो_enable) अणु
		क्रम (cpu = 0; cpu < SMP_NR(d, _INTC_ADDR_E(handle)); cpu++) अणु
			addr = INTC_REG(d, _INTC_ADDR_E(handle), cpu);
			fn = पूर्णांकc_enable_noprio_fns[_INTC_MODE(handle)];
			fn(addr, handle, पूर्णांकc_reg_fns[_INTC_FN(handle)], 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (cpu = 0; cpu < SMP_NR(d, _INTC_ADDR_D(handle)); cpu++) अणु
			addr = INTC_REG(d, _INTC_ADDR_D(handle), cpu);
			fn = पूर्णांकc_disable_fns[_INTC_MODE(handle)];
			fn(addr, handle, पूर्णांकc_reg_fns[_INTC_FN(handle)], 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init पूर्णांकc_enable_disable_क्रमागत(काष्ठा पूर्णांकc_desc *desc,
				     काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				     पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक i, j, data;

	/* go through and enable/disable all mask bits */
	i = j = 0;
	करो अणु
		data = _पूर्णांकc_mask_data(desc, d, क्रमागत_id, &i, &j);
		अगर (data)
			पूर्णांकc_enable_disable(d, data, enable);
		j++;
	पूर्ण जबतक (data);

	/* go through and enable/disable all priority fields */
	i = j = 0;
	करो अणु
		data = _पूर्णांकc_prio_data(desc, d, क्रमागत_id, &i, &j);
		अगर (data)
			पूर्णांकc_enable_disable(d, data, enable);

		j++;
	पूर्ण जबतक (data);
पूर्ण

अचिन्हित पूर्णांक __init
पूर्णांकc_get_sense_handle(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d,
		      पूर्णांकc_क्रमागत क्रमागत_id)
अणु
	काष्ठा पूर्णांकc_sense_reg *sr = desc->hw.sense_regs;
	अचिन्हित पूर्णांक i, j, fn, bit;

	क्रम (i = 0; sr && क्रमागत_id && i < desc->hw.nr_sense_regs; i++) अणु
		sr = desc->hw.sense_regs + i;

		क्रम (j = 0; j < ARRAY_SIZE(sr->क्रमागत_ids); j++) अणु
			अगर (sr->क्रमागत_ids[j] != क्रमागत_id)
				जारी;

			fn = REG_FN_MODIFY_BASE;
			fn += (sr->reg_width >> 3) - 1;

			BUG_ON((j + 1) * sr->field_width > sr->reg_width);

			bit = sr->reg_width - ((j + 1) * sr->field_width);

			वापस _INTC_MK(fn, 0, पूर्णांकc_get_reg(d, sr->reg),
					0, sr->field_width, bit);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


व्योम पूर्णांकc_set_ack_handle(अचिन्हित पूर्णांक irq, काष्ठा पूर्णांकc_desc *desc,
			 काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत id)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Nothing to करो क्रम this IRQ.
	 */
	अगर (!desc->hw.ack_regs)
		वापस;

	raw_spin_lock_irqsave(&पूर्णांकc_big_lock, flags);
	ack_handle[irq] = पूर्णांकc_ack_data(desc, d, id);
	raw_spin_unlock_irqrestore(&पूर्णांकc_big_lock, flags);
पूर्ण

अचिन्हित दीर्घ पूर्णांकc_get_ack_handle(अचिन्हित पूर्णांक irq)
अणु
	वापस ack_handle[irq];
पूर्ण
