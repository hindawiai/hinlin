<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Christoph Hellwig.
 *
 * DMA operations that map physical memory directly without using an IOMMU.
 */
#अगर_अघोषित _KERNEL_DMA_सूचीECT_H
#घोषणा _KERNEL_DMA_सूचीECT_H

#समावेश <linux/dma-direct.h>

पूर्णांक dma_direct_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
bool dma_direct_can_mmap(काष्ठा device *dev);
पूर्णांक dma_direct_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
bool dma_direct_need_sync(काष्ठा device *dev, dma_addr_t dma_addr);
पूर्णांक dma_direct_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
माप_प्रकार dma_direct_max_mapping_size(काष्ठा device *dev);

#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE) || \
    defined(CONFIG_SWIOTLB)
व्योम dma_direct_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir);
#अन्यथा
अटल अंतरभूत व्योम dma_direct_sync_sg_क्रम_device(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL) || \
    defined(CONFIG_SWIOTLB)
व्योम dma_direct_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
व्योम dma_direct_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir);
#अन्यथा
अटल अंतरभूत व्योम dma_direct_unmap_sg(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_direct_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम dma_direct_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t addr, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr = dma_to_phys(dev, addr);

	अगर (unlikely(is_swiotlb_buffer(paddr)))
		swiotlb_sync_single_क्रम_device(dev, paddr, size, dir);

	अगर (!dev_is_dma_coherent(dev))
		arch_sync_dma_क्रम_device(paddr, size, dir);
पूर्ण

अटल अंतरभूत व्योम dma_direct_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t addr, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr = dma_to_phys(dev, addr);

	अगर (!dev_is_dma_coherent(dev)) अणु
		arch_sync_dma_क्रम_cpu(paddr, size, dir);
		arch_sync_dma_क्रम_cpu_all();
	पूर्ण

	अगर (unlikely(is_swiotlb_buffer(paddr)))
		swiotlb_sync_single_क्रम_cpu(dev, paddr, size, dir);

	अगर (dir == DMA_FROM_DEVICE)
		arch_dma_mark_clean(paddr, size);
पूर्ण

अटल अंतरभूत dma_addr_t dma_direct_map_page(काष्ठा device *dev,
		काष्ठा page *page, अचिन्हित दीर्घ offset, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t phys = page_to_phys(page) + offset;
	dma_addr_t dma_addr = phys_to_dma(dev, phys);

	अगर (unlikely(swiotlb_क्रमce == SWIOTLB_FORCE))
		वापस swiotlb_map(dev, phys, size, dir, attrs);

	अगर (unlikely(!dma_capable(dev, dma_addr, size, true))) अणु
		अगर (swiotlb_क्रमce != SWIOTLB_NO_FORCE)
			वापस swiotlb_map(dev, phys, size, dir, attrs);

		dev_WARN_ONCE(dev, 1,
			     "DMA addr %pad+%zu overflow (mask %llx, bus limit %llx).\n",
			     &dma_addr, size, *dev->dma_mask, dev->bus_dma_limit);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	अगर (!dev_is_dma_coherent(dev) && !(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_क्रम_device(phys, size, dir);
	वापस dma_addr;
पूर्ण

अटल अंतरभूत व्योम dma_direct_unmap_page(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t phys = dma_to_phys(dev, addr);

	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		dma_direct_sync_single_क्रम_cpu(dev, addr, size, dir);

	अगर (unlikely(is_swiotlb_buffer(phys)))
		swiotlb_tbl_unmap_single(dev, phys, size, dir, attrs);
पूर्ण
#पूर्ण_अगर /* _KERNEL_DMA_सूचीECT_H */
