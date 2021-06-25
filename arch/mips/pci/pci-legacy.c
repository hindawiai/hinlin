<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2003, 04, 11 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2011 Wind River Systems,
 *   written by Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cpu-info.h>

/*
 * If PCI_PROBE_ONLY in pci_flags is set, we करोn't change any PCI resource
 * assignments.
 */

/*
 * The PCI controller list.
 */
अटल LIST_HEAD(controllers);

अटल पूर्णांक pci_initialized;

/*
 * We need to aव्योम collisions with `mirrored' VGA ports
 * and other strange ISA hardware, so we always want the
 * addresses to be allocated in the 0x000-0x0ff region
 * modulo 0x400.
 *
 * Why? Because some silly बाह्यal IO cards only decode
 * the low 10 bits of the IO address. The 0x00-0xff region
 * is reserved क्रम motherboard devices that decode all 16
 * bits, so it's ok to allocate at, say, 0x2800-0x28ff,
 * but we want to try to aव्योम allocating at 0x2900-0x2bff
 * which might have be mirrored at 0x0100-0x03ff..
 */
resource_माप_प्रकार
pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
		       resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	काष्ठा pci_controller *hose = dev->sysdata;
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		/* Make sure we start at our min on all hoses */
		अगर (start < PCIBIOS_MIN_IO + hose->io_resource->start)
			start = PCIBIOS_MIN_IO + hose->io_resource->start;

		/*
		 * Put everything पूर्णांकo 0x00-0xff region modulo 0x400
		 */
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_MEM) अणु
		/* Make sure we start at our min on all hoses */
		अगर (start < PCIBIOS_MIN_MEM + hose->mem_resource->start)
			start = PCIBIOS_MIN_MEM + hose->mem_resource->start;
	पूर्ण

	वापस start;
पूर्ण

अटल व्योम pcibios_scanbus(काष्ठा pci_controller *hose)
अणु
	अटल पूर्णांक next_busno;
	अटल पूर्णांक need_करोमुख्य_info;
	LIST_HEAD(resources);
	काष्ठा pci_bus *bus;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस;

	अगर (hose->get_busno && pci_has_flag(PCI_PROBE_ONLY))
		next_busno = (*hose->get_busno)();

	pci_add_resource_offset(&resources,
				hose->mem_resource, hose->mem_offset);
	pci_add_resource_offset(&resources,
				hose->io_resource, hose->io_offset);
	list_splice_init(&resources, &bridge->winकरोws);
	bridge->dev.parent = शून्य;
	bridge->sysdata = hose;
	bridge->busnr = next_busno;
	bridge->ops = hose->pci_ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = pcibios_map_irq;
	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस;
	पूर्ण

	hose->bus = bus = bridge->bus;

	need_करोमुख्य_info = need_करोमुख्य_info || pci_करोमुख्य_nr(bus);
	set_pci_need_करोमुख्य_info(hose, need_करोमुख्य_info);

	next_busno = bus->busn_res.end + 1;
	/* Don't allow 8-bit bus number overflow inside the hose -
	   reserve some space क्रम bridges. */
	अगर (next_busno > 224) अणु
		next_busno = 0;
		need_करोमुख्य_info = 1;
	पूर्ण

	/*
	 * We insert PCI resources पूर्णांकo the iomem_resource and
	 * ioport_resource trees in either pci_bus_claim_resources()
	 * or pci_bus_assign_resources().
	 */
	अगर (pci_has_flag(PCI_PROBE_ONLY)) अणु
		pci_bus_claim_resources(bus);
	पूर्ण अन्यथा अणु
		काष्ठा pci_bus *child;

		pci_bus_size_bridges(bus);
		pci_bus_assign_resources(bus);
		list_क्रम_each_entry(child, &bus->children, node)
			pcie_bus_configure_settings(child);
	पूर्ण
	pci_bus_add_devices(bus);
पूर्ण

#अगर_घोषित CONFIG_OF
व्योम pci_load_of_ranges(काष्ठा pci_controller *hose, काष्ठा device_node *node)
अणु
	काष्ठा of_pci_range range;
	काष्ठा of_pci_range_parser parser;

	hose->of_node = node;

	अगर (of_pci_range_parser_init(&parser, node))
		वापस;

	क्रम_each_of_pci_range(&parser, &range) अणु
		काष्ठा resource *res = शून्य;

		चयन (range.flags & IORESOURCE_TYPE_BITS) अणु
		हाल IORESOURCE_IO:
			hose->io_map_base =
				(अचिन्हित दीर्घ)ioremap(range.cpu_addr,
						       range.size);
			res = hose->io_resource;
			अवरोध;
		हाल IORESOURCE_MEM:
			res = hose->mem_resource;
			अवरोध;
		पूर्ण
		अगर (res != शून्य) अणु
			res->name = node->full_name;
			res->flags = range.flags;
			res->start = range.cpu_addr;
			res->end = range.cpu_addr + range.size - 1;
			res->parent = res->child = res->sibling = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा device_node *pcibios_get_phb_of_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	वापस of_node_get(hose->of_node);
पूर्ण
#पूर्ण_अगर

अटल DEFINE_MUTEX(pci_scan_mutex);

व्योम रेजिस्टर_pci_controller(काष्ठा pci_controller *hose)
अणु
	काष्ठा resource *parent;

	parent = hose->mem_resource->parent;
	अगर (!parent)
		parent = &iomem_resource;

	अगर (request_resource(parent, hose->mem_resource) < 0)
		जाओ out;

	parent = hose->io_resource->parent;
	अगर (!parent)
		parent = &ioport_resource;

	अगर (request_resource(parent, hose->io_resource) < 0) अणु
		release_resource(hose->mem_resource);
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&hose->list);
	list_add_tail(&hose->list, &controllers);

	/*
	 * Do not panic here but later - this might happen beक्रमe console init.
	 */
	अगर (!hose->io_map_base) अणु
		prपूर्णांकk(KERN_WARNING
		       "registering PCI controller with io_map_base unset\n");
	पूर्ण

	/*
	 * Scan the bus अगर it is रेजिस्टर after the PCI subप्रणाली
	 * initialization.
	 */
	अगर (pci_initialized) अणु
		mutex_lock(&pci_scan_mutex);
		pcibios_scanbus(hose);
		mutex_unlock(&pci_scan_mutex);
	पूर्ण

	वापस;

out:
	prपूर्णांकk(KERN_WARNING
	       "Skipping PCI bus scan due to resource conflict\n");
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	काष्ठा pci_controller *hose;

	/* Scan all of the recorded PCI controllers.  */
	list_क्रम_each_entry(hose, &controllers, list)
		pcibios_scanbus(hose);

	pci_initialized = 1;

	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);

अटल पूर्णांक pcibios_enable_resources(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	u16 cmd, old_cmd;
	पूर्णांक idx;
	काष्ठा resource *r;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;
	क्रम (idx = 0; idx < PCI_NUM_RESOURCES; idx++) अणु
		/* Only set up the requested stuff */
		अगर (!(mask & (1<<idx)))
			जारी;

		r = &dev->resource[idx];
		अगर (!(r->flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			जारी;
		अगर ((idx == PCI_ROM_RESOURCE) &&
				(!(r->flags & IORESOURCE_ROM_ENABLE)))
			जारी;
		अगर (!r->start && r->end) अणु
			pci_err(dev,
				"can't enable device: resource collisions\n");
			वापस -EINVAL;
		पूर्ण
		अगर (r->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		अगर (r->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	पूर्ण
	अगर (cmd != old_cmd) अणु
		pci_info(dev, "enabling device (%04x -> %04x)\n", old_cmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	पूर्णांक err = pcibios_enable_resources(dev, mask);

	अगर (err < 0)
		वापस err;

	वापस pcibios_plat_dev_init(dev);
पूर्ण

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev = bus->self;

	अगर (pci_has_flag(PCI_PROBE_ONLY) && dev &&
	    (dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		pci_पढ़ो_bridge_bases(bus);
	पूर्ण
पूर्ण

अक्षर * (*pcibios_plat_setup)(अक्षर *str) __initdata;

अक्षर *__init pcibios_setup(अक्षर *str)
अणु
	अगर (pcibios_plat_setup)
		वापस pcibios_plat_setup(str);
	वापस str;
पूर्ण
