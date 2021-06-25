<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci-acpi.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/pci_x86.h>

काष्ठा pci_root_info अणु
	काष्ठा acpi_pci_root_info common;
	काष्ठा pci_sysdata sd;
#अगर_घोषित	CONFIG_PCI_MMCONFIG
	bool mcfg_added;
	u8 start_bus;
	u8 end_bus;
#पूर्ण_अगर
पूर्ण;

अटल bool pci_use_crs = true;
अटल bool pci_ignore_seg = false;

अटल पूर्णांक __init set_use_crs(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pci_use_crs = true;
	वापस 0;
पूर्ण

अटल पूर्णांक __init set_nouse_crs(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pci_use_crs = false;
	वापस 0;
पूर्ण

अटल पूर्णांक __init set_ignore_seg(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	prपूर्णांकk(KERN_INFO "PCI: %s detected: ignoring ACPI _SEG\n", id->ident);
	pci_ignore_seg = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pci_crs_quirks[] __initस्थिर = अणु
	/* http://bugzilla.kernel.org/show_bug.cgi?id=14183 */
	अणु
		.callback = set_use_crs,
		.ident = "IBM System x3800",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "x3800"),
		पूर्ण,
	पूर्ण,
	/* https://bugzilla.kernel.org/show_bug.cgi?id=16007 */
	/* 2006 AMD HT/VIA प्रणाली with two host bridges */
        अणु
		.callback = set_use_crs,
		.ident = "ASRock ALiveSATA2-GLAN",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "ALiveSATA2-GLAN"),
                पूर्ण,
        पूर्ण,
	/* https://bugzilla.kernel.org/show_bug.cgi?id=30552 */
	/* 2006 AMD HT/VIA प्रणाली with two host bridges */
	अणु
		.callback = set_use_crs,
		.ident = "ASUS M2V-MX SE",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "M2V-MX SE"),
			DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
		पूर्ण,
	पूर्ण,
	/* https://bugzilla.kernel.org/show_bug.cgi?id=42619 */
	अणु
		.callback = set_use_crs,
		.ident = "MSI MS-7253",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_BOARD_NAME, "MS-7253"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies, LTD"),
		पूर्ण,
	पूर्ण,
	/* https://bugs.launchpad.net/ubuntu/+source/alsa-driver/+bug/931368 */
	/* https://bugs.launchpad.net/ubuntu/+source/alsa-driver/+bug/1033299 */
	अणु
		.callback = set_use_crs,
		.ident = "Foxconn K8M890-8237A",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Foxconn"),
			DMI_MATCH(DMI_BOARD_NAME, "K8M890-8237A"),
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies, LTD"),
		पूर्ण,
	पूर्ण,

	/* Now क्रम the blacklist.. */

	/* https://bugzilla.redhat.com/show_bug.cgi?id=769657 */
	अणु
		.callback = set_nouse_crs,
		.ident = "Dell Studio 1557",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Studio 1557"),
			DMI_MATCH(DMI_BIOS_VERSION, "A09"),
		पूर्ण,
	पूर्ण,
	/* https://bugzilla.redhat.com/show_bug.cgi?id=769657 */
	अणु
		.callback = set_nouse_crs,
		.ident = "Thinkpad SL510",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_BOARD_NAME, "2847DFG"),
			DMI_MATCH(DMI_BIOS_VERSION, "6JET85WW (1.43 )"),
		पूर्ण,
	पूर्ण,
	/* https://bugzilla.kernel.org/show_bug.cgi?id=42606 */
	अणु
		.callback = set_nouse_crs,
		.ident = "Supermicro X8DTH",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Supermicro"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X8DTH-i/6/iF/6F"),
			DMI_MATCH(DMI_BIOS_VERSION, "2.0a"),
		पूर्ण,
	पूर्ण,

	/* https://bugzilla.kernel.org/show_bug.cgi?id=15362 */
	अणु
		.callback = set_ignore_seg,
		.ident = "HP xw9300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP xw9300 Workstation"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init pci_acpi_crs_quirks(व्योम)
अणु
	पूर्णांक year = dmi_get_bios_year();

	अगर (year >= 0 && year < 2008 && iomem_resource.end <= 0xffffffff)
		pci_use_crs = false;

	dmi_check_प्रणाली(pci_crs_quirks);

	/*
	 * If the user specअगरies "pci=use_crs" or "pci=nocrs" explicitly, that
	 * takes precedence over anything we figured out above.
	 */
	अगर (pci_probe & PCI_ROOT_NO_CRS)
		pci_use_crs = false;
	अन्यथा अगर (pci_probe & PCI_USE__CRS)
		pci_use_crs = true;

	prपूर्णांकk(KERN_INFO "PCI: %s host bridge windows from ACPI; "
	       "if necessary, use \"pci=%s\" and report a bug\n",
	       pci_use_crs ? "Using" : "Ignoring",
	       pci_use_crs ? "nocrs" : "use_crs");
पूर्ण

#अगर_घोषित	CONFIG_PCI_MMCONFIG
अटल पूर्णांक check_segment(u16 seg, काष्ठा device *dev, अक्षर *estr)
अणु
	अगर (seg) अणु
		dev_err(dev,
			"%s can't access PCI configuration "
			"space under this host bridge.\n",
			estr);
		वापस -EIO;
	पूर्ण

	/*
	 * Failure in adding MMCFG inक्रमmation is not fatal,
	 * just can't access extended configuration space of
	 * devices under this host bridge.
	 */
	dev_warn(dev,
		 "%s can't access extended PCI configuration "
		 "space under this bridge.\n",
		 estr);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_mcfg_map(काष्ठा acpi_pci_root_info *ci)
अणु
	पूर्णांक result, seg;
	काष्ठा pci_root_info *info;
	काष्ठा acpi_pci_root *root = ci->root;
	काष्ठा device *dev = &ci->bridge->dev;

	info = container_of(ci, काष्ठा pci_root_info, common);
	info->start_bus = (u8)root->secondary.start;
	info->end_bus = (u8)root->secondary.end;
	info->mcfg_added = false;
	seg = info->sd.करोमुख्य;

	/* वापस success अगर MMCFG is not in use */
	अगर (raw_pci_ext_ops && raw_pci_ext_ops != &pci_mmcfg)
		वापस 0;

	अगर (!(pci_probe & PCI_PROBE_MMCONF))
		वापस check_segment(seg, dev, "MMCONFIG is disabled,");

	result = pci_mmconfig_insert(dev, seg, info->start_bus, info->end_bus,
				     root->mcfg_addr);
	अगर (result == 0) अणु
		/* enable MMCFG अगर it hasn't been enabled yet */
		अगर (raw_pci_ext_ops == शून्य)
			raw_pci_ext_ops = &pci_mmcfg;
		info->mcfg_added = true;
	पूर्ण अन्यथा अगर (result != -EEXIST)
		वापस check_segment(seg, dev,
			 "fail to add MMCONFIG information,");

	वापस 0;
पूर्ण

अटल व्योम tearकरोwn_mcfg_map(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा pci_root_info *info;

	info = container_of(ci, काष्ठा pci_root_info, common);
	अगर (info->mcfg_added) अणु
		pci_mmconfig_delete(info->sd.करोमुख्य,
				    info->start_bus, info->end_bus);
		info->mcfg_added = false;
	पूर्ण
पूर्ण
#अन्यथा
अटल पूर्णांक setup_mcfg_map(काष्ठा acpi_pci_root_info *ci)
अणु
	वापस 0;
पूर्ण

अटल व्योम tearकरोwn_mcfg_map(काष्ठा acpi_pci_root_info *ci)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pci_acpi_root_get_node(काष्ठा acpi_pci_root *root)
अणु
	पूर्णांक busnum = root->secondary.start;
	काष्ठा acpi_device *device = root->device;
	पूर्णांक node = acpi_get_node(device->handle);

	अगर (node == NUMA_NO_NODE) अणु
		node = x86_pci_root_bus_node(busnum);
		अगर (node != 0 && node != NUMA_NO_NODE)
			dev_info(&device->dev, FW_BUG "no _PXM; falling back to node %d from hardware (may be inconsistent with ACPI node numbers)\n",
				node);
	पूर्ण
	अगर (node != NUMA_NO_NODE && !node_online(node))
		node = NUMA_NO_NODE;

	वापस node;
पूर्ण

अटल पूर्णांक pci_acpi_root_init_info(काष्ठा acpi_pci_root_info *ci)
अणु
	वापस setup_mcfg_map(ci);
पूर्ण

अटल व्योम pci_acpi_root_release_info(काष्ठा acpi_pci_root_info *ci)
अणु
	tearकरोwn_mcfg_map(ci);
	kमुक्त(container_of(ci, काष्ठा pci_root_info, common));
पूर्ण

/*
 * An IO port or MMIO resource asचिन्हित to a PCI host bridge may be
 * consumed by the host bridge itself or available to its child
 * bus/devices. The ACPI specअगरication defines a bit (Producer/Consumer)
 * to tell whether the resource is consumed by the host bridge itself,
 * but firmware hasn't used that bit consistently, so we can't rely on it.
 *
 * On x86 and IA64 platक्रमms, all IO port and MMIO resources are assumed
 * to be available to child bus/devices except one special हाल:
 *     IO port [0xCF8-0xCFF] is consumed by the host bridge itself
 *     to access PCI configuration space.
 *
 * So explicitly filter out PCI CFG IO ports[0xCF8-0xCFF].
 */
अटल bool resource_is_pcicfg_ioport(काष्ठा resource *res)
अणु
	वापस (res->flags & IORESOURCE_IO) &&
		res->start == 0xCF8 && res->end == 0xCFF;
पूर्ण

अटल पूर्णांक pci_acpi_root_prepare_resources(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा acpi_device *device = ci->bridge;
	पूर्णांक busnum = ci->root->secondary.start;
	काष्ठा resource_entry *entry, *पंचांगp;
	पूर्णांक status;

	status = acpi_pci_probe_root_resources(ci);
	अगर (pci_use_crs) अणु
		resource_list_क्रम_each_entry_safe(entry, पंचांगp, &ci->resources)
			अगर (resource_is_pcicfg_ioport(entry->res))
				resource_list_destroy_entry(entry);
		वापस status;
	पूर्ण

	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &ci->resources) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &device->dev,
			   "host bridge window %pR (ignored)\n", entry->res);
		resource_list_destroy_entry(entry);
	पूर्ण
	x86_pci_root_bus_resources(busnum, &ci->resources);

	वापस 0;
पूर्ण

अटल काष्ठा acpi_pci_root_ops acpi_pci_root_ops = अणु
	.pci_ops = &pci_root_ops,
	.init_info = pci_acpi_root_init_info,
	.release_info = pci_acpi_root_release_info,
	.prepare_resources = pci_acpi_root_prepare_resources,
पूर्ण;

काष्ठा pci_bus *pci_acpi_scan_root(काष्ठा acpi_pci_root *root)
अणु
	पूर्णांक करोमुख्य = root->segment;
	पूर्णांक busnum = root->secondary.start;
	पूर्णांक node = pci_acpi_root_get_node(root);
	काष्ठा pci_bus *bus;

	अगर (pci_ignore_seg)
		root->segment = करोमुख्य = 0;

	अगर (करोमुख्य && !pci_करोमुख्यs_supported) अणु
		prपूर्णांकk(KERN_WARNING "pci_bus %04x:%02x: "
		       "ignored (multiple domains not supported)\n",
		       करोमुख्य, busnum);
		वापस शून्य;
	पूर्ण

	bus = pci_find_bus(करोमुख्य, busnum);
	अगर (bus) अणु
		/*
		 * If the desired bus has been scanned alपढ़ोy, replace
		 * its bus->sysdata.
		 */
		काष्ठा pci_sysdata sd = अणु
			.करोमुख्य = करोमुख्य,
			.node = node,
			.companion = root->device
		पूर्ण;

		स_नकल(bus->sysdata, &sd, माप(sd));
	पूर्ण अन्यथा अणु
		काष्ठा pci_root_info *info;

		info = kzalloc(माप(*info), GFP_KERNEL);
		अगर (!info)
			dev_err(&root->device->dev,
				"pci_bus %04x:%02x: ignored (out of memory)\n",
				करोमुख्य, busnum);
		अन्यथा अणु
			info->sd.करोमुख्य = करोमुख्य;
			info->sd.node = node;
			info->sd.companion = root->device;
			bus = acpi_pci_root_create(root, &acpi_pci_root_ops,
						   &info->common, &info->sd);
		पूर्ण
	पूर्ण

	/* After the PCI-E bus has been walked and all devices discovered,
	 * configure any settings of the fabric that might be necessary.
	 */
	अगर (bus) अणु
		काष्ठा pci_bus *child;
		list_क्रम_each_entry(child, &bus->children, node)
			pcie_bus_configure_settings(child);
	पूर्ण

	वापस bus;
पूर्ण

पूर्णांक pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	/*
	 * We pass शून्य as parent to pci_create_root_bus(), so अगर it is not शून्य
	 * here, pci_create_root_bus() has been called by someone अन्यथा and
	 * sysdata is likely to be dअगरferent from what we expect.  Let it go in
	 * that हाल.
	 */
	अगर (!bridge->dev.parent) अणु
		काष्ठा pci_sysdata *sd = bridge->bus->sysdata;
		ACPI_COMPANION_SET(&bridge->dev, sd->companion);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init pci_acpi_init(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;

	अगर (acpi_noirq)
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "PCI: Using ACPI for IRQ routing\n");
	acpi_irq_penalty_init();
	pcibios_enable_irq = acpi_pci_irq_enable;
	pcibios_disable_irq = acpi_pci_irq_disable;
	x86_init.pci.init_irq = x86_init_noop;

	अगर (pci_routeirq) अणु
		/*
		 * PCI IRQ routing is set up by pci_enable_device(), but we
		 * also करो it here in हाल there are still broken drivers that
		 * करोn't use pci_enable_device().
		 */
		prपूर्णांकk(KERN_INFO "PCI: Routing PCI interrupts for all devices because \"pci=routeirq\" specified\n");
		क्रम_each_pci_dev(dev)
			acpi_pci_irq_enable(dev);
	पूर्ण

	वापस 0;
पूर्ण
