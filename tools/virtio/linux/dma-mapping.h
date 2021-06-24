<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DMA_MAPPING_H
#घोषणा _LINUX_DMA_MAPPING_H

#अगर_घोषित CONFIG_HAS_DMA
# error Virtio userspace code करोes not support CONFIG_HAS_DMA
#पूर्ण_अगर

क्रमागत dma_data_direction अणु
	DMA_BIसूचीECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
पूर्ण;

#घोषणा dma_alloc_coherent(d, s, hp, f) (अणु \
	व्योम *__dma_alloc_coherent_p = kदो_स्मृति((s), (f)); \
	*(hp) = (अचिन्हित दीर्घ)__dma_alloc_coherent_p; \
	__dma_alloc_coherent_p; \
पूर्ण)

#घोषणा dma_मुक्त_coherent(d, s, p, h) kमुक्त(p)

#घोषणा dma_map_page(d, p, o, s, dir) (page_to_phys(p) + (o))

#घोषणा dma_map_single(d, p, s, dir) (virt_to_phys(p))
#घोषणा dma_mapping_error(...) (0)

#घोषणा dma_unmap_single(...) करो अणु पूर्ण जबतक (0)
#घोषणा dma_unmap_page(...) करो अणु पूर्ण जबतक (0)

#घोषणा dma_max_mapping_size(...) SIZE_MAX

#पूर्ण_अगर
