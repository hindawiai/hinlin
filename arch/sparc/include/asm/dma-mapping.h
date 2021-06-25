<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_DMA_MAPPING_H
#घोषणा ___ASM_SPARC_DMA_MAPPING_H

बाह्य स्थिर काष्ठा dma_map_ops *dma_ops;

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_arch_dma_ops(काष्ठा bus_type *bus)
अणु
	/* sparc32 uses per-device dma_ops */
	वापस IS_ENABLED(CONFIG_SPARC64) ? dma_ops : शून्य;
पूर्ण

#पूर्ण_अगर
