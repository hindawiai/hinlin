<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOMMU API क्रम s390 PCI devices
 *
 * Copyright IBM Corp. 2015
 * Author(s): Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/iommu.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/pci_dma.h>

/*
 * Physically contiguous memory regions can be mapped with 4 KiB alignment,
 * we allow all page sizes that are an order of 4KiB (no special large page
 * support so far).
 */
#घोषणा S390_IOMMU_PGSIZES	(~0xFFFUL)

अटल स्थिर काष्ठा iommu_ops s390_iommu_ops;

काष्ठा s390_करोमुख्य अणु
	काष्ठा iommu_करोमुख्य	करोमुख्य;
	काष्ठा list_head	devices;
	अचिन्हित दीर्घ		*dma_table;
	spinlock_t		dma_table_lock;
	spinlock_t		list_lock;
पूर्ण;

काष्ठा s390_करोमुख्य_device अणु
	काष्ठा list_head	list;
	काष्ठा zpci_dev		*zdev;
पूर्ण;

अटल काष्ठा s390_करोमुख्य *to_s390_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा s390_करोमुख्य, करोमुख्य);
पूर्ण

अटल bool s390_iommu_capable(क्रमागत iommu_cap cap)
अणु
	चयन (cap) अणु
	हाल IOMMU_CAP_CACHE_COHERENCY:
		वापस true;
	हाल IOMMU_CAP_INTR_REMAP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा iommu_करोमुख्य *s390_करोमुख्य_alloc(अचिन्हित करोमुख्य_type)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य;

	अगर (करोमुख्य_type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	s390_करोमुख्य = kzalloc(माप(*s390_करोमुख्य), GFP_KERNEL);
	अगर (!s390_करोमुख्य)
		वापस शून्य;

	s390_करोमुख्य->dma_table = dma_alloc_cpu_table();
	अगर (!s390_करोमुख्य->dma_table) अणु
		kमुक्त(s390_करोमुख्य);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&s390_करोमुख्य->dma_table_lock);
	spin_lock_init(&s390_करोमुख्य->list_lock);
	INIT_LIST_HEAD(&s390_करोमुख्य->devices);

	वापस &s390_करोमुख्य->करोमुख्य;
पूर्ण

अटल व्योम s390_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);

	dma_cleanup_tables(s390_करोमुख्य->dma_table);
	kमुक्त(s390_करोमुख्य);
पूर्ण

अटल पूर्णांक s390_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा device *dev)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);
	काष्ठा zpci_dev *zdev = to_zpci_dev(dev);
	काष्ठा s390_करोमुख्य_device *करोमुख्य_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!zdev)
		वापस -ENODEV;

	करोमुख्य_device = kzalloc(माप(*करोमुख्य_device), GFP_KERNEL);
	अगर (!करोमुख्य_device)
		वापस -ENOMEM;

	अगर (zdev->dma_table)
		zpci_dma_निकास_device(zdev);

	zdev->dma_table = s390_करोमुख्य->dma_table;
	rc = zpci_रेजिस्टर_ioat(zdev, 0, zdev->start_dma, zdev->end_dma,
				(u64) zdev->dma_table);
	अगर (rc)
		जाओ out_restore;

	spin_lock_irqsave(&s390_करोमुख्य->list_lock, flags);
	/* First device defines the DMA range limits */
	अगर (list_empty(&s390_करोमुख्य->devices)) अणु
		करोमुख्य->geometry.aperture_start = zdev->start_dma;
		करोमुख्य->geometry.aperture_end = zdev->end_dma;
		करोमुख्य->geometry.क्रमce_aperture = true;
	/* Allow only devices with identical DMA range limits */
	पूर्ण अन्यथा अगर (करोमुख्य->geometry.aperture_start != zdev->start_dma ||
		   करोमुख्य->geometry.aperture_end != zdev->end_dma) अणु
		rc = -EINVAL;
		spin_unlock_irqrestore(&s390_करोमुख्य->list_lock, flags);
		जाओ out_restore;
	पूर्ण
	करोमुख्य_device->zdev = zdev;
	zdev->s390_करोमुख्य = s390_करोमुख्य;
	list_add(&करोमुख्य_device->list, &s390_करोमुख्य->devices);
	spin_unlock_irqrestore(&s390_करोमुख्य->list_lock, flags);

	वापस 0;

out_restore:
	zpci_dma_init_device(zdev);
	kमुक्त(करोमुख्य_device);

	वापस rc;
पूर्ण

अटल व्योम s390_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);
	काष्ठा zpci_dev *zdev = to_zpci_dev(dev);
	काष्ठा s390_करोमुख्य_device *करोमुख्य_device, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;

	अगर (!zdev)
		वापस;

	spin_lock_irqsave(&s390_करोमुख्य->list_lock, flags);
	list_क्रम_each_entry_safe(करोमुख्य_device, पंचांगp, &s390_करोमुख्य->devices,
				 list) अणु
		अगर (करोमुख्य_device->zdev == zdev) अणु
			list_del(&करोमुख्य_device->list);
			kमुक्त(करोमुख्य_device);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&s390_करोमुख्य->list_lock, flags);

	अगर (found) अणु
		zdev->s390_करोमुख्य = शून्य;
		zpci_unरेजिस्टर_ioat(zdev, 0);
		zpci_dma_init_device(zdev);
	पूर्ण
पूर्ण

अटल काष्ठा iommu_device *s390_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci_dev(dev);

	वापस &zdev->iommu_dev;
पूर्ण

अटल व्योम s390_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci_dev(dev);
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	/*
	 * This is a workaround क्रम a scenario where the IOMMU API common code
	 * "forgets" to call the detach_dev callback: After binding a device
	 * to vfio-pci and completing the VFIO_SET_IOMMU ioctl (which triggers
	 * the attach_dev), removing the device via
	 * "echo 1 > /sys/bus/pci/devices/.../remove" won't trigger detach_dev,
	 * only release_device will be called via the BUS_NOTIFY_REMOVED_DEVICE
	 * notअगरier.
	 *
	 * So let's call detach_dev from here if it hasn't been called beक्रमe.
	 */
	अगर (zdev && zdev->s390_करोमुख्य) अणु
		करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
		अगर (करोमुख्य)
			s390_iommu_detach_device(करोमुख्य, dev);
	पूर्ण
पूर्ण

अटल पूर्णांक s390_iommu_update_trans(काष्ठा s390_करोमुख्य *s390_करोमुख्य,
				   अचिन्हित दीर्घ pa, dma_addr_t dma_addr,
				   माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा s390_करोमुख्य_device *करोमुख्य_device;
	u8 *page_addr = (u8 *) (pa & PAGE_MASK);
	dma_addr_t start_dma_addr = dma_addr;
	अचिन्हित दीर्घ irq_flags, nr_pages, i;
	अचिन्हित दीर्घ *entry;
	पूर्णांक rc = 0;

	अगर (dma_addr < s390_करोमुख्य->करोमुख्य.geometry.aperture_start ||
	    dma_addr + size > s390_करोमुख्य->करोमुख्य.geometry.aperture_end)
		वापस -EINVAL;

	nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	अगर (!nr_pages)
		वापस 0;

	spin_lock_irqsave(&s390_करोमुख्य->dma_table_lock, irq_flags);
	क्रम (i = 0; i < nr_pages; i++) अणु
		entry = dma_walk_cpu_trans(s390_करोमुख्य->dma_table, dma_addr);
		अगर (!entry) अणु
			rc = -ENOMEM;
			जाओ unकरो_cpu_trans;
		पूर्ण
		dma_update_cpu_trans(entry, page_addr, flags);
		page_addr += PAGE_SIZE;
		dma_addr += PAGE_SIZE;
	पूर्ण

	spin_lock(&s390_करोमुख्य->list_lock);
	list_क्रम_each_entry(करोमुख्य_device, &s390_करोमुख्य->devices, list) अणु
		rc = zpci_refresh_trans((u64) करोमुख्य_device->zdev->fh << 32,
					start_dma_addr, nr_pages * PAGE_SIZE);
		अगर (rc)
			अवरोध;
	पूर्ण
	spin_unlock(&s390_करोमुख्य->list_lock);

unकरो_cpu_trans:
	अगर (rc && ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID)) अणु
		flags = ZPCI_PTE_INVALID;
		जबतक (i-- > 0) अणु
			page_addr -= PAGE_SIZE;
			dma_addr -= PAGE_SIZE;
			entry = dma_walk_cpu_trans(s390_करोमुख्य->dma_table,
						   dma_addr);
			अगर (!entry)
				अवरोध;
			dma_update_cpu_trans(entry, page_addr, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&s390_करोमुख्य->dma_table_lock, irq_flags);

	वापस rc;
पूर्ण

अटल पूर्णांक s390_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);
	पूर्णांक flags = ZPCI_PTE_VALID, rc = 0;

	अगर (!(prot & IOMMU_READ))
		वापस -EINVAL;

	अगर (!(prot & IOMMU_WRITE))
		flags |= ZPCI_TABLE_PROTECTED;

	rc = s390_iommu_update_trans(s390_करोमुख्य, (अचिन्हित दीर्घ) paddr, iova,
				     size, flags);

	वापस rc;
पूर्ण

अटल phys_addr_t s390_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t iova)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ *sto, *pto, *rto, flags;
	अचिन्हित पूर्णांक rtx, sx, px;
	phys_addr_t phys = 0;

	अगर (iova < करोमुख्य->geometry.aperture_start ||
	    iova > करोमुख्य->geometry.aperture_end)
		वापस 0;

	rtx = calc_rtx(iova);
	sx = calc_sx(iova);
	px = calc_px(iova);
	rto = s390_करोमुख्य->dma_table;

	spin_lock_irqsave(&s390_करोमुख्य->dma_table_lock, flags);
	अगर (rto && reg_entry_isvalid(rto[rtx])) अणु
		sto = get_rt_sto(rto[rtx]);
		अगर (sto && reg_entry_isvalid(sto[sx])) अणु
			pto = get_st_pto(sto[sx]);
			अगर (pto && pt_entry_isvalid(pto[px]))
				phys = pto[px] & ZPCI_PTE_ADDR_MASK;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&s390_करोमुख्य->dma_table_lock, flags);

	वापस phys;
पूर्ण

अटल माप_प्रकार s390_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
			       अचिन्हित दीर्घ iova, माप_प्रकार size,
			       काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा s390_करोमुख्य *s390_करोमुख्य = to_s390_करोमुख्य(करोमुख्य);
	पूर्णांक flags = ZPCI_PTE_INVALID;
	phys_addr_t paddr;
	पूर्णांक rc;

	paddr = s390_iommu_iova_to_phys(करोमुख्य, iova);
	अगर (!paddr)
		वापस 0;

	rc = s390_iommu_update_trans(s390_करोमुख्य, (अचिन्हित दीर्घ) paddr, iova,
				     size, flags);
	अगर (rc)
		वापस 0;

	वापस size;
पूर्ण

पूर्णांक zpci_init_iommu(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc = 0;

	rc = iommu_device_sysfs_add(&zdev->iommu_dev, शून्य, शून्य,
				    "s390-iommu.%08x", zdev->fid);
	अगर (rc)
		जाओ out_err;

	rc = iommu_device_रेजिस्टर(&zdev->iommu_dev, &s390_iommu_ops, शून्य);
	अगर (rc)
		जाओ out_sysfs;

	वापस 0;

out_sysfs:
	iommu_device_sysfs_हटाओ(&zdev->iommu_dev);

out_err:
	वापस rc;
पूर्ण

व्योम zpci_destroy_iommu(काष्ठा zpci_dev *zdev)
अणु
	iommu_device_unरेजिस्टर(&zdev->iommu_dev);
	iommu_device_sysfs_हटाओ(&zdev->iommu_dev);
पूर्ण

अटल स्थिर काष्ठा iommu_ops s390_iommu_ops = अणु
	.capable = s390_iommu_capable,
	.करोमुख्य_alloc = s390_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = s390_करोमुख्य_मुक्त,
	.attach_dev = s390_iommu_attach_device,
	.detach_dev = s390_iommu_detach_device,
	.map = s390_iommu_map,
	.unmap = s390_iommu_unmap,
	.iova_to_phys = s390_iommu_iova_to_phys,
	.probe_device = s390_iommu_probe_device,
	.release_device = s390_iommu_release_device,
	.device_group = generic_device_group,
	.pgsize_biपंचांगap = S390_IOMMU_PGSIZES,
पूर्ण;

अटल पूर्णांक __init s390_iommu_init(व्योम)
अणु
	वापस bus_set_iommu(&pci_bus_type, &s390_iommu_ops);
पूर्ण
subsys_initcall(s390_iommu_init);
