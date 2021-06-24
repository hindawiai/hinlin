<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2015 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/acpi_iort.h>
#समावेश <linux/device.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

अटल काष्ठा irq_chip its_pmsi_irq_chip = अणु
	.name			= "ITS-pMSI",
पूर्ण;

अटल पूर्णांक of_pmsi_get_dev_id(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
				  u32 *dev_id)
अणु
	पूर्णांक ret, index = 0;

	/* Suck the DeviceID out of the msi-parent property */
	करो अणु
		काष्ठा of_phandle_args args;

		ret = of_parse_phandle_with_args(dev->of_node,
						 "msi-parent", "#msi-cells",
						 index, &args);
		अगर (args.np == irq_करोमुख्य_get_of_node(करोमुख्य)) अणु
			अगर (WARN_ON(args.args_count != 1))
				वापस -EINVAL;
			*dev_id = args.args[0];
			अवरोध;
		पूर्ण
		index++;
	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

पूर्णांक __weak iort_pmsi_get_dev_id(काष्ठा device *dev, u32 *dev_id)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक its_pmsi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			    पूर्णांक nvec, msi_alloc_info_t *info)
अणु
	काष्ठा msi_करोमुख्य_info *msi_info;
	u32 dev_id;
	पूर्णांक ret;

	msi_info = msi_get_करोमुख्य_info(करोमुख्य->parent);

	अगर (dev->of_node)
		ret = of_pmsi_get_dev_id(करोमुख्य, dev, &dev_id);
	अन्यथा
		ret = iort_pmsi_get_dev_id(dev, &dev_id);
	अगर (ret)
		वापस ret;

	/* ITS specअगरic DeviceID, as the core ITS ignores dev. */
	info->scratchpad[0].ul = dev_id;

	/* Allocate at least 32 MSIs, and always as a घातer of 2 */
	nvec = max_t(पूर्णांक, 32, roundup_घात_of_two(nvec));
	वापस msi_info->ops->msi_prepare(करोमुख्य->parent,
					  dev, nvec, info);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops its_pmsi_ops = अणु
	.msi_prepare	= its_pmsi_prepare,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info its_pmsi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.ops	= &its_pmsi_ops,
	.chip	= &its_pmsi_irq_chip,
पूर्ण;

अटल स्थिर काष्ठा of_device_id its_device_id[] = अणु
	अणु	.compatible	= "arm,gic-v3-its",	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init its_pmsi_init_one(काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *name)
अणु
	काष्ठा irq_करोमुख्य *parent;

	parent = irq_find_matching_fwnode(fwnode, DOMAIN_BUS_NEXUS);
	अगर (!parent || !msi_get_करोमुख्य_info(parent)) अणु
		pr_err("%s: unable to locate ITS domain\n", name);
		वापस -ENXIO;
	पूर्ण

	अगर (!platक्रमm_msi_create_irq_करोमुख्य(fwnode, &its_pmsi_करोमुख्य_info,
					    parent)) अणु
		pr_err("%s: unable to create platform domain\n", name);
		वापस -ENXIO;
	पूर्ण

	pr_info("Platform MSI: %s domain created\n", name);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक __init
its_pmsi_parse_madt(जोड़ acpi_subtable_headers *header,
			स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_translator *its_entry;
	काष्ठा fwnode_handle *करोमुख्य_handle;
	स्थिर अक्षर *node_name;
	पूर्णांक err = -ENXIO;

	its_entry = (काष्ठा acpi_madt_generic_translator *)header;
	node_name = kaप्र_लिखो(GFP_KERNEL, "ITS@0x%lx",
			      (दीर्घ)its_entry->base_address);
	करोमुख्य_handle = iort_find_करोमुख्य_token(its_entry->translation_id);
	अगर (!करोमुख्य_handle) अणु
		pr_err("%s: Unable to locate ITS domain handle\n", node_name);
		जाओ out;
	पूर्ण

	err = its_pmsi_init_one(करोमुख्य_handle, node_name);

out:
	kमुक्त(node_name);
	वापस err;
पूर्ण

अटल व्योम __init its_pmsi_acpi_init(व्योम)
अणु
	acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_TRANSLATOR,
			      its_pmsi_parse_madt, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम its_pmsi_acpi_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init its_pmsi_of_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम (np = of_find_matching_node(शून्य, its_device_id); np;
	     np = of_find_matching_node(np, its_device_id)) अणु
		अगर (!of_device_is_available(np))
			जारी;
		अगर (!of_property_पढ़ो_bool(np, "msi-controller"))
			जारी;

		its_pmsi_init_one(of_node_to_fwnode(np), np->full_name);
	पूर्ण
पूर्ण

अटल पूर्णांक __init its_pmsi_init(व्योम)
अणु
	its_pmsi_of_init();
	its_pmsi_acpi_init();
	वापस 0;
पूर्ण
early_initcall(its_pmsi_init);
