<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_DMA_H
#घोषणा __ASM_GENERIC_DMA_H
/*
 * This file traditionally describes the i8237 PC style DMA controller.
 * Most architectures करोn't have these any more and can get the minimal
 * implementation from kernel/dma.c by not defining MAX_DMA_CHANNELS.
 *
 * Some code relies on seeing MAX_DMA_ADDRESS though.
 */
#घोषणा MAX_DMA_ADDRESS PAGE_OFFSET

बाह्य पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर *device_id);
बाह्य व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr);

#पूर्ण_अगर /* __ASM_GENERIC_DMA_H */
