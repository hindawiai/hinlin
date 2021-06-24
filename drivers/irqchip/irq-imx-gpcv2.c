<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */

#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/syscore_ops.h>

#घोषणा IMR_NUM			4
#घोषणा GPC_MAX_IRQS            (IMR_NUM * 32)

#घोषणा GPC_IMR1_CORE0		0x30
#घोषणा GPC_IMR1_CORE1		0x40
#घोषणा GPC_IMR1_CORE2		0x1c0
#घोषणा GPC_IMR1_CORE3		0x1d0


काष्ठा gpcv2_irqchip_data अणु
	काष्ठा raw_spinlock	rlock;
	व्योम __iomem		*gpc_base;
	u32			wakeup_sources[IMR_NUM];
	u32			saved_irq_mask[IMR_NUM];
	u32			cpu2wakeup;
पूर्ण;

अटल काष्ठा gpcv2_irqchip_data *imx_gpcv2_instance;

अटल व्योम __iomem *gpcv2_idx_to_reg(काष्ठा gpcv2_irqchip_data *cd, पूर्णांक i)
अणु
	वापस cd->gpc_base + cd->cpu2wakeup + i * 4;
पूर्ण

अटल पूर्णांक gpcv2_wakeup_source_save(व्योम)
अणु
	काष्ठा gpcv2_irqchip_data *cd;
	व्योम __iomem *reg;
	पूर्णांक i;

	cd = imx_gpcv2_instance;
	अगर (!cd)
		वापस 0;

	क्रम (i = 0; i < IMR_NUM; i++) अणु
		reg = gpcv2_idx_to_reg(cd, i);
		cd->saved_irq_mask[i] = पढ़ोl_relaxed(reg);
		ग_लिखोl_relaxed(cd->wakeup_sources[i], reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpcv2_wakeup_source_restore(व्योम)
अणु
	काष्ठा gpcv2_irqchip_data *cd;
	पूर्णांक i;

	cd = imx_gpcv2_instance;
	अगर (!cd)
		वापस;

	क्रम (i = 0; i < IMR_NUM; i++)
		ग_लिखोl_relaxed(cd->saved_irq_mask[i], gpcv2_idx_to_reg(cd, i));
पूर्ण

अटल काष्ठा syscore_ops imx_gpcv2_syscore_ops = अणु
	.suspend	= gpcv2_wakeup_source_save,
	.resume		= gpcv2_wakeup_source_restore,
पूर्ण;

अटल पूर्णांक imx_gpcv2_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpcv2_irqchip_data *cd = d->chip_data;
	अचिन्हित पूर्णांक idx = d->hwirq / 32;
	अचिन्हित दीर्घ flags;
	u32 mask, val;

	raw_spin_lock_irqsave(&cd->rlock, flags);
	mask = BIT(d->hwirq % 32);
	val = cd->wakeup_sources[idx];

	cd->wakeup_sources[idx] = on ? (val & ~mask) : (val | mask);
	raw_spin_unlock_irqrestore(&cd->rlock, flags);

	/*
	 * Do *not* call पूर्णांकo the parent, as the GIC करोesn't have any
	 * wake-up facility...
	 */

	वापस 0;
पूर्ण

अटल व्योम imx_gpcv2_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpcv2_irqchip_data *cd = d->chip_data;
	व्योम __iomem *reg;
	u32 val;

	raw_spin_lock(&cd->rlock);
	reg = gpcv2_idx_to_reg(cd, d->hwirq / 32);
	val = पढ़ोl_relaxed(reg);
	val &= ~BIT(d->hwirq % 32);
	ग_लिखोl_relaxed(val, reg);
	raw_spin_unlock(&cd->rlock);

	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम imx_gpcv2_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpcv2_irqchip_data *cd = d->chip_data;
	व्योम __iomem *reg;
	u32 val;

	raw_spin_lock(&cd->rlock);
	reg = gpcv2_idx_to_reg(cd, d->hwirq / 32);
	val = पढ़ोl_relaxed(reg);
	val |= BIT(d->hwirq % 32);
	ग_लिखोl_relaxed(val, reg);
	raw_spin_unlock(&cd->rlock);

	irq_chip_mask_parent(d);
पूर्ण

अटल काष्ठा irq_chip gpcv2_irqchip_data_chip = अणु
	.name			= "GPCv2",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= imx_gpcv2_irq_mask,
	.irq_unmask		= imx_gpcv2_irq_unmask,
	.irq_set_wake		= imx_gpcv2_irq_set_wake,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_type		= irq_chip_set_type_parent,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक imx_gpcv2_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा irq_fwspec *fwspec,
				      अचिन्हित दीर्घ *hwirq,
				      अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक imx_gpcv2_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				  अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक nr_irqs,
				  व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक err;
	पूर्णांक i;

	err = imx_gpcv2_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (err)
		वापस err;

	अगर (hwirq >= GPC_MAX_IRQS)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, irq + i, hwirq + i,
				&gpcv2_irqchip_data_chip, करोमुख्य->host_data);
	पूर्ण

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, irq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gpcv2_irqchip_data_करोमुख्य_ops = अणु
	.translate	= imx_gpcv2_करोमुख्य_translate,
	.alloc		= imx_gpcv2_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gpcv2_of_match[] = अणु
	अणु .compatible = "fsl,imx7d-gpc",  .data = (स्थिर व्योम *) 2 पूर्ण,
	अणु .compatible = "fsl,imx8mq-gpc", .data = (स्थिर व्योम *) 4 पूर्ण,
	अणु /* END */ पूर्ण
पूर्ण;

अटल पूर्णांक __init imx_gpcv2_irqchip_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	काष्ठा gpcv2_irqchip_data *cd;
	स्थिर काष्ठा of_device_id *id;
	अचिन्हित दीर्घ core_num;
	पूर्णांक i;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	id = of_match_node(gpcv2_of_match, node);
	अगर (!id) अणु
		pr_err("%pOF: unknown compatibility string\n", node);
		वापस -ENODEV;
	पूर्ण

	core_num = (अचिन्हित दीर्घ)id->data;

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to get parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	cd = kzalloc(माप(काष्ठा gpcv2_irqchip_data), GFP_KERNEL);
	अगर (!cd) अणु
		pr_err("%pOF: kzalloc failed!\n", node);
		वापस -ENOMEM;
	पूर्ण

	raw_spin_lock_init(&cd->rlock);

	cd->gpc_base = of_iomap(node, 0);
	अगर (!cd->gpc_base) अणु
		pr_err("%pOF: unable to map gpc registers\n", node);
		kमुक्त(cd);
		वापस -ENOMEM;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, GPC_MAX_IRQS,
				node, &gpcv2_irqchip_data_करोमुख्य_ops, cd);
	अगर (!करोमुख्य) अणु
		iounmap(cd->gpc_base);
		kमुक्त(cd);
		वापस -ENOMEM;
	पूर्ण
	irq_set_शेष_host(करोमुख्य);

	/* Initially mask all पूर्णांकerrupts */
	क्रम (i = 0; i < IMR_NUM; i++) अणु
		व्योम __iomem *reg = cd->gpc_base + i * 4;

		चयन (core_num) अणु
		हाल 4:
			ग_लिखोl_relaxed(~0, reg + GPC_IMR1_CORE2);
			ग_लिखोl_relaxed(~0, reg + GPC_IMR1_CORE3);
			fallthrough;
		हाल 2:
			ग_लिखोl_relaxed(~0, reg + GPC_IMR1_CORE0);
			ग_लिखोl_relaxed(~0, reg + GPC_IMR1_CORE1);
		पूर्ण
		cd->wakeup_sources[i] = ~0;
	पूर्ण

	/* Let CORE0 as the शेष CPU to wake up by GPC */
	cd->cpu2wakeup = GPC_IMR1_CORE0;

	/*
	 * Due to hardware design failure, need to make sure GPR
	 * पूर्णांकerrupt(#32) is unmasked during RUN mode to aव्योम entering
	 * DSM by mistake.
	 */
	ग_लिखोl_relaxed(~0x1, cd->gpc_base + cd->cpu2wakeup);

	imx_gpcv2_instance = cd;
	रेजिस्टर_syscore_ops(&imx_gpcv2_syscore_ops);

	/*
	 * Clear the OF_POPULATED flag set in of_irq_init so that
	 * later the GPC घातer करोमुख्य driver will not be skipped.
	 */
	of_node_clear_flag(node, OF_POPULATED);
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(imx_gpcv2_imx7d, "fsl,imx7d-gpc", imx_gpcv2_irqchip_init);
IRQCHIP_DECLARE(imx_gpcv2_imx8mq, "fsl,imx8mq-gpc", imx_gpcv2_irqchip_init);
