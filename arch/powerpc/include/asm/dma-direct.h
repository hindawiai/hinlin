<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_POWERPC_DMA_सूचीECT_H
#घोषणा ASM_POWERPC_DMA_सूचीECT_H 1

अटल अंतरभूत dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस paddr + dev->archdata.dma_offset;
पूर्ण

अटल अंतरभूत phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
	वापस daddr - dev->archdata.dma_offset;
पूर्ण
#पूर्ण_अगर /* ASM_POWERPC_DMA_सूचीECT_H */
