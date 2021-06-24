<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Command DMA
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_CDMA_H
#घोषणा __HOST1X_CDMA_H

#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>

काष्ठा host1x_syncpt;
काष्ठा host1x_userctx_समयout;
काष्ठा host1x_job;

/*
 * cdma
 *
 * This is in अक्षरge of a host command DMA channel.
 * Sends ops to a push buffer, and takes responsibility क्रम unpinning
 * (& possibly मुक्तing) of memory after those ops have completed.
 * Producer:
 *	begin
 *		push - send ops to the push buffer
 *	end - start command DMA and enqueue handles to be unpinned
 * Consumer:
 *	update - call to update sync queue and push buffer, unpin memory
 */

काष्ठा push_buffer अणु
	व्योम *mapped;			/* mapped pushbuffer memory */
	dma_addr_t dma;			/* device address of pushbuffer */
	dma_addr_t phys;		/* physical address of pushbuffer */
	u32 fence;			/* index we've written */
	u32 pos;			/* index to ग_लिखो to */
	u32 size;
	u32 alloc_size;
पूर्ण;

काष्ठा buffer_समयout अणु
	काष्ठा delayed_work wq;		/* work queue */
	bool initialized;		/* समयr one-समय setup flag */
	काष्ठा host1x_syncpt *syncpt;	/* buffer completion syncpt */
	u32 syncpt_val;			/* syncpt value when completed */
	kसमय_प्रकार start_kसमय;		/* starting समय */
	/* context समयout inक्रमmation */
	काष्ठा host1x_client *client;
पूर्ण;

क्रमागत cdma_event अणु
	CDMA_EVENT_NONE,		/* not रुकोing क्रम any event */
	CDMA_EVENT_SYNC_QUEUE_EMPTY,	/* रुको क्रम empty sync queue */
	CDMA_EVENT_PUSH_BUFFER_SPACE	/* रुको क्रम space in push buffer */
पूर्ण;

काष्ठा host1x_cdma अणु
	काष्ठा mutex lock;		/* controls access to shared state */
	काष्ठा completion complete;	/* संकेतled when event occurs */
	क्रमागत cdma_event event;		/* event that complete is रुकोing क्रम */
	अचिन्हित पूर्णांक slots_used;	/* pb slots used in current submit */
	अचिन्हित पूर्णांक slots_मुक्त;	/* pb slots मुक्त in current submit */
	अचिन्हित पूर्णांक first_get;		/* DMAGET value, where submit begins */
	अचिन्हित पूर्णांक last_pos;		/* last value written to DMAPUT */
	काष्ठा push_buffer push_buffer;	/* channel's push buffer */
	काष्ठा list_head sync_queue;	/* job queue */
	काष्ठा buffer_समयout समयout;	/* channel's समयout state/wq */
	bool running;
	bool tornकरोwn;
पूर्ण;

#घोषणा cdma_to_channel(cdma) container_of(cdma, काष्ठा host1x_channel, cdma)
#घोषणा cdma_to_host1x(cdma) dev_get_drvdata(cdma_to_channel(cdma)->dev->parent)
#घोषणा pb_to_cdma(pb) container_of(pb, काष्ठा host1x_cdma, push_buffer)

पूर्णांक host1x_cdma_init(काष्ठा host1x_cdma *cdma);
पूर्णांक host1x_cdma_deinit(काष्ठा host1x_cdma *cdma);
पूर्णांक host1x_cdma_begin(काष्ठा host1x_cdma *cdma, काष्ठा host1x_job *job);
व्योम host1x_cdma_push(काष्ठा host1x_cdma *cdma, u32 op1, u32 op2);
व्योम host1x_cdma_push_wide(काष्ठा host1x_cdma *cdma, u32 op1, u32 op2,
			   u32 op3, u32 op4);
व्योम host1x_cdma_end(काष्ठा host1x_cdma *cdma, काष्ठा host1x_job *job);
व्योम host1x_cdma_update(काष्ठा host1x_cdma *cdma);
व्योम host1x_cdma_peek(काष्ठा host1x_cdma *cdma, u32 dmaget, पूर्णांक slot,
		      u32 *out);
अचिन्हित पूर्णांक host1x_cdma_रुको_locked(काष्ठा host1x_cdma *cdma,
				     क्रमागत cdma_event event);
व्योम host1x_cdma_update_sync_queue(काष्ठा host1x_cdma *cdma,
				   काष्ठा device *dev);
#पूर्ण_अगर
