<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2002 Integrated Device Technology, Inc.
 *		All rights reserved.
 *
 * DMA रेजिस्टर definition.
 *
 * Author : ryan.holmQVist@idt.com
 * Date	  : 20011005
 */

#अगर_अघोषित _ASM_RC32434_DMA_V_H_
#घोषणा _ASM_RC32434_DMA_V_H_

#समावेश  <यंत्र/mach-rc32434/dma.h>
#समावेश  <यंत्र/mach-rc32434/rc32434.h>

#घोषणा DMA_CHAN_OFFSET		0x14
#घोषणा IS_DMA_USED(X)		(((X) & \
				(DMA_DESC_FINI | DMA_DESC_DONE | DMA_DESC_TERM)) \
				!= 0)
#घोषणा DMA_COUNT(count)	((count) & DMA_DESC_COUNT_MSK)

#घोषणा DMA_HALT_TIMEOUT	500

अटल अंतरभूत पूर्णांक rc32434_halt_dma(काष्ठा dma_reg *ch)
अणु
	पूर्णांक समयout = 1;
	अगर (__raw_पढ़ोl(&ch->dmac) & DMA_CHAN_RUN_BIT) अणु
		__raw_ग_लिखोl(0, &ch->dmac);
		क्रम (समयout = DMA_HALT_TIMEOUT; समयout > 0; समयout--) अणु
			अगर (__raw_पढ़ोl(&ch->dmas) & DMA_STAT_HALT) अणु
				__raw_ग_लिखोl(0, &ch->dmas);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस समयout ? 0 : 1;
पूर्ण

अटल अंतरभूत व्योम rc32434_start_dma(काष्ठा dma_reg *ch, u32 dma_addr)
अणु
	__raw_ग_लिखोl(0, &ch->dmandptr);
	__raw_ग_लिखोl(dma_addr, &ch->dmadptr);
पूर्ण

अटल अंतरभूत व्योम rc32434_chain_dma(काष्ठा dma_reg *ch, u32 dma_addr)
अणु
	__raw_ग_लिखोl(dma_addr, &ch->dmandptr);
पूर्ण

#पूर्ण_अगर	/* _ASM_RC32434_DMA_V_H_ */
