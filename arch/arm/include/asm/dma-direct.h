<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_ARM_DMA_सूचीECT_H
#घोषणा ASM_ARM_DMA_सूचीECT_H 1

#समावेश <यंत्र/memory.h>

/*
 * dma_to_pfn/pfn_to_dma/virt_to_dma are architecture निजी
 * functions used पूर्णांकernally by the DMA-mapping API to provide DMA
 * addresses. They must not be used by drivers.
 */
अटल अंतरभूत dma_addr_t pfn_to_dma(काष्ठा device *dev, अचिन्हित दीर्घ pfn)
अणु
	अगर (dev && dev->dma_range_map)
		pfn = PFN_DOWN(translate_phys_to_dma(dev, PFN_PHYS(pfn)));
	वापस (dma_addr_t)__pfn_to_bus(pfn);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dma_to_pfn(काष्ठा device *dev, dma_addr_t addr)
अणु
	अचिन्हित दीर्घ pfn = __bus_to_pfn(addr);

	अगर (dev && dev->dma_range_map)
		pfn = PFN_DOWN(translate_dma_to_phys(dev, PFN_PHYS(pfn)));
	वापस pfn;
पूर्ण

अटल अंतरभूत dma_addr_t virt_to_dma(काष्ठा device *dev, व्योम *addr)
अणु
	अगर (dev)
		वापस pfn_to_dma(dev, virt_to_pfn(addr));

	वापस (dma_addr_t)__virt_to_bus((अचिन्हित दीर्घ)(addr));
पूर्ण

अटल अंतरभूत dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	अचिन्हित पूर्णांक offset = paddr & ~PAGE_MASK;
	वापस pfn_to_dma(dev, __phys_to_pfn(paddr)) + offset;
पूर्ण

अटल अंतरभूत phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dev_addr)
अणु
	अचिन्हित पूर्णांक offset = dev_addr & ~PAGE_MASK;
	वापस __pfn_to_phys(dma_to_pfn(dev, dev_addr)) + offset;
पूर्ण

#पूर्ण_अगर /* ASM_ARM_DMA_सूचीECT_H */
