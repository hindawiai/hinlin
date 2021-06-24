<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson PCH MSI support
 */

#घोषणा pr_fmt(fmt) "pch-msi: " fmt

#समावेश <linux/irqchip.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

काष्ठा pch_msi_data अणु
	काष्ठा mutex	msi_map_lock;
	phys_addr_t	करोorbell;
	u32		irq_first;	/* The vector number that MSIs starts */
	u32		num_irqs;	/* The number of vectors क्रम MSIs */
	अचिन्हित दीर्घ	*msi_map;
पूर्ण;

अटल व्योम pch_msi_mask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम pch_msi_unmask_msi_irq(काष्ठा irq_data *d)
अणु
	irq_chip_unmask_parent(d);
	pci_msi_unmask_irq(d);
पूर्ण

अटल काष्ठा irq_chip pch_msi_irq_chip = अणु
	.name			= "PCH PCI MSI",
	.irq_mask		= pch_msi_mask_msi_irq,
	.irq_unmask		= pch_msi_unmask_msi_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक pch_msi_allocate_hwirq(काष्ठा pch_msi_data *priv, पूर्णांक num_req)
अणु
	पूर्णांक first;

	mutex_lock(&priv->msi_map_lock);

	first = biपंचांगap_find_मुक्त_region(priv->msi_map, priv->num_irqs,
					get_count_order(num_req));
	अगर (first < 0) अणु
		mutex_unlock(&priv->msi_map_lock);
		वापस -ENOSPC;
	पूर्ण

	mutex_unlock(&priv->msi_map_lock);

	वापस priv->irq_first + first;
पूर्ण

अटल व्योम pch_msi_मुक्त_hwirq(काष्ठा pch_msi_data *priv,
				पूर्णांक hwirq, पूर्णांक num_req)
अणु
	पूर्णांक first = hwirq - priv->irq_first;

	mutex_lock(&priv->msi_map_lock);
	biपंचांगap_release_region(priv->msi_map, first, get_count_order(num_req));
	mutex_unlock(&priv->msi_map_lock);
पूर्ण

अटल व्योम pch_msi_compose_msi_msg(काष्ठा irq_data *data,
					काष्ठा msi_msg *msg)
अणु
	काष्ठा pch_msi_data *priv = irq_data_get_irq_chip_data(data);

	msg->address_hi = upper_32_bits(priv->करोorbell);
	msg->address_lo = lower_32_bits(priv->करोorbell);
	msg->data = data->hwirq;
पूर्ण

अटल काष्ठा msi_करोमुख्य_info pch_msi_करोमुख्य_info = अणु
	.flags	= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		  MSI_FLAG_MULTI_PCI_MSI | MSI_FLAG_PCI_MSIX,
	.chip	= &pch_msi_irq_chip,
पूर्ण;

अटल काष्ठा irq_chip middle_irq_chip = अणु
	.name			= "PCH MSI",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_ack		= irq_chip_ack_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_compose_msi_msg	= pch_msi_compose_msi_msg,
पूर्ण;

अटल पूर्णांक pch_msi_parent_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, पूर्णांक hwirq)
अणु
	काष्ठा irq_fwspec fwspec;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 1;
	fwspec.param[0] = hwirq;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
पूर्ण

अटल पूर्णांक pch_msi_middle_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq,
					   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा pch_msi_data *priv = करोमुख्य->host_data;
	पूर्णांक hwirq, err, i;

	hwirq = pch_msi_allocate_hwirq(priv, nr_irqs);
	अगर (hwirq < 0)
		वापस hwirq;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		err = pch_msi_parent_करोमुख्य_alloc(करोमुख्य, virq + i, hwirq + i);
		अगर (err)
			जाओ err_hwirq;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &middle_irq_chip, priv);
	पूर्ण

	वापस 0;

err_hwirq:
	pch_msi_मुक्त_hwirq(priv, hwirq, nr_irqs);
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, i - 1);

	वापस err;
पूर्ण

अटल व्योम pch_msi_middle_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq,
					   अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा pch_msi_data *priv = irq_data_get_irq_chip_data(d);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
	pch_msi_मुक्त_hwirq(priv, d->hwirq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pch_msi_middle_करोमुख्य_ops = अणु
	.alloc	= pch_msi_middle_करोमुख्य_alloc,
	.मुक्त	= pch_msi_middle_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक pch_msi_init_करोमुख्यs(काष्ठा pch_msi_data *priv,
				काष्ठा device_node *node,
				काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *middle_करोमुख्य, *msi_करोमुख्य;

	middle_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
						priv->num_irqs,
						&pch_msi_middle_करोमुख्य_ops,
						priv);
	अगर (!middle_करोमुख्य) अणु
		pr_err("Failed to create the MSI middle domain\n");
		वापस -ENOMEM;
	पूर्ण

	middle_करोमुख्य->parent = parent;
	irq_करोमुख्य_update_bus_token(middle_करोमुख्य, DOMAIN_BUS_NEXUS);

	msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
					       &pch_msi_करोमुख्य_info,
					       middle_करोमुख्य);
	अगर (!msi_करोमुख्य) अणु
		pr_err("Failed to create PCI MSI domain\n");
		irq_करोमुख्य_हटाओ(middle_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pch_msi_init(काष्ठा device_node *node,
			    काष्ठा device_node *parent)
अणु
	काष्ठा pch_msi_data *priv;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा resource res;
	पूर्णांक ret;

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("Failed to find the parent domain\n");
		वापस -ENXIO;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->msi_map_lock);

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		pr_err("Failed to allocate resource\n");
		जाओ err_priv;
	पूर्ण

	priv->करोorbell = res.start;

	अगर (of_property_पढ़ो_u32(node, "loongson,msi-base-vec",
				&priv->irq_first)) अणु
		pr_err("Unable to parse MSI vec base\n");
		ret = -EINVAL;
		जाओ err_priv;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "loongson,msi-num-vecs",
				&priv->num_irqs)) अणु
		pr_err("Unable to parse MSI vec number\n");
		ret = -EINVAL;
		जाओ err_priv;
	पूर्ण

	priv->msi_map = biपंचांगap_zalloc(priv->num_irqs, GFP_KERNEL);
	अगर (!priv->msi_map) अणु
		ret = -ENOMEM;
		जाओ err_priv;
	पूर्ण

	pr_debug("Registering %d MSIs, starting at %d\n",
		 priv->num_irqs, priv->irq_first);

	ret = pch_msi_init_करोमुख्यs(priv, node, parent_करोमुख्य);
	अगर (ret)
		जाओ err_map;

	वापस 0;

err_map:
	kमुक्त(priv->msi_map);
err_priv:
	kमुक्त(priv);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(pch_msi, "loongson,pch-msi-1.0", pch_msi_init);
