<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/cache.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-iommu.h>
#समावेश <xen/xen.h>
#समावेश <xen/swiotlb-xen.h>

#समावेश <यंत्र/cacheflush.h>

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_map_area(phys_to_virt(paddr), size, dir);
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_unmap_area(phys_to_virt(paddr), size, dir);
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	__dma_flush_area(page_address(page), size);
पूर्ण

#अगर_घोषित CONFIG_IOMMU_DMA
व्योम arch_tearकरोwn_dma_ops(काष्ठा device *dev)
अणु
	dev->dma_ops = शून्य;
पूर्ण
#पूर्ण_अगर

व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
			स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
	पूर्णांक cls = cache_line_size_of_cpu();

	WARN_TAINT(!coherent && cls > ARCH_DMA_MINALIGN,
		   TAINT_CPU_OUT_OF_SPEC,
		   "%s %s: ARCH_DMA_MINALIGN smaller than CTR_EL0.CWG (%d < %d)",
		   dev_driver_string(dev), dev_name(dev),
		   ARCH_DMA_MINALIGN, cls);

	dev->dma_coherent = coherent;
	अगर (iommu)
		iommu_setup_dma_ops(dev, dma_base, size);

#अगर_घोषित CONFIG_XEN
	अगर (xen_swiotlb_detect())
		dev->dma_ops = &xen_swiotlb_dma_ops;
#पूर्ण_अगर
पूर्ण
