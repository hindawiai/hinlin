<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic PCI resource mmap helper
 *
 * Copyright तऊ 2017 Amazon.com, Inc. or its affiliates.
 *
 * Author: David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>

#अगर_घोषित ARCH_GENERIC_PCI_MMAP_RESOURCE

/*
 * Modern setup: generic pci_mmap_resource_range(), and implement the legacy
 * pci_mmap_page_range() (अगर needed) as a wrapper round it.
 */

#अगर_घोषित HAVE_PCI_MMAP
पूर्णांक pci_mmap_page_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
			काष्ठा vm_area_काष्ठा *vma,
			क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine)
अणु
	resource_माप_प्रकार start, end;

	pci_resource_to_user(pdev, bar, &pdev->resource[bar], &start, &end);

	/* Adjust vm_pgoff to be the offset within the resource */
	vma->vm_pgoff -= start >> PAGE_SHIFT;
	वापस pci_mmap_resource_range(pdev, bar, vma, mmap_state,
				       ग_लिखो_combine);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा vm_operations_काष्ठा pci_phys_vm_ops = अणु
#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#पूर्ण_अगर
पूर्ण;

पूर्णांक pci_mmap_resource_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
			    काष्ठा vm_area_काष्ठा *vma,
			    क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine)
अणु
	अचिन्हित दीर्घ size;
	पूर्णांक ret;

	size = ((pci_resource_len(pdev, bar) - 1) >> PAGE_SHIFT) + 1;
	अगर (vma->vm_pgoff + vma_pages(vma) > size)
		वापस -EINVAL;

	अगर (ग_लिखो_combine)
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	अन्यथा
		vma->vm_page_prot = pgprot_device(vma->vm_page_prot);

	अगर (mmap_state == pci_mmap_io) अणु
		ret = pci_iobar_pfn(pdev, bar, vma);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		vma->vm_pgoff += (pci_resource_start(pdev, bar) >> PAGE_SHIFT);

	vma->vm_ops = &pci_phys_vm_ops;

	वापस io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				  vma->vm_end - vma->vm_start,
				  vma->vm_page_prot);
पूर्ण

#या_अगर defined(HAVE_PCI_MMAP) /* && !ARCH_GENERIC_PCI_MMAP_RESOURCE */

/*
 * Legacy setup: Implement pci_mmap_resource_range() as a wrapper around
 * the architecture's pci_mmap_page_range(), converting to "user visible"
 * addresses as necessary.
 */

पूर्णांक pci_mmap_resource_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
			    काष्ठा vm_area_काष्ठा *vma,
			    क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine)
अणु
	resource_माप_प्रकार start, end;

	/*
	 * pci_mmap_page_range() expects the same kind of entry as coming
	 * from /proc/bus/pci/ which is a "user visible" value. If this is
	 * dअगरferent from the resource itself, arch will करो necessary fixup.
	 */
	pci_resource_to_user(pdev, bar, &pdev->resource[bar], &start, &end);
	vma->vm_pgoff += start >> PAGE_SHIFT;
	वापस pci_mmap_page_range(pdev, bar, vma, mmap_state, ग_लिखो_combine);
पूर्ण
#पूर्ण_अगर
