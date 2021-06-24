<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DMA_H
#घोषणा DMA_H

#समावेश <यंत्र/glue-cache.h>

#अगर_अघोषित MULTI_CACHE
#घोषणा dmac_map_area			__glue(_CACHE,_dma_map_area)
#घोषणा dmac_unmap_area 		__glue(_CACHE,_dma_unmap_area)

/*
 * These are निजी to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to प्रणाली memory is
 * visible to the CPU.
 */
बाह्य व्योम dmac_map_area(स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य व्योम dmac_unmap_area(स्थिर व्योम *, माप_प्रकार, पूर्णांक);

#अन्यथा

/*
 * These are निजी to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to प्रणाली memory is
 * visible to the CPU.
 */
#घोषणा dmac_map_area			cpu_cache.dma_map_area
#घोषणा dmac_unmap_area 		cpu_cache.dma_unmap_area

#पूर्ण_अगर

#पूर्ण_अगर
