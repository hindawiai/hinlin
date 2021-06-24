<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016-2018 Intel Corporation. All rights reserved. */
#समावेश <linux/memremap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश "dax-private.h"
#समावेश "bus.h"

अटल पूर्णांक check_vma(काष्ठा dev_dax *dev_dax, काष्ठा vm_area_काष्ठा *vma,
		स्थिर अक्षर *func)
अणु
	काष्ठा device *dev = &dev_dax->dev;
	अचिन्हित दीर्घ mask;

	अगर (!dax_alive(dev_dax->dax_dev))
		वापस -ENXIO;

	/* prevent निजी mappings from being established */
	अगर ((vma->vm_flags & VM_MAYSHARE) != VM_MAYSHARE) अणु
		dev_info_ratelimited(dev,
				"%s: %s: fail, attempted private mapping\n",
				current->comm, func);
		वापस -EINVAL;
	पूर्ण

	mask = dev_dax->align - 1;
	अगर (vma->vm_start & mask || vma->vm_end & mask) अणु
		dev_info_ratelimited(dev,
				"%s: %s: fail, unaligned vma (%#lx - %#lx, %#lx)\n",
				current->comm, func, vma->vm_start, vma->vm_end,
				mask);
		वापस -EINVAL;
	पूर्ण

	अगर (!vma_is_dax(vma)) अणु
		dev_info_ratelimited(dev,
				"%s: %s: fail, vma is not DAX capable\n",
				current->comm, func);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* see "strong" declaration in tools/testing/nvdimm/dax-dev.c */
__weak phys_addr_t dax_pgoff_to_phys(काष्ठा dev_dax *dev_dax, pgoff_t pgoff,
		अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		काष्ठा dev_dax_range *dax_range = &dev_dax->ranges[i];
		काष्ठा range *range = &dax_range->range;
		अचिन्हित दीर्घ दीर्घ pgoff_end;
		phys_addr_t phys;

		pgoff_end = dax_range->pgoff + PHYS_PFN(range_len(range)) - 1;
		अगर (pgoff < dax_range->pgoff || pgoff > pgoff_end)
			जारी;
		phys = PFN_PHYS(pgoff - dax_range->pgoff) + range->start;
		अगर (phys + size - 1 <= range->end)
			वापस phys;
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

अटल vm_fault_t __dev_dax_pte_fault(काष्ठा dev_dax *dev_dax,
				काष्ठा vm_fault *vmf, pfn_t *pfn)
अणु
	काष्ठा device *dev = &dev_dax->dev;
	phys_addr_t phys;
	अचिन्हित पूर्णांक fault_size = PAGE_SIZE;

	अगर (check_vma(dev_dax, vmf->vma, __func__))
		वापस VM_FAULT_SIGBUS;

	अगर (dev_dax->align > PAGE_SIZE) अणु
		dev_dbg(dev, "alignment (%#x) > fault size (%#x)\n",
			dev_dax->align, fault_size);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	अगर (fault_size != dev_dax->align)
		वापस VM_FAULT_SIGBUS;

	phys = dax_pgoff_to_phys(dev_dax, vmf->pgoff, PAGE_SIZE);
	अगर (phys == -1) अणु
		dev_dbg(dev, "pgoff_to_phys(%#lx) failed\n", vmf->pgoff);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	*pfn = phys_to_pfn_t(phys, PFN_DEV|PFN_MAP);

	वापस vmf_insert_mixed(vmf->vma, vmf->address, *pfn);
पूर्ण

अटल vm_fault_t __dev_dax_pmd_fault(काष्ठा dev_dax *dev_dax,
				काष्ठा vm_fault *vmf, pfn_t *pfn)
अणु
	अचिन्हित दीर्घ pmd_addr = vmf->address & PMD_MASK;
	काष्ठा device *dev = &dev_dax->dev;
	phys_addr_t phys;
	pgoff_t pgoff;
	अचिन्हित पूर्णांक fault_size = PMD_SIZE;

	अगर (check_vma(dev_dax, vmf->vma, __func__))
		वापस VM_FAULT_SIGBUS;

	अगर (dev_dax->align > PMD_SIZE) अणु
		dev_dbg(dev, "alignment (%#x) > fault size (%#x)\n",
			dev_dax->align, fault_size);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	अगर (fault_size < dev_dax->align)
		वापस VM_FAULT_SIGBUS;
	अन्यथा अगर (fault_size > dev_dax->align)
		वापस VM_FAULT_FALLBACK;

	/* अगर we are outside of the VMA */
	अगर (pmd_addr < vmf->vma->vm_start ||
			(pmd_addr + PMD_SIZE) > vmf->vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	pgoff = linear_page_index(vmf->vma, pmd_addr);
	phys = dax_pgoff_to_phys(dev_dax, pgoff, PMD_SIZE);
	अगर (phys == -1) अणु
		dev_dbg(dev, "pgoff_to_phys(%#lx) failed\n", pgoff);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	*pfn = phys_to_pfn_t(phys, PFN_DEV|PFN_MAP);

	वापस vmf_insert_pfn_pmd(vmf, *pfn, vmf->flags & FAULT_FLAG_WRITE);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल vm_fault_t __dev_dax_pud_fault(काष्ठा dev_dax *dev_dax,
				काष्ठा vm_fault *vmf, pfn_t *pfn)
अणु
	अचिन्हित दीर्घ pud_addr = vmf->address & PUD_MASK;
	काष्ठा device *dev = &dev_dax->dev;
	phys_addr_t phys;
	pgoff_t pgoff;
	अचिन्हित पूर्णांक fault_size = PUD_SIZE;


	अगर (check_vma(dev_dax, vmf->vma, __func__))
		वापस VM_FAULT_SIGBUS;

	अगर (dev_dax->align > PUD_SIZE) अणु
		dev_dbg(dev, "alignment (%#x) > fault size (%#x)\n",
			dev_dax->align, fault_size);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	अगर (fault_size < dev_dax->align)
		वापस VM_FAULT_SIGBUS;
	अन्यथा अगर (fault_size > dev_dax->align)
		वापस VM_FAULT_FALLBACK;

	/* अगर we are outside of the VMA */
	अगर (pud_addr < vmf->vma->vm_start ||
			(pud_addr + PUD_SIZE) > vmf->vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	pgoff = linear_page_index(vmf->vma, pud_addr);
	phys = dax_pgoff_to_phys(dev_dax, pgoff, PUD_SIZE);
	अगर (phys == -1) अणु
		dev_dbg(dev, "pgoff_to_phys(%#lx) failed\n", pgoff);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	*pfn = phys_to_pfn_t(phys, PFN_DEV|PFN_MAP);

	वापस vmf_insert_pfn_pud(vmf, *pfn, vmf->flags & FAULT_FLAG_WRITE);
पूर्ण
#अन्यथा
अटल vm_fault_t __dev_dax_pud_fault(काष्ठा dev_dax *dev_dax,
				काष्ठा vm_fault *vmf, pfn_t *pfn)
अणु
	वापस VM_FAULT_FALLBACK;
पूर्ण
#पूर्ण_अगर /* !CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */

अटल vm_fault_t dev_dax_huge_fault(काष्ठा vm_fault *vmf,
		क्रमागत page_entry_size pe_size)
अणु
	काष्ठा file *filp = vmf->vma->vm_file;
	अचिन्हित दीर्घ fault_size;
	vm_fault_t rc = VM_FAULT_SIGBUS;
	पूर्णांक id;
	pfn_t pfn;
	काष्ठा dev_dax *dev_dax = filp->निजी_data;

	dev_dbg(&dev_dax->dev, "%s: %s (%#lx - %#lx) size = %d\n", current->comm,
			(vmf->flags & FAULT_FLAG_WRITE) ? "write" : "read",
			vmf->vma->vm_start, vmf->vma->vm_end, pe_size);

	id = dax_पढ़ो_lock();
	चयन (pe_size) अणु
	हाल PE_SIZE_PTE:
		fault_size = PAGE_SIZE;
		rc = __dev_dax_pte_fault(dev_dax, vmf, &pfn);
		अवरोध;
	हाल PE_SIZE_PMD:
		fault_size = PMD_SIZE;
		rc = __dev_dax_pmd_fault(dev_dax, vmf, &pfn);
		अवरोध;
	हाल PE_SIZE_PUD:
		fault_size = PUD_SIZE;
		rc = __dev_dax_pud_fault(dev_dax, vmf, &pfn);
		अवरोध;
	शेष:
		rc = VM_FAULT_SIGBUS;
	पूर्ण

	अगर (rc == VM_FAULT_NOPAGE) अणु
		अचिन्हित दीर्घ i;
		pgoff_t pgoff;

		/*
		 * In the device-dax हाल the only possibility क्रम a
		 * VM_FAULT_NOPAGE result is when device-dax capacity is
		 * mapped. No need to consider the zero page, or racing
		 * conflicting mappings.
		 */
		pgoff = linear_page_index(vmf->vma, vmf->address
				& ~(fault_size - 1));
		क्रम (i = 0; i < fault_size / PAGE_SIZE; i++) अणु
			काष्ठा page *page;

			page = pfn_to_page(pfn_t_to_pfn(pfn) + i);
			अगर (page->mapping)
				जारी;
			page->mapping = filp->f_mapping;
			page->index = pgoff + i;
		पूर्ण
	पूर्ण
	dax_पढ़ो_unlock(id);

	वापस rc;
पूर्ण

अटल vm_fault_t dev_dax_fault(काष्ठा vm_fault *vmf)
अणु
	वापस dev_dax_huge_fault(vmf, PE_SIZE_PTE);
पूर्ण

अटल पूर्णांक dev_dax_may_split(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा file *filp = vma->vm_file;
	काष्ठा dev_dax *dev_dax = filp->निजी_data;

	अगर (!IS_ALIGNED(addr, dev_dax->align))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ dev_dax_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *filp = vma->vm_file;
	काष्ठा dev_dax *dev_dax = filp->निजी_data;

	वापस dev_dax->align;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा dax_vm_ops = अणु
	.fault = dev_dax_fault,
	.huge_fault = dev_dax_huge_fault,
	.may_split = dev_dax_may_split,
	.pagesize = dev_dax_pagesize,
पूर्ण;

अटल पूर्णांक dax_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा dev_dax *dev_dax = filp->निजी_data;
	पूर्णांक rc, id;

	dev_dbg(&dev_dax->dev, "trace\n");

	/*
	 * We lock to check dax_dev liveness and will re-check at
	 * fault समय.
	 */
	id = dax_पढ़ो_lock();
	rc = check_vma(dev_dax, vma, __func__);
	dax_पढ़ो_unlock(id);
	अगर (rc)
		वापस rc;

	vma->vm_ops = &dax_vm_ops;
	vma->vm_flags |= VM_HUGEPAGE;
	वापस 0;
पूर्ण

/* वापस an unmapped area aligned to the dax region specअगरied alignment */
अटल अचिन्हित दीर्घ dax_get_unmapped_area(काष्ठा file *filp,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ off, off_end, off_align, len_align, addr_align, align;
	काष्ठा dev_dax *dev_dax = filp ? filp->निजी_data : शून्य;

	अगर (!dev_dax || addr)
		जाओ out;

	align = dev_dax->align;
	off = pgoff << PAGE_SHIFT;
	off_end = off + len;
	off_align = round_up(off, align);

	अगर ((off_end <= off_align) || ((off_end - off_align) < align))
		जाओ out;

	len_align = len + align;
	अगर ((off + len_align) < off)
		जाओ out;

	addr_align = current->mm->get_unmapped_area(filp, addr, len_align,
			pgoff, flags);
	अगर (!IS_ERR_VALUE(addr_align)) अणु
		addr_align += (off - addr_align) & (align - 1);
		वापस addr_align;
	पूर्ण
 out:
	वापस current->mm->get_unmapped_area(filp, addr, len, pgoff, flags);
पूर्ण

अटल स्थिर काष्ठा address_space_operations dev_dax_aops = अणु
	.set_page_dirty		= noop_set_page_dirty,
	.invalidatepage		= noop_invalidatepage,
पूर्ण;

अटल पूर्णांक dax_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dax_device *dax_dev = inode_dax(inode);
	काष्ठा inode *__dax_inode = dax_inode(dax_dev);
	काष्ठा dev_dax *dev_dax = dax_get_निजी(dax_dev);

	dev_dbg(&dev_dax->dev, "trace\n");
	inode->i_mapping = __dax_inode->i_mapping;
	inode->i_mapping->host = __dax_inode;
	inode->i_mapping->a_ops = &dev_dax_aops;
	filp->f_mapping = inode->i_mapping;
	filp->f_wb_err = filemap_sample_wb_err(filp->f_mapping);
	filp->f_sb_err = file_sample_sb_err(filp);
	filp->निजी_data = dev_dax;
	inode->i_flags = S_DAX;

	वापस 0;
पूर्ण

अटल पूर्णांक dax_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dev_dax *dev_dax = filp->निजी_data;

	dev_dbg(&dev_dax->dev, "trace\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations dax_fops = अणु
	.llseek = noop_llseek,
	.owner = THIS_MODULE,
	.खोलो = dax_खोलो,
	.release = dax_release,
	.get_unmapped_area = dax_get_unmapped_area,
	.mmap = dax_mmap,
	.mmap_supported_flags = MAP_SYNC,
पूर्ण;

अटल व्योम dev_dax_cdev_del(व्योम *cdev)
अणु
	cdev_del(cdev);
पूर्ण

अटल व्योम dev_dax_समाप्त(व्योम *dev_dax)
अणु
	समाप्त_dev_dax(dev_dax);
पूर्ण

पूर्णांक dev_dax_probe(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा dax_device *dax_dev = dev_dax->dax_dev;
	काष्ठा device *dev = &dev_dax->dev;
	काष्ठा dev_pagemap *pgmap;
	काष्ठा inode *inode;
	काष्ठा cdev *cdev;
	व्योम *addr;
	पूर्णांक rc, i;

	pgmap = dev_dax->pgmap;
	अगर (dev_WARN_ONCE(dev, pgmap && dev_dax->nr_range > 1,
			"static pgmap / multi-range device conflict\n"))
		वापस -EINVAL;

	अगर (!pgmap) अणु
		pgmap = devm_kzalloc(dev, माप(*pgmap) + माप(काष्ठा range)
				* (dev_dax->nr_range - 1), GFP_KERNEL);
		अगर (!pgmap)
			वापस -ENOMEM;
		pgmap->nr_range = dev_dax->nr_range;
	पूर्ण

	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		काष्ठा range *range = &dev_dax->ranges[i].range;

		अगर (!devm_request_mem_region(dev, range->start,
					range_len(range), dev_name(dev))) अणु
			dev_warn(dev, "mapping%d: %#llx-%#llx could not reserve range\n",
					i, range->start, range->end);
			वापस -EBUSY;
		पूर्ण
		/* करोn't update the range क्रम अटल pgmap */
		अगर (!dev_dax->pgmap)
			pgmap->ranges[i] = *range;
	पूर्ण

	pgmap->type = MEMORY_DEVICE_GENERIC;
	addr = devm_memremap_pages(dev, pgmap);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	inode = dax_inode(dax_dev);
	cdev = inode->i_cdev;
	cdev_init(cdev, &dax_fops);
	अगर (dev->class) अणु
		/* क्रम the CONFIG_DEV_DAX_PMEM_COMPAT हाल */
		cdev->owner = dev->parent->driver->owner;
	पूर्ण अन्यथा
		cdev->owner = dev->driver->owner;
	cdev_set_parent(cdev, &dev->kobj);
	rc = cdev_add(cdev, dev->devt, 1);
	अगर (rc)
		वापस rc;

	rc = devm_add_action_or_reset(dev, dev_dax_cdev_del, cdev);
	अगर (rc)
		वापस rc;

	run_dax(dax_dev);
	वापस devm_add_action_or_reset(dev, dev_dax_समाप्त, dev_dax);
पूर्ण
EXPORT_SYMBOL_GPL(dev_dax_probe);

अटल काष्ठा dax_device_driver device_dax_driver = अणु
	.probe = dev_dax_probe,
	/* all probe actions are unwound by devm, so .हटाओ isn't necessary */
	.match_always = 1,
पूर्ण;

अटल पूर्णांक __init dax_init(व्योम)
अणु
	वापस dax_driver_रेजिस्टर(&device_dax_driver);
पूर्ण

अटल व्योम __निकास dax_निकास(व्योम)
अणु
	dax_driver_unरेजिस्टर(&device_dax_driver);
पूर्ण

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
module_init(dax_init);
module_निकास(dax_निकास);
MODULE_ALIAS_DAX_DEVICE(0);
