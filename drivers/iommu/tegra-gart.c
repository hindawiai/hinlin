<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU API क्रम Graphics Address Relocation Table on Tegra20
 *
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Hiroshi DOYU <hकरोyu@nvidia.com>
 */

#घोषणा dev_fmt(fmt)	"gart: " fmt

#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <soc/tegra/mc.h>

#घोषणा GART_REG_BASE		0x24
#घोषणा GART_CONFIG		(0x24 - GART_REG_BASE)
#घोषणा GART_ENTRY_ADDR		(0x28 - GART_REG_BASE)
#घोषणा GART_ENTRY_DATA		(0x2c - GART_REG_BASE)

#घोषणा GART_ENTRY_PHYS_ADDR_VALID	BIT(31)

#घोषणा GART_PAGE_SHIFT		12
#घोषणा GART_PAGE_SIZE		(1 << GART_PAGE_SHIFT)
#घोषणा GART_PAGE_MASK		GENMASK(30, GART_PAGE_SHIFT)

/* biपंचांगap of the page sizes currently supported */
#घोषणा GART_IOMMU_PGSIZES	(GART_PAGE_SIZE)

काष्ठा gart_device अणु
	व्योम __iomem		*regs;
	u32			*savedata;
	अचिन्हित दीर्घ		iovmm_base;	/* offset to vmm_area start */
	अचिन्हित दीर्घ		iovmm_end;	/* offset to vmm_area end */
	spinlock_t		pte_lock;	/* क्रम pagetable */
	spinlock_t		करोm_lock;	/* क्रम active करोमुख्य */
	अचिन्हित पूर्णांक		active_devices;	/* number of active devices */
	काष्ठा iommu_करोमुख्य	*active_करोमुख्य;	/* current active करोमुख्य */
	काष्ठा iommu_device	iommu;		/* IOMMU Core handle */
	काष्ठा device		*dev;
पूर्ण;

अटल काष्ठा gart_device *gart_handle; /* unique क्रम a प्रणाली */

अटल bool gart_debug;

/*
 * Any पूर्णांकeraction between any block on PPSB and a block on APB or AHB
 * must have these पढ़ो-back to ensure the APB/AHB bus transaction is
 * complete beक्रमe initiating activity on the PPSB block.
 */
#घोषणा FLUSH_GART_REGS(gart)	पढ़ोl_relaxed((gart)->regs + GART_CONFIG)

#घोषणा क्रम_each_gart_pte(gart, iova)					\
	क्रम (iova = gart->iovmm_base;					\
	     iova < gart->iovmm_end;					\
	     iova += GART_PAGE_SIZE)

अटल अंतरभूत व्योम gart_set_pte(काष्ठा gart_device *gart,
				अचिन्हित दीर्घ iova, अचिन्हित दीर्घ pte)
अणु
	ग_लिखोl_relaxed(iova, gart->regs + GART_ENTRY_ADDR);
	ग_लिखोl_relaxed(pte, gart->regs + GART_ENTRY_DATA);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gart_पढ़ो_pte(काष्ठा gart_device *gart,
					  अचिन्हित दीर्घ iova)
अणु
	अचिन्हित दीर्घ pte;

	ग_लिखोl_relaxed(iova, gart->regs + GART_ENTRY_ADDR);
	pte = पढ़ोl_relaxed(gart->regs + GART_ENTRY_DATA);

	वापस pte;
पूर्ण

अटल व्योम करो_gart_setup(काष्ठा gart_device *gart, स्थिर u32 *data)
अणु
	अचिन्हित दीर्घ iova;

	क्रम_each_gart_pte(gart, iova)
		gart_set_pte(gart, iova, data ? *(data++) : 0);

	ग_लिखोl_relaxed(1, gart->regs + GART_CONFIG);
	FLUSH_GART_REGS(gart);
पूर्ण

अटल अंतरभूत bool gart_iova_range_invalid(काष्ठा gart_device *gart,
					   अचिन्हित दीर्घ iova, माप_प्रकार bytes)
अणु
	वापस unlikely(iova < gart->iovmm_base || bytes != GART_PAGE_SIZE ||
			iova + bytes > gart->iovmm_end);
पूर्ण

अटल अंतरभूत bool gart_pte_valid(काष्ठा gart_device *gart, अचिन्हित दीर्घ iova)
अणु
	वापस !!(gart_पढ़ो_pte(gart, iova) & GART_ENTRY_PHYS_ADDR_VALID);
पूर्ण

अटल पूर्णांक gart_iommu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	काष्ठा gart_device *gart = gart_handle;
	पूर्णांक ret = 0;

	spin_lock(&gart->करोm_lock);

	अगर (gart->active_करोमुख्य && gart->active_करोमुख्य != करोमुख्य) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अगर (dev_iommu_priv_get(dev) != करोमुख्य) अणु
		dev_iommu_priv_set(dev, करोमुख्य);
		gart->active_करोमुख्य = करोमुख्य;
		gart->active_devices++;
	पूर्ण

	spin_unlock(&gart->करोm_lock);

	वापस ret;
पूर्ण

अटल व्योम gart_iommu_detach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	काष्ठा gart_device *gart = gart_handle;

	spin_lock(&gart->करोm_lock);

	अगर (dev_iommu_priv_get(dev) == करोमुख्य) अणु
		dev_iommu_priv_set(dev, शून्य);

		अगर (--gart->active_devices == 0)
			gart->active_करोमुख्य = शून्य;
	पूर्ण

	spin_unlock(&gart->करोm_lock);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *gart_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
	अगर (करोमुख्य) अणु
		करोमुख्य->geometry.aperture_start = gart_handle->iovmm_base;
		करोमुख्य->geometry.aperture_end = gart_handle->iovmm_end - 1;
		करोमुख्य->geometry.क्रमce_aperture = true;
	पूर्ण

	वापस करोमुख्य;
पूर्ण

अटल व्योम gart_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	WARN_ON(gart_handle->active_करोमुख्य == करोमुख्य);
	kमुक्त(करोमुख्य);
पूर्ण

अटल अंतरभूत पूर्णांक __gart_iommu_map(काष्ठा gart_device *gart, अचिन्हित दीर्घ iova,
				   अचिन्हित दीर्घ pa)
अणु
	अगर (unlikely(gart_debug && gart_pte_valid(gart, iova))) अणु
		dev_err(gart->dev, "Page entry is in-use\n");
		वापस -EINVAL;
	पूर्ण

	gart_set_pte(gart, iova, GART_ENTRY_PHYS_ADDR_VALID | pa);

	वापस 0;
पूर्ण

अटल पूर्णांक gart_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  phys_addr_t pa, माप_प्रकार bytes, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा gart_device *gart = gart_handle;
	पूर्णांक ret;

	अगर (gart_iova_range_invalid(gart, iova, bytes))
		वापस -EINVAL;

	spin_lock(&gart->pte_lock);
	ret = __gart_iommu_map(gart, iova, (अचिन्हित दीर्घ)pa);
	spin_unlock(&gart->pte_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __gart_iommu_unmap(काष्ठा gart_device *gart,
				     अचिन्हित दीर्घ iova)
अणु
	अगर (unlikely(gart_debug && !gart_pte_valid(gart, iova))) अणु
		dev_err(gart->dev, "Page entry is invalid\n");
		वापस -EINVAL;
	पूर्ण

	gart_set_pte(gart, iova, 0);

	वापस 0;
पूर्ण

अटल माप_प्रकार gart_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार bytes, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा gart_device *gart = gart_handle;
	पूर्णांक err;

	अगर (gart_iova_range_invalid(gart, iova, bytes))
		वापस 0;

	spin_lock(&gart->pte_lock);
	err = __gart_iommu_unmap(gart, iova);
	spin_unlock(&gart->pte_lock);

	वापस err ? 0 : bytes;
पूर्ण

अटल phys_addr_t gart_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t iova)
अणु
	काष्ठा gart_device *gart = gart_handle;
	अचिन्हित दीर्घ pte;

	अगर (gart_iova_range_invalid(gart, iova, GART_PAGE_SIZE))
		वापस -EINVAL;

	spin_lock(&gart->pte_lock);
	pte = gart_पढ़ो_pte(gart, iova);
	spin_unlock(&gart->pte_lock);

	वापस pte & GART_PAGE_MASK;
पूर्ण

अटल bool gart_iommu_capable(क्रमागत iommu_cap cap)
अणु
	वापस false;
पूर्ण

अटल काष्ठा iommu_device *gart_iommu_probe_device(काष्ठा device *dev)
अणु
	अगर (!dev_iommu_fwspec_get(dev))
		वापस ERR_PTR(-ENODEV);

	वापस &gart_handle->iommu;
पूर्ण

अटल व्योम gart_iommu_release_device(काष्ठा device *dev)
अणु
पूर्ण

अटल पूर्णांक gart_iommu_of_xlate(काष्ठा device *dev,
			       काष्ठा of_phandle_args *args)
अणु
	वापस 0;
पूर्ण

अटल व्योम gart_iommu_sync_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
				माप_प्रकार size)
अणु
	FLUSH_GART_REGS(gart_handle);
पूर्ण

अटल व्योम gart_iommu_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
			    काष्ठा iommu_iotlb_gather *gather)
अणु
	माप_प्रकार length = gather->end - gather->start + 1;

	gart_iommu_sync_map(करोमुख्य, gather->start, length);
पूर्ण

अटल स्थिर काष्ठा iommu_ops gart_iommu_ops = अणु
	.capable	= gart_iommu_capable,
	.करोमुख्य_alloc	= gart_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= gart_iommu_करोमुख्य_मुक्त,
	.attach_dev	= gart_iommu_attach_dev,
	.detach_dev	= gart_iommu_detach_dev,
	.probe_device	= gart_iommu_probe_device,
	.release_device	= gart_iommu_release_device,
	.device_group	= generic_device_group,
	.map		= gart_iommu_map,
	.unmap		= gart_iommu_unmap,
	.iova_to_phys	= gart_iommu_iova_to_phys,
	.pgsize_biपंचांगap	= GART_IOMMU_PGSIZES,
	.of_xlate	= gart_iommu_of_xlate,
	.iotlb_sync_map	= gart_iommu_sync_map,
	.iotlb_sync	= gart_iommu_sync,
पूर्ण;

पूर्णांक tegra_gart_suspend(काष्ठा gart_device *gart)
अणु
	u32 *data = gart->savedata;
	अचिन्हित दीर्घ iova;

	/*
	 * All GART users shall be suspended at this poपूर्णांक. Disable
	 * address translation to trap all GART accesses as invalid
	 * memory accesses.
	 */
	ग_लिखोl_relaxed(0, gart->regs + GART_CONFIG);
	FLUSH_GART_REGS(gart);

	क्रम_each_gart_pte(gart, iova)
		*(data++) = gart_पढ़ो_pte(gart, iova);

	वापस 0;
पूर्ण

पूर्णांक tegra_gart_resume(काष्ठा gart_device *gart)
अणु
	करो_gart_setup(gart, gart->savedata);

	वापस 0;
पूर्ण

काष्ठा gart_device *tegra_gart_probe(काष्ठा device *dev, काष्ठा tegra_mc *mc)
अणु
	काष्ठा gart_device *gart;
	काष्ठा resource *res;
	पूर्णांक err;

	BUILD_BUG_ON(PAGE_SHIFT != GART_PAGE_SHIFT);

	/* the GART memory aperture is required */
	res = platक्रमm_get_resource(to_platक्रमm_device(dev), IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(dev, "Memory aperture resource unavailable\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	gart = kzalloc(माप(*gart), GFP_KERNEL);
	अगर (!gart)
		वापस ERR_PTR(-ENOMEM);

	gart_handle = gart;

	gart->dev = dev;
	gart->regs = mc->regs + GART_REG_BASE;
	gart->iovmm_base = res->start;
	gart->iovmm_end = res->end + 1;
	spin_lock_init(&gart->pte_lock);
	spin_lock_init(&gart->करोm_lock);

	करो_gart_setup(gart, शून्य);

	err = iommu_device_sysfs_add(&gart->iommu, dev, शून्य, "gart");
	अगर (err)
		जाओ मुक्त_gart;

	err = iommu_device_रेजिस्टर(&gart->iommu, &gart_iommu_ops, dev);
	अगर (err)
		जाओ हटाओ_sysfs;

	gart->savedata = vदो_स्मृति(resource_size(res) / GART_PAGE_SIZE *
				 माप(u32));
	अगर (!gart->savedata) अणु
		err = -ENOMEM;
		जाओ unरेजिस्टर_iommu;
	पूर्ण

	वापस gart;

unरेजिस्टर_iommu:
	iommu_device_unरेजिस्टर(&gart->iommu);
हटाओ_sysfs:
	iommu_device_sysfs_हटाओ(&gart->iommu);
मुक्त_gart:
	kमुक्त(gart);

	वापस ERR_PTR(err);
पूर्ण

module_param(gart_debug, bool, 0644);
MODULE_PARM_DESC(gart_debug, "Enable GART debugging");
