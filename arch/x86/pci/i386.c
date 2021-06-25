<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Low-Level PCI Access क्रम i386 machines
 *
 * Copyright 1993, 1994 Drew Eckhardt
 *      Visionary Computing
 *      (Unix and Linux consulting and custom programming)
 *      Drew@Coloraकरो.EDU
 *      +1 (303) 786-7975
 *
 * Drew's work was sponsored by:
 *	iX Multiuser Multitasking Magazine
 *	Hannover, Germany
 *	hm@ix.de
 *
 * Copyright 1997--2000 Martin Mares <mj@ucw.cz>
 *
 * For more inक्रमmation, please consult the following manuals (look at
 * http://www.pcisig.com/ क्रम how to get them):
 *
 * PCI BIOS Specअगरication
 * PCI Local Bus Specअगरication
 * PCI to PCI Bridge Specअगरication
 * PCI System Design Guide
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/io_apic.h>


/*
 * This list of dynamic mappings is क्रम temporarily मुख्यtaining
 * original BIOS BAR addresses क्रम possible reinstatement.
 */
काष्ठा pcibios_fwaddrmap अणु
	काष्ठा list_head list;
	काष्ठा pci_dev *dev;
	resource_माप_प्रकार fw_addr[DEVICE_COUNT_RESOURCE];
पूर्ण;

अटल LIST_HEAD(pcibios_fwaddrmappings);
अटल DEFINE_SPINLOCK(pcibios_fwaddrmap_lock);
अटल bool pcibios_fw_addr_करोne;

/* Must be called with 'pcibios_fwaddrmap_lock' lock held. */
अटल काष्ठा pcibios_fwaddrmap *pcibios_fwaddrmap_lookup(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcibios_fwaddrmap *map;

	lockdep_निश्चित_held(&pcibios_fwaddrmap_lock);

	list_क्रम_each_entry(map, &pcibios_fwaddrmappings, list)
		अगर (map->dev == dev)
			वापस map;

	वापस शून्य;
पूर्ण

अटल व्योम
pcibios_save_fw_addr(काष्ठा pci_dev *dev, पूर्णांक idx, resource_माप_प्रकार fw_addr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pcibios_fwaddrmap *map;

	अगर (pcibios_fw_addr_करोne)
		वापस;

	spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
	map = pcibios_fwaddrmap_lookup(dev);
	अगर (!map) अणु
		spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);
		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (!map)
			वापस;

		map->dev = pci_dev_get(dev);
		map->fw_addr[idx] = fw_addr;
		INIT_LIST_HEAD(&map->list);

		spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
		list_add_tail(&map->list, &pcibios_fwaddrmappings);
	पूर्ण अन्यथा
		map->fw_addr[idx] = fw_addr;
	spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);
पूर्ण

resource_माप_प्रकार pcibios_retrieve_fw_addr(काष्ठा pci_dev *dev, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pcibios_fwaddrmap *map;
	resource_माप_प्रकार fw_addr = 0;

	अगर (pcibios_fw_addr_करोne)
		वापस 0;

	spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
	map = pcibios_fwaddrmap_lookup(dev);
	अगर (map)
		fw_addr = map->fw_addr[idx];
	spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);

	वापस fw_addr;
पूर्ण

अटल व्योम __init pcibios_fw_addr_list_del(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pcibios_fwaddrmap *entry, *next;

	spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
	list_क्रम_each_entry_safe(entry, next, &pcibios_fwaddrmappings, list) अणु
		list_del(&entry->list);
		pci_dev_put(entry->dev);
		kमुक्त(entry);
	पूर्ण
	spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);
	pcibios_fw_addr_करोne = true;
पूर्ण

अटल पूर्णांक
skip_isa_ioresource_align(काष्ठा pci_dev *dev) अणु

	अगर ((pci_probe & PCI_CAN_SKIP_ISA_ALIGN) &&
	    !(dev->bus->bridge_ctl & PCI_BRIDGE_CTL_ISA))
		वापस 1;
	वापस 0;
पूर्ण

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
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		अगर (skip_isa_ioresource_align(dev))
			वापस start;
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_MEM) अणु
		/* The low 1MB range is reserved क्रम ISA cards */
		अगर (start < BIOS_END)
			start = BIOS_END;
	पूर्ण
	वापस start;
पूर्ण
EXPORT_SYMBOL(pcibios_align_resource);

/*
 *  Handle resources of PCI devices.  If the world were perfect, we could
 *  just allocate all the resource regions and करो nothing more.  It isn't.
 *  On the other hand, we cannot just re-allocate all devices, as it would
 *  require us to know lots of host bridge पूर्णांकernals.  So we attempt to
 *  keep as much of the original configuration as possible, but tweak it
 *  when it's found to be wrong.
 *
 *  Known BIOS problems we have to work around:
 *	- I/O or memory regions not configured
 *	- regions configured, but not enabled in the command रेजिस्टर
 *	- bogus I/O addresses above 64K used
 *	- expansion ROMs left enabled (this may sound harmless, but given
 *	  the fact the PCI specs explicitly allow address decoders to be
 *	  shared between expansion ROMs and other resource regions, it's
 *	  at least dangerous)
 *	- bad resource sizes or overlaps with other regions
 *
 *  Our solution:
 *	(1) Allocate resources क्रम all buses behind PCI-to-PCI bridges.
 *	    This gives us fixed barriers on where we can allocate.
 *	(2) Allocate resources क्रम all enabled devices.  If there is
 *	    a collision, just mark the resource as unallocated. Also
 *	    disable expansion ROMs during this step.
 *	(3) Try to allocate resources क्रम disabled devices.  If the
 *	    resources were asचिन्हित correctly, everything goes well,
 *	    अगर they weren't, they won't disturb allocation of other
 *	    resources.
 *	(4) Assign new addresses to resources which were either
 *	    not configured at all or misconfigured.  If explicitly
 *	    requested by the user, configure expansion ROM address
 *	    as well.
 */

अटल व्योम pcibios_allocate_bridge_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक idx;
	काष्ठा resource *r;

	क्रम (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES; idx++) अणु
		r = &dev->resource[idx];
		अगर (!r->flags)
			जारी;
		अगर (r->parent)	/* Alपढ़ोy allocated */
			जारी;
		अगर (!r->start || pci_claim_bridge_resource(dev, idx) < 0) अणु
			/*
			 * Something is wrong with the region.
			 * Invalidate the resource to prevent
			 * child resource allocations in this
			 * range.
			 */
			r->start = r->end = 0;
			r->flags = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcibios_allocate_bus_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *child;

	/* Depth-First Search on bus tree */
	अगर (bus->self)
		pcibios_allocate_bridge_resources(bus->self);
	list_क्रम_each_entry(child, &bus->children, node)
		pcibios_allocate_bus_resources(child);
पूर्ण

काष्ठा pci_check_idx_range अणु
	पूर्णांक start;
	पूर्णांक end;
पूर्ण;

अटल व्योम pcibios_allocate_dev_resources(काष्ठा pci_dev *dev, पूर्णांक pass)
अणु
	पूर्णांक idx, disabled, i;
	u16 command;
	काष्ठा resource *r;

	काष्ठा pci_check_idx_range idx_range[] = अणु
		अणु PCI_STD_RESOURCES, PCI_STD_RESOURCE_END पूर्ण,
#अगर_घोषित CONFIG_PCI_IOV
		अणु PCI_IOV_RESOURCES, PCI_IOV_RESOURCE_END पूर्ण,
#पूर्ण_अगर
	पूर्ण;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
	क्रम (i = 0; i < ARRAY_SIZE(idx_range); i++)
		क्रम (idx = idx_range[i].start; idx <= idx_range[i].end; idx++) अणु
			r = &dev->resource[idx];
			अगर (r->parent)	/* Alपढ़ोy allocated */
				जारी;
			अगर (!r->start)	/* Address not asचिन्हित at all */
				जारी;
			अगर (r->flags & IORESOURCE_IO)
				disabled = !(command & PCI_COMMAND_IO);
			अन्यथा
				disabled = !(command & PCI_COMMAND_MEMORY);
			अगर (pass == disabled) अणु
				dev_dbg(&dev->dev,
					"BAR %d: reserving %pr (d=%d, p=%d)\n",
					idx, r, disabled, pass);
				अगर (pci_claim_resource(dev, idx) < 0) अणु
					अगर (r->flags & IORESOURCE_PCI_FIXED) अणु
						dev_info(&dev->dev, "BAR %d %pR is immovable\n",
							 idx, r);
					पूर्ण अन्यथा अणु
						/* We'll assign a new address later */
						pcibios_save_fw_addr(dev,
								idx, r->start);
						r->end -= r->start;
						r->start = 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	अगर (!pass) अणु
		r = &dev->resource[PCI_ROM_RESOURCE];
		अगर (r->flags & IORESOURCE_ROM_ENABLE) अणु
			/* Turn the ROM off, leave the resource region,
			 * but keep it unरेजिस्टरed. */
			u32 reg;
			dev_dbg(&dev->dev, "disabling ROM %pR\n", r);
			r->flags &= ~IORESOURCE_ROM_ENABLE;
			pci_पढ़ो_config_dword(dev, dev->rom_base_reg, &reg);
			pci_ग_लिखो_config_dword(dev, dev->rom_base_reg,
						reg & ~PCI_ROM_ADDRESS_ENABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcibios_allocate_resources(काष्ठा pci_bus *bus, पूर्णांक pass)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pcibios_allocate_dev_resources(dev, pass);

		child = dev->subordinate;
		अगर (child)
			pcibios_allocate_resources(child, pass);
	पूर्ण
पूर्ण

अटल व्योम pcibios_allocate_dev_rom_resource(काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *r;

	/*
	 * Try to use BIOS settings क्रम ROMs, otherwise let
	 * pci_assign_unasचिन्हित_resources() allocate the new
	 * addresses.
	 */
	r = &dev->resource[PCI_ROM_RESOURCE];
	अगर (!r->flags || !r->start)
		वापस;
	अगर (r->parent) /* Alपढ़ोy allocated */
		वापस;

	अगर (pci_claim_resource(dev, PCI_ROM_RESOURCE) < 0) अणु
		r->end -= r->start;
		r->start = 0;
	पूर्ण
पूर्ण
अटल व्योम pcibios_allocate_rom_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pcibios_allocate_dev_rom_resource(dev);

		child = dev->subordinate;
		अगर (child)
			pcibios_allocate_rom_resources(child);
	पूर्ण
पूर्ण

अटल पूर्णांक __init pcibios_assign_resources(व्योम)
अणु
	काष्ठा pci_bus *bus;

	अगर (!(pci_probe & PCI_ASSIGN_ROMS))
		list_क्रम_each_entry(bus, &pci_root_buses, node)
			pcibios_allocate_rom_resources(bus);

	pci_assign_unasचिन्हित_resources();
	pcibios_fw_addr_list_del();

	वापस 0;
पूर्ण

/*
 * This is an fs_initcall (one below subsys_initcall) in order to reserve
 * resources properly.
 */
fs_initcall(pcibios_assign_resources);

व्योम pcibios_resource_survey_bus(काष्ठा pci_bus *bus)
अणु
	dev_prपूर्णांकk(KERN_DEBUG, &bus->dev, "Allocating resources\n");

	pcibios_allocate_bus_resources(bus);

	pcibios_allocate_resources(bus, 0);
	pcibios_allocate_resources(bus, 1);

	अगर (!(pci_probe & PCI_ASSIGN_ROMS))
		pcibios_allocate_rom_resources(bus);
पूर्ण

व्योम __init pcibios_resource_survey(व्योम)
अणु
	काष्ठा pci_bus *bus;

	DBG("PCI: Allocating resources\n");

	list_क्रम_each_entry(bus, &pci_root_buses, node)
		pcibios_allocate_bus_resources(bus);

	list_क्रम_each_entry(bus, &pci_root_buses, node)
		pcibios_allocate_resources(bus, 0);
	list_क्रम_each_entry(bus, &pci_root_buses, node)
		pcibios_allocate_resources(bus, 1);

	e820__reserve_resources_late();
	/*
	 * Insert the IO APIC resources after PCI initialization has
	 * occurred to handle IO APICS that are mapped in on a BAR in
	 * PCI space, but beक्रमe trying to assign unasचिन्हित pci res.
	 */
	ioapic_insert_resources();
पूर्ण
