<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale Management Complex (MC) bus driver MSI support
 *
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc.
 * Author: German Rivera <German.Rivera@मुक्तscale.com>
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/fsl/mc.h>

अटल काष्ठा irq_chip its_msi_irq_chip = अणु
	.name = "ITS-fMSI",
	.irq_mask = irq_chip_mask_parent,
	.irq_unmask = irq_chip_unmask_parent,
	.irq_eoi = irq_chip_eoi_parent,
	.irq_set_affinity = msi_करोमुख्य_set_affinity
पूर्ण;

अटल u32 fsl_mc_msi_करोमुख्य_get_msi_id(काष्ठा irq_करोमुख्य *करोमुख्य,
					काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा device_node *of_node;
	u32 out_id;

	of_node = irq_करोमुख्य_get_of_node(करोमुख्य);
	out_id = of_node ? of_msi_map_id(&mc_dev->dev, of_node, mc_dev->icid) :
			iort_msi_map_id(&mc_dev->dev, mc_dev->icid);

	वापस out_id;
पूर्ण

अटल पूर्णांक its_fsl_mc_msi_prepare(काष्ठा irq_करोमुख्य *msi_करोमुख्य,
				  काष्ठा device *dev,
				  पूर्णांक nvec, msi_alloc_info_t *info)
अणु
	काष्ठा fsl_mc_device *mc_bus_dev;
	काष्ठा msi_करोमुख्य_info *msi_info;

	अगर (!dev_is_fsl_mc(dev))
		वापस -EINVAL;

	mc_bus_dev = to_fsl_mc_device(dev);
	अगर (!(mc_bus_dev->flags & FSL_MC_IS_DPRC))
		वापस -EINVAL;

	/*
	 * Set the device Id to be passed to the GIC-ITS:
	 *
	 * NOTE: This device id corresponds to the IOMMU stream ID
	 * associated with the DPRC object (ICID).
	 */
	info->scratchpad[0].ul = fsl_mc_msi_करोमुख्य_get_msi_id(msi_करोमुख्य,
							      mc_bus_dev);
	msi_info = msi_get_करोमुख्य_info(msi_करोमुख्य->parent);

	/* Allocate at least 32 MSIs, and always as a घातer of 2 */
	nvec = max_t(पूर्णांक, 32, roundup_घात_of_two(nvec));
	वापस msi_info->ops->msi_prepare(msi_करोमुख्य->parent, dev, nvec, info);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops its_fsl_mc_msi_ops __ro_after_init = अणु
	.msi_prepare = its_fsl_mc_msi_prepare,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info its_fsl_mc_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.ops	= &its_fsl_mc_msi_ops,
	.chip	= &its_msi_irq_chip,
पूर्ण;

अटल स्थिर काष्ठा of_device_id its_device_id[] = अणु
	अणु	.compatible	= "arm,gic-v3-its",	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init its_fsl_mc_msi_init_one(काष्ठा fwnode_handle *handle,
					  स्थिर अक्षर *name)
अणु
	काष्ठा irq_करोमुख्य *parent;
	काष्ठा irq_करोमुख्य *mc_msi_करोमुख्य;

	parent = irq_find_matching_fwnode(handle, DOMAIN_BUS_NEXUS);
	अगर (!parent || !msi_get_करोमुख्य_info(parent)) अणु
		pr_err("%s: unable to locate ITS domain\n", name);
		वापस;
	पूर्ण

	mc_msi_करोमुख्य = fsl_mc_msi_create_irq_करोमुख्य(handle,
						&its_fsl_mc_msi_करोमुख्य_info,
						parent);
	अगर (!mc_msi_करोमुख्य) अणु
		pr_err("%s: unable to create fsl-mc domain\n", name);
		वापस;
	पूर्ण

	pr_info("fsl-mc MSI: %s domain created\n", name);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक __init
its_fsl_mc_msi_parse_madt(जोड़ acpi_subtable_headers *header,
			  स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_translator *its_entry;
	काष्ठा fwnode_handle *करोm_handle;
	स्थिर अक्षर *node_name;
	पूर्णांक err = 0;

	its_entry = (काष्ठा acpi_madt_generic_translator *)header;
	node_name = kaप्र_लिखो(GFP_KERNEL, "ITS@0x%lx",
			      (दीर्घ)its_entry->base_address);

	करोm_handle = iort_find_करोमुख्य_token(its_entry->translation_id);
	अगर (!करोm_handle) अणु
		pr_err("%s: Unable to locate ITS domain handle\n", node_name);
		err = -ENXIO;
		जाओ out;
	पूर्ण

	its_fsl_mc_msi_init_one(करोm_handle, node_name);

out:
	kमुक्त(node_name);
	वापस err;
पूर्ण


अटल व्योम __init its_fsl_mc_acpi_msi_init(व्योम)
अणु
	acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_TRANSLATOR,
			      its_fsl_mc_msi_parse_madt, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम its_fsl_mc_acpi_msi_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init its_fsl_mc_of_msi_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम (np = of_find_matching_node(शून्य, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) अणु
		अगर (!of_device_is_available(np))
			जारी;
		अगर (!of_property_पढ़ो_bool(np, "msi-controller"))
			जारी;

		its_fsl_mc_msi_init_one(of_node_to_fwnode(np),
					np->full_name);
	पूर्ण
पूर्ण

अटल पूर्णांक __init its_fsl_mc_msi_init(व्योम)
अणु
	its_fsl_mc_of_msi_init();
	its_fsl_mc_acpi_msi_init();

	वापस 0;
पूर्ण

early_initcall(its_fsl_mc_msi_init);
