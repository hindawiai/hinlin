<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM GIC v2m MSI(-X) support
 * Support क्रम Message Signaled Interrupts क्रम प्रणालीs that
 * implement ARM Generic Interrupt Controller: GICv2m.
 *
 * Copyright (C) 2014 Advanced Micro Devices, Inc.
 * Authors: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
 *	    Harish Kasiviswanathan <harish.kasiviswanathan@amd.com>
 *	    Bअक्रमon Anderson <bअक्रमon.anderson@amd.com>
 */

#घोषणा pr_fmt(fmt) "GICv2m: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irqchip/arm-gic.h>

/*
* MSI_TYPER:
*     [31:26] Reserved
*     [25:16] lowest SPI asचिन्हित to MSI
*     [15:10] Reserved
*     [9:0]   Numer of SPIs asचिन्हित to MSI
*/
#घोषणा V2M_MSI_TYPER		       0x008
#घोषणा V2M_MSI_TYPER_BASE_SHIFT       16
#घोषणा V2M_MSI_TYPER_BASE_MASK	       0x3FF
#घोषणा V2M_MSI_TYPER_NUM_MASK	       0x3FF
#घोषणा V2M_MSI_SETSPI_NS	       0x040
#घोषणा V2M_MIN_SPI		       32
#घोषणा V2M_MAX_SPI		       1019
#घोषणा V2M_MSI_IIDR		       0xFCC

#घोषणा V2M_MSI_TYPER_BASE_SPI(x)      \
	       (((x) >> V2M_MSI_TYPER_BASE_SHIFT) & V2M_MSI_TYPER_BASE_MASK)

#घोषणा V2M_MSI_TYPER_NUM_SPI(x)       ((x) & V2M_MSI_TYPER_NUM_MASK)

/* APM X-Gene with GICv2m MSI_IIDR रेजिस्टर value */
#घोषणा XGENE_GICV2M_MSI_IIDR		0x06000170

/* Broadcom NS2 GICv2m MSI_IIDR रेजिस्टर value */
#घोषणा BCM_NS2_GICV2M_MSI_IIDR		0x0000013f

/* List of flags क्रम specअगरic v2m implementation */
#घोषणा GICV2M_NEEDS_SPI_OFFSET		0x00000001
#घोषणा GICV2M_GRAVITON_ADDRESS_ONLY	0x00000002

अटल LIST_HEAD(v2m_nodes);
अटल DEFINE_SPINLOCK(v2m_lock);

काष्ठा v2m_data अणु
	काष्ठा list_head entry;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा resource res;	/* GICv2m resource */
	व्योम __iomem *base;	/* GICv2m virt address */
	u32 spi_start;		/* The SPI number that MSIs start */
	u32 nr_spis;		/* The number of SPIs क्रम MSIs */
	u32 spi_offset;		/* offset to be subtracted from SPI number */
	अचिन्हित दीर्घ *bm;	/* MSI vector biपंचांगap */
	u32 flags;		/* v2m flags क्रम specअगरic implementation */
पूर्ण;

अटल व्योम gicv2m_mask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम gicv2m_unmask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip gicv2m_msi_irq_chip = अणु
	.name			= "MSI",
	.irq_mask		= gicv2m_mask_msi_irq,
	.irq_unmask		= gicv2m_unmask_msi_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_ग_लिखो_msi_msg	= pci_msi_करोमुख्य_ग_लिखो_msg,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info gicv2m_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX | MSI_FLAG_MULTI_PCI_MSI),
	.chip	= &gicv2m_msi_irq_chip,
पूर्ण;

अटल phys_addr_t gicv2m_get_msi_addr(काष्ठा v2m_data *v2m, पूर्णांक hwirq)
अणु
	अगर (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
		वापस v2m->res.start | ((hwirq - 32) << 3);
	अन्यथा
		वापस v2m->res.start + V2M_MSI_SETSPI_NS;
पूर्ण

अटल व्योम gicv2m_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा v2m_data *v2m = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = gicv2m_get_msi_addr(v2m, data->hwirq);

	msg->address_hi = upper_32_bits(addr);
	msg->address_lo = lower_32_bits(addr);

	अगर (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
		msg->data = 0;
	अन्यथा
		msg->data = data->hwirq;
	अगर (v2m->flags & GICV2M_NEEDS_SPI_OFFSET)
		msg->data -= v2m->spi_offset;

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), msg);
पूर्ण

अटल काष्ठा irq_chip gicv2m_irq_chip = अणु
	.name			= "GICv2m",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_compose_msi_msg	= gicv2m_compose_msi_msg,
पूर्ण;

अटल पूर्णांक gicv2m_irq_gic_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq,
				       irq_hw_number_t hwirq)
अणु
	काष्ठा irq_fwspec fwspec;
	काष्ठा irq_data *d;
	पूर्णांक err;

	अगर (is_of_node(करोमुख्य->parent->fwnode)) अणु
		fwspec.fwnode = करोमुख्य->parent->fwnode;
		fwspec.param_count = 3;
		fwspec.param[0] = 0;
		fwspec.param[1] = hwirq - 32;
		fwspec.param[2] = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा अगर (is_fwnode_irqchip(करोमुख्य->parent->fwnode)) अणु
		fwspec.fwnode = करोमुख्य->parent->fwnode;
		fwspec.param_count = 2;
		fwspec.param[0] = hwirq;
		fwspec.param[1] = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (err)
		वापस err;

	/* Configure the पूर्णांकerrupt line to be edge */
	d = irq_करोमुख्य_get_irq_data(करोमुख्य->parent, virq);
	d->chip->irq_set_type(d, IRQ_TYPE_EDGE_RISING);
	वापस 0;
पूर्ण

अटल व्योम gicv2m_unalloc_msi(काष्ठा v2m_data *v2m, अचिन्हित पूर्णांक hwirq,
			       पूर्णांक nr_irqs)
अणु
	spin_lock(&v2m_lock);
	biपंचांगap_release_region(v2m->bm, hwirq - v2m->spi_start,
			      get_count_order(nr_irqs));
	spin_unlock(&v2m_lock);
पूर्ण

अटल पूर्णांक gicv2m_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	msi_alloc_info_t *info = args;
	काष्ठा v2m_data *v2m = शून्य, *पंचांगp;
	पूर्णांक hwirq, offset, i, err = 0;

	spin_lock(&v2m_lock);
	list_क्रम_each_entry(पंचांगp, &v2m_nodes, entry) अणु
		offset = biपंचांगap_find_मुक्त_region(पंचांगp->bm, पंचांगp->nr_spis,
						 get_count_order(nr_irqs));
		अगर (offset >= 0) अणु
			v2m = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&v2m_lock);

	अगर (!v2m)
		वापस -ENOSPC;

	hwirq = v2m->spi_start + offset;

	err = iommu_dma_prepare_msi(info->desc,
				    gicv2m_get_msi_addr(v2m, hwirq));
	अगर (err)
		वापस err;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		err = gicv2m_irq_gic_करोमुख्य_alloc(करोमुख्य, virq + i, hwirq + i);
		अगर (err)
			जाओ fail;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &gicv2m_irq_chip, v2m);
	पूर्ण

	वापस 0;

fail:
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
	gicv2m_unalloc_msi(v2m, hwirq, nr_irqs);
	वापस err;
पूर्ण

अटल व्योम gicv2m_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				   अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा v2m_data *v2m = irq_data_get_irq_chip_data(d);

	gicv2m_unalloc_msi(v2m, d->hwirq, nr_irqs);
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gicv2m_करोमुख्य_ops = अणु
	.alloc			= gicv2m_irq_करोमुख्य_alloc,
	.मुक्त			= gicv2m_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल bool is_msi_spi_valid(u32 base, u32 num)
अणु
	अगर (base < V2M_MIN_SPI) अणु
		pr_err("Invalid MSI base SPI (base:%u)\n", base);
		वापस false;
	पूर्ण

	अगर ((num == 0) || (base + num > V2M_MAX_SPI)) अणु
		pr_err("Number of SPIs (%u) exceed maximum (%u)\n",
		       num, V2M_MAX_SPI - V2M_MIN_SPI + 1);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा irq_chip gicv2m_pmsi_irq_chip = अणु
	.name			= "pMSI",
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops gicv2m_pmsi_ops = अणु
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info gicv2m_pmsi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.ops	= &gicv2m_pmsi_ops,
	.chip	= &gicv2m_pmsi_irq_chip,
पूर्ण;

अटल व्योम gicv2m_tearकरोwn(व्योम)
अणु
	काष्ठा v2m_data *v2m, *पंचांगp;

	list_क्रम_each_entry_safe(v2m, पंचांगp, &v2m_nodes, entry) अणु
		list_del(&v2m->entry);
		kमुक्त(v2m->bm);
		iounmap(v2m->base);
		of_node_put(to_of_node(v2m->fwnode));
		अगर (is_fwnode_irqchip(v2m->fwnode))
			irq_करोमुख्य_मुक्त_fwnode(v2m->fwnode);
		kमुक्त(v2m);
	पूर्ण
पूर्ण

अटल पूर्णांक gicv2m_allocate_करोमुख्यs(काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *inner_करोमुख्य, *pci_करोमुख्य, *plat_करोमुख्य;
	काष्ठा v2m_data *v2m;

	v2m = list_first_entry_or_null(&v2m_nodes, काष्ठा v2m_data, entry);
	अगर (!v2m)
		वापस 0;

	inner_करोमुख्य = irq_करोमुख्य_create_tree(v2m->fwnode,
					      &gicv2m_करोमुख्य_ops, v2m);
	अगर (!inner_करोमुख्य) अणु
		pr_err("Failed to create GICv2m domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_करोमुख्य_update_bus_token(inner_करोमुख्य, DOMAIN_BUS_NEXUS);
	inner_करोमुख्य->parent = parent;
	pci_करोमुख्य = pci_msi_create_irq_करोमुख्य(v2m->fwnode,
					       &gicv2m_msi_करोमुख्य_info,
					       inner_करोमुख्य);
	plat_करोमुख्य = platक्रमm_msi_create_irq_करोमुख्य(v2m->fwnode,
						     &gicv2m_pmsi_करोमुख्य_info,
						     inner_करोमुख्य);
	अगर (!pci_करोमुख्य || !plat_करोमुख्य) अणु
		pr_err("Failed to create MSI domains\n");
		अगर (plat_करोमुख्य)
			irq_करोमुख्य_हटाओ(plat_करोमुख्य);
		अगर (pci_करोमुख्य)
			irq_करोमुख्य_हटाओ(pci_करोमुख्य);
		irq_करोमुख्य_हटाओ(inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init gicv2m_init_one(काष्ठा fwnode_handle *fwnode,
				  u32 spi_start, u32 nr_spis,
				  काष्ठा resource *res, u32 flags)
अणु
	पूर्णांक ret;
	काष्ठा v2m_data *v2m;

	v2m = kzalloc(माप(काष्ठा v2m_data), GFP_KERNEL);
	अगर (!v2m) अणु
		pr_err("Failed to allocate struct v2m_data.\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&v2m->entry);
	v2m->fwnode = fwnode;
	v2m->flags = flags;

	स_नकल(&v2m->res, res, माप(काष्ठा resource));

	v2m->base = ioremap(v2m->res.start, resource_size(&v2m->res));
	अगर (!v2m->base) अणु
		pr_err("Failed to map GICv2m resource\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_v2m;
	पूर्ण

	अगर (spi_start && nr_spis) अणु
		v2m->spi_start = spi_start;
		v2m->nr_spis = nr_spis;
	पूर्ण अन्यथा अणु
		u32 typer;

		/* Graviton should always have explicit spi_start/nr_spis */
		अगर (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY) अणु
			ret = -EINVAL;
			जाओ err_iounmap;
		पूर्ण
		typer = पढ़ोl_relaxed(v2m->base + V2M_MSI_TYPER);

		v2m->spi_start = V2M_MSI_TYPER_BASE_SPI(typer);
		v2m->nr_spis = V2M_MSI_TYPER_NUM_SPI(typer);
	पूर्ण

	अगर (!is_msi_spi_valid(v2m->spi_start, v2m->nr_spis)) अणु
		ret = -EINVAL;
		जाओ err_iounmap;
	पूर्ण

	/*
	 * APM X-Gene GICv2m implementation has an erratum where
	 * the MSI data needs to be the offset from the spi_start
	 * in order to trigger the correct MSI पूर्णांकerrupt. This is
	 * dअगरferent from the standard GICv2m implementation where
	 * the MSI data is the असलolute value within the range from
	 * spi_start to (spi_start + num_spis).
	 *
	 * Broadcom NS2 GICv2m implementation has an erratum where the MSI data
	 * is 'spi_number - 32'
	 *
	 * Reading that रेजिस्टर fails on the Graviton implementation
	 */
	अगर (!(v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)) अणु
		चयन (पढ़ोl_relaxed(v2m->base + V2M_MSI_IIDR)) अणु
		हाल XGENE_GICV2M_MSI_IIDR:
			v2m->flags |= GICV2M_NEEDS_SPI_OFFSET;
			v2m->spi_offset = v2m->spi_start;
			अवरोध;
		हाल BCM_NS2_GICV2M_MSI_IIDR:
			v2m->flags |= GICV2M_NEEDS_SPI_OFFSET;
			v2m->spi_offset = 32;
			अवरोध;
		पूर्ण
	पूर्ण
	v2m->bm = kसुस्मृति(BITS_TO_LONGS(v2m->nr_spis), माप(दीर्घ),
			  GFP_KERNEL);
	अगर (!v2m->bm) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	list_add_tail(&v2m->entry, &v2m_nodes);

	pr_info("range%pR, SPI[%d:%d]\n", res,
		v2m->spi_start, (v2m->spi_start + v2m->nr_spis - 1));
	वापस 0;

err_iounmap:
	iounmap(v2m->base);
err_मुक्त_v2m:
	kमुक्त(v2m);
	वापस ret;
पूर्ण

अटल काष्ठा of_device_id gicv2m_device_id[] = अणु
	अणु	.compatible	= "arm,gic-v2m-frame",	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init gicv2m_of_init(काष्ठा fwnode_handle *parent_handle,
				 काष्ठा irq_करोमुख्य *parent)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_node *node = to_of_node(parent_handle);
	काष्ठा device_node *child;

	क्रम (child = of_find_matching_node(node, gicv2m_device_id); child;
	     child = of_find_matching_node(child, gicv2m_device_id)) अणु
		u32 spi_start = 0, nr_spis = 0;
		काष्ठा resource res;

		अगर (!of_find_property(child, "msi-controller", शून्य))
			जारी;

		ret = of_address_to_resource(child, 0, &res);
		अगर (ret) अणु
			pr_err("Failed to allocate v2m resource.\n");
			अवरोध;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "arm,msi-base-spi",
					  &spi_start) &&
		    !of_property_पढ़ो_u32(child, "arm,msi-num-spis", &nr_spis))
			pr_info("DT overriding V2M MSI_TYPER (base:%u, num:%u)\n",
				spi_start, nr_spis);

		ret = gicv2m_init_one(&child->fwnode, spi_start, nr_spis,
				      &res, 0);
		अगर (ret) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret)
		ret = gicv2m_allocate_करोमुख्यs(parent);
	अगर (ret)
		gicv2m_tearकरोwn();
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक acpi_num_msi;

अटल काष्ठा fwnode_handle *gicv2m_get_fwnode(काष्ठा device *dev)
अणु
	काष्ठा v2m_data *data;

	अगर (WARN_ON(acpi_num_msi <= 0))
		वापस शून्य;

	/* We only वापस the fwnode of the first MSI frame. */
	data = list_first_entry_or_null(&v2m_nodes, काष्ठा v2m_data, entry);
	अगर (!data)
		वापस शून्य;

	वापस data->fwnode;
पूर्ण

अटल bool acpi_check_amazon_graviton_quirks(व्योम)
अणु
	अटल काष्ठा acpi_table_madt *madt;
	acpi_status status;
	bool rc = false;

#घोषणा ACPI_AMZN_OEM_ID		"AMAZON"

	status = acpi_get_table(ACPI_SIG_MADT, 0,
				(काष्ठा acpi_table_header **)&madt);

	अगर (ACPI_FAILURE(status) || !madt)
		वापस rc;
	rc = !स_भेद(madt->header.oem_id, ACPI_AMZN_OEM_ID, ACPI_OEM_ID_SIZE);
	acpi_put_table((काष्ठा acpi_table_header *)madt);

	वापस rc;
पूर्ण

अटल पूर्णांक __init
acpi_parse_madt_msi(जोड़ acpi_subtable_headers *header,
		    स्थिर अचिन्हित दीर्घ end)
अणु
	पूर्णांक ret;
	काष्ठा resource res;
	u32 spi_start = 0, nr_spis = 0;
	काष्ठा acpi_madt_generic_msi_frame *m;
	काष्ठा fwnode_handle *fwnode;
	u32 flags = 0;

	m = (काष्ठा acpi_madt_generic_msi_frame *)header;
	अगर (BAD_MADT_ENTRY(m, end))
		वापस -EINVAL;

	res.start = m->base_address;
	res.end = m->base_address + SZ_4K - 1;
	res.flags = IORESOURCE_MEM;

	अगर (acpi_check_amazon_graviton_quirks()) अणु
		pr_info("applying Amazon Graviton quirk\n");
		res.end = res.start + SZ_8K - 1;
		flags |= GICV2M_GRAVITON_ADDRESS_ONLY;
		gicv2m_msi_करोमुख्य_info.flags &= ~MSI_FLAG_MULTI_PCI_MSI;
	पूर्ण

	अगर (m->flags & ACPI_MADT_OVERRIDE_SPI_VALUES) अणु
		spi_start = m->spi_base;
		nr_spis = m->spi_count;

		pr_info("ACPI overriding V2M MSI_TYPER (base:%u, num:%u)\n",
			spi_start, nr_spis);
	पूर्ण

	fwnode = irq_करोमुख्य_alloc_fwnode(&res.start);
	अगर (!fwnode) अणु
		pr_err("Unable to allocate GICv2m domain token\n");
		वापस -EINVAL;
	पूर्ण

	ret = gicv2m_init_one(fwnode, spi_start, nr_spis, &res, flags);
	अगर (ret)
		irq_करोमुख्य_मुक्त_fwnode(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक __init gicv2m_acpi_init(काष्ठा irq_करोमुख्य *parent)
अणु
	पूर्णांक ret;

	अगर (acpi_num_msi > 0)
		वापस 0;

	acpi_num_msi = acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_MSI_FRAME,
				      acpi_parse_madt_msi, 0);

	अगर (acpi_num_msi <= 0)
		जाओ err_out;

	ret = gicv2m_allocate_करोमुख्यs(parent);
	अगर (ret)
		जाओ err_out;

	pci_msi_रेजिस्टर_fwnode_provider(&gicv2m_get_fwnode);

	वापस 0;

err_out:
	gicv2m_tearकरोwn();
	वापस -EINVAL;
पूर्ण
#अन्यथा /* CONFIG_ACPI */
अटल पूर्णांक __init gicv2m_acpi_init(काष्ठा irq_करोमुख्य *parent)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

पूर्णांक __init gicv2m_init(काष्ठा fwnode_handle *parent_handle,
		       काष्ठा irq_करोमुख्य *parent)
अणु
	अगर (is_of_node(parent_handle))
		वापस gicv2m_of_init(parent_handle, parent);

	वापस gicv2m_acpi_init(parent);
पूर्ण
