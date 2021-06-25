<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver code क्रम Tegra's Legacy Interrupt Controller
 *
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Heavily based on the original arch/arm/mach-tegra/irq.c code:
 * Copyright (C) 2011 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@android.com>
 *
 * Copyright (C) 2010,2013, NVIDIA Corporation
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा ICTLR_CPU_IEP_VFIQ	0x08
#घोषणा ICTLR_CPU_IEP_FIR	0x14
#घोषणा ICTLR_CPU_IEP_FIR_SET	0x18
#घोषणा ICTLR_CPU_IEP_FIR_CLR	0x1c

#घोषणा ICTLR_CPU_IER		0x20
#घोषणा ICTLR_CPU_IER_SET	0x24
#घोषणा ICTLR_CPU_IER_CLR	0x28
#घोषणा ICTLR_CPU_IEP_CLASS	0x2C

#घोषणा ICTLR_COP_IER		0x30
#घोषणा ICTLR_COP_IER_SET	0x34
#घोषणा ICTLR_COP_IER_CLR	0x38
#घोषणा ICTLR_COP_IEP_CLASS	0x3c

#घोषणा TEGRA_MAX_NUM_ICTLRS	6

अटल अचिन्हित पूर्णांक num_ictlrs;

काष्ठा tegra_ictlr_soc अणु
	अचिन्हित पूर्णांक num_ictlrs;
पूर्ण;

अटल स्थिर काष्ठा tegra_ictlr_soc tegra20_ictlr_soc = अणु
	.num_ictlrs = 4,
पूर्ण;

अटल स्थिर काष्ठा tegra_ictlr_soc tegra30_ictlr_soc = अणु
	.num_ictlrs = 5,
पूर्ण;

अटल स्थिर काष्ठा tegra_ictlr_soc tegra210_ictlr_soc = अणु
	.num_ictlrs = 6,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ictlr_matches[] = अणु
	अणु .compatible = "nvidia,tegra210-ictlr", .data = &tegra210_ictlr_soc पूर्ण,
	अणु .compatible = "nvidia,tegra30-ictlr", .data = &tegra30_ictlr_soc पूर्ण,
	अणु .compatible = "nvidia,tegra20-ictlr", .data = &tegra20_ictlr_soc पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा tegra_ictlr_info अणु
	व्योम __iomem *base[TEGRA_MAX_NUM_ICTLRS];
#अगर_घोषित CONFIG_PM_SLEEP
	u32 cop_ier[TEGRA_MAX_NUM_ICTLRS];
	u32 cop_iep[TEGRA_MAX_NUM_ICTLRS];
	u32 cpu_ier[TEGRA_MAX_NUM_ICTLRS];
	u32 cpu_iep[TEGRA_MAX_NUM_ICTLRS];

	u32 ictlr_wake_mask[TEGRA_MAX_NUM_ICTLRS];
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा tegra_ictlr_info *lic;

अटल अंतरभूत व्योम tegra_ictlr_ग_लिखो_mask(काष्ठा irq_data *d, अचिन्हित दीर्घ reg)
अणु
	व्योम __iomem *base = (व्योम __iomem __क्रमce *)d->chip_data;
	u32 mask;

	mask = BIT(d->hwirq % 32);
	ग_लिखोl_relaxed(mask, base + reg);
पूर्ण

अटल व्योम tegra_mask(काष्ठा irq_data *d)
अणु
	tegra_ictlr_ग_लिखो_mask(d, ICTLR_CPU_IER_CLR);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम tegra_unmask(काष्ठा irq_data *d)
अणु
	tegra_ictlr_ग_लिखो_mask(d, ICTLR_CPU_IER_SET);
	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम tegra_eoi(काष्ठा irq_data *d)
अणु
	tegra_ictlr_ग_लिखो_mask(d, ICTLR_CPU_IEP_FIR_CLR);
	irq_chip_eoi_parent(d);
पूर्ण

अटल पूर्णांक tegra_retrigger(काष्ठा irq_data *d)
अणु
	tegra_ictlr_ग_लिखो_mask(d, ICTLR_CPU_IEP_FIR_SET);
	वापस irq_chip_retrigger_hierarchy(d);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	u32 irq = d->hwirq;
	u32 index, mask;

	index = (irq / 32);
	mask = BIT(irq % 32);
	अगर (enable)
		lic->ictlr_wake_mask[index] |= mask;
	अन्यथा
		lic->ictlr_wake_mask[index] &= ~mask;

	/*
	 * Do *not* call पूर्णांकo the parent, as the GIC करोesn't have any
	 * wake-up facility...
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_ictlr_suspend(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	local_irq_save(flags);
	क्रम (i = 0; i < num_ictlrs; i++) अणु
		व्योम __iomem *ictlr = lic->base[i];

		/* Save पूर्णांकerrupt state */
		lic->cpu_ier[i] = पढ़ोl_relaxed(ictlr + ICTLR_CPU_IER);
		lic->cpu_iep[i] = पढ़ोl_relaxed(ictlr + ICTLR_CPU_IEP_CLASS);
		lic->cop_ier[i] = पढ़ोl_relaxed(ictlr + ICTLR_COP_IER);
		lic->cop_iep[i] = पढ़ोl_relaxed(ictlr + ICTLR_COP_IEP_CLASS);

		/* Disable COP पूर्णांकerrupts */
		ग_लिखोl_relaxed(~0ul, ictlr + ICTLR_COP_IER_CLR);

		/* Disable CPU पूर्णांकerrupts */
		ग_लिखोl_relaxed(~0ul, ictlr + ICTLR_CPU_IER_CLR);

		/* Enable the wakeup sources of ictlr */
		ग_लिखोl_relaxed(lic->ictlr_wake_mask[i], ictlr + ICTLR_CPU_IER_SET);
	पूर्ण
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम tegra_ictlr_resume(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	local_irq_save(flags);
	क्रम (i = 0; i < num_ictlrs; i++) अणु
		व्योम __iomem *ictlr = lic->base[i];

		ग_लिखोl_relaxed(lic->cpu_iep[i],
			       ictlr + ICTLR_CPU_IEP_CLASS);
		ग_लिखोl_relaxed(~0ul, ictlr + ICTLR_CPU_IER_CLR);
		ग_लिखोl_relaxed(lic->cpu_ier[i],
			       ictlr + ICTLR_CPU_IER_SET);
		ग_लिखोl_relaxed(lic->cop_iep[i],
			       ictlr + ICTLR_COP_IEP_CLASS);
		ग_लिखोl_relaxed(~0ul, ictlr + ICTLR_COP_IER_CLR);
		ग_लिखोl_relaxed(lic->cop_ier[i],
			       ictlr + ICTLR_COP_IER_SET);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा syscore_ops tegra_ictlr_syscore_ops = अणु
	.suspend	= tegra_ictlr_suspend,
	.resume		= tegra_ictlr_resume,
पूर्ण;

अटल व्योम tegra_ictlr_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&tegra_ictlr_syscore_ops);
पूर्ण
#अन्यथा
#घोषणा tegra_set_wake	शून्य
अटल अंतरभूत व्योम tegra_ictlr_syscore_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip tegra_ictlr_chip = अणु
	.name			= "LIC",
	.irq_eoi		= tegra_eoi,
	.irq_mask		= tegra_mask,
	.irq_unmask		= tegra_unmask,
	.irq_retrigger		= tegra_retrigger,
	.irq_set_wake		= tegra_set_wake,
	.irq_set_type		= irq_chip_set_type_parent,
	.flags			= IRQCHIP_MASK_ON_SUSPEND,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक tegra_ictlr_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
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
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_ictlr_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq,
				    अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	काष्ठा tegra_ictlr_info *info = करोमुख्य->host_data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक i;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;	/* Not GIC compliant */
	अगर (fwspec->param[0] != GIC_SPI)
		वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

	hwirq = fwspec->param[1];
	अगर (hwirq >= (num_ictlrs * 32))
		वापस -EINVAL;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		पूर्णांक ictlr = (hwirq + i) / 32;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &tegra_ictlr_chip,
					      (व्योम __क्रमce *)info->base[ictlr]);
	पूर्ण

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tegra_ictlr_करोमुख्य_ops = अणु
	.translate	= tegra_ictlr_करोमुख्य_translate,
	.alloc		= tegra_ictlr_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init tegra_ictlr_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा tegra_ictlr_soc *soc;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	match = of_match_node(ictlr_matches, node);
	अगर (!match)		/* Should never happen... */
		वापस -ENODEV;

	soc = match->data;

	lic = kzalloc(माप(*lic), GFP_KERNEL);
	अगर (!lic)
		वापस -ENOMEM;

	क्रम (i = 0; i < TEGRA_MAX_NUM_ICTLRS; i++) अणु
		व्योम __iomem *base;

		base = of_iomap(node, i);
		अगर (!base)
			अवरोध;

		lic->base[i] = base;

		/* Disable all पूर्णांकerrupts */
		ग_लिखोl_relaxed(~0UL, base + ICTLR_CPU_IER_CLR);
		/* All पूर्णांकerrupts target IRQ */
		ग_लिखोl_relaxed(0, base + ICTLR_CPU_IEP_CLASS);

		num_ictlrs++;
	पूर्ण

	अगर (!num_ictlrs) अणु
		pr_err("%pOF: no valid regions, giving up\n", node);
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	WARN(num_ictlrs != soc->num_ictlrs,
	     "%pOF: Found %u interrupt controllers in DT; expected %u.\n",
	     node, num_ictlrs, soc->num_ictlrs);


	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, num_ictlrs * 32,
					  node, &tegra_ictlr_करोमुख्य_ops,
					  lic);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: failed to allocated domain\n", node);
		err = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	tegra_ictlr_syscore_init();

	pr_info("%pOF: %d interrupts forwarded to %pOF\n",
		node, num_ictlrs * 32, parent);

	वापस 0;

out_unmap:
	क्रम (i = 0; i < num_ictlrs; i++)
		iounmap(lic->base[i]);
out_मुक्त:
	kमुक्त(lic);
	वापस err;
पूर्ण

IRQCHIP_DECLARE(tegra20_ictlr, "nvidia,tegra20-ictlr", tegra_ictlr_init);
IRQCHIP_DECLARE(tegra30_ictlr, "nvidia,tegra30-ictlr", tegra_ictlr_init);
IRQCHIP_DECLARE(tegra210_ictlr, "nvidia,tegra210-ictlr", tegra_ictlr_init);
