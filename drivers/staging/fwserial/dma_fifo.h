<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * DMA-able FIFO पूर्णांकerface
 *
 * Copyright (C) 2012 Peter Hurley <peter@hurleysoftware.com>
 */

#अगर_अघोषित _DMA_FIFO_H_
#घोषणा _DMA_FIFO_H_

/**
 * The design basis क्रम the DMA FIFO is to provide an output side that
 * complies with the streaming DMA API design that can be DMA'd from directly
 * (without additional copying), coupled with an input side that मुख्यtains a
 * logically consistent 'apparent' size (ie, bytes in + bytes avail is अटल
 * क्रम the lअगरeसमय of the FIFO).
 *
 * DMA output transactions originate on a cache line boundary and can be
 * variably-sized. DMA output transactions can be retired out-of-order but
 * the FIFO will only advance the output in the original input sequence.
 * This means the FIFO will eventually stall अगर a transaction is never retired.
 *
 * Chunking the output side पूर्णांकo cache line multiples means that some FIFO
 * memory is unused. For example, अगर all the avail input has been pended out,
 * then the in and out markers are re-aligned to the next cache line.
 * The maximum possible waste is
 *     (cache line alignment - 1) * (max outstanding dma transactions)
 * This potential waste requires additional hidden capacity within the FIFO
 * to be able to accept input जबतक the 'apparent' size has not been reached.
 *
 * Additional cache lines (ie, guard area) are used to minimize DMA
 * fragmentation when wrapping at the end of the FIFO. Input is allowed पूर्णांकo the
 * guard area, but the in and out FIFO markers are wrapped when DMA is pended.
 */

#घोषणा DMA_FIFO_GUARD 3   /* # of cache lines to reserve क्रम the guard area */

काष्ठा dma_fअगरo अणु
	अचिन्हित पूर्णांक	 in;
	अचिन्हित पूर्णांक	 out;		/* updated when dma is pended         */
	अचिन्हित पूर्णांक	 करोne;		/* updated upon dma completion        */
	काष्ठा अणु
		अचिन्हित corrupt:1;
	पूर्ण;
	पूर्णांक		 size;		/* 'apparent' size of fअगरo	      */
	पूर्णांक		 guard;		/* ofs of guard area		      */
	पूर्णांक		 capacity;	/* size + reserved                    */
	पूर्णांक		 avail;		/* # of unused bytes in fअगरo          */
	अचिन्हित पूर्णांक	 align;		/* must be घातer of 2                 */
	पूर्णांक		 tx_limit;	/* max # of bytes per dma transaction */
	पूर्णांक		 खोलो_limit;	/* max # of outstanding allowed       */
	पूर्णांक		 खोलो;		/* # of outstanding dma transactions  */
	काष्ठा list_head pending;	/* fअगरo markers क्रम outstanding dma   */
	व्योम		 *data;
पूर्ण;

काष्ठा dma_pending अणु
	काष्ठा list_head link;
	व्योम		 *data;
	अचिन्हित पूर्णांक	 len;
	अचिन्हित पूर्णांक	 next;
	अचिन्हित पूर्णांक	 out;
पूर्ण;

अटल अंतरभूत व्योम dp_mark_completed(काष्ठा dma_pending *dp)
अणु
	dp->data += 1;
पूर्ण

अटल अंतरभूत bool dp_is_completed(काष्ठा dma_pending *dp)
अणु
	वापस (अचिन्हित दीर्घ)dp->data & 1UL;
पूर्ण

व्योम dma_fअगरo_init(काष्ठा dma_fअगरo *fअगरo);
पूर्णांक dma_fअगरo_alloc(काष्ठा dma_fअगरo *fअगरo, पूर्णांक size, अचिन्हित पूर्णांक align,
		   पूर्णांक tx_limit, पूर्णांक खोलो_limit, gfp_t gfp_mask);
व्योम dma_fअगरo_मुक्त(काष्ठा dma_fअगरo *fअगरo);
व्योम dma_fअगरo_reset(काष्ठा dma_fअगरo *fअगरo);
पूर्णांक dma_fअगरo_in(काष्ठा dma_fअगरo *fअगरo, स्थिर व्योम *src, पूर्णांक n);
पूर्णांक dma_fअगरo_out_pend(काष्ठा dma_fअगरo *fअगरo, काष्ठा dma_pending *pended);
पूर्णांक dma_fअगरo_out_complete(काष्ठा dma_fअगरo *fअगरo,
			  काष्ठा dma_pending *complete);

/* वापसs the # of used bytes in the fअगरo */
अटल अंतरभूत पूर्णांक dma_fअगरo_level(काष्ठा dma_fअगरo *fअगरo)
अणु
	वापस fअगरo->size - fअगरo->avail;
पूर्ण

/* वापसs the # of bytes पढ़ोy क्रम output in the fअगरo */
अटल अंतरभूत पूर्णांक dma_fअगरo_out_level(काष्ठा dma_fअगरo *fअगरo)
अणु
	वापस fअगरo->in - fअगरo->out;
पूर्ण

/* वापसs the # of unused bytes in the fअगरo */
अटल अंतरभूत पूर्णांक dma_fअगरo_avail(काष्ठा dma_fअगरo *fअगरo)
अणु
	वापस fअगरo->avail;
पूर्ण

/* वापसs true अगर fअगरo has max # of outstanding dmas */
अटल अंतरभूत bool dma_fअगरo_busy(काष्ठा dma_fअगरo *fअगरo)
अणु
	वापस fअगरo->खोलो == fअगरo->खोलो_limit;
पूर्ण

/* changes the max size of dma वापसed from dma_fअगरo_out_pend() */
अटल अंतरभूत पूर्णांक dma_fअगरo_change_tx_limit(काष्ठा dma_fअगरo *fअगरo, पूर्णांक tx_limit)
अणु
	tx_limit = round_करोwn(tx_limit, fअगरo->align);
	fअगरo->tx_limit = max_t(पूर्णांक, tx_limit, fअगरo->align);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _DMA_FIFO_H_ */
