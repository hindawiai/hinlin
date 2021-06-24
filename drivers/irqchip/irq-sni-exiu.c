<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Socionext External Interrupt Unit (EXIU)
 *
 * Copyright (c) 2017-2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 *
 * Based on irq-tegra.c:
 *   Copyright (C) 2011 Google, Inc.
 *   Copyright (C) 2010,2013, NVIDIA Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा NUM_IRQS	32

#घोषणा EIMASK		0x00
#घोषणा EISRCSEL	0x04
#घोषणा EIREQSTA	0x08
#घोषणा EIRAWREQSTA	0x0C
#घोषणा EIREQCLR	0x10
#घोषणा EILVL		0x14
#घोषणा EIEDG		0x18
#घोषणा EISIR		0x1C

काष्ठा exiu_irq_data अणु
	व्योम __iomem	*base;
	u32		spi_base;
पूर्ण;

अटल व्योम exiu_irq_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा exiu_irq_data *data = irq_data_get_irq_chip_data(d);

	ग_लिखोl(BIT(d->hwirq), data->base + EIREQCLR);
	irq_chip_eoi_parent(d);
पूर्ण

अटल व्योम exiu_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा exiu_irq_data *data = irq_data_get_irq_chip_data(d);
	u32 val;

	val = पढ़ोl_relaxed(data->base + EIMASK) | BIT(d->hwirq);
	ग_लिखोl_relaxed(val, data->base + EIMASK);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम exiu_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा exiu_irq_data *data = irq_data_get_irq_chip_data(d);
	u32 val;

	val = पढ़ोl_relaxed(data->base + EIMASK) & ~BIT(d->hwirq);
	ग_लिखोl_relaxed(val, data->base + EIMASK);
	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम exiu_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा exiu_irq_data *data = irq_data_get_irq_chip_data(d);
	u32 val;

	/* clear पूर्णांकerrupts that were latched जबतक disabled */
	ग_लिखोl_relaxed(BIT(d->hwirq), data->base + EIREQCLR);

	val = पढ़ोl_relaxed(data->base + EIMASK) & ~BIT(d->hwirq);
	ग_लिखोl_relaxed(val, data->base + EIMASK);
	irq_chip_enable_parent(d);
पूर्ण

अटल पूर्णांक exiu_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा exiu_irq_data *data = irq_data_get_irq_chip_data(d);
	u32 val;

	val = पढ़ोl_relaxed(data->base + EILVL);
	अगर (type == IRQ_TYPE_EDGE_RISING || type == IRQ_TYPE_LEVEL_HIGH)
		val |= BIT(d->hwirq);
	अन्यथा
		val &= ~BIT(d->hwirq);
	ग_लिखोl_relaxed(val, data->base + EILVL);

	val = पढ़ोl_relaxed(data->base + EIEDG);
	अगर (type == IRQ_TYPE_LEVEL_LOW || type == IRQ_TYPE_LEVEL_HIGH)
		val &= ~BIT(d->hwirq);
	अन्यथा
		val |= BIT(d->hwirq);
	ग_लिखोl_relaxed(val, data->base + EIEDG);

	ग_लिखोl_relaxed(BIT(d->hwirq), data->base + EIREQCLR);

	वापस irq_chip_set_type_parent(d, IRQ_TYPE_LEVEL_HIGH);
पूर्ण

अटल काष्ठा irq_chip exiu_irq_chip = अणु
	.name			= "EXIU",
	.irq_eoi		= exiu_irq_eoi,
	.irq_enable		= exiu_irq_enable,
	.irq_mask		= exiu_irq_mask,
	.irq_unmask		= exiu_irq_unmask,
	.irq_set_type		= exiu_irq_set_type,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_EOI_THREADED |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक exiu_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				 काष्ठा irq_fwspec *fwspec,
				 अचिन्हित दीर्घ *hwirq,
				 अचिन्हित पूर्णांक *type)
अणु
	काष्ठा exiu_irq_data *info = करोमुख्य->host_data;

	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		अगर (fwspec->param[0] != GIC_SPI)
			वापस -EINVAL; /* No PPI should poपूर्णांक to this करोमुख्य */

		*hwirq = fwspec->param[1] - info->spi_base;
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
	पूर्ण अन्यथा अणु
		अगर (fwspec->param_count != 2)
			वापस -EINVAL;
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exiu_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोm, अचिन्हित पूर्णांक virq,
			     अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	काष्ठा exiu_irq_data *info = करोm->host_data;
	irq_hw_number_t hwirq;

	parent_fwspec = *fwspec;
	अगर (is_of_node(करोm->parent->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;	/* Not GIC compliant */
		अगर (fwspec->param[0] != GIC_SPI)
			वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

		hwirq = fwspec->param[1] - info->spi_base;
	पूर्ण अन्यथा अणु
		hwirq = fwspec->param[0];
		parent_fwspec.param[0] = hwirq + info->spi_base + 32;
	पूर्ण
	WARN_ON(nr_irqs != 1);
	irq_करोमुख्य_set_hwirq_and_chip(करोm, virq, hwirq, &exiu_irq_chip, info);

	parent_fwspec.fwnode = करोm->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोm, virq, nr_irqs, &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops exiu_करोमुख्य_ops = अणु
	.translate	= exiu_करोमुख्य_translate,
	.alloc		= exiu_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल काष्ठा exiu_irq_data *exiu_init(स्थिर काष्ठा fwnode_handle *fwnode,
				       काष्ठा resource *res)
अणु
	काष्ठा exiu_irq_data *data;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	अगर (fwnode_property_पढ़ो_u32_array(fwnode, "socionext,spi-base",
					   &data->spi_base, 1)) अणु
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	data->base = ioremap(res->start, resource_size(res));
	अगर (!data->base) अणु
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	/* clear and mask all पूर्णांकerrupts */
	ग_लिखोl_relaxed(0xFFFFFFFF, data->base + EIREQCLR);
	ग_लिखोl_relaxed(0xFFFFFFFF, data->base + EIMASK);

	वापस data;

out_मुक्त:
	kमुक्त(data);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक __init exiu_dt_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	काष्ठा exiu_irq_data *data;
	काष्ठा resource res;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	अगर (of_address_to_resource(node, 0, &res)) अणु
		pr_err("%pOF: failed to parse memory resource\n", node);
		वापस -ENXIO;
	पूर्ण

	data = exiu_init(of_node_to_fwnode(node), &res);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, NUM_IRQS, node,
					  &exiu_करोमुख्य_ops, data);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: failed to allocate domain\n", node);
		जाओ out_unmap;
	पूर्ण

	pr_info("%pOF: %d interrupts forwarded to %pOF\n", node, NUM_IRQS,
		parent);

	वापस 0;

out_unmap:
	iounmap(data->base);
	kमुक्त(data);
	वापस -ENOMEM;
पूर्ण
IRQCHIP_DECLARE(exiu, "socionext,synquacer-exiu", exiu_dt_init);

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक exiu_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा exiu_irq_data *data;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to parse memory resource\n");
		वापस -ENXIO;
	पूर्ण

	data = exiu_init(dev_fwnode(&pdev->dev), res);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	करोमुख्य = acpi_irq_create_hierarchy(0, NUM_IRQS, dev_fwnode(&pdev->dev),
					   &exiu_करोमुख्य_ops, data);
	अगर (!करोमुख्य) अणु
		dev_err(&pdev->dev, "failed to create IRQ domain\n");
		जाओ out_unmap;
	पूर्ण

	dev_info(&pdev->dev, "%d interrupts forwarded\n", NUM_IRQS);

	वापस 0;

out_unmap:
	iounmap(data->base);
	kमुक्त(data);
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id exiu_acpi_ids[] = अणु
	अणु "SCX0008" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, exiu_acpi_ids);

अटल काष्ठा platक्रमm_driver exiu_driver = अणु
	.driver = अणु
		.name = "exiu",
		.acpi_match_table = exiu_acpi_ids,
	पूर्ण,
	.probe = exiu_acpi_probe,
पूर्ण;
builtin_platक्रमm_driver(exiu_driver);
#पूर्ण_अगर
