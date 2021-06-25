<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pci.c - Low-Level PCI Access in IA-64
 *
 * Derived from bios32.c of i386 tree.
 *
 * (c) Copyright 2002, 2005 Hewlett-Packard Development Company, L.P.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 * Copyright (C) 2004 Silicon Graphics, Inc.
 *
 * Note: Above list of copyright holders is incomplete...
 */

#समावेश <linux/acpi.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hw_irq.h>

/*
 * Low-level SAL-based PCI configuration access functions. Note that SAL
 * calls are alपढ़ोy serialized (via sal_lock), so we करोn't need another
 * synchronization mechanism here.
 */

#घोषणा PCI_SAL_ADDRESS(seg, bus, devfn, reg)		\
	(((u64) seg << 24) | (bus << 16) | (devfn << 8) | (reg))

/* SAL 3.2 adds support क्रम extended config space. */

#घोषणा PCI_SAL_EXT_ADDRESS(seg, bus, devfn, reg)	\
	(((u64) seg << 28) | (bus << 20) | (devfn << 12) | (reg))

पूर्णांक raw_pci_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
	      पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	u64 addr, data = 0;
	पूर्णांक mode, result;

	अगर (!value || (seg > 65535) || (bus > 255) || (devfn > 255) || (reg > 4095))
		वापस -EINVAL;

	अगर ((seg | reg) <= 255) अणु
		addr = PCI_SAL_ADDRESS(seg, bus, devfn, reg);
		mode = 0;
	पूर्ण अन्यथा अगर (sal_revision >= SAL_VERSION_CODE(3,2)) अणु
		addr = PCI_SAL_EXT_ADDRESS(seg, bus, devfn, reg);
		mode = 1;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	result = ia64_sal_pci_config_पढ़ो(addr, mode, len, &data);
	अगर (result != 0)
		वापस -EINVAL;

	*value = (u32) data;
	वापस 0;
पूर्ण

पूर्णांक raw_pci_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
	       पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	u64 addr;
	पूर्णांक mode, result;

	अगर ((seg > 65535) || (bus > 255) || (devfn > 255) || (reg > 4095))
		वापस -EINVAL;

	अगर ((seg | reg) <= 255) अणु
		addr = PCI_SAL_ADDRESS(seg, bus, devfn, reg);
		mode = 0;
	पूर्ण अन्यथा अगर (sal_revision >= SAL_VERSION_CODE(3,2)) अणु
		addr = PCI_SAL_EXT_ADDRESS(seg, bus, devfn, reg);
		mode = 1;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	result = ia64_sal_pci_config_ग_लिखो(addr, mode, len, value);
	अगर (result != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
							पूर्णांक size, u32 *value)
अणु
	वापस raw_pci_पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
				 devfn, where, size, value);
पूर्ण

अटल पूर्णांक pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
							पूर्णांक size, u32 value)
अणु
	वापस raw_pci_ग_लिखो(pci_करोमुख्य_nr(bus), bus->number,
				  devfn, where, size, value);
पूर्ण

काष्ठा pci_ops pci_root_ops = अणु
	.पढ़ो = pci_पढ़ो,
	.ग_लिखो = pci_ग_लिखो,
पूर्ण;

काष्ठा pci_root_info अणु
	काष्ठा acpi_pci_root_info common;
	काष्ठा pci_controller controller;
	काष्ठा list_head io_resources;
पूर्ण;

अटल अचिन्हित पूर्णांक new_space(u64 phys_base, पूर्णांक sparse)
अणु
	u64 mmio_base;
	पूर्णांक i;

	अगर (phys_base == 0)
		वापस 0;	/* legacy I/O port space */

	mmio_base = (u64) ioremap(phys_base, 0);
	क्रम (i = 0; i < num_io_spaces; i++)
		अगर (io_space[i].mmio_base == mmio_base &&
		    io_space[i].sparse == sparse)
			वापस i;

	अगर (num_io_spaces == MAX_IO_SPACES) अणु
		pr_err("PCI: Too many IO port spaces "
			"(MAX_IO_SPACES=%lu)\n", MAX_IO_SPACES);
		वापस ~0;
	पूर्ण

	i = num_io_spaces++;
	io_space[i].mmio_base = mmio_base;
	io_space[i].sparse = sparse;

	वापस i;
पूर्ण

अटल पूर्णांक add_io_space(काष्ठा device *dev, काष्ठा pci_root_info *info,
			काष्ठा resource_entry *entry)
अणु
	काष्ठा resource_entry *iospace;
	काष्ठा resource *resource, *res = entry->res;
	अक्षर *name;
	अचिन्हित दीर्घ base, min, max, base_port;
	अचिन्हित पूर्णांक sparse = 0, space_nr, len;

	len = म_माप(info->common.name) + 32;
	iospace = resource_list_create_entry(शून्य, len);
	अगर (!iospace) अणु
		dev_err(dev, "PCI: No memory for %s I/O port space\n",
			info->common.name);
		वापस -ENOMEM;
	पूर्ण

	अगर (res->flags & IORESOURCE_IO_SPARSE)
		sparse = 1;
	space_nr = new_space(entry->offset, sparse);
	अगर (space_nr == ~0)
		जाओ मुक्त_resource;

	name = (अक्षर *)(iospace + 1);
	min = res->start - entry->offset;
	max = res->end - entry->offset;
	base = __pa(io_space[space_nr].mmio_base);
	base_port = IO_SPACE_BASE(space_nr);
	snम_लिखो(name, len, "%s I/O Ports %08lx-%08lx", info->common.name,
		 base_port + min, base_port + max);

	/*
	 * The SDM guarantees the legacy 0-64K space is sparse, but अगर the
	 * mapping is करोne by the processor (not the bridge), ACPI may not
	 * mark it as sparse.
	 */
	अगर (space_nr == 0)
		sparse = 1;

	resource = iospace->res;
	resource->name  = name;
	resource->flags = IORESOURCE_MEM;
	resource->start = base + (sparse ? IO_SPACE_SPARSE_ENCODING(min) : min);
	resource->end   = base + (sparse ? IO_SPACE_SPARSE_ENCODING(max) : max);
	अगर (insert_resource(&iomem_resource, resource)) अणु
		dev_err(dev,
			"can't allocate host bridge io space resource  %pR\n",
			resource);
		जाओ मुक्त_resource;
	पूर्ण

	entry->offset = base_port;
	res->start = min + base_port;
	res->end = max + base_port;
	resource_list_add_tail(iospace, &info->io_resources);

	वापस 0;

मुक्त_resource:
	resource_list_मुक्त_entry(iospace);
	वापस -ENOSPC;
पूर्ण

/*
 * An IO port or MMIO resource asचिन्हित to a PCI host bridge may be
 * consumed by the host bridge itself or available to its child
 * bus/devices. The ACPI specअगरication defines a bit (Producer/Consumer)
 * to tell whether the resource is consumed by the host bridge itself,
 * but firmware hasn't used that bit consistently, so we can't rely on it.
 *
 * On x86 and IA64 platक्रमms, all IO port and MMIO resources are assumed
 * to be available to child bus/devices except one special हाल:
 *     IO port [0xCF8-0xCFF] is consumed by the host bridge itself
 *     to access PCI configuration space.
 *
 * So explicitly filter out PCI CFG IO ports[0xCF8-0xCFF].
 */
अटल bool resource_is_pcicfg_ioport(काष्ठा resource *res)
अणु
	वापस (res->flags & IORESOURCE_IO) &&
		res->start == 0xCF8 && res->end == 0xCFF;
पूर्ण

अटल पूर्णांक pci_acpi_root_prepare_resources(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा device *dev = &ci->bridge->dev;
	काष्ठा pci_root_info *info;
	काष्ठा resource *res;
	काष्ठा resource_entry *entry, *पंचांगp;
	पूर्णांक status;

	status = acpi_pci_probe_root_resources(ci);
	अगर (status > 0) अणु
		info = container_of(ci, काष्ठा pci_root_info, common);
		resource_list_क्रम_each_entry_safe(entry, पंचांगp, &ci->resources) अणु
			res = entry->res;
			अगर (res->flags & IORESOURCE_MEM) अणु
				/*
				 * HP's firmware has a hack to work around a
				 * Winकरोws bug. Ignore these tiny memory ranges.
				 */
				अगर (resource_size(res) <= 16) अणु
					resource_list_del(entry);
					insert_resource(&iomem_resource,
							entry->res);
					resource_list_add_tail(entry,
							&info->io_resources);
				पूर्ण
			पूर्ण अन्यथा अगर (res->flags & IORESOURCE_IO) अणु
				अगर (resource_is_pcicfg_ioport(entry->res))
					resource_list_destroy_entry(entry);
				अन्यथा अगर (add_io_space(dev, info, entry))
					resource_list_destroy_entry(entry);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम pci_acpi_root_release_info(काष्ठा acpi_pci_root_info *ci)
अणु
	काष्ठा pci_root_info *info;
	काष्ठा resource_entry *entry, *पंचांगp;

	info = container_of(ci, काष्ठा pci_root_info, common);
	resource_list_क्रम_each_entry_safe(entry, पंचांगp, &info->io_resources) अणु
		release_resource(entry->res);
		resource_list_destroy_entry(entry);
	पूर्ण
	kमुक्त(info);
पूर्ण

अटल काष्ठा acpi_pci_root_ops pci_acpi_root_ops = अणु
	.pci_ops = &pci_root_ops,
	.release_info = pci_acpi_root_release_info,
	.prepare_resources = pci_acpi_root_prepare_resources,
पूर्ण;

काष्ठा pci_bus *pci_acpi_scan_root(काष्ठा acpi_pci_root *root)
अणु
	काष्ठा acpi_device *device = root->device;
	काष्ठा pci_root_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		dev_err(&device->dev,
			"pci_bus %04x:%02x: ignored (out of memory)\n",
			root->segment, (पूर्णांक)root->secondary.start);
		वापस शून्य;
	पूर्ण

	info->controller.segment = root->segment;
	info->controller.companion = device;
	info->controller.node = acpi_get_node(device->handle);
	INIT_LIST_HEAD(&info->io_resources);
	वापस acpi_pci_root_create(root, &pci_acpi_root_ops,
				    &info->common, &info->controller);
पूर्ण

पूर्णांक pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	/*
	 * We pass शून्य as parent to pci_create_root_bus(), so अगर it is not शून्य
	 * here, pci_create_root_bus() has been called by someone अन्यथा and
	 * sysdata is likely to be dअगरferent from what we expect.  Let it go in
	 * that हाल.
	 */
	अगर (!bridge->dev.parent) अणु
		काष्ठा pci_controller *controller = bridge->bus->sysdata;
		ACPI_COMPANION_SET(&bridge->dev, controller->companion);
	पूर्ण
	वापस 0;
पूर्ण

व्योम pcibios_fixup_device_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक idx;

	अगर (!dev->bus)
		वापस;

	क्रम (idx = 0; idx < PCI_BRIDGE_RESOURCES; idx++) अणु
		काष्ठा resource *r = &dev->resource[idx];

		अगर (!r->flags || r->parent || !r->start)
			जारी;

		pci_claim_resource(dev, idx);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pcibios_fixup_device_resources);

अटल व्योम pcibios_fixup_bridge_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक idx;

	अगर (!dev->bus)
		वापस;

	क्रम (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES; idx++) अणु
		काष्ठा resource *r = &dev->resource[idx];

		अगर (!r->flags || r->parent || !r->start)
			जारी;

		pci_claim_bridge_resource(dev, idx);
	पूर्ण
पूर्ण

/*
 *  Called after each bus is probed, but beक्रमe its children are examined.
 */
व्योम pcibios_fixup_bus(काष्ठा pci_bus *b)
अणु
	काष्ठा pci_dev *dev;

	अगर (b->self) अणु
		pci_पढ़ो_bridge_bases(b);
		pcibios_fixup_bridge_resources(b->self);
	पूर्ण
	list_क्रम_each_entry(dev, &b->devices, bus_list)
		pcibios_fixup_device_resources(dev);
पूर्ण

व्योम pcibios_add_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_add_bus(bus);
पूर्ण

व्योम pcibios_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
	acpi_pci_हटाओ_bus(bus);
पूर्ण

व्योम pcibios_set_master (काष्ठा pci_dev *dev)
अणु
	/* No special bus mastering setup handling */
पूर्ण

पूर्णांक
pcibios_enable_device (काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	पूर्णांक ret;

	ret = pci_enable_resources(dev, mask);
	अगर (ret < 0)
		वापस ret;

	अगर (!pci_dev_msi_enabled(dev))
		वापस acpi_pci_irq_enable(dev);
	वापस 0;
पूर्ण

व्योम
pcibios_disable_device (काष्ठा pci_dev *dev)
अणु
	BUG_ON(atomic_पढ़ो(&dev->enable_cnt));
	अगर (!pci_dev_msi_enabled(dev))
		acpi_pci_irq_disable(dev);
पूर्ण

/**
 * pci_get_legacy_mem - generic legacy mem routine
 * @bus: bus to get legacy memory base address क्रम
 *
 * Find the base of legacy memory क्रम @bus.  This is typically the first
 * megabyte of bus address space क्रम @bus or is simply 0 on platक्रमms whose
 * chipsets support legacy I/O and memory routing.  Returns the base address
 * or an error poपूर्णांकer अगर an error occurred.
 *
 * This is the ia64 generic version of this routine.  Other platक्रमms
 * are मुक्त to override it with a machine vector.
 */
अक्षर *pci_get_legacy_mem(काष्ठा pci_bus *bus)
अणु
	वापस (अक्षर *)__IA64_UNCACHED_OFFSET;
पूर्ण

/**
 * pci_mmap_legacy_page_range - map legacy memory space to userland
 * @bus: bus whose legacy space we're mapping
 * @vma: vma passed in by mmap
 *
 * Map legacy memory space क्रम this device back to userspace using a machine
 * vector to get the base address.
 */
पूर्णांक
pci_mmap_legacy_page_range(काष्ठा pci_bus *bus, काष्ठा vm_area_काष्ठा *vma,
			   क्रमागत pci_mmap_state mmap_state)
अणु
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	pgprot_t prot;
	अक्षर *addr;

	/* We only support mmap'ing of legacy memory space */
	अगर (mmap_state != pci_mmap_mem)
		वापस -ENOSYS;

	/*
	 * Aव्योम attribute aliasing.  See Documentation/ia64/aliasing.rst
	 * क्रम more details.
	 */
	अगर (!valid_mmap_phys_addr_range(vma->vm_pgoff, size))
		वापस -EINVAL;
	prot = phys_mem_access_prot(शून्य, vma->vm_pgoff, size,
				    vma->vm_page_prot);

	addr = pci_get_legacy_mem(bus);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	vma->vm_pgoff += (अचिन्हित दीर्घ)addr >> PAGE_SHIFT;
	vma->vm_page_prot = prot;

	अगर (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			    size, vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

/**
 * pci_legacy_पढ़ो - पढ़ो from legacy I/O space
 * @bus: bus to पढ़ो
 * @port: legacy port value
 * @val: caller allocated storage क्रम वापसed value
 * @size: number of bytes to पढ़ो
 *
 * Simply पढ़ोs @size bytes from @port and माला_दो the result in @val.
 *
 * Again, this (and the ग_लिखो routine) are generic versions that can be
 * overridden by the platक्रमm.  This is necessary on platक्रमms that करोn't
 * support legacy I/O routing or that hard fail on legacy I/O समयouts.
 */
पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, u16 port, u32 *val, u8 size)
अणु
	पूर्णांक ret = size;

	चयन (size) अणु
	हाल 1:
		*val = inb(port);
		अवरोध;
	हाल 2:
		*val = inw(port);
		अवरोध;
	हाल 4:
		*val = inl(port);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pci_legacy_ग_लिखो - perक्रमm a legacy I/O ग_लिखो
 * @bus: bus poपूर्णांकer
 * @port: port to ग_लिखो
 * @val: value to ग_लिखो
 * @size: number of bytes to ग_लिखो from @val
 *
 * Simply ग_लिखोs @size bytes of @val to @port.
 */
पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, u16 port, u32 val, u8 size)
अणु
	पूर्णांक ret = size;

	चयन (size) अणु
	हाल 1:
		outb(val, port);
		अवरोध;
	हाल 2:
		outw(val, port);
		अवरोध;
	हाल 4:
		outl(val, port);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * set_pci_cacheline_size - determine cacheline size क्रम PCI devices
 *
 * We want to use the line-size of the outer-most cache.  We assume
 * that this line-size is the same क्रम all CPUs.
 *
 * Code mostly taken from arch/ia64/kernel/palinfo.c:cache_info().
 */
अटल व्योम __init set_pci_dfl_cacheline_size(व्योम)
अणु
	अचिन्हित दीर्घ levels, unique_caches;
	दीर्घ status;
	pal_cache_config_info_t cci;

	status = ia64_pal_cache_summary(&levels, &unique_caches);
	अगर (status != 0) अणु
		pr_err("%s: ia64_pal_cache_summary() failed "
			"(status=%ld)\n", __func__, status);
		वापस;
	पूर्ण

	status = ia64_pal_cache_config_info(levels - 1,
				/* cache_type (data_or_unअगरied)= */ 2, &cci);
	अगर (status != 0) अणु
		pr_err("%s: ia64_pal_cache_config_info() failed "
			"(status=%ld)\n", __func__, status);
		वापस;
	पूर्ण
	pci_dfl_cache_line_size = (1 << cci.pcci_line_size) / 4;
पूर्ण

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	set_pci_dfl_cacheline_size();
	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);
