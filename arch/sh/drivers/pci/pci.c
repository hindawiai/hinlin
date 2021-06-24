<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * New-style PCI core.
 *
 * Copyright (c) 2004 - 2009  Paul Mundt
 * Copyright (c) 2002  M. R. Brown
 *
 * Modelled after arch/mips/pci/pci.c:
 *  Copyright (C) 2003, 04 Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>

अचिन्हित दीर्घ PCIBIOS_MIN_IO = 0x0000;
अचिन्हित दीर्घ PCIBIOS_MIN_MEM = 0;

/*
 * The PCI controller list.
 */
अटल काष्ठा pci_channel *hose_head, **hose_tail = &hose_head;

अटल पूर्णांक pci_initialized;

अटल व्योम pcibios_scanbus(काष्ठा pci_channel *hose)
अणु
	अटल पूर्णांक next_busno;
	अटल पूर्णांक need_करोमुख्य_info;
	LIST_HEAD(resources);
	काष्ठा resource *res;
	resource_माप_प्रकार offset;
	पूर्णांक i, ret;
	काष्ठा pci_host_bridge *bridge;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस;

	क्रम (i = 0; i < hose->nr_resources; i++) अणु
		res = hose->resources + i;
		offset = 0;
		अगर (res->flags & IORESOURCE_DISABLED)
			जारी;
		अगर (res->flags & IORESOURCE_IO)
			offset = hose->io_offset;
		अन्यथा अगर (res->flags & IORESOURCE_MEM)
			offset = hose->mem_offset;
		pci_add_resource_offset(&resources, res, offset);
	पूर्ण

	list_splice_init(&resources, &bridge->winकरोws);
	bridge->dev.parent = शून्य;
	bridge->sysdata = hose;
	bridge->busnr = next_busno;
	bridge->ops = hose->pci_ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = pcibios_map_platक्रमm_irq;

	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस;
	पूर्ण

	hose->bus = bridge->bus;

	need_करोमुख्य_info = need_करोमुख्य_info || hose->index;
	hose->need_करोमुख्य_info = need_करोमुख्य_info;

	next_busno = hose->bus->busn_res.end + 1;
	/* Don't allow 8-bit bus number overflow inside the hose -
	   reserve some space क्रम bridges. */
	अगर (next_busno > 224) अणु
		next_busno = 0;
		need_करोमुख्य_info = 1;
	पूर्ण

	pci_bus_size_bridges(hose->bus);
	pci_bus_assign_resources(hose->bus);
	pci_bus_add_devices(hose->bus);
पूर्ण

/*
 * This पूर्णांकerrupt-safe spinlock protects all accesses to PCI
 * configuration space.
 */
DEFINE_RAW_SPINLOCK(pci_config_lock);
अटल DEFINE_MUTEX(pci_scan_mutex);

पूर्णांक रेजिस्टर_pci_controller(काष्ठा pci_channel *hose)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hose->nr_resources; i++) अणु
		काष्ठा resource *res = hose->resources + i;

		अगर (res->flags & IORESOURCE_DISABLED)
			जारी;

		अगर (res->flags & IORESOURCE_IO) अणु
			अगर (request_resource(&ioport_resource, res) < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (request_resource(&iomem_resource, res) < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	*hose_tail = hose;
	hose_tail = &hose->next;

	/*
	 * Do not panic here but later - this might happen beक्रमe console init.
	 */
	अगर (!hose->io_map_base) अणु
		pr_warn("registering PCI controller with io_map_base unset\n");
	पूर्ण

	/*
	 * Setup the ERR/PERR and SERR समयrs, अगर available.
	 */
	pcibios_enable_समयrs(hose);

	/*
	 * Scan the bus अगर it is रेजिस्टर after the PCI subप्रणाली
	 * initialization.
	 */
	अगर (pci_initialized) अणु
		mutex_lock(&pci_scan_mutex);
		pcibios_scanbus(hose);
		mutex_unlock(&pci_scan_mutex);
	पूर्ण

	वापस 0;

out:
	क्रम (--i; i >= 0; i--)
		release_resource(&hose->resources[i]);

	pr_warn("Skipping PCI bus scan due to resource conflict\n");
	वापस -1;
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	काष्ठा pci_channel *hose;

	/* Scan all of the recorded PCI controllers.  */
	क्रम (hose = hose_head; hose; hose = hose->next)
		pcibios_scanbus(hose);

	pci_initialized = 1;

	वापस 0;
पूर्ण
subsys_initcall(pcibios_init);

/*
 * We need to aव्योम collisions with `mirrored' VGA ports
 * and other strange ISA hardware, so we always want the
 * addresses to be allocated in the 0x000-0x0ff region
 * modulo 0x400.
 */
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	काष्ठा pci_channel *hose = dev->sysdata;
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		अगर (start < PCIBIOS_MIN_IO + hose->resources[0].start)
			start = PCIBIOS_MIN_IO + hose->resources[0].start;

		/*
                 * Put everything पूर्णांकo 0x00-0xff region modulo 0x400.
		 */
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण

	वापस start;
पूर्ण

अटल व्योम __init
pcibios_bus_report_status_early(काष्ठा pci_channel *hose,
				पूर्णांक top_bus, पूर्णांक current_bus,
				अचिन्हित पूर्णांक status_mask, पूर्णांक warn)
अणु
	अचिन्हित पूर्णांक pci_devfn;
	u16 status;
	पूर्णांक ret;

	क्रम (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) अणु
		अगर (PCI_FUNC(pci_devfn))
			जारी;
		ret = early_पढ़ो_config_word(hose, top_bus, current_bus,
					     pci_devfn, PCI_STATUS, &status);
		अगर (ret != PCIBIOS_SUCCESSFUL)
			जारी;
		अगर (status == 0xffff)
			जारी;

		early_ग_लिखो_config_word(hose, top_bus, current_bus,
					pci_devfn, PCI_STATUS,
					status & status_mask);
		अगर (warn)
			pr_cont("(%02x:%02x: %04X) ", current_bus, pci_devfn,
				status);
	पूर्ण
पूर्ण

/*
 * We can't use pci_find_device() here since we are
 * called from पूर्णांकerrupt context.
 */
अटल व्योम __ref
pcibios_bus_report_status(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक status_mask,
			  पूर्णांक warn)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		u16 status;

		/*
		 * ignore host bridge - we handle
		 * that separately
		 */
		अगर (dev->bus->number == 0 && dev->devfn == 0)
			जारी;

		pci_पढ़ो_config_word(dev, PCI_STATUS, &status);
		अगर (status == 0xffff)
			जारी;

		अगर ((status & status_mask) == 0)
			जारी;

		/* clear the status errors */
		pci_ग_लिखो_config_word(dev, PCI_STATUS, status & status_mask);

		अगर (warn)
			pr_cont("(%s: %04X) ", pci_name(dev), status);
	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list)
		अगर (dev->subordinate)
			pcibios_bus_report_status(dev->subordinate, status_mask, warn);
पूर्ण

व्योम __ref pcibios_report_status(अचिन्हित पूर्णांक status_mask, पूर्णांक warn)
अणु
	काष्ठा pci_channel *hose;

	क्रम (hose = hose_head; hose; hose = hose->next) अणु
		अगर (unlikely(!hose->bus))
			pcibios_bus_report_status_early(hose, hose_head->index,
					hose->index, status_mask, warn);
		अन्यथा
			pcibios_bus_report_status(hose->bus, status_mask, warn);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_GENERIC_IOMAP

व्योम __iomem *__pci_ioport_map(काष्ठा pci_dev *dev,
			       अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा pci_channel *chan = dev->sysdata;

	अगर (unlikely(!chan->io_map_base)) अणु
		chan->io_map_base = sh_io_port_base;

		अगर (pci_करोमुख्यs_supported)
			panic("To avoid data corruption io_map_base MUST be "
			      "set with multiple PCI domains.");
	पूर्ण

	वापस (व्योम __iomem *)(chan->io_map_base + port);
पूर्ण

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr)
अणु
	iounmap(addr);
पूर्ण
EXPORT_SYMBOL(pci_iounmap);

#पूर्ण_अगर /* CONFIG_GENERIC_IOMAP */

EXPORT_SYMBOL(PCIBIOS_MIN_IO);
EXPORT_SYMBOL(PCIBIOS_MIN_MEM);
