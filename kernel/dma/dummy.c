<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dummy DMA ops that always fail.
 */
#समावेश <linux/dma-map-ops.h>

अटल पूर्णांक dma_dummy_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	वापस -ENXIO;
पूर्ण

अटल dma_addr_t dma_dummy_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल पूर्णांक dma_dummy_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nelems, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dma_dummy_supported(काष्ठा device *hwdev, u64 mask)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा dma_map_ops dma_dummy_ops = अणु
	.mmap                   = dma_dummy_mmap,
	.map_page               = dma_dummy_map_page,
	.map_sg                 = dma_dummy_map_sg,
	.dma_supported          = dma_dummy_supported,
पूर्ण;
