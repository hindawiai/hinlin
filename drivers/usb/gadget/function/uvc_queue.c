<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	uvc_queue.c  --  USB Video Class driver - Buffers management
 *
 *	Copyright (C) 2005-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
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

#समावेश <media/v4l2-common.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "uvc.h"

/* ------------------------------------------------------------------------
 * Video buffers queue management.
 *
 * Video queues is initialized by uvcg_queue_init(). The function perक्रमms
 * basic initialization of the uvc_video_queue काष्ठा and never fails.
 *
 * Video buffers are managed by videobuf2. The driver uses a mutex to protect
 * the videobuf2 queue operations by serializing calls to videobuf2 and a
 * spinlock to protect the IRQ queue that holds the buffers to be processed by
 * the driver.
 */

/* -----------------------------------------------------------------------------
 * videobuf2 queue operations
 */

अटल पूर्णांक uvc_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vq);
	काष्ठा uvc_video *video = container_of(queue, काष्ठा uvc_video, queue);

	अगर (*nbuffers > UVC_MAX_VIDEO_BUFFERS)
		*nbuffers = UVC_MAX_VIDEO_BUFFERS;

	*nplanes = 1;

	sizes[0] = video->imagesize;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा uvc_buffer *buf = container_of(vbuf, काष्ठा uvc_buffer, buf);

	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0)) अणु
		uvc_trace(UVC_TRACE_CAPTURE, "[E] Bytes used out of bounds.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(queue->flags & UVC_QUEUE_DISCONNECTED))
		वापस -ENODEV;

	buf->state = UVC_BUF_STATE_QUEUED;
	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);
	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		buf->bytesused = 0;
	अन्यथा
		buf->bytesused = vb2_get_plane_payload(vb, 0);

	वापस 0;
पूर्ण

अटल व्योम uvc_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा uvc_buffer *buf = container_of(vbuf, काष्ठा uvc_buffer, buf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);

	अगर (likely(!(queue->flags & UVC_QUEUE_DISCONNECTED))) अणु
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

अटल स्थिर काष्ठा vb2_ops uvc_queue_qops = अणु
	.queue_setup = uvc_queue_setup,
	.buf_prepare = uvc_buffer_prepare,
	.buf_queue = uvc_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक uvcg_queue_init(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type,
		    काष्ठा mutex *lock)
अणु
	पूर्णांक ret;

	queue->queue.type = type;
	queue->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	queue->queue.drv_priv = queue;
	queue->queue.buf_काष्ठा_size = माप(काष्ठा uvc_buffer);
	queue->queue.ops = &uvc_queue_qops;
	queue->queue.lock = lock;
	queue->queue.mem_ops = &vb2_vदो_स्मृति_memops;
	queue->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC
				     | V4L2_BUF_FLAG_TSTAMP_SRC_खातापूर्ण;
	ret = vb2_queue_init(&queue->queue);
	अगर (ret)
		वापस ret;

	spin_lock_init(&queue->irqlock);
	INIT_LIST_HEAD(&queue->irqqueue);
	queue->flags = 0;

	वापस 0;
पूर्ण

/*
 * Free the video buffers.
 */
व्योम uvcg_मुक्त_buffers(काष्ठा uvc_video_queue *queue)
अणु
	vb2_queue_release(&queue->queue);
पूर्ण

/*
 * Allocate the video buffers.
 */
पूर्णांक uvcg_alloc_buffers(काष्ठा uvc_video_queue *queue,
			      काष्ठा v4l2_requestbuffers *rb)
अणु
	पूर्णांक ret;

	ret = vb2_reqbufs(&queue->queue, rb);

	वापस ret ? ret : rb->count;
पूर्ण

पूर्णांक uvcg_query_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf)
अणु
	वापस vb2_querybuf(&queue->queue, buf);
पूर्ण

पूर्णांक uvcg_queue_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = vb2_qbuf(&queue->queue, शून्य, buf);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&queue->irqlock, flags);
	ret = (queue->flags & UVC_QUEUE_PAUSED) != 0;
	queue->flags &= ~UVC_QUEUE_PAUSED;
	spin_unlock_irqrestore(&queue->irqlock, flags);
	वापस ret;
पूर्ण

/*
 * Dequeue a video buffer. If nonblocking is false, block until a buffer is
 * available.
 */
पूर्णांक uvcg_dequeue_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf,
			पूर्णांक nonblocking)
अणु
	वापस vb2_dqbuf(&queue->queue, buf, nonblocking);
पूर्ण

/*
 * Poll the video queue.
 *
 * This function implements video queue polling and is पूर्णांकended to be used by
 * the device poll handler.
 */
__poll_t uvcg_queue_poll(काष्ठा uvc_video_queue *queue, काष्ठा file *file,
			     poll_table *रुको)
अणु
	वापस vb2_poll(&queue->queue, file, रुको);
पूर्ण

पूर्णांक uvcg_queue_mmap(काष्ठा uvc_video_queue *queue, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vb2_mmap(&queue->queue, vma);
पूर्ण

#अगर_अघोषित CONFIG_MMU
/*
 * Get unmapped area.
 *
 * NO-MMU arch need this function to make mmap() work correctly.
 */
अचिन्हित दीर्घ uvcg_queue_get_unmapped_area(काष्ठा uvc_video_queue *queue,
					   अचिन्हित दीर्घ pgoff)
अणु
	वापस vb2_get_unmapped_area(&queue->queue, 0, 0, pgoff, 0);
पूर्ण
#पूर्ण_अगर

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
व्योम uvcg_queue_cancel(काष्ठा uvc_video_queue *queue, पूर्णांक disconnect)
अणु
	काष्ठा uvc_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	जबतक (!list_empty(&queue->irqqueue)) अणु
		buf = list_first_entry(&queue->irqqueue, काष्ठा uvc_buffer,
				       queue);
		list_del(&buf->queue);
		buf->state = UVC_BUF_STATE_ERROR;
		vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	/* This must be रक्षित by the irqlock spinlock to aव्योम race
	 * conditions between uvc_queue_buffer and the disconnection event that
	 * could result in an पूर्णांकerruptible रुको in uvc_dequeue_buffer. Do not
	 * blindly replace this logic by checking क्रम the UVC_DEV_DISCONNECTED
	 * state outside the queue code.
	 */
	अगर (disconnect)
		queue->flags |= UVC_QUEUE_DISCONNECTED;
	spin_unlock_irqrestore(&queue->irqlock, flags);
पूर्ण

/*
 * Enable or disable the video buffers queue.
 *
 * The queue must be enabled beक्रमe starting video acquisition and must be
 * disabled after stopping it. This ensures that the video buffers queue
 * state can be properly initialized beक्रमe buffers are accessed from the
 * पूर्णांकerrupt handler.
 *
 * Enabling the video queue initializes parameters (such as sequence number,
 * sync pattern, ...). If the queue is alपढ़ोy enabled, वापस -EBUSY.
 *
 * Disabling the video queue cancels the queue and हटाओs all buffers from
 * the मुख्य queue.
 *
 * This function can't be called from पूर्णांकerrupt context. Use
 * uvcg_queue_cancel() instead.
 */
पूर्णांक uvcg_queue_enable(काष्ठा uvc_video_queue *queue, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (enable) अणु
		ret = vb2_streamon(&queue->queue, queue->queue.type);
		अगर (ret < 0)
			वापस ret;

		queue->sequence = 0;
		queue->buf_used = 0;
	पूर्ण अन्यथा अणु
		ret = vb2_streamoff(&queue->queue, queue->queue.type);
		अगर (ret < 0)
			वापस ret;

		spin_lock_irqsave(&queue->irqlock, flags);
		INIT_LIST_HEAD(&queue->irqqueue);

		/*
		 * FIXME: We need to clear the DISCONNECTED flag to ensure that
		 * applications will be able to queue buffers क्रम the next
		 * streaming run. However, clearing it here करोesn't guarantee
		 * that the device will be reconnected in the meanसमय.
		 */
		queue->flags &= ~UVC_QUEUE_DISCONNECTED;
		spin_unlock_irqrestore(&queue->irqlock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/* called with &queue_irqlock held.. */
काष्ठा uvc_buffer *uvcg_queue_next_buffer(काष्ठा uvc_video_queue *queue,
					  काष्ठा uvc_buffer *buf)
अणु
	काष्ठा uvc_buffer *nextbuf;

	अगर ((queue->flags & UVC_QUEUE_DROP_INCOMPLETE) &&
	     buf->length != buf->bytesused) अणु
		buf->state = UVC_BUF_STATE_QUEUED;
		vb2_set_plane_payload(&buf->buf.vb2_buf, 0, 0);
		वापस buf;
	पूर्ण

	list_del(&buf->queue);
	अगर (!list_empty(&queue->irqqueue))
		nextbuf = list_first_entry(&queue->irqqueue, काष्ठा uvc_buffer,
					   queue);
	अन्यथा
		nextbuf = शून्य;

	buf->buf.field = V4L2_FIELD_NONE;
	buf->buf.sequence = queue->sequence++;
	buf->buf.vb2_buf.बारtamp = kसमय_get_ns();

	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, buf->bytesused);
	vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);

	वापस nextbuf;
पूर्ण

काष्ठा uvc_buffer *uvcg_queue_head(काष्ठा uvc_video_queue *queue)
अणु
	काष्ठा uvc_buffer *buf = शून्य;

	अगर (!list_empty(&queue->irqqueue))
		buf = list_first_entry(&queue->irqqueue, काष्ठा uvc_buffer,
				       queue);
	अन्यथा
		queue->flags |= UVC_QUEUE_PAUSED;

	वापस buf;
पूर्ण

