<शैली गुरु>
/*
 * videobuf2-v4l2.h - V4L2 driver helper framework
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _MEDIA_VIDEOBUF2_V4L2_H
#घोषणा _MEDIA_VIDEOBUF2_V4L2_H

#समावेश <linux/videodev2.h>
#समावेश <media/videobuf2-core.h>

#अगर VB2_MAX_FRAME != VIDEO_MAX_FRAME
#त्रुटि VB2_MAX_FRAME != VIDEO_MAX_FRAME
#पूर्ण_अगर

#अगर VB2_MAX_PLANES != VIDEO_MAX_PLANES
#त्रुटि VB2_MAX_PLANES != VIDEO_MAX_PLANES
#पूर्ण_अगर

काष्ठा video_device;

/**
 * काष्ठा vb2_v4l2_buffer - video buffer inक्रमmation क्रम v4l2.
 *
 * @vb2_buf:	embedded काष्ठा &vb2_buffer.
 * @flags:	buffer inक्रमmational flags.
 * @field:	field order of the image in the buffer, as defined by
 *		&क्रमागत v4l2_field.
 * @समयcode:	frame समयcode.
 * @sequence:	sequence count of this frame.
 * @request_fd:	the request_fd associated with this buffer
 * @is_held:	अगर true, then this capture buffer was held
 * @planes:	plane inक्रमmation (userptr/fd, length, bytesused, data_offset).
 *
 * Should contain enough inक्रमmation to be able to cover all the fields
 * of &काष्ठा v4l2_buffer at ``videodev2.h``.
 */
काष्ठा vb2_v4l2_buffer अणु
	काष्ठा vb2_buffer	vb2_buf;

	__u32			flags;
	__u32			field;
	काष्ठा v4l2_समयcode	समयcode;
	__u32			sequence;
	__s32			request_fd;
	bool			is_held;
	काष्ठा vb2_plane	planes[VB2_MAX_PLANES];
पूर्ण;

/* VB2 V4L2 flags as set in vb2_queue.subप्रणाली_flags */
#घोषणा VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF (1 << 0)

/*
 * to_vb2_v4l2_buffer() - cast काष्ठा vb2_buffer * to काष्ठा vb2_v4l2_buffer *
 */
#घोषणा to_vb2_v4l2_buffer(vb) \
	container_of(vb, काष्ठा vb2_v4l2_buffer, vb2_buf)

/**
 * vb2_find_बारtamp() - Find buffer with given बारtamp in the queue
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @बारtamp:	the बारtamp to find.
 * @start_idx:	the start index (usually 0) in the buffer array to start
 *		searching from. Note that there may be multiple buffers
 *		with the same बारtamp value, so you can restart the search
 *		by setting @start_idx to the previously found index + 1.
 *
 * Returns the buffer index of the buffer with the given @बारtamp, or
 * -1 अगर no buffer with @बारtamp was found.
 */
पूर्णांक vb2_find_बारtamp(स्थिर काष्ठा vb2_queue *q, u64 बारtamp,
		       अचिन्हित पूर्णांक start_idx);

पूर्णांक vb2_querybuf(काष्ठा vb2_queue *q, काष्ठा v4l2_buffer *b);

/**
 * vb2_reqbufs() - Wrapper क्रम vb2_core_reqbufs() that also verअगरies
 * the memory and type values.
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @req:	&काष्ठा v4l2_requestbuffers passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_reqbufs handler in driver.
 */
पूर्णांक vb2_reqbufs(काष्ठा vb2_queue *q, काष्ठा v4l2_requestbuffers *req);

/**
 * vb2_create_bufs() - Wrapper क्रम vb2_core_create_bufs() that also verअगरies
 * the memory and type values.
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @create:	creation parameters, passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_create_bufs handler in driver
 */
पूर्णांक vb2_create_bufs(काष्ठा vb2_queue *q, काष्ठा v4l2_create_buffers *create);

/**
 * vb2_prepare_buf() - Pass ownership of a buffer from userspace to the kernel
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @mdev:	poपूर्णांकer to &काष्ठा media_device, may be शून्य.
 * @b:		buffer काष्ठाure passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_prepare_buf handler in driver
 *
 * Should be called from &v4l2_ioctl_ops->vidioc_prepare_buf ioctl handler
 * of a driver.
 *
 * This function:
 *
 * #) verअगरies the passed buffer,
 * #) calls &vb2_ops->buf_prepare callback in the driver (अगर provided),
 *    in which driver-specअगरic buffer initialization can be perक्रमmed.
 * #) अगर @b->request_fd is non-zero and @mdev->ops->req_queue is set,
 *    then bind the prepared buffer to the request.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from &v4l2_ioctl_ops->vidioc_prepare_buf handler in driver.
 */
पूर्णांक vb2_prepare_buf(काष्ठा vb2_queue *q, काष्ठा media_device *mdev,
		    काष्ठा v4l2_buffer *b);

/**
 * vb2_qbuf() - Queue a buffer from userspace
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @mdev:	poपूर्णांकer to &काष्ठा media_device, may be शून्य.
 * @b:		buffer काष्ठाure passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_qbuf handler in driver
 *
 * Should be called from &v4l2_ioctl_ops->vidioc_qbuf handler of a driver.
 *
 * This function:
 *
 * #) verअगरies the passed buffer;
 * #) अगर @b->request_fd is non-zero and @mdev->ops->req_queue is set,
 *    then bind the buffer to the request.
 * #) अगर necessary, calls &vb2_ops->buf_prepare callback in the driver
 *    (अगर provided), in which driver-specअगरic buffer initialization can
 *    be perक्रमmed;
 * #) अगर streaming is on, queues the buffer in driver by the means of
 *    &vb2_ops->buf_queue callback क्रम processing.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from &v4l2_ioctl_ops->vidioc_qbuf handler in driver.
 */
पूर्णांक vb2_qbuf(काष्ठा vb2_queue *q, काष्ठा media_device *mdev,
	     काष्ठा v4l2_buffer *b);

/**
 * vb2_expbuf() - Export a buffer as a file descriptor
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @eb:		export buffer काष्ठाure passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_expbuf handler in driver
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from &v4l2_ioctl_ops->vidioc_expbuf handler in driver.
 */
पूर्णांक vb2_expbuf(काष्ठा vb2_queue *q, काष्ठा v4l2_exportbuffer *eb);

/**
 * vb2_dqbuf() - Dequeue a buffer to the userspace
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @b:		buffer काष्ठाure passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_dqbuf handler in driver
 * @nonblocking: अगर true, this call will not sleep रुकोing क्रम a buffer अगर no
 *		 buffers पढ़ोy क्रम dequeuing are present. Normally the driver
 *		 would be passing (&file->f_flags & %O_NONBLOCK) here
 *
 * Should be called from &v4l2_ioctl_ops->vidioc_dqbuf ioctl handler
 * of a driver.
 *
 * This function:
 *
 * #) verअगरies the passed buffer;
 * #) calls &vb2_ops->buf_finish callback in the driver (अगर provided), in which
 *    driver can perक्रमm any additional operations that may be required beक्रमe
 *    वापसing the buffer to userspace, such as cache sync;
 * #) the buffer काष्ठा members are filled with relevant inक्रमmation क्रम
 *    the userspace.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from &v4l2_ioctl_ops->vidioc_dqbuf handler in driver.
 */
पूर्णांक vb2_dqbuf(काष्ठा vb2_queue *q, काष्ठा v4l2_buffer *b, bool nonblocking);

/**
 * vb2_streamon - start streaming
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @type:	type argument passed from userspace to vidioc_streamon handler,
 *		as defined by &क्रमागत v4l2_buf_type.
 *
 * Should be called from &v4l2_ioctl_ops->vidioc_streamon handler of a driver.
 *
 * This function:
 *
 * 1) verअगरies current state
 * 2) passes any previously queued buffers to the driver and starts streaming
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from &v4l2_ioctl_ops->vidioc_streamon handler in the driver.
 */
पूर्णांक vb2_streamon(काष्ठा vb2_queue *q, क्रमागत v4l2_buf_type type);

/**
 * vb2_streamoff - stop streaming
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @type:	type argument passed from userspace to vidioc_streamoff handler
 *
 * Should be called from vidioc_streamoff handler of a driver.
 *
 * This function:
 *
 * #) verअगरies current state,
 * #) stop streaming and dequeues any queued buffers, including those previously
 *    passed to the driver (after रुकोing क्रम the driver to finish).
 *
 * This call can be used क्रम pausing playback.
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from vidioc_streamoff handler in the driver
 */
पूर्णांक vb2_streamoff(काष्ठा vb2_queue *q, क्रमागत v4l2_buf_type type);

/**
 * vb2_queue_init() - initialize a videobuf2 queue
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * The vb2_queue काष्ठाure should be allocated by the driver. The driver is
 * responsible of clearing it's content and setting initial values क्रम some
 * required entries beक्रमe calling this function.
 * q->ops, q->mem_ops, q->type and q->io_modes are mandatory. Please refer
 * to the काष्ठा vb2_queue description in include/media/videobuf2-core.h
 * क्रम more inक्रमmation.
 */
पूर्णांक __must_check vb2_queue_init(काष्ठा vb2_queue *q);

/**
 * vb2_queue_init_name() - initialize a videobuf2 queue with a name
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @name:	the queue name
 *
 * This function initializes the vb2_queue exactly like vb2_queue_init(),
 * and additionally sets the queue name. The queue name is used क्रम logging
 * purpose, and should uniquely identअगरy the queue within the context of the
 * device it beदीर्घs to. This is useful to attribute kernel log messages to the
 * right queue क्रम m2m devices or other devices that handle multiple queues.
 */
पूर्णांक __must_check vb2_queue_init_name(काष्ठा vb2_queue *q, स्थिर अक्षर *name);

/**
 * vb2_queue_release() - stop streaming, release the queue and मुक्त memory
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This function stops streaming and perक्रमms necessary clean ups, including
 * मुक्तing video buffer memory. The driver is responsible क्रम मुक्तing
 * the vb2_queue काष्ठाure itself.
 */
व्योम vb2_queue_release(काष्ठा vb2_queue *q);

/**
 * vb2_poll() - implements poll userspace operation
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @file:	file argument passed to the poll file operation handler
 * @रुको:	रुको argument passed to the poll file operation handler
 *
 * This function implements poll file operation handler क्रम a driver.
 * For CAPTURE queues, अगर a buffer is पढ़ोy to be dequeued, the userspace will
 * be inक्रमmed that the file descriptor of a video device is available क्रम
 * पढ़ोing.
 * For OUTPUT queues, अगर a buffer is पढ़ोy to be dequeued, the file descriptor
 * will be reported as available क्रम writing.
 *
 * If the driver uses काष्ठा v4l2_fh, then vb2_poll() will also check क्रम any
 * pending events.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from poll handler in driver.
 */
__poll_t vb2_poll(काष्ठा vb2_queue *q, काष्ठा file *file, poll_table *रुको);

/*
 * The following functions are not part of the vb2 core API, but are simple
 * helper functions that you can use in your काष्ठा v4l2_file_operations,
 * काष्ठा v4l2_ioctl_ops and काष्ठा vb2_ops. They will serialize अगर vb2_queue->lock
 * or video_device->lock is set, and they will set and test vb2_queue->owner
 * to check अगर the calling filehandle is permitted to करो the queuing operation.
 */

/* काष्ठा v4l2_ioctl_ops helpers */

पूर्णांक vb2_ioctl_reqbufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_requestbuffers *p);
पूर्णांक vb2_ioctl_create_bufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_create_buffers *p);
पूर्णांक vb2_ioctl_prepare_buf(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_buffer *p);
पूर्णांक vb2_ioctl_querybuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p);
पूर्णांक vb2_ioctl_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p);
पूर्णांक vb2_ioctl_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p);
पूर्णांक vb2_ioctl_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i);
पूर्णांक vb2_ioctl_streamoff(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i);
पूर्णांक vb2_ioctl_expbuf(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_exportbuffer *p);

/* काष्ठा v4l2_file_operations helpers */

पूर्णांक vb2_fop_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक vb2_fop_release(काष्ठा file *file);
पूर्णांक _vb2_fop_release(काष्ठा file *file, काष्ठा mutex *lock);
sमाप_प्रकार vb2_fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos);
sमाप_प्रकार vb2_fop_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos);
__poll_t vb2_fop_poll(काष्ठा file *file, poll_table *रुको);
#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ vb2_fop_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags);
#पूर्ण_अगर

/**
 * vb2_video_unरेजिस्टर_device - unरेजिस्टर the video device and release queue
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 *
 * If the driver uses vb2_fop_release()/_vb2_fop_release(), then it should use
 * vb2_video_unरेजिस्टर_device() instead of video_unरेजिस्टर_device().
 *
 * This function will call video_unरेजिस्टर_device() and then release the
 * vb2_queue अगर streaming is in progress. This will stop streaming and
 * this will simplअगरy the unbind sequence since after this call all subdevs
 * will have stopped streaming as well.
 */
व्योम vb2_video_unरेजिस्टर_device(काष्ठा video_device *vdev);

/**
 * vb2_ops_रुको_prepare - helper function to lock a काष्ठा &vb2_queue
 *
 * @vq: poपूर्णांकer to &काष्ठा vb2_queue
 *
 * ..note:: only use अगर vq->lock is non-शून्य.
 */
व्योम vb2_ops_रुको_prepare(काष्ठा vb2_queue *vq);

/**
 * vb2_ops_रुको_finish - helper function to unlock a काष्ठा &vb2_queue
 *
 * @vq: poपूर्णांकer to &काष्ठा vb2_queue
 *
 * ..note:: only use अगर vq->lock is non-शून्य.
 */
व्योम vb2_ops_रुको_finish(काष्ठा vb2_queue *vq);

काष्ठा media_request;
पूर्णांक vb2_request_validate(काष्ठा media_request *req);
व्योम vb2_request_queue(काष्ठा media_request *req);

#पूर्ण_अगर /* _MEDIA_VIDEOBUF2_V4L2_H */
