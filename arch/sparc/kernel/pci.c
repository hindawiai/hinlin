<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci.c: UltraSparc PCI controller support.
 *
 * Copyright (C) 1997, 1998, 1999 David S. Miller (davem@redhat.com)
 * Copyright (C) 1998, 1999 Eddie C. Dost   (ecd@skynet.be)
 * Copyright (C) 1999 Jakub Jelinek   (jj@ultra.linux.cz)
 *
 * OF tree based PCI bus probing taken from the PowerPC port
 * with minor modअगरications, see there क्रम credits.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/apb.h>

#समावेश "pci_impl.h"
#समावेश "kernel.h"

/* List of all PCI controllers found in the प्रणाली. */
काष्ठा pci_pbm_info *pci_pbm_root = शून्य;

/* Each PBM found माला_लो a unique index. */
पूर्णांक pci_num_pbms = 0;

अस्थिर पूर्णांक pci_poke_in_progress;
अस्थिर पूर्णांक pci_poke_cpu = -1;
अस्थिर पूर्णांक pci_poke_faulted;

अटल DEFINE_SPINLOCK(pci_poke_lock);

व्योम pci_config_पढ़ो8(u8 *addr, u8 *ret)
अणु
	अचिन्हित दीर्घ flags;
	u8 byte;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "lduba [%1] %2, %0\n\t"
			     "membar #Sync"
			     : "=r" (byte)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	अगर (!pci_poke_faulted)
		*ret = byte;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

व्योम pci_config_पढ़ो16(u16 *addr, u16 *ret)
अणु
	अचिन्हित दीर्घ flags;
	u16 word;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "lduha [%1] %2, %0\n\t"
			     "membar #Sync"
			     : "=r" (word)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	अगर (!pci_poke_faulted)
		*ret = word;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

व्योम pci_config_पढ़ो32(u32 *addr, u32 *ret)
अणु
	अचिन्हित दीर्घ flags;
	u32 dword;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "lduwa [%1] %2, %0\n\t"
			     "membar #Sync"
			     : "=r" (dword)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	अगर (!pci_poke_faulted)
		*ret = dword;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

व्योम pci_config_ग_लिखो8(u8 *addr, u8 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "stba %0, [%1] %2\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (val), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

व्योम pci_config_ग_लिखो16(u16 *addr, u16 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "stha %0, [%1] %2\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (val), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

व्योम pci_config_ग_लिखो32(u32 *addr, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_poke_lock, flags);
	pci_poke_cpu = smp_processor_id();
	pci_poke_in_progress = 1;
	pci_poke_faulted = 0;
	__यंत्र__ __अस्थिर__("membar #Sync\n\t"
			     "stwa %0, [%1] %2\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (val), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	pci_poke_in_progress = 0;
	pci_poke_cpu = -1;
	spin_unlock_irqrestore(&pci_poke_lock, flags);
पूर्ण

अटल पूर्णांक ofpci_verbose;

अटल पूर्णांक __init ofpci_debug(अक्षर *str)
अणु
	पूर्णांक val = 0;

	get_option(&str, &val);
	अगर (val)
		ofpci_verbose = 1;
	वापस 1;
पूर्ण

__setup("ofpci_debug=", ofpci_debug);

अटल अचिन्हित दीर्घ pci_parse_of_flags(u32 addr0)
अणु
	अचिन्हित दीर्घ flags = 0;

	अगर (addr0 & 0x02000000) अणु
		flags = IORESOURCE_MEM | PCI_BASE_ADDRESS_SPACE_MEMORY;
		flags |= (addr0 >> 28) & PCI_BASE_ADDRESS_MEM_TYPE_1M;
		अगर (addr0 & 0x01000000)
			flags |= IORESOURCE_MEM_64
				 | PCI_BASE_ADDRESS_MEM_TYPE_64;
		अगर (addr0 & 0x40000000)
			flags |= IORESOURCE_PREFETCH
				 | PCI_BASE_ADDRESS_MEM_PREFETCH;
	पूर्ण अन्यथा अगर (addr0 & 0x01000000)
		flags = IORESOURCE_IO | PCI_BASE_ADDRESS_SPACE_IO;
	वापस flags;
पूर्ण

/* The of_device layer has translated all of the asचिन्हित-address properties
 * पूर्णांकo physical address resources, we only have to figure out the रेजिस्टर
 * mapping.
 */
अटल व्योम pci_parse_of_addrs(काष्ठा platक्रमm_device *op,
			       काष्ठा device_node *node,
			       काष्ठा pci_dev *dev)
अणु
	काष्ठा resource *op_res;
	स्थिर u32 *addrs;
	पूर्णांक proplen;

	addrs = of_get_property(node, "assigned-addresses", &proplen);
	अगर (!addrs)
		वापस;
	अगर (ofpci_verbose)
		pci_info(dev, "    parse addresses (%d bytes) @ %p\n",
			 proplen, addrs);
	op_res = &op->resource[0];
	क्रम (; proplen >= 20; proplen -= 20, addrs += 5, op_res++) अणु
		काष्ठा resource *res;
		अचिन्हित दीर्घ flags;
		पूर्णांक i;

		flags = pci_parse_of_flags(addrs[0]);
		अगर (!flags)
			जारी;
		i = addrs[0] & 0xff;
		अगर (ofpci_verbose)
			pci_info(dev, "  start: %llx, end: %llx, i: %x\n",
				 op_res->start, op_res->end, i);

		अगर (PCI_BASE_ADDRESS_0 <= i && i <= PCI_BASE_ADDRESS_5) अणु
			res = &dev->resource[(i - PCI_BASE_ADDRESS_0) >> 2];
		पूर्ण अन्यथा अगर (i == dev->rom_base_reg) अणु
			res = &dev->resource[PCI_ROM_RESOURCE];
			flags |= IORESOURCE_READONLY | IORESOURCE_SIZEALIGN;
		पूर्ण अन्यथा अणु
			pci_err(dev, "bad cfg reg num 0x%x\n", i);
			जारी;
		पूर्ण
		res->start = op_res->start;
		res->end = op_res->end;
		res->flags = flags;
		res->name = pci_name(dev);

		pci_info(dev, "reg 0x%x: %pR\n", i, res);
	पूर्ण
पूर्ण

अटल व्योम pci_init_dev_archdata(काष्ठा dev_archdata *sd, व्योम *iommu,
				  व्योम *stc, व्योम *host_controller,
				  काष्ठा platक्रमm_device  *op,
				  पूर्णांक numa_node)
अणु
	sd->iommu = iommu;
	sd->stc = stc;
	sd->host_controller = host_controller;
	sd->op = op;
	sd->numa_node = numa_node;
पूर्ण

अटल काष्ठा pci_dev *of_create_pci_dev(काष्ठा pci_pbm_info *pbm,
					 काष्ठा device_node *node,
					 काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	काष्ठा dev_archdata *sd;
	काष्ठा platक्रमm_device *op;
	काष्ठा pci_dev *dev;
	u32 class;

	dev = pci_alloc_dev(bus);
	अगर (!dev)
		वापस शून्य;

	op = of_find_device_by_node(node);
	sd = &dev->dev.archdata;
	pci_init_dev_archdata(sd, pbm->iommu, &pbm->stc, pbm, op,
			      pbm->numa_node);
	sd = &op->dev.archdata;
	sd->iommu = pbm->iommu;
	sd->stc = &pbm->stc;
	sd->numa_node = pbm->numa_node;

	अगर (of_node_name_eq(node, "ebus"))
		of_propagate_archdata(op);

	अगर (ofpci_verbose)
		pci_info(bus,"    create device, devfn: %x, type: %s\n",
			 devfn, of_node_get_device_type(node));

	dev->sysdata = node;
	dev->dev.parent = bus->bridge;
	dev->dev.bus = &pci_bus_type;
	dev->dev.of_node = of_node_get(node);
	dev->devfn = devfn;
	dev->multअगरunction = 0;		/* maybe a lie? */
	set_pcie_port_type(dev);

	pci_dev_assign_slot(dev);
	dev->venकरोr = of_getपूर्णांकprop_शेष(node, "vendor-id", 0xffff);
	dev->device = of_getपूर्णांकprop_शेष(node, "device-id", 0xffff);
	dev->subप्रणाली_venकरोr =
		of_getपूर्णांकprop_शेष(node, "subsystem-vendor-id", 0);
	dev->subप्रणाली_device =
		of_getपूर्णांकprop_शेष(node, "subsystem-id", 0);

	dev->cfg_size = pci_cfg_space_size(dev);

	/* We can't actually use the firmware value, we have
	 * to पढ़ो what is in the रेजिस्टर right now.  One
	 * reason is that in the हाल of IDE पूर्णांकerfaces the
	 * firmware can sample the value beक्रमe the the IDE
	 * पूर्णांकerface is programmed पूर्णांकo native mode.
	 */
	pci_पढ़ो_config_dword(dev, PCI_CLASS_REVISION, &class);
	dev->class = class >> 8;
	dev->revision = class & 0xff;

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_करोमुख्य_nr(bus),
		dev->bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn));

	/* I have seen IDE devices which will not respond to
	 * the bmdma simplex check पढ़ोs अगर bus mastering is
	 * disabled.
	 */
	अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE)
		pci_set_master(dev);

	dev->current_state = PCI_UNKNOWN;	/* unknown घातer state */
	dev->error_state = pci_channel_io_normal;
	dev->dma_mask = 0xffffffff;

	अगर (of_node_name_eq(node, "pci")) अणु
		/* a PCI-PCI bridge */
		dev->hdr_type = PCI_HEADER_TYPE_BRIDGE;
		dev->rom_base_reg = PCI_ROM_ADDRESS1;
	पूर्ण अन्यथा अगर (of_node_is_type(node, "cardbus")) अणु
		dev->hdr_type = PCI_HEADER_TYPE_CARDBUS;
	पूर्ण अन्यथा अणु
		dev->hdr_type = PCI_HEADER_TYPE_NORMAL;
		dev->rom_base_reg = PCI_ROM_ADDRESS;

		dev->irq = sd->op->archdata.irqs[0];
		अगर (dev->irq == 0xffffffff)
			dev->irq = PCI_IRQ_NONE;
	पूर्ण

	pci_info(dev, "[%04x:%04x] type %02x class %#08x\n",
		 dev->venकरोr, dev->device, dev->hdr_type, dev->class);

	pci_parse_of_addrs(sd->op, node, dev);

	अगर (ofpci_verbose)
		pci_info(dev, "    adding to system ...\n");

	pci_device_add(dev, bus);

	वापस dev;
पूर्ण

अटल व्योम apb_calc_first_last(u8 map, u32 *first_p, u32 *last_p)
अणु
	u32 idx, first, last;

	first = 8;
	last = 0;
	क्रम (idx = 0; idx < 8; idx++) अणु
		अगर ((map & (1 << idx)) != 0) अणु
			अगर (first > idx)
				first = idx;
			अगर (last < idx)
				last = idx;
		पूर्ण
	पूर्ण

	*first_p = first;
	*last_p = last;
पूर्ण

/* Cook up fake bus resources क्रम SUNW,simba PCI bridges which lack
 * a proper 'ranges' property.
 */
अटल व्योम apb_fake_ranges(काष्ठा pci_dev *dev,
			    काष्ठा pci_bus *bus,
			    काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;
	u32 first, last;
	u8 map;

	pci_पढ़ो_config_byte(dev, APB_IO_ADDRESS_MAP, &map);
	apb_calc_first_last(map, &first, &last);
	res = bus->resource[0];
	res->flags = IORESOURCE_IO;
	region.start = (first << 21);
	region.end = (last << 21) + ((1 << 21) - 1);
	pcibios_bus_to_resource(dev->bus, res, &region);

	pci_पढ़ो_config_byte(dev, APB_MEM_ADDRESS_MAP, &map);
	apb_calc_first_last(map, &first, &last);
	res = bus->resource[1];
	res->flags = IORESOURCE_MEM;
	region.start = (first << 29);
	region.end = (last << 29) + ((1 << 29) - 1);
	pcibios_bus_to_resource(dev->bus, res, &region);
पूर्ण

अटल व्योम pci_of_scan_bus(काष्ठा pci_pbm_info *pbm,
			    काष्ठा device_node *node,
			    काष्ठा pci_bus *bus);

#घोषणा GET_64BIT(prop, i)	((((u64) (prop)[(i)]) << 32) | (prop)[(i)+1])

अटल व्योम of_scan_pci_bridge(काष्ठा pci_pbm_info *pbm,
			       काष्ठा device_node *node,
			       काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus;
	स्थिर u32 *busrange, *ranges;
	पूर्णांक len, i, simba;
	काष्ठा pci_bus_region region;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक flags;
	u64 size;

	अगर (ofpci_verbose)
		pci_info(dev, "of_scan_pci_bridge(%pOF)\n", node);

	/* parse bus-range property */
	busrange = of_get_property(node, "bus-range", &len);
	अगर (busrange == शून्य || len != 8) अणु
		pci_info(dev, "Can't get bus-range for PCI-PCI bridge %pOF\n",
		       node);
		वापस;
	पूर्ण

	अगर (ofpci_verbose)
		pci_info(dev, "    Bridge bus range [%u --> %u]\n",
			 busrange[0], busrange[1]);

	ranges = of_get_property(node, "ranges", &len);
	simba = 0;
	अगर (ranges == शून्य) अणु
		स्थिर अक्षर *model = of_get_property(node, "model", शून्य);
		अगर (model && !म_भेद(model, "SUNW,simba"))
			simba = 1;
	पूर्ण

	bus = pci_add_new_bus(dev->bus, dev, busrange[0]);
	अगर (!bus) अणु
		pci_err(dev, "Failed to create pci bus for %pOF\n",
			node);
		वापस;
	पूर्ण

	bus->primary = dev->bus->number;
	pci_bus_insert_busn_res(bus, busrange[0], busrange[1]);
	bus->bridge_ctl = 0;

	अगर (ofpci_verbose)
		pci_info(dev, "    Bridge ranges[%p] simba[%d]\n",
			 ranges, simba);

	/* parse ranges property, or cook one up by hand क्रम Simba */
	/* PCI #address-cells == 3 and #size-cells == 2 always */
	res = &dev->resource[PCI_BRIDGE_RESOURCES];
	क्रम (i = 0; i < PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES; ++i) अणु
		res->flags = 0;
		bus->resource[i] = res;
		++res;
	पूर्ण
	अगर (simba) अणु
		apb_fake_ranges(dev, bus, pbm);
		जाओ after_ranges;
	पूर्ण अन्यथा अगर (ranges == शून्य) अणु
		pci_पढ़ो_bridge_bases(bus);
		जाओ after_ranges;
	पूर्ण
	i = 1;
	क्रम (; len >= 32; len -= 32, ranges += 8) अणु
		u64 start;

		अगर (ofpci_verbose)
			pci_info(dev, "    RAW Range[%08x:%08x:%08x:%08x:%08x:%08x:"
				 "%08x:%08x]\n",
				 ranges[0], ranges[1], ranges[2], ranges[3],
				 ranges[4], ranges[5], ranges[6], ranges[7]);

		flags = pci_parse_of_flags(ranges[0]);
		size = GET_64BIT(ranges, 6);
		अगर (flags == 0 || size == 0)
			जारी;

		/* On PCI-Express प्रणालीs, PCI bridges that have no devices करोwnstream
		 * have a bogus size value where the first 32-bit cell is 0xffffffff.
		 * This results in a bogus range where start + size overflows.
		 *
		 * Just skip these otherwise the kernel will complain when the resource
		 * tries to be claimed.
		 */
		अगर (size >> 32 == 0xffffffff)
			जारी;

		अगर (flags & IORESOURCE_IO) अणु
			res = bus->resource[0];
			अगर (res->flags) अणु
				pci_err(dev, "ignoring extra I/O range"
					" for bridge %pOF\n", node);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i >= PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES) अणु
				pci_err(dev, "too many memory ranges"
					" for bridge %pOF\n", node);
				जारी;
			पूर्ण
			res = bus->resource[i];
			++i;
		पूर्ण

		res->flags = flags;
		region.start = start = GET_64BIT(ranges, 1);
		region.end = region.start + size - 1;

		अगर (ofpci_verbose)
			pci_info(dev, "      Using flags[%08x] start[%016llx] size[%016llx]\n",
				 flags, start, size);

		pcibios_bus_to_resource(dev->bus, res, &region);
	पूर्ण
after_ranges:
	प्र_लिखो(bus->name, "PCI Bus %04x:%02x", pci_करोमुख्य_nr(bus),
		bus->number);
	अगर (ofpci_verbose)
		pci_info(dev, "    bus name: %s\n", bus->name);

	pci_of_scan_bus(pbm, node, bus);
पूर्ण

अटल व्योम pci_of_scan_bus(काष्ठा pci_pbm_info *pbm,
			    काष्ठा device_node *node,
			    काष्ठा pci_bus *bus)
अणु
	काष्ठा device_node *child;
	स्थिर u32 *reg;
	पूर्णांक reglen, devfn, prev_devfn;
	काष्ठा pci_dev *dev;

	अगर (ofpci_verbose)
		pci_info(bus, "scan_bus[%pOF] bus no %d\n",
			 node, bus->number);

	prev_devfn = -1;
	क्रम_each_child_of_node(node, child) अणु
		अगर (ofpci_verbose)
			pci_info(bus, "  * %pOF\n", child);
		reg = of_get_property(child, "reg", &reglen);
		अगर (reg == शून्य || reglen < 20)
			जारी;

		devfn = (reg[0] >> 8) & 0xff;

		/* This is a workaround क्रम some device trees
		 * which list PCI devices twice.  On the V100
		 * क्रम example, device number 3 is listed twice.
		 * Once as "pm" and once again as "lomp".
		 */
		अगर (devfn == prev_devfn)
			जारी;
		prev_devfn = devfn;

		/* create a new pci_dev क्रम this device */
		dev = of_create_pci_dev(pbm, child, bus, devfn);
		अगर (!dev)
			जारी;
		अगर (ofpci_verbose)
			pci_info(dev, "dev header type: %x\n", dev->hdr_type);

		अगर (pci_is_bridge(dev))
			of_scan_pci_bridge(pbm, child, dev);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
show_pciobppath_attr(काष्ठा device * dev, काष्ठा device_attribute * attr, अक्षर * buf)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा device_node *dp;

	pdev = to_pci_dev(dev);
	dp = pdev->dev.of_node;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pOF\n", dp);
पूर्ण

अटल DEVICE_ATTR(obppath, S_IRUSR | S_IRGRP | S_IROTH, show_pciobppath_attr, शून्य);

अटल व्योम pci_bus_रेजिस्टर_of_sysfs(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child_bus;
	पूर्णांक err;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		/* we करोn't really care अगर we can create this file or
		 * not, but we need to assign the result of the call
		 * or the world will fall under alien invasion and
		 * everybody will be frozen on a spaceship पढ़ोy to be
		 * eaten on alpha centauri by some green and jelly
		 * humanoid.
		 */
		err = sysfs_create_file(&dev->dev.kobj, &dev_attr_obppath.attr);
		(व्योम) err;
	पूर्ण
	list_क्रम_each_entry(child_bus, &bus->children, node)
		pci_bus_रेजिस्टर_of_sysfs(child_bus);
पूर्ण

अटल व्योम pci_claim_legacy_resources(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus_region region;
	काष्ठा resource *p, *root, *conflict;

	अगर ((dev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
		वापस;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस;

	p->name = "Video RAM area";
	p->flags = IORESOURCE_MEM | IORESOURCE_BUSY;

	region.start = 0xa0000UL;
	region.end = region.start + 0x1ffffUL;
	pcibios_bus_to_resource(dev->bus, p, &region);

	root = pci_find_parent_resource(dev, p);
	अगर (!root) अणु
		pci_info(dev, "can't claim VGA legacy %pR: no compatible bridge window\n", p);
		जाओ err;
	पूर्ण

	conflict = request_resource_conflict(root, p);
	अगर (conflict) अणु
		pci_info(dev, "can't claim VGA legacy %pR: address conflict with %s %pR\n",
			 p, conflict->name, conflict);
		जाओ err;
	पूर्ण

	pci_info(dev, "VGA legacy framebuffer %pR\n", p);
	वापस;

err:
	kमुक्त(p);
पूर्ण

अटल व्योम pci_claim_bus_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *child_bus;
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			काष्ठा resource *r = &dev->resource[i];

			अगर (r->parent || !r->start || !r->flags)
				जारी;

			अगर (ofpci_verbose)
				pci_info(dev, "Claiming Resource %d: %pR\n",
					 i, r);

			pci_claim_resource(dev, i);
		पूर्ण

		pci_claim_legacy_resources(dev);
	पूर्ण

	list_क्रम_each_entry(child_bus, &bus->children, node)
		pci_claim_bus_resources(child_bus);
पूर्ण

काष्ठा pci_bus *pci_scan_one_pbm(काष्ठा pci_pbm_info *pbm,
				 काष्ठा device *parent)
अणु
	LIST_HEAD(resources);
	काष्ठा device_node *node = pbm->op->dev.of_node;
	काष्ठा pci_bus *bus;

	prपूर्णांकk("PCI: Scanning PBM %pOF\n", node);

	pci_add_resource_offset(&resources, &pbm->io_space,
				pbm->io_offset);
	pci_add_resource_offset(&resources, &pbm->mem_space,
				pbm->mem_offset);
	अगर (pbm->mem64_space.flags)
		pci_add_resource_offset(&resources, &pbm->mem64_space,
					pbm->mem64_offset);
	pbm->busn.start = pbm->pci_first_busno;
	pbm->busn.end	= pbm->pci_last_busno;
	pbm->busn.flags	= IORESOURCE_BUS;
	pci_add_resource(&resources, &pbm->busn);
	bus = pci_create_root_bus(parent, pbm->pci_first_busno, pbm->pci_ops,
				  pbm, &resources);
	अगर (!bus) अणु
		prपूर्णांकk(KERN_ERR "Failed to create bus for %pOF\n", node);
		pci_मुक्त_resource_list(&resources);
		वापस शून्य;
	पूर्ण

	pci_of_scan_bus(pbm, node, bus);
	pci_bus_रेजिस्टर_of_sysfs(bus);

	pci_claim_bus_resources(bus);

	pci_bus_add_devices(bus);
	वापस bus;
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	u16 cmd, oldcmd;
	पूर्णांक i;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	oldcmd = cmd;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *res = &dev->resource[i];

		/* Only set up the requested stuff */
		अगर (!(mask & (1<<i)))
			जारी;

		अगर (res->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		अगर (res->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	पूर्ण

	अगर (cmd != oldcmd) अणु
		pci_info(dev, "enabling device (%04x -> %04x)\n", oldcmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण

/* Platक्रमm support क्रम /proc/bus/pci/X/Y mmap()s. */

/* If the user uses a host-bridge as the PCI device, he may use
 * this to perक्रमm a raw mmap() of the I/O or MEM space behind
 * that controller.
 *
 * This can be useful क्रम execution of x86 PCI bios initialization code
 * on a PCI card, like the xमुक्त86 पूर्णांक10 stuff करोes.
 */
अटल पूर्णांक __pci_mmap_make_offset_bus(काष्ठा pci_dev *pdev, काष्ठा vm_area_काष्ठा *vma,
				      क्रमागत pci_mmap_state mmap_state)
अणु
	काष्ठा pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	अचिन्हित दीर्घ space_size, user_offset, user_size;

	अगर (mmap_state == pci_mmap_io) अणु
		space_size = resource_size(&pbm->io_space);
	पूर्ण अन्यथा अणु
		space_size = resource_size(&pbm->mem_space);
	पूर्ण

	/* Make sure the request is in range. */
	user_offset = vma->vm_pgoff << PAGE_SHIFT;
	user_size = vma->vm_end - vma->vm_start;

	अगर (user_offset >= space_size ||
	    (user_offset + user_size) > space_size)
		वापस -EINVAL;

	अगर (mmap_state == pci_mmap_io) अणु
		vma->vm_pgoff = (pbm->io_space.start +
				 user_offset) >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		vma->vm_pgoff = (pbm->mem_space.start +
				 user_offset) >> PAGE_SHIFT;
	पूर्ण

	वापस 0;
पूर्ण

/* Adjust vm_pgoff of VMA such that it is the physical page offset
 * corresponding to the 32-bit pci bus offset क्रम DEV requested by the user.
 *
 * Basically, the user finds the base address क्रम his device which he wishes
 * to mmap.  They पढ़ो the 32-bit value from the config space base रेजिस्टर,
 * add whatever PAGE_SIZE multiple offset they wish, and feed this पूर्णांकo the
 * offset parameter of mmap on /proc/bus/pci/XXX क्रम that device.
 *
 * Returns negative error code on failure, zero on success.
 */
अटल पूर्णांक __pci_mmap_make_offset(काष्ठा pci_dev *pdev,
				  काष्ठा vm_area_काष्ठा *vma,
				  क्रमागत pci_mmap_state mmap_state)
अणु
	अचिन्हित दीर्घ user_paddr, user_size;
	पूर्णांक i, err;

	/* First compute the physical address in vma->vm_pgoff,
	 * making sure the user offset is within range in the
	 * appropriate PCI space.
	 */
	err = __pci_mmap_make_offset_bus(pdev, vma, mmap_state);
	अगर (err)
		वापस err;

	/* If this is a mapping on a host bridge, any address
	 * is OK.
	 */
	अगर ((pdev->class >> 8) == PCI_CLASS_BRIDGE_HOST)
		वापस err;

	/* Otherwise make sure it's in the range क्रम one of the
	 * device's resources.
	 */
	user_paddr = vma->vm_pgoff << PAGE_SHIFT;
	user_size = vma->vm_end - vma->vm_start;

	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
		काष्ठा resource *rp = &pdev->resource[i];
		resource_माप_प्रकार aligned_end;

		/* Active? */
		अगर (!rp->flags)
			जारी;

		/* Same type? */
		अगर (i == PCI_ROM_RESOURCE) अणु
			अगर (mmap_state != pci_mmap_mem)
				जारी;
		पूर्ण अन्यथा अणु
			अगर ((mmap_state == pci_mmap_io &&
			     (rp->flags & IORESOURCE_IO) == 0) ||
			    (mmap_state == pci_mmap_mem &&
			     (rp->flags & IORESOURCE_MEM) == 0))
				जारी;
		पूर्ण

		/* Align the resource end to the next page address.
		 * PAGE_SIZE पूर्णांकentionally added instead of (PAGE_SIZE - 1),
		 * because actually we need the address of the next byte
		 * after rp->end.
		 */
		aligned_end = (rp->end + PAGE_SIZE) & PAGE_MASK;

		अगर ((rp->start <= user_paddr) &&
		    (user_paddr + user_size) <= aligned_end)
			अवरोध;
	पूर्ण

	अगर (i > PCI_ROM_RESOURCE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Set vm_page_prot of VMA, as appropriate क्रम this architecture, क्रम a pci
 * device mapping.
 */
अटल व्योम __pci_mmap_set_pgprot(काष्ठा pci_dev *dev, काष्ठा vm_area_काष्ठा *vma,
					     क्रमागत pci_mmap_state mmap_state)
अणु
	/* Our io_remap_pfn_range takes care of this, करो nothing.  */
पूर्ण

/* Perक्रमm the actual remap of the pages क्रम a PCI device mapping, as appropriate
 * क्रम this architecture.  The region in the process to map is described by vm_start
 * and vm_end members of VMA, the base physical address is found in vm_pgoff.
 * The pci device काष्ठाure is provided so that architectures may make mapping
 * decisions on a per-device or per-bus basis.
 *
 * Returns a negative error code on failure, zero on success.
 */
पूर्णांक pci_mmap_page_range(काष्ठा pci_dev *dev, पूर्णांक bar,
			काष्ठा vm_area_काष्ठा *vma,
			क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine)
अणु
	पूर्णांक ret;

	ret = __pci_mmap_make_offset(dev, vma, mmap_state);
	अगर (ret < 0)
		वापस ret;

	__pci_mmap_set_pgprot(dev, vma, mmap_state);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	ret = io_remap_pfn_range(vma, vma->vm_start,
				 vma->vm_pgoff,
				 vma->vm_end - vma->vm_start,
				 vma->vm_page_prot);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NUMA
पूर्णांक pcibus_to_node(काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_pbm_info *pbm = pbus->sysdata;

	वापस pbm->numa_node;
पूर्ण
EXPORT_SYMBOL(pcibus_to_node);
#पूर्ण_अगर

/* Return the करोमुख्य number क्रम this pci bus */

पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_pbm_info *pbm = pbus->sysdata;
	पूर्णांक ret;

	अगर (!pbm) अणु
		ret = -ENXIO;
	पूर्ण अन्यथा अणु
		ret = pbm->index;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pci_करोमुख्य_nr);

#अगर_घोषित CONFIG_PCI_MSI
पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *pdev, काष्ठा msi_desc *desc)
अणु
	काष्ठा pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	अचिन्हित पूर्णांक irq;

	अगर (!pbm->setup_msi_irq)
		वापस -EINVAL;

	वापस pbm->setup_msi_irq(&irq, pdev, desc);
पूर्ण

व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा msi_desc *entry = irq_get_msi_desc(irq);
	काष्ठा pci_dev *pdev = msi_desc_to_pci_dev(entry);
	काष्ठा pci_pbm_info *pbm = pdev->dev.archdata.host_controller;

	अगर (pbm->tearकरोwn_msi_irq)
		pbm->tearकरोwn_msi_irq(irq, pdev);
पूर्ण
#पूर्ण_अगर /* !(CONFIG_PCI_MSI) */

/* ALI sound chips generate 31-bits of DMA, a special रेजिस्टर
 * determines what bit 31 is emitted as.
 */
पूर्णांक ali_sound_dma_hack(काष्ठा device *dev, u64 device_mask)
अणु
	काष्ठा iommu *iommu = dev->archdata.iommu;
	काष्ठा pci_dev *ali_isa_bridge;
	u8 val;

	अगर (!dev_is_pci(dev))
		वापस 0;

	अगर (to_pci_dev(dev)->venकरोr != PCI_VENDOR_ID_AL ||
	    to_pci_dev(dev)->device != PCI_DEVICE_ID_AL_M5451 ||
	    device_mask != 0x7fffffff)
		वापस 0;

	ali_isa_bridge = pci_get_device(PCI_VENDOR_ID_AL,
					 PCI_DEVICE_ID_AL_M1533,
					 शून्य);

	pci_पढ़ो_config_byte(ali_isa_bridge, 0x7e, &val);
	अगर (iommu->dma_addr_mask & 0x80000000)
		val |= 0x01;
	अन्यथा
		val &= ~0x01;
	pci_ग_लिखो_config_byte(ali_isa_bridge, 0x7e, val);
	pci_dev_put(ali_isa_bridge);
	वापस 1;
पूर्ण

व्योम pci_resource_to_user(स्थिर काष्ठा pci_dev *pdev, पूर्णांक bar,
			  स्थिर काष्ठा resource *rp, resource_माप_प्रकार *start,
			  resource_माप_प्रकार *end)
अणु
	काष्ठा pci_bus_region region;

	/*
	 * "User" addresses are shown in /sys/devices/pci.../.../resource
	 * and /proc/bus/pci/devices and used as mmap offsets क्रम
	 * /proc/bus/pci/BB/DD.F files (see proc_bus_pci_mmap()).
	 *
	 * On sparc, these are PCI bus addresses, i.e., raw BAR values.
	 */
	pcibios_resource_to_bus(pdev->bus, &region, (काष्ठा resource *) rp);
	*start = region.start;
	*end = region.end;
पूर्ण

व्योम pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	/* No special bus mastering setup handling */
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
पूर्णांक pcibios_add_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *pdev;

	/* Add sriov arch specअगरic initialization here.
	 * Copy dev_archdata from PF to VF
	 */
	अगर (dev->is_virtfn) अणु
		काष्ठा dev_archdata *psd;

		pdev = dev->physfn;
		psd = &pdev->dev.archdata;
		pci_init_dev_archdata(&dev->dev.archdata, psd->iommu,
				      psd->stc, psd->host_controller, शून्य,
				      psd->numa_node);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	pci_dfl_cache_line_size = 64 >> 2;
	वापस 0;
पूर्ण
subsys_initcall(pcibios_init);

#अगर_घोषित CONFIG_SYSFS

#घोषणा SLOT_NAME_SIZE  11  /* Max decimal digits + null in u32 */

अटल व्योम pcie_bus_slot_names(काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_bus *bus;

	list_क्रम_each_entry(pdev, &pbus->devices, bus_list) अणु
		अक्षर name[SLOT_NAME_SIZE];
		काष्ठा pci_slot *pci_slot;
		स्थिर u32 *slot_num;
		पूर्णांक len;

		slot_num = of_get_property(pdev->dev.of_node,
					   "physical-slot#", &len);

		अगर (slot_num == शून्य || len != 4)
			जारी;

		snम_लिखो(name, माप(name), "%u", slot_num[0]);
		pci_slot = pci_create_slot(pbus, slot_num[0], name, शून्य);

		अगर (IS_ERR(pci_slot))
			pr_err("PCI: pci_create_slot returned %ld.\n",
			       PTR_ERR(pci_slot));
	पूर्ण

	list_क्रम_each_entry(bus, &pbus->children, node)
		pcie_bus_slot_names(bus);
पूर्ण

अटल व्योम pci_bus_slot_names(काष्ठा device_node *node, काष्ठा pci_bus *bus)
अणु
	स्थिर काष्ठा pci_slot_names अणु
		u32	slot_mask;
		अक्षर	names[0];
	पूर्ण *prop;
	स्थिर अक्षर *sp;
	पूर्णांक len, i;
	u32 mask;

	prop = of_get_property(node, "slot-names", &len);
	अगर (!prop)
		वापस;

	mask = prop->slot_mask;
	sp = prop->names;

	अगर (ofpci_verbose)
		pci_info(bus, "Making slots for [%pOF] mask[0x%02x]\n",
			 node, mask);

	i = 0;
	जबतक (mask) अणु
		काष्ठा pci_slot *pci_slot;
		u32 this_bit = 1 << i;

		अगर (!(mask & this_bit)) अणु
			i++;
			जारी;
		पूर्ण

		अगर (ofpci_verbose)
			pci_info(bus, "Making slot [%s]\n", sp);

		pci_slot = pci_create_slot(bus, i, sp, शून्य);
		अगर (IS_ERR(pci_slot))
			pci_err(bus, "pci_create_slot returned %ld\n",
				PTR_ERR(pci_slot));

		sp += म_माप(sp) + 1;
		mask &= ~this_bit;
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक __init of_pci_slot_init(व्योम)
अणु
	काष्ठा pci_bus *pbus = शून्य;

	जबतक ((pbus = pci_find_next_bus(pbus)) != शून्य) अणु
		काष्ठा device_node *node;
		काष्ठा pci_dev *pdev;

		pdev = list_first_entry(&pbus->devices, काष्ठा pci_dev,
					bus_list);

		अगर (pdev && pci_is_pcie(pdev)) अणु
			pcie_bus_slot_names(pbus);
		पूर्ण अन्यथा अणु

			अगर (pbus->self) अणु

				/* PCI->PCI bridge */
				node = pbus->self->dev.of_node;

			पूर्ण अन्यथा अणु
				काष्ठा pci_pbm_info *pbm = pbus->sysdata;

				/* Host PCI controller */
				node = pbm->op->dev.of_node;
			पूर्ण

			pci_bus_slot_names(node, pbus);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(of_pci_slot_init);
#पूर्ण_अगर
