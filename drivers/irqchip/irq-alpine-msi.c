<शैली गुरु>
/*
 * Annapurna Lअसल MSIX support services
 *
 * Copyright (C) 2016, Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/msi.h>

/* MSIX message address क्रमmat: local GIC target */
#घोषणा ALPINE_MSIX_SPI_TARGET_CLUSTER0		BIT(16)

काष्ठा alpine_msix_data अणु
	spinlock_t msi_map_lock;
	phys_addr_t addr;
	u32 spi_first;		/* The SGI number that MSIs start */
	u32 num_spis;		/* The number of SGIs क्रम MSIs */
	अचिन्हित दीर्घ *msi_map;
पूर्ण;

अटल व्योम alpine_msix_mask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम alpine_msix_unmask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip alpine_msix_irq_chip = अणु
	.name			= "MSIx",
	.irq_mask		= alpine_msix_mask_msi_irq,
	.irq_unmask		= alpine_msix_unmask_msi_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक alpine_msix_allocate_sgi(काष्ठा alpine_msix_data *priv, पूर्णांक num_req)
अणु
	पूर्णांक first;

	spin_lock(&priv->msi_map_lock);

	first = biपंचांगap_find_next_zero_area(priv->msi_map, priv->num_spis, 0,
					   num_req, 0);
	अगर (first >= priv->num_spis) अणु
		spin_unlock(&priv->msi_map_lock);
		वापस -ENOSPC;
	पूर्ण

	biपंचांगap_set(priv->msi_map, first, num_req);

	spin_unlock(&priv->msi_map_lock);

	वापस priv->spi_first + first;
पूर्ण

अटल व्योम alpine_msix_मुक्त_sgi(काष्ठा alpine_msix_data *priv, अचिन्हित sgi,
				 पूर्णांक num_req)
अणु
	पूर्णांक first = sgi - priv->spi_first;

	spin_lock(&priv->msi_map_lock);

	biपंचांगap_clear(priv->msi_map, first, num_req);

	spin_unlock(&priv->msi_map_lock);
पूर्ण

अटल व्योम alpine_msix_compose_msi_msg(काष्ठा irq_data *data,
					काष्ठा msi_msg *msg)
अणु
	काष्ठा alpine_msix_data *priv = irq_data_get_irq_chip_data(data);
	phys_addr_t msg_addr = priv->addr;

	msg_addr |= (data->hwirq << 3);

	msg->address_hi = upper_32_bits(msg_addr);
	msg->address_lo = lower_32_bits(msg_addr);
	msg->data = 0;
पूर्ण

अटल काष्ठा msi_करोमुख्य_info alpine_msix_करोमुख्य_info = अणु
	.flags	= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		  MSI_FLAG_PCI_MSIX,
	.chip	= &alpine_msix_irq_chip,
पूर्ण;

अटल काष्ठा irq_chip middle_irq_chip = अणु
	.name			= "alpine_msix_middle",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_compose_msi_msg	= alpine_msix_compose_msi_msg,
पूर्ण;

अटल पूर्णांक alpine_msix_gic_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, पूर्णांक sgi)
अणु
	काष्ठा irq_fwspec fwspec;
	काष्ठा irq_data *d;
	पूर्णांक ret;

	अगर (!is_of_node(करोमुख्य->parent->fwnode))
		वापस -EINVAL;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = 0;
	fwspec.param[1] = sgi;
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (ret)
		वापस ret;

	d = irq_करोमुख्य_get_irq_data(करोमुख्य->parent, virq);
	d->chip->irq_set_type(d, IRQ_TYPE_EDGE_RISING);

	वापस 0;
पूर्ण

अटल पूर्णांक alpine_msix_middle_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq,
					   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा alpine_msix_data *priv = करोमुख्य->host_data;
	पूर्णांक sgi, err, i;

	sgi = alpine_msix_allocate_sgi(priv, nr_irqs);
	अगर (sgi < 0)
		वापस sgi;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		err = alpine_msix_gic_करोमुख्य_alloc(करोमुख्य, virq + i, sgi + i);
		अगर (err)
			जाओ err_sgi;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, sgi + i,
					      &middle_irq_chip, priv);
	पूर्ण

	वापस 0;

err_sgi:
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, i - 1);
	alpine_msix_मुक्त_sgi(priv, sgi, nr_irqs);
	वापस err;
पूर्ण

अटल व्योम alpine_msix_middle_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq,
					   अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा alpine_msix_data *priv = irq_data_get_irq_chip_data(d);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
	alpine_msix_मुक्त_sgi(priv, d->hwirq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops alpine_msix_middle_करोमुख्य_ops = अणु
	.alloc	= alpine_msix_middle_करोमुख्य_alloc,
	.मुक्त	= alpine_msix_middle_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक alpine_msix_init_करोमुख्यs(काष्ठा alpine_msix_data *priv,
				    काष्ठा device_node *node)
अणु
	काष्ठा irq_करोमुख्य *middle_करोमुख्य, *msi_करोमुख्य, *gic_करोमुख्य;
	काष्ठा device_node *gic_node;

	gic_node = of_irq_find_parent(node);
	अगर (!gic_node) अणु
		pr_err("Failed to find the GIC node\n");
		वापस -ENODEV;
	पूर्ण

	gic_करोमुख्य = irq_find_host(gic_node);
	अगर (!gic_करोमुख्य) अणु
		pr_err("Failed to find the GIC domain\n");
		वापस -ENXIO;
	पूर्ण

	middle_करोमुख्य = irq_करोमुख्य_add_tree(शून्य,
					    &alpine_msix_middle_करोमुख्य_ops,
					    priv);
	अगर (!middle_करोमुख्य) अणु
		pr_err("Failed to create the MSIX middle domain\n");
		वापस -ENOMEM;
	पूर्ण

	middle_करोमुख्य->parent = gic_करोमुख्य;

	msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
					       &alpine_msix_करोमुख्य_info,
					       middle_करोमुख्य);
	अगर (!msi_करोमुख्य) अणु
		pr_err("Failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(middle_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alpine_msix_init(काष्ठा device_node *node,
			    काष्ठा device_node *parent)
अणु
	काष्ठा alpine_msix_data *priv;
	काष्ठा resource res;
	पूर्णांक ret;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->msi_map_lock);

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		pr_err("Failed to allocate resource\n");
		जाओ err_priv;
	पूर्ण

	/*
	 * The 20 least signअगरicant bits of addr provide direct inक्रमmation
	 * regarding the पूर्णांकerrupt destination.
	 *
	 * To select the primary GIC as the target GIC, bits [18:17] must be set
	 * to 0x0. In this हाल, bit 16 (SPI_TARGET_CLUSTER0) must be set.
	 */
	priv->addr = res.start & GENMASK_ULL(63,20);
	priv->addr |= ALPINE_MSIX_SPI_TARGET_CLUSTER0;

	अगर (of_property_पढ़ो_u32(node, "al,msi-base-spi", &priv->spi_first)) अणु
		pr_err("Unable to parse MSI base\n");
		ret = -EINVAL;
		जाओ err_priv;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "al,msi-num-spis", &priv->num_spis)) अणु
		pr_err("Unable to parse MSI numbers\n");
		ret = -EINVAL;
		जाओ err_priv;
	पूर्ण

	priv->msi_map = kसुस्मृति(BITS_TO_LONGS(priv->num_spis),
				माप(*priv->msi_map),
				GFP_KERNEL);
	अगर (!priv->msi_map) अणु
		ret = -ENOMEM;
		जाओ err_priv;
	पूर्ण

	pr_debug("Registering %d msixs, starting at %d\n",
		 priv->num_spis, priv->spi_first);

	ret = alpine_msix_init_करोमुख्यs(priv, node);
	अगर (ret)
		जाओ err_map;

	वापस 0;

err_map:
	kमुक्त(priv->msi_map);
err_priv:
	kमुक्त(priv);
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(alpine_msix, "al,alpine-msix", alpine_msix_init);
