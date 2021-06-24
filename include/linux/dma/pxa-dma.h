<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PXA_DMA_H_
#घोषणा _PXA_DMA_H_

क्रमागत pxad_chan_prio अणु
	PXAD_PRIO_HIGHEST = 0,
	PXAD_PRIO_NORMAL,
	PXAD_PRIO_LOW,
	PXAD_PRIO_LOWEST,
पूर्ण;

/**
 * काष्ठा pxad_param - dma channel request parameters
 * @drcmr: requestor line number
 * @prio: minimal mandatory priority of the channel
 *
 * If a requested channel is granted, its priority will be at least @prio,
 * ie. अगर PXAD_PRIO_LOW is required, the requested channel will be either
 * PXAD_PRIO_LOW, PXAD_PRIO_NORMAL or PXAD_PRIO_HIGHEST.
 */
काष्ठा pxad_param अणु
	अचिन्हित पूर्णांक drcmr;
	क्रमागत pxad_chan_prio prio;
पूर्ण;

#पूर्ण_अगर /* _PXA_DMA_H_ */
