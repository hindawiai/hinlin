<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#घोषणा pr_fmt(fmt) "GICv3: " fmt

#समावेश <linux/dma-iommu.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/irqchip/arm-gic-v3.h>

काष्ठा mbi_range अणु
	u32			spi_start;
	u32			nr_spis;
	अचिन्हित दीर्घ		*bm;
पूर्ण;

अटल DEFINE_MUTEX(mbi_lock);
अटल phys_addr_t		mbi_phys_base;
अटल काष्ठा mbi_range		*mbi_ranges;
अटल अचिन्हित पूर्णांक		mbi_range_nr;

अटल काष्ठा irq_chip mbi_irq_chip = अणु
	.name			= "MBI",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक mbi_irq_gic_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq,
				       irq_hw_number_t hwirq)
अणु
	काष्ठा irq_fwspec fwspec;
	काष्ठा irq_data *d;
	पूर्णांक err;

	/*
	 * Using ACPI? There is no MBI support in the spec, you
	 * shouldn't even be here.
	 */
	अगर (!is_of_node(करोमुख्य->parent->fwnode))
		वापस -EINVAL;

	/*
	 * Let's शेष to edge. This is consistent with traditional
	 * MSIs, and प्रणालीs requiring level संकेतing will just
	 * enक्रमce the trigger on their own.
	 */
	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = 0;
	fwspec.param[1] = hwirq - 32;
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (err)
		वापस err;

	d = irq_करोमुख्य_get_irq_data(करोमुख्य->parent, virq);
	वापस d->chip->irq_set_type(d, IRQ_TYPE_EDGE_RISING);
पूर्ण

अटल व्योम mbi_मुक्त_msi(काष्ठा mbi_range *mbi, अचिन्हित पूर्णांक hwirq,
			 पूर्णांक nr_irqs)
अणु
	mutex_lock(&mbi_lock);
	biपंचांगap_release_region(mbi->bm, hwirq - mbi->spi_start,
			      get_count_order(nr_irqs));
	mutex_unlock(&mbi_lock);
पूर्ण

अटल पूर्णांक mbi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	msi_alloc_info_t *info = args;
	काष्ठा mbi_range *mbi = शून्य;
	पूर्णांक hwirq, offset, i, err = 0;

	mutex_lock(&mbi_lock);
	क्रम (i = 0; i < mbi_range_nr; i++) अणु
		offset = biपंचांगap_find_मुक्त_region(mbi_ranges[i].bm,
						 mbi_ranges[i].nr_spis,
						 get_count_order(nr_irqs));
		अगर (offset >= 0) अणु
			mbi = &mbi_ranges[i];
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mbi_lock);

	अगर (!mbi)
		वापस -ENOSPC;

	hwirq = mbi->spi_start + offset;

	err = iommu_dma_prepare_msi(info->desc,
				    mbi_phys_base + GICD_SETSPI_NSR);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		err = mbi_irq_gic_करोमुख्य_alloc(करोमुख्य, virq + i, hwirq + i);
		अगर (err)
			जाओ fail;

		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &mbi_irq_chip, mbi);
	पूर्ण

	वापस 0;

fail:
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
	mbi_मुक्त_msi(mbi, hwirq, nr_irqs);
	वापस err;
पूर्ण

अटल व्योम mbi_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा mbi_range *mbi = irq_data_get_irq_chip_data(d);

	mbi_मुक्त_msi(mbi, d->hwirq, nr_irqs);
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mbi_करोमुख्य_ops = अणु
	.alloc			= mbi_irq_करोमुख्य_alloc,
	.मुक्त			= mbi_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल व्योम mbi_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	msg[0].address_hi = upper_32_bits(mbi_phys_base + GICD_SETSPI_NSR);
	msg[0].address_lo = lower_32_bits(mbi_phys_base + GICD_SETSPI_NSR);
	msg[0].data = data->parent_data->hwirq;

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), msg);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
/* PCI-specअगरic irqchip */
अटल व्योम mbi_mask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम mbi_unmask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip mbi_msi_irq_chip = अणु
	.name			= "MSI",
	.irq_mask		= mbi_mask_msi_irq,
	.irq_unmask		= mbi_unmask_msi_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_compose_msi_msg	= mbi_compose_msi_msg,
	.irq_ग_लिखो_msi_msg	= pci_msi_करोमुख्य_ग_लिखो_msg,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mbi_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX | MSI_FLAG_MULTI_PCI_MSI),
	.chip	= &mbi_msi_irq_chip,
पूर्ण;

अटल पूर्णांक mbi_allocate_pci_करोमुख्य(काष्ठा irq_करोमुख्य *nexus_करोमुख्य,
				   काष्ठा irq_करोमुख्य **pci_करोमुख्य)
अणु
	*pci_करोमुख्य = pci_msi_create_irq_करोमुख्य(nexus_करोमुख्य->parent->fwnode,
						&mbi_msi_करोमुख्य_info,
						nexus_करोमुख्य);
	अगर (!*pci_करोमुख्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक mbi_allocate_pci_करोमुख्य(काष्ठा irq_करोमुख्य *nexus_करोमुख्य,
				   काष्ठा irq_करोमुख्य **pci_करोमुख्य)
अणु
	*pci_करोमुख्य = शून्य;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम mbi_compose_mbi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	mbi_compose_msi_msg(data, msg);

	msg[1].address_hi = upper_32_bits(mbi_phys_base + GICD_CLRSPI_NSR);
	msg[1].address_lo = lower_32_bits(mbi_phys_base + GICD_CLRSPI_NSR);
	msg[1].data = data->parent_data->hwirq;

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(data), &msg[1]);
पूर्ण

/* Platक्रमm-MSI specअगरic irqchip */
अटल काष्ठा irq_chip mbi_pmsi_irq_chip = अणु
	.name			= "pMSI",
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_compose_msi_msg	= mbi_compose_mbi_msg,
	.flags			= IRQCHIP_SUPPORTS_LEVEL_MSI,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops mbi_pmsi_ops = अणु
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mbi_pmsi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_LEVEL_CAPABLE),
	.ops	= &mbi_pmsi_ops,
	.chip	= &mbi_pmsi_irq_chip,
पूर्ण;

अटल पूर्णांक mbi_allocate_करोमुख्यs(काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा irq_करोमुख्य *nexus_करोमुख्य, *pci_करोमुख्य, *plat_करोमुख्य;
	पूर्णांक err;

	nexus_करोमुख्य = irq_करोमुख्य_create_tree(parent->fwnode,
					      &mbi_करोमुख्य_ops, शून्य);
	अगर (!nexus_करोमुख्य)
		वापस -ENOMEM;

	irq_करोमुख्य_update_bus_token(nexus_करोमुख्य, DOMAIN_BUS_NEXUS);
	nexus_करोमुख्य->parent = parent;

	err = mbi_allocate_pci_करोमुख्य(nexus_करोमुख्य, &pci_करोमुख्य);

	plat_करोमुख्य = platक्रमm_msi_create_irq_करोमुख्य(parent->fwnode,
						     &mbi_pmsi_करोमुख्य_info,
						     nexus_करोमुख्य);

	अगर (err || !plat_करोमुख्य) अणु
		अगर (plat_करोमुख्य)
			irq_करोमुख्य_हटाओ(plat_करोमुख्य);
		अगर (pci_करोमुख्य)
			irq_करोमुख्य_हटाओ(pci_करोमुख्य);
		irq_करोमुख्य_हटाओ(nexus_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init mbi_init(काष्ठा fwnode_handle *fwnode, काष्ठा irq_करोमुख्य *parent)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *reg;
	पूर्णांक ret, n;

	np = to_of_node(fwnode);

	अगर (!of_property_पढ़ो_bool(np, "msi-controller"))
		वापस 0;

	n = of_property_count_elems_of_size(np, "mbi-ranges", माप(u32));
	अगर (n <= 0 || n % 2)
		वापस -EINVAL;

	mbi_range_nr = n / 2;
	mbi_ranges = kसुस्मृति(mbi_range_nr, माप(*mbi_ranges), GFP_KERNEL);
	अगर (!mbi_ranges)
		वापस -ENOMEM;

	क्रम (n = 0; n < mbi_range_nr; n++) अणु
		ret = of_property_पढ़ो_u32_index(np, "mbi-ranges", n * 2,
						 &mbi_ranges[n].spi_start);
		अगर (ret)
			जाओ err_मुक्त_mbi;
		ret = of_property_पढ़ो_u32_index(np, "mbi-ranges", n * 2 + 1,
						 &mbi_ranges[n].nr_spis);
		अगर (ret)
			जाओ err_मुक्त_mbi;

		mbi_ranges[n].bm = kसुस्मृति(BITS_TO_LONGS(mbi_ranges[n].nr_spis),
					   माप(दीर्घ), GFP_KERNEL);
		अगर (!mbi_ranges[n].bm) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_mbi;
		पूर्ण
		pr_info("MBI range [%d:%d]\n", mbi_ranges[n].spi_start,
			mbi_ranges[n].spi_start + mbi_ranges[n].nr_spis - 1);
	पूर्ण

	reg = of_get_property(np, "mbi-alias", शून्य);
	अगर (reg) अणु
		mbi_phys_base = of_translate_address(np, reg);
		अगर (mbi_phys_base == (phys_addr_t)OF_BAD_ADDR) अणु
			ret = -ENXIO;
			जाओ err_मुक्त_mbi;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा resource res;

		अगर (of_address_to_resource(np, 0, &res)) अणु
			ret = -ENXIO;
			जाओ err_मुक्त_mbi;
		पूर्ण

		mbi_phys_base = res.start;
	पूर्ण

	pr_info("Using MBI frame %pa\n", &mbi_phys_base);

	ret = mbi_allocate_करोमुख्यs(parent);
	अगर (ret)
		जाओ err_मुक्त_mbi;

	वापस 0;

err_मुक्त_mbi:
	अगर (mbi_ranges) अणु
		क्रम (n = 0; n < mbi_range_nr; n++)
			kमुक्त(mbi_ranges[n].bm);
		kमुक्त(mbi_ranges);
	पूर्ण

	वापस ret;
पूर्ण
