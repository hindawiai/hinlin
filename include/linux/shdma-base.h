<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Dmaengine driver base library क्रम DMA controllers, found on SH-based SoCs
 *
 * extracted from shdma.c and headers
 *
 * Copyright (C) 2011-2012 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 * Copyright (C) 2009 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 * Copyright (C) 2009 Renesas Solutions, Inc. All rights reserved.
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 */

#अगर_अघोषित SHDMA_BASE_H
#घोषणा SHDMA_BASE_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

/**
 * shdma_pm_state - DMA channel PM state
 * SHDMA_PM_ESTABLISHED:	either idle or during data transfer
 * SHDMA_PM_BUSY:		during the transfer preparation, when we have to
 *				drop the lock temporarily
 * SHDMA_PM_PENDING:	transfers pending
 */
क्रमागत shdma_pm_state अणु
	SHDMA_PM_ESTABLISHED,
	SHDMA_PM_BUSY,
	SHDMA_PM_PENDING,
पूर्ण;

काष्ठा device;

/*
 * Drivers, using this library are expected to embed काष्ठा shdma_dev,
 * काष्ठा shdma_chan, काष्ठा shdma_desc, and काष्ठा shdma_slave
 * in their respective device, channel, descriptor and slave objects.
 */

काष्ठा shdma_slave अणु
	पूर्णांक slave_id;
पूर्ण;

काष्ठा shdma_desc अणु
	काष्ठा list_head node;
	काष्ठा dma_async_tx_descriptor async_tx;
	क्रमागत dma_transfer_direction direction;
	माप_प्रकार partial;
	dma_cookie_t cookie;
	पूर्णांक chunks;
	पूर्णांक mark;
	bool cyclic;			/* used as cyclic transfer */
पूर्ण;

काष्ठा shdma_chan अणु
	spinlock_t chan_lock;		/* Channel operation lock */
	काष्ठा list_head ld_queue;	/* Link descriptors queue */
	काष्ठा list_head ld_मुक्त;	/* Free link descriptors */
	काष्ठा dma_chan dma_chan;	/* DMA channel */
	काष्ठा device *dev;		/* Channel device */
	व्योम *desc;			/* buffer क्रम descriptor array */
	पूर्णांक desc_num;			/* desc count */
	माप_प्रकार max_xfer_len;		/* max transfer length */
	पूर्णांक id;				/* Raw id of this channel */
	पूर्णांक irq;			/* Channel IRQ */
	पूर्णांक slave_id;			/* Client ID क्रम slave DMA */
	पूर्णांक real_slave_id;		/* argument passed to filter function */
	पूर्णांक hw_req;			/* DMA request line क्रम slave DMA - same
					 * as MID/RID, used with DT */
	क्रमागत shdma_pm_state pm_state;
पूर्ण;

/**
 * काष्ठा shdma_ops - simple DMA driver operations
 * desc_completed:	वापस true, अगर this is the descriptor, that just has
 *			completed (atomic)
 * halt_channel:	stop DMA channel operation (atomic)
 * channel_busy:	वापस true, अगर the channel is busy (atomic)
 * slave_addr:		वापस slave DMA address
 * desc_setup:		set up the hardware specअगरic descriptor portion (atomic)
 * set_slave:		bind channel to a slave
 * setup_xfer:		configure channel hardware क्रम operation (atomic)
 * start_xfer:		start the DMA transfer (atomic)
 * embedded_desc:	वापस Nth काष्ठा shdma_desc poपूर्णांकer from the
 *			descriptor array
 * chan_irq:		process channel IRQ, वापस true अगर a transfer has
 *			completed (atomic)
 */
काष्ठा shdma_ops अणु
	bool (*desc_completed)(काष्ठा shdma_chan *, काष्ठा shdma_desc *);
	व्योम (*halt_channel)(काष्ठा shdma_chan *);
	bool (*channel_busy)(काष्ठा shdma_chan *);
	dma_addr_t (*slave_addr)(काष्ठा shdma_chan *);
	पूर्णांक (*desc_setup)(काष्ठा shdma_chan *, काष्ठा shdma_desc *,
			  dma_addr_t, dma_addr_t, माप_प्रकार *);
	पूर्णांक (*set_slave)(काष्ठा shdma_chan *, पूर्णांक, dma_addr_t, bool);
	व्योम (*setup_xfer)(काष्ठा shdma_chan *, पूर्णांक);
	व्योम (*start_xfer)(काष्ठा shdma_chan *, काष्ठा shdma_desc *);
	काष्ठा shdma_desc *(*embedded_desc)(व्योम *, पूर्णांक);
	bool (*chan_irq)(काष्ठा shdma_chan *, पूर्णांक);
	माप_प्रकार (*get_partial)(काष्ठा shdma_chan *, काष्ठा shdma_desc *);
पूर्ण;

काष्ठा shdma_dev अणु
	काष्ठा dma_device dma_dev;
	काष्ठा shdma_chan **schan;
	स्थिर काष्ठा shdma_ops *ops;
	माप_प्रकार desc_size;
पूर्ण;

#घोषणा shdma_क्रम_each_chan(c, d, i) क्रम (i = 0, c = (d)->schan[0]; \
				i < (d)->dma_dev.chancnt; c = (d)->schan[++i])

पूर्णांक shdma_request_irq(काष्ठा shdma_chan *, पूर्णांक,
			   अचिन्हित दीर्घ, स्थिर अक्षर *);
bool shdma_reset(काष्ठा shdma_dev *sdev);
व्योम shdma_chan_probe(काष्ठा shdma_dev *sdev,
			   काष्ठा shdma_chan *schan, पूर्णांक id);
व्योम shdma_chan_हटाओ(काष्ठा shdma_chan *schan);
पूर्णांक shdma_init(काष्ठा device *dev, काष्ठा shdma_dev *sdev,
		    पूर्णांक chan_num);
व्योम shdma_cleanup(काष्ठा shdma_dev *sdev);
#अगर IS_ENABLED(CONFIG_SH_DMAE_BASE)
bool shdma_chan_filter(काष्ठा dma_chan *chan, व्योम *arg);
#अन्यथा
अटल अंतरभूत bool shdma_chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
