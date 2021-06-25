<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Port क्रम PPC64 David Engebretsen, IBM Corp.
 * Contains common pci routines क्रम ppc64 platक्रमm, pSeries and iSeries bअक्रमs.
 * 
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *   Rework, based on alpha PCI code.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/list.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/irq.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>

/* pci_io_base -- the base address from which io bars are offsets.
 * This is the lowest I/O base address (so bar values are always positive),
 * and it *must* be the start of ISA space अगर an ISA bus exists because
 * ISA drivers use hard coded offsets.  If no ISA bus exists nothing
 * is mapped on the first 64K of IO space
 */
अचिन्हित दीर्घ pci_io_base;
EXPORT_SYMBOL(pci_io_base);

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;

	prपूर्णांकk(KERN_INFO "PCI: Probing PCI hardware\n");

	/* For now, override phys_mem_access_prot. If we need it,g
	 * later, we may move that initialization to each ppc_md
	 */
	ppc_md.phys_mem_access_prot = pci_phys_mem_access_prot;

	/* On ppc64, we always enable PCI करोमुख्यs and we keep करोमुख्य 0
	 * backward compatible in /proc क्रम video cards
	 */
	pci_add_flags(PCI_ENABLE_PROC_DOMAINS | PCI_COMPAT_DOMAIN_0);

	/* Scan all of the recorded PCI controllers.  */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		pcibios_scan_phb(hose);

	/* Call common code to handle resource allocation */
	pcibios_resource_survey();

	/* Add devices. */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		pci_bus_add_devices(hose->bus);

	/* Call machine dependent fixup */
	अगर (ppc_md.pcibios_fixup)
		ppc_md.pcibios_fixup();

	prपूर्णांकk(KERN_DEBUG "PCI: Probing PCI hardware done\n");

	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);

पूर्णांक pcibios_unmap_io_space(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose;

	WARN_ON(bus == शून्य);

	/* If this is not a PHB, we only flush the hash table over
	 * the area mapped by this bridge. We करोn't play with the PTE
	 * mappings since we might have to deal with sub-page alignments
	 * so flushing the hash table is the only sane way to make sure
	 * that no hash entries are covering that हटाओd bridge area
	 * जबतक still allowing other busses overlapping those pages
	 *
	 * Note: If we ever support P2P hotplug on Book3E, we'll have
	 * to करो an appropriate TLB flush here too
	 */
	अगर (bus->self) अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
		काष्ठा resource *res = bus->resource[0];
#पूर्ण_अगर

		pr_debug("IO unmapping for PCI-PCI bridge %s\n",
			 pci_name(bus->self));

#अगर_घोषित CONFIG_PPC_BOOK3S_64
		__flush_hash_table_range(res->start + _IO_BASE,
					 res->end + _IO_BASE + 1);
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	/* Get the host bridge */
	hose = pci_bus_to_host(bus);

	pr_debug("IO unmapping for PHB %pOF\n", hose->dn);
	pr_debug("  alloc=0x%p\n", hose->io_base_alloc);

	iounmap(hose->io_base_alloc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_unmap_io_space);

व्योम __iomem *ioremap_phb(phys_addr_t paddr, अचिन्हित दीर्घ size)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ addr;

	WARN_ON_ONCE(paddr & ~PAGE_MASK);
	WARN_ON_ONCE(size & ~PAGE_MASK);

	/*
	 * Let's allocate some IO space for that guy. We don't pass VM_IOREMAP
	 * because we करोn't care about alignment tricks that the core करोes in
	 * that हाल.  Maybe we should due to stupid card with incomplete
	 * address decoding but I'd rather not deal with those outside of the
	 * reserved 64K legacy region.
	 */
	area = __get_vm_area_caller(size, 0, PHB_IO_BASE, PHB_IO_END,
				    __builtin_वापस_address(0));
	अगर (!area)
		वापस शून्य;

	addr = (अचिन्हित दीर्घ)area->addr;
	अगर (ioremap_page_range(addr, addr + size, paddr,
			pgprot_noncached(PAGE_KERNEL))) अणु
		vunmap_range(addr, addr + size);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)addr;
पूर्ण
EXPORT_SYMBOL_GPL(ioremap_phb);

अटल पूर्णांक pcibios_map_phb_io_space(काष्ठा pci_controller *hose)
अणु
	अचिन्हित दीर्घ phys_page;
	अचिन्हित दीर्घ size_page;
	अचिन्हित दीर्घ io_virt_offset;

	phys_page = ALIGN_DOWN(hose->io_base_phys, PAGE_SIZE);
	size_page = ALIGN(hose->pci_io_size, PAGE_SIZE);

	/* Make sure IO area address is clear */
	hose->io_base_alloc = शून्य;

	/* If there's no IO to map on that bus, get away too */
	अगर (hose->pci_io_size == 0 || hose->io_base_phys == 0)
		वापस 0;

	/* Let's allocate some IO space for that guy. We don't pass
	 * VM_IOREMAP because we करोn't care about alignment tricks that
	 * the core करोes in that हाल. Maybe we should due to stupid card
	 * with incomplete address decoding but I'd rather not deal with
	 * those outside of the reserved 64K legacy region.
	 */
	hose->io_base_alloc = ioremap_phb(phys_page, size_page);
	अगर (!hose->io_base_alloc)
		वापस -ENOMEM;
	hose->io_base_virt = hose->io_base_alloc +
				hose->io_base_phys - phys_page;

	pr_debug("IO mapping for PHB %pOF\n", hose->dn);
	pr_debug("  phys=0x%016llx, virt=0x%p (alloc=0x%p)\n",
		 hose->io_base_phys, hose->io_base_virt, hose->io_base_alloc);
	pr_debug("  size=0x%016llx (alloc=0x%016lx)\n",
		 hose->pci_io_size, size_page);

	/* Fixup hose IO resource */
	io_virt_offset = pcibios_io_space_offset(hose);
	hose->io_resource.start += io_virt_offset;
	hose->io_resource.end += io_virt_offset;

	pr_debug("  hose->io_resource=%pR\n", &hose->io_resource);

	वापस 0;
पूर्ण

पूर्णांक pcibios_map_io_space(काष्ठा pci_bus *bus)
अणु
	WARN_ON(bus == शून्य);

	/* If this not a PHB, nothing to करो, page tables still exist and
	 * thus HPTEs will be faulted in when needed
	 */
	अगर (bus->self) अणु
		pr_debug("IO mapping for PCI-PCI bridge %s\n",
			 pci_name(bus->self));
		pr_debug("  virt=0x%016llx...0x%016llx\n",
			 bus->resource[0]->start + _IO_BASE,
			 bus->resource[0]->end + _IO_BASE);
		वापस 0;
	पूर्ण

	वापस pcibios_map_phb_io_space(pci_bus_to_host(bus));
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_map_io_space);

व्योम pcibios_setup_phb_io_space(काष्ठा pci_controller *hose)
अणु
	pcibios_map_phb_io_space(hose);
पूर्ण

#घोषणा IOBASE_BRIDGE_NUMBER	0
#घोषणा IOBASE_MEMORY		1
#घोषणा IOBASE_IO		2
#घोषणा IOBASE_ISA_IO		3
#घोषणा IOBASE_ISA_MEM		4

SYSCALL_DEFINE3(pciconfig_iobase, दीर्घ, which, अचिन्हित दीर्घ, in_bus,
			  अचिन्हित दीर्घ, in_devfn)
अणु
	काष्ठा pci_controller* hose;
	काष्ठा pci_bus *पंचांगp_bus, *bus = शून्य;
	काष्ठा device_node *hose_node;

	/* Argh ! Please क्रमgive me क्रम that hack, but that's the
	 * simplest way to get existing XFree to not lockup on some
	 * G5 machines... So when something asks क्रम bus 0 io base
	 * (bus 0 is HT root), we वापस the AGP one instead.
	 */
	अगर (in_bus == 0 && of_machine_is_compatible("MacRISC4")) अणु
		काष्ठा device_node *agp;

		agp = of_find_compatible_node(शून्य, शून्य, "u3-agp");
		अगर (agp)
			in_bus = 0xf0;
		of_node_put(agp);
	पूर्ण

	/* That syscall isn't quite compatible with PCI domains, but it's
	 * used on pre-करोमुख्यs setup. We वापस the first match
	 */

	list_क्रम_each_entry(पंचांगp_bus, &pci_root_buses, node) अणु
		अगर (in_bus >= पंचांगp_bus->number &&
		    in_bus <= पंचांगp_bus->busn_res.end) अणु
			bus = पंचांगp_bus;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (bus == शून्य || bus->dev.of_node == शून्य)
		वापस -ENODEV;

	hose_node = bus->dev.of_node;
	hose = PCI_DN(hose_node)->phb;

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
		वापस -EINVAL;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_NUMA
पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(bus);
	वापस phb->node;
पूर्ण
EXPORT_SYMBOL(pcibus_to_node);
#पूर्ण_अगर
