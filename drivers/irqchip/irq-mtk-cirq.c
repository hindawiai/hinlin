<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Youlin.Pei <youlin.pei@mediatek.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#घोषणा CIRQ_ACK	0x40
#घोषणा CIRQ_MASK_SET	0xc0
#घोषणा CIRQ_MASK_CLR	0x100
#घोषणा CIRQ_SENS_SET	0x180
#घोषणा CIRQ_SENS_CLR	0x1c0
#घोषणा CIRQ_POL_SET	0x240
#घोषणा CIRQ_POL_CLR	0x280
#घोषणा CIRQ_CONTROL	0x300

#घोषणा CIRQ_EN	0x1
#घोषणा CIRQ_EDGE	0x2
#घोषणा CIRQ_FLUSH	0x4

काष्ठा mtk_cirq_chip_data अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक ext_irq_start;
	अचिन्हित पूर्णांक ext_irq_end;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

अटल काष्ठा mtk_cirq_chip_data *cirq_data;

अटल व्योम mtk_cirq_ग_लिखो_mask(काष्ठा irq_data *data, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mtk_cirq_chip_data *chip_data = data->chip_data;
	अचिन्हित पूर्णांक cirq_num = data->hwirq;
	u32 mask = 1 << (cirq_num % 32);

	ग_लिखोl_relaxed(mask, chip_data->base + offset + (cirq_num / 32) * 4);
पूर्ण

अटल व्योम mtk_cirq_mask(काष्ठा irq_data *data)
अणु
	mtk_cirq_ग_लिखो_mask(data, CIRQ_MASK_SET);
	irq_chip_mask_parent(data);
पूर्ण

अटल व्योम mtk_cirq_unmask(काष्ठा irq_data *data)
अणु
	mtk_cirq_ग_लिखो_mask(data, CIRQ_MASK_CLR);
	irq_chip_unmask_parent(data);
पूर्ण

अटल पूर्णांक mtk_cirq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक ret;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		mtk_cirq_ग_लिखो_mask(data, CIRQ_POL_CLR);
		mtk_cirq_ग_लिखो_mask(data, CIRQ_SENS_CLR);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		mtk_cirq_ग_लिखो_mask(data, CIRQ_POL_SET);
		mtk_cirq_ग_लिखो_mask(data, CIRQ_SENS_CLR);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		mtk_cirq_ग_लिखो_mask(data, CIRQ_POL_CLR);
		mtk_cirq_ग_लिखो_mask(data, CIRQ_SENS_SET);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		mtk_cirq_ग_लिखो_mask(data, CIRQ_POL_SET);
		mtk_cirq_ग_लिखो_mask(data, CIRQ_SENS_SET);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	data = data->parent_data;
	ret = data->chip->irq_set_type(data, type);
	वापस ret;
पूर्ण

अटल काष्ठा irq_chip mtk_cirq_chip = अणु
	.name			= "MT_CIRQ",
	.irq_mask		= mtk_cirq_mask,
	.irq_unmask		= mtk_cirq_unmask,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= mtk_cirq_set_type,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mtk_cirq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
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

		/* cirq support irq number check */
		अगर (fwspec->param[1] < cirq_data->ext_irq_start ||
		    fwspec->param[1] > cirq_data->ext_irq_end)
			वापस -EINVAL;

		*hwirq = fwspec->param[1] - cirq_data->ext_irq_start;
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtk_cirq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा irq_fwspec parent_fwspec = *fwspec;

	ret = mtk_cirq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(nr_irqs != 1))
		वापस -EINVAL;

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
				      &mtk_cirq_chip,
				      करोमुख्य->host_data);

	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops cirq_करोमुख्य_ops = अणु
	.translate	= mtk_cirq_करोमुख्य_translate,
	.alloc		= mtk_cirq_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_cirq_suspend(व्योम)
अणु
	u32 value, mask;
	अचिन्हित पूर्णांक irq, hwirq_num;
	bool pending, masked;
	पूर्णांक i, pendret, maskret;

	/*
	 * When बाह्यal पूर्णांकerrupts happened, CIRQ will record the status
	 * even CIRQ is not enabled. When execute flush command, CIRQ will
	 * resend the संकेतs according to the status. So अगर करोn't clear the
	 * status, CIRQ will resend the wrong संकेतs.
	 *
	 * arch_suspend_disable_irqs() will be called beक्रमe CIRQ suspend
	 * callback. If clear all the status simply, the बाह्यal पूर्णांकerrupts
	 * which happened between arch_suspend_disable_irqs and CIRQ suspend
	 * callback will be lost. Using following steps to aव्योम this issue;
	 *
	 * - Iterate over all the CIRQ supported पूर्णांकerrupts;
	 * - For each पूर्णांकerrupt, inspect its pending and masked status at GIC
	 *   level;
	 * - If pending and unmasked, it happened between
	 *   arch_suspend_disable_irqs and CIRQ suspend callback, करोn't ACK
	 *   it. Otherwise, ACK it.
	 */
	hwirq_num = cirq_data->ext_irq_end - cirq_data->ext_irq_start + 1;
	क्रम (i = 0; i < hwirq_num; i++) अणु
		irq = irq_find_mapping(cirq_data->करोमुख्य, i);
		अगर (irq) अणु
			pendret = irq_get_irqchip_state(irq,
							IRQCHIP_STATE_PENDING,
							&pending);

			maskret = irq_get_irqchip_state(irq,
							IRQCHIP_STATE_MASKED,
							&masked);

			अगर (pendret == 0 && maskret == 0 &&
			    (pending && !masked))
				जारी;
		पूर्ण

		mask = 1 << (i % 32);
		ग_लिखोl_relaxed(mask, cirq_data->base + CIRQ_ACK + (i / 32) * 4);
	पूर्ण

	/* set edge_only mode, record edge-triggerd पूर्णांकerrupts */
	/* enable cirq */
	value = पढ़ोl_relaxed(cirq_data->base + CIRQ_CONTROL);
	value |= (CIRQ_EDGE | CIRQ_EN);
	ग_लिखोl_relaxed(value, cirq_data->base + CIRQ_CONTROL);

	वापस 0;
पूर्ण

अटल व्योम mtk_cirq_resume(व्योम)
अणु
	u32 value;

	/* flush recorded पूर्णांकerrupts, will send संकेतs to parent controller */
	value = पढ़ोl_relaxed(cirq_data->base + CIRQ_CONTROL);
	ग_लिखोl_relaxed(value | CIRQ_FLUSH, cirq_data->base + CIRQ_CONTROL);

	/* disable cirq */
	value = पढ़ोl_relaxed(cirq_data->base + CIRQ_CONTROL);
	value &= ~(CIRQ_EDGE | CIRQ_EN);
	ग_लिखोl_relaxed(value, cirq_data->base + CIRQ_CONTROL);
पूर्ण

अटल काष्ठा syscore_ops mtk_cirq_syscore_ops = अणु
	.suspend	= mtk_cirq_suspend,
	.resume		= mtk_cirq_resume,
पूर्ण;

अटल व्योम mtk_cirq_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&mtk_cirq_syscore_ops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mtk_cirq_syscore_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mtk_cirq_of_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *करोमुख्य_parent;
	अचिन्हित पूर्णांक irq_num;
	पूर्णांक ret;

	करोमुख्य_parent = irq_find_host(parent);
	अगर (!करोमुख्य_parent) अणु
		pr_err("mtk_cirq: interrupt-parent not found\n");
		वापस -EINVAL;
	पूर्ण

	cirq_data = kzalloc(माप(*cirq_data), GFP_KERNEL);
	अगर (!cirq_data)
		वापस -ENOMEM;

	cirq_data->base = of_iomap(node, 0);
	अगर (!cirq_data->base) अणु
		pr_err("mtk_cirq: unable to map cirq register\n");
		ret = -ENXIO;
		जाओ out_मुक्त;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(node, "mediatek,ext-irq-range", 0,
					 &cirq_data->ext_irq_start);
	अगर (ret)
		जाओ out_unmap;

	ret = of_property_पढ़ो_u32_index(node, "mediatek,ext-irq-range", 1,
					 &cirq_data->ext_irq_end);
	अगर (ret)
		जाओ out_unmap;

	irq_num = cirq_data->ext_irq_end - cirq_data->ext_irq_start + 1;
	करोमुख्य = irq_करोमुख्य_add_hierarchy(करोमुख्य_parent, 0,
					  irq_num, node,
					  &cirq_करोमुख्य_ops, cirq_data);
	अगर (!करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण
	cirq_data->करोमुख्य = करोमुख्य;

	mtk_cirq_syscore_init();

	वापस 0;

out_unmap:
	iounmap(cirq_data->base);
out_मुक्त:
	kमुक्त(cirq_data);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(mtk_cirq, "mediatek,mtk-cirq", mtk_cirq_of_init);
