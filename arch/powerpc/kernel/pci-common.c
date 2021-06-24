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
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/mm.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/list.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/irq.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/eeh.h>

#समावेश "../../../drivers/pci/pci.h"

/* hose_spinlock protects accesses to the the phb_biपंचांगap. */
अटल DEFINE_SPINLOCK(hose_spinlock);
LIST_HEAD(hose_list);

/* For dynamic PHB numbering on get_phb_number(): max number of PHBs. */
#घोषणा MAX_PHBS 0x10000

/*
 * For dynamic PHB numbering: used/मुक्त PHBs tracking biपंचांगap.
 * Accesses to this biपंचांगap should be रक्षित by hose_spinlock.
 */
अटल DECLARE_BITMAP(phb_biपंचांगap, MAX_PHBS);

/* ISA Memory physical address */
resource_माप_प्रकार isa_mem_base;
EXPORT_SYMBOL(isa_mem_base);


अटल स्थिर काष्ठा dma_map_ops *pci_dma_ops;

व्योम set_pci_dma_ops(स्थिर काष्ठा dma_map_ops *dma_ops)
अणु
	pci_dma_ops = dma_ops;
पूर्ण

/*
 * This function should run under locking protection, specअगरically
 * hose_spinlock.
 */
अटल पूर्णांक get_phb_number(काष्ठा device_node *dn)
अणु
	पूर्णांक ret, phb_id = -1;
	u32 prop_32;
	u64 prop;

	/*
	 * Try fixed PHB numbering first, by checking archs and पढ़ोing
	 * the respective device-tree properties. Firstly, try घातernv by
	 * पढ़ोing "ibm,opal-phbid", only present in OPAL environment.
	 */
	ret = of_property_पढ़ो_u64(dn, "ibm,opal-phbid", &prop);
	अगर (ret) अणु
		ret = of_property_पढ़ो_u32_index(dn, "reg", 1, &prop_32);
		prop = prop_32;
	पूर्ण

	अगर (!ret)
		phb_id = (पूर्णांक)(prop & (MAX_PHBS - 1));

	/* We need to be sure to not use the same PHB number twice. */
	अगर ((phb_id >= 0) && !test_and_set_bit(phb_id, phb_biपंचांगap))
		वापस phb_id;

	/*
	 * If not pseries nor घातernv, or अगर fixed PHB numbering tried to add
	 * the same PHB number twice, then fallback to dynamic PHB numbering.
	 */
	phb_id = find_first_zero_bit(phb_biपंचांगap, MAX_PHBS);
	BUG_ON(phb_id >= MAX_PHBS);
	set_bit(phb_id, phb_biपंचांगap);

	वापस phb_id;
पूर्ण

काष्ठा pci_controller *pcibios_alloc_controller(काष्ठा device_node *dev)
अणु
	काष्ठा pci_controller *phb;

	phb = zalloc_maybe_booपंचांगem(माप(काष्ठा pci_controller), GFP_KERNEL);
	अगर (phb == शून्य)
		वापस शून्य;
	spin_lock(&hose_spinlock);
	phb->global_number = get_phb_number(dev);
	list_add_tail(&phb->list_node, &hose_list);
	spin_unlock(&hose_spinlock);
	phb->dn = dev;
	phb->is_dynamic = slab_is_available();
#अगर_घोषित CONFIG_PPC64
	अगर (dev) अणु
		पूर्णांक nid = of_node_to_nid(dev);

		अगर (nid < 0 || !node_online(nid))
			nid = NUMA_NO_NODE;

		PHB_SET_NODE(phb, nid);
	पूर्ण
#पूर्ण_अगर
	वापस phb;
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_alloc_controller);

व्योम pcibios_मुक्त_controller(काष्ठा pci_controller *phb)
अणु
	spin_lock(&hose_spinlock);

	/* Clear bit of phb_biपंचांगap to allow reuse of this PHB number. */
	अगर (phb->global_number < MAX_PHBS)
		clear_bit(phb->global_number, phb_biपंचांगap);

	list_del(&phb->list_node);
	spin_unlock(&hose_spinlock);

	अगर (phb->is_dynamic)
		kमुक्त(phb);
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_मुक्त_controller);

/*
 * This function is used to call pcibios_मुक्त_controller()
 * in a deferred manner: a callback from the PCI subप्रणाली.
 *
 * _*DO NOT*_ call pcibios_मुक्त_controller() explicitly अगर
 * this is used (or it may access an invalid *phb poपूर्णांकer).
 *
 * The callback occurs when all references to the root bus
 * are dropped (e.g., child buses/devices and their users).
 *
 * It's called as .release_fn() of 'struct pci_host_bridge'
 * which is associated with the 'struct pci_controller.bus'
 * (root bus) - it expects .release_data to hold a poपूर्णांकer
 * to 'struct pci_controller'.
 *
 * In order to use it, रेजिस्टर .release_fn()/release_data
 * like this:
 *
 * pci_set_host_bridge_release(bridge,
 *                             pcibios_मुक्त_controller_deferred
 *                             (व्योम *) phb);
 *
 * e.g. in the pcibios_root_bridge_prepare() callback from
 * pci_create_root_bus().
 */
व्योम pcibios_मुक्त_controller_deferred(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_controller *phb = (काष्ठा pci_controller *)
					 bridge->release_data;

	pr_debug("domain %d, dynamic %d\n", phb->global_number, phb->is_dynamic);

	pcibios_मुक्त_controller(phb);
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_मुक्त_controller_deferred);

/*
 * The function is used to वापस the minimal alignment
 * क्रम memory or I/O winकरोws of the associated P2P bridge.
 * By शेष, 4KiB alignment क्रम I/O winकरोws and 1MiB क्रम
 * memory winकरोws.
 */
resource_माप_प्रकार pcibios_winकरोw_alignment(काष्ठा pci_bus *bus,
					 अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(bus);

	अगर (phb->controller_ops.winकरोw_alignment)
		वापस phb->controller_ops.winकरोw_alignment(bus, type);

	/*
	 * PCI core will figure out the शेष
	 * alignment: 4KiB क्रम I/O and 1MiB क्रम
	 * memory winकरोw.
	 */
	वापस 1;
पूर्ण

व्योम pcibios_setup_bridge(काष्ठा pci_bus *bus, अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (hose->controller_ops.setup_bridge)
		hose->controller_ops.setup_bridge(bus, type);
पूर्ण

व्योम pcibios_reset_secondary_bus(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);

	अगर (phb->controller_ops.reset_secondary_bus) अणु
		phb->controller_ops.reset_secondary_bus(dev);
		वापस;
	पूर्ण

	pci_reset_secondary_bus(dev);
पूर्ण

resource_माप_प्रकार pcibios_शेष_alignment(व्योम)
अणु
	अगर (ppc_md.pcibios_शेष_alignment)
		वापस ppc_md.pcibios_शेष_alignment();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
resource_माप_प्रकार pcibios_iov_resource_alignment(काष्ठा pci_dev *pdev, पूर्णांक resno)
अणु
	अगर (ppc_md.pcibios_iov_resource_alignment)
		वापस ppc_md.pcibios_iov_resource_alignment(pdev, resno);

	वापस pci_iov_resource_size(pdev, resno);
पूर्ण

पूर्णांक pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	अगर (ppc_md.pcibios_sriov_enable)
		वापस ppc_md.pcibios_sriov_enable(pdev, num_vfs);

	वापस 0;
पूर्ण

पूर्णांक pcibios_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	अगर (ppc_md.pcibios_sriov_disable)
		वापस ppc_md.pcibios_sriov_disable(pdev);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_IOV */

अटल resource_माप_प्रकार pcibios_io_size(स्थिर काष्ठा pci_controller *hose)
अणु
#अगर_घोषित CONFIG_PPC64
	वापस hose->pci_io_size;
#अन्यथा
	वापस resource_size(&hose->io_resource);
#पूर्ण_अगर
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

/*
 * Return the करोमुख्य number क्रम this bus.
 */
पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	वापस hose->global_number;
पूर्ण
EXPORT_SYMBOL(pci_करोमुख्य_nr);

/* This routine is meant to be used early during boot, when the
 * PCI bus numbers have not yet been asचिन्हित, and you need to
 * issue PCI config cycles to an OF device.
 * It could also be used to "fix" RTAS config cycles अगर you want
 * to set pci_assign_all_buses to 1 and still use RTAS क्रम PCI
 * config cycles.
 */
काष्ठा pci_controller* pci_find_hose_क्रम_OF_device(काष्ठा device_node* node)
अणु
	जबतक(node) अणु
		काष्ठा pci_controller *hose, *पंचांगp;
		list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
			अगर (hose->dn == node)
				वापस hose;
		node = node->parent;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा pci_controller *pci_find_controller_क्रम_करोमुख्य(पूर्णांक करोमुख्य_nr)
अणु
	काष्ठा pci_controller *hose;

	list_क्रम_each_entry(hose, &hose_list, list_node)
		अगर (hose->global_number == करोमुख्य_nr)
			वापस hose;

	वापस शून्य;
पूर्ण

काष्ठा pci_पूर्णांकx_virq अणु
	पूर्णांक virq;
	काष्ठा kref kref;
	काष्ठा list_head list_node;
पूर्ण;

अटल LIST_HEAD(पूर्णांकx_list);
अटल DEFINE_MUTEX(पूर्णांकx_mutex);

अटल व्योम ppc_pci_पूर्णांकx_release(काष्ठा kref *kref)
अणु
	काष्ठा pci_पूर्णांकx_virq *vi = container_of(kref, काष्ठा pci_पूर्णांकx_virq, kref);

	list_del(&vi->list_node);
	irq_dispose_mapping(vi->virq);
	kमुक्त(vi);
पूर्ण

अटल पूर्णांक ppc_pci_unmap_irq_line(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(data);

	अगर (action == BUS_NOTIFY_DEL_DEVICE) अणु
		काष्ठा pci_पूर्णांकx_virq *vi;

		mutex_lock(&पूर्णांकx_mutex);
		list_क्रम_each_entry(vi, &पूर्णांकx_list, list_node) अणु
			अगर (vi->virq == pdev->irq) अणु
				kref_put(&vi->kref, ppc_pci_पूर्णांकx_release);
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&पूर्णांकx_mutex);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ppc_pci_unmap_irq_notअगरier = अणु
	.notअगरier_call = ppc_pci_unmap_irq_line,
पूर्ण;

अटल पूर्णांक ppc_pci_रेजिस्टर_irq_notअगरier(व्योम)
अणु
	वापस bus_रेजिस्टर_notअगरier(&pci_bus_type, &ppc_pci_unmap_irq_notअगरier);
पूर्ण
arch_initcall(ppc_pci_रेजिस्टर_irq_notअगरier);

/*
 * Reads the पूर्णांकerrupt pin to determine अगर पूर्णांकerrupt is use by card.
 * If the पूर्णांकerrupt is used, then माला_लो the पूर्णांकerrupt line from the
 * खोलोfirmware and sets it in the pci_dev and pci_config line.
 */
अटल पूर्णांक pci_पढ़ो_irq_line(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक virq;
	काष्ठा pci_पूर्णांकx_virq *vi, *viपंचांगp;

	/* Pपुनः_स्मृतिate vi as शुरुआत is complex अगर this fails after mapping */
	vi = kzalloc(माप(काष्ठा pci_पूर्णांकx_virq), GFP_KERNEL);
	अगर (!vi)
		वापस -1;

	pr_debug("PCI: Try to map irq for %s...\n", pci_name(pci_dev));

	/* Try to get a mapping from the device-tree */
	virq = of_irq_parse_and_map_pci(pci_dev, 0, 0);
	अगर (virq <= 0) अणु
		u8 line, pin;

		/* If that fails, lets fallback to what is in the config
		 * space and map that through the शेष controller. We
		 * also set the type to level low since that's what PCI
		 * पूर्णांकerrupts are. If your platक्रमm करोes dअगरferently, then
		 * either provide a proper पूर्णांकerrupt tree or करोn't use this
		 * function.
		 */
		अगर (pci_पढ़ो_config_byte(pci_dev, PCI_INTERRUPT_PIN, &pin))
			जाओ error_निकास;
		अगर (pin == 0)
			जाओ error_निकास;
		अगर (pci_पढ़ो_config_byte(pci_dev, PCI_INTERRUPT_LINE, &line) ||
		    line == 0xff || line == 0) अणु
			जाओ error_निकास;
		पूर्ण
		pr_debug(" No map ! Using line %d (pin %d) from PCI config\n",
			 line, pin);

		virq = irq_create_mapping(शून्य, line);
		अगर (virq)
			irq_set_irq_type(virq, IRQ_TYPE_LEVEL_LOW);
	पूर्ण

	अगर (!virq) अणु
		pr_debug(" Failed to map !\n");
		जाओ error_निकास;
	पूर्ण

	pr_debug(" Mapped to linux irq %d\n", virq);

	pci_dev->irq = virq;

	mutex_lock(&पूर्णांकx_mutex);
	list_क्रम_each_entry(viपंचांगp, &पूर्णांकx_list, list_node) अणु
		अगर (viपंचांगp->virq == virq) अणु
			kref_get(&viपंचांगp->kref);
			kमुक्त(vi);
			vi = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (vi) अणु
		vi->virq = virq;
		kref_init(&vi->kref);
		list_add_tail(&vi->list_node, &पूर्णांकx_list);
	पूर्ण
	mutex_unlock(&पूर्णांकx_mutex);

	वापस 0;
error_निकास:
	kमुक्त(vi);
	वापस -1;
पूर्ण

/*
 * Platक्रमm support क्रम /proc/bus/pci/X/Y mmap()s.
 *  -- paulus.
 */
पूर्णांक pci_iobar_pfn(काष्ठा pci_dev *pdev, पूर्णांक bar, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);
	resource_माप_प्रकार ioaddr = pci_resource_start(pdev, bar);

	अगर (!hose)
		वापस -EINVAL;

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

	चयन(size) अणु
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
	चयन(size) अणु
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
		 * Because X is lame and can fail starting अगर it माला_लो an error trying
		 * to mmap legacy_mem (instead of just moving on without legacy memory
		 * access) we fake it here by giving it anonymous memory, effectively
		 * behaving just like /dev/zero
		 */
		अगर ((offset + size) > hose->isa_mem_size) अणु
			prपूर्णांकk(KERN_DEBUG
			       "Process %s (pid:%d) mapped non-existing PCI legacy memory for 0%04x:%02x\n",
			       current->comm, current->pid, pci_करोमुख्य_nr(bus), bus->number);
			अगर (vma->vm_flags & VM_SHARED)
				वापस shmem_zero_setup(vma);
			वापस 0;
		पूर्ण
		offset += hose->isa_mem_phys;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ io_offset = (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
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
	पूर्णांक memno = 0;
	काष्ठा resource *res;
	काष्ठा of_pci_range range;
	काष्ठा of_pci_range_parser parser;

	prपूर्णांकk(KERN_INFO "PCI host bridge %pOF %s ranges:\n",
	       dev, primary ? "(primary)" : "");

	/* Check क्रम ranges property */
	अगर (of_pci_range_parser_init(&parser, dev))
		वापस;

	/* Parse it */
	क्रम_each_of_pci_range(&parser, &range) अणु
		/* If we failed translation or got a zero-sized region
		 * (some FW try to feed us with non sensical zero sized regions
		 * such as घातer3 which look like some kind of attempt at exposing
		 * the VGA memory hole)
		 */
		अगर (range.cpu_addr == OF_BAD_ADDR || range.size == 0)
			जारी;

		/* Act based on address space type */
		res = शून्य;
		चयन (range.flags & IORESOURCE_TYPE_BITS) अणु
		हाल IORESOURCE_IO:
			prपूर्णांकk(KERN_INFO
			       "  IO 0x%016llx..0x%016llx -> 0x%016llx\n",
			       range.cpu_addr, range.cpu_addr + range.size - 1,
			       range.pci_addr);

			/* We support only one IO range */
			अगर (hose->pci_io_size) अणु
				prपूर्णांकk(KERN_INFO
				       " \\--> Skipped (too many) !\n");
				जारी;
			पूर्ण
#अगर_घोषित CONFIG_PPC32
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
#पूर्ण_अगर /* CONFIG_PPC32 */
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
			prपूर्णांकk(KERN_INFO
			       " MEM 0x%016llx..0x%016llx -> 0x%016llx %s\n",
			       range.cpu_addr, range.cpu_addr + range.size - 1,
			       range.pci_addr,
			       (range.flags & IORESOURCE_PREFETCH) ?
			       "Prefetch" : "");

			/* We support only 3 memory ranges */
			अगर (memno >= 3) अणु
				prपूर्णांकk(KERN_INFO
				       " \\--> Skipped (too many) !\n");
				जारी;
			पूर्ण
			/* Handles ISA memory hole space here */
			अगर (range.pci_addr == 0) अणु
				अगर (primary || isa_mem_base == 0)
					isa_mem_base = range.cpu_addr;
				hose->isa_mem_phys = range.cpu_addr;
				hose->isa_mem_size = range.size;
			पूर्ण

			/* Build resource */
			hose->mem_offset[memno] = range.cpu_addr -
							range.pci_addr;
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
पूर्ण

/* Decide whether to display the करोमुख्य number in /proc */
पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (!pci_has_flag(PCI_ENABLE_PROC_DOMAINS))
		वापस 0;
	अगर (pci_has_flag(PCI_COMPAT_DOMAIN_0))
		वापस hose->global_number != 0;
	वापस 1;
पूर्ण

पूर्णांक pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	अगर (ppc_md.pcibios_root_bridge_prepare)
		वापस ppc_md.pcibios_root_bridge_prepare(bridge);

	वापस 0;
पूर्ण

/* This header fixup will करो the resource fixup क्रम all devices as they are
 * probed, but not क्रम bridge ranges
 */
अटल व्योम pcibios_fixup_resources(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	पूर्णांक i;

	अगर (!hose) अणु
		prपूर्णांकk(KERN_ERR "No host bridge for PCI dev %s !\n",
		       pci_name(dev));
		वापस;
	पूर्ण

	अगर (dev->is_virtfn)
		वापस;

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		काष्ठा resource *res = dev->resource + i;
		काष्ठा pci_bus_region reg;
		अगर (!res->flags)
			जारी;

		/* If we're going to re-assign everything, we mark all resources
		 * as unset (and 0-base them). In addition, we mark BARs starting
		 * at 0 as unset as well, except अगर PCI_PROBE_ONLY is also set
		 * since in that हाल, we करोn't want to re-assign anything
		 */
		pcibios_resource_to_bus(dev->bus, &reg, res);
		अगर (pci_has_flag(PCI_REASSIGN_ALL_RSRC) ||
		    (reg.start == 0 && !pci_has_flag(PCI_PROBE_ONLY))) अणु
			/* Only prपूर्णांक message अगर not re-assigning */
			अगर (!pci_has_flag(PCI_REASSIGN_ALL_RSRC))
				pr_debug("PCI:%s Resource %d %pR is unassigned\n",
					 pci_name(dev), i, res);
			res->end -= res->start;
			res->start = 0;
			res->flags |= IORESOURCE_UNSET;
			जारी;
		पूर्ण

		pr_debug("PCI:%s Resource %d %pR\n", pci_name(dev), i, res);
	पूर्ण

	/* Call machine specअगरic resource fixup */
	अगर (ppc_md.pcibios_fixup_resources)
		ppc_md.pcibios_fixup_resources(dev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pcibios_fixup_resources);

/* This function tries to figure out अगर a bridge resource has been initialized
 * by the firmware or not. It करोesn't have to be असलolutely bullet proof, but
 * things go more smoothly when it माला_लो it right. It should covers हालs such
 * as Apple "closed" bridge resources and bare-metal pSeries unasचिन्हित bridges
 */
अटल पूर्णांक pcibios_uninitialized_bridge_resource(काष्ठा pci_bus *bus,
						 काष्ठा resource *res)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा pci_dev *dev = bus->self;
	resource_माप_प्रकार offset;
	काष्ठा pci_bus_region region;
	u16 command;
	पूर्णांक i;

	/* We करोn't करो anything अगर PCI_PROBE_ONLY is set */
	अगर (pci_has_flag(PCI_PROBE_ONLY))
		वापस 0;

	/* Job is a bit dअगरferent between memory and IO */
	अगर (res->flags & IORESOURCE_MEM) अणु
		pcibios_resource_to_bus(dev->bus, &region, res);

		/* If the BAR is non-0 then it's probably been initialized */
		अगर (region.start != 0)
			वापस 0;

		/* The BAR is 0, let's check अगर memory decoding is enabled on
		 * the bridge. If not, we consider it unasचिन्हित
		 */
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
		अगर ((command & PCI_COMMAND_MEMORY) == 0)
			वापस 1;

		/* Memory decoding is enabled and the BAR is 0. If any of the bridge
		 * resources covers that starting address (0 then it's good enough क्रम
		 * us क्रम memory space)
		 */
		क्रम (i = 0; i < 3; i++) अणु
			अगर ((hose->mem_resources[i].flags & IORESOURCE_MEM) &&
			    hose->mem_resources[i].start == hose->mem_offset[i])
				वापस 0;
		पूर्ण

		/* Well, it starts at 0 and we know it will collide so we may as
		 * well consider it as unasचिन्हित. That covers the Apple हाल.
		 */
		वापस 1;
	पूर्ण अन्यथा अणु
		/* If the BAR is non-0, then we consider it asचिन्हित */
		offset = (अचिन्हित दीर्घ)hose->io_base_virt - _IO_BASE;
		अगर (((res->start - offset) & 0xfffffffful) != 0)
			वापस 0;

		/* Here, we are a bit dअगरferent than memory as typically IO space
		 * starting at low addresses -is- valid. What we करो instead अगर that
		 * we consider as unasचिन्हित anything that करोesn't have IO enabled
		 * in the PCI command रेजिस्टर, and that's it.
		 */
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
		अगर (command & PCI_COMMAND_IO)
			वापस 0;

		/* It's starting at 0 and IO is disabled in the bridge, consider
		 * it unasचिन्हित
		 */
		वापस 1;
	पूर्ण
पूर्ण

/* Fixup resources of a PCI<->PCI bridge */
अटल व्योम pcibios_fixup_bridge(काष्ठा pci_bus *bus)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	काष्ठा pci_dev *dev = bus->self;

	pci_bus_क्रम_each_resource(bus, res, i) अणु
		अगर (!res || !res->flags)
			जारी;
		अगर (i >= 3 && bus->self->transparent)
			जारी;

		/* If we're going to reassign everything, we can
		 * shrink the P2P resource to have size as being
		 * of 0 in order to save space.
		 */
		अगर (pci_has_flag(PCI_REASSIGN_ALL_RSRC)) अणु
			res->flags |= IORESOURCE_UNSET;
			res->start = 0;
			res->end = -1;
			जारी;
		पूर्ण

		pr_debug("PCI:%s Bus rsrc %d %pR\n", pci_name(dev), i, res);

		/* Try to detect uninitialized P2P bridge resources,
		 * and clear them out so they get re-asचिन्हित later
		 */
		अगर (pcibios_uninitialized_bridge_resource(bus, res)) अणु
			res->flags = 0;
			pr_debug("PCI:%s            (unassigned)\n", pci_name(dev));
		पूर्ण
	पूर्ण
पूर्ण

व्योम pcibios_setup_bus_self(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *phb;

	/* Fix up the bus resources क्रम P2P bridges */
	अगर (bus->self != शून्य)
		pcibios_fixup_bridge(bus);

	/* Platक्रमm specअगरic bus fixups. This is currently only used
	 * by fsl_pci and I'm hoping to get rid of it at some poपूर्णांक
	 */
	अगर (ppc_md.pcibios_fixup_bus)
		ppc_md.pcibios_fixup_bus(bus);

	/* Setup bus DMA mappings */
	phb = pci_bus_to_host(bus);
	अगर (phb->controller_ops.dma_bus_setup)
		phb->controller_ops.dma_bus_setup(bus);
पूर्ण

व्योम pcibios_bus_add_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb;
	/* Fixup NUMA node as it may not be setup yet by the generic
	 * code and is needed by the DMA init
	 */
	set_dev_node(&dev->dev, pcibus_to_node(dev->bus));

	/* Hook up शेष DMA ops */
	set_dma_ops(&dev->dev, pci_dma_ops);
	dev->dev.archdata.dma_offset = PCI_DRAM_OFFSET;

	/* Additional platक्रमm DMA/iommu setup */
	phb = pci_bus_to_host(dev->bus);
	अगर (phb->controller_ops.dma_dev_setup)
		phb->controller_ops.dma_dev_setup(dev);

	/* Read शेष IRQs and fixup अगर necessary */
	pci_पढ़ो_irq_line(dev);
	अगर (ppc_md.pci_irq_fixup)
		ppc_md.pci_irq_fixup(dev);

	अगर (ppc_md.pcibios_bus_add_device)
		ppc_md.pcibios_bus_add_device(dev);
पूर्ण

पूर्णांक pcibios_add_device(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	अगर (ppc_md.pcibios_fixup_sriov)
		ppc_md.pcibios_fixup_sriov(dev);
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	वापस 0;
पूर्ण

व्योम pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	/* No special bus mastering setup handling */
पूर्ण

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	/* When called from the generic PCI probe, पढ़ो PCI<->PCI bridge
	 * bases. This is -not- called when generating the PCI tree from
	 * the OF device-tree.
	 */
	pci_पढ़ो_bridge_bases(bus);

	/* Now fixup the bus bus */
	pcibios_setup_bus_self(bus);
पूर्ण
EXPORT_SYMBOL(pcibios_fixup_bus);

अटल पूर्णांक skip_isa_ioresource_align(काष्ठा pci_dev *dev)
अणु
	अगर (pci_has_flag(PCI_CAN_SKIP_ISA_ALIGN) &&
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
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		अगर (skip_isa_ioresource_align(dev))
			वापस start;
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण

	वापस start;
पूर्ण
EXPORT_SYMBOL(pcibios_align_resource);

/*
 * Reparent resource children of pr that conflict with res
 * under res, and make res replace those children.
 */
अटल पूर्णांक reparent_resources(काष्ठा resource *parent,
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
		pr_debug("PCI: Reparented %s %pR under %s\n",
			 p->name, p, res->name);
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
		अगर (!res || !res->flags || res->start > res->end || res->parent)
			जारी;

		/* If the resource was left unset at this poपूर्णांक, we clear it */
		अगर (res->flags & IORESOURCE_UNSET)
			जाओ clear_resource;

		अगर (bus->parent == शून्य)
			pr = (res->flags & IORESOURCE_IO) ?
				&ioport_resource : &iomem_resource;
		अन्यथा अणु
			pr = pci_find_parent_resource(bus->self, res);
			अगर (pr == res) अणु
				/* this happens when the generic PCI
				 * code (wrongly) decides that this
				 * bridge is transparent  -- paulus
				 */
				जारी;
			पूर्ण
		पूर्ण

		pr_debug("PCI: %s (bus %d) bridge rsrc %d: %pR, parent %p (%s)\n",
			 bus->self ? pci_name(bus->self) : "PHB", bus->number,
			 i, res, pr, (pr && pr->name) ? pr->name : "nil");

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
		pr_warn("PCI: Cannot allocate resource region %d of PCI bridge %d, will remap\n",
			i, bus->number);
	clear_resource:
		/* The resource might be figured out when करोing
		 * reassignment based on the resources required
		 * by the करोwnstream PCI devices. Here we set
		 * the size of the resource to be 0 in order to
		 * save more space.
		 */
		res->start = 0;
		res->end = -1;
		res->flags = 0;
	पूर्ण

	list_क्रम_each_entry(b, &bus->children, node)
		pcibios_allocate_bus_resources(b);
पूर्ण

अटल अंतरभूत व्योम alloc_resource(काष्ठा pci_dev *dev, पूर्णांक idx)
अणु
	काष्ठा resource *pr, *r = &dev->resource[idx];

	pr_debug("PCI: Allocating %s: Resource %d: %pR\n",
		 pci_name(dev), idx, r);

	pr = pci_find_parent_resource(dev, r);
	अगर (!pr || (pr->flags & IORESOURCE_UNSET) ||
	    request_resource(pr, r) < 0) अणु
		prपूर्णांकk(KERN_WARNING "PCI: Cannot allocate resource region %d"
		       " of device %s, will remap\n", idx, pci_name(dev));
		अगर (pr)
			pr_debug("PCI:  parent is %p: %pR\n", pr, pr);
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
			अगर (idx == PCI_ROM_RESOURCE )
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

	pr_debug("Reserving legacy ranges for domain %04x\n", pci_करोमुख्य_nr(bus));

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
		prपूर्णांकk(KERN_DEBUG
		       "PCI %04x:%02x Cannot reserve Legacy IO %pR\n",
		       pci_करोमुख्य_nr(bus), bus->number, res);
		kमुक्त(res);
	पूर्ण

 no_io:
	/* Check क्रम memory */
	क्रम (i = 0; i < 3; i++) अणु
		pres = &hose->mem_resources[i];
		offset = hose->mem_offset[i];
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
		prपूर्णांकk(KERN_DEBUG
		       "PCI %04x:%02x Cannot reserve VGA memory %pR\n",
		       pci_करोमुख्य_nr(bus), bus->number, res);
		kमुक्त(res);
	पूर्ण
पूर्ण

व्योम __init pcibios_resource_survey(व्योम)
अणु
	काष्ठा pci_bus *b;

	/* Allocate and assign resources */
	list_क्रम_each_entry(b, &pci_root_buses, node)
		pcibios_allocate_bus_resources(b);
	अगर (!pci_has_flag(PCI_REASSIGN_ALL_RSRC)) अणु
		pcibios_allocate_resources(0);
		pcibios_allocate_resources(1);
	पूर्ण

	/* Beक्रमe we start assigning unasचिन्हित resource, we try to reserve
	 * the low IO area and the VGA memory area अगर they पूर्णांकersect the
	 * bus available resources to aव्योम allocating things on top of them
	 */
	अगर (!pci_has_flag(PCI_PROBE_ONLY)) अणु
		list_क्रम_each_entry(b, &pci_root_buses, node)
			pcibios_reserve_legacy_regions(b);
	पूर्ण

	/* Now, अगर the platक्रमm didn't decide to blindly trust the firmware,
	 * we proceed to assigning things that were left unasचिन्हित
	 */
	अगर (!pci_has_flag(PCI_PROBE_ONLY)) अणु
		pr_debug("PCI: Assigning unassigned resources...\n");
		pci_assign_unasचिन्हित_resources();
	पूर्ण
पूर्ण

/* This is used by the PCI hotplug driver to allocate resource
 * of newly plugged busses. We can try to consolidate with the
 * rest of the code later, क्रम now, keep it as-is as our मुख्य
 * resource allocation function करोesn't deal with sub-trees yet.
 */
व्योम pcibios_claim_one_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child_bus;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			काष्ठा resource *r = &dev->resource[i];

			अगर (r->parent || !r->start || !r->flags)
				जारी;

			pr_debug("PCI: Claiming %s: Resource %d: %pR\n",
				 pci_name(dev), i, r);

			अगर (pci_claim_resource(dev, i) == 0)
				जारी;

			pci_claim_bridge_resource(dev, i);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(child_bus, &bus->children, node)
		pcibios_claim_one_bus(child_bus);
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_claim_one_bus);


/* pcibios_finish_adding_to_bus
 *
 * This is to be called by the hotplug code after devices have been
 * added to a bus, this include calling it क्रम a PHB that is just
 * being added
 */
व्योम pcibios_finish_adding_to_bus(काष्ठा pci_bus *bus)
अणु
	pr_debug("PCI: Finishing adding to hotplug bus %04x:%02x\n",
		 pci_करोमुख्य_nr(bus), bus->number);

	/* Allocate bus and devices resources */
	pcibios_allocate_bus_resources(bus);
	pcibios_claim_one_bus(bus);
	अगर (!pci_has_flag(PCI_PROBE_ONLY)) अणु
		अगर (bus->self)
			pci_assign_unasचिन्हित_bridge_resources(bus->self);
		अन्यथा
			pci_assign_unasचिन्हित_bus_resources(bus);
	पूर्ण

	/* Add new devices to global lists.  Register in proc, sysfs. */
	pci_bus_add_devices(bus);
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_finish_adding_to_bus);

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);

	अगर (phb->controller_ops.enable_device_hook)
		अगर (!phb->controller_ops.enable_device_hook(dev))
			वापस -EINVAL;

	वापस pci_enable_resources(dev, mask);
पूर्ण

व्योम pcibios_disable_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *phb = pci_bus_to_host(dev->bus);

	अगर (phb->controller_ops.disable_device)
		phb->controller_ops.disable_device(dev);
पूर्ण

resource_माप_प्रकार pcibios_io_space_offset(काष्ठा pci_controller *hose)
अणु
	वापस (अचिन्हित दीर्घ) hose->io_base_virt - _IO_BASE;
पूर्ण

अटल व्योम pcibios_setup_phb_resources(काष्ठा pci_controller *hose,
					काष्ठा list_head *resources)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार offset;
	पूर्णांक i;

	/* Hookup PHB IO resource */
	res = &hose->io_resource;

	अगर (!res->flags) अणु
		pr_debug("PCI: I/O resource not set for host"
			 " bridge %pOF (domain %d)\n",
			 hose->dn, hose->global_number);
	पूर्ण अन्यथा अणु
		offset = pcibios_io_space_offset(hose);

		pr_debug("PCI: PHB IO resource    = %pR off 0x%08llx\n",
			 res, (अचिन्हित दीर्घ दीर्घ)offset);
		pci_add_resource_offset(resources, res, offset);
	पूर्ण

	/* Hookup PHB Memory resources */
	क्रम (i = 0; i < 3; ++i) अणु
		res = &hose->mem_resources[i];
		अगर (!res->flags)
			जारी;

		offset = hose->mem_offset[i];
		pr_debug("PCI: PHB MEM resource %d = %pR off 0x%08llx\n", i,
			 res, (अचिन्हित दीर्घ दीर्घ)offset);

		pci_add_resource_offset(resources, res, offset);
	पूर्ण
पूर्ण

/*
 * Null PCI config access functions, क्रम the हाल when we can't
 * find a hose.
 */
#घोषणा शून्य_PCI_OP(rw, size, type)					\
अटल पूर्णांक								\
null_##rw##_config_##size(काष्ठा pci_dev *dev, पूर्णांक offset, type val)	\
अणु									\
	वापस PCIBIOS_DEVICE_NOT_FOUND;    				\
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

अटल काष्ठा pci_ops null_pci_ops =
अणु
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

	अगर (hose == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Can't find hose for PCI bus %d!\n", busnr);
	पूर्ण
	bus.number = busnr;
	bus.sysdata = hose;
	bus.ops = hose? hose->ops: &null_pci_ops;
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

काष्ठा device_node *pcibios_get_phb_of_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	वापस of_node_get(hose->dn);
पूर्ण

/**
 * pci_scan_phb - Given a pci_controller, setup and scan the PCI bus
 * @hose: Poपूर्णांकer to the PCI host controller instance काष्ठाure
 */
व्योम pcibios_scan_phb(काष्ठा pci_controller *hose)
अणु
	LIST_HEAD(resources);
	काष्ठा pci_bus *bus;
	काष्ठा device_node *node = hose->dn;
	पूर्णांक mode;

	pr_debug("PCI: Scanning PHB %pOF\n", node);

	/* Get some IO space क्रम the new PHB */
	pcibios_setup_phb_io_space(hose);

	/* Wire up PHB bus resources */
	pcibios_setup_phb_resources(hose, &resources);

	hose->busn.start = hose->first_busno;
	hose->busn.end	 = hose->last_busno;
	hose->busn.flags = IORESOURCE_BUS;
	pci_add_resource(&resources, &hose->busn);

	/* Create an empty bus क्रम the toplevel */
	bus = pci_create_root_bus(hose->parent, hose->first_busno,
				  hose->ops, hose, &resources);
	अगर (bus == शून्य) अणु
		pr_err("Failed to create bus for PCI domain %04x\n",
			hose->global_number);
		pci_मुक्त_resource_list(&resources);
		वापस;
	पूर्ण
	hose->bus = bus;

	/* Get probe mode and perक्रमm scan */
	mode = PCI_PROBE_NORMAL;
	अगर (node && hose->controller_ops.probe_mode)
		mode = hose->controller_ops.probe_mode(bus);
	pr_debug("    probe mode: %d\n", mode);
	अगर (mode == PCI_PROBE_DEVTREE)
		of_scan_bus(node, bus);

	अगर (mode == PCI_PROBE_NORMAL) अणु
		pci_bus_update_busn_res_end(bus, 255);
		hose->last_busno = pci_scan_child_bus(bus);
		pci_bus_update_busn_res_end(bus, hose->last_busno);
	पूर्ण

	/* Platक्रमm माला_लो a chance to करो some global fixups beक्रमe
	 * we proceed to resource allocation
	 */
	अगर (ppc_md.pcibios_fixup_phb)
		ppc_md.pcibios_fixup_phb(hose);

	/* Configure PCI Express settings */
	अगर (bus && !pci_has_flag(PCI_PROBE_ONLY)) अणु
		काष्ठा pci_bus *child;
		list_क्रम_each_entry(child, &bus->children, node)
			pcie_bus_configure_settings(child);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_scan_phb);

अटल व्योम fixup_hide_host_resource_fsl(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i, class = dev->class >> 8;
	/* When configured as agent, programing पूर्णांकerface = 1 */
	पूर्णांक prog_अगर = dev->class & 0xf;

	अगर ((class == PCI_CLASS_PROCESSOR_POWERPC ||
	     class == PCI_CLASS_BRIDGE_OTHER) &&
		(dev->hdr_type == PCI_HEADER_TYPE_NORMAL) &&
		(prog_अगर == 0) &&
		(dev->bus->parent == शून्य)) अणु
		क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
			dev->resource[i].start = 0;
			dev->resource[i].end = 0;
			dev->resource[i].flags = 0;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MOTOROLA, PCI_ANY_ID, fixup_hide_host_resource_fsl);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_FREESCALE, PCI_ANY_ID, fixup_hide_host_resource_fsl);


अटल पूर्णांक __init discover_phbs(व्योम)
अणु
	अगर (ppc_md.discover_phbs)
		ppc_md.discover_phbs();

	वापस 0;
पूर्ण
core_initcall(discover_phbs);
