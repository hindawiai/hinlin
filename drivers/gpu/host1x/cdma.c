<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Command DMA
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */


#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/host1x.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>
#समावेश <trace/events/host1x.h>

#समावेश "cdma.h"
#समावेश "channel.h"
#समावेश "dev.h"
#समावेश "debug.h"
#समावेश "job.h"

/*
 * push_buffer
 *
 * The push buffer is a circular array of words to be fetched by command DMA.
 * Note that it works slightly dअगरferently to the sync queue; fence == pos
 * means that the push buffer is full, not empty.
 */

/*
 * Typically the commands written पूर्णांकo the push buffer are a pair of words. We
 * use slots to represent each of these pairs and to simplअगरy things. Note the
 * strange number of slots allocated here. 512 slots will fit exactly within a
 * single memory page. We also need one additional word at the end of the push
 * buffer क्रम the RESTART opcode that will inकाष्ठा the CDMA to jump back to
 * the beginning of the push buffer. With 512 slots, this means that we'll use
 * 2 memory pages and waste 4092 bytes of the second page that will never be
 * used.
 */
#घोषणा HOST1X_PUSHBUFFER_SLOTS	511

/*
 * Clean up push buffer resources
 */
अटल व्योम host1x_pushbuffer_destroy(काष्ठा push_buffer *pb)
अणु
	काष्ठा host1x_cdma *cdma = pb_to_cdma(pb);
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);

	अगर (!pb->mapped)
		वापस;

	अगर (host1x->करोमुख्य) अणु
		iommu_unmap(host1x->करोमुख्य, pb->dma, pb->alloc_size);
		मुक्त_iova(&host1x->iova, iova_pfn(&host1x->iova, pb->dma));
	पूर्ण

	dma_मुक्त_wc(host1x->dev, pb->alloc_size, pb->mapped, pb->phys);

	pb->mapped = शून्य;
	pb->phys = 0;
पूर्ण

/*
 * Init push buffer resources
 */
अटल पूर्णांक host1x_pushbuffer_init(काष्ठा push_buffer *pb)
अणु
	काष्ठा host1x_cdma *cdma = pb_to_cdma(pb);
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	काष्ठा iova *alloc;
	u32 size;
	पूर्णांक err;

	pb->mapped = शून्य;
	pb->phys = 0;
	pb->size = HOST1X_PUSHBUFFER_SLOTS * 8;

	size = pb->size + 4;

	/* initialize buffer poपूर्णांकers */
	pb->fence = pb->size - 8;
	pb->pos = 0;

	अगर (host1x->करोमुख्य) अणु
		अचिन्हित दीर्घ shअगरt;

		size = iova_align(&host1x->iova, size);

		pb->mapped = dma_alloc_wc(host1x->dev, size, &pb->phys,
					  GFP_KERNEL);
		अगर (!pb->mapped)
			वापस -ENOMEM;

		shअगरt = iova_shअगरt(&host1x->iova);
		alloc = alloc_iova(&host1x->iova, size >> shअगरt,
				   host1x->ioबहु_पूर्ण >> shअगरt, true);
		अगर (!alloc) अणु
			err = -ENOMEM;
			जाओ iommu_मुक्त_mem;
		पूर्ण

		pb->dma = iova_dma_addr(&host1x->iova, alloc);
		err = iommu_map(host1x->करोमुख्य, pb->dma, pb->phys, size,
				IOMMU_READ);
		अगर (err)
			जाओ iommu_मुक्त_iova;
	पूर्ण अन्यथा अणु
		pb->mapped = dma_alloc_wc(host1x->dev, size, &pb->phys,
					  GFP_KERNEL);
		अगर (!pb->mapped)
			वापस -ENOMEM;

		pb->dma = pb->phys;
	पूर्ण

	pb->alloc_size = size;

	host1x_hw_pushbuffer_init(host1x, pb);

	वापस 0;

iommu_मुक्त_iova:
	__मुक्त_iova(&host1x->iova, alloc);
iommu_मुक्त_mem:
	dma_मुक्त_wc(host1x->dev, size, pb->mapped, pb->phys);

	वापस err;
पूर्ण

/*
 * Push two words to the push buffer
 * Caller must ensure push buffer is not full
 */
अटल व्योम host1x_pushbuffer_push(काष्ठा push_buffer *pb, u32 op1, u32 op2)
अणु
	u32 *p = (u32 *)((व्योम *)pb->mapped + pb->pos);

	WARN_ON(pb->pos == pb->fence);
	*(p++) = op1;
	*(p++) = op2;
	pb->pos += 8;

	अगर (pb->pos >= pb->size)
		pb->pos -= pb->size;
पूर्ण

/*
 * Pop a number of two word slots from the push buffer
 * Caller must ensure push buffer is not empty
 */
अटल व्योम host1x_pushbuffer_pop(काष्ठा push_buffer *pb, अचिन्हित पूर्णांक slots)
अणु
	/* Advance the next ग_लिखो position */
	pb->fence += slots * 8;

	अगर (pb->fence >= pb->size)
		pb->fence -= pb->size;
पूर्ण

/*
 * Return the number of two word slots मुक्त in the push buffer
 */
अटल u32 host1x_pushbuffer_space(काष्ठा push_buffer *pb)
अणु
	अचिन्हित पूर्णांक fence = pb->fence;

	अगर (pb->fence < pb->pos)
		fence += pb->size;

	वापस (fence - pb->pos) / 8;
पूर्ण

/*
 * Sleep (अगर necessary) until the requested event happens
 *   - CDMA_EVENT_SYNC_QUEUE_EMPTY : sync queue is completely empty.
 *     - Returns 1
 *   - CDMA_EVENT_PUSH_BUFFER_SPACE : there is space in the push buffer
 *     - Return the amount of space (> 0)
 * Must be called with the cdma lock held.
 */
अचिन्हित पूर्णांक host1x_cdma_रुको_locked(काष्ठा host1x_cdma *cdma,
				     क्रमागत cdma_event event)
अणु
	क्रम (;;) अणु
		काष्ठा push_buffer *pb = &cdma->push_buffer;
		अचिन्हित पूर्णांक space;

		चयन (event) अणु
		हाल CDMA_EVENT_SYNC_QUEUE_EMPTY:
			space = list_empty(&cdma->sync_queue) ? 1 : 0;
			अवरोध;

		हाल CDMA_EVENT_PUSH_BUFFER_SPACE:
			space = host1x_pushbuffer_space(pb);
			अवरोध;

		शेष:
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		अगर (space)
			वापस space;

		trace_host1x_रुको_cdma(dev_name(cdma_to_channel(cdma)->dev),
				       event);

		/* If somebody has managed to alपढ़ोy start रुकोing, yield */
		अगर (cdma->event != CDMA_EVENT_NONE) अणु
			mutex_unlock(&cdma->lock);
			schedule();
			mutex_lock(&cdma->lock);
			जारी;
		पूर्ण

		cdma->event = event;

		mutex_unlock(&cdma->lock);
		रुको_क्रम_completion(&cdma->complete);
		mutex_lock(&cdma->lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Sleep (अगर necessary) until the push buffer has enough मुक्त space.
 *
 * Must be called with the cdma lock held.
 */
अटल पूर्णांक host1x_cdma_रुको_pushbuffer_space(काष्ठा host1x *host1x,
					     काष्ठा host1x_cdma *cdma,
					     अचिन्हित पूर्णांक needed)
अणु
	जबतक (true) अणु
		काष्ठा push_buffer *pb = &cdma->push_buffer;
		अचिन्हित पूर्णांक space;

		space = host1x_pushbuffer_space(pb);
		अगर (space >= needed)
			अवरोध;

		trace_host1x_रुको_cdma(dev_name(cdma_to_channel(cdma)->dev),
				       CDMA_EVENT_PUSH_BUFFER_SPACE);

		host1x_hw_cdma_flush(host1x, cdma);

		/* If somebody has managed to alपढ़ोy start रुकोing, yield */
		अगर (cdma->event != CDMA_EVENT_NONE) अणु
			mutex_unlock(&cdma->lock);
			schedule();
			mutex_lock(&cdma->lock);
			जारी;
		पूर्ण

		cdma->event = CDMA_EVENT_PUSH_BUFFER_SPACE;

		mutex_unlock(&cdma->lock);
		रुको_क्रम_completion(&cdma->complete);
		mutex_lock(&cdma->lock);
	पूर्ण

	वापस 0;
पूर्ण
/*
 * Start समयr that tracks the समय spent by the job.
 * Must be called with the cdma lock held.
 */
अटल व्योम cdma_start_समयr_locked(काष्ठा host1x_cdma *cdma,
				    काष्ठा host1x_job *job)
अणु
	अगर (cdma->समयout.client) अणु
		/* समयr alपढ़ोy started */
		वापस;
	पूर्ण

	cdma->समयout.client = job->client;
	cdma->समयout.syncpt = job->syncpt;
	cdma->समयout.syncpt_val = job->syncpt_end;
	cdma->समयout.start_kसमय = kसमय_get();

	schedule_delayed_work(&cdma->समयout.wq,
			      msecs_to_jअगरfies(job->समयout));
पूर्ण

/*
 * Stop समयr when a buffer submission completes.
 * Must be called with the cdma lock held.
 */
अटल व्योम stop_cdma_समयr_locked(काष्ठा host1x_cdma *cdma)
अणु
	cancel_delayed_work(&cdma->समयout.wq);
	cdma->समयout.client = शून्य;
पूर्ण

/*
 * For all sync queue entries that have alपढ़ोy finished according to the
 * current sync poपूर्णांक रेजिस्टरs:
 *  - unpin & unref their mems
 *  - pop their push buffer slots
 *  - हटाओ them from the sync queue
 * This is normally called from the host code's worker thपढ़ो, but can be
 * called manually अगर necessary.
 * Must be called with the cdma lock held.
 */
अटल व्योम update_cdma_locked(काष्ठा host1x_cdma *cdma)
अणु
	bool संकेत = false;
	काष्ठा host1x_job *job, *n;

	/* If CDMA is stopped, queue is cleared and we can वापस */
	अगर (!cdma->running)
		वापस;

	/*
	 * Walk the sync queue, पढ़ोing the sync poपूर्णांक रेजिस्टरs as necessary,
	 * to consume as many sync queue entries as possible without blocking
	 */
	list_क्रम_each_entry_safe(job, n, &cdma->sync_queue, list) अणु
		काष्ठा host1x_syncpt *sp = job->syncpt;

		/* Check whether this syncpt has completed, and bail अगर not */
		अगर (!host1x_syncpt_is_expired(sp, job->syncpt_end)) अणु
			/* Start समयr on next pending syncpt */
			अगर (job->समयout)
				cdma_start_समयr_locked(cdma, job);

			अवरोध;
		पूर्ण

		/* Cancel समयout, when a buffer completes */
		अगर (cdma->समयout.client)
			stop_cdma_समयr_locked(cdma);

		/* Unpin the memory */
		host1x_job_unpin(job);

		/* Pop push buffer slots */
		अगर (job->num_slots) अणु
			काष्ठा push_buffer *pb = &cdma->push_buffer;

			host1x_pushbuffer_pop(pb, job->num_slots);

			अगर (cdma->event == CDMA_EVENT_PUSH_BUFFER_SPACE)
				संकेत = true;
		पूर्ण

		list_del(&job->list);
		host1x_job_put(job);
	पूर्ण

	अगर (cdma->event == CDMA_EVENT_SYNC_QUEUE_EMPTY &&
	    list_empty(&cdma->sync_queue))
		संकेत = true;

	अगर (संकेत) अणु
		cdma->event = CDMA_EVENT_NONE;
		complete(&cdma->complete);
	पूर्ण
पूर्ण

व्योम host1x_cdma_update_sync_queue(काष्ठा host1x_cdma *cdma,
				   काष्ठा device *dev)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	u32 restart_addr, syncpt_incrs, syncpt_val;
	काष्ठा host1x_job *job, *next_job = शून्य;

	syncpt_val = host1x_syncpt_load(cdma->समयout.syncpt);

	dev_dbg(dev, "%s: starting cleanup (thresh %d)\n",
		__func__, syncpt_val);

	/*
	 * Move the sync_queue पढ़ो poपूर्णांकer to the first entry that hasn't
	 * completed based on the current HW syncpt value. It's likely there
	 * won't be any (i.e. we're still at the head), but covers the हाल
	 * where a syncpt incr happens just prior/during the tearकरोwn.
	 */

	dev_dbg(dev, "%s: skip completed buffers still in sync_queue\n",
		__func__);

	list_क्रम_each_entry(job, &cdma->sync_queue, list) अणु
		अगर (syncpt_val < job->syncpt_end) अणु

			अगर (!list_is_last(&job->list, &cdma->sync_queue))
				next_job = list_next_entry(job, list);

			जाओ syncpt_incr;
		पूर्ण

		host1x_job_dump(dev, job);
	पूर्ण

	/* all jobs have been completed */
	job = शून्य;

syncpt_incr:

	/*
	 * Increment with CPU the reमुख्यing syncpts of a partially executed job.
	 *
	 * CDMA will जारी execution starting with the next job or will get
	 * पूर्णांकo idle state.
	 */
	अगर (next_job)
		restart_addr = next_job->first_get;
	अन्यथा
		restart_addr = cdma->last_pos;

	/* करो CPU increments क्रम the reमुख्यing syncpts */
	अगर (job) अणु
		dev_dbg(dev, "%s: perform CPU incr on pending buffers\n",
			__func__);

		/* won't need a समयout when replayed */
		job->समयout = 0;

		syncpt_incrs = job->syncpt_end - syncpt_val;
		dev_dbg(dev, "%s: CPU incr (%d)\n", __func__, syncpt_incrs);

		host1x_job_dump(dev, job);

		/* safe to use CPU to incr syncpts */
		host1x_hw_cdma_समयout_cpu_incr(host1x, cdma, job->first_get,
						syncpt_incrs, job->syncpt_end,
						job->num_slots);

		dev_dbg(dev, "%s: finished sync_queue modification\n",
			__func__);
	पूर्ण

	/* roll back DMAGET and start up channel again */
	host1x_hw_cdma_resume(host1x, cdma, restart_addr);
पूर्ण

/*
 * Create a cdma
 */
पूर्णांक host1x_cdma_init(काष्ठा host1x_cdma *cdma)
अणु
	पूर्णांक err;

	mutex_init(&cdma->lock);
	init_completion(&cdma->complete);

	INIT_LIST_HEAD(&cdma->sync_queue);

	cdma->event = CDMA_EVENT_NONE;
	cdma->running = false;
	cdma->tornकरोwn = false;

	err = host1x_pushbuffer_init(&cdma->push_buffer);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Destroy a cdma
 */
पूर्णांक host1x_cdma_deinit(काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा push_buffer *pb = &cdma->push_buffer;
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);

	अगर (cdma->running) अणु
		pr_warn("%s: CDMA still running\n", __func__);
		वापस -EBUSY;
	पूर्ण

	host1x_pushbuffer_destroy(pb);
	host1x_hw_cdma_समयout_destroy(host1x, cdma);

	वापस 0;
पूर्ण

/*
 * Begin a cdma submit
 */
पूर्णांक host1x_cdma_begin(काष्ठा host1x_cdma *cdma, काष्ठा host1x_job *job)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);

	mutex_lock(&cdma->lock);

	अगर (job->समयout) अणु
		/* init state on first submit with समयout value */
		अगर (!cdma->समयout.initialized) अणु
			पूर्णांक err;

			err = host1x_hw_cdma_समयout_init(host1x, cdma);
			अगर (err) अणु
				mutex_unlock(&cdma->lock);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!cdma->running)
		host1x_hw_cdma_start(host1x, cdma);

	cdma->slots_मुक्त = 0;
	cdma->slots_used = 0;
	cdma->first_get = cdma->push_buffer.pos;

	trace_host1x_cdma_begin(dev_name(job->channel->dev));
	वापस 0;
पूर्ण

/*
 * Push two words पूर्णांकo a push buffer slot
 * Blocks as necessary अगर the push buffer is full.
 */
व्योम host1x_cdma_push(काष्ठा host1x_cdma *cdma, u32 op1, u32 op2)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	काष्ठा push_buffer *pb = &cdma->push_buffer;
	u32 slots_मुक्त = cdma->slots_मुक्त;

	अगर (host1x_debug_trace_cmdbuf)
		trace_host1x_cdma_push(dev_name(cdma_to_channel(cdma)->dev),
				       op1, op2);

	अगर (slots_मुक्त == 0) अणु
		host1x_hw_cdma_flush(host1x, cdma);
		slots_मुक्त = host1x_cdma_रुको_locked(cdma,
						CDMA_EVENT_PUSH_BUFFER_SPACE);
	पूर्ण

	cdma->slots_मुक्त = slots_मुक्त - 1;
	cdma->slots_used++;
	host1x_pushbuffer_push(pb, op1, op2);
पूर्ण

/*
 * Push four words पूर्णांकo two consecutive push buffer slots. Note that extra
 * care needs to be taken not to split the two slots across the end of the
 * push buffer. Otherwise the RESTART opcode at the end of the push buffer
 * that ensures processing will restart at the beginning will अवरोध up the
 * four words.
 *
 * Blocks as necessary अगर the push buffer is full.
 */
व्योम host1x_cdma_push_wide(काष्ठा host1x_cdma *cdma, u32 op1, u32 op2,
			   u32 op3, u32 op4)
अणु
	काष्ठा host1x_channel *channel = cdma_to_channel(cdma);
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	काष्ठा push_buffer *pb = &cdma->push_buffer;
	अचिन्हित पूर्णांक needed = 2, extra = 0, i;
	अचिन्हित पूर्णांक space = cdma->slots_मुक्त;

	अगर (host1x_debug_trace_cmdbuf)
		trace_host1x_cdma_push_wide(dev_name(channel->dev), op1, op2,
					    op3, op4);

	/* compute number of extra slots needed क्रम padding */
	अगर (pb->pos + 16 > pb->size) अणु
		extra = (pb->size - pb->pos) / 8;
		needed += extra;
	पूर्ण

	host1x_cdma_रुको_pushbuffer_space(host1x, cdma, needed);
	space = host1x_pushbuffer_space(pb);

	cdma->slots_मुक्त = space - needed;
	cdma->slots_used += needed;

	/*
	 * Note that we rely on the fact that this is only used to submit wide
	 * gather opcodes, which consist of 3 words, and they are padded with
	 * a NOP to aव्योम having to deal with fractional slots (a slot always
	 * represents 2 words). The fourth opcode passed to this function will
	 * thereक्रमe always be a NOP.
	 *
	 * This works around a slight ambiguity when it comes to opcodes. For
	 * all current host1x incarnations the NOP opcode uses the exact same
	 * encoding (0x20000000), so we could hard-code the value here, but a
	 * new incarnation may change it and अवरोध that assumption.
	 */
	क्रम (i = 0; i < extra; i++)
		host1x_pushbuffer_push(pb, op4, op4);

	host1x_pushbuffer_push(pb, op1, op2);
	host1x_pushbuffer_push(pb, op3, op4);
पूर्ण

/*
 * End a cdma submit
 * Kick off DMA, add job to the sync queue, and a number of slots to be मुक्तd
 * from the pushbuffer. The handles क्रम a submit must all be pinned at the same
 * समय, but they can be unpinned in smaller chunks.
 */
व्योम host1x_cdma_end(काष्ठा host1x_cdma *cdma,
		     काष्ठा host1x_job *job)
अणु
	काष्ठा host1x *host1x = cdma_to_host1x(cdma);
	bool idle = list_empty(&cdma->sync_queue);

	host1x_hw_cdma_flush(host1x, cdma);

	job->first_get = cdma->first_get;
	job->num_slots = cdma->slots_used;
	host1x_job_get(job);
	list_add_tail(&job->list, &cdma->sync_queue);

	/* start समयr on idle -> active transitions */
	अगर (job->समयout && idle)
		cdma_start_समयr_locked(cdma, job);

	trace_host1x_cdma_end(dev_name(job->channel->dev));
	mutex_unlock(&cdma->lock);
पूर्ण

/*
 * Update cdma state according to current sync poपूर्णांक values
 */
व्योम host1x_cdma_update(काष्ठा host1x_cdma *cdma)
अणु
	mutex_lock(&cdma->lock);
	update_cdma_locked(cdma);
	mutex_unlock(&cdma->lock);
पूर्ण
