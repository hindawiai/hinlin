<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI <-> OF mapping helpers
 *
 * Copyright 2011 IBM Corp.
 */
#घोषणा pr_fmt(fmt)	"PCI: OF: " fmt

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश "pci.h"

#अगर_घोषित CONFIG_PCI
व्योम pci_set_of_node(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->bus->dev.of_node)
		वापस;
	dev->dev.of_node = of_pci_find_child_device(dev->bus->dev.of_node,
						    dev->devfn);
	अगर (dev->dev.of_node)
		dev->dev.fwnode = &dev->dev.of_node->fwnode;
पूर्ण

व्योम pci_release_of_node(काष्ठा pci_dev *dev)
अणु
	of_node_put(dev->dev.of_node);
	dev->dev.of_node = शून्य;
	dev->dev.fwnode = शून्य;
पूर्ण

व्योम pci_set_bus_of_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा device_node *node;

	अगर (bus->self == शून्य) अणु
		node = pcibios_get_phb_of_node(bus);
	पूर्ण अन्यथा अणु
		node = of_node_get(bus->self->dev.of_node);
		अगर (node && of_property_पढ़ो_bool(node, "external-facing"))
			bus->self->बाह्यal_facing = true;
	पूर्ण

	bus->dev.of_node = node;

	अगर (bus->dev.of_node)
		bus->dev.fwnode = &bus->dev.of_node->fwnode;
पूर्ण

व्योम pci_release_bus_of_node(काष्ठा pci_bus *bus)
अणु
	of_node_put(bus->dev.of_node);
	bus->dev.of_node = शून्य;
	bus->dev.fwnode = शून्य;
पूर्ण

काष्ठा device_node * __weak pcibios_get_phb_of_node(काष्ठा pci_bus *bus)
अणु
	/* This should only be called क्रम PHBs */
	अगर (WARN_ON(bus->self || bus->parent))
		वापस शून्य;

	/*
	 * Look क्रम a node poपूर्णांकer in either the पूर्णांकermediary device we
	 * create above the root bus or its own parent. Normally only
	 * the later is populated.
	 */
	अगर (bus->bridge->of_node)
		वापस of_node_get(bus->bridge->of_node);
	अगर (bus->bridge->parent && bus->bridge->parent->of_node)
		वापस of_node_get(bus->bridge->parent->of_node);
	वापस शून्य;
पूर्ण

काष्ठा irq_करोमुख्य *pci_host_bridge_of_msi_करोमुख्य(काष्ठा pci_bus *bus)
अणु
#अगर_घोषित CONFIG_IRQ_DOMAIN
	काष्ठा irq_करोमुख्य *d;

	अगर (!bus->dev.of_node)
		वापस शून्य;

	/* Start looking क्रम a phandle to an MSI controller. */
	d = of_msi_get_करोमुख्य(&bus->dev, bus->dev.of_node, DOMAIN_BUS_PCI_MSI);
	अगर (d)
		वापस d;

	/*
	 * If we करोn't have an msi-parent property, look क्रम a करोमुख्य
	 * directly attached to the host bridge.
	 */
	d = irq_find_matching_host(bus->dev.of_node, DOMAIN_BUS_PCI_MSI);
	अगर (d)
		वापस d;

	वापस irq_find_host(bus->dev.of_node);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

bool pci_host_of_has_msi_map(काष्ठा device *dev)
अणु
	अगर (dev && dev->of_node)
		वापस of_get_property(dev->of_node, "msi-map", शून्य);
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक __of_pci_pci_compare(काष्ठा device_node *node,
				       अचिन्हित पूर्णांक data)
अणु
	पूर्णांक devfn;

	devfn = of_pci_get_devfn(node);
	अगर (devfn < 0)
		वापस 0;

	वापस devfn == data;
पूर्ण

काष्ठा device_node *of_pci_find_child_device(काष्ठा device_node *parent,
					     अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा device_node *node, *node2;

	क्रम_each_child_of_node(parent, node) अणु
		अगर (__of_pci_pci_compare(node, devfn))
			वापस node;
		/*
		 * Some OFs create a parent node "multifunc-device" as
		 * a fake root क्रम all functions of a multi-function
		 * device we go करोwn them as well.
		 */
		अगर (of_node_name_eq(node, "multifunc-device")) अणु
			क्रम_each_child_of_node(node, node2) अणु
				अगर (__of_pci_pci_compare(node2, devfn)) अणु
					of_node_put(node);
					वापस node2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_find_child_device);

/**
 * of_pci_get_devfn() - Get device and function numbers क्रम a device node
 * @np: device node
 *
 * Parses a standard 5-cell PCI resource and वापसs an 8-bit value that can
 * be passed to the PCI_SLOT() and PCI_FUNC() macros to extract the device
 * and function numbers respectively. On error a negative error code is
 * वापसed.
 */
पूर्णांक of_pci_get_devfn(काष्ठा device_node *np)
अणु
	u32 reg[5];
	पूर्णांक error;

	error = of_property_पढ़ो_u32_array(np, "reg", reg, ARRAY_SIZE(reg));
	अगर (error)
		वापस error;

	वापस (reg[0] >> 8) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_get_devfn);

/**
 * of_pci_parse_bus_range() - parse the bus-range property of a PCI device
 * @node: device node
 * @res: address to a काष्ठा resource to वापस the bus-range
 *
 * Returns 0 on success or a negative error-code on failure.
 */
पूर्णांक of_pci_parse_bus_range(काष्ठा device_node *node, काष्ठा resource *res)
अणु
	u32 bus_range[2];
	पूर्णांक error;

	error = of_property_पढ़ो_u32_array(node, "bus-range", bus_range,
					   ARRAY_SIZE(bus_range));
	अगर (error)
		वापस error;

	res->name = node->name;
	res->start = bus_range[0];
	res->end = bus_range[1];
	res->flags = IORESOURCE_BUS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_parse_bus_range);

/**
 * of_get_pci_करोमुख्य_nr - Find the host bridge करोमुख्य number
 *			  of the given device node.
 * @node: Device tree node with the करोमुख्य inक्रमmation.
 *
 * This function will try to obtain the host bridge करोमुख्य number by finding
 * a property called "linux,pci-domain" of the given device node.
 *
 * Return:
 * * > 0	- On success, an associated करोमुख्य number.
 * * -EINVAL	- The property "linux,pci-domain" करोes not exist.
 * * -ENODATA	- The linux,pci-करोमुख्य" property करोes not have value.
 * * -EOVERFLOW	- Invalid "linux,pci-domain" property value.
 *
 * Returns the associated करोमुख्य number from DT in the range [0-0xffff], or
 * a negative value अगर the required property is not found.
 */
पूर्णांक of_get_pci_करोमुख्य_nr(काष्ठा device_node *node)
अणु
	u32 करोमुख्य;
	पूर्णांक error;

	error = of_property_पढ़ो_u32(node, "linux,pci-domain", &करोमुख्य);
	अगर (error)
		वापस error;

	वापस (u16)करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_pci_करोमुख्य_nr);

/**
 * of_pci_check_probe_only - Setup probe only mode अगर linux,pci-probe-only
 *                           is present and valid
 */
व्योम of_pci_check_probe_only(व्योम)
अणु
	u32 val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(of_chosen, "linux,pci-probe-only", &val);
	अगर (ret) अणु
		अगर (ret == -ENODATA || ret == -EOVERFLOW)
			pr_warn("linux,pci-probe-only without valid value, ignoring\n");
		वापस;
	पूर्ण

	अगर (val)
		pci_add_flags(PCI_PROBE_ONLY);
	अन्यथा
		pci_clear_flags(PCI_PROBE_ONLY);

	pr_info("PROBE_ONLY %sabled\n", val ? "en" : "dis");
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_check_probe_only);

/**
 * devm_of_pci_get_host_bridge_resources() - Resource-managed parsing of PCI
 *                                           host bridge resources from DT
 * @dev: host bridge device
 * @busno: bus number associated with the bridge root bus
 * @bus_max: maximum number of buses क्रम this bridge
 * @resources: list where the range of resources will be added after DT parsing
 * @ib_resources: list where the range of inbound resources (with addresses
 *                from 'dma-ranges') will be added after DT parsing
 * @io_base: poपूर्णांकer to a variable that will contain on वापस the physical
 * address क्रम the start of the I/O range. Can be शून्य अगर the caller करोesn't
 * expect I/O ranges to be present in the device tree.
 *
 * This function will parse the "ranges" property of a PCI host bridge device
 * node and setup the resource mapping based on its content. It is expected
 * that the property conक्रमms with the Power ePAPR करोcument.
 *
 * It वापसs zero अगर the range parsing has been successful or a standard error
 * value अगर it failed.
 */
अटल पूर्णांक devm_of_pci_get_host_bridge_resources(काष्ठा device *dev,
			अचिन्हित अक्षर busno, अचिन्हित अक्षर bus_max,
			काष्ठा list_head *resources,
			काष्ठा list_head *ib_resources,
			resource_माप_प्रकार *io_base)
अणु
	काष्ठा device_node *dev_node = dev->of_node;
	काष्ठा resource *res, पंचांगp_res;
	काष्ठा resource *bus_range;
	काष्ठा of_pci_range range;
	काष्ठा of_pci_range_parser parser;
	स्थिर अक्षर *range_type;
	पूर्णांक err;

	अगर (io_base)
		*io_base = (resource_माप_प्रकार)OF_BAD_ADDR;

	bus_range = devm_kzalloc(dev, माप(*bus_range), GFP_KERNEL);
	अगर (!bus_range)
		वापस -ENOMEM;

	dev_info(dev, "host bridge %pOF ranges:\n", dev_node);

	err = of_pci_parse_bus_range(dev_node, bus_range);
	अगर (err) अणु
		bus_range->start = busno;
		bus_range->end = bus_max;
		bus_range->flags = IORESOURCE_BUS;
		dev_info(dev, "  No bus range found for %pOF, using %pR\n",
			 dev_node, bus_range);
	पूर्ण अन्यथा अणु
		अगर (bus_range->end > bus_range->start + bus_max)
			bus_range->end = bus_range->start + bus_max;
	पूर्ण
	pci_add_resource(resources, bus_range);

	/* Check क्रम ranges property */
	err = of_pci_range_parser_init(&parser, dev_node);
	अगर (err)
		जाओ failed;

	dev_dbg(dev, "Parsing ranges property...\n");
	क्रम_each_of_pci_range(&parser, &range) अणु
		/* Read next ranges element */
		अगर ((range.flags & IORESOURCE_TYPE_BITS) == IORESOURCE_IO)
			range_type = "IO";
		अन्यथा अगर ((range.flags & IORESOURCE_TYPE_BITS) == IORESOURCE_MEM)
			range_type = "MEM";
		अन्यथा
			range_type = "err";
		dev_info(dev, "  %6s %#012llx..%#012llx -> %#012llx\n",
			 range_type, range.cpu_addr,
			 range.cpu_addr + range.size - 1, range.pci_addr);

		/*
		 * If we failed translation or got a zero-sized region
		 * then skip this range
		 */
		अगर (range.cpu_addr == OF_BAD_ADDR || range.size == 0)
			जारी;

		err = of_pci_range_to_resource(&range, dev_node, &पंचांगp_res);
		अगर (err)
			जारी;

		res = devm_kmemdup(dev, &पंचांगp_res, माप(पंचांगp_res), GFP_KERNEL);
		अगर (!res) अणु
			err = -ENOMEM;
			जाओ failed;
		पूर्ण

		अगर (resource_type(res) == IORESOURCE_IO) अणु
			अगर (!io_base) अणु
				dev_err(dev, "I/O range found for %pOF. Please provide an io_base pointer to save CPU base address\n",
					dev_node);
				err = -EINVAL;
				जाओ failed;
			पूर्ण
			अगर (*io_base != (resource_माप_प्रकार)OF_BAD_ADDR)
				dev_warn(dev, "More than one I/O resource converted for %pOF. CPU base address for old range lost!\n",
					 dev_node);
			*io_base = range.cpu_addr;
		पूर्ण अन्यथा अगर (resource_type(res) == IORESOURCE_MEM) अणु
			res->flags &= ~IORESOURCE_MEM_64;
		पूर्ण

		pci_add_resource_offset(resources, res,	res->start - range.pci_addr);
	पूर्ण

	/* Check क्रम dma-ranges property */
	अगर (!ib_resources)
		वापस 0;
	err = of_pci_dma_range_parser_init(&parser, dev_node);
	अगर (err)
		वापस 0;

	dev_dbg(dev, "Parsing dma-ranges property...\n");
	क्रम_each_of_pci_range(&parser, &range) अणु
		काष्ठा resource_entry *entry;
		/*
		 * If we failed translation or got a zero-sized region
		 * then skip this range
		 */
		अगर (((range.flags & IORESOURCE_TYPE_BITS) != IORESOURCE_MEM) ||
		    range.cpu_addr == OF_BAD_ADDR || range.size == 0)
			जारी;

		dev_info(dev, "  %6s %#012llx..%#012llx -> %#012llx\n",
			 "IB MEM", range.cpu_addr,
			 range.cpu_addr + range.size - 1, range.pci_addr);


		err = of_pci_range_to_resource(&range, dev_node, &पंचांगp_res);
		अगर (err)
			जारी;

		res = devm_kmemdup(dev, &पंचांगp_res, माप(पंचांगp_res), GFP_KERNEL);
		अगर (!res) अणु
			err = -ENOMEM;
			जाओ failed;
		पूर्ण

		/* Keep the resource list sorted */
		resource_list_क्रम_each_entry(entry, ib_resources)
			अगर (entry->res->start > res->start)
				अवरोध;

		pci_add_resource_offset(&entry->node, res,
					res->start - range.pci_addr);
	पूर्ण

	वापस 0;

failed:
	pci_मुक्त_resource_list(resources);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF_IRQ)
/**
 * of_irq_parse_pci - Resolve the पूर्णांकerrupt क्रम a PCI device
 * @pdev:       the device whose पूर्णांकerrupt is to be resolved
 * @out_irq:    काष्ठाure of_phandle_args filled by this function
 *
 * This function resolves the PCI पूर्णांकerrupt क्रम a given PCI device. If a
 * device-node exists क्रम a given pci_dev, it will use normal OF tree
 * walking. If not, it will implement standard swizzling and walk up the
 * PCI tree until an device-node is found, at which poपूर्णांक it will finish
 * resolving using the OF tree walking.
 */
अटल पूर्णांक of_irq_parse_pci(स्थिर काष्ठा pci_dev *pdev, काष्ठा of_phandle_args *out_irq)
अणु
	काष्ठा device_node *dn, *ppnode;
	काष्ठा pci_dev *ppdev;
	__be32 laddr[3];
	u8 pin;
	पूर्णांक rc;

	/*
	 * Check अगर we have a device node, अगर yes, fallback to standard
	 * device tree parsing
	 */
	dn = pci_device_to_OF_node(pdev);
	अगर (dn) अणु
		rc = of_irq_parse_one(dn, 0, out_irq);
		अगर (!rc)
			वापस rc;
	पूर्ण

	/*
	 * Ok, we करोn't, time to have fun. Let's start by building up an
	 * पूर्णांकerrupt spec.  we assume #पूर्णांकerrupt-cells is 1, which is standard
	 * क्रम PCI. If you करो dअगरferent, then करोn't use that routine.
	 */
	rc = pci_पढ़ो_config_byte(pdev, PCI_INTERRUPT_PIN, &pin);
	अगर (rc != 0)
		जाओ err;
	/* No pin, निकास with no error message. */
	अगर (pin == 0)
		वापस -ENODEV;

	/* Now we walk up the PCI tree */
	क्रम (;;) अणु
		/* Get the pci_dev of our parent */
		ppdev = pdev->bus->self;

		/* Ouch, it's a host bridge... */
		अगर (ppdev == शून्य) अणु
			ppnode = pci_bus_to_OF_node(pdev->bus);

			/* No node क्रम host bridge ? give up */
			अगर (ppnode == शून्य) अणु
				rc = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* We found a P2P bridge, check अगर it has a node */
			ppnode = pci_device_to_OF_node(ppdev);
		पूर्ण

		/*
		 * Ok, we have found a parent with a device-node, hand over to
		 * the OF parsing code.
		 * We build a unit address from the linux device to be used क्रम
		 * resolution. Note that we use the linux bus number which may
		 * not match your firmware bus numbering.
		 * Fortunately, in most हालs, पूर्णांकerrupt-map-mask करोesn't
		 * include the bus number as part of the matching.
		 * You should still be careful about that though अगर you पूर्णांकend
		 * to rely on this function (you ship a firmware that करोesn't
		 * create device nodes क्रम all PCI devices).
		 */
		अगर (ppnode)
			अवरोध;

		/*
		 * We can only get here अगर we hit a P2P bridge with no node;
		 * let's करो standard swizzling and try again
		 */
		pin = pci_swizzle_पूर्णांकerrupt_pin(pdev, pin);
		pdev = ppdev;
	पूर्ण

	out_irq->np = ppnode;
	out_irq->args_count = 1;
	out_irq->args[0] = pin;
	laddr[0] = cpu_to_be32((pdev->bus->number << 16) | (pdev->devfn << 8));
	laddr[1] = laddr[2] = cpu_to_be32(0);
	rc = of_irq_parse_raw(laddr, out_irq);
	अगर (rc)
		जाओ err;
	वापस 0;
err:
	अगर (rc == -ENOENT) अणु
		dev_warn(&pdev->dev,
			"%s: no interrupt-map found, INTx interrupts not available\n",
			__func__);
		pr_warn_once("%s: possibly some PCI slots don't have level triggered interrupts capability\n",
			__func__);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "%s: failed with rc=%d\n", __func__, rc);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * of_irq_parse_and_map_pci() - Decode a PCI IRQ from the device tree and map to a VIRQ
 * @dev: The PCI device needing an IRQ
 * @slot: PCI slot number; passed when used as map_irq callback. Unused
 * @pin: PCI IRQ pin number; passed when used as map_irq callback. Unused
 *
 * @slot and @pin are unused, but included in the function so that this
 * function can be used directly as the map_irq callback to
 * pci_assign_irq() and काष्ठा pci_host_bridge.map_irq poपूर्णांकer
 */
पूर्णांक of_irq_parse_and_map_pci(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा of_phandle_args oirq;
	पूर्णांक ret;

	ret = of_irq_parse_pci(dev, &oirq);
	अगर (ret)
		वापस 0; /* Proper वापस code 0 == NO_IRQ */

	वापस irq_create_of_mapping(&oirq);
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_parse_and_map_pci);
#पूर्ण_अगर	/* CONFIG_OF_IRQ */

अटल पूर्णांक pci_parse_request_of_pci_ranges(काष्ठा device *dev,
					   काष्ठा pci_host_bridge *bridge)
अणु
	पूर्णांक err, res_valid = 0;
	resource_माप_प्रकार iobase;
	काष्ठा resource_entry *win, *पंचांगp;

	INIT_LIST_HEAD(&bridge->winकरोws);
	INIT_LIST_HEAD(&bridge->dma_ranges);

	err = devm_of_pci_get_host_bridge_resources(dev, 0, 0xff, &bridge->winकरोws,
						    &bridge->dma_ranges, &iobase);
	अगर (err)
		वापस err;

	err = devm_request_pci_bus_resources(dev, &bridge->winकरोws);
	अगर (err)
		वापस err;

	resource_list_क्रम_each_entry_safe(win, पंचांगp, &bridge->winकरोws) अणु
		काष्ठा resource *res = win->res;

		चयन (resource_type(res)) अणु
		हाल IORESOURCE_IO:
			err = devm_pci_remap_iospace(dev, res, iobase);
			अगर (err) अणु
				dev_warn(dev, "error %d: failed to map resource %pR\n",
					 err, res);
				resource_list_destroy_entry(win);
			पूर्ण
			अवरोध;
		हाल IORESOURCE_MEM:
			res_valid |= !(res->flags & IORESOURCE_PREFETCH);

			अगर (!(res->flags & IORESOURCE_PREFETCH))
				अगर (upper_32_bits(resource_size(res)))
					dev_warn(dev, "Memory resource size exceeds max for 32 bits\n");

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!res_valid)
		dev_warn(dev, "non-prefetchable memory resource required\n");

	वापस 0;
पूर्ण

पूर्णांक devm_of_pci_bridge_init(काष्ठा device *dev, काष्ठा pci_host_bridge *bridge)
अणु
	अगर (!dev->of_node)
		वापस 0;

	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = of_irq_parse_and_map_pci;

	वापस pci_parse_request_of_pci_ranges(dev, bridge);
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI */

/**
 * of_pci_get_max_link_speed - Find the maximum link speed of the given device node.
 * @node: Device tree node with the maximum link speed inक्रमmation.
 *
 * This function will try to find the limitation of link speed by finding
 * a property called "max-link-speed" of the given device node.
 *
 * Return:
 * * > 0	- On success, a maximum link speed.
 * * -EINVAL	- Invalid "max-link-speed" property value, or failure to access
 *		  the property of the device tree node.
 *
 * Returns the associated max link speed from DT, or a negative value अगर the
 * required property is not found or is invalid.
 */
पूर्णांक of_pci_get_max_link_speed(काष्ठा device_node *node)
अणु
	u32 max_link_speed;

	अगर (of_property_पढ़ो_u32(node, "max-link-speed", &max_link_speed) ||
	    max_link_speed == 0 || max_link_speed > 4)
		वापस -EINVAL;

	वापस max_link_speed;
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_get_max_link_speed);
