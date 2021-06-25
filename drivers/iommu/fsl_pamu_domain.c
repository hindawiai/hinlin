<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 * Author: Varun Sethi <varun.sethi@मुक्तscale.com>
 */

#घोषणा pr_fmt(fmt)    "fsl-pamu-domain: %s: " fmt, __func__

#समावेश "fsl_pamu_domain.h"

#समावेश <sysdev/fsl_pci.h>

/*
 * Global spinlock that needs to be held जबतक
 * configuring PAMU.
 */
अटल DEFINE_SPINLOCK(iommu_lock);

अटल काष्ठा kmem_cache *fsl_pamu_करोमुख्य_cache;
अटल काष्ठा kmem_cache *iommu_devinfo_cache;
अटल DEFINE_SPINLOCK(device_करोमुख्य_lock);

काष्ठा iommu_device pamu_iommu;	/* IOMMU core code handle */

अटल काष्ठा fsl_dma_करोमुख्य *to_fsl_dma_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा fsl_dma_करोमुख्य, iommu_करोमुख्य);
पूर्ण

अटल पूर्णांक __init iommu_init_mempool(व्योम)
अणु
	fsl_pamu_करोमुख्य_cache = kmem_cache_create("fsl_pamu_domain",
						  माप(काष्ठा fsl_dma_करोमुख्य),
						  0,
						  SLAB_HWCACHE_ALIGN,
						  शून्य);
	अगर (!fsl_pamu_करोमुख्य_cache) अणु
		pr_debug("Couldn't create fsl iommu_domain cache\n");
		वापस -ENOMEM;
	पूर्ण

	iommu_devinfo_cache = kmem_cache_create("iommu_devinfo",
						माप(काष्ठा device_करोमुख्य_info),
						0,
						SLAB_HWCACHE_ALIGN,
						शून्य);
	अगर (!iommu_devinfo_cache) अणु
		pr_debug("Couldn't create devinfo cache\n");
		kmem_cache_destroy(fsl_pamu_करोमुख्य_cache);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक update_liodn_stash(पूर्णांक liodn, काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य,
			      u32 val)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu_lock, flags);
	ret = pamu_update_paace_stash(liodn, val);
	अगर (ret) अणु
		pr_debug("Failed to update SPAACE for liodn %d\n ", liodn);
		spin_unlock_irqrestore(&iommu_lock, flags);
		वापस ret;
	पूर्ण

	spin_unlock_irqrestore(&iommu_lock, flags);

	वापस ret;
पूर्ण

/* Set the geometry parameters क्रम a LIODN */
अटल पूर्णांक pamu_set_liodn(काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य, काष्ठा device *dev,
			  पूर्णांक liodn)
अणु
	u32 omi_index = ~(u32)0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Configure the omi_index at the geometry setup समय.
	 * This is a अटल value which depends on the type of
	 * device and would not change thereafter.
	 */
	get_ome_index(&omi_index, dev);

	spin_lock_irqsave(&iommu_lock, flags);
	ret = pamu_disable_liodn(liodn);
	अगर (ret)
		जाओ out_unlock;
	ret = pamu_config_ppaace(liodn, omi_index, dma_करोमुख्य->stash_id, 0);
	अगर (ret)
		जाओ out_unlock;
	ret = pamu_config_ppaace(liodn, ~(u32)0, dma_करोमुख्य->stash_id,
				 PAACE_AP_PERMS_QUERY | PAACE_AP_PERMS_UPDATE);
out_unlock:
	spin_unlock_irqrestore(&iommu_lock, flags);
	अगर (ret) अणु
		pr_debug("PAACE configuration failed for liodn %d\n",
			 liodn);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम हटाओ_device_ref(काष्ठा device_करोमुख्य_info *info)
अणु
	अचिन्हित दीर्घ flags;

	list_del(&info->link);
	spin_lock_irqsave(&iommu_lock, flags);
	pamu_disable_liodn(info->liodn);
	spin_unlock_irqrestore(&iommu_lock, flags);
	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	dev_iommu_priv_set(info->dev, शून्य);
	kmem_cache_मुक्त(iommu_devinfo_cache, info);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
पूर्ण

अटल व्योम detach_device(काष्ठा device *dev, काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य)
अणु
	काष्ठा device_करोमुख्य_info *info, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dma_करोमुख्य->करोमुख्य_lock, flags);
	/* Remove the device from the करोमुख्य device list */
	list_क्रम_each_entry_safe(info, पंचांगp, &dma_करोमुख्य->devices, link) अणु
		अगर (!dev || (info->dev == dev))
			हटाओ_device_ref(info);
	पूर्ण
	spin_unlock_irqrestore(&dma_करोमुख्य->करोमुख्य_lock, flags);
पूर्ण

अटल व्योम attach_device(काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य, पूर्णांक liodn, काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info, *old_करोमुख्य_info;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	/*
	 * Check here अगर the device is alपढ़ोy attached to करोमुख्य or not.
	 * If the device is alपढ़ोy attached to a करोमुख्य detach it.
	 */
	old_करोमुख्य_info = dev_iommu_priv_get(dev);
	अगर (old_करोमुख्य_info && old_करोमुख्य_info->करोमुख्य != dma_करोमुख्य) अणु
		spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
		detach_device(dev, old_करोमुख्य_info->करोमुख्य);
		spin_lock_irqsave(&device_करोमुख्य_lock, flags);
	पूर्ण

	info = kmem_cache_zalloc(iommu_devinfo_cache, GFP_ATOMIC);

	info->dev = dev;
	info->liodn = liodn;
	info->करोमुख्य = dma_करोमुख्य;

	list_add(&info->link, &dma_करोमुख्य->devices);
	/*
	 * In हाल of devices with multiple LIODNs just store
	 * the info क्रम the first LIODN as all
	 * LIODNs share the same करोमुख्य
	 */
	अगर (!dev_iommu_priv_get(dev))
		dev_iommu_priv_set(dev, info);
	spin_unlock_irqrestore(&device_करोमुख्य_lock, flags);
पूर्ण

अटल phys_addr_t fsl_pamu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					 dma_addr_t iova)
अणु
	अगर (iova < करोमुख्य->geometry.aperture_start ||
	    iova > करोमुख्य->geometry.aperture_end)
		वापस 0;
	वापस iova;
पूर्ण

अटल bool fsl_pamu_capable(क्रमागत iommu_cap cap)
अणु
	वापस cap == IOMMU_CAP_CACHE_COHERENCY;
पूर्ण

अटल व्योम fsl_pamu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य = to_fsl_dma_करोमुख्य(करोमुख्य);

	/* हटाओ all the devices from the device list */
	detach_device(शून्य, dma_करोमुख्य);
	kmem_cache_मुक्त(fsl_pamu_करोमुख्य_cache, dma_करोमुख्य);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *fsl_pamu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	dma_करोमुख्य = kmem_cache_zalloc(fsl_pamu_करोमुख्य_cache, GFP_KERNEL);
	अगर (!dma_करोमुख्य)
		वापस शून्य;

	dma_करोमुख्य->stash_id = ~(u32)0;
	INIT_LIST_HEAD(&dma_करोमुख्य->devices);
	spin_lock_init(&dma_करोमुख्य->करोमुख्य_lock);

	/* शेष geometry 64 GB i.e. maximum प्रणाली address */
	dma_करोमुख्य->iommu_करोमुख्य. geometry.aperture_start = 0;
	dma_करोमुख्य->iommu_करोमुख्य.geometry.aperture_end = (1ULL << 36) - 1;
	dma_करोमुख्य->iommu_करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &dma_करोमुख्य->iommu_करोमुख्य;
पूर्ण

/* Update stash destination क्रम all LIODNs associated with the करोमुख्य */
अटल पूर्णांक update_करोमुख्य_stash(काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य, u32 val)
अणु
	काष्ठा device_करोमुख्य_info *info;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(info, &dma_करोमुख्य->devices, link) अणु
		ret = update_liodn_stash(info->liodn, dma_करोमुख्य, val);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_pamu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य = to_fsl_dma_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक len, ret = 0, i;
	स्थिर u32 *liodn;
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा pci_controller *pci_ctl;

	/*
	 * Use LIODN of the PCI controller जबतक attaching a
	 * PCI device.
	 */
	अगर (dev_is_pci(dev)) अणु
		pdev = to_pci_dev(dev);
		pci_ctl = pci_bus_to_host(pdev->bus);
		/*
		 * make dev poपूर्णांक to pci controller device
		 * so we can get the LIODN programmed by
		 * u-boot.
		 */
		dev = pci_ctl->parent;
	पूर्ण

	liodn = of_get_property(dev->of_node, "fsl,liodn", &len);
	अगर (!liodn) अणु
		pr_debug("missing fsl,liodn property at %pOF\n", dev->of_node);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&dma_करोमुख्य->करोमुख्य_lock, flags);
	क्रम (i = 0; i < len / माप(u32); i++) अणु
		/* Ensure that LIODN value is valid */
		अगर (liodn[i] >= PAACE_NUMBER_ENTRIES) अणु
			pr_debug("Invalid liodn %d, attach device failed for %pOF\n",
				 liodn[i], dev->of_node);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		attach_device(dma_करोमुख्य, liodn[i], dev);
		ret = pamu_set_liodn(dma_करोमुख्य, dev, liodn[i]);
		अगर (ret)
			अवरोध;
		ret = pamu_enable_liodn(liodn[i]);
		अगर (ret)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dma_करोमुख्य->करोमुख्य_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम fsl_pamu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य = to_fsl_dma_करोमुख्य(करोमुख्य);
	स्थिर u32 *prop;
	पूर्णांक len;
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा pci_controller *pci_ctl;

	/*
	 * Use LIODN of the PCI controller जबतक detaching a
	 * PCI device.
	 */
	अगर (dev_is_pci(dev)) अणु
		pdev = to_pci_dev(dev);
		pci_ctl = pci_bus_to_host(pdev->bus);
		/*
		 * make dev poपूर्णांक to pci controller device
		 * so we can get the LIODN programmed by
		 * u-boot.
		 */
		dev = pci_ctl->parent;
	पूर्ण

	prop = of_get_property(dev->of_node, "fsl,liodn", &len);
	अगर (prop)
		detach_device(dev, dma_करोमुख्य);
	अन्यथा
		pr_debug("missing fsl,liodn property at %pOF\n", dev->of_node);
पूर्ण

/* Set the करोमुख्य stash attribute */
पूर्णांक fsl_pamu_configure_l1_stash(काष्ठा iommu_करोमुख्य *करोमुख्य, u32 cpu)
अणु
	काष्ठा fsl_dma_करोमुख्य *dma_करोमुख्य = to_fsl_dma_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&dma_करोमुख्य->करोमुख्य_lock, flags);
	dma_करोमुख्य->stash_id = get_stash_id(PAMU_ATTR_CACHE_L1, cpu);
	अगर (dma_करोमुख्य->stash_id == ~(u32)0) अणु
		pr_debug("Invalid stash attributes\n");
		spin_unlock_irqrestore(&dma_करोमुख्य->करोमुख्य_lock, flags);
		वापस -EINVAL;
	पूर्ण
	ret = update_करोमुख्य_stash(dma_करोमुख्य, dma_करोमुख्य->stash_id);
	spin_unlock_irqrestore(&dma_करोमुख्य->करोमुख्य_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा iommu_group *get_device_iommu_group(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;

	group = iommu_group_get(dev);
	अगर (!group)
		group = iommu_group_alloc();

	वापस group;
पूर्ण

अटल  bool check_pci_ctl_endpt_part(काष्ठा pci_controller *pci_ctl)
अणु
	u32 version;

	/* Check the PCI controller version number by पढ़ोding BRR1 रेजिस्टर */
	version = in_be32(pci_ctl->cfg_addr + (PCI_FSL_BRR1 >> 2));
	version &= PCI_FSL_BRR1_VER;
	/* If PCI controller version is >= 0x204 we can partition endpoपूर्णांकs */
	वापस version >= 0x204;
पूर्ण

/* Get iommu group inक्रमmation from peer devices or devices on the parent bus */
अटल काष्ठा iommu_group *get_shared_pci_device_group(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *पंचांगp;
	काष्ठा iommu_group *group;
	काष्ठा pci_bus *bus = pdev->bus;

	/*
	 * Traverese the pci bus device list to get
	 * the shared iommu group.
	 */
	जबतक (bus) अणु
		list_क्रम_each_entry(पंचांगp, &bus->devices, bus_list) अणु
			अगर (पंचांगp == pdev)
				जारी;
			group = iommu_group_get(&पंचांगp->dev);
			अगर (group)
				वापस group;
		पूर्ण

		bus = bus->parent;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा iommu_group *get_pci_device_group(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_controller *pci_ctl;
	bool pci_endpt_partitioning;
	काष्ठा iommu_group *group = शून्य;

	pci_ctl = pci_bus_to_host(pdev->bus);
	pci_endpt_partitioning = check_pci_ctl_endpt_part(pci_ctl);
	/* We can partition PCIe devices so assign device group to the device */
	अगर (pci_endpt_partitioning) अणु
		group = pci_device_group(&pdev->dev);

		/*
		 * PCIe controller is not a paritionable entity
		 * मुक्त the controller device iommu_group.
		 */
		अगर (pci_ctl->parent->iommu_group)
			iommu_group_हटाओ_device(pci_ctl->parent);
	पूर्ण अन्यथा अणु
		/*
		 * All devices connected to the controller will share the
		 * PCI controllers device group. If this is the first
		 * device to be probed क्रम the pci controller, copy the
		 * device group inक्रमmation from the PCI controller device
		 * node and हटाओ the PCI controller iommu group.
		 * For subsequent devices, the iommu group inक्रमmation can
		 * be obtained from sibling devices (i.e. from the bus_devices
		 * link list).
		 */
		अगर (pci_ctl->parent->iommu_group) अणु
			group = get_device_iommu_group(pci_ctl->parent);
			iommu_group_हटाओ_device(pci_ctl->parent);
		पूर्ण अन्यथा अणु
			group = get_shared_pci_device_group(pdev);
		पूर्ण
	पूर्ण

	अगर (!group)
		group = ERR_PTR(-ENODEV);

	वापस group;
पूर्ण

अटल काष्ठा iommu_group *fsl_pamu_device_group(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group = ERR_PTR(-ENODEV);
	पूर्णांक len;

	/*
	 * For platक्रमm devices we allocate a separate group क्रम
	 * each of the devices.
	 */
	अगर (dev_is_pci(dev))
		group = get_pci_device_group(to_pci_dev(dev));
	अन्यथा अगर (of_get_property(dev->of_node, "fsl,liodn", &len))
		group = get_device_iommu_group(dev);

	वापस group;
पूर्ण

अटल काष्ठा iommu_device *fsl_pamu_probe_device(काष्ठा device *dev)
अणु
	वापस &pamu_iommu;
पूर्ण

अटल व्योम fsl_pamu_release_device(काष्ठा device *dev)
अणु
पूर्ण

अटल स्थिर काष्ठा iommu_ops fsl_pamu_ops = अणु
	.capable	= fsl_pamu_capable,
	.करोमुख्य_alloc	= fsl_pamu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त    = fsl_pamu_करोमुख्य_मुक्त,
	.attach_dev	= fsl_pamu_attach_device,
	.detach_dev	= fsl_pamu_detach_device,
	.iova_to_phys	= fsl_pamu_iova_to_phys,
	.probe_device	= fsl_pamu_probe_device,
	.release_device	= fsl_pamu_release_device,
	.device_group   = fsl_pamu_device_group,
पूर्ण;

पूर्णांक __init pamu_करोमुख्य_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = iommu_init_mempool();
	अगर (ret)
		वापस ret;

	ret = iommu_device_sysfs_add(&pamu_iommu, शून्य, शून्य, "iommu0");
	अगर (ret)
		वापस ret;

	ret = iommu_device_रेजिस्टर(&pamu_iommu, &fsl_pamu_ops, शून्य);
	अगर (ret) अणु
		iommu_device_sysfs_हटाओ(&pamu_iommu);
		pr_err("Can't register iommu device\n");
		वापस ret;
	पूर्ण

	bus_set_iommu(&platक्रमm_bus_type, &fsl_pamu_ops);
	bus_set_iommu(&pci_bus_type, &fsl_pamu_ops);

	वापस ret;
पूर्ण
