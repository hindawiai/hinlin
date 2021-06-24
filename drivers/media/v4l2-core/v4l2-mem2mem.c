<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Memory-to-memory device framework क्रम Video क्रम Linux 2 and videobuf.
 *
 * Helper functions क्रम devices that use videobuf buffers क्रम both their
 * source and destination.
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <media/media-device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

MODULE_DESCRIPTION("Mem to mem device framework for videobuf");
MODULE_AUTHOR("Pawel Osciak, <pawel@osciak.com>");
MODULE_LICENSE("GPL");

अटल bool debug;
module_param(debug, bool, 0644);

#घोषणा dprपूर्णांकk(fmt, arg...)						\
	करो अणु								\
		अगर (debug)						\
			prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, ## arg);\
	पूर्ण जबतक (0)


/* Instance is alपढ़ोy queued on the job_queue */
#घोषणा TRANS_QUEUED		(1 << 0)
/* Instance is currently running in hardware */
#घोषणा TRANS_RUNNING		(1 << 1)
/* Instance is currently पातing */
#घोषणा TRANS_ABORT		(1 << 2)


/* The job queue is not running new jobs */
#घोषणा QUEUE_PAUSED		(1 << 0)


/* Offset base क्रम buffers on the destination queue - used to distinguish
 * between source and destination buffers when mmapping - they receive the same
 * offsets but क्रम dअगरferent queues */
#घोषणा DST_QUEUE_OFF_BASE	(1 << 30)

क्रमागत v4l2_m2m_entity_type अणु
	MEM2MEM_ENT_TYPE_SOURCE,
	MEM2MEM_ENT_TYPE_SINK,
	MEM2MEM_ENT_TYPE_PROC
पूर्ण;

अटल स्थिर अक्षर * स्थिर m2m_entity_name[] = अणु
	"source",
	"sink",
	"proc"
पूर्ण;

/**
 * काष्ठा v4l2_m2m_dev - per-device context
 * @source:		&काष्ठा media_entity poपूर्णांकer with the source entity
 *			Used only when the M2M device is रेजिस्टरed via
 *			v4l2_m2m_unरेजिस्टर_media_controller().
 * @source_pad:		&काष्ठा media_pad with the source pad.
 *			Used only when the M2M device is रेजिस्टरed via
 *			v4l2_m2m_unरेजिस्टर_media_controller().
 * @sink:		&काष्ठा media_entity poपूर्णांकer with the sink entity
 *			Used only when the M2M device is रेजिस्टरed via
 *			v4l2_m2m_unरेजिस्टर_media_controller().
 * @sink_pad:		&काष्ठा media_pad with the sink pad.
 *			Used only when the M2M device is रेजिस्टरed via
 *			v4l2_m2m_unरेजिस्टर_media_controller().
 * @proc:		&काष्ठा media_entity poपूर्णांकer with the M2M device itself.
 * @proc_pads:		&काष्ठा media_pad with the @proc pads.
 *			Used only when the M2M device is रेजिस्टरed via
 *			v4l2_m2m_unरेजिस्टर_media_controller().
 * @पूर्णांकf_devnode:	&काष्ठा media_पूर्णांकf devnode poपूर्णांकer with the पूर्णांकerface
 *			with controls the M2M device.
 * @curr_ctx:		currently running instance
 * @job_queue:		instances queued to run
 * @job_spinlock:	protects job_queue
 * @job_work:		worker to run queued jobs.
 * @job_queue_flags:	flags of the queue status, %QUEUE_PAUSED.
 * @m2m_ops:		driver callbacks
 */
काष्ठा v4l2_m2m_dev अणु
	काष्ठा v4l2_m2m_ctx	*curr_ctx;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_entity	*source;
	काष्ठा media_pad	source_pad;
	काष्ठा media_entity	sink;
	काष्ठा media_pad	sink_pad;
	काष्ठा media_entity	proc;
	काष्ठा media_pad	proc_pads[2];
	काष्ठा media_पूर्णांकf_devnode *पूर्णांकf_devnode;
#पूर्ण_अगर

	काष्ठा list_head	job_queue;
	spinlock_t		job_spinlock;
	काष्ठा work_काष्ठा	job_work;
	अचिन्हित दीर्घ		job_queue_flags;

	स्थिर काष्ठा v4l2_m2m_ops *m2m_ops;
पूर्ण;

अटल काष्ठा v4l2_m2m_queue_ctx *get_queue_ctx(काष्ठा v4l2_m2m_ctx *m2m_ctx,
						क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &m2m_ctx->out_q_ctx;
	अन्यथा
		वापस &m2m_ctx->cap_q_ctx;
पूर्ण

काष्ठा vb2_queue *v4l2_m2m_get_vq(काष्ठा v4l2_m2m_ctx *m2m_ctx,
				       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_m2m_queue_ctx *q_ctx;

	q_ctx = get_queue_ctx(m2m_ctx, type);
	अगर (!q_ctx)
		वापस शून्य;

	वापस &q_ctx->q;
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_get_vq);

काष्ठा vb2_v4l2_buffer *v4l2_m2m_next_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx)
अणु
	काष्ठा v4l2_m2m_buffer *b;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);

	अगर (list_empty(&q_ctx->rdy_queue)) अणु
		spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
		वापस शून्य;
	पूर्ण

	b = list_first_entry(&q_ctx->rdy_queue, काष्ठा v4l2_m2m_buffer, list);
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
	वापस &b->vb;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_next_buf);

काष्ठा vb2_v4l2_buffer *v4l2_m2m_last_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx)
अणु
	काष्ठा v4l2_m2m_buffer *b;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);

	अगर (list_empty(&q_ctx->rdy_queue)) अणु
		spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
		वापस शून्य;
	पूर्ण

	b = list_last_entry(&q_ctx->rdy_queue, काष्ठा v4l2_m2m_buffer, list);
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
	वापस &b->vb;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_last_buf);

काष्ठा vb2_v4l2_buffer *v4l2_m2m_buf_हटाओ(काष्ठा v4l2_m2m_queue_ctx *q_ctx)
अणु
	काष्ठा v4l2_m2m_buffer *b;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	अगर (list_empty(&q_ctx->rdy_queue)) अणु
		spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
		वापस शून्य;
	पूर्ण
	b = list_first_entry(&q_ctx->rdy_queue, काष्ठा v4l2_m2m_buffer, list);
	list_del(&b->list);
	q_ctx->num_rdy--;
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);

	वापस &b->vb;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_buf_हटाओ);

व्योम v4l2_m2m_buf_हटाओ_by_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx,
				काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा v4l2_m2m_buffer *b;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	b = container_of(vbuf, काष्ठा v4l2_m2m_buffer, vb);
	list_del(&b->list);
	q_ctx->num_rdy--;
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_buf_हटाओ_by_buf);

काष्ठा vb2_v4l2_buffer *
v4l2_m2m_buf_हटाओ_by_idx(काष्ठा v4l2_m2m_queue_ctx *q_ctx, अचिन्हित पूर्णांक idx)

अणु
	काष्ठा v4l2_m2m_buffer *b, *पंचांगp;
	काष्ठा vb2_v4l2_buffer *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	list_क्रम_each_entry_safe(b, पंचांगp, &q_ctx->rdy_queue, list) अणु
		अगर (b->vb.vb2_buf.index == idx) अणु
			list_del(&b->list);
			q_ctx->num_rdy--;
			ret = &b->vb;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_buf_हटाओ_by_idx);

/*
 * Scheduling handlers
 */

व्योम *v4l2_m2m_get_curr_priv(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *ret = शून्य;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	अगर (m2m_dev->curr_ctx)
		ret = m2m_dev->curr_ctx->priv;
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_get_curr_priv);

/**
 * v4l2_m2m_try_run() - select next job to perक्रमm and run it अगर possible
 * @m2m_dev: per-device context
 *
 * Get next transaction (अगर present) from the रुकोing jobs list and run it.
 *
 * Note that this function can run on a given v4l2_m2m_ctx context,
 * but call .device_run क्रम another context.
 */
अटल व्योम v4l2_m2m_try_run(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	अगर (शून्य != m2m_dev->curr_ctx) अणु
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprपूर्णांकk("Another instance is running, won't run now\n");
		वापस;
	पूर्ण

	अगर (list_empty(&m2m_dev->job_queue)) अणु
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprपूर्णांकk("No job pending\n");
		वापस;
	पूर्ण

	अगर (m2m_dev->job_queue_flags & QUEUE_PAUSED) अणु
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprपूर्णांकk("Running new jobs is paused\n");
		वापस;
	पूर्ण

	m2m_dev->curr_ctx = list_first_entry(&m2m_dev->job_queue,
				   काष्ठा v4l2_m2m_ctx, queue);
	m2m_dev->curr_ctx->job_flags |= TRANS_RUNNING;
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	dprपूर्णांकk("Running job on m2m_ctx: %p\n", m2m_dev->curr_ctx);
	m2m_dev->m2m_ops->device_run(m2m_dev->curr_ctx->priv);
पूर्ण

/*
 * __v4l2_m2m_try_queue() - queue a job
 * @m2m_dev: m2m device
 * @m2m_ctx: m2m context
 *
 * Check अगर this context is पढ़ोy to queue a job.
 *
 * This function can run in पूर्णांकerrupt context.
 */
अटल व्योम __v4l2_m2m_try_queue(काष्ठा v4l2_m2m_dev *m2m_dev,
				 काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	अचिन्हित दीर्घ flags_job;
	काष्ठा vb2_v4l2_buffer *dst, *src;

	dprपूर्णांकk("Trying to schedule a job for m2m_ctx: %p\n", m2m_ctx);

	अगर (!m2m_ctx->out_q_ctx.q.streaming
	    || !m2m_ctx->cap_q_ctx.q.streaming) अणु
		dprपूर्णांकk("Streaming needs to be on for both queues\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags_job);

	/* If the context is पातed then करोn't schedule it */
	अगर (m2m_ctx->job_flags & TRANS_ABORT) अणु
		dprपूर्णांकk("Aborted context\n");
		जाओ job_unlock;
	पूर्ण

	अगर (m2m_ctx->job_flags & TRANS_QUEUED) अणु
		dprपूर्णांकk("On job queue already\n");
		जाओ job_unlock;
	पूर्ण

	src = v4l2_m2m_next_src_buf(m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(m2m_ctx);
	अगर (!src && !m2m_ctx->out_q_ctx.buffered) अणु
		dprपूर्णांकk("No input buffers available\n");
		जाओ job_unlock;
	पूर्ण
	अगर (!dst && !m2m_ctx->cap_q_ctx.buffered) अणु
		dprपूर्णांकk("No output buffers available\n");
		जाओ job_unlock;
	पूर्ण

	m2m_ctx->new_frame = true;

	अगर (src && dst && dst->is_held &&
	    dst->vb2_buf.copied_बारtamp &&
	    dst->vb2_buf.बारtamp != src->vb2_buf.बारtamp) अणु
		dst->is_held = false;
		v4l2_m2m_dst_buf_हटाओ(m2m_ctx);
		v4l2_m2m_buf_करोne(dst, VB2_BUF_STATE_DONE);
		dst = v4l2_m2m_next_dst_buf(m2m_ctx);

		अगर (!dst && !m2m_ctx->cap_q_ctx.buffered) अणु
			dprपूर्णांकk("No output buffers available after returning held buffer\n");
			जाओ job_unlock;
		पूर्ण
	पूर्ण

	अगर (src && dst && (m2m_ctx->out_q_ctx.q.subप्रणाली_flags &
			   VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF))
		m2m_ctx->new_frame = !dst->vb2_buf.copied_बारtamp ||
			dst->vb2_buf.बारtamp != src->vb2_buf.बारtamp;

	अगर (m2m_ctx->has_stopped) अणु
		dprपूर्णांकk("Device has stopped\n");
		जाओ job_unlock;
	पूर्ण

	अगर (m2m_dev->m2m_ops->job_पढ़ोy
		&& (!m2m_dev->m2m_ops->job_पढ़ोy(m2m_ctx->priv))) अणु
		dprपूर्णांकk("Driver not ready\n");
		जाओ job_unlock;
	पूर्ण

	list_add_tail(&m2m_ctx->queue, &m2m_dev->job_queue);
	m2m_ctx->job_flags |= TRANS_QUEUED;

job_unlock:
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);
पूर्ण

/**
 * v4l2_m2m_try_schedule() - schedule and possibly run a job क्रम any context
 * @m2m_ctx: m2m context
 *
 * Check अगर this context is पढ़ोy to queue a job. If suitable,
 * run the next queued job on the mem2mem device.
 *
 * This function shouldn't run in पूर्णांकerrupt context.
 *
 * Note that v4l2_m2m_try_schedule() can schedule one job क्रम this context,
 * and then run another job क्रम another context.
 */
व्योम v4l2_m2m_try_schedule(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	काष्ठा v4l2_m2m_dev *m2m_dev = m2m_ctx->m2m_dev;

	__v4l2_m2m_try_queue(m2m_dev, m2m_ctx);
	v4l2_m2m_try_run(m2m_dev);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_try_schedule);

/**
 * v4l2_m2m_device_run_work() - run pending jobs क्रम the context
 * @work: Work काष्ठाure used क्रम scheduling the execution of this function.
 */
अटल व्योम v4l2_m2m_device_run_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा v4l2_m2m_dev *m2m_dev =
		container_of(work, काष्ठा v4l2_m2m_dev, job_work);

	v4l2_m2m_try_run(m2m_dev);
पूर्ण

/**
 * v4l2_m2m_cancel_job() - cancel pending jobs क्रम the context
 * @m2m_ctx: m2m context with jobs to be canceled
 *
 * In हाल of streamoff or release called on any context,
 * 1] If the context is currently running, then पात job will be called
 * 2] If the context is queued, then the context will be हटाओd from
 *    the job_queue
 */
अटल व्योम v4l2_m2m_cancel_job(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	काष्ठा v4l2_m2m_dev *m2m_dev;
	अचिन्हित दीर्घ flags;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);

	m2m_ctx->job_flags |= TRANS_ABORT;
	अगर (m2m_ctx->job_flags & TRANS_RUNNING) अणु
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		अगर (m2m_dev->m2m_ops->job_पात)
			m2m_dev->m2m_ops->job_पात(m2m_ctx->priv);
		dprपूर्णांकk("m2m_ctx %p running, will wait to complete\n", m2m_ctx);
		रुको_event(m2m_ctx->finished,
				!(m2m_ctx->job_flags & TRANS_RUNNING));
	पूर्ण अन्यथा अगर (m2m_ctx->job_flags & TRANS_QUEUED) अणु
		list_del(&m2m_ctx->queue);
		m2m_ctx->job_flags &= ~(TRANS_QUEUED | TRANS_RUNNING);
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
		dprपूर्णांकk("m2m_ctx: %p had been on queue and was removed\n",
			m2m_ctx);
	पूर्ण अन्यथा अणु
		/* Do nothing, was not on queue/running */
		spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);
	पूर्ण
पूर्ण

/*
 * Schedule the next job, called from v4l2_m2m_job_finish() or
 * v4l2_m2m_buf_करोne_and_job_finish().
 */
अटल व्योम v4l2_m2m_schedule_next_job(काष्ठा v4l2_m2m_dev *m2m_dev,
				       काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	/*
	 * This instance might have more buffers पढ़ोy, but since we करो not
	 * allow more than one job on the job_queue per instance, each has
	 * to be scheduled separately after the previous one finishes.
	 */
	__v4l2_m2m_try_queue(m2m_dev, m2m_ctx);

	/*
	 * We might be running in atomic context,
	 * but the job must be run in non-atomic context.
	 */
	schedule_work(&m2m_dev->job_work);
पूर्ण

/*
 * Assumes job_spinlock is held, called from v4l2_m2m_job_finish() or
 * v4l2_m2m_buf_करोne_and_job_finish().
 */
अटल bool _v4l2_m2m_job_finish(काष्ठा v4l2_m2m_dev *m2m_dev,
				 काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	अगर (!m2m_dev->curr_ctx || m2m_dev->curr_ctx != m2m_ctx) अणु
		dprपूर्णांकk("Called by an instance not currently running\n");
		वापस false;
	पूर्ण

	list_del(&m2m_dev->curr_ctx->queue);
	m2m_dev->curr_ctx->job_flags &= ~(TRANS_QUEUED | TRANS_RUNNING);
	wake_up(&m2m_dev->curr_ctx->finished);
	m2m_dev->curr_ctx = शून्य;
	वापस true;
पूर्ण

व्योम v4l2_m2m_job_finish(काष्ठा v4l2_m2m_dev *m2m_dev,
			 काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	अचिन्हित दीर्घ flags;
	bool schedule_next;

	/*
	 * This function should not be used क्रम drivers that support
	 * holding capture buffers. Those should use
	 * v4l2_m2m_buf_करोne_and_job_finish() instead.
	 */
	WARN_ON(m2m_ctx->out_q_ctx.q.subप्रणाली_flags &
		VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF);
	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	schedule_next = _v4l2_m2m_job_finish(m2m_dev, m2m_ctx);
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	अगर (schedule_next)
		v4l2_m2m_schedule_next_job(m2m_dev, m2m_ctx);
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_job_finish);

व्योम v4l2_m2m_buf_करोne_and_job_finish(काष्ठा v4l2_m2m_dev *m2m_dev,
				      काष्ठा v4l2_m2m_ctx *m2m_ctx,
				      क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	bool schedule_next = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	src_buf = v4l2_m2m_src_buf_हटाओ(m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(m2m_ctx);

	अगर (WARN_ON(!src_buf || !dst_buf))
		जाओ unlock;
	dst_buf->is_held = src_buf->flags & V4L2_BUF_FLAG_M2M_HOLD_CAPTURE_BUF;
	अगर (!dst_buf->is_held) अणु
		v4l2_m2m_dst_buf_हटाओ(m2m_ctx);
		v4l2_m2m_buf_करोne(dst_buf, state);
	पूर्ण
	/*
	 * If the request API is being used, वापसing the OUTPUT
	 * (src) buffer will wake-up any process रुकोing on the
	 * request file descriptor.
	 *
	 * Thereक्रमe, वापस the CAPTURE (dst) buffer first,
	 * to aव्योम संकेतling the request file descriptor
	 * beक्रमe the CAPTURE buffer is करोne.
	 */
	v4l2_m2m_buf_करोne(src_buf, state);
	schedule_next = _v4l2_m2m_job_finish(m2m_dev, m2m_ctx);
unlock:
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	अगर (schedule_next)
		v4l2_m2m_schedule_next_job(m2m_dev, m2m_ctx);
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_buf_करोne_and_job_finish);

व्योम v4l2_m2m_suspend(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा v4l2_m2m_ctx *curr_ctx;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	m2m_dev->job_queue_flags |= QUEUE_PAUSED;
	curr_ctx = m2m_dev->curr_ctx;
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	अगर (curr_ctx)
		रुको_event(curr_ctx->finished,
			   !(curr_ctx->job_flags & TRANS_RUNNING));
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_suspend);

व्योम v4l2_m2m_resume(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	m2m_dev->job_queue_flags &= ~QUEUE_PAUSED;
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	v4l2_m2m_try_run(m2m_dev);
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_resume);

पूर्णांक v4l2_m2m_reqbufs(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		     काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, reqbufs->type);
	ret = vb2_reqbufs(vq, reqbufs);
	/* If count == 0, then the owner has released all buffers and he
	   is no दीर्घer owner of the queue. Otherwise we have an owner. */
	अगर (ret == 0)
		vq->owner = reqbufs->count ? file->निजी_data : शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_reqbufs);

पूर्णांक v4l2_m2m_querybuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		      काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा vb2_queue *vq;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	ret = vb2_querybuf(vq, buf);

	/* Adjust MMAP memory offsets क्रम the CAPTURE queue */
	अगर (buf->memory == V4L2_MEMORY_MMAP && V4L2_TYPE_IS_CAPTURE(vq->type)) अणु
		अगर (V4L2_TYPE_IS_MULTIPLANAR(vq->type)) अणु
			क्रम (i = 0; i < buf->length; ++i)
				buf->m.planes[i].m.mem_offset
					+= DST_QUEUE_OFF_BASE;
		पूर्ण अन्यथा अणु
			buf->m.offset += DST_QUEUE_OFF_BASE;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_querybuf);

/*
 * This will add the LAST flag and mark the buffer management
 * state as stopped.
 * This is called when the last capture buffer must be flagged as LAST
 * in draining mode from the encoder/decoder driver buf_queue() callback
 * or from v4l2_update_last_buf_state() when a capture buffer is available.
 */
व्योम v4l2_m2m_last_buffer_करोne(काष्ठा v4l2_m2m_ctx *m2m_ctx,
			       काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	vbuf->flags |= V4L2_BUF_FLAG_LAST;
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	v4l2_m2m_mark_stopped(m2m_ctx);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_last_buffer_करोne);

/* When stop command is issued, update buffer management state */
अटल पूर्णांक v4l2_update_last_buf_state(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	काष्ठा vb2_v4l2_buffer *next_dst_buf;

	अगर (m2m_ctx->is_draining)
		वापस -EBUSY;

	अगर (m2m_ctx->has_stopped)
		वापस 0;

	m2m_ctx->last_src_buf = v4l2_m2m_last_src_buf(m2m_ctx);
	m2m_ctx->is_draining = true;

	/*
	 * The processing of the last output buffer queued beक्रमe
	 * the STOP command is expected to mark the buffer management
	 * state as stopped with v4l2_m2m_mark_stopped().
	 */
	अगर (m2m_ctx->last_src_buf)
		वापस 0;

	/*
	 * In हाल the output queue is empty, try to mark the last capture
	 * buffer as LAST.
	 */
	next_dst_buf = v4l2_m2m_dst_buf_हटाओ(m2m_ctx);
	अगर (!next_dst_buf) अणु
		/*
		 * Wait क्रम the next queued one in encoder/decoder driver
		 * buf_queue() callback using the v4l2_m2m_dst_buf_is_last()
		 * helper or in v4l2_m2m_qbuf() अगर encoder/decoder is not yet
		 * streaming.
		 */
		m2m_ctx->next_buf_last = true;
		वापस 0;
	पूर्ण

	v4l2_m2m_last_buffer_करोne(m2m_ctx, next_dst_buf);

	वापस 0;
पूर्ण

/*
 * Updates the encoding/decoding buffer management state, should
 * be called from encoder/decoder drivers start_streaming()
 */
व्योम v4l2_m2m_update_start_streaming_state(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					   काष्ठा vb2_queue *q)
अणु
	/* If start streaming again, untag the last output buffer */
	अगर (V4L2_TYPE_IS_OUTPUT(q->type))
		m2m_ctx->last_src_buf = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_update_start_streaming_state);

/*
 * Updates the encoding/decoding buffer management state, should
 * be called from encoder/decoder driver stop_streaming()
 */
व्योम v4l2_m2m_update_stop_streaming_state(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					  काष्ठा vb2_queue *q)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		/*
		 * If in draining state, either mark next dst buffer as
		 * करोne or flag next one to be marked as करोne either
		 * in encoder/decoder driver buf_queue() callback using
		 * the v4l2_m2m_dst_buf_is_last() helper or in v4l2_m2m_qbuf()
		 * अगर encoder/decoder is not yet streaming
		 */
		अगर (m2m_ctx->is_draining) अणु
			काष्ठा vb2_v4l2_buffer *next_dst_buf;

			m2m_ctx->last_src_buf = शून्य;
			next_dst_buf = v4l2_m2m_dst_buf_हटाओ(m2m_ctx);
			अगर (!next_dst_buf)
				m2m_ctx->next_buf_last = true;
			अन्यथा
				v4l2_m2m_last_buffer_करोne(m2m_ctx,
							  next_dst_buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		v4l2_m2m_clear_state(m2m_ctx);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_update_stop_streaming_state);

अटल व्योम v4l2_m2m_क्रमce_last_buf_करोne(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					 काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_buffer *vb;
	काष्ठा vb2_v4l2_buffer *vbuf;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(q->is_output))
		वापस;
	अगर (list_empty(&q->queued_list))
		वापस;

	vb = list_first_entry(&q->queued_list, काष्ठा vb2_buffer, queued_entry);
	क्रम (i = 0; i < vb->num_planes; i++)
		vb2_set_plane_payload(vb, i, 0);

	/*
	 * Since the buffer hasn't been queued to the पढ़ोy queue,
	 * mark is active and owned beक्रमe marking it LAST and DONE
	 */
	vb->state = VB2_BUF_STATE_ACTIVE;
	atomic_inc(&q->owned_by_drv_count);

	vbuf = to_vb2_v4l2_buffer(vb);
	vbuf->field = V4L2_FIELD_NONE;

	v4l2_m2m_last_buffer_करोne(m2m_ctx, vbuf);
पूर्ण

पूर्णांक v4l2_m2m_qbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		  काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	अगर (V4L2_TYPE_IS_CAPTURE(vq->type) &&
	    (buf->flags & V4L2_BUF_FLAG_REQUEST_FD)) अणु
		dprपूर्णांकk("%s: requests cannot be used with capture buffers\n",
			__func__);
		वापस -EPERM;
	पूर्ण

	ret = vb2_qbuf(vq, vdev->v4l2_dev->mdev, buf);
	अगर (ret)
		वापस ret;

	/*
	 * If the capture queue is streaming, but streaming hasn't started
	 * on the device, but was asked to stop, mark the previously queued
	 * buffer as DONE with LAST flag since it won't be queued on the
	 * device.
	 */
	अगर (V4L2_TYPE_IS_CAPTURE(vq->type) &&
	    vb2_is_streaming(vq) && !vb2_start_streaming_called(vq) &&
	   (v4l2_m2m_has_stopped(m2m_ctx) || v4l2_m2m_dst_buf_is_last(m2m_ctx)))
		v4l2_m2m_क्रमce_last_buf_करोne(m2m_ctx, vq);
	अन्यथा अगर (!(buf->flags & V4L2_BUF_FLAG_IN_REQUEST))
		v4l2_m2m_try_schedule(m2m_ctx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_qbuf);

पूर्णांक v4l2_m2m_dqbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		   काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	वापस vb2_dqbuf(vq, buf, file->f_flags & O_NONBLOCK);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_dqbuf);

पूर्णांक v4l2_m2m_prepare_buf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	वापस vb2_prepare_buf(vq, vdev->v4l2_dev->mdev, buf);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_prepare_buf);

पूर्णांक v4l2_m2m_create_bufs(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_create_buffers *create)
अणु
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, create->क्रमmat.type);
	वापस vb2_create_bufs(vq, create);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_create_bufs);

पूर्णांक v4l2_m2m_expbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		  काष्ठा v4l2_exportbuffer *eb)
अणु
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(m2m_ctx, eb->type);
	वापस vb2_expbuf(vq, eb);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_expbuf);

पूर्णांक v4l2_m2m_streamon(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		      क्रमागत v4l2_buf_type type)
अणु
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, type);
	ret = vb2_streamon(vq, type);
	अगर (!ret)
		v4l2_m2m_try_schedule(m2m_ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_streamon);

पूर्णांक v4l2_m2m_streamoff(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		       क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा v4l2_m2m_queue_ctx *q_ctx;
	अचिन्हित दीर्घ flags_job, flags;
	पूर्णांक ret;

	/* रुको until the current context is dequeued from job_queue */
	v4l2_m2m_cancel_job(m2m_ctx);

	q_ctx = get_queue_ctx(m2m_ctx, type);
	ret = vb2_streamoff(&q_ctx->q, type);
	अगर (ret)
		वापस ret;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_lock_irqsave(&m2m_dev->job_spinlock, flags_job);
	/* We should not be scheduled anymore, since we're dropping a queue. */
	अगर (m2m_ctx->job_flags & TRANS_QUEUED)
		list_del(&m2m_ctx->queue);
	m2m_ctx->job_flags = 0;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	/* Drop queue, since streamoff वापसs device to the same state as after
	 * calling reqbufs. */
	INIT_LIST_HEAD(&q_ctx->rdy_queue);
	q_ctx->num_rdy = 0;
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);

	अगर (m2m_dev->curr_ctx == m2m_ctx) अणु
		m2m_dev->curr_ctx = शून्य;
		wake_up(&m2m_ctx->finished);
	पूर्ण
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags_job);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_streamoff);

अटल __poll_t v4l2_m2m_poll_क्रम_data(काष्ठा file *file,
				       काष्ठा v4l2_m2m_ctx *m2m_ctx,
				       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा vb2_queue *src_q, *dst_q;
	__poll_t rc = 0;
	अचिन्हित दीर्घ flags;

	src_q = v4l2_m2m_get_src_vq(m2m_ctx);
	dst_q = v4l2_m2m_get_dst_vq(m2m_ctx);

	/*
	 * There has to be at least one buffer queued on each queued_list, which
	 * means either in driver alपढ़ोy or रुकोing क्रम driver to claim it
	 * and start processing.
	 */
	अगर ((!src_q->streaming || src_q->error ||
	     list_empty(&src_q->queued_list)) &&
	    (!dst_q->streaming || dst_q->error ||
	     list_empty(&dst_q->queued_list)))
		वापस EPOLLERR;

	spin_lock_irqsave(&src_q->करोne_lock, flags);
	अगर (!list_empty(&src_q->करोne_list))
		rc |= EPOLLOUT | EPOLLWRNORM;
	spin_unlock_irqrestore(&src_q->करोne_lock, flags);

	spin_lock_irqsave(&dst_q->करोne_lock, flags);
	/*
	 * If the last buffer was dequeued from the capture queue, संकेत
	 * userspace. DQBUF(CAPTURE) will वापस -EPIPE.
	 */
	अगर (!list_empty(&dst_q->करोne_list) || dst_q->last_buffer_dequeued)
		rc |= EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&dst_q->करोne_lock, flags);

	वापस rc;
पूर्ण

__poll_t v4l2_m2m_poll(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा vb2_queue *src_q = v4l2_m2m_get_src_vq(m2m_ctx);
	काष्ठा vb2_queue *dst_q = v4l2_m2m_get_dst_vq(m2m_ctx);
	__poll_t req_events = poll_requested_events(रुको);
	__poll_t rc = 0;

	/*
	 * poll_रुको() MUST be called on the first invocation on all the
	 * potential queues of पूर्णांकerest, even अगर we are not पूर्णांकerested in their
	 * events during this first call. Failure to करो so will result in
	 * queue's events to be ignored because the poll_table won't be capable
	 * of adding new रुको queues thereafter.
	 */
	poll_रुको(file, &src_q->करोne_wq, रुको);
	poll_रुको(file, &dst_q->करोne_wq, रुको);

	अगर (req_events & (EPOLLOUT | EPOLLWRNORM | EPOLLIN | EPOLLRDNORM))
		rc = v4l2_m2m_poll_क्रम_data(file, m2m_ctx, रुको);

	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags)) अणु
		काष्ठा v4l2_fh *fh = file->निजी_data;

		poll_रुको(file, &fh->रुको, रुको);
		अगर (v4l2_event_pending(fh))
			rc |= EPOLLPRI;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_poll);

पूर्णांक v4l2_m2m_mmap(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा vb2_queue *vq;

	अगर (offset < DST_QUEUE_OFF_BASE) अणु
		vq = v4l2_m2m_get_src_vq(m2m_ctx);
	पूर्ण अन्यथा अणु
		vq = v4l2_m2m_get_dst_vq(m2m_ctx);
		vma->vm_pgoff -= (DST_QUEUE_OFF_BASE >> PAGE_SHIFT);
	पूर्ण

	वापस vb2_mmap(vq, vma);
पूर्ण
EXPORT_SYMBOL(v4l2_m2m_mmap);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
व्योम v4l2_m2m_unरेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	media_हटाओ_पूर्णांकf_links(&m2m_dev->पूर्णांकf_devnode->पूर्णांकf);
	media_devnode_हटाओ(m2m_dev->पूर्णांकf_devnode);

	media_entity_हटाओ_links(m2m_dev->source);
	media_entity_हटाओ_links(&m2m_dev->sink);
	media_entity_हटाओ_links(&m2m_dev->proc);
	media_device_unरेजिस्टर_entity(m2m_dev->source);
	media_device_unरेजिस्टर_entity(&m2m_dev->sink);
	media_device_unरेजिस्टर_entity(&m2m_dev->proc);
	kमुक्त(m2m_dev->source->name);
	kमुक्त(m2m_dev->sink.name);
	kमुक्त(m2m_dev->proc.name);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_unरेजिस्टर_media_controller);

अटल पूर्णांक v4l2_m2m_रेजिस्टर_entity(काष्ठा media_device *mdev,
	काष्ठा v4l2_m2m_dev *m2m_dev, क्रमागत v4l2_m2m_entity_type type,
	काष्ठा video_device *vdev, पूर्णांक function)
अणु
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pads;
	अक्षर *name;
	अचिन्हित पूर्णांक len;
	पूर्णांक num_pads;
	पूर्णांक ret;

	चयन (type) अणु
	हाल MEM2MEM_ENT_TYPE_SOURCE:
		entity = m2m_dev->source;
		pads = &m2m_dev->source_pad;
		pads[0].flags = MEDIA_PAD_FL_SOURCE;
		num_pads = 1;
		अवरोध;
	हाल MEM2MEM_ENT_TYPE_SINK:
		entity = &m2m_dev->sink;
		pads = &m2m_dev->sink_pad;
		pads[0].flags = MEDIA_PAD_FL_SINK;
		num_pads = 1;
		अवरोध;
	हाल MEM2MEM_ENT_TYPE_PROC:
		entity = &m2m_dev->proc;
		pads = m2m_dev->proc_pads;
		pads[0].flags = MEDIA_PAD_FL_SINK;
		pads[1].flags = MEDIA_PAD_FL_SOURCE;
		num_pads = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	entity->obj_type = MEDIA_ENTITY_TYPE_BASE;
	अगर (type != MEM2MEM_ENT_TYPE_PROC) अणु
		entity->info.dev.major = VIDEO_MAJOR;
		entity->info.dev.minor = vdev->minor;
	पूर्ण
	len = म_माप(vdev->name) + 2 + म_माप(m2m_entity_name[type]);
	name = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	snम_लिखो(name, len, "%s-%s", vdev->name, m2m_entity_name[type]);
	entity->name = name;
	entity->function = function;

	ret = media_entity_pads_init(entity, num_pads, pads);
	अगर (ret)
		वापस ret;
	ret = media_device_रेजिस्टर_entity(mdev, entity);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक v4l2_m2m_रेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev,
		काष्ठा video_device *vdev, पूर्णांक function)
अणु
	काष्ठा media_device *mdev = vdev->v4l2_dev->mdev;
	काष्ठा media_link *link;
	पूर्णांक ret;

	अगर (!mdev)
		वापस 0;

	/* A memory-to-memory device consists in two
	 * DMA engine and one video processing entities.
	 * The DMA engine entities are linked to a V4L पूर्णांकerface
	 */

	/* Create the three entities with their pads */
	m2m_dev->source = &vdev->entity;
	ret = v4l2_m2m_रेजिस्टर_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_SOURCE, vdev, MEDIA_ENT_F_IO_V4L);
	अगर (ret)
		वापस ret;
	ret = v4l2_m2m_रेजिस्टर_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_PROC, vdev, function);
	अगर (ret)
		जाओ err_rel_entity0;
	ret = v4l2_m2m_रेजिस्टर_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_SINK, vdev, MEDIA_ENT_F_IO_V4L);
	अगर (ret)
		जाओ err_rel_entity1;

	/* Connect the three entities */
	ret = media_create_pad_link(m2m_dev->source, 0, &m2m_dev->proc, 0,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		जाओ err_rel_entity2;

	ret = media_create_pad_link(&m2m_dev->proc, 1, &m2m_dev->sink, 0,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		जाओ err_rm_links0;

	/* Create video पूर्णांकerface */
	m2m_dev->पूर्णांकf_devnode = media_devnode_create(mdev,
			MEDIA_INTF_T_V4L_VIDEO, 0,
			VIDEO_MAJOR, vdev->minor);
	अगर (!m2m_dev->पूर्णांकf_devnode) अणु
		ret = -ENOMEM;
		जाओ err_rm_links1;
	पूर्ण

	/* Connect the two DMA engines to the पूर्णांकerface */
	link = media_create_पूर्णांकf_link(m2m_dev->source,
			&m2m_dev->पूर्णांकf_devnode->पूर्णांकf,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
	अगर (!link) अणु
		ret = -ENOMEM;
		जाओ err_rm_devnode;
	पूर्ण

	link = media_create_पूर्णांकf_link(&m2m_dev->sink,
			&m2m_dev->पूर्णांकf_devnode->पूर्णांकf,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
	अगर (!link) अणु
		ret = -ENOMEM;
		जाओ err_rm_पूर्णांकf_link;
	पूर्ण
	वापस 0;

err_rm_पूर्णांकf_link:
	media_हटाओ_पूर्णांकf_links(&m2m_dev->पूर्णांकf_devnode->पूर्णांकf);
err_rm_devnode:
	media_devnode_हटाओ(m2m_dev->पूर्णांकf_devnode);
err_rm_links1:
	media_entity_हटाओ_links(&m2m_dev->sink);
err_rm_links0:
	media_entity_हटाओ_links(&m2m_dev->proc);
	media_entity_हटाओ_links(m2m_dev->source);
err_rel_entity2:
	media_device_unरेजिस्टर_entity(&m2m_dev->proc);
	kमुक्त(m2m_dev->proc.name);
err_rel_entity1:
	media_device_unरेजिस्टर_entity(&m2m_dev->sink);
	kमुक्त(m2m_dev->sink.name);
err_rel_entity0:
	media_device_unरेजिस्टर_entity(m2m_dev->source);
	kमुक्त(m2m_dev->source->name);
	वापस ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_रेजिस्टर_media_controller);
#पूर्ण_अगर

काष्ठा v4l2_m2m_dev *v4l2_m2m_init(स्थिर काष्ठा v4l2_m2m_ops *m2m_ops)
अणु
	काष्ठा v4l2_m2m_dev *m2m_dev;

	अगर (!m2m_ops || WARN_ON(!m2m_ops->device_run))
		वापस ERR_PTR(-EINVAL);

	m2m_dev = kzalloc(माप *m2m_dev, GFP_KERNEL);
	अगर (!m2m_dev)
		वापस ERR_PTR(-ENOMEM);

	m2m_dev->curr_ctx = शून्य;
	m2m_dev->m2m_ops = m2m_ops;
	INIT_LIST_HEAD(&m2m_dev->job_queue);
	spin_lock_init(&m2m_dev->job_spinlock);
	INIT_WORK(&m2m_dev->job_work, v4l2_m2m_device_run_work);

	वापस m2m_dev;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_init);

व्योम v4l2_m2m_release(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
	kमुक्त(m2m_dev);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_release);

काष्ठा v4l2_m2m_ctx *v4l2_m2m_ctx_init(काष्ठा v4l2_m2m_dev *m2m_dev,
		व्योम *drv_priv,
		पूर्णांक (*queue_init)(व्योम *priv, काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq))
अणु
	काष्ठा v4l2_m2m_ctx *m2m_ctx;
	काष्ठा v4l2_m2m_queue_ctx *out_q_ctx, *cap_q_ctx;
	पूर्णांक ret;

	m2m_ctx = kzalloc(माप *m2m_ctx, GFP_KERNEL);
	अगर (!m2m_ctx)
		वापस ERR_PTR(-ENOMEM);

	m2m_ctx->priv = drv_priv;
	m2m_ctx->m2m_dev = m2m_dev;
	init_रुकोqueue_head(&m2m_ctx->finished);

	out_q_ctx = &m2m_ctx->out_q_ctx;
	cap_q_ctx = &m2m_ctx->cap_q_ctx;

	INIT_LIST_HEAD(&out_q_ctx->rdy_queue);
	INIT_LIST_HEAD(&cap_q_ctx->rdy_queue);
	spin_lock_init(&out_q_ctx->rdy_spinlock);
	spin_lock_init(&cap_q_ctx->rdy_spinlock);

	INIT_LIST_HEAD(&m2m_ctx->queue);

	ret = queue_init(drv_priv, &out_q_ctx->q, &cap_q_ctx->q);

	अगर (ret)
		जाओ err;
	/*
	 * Both queues should use same the mutex to lock the m2m context.
	 * This lock is used in some v4l2_m2m_* helpers.
	 */
	अगर (WARN_ON(out_q_ctx->q.lock != cap_q_ctx->q.lock)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	m2m_ctx->q_lock = out_q_ctx->q.lock;

	वापस m2m_ctx;
err:
	kमुक्त(m2m_ctx);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ctx_init);

व्योम v4l2_m2m_ctx_release(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	/* रुको until the current context is dequeued from job_queue */
	v4l2_m2m_cancel_job(m2m_ctx);

	vb2_queue_release(&m2m_ctx->cap_q_ctx.q);
	vb2_queue_release(&m2m_ctx->out_q_ctx.q);

	kमुक्त(m2m_ctx);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ctx_release);

व्योम v4l2_m2m_buf_queue(काष्ठा v4l2_m2m_ctx *m2m_ctx,
		काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा v4l2_m2m_buffer *b = container_of(vbuf,
				काष्ठा v4l2_m2m_buffer, vb);
	काष्ठा v4l2_m2m_queue_ctx *q_ctx;
	अचिन्हित दीर्घ flags;

	q_ctx = get_queue_ctx(m2m_ctx, vbuf->vb2_buf.vb2_queue->type);
	अगर (!q_ctx)
		वापस;

	spin_lock_irqsave(&q_ctx->rdy_spinlock, flags);
	list_add_tail(&b->list, &q_ctx->rdy_queue);
	q_ctx->num_rdy++;
	spin_unlock_irqrestore(&q_ctx->rdy_spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_buf_queue);

व्योम v4l2_m2m_buf_copy_metadata(स्थिर काष्ठा vb2_v4l2_buffer *out_vb,
				काष्ठा vb2_v4l2_buffer *cap_vb,
				bool copy_frame_flags)
अणु
	u32 mask = V4L2_BUF_FLAG_TIMECODE | V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	अगर (copy_frame_flags)
		mask |= V4L2_BUF_FLAG_KEYFRAME | V4L2_BUF_FLAG_PFRAME |
			V4L2_BUF_FLAG_BFRAME;

	cap_vb->vb2_buf.बारtamp = out_vb->vb2_buf.बारtamp;

	अगर (out_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		cap_vb->समयcode = out_vb->समयcode;
	cap_vb->field = out_vb->field;
	cap_vb->flags &= ~mask;
	cap_vb->flags |= out_vb->flags & mask;
	cap_vb->vb2_buf.copied_बारtamp = 1;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_buf_copy_metadata);

व्योम v4l2_m2m_request_queue(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj, *obj_safe;
	काष्ठा v4l2_m2m_ctx *m2m_ctx = शून्य;

	/*
	 * Queue all objects. Note that buffer objects are at the end of the
	 * objects list, after all other object types. Once buffer objects
	 * are queued, the driver might delete them immediately (अगर the driver
	 * processes the buffer at once), so we have to use
	 * list_क्रम_each_entry_safe() to handle the हाल where the object we
	 * queue is deleted.
	 */
	list_क्रम_each_entry_safe(obj, obj_safe, &req->objects, list) अणु
		काष्ठा v4l2_m2m_ctx *m2m_ctx_obj;
		काष्ठा vb2_buffer *vb;

		अगर (!obj->ops->queue)
			जारी;

		अगर (vb2_request_object_is_buffer(obj)) अणु
			/* Sanity checks */
			vb = container_of(obj, काष्ठा vb2_buffer, req_obj);
			WARN_ON(!V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type));
			m2m_ctx_obj = container_of(vb->vb2_queue,
						   काष्ठा v4l2_m2m_ctx,
						   out_q_ctx.q);
			WARN_ON(m2m_ctx && m2m_ctx_obj != m2m_ctx);
			m2m_ctx = m2m_ctx_obj;
		पूर्ण

		/*
		 * The buffer we queue here can in theory be immediately
		 * unbound, hence the use of list_क्रम_each_entry_safe()
		 * above and why we call the queue op last.
		 */
		obj->ops->queue(obj);
	पूर्ण

	WARN_ON(!m2m_ctx);

	अगर (m2m_ctx)
		v4l2_m2m_try_schedule(m2m_ctx);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_request_queue);

/* Videobuf2 ioctl helpers */

पूर्णांक v4l2_m2m_ioctl_reqbufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_reqbufs(file, fh->m2m_ctx, rb);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_reqbufs);

पूर्णांक v4l2_m2m_ioctl_create_bufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_create_buffers *create)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_create_bufs(file, fh->m2m_ctx, create);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_create_bufs);

पूर्णांक v4l2_m2m_ioctl_querybuf(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_querybuf(file, fh->m2m_ctx, buf);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_querybuf);

पूर्णांक v4l2_m2m_ioctl_qbuf(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_qbuf(file, fh->m2m_ctx, buf);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_qbuf);

पूर्णांक v4l2_m2m_ioctl_dqbuf(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_dqbuf(file, fh->m2m_ctx, buf);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_dqbuf);

पूर्णांक v4l2_m2m_ioctl_prepare_buf(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_prepare_buf(file, fh->m2m_ctx, buf);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_prepare_buf);

पूर्णांक v4l2_m2m_ioctl_expbuf(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_exportbuffer *eb)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_expbuf(file, fh->m2m_ctx, eb);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_expbuf);

पूर्णांक v4l2_m2m_ioctl_streamon(काष्ठा file *file, व्योम *priv,
				क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_streamon(file, fh->m2m_ctx, type);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_streamon);

पूर्णांक v4l2_m2m_ioctl_streamoff(काष्ठा file *file, व्योम *priv,
				क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_streamoff(file, fh->m2m_ctx, type);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_streamoff);

पूर्णांक v4l2_m2m_ioctl_try_encoder_cmd(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_encoder_cmd *ec)
अणु
	अगर (ec->cmd != V4L2_ENC_CMD_STOP && ec->cmd != V4L2_ENC_CMD_START)
		वापस -EINVAL;

	ec->flags = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_try_encoder_cmd);

पूर्णांक v4l2_m2m_ioctl_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_decoder_cmd *dc)
अणु
	अगर (dc->cmd != V4L2_DEC_CMD_STOP && dc->cmd != V4L2_DEC_CMD_START)
		वापस -EINVAL;

	dc->flags = 0;

	अगर (dc->cmd == V4L2_DEC_CMD_STOP) अणु
		dc->stop.pts = 0;
	पूर्ण अन्यथा अगर (dc->cmd == V4L2_DEC_CMD_START) अणु
		dc->start.speed = 0;
		dc->start.क्रमmat = V4L2_DEC_START_FMT_NONE;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_try_decoder_cmd);

/*
 * Updates the encoding state on ENC_CMD_STOP/ENC_CMD_START
 * Should be called from the encoder driver encoder_cmd() callback
 */
पूर्णांक v4l2_m2m_encoder_cmd(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_encoder_cmd *ec)
अणु
	अगर (ec->cmd != V4L2_ENC_CMD_STOP && ec->cmd != V4L2_ENC_CMD_START)
		वापस -EINVAL;

	अगर (ec->cmd == V4L2_ENC_CMD_STOP)
		वापस v4l2_update_last_buf_state(m2m_ctx);

	अगर (m2m_ctx->is_draining)
		वापस -EBUSY;

	अगर (m2m_ctx->has_stopped)
		m2m_ctx->has_stopped = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_encoder_cmd);

/*
 * Updates the decoding state on DEC_CMD_STOP/DEC_CMD_START
 * Should be called from the decoder driver decoder_cmd() callback
 */
पूर्णांक v4l2_m2m_decoder_cmd(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_decoder_cmd *dc)
अणु
	अगर (dc->cmd != V4L2_DEC_CMD_STOP && dc->cmd != V4L2_DEC_CMD_START)
		वापस -EINVAL;

	अगर (dc->cmd == V4L2_DEC_CMD_STOP)
		वापस v4l2_update_last_buf_state(m2m_ctx);

	अगर (m2m_ctx->is_draining)
		वापस -EBUSY;

	अगर (m2m_ctx->has_stopped)
		m2m_ctx->has_stopped = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_decoder_cmd);

पूर्णांक v4l2_m2m_ioctl_encoder_cmd(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_encoder_cmd *ec)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_encoder_cmd(file, fh->m2m_ctx, ec);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_encoder_cmd);

पूर्णांक v4l2_m2m_ioctl_decoder_cmd(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_decoder_cmd *dc)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_decoder_cmd(file, fh->m2m_ctx, dc);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_decoder_cmd);

पूर्णांक v4l2_m2m_ioctl_stateless_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_decoder_cmd *dc)
अणु
	अगर (dc->cmd != V4L2_DEC_CMD_FLUSH)
		वापस -EINVAL;

	dc->flags = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_stateless_try_decoder_cmd);

पूर्णांक v4l2_m2m_ioctl_stateless_decoder_cmd(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_decoder_cmd *dc)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा vb2_v4l2_buffer *out_vb, *cap_vb;
	काष्ठा v4l2_m2m_dev *m2m_dev = fh->m2m_ctx->m2m_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = v4l2_m2m_ioctl_stateless_try_decoder_cmd(file, priv, dc);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&m2m_dev->job_spinlock, flags);
	out_vb = v4l2_m2m_last_src_buf(fh->m2m_ctx);
	cap_vb = v4l2_m2m_last_dst_buf(fh->m2m_ctx);

	/*
	 * If there is an out buffer pending, then clear any HOLD flag.
	 *
	 * By clearing this flag we ensure that when this output
	 * buffer is processed any held capture buffer will be released.
	 */
	अगर (out_vb) अणु
		out_vb->flags &= ~V4L2_BUF_FLAG_M2M_HOLD_CAPTURE_BUF;
	पूर्ण अन्यथा अगर (cap_vb && cap_vb->is_held) अणु
		/*
		 * If there were no output buffers, but there is a
		 * capture buffer that is held, then release that
		 * buffer.
		 */
		cap_vb->is_held = false;
		v4l2_m2m_dst_buf_हटाओ(fh->m2m_ctx);
		v4l2_m2m_buf_करोne(cap_vb, VB2_BUF_STATE_DONE);
	पूर्ण
	spin_unlock_irqrestore(&m2m_dev->job_spinlock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_ioctl_stateless_decoder_cmd);

/*
 * v4l2_file_operations helpers. It is assumed here same lock is used
 * क्रम the output and the capture buffer queue.
 */

पूर्णांक v4l2_m2m_fop_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	वापस v4l2_m2m_mmap(file, fh->m2m_ctx, vma);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_fop_mmap);

__poll_t v4l2_m2m_fop_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा v4l2_m2m_ctx *m2m_ctx = fh->m2m_ctx;
	__poll_t ret;

	अगर (m2m_ctx->q_lock)
		mutex_lock(m2m_ctx->q_lock);

	ret = v4l2_m2m_poll(file, m2m_ctx, रुको);

	अगर (m2m_ctx->q_lock)
		mutex_unlock(m2m_ctx->q_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_m2m_fop_poll);

