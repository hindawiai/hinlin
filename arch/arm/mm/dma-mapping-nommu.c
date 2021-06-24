<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Based on linux/arch/arm/mm/dma-mapping.c
 *
 *  Copyright (C) 2000-2004 Russell King
 */

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/outercache.h>
#समावेश <यंत्र/cp15.h>

#समावेश "dma.h"

/*
 *  The generic direct mapping code is used अगर
 *   - MMU/MPU is off
 *   - cpu is v7m w/o cache support
 *   - device is coherent
 *  otherwise arm_nommu_dma_ops is used.
 *
 *  arm_nommu_dma_ops rely on consistent DMA memory (please, refer to
 *  [1] on how to declare such memory).
 *
 *  [1] Documentation/devicetree/bindings/reserved-memory/reserved-memory.txt
 */

अटल व्योम *arm_nommu_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
				 dma_addr_t *dma_handle, gfp_t gfp,
				 अचिन्हित दीर्घ attrs)

अणु
	व्योम *ret = dma_alloc_from_global_coherent(dev, size, dma_handle);

	/*
	 * dma_alloc_from_global_coherent() may fail because:
	 *
	 * - no consistent DMA region has been defined, so we can't
	 *   जारी.
	 * - there is no space left in consistent DMA region, so we
	 *   only can fallback to generic allocator अगर we are
	 *   advertised that consistency is not required.
	 */

	WARN_ON_ONCE(ret == शून्य);
	वापस ret;
पूर्ण

अटल व्योम arm_nommu_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size,
			       व्योम *cpu_addr, dma_addr_t dma_addr,
			       अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक ret = dma_release_from_global_coherent(get_order(size), cpu_addr);

	WARN_ON_ONCE(ret == 0);
पूर्ण

अटल पूर्णांक arm_nommu_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
			      व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
			      अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक ret;

	अगर (dma_mmap_from_global_coherent(vma, cpu_addr, size, &ret))
		वापस ret;
	अगर (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		वापस ret;
	वापस -ENXIO;
पूर्ण


अटल व्योम __dma_page_cpu_to_dev(phys_addr_t paddr, माप_प्रकार size,
				  क्रमागत dma_data_direction dir)
अणु
	dmac_map_area(__va(paddr), size, dir);

	अगर (dir == DMA_FROM_DEVICE)
		outer_inv_range(paddr, paddr + size);
	अन्यथा
		outer_clean_range(paddr, paddr + size);
पूर्ण

अटल व्योम __dma_page_dev_to_cpu(phys_addr_t paddr, माप_प्रकार size,
				  क्रमागत dma_data_direction dir)
अणु
	अगर (dir != DMA_TO_DEVICE) अणु
		outer_inv_range(paddr, paddr + size);
		dmac_unmap_area(__va(paddr), size, dir);
	पूर्ण
पूर्ण

अटल dma_addr_t arm_nommu_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
					 अचिन्हित दीर्घ offset, माप_प्रकार size,
					 क्रमागत dma_data_direction dir,
					 अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t handle = page_to_phys(page) + offset;

	__dma_page_cpu_to_dev(handle, size, dir);

	वापस handle;
पूर्ण

अटल व्योम arm_nommu_dma_unmap_page(काष्ठा device *dev, dma_addr_t handle,
				     माप_प्रकार size, क्रमागत dma_data_direction dir,
				     अचिन्हित दीर्घ attrs)
अणु
	__dma_page_dev_to_cpu(handle, size, dir);
पूर्ण


अटल पूर्णांक arm_nommu_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
				पूर्णांक nents, क्रमागत dma_data_direction dir,
				अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		sg_dma_address(sg) = sg_phys(sg);
		sg_dma_len(sg) = sg->length;
		__dma_page_cpu_to_dev(sg_dma_address(sg), sg_dma_len(sg), dir);
	पूर्ण

	वापस nents;
पूर्ण

अटल व्योम arm_nommu_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
				   पूर्णांक nents, क्रमागत dma_data_direction dir,
				   अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		__dma_page_dev_to_cpu(sg_dma_address(sg), sg_dma_len(sg), dir);
पूर्ण

अटल व्योम arm_nommu_dma_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	__dma_page_cpu_to_dev(handle, size, dir);
पूर्ण

अटल व्योम arm_nommu_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	__dma_page_cpu_to_dev(handle, size, dir);
पूर्ण

अटल व्योम arm_nommu_dma_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sgl,
					     पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		__dma_page_cpu_to_dev(sg_dma_address(sg), sg_dma_len(sg), dir);
पूर्ण

अटल व्योम arm_nommu_dma_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sgl,
					  पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		__dma_page_dev_to_cpu(sg_dma_address(sg), sg_dma_len(sg), dir);
पूर्ण

स्थिर काष्ठा dma_map_ops arm_nommu_dma_ops = अणु
	.alloc			= arm_nommu_dma_alloc,
	.मुक्त			= arm_nommu_dma_मुक्त,
	.alloc_pages		= dma_direct_alloc_pages,
	.मुक्त_pages		= dma_direct_मुक्त_pages,
	.mmap			= arm_nommu_dma_mmap,
	.map_page		= arm_nommu_dma_map_page,
	.unmap_page		= arm_nommu_dma_unmap_page,
	.map_sg			= arm_nommu_dma_map_sg,
	.unmap_sg		= arm_nommu_dma_unmap_sg,
	.sync_single_क्रम_device	= arm_nommu_dma_sync_single_क्रम_device,
	.sync_single_क्रम_cpu	= arm_nommu_dma_sync_single_क्रम_cpu,
	.sync_sg_क्रम_device	= arm_nommu_dma_sync_sg_क्रम_device,
	.sync_sg_क्रम_cpu	= arm_nommu_dma_sync_sg_क्रम_cpu,
पूर्ण;
EXPORT_SYMBOL(arm_nommu_dma_ops);

व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
			स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
	अगर (IS_ENABLED(CONFIG_CPU_V7M)) अणु
		/*
		 * Cache support क्रम v7m is optional, so can be treated as
		 * coherent अगर no cache has been detected. Note that it is not
		 * enough to check अगर MPU is in use or not since in असलense of
		 * MPU प्रणाली memory map is used.
		 */
		dev->archdata.dma_coherent = (cacheid) ? coherent : true;
	पूर्ण अन्यथा अणु
		/*
		 * Assume coherent DMA in हाल MMU/MPU has not been set up.
		 */
		dev->archdata.dma_coherent = (get_cr() & CR_M) ? coherent : true;
	पूर्ण

	अगर (!dev->archdata.dma_coherent)
		set_dma_ops(dev, &arm_nommu_dma_ops);
पूर्ण
