<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <nds32_पूर्णांकrinsic.h>

अचिन्हित दीर्घ wake_mask;

अटल व्योम ativic32_ack_irq(काष्ठा irq_data *data)
अणु
	__nds32__mtsr_dsb(BIT(data->hwirq), NDS32_SR_INT_PEND2);
पूर्ण

अटल व्योम ativic32_mask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ पूर्णांक_mask2 = __nds32__mfsr(NDS32_SR_INT_MASK2);
	__nds32__mtsr_dsb(पूर्णांक_mask2 & (~(BIT(data->hwirq))), NDS32_SR_INT_MASK2);
पूर्ण

अटल व्योम ativic32_unmask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ पूर्णांक_mask2 = __nds32__mfsr(NDS32_SR_INT_MASK2);
	__nds32__mtsr_dsb(पूर्णांक_mask2 | (BIT(data->hwirq)), NDS32_SR_INT_MASK2);
पूर्ण

अटल पूर्णांक noपूर्णांकc_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ पूर्णांक_mask = __nds32__mfsr(NDS32_SR_INT_MASK);
	अटल अचिन्हित दीर्घ irq_orig_bit;
	u32 bit = 1 << data->hwirq;

	अगर (on) अणु
		अगर (पूर्णांक_mask & bit)
			__assign_bit(data->hwirq, &irq_orig_bit, true);
		अन्यथा
			__assign_bit(data->hwirq, &irq_orig_bit, false);

		__assign_bit(data->hwirq, &पूर्णांक_mask, true);
		__assign_bit(data->hwirq, &wake_mask, true);

	पूर्ण अन्यथा अणु
		अगर (!(irq_orig_bit & bit))
			__assign_bit(data->hwirq, &पूर्णांक_mask, false);

		__assign_bit(data->hwirq, &wake_mask, false);
		__assign_bit(data->hwirq, &irq_orig_bit, false);
	पूर्ण

	__nds32__mtsr_dsb(पूर्णांक_mask, NDS32_SR_INT_MASK);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ativic32_chip = अणु
	.name = "ativic32",
	.irq_ack = ativic32_ack_irq,
	.irq_mask = ativic32_mask_irq,
	.irq_unmask = ativic32_unmask_irq,
	.irq_set_wake = noपूर्णांकc_set_wake,
पूर्ण;

अटल अचिन्हित पूर्णांक __initdata nivic_map[6] = अणु 6, 2, 10, 16, 24, 32 पूर्ण;

अटल काष्ठा irq_करोमुख्य *root_करोमुख्य;
अटल पूर्णांक ativic32_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *id, अचिन्हित पूर्णांक virq,
				  irq_hw_number_t hw)
अणु

	अचिन्हित दीर्घ पूर्णांक_trigger_type;
	u32 type;
	काष्ठा irq_data *irq_data;
	पूर्णांक_trigger_type = __nds32__mfsr(NDS32_SR_INT_TRIGGER);
	irq_data = irq_get_irq_data(virq);
	अगर (!irq_data)
		वापस -EINVAL;

	अगर (पूर्णांक_trigger_type & (BIT(hw))) अणु
		irq_set_chip_and_handler(virq, &ativic32_chip, handle_edge_irq);
		type = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(virq, &ativic32_chip, handle_level_irq);
		type = IRQ_TYPE_LEVEL_HIGH;
	पूर्ण

	irqd_set_trigger_type(irq_data, type);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ativic32_ops = अणु
	.map = ativic32_irq_करोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell
पूर्ण;

अटल irq_hw_number_t get_पूर्णांकr_src(व्योम)
अणु
	वापस ((__nds32__mfsr(NDS32_SR_ITYPE) & ITYPE_mskVECTOR) >> ITYPE_offVECTOR)
		- NDS32_VECTOR_offINTERRUPT;
पूर्ण

यंत्रlinkage व्योम यंत्र_करो_IRQ(काष्ठा pt_regs *regs)
अणु
	irq_hw_number_t hwirq = get_पूर्णांकr_src();
	handle_करोमुख्य_irq(root_करोमुख्य, hwirq, regs);
पूर्ण

पूर्णांक __init ativic32_init_irq(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	अचिन्हित दीर्घ पूर्णांक_vec_base, nivic, nr_पूर्णांकs;

	अगर (WARN(parent, "non-root ativic32 are not supported"))
		वापस -EINVAL;

	पूर्णांक_vec_base = __nds32__mfsr(NDS32_SR_IVB);

	अगर (((पूर्णांक_vec_base & IVB_mskIVIC_VER) >> IVB_offIVIC_VER) == 0)
		panic("Unable to use atcivic32 for this cpu.\n");

	nivic = (पूर्णांक_vec_base & IVB_mskNIVIC) >> IVB_offNIVIC;
	अगर (nivic >= ARRAY_SIZE(nivic_map))
		panic("The number of input for ativic32 is not supported.\n");

	nr_पूर्णांकs = nivic_map[nivic];

	root_करोमुख्य = irq_करोमुख्य_add_linear(node, nr_पूर्णांकs,
			&ativic32_ops, शून्य);

	अगर (!root_करोमुख्य)
		panic("%s: unable to create IRQ domain\n", node->full_name);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(ativic32, "andestech,ativic32", ativic32_init_irq);
