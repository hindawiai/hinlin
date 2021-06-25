<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  TI EDMA definitions
 *
 *  Copyright (C) 2006-2013 Texas Instruments.
 */

/*
 * This EDMA3 programming framework exposes two basic kinds of resource:
 *
 *  Channel	Triggers transfers, usually from a hardware event but
 *		also manually or by "chaining" from DMA completions.
 *		Each channel is coupled to a Parameter RAM (PaRAM) slot.
 *
 *  Slot	Each PaRAM slot holds a DMA transfer descriptor (PaRAM
 *		"set"), source and destination addresses, a link to a
 *		next PaRAM slot (अगर any), options क्रम the transfer, and
 *		inकाष्ठाions क्रम updating those addresses.  There are
 *		more than twice as many slots as event channels.
 *
 * Each PaRAM set describes a sequence of transfers, either क्रम one large
 * buffer or क्रम several discontiguous smaller buffers.  An EDMA transfer
 * is driven only from a channel, which perक्रमms the transfers specअगरied
 * in its PaRAM slot until there are no more transfers.  When that last
 * transfer completes, the "link" field may be used to reload the channel's
 * PaRAM slot with a new transfer descriptor.
 *
 * The EDMA Channel Controller (CC) maps requests from channels पूर्णांकo physical
 * Transfer Controller (TC) requests when the channel triggers (by hardware
 * or software events, or by chaining).  The two physical DMA channels provided
 * by the TCs are thus shared by many logical channels.
 *
 * DaVinci hardware also has a "QDMA" mechanism which is not currently
 * supported through this पूर्णांकerface.  (DSP firmware uses it though.)
 */

#अगर_अघोषित EDMA_H_
#घोषणा EDMA_H_

क्रमागत dma_event_q अणु
	EVENTQ_0 = 0,
	EVENTQ_1 = 1,
	EVENTQ_2 = 2,
	EVENTQ_3 = 3,
	EVENTQ_DEFAULT = -1
पूर्ण;

#घोषणा EDMA_CTLR_CHAN(ctlr, chan)	(((ctlr) << 16) | (chan))
#घोषणा EDMA_CTLR(i)			((i) >> 16)
#घोषणा EDMA_CHAN_SLOT(i)		((i) & 0xffff)

#घोषणा EDMA_FILTER_PARAM(ctlr, chan)	((पूर्णांक[]) अणु EDMA_CTLR_CHAN(ctlr, chan) पूर्ण)

काष्ठा edma_rsv_info अणु

	स्थिर s16	(*rsv_chans)[2];
	स्थिर s16	(*rsv_slots)[2];
पूर्ण;

काष्ठा dma_slave_map;

/* platक्रमm_data क्रम EDMA driver */
काष्ठा edma_soc_info अणु
	/*
	 * Default queue is expected to be a low-priority queue.
	 * This way, दीर्घ transfers on the शेष queue started
	 * by the codec engine will not cause audio defects.
	 */
	क्रमागत dma_event_q	शेष_queue;

	/* Resource reservation क्रम other cores */
	काष्ठा edma_rsv_info	*rsv;

	/* List of channels allocated क्रम स_नकल, terminated with -1 */
	s32			*स_नकल_channels;

	s8	(*queue_priority_mapping)[2];
	स्थिर s16	(*xbar_chans)[2];

	स्थिर काष्ठा dma_slave_map *slave_map;
	पूर्णांक slavecnt;
पूर्ण;

#पूर्ण_अगर
