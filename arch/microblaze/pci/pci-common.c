<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Contains common pci routines क्रम ALL ppc platक्रमm
 * (based on pci_32.c and pci_64.c)
 *
 * Port क्रम PPC64 David Engebretsen, IBM Corp.
 * Contains common pci routines क्रम ppc64 platक्रमm, pSeries and iSeries bअक्रमs.
 *
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *   Rework, based on alpha PCI code.
 *
 * Common pmac/prep/chrp pci routines. -- Cort
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/list.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/irq.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/processor.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/byteorder.h>

अटल DEFINE_SPINLOCK(hose_spinlock);
LIST_HEAD(hose_list);

/* XXX समाप्त that some day ... */
अटल पूर्णांक global_phb_number;		/* Global phb counter */

/* ISA Memory physical address */
resource_माप_प्रकार isa_mem_base;

अचिन्हित दीर्घ isa_io_base;
EXPORT_SYMBOL(isa_io_base);

अटल पूर्णांक pci_bus_count;

काष्ठा pci_controller *pcibios_alloc_controller(काष्ठा device_node *dev)
अणु
	काष्ठा pci_controller *phb;

	phb = zalloc_maybe_booपंचांगem(माप(काष्ठा pci_controller), GFP_KERNEL);
	अगर (!phb)
		वापस शून्य;
	spin_lock(&hose_spinlock);
	phb->global_number = global_phb_number++;
	list_add_tail(&phb->list_node, &hose_list);
	spin_unlock(&hose_spinlock);
	phb->dn = dev;
	phb->is_dynamic = mem_init_करोne;
	वापस phb;
पूर्ण

व्योम pcibios_मुक्त_controller(काष्ठा pci_controller *phb)
अणु
	spin_lock(&hose_spinlock);
	list_del(&phb->list_node);
	spin_unlock(&hose_spinlock);

	अगर (phb->is_dynamic)
		kमुक्त(phb);
पूर्ण

अटल resource_माप_प्रकार pcibios_io_size(स्थिर काष्ठा pci_controller *hose)
अणु
	वापस resource_size(&hose->io_resource);
पूर्ण

पूर्णांक pcibios_vaddr_is_ioport(व्योम __iomem *address)
अणु
	पूर्णांक ret = 0;
	काष्ठा pci_controller *hose;
	resource_माप_प्रकार size;

	spin_lock(&hose_spinlock);
	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		size = pcibios_io_size(hose);
		अगर (address >= hose->io_base_virt &&
		    address < (hose->io_base_virt + size)) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&hose_spinlock);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ pci_address_to_pio(phys_addr_t address)
अणु
	काष्ठा pci_controller *hose;
	resource_माप_प्रकार size;
	अचिन्हित दीर्घ ret = ~0;

	spin_lock(&hose_spinlock);
	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		size = pcibios_io_size(hose);
		अगर (address >= hose->io_base_phys &&
		    address < (hose->io_base_phys + size)) अणु
			अचिन्हित दीर्घ base =
				(अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
			ret = base + (address - hose->io_base_phys);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&hose_spinlock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_address_to_pio);

/* This routine is meant to be used early during boot, when the
 * PCI bus numbers have not yet been asचिन्हित, and you need to
 * issue PCI config cycles to an OF device.
 * It could also be used to "fix" RTAS config cycles अगर you want
 * to set pci_assign_all_buses to 1 and still use RTAS क्रम PCI
 * config cycles.
 */
काष्ठा pci_controller *pci_find_hose_क्रम_OF_device(काष्ठा device_node *node)
अणु
	जबतक (node) अणु
		काष्ठा pci_controller *hose, *पंचांगp;
		list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
			अगर (hose->dn == node)
				वापस hose;
		node = node->parent;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	/* No special bus mastering setup handling */
पूर्ण

/*
 * Platक्रमm support क्रम /proc/bus/pci/X/Y mmap()s.
 */

पूर्णांक pci_iobar_pfn(काष्ठा pci_dev *pdev, पूर्णांक bar, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);
	resource_माप_प्रकार ioaddr = pci_resource_start(pdev, bar);

	अगर (!hose)
		वापस -EINVAL;		/* should never happen */

	/* Convert to an offset within this PCI controller */
	ioaddr -= (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;

	vma->vm_pgoff += (ioaddr + hose->io_base_phys) >> PAGE_SHIFT;
	वापस 0;
पूर्ण

/*
 * This one is used by /dev/mem and fbdev who have no clue about the
 * PCI device, it tries to find the PCI device first and calls the
 * above routine
 */
pgprot_t pci_phys_mem_access_prot(काष्ठा file *file,
				  अचिन्हित दीर्घ pfn,
				  अचिन्हित दीर्घ size,
				  pgprot_t prot)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा resource *found = शून्य;
	resource_माप_प्रकार offset = ((resource_माप_प्रकार)pfn) << PAGE_SHIFT;
	पूर्णांक i;

	अगर (page_is_ram(pfn))
		वापस prot;

	prot = pgprot_noncached(prot);
	क्रम_each_pci_dev(pdev) अणु
		क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
			काष्ठा resource *rp = &pdev->resource[i];
			पूर्णांक flags = rp->flags;

			/* Active and same type? */
			अगर ((flags & IORESOURCE_MEM) == 0)
				जारी;
			/* In the range of this resource? */
			अगर (offset < (rp->start & PAGE_MASK) ||
			    offset > rp->end)
				जारी;
			found = rp;
			अवरोध;
		पूर्ण
		अगर (found)
			अवरोध;
	पूर्ण
	अगर (found) अणु
		अगर (found->flags & IORESOURCE_PREFETCH)
			prot = pgprot_noncached_wc(prot);
		pci_dev_put(pdev);
	पूर्ण

	pr_debug("PCI: Non-PCI map for %llx, prot: %lx\n",
		 (अचिन्हित दीर्घ दीर्घ)offset, pgprot_val(prot));

	वापस prot;
पूर्ण

/* This provides legacy IO पढ़ो access on a bus */
पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, loff_t port, u32 *val, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा resource *rp = &hose->io_resource;
	व्योम __iomem *addr;

	/* Check अगर port can be supported by that bus. We only check
	 * the ranges of the PHB though, not the bus itself as the rules
	 * क्रम क्रमwarding legacy cycles करोwn bridges are not our problem
	 * here. So अगर the host bridge supports it, we करो it.
	 */
	offset = (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
	offset += port;

	अगर (!(rp->flags & IORESOURCE_IO))
		वापस -ENXIO;
	अगर (offset < rp->start || (offset + size) > rp->end)
		वापस -ENXIO;
	addr = hose->io_base_virt + port;

	चयन (size) अणु
	हाल 1:
		*((u8 *)val) = in_8(addr);
		वापस 1;
	हाल 2:
		अगर (port & 1)
			वापस -EINVAL;
		*((u16 *)val) = in_le16(addr);
		वापस 2;
	हाल 4:
		अगर (port & 3)
			वापस -EINVAL;
		*((u32 *)val) = in_le32(addr);
		वापस 4;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* This provides legacy IO ग_लिखो access on a bus */
पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, loff_t port, u32 val, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा resource *rp = &hose->io_resource;
	व्योम __iomem *addr;

	/* Check अगर port can be supported by that bus. We only check
	 * the ranges of the PHB though, not the bus itself as the rules
	 * क्रम क्रमwarding legacy cycles करोwn bridges are not our problem
	 * here. So अगर the host bridge supports it, we करो it.
	 */
	offset = (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
	offset += port;

	अगर (!(rp->flags & IORESOURCE_IO))
		वापस -ENXIO;
	अगर (offset < rp->start || (offset + size) > rp->end)
		वापस -ENXIO;
	addr = hose->io_base_virt + port;

	/* WARNING: The generic code is idiotic. It माला_लो passed a poपूर्णांकer
	 * to what can be a 1, 2 or 4 byte quantity and always पढ़ोs that
	 * as a u32, which means that we have to correct the location of
	 * the data पढ़ो within those 32 bits क्रम size 1 and 2
	 */
	चयन (size) अणु
	हाल 1:
		out_8(addr, val >> 24);
		वापस 1;
	हाल 2:
		अगर (port & 1)
			वापस -EINVAL;
		out_le16(addr, val >> 16);
		वापस 2;
	हाल 4:
		अगर (port & 3)
			वापस -EINVAL;
		out_le32(addr, val);
		वापस 4;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* This provides legacy IO or memory mmap access on a bus */
पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus,
			       काष्ठा vm_area_काष्ठा *vma,
			       क्रमागत pci_mmap_state mmap_state)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	resource_माप_प्रकार offset =
		((resource_माप_प्रकार)vma->vm_pgoff) << PAGE_SHIFT;
	resource_माप_प्रकार size = vma->vm_end - vma->vm_start;
	काष्ठा resource *rp;

	pr_debug("pci_mmap_legacy_page_range(%04x:%02x, %s @%llx..%llx)\n",
		 pci_करोमुख्य_nr(bus), bus->number,
		 mmap_state == pci_mmap_mem ? "MEM" : "IO",
		 (अचिन्हित दीर्घ दीर्घ)offset,
		 (अचिन्हित दीर्घ दीर्घ)(offset + size - 1));

	अगर (mmap_state == pci_mmap_mem) अणु
		/* Hack alert !
		 *
		 * Because X is lame and can fail starting अगर it माला_लो an error
		 * trying to mmap legacy_mem (instead of just moving on without
		 * legacy memory access) we fake it here by giving it anonymous
		 * memory, effectively behaving just like /dev/zero
		 */
		अगर ((offset + size) > hose->isa_mem_size) अणु
			pr_debug("Process %s (pid:%d) mapped non-existing PCI",
				current->comm, current->pid);
			pr_debug("legacy memory for 0%04x:%02x\n",
				pci_करोमुख्य_nr(bus), bus->number);
			अगर (vma->vm_flags & VM_SHARED)
				वापस shmem_zero_setup(vma);
			वापस 0;
		पूर्ण
		offset += hose->isa_mem_phys;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ io_offset = (अचिन्हित दीर्घ)hose->io_base_virt -
								_IO_BASE;
		अचिन्हित दीर्घ roffset = offset + io_offset;
		rp = &hose->io_resource;
		अगर (!(rp->flags & IORESOURCE_IO))
			वापस -ENXIO;
		अगर (roffset < rp->start || (roffset + size) > rp->end)
			वापस -ENXIO;
		offset += hose->io_base_phys;
	पूर्ण
	pr_debug(" -> mapping phys %llx\n", (अचिन्हित दीर्घ दीर्घ)offset);

	vma->vm_pgoff = offset >> PAGE_SHIFT;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
पूर्ण

व्योम pci_resource_to_user(स्थिर काष्ठा pci_dev *dev, पूर्णांक bar,
			  स्थिर काष्ठा resource *rsrc,
			  resource_माप_प्रकार *start, resource_माप_प्रकार *end)
अणु
	काष्ठा pci_bus_region region;

	अगर (rsrc->flags & IORESOURCE_IO) अणु
		pcibios_resource_to_bus(dev->bus, &region,
					(काष्ठा resource *) rsrc);
		*start = region.start;
		*end = region.end;
		वापस;
	पूर्ण

	/* We pass a CPU physical address to userland क्रम MMIO instead of a
	 * BAR value because X is lame and expects to be able to use that
	 * to pass to /dev/mem!
	 *
	 * That means we may have 64-bit values where some apps only expect
	 * 32 (like X itself since it thinks only Sparc has 64-bit MMIO).
	 */
	*start = rsrc->start;
	*end = rsrc->end;
पूर्ण

/**
 * pci_process_bridge_OF_ranges - Parse PCI bridge resources from device tree
 * @hose: newly allocated pci_controller to be setup
 * @dev: device node of the host bridge
 * @primary: set अगर primary bus (32 bits only, soon to be deprecated)
 *
 * This function will parse the "ranges" property of a PCI host bridge device
 * node and setup the resource mapping of a pci controller based on its
 * content.
 *
 * Lअगरe would be boring अगर it wasn't क्रम a few issues that we have to deal
 * with here:
 *
 *   - We can only cope with one IO space range and up to 3 Memory space
 *     ranges. However, some machines (thanks Apple !) tend to split their
 *     space पूर्णांकo lots of small contiguous ranges. So we have to coalesce.
 *
 *   - We can only cope with all memory ranges having the same offset
 *     between CPU addresses and PCI addresses. Unक्रमtunately, some bridges
 *     are setup क्रम a large 1:1 mapping aदीर्घ with a small "window" which
 *     maps PCI address 0 to some arbitrary high address of the CPU space in
 *     order to give access to the ISA memory hole.
 *     The way out of here that I've chosen क्रम now is to always set the
 *     offset based on the first resource found, then override it अगर we
 *     have a dअगरferent offset and the previous was set by an ISA hole.
 *
 *   - Some busses have IO space not starting at 0, which causes trouble with
 *     the way we करो our IO resource rक्रमागतbering. The code somewhat deals with
 *     it क्रम 64 bits but I would expect problems on 32 bits.
 *
 *   - Some 32 bits platक्रमms such as 4xx can have physical space larger than
 *     32 bits so we need to use 64 bits values क्रम the parsing
 */
व्योम pci_process_bridge_OF_ranges(काष्ठा pci_controller *hose,
				  काष्ठा device_node *dev, पूर्णांक primary)
अणु
	पूर्णांक memno = 0, isa_hole = -1;
	अचिन्हित दीर्घ दीर्घ isa_mb = 0;
	काष्ठा resource *res;
	काष्ठा of_pci_range range;
	काष्ठा of_pci_range_parser parser;

	pr_info("PCI host bridge %pOF %s ranges:\n",
	       dev, primary ? "(primary)" : "");

	/* Check क्रम ranges property */
	अगर (of_pci_range_parser_init(&parser, dev))
		वापस;

	pr_debug("Parsing ranges property...\n");
	क्रम_each_of_pci_range(&parser, &range) अणु
		/* Read next ranges element */

		/* If we failed translation or got a zero-sized region
		 * (some FW try to feed us with non sensical zero sized regions
		 * such as घातer3 which look like some kind of attempt
		 * at exposing the VGA memory hole)
		 */
		अगर (range.cpu_addr == OF_BAD_ADDR || range.size == 0)
			जारी;

		/* Act based on address space type */
		res = शून्य;
		चयन (range.flags & IORESOURCE_TYPE_BITS) अणु
		हाल IORESOURCE_IO:
			pr_info("  IO 0x%016llx..0x%016llx -> 0x%016llx\n",
				range.cpu_addr, range.cpu_addr + range.size - 1,
				range.pci_addr);

			/* We support only one IO range */
			अगर (hose->pci_io_size) अणु
				pr_info(" \\--> Skipped (too many) !\n");
				जारी;
			पूर्ण
			/* On 32 bits, limit I/O space to 16MB */
			अगर (range.size > 0x01000000)
				range.size = 0x01000000;

			/* 32 bits needs to map IOs here */
			hose->io_base_virt = ioremap(range.cpu_addr,
						range.size);

			/* Expect trouble अगर pci_addr is not 0 */
			अगर (primary)
				isa_io_base =
					(अचिन्हित दीर्घ)hose->io_base_virt;
			/* pci_io_size and io_base_phys always represent IO
			 * space starting at 0 so we factor in pci_addr
			 */
			hose->pci_io_size = range.pci_addr + range.size;
			hose->io_base_phys = range.cpu_addr - range.pci_addr;

			/* Build resource */
			res = &hose->io_resource;
			range.cpu_addr = range.pci_addr;

			अवरोध;
		हाल IORESOURCE_MEM:
			pr_info(" MEM 0x%016llx..0x%016llx -> 0x%016llx %s\n",
				range.cpu_addr, range.cpu_addr + range.size - 1,
				range.pci_addr,
				(range.flags & IORESOURCE_PREFETCH) ?
				"Prefetch" : "");

			/* We support only 3 memory ranges */
			अगर (memno >= 3) अणु
				pr_info(" \\--> Skipped (too many) !\n");
				जारी;
			पूर्ण
			/* Handles ISA memory hole space here */
			अगर (range.pci_addr == 0) अणु
				isa_mb = range.cpu_addr;
				isa_hole = memno;
				अगर (primary || isa_mem_base == 0)
					isa_mem_base = range.cpu_addr;
				hose->isa_mem_phys = range.cpu_addr;
				hose->isa_mem_size = range.size;
			पूर्ण

			/* We get the PCI/Mem offset from the first range or
			 * the, current one अगर the offset came from an ISA
			 * hole. If they करोn't match, bugger.
			 */
			अगर (memno == 0 ||
			    (isa_hole >= 0 && range.pci_addr != 0 &&
			     hose->pci_mem_offset == isa_mb))
				hose->pci_mem_offset = range.cpu_addr -
							range.pci_addr;
			अन्यथा अगर (range.pci_addr != 0 &&
				 hose->pci_mem_offset != range.cpu_addr -
							range.pci_addr) अणु
				pr_info(" \\--> Skipped (offset mismatch) !\n");
				जारी;
			पूर्ण

			/* Build resource */
			res = &hose->mem_resources[memno++];
			अवरोध;
		पूर्ण
		अगर (res != शून्य) अणु
			res->name = dev->full_name;
			res->flags = range.flags;
			res->start = range.cpu_addr;
			res->end = range.cpu_addr + range.size - 1;
			res->parent = res->child = res->sibling = शून्य;
		पूर्ण
	पूर्ण

	/* If there's an ISA hole and the pci_mem_offset is -not- matching
	 * the ISA hole offset, then we need to हटाओ the ISA hole from
	 * the resource list क्रम that brige
	 */
	अगर (isa_hole >= 0 && hose->pci_mem_offset != isa_mb) अणु
		अचिन्हित पूर्णांक next = isa_hole + 1;
		pr_info(" Removing ISA hole at 0x%016llx\n", isa_mb);
		अगर (next < memno)
			स_हटाओ(&hose->mem_resources[isa_hole],
				&hose->mem_resources[next],
				माप(काष्ठा resource) * (memno - next));
		hose->mem_resources[--memno].flags = 0;
	पूर्ण
पूर्ण

/* Display the करोमुख्य number in /proc */
पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस pci_करोमुख्य_nr(bus);
पूर्ण

/* This header fixup will करो the resource fixup क्रम all devices as they are
 * probed, but not क्रम bridge ranges
 */
अटल व्योम pcibios_fixup_resources(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	पूर्णांक i;

	अगर (!hose) अणु
		pr_err("No host bridge for PCI dev %s !\n",
		       pci_name(dev));
		वापस;
	पूर्ण
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		काष्ठा resource *res = dev->resource + i;
		अगर (!res->flags)
			जारी;
		अगर (res->start == 0) अणु
			pr_debug("PCI:%s Resource %d %016llx-%016llx [%x]",
				 pci_name(dev), i,
				 (अचिन्हित दीर्घ दीर्घ)res->start,
				 (अचिन्हित दीर्घ दीर्घ)res->end,
				 (अचिन्हित पूर्णांक)res->flags);
			pr_debug("is unassigned\n");
			res->end -= res->start;
			res->start = 0;
			res->flags |= IORESOURCE_UNSET;
			जारी;
		पूर्ण

		pr_debug("PCI:%s Resource %d %016llx-%016llx [%x]\n",
			 pci_name(dev), i,
			 (अचिन्हित दीर्घ दीर्घ)res->start,
			 (अचिन्हित दीर्घ दीर्घ)res->end,
			 (अचिन्हित पूर्णांक)res->flags);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pcibios_fixup_resources);

पूर्णांक pcibios_add_device(काष्ठा pci_dev *dev)
अणु
	dev->irq = of_irq_parse_and_map_pci(dev, 0, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcibios_add_device);

/*
 * Reparent resource children of pr that conflict with res
 * under res, and make res replace those children.
 */
अटल पूर्णांक __init reparent_resources(काष्ठा resource *parent,
				     काष्ठा resource *res)
अणु
	काष्ठा resource *p, **pp;
	काष्ठा resource **firstpp = शून्य;

	क्रम (pp = &parent->child; (p = *pp) != शून्य; pp = &p->sibling) अणु
		अगर (p->end < res->start)
			जारी;
		अगर (res->end < p->start)
			अवरोध;
		अगर (p->start < res->start || p->end > res->end)
			वापस -1;	/* not completely contained */
		अगर (firstpp == शून्य)
			firstpp = pp;
	पूर्ण
	अगर (firstpp == शून्य)
		वापस -1;	/* didn't find any conflicting entries? */
	res->parent = parent;
	res->child = *firstpp;
	res->sibling = *pp;
	*firstpp = res;
	*pp = शून्य;
	क्रम (p = res->child; p != शून्य; p = p->sibling) अणु
		p->parent = res;
		pr_debug("PCI: Reparented %s [%llx..%llx] under %s\n",
			 p->name,
			 (अचिन्हित दीर्घ दीर्घ)p->start,
			 (अचिन्हित दीर्घ दीर्घ)p->end, res->name);
	पूर्ण
	वापस 0;
पूर्ण

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

अटल व्योम pcibios_allocate_bus_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *b;
	पूर्णांक i;
	काष्ठा resource *res, *pr;

	pr_debug("PCI: Allocating bus resources for %04x:%02x...\n",
		 pci_करोमुख्य_nr(bus), bus->number);

	pci_bus_क्रम_each_resource(bus, res, i) अणु
		अगर (!res || !res->flags
		    || res->start > res->end || res->parent)
			जारी;
		अगर (bus->parent == शून्य)
			pr = (res->flags & IORESOURCE_IO) ?
				&ioport_resource : &iomem_resource;
		अन्यथा अणु
			/* Don't bother with non-root busses when
			 * re-assigning all resources. We clear the
			 * resource flags as अगर they were colliding
			 * and as such ensure proper re-allocation
			 * later.
			 */
			pr = pci_find_parent_resource(bus->self, res);
			अगर (pr == res) अणु
				/* this happens when the generic PCI
				 * code (wrongly) decides that this
				 * bridge is transparent  -- paulus
				 */
				जारी;
			पूर्ण
		पूर्ण

		pr_debug("PCI: %s (bus %d) bridge rsrc %d: %016llx-%016llx ",
			 bus->self ? pci_name(bus->self) : "PHB",
			 bus->number, i,
			 (अचिन्हित दीर्घ दीर्घ)res->start,
			 (अचिन्हित दीर्घ दीर्घ)res->end);
		pr_debug("[0x%x], parent %p (%s)\n",
			 (अचिन्हित पूर्णांक)res->flags,
			 pr, (pr && pr->name) ? pr->name : "nil");

		अगर (pr && !(pr->flags & IORESOURCE_UNSET)) अणु
			काष्ठा pci_dev *dev = bus->self;

			अगर (request_resource(pr, res) == 0)
				जारी;
			/*
			 * Must be a conflict with an existing entry.
			 * Move that entry (or entries) under the
			 * bridge resource and try again.
			 */
			अगर (reparent_resources(pr, res) == 0)
				जारी;

			अगर (dev && i < PCI_BRIDGE_RESOURCE_NUM &&
			    pci_claim_bridge_resource(dev,
						 i + PCI_BRIDGE_RESOURCES) == 0)
				जारी;

		पूर्ण
		pr_warn("PCI: Cannot allocate resource region ");
		pr_cont("%d of PCI bridge %d, will remap\n", i, bus->number);
		res->start = res->end = 0;
		res->flags = 0;
	पूर्ण

	list_क्रम_each_entry(b, &bus->children, node)
		pcibios_allocate_bus_resources(b);
पूर्ण

अटल अंतरभूत व्योम alloc_resource(काष्ठा pci_dev *dev, पूर्णांक idx)
अणु
	काष्ठा resource *pr, *r = &dev->resource[idx];

	pr_debug("PCI: Allocating %s: Resource %d: %016llx..%016llx [%x]\n",
		 pci_name(dev), idx,
		 (अचिन्हित दीर्घ दीर्घ)r->start,
		 (अचिन्हित दीर्घ दीर्घ)r->end,
		 (अचिन्हित पूर्णांक)r->flags);

	pr = pci_find_parent_resource(dev, r);
	अगर (!pr || (pr->flags & IORESOURCE_UNSET) ||
	    request_resource(pr, r) < 0) अणु
		pr_warn("PCI: Cannot allocate resource region %d ", idx);
		pr_cont("of device %s, will remap\n", pci_name(dev));
		अगर (pr)
			pr_debug("PCI:  parent is %p: %016llx-%016llx [%x]\n",
				 pr,
				 (अचिन्हित दीर्घ दीर्घ)pr->start,
				 (अचिन्हित दीर्घ दीर्घ)pr->end,
				 (अचिन्हित पूर्णांक)pr->flags);
		/* We'll assign a new address later */
		r->flags |= IORESOURCE_UNSET;
		r->end -= r->start;
		r->start = 0;
	पूर्ण
पूर्ण

अटल व्योम __init pcibios_allocate_resources(पूर्णांक pass)
अणु
	काष्ठा pci_dev *dev = शून्य;
	पूर्णांक idx, disabled;
	u16 command;
	काष्ठा resource *r;

	क्रम_each_pci_dev(dev) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
		क्रम (idx = 0; idx <= PCI_ROM_RESOURCE; idx++) अणु
			r = &dev->resource[idx];
			अगर (r->parent)		/* Alपढ़ोy allocated */
				जारी;
			अगर (!r->flags || (r->flags & IORESOURCE_UNSET))
				जारी;	/* Not asचिन्हित at all */
			/* We only allocate ROMs on pass 1 just in हाल they
			 * have been screwed up by firmware
			 */
			अगर (idx == PCI_ROM_RESOURCE)
				disabled = 1;
			अगर (r->flags & IORESOURCE_IO)
				disabled = !(command & PCI_COMMAND_IO);
			अन्यथा
				disabled = !(command & PCI_COMMAND_MEMORY);
			अगर (pass == disabled)
				alloc_resource(dev, idx);
		पूर्ण
		अगर (pass)
			जारी;
		r = &dev->resource[PCI_ROM_RESOURCE];
		अगर (r->flags) अणु
			/* Turn the ROM off, leave the resource region,
			 * but keep it unरेजिस्टरed.
			 */
			u32 reg;
			pci_पढ़ो_config_dword(dev, dev->rom_base_reg, &reg);
			अगर (reg & PCI_ROM_ADDRESS_ENABLE) अणु
				pr_debug("PCI: Switching off ROM of %s\n",
					 pci_name(dev));
				r->flags &= ~IORESOURCE_ROM_ENABLE;
				pci_ग_लिखो_config_dword(dev, dev->rom_base_reg,
						reg & ~PCI_ROM_ADDRESS_ENABLE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init pcibios_reserve_legacy_regions(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	resource_माप_प्रकार	offset;
	काष्ठा resource *res, *pres;
	पूर्णांक i;

	pr_debug("Reserving legacy ranges for domain %04x\n",
							pci_करोमुख्य_nr(bus));

	/* Check क्रम IO */
	अगर (!(hose->io_resource.flags & IORESOURCE_IO))
		जाओ no_io;
	offset = (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	BUG_ON(res == शून्य);
	res->name = "Legacy IO";
	res->flags = IORESOURCE_IO;
	res->start = offset;
	res->end = (offset + 0xfff) & 0xfffffffful;
	pr_debug("Candidate legacy IO: %pR\n", res);
	अगर (request_resource(&hose->io_resource, res)) अणु
		pr_debug("PCI %04x:%02x Cannot reserve Legacy IO %pR\n",
		       pci_करोमुख्य_nr(bus), bus->number, res);
		kमुक्त(res);
	पूर्ण

 no_io:
	/* Check क्रम memory */
	offset = hose->pci_mem_offset;
	pr_debug("hose mem offset: %016llx\n", (अचिन्हित दीर्घ दीर्घ)offset);
	क्रम (i = 0; i < 3; i++) अणु
		pres = &hose->mem_resources[i];
		अगर (!(pres->flags & IORESOURCE_MEM))
			जारी;
		pr_debug("hose mem res: %pR\n", pres);
		अगर ((pres->start - offset) <= 0xa0000 &&
		    (pres->end - offset) >= 0xbffff)
			अवरोध;
	पूर्ण
	अगर (i >= 3)
		वापस;
	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	BUG_ON(res == शून्य);
	res->name = "Legacy VGA memory";
	res->flags = IORESOURCE_MEM;
	res->start = 0xa0000 + offset;
	res->end = 0xbffff + offset;
	pr_debug("Candidate VGA memory: %pR\n", res);
	अगर (request_resource(pres, res)) अणु
		pr_debug("PCI %04x:%02x Cannot reserve VGA memory %pR\n",
		       pci_करोमुख्य_nr(bus), bus->number, res);
		kमुक्त(res);
	पूर्ण
पूर्ण

व्योम __init pcibios_resource_survey(व्योम)
अणु
	काष्ठा pci_bus *b;

	/* Allocate and assign resources. If we re-assign everything, then
	 * we skip the allocate phase
	 */
	list_क्रम_each_entry(b, &pci_root_buses, node)
		pcibios_allocate_bus_resources(b);

	pcibios_allocate_resources(0);
	pcibios_allocate_resources(1);

	/* Beक्रमe we start assigning unasचिन्हित resource, we try to reserve
	 * the low IO area and the VGA memory area अगर they पूर्णांकersect the
	 * bus available resources to aव्योम allocating things on top of them
	 */
	list_क्रम_each_entry(b, &pci_root_buses, node)
		pcibios_reserve_legacy_regions(b);

	/* Now proceed to assigning things that were left unasचिन्हित */
	pr_debug("PCI: Assigning unassigned resources...\n");
	pci_assign_unasचिन्हित_resources();
पूर्ण

अटल व्योम pcibios_setup_phb_resources(काष्ठा pci_controller *hose,
					काष्ठा list_head *resources)
अणु
	अचिन्हित दीर्घ io_offset;
	काष्ठा resource *res;
	पूर्णांक i;

	/* Hookup PHB IO resource */
	res = &hose->io_resource;

	/* Fixup IO space offset */
	io_offset = (अचिन्हित दीर्घ)hose->io_base_virt - isa_io_base;
	res->start = (res->start + io_offset) & 0xffffffffu;
	res->end = (res->end + io_offset) & 0xffffffffu;

	अगर (!res->flags) अणु
		pr_warn("PCI: I/O resource not set for host ");
		pr_cont("bridge %pOF (domain %d)\n",
			hose->dn, hose->global_number);
		/* Workaround क्रम lack of IO resource only on 32-bit */
		res->start = (अचिन्हित दीर्घ)hose->io_base_virt - isa_io_base;
		res->end = res->start + IO_SPACE_LIMIT;
		res->flags = IORESOURCE_IO;
	पूर्ण
	pci_add_resource_offset(resources, res,
		(__क्रमce resource_माप_प्रकार)(hose->io_base_virt - _IO_BASE));

	pr_debug("PCI: PHB IO resource    = %016llx-%016llx [%lx]\n",
		 (अचिन्हित दीर्घ दीर्घ)res->start,
		 (अचिन्हित दीर्घ दीर्घ)res->end,
		 (अचिन्हित दीर्घ)res->flags);

	/* Hookup PHB Memory resources */
	क्रम (i = 0; i < 3; ++i) अणु
		res = &hose->mem_resources[i];
		अगर (!res->flags) अणु
			अगर (i > 0)
				जारी;
			pr_err("PCI: Memory resource 0 not set for ");
			pr_cont("host bridge %pOF (domain %d)\n",
				hose->dn, hose->global_number);

			/* Workaround क्रम lack of MEM resource only on 32-bit */
			res->start = hose->pci_mem_offset;
			res->end = (resource_माप_प्रकार)-1LL;
			res->flags = IORESOURCE_MEM;

		पूर्ण
		pci_add_resource_offset(resources, res, hose->pci_mem_offset);

		pr_debug("PCI: PHB MEM resource %d = %016llx-%016llx [%lx]\n",
			i, (अचिन्हित दीर्घ दीर्घ)res->start,
			(अचिन्हित दीर्घ दीर्घ)res->end,
			(अचिन्हित दीर्घ)res->flags);
	पूर्ण

	pr_debug("PCI: PHB MEM offset     = %016llx\n",
		 (अचिन्हित दीर्घ दीर्घ)hose->pci_mem_offset);
	pr_debug("PCI: PHB IO  offset     = %08lx\n",
		 (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE);
पूर्ण

अटल व्योम pcibios_scan_phb(काष्ठा pci_controller *hose)
अणु
	LIST_HEAD(resources);
	काष्ठा pci_bus *bus;
	काष्ठा device_node *node = hose->dn;

	pr_debug("PCI: Scanning PHB %pOF\n", node);

	pcibios_setup_phb_resources(hose, &resources);

	bus = pci_scan_root_bus(hose->parent, hose->first_busno,
				hose->ops, hose, &resources);
	अगर (bus == शून्य) अणु
		pr_err("Failed to create bus for PCI domain %04x\n",
		       hose->global_number);
		pci_मुक्त_resource_list(&resources);
		वापस;
	पूर्ण
	bus->busn_res.start = hose->first_busno;
	hose->bus = bus;

	hose->last_busno = bus->busn_res.end;
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;
	पूर्णांक next_busno = 0;

	pr_info("PCI: Probing PCI hardware\n");

	/* Scan all of the recorded PCI controllers.  */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node) अणु
		hose->last_busno = 0xff;
		pcibios_scan_phb(hose);
		अगर (next_busno <= hose->last_busno)
			next_busno = hose->last_busno + 1;
	पूर्ण
	pci_bus_count = next_busno;

	/* Call common code to handle resource allocation */
	pcibios_resource_survey();
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node) अणु
		अगर (hose->bus)
			pci_bus_add_devices(hose->bus);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);

अटल काष्ठा pci_controller *pci_bus_to_hose(पूर्णांक bus)
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

दीर्घ sys_pciconfig_iobase(दीर्घ which, अचिन्हित दीर्घ bus, अचिन्हित दीर्घ devfn)
अणु
	काष्ठा pci_controller *hose;
	दीर्घ result = -EOPNOTSUPP;

	hose = pci_bus_to_hose(bus);
	अगर (!hose)
		वापस -ENODEV;

	चयन (which) अणु
	हाल IOBASE_BRIDGE_NUMBER:
		वापस (दीर्घ)hose->first_busno;
	हाल IOBASE_MEMORY:
		वापस (दीर्घ)hose->pci_mem_offset;
	हाल IOBASE_IO:
		वापस (दीर्घ)hose->io_base_phys;
	हाल IOBASE_ISA_IO:
		वापस (दीर्घ)isa_io_base;
	हाल IOBASE_ISA_MEM:
		वापस (दीर्घ)isa_mem_base;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Null PCI config access functions, क्रम the हाल when we can't
 * find a hose.
 */
#घोषणा शून्य_PCI_OP(rw, size, type)					\
अटल पूर्णांक								\
null_##rw##_config_##size(काष्ठा pci_dev *dev, पूर्णांक offset, type val)	\
अणु									\
	वापस PCIBIOS_DEVICE_NOT_FOUND;				\
पूर्ण

अटल पूर्णांक
null_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
		 पूर्णांक len, u32 *val)
अणु
	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल पूर्णांक
null_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
		  पूर्णांक len, u32 val)
अणु
	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल काष्ठा pci_ops null_pci_ops = अणु
	.पढ़ो = null_पढ़ो_config,
	.ग_लिखो = null_ग_लिखो_config,
पूर्ण;

/*
 * These functions are used early on beक्रमe PCI scanning is करोne
 * and all of the pci_dev and pci_bus काष्ठाures have been created.
 */
अटल काष्ठा pci_bus *
fake_pci_bus(काष्ठा pci_controller *hose, पूर्णांक busnr)
अणु
	अटल काष्ठा pci_bus bus;

	अगर (!hose)
		pr_err("Can't find hose for PCI bus %d!\n", busnr);

	bus.number = busnr;
	bus.sysdata = hose;
	bus.ops = hose ? hose->ops : &null_pci_ops;
	वापस &bus;
पूर्ण

#घोषणा EARLY_PCI_OP(rw, size, type)					\
पूर्णांक early_##rw##_config_##size(काष्ठा pci_controller *hose, पूर्णांक bus,	\
			       पूर्णांक devfn, पूर्णांक offset, type value)	\
अणु									\
	वापस pci_bus_##rw##_config_##size(fake_pci_bus(hose, bus),	\
					    devfn, offset, value);	\
पूर्ण

EARLY_PCI_OP(पढ़ो, byte, u8 *)
EARLY_PCI_OP(पढ़ो, word, u16 *)
EARLY_PCI_OP(पढ़ो, dword, u32 *)
EARLY_PCI_OP(ग_लिखो, byte, u8)
EARLY_PCI_OP(ग_लिखो, word, u16)
EARLY_PCI_OP(ग_लिखो, dword, u32)

पूर्णांक early_find_capability(काष्ठा pci_controller *hose, पूर्णांक bus, पूर्णांक devfn,
			  पूर्णांक cap)
अणु
	वापस pci_bus_find_capability(fake_pci_bus(hose, bus), devfn, cap);
पूर्ण
