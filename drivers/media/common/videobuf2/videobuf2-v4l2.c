<शैली गुरु>
/*
 * videobuf2-v4l2.c - V4L2 driver helper framework
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *	   Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * The vb2_thपढ़ो implementation was based on code from videobuf-dvb.c:
 *	(c) 2004 Gerd Knorr <kraxel@bytesex.org> [SUSE Lअसल]
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>

#समावेश <media/videobuf2-v4l2.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा dprपूर्णांकk(q, level, fmt, arg...)					      \
	करो अणु								      \
		अगर (debug >= level)					      \
			pr_info("vb2-v4l2: [%p] %s: " fmt,		      \
				(q)->name, __func__, ## arg);		      \
	पूर्ण जबतक (0)

/* Flags that are set by us */
#घोषणा V4L2_BUFFER_MASK_FLAGS	(V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_QUEUED | \
				 V4L2_BUF_FLAG_DONE | V4L2_BUF_FLAG_ERROR | \
				 V4L2_BUF_FLAG_PREPARED | \
				 V4L2_BUF_FLAG_IN_REQUEST | \
				 V4L2_BUF_FLAG_REQUEST_FD | \
				 V4L2_BUF_FLAG_TIMESTAMP_MASK)
/* Output buffer flags that should be passed on to the driver */
#घोषणा V4L2_BUFFER_OUT_FLAGS	(V4L2_BUF_FLAG_PFRAME | \
				 V4L2_BUF_FLAG_BFRAME | \
				 V4L2_BUF_FLAG_KEYFRAME | \
				 V4L2_BUF_FLAG_TIMECODE | \
				 V4L2_BUF_FLAG_M2M_HOLD_CAPTURE_BUF)

/*
 * __verअगरy_planes_array() - verअगरy that the planes array passed in काष्ठा
 * v4l2_buffer from userspace can be safely used
 */
अटल पूर्णांक __verअगरy_planes_array(काष्ठा vb2_buffer *vb, स्थिर काष्ठा v4l2_buffer *b)
अणु
	अगर (!V4L2_TYPE_IS_MULTIPLANAR(b->type))
		वापस 0;

	/* Is memory क्रम copying plane inक्रमmation present? */
	अगर (b->m.planes == शून्य) अणु
		dprपूर्णांकk(vb->vb2_queue, 1,
			"multi-planar buffer passed but planes array not provided\n");
		वापस -EINVAL;
	पूर्ण

	अगर (b->length < vb->num_planes || b->length > VB2_MAX_PLANES) अणु
		dprपूर्णांकk(vb->vb2_queue, 1,
			"incorrect planes array length, expected %d, got %d\n",
			vb->num_planes, b->length);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __verअगरy_planes_array_core(काष्ठा vb2_buffer *vb, स्थिर व्योम *pb)
अणु
	वापस __verअगरy_planes_array(vb, pb);
पूर्ण

/*
 * __verअगरy_length() - Verअगरy that the bytesused value क्रम each plane fits in
 * the plane length and that the data offset करोesn't exceed the bytesused value.
 */
अटल पूर्णांक __verअगरy_length(काष्ठा vb2_buffer *vb, स्थिर काष्ठा v4l2_buffer *b)
अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक bytesused;
	अचिन्हित पूर्णांक plane;

	अगर (V4L2_TYPE_IS_CAPTURE(b->type))
		वापस 0;

	अगर (V4L2_TYPE_IS_MULTIPLANAR(b->type)) अणु
		क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
			length = (b->memory == VB2_MEMORY_USERPTR ||
				  b->memory == VB2_MEMORY_DMABUF)
			       ? b->m.planes[plane].length
				: vb->planes[plane].length;
			bytesused = b->m.planes[plane].bytesused
				  ? b->m.planes[plane].bytesused : length;

			अगर (b->m.planes[plane].bytesused > length)
				वापस -EINVAL;

			अगर (b->m.planes[plane].data_offset > 0 &&
			    b->m.planes[plane].data_offset >= bytesused)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		length = (b->memory == VB2_MEMORY_USERPTR)
			? b->length : vb->planes[0].length;

		अगर (b->bytesused > length)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * __init_vb2_v4l2_buffer() - initialize the vb2_v4l2_buffer काष्ठा
 */
अटल व्योम __init_vb2_v4l2_buffer(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->request_fd = -1;
पूर्ण

अटल व्योम __copy_बारtamp(काष्ठा vb2_buffer *vb, स्थिर व्योम *pb)
अणु
	स्थिर काष्ठा v4l2_buffer *b = pb;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *q = vb->vb2_queue;

	अगर (q->is_output) अणु
		/*
		 * For output buffers copy the बारtamp अगर needed,
		 * and the समयcode field and flag अगर needed.
		 */
		अगर (q->copy_बारtamp)
			vb->बारtamp = v4l2_buffer_get_बारtamp(b);
		vbuf->flags |= b->flags & V4L2_BUF_FLAG_TIMECODE;
		अगर (b->flags & V4L2_BUF_FLAG_TIMECODE)
			vbuf->समयcode = b->समयcode;
	पूर्ण
पूर्ण;

अटल व्योम vb2_warn_zero_bytesused(काष्ठा vb2_buffer *vb)
अणु
	अटल bool check_once;

	अगर (check_once)
		वापस;

	check_once = true;

	pr_warn("use of bytesused == 0 is deprecated and will be removed in the future,\n");
	अगर (vb->vb2_queue->allow_zero_bytesused)
		pr_warn("use VIDIOC_DECODER_CMD(V4L2_DEC_CMD_STOP) instead.\n");
	अन्यथा
		pr_warn("use the actual size instead.\n");
पूर्ण

अटल पूर्णांक vb2_fill_vb2_v4l2_buffer(काष्ठा vb2_buffer *vb, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_plane *planes = vbuf->planes;
	अचिन्हित पूर्णांक plane;
	पूर्णांक ret;

	ret = __verअगरy_length(vb, b);
	अगर (ret < 0) अणु
		dprपूर्णांकk(q, 1, "plane parameters verification failed: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (b->field == V4L2_FIELD_ALTERNATE && q->is_output) अणु
		/*
		 * If the क्रमmat's field is ALTERNATE, then the buffer's field
		 * should be either TOP or BOTTOM, not ALTERNATE since that
		 * makes no sense. The driver has to know whether the
		 * buffer represents a top or a bottom field in order to
		 * program any DMA correctly. Using ALTERNATE is wrong, since
		 * that just says that it is either a top or a bottom field,
		 * but not which of the two it is.
		 */
		dprपूर्णांकk(q, 1, "the field is incorrectly set to ALTERNATE for an output buffer\n");
		वापस -EINVAL;
	पूर्ण
	vbuf->sequence = 0;
	vbuf->request_fd = -1;
	vbuf->is_held = false;

	अगर (V4L2_TYPE_IS_MULTIPLANAR(b->type)) अणु
		चयन (b->memory) अणु
		हाल VB2_MEMORY_USERPTR:
			क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
				planes[plane].m.userptr =
					b->m.planes[plane].m.userptr;
				planes[plane].length =
					b->m.planes[plane].length;
			पूर्ण
			अवरोध;
		हाल VB2_MEMORY_DMABUF:
			क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
				planes[plane].m.fd =
					b->m.planes[plane].m.fd;
				planes[plane].length =
					b->m.planes[plane].length;
			पूर्ण
			अवरोध;
		शेष:
			क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
				planes[plane].m.offset =
					vb->planes[plane].m.offset;
				planes[plane].length =
					vb->planes[plane].length;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Fill in driver-provided inक्रमmation क्रम OUTPUT types */
		अगर (V4L2_TYPE_IS_OUTPUT(b->type)) अणु
			/*
			 * Will have to go up to b->length when API starts
			 * accepting variable number of planes.
			 *
			 * If bytesused == 0 क्रम the output buffer, then fall
			 * back to the full buffer size. In that हाल
			 * userspace clearly never bothered to set it and
			 * it's a safe assumption that they really meant to
			 * use the full plane sizes.
			 *
			 * Some drivers, e.g. old codec drivers, use bytesused == 0
			 * as a way to indicate that streaming is finished.
			 * In that हाल, the driver should use the
			 * allow_zero_bytesused flag to keep old userspace
			 * applications working.
			 */
			क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
				काष्ठा vb2_plane *pdst = &planes[plane];
				काष्ठा v4l2_plane *psrc = &b->m.planes[plane];

				अगर (psrc->bytesused == 0)
					vb2_warn_zero_bytesused(vb);

				अगर (vb->vb2_queue->allow_zero_bytesused)
					pdst->bytesused = psrc->bytesused;
				अन्यथा
					pdst->bytesused = psrc->bytesused ?
						psrc->bytesused : pdst->length;
				pdst->data_offset = psrc->data_offset;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Single-planar buffers करो not use planes array,
		 * so fill in relevant v4l2_buffer काष्ठा fields instead.
		 * In videobuf we use our पूर्णांकernal V4l2_planes काष्ठा क्रम
		 * single-planar buffers as well, क्रम simplicity.
		 *
		 * If bytesused == 0 क्रम the output buffer, then fall back
		 * to the full buffer size as that's a sensible शेष.
		 *
		 * Some drivers, e.g. old codec drivers, use bytesused == 0 as
		 * a way to indicate that streaming is finished. In that हाल,
		 * the driver should use the allow_zero_bytesused flag to keep
		 * old userspace applications working.
		 */
		चयन (b->memory) अणु
		हाल VB2_MEMORY_USERPTR:
			planes[0].m.userptr = b->m.userptr;
			planes[0].length = b->length;
			अवरोध;
		हाल VB2_MEMORY_DMABUF:
			planes[0].m.fd = b->m.fd;
			planes[0].length = b->length;
			अवरोध;
		शेष:
			planes[0].m.offset = vb->planes[0].m.offset;
			planes[0].length = vb->planes[0].length;
			अवरोध;
		पूर्ण

		planes[0].data_offset = 0;
		अगर (V4L2_TYPE_IS_OUTPUT(b->type)) अणु
			अगर (b->bytesused == 0)
				vb2_warn_zero_bytesused(vb);

			अगर (vb->vb2_queue->allow_zero_bytesused)
				planes[0].bytesused = b->bytesused;
			अन्यथा
				planes[0].bytesused = b->bytesused ?
					b->bytesused : planes[0].length;
		पूर्ण अन्यथा
			planes[0].bytesused = 0;

	पूर्ण

	/* Zero flags that we handle */
	vbuf->flags = b->flags & ~V4L2_BUFFER_MASK_FLAGS;
	अगर (!vb->vb2_queue->copy_बारtamp || V4L2_TYPE_IS_CAPTURE(b->type)) अणु
		/*
		 * Non-COPY बारtamps and non-OUTPUT queues will get
		 * their बारtamp and बारtamp source flags from the
		 * queue.
		 */
		vbuf->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	पूर्ण

	अगर (V4L2_TYPE_IS_OUTPUT(b->type)) अणु
		/*
		 * For output buffers mask out the समयcode flag:
		 * this will be handled later in vb2_qbuf().
		 * The 'field' is valid metadata क्रम this output buffer
		 * and so that needs to be copied here.
		 */
		vbuf->flags &= ~V4L2_BUF_FLAG_TIMECODE;
		vbuf->field = b->field;
		अगर (!(q->subप्रणाली_flags & VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF))
			vbuf->flags &= ~V4L2_BUF_FLAG_M2M_HOLD_CAPTURE_BUF;
	पूर्ण अन्यथा अणु
		/* Zero any output buffer flags as this is a capture buffer */
		vbuf->flags &= ~V4L2_BUFFER_OUT_FLAGS;
		/* Zero last flag, this is a संकेत from driver to userspace */
		vbuf->flags &= ~V4L2_BUF_FLAG_LAST;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_buffer_cache_hपूर्णांकs(काष्ठा vb2_queue *q,
				   काष्ठा vb2_buffer *vb,
				   काष्ठा v4l2_buffer *b)
अणु
	/*
	 * DMA exporter should take care of cache syncs, so we can aव्योम
	 * explicit ->prepare()/->finish() syncs. For other ->memory types
	 * we always need ->prepare() or/and ->finish() cache sync.
	 */
	अगर (q->memory == VB2_MEMORY_DMABUF) अणु
		vb->need_cache_sync_on_finish = 0;
		vb->need_cache_sync_on_prepare = 0;
		वापस;
	पूर्ण

	/*
	 * Cache sync/invalidation flags are set by शेष in order to
	 * preserve existing behaviour क्रम old apps/drivers.
	 */
	vb->need_cache_sync_on_prepare = 1;
	vb->need_cache_sync_on_finish = 1;

	अगर (!vb2_queue_allows_cache_hपूर्णांकs(q)) अणु
		/*
		 * Clear buffer cache flags अगर queue करोes not support user
		 * space hपूर्णांकs. That's to indicate to userspace that these
		 * flags won't work.
		 */
		b->flags &= ~V4L2_BUF_FLAG_NO_CACHE_INVALIDATE;
		b->flags &= ~V4L2_BUF_FLAG_NO_CACHE_CLEAN;
		वापस;
	पूर्ण

	/*
	 * ->finish() cache sync can be aव्योमed when queue direction is
	 * TO_DEVICE.
	 */
	अगर (q->dma_dir == DMA_TO_DEVICE)
		vb->need_cache_sync_on_finish = 0;

	अगर (b->flags & V4L2_BUF_FLAG_NO_CACHE_INVALIDATE)
		vb->need_cache_sync_on_finish = 0;

	अगर (b->flags & V4L2_BUF_FLAG_NO_CACHE_CLEAN)
		vb->need_cache_sync_on_prepare = 0;
पूर्ण

अटल पूर्णांक vb2_queue_or_prepare_buf(काष्ठा vb2_queue *q, काष्ठा media_device *mdev,
				    काष्ठा v4l2_buffer *b, bool is_prepare,
				    काष्ठा media_request **p_req)
अणु
	स्थिर अक्षर *opname = is_prepare ? "prepare_buf" : "qbuf";
	काष्ठा media_request *req;
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	अगर (b->type != q->type) अणु
		dprपूर्णांकk(q, 1, "%s: invalid buffer type\n", opname);
		वापस -EINVAL;
	पूर्ण

	अगर (b->index >= q->num_buffers) अणु
		dprपूर्णांकk(q, 1, "%s: buffer index out of range\n", opname);
		वापस -EINVAL;
	पूर्ण

	अगर (q->bufs[b->index] == शून्य) अणु
		/* Should never happen */
		dprपूर्णांकk(q, 1, "%s: buffer is NULL\n", opname);
		वापस -EINVAL;
	पूर्ण

	अगर (b->memory != q->memory) अणु
		dprपूर्णांकk(q, 1, "%s: invalid memory type\n", opname);
		वापस -EINVAL;
	पूर्ण

	vb = q->bufs[b->index];
	vbuf = to_vb2_v4l2_buffer(vb);
	ret = __verअगरy_planes_array(vb, b);
	अगर (ret)
		वापस ret;

	अगर (!is_prepare && (b->flags & V4L2_BUF_FLAG_REQUEST_FD) &&
	    vb->state != VB2_BUF_STATE_DEQUEUED) अणु
		dprपूर्णांकk(q, 1, "%s: buffer is not in dequeued state\n", opname);
		वापस -EINVAL;
	पूर्ण

	अगर (!vb->prepared) अणु
		set_buffer_cache_hपूर्णांकs(q, vb, b);
		/* Copy relevant inक्रमmation provided by the userspace */
		स_रखो(vbuf->planes, 0,
		       माप(vbuf->planes[0]) * vb->num_planes);
		ret = vb2_fill_vb2_v4l2_buffer(vb, b);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (is_prepare)
		वापस 0;

	अगर (!(b->flags & V4L2_BUF_FLAG_REQUEST_FD)) अणु
		अगर (q->requires_requests) अणु
			dprपूर्णांकk(q, 1, "%s: queue requires requests\n", opname);
			वापस -EBADR;
		पूर्ण
		अगर (q->uses_requests) अणु
			dprपूर्णांकk(q, 1, "%s: queue uses requests\n", opname);
			वापस -EBUSY;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (!q->supports_requests) अणु
		dprपूर्णांकk(q, 1, "%s: queue does not support requests\n", opname);
		वापस -EBADR;
	पूर्ण अन्यथा अगर (q->uses_qbuf) अणु
		dprपूर्णांकk(q, 1, "%s: queue does not use requests\n", opname);
		वापस -EBUSY;
	पूर्ण

	/*
	 * For proper locking when queueing a request you need to be able
	 * to lock access to the vb2 queue, so check that there is a lock
	 * that we can use. In addition p_req must be non-शून्य.
	 */
	अगर (WARN_ON(!q->lock || !p_req))
		वापस -EINVAL;

	/*
	 * Make sure this op is implemented by the driver. It's easy to क्रमget
	 * this callback, but is it important when canceling a buffer in a
	 * queued request.
	 */
	अगर (WARN_ON(!q->ops->buf_request_complete))
		वापस -EINVAL;
	/*
	 * Make sure this op is implemented by the driver क्रम the output queue.
	 * It's easy to क्रमget this callback, but is it important to correctly
	 * validate the 'field' value at QBUF समय.
	 */
	अगर (WARN_ON((q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT ||
		     q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) &&
		    !q->ops->buf_out_validate))
		वापस -EINVAL;

	req = media_request_get_by_fd(mdev, b->request_fd);
	अगर (IS_ERR(req)) अणु
		dprपूर्णांकk(q, 1, "%s: invalid request_fd\n", opname);
		वापस PTR_ERR(req);
	पूर्ण

	/*
	 * Early sanity check. This is checked again when the buffer
	 * is bound to the request in vb2_core_qbuf().
	 */
	अगर (req->state != MEDIA_REQUEST_STATE_IDLE &&
	    req->state != MEDIA_REQUEST_STATE_UPDATING) अणु
		dprपूर्णांकk(q, 1, "%s: request is not idle\n", opname);
		media_request_put(req);
		वापस -EBUSY;
	पूर्ण

	*p_req = req;
	vbuf->request_fd = b->request_fd;

	वापस 0;
पूर्ण

/*
 * __fill_v4l2_buffer() - fill in a काष्ठा v4l2_buffer with inक्रमmation to be
 * वापसed to userspace
 */
अटल व्योम __fill_v4l2_buffer(काष्ठा vb2_buffer *vb, व्योम *pb)
अणु
	काष्ठा v4l2_buffer *b = pb;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *q = vb->vb2_queue;
	अचिन्हित पूर्णांक plane;

	/* Copy back data such as बारtamp, flags, etc. */
	b->index = vb->index;
	b->type = vb->type;
	b->memory = vb->memory;
	b->bytesused = 0;

	b->flags = vbuf->flags;
	b->field = vbuf->field;
	v4l2_buffer_set_बारtamp(b, vb->बारtamp);
	b->समयcode = vbuf->समयcode;
	b->sequence = vbuf->sequence;
	b->reserved2 = 0;
	b->request_fd = 0;

	अगर (q->is_multiplanar) अणु
		/*
		 * Fill in plane-related data अगर userspace provided an array
		 * क्रम it. The caller has alपढ़ोy verअगरied memory and size.
		 */
		b->length = vb->num_planes;
		क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
			काष्ठा v4l2_plane *pdst = &b->m.planes[plane];
			काष्ठा vb2_plane *psrc = &vb->planes[plane];

			pdst->bytesused = psrc->bytesused;
			pdst->length = psrc->length;
			अगर (q->memory == VB2_MEMORY_MMAP)
				pdst->m.mem_offset = psrc->m.offset;
			अन्यथा अगर (q->memory == VB2_MEMORY_USERPTR)
				pdst->m.userptr = psrc->m.userptr;
			अन्यथा अगर (q->memory == VB2_MEMORY_DMABUF)
				pdst->m.fd = psrc->m.fd;
			pdst->data_offset = psrc->data_offset;
			स_रखो(pdst->reserved, 0, माप(pdst->reserved));
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We use length and offset in v4l2_planes array even क्रम
		 * single-planar buffers, but userspace करोes not.
		 */
		b->length = vb->planes[0].length;
		b->bytesused = vb->planes[0].bytesused;
		अगर (q->memory == VB2_MEMORY_MMAP)
			b->m.offset = vb->planes[0].m.offset;
		अन्यथा अगर (q->memory == VB2_MEMORY_USERPTR)
			b->m.userptr = vb->planes[0].m.userptr;
		अन्यथा अगर (q->memory == VB2_MEMORY_DMABUF)
			b->m.fd = vb->planes[0].m.fd;
	पूर्ण

	/*
	 * Clear any buffer state related flags.
	 */
	b->flags &= ~V4L2_BUFFER_MASK_FLAGS;
	b->flags |= q->बारtamp_flags & V4L2_BUF_FLAG_TIMESTAMP_MASK;
	अगर (!q->copy_बारtamp) अणु
		/*
		 * For non-COPY बारtamps, drop बारtamp source bits
		 * and obtain the बारtamp source from the queue.
		 */
		b->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		b->flags |= q->बारtamp_flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	पूर्ण

	चयन (vb->state) अणु
	हाल VB2_BUF_STATE_QUEUED:
	हाल VB2_BUF_STATE_ACTIVE:
		b->flags |= V4L2_BUF_FLAG_QUEUED;
		अवरोध;
	हाल VB2_BUF_STATE_IN_REQUEST:
		b->flags |= V4L2_BUF_FLAG_IN_REQUEST;
		अवरोध;
	हाल VB2_BUF_STATE_ERROR:
		b->flags |= V4L2_BUF_FLAG_ERROR;
		fallthrough;
	हाल VB2_BUF_STATE_DONE:
		b->flags |= V4L2_BUF_FLAG_DONE;
		अवरोध;
	हाल VB2_BUF_STATE_PREPARING:
	हाल VB2_BUF_STATE_DEQUEUED:
		/* nothing */
		अवरोध;
	पूर्ण

	अगर ((vb->state == VB2_BUF_STATE_DEQUEUED ||
	     vb->state == VB2_BUF_STATE_IN_REQUEST) &&
	    vb->synced && vb->prepared)
		b->flags |= V4L2_BUF_FLAG_PREPARED;

	अगर (vb2_buffer_in_use(q, vb))
		b->flags |= V4L2_BUF_FLAG_MAPPED;
	अगर (vbuf->request_fd >= 0) अणु
		b->flags |= V4L2_BUF_FLAG_REQUEST_FD;
		b->request_fd = vbuf->request_fd;
	पूर्ण
पूर्ण

/*
 * __fill_vb2_buffer() - fill a vb2_buffer with inक्रमmation provided in a
 * v4l2_buffer by the userspace. It also verअगरies that काष्ठा
 * v4l2_buffer has a valid number of planes.
 */
अटल पूर्णांक __fill_vb2_buffer(काष्ठा vb2_buffer *vb, काष्ठा vb2_plane *planes)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	अचिन्हित पूर्णांक plane;

	अगर (!vb->vb2_queue->copy_बारtamp)
		vb->बारtamp = 0;

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		अगर (vb->vb2_queue->memory != VB2_MEMORY_MMAP) अणु
			planes[plane].m = vbuf->planes[plane].m;
			planes[plane].length = vbuf->planes[plane].length;
		पूर्ण
		planes[plane].bytesused = vbuf->planes[plane].bytesused;
		planes[plane].data_offset = vbuf->planes[plane].data_offset;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_buf_ops v4l2_buf_ops = अणु
	.verअगरy_planes_array	= __verअगरy_planes_array_core,
	.init_buffer		= __init_vb2_v4l2_buffer,
	.fill_user_buffer	= __fill_v4l2_buffer,
	.fill_vb2_buffer	= __fill_vb2_buffer,
	.copy_बारtamp		= __copy_बारtamp,
पूर्ण;

पूर्णांक vb2_find_बारtamp(स्थिर काष्ठा vb2_queue *q, u64 बारtamp,
		       अचिन्हित पूर्णांक start_idx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = start_idx; i < q->num_buffers; i++)
		अगर (q->bufs[i]->copied_बारtamp &&
		    q->bufs[i]->बारtamp == बारtamp)
			वापस i;
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_find_बारtamp);

/*
 * vb2_querybuf() - query video buffer inक्रमmation
 * @q:		videobuf queue
 * @b:		buffer काष्ठा passed from userspace to vidioc_querybuf handler
 *		in driver
 *
 * Should be called from vidioc_querybuf ioctl handler in driver.
 * This function will verअगरy the passed v4l2_buffer काष्ठाure and fill the
 * relevant inक्रमmation क्रम the userspace.
 *
 * The वापस values from this function are पूर्णांकended to be directly वापसed
 * from vidioc_querybuf handler in driver.
 */
पूर्णांक vb2_querybuf(काष्ठा vb2_queue *q, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	अगर (b->type != q->type) अणु
		dprपूर्णांकk(q, 1, "wrong buffer type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (b->index >= q->num_buffers) अणु
		dprपूर्णांकk(q, 1, "buffer index out of range\n");
		वापस -EINVAL;
	पूर्ण
	vb = q->bufs[b->index];
	ret = __verअगरy_planes_array(vb, b);
	अगर (!ret)
		vb2_core_querybuf(q, b->index, b);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vb2_querybuf);

अटल व्योम fill_buf_caps(काष्ठा vb2_queue *q, u32 *caps)
अणु
	*caps = V4L2_BUF_CAP_SUPPORTS_ORPHANED_BUFS;
	अगर (q->io_modes & VB2_MMAP)
		*caps |= V4L2_BUF_CAP_SUPPORTS_MMAP;
	अगर (q->io_modes & VB2_USERPTR)
		*caps |= V4L2_BUF_CAP_SUPPORTS_USERPTR;
	अगर (q->io_modes & VB2_DMABUF)
		*caps |= V4L2_BUF_CAP_SUPPORTS_DMABUF;
	अगर (q->subप्रणाली_flags & VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF)
		*caps |= V4L2_BUF_CAP_SUPPORTS_M2M_HOLD_CAPTURE_BUF;
	अगर (q->allow_cache_hपूर्णांकs && q->io_modes & VB2_MMAP)
		*caps |= V4L2_BUF_CAP_SUPPORTS_MMAP_CACHE_HINTS;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_REQUEST_API
	अगर (q->supports_requests)
		*caps |= V4L2_BUF_CAP_SUPPORTS_REQUESTS;
#पूर्ण_अगर
पूर्ण

पूर्णांक vb2_reqbufs(काष्ठा vb2_queue *q, काष्ठा v4l2_requestbuffers *req)
अणु
	पूर्णांक ret = vb2_verअगरy_memory_type(q, req->memory, req->type);

	fill_buf_caps(q, &req->capabilities);
	वापस ret ? ret : vb2_core_reqbufs(q, req->memory, &req->count);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_reqbufs);

पूर्णांक vb2_prepare_buf(काष्ठा vb2_queue *q, काष्ठा media_device *mdev,
		    काष्ठा v4l2_buffer *b)
अणु
	पूर्णांक ret;

	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण

	अगर (b->flags & V4L2_BUF_FLAG_REQUEST_FD)
		वापस -EINVAL;

	ret = vb2_queue_or_prepare_buf(q, mdev, b, true, शून्य);

	वापस ret ? ret : vb2_core_prepare_buf(q, b->index, b);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_prepare_buf);

पूर्णांक vb2_create_bufs(काष्ठा vb2_queue *q, काष्ठा v4l2_create_buffers *create)
अणु
	अचिन्हित requested_planes = 1;
	अचिन्हित requested_sizes[VIDEO_MAX_PLANES];
	काष्ठा v4l2_क्रमmat *f = &create->क्रमmat;
	पूर्णांक ret = vb2_verअगरy_memory_type(q, create->memory, f->type);
	अचिन्हित i;

	fill_buf_caps(q, &create->capabilities);
	create->index = q->num_buffers;
	अगर (create->count == 0)
		वापस ret != -EBUSY ? ret : 0;

	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		requested_planes = f->fmt.pix_mp.num_planes;
		अगर (requested_planes == 0 ||
		    requested_planes > VIDEO_MAX_PLANES)
			वापस -EINVAL;
		क्रम (i = 0; i < requested_planes; i++)
			requested_sizes[i] =
				f->fmt.pix_mp.plane_fmt[i].sizeimage;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		requested_sizes[0] = f->fmt.pix.sizeimage;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.vbi.samples_per_line *
			(f->fmt.vbi.count[0] + f->fmt.vbi.count[1]);
		अवरोध;
	हाल V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.sliced.io_size;
		अवरोध;
	हाल V4L2_BUF_TYPE_SDR_CAPTURE:
	हाल V4L2_BUF_TYPE_SDR_OUTPUT:
		requested_sizes[0] = f->fmt.sdr.buffersize;
		अवरोध;
	हाल V4L2_BUF_TYPE_META_CAPTURE:
	हाल V4L2_BUF_TYPE_META_OUTPUT:
		requested_sizes[0] = f->fmt.meta.buffersize;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < requested_planes; i++)
		अगर (requested_sizes[i] == 0)
			वापस -EINVAL;
	वापस ret ? ret : vb2_core_create_bufs(q, create->memory,
						&create->count,
						requested_planes,
						requested_sizes);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_create_bufs);

पूर्णांक vb2_qbuf(काष्ठा vb2_queue *q, काष्ठा media_device *mdev,
	     काष्ठा v4l2_buffer *b)
अणु
	काष्ठा media_request *req = शून्य;
	पूर्णांक ret;

	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण

	ret = vb2_queue_or_prepare_buf(q, mdev, b, false, &req);
	अगर (ret)
		वापस ret;
	ret = vb2_core_qbuf(q, b->index, b, req);
	अगर (req)
		media_request_put(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_qbuf);

पूर्णांक vb2_dqbuf(काष्ठा vb2_queue *q, काष्ठा v4l2_buffer *b, bool nonblocking)
अणु
	पूर्णांक ret;

	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण

	अगर (b->type != q->type) अणु
		dprपूर्णांकk(q, 1, "invalid buffer type\n");
		वापस -EINVAL;
	पूर्ण

	ret = vb2_core_dqbuf(q, शून्य, b, nonblocking);

	अगर (!q->is_output &&
	    b->flags & V4L2_BUF_FLAG_DONE &&
	    b->flags & V4L2_BUF_FLAG_LAST)
		q->last_buffer_dequeued = true;

	/*
	 *  After calling the VIDIOC_DQBUF V4L2_BUF_FLAG_DONE must be
	 *  cleared.
	 */
	b->flags &= ~V4L2_BUF_FLAG_DONE;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_dqbuf);

पूर्णांक vb2_streamon(काष्ठा vb2_queue *q, क्रमागत v4l2_buf_type type)
अणु
	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण
	वापस vb2_core_streamon(q, type);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_streamon);

पूर्णांक vb2_streamoff(काष्ठा vb2_queue *q, क्रमागत v4l2_buf_type type)
अणु
	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण
	वापस vb2_core_streamoff(q, type);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_streamoff);

पूर्णांक vb2_expbuf(काष्ठा vb2_queue *q, काष्ठा v4l2_exportbuffer *eb)
अणु
	वापस vb2_core_expbuf(q, &eb->fd, eb->type, eb->index,
				eb->plane, eb->flags);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_expbuf);

पूर्णांक vb2_queue_init_name(काष्ठा vb2_queue *q, स्थिर अक्षर *name)
अणु
	/*
	 * Sanity check
	 */
	अगर (WARN_ON(!q)			  ||
	    WARN_ON(q->बारtamp_flags &
		    ~(V4L2_BUF_FLAG_TIMESTAMP_MASK |
		      V4L2_BUF_FLAG_TSTAMP_SRC_MASK)))
		वापस -EINVAL;

	/* Warn that the driver should choose an appropriate बारtamp type */
	WARN_ON((q->बारtamp_flags & V4L2_BUF_FLAG_TIMESTAMP_MASK) ==
		V4L2_BUF_FLAG_TIMESTAMP_UNKNOWN);

	/* Warn that vb2_memory should match with v4l2_memory */
	अगर (WARN_ON(VB2_MEMORY_MMAP != (पूर्णांक)V4L2_MEMORY_MMAP)
		|| WARN_ON(VB2_MEMORY_USERPTR != (पूर्णांक)V4L2_MEMORY_USERPTR)
		|| WARN_ON(VB2_MEMORY_DMABUF != (पूर्णांक)V4L2_MEMORY_DMABUF))
		वापस -EINVAL;

	अगर (q->buf_काष्ठा_size == 0)
		q->buf_काष्ठा_size = माप(काष्ठा vb2_v4l2_buffer);

	q->buf_ops = &v4l2_buf_ops;
	q->is_multiplanar = V4L2_TYPE_IS_MULTIPLANAR(q->type);
	q->is_output = V4L2_TYPE_IS_OUTPUT(q->type);
	q->copy_बारtamp = (q->बारtamp_flags & V4L2_BUF_FLAG_TIMESTAMP_MASK)
			== V4L2_BUF_FLAG_TIMESTAMP_COPY;
	/*
	 * For compatibility with vb1: अगर QBUF hasn't been called yet, then
	 * वापस EPOLLERR as well. This only affects capture queues, output
	 * queues will always initialize रुकोing_क्रम_buffers to false.
	 */
	q->quirk_poll_must_check_रुकोing_क्रम_buffers = true;

	अगर (name)
		strscpy(q->name, name, माप(q->name));
	अन्यथा
		q->name[0] = '\0';

	वापस vb2_core_queue_init(q);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_queue_init_name);

पूर्णांक vb2_queue_init(काष्ठा vb2_queue *q)
अणु
	वापस vb2_queue_init_name(q, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_queue_init);

व्योम vb2_queue_release(काष्ठा vb2_queue *q)
अणु
	vb2_core_queue_release(q);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_queue_release);

__poll_t vb2_poll(काष्ठा vb2_queue *q, काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	__poll_t res;

	res = vb2_core_poll(q, file, रुको);

	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags)) अणु
		काष्ठा v4l2_fh *fh = file->निजी_data;

		poll_रुको(file, &fh->रुको, रुको);
		अगर (v4l2_event_pending(fh))
			res |= EPOLLPRI;
	पूर्ण

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_poll);

/*
 * The following functions are not part of the vb2 core API, but are helper
 * functions that plug पूर्णांकo काष्ठा v4l2_ioctl_ops, काष्ठा v4l2_file_operations
 * and काष्ठा vb2_ops.
 * They contain boilerplate code that most अगर not all drivers have to करो
 * and so they simplअगरy the driver code.
 */

/* The queue is busy अगर there is a owner and you are not that owner. */
अटल अंतरभूत bool vb2_queue_is_busy(काष्ठा video_device *vdev, काष्ठा file *file)
अणु
	वापस vdev->queue->owner && vdev->queue->owner != file->निजी_data;
पूर्ण

/* vb2 ioctl helpers */

पूर्णांक vb2_ioctl_reqbufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_requestbuffers *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक res = vb2_verअगरy_memory_type(vdev->queue, p->memory, p->type);

	fill_buf_caps(vdev->queue, &p->capabilities);
	अगर (res)
		वापस res;
	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	res = vb2_core_reqbufs(vdev->queue, p->memory, &p->count);
	/* If count == 0, then the owner has released all buffers and he
	   is no दीर्घer owner of the queue. Otherwise we have a new owner. */
	अगर (res == 0)
		vdev->queue->owner = p->count ? file->निजी_data : शून्य;
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_reqbufs);

पूर्णांक vb2_ioctl_create_bufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_create_buffers *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक res = vb2_verअगरy_memory_type(vdev->queue, p->memory,
			p->क्रमmat.type);

	p->index = vdev->queue->num_buffers;
	fill_buf_caps(vdev->queue, &p->capabilities);
	/*
	 * If count == 0, then just check अगर memory and type are valid.
	 * Any -EBUSY result from vb2_verअगरy_memory_type can be mapped to 0.
	 */
	अगर (p->count == 0)
		वापस res != -EBUSY ? res : 0;
	अगर (res)
		वापस res;
	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;

	res = vb2_create_bufs(vdev->queue, p);
	अगर (res == 0)
		vdev->queue->owner = file->निजी_data;
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_create_bufs);

पूर्णांक vb2_ioctl_prepare_buf(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_buffer *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_prepare_buf(vdev->queue, vdev->v4l2_dev->mdev, p);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_prepare_buf);

पूर्णांक vb2_ioctl_querybuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	/* No need to call vb2_queue_is_busy(), anyone can query buffers. */
	वापस vb2_querybuf(vdev->queue, p);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_querybuf);

पूर्णांक vb2_ioctl_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_qbuf(vdev->queue, vdev->v4l2_dev->mdev, p);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_qbuf);

पूर्णांक vb2_ioctl_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_dqbuf(vdev->queue, p, file->f_flags & O_NONBLOCK);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_dqbuf);

पूर्णांक vb2_ioctl_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_streamon(vdev->queue, i);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_streamon);

पूर्णांक vb2_ioctl_streamoff(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_streamoff(vdev->queue, i);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_streamoff);

पूर्णांक vb2_ioctl_expbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_exportbuffer *p)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vb2_queue_is_busy(vdev, file))
		वापस -EBUSY;
	वापस vb2_expbuf(vdev->queue, p);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ioctl_expbuf);

/* v4l2_file_operations helpers */

पूर्णांक vb2_fop_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	वापस vb2_mmap(vdev->queue, vma);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_mmap);

पूर्णांक _vb2_fop_release(काष्ठा file *file, काष्ठा mutex *lock)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (lock)
		mutex_lock(lock);
	अगर (file->निजी_data == vdev->queue->owner) अणु
		vb2_queue_release(vdev->queue);
		vdev->queue->owner = शून्य;
	पूर्ण
	अगर (lock)
		mutex_unlock(lock);
	वापस v4l2_fh_release(file);
पूर्ण
EXPORT_SYMBOL_GPL(_vb2_fop_release);

पूर्णांक vb2_fop_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा mutex *lock = vdev->queue->lock ? vdev->queue->lock : vdev->lock;

	वापस _vb2_fop_release(file, lock);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_release);

sमाप_प्रकार vb2_fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा mutex *lock = vdev->queue->lock ? vdev->queue->lock : vdev->lock;
	पूर्णांक err = -EBUSY;

	अगर (!(vdev->queue->io_modes & VB2_WRITE))
		वापस -EINVAL;
	अगर (lock && mutex_lock_पूर्णांकerruptible(lock))
		वापस -ERESTARTSYS;
	अगर (vb2_queue_is_busy(vdev, file))
		जाओ निकास;
	err = vb2_ग_लिखो(vdev->queue, buf, count, ppos,
		       file->f_flags & O_NONBLOCK);
	अगर (vdev->queue->fileio)
		vdev->queue->owner = file->निजी_data;
निकास:
	अगर (lock)
		mutex_unlock(lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_ग_लिखो);

sमाप_प्रकार vb2_fop_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा mutex *lock = vdev->queue->lock ? vdev->queue->lock : vdev->lock;
	पूर्णांक err = -EBUSY;

	अगर (!(vdev->queue->io_modes & VB2_READ))
		वापस -EINVAL;
	अगर (lock && mutex_lock_पूर्णांकerruptible(lock))
		वापस -ERESTARTSYS;
	अगर (vb2_queue_is_busy(vdev, file))
		जाओ निकास;
	err = vb2_पढ़ो(vdev->queue, buf, count, ppos,
		       file->f_flags & O_NONBLOCK);
	अगर (vdev->queue->fileio)
		vdev->queue->owner = file->निजी_data;
निकास:
	अगर (lock)
		mutex_unlock(lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_पढ़ो);

__poll_t vb2_fop_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा vb2_queue *q = vdev->queue;
	काष्ठा mutex *lock = q->lock ? q->lock : vdev->lock;
	__poll_t res;
	व्योम *fileio;

	/*
	 * If this helper करोesn't know how to lock, then you shouldn't be using
	 * it but you should ग_लिखो your own.
	 */
	WARN_ON(!lock);

	अगर (lock && mutex_lock_पूर्णांकerruptible(lock))
		वापस EPOLLERR;

	fileio = q->fileio;

	res = vb2_poll(vdev->queue, file, रुको);

	/* If fileio was started, then we have a new queue owner. */
	अगर (!fileio && q->fileio)
		q->owner = file->निजी_data;
	अगर (lock)
		mutex_unlock(lock);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_poll);

#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ vb2_fop_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	वापस vb2_get_unmapped_area(vdev->queue, addr, len, pgoff, flags);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_fop_get_unmapped_area);
#पूर्ण_अगर

व्योम vb2_video_unरेजिस्टर_device(काष्ठा video_device *vdev)
अणु
	/* Check अगर vdev was ever रेजिस्टरed at all */
	अगर (!vdev || !video_is_रेजिस्टरed(vdev))
		वापस;

	/*
	 * Calling this function only makes sense अगर vdev->queue is set.
	 * If it is शून्य, then just call video_unरेजिस्टर_device() instead.
	 */
	WARN_ON(!vdev->queue);

	/*
	 * Take a reference to the device since video_unरेजिस्टर_device()
	 * calls device_unरेजिस्टर(), but we करोn't want that to release
	 * the device since we want to clean up the queue first.
	 */
	get_device(&vdev->dev);
	video_unरेजिस्टर_device(vdev);
	अगर (vdev->queue && vdev->queue->owner) अणु
		काष्ठा mutex *lock = vdev->queue->lock ?
			vdev->queue->lock : vdev->lock;

		अगर (lock)
			mutex_lock(lock);
		vb2_queue_release(vdev->queue);
		vdev->queue->owner = शून्य;
		अगर (lock)
			mutex_unlock(lock);
	पूर्ण
	/*
	 * Now we put the device, and in most हालs this will release
	 * everything.
	 */
	put_device(&vdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_video_unरेजिस्टर_device);

/* vb2_ops helpers. Only use अगर vq->lock is non-शून्य. */

व्योम vb2_ops_रुको_prepare(काष्ठा vb2_queue *vq)
अणु
	mutex_unlock(vq->lock);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ops_रुको_prepare);

व्योम vb2_ops_रुको_finish(काष्ठा vb2_queue *vq)
अणु
	mutex_lock(vq->lock);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ops_रुको_finish);

/*
 * Note that this function is called during validation समय and
 * thus the req_queue_mutex is held to ensure no request objects
 * can be added or deleted जबतक validating. So there is no need
 * to protect the objects list.
 */
पूर्णांक vb2_request_validate(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj;
	पूर्णांक ret = 0;

	अगर (!vb2_request_buffer_cnt(req))
		वापस -ENOENT;

	list_क्रम_each_entry(obj, &req->objects, list) अणु
		अगर (!obj->ops->prepare)
			जारी;

		ret = obj->ops->prepare(obj);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		list_क्रम_each_entry_जारी_reverse(obj, &req->objects, list)
			अगर (obj->ops->unprepare)
				obj->ops->unprepare(obj);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_request_validate);

व्योम vb2_request_queue(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj, *obj_safe;

	/*
	 * Queue all objects. Note that buffer objects are at the end of the
	 * objects list, after all other object types. Once buffer objects
	 * are queued, the driver might delete them immediately (अगर the driver
	 * processes the buffer at once), so we have to use
	 * list_क्रम_each_entry_safe() to handle the हाल where the object we
	 * queue is deleted.
	 */
	list_क्रम_each_entry_safe(obj, obj_safe, &req->objects, list)
		अगर (obj->ops->queue)
			obj->ops->queue(obj);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_request_queue);

MODULE_DESCRIPTION("Driver helper framework for Video for Linux 2");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>, Marek Szyprowski");
MODULE_LICENSE("GPL");
