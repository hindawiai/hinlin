<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NVIDIA Tegra Video decoder driver
 *
 * Copyright (C) 2016-2019 GRATE-DRIVER project
 */

#समावेश <linux/iommu.h>
#समावेश <linux/iova.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#अगर IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)
#समावेश <यंत्र/dma-iommu.h>
#पूर्ण_अगर

#समावेश "vde.h"

पूर्णांक tegra_vde_iommu_map(काष्ठा tegra_vde *vde,
			काष्ठा sg_table *sgt,
			काष्ठा iova **iovap,
			माप_प्रकार size)
अणु
	काष्ठा iova *iova;
	अचिन्हित दीर्घ shअगरt;
	अचिन्हित दीर्घ end;
	dma_addr_t addr;

	end = vde->करोमुख्य->geometry.aperture_end;
	size = iova_align(&vde->iova, size);
	shअगरt = iova_shअगरt(&vde->iova);

	iova = alloc_iova(&vde->iova, size >> shअगरt, end >> shअगरt, true);
	अगर (!iova)
		वापस -ENOMEM;

	addr = iova_dma_addr(&vde->iova, iova);

	size = iommu_map_sgtable(vde->करोमुख्य, addr, sgt,
				 IOMMU_READ | IOMMU_WRITE);
	अगर (!size) अणु
		__मुक्त_iova(&vde->iova, iova);
		वापस -ENXIO;
	पूर्ण

	*iovap = iova;

	वापस 0;
पूर्ण

व्योम tegra_vde_iommu_unmap(काष्ठा tegra_vde *vde, काष्ठा iova *iova)
अणु
	अचिन्हित दीर्घ shअगरt = iova_shअगरt(&vde->iova);
	अचिन्हित दीर्घ size = iova_size(iova) << shअगरt;
	dma_addr_t addr = iova_dma_addr(&vde->iova, iova);

	iommu_unmap(vde->करोमुख्य, addr, size);
	__मुक्त_iova(&vde->iova, iova);
पूर्ण

पूर्णांक tegra_vde_iommu_init(काष्ठा tegra_vde *vde)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	काष्ठा iova *iova;
	अचिन्हित दीर्घ order;
	अचिन्हित दीर्घ shअगरt;
	पूर्णांक err;

	vde->group = iommu_group_get(dev);
	अगर (!vde->group)
		वापस 0;

#अगर IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)
	अगर (dev->archdata.mapping) अणु
		काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

		arm_iommu_detach_device(dev);
		arm_iommu_release_mapping(mapping);
	पूर्ण
#पूर्ण_अगर
	vde->करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!vde->करोमुख्य) अणु
		err = -ENOMEM;
		जाओ put_group;
	पूर्ण

	err = iova_cache_get();
	अगर (err)
		जाओ मुक्त_करोमुख्य;

	order = __ffs(vde->करोमुख्य->pgsize_biपंचांगap);
	init_iova_करोमुख्य(&vde->iova, 1UL << order, 0);

	err = iommu_attach_group(vde->करोमुख्य, vde->group);
	अगर (err)
		जाओ put_iova;

	/*
	 * We're using some अटल addresses that are not accessible by VDE
	 * to trap invalid memory accesses.
	 */
	shअगरt = iova_shअगरt(&vde->iova);
	iova = reserve_iova(&vde->iova, 0x60000000 >> shअगरt,
			    0x70000000 >> shअगरt);
	अगर (!iova) अणु
		err = -ENOMEM;
		जाओ detach_group;
	पूर्ण

	vde->iova_resv_अटल_addresses = iova;

	/*
	 * BSEV's end-address wraps around due to पूर्णांकeger overflow during
	 * of hardware context preparation अगर IOVA is allocated at the end
	 * of address space and VDE can't handle that. Hence simply reserve
	 * the last page to aव्योम the problem.
	 */
	iova = reserve_iova(&vde->iova, 0xffffffff >> shअगरt,
			    (0xffffffff >> shअगरt) + 1);
	अगर (!iova) अणु
		err = -ENOMEM;
		जाओ unreserve_iova;
	पूर्ण

	vde->iova_resv_last_page = iova;

	वापस 0;

unreserve_iova:
	__मुक्त_iova(&vde->iova, vde->iova_resv_अटल_addresses);
detach_group:
	iommu_detach_group(vde->करोमुख्य, vde->group);
put_iova:
	put_iova_करोमुख्य(&vde->iova);
	iova_cache_put();
मुक्त_करोमुख्य:
	iommu_करोमुख्य_मुक्त(vde->करोमुख्य);
put_group:
	iommu_group_put(vde->group);

	वापस err;
पूर्ण

व्योम tegra_vde_iommu_deinit(काष्ठा tegra_vde *vde)
अणु
	अगर (vde->करोमुख्य) अणु
		__मुक्त_iova(&vde->iova, vde->iova_resv_last_page);
		__मुक्त_iova(&vde->iova, vde->iova_resv_अटल_addresses);
		iommu_detach_group(vde->करोमुख्य, vde->group);
		put_iova_करोमुख्य(&vde->iova);
		iova_cache_put();
		iommu_करोमुख्य_मुक्त(vde->करोमुख्य);
		iommu_group_put(vde->group);

		vde->करोमुख्य = शून्य;
	पूर्ण
पूर्ण
