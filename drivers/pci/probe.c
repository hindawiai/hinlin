<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI detection and setup code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/aer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/hypervisor.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "pci.h"

#घोषणा CARDBUS_LATENCY_TIMER	176	/* secondary latency समयr */
#घोषणा CARDBUS_RESERVE_BUSNR	3

अटल काष्ठा resource busn_resource = अणु
	.name	= "PCI busn",
	.start	= 0,
	.end	= 255,
	.flags	= IORESOURCE_BUS,
पूर्ण;

/* Ugh.  Need to stop exporting this to modules. */
LIST_HEAD(pci_root_buses);
EXPORT_SYMBOL(pci_root_buses);

अटल LIST_HEAD(pci_करोमुख्य_busn_res_list);

काष्ठा pci_करोमुख्य_busn_res अणु
	काष्ठा list_head list;
	काष्ठा resource res;
	पूर्णांक करोमुख्य_nr;
पूर्ण;

अटल काष्ठा resource *get_pci_करोमुख्य_busn_res(पूर्णांक करोमुख्य_nr)
अणु
	काष्ठा pci_करोमुख्य_busn_res *r;

	list_क्रम_each_entry(r, &pci_करोमुख्य_busn_res_list, list)
		अगर (r->करोमुख्य_nr == करोमुख्य_nr)
			वापस &r->res;

	r = kzalloc(माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस शून्य;

	r->करोमुख्य_nr = करोमुख्य_nr;
	r->res.start = 0;
	r->res.end = 0xff;
	r->res.flags = IORESOURCE_BUS | IORESOURCE_PCI_FIXED;

	list_add_tail(&r->list, &pci_करोमुख्य_busn_res_list);

	वापस &r->res;
पूर्ण

/*
 * Some device drivers need know अगर PCI is initiated.
 * Basically, we think PCI is not initiated when there
 * is no device to be found on the pci_bus_type.
 */
पूर्णांक no_pci_devices(व्योम)
अणु
	काष्ठा device *dev;
	पूर्णांक no_devices;

	dev = bus_find_next_device(&pci_bus_type, शून्य);
	no_devices = (dev == शून्य);
	put_device(dev);
	वापस no_devices;
पूर्ण
EXPORT_SYMBOL(no_pci_devices);

/*
 * PCI Bus Class
 */
अटल व्योम release_pcibus_dev(काष्ठा device *dev)
अणु
	काष्ठा pci_bus *pci_bus = to_pci_bus(dev);

	put_device(pci_bus->bridge);
	pci_bus_हटाओ_resources(pci_bus);
	pci_release_bus_of_node(pci_bus);
	kमुक्त(pci_bus);
पूर्ण

अटल काष्ठा class pcibus_class = अणु
	.name		= "pci_bus",
	.dev_release	= &release_pcibus_dev,
	.dev_groups	= pcibus_groups,
पूर्ण;

अटल पूर्णांक __init pcibus_class_init(व्योम)
अणु
	वापस class_रेजिस्टर(&pcibus_class);
पूर्ण
postcore_initcall(pcibus_class_init);

अटल u64 pci_size(u64 base, u64 maxbase, u64 mask)
अणु
	u64 size = mask & maxbase;	/* Find the signअगरicant bits */
	अगर (!size)
		वापस 0;

	/*
	 * Get the lowest of them to find the decode size, and from that
	 * the extent.
	 */
	size = size & ~(size-1);

	/*
	 * base == maxbase can be valid only अगर the BAR has alपढ़ोy been
	 * programmed with all 1s.
	 */
	अगर (base == maxbase && ((base | (size - 1)) & mask) != mask)
		वापस 0;

	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ decode_bar(काष्ठा pci_dev *dev, u32 bar)
अणु
	u32 mem_type;
	अचिन्हित दीर्घ flags;

	अगर ((bar & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) अणु
		flags = bar & ~PCI_BASE_ADDRESS_IO_MASK;
		flags |= IORESOURCE_IO;
		वापस flags;
	पूर्ण

	flags = bar & ~PCI_BASE_ADDRESS_MEM_MASK;
	flags |= IORESOURCE_MEM;
	अगर (flags & PCI_BASE_ADDRESS_MEM_PREFETCH)
		flags |= IORESOURCE_PREFETCH;

	mem_type = bar & PCI_BASE_ADDRESS_MEM_TYPE_MASK;
	चयन (mem_type) अणु
	हाल PCI_BASE_ADDRESS_MEM_TYPE_32:
		अवरोध;
	हाल PCI_BASE_ADDRESS_MEM_TYPE_1M:
		/* 1M mem BAR treated as 32-bit BAR */
		अवरोध;
	हाल PCI_BASE_ADDRESS_MEM_TYPE_64:
		flags |= IORESOURCE_MEM_64;
		अवरोध;
	शेष:
		/* mem unknown type treated as 32-bit BAR */
		अवरोध;
	पूर्ण
	वापस flags;
पूर्ण

#घोषणा PCI_COMMAND_DECODE_ENABLE	(PCI_COMMAND_MEMORY | PCI_COMMAND_IO)

/**
 * __pci_पढ़ो_base - Read a PCI BAR
 * @dev: the PCI device
 * @type: type of the BAR
 * @res: resource buffer to be filled in
 * @pos: BAR position in the config space
 *
 * Returns 1 अगर the BAR is 64-bit, or 0 अगर 32-bit.
 */
पूर्णांक __pci_पढ़ो_base(काष्ठा pci_dev *dev, क्रमागत pci_bar_type type,
		    काष्ठा resource *res, अचिन्हित पूर्णांक pos)
अणु
	u32 l = 0, sz = 0, mask;
	u64 l64, sz64, mask64;
	u16 orig_cmd;
	काष्ठा pci_bus_region region, inverted_region;

	mask = type ? PCI_ROM_ADDRESS_MASK : ~0;

	/* No prपूर्णांकks जबतक decoding is disabled! */
	अगर (!dev->mmio_always_on) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &orig_cmd);
		अगर (orig_cmd & PCI_COMMAND_DECODE_ENABLE) अणु
			pci_ग_लिखो_config_word(dev, PCI_COMMAND,
				orig_cmd & ~PCI_COMMAND_DECODE_ENABLE);
		पूर्ण
	पूर्ण

	res->name = pci_name(dev);

	pci_पढ़ो_config_dword(dev, pos, &l);
	pci_ग_लिखो_config_dword(dev, pos, l | mask);
	pci_पढ़ो_config_dword(dev, pos, &sz);
	pci_ग_लिखो_config_dword(dev, pos, l);

	/*
	 * All bits set in sz means the device isn't working properly.
	 * If the BAR isn't implemented, all bits must be 0.  If it's a
	 * memory BAR or a ROM, bit 0 must be clear; अगर it's an io BAR, bit
	 * 1 must be clear.
	 */
	अगर (sz == 0xffffffff)
		sz = 0;

	/*
	 * I करोn't know how l can have all bits set.  Copied from old code.
	 * Maybe it fixes a bug on some ancient platक्रमm.
	 */
	अगर (l == 0xffffffff)
		l = 0;

	अगर (type == pci_bar_unknown) अणु
		res->flags = decode_bar(dev, l);
		res->flags |= IORESOURCE_SIZEALIGN;
		अगर (res->flags & IORESOURCE_IO) अणु
			l64 = l & PCI_BASE_ADDRESS_IO_MASK;
			sz64 = sz & PCI_BASE_ADDRESS_IO_MASK;
			mask64 = PCI_BASE_ADDRESS_IO_MASK & (u32)IO_SPACE_LIMIT;
		पूर्ण अन्यथा अणु
			l64 = l & PCI_BASE_ADDRESS_MEM_MASK;
			sz64 = sz & PCI_BASE_ADDRESS_MEM_MASK;
			mask64 = (u32)PCI_BASE_ADDRESS_MEM_MASK;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (l & PCI_ROM_ADDRESS_ENABLE)
			res->flags |= IORESOURCE_ROM_ENABLE;
		l64 = l & PCI_ROM_ADDRESS_MASK;
		sz64 = sz & PCI_ROM_ADDRESS_MASK;
		mask64 = PCI_ROM_ADDRESS_MASK;
	पूर्ण

	अगर (res->flags & IORESOURCE_MEM_64) अणु
		pci_पढ़ो_config_dword(dev, pos + 4, &l);
		pci_ग_लिखो_config_dword(dev, pos + 4, ~0);
		pci_पढ़ो_config_dword(dev, pos + 4, &sz);
		pci_ग_लिखो_config_dword(dev, pos + 4, l);

		l64 |= ((u64)l << 32);
		sz64 |= ((u64)sz << 32);
		mask64 |= ((u64)~0 << 32);
	पूर्ण

	अगर (!dev->mmio_always_on && (orig_cmd & PCI_COMMAND_DECODE_ENABLE))
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, orig_cmd);

	अगर (!sz64)
		जाओ fail;

	sz64 = pci_size(l64, sz64, mask64);
	अगर (!sz64) अणु
		pci_info(dev, FW_BUG "reg 0x%x: invalid BAR (can't size)\n",
			 pos);
		जाओ fail;
	पूर्ण

	अगर (res->flags & IORESOURCE_MEM_64) अणु
		अगर ((माप(pci_bus_addr_t) < 8 || माप(resource_माप_प्रकार) < 8)
		    && sz64 > 0x100000000ULL) अणु
			res->flags |= IORESOURCE_UNSET | IORESOURCE_DISABLED;
			res->start = 0;
			res->end = 0;
			pci_err(dev, "reg 0x%x: can't handle BAR larger than 4GB (size %#010llx)\n",
				pos, (अचिन्हित दीर्घ दीर्घ)sz64);
			जाओ out;
		पूर्ण

		अगर ((माप(pci_bus_addr_t) < 8) && l) अणु
			/* Above 32-bit boundary; try to पुनः_स्मृतिate */
			res->flags |= IORESOURCE_UNSET;
			res->start = 0;
			res->end = sz64 - 1;
			pci_info(dev, "reg 0x%x: can't handle BAR above 4GB (bus address %#010llx)\n",
				 pos, (अचिन्हित दीर्घ दीर्घ)l64);
			जाओ out;
		पूर्ण
	पूर्ण

	region.start = l64;
	region.end = l64 + sz64 - 1;

	pcibios_bus_to_resource(dev->bus, res, &region);
	pcibios_resource_to_bus(dev->bus, &inverted_region, res);

	/*
	 * If "A" is a BAR value (a bus address), "bus_to_resource(A)" is
	 * the corresponding resource address (the physical address used by
	 * the CPU.  Converting that resource address back to a bus address
	 * should yield the original BAR value:
	 *
	 *     resource_to_bus(bus_to_resource(A)) == A
	 *
	 * If it करोesn't, CPU accesses to "bus_to_resource(A)" will not
	 * be claimed by the device.
	 */
	अगर (inverted_region.start != region.start) अणु
		res->flags |= IORESOURCE_UNSET;
		res->start = 0;
		res->end = region.end - region.start;
		pci_info(dev, "reg 0x%x: initial BAR value %#010llx invalid\n",
			 pos, (अचिन्हित दीर्घ दीर्घ)region.start);
	पूर्ण

	जाओ out;


fail:
	res->flags = 0;
out:
	अगर (res->flags)
		pci_info(dev, "reg 0x%x: %pR\n", pos, res);

	वापस (res->flags & IORESOURCE_MEM_64) ? 1 : 0;
पूर्ण

अटल व्योम pci_पढ़ो_bases(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक howmany, पूर्णांक rom)
अणु
	अचिन्हित पूर्णांक pos, reg;

	अगर (dev->non_compliant_bars)
		वापस;

	/* Per PCIe r4.0, sec 9.3.4.1.11, the VF BARs are all RO Zero */
	अगर (dev->is_virtfn)
		वापस;

	क्रम (pos = 0; pos < howmany; pos++) अणु
		काष्ठा resource *res = &dev->resource[pos];
		reg = PCI_BASE_ADDRESS_0 + (pos << 2);
		pos += __pci_पढ़ो_base(dev, pci_bar_unknown, res, reg);
	पूर्ण

	अगर (rom) अणु
		काष्ठा resource *res = &dev->resource[PCI_ROM_RESOURCE];
		dev->rom_base_reg = rom;
		res->flags = IORESOURCE_MEM | IORESOURCE_PREFETCH |
				IORESOURCE_READONLY | IORESOURCE_SIZEALIGN;
		__pci_पढ़ो_base(dev, pci_bar_mem32, res, rom);
	पूर्ण
पूर्ण

अटल व्योम pci_पढ़ो_bridge_winकरोws(काष्ठा pci_dev *bridge)
अणु
	u16 io;
	u32 pmem, पंचांगp;

	pci_पढ़ो_config_word(bridge, PCI_IO_BASE, &io);
	अगर (!io) अणु
		pci_ग_लिखो_config_word(bridge, PCI_IO_BASE, 0xe0f0);
		pci_पढ़ो_config_word(bridge, PCI_IO_BASE, &io);
		pci_ग_लिखो_config_word(bridge, PCI_IO_BASE, 0x0);
	पूर्ण
	अगर (io)
		bridge->io_winकरोw = 1;

	/*
	 * DECchip 21050 pass 2 errata: the bridge may miss an address
	 * disconnect boundary by one PCI data phase.  Workaround: करो not
	 * use prefetching on this device.
	 */
	अगर (bridge->venकरोr == PCI_VENDOR_ID_DEC && bridge->device == 0x0001)
		वापस;

	pci_पढ़ो_config_dword(bridge, PCI_PREF_MEMORY_BASE, &pmem);
	अगर (!pmem) अणु
		pci_ग_लिखो_config_dword(bridge, PCI_PREF_MEMORY_BASE,
					       0xffe0fff0);
		pci_पढ़ो_config_dword(bridge, PCI_PREF_MEMORY_BASE, &pmem);
		pci_ग_लिखो_config_dword(bridge, PCI_PREF_MEMORY_BASE, 0x0);
	पूर्ण
	अगर (!pmem)
		वापस;

	bridge->pref_winकरोw = 1;

	अगर ((pmem & PCI_PREF_RANGE_TYPE_MASK) == PCI_PREF_RANGE_TYPE_64) अणु

		/*
		 * Bridge claims to have a 64-bit prefetchable memory
		 * winकरोw; verअगरy that the upper bits are actually
		 * writable.
		 */
		pci_पढ़ो_config_dword(bridge, PCI_PREF_BASE_UPPER32, &pmem);
		pci_ग_लिखो_config_dword(bridge, PCI_PREF_BASE_UPPER32,
				       0xffffffff);
		pci_पढ़ो_config_dword(bridge, PCI_PREF_BASE_UPPER32, &पंचांगp);
		pci_ग_लिखो_config_dword(bridge, PCI_PREF_BASE_UPPER32, pmem);
		अगर (पंचांगp)
			bridge->pref_64_winकरोw = 1;
	पूर्ण
पूर्ण

अटल व्योम pci_पढ़ो_bridge_io(काष्ठा pci_bus *child)
अणु
	काष्ठा pci_dev *dev = child->self;
	u8 io_base_lo, io_limit_lo;
	अचिन्हित दीर्घ io_mask, io_granularity, base, limit;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;

	io_mask = PCI_IO_RANGE_MASK;
	io_granularity = 0x1000;
	अगर (dev->io_winकरोw_1k) अणु
		/* Support 1K I/O space granularity */
		io_mask = PCI_IO_1K_RANGE_MASK;
		io_granularity = 0x400;
	पूर्ण

	res = child->resource[0];
	pci_पढ़ो_config_byte(dev, PCI_IO_BASE, &io_base_lo);
	pci_पढ़ो_config_byte(dev, PCI_IO_LIMIT, &io_limit_lo);
	base = (io_base_lo & io_mask) << 8;
	limit = (io_limit_lo & io_mask) << 8;

	अगर ((io_base_lo & PCI_IO_RANGE_TYPE_MASK) == PCI_IO_RANGE_TYPE_32) अणु
		u16 io_base_hi, io_limit_hi;

		pci_पढ़ो_config_word(dev, PCI_IO_BASE_UPPER16, &io_base_hi);
		pci_पढ़ो_config_word(dev, PCI_IO_LIMIT_UPPER16, &io_limit_hi);
		base |= ((अचिन्हित दीर्घ) io_base_hi << 16);
		limit |= ((अचिन्हित दीर्घ) io_limit_hi << 16);
	पूर्ण

	अगर (base <= limit) अणु
		res->flags = (io_base_lo & PCI_IO_RANGE_TYPE_MASK) | IORESOURCE_IO;
		region.start = base;
		region.end = limit + io_granularity - 1;
		pcibios_bus_to_resource(dev->bus, res, &region);
		pci_info(dev, "  bridge window %pR\n", res);
	पूर्ण
पूर्ण

अटल व्योम pci_पढ़ो_bridge_mmio(काष्ठा pci_bus *child)
अणु
	काष्ठा pci_dev *dev = child->self;
	u16 mem_base_lo, mem_limit_lo;
	अचिन्हित दीर्घ base, limit;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;

	res = child->resource[1];
	pci_पढ़ो_config_word(dev, PCI_MEMORY_BASE, &mem_base_lo);
	pci_पढ़ो_config_word(dev, PCI_MEMORY_LIMIT, &mem_limit_lo);
	base = ((अचिन्हित दीर्घ) mem_base_lo & PCI_MEMORY_RANGE_MASK) << 16;
	limit = ((अचिन्हित दीर्घ) mem_limit_lo & PCI_MEMORY_RANGE_MASK) << 16;
	अगर (base <= limit) अणु
		res->flags = (mem_base_lo & PCI_MEMORY_RANGE_TYPE_MASK) | IORESOURCE_MEM;
		region.start = base;
		region.end = limit + 0xfffff;
		pcibios_bus_to_resource(dev->bus, res, &region);
		pci_info(dev, "  bridge window %pR\n", res);
	पूर्ण
पूर्ण

अटल व्योम pci_पढ़ो_bridge_mmio_pref(काष्ठा pci_bus *child)
अणु
	काष्ठा pci_dev *dev = child->self;
	u16 mem_base_lo, mem_limit_lo;
	u64 base64, limit64;
	pci_bus_addr_t base, limit;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;

	res = child->resource[2];
	pci_पढ़ो_config_word(dev, PCI_PREF_MEMORY_BASE, &mem_base_lo);
	pci_पढ़ो_config_word(dev, PCI_PREF_MEMORY_LIMIT, &mem_limit_lo);
	base64 = (mem_base_lo & PCI_PREF_RANGE_MASK) << 16;
	limit64 = (mem_limit_lo & PCI_PREF_RANGE_MASK) << 16;

	अगर ((mem_base_lo & PCI_PREF_RANGE_TYPE_MASK) == PCI_PREF_RANGE_TYPE_64) अणु
		u32 mem_base_hi, mem_limit_hi;

		pci_पढ़ो_config_dword(dev, PCI_PREF_BASE_UPPER32, &mem_base_hi);
		pci_पढ़ो_config_dword(dev, PCI_PREF_LIMIT_UPPER32, &mem_limit_hi);

		/*
		 * Some bridges set the base > limit by शेष, and some
		 * (broken) BIOSes करो not initialize them.  If we find
		 * this, just assume they are not being used.
		 */
		अगर (mem_base_hi <= mem_limit_hi) अणु
			base64 |= (u64) mem_base_hi << 32;
			limit64 |= (u64) mem_limit_hi << 32;
		पूर्ण
	पूर्ण

	base = (pci_bus_addr_t) base64;
	limit = (pci_bus_addr_t) limit64;

	अगर (base != base64) अणु
		pci_err(dev, "can't handle bridge window above 4GB (bus address %#010llx)\n",
			(अचिन्हित दीर्घ दीर्घ) base64);
		वापस;
	पूर्ण

	अगर (base <= limit) अणु
		res->flags = (mem_base_lo & PCI_PREF_RANGE_TYPE_MASK) |
					 IORESOURCE_MEM | IORESOURCE_PREFETCH;
		अगर (res->flags & PCI_PREF_RANGE_TYPE_64)
			res->flags |= IORESOURCE_MEM_64;
		region.start = base;
		region.end = limit + 0xfffff;
		pcibios_bus_to_resource(dev->bus, res, &region);
		pci_info(dev, "  bridge window %pR\n", res);
	पूर्ण
पूर्ण

व्योम pci_पढ़ो_bridge_bases(काष्ठा pci_bus *child)
अणु
	काष्ठा pci_dev *dev = child->self;
	काष्ठा resource *res;
	पूर्णांक i;

	अगर (pci_is_root_bus(child))	/* It's a host bus, nothing to पढ़ो */
		वापस;

	pci_info(dev, "PCI bridge to %pR%s\n",
		 &child->busn_res,
		 dev->transparent ? " (subtractive decode)" : "");

	pci_bus_हटाओ_resources(child);
	क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++)
		child->resource[i] = &dev->resource[PCI_BRIDGE_RESOURCES+i];

	pci_पढ़ो_bridge_io(child);
	pci_पढ़ो_bridge_mmio(child);
	pci_पढ़ो_bridge_mmio_pref(child);

	अगर (dev->transparent) अणु
		pci_bus_क्रम_each_resource(child->parent, res, i) अणु
			अगर (res && res->flags) अणु
				pci_bus_add_resource(child, res,
						     PCI_SUBTRACTIVE_DECODE);
				pci_info(dev, "  bridge window %pR (subtractive decode)\n",
					   res);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा pci_bus *pci_alloc_bus(काष्ठा pci_bus *parent)
अणु
	काष्ठा pci_bus *b;

	b = kzalloc(माप(*b), GFP_KERNEL);
	अगर (!b)
		वापस शून्य;

	INIT_LIST_HEAD(&b->node);
	INIT_LIST_HEAD(&b->children);
	INIT_LIST_HEAD(&b->devices);
	INIT_LIST_HEAD(&b->slots);
	INIT_LIST_HEAD(&b->resources);
	b->max_bus_speed = PCI_SPEED_UNKNOWN;
	b->cur_bus_speed = PCI_SPEED_UNKNOWN;
#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
	अगर (parent)
		b->करोमुख्य_nr = parent->करोमुख्य_nr;
#पूर्ण_अगर
	वापस b;
पूर्ण

अटल व्योम pci_release_host_bridge_dev(काष्ठा device *dev)
अणु
	काष्ठा pci_host_bridge *bridge = to_pci_host_bridge(dev);

	अगर (bridge->release_fn)
		bridge->release_fn(bridge);

	pci_मुक्त_resource_list(&bridge->winकरोws);
	pci_मुक्त_resource_list(&bridge->dma_ranges);
	kमुक्त(bridge);
पूर्ण

अटल व्योम pci_init_host_bridge(काष्ठा pci_host_bridge *bridge)
अणु
	INIT_LIST_HEAD(&bridge->winकरोws);
	INIT_LIST_HEAD(&bridge->dma_ranges);

	/*
	 * We assume we can manage these PCIe features.  Some प्रणालीs may
	 * reserve these क्रम use by the platक्रमm itself, e.g., an ACPI BIOS
	 * may implement its own AER handling and use _OSC to prevent the
	 * OS from पूर्णांकerfering.
	 */
	bridge->native_aer = 1;
	bridge->native_pcie_hotplug = 1;
	bridge->native_shpc_hotplug = 1;
	bridge->native_pme = 1;
	bridge->native_ltr = 1;
	bridge->native_dpc = 1;

	device_initialize(&bridge->dev);
पूर्ण

काष्ठा pci_host_bridge *pci_alloc_host_bridge(माप_प्रकार priv)
अणु
	काष्ठा pci_host_bridge *bridge;

	bridge = kzalloc(माप(*bridge) + priv, GFP_KERNEL);
	अगर (!bridge)
		वापस शून्य;

	pci_init_host_bridge(bridge);
	bridge->dev.release = pci_release_host_bridge_dev;

	वापस bridge;
पूर्ण
EXPORT_SYMBOL(pci_alloc_host_bridge);

अटल व्योम devm_pci_alloc_host_bridge_release(व्योम *data)
अणु
	pci_मुक्त_host_bridge(data);
पूर्ण

काष्ठा pci_host_bridge *devm_pci_alloc_host_bridge(काष्ठा device *dev,
						   माप_प्रकार priv)
अणु
	पूर्णांक ret;
	काष्ठा pci_host_bridge *bridge;

	bridge = pci_alloc_host_bridge(priv);
	अगर (!bridge)
		वापस शून्य;

	bridge->dev.parent = dev;

	ret = devm_add_action_or_reset(dev, devm_pci_alloc_host_bridge_release,
				       bridge);
	अगर (ret)
		वापस शून्य;

	ret = devm_of_pci_bridge_init(dev, bridge);
	अगर (ret)
		वापस शून्य;

	वापस bridge;
पूर्ण
EXPORT_SYMBOL(devm_pci_alloc_host_bridge);

व्योम pci_मुक्त_host_bridge(काष्ठा pci_host_bridge *bridge)
अणु
	put_device(&bridge->dev);
पूर्ण
EXPORT_SYMBOL(pci_मुक्त_host_bridge);

/* Indexed by PCI_X_SSTATUS_FREQ (secondary bus mode and frequency) */
अटल स्थिर अचिन्हित अक्षर pcix_bus_speed[] = अणु
	PCI_SPEED_UNKNOWN,		/* 0 */
	PCI_SPEED_66MHz_PCIX,		/* 1 */
	PCI_SPEED_100MHz_PCIX,		/* 2 */
	PCI_SPEED_133MHz_PCIX,		/* 3 */
	PCI_SPEED_UNKNOWN,		/* 4 */
	PCI_SPEED_66MHz_PCIX_ECC,	/* 5 */
	PCI_SPEED_100MHz_PCIX_ECC,	/* 6 */
	PCI_SPEED_133MHz_PCIX_ECC,	/* 7 */
	PCI_SPEED_UNKNOWN,		/* 8 */
	PCI_SPEED_66MHz_PCIX_266,	/* 9 */
	PCI_SPEED_100MHz_PCIX_266,	/* A */
	PCI_SPEED_133MHz_PCIX_266,	/* B */
	PCI_SPEED_UNKNOWN,		/* C */
	PCI_SPEED_66MHz_PCIX_533,	/* D */
	PCI_SPEED_100MHz_PCIX_533,	/* E */
	PCI_SPEED_133MHz_PCIX_533	/* F */
पूर्ण;

/* Indexed by PCI_EXP_LNKCAP_SLS, PCI_EXP_LNKSTA_CLS */
स्थिर अचिन्हित अक्षर pcie_link_speed[] = अणु
	PCI_SPEED_UNKNOWN,		/* 0 */
	PCIE_SPEED_2_5GT,		/* 1 */
	PCIE_SPEED_5_0GT,		/* 2 */
	PCIE_SPEED_8_0GT,		/* 3 */
	PCIE_SPEED_16_0GT,		/* 4 */
	PCIE_SPEED_32_0GT,		/* 5 */
	PCIE_SPEED_64_0GT,		/* 6 */
	PCI_SPEED_UNKNOWN,		/* 7 */
	PCI_SPEED_UNKNOWN,		/* 8 */
	PCI_SPEED_UNKNOWN,		/* 9 */
	PCI_SPEED_UNKNOWN,		/* A */
	PCI_SPEED_UNKNOWN,		/* B */
	PCI_SPEED_UNKNOWN,		/* C */
	PCI_SPEED_UNKNOWN,		/* D */
	PCI_SPEED_UNKNOWN,		/* E */
	PCI_SPEED_UNKNOWN		/* F */
पूर्ण;
EXPORT_SYMBOL_GPL(pcie_link_speed);

स्थिर अक्षर *pci_speed_string(क्रमागत pci_bus_speed speed)
अणु
	/* Indexed by the pci_bus_speed क्रमागत */
	अटल स्थिर अक्षर *speed_strings[] = अणु
	    "33 MHz PCI",		/* 0x00 */
	    "66 MHz PCI",		/* 0x01 */
	    "66 MHz PCI-X",		/* 0x02 */
	    "100 MHz PCI-X",		/* 0x03 */
	    "133 MHz PCI-X",		/* 0x04 */
	    शून्य,			/* 0x05 */
	    शून्य,			/* 0x06 */
	    शून्य,			/* 0x07 */
	    शून्य,			/* 0x08 */
	    "66 MHz PCI-X 266",		/* 0x09 */
	    "100 MHz PCI-X 266",	/* 0x0a */
	    "133 MHz PCI-X 266",	/* 0x0b */
	    "Unknown AGP",		/* 0x0c */
	    "1x AGP",			/* 0x0d */
	    "2x AGP",			/* 0x0e */
	    "4x AGP",			/* 0x0f */
	    "8x AGP",			/* 0x10 */
	    "66 MHz PCI-X 533",		/* 0x11 */
	    "100 MHz PCI-X 533",	/* 0x12 */
	    "133 MHz PCI-X 533",	/* 0x13 */
	    "2.5 GT/s PCIe",		/* 0x14 */
	    "5.0 GT/s PCIe",		/* 0x15 */
	    "8.0 GT/s PCIe",		/* 0x16 */
	    "16.0 GT/s PCIe",		/* 0x17 */
	    "32.0 GT/s PCIe",		/* 0x18 */
	    "64.0 GT/s PCIe",		/* 0x19 */
	पूर्ण;

	अगर (speed < ARRAY_SIZE(speed_strings))
		वापस speed_strings[speed];
	वापस "Unknown";
पूर्ण
EXPORT_SYMBOL_GPL(pci_speed_string);

व्योम pcie_update_link_speed(काष्ठा pci_bus *bus, u16 linksta)
अणु
	bus->cur_bus_speed = pcie_link_speed[linksta & PCI_EXP_LNKSTA_CLS];
पूर्ण
EXPORT_SYMBOL_GPL(pcie_update_link_speed);

अटल अचिन्हित अक्षर agp_speeds[] = अणु
	AGP_UNKNOWN,
	AGP_1X,
	AGP_2X,
	AGP_4X,
	AGP_8X
पूर्ण;

अटल क्रमागत pci_bus_speed agp_speed(पूर्णांक agp3, पूर्णांक agpstat)
अणु
	पूर्णांक index = 0;

	अगर (agpstat & 4)
		index = 3;
	अन्यथा अगर (agpstat & 2)
		index = 2;
	अन्यथा अगर (agpstat & 1)
		index = 1;
	अन्यथा
		जाओ out;

	अगर (agp3) अणु
		index += 2;
		अगर (index == 5)
			index = 0;
	पूर्ण

 out:
	वापस agp_speeds[index];
पूर्ण

अटल व्योम pci_set_bus_speed(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *bridge = bus->self;
	पूर्णांक pos;

	pos = pci_find_capability(bridge, PCI_CAP_ID_AGP);
	अगर (!pos)
		pos = pci_find_capability(bridge, PCI_CAP_ID_AGP3);
	अगर (pos) अणु
		u32 agpstat, agpcmd;

		pci_पढ़ो_config_dword(bridge, pos + PCI_AGP_STATUS, &agpstat);
		bus->max_bus_speed = agp_speed(agpstat & 8, agpstat & 7);

		pci_पढ़ो_config_dword(bridge, pos + PCI_AGP_COMMAND, &agpcmd);
		bus->cur_bus_speed = agp_speed(agpstat & 8, agpcmd & 7);
	पूर्ण

	pos = pci_find_capability(bridge, PCI_CAP_ID_PCIX);
	अगर (pos) अणु
		u16 status;
		क्रमागत pci_bus_speed max;

		pci_पढ़ो_config_word(bridge, pos + PCI_X_BRIDGE_SSTATUS,
				     &status);

		अगर (status & PCI_X_SSTATUS_533MHZ) अणु
			max = PCI_SPEED_133MHz_PCIX_533;
		पूर्ण अन्यथा अगर (status & PCI_X_SSTATUS_266MHZ) अणु
			max = PCI_SPEED_133MHz_PCIX_266;
		पूर्ण अन्यथा अगर (status & PCI_X_SSTATUS_133MHZ) अणु
			अगर ((status & PCI_X_SSTATUS_VERS) == PCI_X_SSTATUS_V2)
				max = PCI_SPEED_133MHz_PCIX_ECC;
			अन्यथा
				max = PCI_SPEED_133MHz_PCIX;
		पूर्ण अन्यथा अणु
			max = PCI_SPEED_66MHz_PCIX;
		पूर्ण

		bus->max_bus_speed = max;
		bus->cur_bus_speed = pcix_bus_speed[
			(status & PCI_X_SSTATUS_FREQ) >> 6];

		वापस;
	पूर्ण

	अगर (pci_is_pcie(bridge)) अणु
		u32 linkcap;
		u16 linksta;

		pcie_capability_पढ़ो_dword(bridge, PCI_EXP_LNKCAP, &linkcap);
		bus->max_bus_speed = pcie_link_speed[linkcap & PCI_EXP_LNKCAP_SLS];
		bridge->link_active_reporting = !!(linkcap & PCI_EXP_LNKCAP_DLLLARC);

		pcie_capability_पढ़ो_word(bridge, PCI_EXP_LNKSTA, &linksta);
		pcie_update_link_speed(bus, linksta);
	पूर्ण
पूर्ण

अटल काष्ठा irq_करोमुख्य *pci_host_bridge_msi_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा irq_करोमुख्य *d;

	/*
	 * Any firmware पूर्णांकerface that can resolve the msi_करोमुख्य
	 * should be called from here.
	 */
	d = pci_host_bridge_of_msi_करोमुख्य(bus);
	अगर (!d)
		d = pci_host_bridge_acpi_msi_करोमुख्य(bus);

#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
	/*
	 * If no IRQ करोमुख्य was found via the OF tree, try looking it up
	 * directly through the fwnode_handle.
	 */
	अगर (!d) अणु
		काष्ठा fwnode_handle *fwnode = pci_root_bus_fwnode(bus);

		अगर (fwnode)
			d = irq_find_matching_fwnode(fwnode,
						     DOMAIN_BUS_PCI_MSI);
	पूर्ण
#पूर्ण_अगर

	वापस d;
पूर्ण

अटल व्योम pci_set_bus_msi_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा irq_करोमुख्य *d;
	काष्ठा pci_bus *b;

	/*
	 * The bus can be a root bus, a subordinate bus, or a भव bus
	 * created by an SR-IOV device.  Walk up to the first bridge device
	 * found or derive the करोमुख्य from the host bridge.
	 */
	क्रम (b = bus, d = शून्य; !d && !pci_is_root_bus(b); b = b->parent) अणु
		अगर (b->self)
			d = dev_get_msi_करोमुख्य(&b->self->dev);
	पूर्ण

	अगर (!d)
		d = pci_host_bridge_msi_करोमुख्य(b);

	dev_set_msi_करोमुख्य(&bus->dev, d);
पूर्ण

अटल पूर्णांक pci_रेजिस्टर_host_bridge(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा device *parent = bridge->dev.parent;
	काष्ठा resource_entry *winकरोw, *n;
	काष्ठा pci_bus *bus, *b;
	resource_माप_प्रकार offset;
	LIST_HEAD(resources);
	काष्ठा resource *res;
	अक्षर addr[64], *fmt;
	स्थिर अक्षर *name;
	पूर्णांक err;

	bus = pci_alloc_bus(शून्य);
	अगर (!bus)
		वापस -ENOMEM;

	bridge->bus = bus;

	/* Temporarily move resources off the list */
	list_splice_init(&bridge->winकरोws, &resources);
	bus->sysdata = bridge->sysdata;
	bus->ops = bridge->ops;
	bus->number = bus->busn_res.start = bridge->busnr;
#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
	bus->करोमुख्य_nr = pci_bus_find_करोमुख्य_nr(bus, parent);
#पूर्ण_अगर

	b = pci_find_bus(pci_करोमुख्य_nr(bus), bridge->busnr);
	अगर (b) अणु
		/* Ignore it अगर we alपढ़ोy got here via a dअगरferent bridge */
		dev_dbg(&b->dev, "bus already known\n");
		err = -EEXIST;
		जाओ मुक्त;
	पूर्ण

	dev_set_name(&bridge->dev, "pci%04x:%02x", pci_करोमुख्य_nr(bus),
		     bridge->busnr);

	err = pcibios_root_bridge_prepare(bridge);
	अगर (err)
		जाओ मुक्त;

	err = device_add(&bridge->dev);
	अगर (err) अणु
		put_device(&bridge->dev);
		जाओ मुक्त;
	पूर्ण
	bus->bridge = get_device(&bridge->dev);
	device_enable_async_suspend(bus->bridge);
	pci_set_bus_of_node(bus);
	pci_set_bus_msi_करोमुख्य(bus);
	अगर (bridge->msi_करोमुख्य && !dev_get_msi_करोमुख्य(&bus->dev) &&
	    !pci_host_of_has_msi_map(parent))
		bus->bus_flags |= PCI_BUS_FLAGS_NO_MSI;

	अगर (!parent)
		set_dev_node(bus->bridge, pcibus_to_node(bus));

	bus->dev.class = &pcibus_class;
	bus->dev.parent = bus->bridge;

	dev_set_name(&bus->dev, "%04x:%02x", pci_करोमुख्य_nr(bus), bus->number);
	name = dev_name(&bus->dev);

	err = device_रेजिस्टर(&bus->dev);
	अगर (err)
		जाओ unरेजिस्टर;

	pcibios_add_bus(bus);

	अगर (bus->ops->add_bus) अणु
		err = bus->ops->add_bus(bus);
		अगर (WARN_ON(err < 0))
			dev_err(&bus->dev, "failed to add bus: %d\n", err);
	पूर्ण

	/* Create legacy_io and legacy_mem files क्रम this bus */
	pci_create_legacy_files(bus);

	अगर (parent)
		dev_info(parent, "PCI host bridge to bus %s\n", name);
	अन्यथा
		pr_info("PCI host bridge to bus %s\n", name);

	अगर (nr_node_ids > 1 && pcibus_to_node(bus) == NUMA_NO_NODE)
		dev_warn(&bus->dev, "Unknown NUMA node; performance will be reduced\n");

	/* Add initial resources to the bus */
	resource_list_क्रम_each_entry_safe(winकरोw, n, &resources) अणु
		list_move_tail(&winकरोw->node, &bridge->winकरोws);
		offset = winकरोw->offset;
		res = winकरोw->res;

		अगर (res->flags & IORESOURCE_BUS)
			pci_bus_insert_busn_res(bus, bus->number, res->end);
		अन्यथा
			pci_bus_add_resource(bus, res, 0);

		अगर (offset) अणु
			अगर (resource_type(res) == IORESOURCE_IO)
				fmt = " (bus address [%#06llx-%#06llx])";
			अन्यथा
				fmt = " (bus address [%#010llx-%#010llx])";

			snम_लिखो(addr, माप(addr), fmt,
				 (अचिन्हित दीर्घ दीर्घ)(res->start - offset),
				 (अचिन्हित दीर्घ दीर्घ)(res->end - offset));
		पूर्ण अन्यथा
			addr[0] = '\0';

		dev_info(&bus->dev, "root bus resource %pR%s\n", res, addr);
	पूर्ण

	करोwn_ग_लिखो(&pci_bus_sem);
	list_add_tail(&bus->node, &pci_root_buses);
	up_ग_लिखो(&pci_bus_sem);

	वापस 0;

unरेजिस्टर:
	put_device(&bridge->dev);
	device_del(&bridge->dev);

मुक्त:
	kमुक्त(bus);
	वापस err;
पूर्ण

अटल bool pci_bridge_child_ext_cfg_accessible(काष्ठा pci_dev *bridge)
अणु
	पूर्णांक pos;
	u32 status;

	/*
	 * If extended config space isn't accessible on a bridge's primary
	 * bus, we certainly can't access it on the secondary bus.
	 */
	अगर (bridge->bus->bus_flags & PCI_BUS_FLAGS_NO_EXTCFG)
		वापस false;

	/*
	 * PCIe Root Ports and चयन ports are PCIe on both sides, so अगर
	 * extended config space is accessible on the primary, it's also
	 * accessible on the secondary.
	 */
	अगर (pci_is_pcie(bridge) &&
	    (pci_pcie_type(bridge) == PCI_EXP_TYPE_ROOT_PORT ||
	     pci_pcie_type(bridge) == PCI_EXP_TYPE_UPSTREAM ||
	     pci_pcie_type(bridge) == PCI_EXP_TYPE_DOWNSTREAM))
		वापस true;

	/*
	 * For the other bridge types:
	 *   - PCI-to-PCI bridges
	 *   - PCIe-to-PCI/PCI-X क्रमward bridges
	 *   - PCI/PCI-X-to-PCIe reverse bridges
	 * extended config space on the secondary side is only accessible
	 * अगर the bridge supports PCI-X Mode 2.
	 */
	pos = pci_find_capability(bridge, PCI_CAP_ID_PCIX);
	अगर (!pos)
		वापस false;

	pci_पढ़ो_config_dword(bridge, pos + PCI_X_STATUS, &status);
	वापस status & (PCI_X_STATUS_266MHZ | PCI_X_STATUS_533MHZ);
पूर्ण

अटल काष्ठा pci_bus *pci_alloc_child_bus(काष्ठा pci_bus *parent,
					   काष्ठा pci_dev *bridge, पूर्णांक busnr)
अणु
	काष्ठा pci_bus *child;
	काष्ठा pci_host_bridge *host;
	पूर्णांक i;
	पूर्णांक ret;

	/* Allocate a new bus and inherit stuff from the parent */
	child = pci_alloc_bus(parent);
	अगर (!child)
		वापस शून्य;

	child->parent = parent;
	child->sysdata = parent->sysdata;
	child->bus_flags = parent->bus_flags;

	host = pci_find_host_bridge(parent);
	अगर (host->child_ops)
		child->ops = host->child_ops;
	अन्यथा
		child->ops = parent->ops;

	/*
	 * Initialize some portions of the bus device, but करोn't रेजिस्टर
	 * it now as the parent is not properly set up yet.
	 */
	child->dev.class = &pcibus_class;
	dev_set_name(&child->dev, "%04x:%02x", pci_करोमुख्य_nr(child), busnr);

	/* Set up the primary, secondary and subordinate bus numbers */
	child->number = child->busn_res.start = busnr;
	child->primary = parent->busn_res.start;
	child->busn_res.end = 0xff;

	अगर (!bridge) अणु
		child->dev.parent = parent->bridge;
		जाओ add_dev;
	पूर्ण

	child->self = bridge;
	child->bridge = get_device(&bridge->dev);
	child->dev.parent = child->bridge;
	pci_set_bus_of_node(child);
	pci_set_bus_speed(child);

	/*
	 * Check whether extended config space is accessible on the child
	 * bus.  Note that we currently assume it is always accessible on
	 * the root bus.
	 */
	अगर (!pci_bridge_child_ext_cfg_accessible(bridge)) अणु
		child->bus_flags |= PCI_BUS_FLAGS_NO_EXTCFG;
		pci_info(child, "extended config space not accessible\n");
	पूर्ण

	/* Set up शेष resource poपूर्णांकers and names */
	क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++) अणु
		child->resource[i] = &bridge->resource[PCI_BRIDGE_RESOURCES+i];
		child->resource[i]->name = child->name;
	पूर्ण
	bridge->subordinate = child;

add_dev:
	pci_set_bus_msi_करोमुख्य(child);
	ret = device_रेजिस्टर(&child->dev);
	WARN_ON(ret < 0);

	pcibios_add_bus(child);

	अगर (child->ops->add_bus) अणु
		ret = child->ops->add_bus(child);
		अगर (WARN_ON(ret < 0))
			dev_err(&child->dev, "failed to add bus: %d\n", ret);
	पूर्ण

	/* Create legacy_io and legacy_mem files क्रम this bus */
	pci_create_legacy_files(child);

	वापस child;
पूर्ण

काष्ठा pci_bus *pci_add_new_bus(काष्ठा pci_bus *parent, काष्ठा pci_dev *dev,
				पूर्णांक busnr)
अणु
	काष्ठा pci_bus *child;

	child = pci_alloc_child_bus(parent, dev, busnr);
	अगर (child) अणु
		करोwn_ग_लिखो(&pci_bus_sem);
		list_add_tail(&child->node, &parent->children);
		up_ग_लिखो(&pci_bus_sem);
	पूर्ण
	वापस child;
पूर्ण
EXPORT_SYMBOL(pci_add_new_bus);

अटल व्योम pci_enable_crs(काष्ठा pci_dev *pdev)
अणु
	u16 root_cap = 0;

	/* Enable CRS Software Visibility अगर supported */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_RTCAP, &root_cap);
	अगर (root_cap & PCI_EXP_RTCAP_CRSVIS)
		pcie_capability_set_word(pdev, PCI_EXP_RTCTL,
					 PCI_EXP_RTCTL_CRSSVE);
पूर्ण

अटल अचिन्हित पूर्णांक pci_scan_child_bus_extend(काष्ठा pci_bus *bus,
					      अचिन्हित पूर्णांक available_buses);
/**
 * pci_ea_fixed_busnrs() - Read fixed Secondary and Subordinate bus
 * numbers from EA capability.
 * @dev: Bridge
 * @sec: updated with secondary bus number from EA
 * @sub: updated with subordinate bus number from EA
 *
 * If @dev is a bridge with EA capability that specअगरies valid secondary
 * and subordinate bus numbers, वापस true with the bus numbers in @sec
 * and @sub.  Otherwise वापस false.
 */
अटल bool pci_ea_fixed_busnrs(काष्ठा pci_dev *dev, u8 *sec, u8 *sub)
अणु
	पूर्णांक ea, offset;
	u32 dw;
	u8 ea_sec, ea_sub;

	अगर (dev->hdr_type != PCI_HEADER_TYPE_BRIDGE)
		वापस false;

	/* find PCI EA capability in list */
	ea = pci_find_capability(dev, PCI_CAP_ID_EA);
	अगर (!ea)
		वापस false;

	offset = ea + PCI_EA_FIRST_ENT;
	pci_पढ़ो_config_dword(dev, offset, &dw);
	ea_sec =  dw & PCI_EA_SEC_BUS_MASK;
	ea_sub = (dw & PCI_EA_SUB_BUS_MASK) >> PCI_EA_SUB_BUS_SHIFT;
	अगर (ea_sec  == 0 || ea_sub < ea_sec)
		वापस false;

	*sec = ea_sec;
	*sub = ea_sub;
	वापस true;
पूर्ण

/*
 * pci_scan_bridge_extend() - Scan buses behind a bridge
 * @bus: Parent bus the bridge is on
 * @dev: Bridge itself
 * @max: Starting subordinate number of buses behind this bridge
 * @available_buses: Total number of buses available क्रम this bridge and
 *		     the devices below. After the minimal bus space has
 *		     been allocated the reमुख्यing buses will be
 *		     distributed equally between hotplug-capable bridges.
 * @pass: Either %0 (scan alपढ़ोy configured bridges) or %1 (scan bridges
 *        that need to be reconfigured.
 *
 * If it's a bridge, configure it and scan the bus behind it.
 * For CardBus bridges, we करोn't scan behind as the devices will
 * be handled by the bridge driver itself.
 *
 * We need to process bridges in two passes -- first we scan those
 * alपढ़ोy configured by the BIOS and after we are करोne with all of
 * them, we proceed to assigning numbers to the reमुख्यing buses in
 * order to aव्योम overlaps between old and new bus numbers.
 *
 * Return: New subordinate number covering all buses behind this bridge.
 */
अटल पूर्णांक pci_scan_bridge_extend(काष्ठा pci_bus *bus, काष्ठा pci_dev *dev,
				  पूर्णांक max, अचिन्हित पूर्णांक available_buses,
				  पूर्णांक pass)
अणु
	काष्ठा pci_bus *child;
	पूर्णांक is_cardbus = (dev->hdr_type == PCI_HEADER_TYPE_CARDBUS);
	u32 buses, i, j = 0;
	u16 bctl;
	u8 primary, secondary, subordinate;
	पूर्णांक broken = 0;
	bool fixed_buses;
	u8 fixed_sec, fixed_sub;
	पूर्णांक next_busnr;

	/*
	 * Make sure the bridge is घातered on to be able to access config
	 * space of devices below it.
	 */
	pm_runसमय_get_sync(&dev->dev);

	pci_पढ़ो_config_dword(dev, PCI_PRIMARY_BUS, &buses);
	primary = buses & 0xFF;
	secondary = (buses >> 8) & 0xFF;
	subordinate = (buses >> 16) & 0xFF;

	pci_dbg(dev, "scanning [bus %02x-%02x] behind bridge, pass %d\n",
		secondary, subordinate, pass);

	अगर (!primary && (primary != bus->number) && secondary && subordinate) अणु
		pci_warn(dev, "Primary bus is hard wired to 0\n");
		primary = bus->number;
	पूर्ण

	/* Check अगर setup is sensible at all */
	अगर (!pass &&
	    (primary != bus->number || secondary <= bus->number ||
	     secondary > subordinate)) अणु
		pci_info(dev, "bridge configuration invalid ([bus %02x-%02x]), reconfiguring\n",
			 secondary, subordinate);
		broken = 1;
	पूर्ण

	/*
	 * Disable Master-Abort Mode during probing to aव्योम reporting of
	 * bus errors in some architectures.
	 */
	pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &bctl);
	pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL,
			      bctl & ~PCI_BRIDGE_CTL_MASTER_ABORT);

	pci_enable_crs(dev);

	अगर ((secondary || subordinate) && !pcibios_assign_all_busses() &&
	    !is_cardbus && !broken) अणु
		अचिन्हित पूर्णांक cmax;

		/*
		 * Bus alपढ़ोy configured by firmware, process it in the
		 * first pass and just note the configuration.
		 */
		अगर (pass)
			जाओ out;

		/*
		 * The bus might alपढ़ोy exist क्रम two reasons: Either we
		 * are rescanning the bus or the bus is reachable through
		 * more than one bridge. The second हाल can happen with
		 * the i450NX chipset.
		 */
		child = pci_find_bus(pci_करोमुख्य_nr(bus), secondary);
		अगर (!child) अणु
			child = pci_add_new_bus(bus, dev, secondary);
			अगर (!child)
				जाओ out;
			child->primary = primary;
			pci_bus_insert_busn_res(child, secondary, subordinate);
			child->bridge_ctl = bctl;
		पूर्ण

		cmax = pci_scan_child_bus(child);
		अगर (cmax > subordinate)
			pci_warn(dev, "bridge has subordinate %02x but max busn %02x\n",
				 subordinate, cmax);

		/* Subordinate should equal child->busn_res.end */
		अगर (subordinate > max)
			max = subordinate;
	पूर्ण अन्यथा अणु

		/*
		 * We need to assign a number to this bus which we always
		 * करो in the second pass.
		 */
		अगर (!pass) अणु
			अगर (pcibios_assign_all_busses() || broken || is_cardbus)

				/*
				 * Temporarily disable क्रमwarding of the
				 * configuration cycles on all bridges in
				 * this bus segment to aव्योम possible
				 * conflicts in the second pass between two
				 * bridges programmed with overlapping bus
				 * ranges.
				 */
				pci_ग_लिखो_config_dword(dev, PCI_PRIMARY_BUS,
						       buses & ~0xffffff);
			जाओ out;
		पूर्ण

		/* Clear errors */
		pci_ग_लिखो_config_word(dev, PCI_STATUS, 0xffff);

		/* Read bus numbers from EA Capability (अगर present) */
		fixed_buses = pci_ea_fixed_busnrs(dev, &fixed_sec, &fixed_sub);
		अगर (fixed_buses)
			next_busnr = fixed_sec;
		अन्यथा
			next_busnr = max + 1;

		/*
		 * Prevent assigning a bus number that alपढ़ोy exists.
		 * This can happen when a bridge is hot-plugged, so in this
		 * हाल we only re-scan this bus.
		 */
		child = pci_find_bus(pci_करोमुख्य_nr(bus), next_busnr);
		अगर (!child) अणु
			child = pci_add_new_bus(bus, dev, next_busnr);
			अगर (!child)
				जाओ out;
			pci_bus_insert_busn_res(child, next_busnr,
						bus->busn_res.end);
		पूर्ण
		max++;
		अगर (available_buses)
			available_buses--;

		buses = (buses & 0xff000000)
		      | ((अचिन्हित पूर्णांक)(child->primary)     <<  0)
		      | ((अचिन्हित पूर्णांक)(child->busn_res.start)   <<  8)
		      | ((अचिन्हित पूर्णांक)(child->busn_res.end) << 16);

		/*
		 * yenta.c क्रमces a secondary latency समयr of 176.
		 * Copy that behaviour here.
		 */
		अगर (is_cardbus) अणु
			buses &= ~0xff000000;
			buses |= CARDBUS_LATENCY_TIMER << 24;
		पूर्ण

		/* We need to blast all three values with a single ग_लिखो */
		pci_ग_लिखो_config_dword(dev, PCI_PRIMARY_BUS, buses);

		अगर (!is_cardbus) अणु
			child->bridge_ctl = bctl;
			max = pci_scan_child_bus_extend(child, available_buses);
		पूर्ण अन्यथा अणु

			/*
			 * For CardBus bridges, we leave 4 bus numbers as
			 * cards with a PCI-to-PCI bridge can be inserted
			 * later.
			 */
			क्रम (i = 0; i < CARDBUS_RESERVE_BUSNR; i++) अणु
				काष्ठा pci_bus *parent = bus;
				अगर (pci_find_bus(pci_करोमुख्य_nr(bus),
							max+i+1))
					अवरोध;
				जबतक (parent->parent) अणु
					अगर ((!pcibios_assign_all_busses()) &&
					    (parent->busn_res.end > max) &&
					    (parent->busn_res.end <= max+i)) अणु
						j = 1;
					पूर्ण
					parent = parent->parent;
				पूर्ण
				अगर (j) अणु

					/*
					 * Often, there are two CardBus
					 * bridges -- try to leave one
					 * valid bus number क्रम each one.
					 */
					i /= 2;
					अवरोध;
				पूर्ण
			पूर्ण
			max += i;
		पूर्ण

		/*
		 * Set subordinate bus number to its real value.
		 * If fixed subordinate bus number exists from EA
		 * capability then use it.
		 */
		अगर (fixed_buses)
			max = fixed_sub;
		pci_bus_update_busn_res_end(child, max);
		pci_ग_लिखो_config_byte(dev, PCI_SUBORDINATE_BUS, max);
	पूर्ण

	प्र_लिखो(child->name,
		(is_cardbus ? "PCI CardBus %04x:%02x" : "PCI Bus %04x:%02x"),
		pci_करोमुख्य_nr(bus), child->number);

	/* Check that all devices are accessible */
	जबतक (bus->parent) अणु
		अगर ((child->busn_res.end > bus->busn_res.end) ||
		    (child->number > bus->busn_res.end) ||
		    (child->number < bus->number) ||
		    (child->busn_res.end < bus->number)) अणु
			dev_info(&dev->dev, "devices behind bridge are unusable because %pR cannot be assigned for them\n",
				 &child->busn_res);
			अवरोध;
		पूर्ण
		bus = bus->parent;
	पूर्ण

out:
	pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, bctl);

	pm_runसमय_put(&dev->dev);

	वापस max;
पूर्ण

/*
 * pci_scan_bridge() - Scan buses behind a bridge
 * @bus: Parent bus the bridge is on
 * @dev: Bridge itself
 * @max: Starting subordinate number of buses behind this bridge
 * @pass: Either %0 (scan alपढ़ोy configured bridges) or %1 (scan bridges
 *        that need to be reconfigured.
 *
 * If it's a bridge, configure it and scan the bus behind it.
 * For CardBus bridges, we करोn't scan behind as the devices will
 * be handled by the bridge driver itself.
 *
 * We need to process bridges in two passes -- first we scan those
 * alपढ़ोy configured by the BIOS and after we are करोne with all of
 * them, we proceed to assigning numbers to the reमुख्यing buses in
 * order to aव्योम overlaps between old and new bus numbers.
 *
 * Return: New subordinate number covering all buses behind this bridge.
 */
पूर्णांक pci_scan_bridge(काष्ठा pci_bus *bus, काष्ठा pci_dev *dev, पूर्णांक max, पूर्णांक pass)
अणु
	वापस pci_scan_bridge_extend(bus, dev, max, 0, pass);
पूर्ण
EXPORT_SYMBOL(pci_scan_bridge);

/*
 * Read पूर्णांकerrupt line and base address रेजिस्टरs.
 * The architecture-dependent code can tweak these, of course.
 */
अटल व्योम pci_पढ़ो_irq(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर irq;

	/* VFs are not allowed to use INTx, so skip the config पढ़ोs */
	अगर (dev->is_virtfn) अणु
		dev->pin = 0;
		dev->irq = 0;
		वापस;
	पूर्ण

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &irq);
	dev->pin = irq;
	अगर (irq)
		pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	dev->irq = irq;
पूर्ण

व्योम set_pcie_port_type(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos;
	u16 reg16;
	पूर्णांक type;
	काष्ठा pci_dev *parent;

	pos = pci_find_capability(pdev, PCI_CAP_ID_EXP);
	अगर (!pos)
		वापस;

	pdev->pcie_cap = pos;
	pci_पढ़ो_config_word(pdev, pos + PCI_EXP_FLAGS, &reg16);
	pdev->pcie_flags_reg = reg16;
	pci_पढ़ो_config_word(pdev, pos + PCI_EXP_DEVCAP, &reg16);
	pdev->pcie_mpss = reg16 & PCI_EXP_DEVCAP_PAYLOAD;

	parent = pci_upstream_bridge(pdev);
	अगर (!parent)
		वापस;

	/*
	 * Some प्रणालीs करो not identअगरy their upstream/करोwnstream ports
	 * correctly so detect impossible configurations here and correct
	 * the port type accordingly.
	 */
	type = pci_pcie_type(pdev);
	अगर (type == PCI_EXP_TYPE_DOWNSTREAM) अणु
		/*
		 * If pdev claims to be करोwnstream port but the parent
		 * device is also करोwnstream port assume pdev is actually
		 * upstream port.
		 */
		अगर (pcie_करोwnstream_port(parent)) अणु
			pci_info(pdev, "claims to be downstream port but is acting as upstream port, correcting type\n");
			pdev->pcie_flags_reg &= ~PCI_EXP_FLAGS_TYPE;
			pdev->pcie_flags_reg |= PCI_EXP_TYPE_UPSTREAM;
		पूर्ण
	पूर्ण अन्यथा अगर (type == PCI_EXP_TYPE_UPSTREAM) अणु
		/*
		 * If pdev claims to be upstream port but the parent
		 * device is also upstream port assume pdev is actually
		 * करोwnstream port.
		 */
		अगर (pci_pcie_type(parent) == PCI_EXP_TYPE_UPSTREAM) अणु
			pci_info(pdev, "claims to be upstream port but is acting as downstream port, correcting type\n");
			pdev->pcie_flags_reg &= ~PCI_EXP_FLAGS_TYPE;
			pdev->pcie_flags_reg |= PCI_EXP_TYPE_DOWNSTREAM;
		पूर्ण
	पूर्ण
पूर्ण

व्योम set_pcie_hotplug_bridge(काष्ठा pci_dev *pdev)
अणु
	u32 reg32;

	pcie_capability_पढ़ो_dword(pdev, PCI_EXP_SLTCAP, &reg32);
	अगर (reg32 & PCI_EXP_SLTCAP_HPC)
		pdev->is_hotplug_bridge = 1;
पूर्ण

अटल व्योम set_pcie_thunderbolt(काष्ठा pci_dev *dev)
अणु
	पूर्णांक vsec = 0;
	u32 header;

	जबतक ((vsec = pci_find_next_ext_capability(dev, vsec,
						    PCI_EXT_CAP_ID_VNDR))) अणु
		pci_पढ़ो_config_dword(dev, vsec + PCI_VNDR_HEADER, &header);

		/* Is the device part of a Thunderbolt controller? */
		अगर (dev->venकरोr == PCI_VENDOR_ID_INTEL &&
		    PCI_VNDR_HEADER_ID(header) == PCI_VSEC_ID_INTEL_TBT) अणु
			dev->is_thunderbolt = 1;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_pcie_untrusted(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *parent;

	/*
	 * If the upstream bridge is untrusted we treat this device
	 * untrusted as well.
	 */
	parent = pci_upstream_bridge(dev);
	अगर (parent && (parent->untrusted || parent->बाह्यal_facing))
		dev->untrusted = true;
पूर्ण

/**
 * pci_ext_cfg_is_aliased - Is ext config space just an alias of std config?
 * @dev: PCI device
 *
 * PCI Express to PCI/PCI-X Bridge Specअगरication, rev 1.0, 4.1.4 says that
 * when क्रमwarding a type1 configuration request the bridge must check that
 * the extended रेजिस्टर address field is zero.  The bridge is not permitted
 * to क्रमward the transactions and must handle it as an Unsupported Request.
 * Some bridges करो not follow this rule and simply drop the extended रेजिस्टर
 * bits, resulting in the standard config space being aliased, every 256
 * bytes across the entire configuration space.  Test क्रम this condition by
 * comparing the first dword of each potential alias to the venकरोr/device ID.
 * Known offenders:
 *   ASM1083/1085 PCIe-to-PCI Reversible Bridge (1b21:1080, rev 01 & 03)
 *   AMD/ATI SBx00 PCI to PCI Bridge (1002:4384, rev 40)
 */
अटल bool pci_ext_cfg_is_aliased(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_QUIRKS
	पूर्णांक pos;
	u32 header, पंचांगp;

	pci_पढ़ो_config_dword(dev, PCI_VENDOR_ID, &header);

	क्रम (pos = PCI_CFG_SPACE_SIZE;
	     pos < PCI_CFG_SPACE_EXP_SIZE; pos += PCI_CFG_SPACE_SIZE) अणु
		अगर (pci_पढ़ो_config_dword(dev, pos, &पंचांगp) != PCIBIOS_SUCCESSFUL
		    || header != पंचांगp)
			वापस false;
	पूर्ण

	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/**
 * pci_cfg_space_size_ext - Get the configuration space size of the PCI device
 * @dev: PCI device
 *
 * Regular PCI devices have 256 bytes, but PCI-X 2 and PCI Express devices
 * have 4096 bytes.  Even अगर the device is capable, that करोesn't mean we can
 * access it.  Maybe we करोn't have a way to generate extended config space
 * accesses, or the device is behind a reverse Express bridge.  So we try
 * पढ़ोing the dword at 0x100 which must either be 0 or a valid extended
 * capability header.
 */
अटल पूर्णांक pci_cfg_space_size_ext(काष्ठा pci_dev *dev)
अणु
	u32 status;
	पूर्णांक pos = PCI_CFG_SPACE_SIZE;

	अगर (pci_पढ़ो_config_dword(dev, pos, &status) != PCIBIOS_SUCCESSFUL)
		वापस PCI_CFG_SPACE_SIZE;
	अगर (status == 0xffffffff || pci_ext_cfg_is_aliased(dev))
		वापस PCI_CFG_SPACE_SIZE;

	वापस PCI_CFG_SPACE_EXP_SIZE;
पूर्ण

पूर्णांक pci_cfg_space_size(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u32 status;
	u16 class;

#अगर_घोषित CONFIG_PCI_IOV
	/*
	 * Per the SR-IOV specअगरication (rev 1.1, sec 3.5), VFs are required to
	 * implement a PCIe capability and thereक्रमe must implement extended
	 * config space.  We can skip the NO_EXTCFG test below and the
	 * reachability/aliasing test in pci_cfg_space_size_ext() by virtue of
	 * the fact that the SR-IOV capability on the PF resides in extended
	 * config space and must be accessible and non-aliased to have enabled
	 * support क्रम this VF.  This is a micro perक्रमmance optimization क्रम
	 * प्रणालीs supporting many VFs.
	 */
	अगर (dev->is_virtfn)
		वापस PCI_CFG_SPACE_EXP_SIZE;
#पूर्ण_अगर

	अगर (dev->bus->bus_flags & PCI_BUS_FLAGS_NO_EXTCFG)
		वापस PCI_CFG_SPACE_SIZE;

	class = dev->class >> 8;
	अगर (class == PCI_CLASS_BRIDGE_HOST)
		वापस pci_cfg_space_size_ext(dev);

	अगर (pci_is_pcie(dev))
		वापस pci_cfg_space_size_ext(dev);

	pos = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!pos)
		वापस PCI_CFG_SPACE_SIZE;

	pci_पढ़ो_config_dword(dev, pos + PCI_X_STATUS, &status);
	अगर (status & (PCI_X_STATUS_266MHZ | PCI_X_STATUS_533MHZ))
		वापस pci_cfg_space_size_ext(dev);

	वापस PCI_CFG_SPACE_SIZE;
पूर्ण

अटल u32 pci_class(काष्ठा pci_dev *dev)
अणु
	u32 class;

#अगर_घोषित CONFIG_PCI_IOV
	अगर (dev->is_virtfn)
		वापस dev->physfn->sriov->class;
#पूर्ण_अगर
	pci_पढ़ो_config_dword(dev, PCI_CLASS_REVISION, &class);
	वापस class;
पूर्ण

अटल व्योम pci_subप्रणाली_ids(काष्ठा pci_dev *dev, u16 *venकरोr, u16 *device)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	अगर (dev->is_virtfn) अणु
		*venकरोr = dev->physfn->sriov->subप्रणाली_venकरोr;
		*device = dev->physfn->sriov->subप्रणाली_device;
		वापस;
	पूर्ण
#पूर्ण_अगर
	pci_पढ़ो_config_word(dev, PCI_SUBSYSTEM_VENDOR_ID, venकरोr);
	pci_पढ़ो_config_word(dev, PCI_SUBSYSTEM_ID, device);
पूर्ण

अटल u8 pci_hdr_type(काष्ठा pci_dev *dev)
अणु
	u8 hdr_type;

#अगर_घोषित CONFIG_PCI_IOV
	अगर (dev->is_virtfn)
		वापस dev->physfn->sriov->hdr_type;
#पूर्ण_अगर
	pci_पढ़ो_config_byte(dev, PCI_HEADER_TYPE, &hdr_type);
	वापस hdr_type;
पूर्ण

#घोषणा LEGACY_IO_RESOURCE	(IORESOURCE_IO | IORESOURCE_PCI_FIXED)

/**
 * pci_पूर्णांकx_mask_broken - Test PCI_COMMAND_INTX_DISABLE writability
 * @dev: PCI device
 *
 * Test whether PCI_COMMAND_INTX_DISABLE is writable क्रम @dev.  Check this
 * at क्रमागतeration-समय to aव्योम modअगरying PCI_COMMAND at run-समय.
 */
अटल पूर्णांक pci_पूर्णांकx_mask_broken(काष्ठा pci_dev *dev)
अणु
	u16 orig, toggle, new;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &orig);
	toggle = orig ^ PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, toggle);
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &new);

	pci_ग_लिखो_config_word(dev, PCI_COMMAND, orig);

	/*
	 * PCI_COMMAND_INTX_DISABLE was reserved and पढ़ो-only prior to PCI
	 * r2.3, so strictly speaking, a device is not *broken* अगर it's not
	 * writable.  But we'll live with the misnomer क्रम now.
	 */
	अगर (new != toggle)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम early_dump_pci_device(काष्ठा pci_dev *pdev)
अणु
	u32 value[256 / 4];
	पूर्णांक i;

	pci_info(pdev, "config space:\n");

	क्रम (i = 0; i < 256; i += 4)
		pci_पढ़ो_config_dword(pdev, i, &value[i / 4]);

	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
		       value, 256, false);
पूर्ण

/**
 * pci_setup_device - Fill in class and map inक्रमmation of a device
 * @dev: the device काष्ठाure to fill
 *
 * Initialize the device काष्ठाure with inक्रमmation about the device's
 * venकरोr,class,memory and IO-space addresses, IRQ lines etc.
 * Called at initialisation of the PCI subप्रणाली and by CardBus services.
 * Returns 0 on success and negative अगर unknown type of device (not normal,
 * bridge or CardBus).
 */
पूर्णांक pci_setup_device(काष्ठा pci_dev *dev)
अणु
	u32 class;
	u16 cmd;
	u8 hdr_type;
	पूर्णांक pos = 0;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;

	hdr_type = pci_hdr_type(dev);

	dev->sysdata = dev->bus->sysdata;
	dev->dev.parent = dev->bus->bridge;
	dev->dev.bus = &pci_bus_type;
	dev->hdr_type = hdr_type & 0x7f;
	dev->multअगरunction = !!(hdr_type & 0x80);
	dev->error_state = pci_channel_io_normal;
	set_pcie_port_type(dev);

	pci_dev_assign_slot(dev);

	/*
	 * Assume 32-bit PCI; let 64-bit PCI cards (which are far rarer)
	 * set this higher, assuming the प्रणाली even supports it.
	 */
	dev->dma_mask = 0xffffffff;

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_करोमुख्य_nr(dev->bus),
		     dev->bus->number, PCI_SLOT(dev->devfn),
		     PCI_FUNC(dev->devfn));

	class = pci_class(dev);

	dev->revision = class & 0xff;
	dev->class = class >> 8;		    /* upper 3 bytes */

	अगर (pci_early_dump)
		early_dump_pci_device(dev);

	/* Need to have dev->class पढ़ोy */
	dev->cfg_size = pci_cfg_space_size(dev);

	/* Need to have dev->cfg_size पढ़ोy */
	set_pcie_thunderbolt(dev);

	set_pcie_untrusted(dev);

	/* "Unknown power state" */
	dev->current_state = PCI_UNKNOWN;

	/* Early fixups, beक्रमe probing the BARs */
	pci_fixup_device(pci_fixup_early, dev);

	pci_info(dev, "[%04x:%04x] type %02x class %#08x\n",
		 dev->venकरोr, dev->device, dev->hdr_type, dev->class);

	/* Device class may be changed after fixup */
	class = dev->class >> 8;

	अगर (dev->non_compliant_bars && !dev->mmio_always_on) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		अगर (cmd & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY)) अणु
			pci_info(dev, "device has non-compliant BARs; disabling IO/MEM decoding\n");
			cmd &= ~PCI_COMMAND_IO;
			cmd &= ~PCI_COMMAND_MEMORY;
			pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
		पूर्ण
	पूर्ण

	dev->broken_पूर्णांकx_masking = pci_पूर्णांकx_mask_broken(dev);

	चयन (dev->hdr_type) अणु		    /* header type */
	हाल PCI_HEADER_TYPE_NORMAL:		    /* standard header */
		अगर (class == PCI_CLASS_BRIDGE_PCI)
			जाओ bad;
		pci_पढ़ो_irq(dev);
		pci_पढ़ो_bases(dev, 6, PCI_ROM_ADDRESS);

		pci_subप्रणाली_ids(dev, &dev->subप्रणाली_venकरोr, &dev->subप्रणाली_device);

		/*
		 * Do the ugly legacy mode stuff here rather than broken chip
		 * quirk code. Legacy mode ATA controllers have fixed
		 * addresses. These are not always echoed in BAR0-3, and
		 * BAR0-3 in a few हालs contain junk!
		 */
		अगर (class == PCI_CLASS_STORAGE_IDE) अणु
			u8 progअगर;
			pci_पढ़ो_config_byte(dev, PCI_CLASS_PROG, &progअगर);
			अगर ((progअगर & 1) == 0) अणु
				region.start = 0x1F0;
				region.end = 0x1F7;
				res = &dev->resource[0];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x10: %pR\n",
					 res);
				region.start = 0x3F6;
				region.end = 0x3F6;
				res = &dev->resource[1];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x14: %pR\n",
					 res);
			पूर्ण
			अगर ((progअगर & 4) == 0) अणु
				region.start = 0x170;
				region.end = 0x177;
				res = &dev->resource[2];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x18: %pR\n",
					 res);
				region.start = 0x376;
				region.end = 0x376;
				res = &dev->resource[3];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x1c: %pR\n",
					 res);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल PCI_HEADER_TYPE_BRIDGE:		    /* bridge header */
		/*
		 * The PCI-to-PCI bridge spec requires that subtractive
		 * decoding (i.e. transparent) bridge must have programming
		 * पूर्णांकerface code of 0x01.
		 */
		pci_पढ़ो_irq(dev);
		dev->transparent = ((dev->class & 0xff) == 1);
		pci_पढ़ो_bases(dev, 2, PCI_ROM_ADDRESS1);
		pci_पढ़ो_bridge_winकरोws(dev);
		set_pcie_hotplug_bridge(dev);
		pos = pci_find_capability(dev, PCI_CAP_ID_SSVID);
		अगर (pos) अणु
			pci_पढ़ो_config_word(dev, pos + PCI_SSVID_VENDOR_ID, &dev->subप्रणाली_venकरोr);
			pci_पढ़ो_config_word(dev, pos + PCI_SSVID_DEVICE_ID, &dev->subप्रणाली_device);
		पूर्ण
		अवरोध;

	हाल PCI_HEADER_TYPE_CARDBUS:		    /* CardBus bridge header */
		अगर (class != PCI_CLASS_BRIDGE_CARDBUS)
			जाओ bad;
		pci_पढ़ो_irq(dev);
		pci_पढ़ो_bases(dev, 1, 0);
		pci_पढ़ो_config_word(dev, PCI_CB_SUBSYSTEM_VENDOR_ID, &dev->subप्रणाली_venकरोr);
		pci_पढ़ो_config_word(dev, PCI_CB_SUBSYSTEM_ID, &dev->subप्रणाली_device);
		अवरोध;

	शेष:				    /* unknown header */
		pci_err(dev, "unknown header type %02x, ignoring device\n",
			dev->hdr_type);
		वापस -EIO;

	bad:
		pci_err(dev, "ignoring class %#08x (doesn't match header type %02x)\n",
			dev->class, dev->hdr_type);
		dev->class = PCI_CLASS_NOT_DEFINED << 8;
	पूर्ण

	/* We found a fine healthy device, go go go... */
	वापस 0;
पूर्ण

अटल व्योम pci_configure_mps(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *bridge = pci_upstream_bridge(dev);
	पूर्णांक mps, mpss, p_mps, rc;

	अगर (!pci_is_pcie(dev))
		वापस;

	/* MPS and MRRS fields are of type 'RsvdP' क्रम VFs, लघु-circuit out */
	अगर (dev->is_virtfn)
		वापस;

	/*
	 * For Root Complex Integrated Endpoपूर्णांकs, program the maximum
	 * supported value unless limited by the PCIE_BUS_PEER2PEER हाल.
	 */
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END) अणु
		अगर (pcie_bus_config == PCIE_BUS_PEER2PEER)
			mps = 128;
		अन्यथा
			mps = 128 << dev->pcie_mpss;
		rc = pcie_set_mps(dev, mps);
		अगर (rc) अणु
			pci_warn(dev, "can't set Max Payload Size to %d; if necessary, use \"pci=pcie_bus_safe\" and report a bug\n",
				 mps);
		पूर्ण
		वापस;
	पूर्ण

	अगर (!bridge || !pci_is_pcie(bridge))
		वापस;

	mps = pcie_get_mps(dev);
	p_mps = pcie_get_mps(bridge);

	अगर (mps == p_mps)
		वापस;

	अगर (pcie_bus_config == PCIE_BUS_TUNE_OFF) अणु
		pci_warn(dev, "Max Payload Size %d, but upstream %s set to %d; if necessary, use \"pci=pcie_bus_safe\" and report a bug\n",
			 mps, pci_name(bridge), p_mps);
		वापस;
	पूर्ण

	/*
	 * Fancier MPS configuration is करोne later by
	 * pcie_bus_configure_settings()
	 */
	अगर (pcie_bus_config != PCIE_BUS_DEFAULT)
		वापस;

	mpss = 128 << dev->pcie_mpss;
	अगर (mpss < p_mps && pci_pcie_type(bridge) == PCI_EXP_TYPE_ROOT_PORT) अणु
		pcie_set_mps(bridge, mpss);
		pci_info(dev, "Upstream bridge's Max Payload Size set to %d (was %d, max %d)\n",
			 mpss, p_mps, 128 << bridge->pcie_mpss);
		p_mps = pcie_get_mps(bridge);
	पूर्ण

	rc = pcie_set_mps(dev, p_mps);
	अगर (rc) अणु
		pci_warn(dev, "can't set Max Payload Size to %d; if necessary, use \"pci=pcie_bus_safe\" and report a bug\n",
			 p_mps);
		वापस;
	पूर्ण

	pci_info(dev, "Max Payload Size set to %d (was %d, max %d)\n",
		 p_mps, mps, mpss);
पूर्ण

पूर्णांक pci_configure_extended_tags(काष्ठा pci_dev *dev, व्योम *ign)
अणु
	काष्ठा pci_host_bridge *host;
	u32 cap;
	u16 ctl;
	पूर्णांक ret;

	अगर (!pci_is_pcie(dev))
		वापस 0;

	ret = pcie_capability_पढ़ो_dword(dev, PCI_EXP_DEVCAP, &cap);
	अगर (ret)
		वापस 0;

	अगर (!(cap & PCI_EXP_DEVCAP_EXT_TAG))
		वापस 0;

	ret = pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &ctl);
	अगर (ret)
		वापस 0;

	host = pci_find_host_bridge(dev->bus);
	अगर (!host)
		वापस 0;

	/*
	 * If some device in the hierarchy करोesn't handle Extended Tags
	 * correctly, make sure they're disabled.
	 */
	अगर (host->no_ext_tags) अणु
		अगर (ctl & PCI_EXP_DEVCTL_EXT_TAG) अणु
			pci_info(dev, "disabling Extended Tags\n");
			pcie_capability_clear_word(dev, PCI_EXP_DEVCTL,
						   PCI_EXP_DEVCTL_EXT_TAG);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!(ctl & PCI_EXP_DEVCTL_EXT_TAG)) अणु
		pci_info(dev, "enabling Extended Tags\n");
		pcie_capability_set_word(dev, PCI_EXP_DEVCTL,
					 PCI_EXP_DEVCTL_EXT_TAG);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pcie_relaxed_ordering_enabled - Probe क्रम PCIe relaxed ordering enable
 * @dev: PCI device to query
 *
 * Returns true अगर the device has enabled relaxed ordering attribute.
 */
bool pcie_relaxed_ordering_enabled(काष्ठा pci_dev *dev)
अणु
	u16 v;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &v);

	वापस !!(v & PCI_EXP_DEVCTL_RELAX_EN);
पूर्ण
EXPORT_SYMBOL(pcie_relaxed_ordering_enabled);

अटल व्योम pci_configure_relaxed_ordering(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *root;

	/* PCI_EXP_DEVICE_RELAX_EN is RsvdP in VFs */
	अगर (dev->is_virtfn)
		वापस;

	अगर (!pcie_relaxed_ordering_enabled(dev))
		वापस;

	/*
	 * For now, we only deal with Relaxed Ordering issues with Root
	 * Ports. Peer-to-Peer DMA is another can of worms.
	 */
	root = pcie_find_root_port(dev);
	अगर (!root)
		वापस;

	अगर (root->dev_flags & PCI_DEV_FLAGS_NO_RELAXED_ORDERING) अणु
		pcie_capability_clear_word(dev, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_RELAX_EN);
		pci_info(dev, "Relaxed Ordering disabled because the Root Port didn't support it\n");
	पूर्ण
पूर्ण

अटल व्योम pci_configure_ltr(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCIEASPM
	काष्ठा pci_host_bridge *host = pci_find_host_bridge(dev->bus);
	काष्ठा pci_dev *bridge;
	u32 cap, ctl;

	अगर (!pci_is_pcie(dev))
		वापस;

	/* Read L1 PM substate capabilities */
	dev->l1ss = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_L1SS);

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_DEVCAP2, &cap);
	अगर (!(cap & PCI_EXP_DEVCAP2_LTR))
		वापस;

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_DEVCTL2, &ctl);
	अगर (ctl & PCI_EXP_DEVCTL2_LTR_EN) अणु
		अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT) अणु
			dev->ltr_path = 1;
			वापस;
		पूर्ण

		bridge = pci_upstream_bridge(dev);
		अगर (bridge && bridge->ltr_path)
			dev->ltr_path = 1;

		वापस;
	पूर्ण

	अगर (!host->native_ltr)
		वापस;

	/*
	 * Software must not enable LTR in an Endpoपूर्णांक unless the Root
	 * Complex and all पूर्णांकermediate Switches indicate support क्रम LTR.
	 * PCIe r4.0, sec 6.18.
	 */
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT ||
	    ((bridge = pci_upstream_bridge(dev)) &&
	      bridge->ltr_path)) अणु
		pcie_capability_set_word(dev, PCI_EXP_DEVCTL2,
					 PCI_EXP_DEVCTL2_LTR_EN);
		dev->ltr_path = 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम pci_configure_eetlp_prefix(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_PASID
	काष्ठा pci_dev *bridge;
	पूर्णांक pcie_type;
	u32 cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_DEVCAP2, &cap);
	अगर (!(cap & PCI_EXP_DEVCAP2_EE_PREFIX))
		वापस;

	pcie_type = pci_pcie_type(dev);
	अगर (pcie_type == PCI_EXP_TYPE_ROOT_PORT ||
	    pcie_type == PCI_EXP_TYPE_RC_END)
		dev->eetlp_prefix_path = 1;
	अन्यथा अणु
		bridge = pci_upstream_bridge(dev);
		अगर (bridge && bridge->eetlp_prefix_path)
			dev->eetlp_prefix_path = 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम pci_configure_serr(काष्ठा pci_dev *dev)
अणु
	u16 control;

	अगर (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) अणु

		/*
		 * A bridge will not क्रमward ERR_ messages coming from an
		 * endpoपूर्णांक unless SERR# क्रमwarding is enabled.
		 */
		pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &control);
		अगर (!(control & PCI_BRIDGE_CTL_SERR)) अणु
			control |= PCI_BRIDGE_CTL_SERR;
			pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, control);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pci_configure_device(काष्ठा pci_dev *dev)
अणु
	pci_configure_mps(dev);
	pci_configure_extended_tags(dev, शून्य);
	pci_configure_relaxed_ordering(dev);
	pci_configure_ltr(dev);
	pci_configure_eetlp_prefix(dev);
	pci_configure_serr(dev);

	pci_acpi_program_hp_params(dev);
पूर्ण

अटल व्योम pci_release_capabilities(काष्ठा pci_dev *dev)
अणु
	pci_aer_निकास(dev);
	pci_rcec_निकास(dev);
	pci_vpd_release(dev);
	pci_iov_release(dev);
	pci_मुक्त_cap_save_buffers(dev);
पूर्ण

/**
 * pci_release_dev - Free a PCI device काष्ठाure when all users of it are
 *		     finished
 * @dev: device that's been disconnected
 *
 * Will be called only by the device core when all users of this PCI device are
 * करोne.
 */
अटल व्योम pci_release_dev(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev;

	pci_dev = to_pci_dev(dev);
	pci_release_capabilities(pci_dev);
	pci_release_of_node(pci_dev);
	pcibios_release_device(pci_dev);
	pci_bus_put(pci_dev->bus);
	kमुक्त(pci_dev->driver_override);
	biपंचांगap_मुक्त(pci_dev->dma_alias_mask);
	kमुक्त(pci_dev);
पूर्ण

काष्ठा pci_dev *pci_alloc_dev(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	dev = kzalloc(माप(काष्ठा pci_dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	INIT_LIST_HEAD(&dev->bus_list);
	dev->dev.type = &pci_dev_type;
	dev->bus = pci_bus_get(bus);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(pci_alloc_dev);

अटल bool pci_bus_crs_venकरोr_id(u32 l)
अणु
	वापस (l & 0xffff) == 0x0001;
पूर्ण

अटल bool pci_bus_रुको_crs(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *l,
			     पूर्णांक समयout)
अणु
	पूर्णांक delay = 1;

	अगर (!pci_bus_crs_venकरोr_id(*l))
		वापस true;	/* not a CRS completion */

	अगर (!समयout)
		वापस false;	/* CRS, but caller करोesn't want to रुको */

	/*
	 * We got the reserved Venकरोr ID that indicates a completion with
	 * Configuration Request Retry Status (CRS).  Retry until we get a
	 * valid Venकरोr ID or we समय out.
	 */
	जबतक (pci_bus_crs_venकरोr_id(*l)) अणु
		अगर (delay > समयout) अणु
			pr_warn("pci %04x:%02x:%02x.%d: not ready after %dms; giving up\n",
				pci_करोमुख्य_nr(bus), bus->number,
				PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

			वापस false;
		पूर्ण
		अगर (delay >= 1000)
			pr_info("pci %04x:%02x:%02x.%d: not ready after %dms; waiting\n",
				pci_करोमुख्य_nr(bus), bus->number,
				PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

		msleep(delay);
		delay *= 2;

		अगर (pci_bus_पढ़ो_config_dword(bus, devfn, PCI_VENDOR_ID, l))
			वापस false;
	पूर्ण

	अगर (delay >= 1000)
		pr_info("pci %04x:%02x:%02x.%d: ready after %dms\n",
			pci_करोमुख्य_nr(bus), bus->number,
			PCI_SLOT(devfn), PCI_FUNC(devfn), delay - 1);

	वापस true;
पूर्ण

bool pci_bus_generic_पढ़ो_dev_venकरोr_id(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *l,
					पूर्णांक समयout)
अणु
	अगर (pci_bus_पढ़ो_config_dword(bus, devfn, PCI_VENDOR_ID, l))
		वापस false;

	/* Some broken boards वापस 0 or ~0 अगर a slot is empty: */
	अगर (*l == 0xffffffff || *l == 0x00000000 ||
	    *l == 0x0000ffff || *l == 0xffff0000)
		वापस false;

	अगर (pci_bus_crs_venकरोr_id(*l))
		वापस pci_bus_रुको_crs(bus, devfn, l, समयout);

	वापस true;
पूर्ण

bool pci_bus_पढ़ो_dev_venकरोr_id(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *l,
				पूर्णांक समयout)
अणु
#अगर_घोषित CONFIG_PCI_QUIRKS
	काष्ठा pci_dev *bridge = bus->self;

	/*
	 * Certain IDT चयनes have an issue where they improperly trigger
	 * ACS Source Validation errors on completions क्रम config पढ़ोs.
	 */
	अगर (bridge && bridge->venकरोr == PCI_VENDOR_ID_IDT &&
	    bridge->device == 0x80b5)
		वापस pci_idt_bus_quirk(bus, devfn, l, समयout);
#पूर्ण_अगर

	वापस pci_bus_generic_पढ़ो_dev_venकरोr_id(bus, devfn, l, समयout);
पूर्ण
EXPORT_SYMBOL(pci_bus_पढ़ो_dev_venकरोr_id);

/*
 * Read the config data क्रम a PCI device, sanity-check it,
 * and fill in the dev काष्ठाure.
 */
अटल काष्ठा pci_dev *pci_scan_device(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	काष्ठा pci_dev *dev;
	u32 l;

	अगर (!pci_bus_पढ़ो_dev_venकरोr_id(bus, devfn, &l, 60*1000))
		वापस शून्य;

	dev = pci_alloc_dev(bus);
	अगर (!dev)
		वापस शून्य;

	dev->devfn = devfn;
	dev->venकरोr = l & 0xffff;
	dev->device = (l >> 16) & 0xffff;

	pci_set_of_node(dev);

	अगर (pci_setup_device(dev)) अणु
		pci_release_of_node(dev);
		pci_bus_put(dev->bus);
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

व्योम pcie_report_करोwntraining(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_is_pcie(dev))
		वापस;

	/* Look from the device up to aव्योम करोwnstream ports with no devices */
	अगर ((pci_pcie_type(dev) != PCI_EXP_TYPE_ENDPOINT) &&
	    (pci_pcie_type(dev) != PCI_EXP_TYPE_LEG_END) &&
	    (pci_pcie_type(dev) != PCI_EXP_TYPE_UPSTREAM))
		वापस;

	/* Multi-function PCIe devices share the same link/status */
	अगर (PCI_FUNC(dev->devfn) != 0 || dev->is_virtfn)
		वापस;

	/* Prपूर्णांक link status only अगर the device is स्थिरrained by the fabric */
	__pcie_prपूर्णांक_link_status(dev, false);
पूर्ण

अटल व्योम pci_init_capabilities(काष्ठा pci_dev *dev)
अणु
	pci_ea_init(dev);		/* Enhanced Allocation */
	pci_msi_init(dev);		/* Disable MSI */
	pci_msix_init(dev);		/* Disable MSI-X */

	/* Buffers क्रम saving PCIe and PCI-X capabilities */
	pci_allocate_cap_save_buffers(dev);

	pci_pm_init(dev);		/* Power Management */
	pci_vpd_init(dev);		/* Vital Product Data */
	pci_configure_ari(dev);		/* Alternative Routing-ID Forwarding */
	pci_iov_init(dev);		/* Single Root I/O Virtualization */
	pci_ats_init(dev);		/* Address Translation Services */
	pci_pri_init(dev);		/* Page Request Interface */
	pci_pasid_init(dev);		/* Process Address Space ID */
	pci_acs_init(dev);		/* Access Control Services */
	pci_pपंचांग_init(dev);		/* Precision Time Measurement */
	pci_aer_init(dev);		/* Advanced Error Reporting */
	pci_dpc_init(dev);		/* Downstream Port Containment */
	pci_rcec_init(dev);		/* Root Complex Event Collector */

	pcie_report_करोwntraining(dev);

	अगर (pci_probe_reset_function(dev) == 0)
		dev->reset_fn = 1;
पूर्ण

/*
 * This is the equivalent of pci_host_bridge_msi_करोमुख्य() that acts on
 * devices. Firmware पूर्णांकerfaces that can select the MSI करोमुख्य on a
 * per-device basis should be called from here.
 */
अटल काष्ठा irq_करोमुख्य *pci_dev_msi_करोमुख्य(काष्ठा pci_dev *dev)
अणु
	काष्ठा irq_करोमुख्य *d;

	/*
	 * If a करोमुख्य has been set through the pcibios_add_device()
	 * callback, then this is the one (platक्रमm code knows best).
	 */
	d = dev_get_msi_करोमुख्य(&dev->dev);
	अगर (d)
		वापस d;

	/*
	 * Let's see अगर we have a firmware पूर्णांकerface able to provide
	 * the करोमुख्य.
	 */
	d = pci_msi_get_device_करोमुख्य(dev);
	अगर (d)
		वापस d;

	वापस शून्य;
पूर्ण

अटल व्योम pci_set_msi_करोमुख्य(काष्ठा pci_dev *dev)
अणु
	काष्ठा irq_करोमुख्य *d;

	/*
	 * If the platक्रमm or firmware पूर्णांकerfaces cannot supply a
	 * device-specअगरic MSI करोमुख्य, then inherit the शेष करोमुख्य
	 * from the host bridge itself.
	 */
	d = pci_dev_msi_करोमुख्य(dev);
	अगर (!d)
		d = dev_get_msi_करोमुख्य(&dev->bus->dev);

	dev_set_msi_करोमुख्य(&dev->dev, d);
पूर्ण

व्योम pci_device_add(काष्ठा pci_dev *dev, काष्ठा pci_bus *bus)
अणु
	पूर्णांक ret;

	pci_configure_device(dev);

	device_initialize(&dev->dev);
	dev->dev.release = pci_release_dev;

	set_dev_node(&dev->dev, pcibus_to_node(bus));
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.dma_parms = &dev->dma_parms;
	dev->dev.coherent_dma_mask = 0xffffffffull;

	dma_set_max_seg_size(&dev->dev, 65536);
	dma_set_seg_boundary(&dev->dev, 0xffffffff);

	/* Fix up broken headers */
	pci_fixup_device(pci_fixup_header, dev);

	pci_reassigndev_resource_alignment(dev);

	dev->state_saved = false;

	pci_init_capabilities(dev);

	/*
	 * Add the device to our list of discovered devices
	 * and the bus list क्रम fixup functions, etc.
	 */
	करोwn_ग_लिखो(&pci_bus_sem);
	list_add_tail(&dev->bus_list, &bus->devices);
	up_ग_लिखो(&pci_bus_sem);

	ret = pcibios_add_device(dev);
	WARN_ON(ret < 0);

	/* Set up MSI IRQ करोमुख्य */
	pci_set_msi_करोमुख्य(dev);

	/* Notअगरier could use PCI capabilities */
	dev->match_driver = false;
	ret = device_add(&dev->dev);
	WARN_ON(ret < 0);
पूर्ण

काष्ठा pci_dev *pci_scan_single_device(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	काष्ठा pci_dev *dev;

	dev = pci_get_slot(bus, devfn);
	अगर (dev) अणु
		pci_dev_put(dev);
		वापस dev;
	पूर्ण

	dev = pci_scan_device(bus, devfn);
	अगर (!dev)
		वापस शून्य;

	pci_device_add(dev, bus);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(pci_scan_single_device);

अटल अचिन्हित next_fn(काष्ठा pci_bus *bus, काष्ठा pci_dev *dev, अचिन्हित fn)
अणु
	पूर्णांक pos;
	u16 cap = 0;
	अचिन्हित next_fn;

	अगर (pci_ari_enabled(bus)) अणु
		अगर (!dev)
			वापस 0;
		pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ARI);
		अगर (!pos)
			वापस 0;

		pci_पढ़ो_config_word(dev, pos + PCI_ARI_CAP, &cap);
		next_fn = PCI_ARI_CAP_NFN(cap);
		अगर (next_fn <= fn)
			वापस 0;	/* protect against malक्रमmed list */

		वापस next_fn;
	पूर्ण

	/* dev may be शून्य क्रम non-contiguous multअगरunction devices */
	अगर (!dev || dev->multअगरunction)
		वापस (fn + 1) % 8;

	वापस 0;
पूर्ण

अटल पूर्णांक only_one_child(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *bridge = bus->self;

	/*
	 * Systems with unusual topologies set PCI_SCAN_ALL_PCIE_DEVS so
	 * we scan क्रम all possible devices, not just Device 0.
	 */
	अगर (pci_has_flag(PCI_SCAN_ALL_PCIE_DEVS))
		वापस 0;

	/*
	 * A PCIe Downstream Port normally leads to a Link with only Device
	 * 0 on it (PCIe spec r3.1, sec 7.3.1).  As an optimization, scan
	 * only क्रम Device 0 in that situation.
	 */
	अगर (bridge && pci_is_pcie(bridge) && pcie_करोwnstream_port(bridge))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * pci_scan_slot - Scan a PCI slot on a bus क्रम devices
 * @bus: PCI bus to scan
 * @devfn: slot number to scan (must have zero function)
 *
 * Scan a PCI slot on the specअगरied PCI bus क्रम devices, adding
 * discovered devices to the @bus->devices list.  New devices
 * will not have is_added set.
 *
 * Returns the number of new devices found.
 */
पूर्णांक pci_scan_slot(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	अचिन्हित fn, nr = 0;
	काष्ठा pci_dev *dev;

	अगर (only_one_child(bus) && (devfn > 0))
		वापस 0; /* Alपढ़ोy scanned the entire slot */

	dev = pci_scan_single_device(bus, devfn);
	अगर (!dev)
		वापस 0;
	अगर (!pci_dev_is_added(dev))
		nr++;

	क्रम (fn = next_fn(bus, dev, 0); fn > 0; fn = next_fn(bus, dev, fn)) अणु
		dev = pci_scan_single_device(bus, devfn + fn);
		अगर (dev) अणु
			अगर (!pci_dev_is_added(dev))
				nr++;
			dev->multअगरunction = 1;
		पूर्ण
	पूर्ण

	/* Only one slot has PCIe device */
	अगर (bus->self && nr)
		pcie_aspm_init_link_state(bus->self);

	वापस nr;
पूर्ण
EXPORT_SYMBOL(pci_scan_slot);

अटल पूर्णांक pcie_find_smpss(काष्ठा pci_dev *dev, व्योम *data)
अणु
	u8 *smpss = data;

	अगर (!pci_is_pcie(dev))
		वापस 0;

	/*
	 * We करोn't have a way to change MPS settings on devices that have
	 * drivers attached.  A hot-added device might support only the minimum
	 * MPS setting (MPS=128).  Thereक्रमe, अगर the fabric contains a bridge
	 * where devices may be hot-added, we limit the fabric MPS to 128 so
	 * hot-added devices will work correctly.
	 *
	 * However, अगर we hot-add a device to a slot directly below a Root
	 * Port, it's impossible क्रम there to be other existing devices below
	 * the port.  We करोn't limit the MPS in this हाल because we can
	 * reconfigure MPS on both the Root Port and the hot-added device,
	 * and there are no other devices involved.
	 *
	 * Note that this PCIE_BUS_SAFE path assumes no peer-to-peer DMA.
	 */
	अगर (dev->is_hotplug_bridge &&
	    pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		*smpss = 0;

	अगर (*smpss > dev->pcie_mpss)
		*smpss = dev->pcie_mpss;

	वापस 0;
पूर्ण

अटल व्योम pcie_ग_लिखो_mps(काष्ठा pci_dev *dev, पूर्णांक mps)
अणु
	पूर्णांक rc;

	अगर (pcie_bus_config == PCIE_BUS_PERFORMANCE) अणु
		mps = 128 << dev->pcie_mpss;

		अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT &&
		    dev->bus->self)

			/*
			 * For "Performance", the assumption is made that
			 * करोwnstream communication will never be larger than
			 * the MRRS.  So, the MPS only needs to be configured
			 * क्रम the upstream communication.  This being the हाल,
			 * walk from the top करोwn and set the MPS of the child
			 * to that of the parent bus.
			 *
			 * Configure the device MPS with the smaller of the
			 * device MPSS or the bridge MPS (which is assumed to be
			 * properly configured at this poपूर्णांक to the largest
			 * allowable MPS based on its parent bus).
			 */
			mps = min(mps, pcie_get_mps(dev->bus->self));
	पूर्ण

	rc = pcie_set_mps(dev, mps);
	अगर (rc)
		pci_err(dev, "Failed attempting to set the MPS\n");
पूर्ण

अटल व्योम pcie_ग_लिखो_mrrs(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc, mrrs;

	/*
	 * In the "safe" हाल, करो not configure the MRRS.  There appear to be
	 * issues with setting MRRS to 0 on a number of devices.
	 */
	अगर (pcie_bus_config != PCIE_BUS_PERFORMANCE)
		वापस;

	/*
	 * For max perक्रमmance, the MRRS must be set to the largest supported
	 * value.  However, it cannot be configured larger than the MPS the
	 * device or the bus can support.  This should alपढ़ोy be properly
	 * configured by a prior call to pcie_ग_लिखो_mps().
	 */
	mrrs = pcie_get_mps(dev);

	/*
	 * MRRS is a R/W रेजिस्टर.  Invalid values can be written, but a
	 * subsequent पढ़ो will verअगरy अगर the value is acceptable or not.
	 * If the MRRS value provided is not acceptable (e.g., too large),
	 * shrink the value until it is acceptable to the HW.
	 */
	जबतक (mrrs != pcie_get_पढ़ोrq(dev) && mrrs >= 128) अणु
		rc = pcie_set_पढ़ोrq(dev, mrrs);
		अगर (!rc)
			अवरोध;

		pci_warn(dev, "Failed attempting to set the MRRS\n");
		mrrs /= 2;
	पूर्ण

	अगर (mrrs < 128)
		pci_err(dev, "MRRS was unable to be configured with a safe value.  If problems are experienced, try running with pci=pcie_bus_safe\n");
पूर्ण

अटल पूर्णांक pcie_bus_configure_set(काष्ठा pci_dev *dev, व्योम *data)
अणु
	पूर्णांक mps, orig_mps;

	अगर (!pci_is_pcie(dev))
		वापस 0;

	अगर (pcie_bus_config == PCIE_BUS_TUNE_OFF ||
	    pcie_bus_config == PCIE_BUS_DEFAULT)
		वापस 0;

	mps = 128 << *(u8 *)data;
	orig_mps = pcie_get_mps(dev);

	pcie_ग_लिखो_mps(dev, mps);
	pcie_ग_लिखो_mrrs(dev);

	pci_info(dev, "Max Payload Size set to %4d/%4d (was %4d), Max Read Rq %4d\n",
		 pcie_get_mps(dev), 128 << dev->pcie_mpss,
		 orig_mps, pcie_get_पढ़ोrq(dev));

	वापस 0;
पूर्ण

/*
 * pcie_bus_configure_settings() requires that pci_walk_bus work in a top-करोwn,
 * parents then children fashion.  If this changes, then this code will not
 * work as deचिन्हित.
 */
व्योम pcie_bus_configure_settings(काष्ठा pci_bus *bus)
अणु
	u8 smpss = 0;

	अगर (!bus->self)
		वापस;

	अगर (!pci_is_pcie(bus->self))
		वापस;

	/*
	 * FIXME - Peer to peer DMA is possible, though the endpoपूर्णांक would need
	 * to be aware of the MPS of the destination.  To work around this,
	 * simply क्रमce the MPS of the entire प्रणाली to the smallest possible.
	 */
	अगर (pcie_bus_config == PCIE_BUS_PEER2PEER)
		smpss = 0;

	अगर (pcie_bus_config == PCIE_BUS_SAFE) अणु
		smpss = bus->self->pcie_mpss;

		pcie_find_smpss(bus->self, &smpss);
		pci_walk_bus(bus, pcie_find_smpss, &smpss);
	पूर्ण

	pcie_bus_configure_set(bus->self, &smpss);
	pci_walk_bus(bus, pcie_bus_configure_set, &smpss);
पूर्ण
EXPORT_SYMBOL_GPL(pcie_bus_configure_settings);

/*
 * Called after each bus is probed, but beक्रमe its children are examined.  This
 * is marked as __weak because multiple architectures define it.
 */
व्योम __weak pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
       /* nothing to करो, expected to be हटाओd in the future */
पूर्ण

/**
 * pci_scan_child_bus_extend() - Scan devices below a bus
 * @bus: Bus to scan क्रम devices
 * @available_buses: Total number of buses available (%0 करोes not try to
 *		     extend beyond the minimal)
 *
 * Scans devices below @bus including subordinate buses. Returns new
 * subordinate number including all the found devices. Passing
 * @available_buses causes the reमुख्यing bus space to be distributed
 * equally between hotplug-capable bridges to allow future extension of the
 * hierarchy.
 */
अटल अचिन्हित पूर्णांक pci_scan_child_bus_extend(काष्ठा pci_bus *bus,
					      अचिन्हित पूर्णांक available_buses)
अणु
	अचिन्हित पूर्णांक used_buses, normal_bridges = 0, hotplug_bridges = 0;
	अचिन्हित पूर्णांक start = bus->busn_res.start;
	अचिन्हित पूर्णांक devfn, fn, cmax, max = start;
	काष्ठा pci_dev *dev;
	पूर्णांक nr_devs;

	dev_dbg(&bus->dev, "scanning bus\n");

	/* Go find them, Rover! */
	क्रम (devfn = 0; devfn < 256; devfn += 8) अणु
		nr_devs = pci_scan_slot(bus, devfn);

		/*
		 * The Jailhouse hypervisor may pass inभागidual functions of a
		 * multi-function device to a guest without passing function 0.
		 * Look क्रम them as well.
		 */
		अगर (jailhouse_paravirt() && nr_devs == 0) अणु
			क्रम (fn = 1; fn < 8; fn++) अणु
				dev = pci_scan_single_device(bus, devfn + fn);
				अगर (dev)
					dev->multअगरunction = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Reserve buses क्रम SR-IOV capability */
	used_buses = pci_iov_bus_range(bus);
	max += used_buses;

	/*
	 * After perक्रमming arch-dependent fixup of the bus, look behind
	 * all PCI-to-PCI bridges on this bus.
	 */
	अगर (!bus->is_added) अणु
		dev_dbg(&bus->dev, "fixups for bus\n");
		pcibios_fixup_bus(bus);
		bus->is_added = 1;
	पूर्ण

	/*
	 * Calculate how many hotplug bridges and normal bridges there
	 * are on this bus. We will distribute the additional available
	 * buses between hotplug bridges.
	 */
	क्रम_each_pci_bridge(dev, bus) अणु
		अगर (dev->is_hotplug_bridge)
			hotplug_bridges++;
		अन्यथा
			normal_bridges++;
	पूर्ण

	/*
	 * Scan bridges that are alपढ़ोy configured. We करोn't touch them
	 * unless they are misconfigured (which will be करोne in the second
	 * scan below).
	 */
	क्रम_each_pci_bridge(dev, bus) अणु
		cmax = max;
		max = pci_scan_bridge_extend(bus, dev, max, 0, 0);

		/*
		 * Reserve one bus क्रम each bridge now to aव्योम extending
		 * hotplug bridges too much during the second scan below.
		 */
		used_buses++;
		अगर (cmax - max > 1)
			used_buses += cmax - max - 1;
	पूर्ण

	/* Scan bridges that need to be reconfigured */
	क्रम_each_pci_bridge(dev, bus) अणु
		अचिन्हित पूर्णांक buses = 0;

		अगर (!hotplug_bridges && normal_bridges == 1) अणु

			/*
			 * There is only one bridge on the bus (upstream
			 * port) so it माला_लो all available buses which it
			 * can then distribute to the possible hotplug
			 * bridges below.
			 */
			buses = available_buses;
		पूर्ण अन्यथा अगर (dev->is_hotplug_bridge) अणु

			/*
			 * Distribute the extra buses between hotplug
			 * bridges अगर any.
			 */
			buses = available_buses / hotplug_bridges;
			buses = min(buses, available_buses - used_buses + 1);
		पूर्ण

		cmax = max;
		max = pci_scan_bridge_extend(bus, dev, cmax, buses, 1);
		/* One bus is alपढ़ोy accounted so करोn't add it again */
		अगर (max - cmax > 1)
			used_buses += max - cmax - 1;
	पूर्ण

	/*
	 * Make sure a hotplug bridge has at least the minimum requested
	 * number of buses but allow it to grow up to the maximum available
	 * bus number of there is room.
	 */
	अगर (bus->self && bus->self->is_hotplug_bridge) अणु
		used_buses = max_t(अचिन्हित पूर्णांक, available_buses,
				   pci_hotplug_bus_size - 1);
		अगर (max - start < used_buses) अणु
			max = start + used_buses;

			/* Do not allocate more buses than we have room left */
			अगर (max > bus->busn_res.end)
				max = bus->busn_res.end;

			dev_dbg(&bus->dev, "%pR extended by %#02x\n",
				&bus->busn_res, max - start);
		पूर्ण
	पूर्ण

	/*
	 * We've scanned the bus and so we know all about what's on
	 * the other side of any bridges that may be on this bus plus
	 * any devices.
	 *
	 * Return how far we've got finding sub-buses.
	 */
	dev_dbg(&bus->dev, "bus scan returning with max=%02x\n", max);
	वापस max;
पूर्ण

/**
 * pci_scan_child_bus() - Scan devices below a bus
 * @bus: Bus to scan क्रम devices
 *
 * Scans devices below @bus including subordinate buses. Returns new
 * subordinate number including all the found devices.
 */
अचिन्हित पूर्णांक pci_scan_child_bus(काष्ठा pci_bus *bus)
अणु
	वापस pci_scan_child_bus_extend(bus, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pci_scan_child_bus);

/**
 * pcibios_root_bridge_prepare - Platक्रमm-specअगरic host bridge setup
 * @bridge: Host bridge to set up
 *
 * Default empty implementation.  Replace with an architecture-specअगरic setup
 * routine, अगर necessary.
 */
पूर्णांक __weak pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	वापस 0;
पूर्ण

व्योम __weak pcibios_add_bus(काष्ठा pci_bus *bus)
अणु
पूर्ण

व्योम __weak pcibios_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
पूर्ण

काष्ठा pci_bus *pci_create_root_bus(काष्ठा device *parent, पूर्णांक bus,
		काष्ठा pci_ops *ops, व्योम *sysdata, काष्ठा list_head *resources)
अणु
	पूर्णांक error;
	काष्ठा pci_host_bridge *bridge;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस शून्य;

	bridge->dev.parent = parent;

	list_splice_init(resources, &bridge->winकरोws);
	bridge->sysdata = sysdata;
	bridge->busnr = bus;
	bridge->ops = ops;

	error = pci_रेजिस्टर_host_bridge(bridge);
	अगर (error < 0)
		जाओ err_out;

	वापस bridge->bus;

err_out:
	put_device(&bridge->dev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_create_root_bus);

पूर्णांक pci_host_probe(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_bus *bus, *child;
	पूर्णांक ret;

	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret < 0) अणु
		dev_err(bridge->dev.parent, "Scanning root bridge failed");
		वापस ret;
	पूर्ण

	bus = bridge->bus;

	/*
	 * We insert PCI resources पूर्णांकo the iomem_resource and
	 * ioport_resource trees in either pci_bus_claim_resources()
	 * or pci_bus_assign_resources().
	 */
	अगर (pci_has_flag(PCI_PROBE_ONLY)) अणु
		pci_bus_claim_resources(bus);
	पूर्ण अन्यथा अणु
		pci_bus_size_bridges(bus);
		pci_bus_assign_resources(bus);

		list_क्रम_each_entry(child, &bus->children, node)
			pcie_bus_configure_settings(child);
	पूर्ण

	pci_bus_add_devices(bus);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_host_probe);

पूर्णांक pci_bus_insert_busn_res(काष्ठा pci_bus *b, पूर्णांक bus, पूर्णांक bus_max)
अणु
	काष्ठा resource *res = &b->busn_res;
	काष्ठा resource *parent_res, *conflict;

	res->start = bus;
	res->end = bus_max;
	res->flags = IORESOURCE_BUS;

	अगर (!pci_is_root_bus(b))
		parent_res = &b->parent->busn_res;
	अन्यथा अणु
		parent_res = get_pci_करोमुख्य_busn_res(pci_करोमुख्य_nr(b));
		res->flags |= IORESOURCE_PCI_FIXED;
	पूर्ण

	conflict = request_resource_conflict(parent_res, res);

	अगर (conflict)
		dev_info(&b->dev,
			   "busn_res: can not insert %pR under %s%pR (conflicts with %s %pR)\n",
			    res, pci_is_root_bus(b) ? "domain " : "",
			    parent_res, conflict->name, conflict);

	वापस conflict == शून्य;
पूर्ण

पूर्णांक pci_bus_update_busn_res_end(काष्ठा pci_bus *b, पूर्णांक bus_max)
अणु
	काष्ठा resource *res = &b->busn_res;
	काष्ठा resource old_res = *res;
	resource_माप_प्रकार size;
	पूर्णांक ret;

	अगर (res->start > bus_max)
		वापस -EINVAL;

	size = bus_max - res->start + 1;
	ret = adjust_resource(res, res->start, size);
	dev_info(&b->dev, "busn_res: %pR end %s updated to %02x\n",
			&old_res, ret ? "can not be" : "is", bus_max);

	अगर (!ret && !res->parent)
		pci_bus_insert_busn_res(b, res->start, res->end);

	वापस ret;
पूर्ण

व्योम pci_bus_release_busn_res(काष्ठा pci_bus *b)
अणु
	काष्ठा resource *res = &b->busn_res;
	पूर्णांक ret;

	अगर (!res->flags || !res->parent)
		वापस;

	ret = release_resource(res);
	dev_info(&b->dev, "busn_res: %pR %s released\n",
			res, ret ? "can not be" : "is");
पूर्ण

पूर्णांक pci_scan_root_bus_bridge(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा resource_entry *winकरोw;
	bool found = false;
	काष्ठा pci_bus *b;
	पूर्णांक max, bus, ret;

	अगर (!bridge)
		वापस -EINVAL;

	resource_list_क्रम_each_entry(winकरोw, &bridge->winकरोws)
		अगर (winकरोw->res->flags & IORESOURCE_BUS) अणु
			bridge->busnr = winकरोw->res->start;
			found = true;
			अवरोध;
		पूर्ण

	ret = pci_रेजिस्टर_host_bridge(bridge);
	अगर (ret < 0)
		वापस ret;

	b = bridge->bus;
	bus = bridge->busnr;

	अगर (!found) अणु
		dev_info(&b->dev,
		 "No busn resource found for root bus, will use [bus %02x-ff]\n",
			bus);
		pci_bus_insert_busn_res(b, bus, 255);
	पूर्ण

	max = pci_scan_child_bus(b);

	अगर (!found)
		pci_bus_update_busn_res_end(b, max);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_scan_root_bus_bridge);

काष्ठा pci_bus *pci_scan_root_bus(काष्ठा device *parent, पूर्णांक bus,
		काष्ठा pci_ops *ops, व्योम *sysdata, काष्ठा list_head *resources)
अणु
	काष्ठा resource_entry *winकरोw;
	bool found = false;
	काष्ठा pci_bus *b;
	पूर्णांक max;

	resource_list_क्रम_each_entry(winकरोw, resources)
		अगर (winकरोw->res->flags & IORESOURCE_BUS) अणु
			found = true;
			अवरोध;
		पूर्ण

	b = pci_create_root_bus(parent, bus, ops, sysdata, resources);
	अगर (!b)
		वापस शून्य;

	अगर (!found) अणु
		dev_info(&b->dev,
		 "No busn resource found for root bus, will use [bus %02x-ff]\n",
			bus);
		pci_bus_insert_busn_res(b, bus, 255);
	पूर्ण

	max = pci_scan_child_bus(b);

	अगर (!found)
		pci_bus_update_busn_res_end(b, max);

	वापस b;
पूर्ण
EXPORT_SYMBOL(pci_scan_root_bus);

काष्ठा pci_bus *pci_scan_bus(पूर्णांक bus, काष्ठा pci_ops *ops,
					व्योम *sysdata)
अणु
	LIST_HEAD(resources);
	काष्ठा pci_bus *b;

	pci_add_resource(&resources, &ioport_resource);
	pci_add_resource(&resources, &iomem_resource);
	pci_add_resource(&resources, &busn_resource);
	b = pci_create_root_bus(शून्य, bus, ops, sysdata, &resources);
	अगर (b) अणु
		pci_scan_child_bus(b);
	पूर्ण अन्यथा अणु
		pci_मुक्त_resource_list(&resources);
	पूर्ण
	वापस b;
पूर्ण
EXPORT_SYMBOL(pci_scan_bus);

/**
 * pci_rescan_bus_bridge_resize - Scan a PCI bus क्रम devices
 * @bridge: PCI bridge क्रम the bus to scan
 *
 * Scan a PCI bus and child buses क्रम new devices, add them,
 * and enable them, resizing bridge mmio/io resource अगर necessary
 * and possible.  The caller must ensure the child devices are alपढ़ोy
 * हटाओd क्रम resizing to occur.
 *
 * Returns the max number of subordinate bus discovered.
 */
अचिन्हित पूर्णांक pci_rescan_bus_bridge_resize(काष्ठा pci_dev *bridge)
अणु
	अचिन्हित पूर्णांक max;
	काष्ठा pci_bus *bus = bridge->subordinate;

	max = pci_scan_child_bus(bus);

	pci_assign_unasचिन्हित_bridge_resources(bridge);

	pci_bus_add_devices(bus);

	वापस max;
पूर्ण

/**
 * pci_rescan_bus - Scan a PCI bus क्रम devices
 * @bus: PCI bus to scan
 *
 * Scan a PCI bus and child buses क्रम new devices, add them,
 * and enable them.
 *
 * Returns the max number of subordinate bus discovered.
 */
अचिन्हित पूर्णांक pci_rescan_bus(काष्ठा pci_bus *bus)
अणु
	अचिन्हित पूर्णांक max;

	max = pci_scan_child_bus(bus);
	pci_assign_unasचिन्हित_bus_resources(bus);
	pci_bus_add_devices(bus);

	वापस max;
पूर्ण
EXPORT_SYMBOL_GPL(pci_rescan_bus);

/*
 * pci_rescan_bus(), pci_rescan_bus_bridge_resize() and PCI device removal
 * routines should always be executed under this mutex.
 */
अटल DEFINE_MUTEX(pci_rescan_हटाओ_lock);

व्योम pci_lock_rescan_हटाओ(व्योम)
अणु
	mutex_lock(&pci_rescan_हटाओ_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_lock_rescan_हटाओ);

व्योम pci_unlock_rescan_हटाओ(व्योम)
अणु
	mutex_unlock(&pci_rescan_हटाओ_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_unlock_rescan_हटाओ);

अटल पूर्णांक __init pci_sort_bf_cmp(स्थिर काष्ठा device *d_a,
				  स्थिर काष्ठा device *d_b)
अणु
	स्थिर काष्ठा pci_dev *a = to_pci_dev(d_a);
	स्थिर काष्ठा pci_dev *b = to_pci_dev(d_b);

	अगर      (pci_करोमुख्य_nr(a->bus) < pci_करोमुख्य_nr(b->bus)) वापस -1;
	अन्यथा अगर (pci_करोमुख्य_nr(a->bus) > pci_करोमुख्य_nr(b->bus)) वापस  1;

	अगर      (a->bus->number < b->bus->number) वापस -1;
	अन्यथा अगर (a->bus->number > b->bus->number) वापस  1;

	अगर      (a->devfn < b->devfn) वापस -1;
	अन्यथा अगर (a->devfn > b->devfn) वापस  1;

	वापस 0;
पूर्ण

व्योम __init pci_sort_bपढ़ोthfirst(व्योम)
अणु
	bus_sort_bपढ़ोthfirst(&pci_bus_type, &pci_sort_bf_cmp);
पूर्ण

पूर्णांक pci_hp_add_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *parent = dev->bus;
	पूर्णांक busnr, start = parent->busn_res.start;
	अचिन्हित पूर्णांक available_buses = 0;
	पूर्णांक end = parent->busn_res.end;

	क्रम (busnr = start; busnr <= end; busnr++) अणु
		अगर (!pci_find_bus(pci_करोमुख्य_nr(parent), busnr))
			अवरोध;
	पूर्ण
	अगर (busnr-- > end) अणु
		pci_err(dev, "No bus number available for hot-added bridge\n");
		वापस -1;
	पूर्ण

	/* Scan bridges that are alपढ़ोy configured */
	busnr = pci_scan_bridge(parent, dev, busnr, 0);

	/*
	 * Distribute the available bus numbers between hotplug-capable
	 * bridges to make extending the chain later possible.
	 */
	available_buses = end - busnr;

	/* Scan bridges that need to be reconfigured */
	pci_scan_bridge_extend(parent, dev, busnr, available_buses, 1);

	अगर (!dev->subordinate)
		वापस -1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_hp_add_bridge);
