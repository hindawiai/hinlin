<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helper routines to scan the device tree क्रम PCI devices and busses
 *
 * Migrated out of PowerPC architecture pci_64.c file by Grant Likely
 * <grant.likely@secretlab.ca> so that these routines are available क्रम
 * 32 bit also.
 *
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *   Rework, based on alpha PCI code.
 * Copyright (c) 2009 Secret Lab Technologies Ltd.
 */

#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>

/**
 * get_पूर्णांक_prop - Decode a u32 from a device tree property
 */
अटल u32 get_पूर्णांक_prop(काष्ठा device_node *np, स्थिर अक्षर *name, u32 def)
अणु
	स्थिर __be32 *prop;
	पूर्णांक len;

	prop = of_get_property(np, name, &len);
	अगर (prop && len >= 4)
		वापस of_पढ़ो_number(prop, 1);
	वापस def;
पूर्ण

/**
 * pci_parse_of_flags - Parse the flags cell of a device tree PCI address
 * @addr0: value of 1st cell of a device tree PCI address.
 * @bridge: Set this flag अगर the address is from a bridge 'ranges' property
 *
 * PCI Bus Binding to IEEE Std 1275-1994
 *
 * Bit#            33222222 22221111 11111100 00000000
 *                 10987654 32109876 54321098 76543210
 * phys.hi cell:   npt000ss bbbbbbbb dddddfff rrrrrrrr
 * phys.mid cell:  hhhhhhhh hhhhhhhh hhhhhhhh hhhhhhhh
 * phys.lo cell:   llllllll llllllll llllllll llllllll
 *
 * where:
 * n        is 0 अगर the address is relocatable, 1 otherwise
 * p        is 1 अगर the addressable region is "prefetchable", 0 otherwise
 * t        is 1 अगर the address is aliased (क्रम non-relocatable I/O),
 *          below 1 MB (क्रम Memory),or below 64 KB (क्रम relocatable I/O).
 * ss       is the space code, denoting the address space:
 *              00 denotes Configuration Space
 *              01 denotes I/O Space
 *              10 denotes 32-bit-address Memory Space
 *              11 denotes 64-bit-address Memory Space
 * bbbbbbbb is the 8-bit Bus Number
 * ddddd    is the 5-bit Device Number
 * fff      is the 3-bit Function Number
 * rrrrrrrr is the 8-bit Register Number
 */
#घोषणा OF_PCI_ADDR0_SPACE(ss)		(((ss)&3)<<24)
#घोषणा OF_PCI_ADDR0_SPACE_CFG		OF_PCI_ADDR0_SPACE(0)
#घोषणा OF_PCI_ADDR0_SPACE_IO		OF_PCI_ADDR0_SPACE(1)
#घोषणा OF_PCI_ADDR0_SPACE_MMIO32	OF_PCI_ADDR0_SPACE(2)
#घोषणा OF_PCI_ADDR0_SPACE_MMIO64	OF_PCI_ADDR0_SPACE(3)
#घोषणा OF_PCI_ADDR0_SPACE_MASK		OF_PCI_ADDR0_SPACE(3)
#घोषणा OF_PCI_ADDR0_RELOC		(1UL<<31)
#घोषणा OF_PCI_ADDR0_PREFETCH		(1UL<<30)
#घोषणा OF_PCI_ADDR0_ALIAS		(1UL<<29)
#घोषणा OF_PCI_ADDR0_BUS		0x00FF0000UL
#घोषणा OF_PCI_ADDR0_DEV		0x0000F800UL
#घोषणा OF_PCI_ADDR0_FN			0x00000700UL
#घोषणा OF_PCI_ADDR0_BARREG		0x000000FFUL

अचिन्हित पूर्णांक pci_parse_of_flags(u32 addr0, पूर्णांक bridge)
अणु
	अचिन्हित पूर्णांक flags = 0, as = addr0 & OF_PCI_ADDR0_SPACE_MASK;

	अगर (as == OF_PCI_ADDR0_SPACE_MMIO32 || as == OF_PCI_ADDR0_SPACE_MMIO64) अणु
		flags = IORESOURCE_MEM | PCI_BASE_ADDRESS_SPACE_MEMORY;

		अगर (as == OF_PCI_ADDR0_SPACE_MMIO64)
			flags |= PCI_BASE_ADDRESS_MEM_TYPE_64 | IORESOURCE_MEM_64;

		अगर (addr0 & OF_PCI_ADDR0_ALIAS)
			flags |= PCI_BASE_ADDRESS_MEM_TYPE_1M;

		अगर (addr0 & OF_PCI_ADDR0_PREFETCH)
			flags |= IORESOURCE_PREFETCH |
				 PCI_BASE_ADDRESS_MEM_PREFETCH;

		/* Note: We करोn't know whether the ROM has been left enabled
		 * by the firmware or not. We mark it as disabled (ie, we करो
		 * not set the IORESOURCE_ROM_ENABLE flag) क्रम now rather than
		 * करो a config space पढ़ो, it will be क्रमce-enabled अगर needed
		 */
		अगर (!bridge && (addr0 & OF_PCI_ADDR0_BARREG) == PCI_ROM_ADDRESS)
			flags |= IORESOURCE_READONLY;

	पूर्ण अन्यथा अगर (as == OF_PCI_ADDR0_SPACE_IO)
		flags = IORESOURCE_IO | PCI_BASE_ADDRESS_SPACE_IO;

	अगर (flags)
		flags |= IORESOURCE_SIZEALIGN;

	वापस flags;
पूर्ण

/**
 * of_pci_parse_addrs - Parse PCI addresses asचिन्हित in the device tree node
 * @node: device tree node क्रम the PCI device
 * @dev: pci_dev काष्ठाure क्रम the device
 *
 * This function parses the 'assigned-addresses' property of a PCI devices'
 * device tree node and ग_लिखोs them पूर्णांकo the associated pci_dev काष्ठाure.
 */
अटल व्योम of_pci_parse_addrs(काष्ठा device_node *node, काष्ठा pci_dev *dev)
अणु
	u64 base, size;
	अचिन्हित पूर्णांक flags;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;
	स्थिर __be32 *addrs;
	u32 i;
	पूर्णांक proplen;
	bool mark_unset = false;

	addrs = of_get_property(node, "assigned-addresses", &proplen);
	अगर (!addrs || !proplen) अणु
		addrs = of_get_property(node, "reg", &proplen);
		अगर (!addrs || !proplen)
			वापस;
		mark_unset = true;
	पूर्ण

	pr_debug("    parse addresses (%d bytes) @ %p\n", proplen, addrs);
	क्रम (; proplen >= 20; proplen -= 20, addrs += 5) अणु
		flags = pci_parse_of_flags(of_पढ़ो_number(addrs, 1), 0);
		अगर (!flags)
			जारी;
		base = of_पढ़ो_number(&addrs[1], 2);
		size = of_पढ़ो_number(&addrs[3], 2);
		अगर (!size)
			जारी;
		i = of_पढ़ो_number(addrs, 1) & 0xff;
		pr_debug("  base: %llx, size: %llx, i: %x\n",
			 (अचिन्हित दीर्घ दीर्घ)base,
			 (अचिन्हित दीर्घ दीर्घ)size, i);

		अगर (PCI_BASE_ADDRESS_0 <= i && i <= PCI_BASE_ADDRESS_5) अणु
			res = &dev->resource[(i - PCI_BASE_ADDRESS_0) >> 2];
		पूर्ण अन्यथा अगर (i == dev->rom_base_reg) अणु
			res = &dev->resource[PCI_ROM_RESOURCE];
			flags |= IORESOURCE_READONLY;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "PCI: bad cfg reg num 0x%x\n", i);
			जारी;
		पूर्ण
		res->flags = flags;
		अगर (mark_unset)
			res->flags |= IORESOURCE_UNSET;
		res->name = pci_name(dev);
		region.start = base;
		region.end = base + size - 1;
		pcibios_bus_to_resource(dev->bus, res, &region);
	पूर्ण
पूर्ण

/**
 * of_create_pci_dev - Given a device tree node on a pci bus, create a pci_dev
 * @node: device tree node poपूर्णांकer
 * @bus: bus the device is sitting on
 * @devfn: PCI function number, extracted from device tree by caller.
 */
काष्ठा pci_dev *of_create_pci_dev(काष्ठा device_node *node,
				 काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	काष्ठा pci_dev *dev;

	dev = pci_alloc_dev(bus);
	अगर (!dev)
		वापस शून्य;

	pr_debug("    create device, devfn: %x, type: %s\n", devfn,
		 of_node_get_device_type(node));

	dev->dev.of_node = of_node_get(node);
	dev->dev.parent = bus->bridge;
	dev->dev.bus = &pci_bus_type;
	dev->devfn = devfn;
	dev->multअगरunction = 0;		/* maybe a lie? */
	dev->needs_freset = 0;		/* pcie fundamental reset required */
	set_pcie_port_type(dev);

	pci_dev_assign_slot(dev);
	dev->venकरोr = get_पूर्णांक_prop(node, "vendor-id", 0xffff);
	dev->device = get_पूर्णांक_prop(node, "device-id", 0xffff);
	dev->subप्रणाली_venकरोr = get_पूर्णांक_prop(node, "subsystem-vendor-id", 0);
	dev->subप्रणाली_device = get_पूर्णांक_prop(node, "subsystem-id", 0);

	dev->cfg_size = pci_cfg_space_size(dev);

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_करोमुख्य_nr(bus),
		dev->bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn));
	dev->class = get_पूर्णांक_prop(node, "class-code", 0);
	dev->revision = get_पूर्णांक_prop(node, "revision-id", 0);

	pr_debug("    class: 0x%x\n", dev->class);
	pr_debug("    revision: 0x%x\n", dev->revision);

	dev->current_state = PCI_UNKNOWN;	/* unknown घातer state */
	dev->error_state = pci_channel_io_normal;
	dev->dma_mask = 0xffffffff;

	/* Early fixups, beक्रमe probing the BARs */
	pci_fixup_device(pci_fixup_early, dev);

	अगर (of_node_is_type(node, "pci") || of_node_is_type(node, "pciex")) अणु
		/* a PCI-PCI bridge */
		dev->hdr_type = PCI_HEADER_TYPE_BRIDGE;
		dev->rom_base_reg = PCI_ROM_ADDRESS1;
		set_pcie_hotplug_bridge(dev);
	पूर्ण अन्यथा अगर (of_node_is_type(node, "cardbus")) अणु
		dev->hdr_type = PCI_HEADER_TYPE_CARDBUS;
	पूर्ण अन्यथा अणु
		dev->hdr_type = PCI_HEADER_TYPE_NORMAL;
		dev->rom_base_reg = PCI_ROM_ADDRESS;
		/* Maybe करो a शेष OF mapping here */
		dev->irq = 0;
	पूर्ण

	of_pci_parse_addrs(node, dev);

	pr_debug("    adding to system ...\n");

	pci_device_add(dev, bus);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(of_create_pci_dev);

/**
 * of_scan_pci_bridge - Set up a PCI bridge and scan क्रम child nodes
 * @dev: pci_dev काष्ठाure क्रम the bridge
 *
 * of_scan_bus() calls this routine क्रम each PCI bridge that it finds, and
 * this routine in turn call of_scan_bus() recusively to scan क्रम more child
 * devices.
 */
व्योम of_scan_pci_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *node = dev->dev.of_node;
	काष्ठा pci_bus *bus;
	काष्ठा pci_controller *phb;
	स्थिर __be32 *busrange, *ranges;
	पूर्णांक len, i, mode;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक flags;
	u64 size;

	pr_debug("of_scan_pci_bridge(%pOF)\n", node);

	/* parse bus-range property */
	busrange = of_get_property(node, "bus-range", &len);
	अगर (busrange == शून्य || len != 8) अणु
		prपूर्णांकk(KERN_DEBUG "Can't get bus-range for PCI-PCI bridge %pOF\n",
		       node);
		वापस;
	पूर्ण
	ranges = of_get_property(node, "ranges", &len);
	अगर (ranges == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "Can't get ranges for PCI-PCI bridge %pOF\n",
		       node);
		वापस;
	पूर्ण

	bus = pci_find_bus(pci_करोमुख्य_nr(dev->bus),
			   of_पढ़ो_number(busrange, 1));
	अगर (!bus) अणु
		bus = pci_add_new_bus(dev->bus, dev,
				      of_पढ़ो_number(busrange, 1));
		अगर (!bus) अणु
			prपूर्णांकk(KERN_ERR "Failed to create pci bus for %pOF\n",
			       node);
			वापस;
		पूर्ण
	पूर्ण

	bus->primary = dev->bus->number;
	pci_bus_insert_busn_res(bus, of_पढ़ो_number(busrange, 1),
				of_पढ़ो_number(busrange+1, 1));
	bus->bridge_ctl = 0;

	/* parse ranges property */
	/* PCI #address-cells == 3 and #size-cells == 2 always */
	res = &dev->resource[PCI_BRIDGE_RESOURCES];
	क्रम (i = 0; i < PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES; ++i) अणु
		res->flags = 0;
		bus->resource[i] = res;
		++res;
	पूर्ण
	i = 1;
	क्रम (; len >= 32; len -= 32, ranges += 8) अणु
		flags = pci_parse_of_flags(of_पढ़ो_number(ranges, 1), 1);
		size = of_पढ़ो_number(&ranges[6], 2);
		अगर (flags == 0 || size == 0)
			जारी;
		अगर (flags & IORESOURCE_IO) अणु
			res = bus->resource[0];
			अगर (res->flags) अणु
				prपूर्णांकk(KERN_ERR "PCI: ignoring extra I/O range"
				       " for bridge %pOF\n", node);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i >= PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES) अणु
				prपूर्णांकk(KERN_ERR "PCI: too many memory ranges"
				       " for bridge %pOF\n", node);
				जारी;
			पूर्ण
			res = bus->resource[i];
			++i;
		पूर्ण
		res->flags = flags;
		region.start = of_पढ़ो_number(&ranges[1], 2);
		region.end = region.start + size - 1;
		pcibios_bus_to_resource(dev->bus, res, &region);
	पूर्ण
	प्र_लिखो(bus->name, "PCI Bus %04x:%02x", pci_करोमुख्य_nr(bus),
		bus->number);
	pr_debug("    bus name: %s\n", bus->name);

	phb = pci_bus_to_host(bus);

	mode = PCI_PROBE_NORMAL;
	अगर (phb->controller_ops.probe_mode)
		mode = phb->controller_ops.probe_mode(bus);
	pr_debug("    probe mode: %d\n", mode);

	अगर (mode == PCI_PROBE_DEVTREE)
		of_scan_bus(node, bus);
	अन्यथा अगर (mode == PCI_PROBE_NORMAL)
		pci_scan_child_bus(bus);
पूर्ण
EXPORT_SYMBOL(of_scan_pci_bridge);

अटल काष्ठा pci_dev *of_scan_pci_dev(काष्ठा pci_bus *bus,
			    काष्ठा device_node *dn)
अणु
	काष्ठा pci_dev *dev = शून्य;
	स्थिर __be32 *reg;
	पूर्णांक reglen, devfn;
#अगर_घोषित CONFIG_EEH
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(PCI_DN(dn));
#पूर्ण_अगर

	pr_debug("  * %pOF\n", dn);
	अगर (!of_device_is_available(dn))
		वापस शून्य;

	reg = of_get_property(dn, "reg", &reglen);
	अगर (reg == शून्य || reglen < 20)
		वापस शून्य;
	devfn = (of_पढ़ो_number(reg, 1) >> 8) & 0xff;

	/* Check अगर the PCI device is alपढ़ोy there */
	dev = pci_get_slot(bus, devfn);
	अगर (dev) अणु
		pci_dev_put(dev);
		वापस dev;
	पूर्ण

	/* Device हटाओd permanently ? */
#अगर_घोषित CONFIG_EEH
	अगर (edev && (edev->mode & EEH_DEV_REMOVED))
		वापस शून्य;
#पूर्ण_अगर

	/* create a new pci_dev क्रम this device */
	dev = of_create_pci_dev(dn, bus, devfn);
	अगर (!dev)
		वापस शून्य;

	pr_debug("  dev header type: %x\n", dev->hdr_type);
	वापस dev;
पूर्ण

/**
 * __of_scan_bus - given a PCI bus node, setup bus and scan क्रम child devices
 * @node: device tree node क्रम the PCI bus
 * @bus: pci_bus काष्ठाure क्रम the PCI bus
 * @rescan_existing: Flag indicating bus has alपढ़ोy been set up
 */
अटल व्योम __of_scan_bus(काष्ठा device_node *node, काष्ठा pci_bus *bus,
			  पूर्णांक rescan_existing)
अणु
	काष्ठा device_node *child;
	काष्ठा pci_dev *dev;

	pr_debug("of_scan_bus(%pOF) bus no %d...\n",
		 node, bus->number);

	/* Scan direct children */
	क्रम_each_child_of_node(node, child) अणु
		dev = of_scan_pci_dev(bus, child);
		अगर (!dev)
			जारी;
		pr_debug("    dev header type: %x\n", dev->hdr_type);
	पूर्ण

	/* Apply all fixups necessary. We करोn't fixup the bus "self"
	 * क्रम an existing bridge that is being rescanned
	 */
	अगर (!rescan_existing)
		pcibios_setup_bus_self(bus);

	/* Now scan child busses */
	क्रम_each_pci_bridge(dev, bus)
		of_scan_pci_bridge(dev);
पूर्ण

/**
 * of_scan_bus - given a PCI bus node, setup bus and scan क्रम child devices
 * @node: device tree node क्रम the PCI bus
 * @bus: pci_bus काष्ठाure क्रम the PCI bus
 */
व्योम of_scan_bus(काष्ठा device_node *node, काष्ठा pci_bus *bus)
अणु
	__of_scan_bus(node, bus, 0);
पूर्ण
EXPORT_SYMBOL_GPL(of_scan_bus);

/**
 * of_rescan_bus - given a PCI bus node, scan क्रम child devices
 * @node: device tree node क्रम the PCI bus
 * @bus: pci_bus काष्ठाure क्रम the PCI bus
 *
 * Same as of_scan_bus, but क्रम a pci_bus काष्ठाure that has alपढ़ोy been
 * setup.
 */
व्योम of_rescan_bus(काष्ठा device_node *node, काष्ठा pci_bus *bus)
अणु
	__of_scan_bus(node, bus, 1);
पूर्ण
EXPORT_SYMBOL_GPL(of_rescan_bus);

