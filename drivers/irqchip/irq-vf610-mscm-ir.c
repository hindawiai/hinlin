<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2015 Toradex AG
 * Author: Stefan Agner <stefan@agner.ch>
 *
 * IRQ chip driver क्रम MSCM पूर्णांकerrupt router available on Vybrid SoC's.
 * The पूर्णांकerrupt router is between the CPU's पूर्णांकerrupt controller and the
 * peripheral. The router allows to route the peripheral पूर्णांकerrupts to
 * one of the two available CPU's on Vybrid VF6xx SoC's (Cortex-A5 or
 * Cortex-M4). The router will be configured transparently on a IRQ
 * request.
 *
 * o All peripheral पूर्णांकerrupts of the Vybrid SoC can be routed to
 *   CPU 0, CPU 1 or both. The routing is useful क्रम dual-core
 *   variants of Vybrid SoC such as VF6xx. This driver routes the
 *   requested पूर्णांकerrupt to the CPU currently running on.
 *
 * o It is required to setup the पूर्णांकerrupt router even on single-core
 *   variants of Vybrid.
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#घोषणा MSCM_CPxNUM		0x4

#घोषणा MSCM_IRSPRC(n)		(0x80 + 2 * (n))
#घोषणा MSCM_IRSPRC_CPEN_MASK	0x3

#घोषणा MSCM_IRSPRC_NUM		112

काष्ठा vf610_mscm_ir_chip_data अणु
	व्योम __iomem *mscm_ir_base;
	u16 cpu_mask;
	u16 saved_irsprc[MSCM_IRSPRC_NUM];
	bool is_nvic;
पूर्ण;

अटल काष्ठा vf610_mscm_ir_chip_data *mscm_ir_data;

अटल अंतरभूत व्योम vf610_mscm_ir_save(काष्ठा vf610_mscm_ir_chip_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MSCM_IRSPRC_NUM; i++)
		data->saved_irsprc[i] = पढ़ोw_relaxed(data->mscm_ir_base + MSCM_IRSPRC(i));
पूर्ण

अटल अंतरभूत व्योम vf610_mscm_ir_restore(काष्ठा vf610_mscm_ir_chip_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MSCM_IRSPRC_NUM; i++)
		ग_लिखोw_relaxed(data->saved_irsprc[i], data->mscm_ir_base + MSCM_IRSPRC(i));
पूर्ण

अटल पूर्णांक vf610_mscm_ir_notअगरier(काष्ठा notअगरier_block *self,
				  अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		vf610_mscm_ir_save(mscm_ir_data);
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		vf610_mscm_ir_restore(mscm_ir_data);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mscm_ir_notअगरier_block = अणु
	.notअगरier_call = vf610_mscm_ir_notअगरier,
पूर्ण;

अटल व्योम vf610_mscm_ir_enable(काष्ठा irq_data *data)
अणु
	irq_hw_number_t hwirq = data->hwirq;
	काष्ठा vf610_mscm_ir_chip_data *chip_data = data->chip_data;
	u16 irsprc;

	irsprc = पढ़ोw_relaxed(chip_data->mscm_ir_base + MSCM_IRSPRC(hwirq));
	irsprc &= MSCM_IRSPRC_CPEN_MASK;

	WARN_ON(irsprc & ~chip_data->cpu_mask);

	ग_लिखोw_relaxed(chip_data->cpu_mask,
		       chip_data->mscm_ir_base + MSCM_IRSPRC(hwirq));

	irq_chip_enable_parent(data);
पूर्ण

अटल व्योम vf610_mscm_ir_disable(काष्ठा irq_data *data)
अणु
	irq_hw_number_t hwirq = data->hwirq;
	काष्ठा vf610_mscm_ir_chip_data *chip_data = data->chip_data;

	ग_लिखोw_relaxed(0x0, chip_data->mscm_ir_base + MSCM_IRSPRC(hwirq));

	irq_chip_disable_parent(data);
पूर्ण

अटल काष्ठा irq_chip vf610_mscm_ir_irq_chip = अणु
	.name			= "mscm-ir",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_enable		= vf610_mscm_ir_enable,
	.irq_disable		= vf610_mscm_ir_disable,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक vf610_mscm_ir_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i;
	irq_hw_number_t hwirq;
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा irq_fwspec parent_fwspec;

	अगर (!irq_करोमुख्य_get_of_node(करोमुख्य->parent))
		वापस -EINVAL;

	अगर (fwspec->param_count != 2)
		वापस -EINVAL;

	hwirq = fwspec->param[0];
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &vf610_mscm_ir_irq_chip,
					      करोमुख्य->host_data);

	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;

	अगर (mscm_ir_data->is_nvic) अणु
		parent_fwspec.param_count = 1;
		parent_fwspec.param[0] = fwspec->param[0];
	पूर्ण अन्यथा अणु
		parent_fwspec.param_count = 3;
		parent_fwspec.param[0] = GIC_SPI;
		parent_fwspec.param[1] = fwspec->param[0];
		parent_fwspec.param[2] = fwspec->param[1];
	पूर्ण

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल पूर्णांक vf610_mscm_ir_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
					  काष्ठा irq_fwspec *fwspec,
					  अचिन्हित दीर्घ *hwirq,
					  अचिन्हित पूर्णांक *type)
अणु
	अगर (WARN_ON(fwspec->param_count < 2))
		वापस -EINVAL;
	*hwirq = fwspec->param[0];
	*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mscm_irq_करोमुख्य_ops = अणु
	.translate = vf610_mscm_ir_करोमुख्य_translate,
	.alloc = vf610_mscm_ir_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init vf610_mscm_ir_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *करोमुख्य_parent;
	काष्ठा regmap *mscm_cp_regmap;
	पूर्णांक ret, cpuid;

	करोमुख्य_parent = irq_find_host(parent);
	अगर (!करोमुख्य_parent) अणु
		pr_err("vf610_mscm_ir: interrupt-parent not found\n");
		वापस -EINVAL;
	पूर्ण

	mscm_ir_data = kzalloc(माप(*mscm_ir_data), GFP_KERNEL);
	अगर (!mscm_ir_data)
		वापस -ENOMEM;

	mscm_ir_data->mscm_ir_base = of_io_request_and_map(node, 0, "mscm-ir");
	अगर (IS_ERR(mscm_ir_data->mscm_ir_base)) अणु
		pr_err("vf610_mscm_ir: unable to map mscm register\n");
		ret = PTR_ERR(mscm_ir_data->mscm_ir_base);
		जाओ out_मुक्त;
	पूर्ण

	mscm_cp_regmap = syscon_regmap_lookup_by_phandle(node, "fsl,cpucfg");
	अगर (IS_ERR(mscm_cp_regmap)) अणु
		ret = PTR_ERR(mscm_cp_regmap);
		pr_err("vf610_mscm_ir: regmap lookup for cpucfg failed\n");
		जाओ out_unmap;
	पूर्ण

	regmap_पढ़ो(mscm_cp_regmap, MSCM_CPxNUM, &cpuid);
	mscm_ir_data->cpu_mask = 0x1 << cpuid;

	करोमुख्य = irq_करोमुख्य_add_hierarchy(करोमुख्य_parent, 0,
					  MSCM_IRSPRC_NUM, node,
					  &mscm_irq_करोमुख्य_ops, mscm_ir_data);
	अगर (!करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	अगर (of_device_is_compatible(irq_करोमुख्य_get_of_node(करोमुख्य->parent),
				    "arm,armv7m-nvic"))
		mscm_ir_data->is_nvic = true;

	cpu_pm_रेजिस्टर_notअगरier(&mscm_ir_notअगरier_block);

	वापस 0;

out_unmap:
	iounmap(mscm_ir_data->mscm_ir_base);
out_मुक्त:
	kमुक्त(mscm_ir_data);
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(vf610_mscm_ir, "fsl,vf610-mscm-ir", vf610_mscm_ir_of_init);
