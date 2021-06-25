<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_DMA_H
#घोषणा _ASM_MICROBLAZE_DMA_H

/* Virtual address corresponding to last available physical memory address.  */
#घोषणा MAX_DMA_ADDRESS (CONFIG_KERNEL_START + memory_size - 1)

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy     (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_MICROBLAZE_DMA_H */
