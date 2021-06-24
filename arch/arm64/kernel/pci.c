<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Code borrowed from घातerpc/kernel/pci-common.c
 *
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 * Copyright (C) 2014 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_ACPI
/*
 * Try to assign the IRQ number when probing a new device
 */
पूर्णांक pcibios_alloc_irq(काष्ठा pci_dev *dev)
अणु
	अगर (!acpi_disabled)
		acpi_pci_irq_enable(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * raw_pci_पढ़ो/ग_लिखो - Platक्रमm-specअगरic PCI config space access.
 */
पूर्णांक raw_pci_पढ़ो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
		  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_bus *b = pci_find_bus(करोमुख्य, bus);

	अगर (!b)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	वापस b->ops->पढ़ो(b, devfn, reg, len, val);
पूर्ण

पूर्णांक raw_pci_ग_लिखो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
		अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_bus *b = pci_find_bus(करोमुख्य, bus);

	अगर (!b)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	वापस b->ops->ग_लिखो(b, devfn, reg, len, val);
पूर्ण

#अगर_घोषित CONFIG_NUMA

पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	वापस dev_to_node(&bus->dev);
पूर्ण
EXPORT_SYMBOL(pcibus_to_node);

#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI

काष्ठा acpi_pci_generic_root_info अणु
	काष्ठा acpi_pci_root_info	common;
	काष्ठा pci_config_winकरोw	*cfg;	/* config space mapping */
पूर्ण;

पूर्णांक acpi_pci_bus_find_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	काष्ठा acpi_device *adev = to_acpi_device(cfg->parent);
	काष्ठा acpi_pci_root *root = acpi_driver_data(adev);

	वापस root->segment;
पूर्ण

पूर्णांक pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	अगर (!acpi_disabled) अणु
		काष्ठा pci_config_winकरोw *cfg = bridge->bus->sysdata;
		काष्ठा acpi_device *adev = to_acpi_device(cfg->parent);
		काष्ठा device *bus_dev = &bridge->bus->dev;

		ACPI_COMPANION_SET(&bridge->dev, adev);
		set_dev_node(bus_dev, acpi_get_node(acpi_device_handle(adev)));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_acpi_root_prepare_resources(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा resource_entry *entry, *पंचांगp;
	पूर्णांक status;

	status = acpi_pci_probe_root_resources(ci);
	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &ci->resources) अणु
		अगर (!(entry->res->flags & IORESOURCE_WINDOW))
			resource_list_destroy_entry(entry);
	पूर्ण
	वापस status;
पूर्ण

/*
 * Lookup the bus range क्रम the करोमुख्य in MCFG, and set up config space
 * mapping.
 */
अटल काष्ठा pci_config_winकरोw *
pci_acpi_setup_ecam_mapping(काष्ठा acpi_pci_root *root)
अणु
	काष्ठा device *dev = &root->device->dev;
	काष्ठा resource *bus_res = &root->secondary;
	u16 seg = root->segment;
	स्थिर काष्ठा pci_ecam_ops *ecam_ops;
	काष्ठा resource cfgres;
	काष्ठा acpi_device *adev;
	काष्ठा pci_config_winकरोw *cfg;
	पूर्णांक ret;

	ret = pci_mcfg_lookup(root, &cfgres, &ecam_ops);
	अगर (ret) अणु
		dev_err(dev, "%04x:%pR ECAM region not found\n", seg, bus_res);
		वापस शून्य;
	पूर्ण

	adev = acpi_resource_consumer(&cfgres);
	अगर (adev)
		dev_info(dev, "ECAM area %pR reserved by %s\n", &cfgres,
			 dev_name(&adev->dev));
	अन्यथा
		dev_warn(dev, FW_BUG "ECAM area %pR not reserved in ACPI namespace\n",
			 &cfgres);

	cfg = pci_ecam_create(dev, &cfgres, bus_res, ecam_ops);
	अगर (IS_ERR(cfg)) अणु
		dev_err(dev, "%04x:%pR error %ld mapping ECAM\n", seg, bus_res,
			PTR_ERR(cfg));
		वापस शून्य;
	पूर्ण

	वापस cfg;
पूर्ण

/* release_info: मुक्त resources allocated by init_info */
अटल व्योम pci_acpi_generic_release_info(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा acpi_pci_generic_root_info *ri;

	ri = container_of(ci, काष्ठा acpi_pci_generic_root_info, common);
	pci_ecam_मुक्त(ri->cfg);
	kमुक्त(ci->ops);
	kमुक्त(ri);
पूर्ण

/* Interface called from ACPI code to setup PCI host controller */
काष्ठा pci_bus *pci_acpi_scan_root(काष्ठा acpi_pci_root *root)
अणु
	काष्ठा acpi_pci_generic_root_info *ri;
	काष्ठा pci_bus *bus, *child;
	काष्ठा acpi_pci_root_ops *root_ops;
	काष्ठा pci_host_bridge *host;

	ri = kzalloc(माप(*ri), GFP_KERNEL);
	अगर (!ri)
		वापस शून्य;

	root_ops = kzalloc(माप(*root_ops), GFP_KERNEL);
	अगर (!root_ops) अणु
		kमुक्त(ri);
		वापस शून्य;
	पूर्ण

	ri->cfg = pci_acpi_setup_ecam_mapping(root);
	अगर (!ri->cfg) अणु
		kमुक्त(ri);
		kमुक्त(root_ops);
		वापस शून्य;
	पूर्ण

	root_ops->release_info = pci_acpi_generic_release_info;
	root_ops->prepare_resources = pci_acpi_root_prepare_resources;
	root_ops->pci_ops = (काष्ठा pci_ops *)&ri->cfg->ops->pci_ops;
	bus = acpi_pci_root_create(root, root_ops, &ri->common, ri->cfg);
	अगर (!bus)
		वापस शून्य;

	/* If we must preserve the resource configuration, claim now */
	host = pci_find_host_bridge(bus);
	अगर (host->preserve_config)
		pci_bus_claim_resources(bus);

	/*
	 * Assign whatever was left unasचिन्हित. If we didn't claim above,
	 * this will reassign everything.
	 */
	pci_assign_unasचिन्हित_root_bus_resources(bus);

	list_क्रम_each_entry(child, &bus->children, node)
		pcie_bus_configure_settings(child);

	वापस bus;
पूर्ण

व्योम pcibios_add_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_add_bus(bus);
पूर्ण

व्योम pcibios_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_हटाओ_bus(bus);
पूर्ण

#पूर्ण_अगर
