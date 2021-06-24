<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/kernel/pci-sysfs.c
 *
 * Copyright (C) 2009 Ivan Kokshaysky
 *
 * Alpha PCI resource files.
 *
 * Loosely based on generic HAVE_PCI_MMAP implementation in
 * drivers/pci/pci-sysfs.c
 */

#समावेश <linux/sched.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>

अटल पूर्णांक hose_mmap_page_range(काष्ठा pci_controller *hose,
				काष्ठा vm_area_काष्ठा *vma,
				क्रमागत pci_mmap_state mmap_type, पूर्णांक sparse)
अणु
	अचिन्हित दीर्घ base;

	अगर (mmap_type == pci_mmap_mem)
		base = sparse ? hose->sparse_mem_base : hose->dense_mem_base;
	अन्यथा
		base = sparse ? hose->sparse_io_base : hose->dense_io_base;

	vma->vm_pgoff += base >> PAGE_SHIFT;

	वापस io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				  vma->vm_end - vma->vm_start,
				  vma->vm_page_prot);
पूर्ण

अटल पूर्णांक __pci_mmap_fits(काष्ठा pci_dev *pdev, पूर्णांक num,
			   काष्ठा vm_area_काष्ठा *vma, पूर्णांक sparse)
अणु
	अचिन्हित दीर्घ nr, start, size;
	पूर्णांक shअगरt = sparse ? 5 : 0;

	nr = vma_pages(vma);
	start = vma->vm_pgoff;
	size = ((pci_resource_len(pdev, num) - 1) >> (PAGE_SHIFT - shअगरt)) + 1;

	अगर (start < size && size - start >= nr)
		वापस 1;
	WARN(1, "process \"%s\" tried to map%s 0x%08lx-0x%08lx on %s BAR %d "
		"(size 0x%08lx)\n",
		current->comm, sparse ? " sparse" : "", start, start + nr,
		pci_name(pdev), num, size);
	वापस 0;
पूर्ण

/**
 * pci_mmap_resource - map a PCI resource पूर्णांकo user memory space
 * @kobj: kobject क्रम mapping
 * @attr: काष्ठा bin_attribute क्रम the file being mapped
 * @vma: काष्ठा vm_area_काष्ठा passed पूर्णांकo the mmap
 * @sparse: address space type
 *
 * Use the bus mapping routines to map a PCI resource पूर्णांकo userspace.
 */
अटल पूर्णांक pci_mmap_resource(काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *attr,
			     काष्ठा vm_area_काष्ठा *vma, पूर्णांक sparse)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	काष्ठा resource *res = attr->निजी;
	क्रमागत pci_mmap_state mmap_type;
	काष्ठा pci_bus_region bar;
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++)
		अगर (res == &pdev->resource[i])
			अवरोध;
	अगर (i >= PCI_STD_NUM_BARS)
		वापस -ENODEV;

	अगर (res->flags & IORESOURCE_MEM && iomem_is_exclusive(res->start))
		वापस -EINVAL;

	अगर (!__pci_mmap_fits(pdev, i, vma, sparse))
		वापस -EINVAL;

	pcibios_resource_to_bus(pdev->bus, &bar, res);
	vma->vm_pgoff += bar.start >> (PAGE_SHIFT - (sparse ? 5 : 0));
	mmap_type = res->flags & IORESOURCE_MEM ? pci_mmap_mem : pci_mmap_io;

	वापस hose_mmap_page_range(pdev->sysdata, vma, mmap_type, sparse);
पूर्ण

अटल पूर्णांक pci_mmap_resource_sparse(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *attr,
				    काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस pci_mmap_resource(kobj, attr, vma, 1);
पूर्ण

अटल पूर्णांक pci_mmap_resource_dense(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *attr,
				   काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस pci_mmap_resource(kobj, attr, vma, 0);
पूर्ण

/**
 * pci_हटाओ_resource_files - cleanup resource files
 * @dev: dev to cleanup
 *
 * If we created resource files क्रम @dev, हटाओ them from sysfs and
 * मुक्त their resources.
 */
व्योम pci_हटाओ_resource_files(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		काष्ठा bin_attribute *res_attr;

		res_attr = pdev->res_attr[i];
		अगर (res_attr) अणु
			sysfs_हटाओ_bin_file(&pdev->dev.kobj, res_attr);
			kमुक्त(res_attr);
		पूर्ण

		res_attr = pdev->res_attr_wc[i];
		अगर (res_attr) अणु
			sysfs_हटाओ_bin_file(&pdev->dev.kobj, res_attr);
			kमुक्त(res_attr);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sparse_mem_mmap_fits(काष्ठा pci_dev *pdev, पूर्णांक num)
अणु
	काष्ठा pci_bus_region bar;
	काष्ठा pci_controller *hose = pdev->sysdata;
	दीर्घ dense_offset;
	अचिन्हित दीर्घ sparse_size;

	pcibios_resource_to_bus(pdev->bus, &bar, &pdev->resource[num]);

	/* All core logic chips have 4G sparse address space, except
	   CIA which has 16G (see xxx_SPARSE_MEM and xxx_DENSE_MEM
	   definitions in यंत्र/core_xxx.h files). This corresponds
	   to 128M or 512M of the bus space. */
	dense_offset = (दीर्घ)(hose->dense_mem_base - hose->sparse_mem_base);
	sparse_size = dense_offset >= 0x400000000UL ? 0x20000000 : 0x8000000;

	वापस bar.end < sparse_size;
पूर्ण

अटल पूर्णांक pci_create_one_attr(काष्ठा pci_dev *pdev, पूर्णांक num, अक्षर *name,
			       अक्षर *suffix, काष्ठा bin_attribute *res_attr,
			       अचिन्हित दीर्घ sparse)
अणु
	माप_प्रकार size = pci_resource_len(pdev, num);

	प्र_लिखो(name, "resource%d%s", num, suffix);
	res_attr->mmap = sparse ? pci_mmap_resource_sparse :
				  pci_mmap_resource_dense;
	res_attr->attr.name = name;
	res_attr->attr.mode = S_IRUSR | S_IWUSR;
	res_attr->size = sparse ? size << 5 : size;
	res_attr->निजी = &pdev->resource[num];
	वापस sysfs_create_bin_file(&pdev->dev.kobj, res_attr);
पूर्ण

अटल पूर्णांक pci_create_attr(काष्ठा pci_dev *pdev, पूर्णांक num)
अणु
	/* allocate attribute काष्ठाure, piggyback attribute name */
	पूर्णांक retval, nlen1, nlen2 = 0, res_count = 1;
	अचिन्हित दीर्घ sparse_base, dense_base;
	काष्ठा bin_attribute *attr;
	काष्ठा pci_controller *hose = pdev->sysdata;
	अक्षर *suffix, *attr_name;

	suffix = "";	/* Assume bwx machine, normal resourceN files. */
	nlen1 = 10;

	अगर (pdev->resource[num].flags & IORESOURCE_MEM) अणु
		sparse_base = hose->sparse_mem_base;
		dense_base = hose->dense_mem_base;
		अगर (sparse_base && !sparse_mem_mmap_fits(pdev, num)) अणु
			sparse_base = 0;
			suffix = "_dense";
			nlen1 = 16;	/* resourceN_dense */
		पूर्ण
	पूर्ण अन्यथा अणु
		sparse_base = hose->sparse_io_base;
		dense_base = hose->dense_io_base;
	पूर्ण

	अगर (sparse_base) अणु
		suffix = "_sparse";
		nlen1 = 17;
		अगर (dense_base) अणु
			nlen2 = 16;	/* resourceN_dense */
			res_count = 2;
		पूर्ण
	पूर्ण

	attr = kzalloc(माप(*attr) * res_count + nlen1 + nlen2, GFP_ATOMIC);
	अगर (!attr)
		वापस -ENOMEM;

	/* Create bwx, sparse or single dense file */
	attr_name = (अक्षर *)(attr + res_count);
	pdev->res_attr[num] = attr;
	retval = pci_create_one_attr(pdev, num, attr_name, suffix, attr,
				     sparse_base);
	अगर (retval || res_count == 1)
		वापस retval;

	/* Create dense file */
	attr_name += nlen1;
	attr++;
	pdev->res_attr_wc[num] = attr;
	वापस pci_create_one_attr(pdev, num, attr_name, "_dense", attr, 0);
पूर्ण

/**
 * pci_create_resource_files - create resource files in sysfs क्रम @dev
 * @dev: dev in question
 *
 * Walk the resources in @dev creating files क्रम each resource available.
 */
पूर्णांक pci_create_resource_files(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	पूर्णांक retval;

	/* Expose the PCI resources from this device as files */
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु

		/* skip empty resources */
		अगर (!pci_resource_len(pdev, i))
			जारी;

		retval = pci_create_attr(pdev, i);
		अगर (retval) अणु
			pci_हटाओ_resource_files(pdev);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Legacy I/O bus mapping stuff. */

अटल पूर्णांक __legacy_mmap_fits(काष्ठा pci_controller *hose,
			      काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ res_size, पूर्णांक sparse)
अणु
	अचिन्हित दीर्घ nr, start, size;

	nr = vma_pages(vma);
	start = vma->vm_pgoff;
	size = ((res_size - 1) >> PAGE_SHIFT) + 1;

	अगर (start < size && size - start >= nr)
		वापस 1;
	WARN(1, "process \"%s\" tried to map%s 0x%08lx-0x%08lx on hose %d "
		"(size 0x%08lx)\n",
		current->comm, sparse ? " sparse" : "", start, start + nr,
		hose->index, size);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक has_sparse(काष्ठा pci_controller *hose,
			     क्रमागत pci_mmap_state mmap_type)
अणु
	अचिन्हित दीर्घ base;

	base = (mmap_type == pci_mmap_mem) ? hose->sparse_mem_base :
					     hose->sparse_io_base;

	वापस base != 0;
पूर्ण

पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus, काष्ठा vm_area_काष्ठा *vma,
			       क्रमागत pci_mmap_state mmap_type)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;
	पूर्णांक sparse = has_sparse(hose, mmap_type);
	अचिन्हित दीर्घ res_size;

	res_size = (mmap_type == pci_mmap_mem) ? bus->legacy_mem->size :
						 bus->legacy_io->size;
	अगर (!__legacy_mmap_fits(hose, vma, res_size, sparse))
		वापस -EINVAL;

	वापस hose_mmap_page_range(hose, vma, mmap_type, sparse);
पूर्ण

/**
 * pci_adjust_legacy_attr - adjusपंचांगent of legacy file attributes
 * @b: bus to create files under
 * @mmap_type: I/O port or memory
 *
 * Adjust file name and size क्रम sparse mappings.
 */
व्योम pci_adjust_legacy_attr(काष्ठा pci_bus *bus, क्रमागत pci_mmap_state mmap_type)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	अगर (!has_sparse(hose, mmap_type))
		वापस;

	अगर (mmap_type == pci_mmap_mem) अणु
		bus->legacy_mem->attr.name = "legacy_mem_sparse";
		bus->legacy_mem->size <<= 5;
	पूर्ण अन्यथा अणु
		bus->legacy_io->attr.name = "legacy_io_sparse";
		bus->legacy_io->size <<= 5;
	पूर्ण
	वापस;
पूर्ण

/* Legacy I/O bus पढ़ो/ग_लिखो functions */
पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, loff_t port, u32 *val, माप_प्रकार size)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	port += hose->io_space->start;

	चयन(size) अणु
	हाल 1:
		*((u8 *)val) = inb(port);
		वापस 1;
	हाल 2:
		अगर (port & 1)
			वापस -EINVAL;
		*((u16 *)val) = inw(port);
		वापस 2;
	हाल 4:
		अगर (port & 3)
			वापस -EINVAL;
		*((u32 *)val) = inl(port);
		वापस 4;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, loff_t port, u32 val, माप_प्रकार size)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	port += hose->io_space->start;

	चयन(size) अणु
	हाल 1:
		outb(port, val);
		वापस 1;
	हाल 2:
		अगर (port & 1)
			वापस -EINVAL;
		outw(port, val);
		वापस 2;
	हाल 4:
		अगर (port & 3)
			वापस -EINVAL;
		outl(port, val);
		वापस 4;
	पूर्ण
	वापस -EINVAL;
पूर्ण
