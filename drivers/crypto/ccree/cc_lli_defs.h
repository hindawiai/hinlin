<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#अगर_अघोषित _CC_LLI_DEFS_H_
#घोषणा _CC_LLI_DEFS_H_

#समावेश <linux/types.h>

/* Max DLLI size
 *  AKA CC_DSCRPTR_QUEUE_WORD1_DIN_SIZE_BIT_SIZE
 */
#घोषणा DLLI_SIZE_BIT_SIZE	0x18

#घोषणा CC_MAX_MLLI_ENTRY_SIZE 0xFFFF

#घोषणा LLI_MAX_NUM_OF_DATA_ENTRIES 128
#घोषणा LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES 8
#घोषणा MLLI_TABLE_MIN_ALIGNMENT 4 /* 32 bit alignment */
#घोषणा MAX_NUM_OF_BUFFERS_IN_MLLI 4
#घोषणा MAX_NUM_OF_TOTAL_MLLI_ENTRIES \
		(2 * LLI_MAX_NUM_OF_DATA_ENTRIES + \
		 LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES)

/* Size of entry */
#घोषणा LLI_ENTRY_WORD_SIZE 2
#घोषणा LLI_ENTRY_BYTE_SIZE (LLI_ENTRY_WORD_SIZE * माप(u32))

/* Word0[31:0] = ADDR[31:0] */
#घोषणा LLI_WORD0_OFFSET 0
#घोषणा LLI_LADDR_BIT_OFFSET 0
#घोषणा LLI_LADDR_BIT_SIZE 32
/* Word1[31:16] = ADDR[47:32]; Word1[15:0] = SIZE */
#घोषणा LLI_WORD1_OFFSET 1
#घोषणा LLI_SIZE_BIT_OFFSET 0
#घोषणा LLI_SIZE_BIT_SIZE 16
#घोषणा LLI_HADDR_BIT_OFFSET 16
#घोषणा LLI_HADDR_BIT_SIZE 16

#घोषणा LLI_SIZE_MASK GENMASK((LLI_SIZE_BIT_SIZE - 1), LLI_SIZE_BIT_OFFSET)
#घोषणा LLI_HADDR_MASK GENMASK( \
			       (LLI_HADDR_BIT_OFFSET + LLI_HADDR_BIT_SIZE - 1),\
				LLI_HADDR_BIT_OFFSET)

अटल अंतरभूत व्योम cc_lli_set_addr(u32 *lli_p, dma_addr_t addr)
अणु
	lli_p[LLI_WORD0_OFFSET] = (addr & U32_MAX);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	lli_p[LLI_WORD1_OFFSET] &= ~LLI_HADDR_MASK;
	lli_p[LLI_WORD1_OFFSET] |= FIELD_PREP(LLI_HADDR_MASK, (addr >> 32));
#पूर्ण_अगर /* CONFIG_ARCH_DMA_ADDR_T_64BIT */
पूर्ण

अटल अंतरभूत व्योम cc_lli_set_size(u32 *lli_p, u16 size)
अणु
	lli_p[LLI_WORD1_OFFSET] &= ~LLI_SIZE_MASK;
	lli_p[LLI_WORD1_OFFSET] |= FIELD_PREP(LLI_SIZE_MASK, size);
पूर्ण

#पूर्ण_अगर /*_CC_LLI_DEFS_H_*/
