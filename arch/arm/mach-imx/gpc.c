<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011-2013 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश "common.h"
#समावेश "hardware.h"

#घोषणा GPC_CNTR		0x0
#घोषणा GPC_IMR1		0x008
#घोषणा GPC_PGC_CPU_PDN		0x2a0
#घोषणा GPC_PGC_CPU_PUPSCR	0x2a4
#घोषणा GPC_PGC_CPU_PDNSCR	0x2a8
#घोषणा GPC_PGC_SW2ISO_SHIFT	0x8
#घोषणा GPC_PGC_SW_SHIFT	0x0

#घोषणा GPC_CNTR_L2_PGE_SHIFT	22

#घोषणा IMR_NUM			4
#घोषणा GPC_MAX_IRQS		(IMR_NUM * 32)

अटल व्योम __iomem *gpc_base;
अटल u32 gpc_wake_irqs[IMR_NUM];
अटल u32 gpc_saved_imrs[IMR_NUM];

व्योम imx_gpc_set_arm_घातer_up_timing(u32 sw2iso, u32 sw)
अणु
	ग_लिखोl_relaxed((sw2iso << GPC_PGC_SW2ISO_SHIFT) |
		(sw << GPC_PGC_SW_SHIFT), gpc_base + GPC_PGC_CPU_PUPSCR);
पूर्ण

व्योम imx_gpc_set_arm_घातer_करोwn_timing(u32 sw2iso, u32 sw)
अणु
	ग_लिखोl_relaxed((sw2iso << GPC_PGC_SW2ISO_SHIFT) |
		(sw << GPC_PGC_SW_SHIFT), gpc_base + GPC_PGC_CPU_PDNSCR);
पूर्ण

व्योम imx_gpc_set_arm_घातer_in_lpm(bool घातer_off)
अणु
	ग_लिखोl_relaxed(घातer_off, gpc_base + GPC_PGC_CPU_PDN);
पूर्ण

व्योम imx_gpc_set_l2_mem_घातer_in_lpm(bool घातer_off)
अणु
	u32 val;

	val = पढ़ोl_relaxed(gpc_base + GPC_CNTR);
	val &= ~(1 << GPC_CNTR_L2_PGE_SHIFT);
	अगर (घातer_off)
		val |= 1 << GPC_CNTR_L2_PGE_SHIFT;
	ग_लिखोl_relaxed(val, gpc_base + GPC_CNTR);
पूर्ण

व्योम imx_gpc_pre_suspend(bool arm_घातer_off)
अणु
	व्योम __iomem *reg_imr1 = gpc_base + GPC_IMR1;
	पूर्णांक i;

	/* Tell GPC to घातer off ARM core when suspend */
	अगर (arm_घातer_off)
		imx_gpc_set_arm_घातer_in_lpm(arm_घातer_off);

	क्रम (i = 0; i < IMR_NUM; i++) अणु
		gpc_saved_imrs[i] = पढ़ोl_relaxed(reg_imr1 + i * 4);
		ग_लिखोl_relaxed(~gpc_wake_irqs[i], reg_imr1 + i * 4);
	पूर्ण
पूर्ण

व्योम imx_gpc_post_resume(व्योम)
अणु
	व्योम __iomem *reg_imr1 = gpc_base + GPC_IMR1;
	पूर्णांक i;

	/* Keep ARM core घातered on क्रम other low-घातer modes */
	imx_gpc_set_arm_घातer_in_lpm(false);

	क्रम (i = 0; i < IMR_NUM; i++)
		ग_लिखोl_relaxed(gpc_saved_imrs[i], reg_imr1 + i * 4);
पूर्ण

अटल पूर्णांक imx_gpc_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित पूर्णांक idx = d->hwirq / 32;
	u32 mask;

	mask = 1 << d->hwirq % 32;
	gpc_wake_irqs[idx] = on ? gpc_wake_irqs[idx] | mask :
				  gpc_wake_irqs[idx] & ~mask;

	/*
	 * Do *not* call पूर्णांकo the parent, as the GIC करोesn't have any
	 * wake-up facility...
	 */
	वापस 0;
पूर्ण

व्योम imx_gpc_mask_all(व्योम)
अणु
	व्योम __iomem *reg_imr1 = gpc_base + GPC_IMR1;
	पूर्णांक i;

	क्रम (i = 0; i < IMR_NUM; i++) अणु
		gpc_saved_imrs[i] = पढ़ोl_relaxed(reg_imr1 + i * 4);
		ग_लिखोl_relaxed(~0, reg_imr1 + i * 4);
	पूर्ण
पूर्ण

व्योम imx_gpc_restore_all(व्योम)
अणु
	व्योम __iomem *reg_imr1 = gpc_base + GPC_IMR1;
	पूर्णांक i;

	क्रम (i = 0; i < IMR_NUM; i++)
		ग_लिखोl_relaxed(gpc_saved_imrs[i], reg_imr1 + i * 4);
पूर्ण

व्योम imx_gpc_hwirq_unmask(अचिन्हित पूर्णांक hwirq)
अणु
	व्योम __iomem *reg;
	u32 val;

	reg = gpc_base + GPC_IMR1 + hwirq / 32 * 4;
	val = पढ़ोl_relaxed(reg);
	val &= ~(1 << hwirq % 32);
	ग_लिखोl_relaxed(val, reg);
पूर्ण

व्योम imx_gpc_hwirq_mask(अचिन्हित पूर्णांक hwirq)
अणु
	व्योम __iomem *reg;
	u32 val;

	reg = gpc_base + GPC_IMR1 + hwirq / 32 * 4;
	val = पढ़ोl_relaxed(reg);
	val |= 1 << (hwirq % 32);
	ग_लिखोl_relaxed(val, reg);
पूर्ण

अटल व्योम imx_gpc_irq_unmask(काष्ठा irq_data *d)
अणु
	imx_gpc_hwirq_unmask(d->hwirq);
	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम imx_gpc_irq_mask(काष्ठा irq_data *d)
अणु
	imx_gpc_hwirq_mask(d->hwirq);
	irq_chip_mask_parent(d);
पूर्ण

अटल काष्ठा irq_chip imx_gpc_chip = अणु
	.name			= "GPC",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= imx_gpc_irq_mask,
	.irq_unmask		= imx_gpc_irq_unmask,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_wake		= imx_gpc_irq_set_wake,
	.irq_set_type           = irq_chip_set_type_parent,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक imx_gpc_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
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

अटल पूर्णांक imx_gpc_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				  अचिन्हित पूर्णांक irq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	पूर्णांक i;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;	/* Not GIC compliant */
	अगर (fwspec->param[0] != 0)
		वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

	hwirq = fwspec->param[1];
	अगर (hwirq >= GPC_MAX_IRQS)
		वापस -EINVAL;	/* Can't deal with this */

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, irq + i, hwirq + i,
					      &imx_gpc_chip, शून्य);

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, irq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops imx_gpc_करोमुख्य_ops = अणु
	.translate	= imx_gpc_करोमुख्य_translate,
	.alloc		= imx_gpc_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init imx_gpc_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	पूर्णांक i;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	gpc_base = of_iomap(node, 0);
	अगर (WARN_ON(!gpc_base))
	        वापस -ENOMEM;

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, GPC_MAX_IRQS,
					  node, &imx_gpc_करोमुख्य_ops,
					  शून्य);
	अगर (!करोमुख्य) अणु
		iounmap(gpc_base);
		वापस -ENOMEM;
	पूर्ण

	/* Initially mask all पूर्णांकerrupts */
	क्रम (i = 0; i < IMR_NUM; i++)
		ग_लिखोl_relaxed(~0, gpc_base + GPC_IMR1 + i * 4);

	/*
	 * Clear the OF_POPULATED flag set in of_irq_init so that
	 * later the GPC घातer करोमुख्य driver will not be skipped.
	 */
	of_node_clear_flag(node, OF_POPULATED);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(imx_gpc, "fsl,imx6q-gpc", imx_gpc_init);

व्योम __init imx_gpc_check_dt(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-gpc");
	अगर (WARN_ON(!np))
		वापस;

	अगर (WARN_ON(!of_find_property(np, "interrupt-controller", शून्य))) अणु
		pr_warn("Outdated DT detected, suspend/resume will NOT work\n");

		/* map GPC, so that at least CPUidle and WARs keep working */
		gpc_base = of_iomap(np, 0);
	पूर्ण
	of_node_put(np);
पूर्ण
