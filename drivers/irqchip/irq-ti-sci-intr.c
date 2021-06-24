<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments' K3 Interrupt Router irqchip driver
 *
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - https://www.ti.com/
 *	Lokesh Vutla <lokeshvutla@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>

/**
 * काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य - Structure representing a TISCI based
 *				   Interrupt Router IRQ करोमुख्य.
 * @sci:	Poपूर्णांकer to TISCI handle
 * @out_irqs:	TISCI resource poपूर्णांकer representing INTR irqs.
 * @dev:	Struct device poपूर्णांकer.
 * @ti_sci_id:	TI-SCI device identअगरier
 * @type:	Specअगरies the trigger type supported by this Interrupt Router
 */
काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य अणु
	स्थिर काष्ठा ti_sci_handle *sci;
	काष्ठा ti_sci_resource *out_irqs;
	काष्ठा device *dev;
	u32 ti_sci_id;
	u32 type;
पूर्ण;

अटल काष्ठा irq_chip ti_sci_पूर्णांकr_irq_chip = अणु
	.name			= "INTR",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

/**
 * ti_sci_पूर्णांकr_irq_करोमुख्य_translate() - Retrieve hwirq and type from
 *					IRQ firmware specअगरic handler.
 * @करोमुख्य:	Poपूर्णांकer to IRQ करोमुख्य
 * @fwspec:	Poपूर्णांकer to IRQ specअगरic firmware काष्ठाure
 * @hwirq:	IRQ number identअगरied by hardware
 * @type:	IRQ type
 *
 * Return 0 अगर all went ok अन्यथा appropriate error.
 */
अटल पूर्णांक ti_sci_पूर्णांकr_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
					    काष्ठा irq_fwspec *fwspec,
					    अचिन्हित दीर्घ *hwirq,
					    अचिन्हित पूर्णांक *type)
अणु
	काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य *पूर्णांकr = करोमुख्य->host_data;

	अगर (fwspec->param_count != 1)
		वापस -EINVAL;

	*hwirq = fwspec->param[0];
	*type = पूर्णांकr->type;

	वापस 0;
पूर्ण

/**
 * ti_sci_पूर्णांकr_xlate_irq() - Translate hwirq to parent's hwirq.
 * @पूर्णांकr:	IRQ करोमुख्य corresponding to Interrupt Router
 * @irq:	Hardware irq corresponding to the above irq करोमुख्य
 *
 * Return parent irq number अगर translation is available अन्यथा -ENOENT.
 */
अटल पूर्णांक ti_sci_पूर्णांकr_xlate_irq(काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य *पूर्णांकr, u32 irq)
अणु
	काष्ठा device_node *np = dev_of_node(पूर्णांकr->dev);
	u32 base, pbase, size, len;
	स्थिर __be32 *range;

	range = of_get_property(np, "ti,interrupt-ranges", &len);
	अगर (!range)
		वापस irq;

	क्रम (len /= माप(*range); len >= 3; len -= 3) अणु
		base = be32_to_cpu(*range++);
		pbase = be32_to_cpu(*range++);
		size = be32_to_cpu(*range++);

		अगर (base <= irq && irq < base + size)
			वापस irq - base + pbase;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * ti_sci_पूर्णांकr_irq_करोमुख्य_मुक्त() - Free the specअगरied IRQs from the करोमुख्य.
 * @करोमुख्य:	Doमुख्य to which the irqs beदीर्घ
 * @virq:	Linux भव IRQ to be मुक्तd.
 * @nr_irqs:	Number of continuous irqs to be मुक्तd
 */
अटल व्योम ti_sci_पूर्णांकr_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य *पूर्णांकr = करोमुख्य->host_data;
	काष्ठा irq_data *data;
	पूर्णांक out_irq;

	data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	out_irq = (uपूर्णांकptr_t)data->chip_data;

	पूर्णांकr->sci->ops.rm_irq_ops.मुक्त_irq(पूर्णांकr->sci,
					   पूर्णांकr->ti_sci_id, data->hwirq,
					   पूर्णांकr->ti_sci_id, out_irq);
	ti_sci_release_resource(पूर्णांकr->out_irqs, out_irq);
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, 1);
	irq_करोमुख्य_reset_irq_data(data);
पूर्ण

/**
 * ti_sci_पूर्णांकr_alloc_parent_irq() - Allocate parent IRQ
 * @करोमुख्य:	Poपूर्णांकer to the पूर्णांकerrupt router IRQ करोमुख्य
 * @virq:	Corresponding Linux भव IRQ number
 * @hwirq:	Corresponding hwirq क्रम the IRQ within this IRQ करोमुख्य
 *
 * Returns पूर्णांकr output irq अगर all went well अन्यथा appropriate error poपूर्णांकer.
 */
अटल पूर्णांक ti_sci_पूर्णांकr_alloc_parent_irq(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, u32 hwirq)
अणु
	काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य *पूर्णांकr = करोमुख्य->host_data;
	काष्ठा device_node *parent_node;
	काष्ठा irq_fwspec fwspec;
	पूर्णांक p_hwirq, err = 0;
	u16 out_irq;

	out_irq = ti_sci_get_मुक्त_resource(पूर्णांकr->out_irqs);
	अगर (out_irq == TI_SCI_RESOURCE_शून्य)
		वापस -EINVAL;

	p_hwirq = ti_sci_पूर्णांकr_xlate_irq(पूर्णांकr, out_irq);
	अगर (p_hwirq < 0)
		जाओ err_irqs;

	parent_node = of_irq_find_parent(dev_of_node(पूर्णांकr->dev));
	fwspec.fwnode = of_node_to_fwnode(parent_node);

	अगर (of_device_is_compatible(parent_node, "arm,gic-v3")) अणु
		/* Parent is GIC */
		fwspec.param_count = 3;
		fwspec.param[0] = 0;	/* SPI */
		fwspec.param[1] = p_hwirq - 32; /* SPI offset */
		fwspec.param[2] = पूर्णांकr->type;
	पूर्ण अन्यथा अणु
		/* Parent is Interrupt Router */
		fwspec.param_count = 1;
		fwspec.param[0] = p_hwirq;
	पूर्ण

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (err)
		जाओ err_irqs;

	err = पूर्णांकr->sci->ops.rm_irq_ops.set_irq(पूर्णांकr->sci,
						पूर्णांकr->ti_sci_id, hwirq,
						पूर्णांकr->ti_sci_id, out_irq);
	अगर (err)
		जाओ err_msg;

	वापस out_irq;

err_msg:
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, 1);
err_irqs:
	ti_sci_release_resource(पूर्णांकr->out_irqs, out_irq);
	वापस err;
पूर्ण

/**
 * ti_sci_पूर्णांकr_irq_करोमुख्य_alloc() - Allocate Interrupt router IRQs
 * @करोमुख्य:	Poपूर्णांक to the पूर्णांकerrupt router IRQ करोमुख्य
 * @virq:	Corresponding Linux भव IRQ number
 * @nr_irqs:	Continuous irqs to be allocated
 * @data:	Poपूर्णांकer to firmware specअगरier
 *
 * Return 0 अगर all went well अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_sci_पूर्णांकr_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
					व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	अचिन्हित दीर्घ hwirq;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err, out_irq;

	err = ti_sci_पूर्णांकr_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &flags);
	अगर (err)
		वापस err;

	out_irq = ti_sci_पूर्णांकr_alloc_parent_irq(करोमुख्य, virq, hwirq);
	अगर (out_irq < 0)
		वापस out_irq;

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
				      &ti_sci_पूर्णांकr_irq_chip,
				      (व्योम *)(uपूर्णांकptr_t)out_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ti_sci_पूर्णांकr_irq_करोमुख्य_ops = अणु
	.मुक्त		= ti_sci_पूर्णांकr_irq_करोमुख्य_मुक्त,
	.alloc		= ti_sci_पूर्णांकr_irq_करोमुख्य_alloc,
	.translate	= ti_sci_पूर्णांकr_irq_करोमुख्य_translate,
पूर्ण;

अटल पूर्णांक ti_sci_पूर्णांकr_irq_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	काष्ठा ti_sci_पूर्णांकr_irq_करोमुख्य *पूर्णांकr;
	काष्ठा device_node *parent_node;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	parent_node = of_irq_find_parent(dev_of_node(dev));
	अगर (!parent_node) अणु
		dev_err(dev, "Failed to get IRQ parent node\n");
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent_node);
	अगर (!parent_करोमुख्य) अणु
		dev_err(dev, "Failed to find IRQ parent domain\n");
		वापस -ENODEV;
	पूर्ण

	पूर्णांकr = devm_kzalloc(dev, माप(*पूर्णांकr), GFP_KERNEL);
	अगर (!पूर्णांकr)
		वापस -ENOMEM;

	पूर्णांकr->dev = dev;
	ret = of_property_पढ़ो_u32(dev_of_node(dev), "ti,intr-trigger-type",
				   &पूर्णांकr->type);
	अगर (ret) अणु
		dev_err(dev, "missing ti,intr-trigger-type property\n");
		वापस -EINVAL;
	पूर्ण

	पूर्णांकr->sci = devm_ti_sci_get_by_phandle(dev, "ti,sci");
	अगर (IS_ERR(पूर्णांकr->sci))
		वापस dev_err_probe(dev, PTR_ERR(पूर्णांकr->sci),
				     "ti,sci read fail\n");

	ret = of_property_पढ़ो_u32(dev_of_node(dev), "ti,sci-dev-id",
				   &पूर्णांकr->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "missing 'ti,sci-dev-id' property\n");
		वापस -EINVAL;
	पूर्ण

	पूर्णांकr->out_irqs = devm_ti_sci_get_resource(पूर्णांकr->sci, dev,
						  पूर्णांकr->ti_sci_id,
						  TI_SCI_RESASG_SUBTYPE_IR_OUTPUT);
	अगर (IS_ERR(पूर्णांकr->out_irqs)) अणु
		dev_err(dev, "Destination irq resource allocation failed\n");
		वापस PTR_ERR(पूर्णांकr->out_irqs);
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, 0, dev_of_node(dev),
					  &ti_sci_पूर्णांकr_irq_करोमुख्य_ops, पूर्णांकr);
	अगर (!करोमुख्य) अणु
		dev_err(dev, "Failed to allocate IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	dev_info(dev, "Interrupt Router %d domain created\n", पूर्णांकr->ti_sci_id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_sci_पूर्णांकr_irq_करोमुख्य_of_match[] = अणु
	अणु .compatible = "ti,sci-intr", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_पूर्णांकr_irq_करोमुख्य_of_match);

अटल काष्ठा platक्रमm_driver ti_sci_पूर्णांकr_irq_करोमुख्य_driver = अणु
	.probe = ti_sci_पूर्णांकr_irq_करोमुख्य_probe,
	.driver = अणु
		.name = "ti-sci-intr",
		.of_match_table = ti_sci_पूर्णांकr_irq_करोमुख्य_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_पूर्णांकr_irq_करोमुख्य_driver);

MODULE_AUTHOR("Lokesh Vutla <lokeshvutla@ticom>");
MODULE_DESCRIPTION("K3 Interrupt Router driver over TI SCI protocol");
MODULE_LICENSE("GPL v2");
