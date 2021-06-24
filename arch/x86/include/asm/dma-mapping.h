<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DMA_MAPPING_H
#घोषणा _ASM_X86_DMA_MAPPING_H

/*
 * IOMMU पूर्णांकerface. See Documentation/core-api/dma-api-howto.rst and
 * Documentation/core-api/dma-api.rst क्रम करोcumentation.
 */

#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/swiotlb.h>

बाह्य पूर्णांक iommu_merge;
बाह्य पूर्णांक panic_on_overflow;

बाह्य स्थिर काष्ठा dma_map_ops *dma_ops;

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_arch_dma_ops(काष्ठा bus_type *bus)
अणु
	वापस dma_ops;
पूर्ण

#पूर्ण_अगर
