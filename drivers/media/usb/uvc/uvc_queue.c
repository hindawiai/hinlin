<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_queue.c  --  USB Video Class driver - Buffers management
 *
 *      Copyright (C) 2005-2010
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "uvcvideo.h"

/* ------------------------------------------------------------------------
 * Video buffers queue management.
 *
 * Video queues is initialized by uvc_queue_init(). The function perक्रमms
 * basic initialization of the uvc_video_queue काष्ठा and never fails.
 *
 * Video buffers are managed by videobuf2. The driver uses a mutex to protect
 * the videobuf2 queue operations by serializing calls to videobuf2 and a
 * spinlock to protect the IRQ queue that holds the buffers to be processed by
 * the driver.
 */

अटल अंतरभूत काष्ठा uvc_buffer *uvc_vbuf_to_buffer(काष्ठा vb2_v4l2_buffer *buf)
अणु
	वापस container_of(buf, काष्ठा uvc_buffer, buf);
पूर्ण

/*
 * Return all queued buffers to videobuf2 in the requested state.
 *
 * This function must be called with the queue spinlock held.
 */
अटल व्योम uvc_queue_वापस_buffers(काष्ठा uvc_video_queue *queue,
			       क्रमागत uvc_buffer_state state)
अणु
	क्रमागत vb2_buffer_state vb2_state = state == UVC_BUF_STATE_ERROR
					? VB2_BUF_STATE_ERROR
					: VB2_BUF_STATE_QUEUED;

	जबतक (!list_empty(&queue->irqqueue)) अणु
		काष्ठा uvc_buffer *buf = list_first_entry(&queue->irqqueue,
							  काष्ठा uvc_buffer,
							  queue);
		list_del(&buf->queue);
		buf->state = state;
		vb2_buffer_करोne(&buf->buf.vb2_buf, vb2_state);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * videobuf2 queue operations
 */

अटल पूर्णांक uvc_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vq);
	काष्ठा uvc_streaming *stream;
	अचिन्हित पूर्णांक size;

	चयन (vq->type) अणु
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		size = UVC_METADATA_BUF_SIZE;
		अवरोध;

	शेष:
		stream = uvc_queue_to_stream(queue);
		size = stream->ctrl.dwMaxVideoFrameSize;
		अवरोध;
	पूर्ण

	/*
	 * When called with plane sizes, validate them. The driver supports
	 * single planar क्रमmats only, and requires buffers to be large enough
	 * to store a complete frame.
	 */
	अगर (*nplanes)
		वापस *nplanes != 1 || sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक uvc_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा uvc_buffer *buf = uvc_vbuf_to_buffer(vbuf);

	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0)) अणु
		uvc_dbg(uvc_queue_to_stream(queue)->dev, CAPTURE,
			"[E] Bytes used out of bounds\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(queue->flags & UVC_QUEUE_DISCONNECTED))
		वापस -ENODEV;

	buf->state = UVC_BUF_STATE_QUEUED;
	buf->error = 0;
	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);
	अगर (vb->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf->bytesused = 0;
	अन्यथा
		buf->bytesused = vb2_get_plane_payload(vb, 0);

	वापस 0;
पूर्ण

अटल व्योम uvc_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा uvc_buffer *buf = uvc_vbuf_to_buffer(vbuf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	अगर (likely(!(queue->flags & UVC_QUEUE_DISCONNECTED))) अणु
		kref_init(&buf->ref);
		list_add_tail(&buf->queue, &queue->irqqueue);
	पूर्ण अन्यथा अणु
		/* If the device is disconnected वापस the buffer to userspace
		 * directly. The next QBUF call will fail with -ENODEV.
		 */
		buf->state = UVC_BUF_STATE_ERROR;
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
	पूर्ण

	spin_unlock_irqrestore(&queue->irqlock, flags);
पूर्ण

अटल व्योम uvc_buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा uvc_streaming *stream = uvc_queue_to_stream(queue);
	काष्ठा uvc_buffer *buf = uvc_vbuf_to_buffer(vbuf);

	अगर (vb->state == VB2_BUF_STATE_DONE)
		uvc_video_घड़ी_update(stream, vbuf, buf);
पूर्ण

अटल पूर्णांक uvc_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vq);
	काष्ठा uvc_streaming *stream = uvc_queue_to_stream(queue);
	पूर्णांक ret;

	lockdep_निश्चित_irqs_enabled();

	queue->buf_used = 0;

	ret = uvc_video_start_streaming(stream);
	अगर (ret == 0)
		वापस 0;

	spin_lock_irq(&queue->irqlock);
	uvc_queue_वापस_buffers(queue, UVC_BUF_STATE_QUEUED);
	spin_unlock_irq(&queue->irqlock);

	वापस ret;
पूर्ण

अटल व्योम uvc_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vq);

	lockdep_निश्चित_irqs_enabled();

	अगर (vq->type != V4L2_BUF_TYPE_META_CAPTURE)
		uvc_video_stop_streaming(uvc_queue_to_stream(queue));

	spin_lock_irq(&queue->irqlock);
	uvc_queue_वापस_buffers(queue, UVC_BUF_STATE_ERROR);
	spin_unlock_irq(&queue->irqlock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops uvc_queue_qops = अणु
	.queue_setup = uvc_queue_setup,
	.buf_prepare = uvc_buffer_prepare,
	.buf_queue = uvc_buffer_queue,
	.buf_finish = uvc_buffer_finish,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = uvc_start_streaming,
	.stop_streaming = uvc_stop_streaming,
पूर्ण;

अटल स्थिर काष्ठा vb2_ops uvc_meta_queue_qops = अणु
	.queue_setup = uvc_queue_setup,
	.buf_prepare = uvc_buffer_prepare,
	.buf_queue = uvc_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.stop_streaming = uvc_stop_streaming,
पूर्ण;

पूर्णांक uvc_queue_init(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type,
		    पूर्णांक drop_corrupted)
अणु
	पूर्णांक ret;

	queue->queue.type = type;
	queue->queue.io_modes = VB2_MMAP | VB2_USERPTR;
	queue->queue.drv_priv = queue;
	queue->queue.buf_काष्ठा_size = माप(काष्ठा uvc_buffer);
	queue->queue.mem_ops = &vb2_vदो_स्मृति_memops;
	queue->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC
		| V4L2_BUF_FLAG_TSTAMP_SRC_SOE;
	queue->queue.lock = &queue->mutex;

	चयन (type) अणु
	हाल V4L2_BUF_TYPE_META_CAPTURE:
		queue->queue.ops = &uvc_meta_queue_qops;
		अवरोध;
	शेष:
		queue->queue.io_modes |= VB2_DMABUF;
		queue->queue.ops = &uvc_queue_qops;
		अवरोध;
	पूर्ण

	ret = vb2_queue_init(&queue->queue);
	अगर (ret)
		वापस ret;

	mutex_init(&queue->mutex);
	spin_lock_init(&queue->irqlock);
	INIT_LIST_HEAD(&queue->irqqueue);
	queue->flags = drop_corrupted ? UVC_QUEUE_DROP_CORRUPTED : 0;

	वापस 0;
पूर्ण

व्योम uvc_queue_release(काष्ठा uvc_video_queue *queue)
अणु
	mutex_lock(&queue->mutex);
	vb2_queue_release(&queue->queue);
	mutex_unlock(&queue->mutex);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 queue operations
 */

पूर्णांक uvc_request_buffers(काष्ठा uvc_video_queue *queue,
			काष्ठा v4l2_requestbuffers *rb)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_reqbufs(&queue->queue, rb);
	mutex_unlock(&queue->mutex);

	वापस ret ? ret : rb->count;
पूर्ण

पूर्णांक uvc_query_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_querybuf(&queue->queue, buf);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_create_buffers(काष्ठा uvc_video_queue *queue,
		       काष्ठा v4l2_create_buffers *cb)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_create_bufs(&queue->queue, cb);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_queue_buffer(काष्ठा uvc_video_queue *queue,
		     काष्ठा media_device *mdev, काष्ठा v4l2_buffer *buf)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_qbuf(&queue->queue, mdev, buf);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_export_buffer(काष्ठा uvc_video_queue *queue,
		      काष्ठा v4l2_exportbuffer *exp)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_expbuf(&queue->queue, exp);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_dequeue_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf,
		       पूर्णांक nonblocking)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_dqbuf(&queue->queue, buf, nonblocking);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_queue_streamon(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_streamon(&queue->queue, type);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_queue_streamoff(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type)
अणु
	पूर्णांक ret;

	mutex_lock(&queue->mutex);
	ret = vb2_streamoff(&queue->queue, type);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

पूर्णांक uvc_queue_mmap(काष्ठा uvc_video_queue *queue, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vb2_mmap(&queue->queue, vma);
पूर्ण

#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ uvc_queue_get_unmapped_area(काष्ठा uvc_video_queue *queue,
		अचिन्हित दीर्घ pgoff)
अणु
	वापस vb2_get_unmapped_area(&queue->queue, 0, 0, pgoff, 0);
पूर्ण
#पूर्ण_अगर

__poll_t uvc_queue_poll(काष्ठा uvc_video_queue *queue, काष्ठा file *file,
			    poll_table *रुको)
अणु
	__poll_t ret;

	mutex_lock(&queue->mutex);
	ret = vb2_poll(&queue->queue, file, रुको);
	mutex_unlock(&queue->mutex);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 *
 */

/*
 * Check अगर buffers have been allocated.
 */
पूर्णांक uvc_queue_allocated(काष्ठा uvc_video_queue *queue)
अणु
	पूर्णांक allocated;

	mutex_lock(&queue->mutex);
	allocated = vb2_is_busy(&queue->queue);
	mutex_unlock(&queue->mutex);

	वापस allocated;
पूर्ण

/*
 * Cancel the video buffers queue.
 *
 * Cancelling the queue marks all buffers on the irq queue as erroneous,
 * wakes them up and हटाओs them from the queue.
 *
 * If the disconnect parameter is set, further calls to uvc_queue_buffer will
 * fail with -ENODEV.
 *
 * This function acquires the irq spinlock and can be called from पूर्णांकerrupt
 * context.
 */
व्योम uvc_queue_cancel(काष्ठा uvc_video_queue *queue, पूर्णांक disconnect)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	uvc_queue_वापस_buffers(queue, UVC_BUF_STATE_ERROR);
	/* This must be रक्षित by the irqlock spinlock to aव्योम race
	 * conditions between uvc_buffer_queue and the disconnection event that
	 * could result in an पूर्णांकerruptible रुको in uvc_dequeue_buffer. Do not
	 * blindly replace this logic by checking क्रम the UVC_QUEUE_DISCONNECTED
	 * state outside the queue code.
	 */
	अगर (disconnect)
		queue->flags |= UVC_QUEUE_DISCONNECTED;
	spin_unlock_irqrestore(&queue->irqlock, flags);
पूर्ण

/*
 * uvc_queue_get_current_buffer: Obtain the current working output buffer
 *
 * Buffers may span multiple packets, and even URBs, thereक्रमe the active buffer
 * reमुख्यs on the queue until the खातापूर्ण marker.
 */
अटल काष्ठा uvc_buffer *
__uvc_queue_get_current_buffer(काष्ठा uvc_video_queue *queue)
अणु
	अगर (list_empty(&queue->irqqueue))
		वापस शून्य;

	वापस list_first_entry(&queue->irqqueue, काष्ठा uvc_buffer, queue);
पूर्ण

काष्ठा uvc_buffer *uvc_queue_get_current_buffer(काष्ठा uvc_video_queue *queue)
अणु
	काष्ठा uvc_buffer *nextbuf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	nextbuf = __uvc_queue_get_current_buffer(queue);
	spin_unlock_irqrestore(&queue->irqlock, flags);

	वापस nextbuf;
पूर्ण

/*
 * uvc_queue_buffer_requeue: Requeue a buffer on our पूर्णांकernal irqqueue
 *
 * Reuse a buffer through our पूर्णांकernal queue without the need to 'prepare'.
 * The buffer will be वापसed to userspace through the uvc_buffer_queue call अगर
 * the device has been disconnected.
 */
अटल व्योम uvc_queue_buffer_requeue(काष्ठा uvc_video_queue *queue,
		काष्ठा uvc_buffer *buf)
अणु
	buf->error = 0;
	buf->state = UVC_BUF_STATE_QUEUED;
	buf->bytesused = 0;
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, 0);

	uvc_buffer_queue(&buf->buf.vb2_buf);
पूर्ण

अटल व्योम uvc_queue_buffer_complete(काष्ठा kref *ref)
अणु
	काष्ठा uvc_buffer *buf = container_of(ref, काष्ठा uvc_buffer, ref);
	काष्ठा vb2_buffer *vb = &buf->buf.vb2_buf;
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);

	अगर ((queue->flags & UVC_QUEUE_DROP_CORRUPTED) && buf->error) अणु
		uvc_queue_buffer_requeue(queue, buf);
		वापस;
	पूर्ण

	buf->state = buf->error ? UVC_BUF_STATE_ERROR : UVC_BUF_STATE_DONE;
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, buf->bytesused);
	vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

/*
 * Release a reference on the buffer. Complete the buffer when the last
 * reference is released.
 */
व्योम uvc_queue_buffer_release(काष्ठा uvc_buffer *buf)
अणु
	kref_put(&buf->ref, uvc_queue_buffer_complete);
पूर्ण

/*
 * Remove this buffer from the queue. Lअगरeसमय will persist जबतक async actions
 * are still running (अगर any), and uvc_queue_buffer_release will give the buffer
 * back to VB2 when all users have completed.
 */
काष्ठा uvc_buffer *uvc_queue_next_buffer(काष्ठा uvc_video_queue *queue,
		काष्ठा uvc_buffer *buf)
अणु
	काष्ठा uvc_buffer *nextbuf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	list_del(&buf->queue);
	nextbuf = __uvc_queue_get_current_buffer(queue);
	spin_unlock_irqrestore(&queue->irqlock, flags);

	uvc_queue_buffer_release(buf);

	वापस nextbuf;
पूर्ण
