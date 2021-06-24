<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common pmac/prep/chrp pci routines. -- Cort
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/memblock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/irq.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/machdep.h>

#अघोषित DEBUG

अचिन्हित दीर्घ isa_io_base     = 0;
अचिन्हित दीर्घ pci_dram_offset = 0;
पूर्णांक pcibios_assign_bus_offset = 1;
EXPORT_SYMBOL(isa_io_base);
EXPORT_SYMBOL(pci_dram_offset);

व्योम pcibios_make_OF_bus_map(व्योम);

अटल व्योम fixup_cpc710_pci64(काष्ठा pci_dev* dev);
अटल u8* pci_to_OF_bus_map;

/* By शेष, we करोn't re-assign bus numbers. We करो this only on
 * some pmacs
 */
अटल पूर्णांक pci_assign_all_buses;

अटल पूर्णांक pci_bus_count;

/* This will reमुख्य शून्य क्रम now, until isa-bridge.c is made common
 * to both 32-bit and 64-bit.
 */
काष्ठा pci_dev *isa_bridge_pcidev;
EXPORT_SYMBOL_GPL(isa_bridge_pcidev);

अटल व्योम
fixup_cpc710_pci64(काष्ठा pci_dev* dev)
अणु
	/* Hide the PCI64 BARs from the kernel as their content करोesn't
	 * fit well in the resource management
	 */
	dev->resource[0].start = dev->resource[0].end = 0;
	dev->resource[0].flags = 0;
	dev->resource[1].start = dev->resource[1].end = 0;
	dev->resource[1].flags = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_IBM,	PCI_DEVICE_ID_IBM_CPC710_PCI64,	fixup_cpc710_pci64);

/*
 * Functions below are used on OpenFirmware machines.
 */
अटल व्योम
make_one_node_map(काष्ठा device_node* node, u8 pci_bus)
अणु
	स्थिर पूर्णांक *bus_range;
	पूर्णांक len;

	अगर (pci_bus >= pci_bus_count)
		वापस;
	bus_range = of_get_property(node, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, "
		       "assuming it starts at 0\n", node);
		pci_to_OF_bus_map[pci_bus] = 0;
	पूर्ण अन्यथा
		pci_to_OF_bus_map[pci_bus] = bus_range[0];

	क्रम_each_child_of_node(node, node) अणु
		काष्ठा pci_dev* dev;
		स्थिर अचिन्हित पूर्णांक *class_code, *reg;
	
		class_code = of_get_property(node, "class-code", शून्य);
		अगर (!class_code || ((*class_code >> 8) != PCI_CLASS_BRIDGE_PCI &&
			(*class_code >> 8) != PCI_CLASS_BRIDGE_CARDBUS))
			जारी;
		reg = of_get_property(node, "reg", शून्य);
		अगर (!reg)
			जारी;
		dev = pci_get_करोमुख्य_bus_and_slot(0, pci_bus,
						  ((reg[0] >> 8) & 0xff));
		अगर (!dev || !dev->subordinate) अणु
			pci_dev_put(dev);
			जारी;
		पूर्ण
		make_one_node_map(node, dev->subordinate->number);
		pci_dev_put(dev);
	पूर्ण
पूर्ण
	
व्योम
pcibios_make_OF_bus_map(व्योम)
अणु
	पूर्णांक i;
	काष्ठा pci_controller *hose, *पंचांगp;
	काष्ठा property *map_prop;
	काष्ठा device_node *dn;

	pci_to_OF_bus_map = kदो_स्मृति(pci_bus_count, GFP_KERNEL);
	अगर (!pci_to_OF_bus_map) अणु
		prपूर्णांकk(KERN_ERR "Can't allocate OF bus map !\n");
		वापस;
	पूर्ण

	/* We fill the bus map with invalid values, that helps
	 * debugging.
	 */
	क्रम (i=0; i<pci_bus_count; i++)
		pci_to_OF_bus_map[i] = 0xff;

	/* For each hose, we begin searching bridges */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node) अणु
		काष्ठा device_node* node = hose->dn;

		अगर (!node)
			जारी;
		make_one_node_map(node, hose->first_busno);
	पूर्ण
	dn = of_find_node_by_path("/");
	map_prop = of_find_property(dn, "pci-OF-bus-map", शून्य);
	अगर (map_prop) अणु
		BUG_ON(pci_bus_count > map_prop->length);
		स_नकल(map_prop->value, pci_to_OF_bus_map, pci_bus_count);
	पूर्ण
	of_node_put(dn);
#अगर_घोषित DEBUG
	prपूर्णांकk("PCI->OF bus map:\n");
	क्रम (i=0; i<pci_bus_count; i++) अणु
		अगर (pci_to_OF_bus_map[i] == 0xff)
			जारी;
		prपूर्णांकk("%d -> %d\n", i, pci_to_OF_bus_map[i]);
	पूर्ण
#पूर्ण_अगर
पूर्ण


/*
 * Returns the PCI device matching a given OF node
 */
पूर्णांक pci_device_from_OF_node(काष्ठा device_node *node, u8 *bus, u8 *devfn)
अणु
	काष्ठा pci_dev *dev = शून्य;
	स्थिर __be32 *reg;
	पूर्णांक size;

	/* Check अगर it might have a chance to be a PCI device */
	अगर (!pci_find_hose_क्रम_OF_device(node))
		वापस -ENODEV;

	reg = of_get_property(node, "reg", &size);
	अगर (!reg || size < 5 * माप(u32))
		वापस -ENODEV;

	*bus = (be32_to_cpup(&reg[0]) >> 16) & 0xff;
	*devfn = (be32_to_cpup(&reg[0]) >> 8) & 0xff;

	/* Ok, here we need some tweak. If we have alपढ़ोy rक्रमागतbered
	 * all busses, we can't rely on the OF bus number any more.
	 * the pci_to_OF_bus_map is not enough as several PCI busses
	 * may match the same OF bus number.
	 */
	अगर (!pci_to_OF_bus_map)
		वापस 0;

	क्रम_each_pci_dev(dev)
		अगर (pci_to_OF_bus_map[dev->bus->number] == *bus &&
				dev->devfn == *devfn) अणु
			*bus = dev->bus->number;
			pci_dev_put(dev);
			वापस 0;
		पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(pci_device_from_OF_node);

/* We create the "pci-OF-bus-map" property now so it appears in the
 * /proc device tree
 */
व्योम __init
pci_create_OF_bus_map(व्योम)
अणु
	काष्ठा property* of_prop;
	काष्ठा device_node *dn;

	of_prop = memblock_alloc(माप(काष्ठा property) + 256,
				 SMP_CACHE_BYTES);
	अगर (!of_prop)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(काष्ठा property) + 256);
	dn = of_find_node_by_path("/");
	अगर (dn) अणु
		स_रखो(of_prop, -1, माप(काष्ठा property) + 256);
		of_prop->name = "pci-OF-bus-map";
		of_prop->length = 256;
		of_prop->value = &of_prop[1];
		of_add_property(dn, of_prop);
		of_node_put(dn);
	पूर्ण
पूर्ण

व्योम pcibios_setup_phb_io_space(काष्ठा pci_controller *hose)
अणु
	अचिन्हित दीर्घ io_offset;
	काष्ठा resource *res = &hose->io_resource;

	/* Fixup IO space offset */
	io_offset = pcibios_io_space_offset(hose);
	res->start += io_offset;
	res->end += io_offset;
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;
	पूर्णांक next_busno = 0;

	prपूर्णांकk(KERN_INFO "PCI: Probing PCI hardware\n");

	अगर (pci_has_flag(PCI_REASSIGN_ALL_BUS))
		pci_assign_all_buses = 1;

	/* Scan all of the recorded PCI controllers.  */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node) अणु
		अगर (pci_assign_all_buses)
			hose->first_busno = next_busno;
		hose->last_busno = 0xff;
		pcibios_scan_phb(hose);
		pci_bus_add_devices(hose->bus);
		अगर (pci_assign_all_buses || next_busno <= hose->last_busno)
			next_busno = hose->last_busno + pcibios_assign_bus_offset;
	पूर्ण
	pci_bus_count = next_busno;

	/* OpenFirmware based machines need a map of OF bus
	 * numbers vs. kernel bus numbers since we may have to
	 * remap them.
	 */
	अगर (pci_assign_all_buses)
		pcibios_make_OF_bus_map();

	/* Call common code to handle resource allocation */
	pcibios_resource_survey();

	/* Call machine dependent fixup */
	अगर (ppc_md.pcibios_fixup)
		ppc_md.pcibios_fixup();

	/* Call machine dependent post-init code */
	अगर (ppc_md.pcibios_after_init)
		ppc_md.pcibios_after_init();

	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);

अटल काष्ठा pci_controller*
pci_bus_to_hose(पूर्णांक bus)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;

	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		अगर (bus >= hose->first_busno && bus <= hose->last_busno)
			वापस hose;
	वापस शून्य;
पूर्ण

/* Provide inक्रमmation on locations of various I/O regions in physical
 * memory.  Do this on a per-card basis so that we choose the right
 * root bridge.
 * Note that the वापसed IO or memory base is a physical address
 */

SYSCALL_DEFINE3(pciconfig_iobase, दीर्घ, which,
		अचिन्हित दीर्घ, bus, अचिन्हित दीर्घ, devfn)
अणु
	काष्ठा pci_controller* hose;
	दीर्घ result = -EOPNOTSUPP;

	hose = pci_bus_to_hose(bus);
	अगर (!hose)
		वापस -ENODEV;

	चयन (which) अणु
	हाल IOBASE_BRIDGE_NUMBER:
		वापस (दीर्घ)hose->first_busno;
	हाल IOBASE_MEMORY:
		वापस (दीर्घ)hose->mem_offset[0];
	हाल IOBASE_IO:
		वापस (दीर्घ)hose->io_base_phys;
	हाल IOBASE_ISA_IO:
		वापस (दीर्घ)isa_io_base;
	हाल IOBASE_ISA_MEM:
		वापस (दीर्घ)isa_mem_base;
	पूर्ण

	वापस result;
पूर्ण
