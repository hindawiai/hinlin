<शैली गुरु>
/*
 * videobuf2-core.h - Video Buffer 2 Core Framework
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _MEDIA_VIDEOBUF2_CORE_H
#घोषणा _MEDIA_VIDEOBUF2_CORE_H

#समावेश <linux/mm_types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/bitops.h>
#समावेश <media/media-request.h>
#समावेश <media/frame_vector.h>

#घोषणा VB2_MAX_FRAME	(32)
#घोषणा VB2_MAX_PLANES	(8)

/**
 * क्रमागत vb2_memory - type of memory model used to make the buffers visible
 *	on userspace.
 *
 * @VB2_MEMORY_UNKNOWN:	Buffer status is unknown or it is not used yet on
 *			userspace.
 * @VB2_MEMORY_MMAP:	The buffers are allocated by the Kernel and it is
 *			memory mapped via mmap() ioctl. This model is
 *			also used when the user is using the buffers via
 *			पढ़ो() or ग_लिखो() प्रणाली calls.
 * @VB2_MEMORY_USERPTR:	The buffers was allocated in userspace and it is
 *			memory mapped via mmap() ioctl.
 * @VB2_MEMORY_DMABUF:	The buffers are passed to userspace via DMA buffer.
 */
क्रमागत vb2_memory अणु
	VB2_MEMORY_UNKNOWN	= 0,
	VB2_MEMORY_MMAP		= 1,
	VB2_MEMORY_USERPTR	= 2,
	VB2_MEMORY_DMABUF	= 4,
पूर्ण;

काष्ठा vb2_fileio_data;
काष्ठा vb2_thपढ़ोio_data;

/**
 * काष्ठा vb2_mem_ops - memory handling/memory allocator operations.
 * @alloc:	allocate video memory and, optionally, allocator निजी data,
 *		वापस ERR_PTR() on failure or a poपूर्णांकer to allocator निजी,
 *		per-buffer data on success; the वापसed निजी काष्ठाure
 *		will then be passed as @buf_priv argument to other ops in this
 *		काष्ठाure. Additional gfp_flags to use when allocating the
 *		are also passed to this operation. These flags are from the
 *		gfp_flags field of vb2_queue. The size argument to this function
 *		shall be *page aligned*.
 * @put:	inक्रमm the allocator that the buffer will no दीर्घer be used;
 *		usually will result in the allocator मुक्तing the buffer (अगर
 *		no other users of this buffer are present); the @buf_priv
 *		argument is the allocator निजी per-buffer काष्ठाure
 *		previously वापसed from the alloc callback.
 * @get_dmabuf: acquire userspace memory क्रम a hardware operation; used क्रम
 *		 DMABUF memory types.
 * @get_userptr: acquire userspace memory क्रम a hardware operation; used क्रम
 *		 USERPTR memory types; vaddr is the address passed to the
 *		 videobuf layer when queuing a video buffer of USERPTR type;
 *		 should वापस an allocator निजी per-buffer काष्ठाure
 *		 associated with the buffer on success, ERR_PTR() on failure;
 *		 the वापसed निजी काष्ठाure will then be passed as @buf_priv
 *		 argument to other ops in this काष्ठाure.
 * @put_userptr: inक्रमm the allocator that a USERPTR buffer will no दीर्घer
 *		 be used.
 * @attach_dmabuf: attach a shared &काष्ठा dma_buf क्रम a hardware operation;
 *		   used क्रम DMABUF memory types; dev is the alloc device
 *		   dbuf is the shared dma_buf; वापसs ERR_PTR() on failure;
 *		   allocator निजी per-buffer काष्ठाure on success;
 *		   this needs to be used क्रम further accesses to the buffer.
 * @detach_dmabuf: inक्रमm the exporter of the buffer that the current DMABUF
 *		   buffer is no दीर्घer used; the @buf_priv argument is the
 *		   allocator निजी per-buffer काष्ठाure previously वापसed
 *		   from the attach_dmabuf callback.
 * @map_dmabuf: request क्रम access to the dmabuf from allocator; the allocator
 *		of dmabuf is inक्रमmed that this driver is going to use the
 *		dmabuf.
 * @unmap_dmabuf: releases access control to the dmabuf - allocator is notअगरied
 *		  that this driver is करोne using the dmabuf क्रम now.
 * @prepare:	called every समय the buffer is passed from userspace to the
 *		driver, useful क्रम cache synchronisation, optional.
 * @finish:	called every समय the buffer is passed back from the driver
 *		to the userspace, also optional.
 * @vaddr:	वापस a kernel भव address to a given memory buffer
 *		associated with the passed निजी काष्ठाure or शून्य अगर no
 *		such mapping exists.
 * @cookie:	वापस allocator specअगरic cookie क्रम a given memory buffer
 *		associated with the passed निजी काष्ठाure or शून्य अगर not
 *		available.
 * @num_users:	वापस the current number of users of a memory buffer;
 *		वापस 1 अगर the videobuf layer (or actually the driver using
 *		it) is the only user.
 * @mmap:	setup a userspace mapping क्रम a given memory buffer under
 *		the provided भव memory region.
 *
 * Those operations are used by the videobuf2 core to implement the memory
 * handling/memory allocators क्रम each type of supported streaming I/O method.
 *
 * .. note::
 *    #) Required ops क्रम USERPTR types: get_userptr, put_userptr.
 *
 *    #) Required ops क्रम MMAP types: alloc, put, num_users, mmap.
 *
 *    #) Required ops क्रम पढ़ो/ग_लिखो access types: alloc, put, num_users, vaddr.
 *
 *    #) Required ops क्रम DMABUF types: attach_dmabuf, detach_dmabuf,
 *       map_dmabuf, unmap_dmabuf.
 */
काष्ठा vb2_mem_ops अणु
	व्योम		*(*alloc)(काष्ठा device *dev, अचिन्हित दीर्घ attrs,
				  अचिन्हित दीर्घ size,
				  क्रमागत dma_data_direction dma_dir,
				  gfp_t gfp_flags);
	व्योम		(*put)(व्योम *buf_priv);
	काष्ठा dma_buf *(*get_dmabuf)(व्योम *buf_priv, अचिन्हित दीर्घ flags);

	व्योम		*(*get_userptr)(काष्ठा device *dev, अचिन्हित दीर्घ vaddr,
					अचिन्हित दीर्घ size,
					क्रमागत dma_data_direction dma_dir);
	व्योम		(*put_userptr)(व्योम *buf_priv);

	व्योम		(*prepare)(व्योम *buf_priv);
	व्योम		(*finish)(व्योम *buf_priv);

	व्योम		*(*attach_dmabuf)(काष्ठा device *dev,
					  काष्ठा dma_buf *dbuf,
					  अचिन्हित दीर्घ size,
					  क्रमागत dma_data_direction dma_dir);
	व्योम		(*detach_dmabuf)(व्योम *buf_priv);
	पूर्णांक		(*map_dmabuf)(व्योम *buf_priv);
	व्योम		(*unmap_dmabuf)(व्योम *buf_priv);

	व्योम		*(*vaddr)(व्योम *buf_priv);
	व्योम		*(*cookie)(व्योम *buf_priv);

	अचिन्हित पूर्णांक	(*num_users)(व्योम *buf_priv);

	पूर्णांक		(*mmap)(व्योम *buf_priv, काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

/**
 * काष्ठा vb2_plane - plane inक्रमmation.
 * @mem_priv:	निजी data with this plane.
 * @dbuf:	dma_buf - shared buffer object.
 * @dbuf_mapped:	flag to show whether dbuf is mapped or not
 * @bytesused:	number of bytes occupied by data in the plane (payload).
 * @length:	size of this plane (NOT the payload) in bytes. The maximum
 *		valid size is MAX_UINT - PAGE_SIZE.
 * @min_length:	minimum required size of this plane (NOT the payload) in bytes.
 *		@length is always greater or equal to @min_length, and like
 *		@length, it is limited to MAX_UINT - PAGE_SIZE.
 * @m:		Union with memtype-specअगरic data.
 * @m.offset:	when memory in the associated काष्ठा vb2_buffer is
 *		%VB2_MEMORY_MMAP, equals the offset from the start of
 *		the device memory क्रम this plane (or is a "cookie" that
 *		should be passed to mmap() called on the video node).
 * @m.userptr:	when memory is %VB2_MEMORY_USERPTR, a userspace poपूर्णांकer
 *		poपूर्णांकing to this plane.
 * @m.fd:	when memory is %VB2_MEMORY_DMABUF, a userspace file
 *		descriptor associated with this plane.
 * @data_offset:	offset in the plane to the start of data; usually 0,
 *		unless there is a header in front of the data.
 *
 * Should contain enough inक्रमmation to be able to cover all the fields
 * of &काष्ठा v4l2_plane at videodev2.h.
 */
काष्ठा vb2_plane अणु
	व्योम			*mem_priv;
	काष्ठा dma_buf		*dbuf;
	अचिन्हित पूर्णांक		dbuf_mapped;
	अचिन्हित पूर्णांक		bytesused;
	अचिन्हित पूर्णांक		length;
	अचिन्हित पूर्णांक		min_length;
	जोड़ अणु
		अचिन्हित पूर्णांक	offset;
		अचिन्हित दीर्घ	userptr;
		पूर्णांक		fd;
	पूर्ण m;
	अचिन्हित पूर्णांक		data_offset;
पूर्ण;

/**
 * क्रमागत vb2_io_modes - queue access methods.
 * @VB2_MMAP:		driver supports MMAP with streaming API.
 * @VB2_USERPTR:	driver supports USERPTR with streaming API.
 * @VB2_READ:		driver supports पढ़ो() style access.
 * @VB2_WRITE:		driver supports ग_लिखो() style access.
 * @VB2_DMABUF:		driver supports DMABUF with streaming API.
 */
क्रमागत vb2_io_modes अणु
	VB2_MMAP	= BIT(0),
	VB2_USERPTR	= BIT(1),
	VB2_READ	= BIT(2),
	VB2_WRITE	= BIT(3),
	VB2_DMABUF	= BIT(4),
पूर्ण;

/**
 * क्रमागत vb2_buffer_state - current video buffer state.
 * @VB2_BUF_STATE_DEQUEUED:	buffer under userspace control.
 * @VB2_BUF_STATE_IN_REQUEST:	buffer is queued in media request.
 * @VB2_BUF_STATE_PREPARING:	buffer is being prepared in videobuf.
 * @VB2_BUF_STATE_QUEUED:	buffer queued in videobuf, but not in driver.
 * @VB2_BUF_STATE_ACTIVE:	buffer queued in driver and possibly used
 *				in a hardware operation.
 * @VB2_BUF_STATE_DONE:		buffer वापसed from driver to videobuf, but
 *				not yet dequeued to userspace.
 * @VB2_BUF_STATE_ERROR:	same as above, but the operation on the buffer
 *				has ended with an error, which will be reported
 *				to the userspace when it is dequeued.
 */
क्रमागत vb2_buffer_state अणु
	VB2_BUF_STATE_DEQUEUED,
	VB2_BUF_STATE_IN_REQUEST,
	VB2_BUF_STATE_PREPARING,
	VB2_BUF_STATE_QUEUED,
	VB2_BUF_STATE_ACTIVE,
	VB2_BUF_STATE_DONE,
	VB2_BUF_STATE_ERROR,
पूर्ण;

काष्ठा vb2_queue;

/**
 * काष्ठा vb2_buffer - represents a video buffer.
 * @vb2_queue:		poपूर्णांकer to &काष्ठा vb2_queue with the queue to
 *			which this driver beदीर्घs.
 * @index:		id number of the buffer.
 * @type:		buffer type.
 * @memory:		the method, in which the actual data is passed.
 * @num_planes:		number of planes in the buffer
 *			on an पूर्णांकernal driver queue.
 * @बारtamp:		frame बारtamp in ns.
 * @request:		the request this buffer is associated with.
 * @req_obj:		used to bind this buffer to a request. This
 *			request object has a refcount.
 */
काष्ठा vb2_buffer अणु
	काष्ठा vb2_queue	*vb2_queue;
	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		type;
	अचिन्हित पूर्णांक		memory;
	अचिन्हित पूर्णांक		num_planes;
	u64			बारtamp;
	काष्ठा media_request	*request;
	काष्ठा media_request_object	req_obj;

	/* निजी: पूर्णांकernal use only
	 *
	 * state:		current buffer state; करो not change
	 * synced:		this buffer has been synced क्रम DMA, i.e. the
	 *			'prepare' memop was called. It is cleared again
	 *			after the 'finish' memop is called.
	 * prepared:		this buffer has been prepared, i.e. the
	 *			buf_prepare op was called. It is cleared again
	 *			after the 'buf_finish' op is called.
	 * copied_बारtamp:	the बारtamp of this capture buffer was copied
	 *			from an output buffer.
	 * need_cache_sync_on_prepare: when set buffer's ->prepare() function
	 *			perक्रमms cache sync/invalidation.
	 * need_cache_sync_on_finish: when set buffer's ->finish() function
	 *			perक्रमms cache sync/invalidation.
	 * queued_entry:	entry on the queued buffers list, which holds
	 *			all buffers queued from userspace
	 * करोne_entry:		entry on the list that stores all buffers पढ़ोy
	 *			to be dequeued to userspace
	 * vb2_plane:		per-plane inक्रमmation; करो not change
	 */
	क्रमागत vb2_buffer_state	state;
	अचिन्हित पूर्णांक		synced:1;
	अचिन्हित पूर्णांक		prepared:1;
	अचिन्हित पूर्णांक		copied_बारtamp:1;
	अचिन्हित पूर्णांक		need_cache_sync_on_prepare:1;
	अचिन्हित पूर्णांक		need_cache_sync_on_finish:1;

	काष्ठा vb2_plane	planes[VB2_MAX_PLANES];
	काष्ठा list_head	queued_entry;
	काष्ठा list_head	करोne_entry;
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Counters क्रम how often these buffer-related ops are
	 * called. Used to check क्रम unbalanced ops.
	 */
	u32		cnt_mem_alloc;
	u32		cnt_mem_put;
	u32		cnt_mem_get_dmabuf;
	u32		cnt_mem_get_userptr;
	u32		cnt_mem_put_userptr;
	u32		cnt_mem_prepare;
	u32		cnt_mem_finish;
	u32		cnt_mem_attach_dmabuf;
	u32		cnt_mem_detach_dmabuf;
	u32		cnt_mem_map_dmabuf;
	u32		cnt_mem_unmap_dmabuf;
	u32		cnt_mem_vaddr;
	u32		cnt_mem_cookie;
	u32		cnt_mem_num_users;
	u32		cnt_mem_mmap;

	u32		cnt_buf_out_validate;
	u32		cnt_buf_init;
	u32		cnt_buf_prepare;
	u32		cnt_buf_finish;
	u32		cnt_buf_cleanup;
	u32		cnt_buf_queue;
	u32		cnt_buf_request_complete;

	/* This counts the number of calls to vb2_buffer_करोne() */
	u32		cnt_buf_करोne;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा vb2_ops - driver-specअगरic callbacks.
 *
 * These operations are not called from पूर्णांकerrupt context except where
 * mentioned specअगरically.
 *
 * @queue_setup:	called from VIDIOC_REQBUFS() and VIDIOC_CREATE_BUFS()
 *			handlers beक्रमe memory allocation. It can be called
 *			twice: अगर the original number of requested buffers
 *			could not be allocated, then it will be called a
 *			second समय with the actually allocated number of
 *			buffers to verअगरy अगर that is OK.
 *			The driver should वापस the required number of buffers
 *			in \*num_buffers, the required number of planes per
 *			buffer in \*num_planes, the size of each plane should be
 *			set in the sizes\[\] array and optional per-plane
 *			allocator specअगरic device in the alloc_devs\[\] array.
 *			When called from VIDIOC_REQBUFS(), \*num_planes == 0,
 *			the driver has to use the currently configured क्रमmat to
 *			determine the plane sizes and \*num_buffers is the total
 *			number of buffers that are being allocated. When called
 *			from VIDIOC_CREATE_BUFS(), \*num_planes != 0 and it
 *			describes the requested number of planes and sizes\[\]
 *			contains the requested plane sizes. In this हाल
 *			\*num_buffers are being allocated additionally to
 *			q->num_buffers. If either \*num_planes or the requested
 *			sizes are invalid callback must वापस %-EINVAL.
 * @रुको_prepare:	release any locks taken जबतक calling vb2 functions;
 *			it is called beक्रमe an ioctl needs to रुको क्रम a new
 *			buffer to arrive; required to aव्योम a deadlock in
 *			blocking access type.
 * @रुको_finish:	reacquire all locks released in the previous callback;
 *			required to जारी operation after sleeping जबतक
 *			रुकोing क्रम a new buffer to arrive.
 * @buf_out_validate:	called when the output buffer is prepared or queued
 *			to a request; drivers can use this to validate
 *			userspace-provided inक्रमmation; this is required only
 *			क्रम OUTPUT queues.
 * @buf_init:		called once after allocating a buffer (in MMAP हाल)
 *			or after acquiring a new USERPTR buffer; drivers may
 *			perक्रमm additional buffer-related initialization;
 *			initialization failure (वापस != 0) will prevent
 *			queue setup from completing successfully; optional.
 * @buf_prepare:	called every समय the buffer is queued from userspace
 *			and from the VIDIOC_PREPARE_BUF() ioctl; drivers may
 *			perक्रमm any initialization required beक्रमe each
 *			hardware operation in this callback; drivers can
 *			access/modअगरy the buffer here as it is still synced क्रम
 *			the CPU; drivers that support VIDIOC_CREATE_BUFS() must
 *			also validate the buffer size; अगर an error is वापसed,
 *			the buffer will not be queued in driver; optional.
 * @buf_finish:		called beक्रमe every dequeue of the buffer back to
 *			userspace; the buffer is synced क्रम the CPU, so drivers
 *			can access/modअगरy the buffer contents; drivers may
 *			perक्रमm any operations required beक्रमe userspace
 *			accesses the buffer; optional. The buffer state can be
 *			one of the following: %DONE and %ERROR occur जबतक
 *			streaming is in progress, and the %PREPARED state occurs
 *			when the queue has been canceled and all pending
 *			buffers are being वापसed to their शेष %DEQUEUED
 *			state. Typically you only have to करो something अगर the
 *			state is %VB2_BUF_STATE_DONE, since in all other हालs
 *			the buffer contents will be ignored anyway.
 * @buf_cleanup:	called once beक्रमe the buffer is मुक्तd; drivers may
 *			perक्रमm any additional cleanup; optional.
 * @start_streaming:	called once to enter 'streaming' state; the driver may
 *			receive buffers with @buf_queue callback
 *			beक्रमe @start_streaming is called; the driver माला_लो the
 *			number of alपढ़ोy queued buffers in count parameter;
 *			driver can वापस an error अगर hardware fails, in that
 *			हाल all buffers that have been alपढ़ोy given by
 *			the @buf_queue callback are to be वापसed by the driver
 *			by calling vb2_buffer_करोne() with %VB2_BUF_STATE_QUEUED.
 *			If you need a minimum number of buffers beक्रमe you can
 *			start streaming, then set
 *			&vb2_queue->min_buffers_needed. If that is non-zero
 *			then @start_streaming won't be called until at least
 *			that many buffers have been queued up by userspace.
 * @stop_streaming:	called when 'streaming' state must be disabled; driver
 *			should stop any DMA transactions or रुको until they
 *			finish and give back all buffers it got from &buf_queue
 *			callback by calling vb2_buffer_करोne() with either
 *			%VB2_BUF_STATE_DONE or %VB2_BUF_STATE_ERROR; may use
 *			vb2_रुको_क्रम_all_buffers() function
 * @buf_queue:		passes buffer vb to the driver; driver may start
 *			hardware operation on this buffer; driver should give
 *			the buffer back by calling vb2_buffer_करोne() function;
 *			it is always called after calling VIDIOC_STREAMON()
 *			ioctl; might be called beक्रमe @start_streaming callback
 *			अगर user pre-queued buffers beक्रमe calling
 *			VIDIOC_STREAMON().
 * @buf_request_complete: a buffer that was never queued to the driver but is
 *			associated with a queued request was canceled.
 *			The driver will have to mark associated objects in the
 *			request as completed; required अगर requests are
 *			supported.
 */
काष्ठा vb2_ops अणु
	पूर्णांक (*queue_setup)(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[]);

	व्योम (*रुको_prepare)(काष्ठा vb2_queue *q);
	व्योम (*रुको_finish)(काष्ठा vb2_queue *q);

	पूर्णांक (*buf_out_validate)(काष्ठा vb2_buffer *vb);
	पूर्णांक (*buf_init)(काष्ठा vb2_buffer *vb);
	पूर्णांक (*buf_prepare)(काष्ठा vb2_buffer *vb);
	व्योम (*buf_finish)(काष्ठा vb2_buffer *vb);
	व्योम (*buf_cleanup)(काष्ठा vb2_buffer *vb);

	पूर्णांक (*start_streaming)(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count);
	व्योम (*stop_streaming)(काष्ठा vb2_queue *q);

	व्योम (*buf_queue)(काष्ठा vb2_buffer *vb);

	व्योम (*buf_request_complete)(काष्ठा vb2_buffer *vb);
पूर्ण;

/**
 * काष्ठा vb2_buf_ops - driver-specअगरic callbacks.
 *
 * @verअगरy_planes_array: Verअगरy that a given user space काष्ठाure contains
 *			enough planes क्रम the buffer. This is called
 *			क्रम each dequeued buffer.
 * @init_buffer:	given a &vb2_buffer initialize the extra data after
 *			काष्ठा vb2_buffer.
 *			For V4L2 this is a &काष्ठा vb2_v4l2_buffer.
 * @fill_user_buffer:	given a &vb2_buffer fill in the userspace काष्ठाure.
 *			For V4L2 this is a &काष्ठा v4l2_buffer.
 * @fill_vb2_buffer:	given a userspace काष्ठाure, fill in the &vb2_buffer.
 *			If the userspace काष्ठाure is invalid, then this op
 *			will वापस an error.
 * @copy_बारtamp:	copy the बारtamp from a userspace काष्ठाure to
 *			the &काष्ठा vb2_buffer.
 */
काष्ठा vb2_buf_ops अणु
	पूर्णांक (*verअगरy_planes_array)(काष्ठा vb2_buffer *vb, स्थिर व्योम *pb);
	व्योम (*init_buffer)(काष्ठा vb2_buffer *vb);
	व्योम (*fill_user_buffer)(काष्ठा vb2_buffer *vb, व्योम *pb);
	पूर्णांक (*fill_vb2_buffer)(काष्ठा vb2_buffer *vb, काष्ठा vb2_plane *planes);
	व्योम (*copy_बारtamp)(काष्ठा vb2_buffer *vb, स्थिर व्योम *pb);
पूर्ण;

/**
 * काष्ठा vb2_queue - a videobuf queue.
 *
 * @type:	निजी buffer type whose content is defined by the vb2-core
 *		caller. For example, क्रम V4L2, it should match
 *		the types defined on &क्रमागत v4l2_buf_type.
 * @io_modes:	supported io methods (see &क्रमागत vb2_io_modes).
 * @alloc_devs:	&काष्ठा device memory type/allocator-specअगरic per-plane device
 * @dev:	device to use क्रम the शेष allocation context अगर the driver
 *		करोesn't fill in the @alloc_devs array.
 * @dma_attrs:	DMA attributes to use क्रम the DMA.
 * @bidirectional: when this flag is set the DMA direction क्रम the buffers of
 *		this queue will be overridden with %DMA_BIसूचीECTIONAL direction.
 *		This is useful in हालs where the hardware (firmware) ग_लिखोs to
 *		a buffer which is mapped as पढ़ो (%DMA_TO_DEVICE), or पढ़ोs from
 *		buffer which is mapped क्रम ग_लिखो (%DMA_FROM_DEVICE) in order
 *		to satisfy some पूर्णांकernal hardware restrictions or adds a padding
 *		needed by the processing algorithm. In हाल the DMA mapping is
 *		not bidirectional but the hardware (firmware) trying to access
 *		the buffer (in the opposite direction) this could lead to an
 *		IOMMU protection faults.
 * @fileio_पढ़ो_once:		report खातापूर्ण after पढ़ोing the first buffer
 * @fileio_ग_लिखो_immediately:	queue buffer after each ग_लिखो() call
 * @allow_zero_bytesused:	allow bytesused == 0 to be passed to the driver
 * @quirk_poll_must_check_रुकोing_क्रम_buffers: Return %EPOLLERR at poll when QBUF
 *              has not been called. This is a vb1 idiom that has been aकरोpted
 *              also by vb2.
 * @supports_requests: this queue supports the Request API.
 * @requires_requests: this queue requires the Request API. If this is set to 1,
 *		then supports_requests must be set to 1 as well.
 * @uses_qbuf:	qbuf was used directly क्रम this queue. Set to 1 the first
 *		समय this is called. Set to 0 when the queue is canceled.
 *		If this is 1, then you cannot queue buffers from a request.
 * @uses_requests: requests are used क्रम this queue. Set to 1 the first समय
 *		a request is queued. Set to 0 when the queue is canceled.
 *		If this is 1, then you cannot queue buffers directly.
 * @allow_cache_hपूर्णांकs: when set user-space can pass cache management hपूर्णांकs in
 *		order to skip cache flush/invalidation on ->prepare() or/and
 *		->finish().
 * @lock:	poपूर्णांकer to a mutex that protects the &काष्ठा vb2_queue. The
 *		driver can set this to a mutex to let the v4l2 core serialize
 *		the queuing ioctls. If the driver wants to handle locking
 *		itself, then this should be set to शून्य. This lock is not used
 *		by the videobuf2 core API.
 * @owner:	The filehandle that 'owns' the buffers, i.e. the filehandle
 *		that called reqbufs, create_buffers or started fileio.
 *		This field is not used by the videobuf2 core API, but it allows
 *		drivers to easily associate an owner filehandle with the queue.
 * @ops:	driver-specअगरic callbacks
 * @mem_ops:	memory allocator specअगरic callbacks
 * @buf_ops:	callbacks to deliver buffer inक्रमmation.
 *		between user-space and kernel-space.
 * @drv_priv:	driver निजी data.
 * @subप्रणाली_flags: Flags specअगरic to the subप्रणाली (V4L2/DVB/etc.). Not used
 *		by the vb2 core.
 * @buf_काष्ठा_size: size of the driver-specअगरic buffer काष्ठाure;
 *		"0" indicates the driver करोesn't want to use a custom buffer
 *		काष्ठाure type. In that हाल a subप्रणाली-specअगरic काष्ठा
 *		will be used (in the हाल of V4L2 that is
 *		``माप(काष्ठा vb2_v4l2_buffer)``). The first field of the
 *		driver-specअगरic buffer काष्ठाure must be the subप्रणाली-specअगरic
 *		काष्ठा (vb2_v4l2_buffer in the हाल of V4L2).
 * @बारtamp_flags: Timestamp flags; ``V4L2_BUF_FLAG_TIMESTAMP_*`` and
 *		``V4L2_BUF_FLAG_TSTAMP_SRC_*``
 * @gfp_flags:	additional gfp flags used when allocating the buffers.
 *		Typically this is 0, but it may be e.g. %GFP_DMA or %__GFP_DMA32
 *		to क्रमce the buffer allocation to a specअगरic memory zone.
 * @min_buffers_needed: the minimum number of buffers needed beक्रमe
 *		@start_streaming can be called. Used when a DMA engine
 *		cannot be started unless at least this number of buffers
 *		have been queued पूर्णांकo the driver.
 */
/*
 * Private elements (won't appear at the uAPI book):
 * @mmap_lock:	निजी mutex used when buffers are allocated/मुक्तd/mmapped
 * @memory:	current memory type used
 * @dma_dir:	DMA mapping direction.
 * @bufs:	videobuf buffer काष्ठाures
 * @num_buffers: number of allocated/used buffers
 * @queued_list: list of buffers currently queued from userspace
 * @queued_count: number of buffers queued and पढ़ोy क्रम streaming.
 * @owned_by_drv_count: number of buffers owned by the driver
 * @करोne_list:	list of buffers पढ़ोy to be dequeued to userspace
 * @करोne_lock:	lock to protect करोne_list list
 * @करोne_wq:	रुकोqueue क्रम processes रुकोing क्रम buffers पढ़ोy to be dequeued
 * @streaming:	current streaming state
 * @start_streaming_called: @start_streaming was called successfully and we
 *		started streaming.
 * @error:	a fatal error occurred on the queue
 * @रुकोing_क्रम_buffers: used in poll() to check अगर vb2 is still रुकोing क्रम
 *		buffers. Only set क्रम capture queues अगर qbuf has not yet been
 *		called since poll() needs to वापस %EPOLLERR in that situation.
 * @is_multiplanar: set अगर buffer type is multiplanar
 * @is_output:	set अगर buffer type is output
 * @copy_बारtamp: set अगर vb2-core should set बारtamps
 * @last_buffer_dequeued: used in poll() and DQBUF to immediately वापस अगर the
 *		last decoded buffer was alपढ़ोy dequeued. Set क्रम capture queues
 *		when a buffer with the %V4L2_BUF_FLAG_LAST is dequeued.
 * @fileio:	file io emulator पूर्णांकernal data, used only अगर emulator is active
 * @thपढ़ोio:	thपढ़ो io पूर्णांकernal data, used only अगर thपढ़ो is active
 * @name:	queue name, used क्रम logging purpose. Initialized स्वतःmatically
 *		अगर left empty by drivers.
 */
काष्ठा vb2_queue अणु
	अचिन्हित पूर्णांक			type;
	अचिन्हित पूर्णांक			io_modes;
	काष्ठा device			*dev;
	अचिन्हित दीर्घ			dma_attrs;
	अचिन्हित पूर्णांक			bidirectional:1;
	अचिन्हित पूर्णांक			fileio_पढ़ो_once:1;
	अचिन्हित पूर्णांक			fileio_ग_लिखो_immediately:1;
	अचिन्हित पूर्णांक			allow_zero_bytesused:1;
	अचिन्हित पूर्णांक		   quirk_poll_must_check_रुकोing_क्रम_buffers:1;
	अचिन्हित पूर्णांक			supports_requests:1;
	अचिन्हित पूर्णांक			requires_requests:1;
	अचिन्हित पूर्णांक			uses_qbuf:1;
	अचिन्हित पूर्णांक			uses_requests:1;
	अचिन्हित पूर्णांक			allow_cache_hपूर्णांकs:1;

	काष्ठा mutex			*lock;
	व्योम				*owner;

	स्थिर काष्ठा vb2_ops		*ops;
	स्थिर काष्ठा vb2_mem_ops	*mem_ops;
	स्थिर काष्ठा vb2_buf_ops	*buf_ops;

	व्योम				*drv_priv;
	u32				subप्रणाली_flags;
	अचिन्हित पूर्णांक			buf_काष्ठा_size;
	u32				बारtamp_flags;
	gfp_t				gfp_flags;
	u32				min_buffers_needed;

	काष्ठा device			*alloc_devs[VB2_MAX_PLANES];

	/* निजी: पूर्णांकernal use only */
	काष्ठा mutex			mmap_lock;
	अचिन्हित पूर्णांक			memory;
	क्रमागत dma_data_direction		dma_dir;
	काष्ठा vb2_buffer		*bufs[VB2_MAX_FRAME];
	अचिन्हित पूर्णांक			num_buffers;

	काष्ठा list_head		queued_list;
	अचिन्हित पूर्णांक			queued_count;

	atomic_t			owned_by_drv_count;
	काष्ठा list_head		करोne_list;
	spinlock_t			करोne_lock;
	रुको_queue_head_t		करोne_wq;

	अचिन्हित पूर्णांक			streaming:1;
	अचिन्हित पूर्णांक			start_streaming_called:1;
	अचिन्हित पूर्णांक			error:1;
	अचिन्हित पूर्णांक			रुकोing_क्रम_buffers:1;
	अचिन्हित पूर्णांक			रुकोing_in_dqbuf:1;
	अचिन्हित पूर्णांक			is_multiplanar:1;
	अचिन्हित पूर्णांक			is_output:1;
	अचिन्हित पूर्णांक			copy_बारtamp:1;
	अचिन्हित पूर्णांक			last_buffer_dequeued:1;

	काष्ठा vb2_fileio_data		*fileio;
	काष्ठा vb2_thपढ़ोio_data	*thपढ़ोio;

	अक्षर				name[32];

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Counters क्रम how often these queue-related ops are
	 * called. Used to check क्रम unbalanced ops.
	 */
	u32				cnt_queue_setup;
	u32				cnt_रुको_prepare;
	u32				cnt_रुको_finish;
	u32				cnt_start_streaming;
	u32				cnt_stop_streaming;
#पूर्ण_अगर
पूर्ण;

/**
 * vb2_queue_allows_cache_hपूर्णांकs() - Return true अगर the queue allows cache
 * and memory consistency hपूर्णांकs.
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue
 */
अटल अंतरभूत bool vb2_queue_allows_cache_hपूर्णांकs(काष्ठा vb2_queue *q)
अणु
	वापस q->allow_cache_hपूर्णांकs && q->memory == VB2_MEMORY_MMAP;
पूर्ण

/**
 * vb2_plane_vaddr() - Return a kernel भव address of a given plane.
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to which the plane in
 *		question beदीर्घs to.
 * @plane_no:	plane number क्रम which the address is to be वापसed.
 *
 * This function वापसs a kernel भव address of a given plane अगर
 * such a mapping exist, शून्य otherwise.
 */
व्योम *vb2_plane_vaddr(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no);

/**
 * vb2_plane_cookie() - Return allocator specअगरic cookie क्रम the given plane.
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to which the plane in
 *		question beदीर्घs to.
 * @plane_no:	plane number क्रम which the cookie is to be वापसed.
 *
 * This function वापसs an allocator specअगरic cookie क्रम a given plane अगर
 * available, शून्य otherwise. The allocator should provide some simple अटल
 * अंतरभूत function, which would convert this cookie to the allocator specअगरic
 * type that can be used directly by the driver to access the buffer. This can
 * be क्रम example physical address, poपूर्णांकer to scatter list or IOMMU mapping.
 */
व्योम *vb2_plane_cookie(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no);

/**
 * vb2_buffer_करोne() - inक्रमm videobuf that an operation on a buffer
 *	is finished.
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to be used.
 * @state:	state of the buffer, as defined by &क्रमागत vb2_buffer_state.
 *		Either %VB2_BUF_STATE_DONE अगर the operation finished
 *		successfully, %VB2_BUF_STATE_ERROR अगर the operation finished
 *		with an error or %VB2_BUF_STATE_QUEUED.
 *
 * This function should be called by the driver after a hardware operation on
 * a buffer is finished and the buffer may be वापसed to userspace. The driver
 * cannot use this buffer anymore until it is queued back to it by videobuf
 * by the means of &vb2_ops->buf_queue callback. Only buffers previously queued
 * to the driver by &vb2_ops->buf_queue can be passed to this function.
 *
 * While streaming a buffer can only be वापसed in state DONE or ERROR.
 * The &vb2_ops->start_streaming op can also वापस them in हाल the DMA engine
 * cannot be started क्रम some reason. In that हाल the buffers should be
 * वापसed with state QUEUED to put them back पूर्णांकo the queue.
 */
व्योम vb2_buffer_करोne(काष्ठा vb2_buffer *vb, क्रमागत vb2_buffer_state state);

/**
 * vb2_discard_करोne() - discard all buffers marked as DONE.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This function is पूर्णांकended to be used with suspend/resume operations. It
 * discards all 'done' buffers as they would be too old to be requested after
 * resume.
 *
 * Drivers must stop the hardware and synchronize with पूर्णांकerrupt handlers and/or
 * delayed works beक्रमe calling this function to make sure no buffer will be
 * touched by the driver and/or hardware.
 */
व्योम vb2_discard_करोne(काष्ठा vb2_queue *q);

/**
 * vb2_रुको_क्रम_all_buffers() - रुको until all buffers are given back to vb2.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This function will रुको until all buffers that have been given to the driver
 * by &vb2_ops->buf_queue are given back to vb2 with vb2_buffer_करोne(). It
 * करोesn't call &vb2_ops->रुको_prepare/&vb2_ops->रुको_finish pair.
 * It is पूर्णांकended to be called with all locks taken, क्रम example from
 * &vb2_ops->stop_streaming callback.
 */
पूर्णांक vb2_रुको_क्रम_all_buffers(काष्ठा vb2_queue *q);

/**
 * vb2_core_querybuf() - query video buffer inक्रमmation.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @index:	id number of the buffer.
 * @pb:		buffer काष्ठा passed from userspace.
 *
 * Videobuf2 core helper to implement VIDIOC_QUERYBUF() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * The passed buffer should have been verअगरied.
 *
 * This function fills the relevant inक्रमmation क्रम the userspace.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
व्योम vb2_core_querybuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb);

/**
 * vb2_core_reqbufs() - Initiate streaming.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @memory:	memory type, as defined by &क्रमागत vb2_memory.
 * @count:	requested buffer count.
 *
 * Videobuf2 core helper to implement VIDIOC_REQBUF() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * This function:
 *
 * #) verअगरies streaming parameters passed from the userspace;
 * #) sets up the queue;
 * #) negotiates number of buffers and planes per buffer with the driver
 *    to be used during streaming;
 * #) allocates पूर्णांकernal buffer काष्ठाures (&काष्ठा vb2_buffer), according to
 *    the agreed parameters;
 * #) क्रम MMAP memory type, allocates actual video memory, using the
 *    memory handling/allocation routines provided during queue initialization.
 *
 * If req->count is 0, all the memory will be मुक्तd instead.
 *
 * If the queue has been allocated previously by a previous vb2_core_reqbufs()
 * call and the queue is not busy, memory will be पुनः_स्मृतिated.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_reqbufs(काष्ठा vb2_queue *q, क्रमागत vb2_memory memory,
		    अचिन्हित पूर्णांक *count);

/**
 * vb2_core_create_bufs() - Allocate buffers and any required auxiliary काष्ठाs
 * @q: poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @memory: memory type, as defined by &क्रमागत vb2_memory.
 * @count: requested buffer count.
 * @requested_planes: number of planes requested.
 * @requested_sizes: array with the size of the planes.
 *
 * Videobuf2 core helper to implement VIDIOC_CREATE_BUFS() operation. It is
 * called पूर्णांकernally by VB2 by an API-specअगरic handler, like
 * ``videobuf2-v4l2.h``.
 *
 * This function:
 *
 * #) verअगरies parameter sanity;
 * #) calls the &vb2_ops->queue_setup queue operation;
 * #) perक्रमms any necessary memory allocations.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_create_bufs(काष्ठा vb2_queue *q, क्रमागत vb2_memory memory,
			 अचिन्हित पूर्णांक *count,
			 अचिन्हित पूर्णांक requested_planes,
			 स्थिर अचिन्हित पूर्णांक requested_sizes[]);

/**
 * vb2_core_prepare_buf() - Pass ownership of a buffer from userspace
 *			to the kernel.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @index:	id number of the buffer.
 * @pb:		buffer काष्ठाure passed from userspace to
 *		&v4l2_ioctl_ops->vidioc_prepare_buf handler in driver.
 *
 * Videobuf2 core helper to implement VIDIOC_PREPARE_BUF() operation. It is
 * called पूर्णांकernally by VB2 by an API-specअगरic handler, like
 * ``videobuf2-v4l2.h``.
 *
 * The passed buffer should have been verअगरied.
 *
 * This function calls vb2_ops->buf_prepare callback in the driver
 * (अगर provided), in which driver-specअगरic buffer initialization can
 * be perक्रमmed.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_prepare_buf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb);

/**
 * vb2_core_qbuf() - Queue a buffer from userspace
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @index:	id number of the buffer
 * @pb:		buffer काष्ठाure passed from userspace to
 *		v4l2_ioctl_ops->vidioc_qbuf handler in driver
 * @req:	poपूर्णांकer to &काष्ठा media_request, may be शून्य.
 *
 * Videobuf2 core helper to implement VIDIOC_QBUF() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * This function:
 *
 * #) If @req is non-शून्य, then the buffer will be bound to this
 *    media request and it वापसs. The buffer will be prepared and
 *    queued to the driver (i.e. the next two steps) when the request
 *    itself is queued.
 * #) अगर necessary, calls &vb2_ops->buf_prepare callback in the driver
 *    (अगर provided), in which driver-specअगरic buffer initialization can
 *    be perक्रमmed;
 * #) अगर streaming is on, queues the buffer in driver by the means of
 *    &vb2_ops->buf_queue callback क्रम processing.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_qbuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb,
		  काष्ठा media_request *req);

/**
 * vb2_core_dqbuf() - Dequeue a buffer to the userspace
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue
 * @pindex:	poपूर्णांकer to the buffer index. May be शून्य
 * @pb:		buffer काष्ठाure passed from userspace to
 *		v4l2_ioctl_ops->vidioc_dqbuf handler in driver.
 * @nonblocking: अगर true, this call will not sleep रुकोing क्रम a buffer अगर no
 *		 buffers पढ़ोy क्रम dequeuing are present. Normally the driver
 *		 would be passing (file->f_flags & O_NONBLOCK) here.
 *
 * Videobuf2 core helper to implement VIDIOC_DQBUF() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * This function:
 *
 * #) calls buf_finish callback in the driver (अगर provided), in which
 *    driver can perक्रमm any additional operations that may be required beक्रमe
 *    वापसing the buffer to userspace, such as cache sync,
 * #) the buffer काष्ठा members are filled with relevant inक्रमmation क्रम
 *    the userspace.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_dqbuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक *pindex, व्योम *pb,
		   bool nonblocking);

/**
 * vb2_core_streamon() - Implements VB2 stream ON logic
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue
 * @type:	type of the queue to be started.
 *		For V4L2, this is defined by &क्रमागत v4l2_buf_type type.
 *
 * Videobuf2 core helper to implement VIDIOC_STREAMON() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_streamon(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक type);

/**
 * vb2_core_streamoff() - Implements VB2 stream OFF logic
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue
 * @type:	type of the queue to be started.
 *		For V4L2, this is defined by &क्रमागत v4l2_buf_type type.
 *
 * Videobuf2 core helper to implement VIDIOC_STREAMOFF() operation. It is
 * called पूर्णांकernally by VB2 by an API-specअगरic handler, like
 * ``videobuf2-v4l2.h``.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_streamoff(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक type);

/**
 * vb2_core_expbuf() - Export a buffer as a file descriptor.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @fd:		poपूर्णांकer to the file descriptor associated with DMABUF
 *		(set by driver).
 * @type:	buffer type.
 * @index:	id number of the buffer.
 * @plane:	index of the plane to be exported, 0 क्रम single plane queues
 * @flags:	file flags क्रम newly created file, as defined at
 *		include/uapi/यंत्र-generic/fcntl.h.
 *		Currently, the only used flag is %O_CLOEXEC.
 *		is supported, refer to manual of खोलो syscall क्रम more details.
 *
 *
 * Videobuf2 core helper to implement VIDIOC_EXPBUF() operation. It is called
 * पूर्णांकernally by VB2 by an API-specअगरic handler, like ``videobuf2-v4l2.h``.
 *
 * Return: वापसs zero on success; an error code otherwise.
 */
पूर्णांक vb2_core_expbuf(काष्ठा vb2_queue *q, पूर्णांक *fd, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक plane, अचिन्हित पूर्णांक flags);

/**
 * vb2_core_queue_init() - initialize a videobuf2 queue
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *		This काष्ठाure should be allocated in driver
 *
 * The &vb2_queue काष्ठाure should be allocated by the driver. The driver is
 * responsible of clearing it's content and setting initial values क्रम some
 * required entries beक्रमe calling this function.
 *
 * .. note::
 *
 *    The following fields at @q should be set beक्रमe calling this function:
 *    &vb2_queue->ops, &vb2_queue->mem_ops, &vb2_queue->type.
 */
पूर्णांक vb2_core_queue_init(काष्ठा vb2_queue *q);

/**
 * vb2_core_queue_release() - stop streaming, release the queue and मुक्त memory
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This function stops streaming and perक्रमms necessary clean ups, including
 * मुक्तing video buffer memory. The driver is responsible क्रम मुक्तing
 * the &काष्ठा vb2_queue itself.
 */
व्योम vb2_core_queue_release(काष्ठा vb2_queue *q);

/**
 * vb2_queue_error() - संकेत a fatal error on the queue
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * Flag that a fatal unrecoverable error has occurred and wake up all processes
 * रुकोing on the queue. Polling will now set %EPOLLERR and queuing and dequeuing
 * buffers will वापस %-EIO.
 *
 * The error flag will be cleared when canceling the queue, either from
 * vb2_streamoff() or vb2_queue_release(). Drivers should thus not call this
 * function beक्रमe starting the stream, otherwise the error flag will reमुख्य set
 * until the queue is released when closing the device node.
 */
व्योम vb2_queue_error(काष्ठा vb2_queue *q);

/**
 * vb2_mmap() - map video buffers पूर्णांकo application address space.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @vma:	poपूर्णांकer to &काष्ठा vm_area_काष्ठा with the vma passed
 *		to the mmap file operation handler in the driver.
 *
 * Should be called from mmap file operation handler of a driver.
 * This function maps one plane of one of the available video buffers to
 * userspace. To map whole video memory allocated on reqbufs, this function
 * has to be called once per each plane per each buffer previously allocated.
 *
 * When the userspace application calls mmap, it passes to it an offset वापसed
 * to it earlier by the means of &v4l2_ioctl_ops->vidioc_querybuf handler.
 * That offset acts as a "cookie", which is then used to identअगरy the plane
 * to be mapped.
 *
 * This function finds a plane with a matching offset and a mapping is perक्रमmed
 * by the means of a provided memory operation.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from the mmap handler in driver.
 */
पूर्णांक vb2_mmap(काष्ठा vb2_queue *q, काष्ठा vm_area_काष्ठा *vma);

#अगर_अघोषित CONFIG_MMU
/**
 * vb2_get_unmapped_area - map video buffers पूर्णांकo application address space.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @addr:	memory address.
 * @len:	buffer size.
 * @pgoff:	page offset.
 * @flags:	memory flags.
 *
 * This function is used in noMMU platक्रमms to propose address mapping
 * क्रम a given buffer. It's पूर्णांकended to be used as a handler क्रम the
 * &file_operations->get_unmapped_area operation.
 *
 * This is called by the mmap() syscall routines will call this
 * to get a proposed address क्रम the mapping, when ``!CONFIG_MMU``.
 */
अचिन्हित दीर्घ vb2_get_unmapped_area(काष्ठा vb2_queue *q,
				    अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ pgoff,
				    अचिन्हित दीर्घ flags);
#पूर्ण_अगर

/**
 * vb2_core_poll() - implements poll syscall() logic.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @file:	&काष्ठा file argument passed to the poll
 *		file operation handler.
 * @रुको:	&poll_table रुको argument passed to the poll
 *		file operation handler.
 *
 * This function implements poll file operation handler क्रम a driver.
 * For CAPTURE queues, अगर a buffer is पढ़ोy to be dequeued, the userspace will
 * be inक्रमmed that the file descriptor of a video device is available क्रम
 * पढ़ोing.
 * For OUTPUT queues, अगर a buffer is पढ़ोy to be dequeued, the file descriptor
 * will be reported as available क्रम writing.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from poll handler in driver.
 */
__poll_t vb2_core_poll(काष्ठा vb2_queue *q, काष्ठा file *file,
			   poll_table *रुको);

/**
 * vb2_पढ़ो() - implements पढ़ो() syscall logic.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @data:	poपूर्णांकed to target userspace buffer
 * @count:	number of bytes to पढ़ो
 * @ppos:	file handle position tracking poपूर्णांकer
 * @nonblock:	mode selector (1 means blocking calls, 0 means nonblocking)
 */
माप_प्रकार vb2_पढ़ो(काष्ठा vb2_queue *q, अक्षर __user *data, माप_प्रकार count,
		loff_t *ppos, पूर्णांक nonblock);
/**
 * vb2_ग_लिखो() - implements ग_लिखो() syscall logic.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @data:	poपूर्णांकed to target userspace buffer
 * @count:	number of bytes to ग_लिखो
 * @ppos:	file handle position tracking poपूर्णांकer
 * @nonblock:	mode selector (1 means blocking calls, 0 means nonblocking)
 */
माप_प्रकार vb2_ग_लिखो(काष्ठा vb2_queue *q, स्थिर अक्षर __user *data, माप_प्रकार count,
		loff_t *ppos, पूर्णांक nonblock);

/**
 * प्रकार vb2_thपढ़ो_fnc - callback function क्रम use with vb2_thपढ़ो.
 *
 * @vb: poपूर्णांकer to काष्ठा &vb2_buffer.
 * @priv: poपूर्णांकer to a निजी data.
 *
 * This is called whenever a buffer is dequeued in the thपढ़ो.
 */
प्रकार पूर्णांक (*vb2_thपढ़ो_fnc)(काष्ठा vb2_buffer *vb, व्योम *priv);

/**
 * vb2_thपढ़ो_start() - start a thपढ़ो क्रम the given queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @fnc:	&vb2_thपढ़ो_fnc callback function.
 * @priv:	priv poपूर्णांकer passed to the callback function.
 * @thपढ़ो_name:the name of the thपढ़ो. This will be prefixed with "vb2-".
 *
 * This starts a thपढ़ो that will queue and dequeue until an error occurs
 * or vb2_thपढ़ो_stop() is called.
 *
 * .. attention::
 *
 *   This function should not be used क्रम anything अन्यथा but the videobuf2-dvb
 *   support. If you think you have another good use-हाल क्रम this, then please
 *   contact the linux-media mailing list first.
 */
पूर्णांक vb2_thपढ़ो_start(काष्ठा vb2_queue *q, vb2_thपढ़ो_fnc fnc, व्योम *priv,
		     स्थिर अक्षर *thपढ़ो_name);

/**
 * vb2_thपढ़ो_stop() - stop the thपढ़ो क्रम the given queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
पूर्णांक vb2_thपढ़ो_stop(काष्ठा vb2_queue *q);

/**
 * vb2_is_streaming() - वापस streaming status of the queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
अटल अंतरभूत bool vb2_is_streaming(काष्ठा vb2_queue *q)
अणु
	वापस q->streaming;
पूर्ण

/**
 * vb2_fileio_is_active() - वापस true अगर fileio is active.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This वापसs true अगर पढ़ो() or ग_लिखो() is used to stream the data
 * as opposed to stream I/O. This is almost never an important distinction,
 * except in rare हालs. One such हाल is that using पढ़ो() or ग_लिखो() to
 * stream a क्रमmat using %V4L2_FIELD_ALTERNATE is not allowed since there
 * is no way you can pass the field inक्रमmation of each buffer to/from
 * userspace. A driver that supports this field क्रमmat should check क्रम
 * this in the &vb2_ops->queue_setup op and reject it अगर this function वापसs
 * true.
 */
अटल अंतरभूत bool vb2_fileio_is_active(काष्ठा vb2_queue *q)
अणु
	वापस q->fileio;
पूर्ण

/**
 * vb2_is_busy() - वापस busy status of the queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 *
 * This function checks अगर queue has any buffers allocated.
 */
अटल अंतरभूत bool vb2_is_busy(काष्ठा vb2_queue *q)
अणु
	वापस (q->num_buffers > 0);
पूर्ण

/**
 * vb2_get_drv_priv() - वापस driver निजी data associated with the queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
अटल अंतरभूत व्योम *vb2_get_drv_priv(काष्ठा vb2_queue *q)
अणु
	वापस q->drv_priv;
पूर्ण

/**
 * vb2_set_plane_payload() - set bytesused क्रम the plane @plane_no.
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to which the plane in
 *		question beदीर्घs to.
 * @plane_no:	plane number क्रम which payload should be set.
 * @size:	payload in bytes.
 */
अटल अंतरभूत व्योम vb2_set_plane_payload(काष्ठा vb2_buffer *vb,
				 अचिन्हित पूर्णांक plane_no, अचिन्हित दीर्घ size)
अणु
	अगर (plane_no < vb->num_planes)
		vb->planes[plane_no].bytesused = size;
पूर्ण

/**
 * vb2_get_plane_payload() - get bytesused क्रम the plane plane_no
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to which the plane in
 *		question beदीर्घs to.
 * @plane_no:	plane number क्रम which payload should be set.
 */
अटल अंतरभूत अचिन्हित दीर्घ vb2_get_plane_payload(काष्ठा vb2_buffer *vb,
				 अचिन्हित पूर्णांक plane_no)
अणु
	अगर (plane_no < vb->num_planes)
		वापस vb->planes[plane_no].bytesused;
	वापस 0;
पूर्ण

/**
 * vb2_plane_size() - वापस plane size in bytes.
 * @vb:		poपूर्णांकer to &काष्ठा vb2_buffer to which the plane in
 *		question beदीर्घs to.
 * @plane_no:	plane number क्रम which size should be वापसed.
 */
अटल अंतरभूत अचिन्हित दीर्घ
vb2_plane_size(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no)
अणु
	अगर (plane_no < vb->num_planes)
		वापस vb->planes[plane_no].length;
	वापस 0;
पूर्ण

/**
 * vb2_start_streaming_called() - वापस streaming status of driver.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
अटल अंतरभूत bool vb2_start_streaming_called(काष्ठा vb2_queue *q)
अणु
	वापस q->start_streaming_called;
पूर्ण

/**
 * vb2_clear_last_buffer_dequeued() - clear last buffer dequeued flag of queue.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
अटल अंतरभूत व्योम vb2_clear_last_buffer_dequeued(काष्ठा vb2_queue *q)
अणु
	q->last_buffer_dequeued = false;
पूर्ण

/**
 * vb2_get_buffer() - get a buffer from a queue
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @index:	buffer index
 *
 * This function obtains a buffer from a queue, by its index.
 * Keep in mind that there is no refcounting involved in this
 * operation, so the buffer lअगरeसमय should be taken पूर्णांकo
 * consideration.
 */
अटल अंतरभूत काष्ठा vb2_buffer *vb2_get_buffer(काष्ठा vb2_queue *q,
						अचिन्हित पूर्णांक index)
अणु
	अगर (index < q->num_buffers)
		वापस q->bufs[index];
	वापस शून्य;
पूर्ण

/*
 * The following functions are not part of the vb2 core API, but are useful
 * functions क्रम videobuf2-*.
 */

/**
 * vb2_buffer_in_use() - वापस true अगर the buffer is in use and
 * the queue cannot be मुक्तd (by the means of VIDIOC_REQBUFS(0)) call.
 *
 * @vb:		buffer क्रम which plane size should be वापसed.
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 */
bool vb2_buffer_in_use(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb);

/**
 * vb2_verअगरy_memory_type() - Check whether the memory type and buffer type
 * passed to a buffer operation are compatible with the queue.
 *
 * @q:		poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @memory:	memory model, as defined by क्रमागत &vb2_memory.
 * @type:	निजी buffer type whose content is defined by the vb2-core
 *		caller. For example, क्रम V4L2, it should match
 *		the types defined on क्रमागत &v4l2_buf_type.
 */
पूर्णांक vb2_verअगरy_memory_type(काष्ठा vb2_queue *q,
		क्रमागत vb2_memory memory, अचिन्हित पूर्णांक type);

/**
 * vb2_request_object_is_buffer() - वापस true अगर the object is a buffer
 *
 * @obj:	the request object.
 */
bool vb2_request_object_is_buffer(काष्ठा media_request_object *obj);

/**
 * vb2_request_buffer_cnt() - वापस the number of buffers in the request
 *
 * @req:	the request.
 */
अचिन्हित पूर्णांक vb2_request_buffer_cnt(काष्ठा media_request *req);

#पूर्ण_अगर /* _MEDIA_VIDEOBUF2_CORE_H */
