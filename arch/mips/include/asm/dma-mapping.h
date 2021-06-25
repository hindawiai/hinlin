<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_DMA_MAPPING_H
#घोषणा _ASM_DMA_MAPPING_H

#समावेश <linux/swiotlb.h>

बाह्य स्थिर काष्ठा dma_map_ops jazz_dma_ops;

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_arch_dma_ops(काष्ठा bus_type *bus)
अणु
#अगर defined(CONFIG_MACH_JAZZ)
	वापस &jazz_dma_ops;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_DMA_MAPPING_H */
