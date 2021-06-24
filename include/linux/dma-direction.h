<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DMA_सूचीECTION_H
#घोषणा _LINUX_DMA_सूचीECTION_H

क्रमागत dma_data_direction अणु
	DMA_BIसूचीECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
पूर्ण;

अटल अंतरभूत पूर्णांक valid_dma_direction(क्रमागत dma_data_direction dir)
अणु
	वापस dir == DMA_BIसूचीECTIONAL || dir == DMA_TO_DEVICE ||
		dir == DMA_FROM_DEVICE;
पूर्ण

#पूर्ण_अगर /* _LINUX_DMA_सूचीECTION_H */
