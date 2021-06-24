<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Abilis Systems पूर्णांकerrupt controller driver
 *
 * Copyright (C) Abilis Systems 2012
 *
 * Author: Christian Ruppert <christian.ruppert@abilis.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

#घोषणा AB_IRQCTL_INT_ENABLE   0x00
#घोषणा AB_IRQCTL_INT_STATUS   0x04
#घोषणा AB_IRQCTL_SRC_MODE     0x08
#घोषणा AB_IRQCTL_SRC_POLARITY 0x0C
#घोषणा AB_IRQCTL_INT_MODE     0x10
#घोषणा AB_IRQCTL_INT_POLARITY 0x14
#घोषणा AB_IRQCTL_INT_FORCE    0x18

#घोषणा AB_IRQCTL_MAXIRQ       32

अटल अंतरभूत व्योम ab_irqctl_ग_लिखोreg(काष्ठा irq_chip_generic *gc, u32 reg,
	u32 val)
अणु
	irq_reg_ग_लिखोl(gc, val, reg);
पूर्ण

अटल अंतरभूत u32 ab_irqctl_पढ़ोreg(काष्ठा irq_chip_generic *gc, u32 reg)
अणु
	वापस irq_reg_पढ़ोl(gc, reg);
पूर्ण

अटल पूर्णांक tb10x_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	uपूर्णांक32_t im, mod, pol;

	im = data->mask;

	irq_gc_lock(gc);

	mod = ab_irqctl_पढ़ोreg(gc, AB_IRQCTL_SRC_MODE) | im;
	pol = ab_irqctl_पढ़ोreg(gc, AB_IRQCTL_SRC_POLARITY) | im;

	चयन (flow_type & IRQF_TRIGGER_MASK) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		pol ^= im;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		mod ^= im;
		अवरोध;
	हाल IRQ_TYPE_NONE:
		flow_type = IRQ_TYPE_LEVEL_LOW;
		fallthrough;
	हाल IRQ_TYPE_LEVEL_LOW:
		mod ^= im;
		pol ^= im;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		अवरोध;
	शेष:
		irq_gc_unlock(gc);
		pr_err("%s: Cannot assign multiple trigger modes to IRQ %d.\n",
			__func__, data->irq);
		वापस -EBADR;
	पूर्ण

	irqd_set_trigger_type(data, flow_type);
	irq_setup_alt_chip(data, flow_type);

	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_SRC_MODE, mod);
	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_SRC_POLARITY, pol);
	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_INT_STATUS, im);

	irq_gc_unlock(gc);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम tb10x_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);

	generic_handle_irq(irq_find_mapping(करोमुख्य, irq));
पूर्ण

अटल पूर्णांक __init of_tb10x_init_irq(काष्ठा device_node *ictl,
					काष्ठा device_node *parent)
अणु
	पूर्णांक i, ret, nrirqs = of_irq_count(ictl);
	काष्ठा resource mem;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *reg_base;

	अगर (of_address_to_resource(ictl, 0, &mem)) अणु
		pr_err("%pOFn: No registers declared in DeviceTree.\n",
			ictl);
		वापस -EINVAL;
	पूर्ण

	अगर (!request_mem_region(mem.start, resource_size(&mem),
		ictl->full_name)) अणु
		pr_err("%pOFn: Request mem region failed.\n", ictl);
		वापस -EBUSY;
	पूर्ण

	reg_base = ioremap(mem.start, resource_size(&mem));
	अगर (!reg_base) अणु
		ret = -EBUSY;
		pr_err("%pOFn: ioremap failed.\n", ictl);
		जाओ ioremap_fail;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(ictl, AB_IRQCTL_MAXIRQ,
					&irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		ret = -ENOMEM;
		pr_err("%pOFn: Could not register interrupt domain.\n",
			ictl);
		जाओ irq_करोमुख्य_add_fail;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, AB_IRQCTL_MAXIRQ,
				2, ictl->name, handle_level_irq,
				IRQ_NOREQUEST, IRQ_NOPROBE,
				IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("%pOFn: Could not allocate generic interrupt chip.\n",
			ictl);
		जाओ gc_alloc_fail;
	पूर्ण

	gc = करोमुख्य->gc->gc[0];
	gc->reg_base                         = reg_base;

	gc->chip_types[0].type               = IRQ_TYPE_LEVEL_MASK;
	gc->chip_types[0].chip.irq_mask      = irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask    = irq_gc_mask_set_bit;
	gc->chip_types[0].chip.irq_set_type  = tb10x_irq_set_type;
	gc->chip_types[0].regs.mask          = AB_IRQCTL_INT_ENABLE;

	gc->chip_types[1].type               = IRQ_TYPE_EDGE_BOTH;
	gc->chip_types[1].chip.name          = gc->chip_types[0].chip.name;
	gc->chip_types[1].chip.irq_ack       = irq_gc_ack_set_bit;
	gc->chip_types[1].chip.irq_mask      = irq_gc_mask_clr_bit;
	gc->chip_types[1].chip.irq_unmask    = irq_gc_mask_set_bit;
	gc->chip_types[1].chip.irq_set_type  = tb10x_irq_set_type;
	gc->chip_types[1].regs.ack           = AB_IRQCTL_INT_STATUS;
	gc->chip_types[1].regs.mask          = AB_IRQCTL_INT_ENABLE;
	gc->chip_types[1].handler            = handle_edge_irq;

	क्रम (i = 0; i < nrirqs; i++) अणु
		अचिन्हित पूर्णांक irq = irq_of_parse_and_map(ictl, i);

		irq_set_chained_handler_and_data(irq, tb10x_irq_cascade,
						 करोमुख्य);
	पूर्ण

	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_INT_ENABLE, 0);
	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_INT_MODE, 0);
	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_INT_POLARITY, 0);
	ab_irqctl_ग_लिखोreg(gc, AB_IRQCTL_INT_STATUS, ~0UL);

	वापस 0;

gc_alloc_fail:
	irq_करोमुख्य_हटाओ(करोमुख्य);
irq_करोमुख्य_add_fail:
	iounmap(reg_base);
ioremap_fail:
	release_mem_region(mem.start, resource_size(&mem));
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(tb10x_पूर्णांकc, "abilis,tb10x-ictl", of_tb10x_init_irq);
