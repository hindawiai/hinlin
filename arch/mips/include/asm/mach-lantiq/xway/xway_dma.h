<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *   Copyright (C) 2011 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित LTQ_DMA_H__
#घोषणा LTQ_DMA_H__

#घोषणा LTQ_DESC_SIZE		0x08	/* each descriptor is 64bit */
#घोषणा LTQ_DESC_NUM		0x40	/* 64 descriptors / channel */

#घोषणा LTQ_DMA_OWN		BIT(31) /* owner bit */
#घोषणा LTQ_DMA_C		BIT(30) /* complete bit */
#घोषणा LTQ_DMA_SOP		BIT(29) /* start of packet */
#घोषणा LTQ_DMA_EOP		BIT(28) /* end of packet */
#घोषणा LTQ_DMA_TX_OFFSET(x)	((x & 0x1f) << 23) /* data bytes offset */
#घोषणा LTQ_DMA_RX_OFFSET(x)	((x & 0x7) << 23) /* data bytes offset */
#घोषणा LTQ_DMA_SIZE_MASK	(0xffff) /* the size field is 16 bit */

काष्ठा ltq_dma_desc अणु
	u32 ctl;
	u32 addr;
पूर्ण;

काष्ठा ltq_dma_channel अणु
	पूर्णांक nr;				/* the channel number */
	पूर्णांक irq;			/* the mapped irq */
	पूर्णांक desc;			/* the current descriptor */
	काष्ठा ltq_dma_desc *desc_base; /* the descriptor base */
	पूर्णांक phys;			/* physical addr */
	काष्ठा device *dev;
पूर्ण;

क्रमागत अणु
	DMA_PORT_ETOP = 0,
	DMA_PORT_DEU,
पूर्ण;

बाह्य व्योम ltq_dma_enable_irq(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_disable_irq(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_ack_irq(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_खोलो(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_बंद(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_alloc_tx(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_alloc_rx(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_मुक्त(काष्ठा ltq_dma_channel *ch);
बाह्य व्योम ltq_dma_init_port(पूर्णांक p);

#पूर्ण_अगर
