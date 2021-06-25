<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Memory-to-memory device framework क्रम Video क्रम Linux 2.
 *
 * Helper functions क्रम devices that use memory buffers क्रम both source
 * and destination.
 *
 * Copyright (c) 2009 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */

#अगर_अघोषित _MEDIA_V4L2_MEM2MEM_H
#घोषणा _MEDIA_V4L2_MEM2MEM_H

#समावेश <media/videobuf2-v4l2.h>

/**
 * काष्ठा v4l2_m2m_ops - mem-to-mem device driver callbacks
 * @device_run:	required. Begin the actual job (transaction) inside this
 *		callback.
 *		The job करोes NOT have to end beक्रमe this callback वापसs
 *		(and it will be the usual हाल). When the job finishes,
 *		v4l2_m2m_job_finish() or v4l2_m2m_buf_करोne_and_job_finish()
 *		has to be called.
 * @job_पढ़ोy:	optional. Should वापस 0 अगर the driver करोes not have a job
 *		fully prepared to run yet (i.e. it will not be able to finish a
 *		transaction without sleeping). If not provided, it will be
 *		assumed that one source and one destination buffer are all
 *		that is required क्रम the driver to perक्रमm one full transaction.
 *		This method may not sleep.
 * @job_पात:	optional. Inक्रमms the driver that it has to पात the currently
 *		running transaction as soon as possible (i.e. as soon as it can
 *		stop the device safely; e.g. in the next पूर्णांकerrupt handler),
 *		even अगर the transaction would not have been finished by then.
 *		After the driver perक्रमms the necessary steps, it has to call
 *		v4l2_m2m_job_finish() or v4l2_m2m_buf_करोne_and_job_finish() as
 *		अगर the transaction ended normally.
 *		This function करोes not have to (and will usually not) रुको
 *		until the device enters a state when it can be stopped.
 */
काष्ठा v4l2_m2m_ops अणु
	व्योम (*device_run)(व्योम *priv);
	पूर्णांक (*job_पढ़ोy)(व्योम *priv);
	व्योम (*job_पात)(व्योम *priv);
पूर्ण;

काष्ठा video_device;
काष्ठा v4l2_m2m_dev;

/**
 * काष्ठा v4l2_m2m_queue_ctx - represents a queue क्रम buffers पढ़ोy to be
 *	processed
 *
 * @q:		poपूर्णांकer to काष्ठा &vb2_queue
 * @rdy_queue:	List of V4L2 mem-to-mem queues
 * @rdy_spinlock: spin lock to protect the काष्ठा usage
 * @num_rdy:	number of buffers पढ़ोy to be processed
 * @buffered:	is the queue buffered?
 *
 * Queue क्रम buffers पढ़ोy to be processed as soon as this
 * instance receives access to the device.
 */

काष्ठा v4l2_m2m_queue_ctx अणु
	काष्ठा vb2_queue	q;

	काष्ठा list_head	rdy_queue;
	spinlock_t		rdy_spinlock;
	u8			num_rdy;
	bool			buffered;
पूर्ण;

/**
 * काष्ठा v4l2_m2m_ctx - Memory to memory context काष्ठाure
 *
 * @q_lock: काष्ठा &mutex lock
 * @new_frame: valid in the device_run callback: अगर true, then this
 *		starts a new frame; अगर false, then this is a new slice
 *		क्रम an existing frame. This is always true unless
 *		V4L2_BUF_CAP_SUPPORTS_M2M_HOLD_CAPTURE_BUF is set, which
 *		indicates slicing support.
 * @is_draining: indicates device is in draining phase
 * @last_src_buf: indicate the last source buffer क्रम draining
 * @next_buf_last: next capture queud buffer will be tagged as last
 * @has_stopped: indicate the device has been stopped
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 * @cap_q_ctx: Capture (output to memory) queue context
 * @out_q_ctx: Output (input from memory) queue context
 * @queue: List of memory to memory contexts
 * @job_flags: Job queue flags, used पूर्णांकernally by v4l2-mem2mem.c:
 *		%TRANS_QUEUED, %TRANS_RUNNING and %TRANS_ABORT.
 * @finished: Wait queue used to संकेतize when a job queue finished.
 * @priv: Instance निजी data
 *
 * The memory to memory context is specअगरic to a file handle, NOT to e.g.
 * a device.
 */
काष्ठा v4l2_m2m_ctx अणु
	/* optional cap/out vb2 queues lock */
	काष्ठा mutex			*q_lock;

	bool				new_frame;

	bool				is_draining;
	काष्ठा vb2_v4l2_buffer		*last_src_buf;
	bool				next_buf_last;
	bool				has_stopped;

	/* पूर्णांकernal use only */
	काष्ठा v4l2_m2m_dev		*m2m_dev;

	काष्ठा v4l2_m2m_queue_ctx	cap_q_ctx;

	काष्ठा v4l2_m2m_queue_ctx	out_q_ctx;

	/* For device job queue */
	काष्ठा list_head		queue;
	अचिन्हित दीर्घ			job_flags;
	रुको_queue_head_t		finished;

	व्योम				*priv;
पूर्ण;

/**
 * काष्ठा v4l2_m2m_buffer - Memory to memory buffer
 *
 * @vb: poपूर्णांकer to काष्ठा &vb2_v4l2_buffer
 * @list: list of m2m buffers
 */
काष्ठा v4l2_m2m_buffer अणु
	काष्ठा vb2_v4l2_buffer	vb;
	काष्ठा list_head	list;
पूर्ण;

/**
 * v4l2_m2m_get_curr_priv() - वापस driver निजी data क्रम the currently
 * running instance or शून्य अगर no instance is running
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 */
व्योम *v4l2_m2m_get_curr_priv(काष्ठा v4l2_m2m_dev *m2m_dev);

/**
 * v4l2_m2m_get_vq() - वापस vb2_queue क्रम the given type
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @type: type of the V4L2 buffer, as defined by क्रमागत &v4l2_buf_type
 */
काष्ठा vb2_queue *v4l2_m2m_get_vq(काष्ठा v4l2_m2m_ctx *m2m_ctx,
				       क्रमागत v4l2_buf_type type);

/**
 * v4l2_m2m_try_schedule() - check whether an instance is पढ़ोy to be added to
 * the pending job queue and add it अगर so.
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 *
 * There are three basic requirements an instance has to meet to be able to run:
 * 1) at least one source buffer has to be queued,
 * 2) at least one destination buffer has to be queued,
 * 3) streaming has to be on.
 *
 * If a queue is buffered (क्रम example a decoder hardware ringbuffer that has
 * to be drained beक्रमe करोing streamoff), allow scheduling without v4l2 buffers
 * on that queue.
 *
 * There may also be additional, custom requirements. In such हाल the driver
 * should supply a custom callback (job_पढ़ोy in v4l2_m2m_ops) that should
 * वापस 1 अगर the instance is पढ़ोy.
 * An example of the above could be an instance that requires more than one
 * src/dst buffer per transaction.
 */
व्योम v4l2_m2m_try_schedule(काष्ठा v4l2_m2m_ctx *m2m_ctx);

/**
 * v4l2_m2m_job_finish() - inक्रमm the framework that a job has been finished
 * and have it clean up
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 *
 * Called by a driver to yield back the device after it has finished with it.
 * Should be called as soon as possible after reaching a state which allows
 * other instances to take control of the device.
 *
 * This function has to be called only after &v4l2_m2m_ops->device_run
 * callback has been called on the driver. To prevent recursion, it should
 * not be called directly from the &v4l2_m2m_ops->device_run callback though.
 */
व्योम v4l2_m2m_job_finish(काष्ठा v4l2_m2m_dev *m2m_dev,
			 काष्ठा v4l2_m2m_ctx *m2m_ctx);

/**
 * v4l2_m2m_buf_करोne_and_job_finish() - वापस source/destination buffers with
 * state and inक्रमm the framework that a job has been finished and have it
 * clean up
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @state: vb2 buffer state passed to v4l2_m2m_buf_करोne().
 *
 * Drivers that set V4L2_BUF_CAP_SUPPORTS_M2M_HOLD_CAPTURE_BUF must use this
 * function instead of job_finish() to take held buffers पूर्णांकo account. It is
 * optional क्रम other drivers.
 *
 * This function हटाओs the source buffer from the पढ़ोy list and वापसs
 * it with the given state. The same is करोne क्रम the destination buffer, unless
 * it is marked 'held'. In that हाल the buffer is kept on the पढ़ोy list.
 *
 * After that the job is finished (see job_finish()).
 *
 * This allows क्रम multiple output buffers to be used to fill in a single
 * capture buffer. This is typically used by stateless decoders where
 * multiple e.g. H.264 slices contribute to a single decoded frame.
 */
व्योम v4l2_m2m_buf_करोne_and_job_finish(काष्ठा v4l2_m2m_dev *m2m_dev,
				      काष्ठा v4l2_m2m_ctx *m2m_ctx,
				      क्रमागत vb2_buffer_state state);

अटल अंतरभूत व्योम
v4l2_m2m_buf_करोne(काष्ठा vb2_v4l2_buffer *buf, क्रमागत vb2_buffer_state state)
अणु
	vb2_buffer_करोne(&buf->vb2_buf, state);
पूर्ण

/**
 * v4l2_m2m_clear_state() - clear encoding/decoding state
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत व्योम
v4l2_m2m_clear_state(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	m2m_ctx->next_buf_last = false;
	m2m_ctx->is_draining = false;
	m2m_ctx->has_stopped = false;
पूर्ण

/**
 * v4l2_m2m_mark_stopped() - set current encoding/decoding state as stopped
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत व्योम
v4l2_m2m_mark_stopped(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	m2m_ctx->next_buf_last = false;
	m2m_ctx->is_draining = false;
	m2m_ctx->has_stopped = true;
पूर्ण

/**
 * v4l2_m2m_dst_buf_is_last() - वापस the current encoding/decoding session
 * draining management state of next queued capture buffer
 *
 * This last capture buffer should be tagged with V4L2_BUF_FLAG_LAST to notअगरy
 * the end of the capture session.
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत bool
v4l2_m2m_dst_buf_is_last(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस m2m_ctx->is_draining && m2m_ctx->next_buf_last;
पूर्ण

/**
 * v4l2_m2m_has_stopped() - वापस the current encoding/decoding session
 * stopped state
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत bool
v4l2_m2m_has_stopped(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस m2m_ctx->has_stopped;
पूर्ण

/**
 * v4l2_m2m_is_last_draining_src_buf() - वापस the output buffer draining
 * state in the current encoding/decoding session
 *
 * This will identअगरy the last output buffer queued beक्रमe a session stop
 * was required, leading to an actual encoding/decoding session stop state
 * in the encoding/decoding process after being processed.
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vbuf: poपूर्णांकer to काष्ठा &v4l2_buffer
 */
अटल अंतरभूत bool
v4l2_m2m_is_last_draining_src_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx,
				  काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	वापस m2m_ctx->is_draining && vbuf == m2m_ctx->last_src_buf;
पूर्ण

/**
 * v4l2_m2m_last_buffer_करोne() - marks the buffer with LAST flag and DONE
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vbuf: poपूर्णांकer to काष्ठा &v4l2_buffer
 */
व्योम v4l2_m2m_last_buffer_करोne(काष्ठा v4l2_m2m_ctx *m2m_ctx,
			       काष्ठा vb2_v4l2_buffer *vbuf);

/**
 * v4l2_m2m_suspend() - stop new jobs from being run and रुको क्रम current job
 * to finish
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 *
 * Called by a driver in the suspend hook. Stop new jobs from being run, and
 * रुको क्रम current running job to finish.
 */
व्योम v4l2_m2m_suspend(काष्ठा v4l2_m2m_dev *m2m_dev);

/**
 * v4l2_m2m_resume() - resume job running and try to run a queued job
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 *
 * Called by a driver in the resume hook. This reverts the operation of
 * v4l2_m2m_suspend() and allows job to be run. Also try to run a queued job अगर
 * there is any.
 */
व्योम v4l2_m2m_resume(काष्ठा v4l2_m2m_dev *m2m_dev);

/**
 * v4l2_m2m_reqbufs() - multi-queue-aware REQBUFS multiplexer
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @reqbufs: poपूर्णांकer to काष्ठा &v4l2_requestbuffers
 */
पूर्णांक v4l2_m2m_reqbufs(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		     काष्ठा v4l2_requestbuffers *reqbufs);

/**
 * v4l2_m2m_querybuf() - multi-queue-aware QUERYBUF multiplexer
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @buf: poपूर्णांकer to काष्ठा &v4l2_buffer
 *
 * See v4l2_m2m_mmap() करोcumentation क्रम details.
 */
पूर्णांक v4l2_m2m_querybuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		      काष्ठा v4l2_buffer *buf);

/**
 * v4l2_m2m_qbuf() - enqueue a source or destination buffer, depending on
 * the type
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @buf: poपूर्णांकer to काष्ठा &v4l2_buffer
 */
पूर्णांक v4l2_m2m_qbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		  काष्ठा v4l2_buffer *buf);

/**
 * v4l2_m2m_dqbuf() - dequeue a source or destination buffer, depending on
 * the type
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @buf: poपूर्णांकer to काष्ठा &v4l2_buffer
 */
पूर्णांक v4l2_m2m_dqbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		   काष्ठा v4l2_buffer *buf);

/**
 * v4l2_m2m_prepare_buf() - prepare a source or destination buffer, depending on
 * the type
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @buf: poपूर्णांकer to काष्ठा &v4l2_buffer
 */
पूर्णांक v4l2_m2m_prepare_buf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_buffer *buf);

/**
 * v4l2_m2m_create_bufs() - create a source or destination buffer, depending
 * on the type
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @create: poपूर्णांकer to काष्ठा &v4l2_create_buffers
 */
पूर्णांक v4l2_m2m_create_bufs(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_create_buffers *create);

/**
 * v4l2_m2m_expbuf() - export a source or destination buffer, depending on
 * the type
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @eb: poपूर्णांकer to काष्ठा &v4l2_exportbuffer
 */
पूर्णांक v4l2_m2m_expbuf(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		   काष्ठा v4l2_exportbuffer *eb);

/**
 * v4l2_m2m_streamon() - turn on streaming क्रम a video queue
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @type: type of the V4L2 buffer, as defined by क्रमागत &v4l2_buf_type
 */
पूर्णांक v4l2_m2m_streamon(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		      क्रमागत v4l2_buf_type type);

/**
 * v4l2_m2m_streamoff() - turn off streaming क्रम a video queue
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @type: type of the V4L2 buffer, as defined by क्रमागत &v4l2_buf_type
 */
पूर्णांक v4l2_m2m_streamoff(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		       क्रमागत v4l2_buf_type type);

/**
 * v4l2_m2m_update_start_streaming_state() - update the encoding/decoding
 * session state when a start of streaming of a video queue is requested
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @q: queue
 */
व्योम v4l2_m2m_update_start_streaming_state(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					   काष्ठा vb2_queue *q);

/**
 * v4l2_m2m_update_stop_streaming_state() -  update the encoding/decoding
 * session state when a stop of streaming of a video queue is requested
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @q: queue
 */
व्योम v4l2_m2m_update_stop_streaming_state(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					  काष्ठा vb2_queue *q);

/**
 * v4l2_m2m_encoder_cmd() - execute an encoder command
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @ec: poपूर्णांकer to the encoder command
 */
पूर्णांक v4l2_m2m_encoder_cmd(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_encoder_cmd *ec);

/**
 * v4l2_m2m_decoder_cmd() - execute a decoder command
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @dc: poपूर्णांकer to the decoder command
 */
पूर्णांक v4l2_m2m_decoder_cmd(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			 काष्ठा v4l2_decoder_cmd *dc);

/**
 * v4l2_m2m_poll() - poll replacement, क्रम destination buffers only
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @रुको: poपूर्णांकer to काष्ठा &poll_table_काष्ठा
 *
 * Call from the driver's poll() function. Will poll both queues. If a buffer
 * is available to dequeue (with dqbuf) from the source queue, this will
 * indicate that a non-blocking ग_लिखो can be perक्रमmed, जबतक पढ़ो will be
 * वापसed in हाल of the destination queue.
 */
__poll_t v4l2_m2m_poll(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
			   काष्ठा poll_table_काष्ठा *रुको);

/**
 * v4l2_m2m_mmap() - source and destination queues-aware mmap multiplexer
 *
 * @file: poपूर्णांकer to काष्ठा &file
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vma: poपूर्णांकer to काष्ठा &vm_area_काष्ठा
 *
 * Call from driver's mmap() function. Will handle mmap() क्रम both queues
 * seamlessly क्रम videobuffer, which will receive normal per-queue offsets and
 * proper videobuf queue poपूर्णांकers. The dअगरferentiation is made outside videobuf
 * by adding a predefined offset to buffers from one of the queues and
 * subtracting it beक्रमe passing it back to videobuf. Only drivers (and
 * thus applications) receive modअगरied offsets.
 */
पूर्णांक v4l2_m2m_mmap(काष्ठा file *file, काष्ठा v4l2_m2m_ctx *m2m_ctx,
		  काष्ठा vm_area_काष्ठा *vma);

/**
 * v4l2_m2m_init() - initialize per-driver m2m data
 *
 * @m2m_ops: poपूर्णांकer to काष्ठा v4l2_m2m_ops
 *
 * Usually called from driver's ``probe()`` function.
 *
 * Return: वापसs an opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 */
काष्ठा v4l2_m2m_dev *v4l2_m2m_init(स्थिर काष्ठा v4l2_m2m_ops *m2m_ops);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
व्योम v4l2_m2m_unरेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev);
पूर्णांक v4l2_m2m_रेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev,
			काष्ठा video_device *vdev, पूर्णांक function);
#अन्यथा
अटल अंतरभूत व्योम
v4l2_m2m_unरेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
v4l2_m2m_रेजिस्टर_media_controller(काष्ठा v4l2_m2m_dev *m2m_dev,
		काष्ठा video_device *vdev, पूर्णांक function)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * v4l2_m2m_release() - cleans up and मुक्तs a m2m_dev काष्ठाure
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 *
 * Usually called from driver's ``हटाओ()`` function.
 */
व्योम v4l2_m2m_release(काष्ठा v4l2_m2m_dev *m2m_dev);

/**
 * v4l2_m2m_ctx_init() - allocate and initialize a m2m context
 *
 * @m2m_dev: opaque poपूर्णांकer to the पूर्णांकernal data to handle M2M context
 * @drv_priv: driver's instance निजी data
 * @queue_init: a callback क्रम queue type-specअगरic initialization function
 *	to be used क्रम initializing videobuf_queues
 *
 * Usually called from driver's ``खोलो()`` function.
 */
काष्ठा v4l2_m2m_ctx *v4l2_m2m_ctx_init(काष्ठा v4l2_m2m_dev *m2m_dev,
		व्योम *drv_priv,
		पूर्णांक (*queue_init)(व्योम *priv, काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq));

अटल अंतरभूत व्योम v4l2_m2m_set_src_buffered(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					     bool buffered)
अणु
	m2m_ctx->out_q_ctx.buffered = buffered;
पूर्ण

अटल अंतरभूत व्योम v4l2_m2m_set_dst_buffered(काष्ठा v4l2_m2m_ctx *m2m_ctx,
					     bool buffered)
अणु
	m2m_ctx->cap_q_ctx.buffered = buffered;
पूर्ण

/**
 * v4l2_m2m_ctx_release() - release m2m context
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 *
 * Usually called from driver's release() function.
 */
व्योम v4l2_m2m_ctx_release(काष्ठा v4l2_m2m_ctx *m2m_ctx);

/**
 * v4l2_m2m_buf_queue() - add a buffer to the proper पढ़ोy buffers list.
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vbuf: poपूर्णांकer to काष्ठा &vb2_v4l2_buffer
 *
 * Call from videobuf_queue_ops->ops->buf_queue, videobuf_queue_ops callback.
 */
व्योम v4l2_m2m_buf_queue(काष्ठा v4l2_m2m_ctx *m2m_ctx,
			काष्ठा vb2_v4l2_buffer *vbuf);

/**
 * v4l2_m2m_num_src_bufs_पढ़ोy() - वापस the number of source buffers पढ़ोy क्रम
 * use
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत
अचिन्हित पूर्णांक v4l2_m2m_num_src_bufs_पढ़ोy(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस m2m_ctx->out_q_ctx.num_rdy;
पूर्ण

/**
 * v4l2_m2m_num_dst_bufs_पढ़ोy() - वापस the number of destination buffers
 * पढ़ोy क्रम use
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत
अचिन्हित पूर्णांक v4l2_m2m_num_dst_bufs_पढ़ोy(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस m2m_ctx->cap_q_ctx.num_rdy;
पूर्ण

/**
 * v4l2_m2m_next_buf() - वापस next buffer from the list of पढ़ोy buffers
 *
 * @q_ctx: poपूर्णांकer to काष्ठा @v4l2_m2m_queue_ctx
 */
काष्ठा vb2_v4l2_buffer *v4l2_m2m_next_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx);

/**
 * v4l2_m2m_next_src_buf() - वापस next source buffer from the list of पढ़ोy
 * buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_next_src_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_next_buf(&m2m_ctx->out_q_ctx);
पूर्ण

/**
 * v4l2_m2m_next_dst_buf() - वापस next destination buffer from the list of
 * पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_next_dst_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_next_buf(&m2m_ctx->cap_q_ctx);
पूर्ण

/**
 * v4l2_m2m_last_buf() - वापस last buffer from the list of पढ़ोy buffers
 *
 * @q_ctx: poपूर्णांकer to काष्ठा @v4l2_m2m_queue_ctx
 */
काष्ठा vb2_v4l2_buffer *v4l2_m2m_last_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx);

/**
 * v4l2_m2m_last_src_buf() - वापस last destination buffer from the list of
 * पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_last_src_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_last_buf(&m2m_ctx->out_q_ctx);
पूर्ण

/**
 * v4l2_m2m_last_dst_buf() - वापस last destination buffer from the list of
 * पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_last_dst_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_last_buf(&m2m_ctx->cap_q_ctx);
पूर्ण

/**
 * v4l2_m2m_क्रम_each_dst_buf() - iterate over a list of destination पढ़ोy
 * buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @b: current buffer of type काष्ठा v4l2_m2m_buffer
 */
#घोषणा v4l2_m2m_क्रम_each_dst_buf(m2m_ctx, b)	\
	list_क्रम_each_entry(b, &m2m_ctx->cap_q_ctx.rdy_queue, list)

/**
 * v4l2_m2m_क्रम_each_src_buf() - iterate over a list of source पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @b: current buffer of type काष्ठा v4l2_m2m_buffer
 */
#घोषणा v4l2_m2m_क्रम_each_src_buf(m2m_ctx, b)	\
	list_क्रम_each_entry(b, &m2m_ctx->out_q_ctx.rdy_queue, list)

/**
 * v4l2_m2m_क्रम_each_dst_buf_safe() - iterate over a list of destination पढ़ोy
 * buffers safely
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @b: current buffer of type काष्ठा v4l2_m2m_buffer
 * @n: used as temporary storage
 */
#घोषणा v4l2_m2m_क्रम_each_dst_buf_safe(m2m_ctx, b, n)	\
	list_क्रम_each_entry_safe(b, n, &m2m_ctx->cap_q_ctx.rdy_queue, list)

/**
 * v4l2_m2m_क्रम_each_src_buf_safe() - iterate over a list of source पढ़ोy
 * buffers safely
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @b: current buffer of type काष्ठा v4l2_m2m_buffer
 * @n: used as temporary storage
 */
#घोषणा v4l2_m2m_क्रम_each_src_buf_safe(m2m_ctx, b, n)	\
	list_क्रम_each_entry_safe(b, n, &m2m_ctx->out_q_ctx.rdy_queue, list)

/**
 * v4l2_m2m_get_src_vq() - वापस vb2_queue क्रम source buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत
काष्ठा vb2_queue *v4l2_m2m_get_src_vq(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस &m2m_ctx->out_q_ctx.q;
पूर्ण

/**
 * v4l2_m2m_get_dst_vq() - वापस vb2_queue क्रम destination buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत
काष्ठा vb2_queue *v4l2_m2m_get_dst_vq(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस &m2m_ctx->cap_q_ctx.q;
पूर्ण

/**
 * v4l2_m2m_buf_हटाओ() - take off a buffer from the list of पढ़ोy buffers and
 * वापस it
 *
 * @q_ctx: poपूर्णांकer to काष्ठा @v4l2_m2m_queue_ctx
 */
काष्ठा vb2_v4l2_buffer *v4l2_m2m_buf_हटाओ(काष्ठा v4l2_m2m_queue_ctx *q_ctx);

/**
 * v4l2_m2m_src_buf_हटाओ() - take off a source buffer from the list of पढ़ोy
 * buffers and वापस it
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_src_buf_हटाओ(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_buf_हटाओ(&m2m_ctx->out_q_ctx);
पूर्ण

/**
 * v4l2_m2m_dst_buf_हटाओ() - take off a destination buffer from the list of
 * पढ़ोy buffers and वापस it
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 */
अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_dst_buf_हटाओ(काष्ठा v4l2_m2m_ctx *m2m_ctx)
अणु
	वापस v4l2_m2m_buf_हटाओ(&m2m_ctx->cap_q_ctx);
पूर्ण

/**
 * v4l2_m2m_buf_हटाओ_by_buf() - take off exact buffer from the list of पढ़ोy
 * buffers
 *
 * @q_ctx: poपूर्णांकer to काष्ठा @v4l2_m2m_queue_ctx
 * @vbuf: the buffer to be हटाओd
 */
व्योम v4l2_m2m_buf_हटाओ_by_buf(काष्ठा v4l2_m2m_queue_ctx *q_ctx,
				काष्ठा vb2_v4l2_buffer *vbuf);

/**
 * v4l2_m2m_src_buf_हटाओ_by_buf() - take off exact source buffer from the list
 * of पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vbuf: the buffer to be हटाओd
 */
अटल अंतरभूत व्योम v4l2_m2m_src_buf_हटाओ_by_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx,
						  काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	v4l2_m2m_buf_हटाओ_by_buf(&m2m_ctx->out_q_ctx, vbuf);
पूर्ण

/**
 * v4l2_m2m_dst_buf_हटाओ_by_buf() - take off exact destination buffer from the
 * list of पढ़ोy buffers
 *
 * @m2m_ctx: m2m context asचिन्हित to the instance given by काष्ठा &v4l2_m2m_ctx
 * @vbuf: the buffer to be हटाओd
 */
अटल अंतरभूत व्योम v4l2_m2m_dst_buf_हटाओ_by_buf(काष्ठा v4l2_m2m_ctx *m2m_ctx,
						  काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	v4l2_m2m_buf_हटाओ_by_buf(&m2m_ctx->cap_q_ctx, vbuf);
पूर्ण

काष्ठा vb2_v4l2_buffer *
v4l2_m2m_buf_हटाओ_by_idx(काष्ठा v4l2_m2m_queue_ctx *q_ctx, अचिन्हित पूर्णांक idx);

अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_src_buf_हटाओ_by_idx(काष्ठा v4l2_m2m_ctx *m2m_ctx, अचिन्हित पूर्णांक idx)
अणु
	वापस v4l2_m2m_buf_हटाओ_by_idx(&m2m_ctx->out_q_ctx, idx);
पूर्ण

अटल अंतरभूत काष्ठा vb2_v4l2_buffer *
v4l2_m2m_dst_buf_हटाओ_by_idx(काष्ठा v4l2_m2m_ctx *m2m_ctx, अचिन्हित पूर्णांक idx)
अणु
	वापस v4l2_m2m_buf_हटाओ_by_idx(&m2m_ctx->cap_q_ctx, idx);
पूर्ण

/**
 * v4l2_m2m_buf_copy_metadata() - copy buffer metadata from
 * the output buffer to the capture buffer
 *
 * @out_vb: the output buffer that is the source of the metadata.
 * @cap_vb: the capture buffer that will receive the metadata.
 * @copy_frame_flags: copy the KEY/B/PFRAME flags as well.
 *
 * This helper function copies the बारtamp, समयcode (अगर the TIMECODE
 * buffer flag was set), field and the TIMECODE, KEYFRAME, BFRAME, PFRAME
 * and TSTAMP_SRC_MASK flags from @out_vb to @cap_vb.
 *
 * If @copy_frame_flags is false, then the KEYFRAME, BFRAME and PFRAME
 * flags are not copied. This is typically needed क्रम encoders that
 * set this bits explicitly.
 */
व्योम v4l2_m2m_buf_copy_metadata(स्थिर काष्ठा vb2_v4l2_buffer *out_vb,
				काष्ठा vb2_v4l2_buffer *cap_vb,
				bool copy_frame_flags);

/* v4l2 request helper */

व्योम v4l2_m2m_request_queue(काष्ठा media_request *req);

/* v4l2 ioctl helpers */

पूर्णांक v4l2_m2m_ioctl_reqbufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_requestbuffers *rb);
पूर्णांक v4l2_m2m_ioctl_create_bufs(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_create_buffers *create);
पूर्णांक v4l2_m2m_ioctl_querybuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_buffer *buf);
पूर्णांक v4l2_m2m_ioctl_expbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_exportbuffer *eb);
पूर्णांक v4l2_m2m_ioctl_qbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_buffer *buf);
पूर्णांक v4l2_m2m_ioctl_dqbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_buffer *buf);
पूर्णांक v4l2_m2m_ioctl_prepare_buf(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_buffer *buf);
पूर्णांक v4l2_m2m_ioctl_streamon(काष्ठा file *file, व्योम *fh,
				क्रमागत v4l2_buf_type type);
पूर्णांक v4l2_m2m_ioctl_streamoff(काष्ठा file *file, व्योम *fh,
				क्रमागत v4l2_buf_type type);
पूर्णांक v4l2_m2m_ioctl_encoder_cmd(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_encoder_cmd *ec);
पूर्णांक v4l2_m2m_ioctl_decoder_cmd(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_decoder_cmd *dc);
पूर्णांक v4l2_m2m_ioctl_try_encoder_cmd(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_encoder_cmd *ec);
पूर्णांक v4l2_m2m_ioctl_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_decoder_cmd *dc);
पूर्णांक v4l2_m2m_ioctl_stateless_try_decoder_cmd(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_decoder_cmd *dc);
पूर्णांक v4l2_m2m_ioctl_stateless_decoder_cmd(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_decoder_cmd *dc);
पूर्णांक v4l2_m2m_fop_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
__poll_t v4l2_m2m_fop_poll(काष्ठा file *file, poll_table *रुको);

#पूर्ण_अगर /* _MEDIA_V4L2_MEM2MEM_H */

