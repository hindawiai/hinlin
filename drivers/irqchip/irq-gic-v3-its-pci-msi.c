<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2015 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/acpi_iort.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>

अटल व्योम its_mask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम its_unmask_msi_irq(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip its_msi_irq_chip = अणु
	.name			= "ITS-MSI",
	.irq_unmask		= its_unmask_msi_irq,
	.irq_mask		= its_mask_msi_irq,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_ग_लिखो_msi_msg	= pci_msi_करोमुख्य_ग_लिखो_msg,
पूर्ण;

अटल पूर्णांक its_pci_msi_vec_count(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	पूर्णांक msi, msix, *count = data;

	msi = max(pci_msi_vec_count(pdev), 0);
	msix = max(pci_msix_vec_count(pdev), 0);
	*count += max(msi, msix);

	वापस 0;
पूर्ण

अटल पूर्णांक its_get_pci_alias(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	काष्ठा pci_dev **alias_dev = data;

	*alias_dev = pdev;

	वापस 0;
पूर्ण

अटल पूर्णांक its_pci_msi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			       पूर्णांक nvec, msi_alloc_info_t *info)
अणु
	काष्ठा pci_dev *pdev, *alias_dev;
	काष्ठा msi_करोमुख्य_info *msi_info;
	पूर्णांक alias_count = 0, minnvec = 1;

	अगर (!dev_is_pci(dev))
		वापस -EINVAL;

	msi_info = msi_get_करोमुख्य_info(करोमुख्य->parent);

	pdev = to_pci_dev(dev);
	/*
	 * If pdev is करोwnstream of any aliasing bridges, take an upper
	 * bound of how many other vectors could map to the same DevID.
	 * Also tell the ITS that the संकेतling will come from a proxy
	 * device, and that special allocation rules apply.
	 */
	pci_क्रम_each_dma_alias(pdev, its_get_pci_alias, &alias_dev);
	अगर (alias_dev != pdev) अणु
		अगर (alias_dev->subordinate)
			pci_walk_bus(alias_dev->subordinate,
				     its_pci_msi_vec_count, &alias_count);
		info->flags |= MSI_ALLOC_FLAGS_PROXY_DEVICE;
	पूर्ण

	/* ITS specअगरic DeviceID, as the core ITS ignores dev. */
	info->scratchpad[0].ul = pci_msi_करोमुख्य_get_msi_rid(करोमुख्य, pdev);

	/*
	 * Always allocate a घातer of 2, and special हाल device 0 क्रम
	 * broken प्रणालीs where the DevID is not wired (and all devices
	 * appear as DevID 0). For that reason, we generously allocate a
	 * minimum of 32 MSIs क्रम DevID 0. If you want more because all
	 * your devices are aliasing to DevID 0, consider fixing your HW.
	 */
	nvec = max(nvec, alias_count);
	अगर (!info->scratchpad[0].ul)
		minnvec = 32;
	nvec = max_t(पूर्णांक, minnvec, roundup_घात_of_two(nvec));
	वापस msi_info->ops->msi_prepare(करोमुख्य->parent, dev, nvec, info);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops its_pci_msi_ops = अणु
	.msi_prepare	= its_pci_msi_prepare,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info its_pci_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_MULTI_PCI_MSI | MSI_FLAG_PCI_MSIX),
	.ops	= &its_pci_msi_ops,
	.chip	= &its_msi_irq_chip,
पूर्ण;

अटल काष्ठा of_device_id its_device_id[] = अणु
	अणु	.compatible	= "arm,gic-v3-its",	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init its_pci_msi_init_one(काष्ठा fwnode_handle *handle,
				       स्थिर अक्षर *name)
अणु
	काष्ठा irq_करोमुख्य *parent;

	parent = irq_find_matching_fwnode(handle, DOMAIN_BUS_NEXUS);
	अगर (!parent || !msi_get_करोमुख्य_info(parent)) अणु
		pr_err("%s: Unable to locate ITS domain\n", name);
		वापस -ENXIO;
	पूर्ण

	अगर (!pci_msi_create_irq_करोमुख्य(handle, &its_pci_msi_करोमुख्य_info,
				       parent)) अणु
		pr_err("%s: Unable to create PCI domain\n", name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init its_pci_of_msi_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम (np = of_find_matching_node(शून्य, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) अणु
		अगर (!of_device_is_available(np))
			जारी;
		अगर (!of_property_पढ़ो_bool(np, "msi-controller"))
			जारी;

		अगर (its_pci_msi_init_one(of_node_to_fwnode(np), np->full_name))
			जारी;

		pr_info("PCI/MSI: %pOF domain created\n", np);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल पूर्णांक __init
its_pci_msi_parse_madt(जोड़ acpi_subtable_headers *header,
		       स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_translator *its_entry;
	काष्ठा fwnode_handle *करोm_handle;
	स्थिर अक्षर *node_name;
	पूर्णांक err = -ENXIO;

	its_entry = (काष्ठा acpi_madt_generic_translator *)header;
	node_name = kaप्र_लिखो(GFP_KERNEL, "ITS@0x%lx",
			      (दीर्घ)its_entry->base_address);
	करोm_handle = iort_find_करोमुख्य_token(its_entry->translation_id);
	अगर (!करोm_handle) अणु
		pr_err("%s: Unable to locate ITS domain handle\n", node_name);
		जाओ out;
	पूर्ण

	err = its_pci_msi_init_one(करोm_handle, node_name);
	अगर (!err)
		pr_info("PCI/MSI: %s domain created\n", node_name);

out:
	kमुक्त(node_name);
	वापस err;
पूर्ण

अटल पूर्णांक __init its_pci_acpi_msi_init(व्योम)
अणु
	acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_TRANSLATOR,
			      its_pci_msi_parse_madt, 0);
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक __init its_pci_acpi_msi_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init its_pci_msi_init(व्योम)
अणु
	its_pci_of_msi_init();
	its_pci_acpi_msi_init();

	वापस 0;
पूर्ण
early_initcall(its_pci_msi_init);
