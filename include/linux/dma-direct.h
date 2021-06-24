<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Internals of the DMA direct mapping implementation.  Only क्रम use by the
 * DMA mapping code and IOMMU drivers.
 */
#अगर_अघोषित _LINUX_DMA_सूचीECT_H
#घोषणा _LINUX_DMA_सूचीECT_H 1

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/memblock.h> /* क्रम min_low_pfn */
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/swiotlb.h>

बाह्य अचिन्हित पूर्णांक zone_dma_bits;

/*
 * Record the mapping of CPU physical to DMA addresses क्रम a given region.
 */
काष्ठा bus_dma_region अणु
	phys_addr_t	cpu_start;
	dma_addr_t	dma_start;
	u64		size;
	u64		offset;
पूर्ण;

अटल अंतरभूत dma_addr_t translate_phys_to_dma(काष्ठा device *dev,
		phys_addr_t paddr)
अणु
	स्थिर काष्ठा bus_dma_region *m;

	क्रम (m = dev->dma_range_map; m->size; m++)
		अगर (paddr >= m->cpu_start && paddr - m->cpu_start < m->size)
			वापस (dma_addr_t)paddr - m->offset;

	/* make sure dma_capable fails when no translation is available */
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल अंतरभूत phys_addr_t translate_dma_to_phys(काष्ठा device *dev,
		dma_addr_t dma_addr)
अणु
	स्थिर काष्ठा bus_dma_region *m;

	क्रम (m = dev->dma_range_map; m->size; m++)
		अगर (dma_addr >= m->dma_start && dma_addr - m->dma_start < m->size)
			वापस (phys_addr_t)dma_addr + m->offset;

	वापस (phys_addr_t)-1;
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PHYS_TO_DMA
#समावेश <यंत्र/dma-direct.h>
#अगर_अघोषित phys_to_dma_unencrypted
#घोषणा phys_to_dma_unencrypted		phys_to_dma
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत dma_addr_t phys_to_dma_unencrypted(काष्ठा device *dev,
		phys_addr_t paddr)
अणु
	अगर (dev->dma_range_map)
		वापस translate_phys_to_dma(dev, paddr);
	वापस paddr;
पूर्ण

/*
 * If memory encryption is supported, phys_to_dma will set the memory encryption
 * bit in the DMA address, and dma_to_phys will clear it.
 * phys_to_dma_unencrypted is क्रम use on special unencrypted memory like swiotlb
 * buffers.
 */
अटल अंतरभूत dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस __sme_set(phys_to_dma_unencrypted(dev, paddr));
पूर्ण

अटल अंतरभूत phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	phys_addr_t paddr;

	अगर (dev->dma_range_map)
		paddr = translate_dma_to_phys(dev, dma_addr);
	अन्यथा
		paddr = dma_addr;

	वापस __sme_clr(paddr);
पूर्ण
#पूर्ण_अगर /* !CONFIG_ARCH_HAS_PHYS_TO_DMA */

#अगर_घोषित CONFIG_ARCH_HAS_FORCE_DMA_UNENCRYPTED
bool क्रमce_dma_unencrypted(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत bool क्रमce_dma_unencrypted(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_FORCE_DMA_UNENCRYPTED */

अटल अंतरभूत bool dma_capable(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		bool is_ram)
अणु
	dma_addr_t end = addr + size - 1;

	अगर (addr == DMA_MAPPING_ERROR)
		वापस false;
	अगर (is_ram && !IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT) &&
	    min(addr, end) < phys_to_dma(dev, PFN_PHYS(min_low_pfn)))
		वापस false;

	वापस end <= min_not_zero(*dev->dma_mask, dev->bus_dma_limit);
पूर्ण

u64 dma_direct_get_required_mask(काष्ठा device *dev);
व्योम *dma_direct_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs);
व्योम dma_direct_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_addr, अचिन्हित दीर्घ attrs);
काष्ठा page *dma_direct_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp);
व्योम dma_direct_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा page *page, dma_addr_t dma_addr,
		क्रमागत dma_data_direction dir);
पूर्णांक dma_direct_supported(काष्ठा device *dev, u64 mask);
dma_addr_t dma_direct_map_resource(काष्ठा device *dev, phys_addr_t paddr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);

#पूर्ण_अगर /* _LINUX_DMA_सूचीECT_H */
