<शैली गुरु>
/*
 * videobuf2-core.c - video buffer 2 core framework
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश <media/videobuf2-core.h>
#समावेश <media/v4l2-mc.h>

#समावेश <trace/events/vb2.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा dprपूर्णांकk(q, level, fmt, arg...)					\
	करो अणु								\
		अगर (debug >= level)					\
			pr_info("[%s] %s: " fmt, (q)->name, __func__,	\
				## arg);				\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG

/*
 * If advanced debugging is on, then count how often each op is called
 * successfully, which can either be per-buffer or per-queue.
 *
 * This makes it easy to check that the 'init' and 'cleanup'
 * (and variations thereof) stay balanced.
 */

#घोषणा log_memop(vb, op)						\
	dprपूर्णांकk((vb)->vb2_queue, 2, "call_memop(%d, %s)%s\n",		\
		(vb)->index, #op,					\
		(vb)->vb2_queue->mem_ops->op ? "" : " (nop)")

#घोषणा call_memop(vb, op, args...)					\
(अणु									\
	काष्ठा vb2_queue *_q = (vb)->vb2_queue;				\
	पूर्णांक err;							\
									\
	log_memop(vb, op);						\
	err = _q->mem_ops->op ? _q->mem_ops->op(args) : 0;		\
	अगर (!err)							\
		(vb)->cnt_mem_ ## op++;					\
	err;								\
पूर्ण)

#घोषणा call_ptr_memop(vb, op, args...)					\
(अणु									\
	काष्ठा vb2_queue *_q = (vb)->vb2_queue;				\
	व्योम *ptr;							\
									\
	log_memop(vb, op);						\
	ptr = _q->mem_ops->op ? _q->mem_ops->op(args) : शून्य;		\
	अगर (!IS_ERR_OR_शून्य(ptr))					\
		(vb)->cnt_mem_ ## op++;					\
	ptr;								\
पूर्ण)

#घोषणा call_व्योम_memop(vb, op, args...)				\
(अणु									\
	काष्ठा vb2_queue *_q = (vb)->vb2_queue;				\
									\
	log_memop(vb, op);						\
	अगर (_q->mem_ops->op)						\
		_q->mem_ops->op(args);					\
	(vb)->cnt_mem_ ## op++;						\
पूर्ण)

#घोषणा log_qop(q, op)							\
	dprपूर्णांकk(q, 2, "call_qop(%s)%s\n", #op,				\
		(q)->ops->op ? "" : " (nop)")

#घोषणा call_qop(q, op, args...)					\
(अणु									\
	पूर्णांक err;							\
									\
	log_qop(q, op);							\
	err = (q)->ops->op ? (q)->ops->op(args) : 0;			\
	अगर (!err)							\
		(q)->cnt_ ## op++;					\
	err;								\
पूर्ण)

#घोषणा call_व्योम_qop(q, op, args...)					\
(अणु									\
	log_qop(q, op);							\
	अगर ((q)->ops->op)						\
		(q)->ops->op(args);					\
	(q)->cnt_ ## op++;						\
पूर्ण)

#घोषणा log_vb_qop(vb, op, args...)					\
	dprपूर्णांकk((vb)->vb2_queue, 2, "call_vb_qop(%d, %s)%s\n",		\
		(vb)->index, #op,					\
		(vb)->vb2_queue->ops->op ? "" : " (nop)")

#घोषणा call_vb_qop(vb, op, args...)					\
(अणु									\
	पूर्णांक err;							\
									\
	log_vb_qop(vb, op);						\
	err = (vb)->vb2_queue->ops->op ?				\
		(vb)->vb2_queue->ops->op(args) : 0;			\
	अगर (!err)							\
		(vb)->cnt_ ## op++;					\
	err;								\
पूर्ण)

#घोषणा call_व्योम_vb_qop(vb, op, args...)				\
(अणु									\
	log_vb_qop(vb, op);						\
	अगर ((vb)->vb2_queue->ops->op)					\
		(vb)->vb2_queue->ops->op(args);				\
	(vb)->cnt_ ## op++;						\
पूर्ण)

#अन्यथा

#घोषणा call_memop(vb, op, args...)					\
	((vb)->vb2_queue->mem_ops->op ?					\
		(vb)->vb2_queue->mem_ops->op(args) : 0)

#घोषणा call_ptr_memop(vb, op, args...)					\
	((vb)->vb2_queue->mem_ops->op ?					\
		(vb)->vb2_queue->mem_ops->op(args) : शून्य)

#घोषणा call_व्योम_memop(vb, op, args...)				\
	करो अणु								\
		अगर ((vb)->vb2_queue->mem_ops->op)			\
			(vb)->vb2_queue->mem_ops->op(args);		\
	पूर्ण जबतक (0)

#घोषणा call_qop(q, op, args...)					\
	((q)->ops->op ? (q)->ops->op(args) : 0)

#घोषणा call_व्योम_qop(q, op, args...)					\
	करो अणु								\
		अगर ((q)->ops->op)					\
			(q)->ops->op(args);				\
	पूर्ण जबतक (0)

#घोषणा call_vb_qop(vb, op, args...)					\
	((vb)->vb2_queue->ops->op ? (vb)->vb2_queue->ops->op(args) : 0)

#घोषणा call_व्योम_vb_qop(vb, op, args...)				\
	करो अणु								\
		अगर ((vb)->vb2_queue->ops->op)				\
			(vb)->vb2_queue->ops->op(args);			\
	पूर्ण जबतक (0)

#पूर्ण_अगर

#घोषणा call_bufop(q, op, args...)					\
(अणु									\
	पूर्णांक ret = 0;							\
	अगर (q && q->buf_ops && q->buf_ops->op)				\
		ret = q->buf_ops->op(args);				\
	ret;								\
पूर्ण)

#घोषणा call_व्योम_bufop(q, op, args...)					\
(अणु									\
	अगर (q && q->buf_ops && q->buf_ops->op)				\
		q->buf_ops->op(args);					\
पूर्ण)

अटल व्योम __vb2_queue_cancel(काष्ठा vb2_queue *q);
अटल व्योम __enqueue_in_driver(काष्ठा vb2_buffer *vb);

अटल स्थिर अक्षर *vb2_state_name(क्रमागत vb2_buffer_state s)
अणु
	अटल स्थिर अक्षर * स्थिर state_names[] = अणु
		[VB2_BUF_STATE_DEQUEUED] = "dequeued",
		[VB2_BUF_STATE_IN_REQUEST] = "in request",
		[VB2_BUF_STATE_PREPARING] = "preparing",
		[VB2_BUF_STATE_QUEUED] = "queued",
		[VB2_BUF_STATE_ACTIVE] = "active",
		[VB2_BUF_STATE_DONE] = "done",
		[VB2_BUF_STATE_ERROR] = "error",
	पूर्ण;

	अगर ((अचिन्हित पूर्णांक)(s) < ARRAY_SIZE(state_names))
		वापस state_names[s];
	वापस "unknown";
पूर्ण

/*
 * __vb2_buf_mem_alloc() - allocate video memory क्रम the given buffer
 */
अटल पूर्णांक __vb2_buf_mem_alloc(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	व्योम *mem_priv;
	पूर्णांक plane;
	पूर्णांक ret = -ENOMEM;

	/*
	 * Allocate memory क्रम all planes in this buffer
	 * NOTE: mmapped areas should be page aligned
	 */
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		/* Memops alloc requires size to be page aligned. */
		अचिन्हित दीर्घ size = PAGE_ALIGN(vb->planes[plane].length);

		/* Did it wrap around? */
		अगर (size < vb->planes[plane].length)
			जाओ मुक्त;

		mem_priv = call_ptr_memop(vb, alloc,
				q->alloc_devs[plane] ? : q->dev,
				q->dma_attrs, size, q->dma_dir, q->gfp_flags);
		अगर (IS_ERR_OR_शून्य(mem_priv)) अणु
			अगर (mem_priv)
				ret = PTR_ERR(mem_priv);
			जाओ मुक्त;
		पूर्ण

		/* Associate allocator निजी data with this plane */
		vb->planes[plane].mem_priv = mem_priv;
	पूर्ण

	वापस 0;
मुक्त:
	/* Free alपढ़ोy allocated memory अगर one of the allocations failed */
	क्रम (; plane > 0; --plane) अणु
		call_व्योम_memop(vb, put, vb->planes[plane - 1].mem_priv);
		vb->planes[plane - 1].mem_priv = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * __vb2_buf_mem_मुक्त() - मुक्त memory of the given buffer
 */
अटल व्योम __vb2_buf_mem_मुक्त(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		call_व्योम_memop(vb, put, vb->planes[plane].mem_priv);
		vb->planes[plane].mem_priv = शून्य;
		dprपूर्णांकk(vb->vb2_queue, 3, "freed plane %d of buffer %d\n",
			plane, vb->index);
	पूर्ण
पूर्ण

/*
 * __vb2_buf_userptr_put() - release userspace memory associated with
 * a USERPTR buffer
 */
अटल व्योम __vb2_buf_userptr_put(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		अगर (vb->planes[plane].mem_priv)
			call_व्योम_memop(vb, put_userptr, vb->planes[plane].mem_priv);
		vb->planes[plane].mem_priv = शून्य;
	पूर्ण
पूर्ण

/*
 * __vb2_plane_dmabuf_put() - release memory associated with
 * a DMABUF shared plane
 */
अटल व्योम __vb2_plane_dmabuf_put(काष्ठा vb2_buffer *vb, काष्ठा vb2_plane *p)
अणु
	अगर (!p->mem_priv)
		वापस;

	अगर (p->dbuf_mapped)
		call_व्योम_memop(vb, unmap_dmabuf, p->mem_priv);

	call_व्योम_memop(vb, detach_dmabuf, p->mem_priv);
	dma_buf_put(p->dbuf);
	p->mem_priv = शून्य;
	p->dbuf = शून्य;
	p->dbuf_mapped = 0;
पूर्ण

/*
 * __vb2_buf_dmabuf_put() - release memory associated with
 * a DMABUF shared buffer
 */
अटल व्योम __vb2_buf_dmabuf_put(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;

	क्रम (plane = 0; plane < vb->num_planes; ++plane)
		__vb2_plane_dmabuf_put(vb, &vb->planes[plane]);
पूर्ण

/*
 * __vb2_buf_mem_prepare() - call ->prepare() on buffer's निजी memory
 * to sync caches
 */
अटल व्योम __vb2_buf_mem_prepare(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;

	अगर (vb->synced)
		वापस;

	अगर (vb->need_cache_sync_on_prepare) अणु
		क्रम (plane = 0; plane < vb->num_planes; ++plane)
			call_व्योम_memop(vb, prepare,
					vb->planes[plane].mem_priv);
	पूर्ण
	vb->synced = 1;
पूर्ण

/*
 * __vb2_buf_mem_finish() - call ->finish on buffer's निजी memory
 * to sync caches
 */
अटल व्योम __vb2_buf_mem_finish(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;

	अगर (!vb->synced)
		वापस;

	अगर (vb->need_cache_sync_on_finish) अणु
		क्रम (plane = 0; plane < vb->num_planes; ++plane)
			call_व्योम_memop(vb, finish,
					vb->planes[plane].mem_priv);
	पूर्ण
	vb->synced = 0;
पूर्ण

/*
 * __setup_offsets() - setup unique offsets ("cookies") क्रम every plane in
 * the buffer.
 */
अटल व्योम __setup_offsets(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	अचिन्हित पूर्णांक plane;
	अचिन्हित दीर्घ off = 0;

	अगर (vb->index) अणु
		काष्ठा vb2_buffer *prev = q->bufs[vb->index - 1];
		काष्ठा vb2_plane *p = &prev->planes[prev->num_planes - 1];

		off = PAGE_ALIGN(p->m.offset + p->length);
	पूर्ण

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		vb->planes[plane].m.offset = off;

		dprपूर्णांकk(q, 3, "buffer %d, plane %d offset 0x%08lx\n",
				vb->index, plane, off);

		off += vb->planes[plane].length;
		off = PAGE_ALIGN(off);
	पूर्ण
पूर्ण

/*
 * __vb2_queue_alloc() - allocate videobuf buffer काष्ठाures and (क्रम MMAP type)
 * video buffer memory क्रम all buffers/planes on the queue and initializes the
 * queue
 *
 * Returns the number of buffers successfully allocated.
 */
अटल पूर्णांक __vb2_queue_alloc(काष्ठा vb2_queue *q, क्रमागत vb2_memory memory,
			     अचिन्हित पूर्णांक num_buffers, अचिन्हित पूर्णांक num_planes,
			     स्थिर अचिन्हित plane_sizes[VB2_MAX_PLANES])
अणु
	अचिन्हित पूर्णांक buffer, plane;
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	/* Ensure that q->num_buffers+num_buffers is below VB2_MAX_FRAME */
	num_buffers = min_t(अचिन्हित पूर्णांक, num_buffers,
			    VB2_MAX_FRAME - q->num_buffers);

	क्रम (buffer = 0; buffer < num_buffers; ++buffer) अणु
		/* Allocate videobuf buffer काष्ठाures */
		vb = kzalloc(q->buf_काष्ठा_size, GFP_KERNEL);
		अगर (!vb) अणु
			dprपूर्णांकk(q, 1, "memory alloc for buffer struct failed\n");
			अवरोध;
		पूर्ण

		vb->state = VB2_BUF_STATE_DEQUEUED;
		vb->vb2_queue = q;
		vb->num_planes = num_planes;
		vb->index = q->num_buffers + buffer;
		vb->type = q->type;
		vb->memory = memory;
		/*
		 * We need to set these flags here so that the videobuf2 core
		 * will call ->prepare()/->finish() cache sync/flush on vb2
		 * buffers when appropriate. However, we can aव्योम explicit
		 * ->prepare() and ->finish() cache sync क्रम DMABUF buffers,
		 * because DMA exporter takes care of it.
		 */
		अगर (q->memory != VB2_MEMORY_DMABUF) अणु
			vb->need_cache_sync_on_prepare = 1;
			vb->need_cache_sync_on_finish = 1;
		पूर्ण
		क्रम (plane = 0; plane < num_planes; ++plane) अणु
			vb->planes[plane].length = plane_sizes[plane];
			vb->planes[plane].min_length = plane_sizes[plane];
		पूर्ण
		call_व्योम_bufop(q, init_buffer, vb);

		q->bufs[vb->index] = vb;

		/* Allocate video buffer memory क्रम the MMAP type */
		अगर (memory == VB2_MEMORY_MMAP) अणु
			ret = __vb2_buf_mem_alloc(vb);
			अगर (ret) अणु
				dprपूर्णांकk(q, 1, "failed allocating memory for buffer %d\n",
					buffer);
				q->bufs[vb->index] = शून्य;
				kमुक्त(vb);
				अवरोध;
			पूर्ण
			__setup_offsets(vb);
			/*
			 * Call the driver-provided buffer initialization
			 * callback, अगर given. An error in initialization
			 * results in queue setup failure.
			 */
			ret = call_vb_qop(vb, buf_init, vb);
			अगर (ret) अणु
				dprपूर्णांकk(q, 1, "buffer %d %p initialization failed\n",
					buffer, vb);
				__vb2_buf_mem_मुक्त(vb);
				q->bufs[vb->index] = शून्य;
				kमुक्त(vb);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dprपूर्णांकk(q, 3, "allocated %d buffers, %d plane(s) each\n",
		buffer, num_planes);

	वापस buffer;
पूर्ण

/*
 * __vb2_मुक्त_mem() - release all video buffer memory क्रम a given queue
 */
अटल व्योम __vb2_मुक्त_mem(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक buffers)
अणु
	अचिन्हित पूर्णांक buffer;
	काष्ठा vb2_buffer *vb;

	क्रम (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) अणु
		vb = q->bufs[buffer];
		अगर (!vb)
			जारी;

		/* Free MMAP buffers or release USERPTR buffers */
		अगर (q->memory == VB2_MEMORY_MMAP)
			__vb2_buf_mem_मुक्त(vb);
		अन्यथा अगर (q->memory == VB2_MEMORY_DMABUF)
			__vb2_buf_dmabuf_put(vb);
		अन्यथा
			__vb2_buf_userptr_put(vb);
	पूर्ण
पूर्ण

/*
 * __vb2_queue_मुक्त() - मुक्त buffers at the end of the queue - video memory and
 * related inक्रमmation, अगर no buffers are left वापस the queue to an
 * uninitialized state. Might be called even अगर the queue has alपढ़ोy been मुक्तd.
 */
अटल पूर्णांक __vb2_queue_मुक्त(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक buffers)
अणु
	अचिन्हित पूर्णांक buffer;

	/*
	 * Sanity check: when preparing a buffer the queue lock is released क्रम
	 * a लघु जबतक (see __buf_prepare क्रम the details), which would allow
	 * a race with a reqbufs which can call this function. Removing the
	 * buffers from underneath __buf_prepare is obviously a bad idea, so we
	 * check अगर any of the buffers is in the state PREPARING, and अगर so we
	 * just वापस -EAGAIN.
	 */
	क्रम (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) अणु
		अगर (q->bufs[buffer] == शून्य)
			जारी;
		अगर (q->bufs[buffer]->state == VB2_BUF_STATE_PREPARING) अणु
			dprपूर्णांकk(q, 1, "preparing buffers, cannot free\n");
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	/* Call driver-provided cleanup function क्रम each buffer, अगर provided */
	क्रम (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) अणु
		काष्ठा vb2_buffer *vb = q->bufs[buffer];

		अगर (vb && vb->planes[0].mem_priv)
			call_व्योम_vb_qop(vb, buf_cleanup, vb);
	पूर्ण

	/* Release video buffer memory */
	__vb2_मुक्त_mem(q, buffers);

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Check that all the calls were balances during the lअगरe-समय of this
	 * queue. If not (or अगर the debug level is 1 or up), then dump the
	 * counters to the kernel log.
	 */
	अगर (q->num_buffers) अणु
		bool unbalanced = q->cnt_start_streaming != q->cnt_stop_streaming ||
				  q->cnt_रुको_prepare != q->cnt_रुको_finish;

		अगर (unbalanced || debug) अणु
			pr_info("counters for queue %p:%s\n", q,
				unbalanced ? " UNBALANCED!" : "");
			pr_info("     setup: %u start_streaming: %u stop_streaming: %u\n",
				q->cnt_queue_setup, q->cnt_start_streaming,
				q->cnt_stop_streaming);
			pr_info("     wait_prepare: %u wait_finish: %u\n",
				q->cnt_रुको_prepare, q->cnt_रुको_finish);
		पूर्ण
		q->cnt_queue_setup = 0;
		q->cnt_रुको_prepare = 0;
		q->cnt_रुको_finish = 0;
		q->cnt_start_streaming = 0;
		q->cnt_stop_streaming = 0;
	पूर्ण
	क्रम (buffer = 0; buffer < q->num_buffers; ++buffer) अणु
		काष्ठा vb2_buffer *vb = q->bufs[buffer];
		bool unbalanced = vb->cnt_mem_alloc != vb->cnt_mem_put ||
				  vb->cnt_mem_prepare != vb->cnt_mem_finish ||
				  vb->cnt_mem_get_userptr != vb->cnt_mem_put_userptr ||
				  vb->cnt_mem_attach_dmabuf != vb->cnt_mem_detach_dmabuf ||
				  vb->cnt_mem_map_dmabuf != vb->cnt_mem_unmap_dmabuf ||
				  vb->cnt_buf_queue != vb->cnt_buf_करोne ||
				  vb->cnt_buf_prepare != vb->cnt_buf_finish ||
				  vb->cnt_buf_init != vb->cnt_buf_cleanup;

		अगर (unbalanced || debug) अणु
			pr_info("   counters for queue %p, buffer %d:%s\n",
				q, buffer, unbalanced ? " UNBALANCED!" : "");
			pr_info("     buf_init: %u buf_cleanup: %u buf_prepare: %u buf_finish: %u\n",
				vb->cnt_buf_init, vb->cnt_buf_cleanup,
				vb->cnt_buf_prepare, vb->cnt_buf_finish);
			pr_info("     buf_out_validate: %u buf_queue: %u buf_done: %u buf_request_complete: %u\n",
				vb->cnt_buf_out_validate, vb->cnt_buf_queue,
				vb->cnt_buf_करोne, vb->cnt_buf_request_complete);
			pr_info("     alloc: %u put: %u prepare: %u finish: %u mmap: %u\n",
				vb->cnt_mem_alloc, vb->cnt_mem_put,
				vb->cnt_mem_prepare, vb->cnt_mem_finish,
				vb->cnt_mem_mmap);
			pr_info("     get_userptr: %u put_userptr: %u\n",
				vb->cnt_mem_get_userptr, vb->cnt_mem_put_userptr);
			pr_info("     attach_dmabuf: %u detach_dmabuf: %u map_dmabuf: %u unmap_dmabuf: %u\n",
				vb->cnt_mem_attach_dmabuf, vb->cnt_mem_detach_dmabuf,
				vb->cnt_mem_map_dmabuf, vb->cnt_mem_unmap_dmabuf);
			pr_info("     get_dmabuf: %u num_users: %u vaddr: %u cookie: %u\n",
				vb->cnt_mem_get_dmabuf,
				vb->cnt_mem_num_users,
				vb->cnt_mem_vaddr,
				vb->cnt_mem_cookie);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Free videobuf buffers */
	क्रम (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) अणु
		kमुक्त(q->bufs[buffer]);
		q->bufs[buffer] = शून्य;
	पूर्ण

	q->num_buffers -= buffers;
	अगर (!q->num_buffers) अणु
		q->memory = VB2_MEMORY_UNKNOWN;
		INIT_LIST_HEAD(&q->queued_list);
	पूर्ण
	वापस 0;
पूर्ण

bool vb2_buffer_in_use(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित पूर्णांक plane;
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		व्योम *mem_priv = vb->planes[plane].mem_priv;
		/*
		 * If num_users() has not been provided, call_memop
		 * will वापस 0, apparently nobody cares about this
		 * हाल anyway. If num_users() वापसs more than 1,
		 * we are not the only user of the plane's memory.
		 */
		अगर (mem_priv && call_memop(vb, num_users, mem_priv) > 1)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(vb2_buffer_in_use);

/*
 * __buffers_in_use() - वापस true अगर any buffers on the queue are in use and
 * the queue cannot be मुक्तd (by the means of REQBUFS(0)) call
 */
अटल bool __buffers_in_use(काष्ठा vb2_queue *q)
अणु
	अचिन्हित पूर्णांक buffer;
	क्रम (buffer = 0; buffer < q->num_buffers; ++buffer) अणु
		अगर (vb2_buffer_in_use(q, q->bufs[buffer]))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम vb2_core_querybuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb)
अणु
	call_व्योम_bufop(q, fill_user_buffer, q->bufs[index], pb);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_querybuf);

/*
 * __verअगरy_userptr_ops() - verअगरy that all memory operations required क्रम
 * USERPTR queue type have been provided
 */
अटल पूर्णांक __verअगरy_userptr_ops(काष्ठा vb2_queue *q)
अणु
	अगर (!(q->io_modes & VB2_USERPTR) || !q->mem_ops->get_userptr ||
	    !q->mem_ops->put_userptr)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * __verअगरy_mmap_ops() - verअगरy that all memory operations required क्रम
 * MMAP queue type have been provided
 */
अटल पूर्णांक __verअगरy_mmap_ops(काष्ठा vb2_queue *q)
अणु
	अगर (!(q->io_modes & VB2_MMAP) || !q->mem_ops->alloc ||
	    !q->mem_ops->put || !q->mem_ops->mmap)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * __verअगरy_dmabuf_ops() - verअगरy that all memory operations required क्रम
 * DMABUF queue type have been provided
 */
अटल पूर्णांक __verअगरy_dmabuf_ops(काष्ठा vb2_queue *q)
अणु
	अगर (!(q->io_modes & VB2_DMABUF) || !q->mem_ops->attach_dmabuf ||
	    !q->mem_ops->detach_dmabuf  || !q->mem_ops->map_dmabuf ||
	    !q->mem_ops->unmap_dmabuf)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक vb2_verअगरy_memory_type(काष्ठा vb2_queue *q,
		क्रमागत vb2_memory memory, अचिन्हित पूर्णांक type)
अणु
	अगर (memory != VB2_MEMORY_MMAP && memory != VB2_MEMORY_USERPTR &&
	    memory != VB2_MEMORY_DMABUF) अणु
		dprपूर्णांकk(q, 1, "unsupported memory type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (type != q->type) अणु
		dprपूर्णांकk(q, 1, "requested type is incorrect\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Make sure all the required memory ops क्रम given memory type
	 * are available.
	 */
	अगर (memory == VB2_MEMORY_MMAP && __verअगरy_mmap_ops(q)) अणु
		dprपूर्णांकk(q, 1, "MMAP for current setup unsupported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (memory == VB2_MEMORY_USERPTR && __verअगरy_userptr_ops(q)) अणु
		dprपूर्णांकk(q, 1, "USERPTR for current setup unsupported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (memory == VB2_MEMORY_DMABUF && __verअगरy_dmabuf_ops(q)) अणु
		dprपूर्णांकk(q, 1, "DMABUF for current setup unsupported\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Place the busy tests at the end: -EBUSY can be ignored when
	 * create_bufs is called with count == 0, but count == 0 should still
	 * करो the memory and type validation.
	 */
	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "file io in progress\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vb2_verअगरy_memory_type);

पूर्णांक vb2_core_reqbufs(काष्ठा vb2_queue *q, क्रमागत vb2_memory memory,
		     अचिन्हित पूर्णांक *count)
अणु
	अचिन्हित पूर्णांक num_buffers, allocated_buffers, num_planes = 0;
	अचिन्हित plane_sizes[VB2_MAX_PLANES] = अणु पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (q->streaming) अणु
		dprपूर्णांकk(q, 1, "streaming active\n");
		वापस -EBUSY;
	पूर्ण

	अगर (q->रुकोing_in_dqbuf && *count) अणु
		dprपूर्णांकk(q, 1, "another dup()ped fd is waiting for a buffer\n");
		वापस -EBUSY;
	पूर्ण

	अगर (*count == 0 || q->num_buffers != 0 ||
	    (q->memory != VB2_MEMORY_UNKNOWN && q->memory != memory)) अणु
		/*
		 * We alपढ़ोy have buffers allocated, so first check अगर they
		 * are not in use and can be मुक्तd.
		 */
		mutex_lock(&q->mmap_lock);
		अगर (debug && q->memory == VB2_MEMORY_MMAP &&
		    __buffers_in_use(q))
			dprपूर्णांकk(q, 1, "memory in use, orphaning buffers\n");

		/*
		 * Call queue_cancel to clean up any buffers in the
		 * QUEUED state which is possible अगर buffers were prepared or
		 * queued without ever calling STREAMON.
		 */
		__vb2_queue_cancel(q);
		ret = __vb2_queue_मुक्त(q, q->num_buffers);
		mutex_unlock(&q->mmap_lock);
		अगर (ret)
			वापस ret;

		/*
		 * In हाल of REQBUFS(0) वापस immediately without calling
		 * driver's queue_setup() callback and allocating resources.
		 */
		अगर (*count == 0)
			वापस 0;
	पूर्ण

	/*
	 * Make sure the requested values and current शेषs are sane.
	 */
	WARN_ON(q->min_buffers_needed > VB2_MAX_FRAME);
	num_buffers = max_t(अचिन्हित पूर्णांक, *count, q->min_buffers_needed);
	num_buffers = min_t(अचिन्हित पूर्णांक, num_buffers, VB2_MAX_FRAME);
	स_रखो(q->alloc_devs, 0, माप(q->alloc_devs));
	q->memory = memory;

	/*
	 * Ask the driver how many buffers and planes per buffer it requires.
	 * Driver also sets the size and allocator context क्रम each plane.
	 */
	ret = call_qop(q, queue_setup, q, &num_buffers, &num_planes,
		       plane_sizes, q->alloc_devs);
	अगर (ret)
		वापस ret;

	/* Check that driver has set sane values */
	अगर (WARN_ON(!num_planes))
		वापस -EINVAL;

	क्रम (i = 0; i < num_planes; i++)
		अगर (WARN_ON(!plane_sizes[i]))
			वापस -EINVAL;

	/* Finally, allocate buffers and video memory */
	allocated_buffers =
		__vb2_queue_alloc(q, memory, num_buffers, num_planes, plane_sizes);
	अगर (allocated_buffers == 0) अणु
		dprपूर्णांकk(q, 1, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * There is no poपूर्णांक in continuing अगर we can't allocate the minimum
	 * number of buffers needed by this vb2_queue.
	 */
	अगर (allocated_buffers < q->min_buffers_needed)
		ret = -ENOMEM;

	/*
	 * Check अगर driver can handle the allocated number of buffers.
	 */
	अगर (!ret && allocated_buffers < num_buffers) अणु
		num_buffers = allocated_buffers;
		/*
		 * num_planes is set by the previous queue_setup(), but since it
		 * संकेतs to queue_setup() whether it is called from create_bufs()
		 * vs reqbufs() we zero it here to संकेत that queue_setup() is
		 * called क्रम the reqbufs() हाल.
		 */
		num_planes = 0;

		ret = call_qop(q, queue_setup, q, &num_buffers,
			       &num_planes, plane_sizes, q->alloc_devs);

		अगर (!ret && allocated_buffers < num_buffers)
			ret = -ENOMEM;

		/*
		 * Either the driver has accepted a smaller number of buffers,
		 * or .queue_setup() वापसed an error
		 */
	पूर्ण

	mutex_lock(&q->mmap_lock);
	q->num_buffers = allocated_buffers;

	अगर (ret < 0) अणु
		/*
		 * Note: __vb2_queue_मुक्त() will subtract 'allocated_buffers'
		 * from q->num_buffers.
		 */
		__vb2_queue_मुक्त(q, allocated_buffers);
		mutex_unlock(&q->mmap_lock);
		वापस ret;
	पूर्ण
	mutex_unlock(&q->mmap_lock);

	/*
	 * Return the number of successfully allocated buffers
	 * to the userspace.
	 */
	*count = allocated_buffers;
	q->रुकोing_क्रम_buffers = !q->is_output;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_reqbufs);

पूर्णांक vb2_core_create_bufs(काष्ठा vb2_queue *q, क्रमागत vb2_memory memory,
			 अचिन्हित पूर्णांक *count,
			 अचिन्हित पूर्णांक requested_planes,
			 स्थिर अचिन्हित पूर्णांक requested_sizes[])
अणु
	अचिन्हित पूर्णांक num_planes = 0, num_buffers, allocated_buffers;
	अचिन्हित plane_sizes[VB2_MAX_PLANES] = अणु पूर्ण;
	पूर्णांक ret;

	अगर (q->num_buffers == VB2_MAX_FRAME) अणु
		dprपूर्णांकk(q, 1, "maximum number of buffers already allocated\n");
		वापस -ENOBUFS;
	पूर्ण

	अगर (!q->num_buffers) अणु
		अगर (q->रुकोing_in_dqbuf && *count) अणु
			dprपूर्णांकk(q, 1, "another dup()ped fd is waiting for a buffer\n");
			वापस -EBUSY;
		पूर्ण
		स_रखो(q->alloc_devs, 0, माप(q->alloc_devs));
		q->memory = memory;
		q->रुकोing_क्रम_buffers = !q->is_output;
	पूर्ण अन्यथा अणु
		अगर (q->memory != memory) अणु
			dprपूर्णांकk(q, 1, "memory model mismatch\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	num_buffers = min(*count, VB2_MAX_FRAME - q->num_buffers);

	अगर (requested_planes && requested_sizes) अणु
		num_planes = requested_planes;
		स_नकल(plane_sizes, requested_sizes, माप(plane_sizes));
	पूर्ण

	/*
	 * Ask the driver, whether the requested number of buffers, planes per
	 * buffer and their sizes are acceptable
	 */
	ret = call_qop(q, queue_setup, q, &num_buffers,
		       &num_planes, plane_sizes, q->alloc_devs);
	अगर (ret)
		वापस ret;

	/* Finally, allocate buffers and video memory */
	allocated_buffers = __vb2_queue_alloc(q, memory, num_buffers,
				num_planes, plane_sizes);
	अगर (allocated_buffers == 0) अणु
		dprपूर्णांकk(q, 1, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Check अगर driver can handle the so far allocated number of buffers.
	 */
	अगर (allocated_buffers < num_buffers) अणु
		num_buffers = allocated_buffers;

		/*
		 * q->num_buffers contains the total number of buffers, that the
		 * queue driver has set up
		 */
		ret = call_qop(q, queue_setup, q, &num_buffers,
			       &num_planes, plane_sizes, q->alloc_devs);

		अगर (!ret && allocated_buffers < num_buffers)
			ret = -ENOMEM;

		/*
		 * Either the driver has accepted a smaller number of buffers,
		 * or .queue_setup() वापसed an error
		 */
	पूर्ण

	mutex_lock(&q->mmap_lock);
	q->num_buffers += allocated_buffers;

	अगर (ret < 0) अणु
		/*
		 * Note: __vb2_queue_मुक्त() will subtract 'allocated_buffers'
		 * from q->num_buffers.
		 */
		__vb2_queue_मुक्त(q, allocated_buffers);
		mutex_unlock(&q->mmap_lock);
		वापस -ENOMEM;
	पूर्ण
	mutex_unlock(&q->mmap_lock);

	/*
	 * Return the number of successfully allocated buffers
	 * to the userspace.
	 */
	*count = allocated_buffers;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_create_bufs);

व्योम *vb2_plane_vaddr(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no)
अणु
	अगर (plane_no >= vb->num_planes || !vb->planes[plane_no].mem_priv)
		वापस शून्य;

	वापस call_ptr_memop(vb, vaddr, vb->planes[plane_no].mem_priv);

पूर्ण
EXPORT_SYMBOL_GPL(vb2_plane_vaddr);

व्योम *vb2_plane_cookie(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no)
अणु
	अगर (plane_no >= vb->num_planes || !vb->planes[plane_no].mem_priv)
		वापस शून्य;

	वापस call_ptr_memop(vb, cookie, vb->planes[plane_no].mem_priv);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_plane_cookie);

व्योम vb2_buffer_करोne(काष्ठा vb2_buffer *vb, क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(vb->state != VB2_BUF_STATE_ACTIVE))
		वापस;

	अगर (WARN_ON(state != VB2_BUF_STATE_DONE &&
		    state != VB2_BUF_STATE_ERROR &&
		    state != VB2_BUF_STATE_QUEUED))
		state = VB2_BUF_STATE_ERROR;

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Although this is not a callback, it still करोes have to balance
	 * with the buf_queue op. So update this counter manually.
	 */
	vb->cnt_buf_करोne++;
#पूर्ण_अगर
	dprपूर्णांकk(q, 4, "done processing on buffer %d, state: %s\n",
		vb->index, vb2_state_name(state));

	अगर (state != VB2_BUF_STATE_QUEUED)
		__vb2_buf_mem_finish(vb);

	spin_lock_irqsave(&q->करोne_lock, flags);
	अगर (state == VB2_BUF_STATE_QUEUED) अणु
		vb->state = VB2_BUF_STATE_QUEUED;
	पूर्ण अन्यथा अणु
		/* Add the buffer to the करोne buffers list */
		list_add_tail(&vb->करोne_entry, &q->करोne_list);
		vb->state = state;
	पूर्ण
	atomic_dec(&q->owned_by_drv_count);

	अगर (state != VB2_BUF_STATE_QUEUED && vb->req_obj.req) अणु
		media_request_object_unbind(&vb->req_obj);
		media_request_object_put(&vb->req_obj);
	पूर्ण

	spin_unlock_irqrestore(&q->करोne_lock, flags);

	trace_vb2_buf_करोne(q, vb);

	चयन (state) अणु
	हाल VB2_BUF_STATE_QUEUED:
		वापस;
	शेष:
		/* Inक्रमm any processes that may be रुकोing क्रम buffers */
		wake_up(&q->करोne_wq);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vb2_buffer_करोne);

व्योम vb2_discard_करोne(काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_buffer *vb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->करोne_lock, flags);
	list_क्रम_each_entry(vb, &q->करोne_list, करोne_entry)
		vb->state = VB2_BUF_STATE_ERROR;
	spin_unlock_irqrestore(&q->करोne_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_discard_करोne);

/*
 * __prepare_mmap() - prepare an MMAP buffer
 */
अटल पूर्णांक __prepare_mmap(काष्ठा vb2_buffer *vb)
अणु
	पूर्णांक ret = 0;

	ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
			 vb, vb->planes);
	वापस ret ? ret : call_vb_qop(vb, buf_prepare, vb);
पूर्ण

/*
 * __prepare_userptr() - prepare a USERPTR buffer
 */
अटल पूर्णांक __prepare_userptr(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_plane planes[VB2_MAX_PLANES];
	काष्ठा vb2_queue *q = vb->vb2_queue;
	व्योम *mem_priv;
	अचिन्हित पूर्णांक plane;
	पूर्णांक ret = 0;
	bool reacquired = vb->planes[0].mem_priv == शून्य;

	स_रखो(planes, 0, माप(planes[0]) * vb->num_planes);
	/* Copy relevant inक्रमmation provided by the userspace */
	ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
			 vb, planes);
	अगर (ret)
		वापस ret;

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		/* Skip the plane अगर alपढ़ोy verअगरied */
		अगर (vb->planes[plane].m.userptr &&
			vb->planes[plane].m.userptr == planes[plane].m.userptr
			&& vb->planes[plane].length == planes[plane].length)
			जारी;

		dprपूर्णांकk(q, 3, "userspace address for plane %d changed, reacquiring memory\n",
			plane);

		/* Check अगर the provided plane buffer is large enough */
		अगर (planes[plane].length < vb->planes[plane].min_length) अणु
			dprपूर्णांकk(q, 1, "provided buffer size %u is less than setup size %u for plane %d\n",
						planes[plane].length,
						vb->planes[plane].min_length,
						plane);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		/* Release previously acquired memory अगर present */
		अगर (vb->planes[plane].mem_priv) अणु
			अगर (!reacquired) अणु
				reacquired = true;
				vb->copied_बारtamp = 0;
				call_व्योम_vb_qop(vb, buf_cleanup, vb);
			पूर्ण
			call_व्योम_memop(vb, put_userptr, vb->planes[plane].mem_priv);
		पूर्ण

		vb->planes[plane].mem_priv = शून्य;
		vb->planes[plane].bytesused = 0;
		vb->planes[plane].length = 0;
		vb->planes[plane].m.userptr = 0;
		vb->planes[plane].data_offset = 0;

		/* Acquire each plane's memory */
		mem_priv = call_ptr_memop(vb, get_userptr,
				q->alloc_devs[plane] ? : q->dev,
				planes[plane].m.userptr,
				planes[plane].length, q->dma_dir);
		अगर (IS_ERR(mem_priv)) अणु
			dprपूर्णांकk(q, 1, "failed acquiring userspace memory for plane %d\n",
				plane);
			ret = PTR_ERR(mem_priv);
			जाओ err;
		पूर्ण
		vb->planes[plane].mem_priv = mem_priv;
	पूर्ण

	/*
	 * Now that everything is in order, copy relevant inक्रमmation
	 * provided by userspace.
	 */
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		vb->planes[plane].bytesused = planes[plane].bytesused;
		vb->planes[plane].length = planes[plane].length;
		vb->planes[plane].m.userptr = planes[plane].m.userptr;
		vb->planes[plane].data_offset = planes[plane].data_offset;
	पूर्ण

	अगर (reacquired) अणु
		/*
		 * One or more planes changed, so we must call buf_init to करो
		 * the driver-specअगरic initialization on the newly acquired
		 * buffer, अगर provided.
		 */
		ret = call_vb_qop(vb, buf_init, vb);
		अगर (ret) अणु
			dprपूर्णांकk(q, 1, "buffer initialization failed\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = call_vb_qop(vb, buf_prepare, vb);
	अगर (ret) अणु
		dprपूर्णांकk(q, 1, "buffer preparation failed\n");
		call_व्योम_vb_qop(vb, buf_cleanup, vb);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	/* In हाल of errors, release planes that were alपढ़ोy acquired */
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		अगर (vb->planes[plane].mem_priv)
			call_व्योम_memop(vb, put_userptr,
				vb->planes[plane].mem_priv);
		vb->planes[plane].mem_priv = शून्य;
		vb->planes[plane].m.userptr = 0;
		vb->planes[plane].length = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * __prepare_dmabuf() - prepare a DMABUF buffer
 */
अटल पूर्णांक __prepare_dmabuf(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_plane planes[VB2_MAX_PLANES];
	काष्ठा vb2_queue *q = vb->vb2_queue;
	व्योम *mem_priv;
	अचिन्हित पूर्णांक plane;
	पूर्णांक ret = 0;
	bool reacquired = vb->planes[0].mem_priv == शून्य;

	स_रखो(planes, 0, माप(planes[0]) * vb->num_planes);
	/* Copy relevant inक्रमmation provided by the userspace */
	ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
			 vb, planes);
	अगर (ret)
		वापस ret;

	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		काष्ठा dma_buf *dbuf = dma_buf_get(planes[plane].m.fd);

		अगर (IS_ERR_OR_शून्य(dbuf)) अणु
			dprपूर्णांकk(q, 1, "invalid dmabuf fd for plane %d\n",
				plane);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		/* use DMABUF size अगर length is not provided */
		अगर (planes[plane].length == 0)
			planes[plane].length = dbuf->size;

		अगर (planes[plane].length < vb->planes[plane].min_length) अणु
			dprपूर्णांकk(q, 1, "invalid dmabuf length %u for plane %d, minimum length %u\n",
				planes[plane].length, plane,
				vb->planes[plane].min_length);
			dma_buf_put(dbuf);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		/* Skip the plane अगर alपढ़ोy verअगरied */
		अगर (dbuf == vb->planes[plane].dbuf &&
			vb->planes[plane].length == planes[plane].length) अणु
			dma_buf_put(dbuf);
			जारी;
		पूर्ण

		dprपूर्णांकk(q, 3, "buffer for plane %d changed\n", plane);

		अगर (!reacquired) अणु
			reacquired = true;
			vb->copied_बारtamp = 0;
			call_व्योम_vb_qop(vb, buf_cleanup, vb);
		पूर्ण

		/* Release previously acquired memory अगर present */
		__vb2_plane_dmabuf_put(vb, &vb->planes[plane]);
		vb->planes[plane].bytesused = 0;
		vb->planes[plane].length = 0;
		vb->planes[plane].m.fd = 0;
		vb->planes[plane].data_offset = 0;

		/* Acquire each plane's memory */
		mem_priv = call_ptr_memop(vb, attach_dmabuf,
				q->alloc_devs[plane] ? : q->dev,
				dbuf, planes[plane].length, q->dma_dir);
		अगर (IS_ERR(mem_priv)) अणु
			dprपूर्णांकk(q, 1, "failed to attach dmabuf\n");
			ret = PTR_ERR(mem_priv);
			dma_buf_put(dbuf);
			जाओ err;
		पूर्ण

		vb->planes[plane].dbuf = dbuf;
		vb->planes[plane].mem_priv = mem_priv;
	पूर्ण

	/*
	 * This pins the buffer(s) with dma_buf_map_attachment()). It's करोne
	 * here instead just beक्रमe the DMA, जबतक queueing the buffer(s) so
	 * userspace knows sooner rather than later अगर the dma-buf map fails.
	 */
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		अगर (vb->planes[plane].dbuf_mapped)
			जारी;

		ret = call_memop(vb, map_dmabuf, vb->planes[plane].mem_priv);
		अगर (ret) अणु
			dprपूर्णांकk(q, 1, "failed to map dmabuf for plane %d\n",
				plane);
			जाओ err;
		पूर्ण
		vb->planes[plane].dbuf_mapped = 1;
	पूर्ण

	/*
	 * Now that everything is in order, copy relevant inक्रमmation
	 * provided by userspace.
	 */
	क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
		vb->planes[plane].bytesused = planes[plane].bytesused;
		vb->planes[plane].length = planes[plane].length;
		vb->planes[plane].m.fd = planes[plane].m.fd;
		vb->planes[plane].data_offset = planes[plane].data_offset;
	पूर्ण

	अगर (reacquired) अणु
		/*
		 * Call driver-specअगरic initialization on the newly acquired buffer,
		 * अगर provided.
		 */
		ret = call_vb_qop(vb, buf_init, vb);
		अगर (ret) अणु
			dprपूर्णांकk(q, 1, "buffer initialization failed\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = call_vb_qop(vb, buf_prepare, vb);
	अगर (ret) अणु
		dprपूर्णांकk(q, 1, "buffer preparation failed\n");
		call_व्योम_vb_qop(vb, buf_cleanup, vb);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	/* In हाल of errors, release planes that were alपढ़ोy acquired */
	__vb2_buf_dmabuf_put(vb);

	वापस ret;
पूर्ण

/*
 * __enqueue_in_driver() - enqueue a vb2_buffer in driver क्रम processing
 */
अटल व्योम __enqueue_in_driver(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;

	vb->state = VB2_BUF_STATE_ACTIVE;
	atomic_inc(&q->owned_by_drv_count);

	trace_vb2_buf_queue(q, vb);

	call_व्योम_vb_qop(vb, buf_queue, vb);
पूर्ण

अटल पूर्णांक __buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	क्रमागत vb2_buffer_state orig_state = vb->state;
	पूर्णांक ret;

	अगर (q->error) अणु
		dprपूर्णांकk(q, 1, "fatal error occurred on queue\n");
		वापस -EIO;
	पूर्ण

	अगर (vb->prepared)
		वापस 0;
	WARN_ON(vb->synced);

	अगर (q->is_output) अणु
		ret = call_vb_qop(vb, buf_out_validate, vb);
		अगर (ret) अणु
			dprपूर्णांकk(q, 1, "buffer validation failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	vb->state = VB2_BUF_STATE_PREPARING;

	चयन (q->memory) अणु
	हाल VB2_MEMORY_MMAP:
		ret = __prepare_mmap(vb);
		अवरोध;
	हाल VB2_MEMORY_USERPTR:
		ret = __prepare_userptr(vb);
		अवरोध;
	हाल VB2_MEMORY_DMABUF:
		ret = __prepare_dmabuf(vb);
		अवरोध;
	शेष:
		WARN(1, "Invalid queue type\n");
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		dprपूर्णांकk(q, 1, "buffer preparation failed: %d\n", ret);
		vb->state = orig_state;
		वापस ret;
	पूर्ण

	__vb2_buf_mem_prepare(vb);
	vb->prepared = 1;
	vb->state = orig_state;

	वापस 0;
पूर्ण

अटल पूर्णांक vb2_req_prepare(काष्ठा media_request_object *obj)
अणु
	काष्ठा vb2_buffer *vb = container_of(obj, काष्ठा vb2_buffer, req_obj);
	पूर्णांक ret;

	अगर (WARN_ON(vb->state != VB2_BUF_STATE_IN_REQUEST))
		वापस -EINVAL;

	mutex_lock(vb->vb2_queue->lock);
	ret = __buf_prepare(vb);
	mutex_unlock(vb->vb2_queue->lock);
	वापस ret;
पूर्ण

अटल व्योम __vb2_dqbuf(काष्ठा vb2_buffer *vb);

अटल व्योम vb2_req_unprepare(काष्ठा media_request_object *obj)
अणु
	काष्ठा vb2_buffer *vb = container_of(obj, काष्ठा vb2_buffer, req_obj);

	mutex_lock(vb->vb2_queue->lock);
	__vb2_dqbuf(vb);
	vb->state = VB2_BUF_STATE_IN_REQUEST;
	mutex_unlock(vb->vb2_queue->lock);
	WARN_ON(!vb->req_obj.req);
पूर्ण

पूर्णांक vb2_core_qbuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb,
		  काष्ठा media_request *req);

अटल व्योम vb2_req_queue(काष्ठा media_request_object *obj)
अणु
	काष्ठा vb2_buffer *vb = container_of(obj, काष्ठा vb2_buffer, req_obj);

	mutex_lock(vb->vb2_queue->lock);
	vb2_core_qbuf(vb->vb2_queue, vb->index, शून्य, शून्य);
	mutex_unlock(vb->vb2_queue->lock);
पूर्ण

अटल व्योम vb2_req_unbind(काष्ठा media_request_object *obj)
अणु
	काष्ठा vb2_buffer *vb = container_of(obj, काष्ठा vb2_buffer, req_obj);

	अगर (vb->state == VB2_BUF_STATE_IN_REQUEST)
		call_व्योम_bufop(vb->vb2_queue, init_buffer, vb);
पूर्ण

अटल व्योम vb2_req_release(काष्ठा media_request_object *obj)
अणु
	काष्ठा vb2_buffer *vb = container_of(obj, काष्ठा vb2_buffer, req_obj);

	अगर (vb->state == VB2_BUF_STATE_IN_REQUEST) अणु
		vb->state = VB2_BUF_STATE_DEQUEUED;
		अगर (vb->request)
			media_request_put(vb->request);
		vb->request = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा media_request_object_ops vb2_core_req_ops = अणु
	.prepare = vb2_req_prepare,
	.unprepare = vb2_req_unprepare,
	.queue = vb2_req_queue,
	.unbind = vb2_req_unbind,
	.release = vb2_req_release,
पूर्ण;

bool vb2_request_object_is_buffer(काष्ठा media_request_object *obj)
अणु
	वापस obj->ops == &vb2_core_req_ops;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_request_object_is_buffer);

अचिन्हित पूर्णांक vb2_request_buffer_cnt(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक buffer_cnt = 0;

	spin_lock_irqsave(&req->lock, flags);
	list_क्रम_each_entry(obj, &req->objects, list)
		अगर (vb2_request_object_is_buffer(obj))
			buffer_cnt++;
	spin_unlock_irqrestore(&req->lock, flags);

	वापस buffer_cnt;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_request_buffer_cnt);

पूर्णांक vb2_core_prepare_buf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb)
अणु
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	vb = q->bufs[index];
	अगर (vb->state != VB2_BUF_STATE_DEQUEUED) अणु
		dprपूर्णांकk(q, 1, "invalid buffer state %s\n",
			vb2_state_name(vb->state));
		वापस -EINVAL;
	पूर्ण
	अगर (vb->prepared) अणु
		dprपूर्णांकk(q, 1, "buffer already prepared\n");
		वापस -EINVAL;
	पूर्ण

	ret = __buf_prepare(vb);
	अगर (ret)
		वापस ret;

	/* Fill buffer inक्रमmation क्रम the userspace */
	call_व्योम_bufop(q, fill_user_buffer, vb, pb);

	dprपूर्णांकk(q, 2, "prepare of buffer %d succeeded\n", vb->index);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_prepare_buf);

/*
 * vb2_start_streaming() - Attempt to start streaming.
 * @q:		videobuf2 queue
 *
 * Attempt to start streaming. When this function is called there must be
 * at least q->min_buffers_needed buffers queued up (i.e. the minimum
 * number of buffers required क्रम the DMA engine to function). If the
 * @start_streaming op fails it is supposed to वापस all the driver-owned
 * buffers back to vb2 in state QUEUED. Check अगर that happened and अगर
 * not warn and reclaim them क्रमcefully.
 */
अटल पूर्णांक vb2_start_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	/*
	 * If any buffers were queued beक्रमe streamon,
	 * we can now pass them to driver क्रम processing.
	 */
	list_क्रम_each_entry(vb, &q->queued_list, queued_entry)
		__enqueue_in_driver(vb);

	/* Tell the driver to start streaming */
	q->start_streaming_called = 1;
	ret = call_qop(q, start_streaming, q,
		       atomic_पढ़ो(&q->owned_by_drv_count));
	अगर (!ret)
		वापस 0;

	q->start_streaming_called = 0;

	dprपूर्णांकk(q, 1, "driver refused to start streaming\n");
	/*
	 * If you see this warning, then the driver isn't cleaning up properly
	 * after a failed start_streaming(). See the start_streaming()
	 * करोcumentation in videobuf2-core.h क्रम more inक्रमmation how buffers
	 * should be वापसed to vb2 in start_streaming().
	 */
	अगर (WARN_ON(atomic_पढ़ो(&q->owned_by_drv_count))) अणु
		अचिन्हित i;

		/*
		 * Forcefully reclaim buffers अगर the driver did not
		 * correctly वापस them to vb2.
		 */
		क्रम (i = 0; i < q->num_buffers; ++i) अणु
			vb = q->bufs[i];
			अगर (vb->state == VB2_BUF_STATE_ACTIVE)
				vb2_buffer_करोne(vb, VB2_BUF_STATE_QUEUED);
		पूर्ण
		/* Must be zero now */
		WARN_ON(atomic_पढ़ो(&q->owned_by_drv_count));
	पूर्ण
	/*
	 * If करोne_list is not empty, then start_streaming() didn't call
	 * vb2_buffer_करोne(vb, VB2_BUF_STATE_QUEUED) but STATE_ERROR or
	 * STATE_DONE.
	 */
	WARN_ON(!list_empty(&q->करोne_list));
	वापस ret;
पूर्ण

पूर्णांक vb2_core_qbuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक index, व्योम *pb,
		  काष्ठा media_request *req)
अणु
	काष्ठा vb2_buffer *vb;
	पूर्णांक ret;

	अगर (q->error) अणु
		dprपूर्णांकk(q, 1, "fatal error occurred on queue\n");
		वापस -EIO;
	पूर्ण

	vb = q->bufs[index];

	अगर (!req && vb->state != VB2_BUF_STATE_IN_REQUEST &&
	    q->requires_requests) अणु
		dprपूर्णांकk(q, 1, "qbuf requires a request\n");
		वापस -EBADR;
	पूर्ण

	अगर ((req && q->uses_qbuf) ||
	    (!req && vb->state != VB2_BUF_STATE_IN_REQUEST &&
	     q->uses_requests)) अणु
		dprपूर्णांकk(q, 1, "queue in wrong mode (qbuf vs requests)\n");
		वापस -EBUSY;
	पूर्ण

	अगर (req) अणु
		पूर्णांक ret;

		q->uses_requests = 1;
		अगर (vb->state != VB2_BUF_STATE_DEQUEUED) अणु
			dprपूर्णांकk(q, 1, "buffer %d not in dequeued state\n",
				vb->index);
			वापस -EINVAL;
		पूर्ण

		अगर (q->is_output && !vb->prepared) अणु
			ret = call_vb_qop(vb, buf_out_validate, vb);
			अगर (ret) अणु
				dprपूर्णांकk(q, 1, "buffer validation failed\n");
				वापस ret;
			पूर्ण
		पूर्ण

		media_request_object_init(&vb->req_obj);

		/* Make sure the request is in a safe state क्रम updating. */
		ret = media_request_lock_क्रम_update(req);
		अगर (ret)
			वापस ret;
		ret = media_request_object_bind(req, &vb2_core_req_ops,
						q, true, &vb->req_obj);
		media_request_unlock_क्रम_update(req);
		अगर (ret)
			वापस ret;

		vb->state = VB2_BUF_STATE_IN_REQUEST;

		/*
		 * Increment the refcount and store the request.
		 * The request refcount is decremented again when the
		 * buffer is dequeued. This is to prevent vb2_buffer_करोne()
		 * from मुक्तing the request from पूर्णांकerrupt context, which can
		 * happen अगर the application बंदd the request fd after
		 * queueing the request.
		 */
		media_request_get(req);
		vb->request = req;

		/* Fill buffer inक्रमmation क्रम the userspace */
		अगर (pb) अणु
			call_व्योम_bufop(q, copy_बारtamp, vb, pb);
			call_व्योम_bufop(q, fill_user_buffer, vb, pb);
		पूर्ण

		dprपूर्णांकk(q, 2, "qbuf of buffer %d succeeded\n", vb->index);
		वापस 0;
	पूर्ण

	अगर (vb->state != VB2_BUF_STATE_IN_REQUEST)
		q->uses_qbuf = 1;

	चयन (vb->state) अणु
	हाल VB2_BUF_STATE_DEQUEUED:
	हाल VB2_BUF_STATE_IN_REQUEST:
		अगर (!vb->prepared) अणु
			ret = __buf_prepare(vb);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल VB2_BUF_STATE_PREPARING:
		dprपूर्णांकk(q, 1, "buffer still being prepared\n");
		वापस -EINVAL;
	शेष:
		dprपूर्णांकk(q, 1, "invalid buffer state %s\n",
			vb2_state_name(vb->state));
		वापस -EINVAL;
	पूर्ण

	/*
	 * Add to the queued buffers list, a buffer will stay on it until
	 * dequeued in dqbuf.
	 */
	list_add_tail(&vb->queued_entry, &q->queued_list);
	q->queued_count++;
	q->रुकोing_क्रम_buffers = false;
	vb->state = VB2_BUF_STATE_QUEUED;

	अगर (pb)
		call_व्योम_bufop(q, copy_बारtamp, vb, pb);

	trace_vb2_qbuf(q, vb);

	/*
	 * If alपढ़ोy streaming, give the buffer to driver क्रम processing.
	 * If not, the buffer will be given to driver on next streamon.
	 */
	अगर (q->start_streaming_called)
		__enqueue_in_driver(vb);

	/* Fill buffer inक्रमmation क्रम the userspace */
	अगर (pb)
		call_व्योम_bufop(q, fill_user_buffer, vb, pb);

	/*
	 * If streamon has been called, and we haven't yet called
	 * start_streaming() since not enough buffers were queued, and
	 * we now have reached the minimum number of queued buffers,
	 * then we can finally call start_streaming().
	 */
	अगर (q->streaming && !q->start_streaming_called &&
	    q->queued_count >= q->min_buffers_needed) अणु
		ret = vb2_start_streaming(q);
		अगर (ret)
			वापस ret;
	पूर्ण

	dprपूर्णांकk(q, 2, "qbuf of buffer %d succeeded\n", vb->index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_qbuf);

/*
 * __vb2_रुको_क्रम_करोne_vb() - रुको क्रम a buffer to become available
 * क्रम dequeuing
 *
 * Will sleep अगर required क्रम nonblocking == false.
 */
अटल पूर्णांक __vb2_रुको_क्रम_करोne_vb(काष्ठा vb2_queue *q, पूर्णांक nonblocking)
अणु
	/*
	 * All operations on vb_करोne_list are perक्रमmed under करोne_lock
	 * spinlock protection. However, buffers may be हटाओd from
	 * it and वापसed to userspace only जबतक holding both driver's
	 * lock and the करोne_lock spinlock. Thus we can be sure that as
	 * दीर्घ as we hold the driver's lock, the list will reमुख्य not
	 * empty अगर list_empty() check succeeds.
	 */

	क्रम (;;) अणु
		पूर्णांक ret;

		अगर (q->रुकोing_in_dqbuf) अणु
			dprपूर्णांकk(q, 1, "another dup()ped fd is waiting for a buffer\n");
			वापस -EBUSY;
		पूर्ण

		अगर (!q->streaming) अणु
			dprपूर्णांकk(q, 1, "streaming off, will not wait for buffers\n");
			वापस -EINVAL;
		पूर्ण

		अगर (q->error) अणु
			dprपूर्णांकk(q, 1, "Queue in error state, will not wait for buffers\n");
			वापस -EIO;
		पूर्ण

		अगर (q->last_buffer_dequeued) अणु
			dprपूर्णांकk(q, 3, "last buffer dequeued already, will not wait for buffers\n");
			वापस -EPIPE;
		पूर्ण

		अगर (!list_empty(&q->करोne_list)) अणु
			/*
			 * Found a buffer that we were रुकोing क्रम.
			 */
			अवरोध;
		पूर्ण

		अगर (nonblocking) अणु
			dprपूर्णांकk(q, 3, "nonblocking and no buffers to dequeue, will not wait\n");
			वापस -EAGAIN;
		पूर्ण

		q->रुकोing_in_dqbuf = 1;
		/*
		 * We are streaming and blocking, रुको क्रम another buffer to
		 * become पढ़ोy or क्रम streamoff. Driver's lock is released to
		 * allow streamoff or qbuf to be called जबतक रुकोing.
		 */
		call_व्योम_qop(q, रुको_prepare, q);

		/*
		 * All locks have been released, it is safe to sleep now.
		 */
		dprपूर्णांकk(q, 3, "will sleep waiting for buffers\n");
		ret = रुको_event_पूर्णांकerruptible(q->करोne_wq,
				!list_empty(&q->करोne_list) || !q->streaming ||
				q->error);

		/*
		 * We need to reevaluate both conditions again after reacquiring
		 * the locks or वापस an error अगर one occurred.
		 */
		call_व्योम_qop(q, रुको_finish, q);
		q->रुकोing_in_dqbuf = 0;
		अगर (ret) अणु
			dprपूर्णांकk(q, 1, "sleep was interrupted\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * __vb2_get_करोne_vb() - get a buffer पढ़ोy क्रम dequeuing
 *
 * Will sleep अगर required क्रम nonblocking == false.
 */
अटल पूर्णांक __vb2_get_करोne_vb(काष्ठा vb2_queue *q, काष्ठा vb2_buffer **vb,
			     व्योम *pb, पूर्णांक nonblocking)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * Wait क्रम at least one buffer to become available on the करोne_list.
	 */
	ret = __vb2_रुको_क्रम_करोne_vb(q, nonblocking);
	अगर (ret)
		वापस ret;

	/*
	 * Driver's lock has been held since we last verअगरied that करोne_list
	 * is not empty, so no need क्रम another list_empty(करोne_list) check.
	 */
	spin_lock_irqsave(&q->करोne_lock, flags);
	*vb = list_first_entry(&q->करोne_list, काष्ठा vb2_buffer, करोne_entry);
	/*
	 * Only हटाओ the buffer from करोne_list अगर all planes can be
	 * handled. Some हालs such as V4L2 file I/O and DVB have pb
	 * == शून्य; skip the check then as there's nothing to verअगरy.
	 */
	अगर (pb)
		ret = call_bufop(q, verअगरy_planes_array, *vb, pb);
	अगर (!ret)
		list_del(&(*vb)->करोne_entry);
	spin_unlock_irqrestore(&q->करोne_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक vb2_रुको_क्रम_all_buffers(काष्ठा vb2_queue *q)
अणु
	अगर (!q->streaming) अणु
		dprपूर्णांकk(q, 1, "streaming off, will not wait for buffers\n");
		वापस -EINVAL;
	पूर्ण

	अगर (q->start_streaming_called)
		रुको_event(q->करोne_wq, !atomic_पढ़ो(&q->owned_by_drv_count));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_रुको_क्रम_all_buffers);

/*
 * __vb2_dqbuf() - bring back the buffer to the DEQUEUED state
 */
अटल व्योम __vb2_dqbuf(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;

	/* nothing to करो अगर the buffer is alपढ़ोy dequeued */
	अगर (vb->state == VB2_BUF_STATE_DEQUEUED)
		वापस;

	vb->state = VB2_BUF_STATE_DEQUEUED;

	call_व्योम_bufop(q, init_buffer, vb);
पूर्ण

पूर्णांक vb2_core_dqbuf(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक *pindex, व्योम *pb,
		   bool nonblocking)
अणु
	काष्ठा vb2_buffer *vb = शून्य;
	पूर्णांक ret;

	ret = __vb2_get_करोne_vb(q, &vb, pb, nonblocking);
	अगर (ret < 0)
		वापस ret;

	चयन (vb->state) अणु
	हाल VB2_BUF_STATE_DONE:
		dprपूर्णांकk(q, 3, "returning done buffer\n");
		अवरोध;
	हाल VB2_BUF_STATE_ERROR:
		dprपूर्णांकk(q, 3, "returning done buffer with errors\n");
		अवरोध;
	शेष:
		dprपूर्णांकk(q, 1, "invalid buffer state %s\n",
			vb2_state_name(vb->state));
		वापस -EINVAL;
	पूर्ण

	call_व्योम_vb_qop(vb, buf_finish, vb);
	vb->prepared = 0;

	अगर (pindex)
		*pindex = vb->index;

	/* Fill buffer inक्रमmation क्रम the userspace */
	अगर (pb)
		call_व्योम_bufop(q, fill_user_buffer, vb, pb);

	/* Remove from videobuf queue */
	list_del(&vb->queued_entry);
	q->queued_count--;

	trace_vb2_dqbuf(q, vb);

	/* go back to dequeued state */
	__vb2_dqbuf(vb);

	अगर (WARN_ON(vb->req_obj.req)) अणु
		media_request_object_unbind(&vb->req_obj);
		media_request_object_put(&vb->req_obj);
	पूर्ण
	अगर (vb->request)
		media_request_put(vb->request);
	vb->request = शून्य;

	dprपूर्णांकk(q, 2, "dqbuf of buffer %d, state: %s\n",
		vb->index, vb2_state_name(vb->state));

	वापस 0;

पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_dqbuf);

/*
 * __vb2_queue_cancel() - cancel and stop (छोड़ो) streaming
 *
 * Removes all queued buffers from driver's queue and all buffers queued by
 * userspace from videobuf's queue. Returns to state after reqbufs.
 */
अटल व्योम __vb2_queue_cancel(काष्ठा vb2_queue *q)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * Tell driver to stop all transactions and release all queued
	 * buffers.
	 */
	अगर (q->start_streaming_called)
		call_व्योम_qop(q, stop_streaming, q);

	/*
	 * If you see this warning, then the driver isn't cleaning up properly
	 * in stop_streaming(). See the stop_streaming() करोcumentation in
	 * videobuf2-core.h क्रम more inक्रमmation how buffers should be वापसed
	 * to vb2 in stop_streaming().
	 */
	अगर (WARN_ON(atomic_पढ़ो(&q->owned_by_drv_count))) अणु
		क्रम (i = 0; i < q->num_buffers; ++i)
			अगर (q->bufs[i]->state == VB2_BUF_STATE_ACTIVE) अणु
				pr_warn("driver bug: stop_streaming operation is leaving buf %p in active state\n",
					q->bufs[i]);
				vb2_buffer_करोne(q->bufs[i], VB2_BUF_STATE_ERROR);
			पूर्ण
		/* Must be zero now */
		WARN_ON(atomic_पढ़ो(&q->owned_by_drv_count));
	पूर्ण

	q->streaming = 0;
	q->start_streaming_called = 0;
	q->queued_count = 0;
	q->error = 0;
	q->uses_requests = 0;
	q->uses_qbuf = 0;

	/*
	 * Remove all buffers from videobuf's list...
	 */
	INIT_LIST_HEAD(&q->queued_list);
	/*
	 * ...and करोne list; userspace will not receive any buffers it
	 * has not alपढ़ोy dequeued beक्रमe initiating cancel.
	 */
	INIT_LIST_HEAD(&q->करोne_list);
	atomic_set(&q->owned_by_drv_count, 0);
	wake_up_all(&q->करोne_wq);

	/*
	 * Reinitialize all buffers क्रम next use.
	 * Make sure to call buf_finish क्रम any queued buffers. Normally
	 * that's done in dqbuf, but that's not going to happen when we
	 * cancel the whole queue. Note: this code beदीर्घs here, not in
	 * __vb2_dqbuf() since in vb2_core_dqbuf() there is a critical
	 * call to __fill_user_buffer() after buf_finish(). That order can't
	 * be changed, so we can't move the buf_finish() to __vb2_dqbuf().
	 */
	क्रम (i = 0; i < q->num_buffers; ++i) अणु
		काष्ठा vb2_buffer *vb = q->bufs[i];
		काष्ठा media_request *req = vb->req_obj.req;

		/*
		 * If a request is associated with this buffer, then
		 * call buf_request_cancel() to give the driver to complete()
		 * related request objects. Otherwise those objects would
		 * never complete.
		 */
		अगर (req) अणु
			क्रमागत media_request_state state;
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&req->lock, flags);
			state = req->state;
			spin_unlock_irqrestore(&req->lock, flags);

			अगर (state == MEDIA_REQUEST_STATE_QUEUED)
				call_व्योम_vb_qop(vb, buf_request_complete, vb);
		पूर्ण

		__vb2_buf_mem_finish(vb);

		अगर (vb->prepared) अणु
			call_व्योम_vb_qop(vb, buf_finish, vb);
			vb->prepared = 0;
		पूर्ण
		__vb2_dqbuf(vb);

		अगर (vb->req_obj.req) अणु
			media_request_object_unbind(&vb->req_obj);
			media_request_object_put(&vb->req_obj);
		पूर्ण
		अगर (vb->request)
			media_request_put(vb->request);
		vb->request = शून्य;
		vb->copied_बारtamp = 0;
	पूर्ण
पूर्ण

पूर्णांक vb2_core_streamon(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक ret;

	अगर (type != q->type) अणु
		dprपूर्णांकk(q, 1, "invalid stream type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (q->streaming) अणु
		dprपूर्णांकk(q, 3, "already streaming\n");
		वापस 0;
	पूर्ण

	अगर (!q->num_buffers) अणु
		dprपूर्णांकk(q, 1, "no buffers have been allocated\n");
		वापस -EINVAL;
	पूर्ण

	अगर (q->num_buffers < q->min_buffers_needed) अणु
		dprपूर्णांकk(q, 1, "need at least %u allocated buffers\n",
				q->min_buffers_needed);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Tell driver to start streaming provided sufficient buffers
	 * are available.
	 */
	अगर (q->queued_count >= q->min_buffers_needed) अणु
		ret = v4l_vb2q_enable_media_source(q);
		अगर (ret)
			वापस ret;
		ret = vb2_start_streaming(q);
		अगर (ret)
			वापस ret;
	पूर्ण

	q->streaming = 1;

	dprपूर्णांकk(q, 3, "successful\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_streamon);

व्योम vb2_queue_error(काष्ठा vb2_queue *q)
अणु
	q->error = 1;

	wake_up_all(&q->करोne_wq);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_queue_error);

पूर्णांक vb2_core_streamoff(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक type)
अणु
	अगर (type != q->type) अणु
		dprपूर्णांकk(q, 1, "invalid stream type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Cancel will छोड़ो streaming and हटाओ all buffers from the driver
	 * and videobuf, effectively वापसing control over them to userspace.
	 *
	 * Note that we करो this even अगर q->streaming == 0: अगर you prepare or
	 * queue buffers, and then call streamoff without ever having called
	 * streamon, you would still expect those buffers to be वापसed to
	 * their normal dequeued state.
	 */
	__vb2_queue_cancel(q);
	q->रुकोing_क्रम_buffers = !q->is_output;
	q->last_buffer_dequeued = false;

	dprपूर्णांकk(q, 3, "successful\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_streamoff);

/*
 * __find_plane_by_offset() - find plane associated with the given offset off
 */
अटल पूर्णांक __find_plane_by_offset(काष्ठा vb2_queue *q, अचिन्हित दीर्घ off,
			अचिन्हित पूर्णांक *_buffer, अचिन्हित पूर्णांक *_plane)
अणु
	काष्ठा vb2_buffer *vb;
	अचिन्हित पूर्णांक buffer, plane;

	/*
	 * Go over all buffers and their planes, comparing the given offset
	 * with an offset asचिन्हित to each plane. If a match is found,
	 * वापस its buffer and plane numbers.
	 */
	क्रम (buffer = 0; buffer < q->num_buffers; ++buffer) अणु
		vb = q->bufs[buffer];

		क्रम (plane = 0; plane < vb->num_planes; ++plane) अणु
			अगर (vb->planes[plane].m.offset == off) अणु
				*_buffer = buffer;
				*_plane = plane;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक vb2_core_expbuf(काष्ठा vb2_queue *q, पूर्णांक *fd, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक plane, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vb2_buffer *vb = शून्य;
	काष्ठा vb2_plane *vb_plane;
	पूर्णांक ret;
	काष्ठा dma_buf *dbuf;

	अगर (q->memory != VB2_MEMORY_MMAP) अणु
		dprपूर्णांकk(q, 1, "queue is not currently set up for mmap\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!q->mem_ops->get_dmabuf) अणु
		dprपूर्णांकk(q, 1, "queue does not support DMA buffer exporting\n");
		वापस -EINVAL;
	पूर्ण

	अगर (flags & ~(O_CLOEXEC | O_ACCMODE)) अणु
		dprपूर्णांकk(q, 1, "queue does support only O_CLOEXEC and access mode flags\n");
		वापस -EINVAL;
	पूर्ण

	अगर (type != q->type) अणु
		dprपूर्णांकk(q, 1, "invalid buffer type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (index >= q->num_buffers) अणु
		dprपूर्णांकk(q, 1, "buffer index out of range\n");
		वापस -EINVAL;
	पूर्ण

	vb = q->bufs[index];

	अगर (plane >= vb->num_planes) अणु
		dprपूर्णांकk(q, 1, "buffer plane out of range\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "expbuf: file io in progress\n");
		वापस -EBUSY;
	पूर्ण

	vb_plane = &vb->planes[plane];

	dbuf = call_ptr_memop(vb, get_dmabuf, vb_plane->mem_priv,
				flags & O_ACCMODE);
	अगर (IS_ERR_OR_शून्य(dbuf)) अणु
		dprपूर्णांकk(q, 1, "failed to export buffer %d, plane %d\n",
			index, plane);
		वापस -EINVAL;
	पूर्ण

	ret = dma_buf_fd(dbuf, flags & ~O_ACCMODE);
	अगर (ret < 0) अणु
		dprपूर्णांकk(q, 3, "buffer %d, plane %d failed to export (%d)\n",
			index, plane, ret);
		dma_buf_put(dbuf);
		वापस ret;
	पूर्ण

	dprपूर्णांकk(q, 3, "buffer %d, plane %d exported as %d descriptor\n",
		index, plane, ret);
	*fd = ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_expbuf);

पूर्णांक vb2_mmap(काष्ठा vb2_queue *q, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ off = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा vb2_buffer *vb;
	अचिन्हित पूर्णांक buffer = 0, plane = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ length;

	अगर (q->memory != VB2_MEMORY_MMAP) अणु
		dprपूर्णांकk(q, 1, "queue is not currently set up for mmap\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check memory area access mode.
	 */
	अगर (!(vma->vm_flags & VM_SHARED)) अणु
		dprपूर्णांकk(q, 1, "invalid vma flags, VM_SHARED needed\n");
		वापस -EINVAL;
	पूर्ण
	अगर (q->is_output) अणु
		अगर (!(vma->vm_flags & VM_WRITE)) अणु
			dprपूर्णांकk(q, 1, "invalid vma flags, VM_WRITE needed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(vma->vm_flags & VM_READ)) अणु
			dprपूर्णांकk(q, 1, "invalid vma flags, VM_READ needed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mutex_lock(&q->mmap_lock);

	अगर (vb2_fileio_is_active(q)) अणु
		dprपूर्णांकk(q, 1, "mmap: file io in progress\n");
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	/*
	 * Find the plane corresponding to the offset passed by userspace.
	 */
	ret = __find_plane_by_offset(q, off, &buffer, &plane);
	अगर (ret)
		जाओ unlock;

	vb = q->bufs[buffer];

	/*
	 * MMAP requires page_aligned buffers.
	 * The buffer length was page_aligned at __vb2_buf_mem_alloc(),
	 * so, we need to करो the same here.
	 */
	length = PAGE_ALIGN(vb->planes[plane].length);
	अगर (length < (vma->vm_end - vma->vm_start)) अणु
		dprपूर्णांकk(q, 1,
			"MMAP invalid, as it would overflow buffer length\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	/*
	 * vm_pgoff is treated in V4L2 API as a 'cookie' to select a buffer,
	 * not as a in-buffer offset. We always want to mmap a whole buffer
	 * from its beginning.
	 */
	vma->vm_pgoff = 0;

	ret = call_memop(vb, mmap, vb->planes[plane].mem_priv, vma);

unlock:
	mutex_unlock(&q->mmap_lock);
	अगर (ret)
		वापस ret;

	dprपूर्णांकk(q, 3, "buffer %d, plane %d successfully mapped\n", buffer, plane);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_mmap);

#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ vb2_get_unmapped_area(काष्ठा vb2_queue *q,
				    अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ pgoff,
				    अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ off = pgoff << PAGE_SHIFT;
	काष्ठा vb2_buffer *vb;
	अचिन्हित पूर्णांक buffer, plane;
	व्योम *vaddr;
	पूर्णांक ret;

	अगर (q->memory != VB2_MEMORY_MMAP) अणु
		dprपूर्णांकk(q, 1, "queue is not currently set up for mmap\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Find the plane corresponding to the offset passed by userspace.
	 */
	ret = __find_plane_by_offset(q, off, &buffer, &plane);
	अगर (ret)
		वापस ret;

	vb = q->bufs[buffer];

	vaddr = vb2_plane_vaddr(vb, plane);
	वापस vaddr ? (अचिन्हित दीर्घ)vaddr : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_get_unmapped_area);
#पूर्ण_अगर

पूर्णांक vb2_core_queue_init(काष्ठा vb2_queue *q)
अणु
	/*
	 * Sanity check
	 */
	अगर (WARN_ON(!q)			  ||
	    WARN_ON(!q->ops)		  ||
	    WARN_ON(!q->mem_ops)	  ||
	    WARN_ON(!q->type)		  ||
	    WARN_ON(!q->io_modes)	  ||
	    WARN_ON(!q->ops->queue_setup) ||
	    WARN_ON(!q->ops->buf_queue))
		वापस -EINVAL;

	अगर (WARN_ON(q->requires_requests && !q->supports_requests))
		वापस -EINVAL;

	INIT_LIST_HEAD(&q->queued_list);
	INIT_LIST_HEAD(&q->करोne_list);
	spin_lock_init(&q->करोne_lock);
	mutex_init(&q->mmap_lock);
	init_रुकोqueue_head(&q->करोne_wq);

	q->memory = VB2_MEMORY_UNKNOWN;

	अगर (q->buf_काष्ठा_size == 0)
		q->buf_काष्ठा_size = माप(काष्ठा vb2_buffer);

	अगर (q->bidirectional)
		q->dma_dir = DMA_BIसूचीECTIONAL;
	अन्यथा
		q->dma_dir = q->is_output ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	अगर (q->name[0] == '\0')
		snम_लिखो(q->name, माप(q->name), "%s-%p",
			 q->is_output ? "out" : "cap", q);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_queue_init);

अटल पूर्णांक __vb2_init_fileio(काष्ठा vb2_queue *q, पूर्णांक पढ़ो);
अटल पूर्णांक __vb2_cleanup_fileio(काष्ठा vb2_queue *q);
व्योम vb2_core_queue_release(काष्ठा vb2_queue *q)
अणु
	__vb2_cleanup_fileio(q);
	__vb2_queue_cancel(q);
	mutex_lock(&q->mmap_lock);
	__vb2_queue_मुक्त(q, q->num_buffers);
	mutex_unlock(&q->mmap_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_queue_release);

__poll_t vb2_core_poll(काष्ठा vb2_queue *q, काष्ठा file *file,
		poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा vb2_buffer *vb = शून्य;
	अचिन्हित दीर्घ flags;

	/*
	 * poll_रुको() MUST be called on the first invocation on all the
	 * potential queues of पूर्णांकerest, even अगर we are not पूर्णांकerested in their
	 * events during this first call. Failure to करो so will result in
	 * queue's events to be ignored because the poll_table won't be capable
	 * of adding new रुको queues thereafter.
	 */
	poll_रुको(file, &q->करोne_wq, रुको);

	अगर (!q->is_output && !(req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस 0;
	अगर (q->is_output && !(req_events & (EPOLLOUT | EPOLLWRNORM)))
		वापस 0;

	/*
	 * Start file I/O emulator only अगर streaming API has not been used yet.
	 */
	अगर (q->num_buffers == 0 && !vb2_fileio_is_active(q)) अणु
		अगर (!q->is_output && (q->io_modes & VB2_READ) &&
				(req_events & (EPOLLIN | EPOLLRDNORM))) अणु
			अगर (__vb2_init_fileio(q, 1))
				वापस EPOLLERR;
		पूर्ण
		अगर (q->is_output && (q->io_modes & VB2_WRITE) &&
				(req_events & (EPOLLOUT | EPOLLWRNORM))) अणु
			अगर (__vb2_init_fileio(q, 0))
				वापस EPOLLERR;
			/*
			 * Write to OUTPUT queue can be करोne immediately.
			 */
			वापस EPOLLOUT | EPOLLWRNORM;
		पूर्ण
	पूर्ण

	/*
	 * There is nothing to रुको क्रम अगर the queue isn't streaming, or अगर the
	 * error flag is set.
	 */
	अगर (!vb2_is_streaming(q) || q->error)
		वापस EPOLLERR;

	/*
	 * If this quirk is set and QBUF hasn't been called yet then
	 * वापस EPOLLERR as well. This only affects capture queues, output
	 * queues will always initialize रुकोing_क्रम_buffers to false.
	 * This quirk is set by V4L2 क्रम backwards compatibility reasons.
	 */
	अगर (q->quirk_poll_must_check_रुकोing_क्रम_buffers &&
	    q->रुकोing_क्रम_buffers && (req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस EPOLLERR;

	/*
	 * For output streams you can call ग_लिखो() as दीर्घ as there are fewer
	 * buffers queued than there are buffers available.
	 */
	अगर (q->is_output && q->fileio && q->queued_count < q->num_buffers)
		वापस EPOLLOUT | EPOLLWRNORM;

	अगर (list_empty(&q->करोne_list)) अणु
		/*
		 * If the last buffer was dequeued from a capture queue,
		 * वापस immediately. DQBUF will वापस -EPIPE.
		 */
		अगर (q->last_buffer_dequeued)
			वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण

	/*
	 * Take first buffer available क्रम dequeuing.
	 */
	spin_lock_irqsave(&q->करोne_lock, flags);
	अगर (!list_empty(&q->करोne_list))
		vb = list_first_entry(&q->करोne_list, काष्ठा vb2_buffer,
					करोne_entry);
	spin_unlock_irqrestore(&q->करोne_lock, flags);

	अगर (vb && (vb->state == VB2_BUF_STATE_DONE
			|| vb->state == VB2_BUF_STATE_ERROR)) अणु
		वापस (q->is_output) ?
				EPOLLOUT | EPOLLWRNORM :
				EPOLLIN | EPOLLRDNORM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_core_poll);

/*
 * काष्ठा vb2_fileio_buf - buffer context used by file io emulator
 *
 * vb2 provides a compatibility layer and emulator of file io (पढ़ो and
 * ग_लिखो) calls on top of streaming API. This काष्ठाure is used क्रम
 * tracking context related to the buffers.
 */
काष्ठा vb2_fileio_buf अणु
	व्योम *vaddr;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक queued:1;
पूर्ण;

/*
 * काष्ठा vb2_fileio_data - queue context used by file io emulator
 *
 * @cur_index:	the index of the buffer currently being पढ़ो from or
 *		written to. If equal to q->num_buffers then a new buffer
 *		must be dequeued.
 * @initial_index: in the पढ़ो() हाल all buffers are queued up immediately
 *		in __vb2_init_fileio() and __vb2_perक्रमm_fileio() just cycles
 *		buffers. However, in the ग_लिखो() हाल no buffers are initially
 *		queued, instead whenever a buffer is full it is queued up by
 *		__vb2_perक्रमm_fileio(). Only once all available buffers have
 *		been queued up will __vb2_perक्रमm_fileio() start to dequeue
 *		buffers. This means that initially __vb2_perक्रमm_fileio()
 *		needs to know what buffer index to use when it is queuing up
 *		the buffers क्रम the first समय. That initial index is stored
 *		in this field. Once it is equal to q->num_buffers all
 *		available buffers have been queued and __vb2_perक्रमm_fileio()
 *		should start the normal dequeue/queue cycle.
 *
 * vb2 provides a compatibility layer and emulator of file io (पढ़ो and
 * ग_लिखो) calls on top of streaming API. For proper operation it required
 * this काष्ठाure to save the driver state between each call of the पढ़ो
 * or ग_लिखो function.
 */
काष्ठा vb2_fileio_data अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक memory;
	काष्ठा vb2_fileio_buf bufs[VB2_MAX_FRAME];
	अचिन्हित पूर्णांक cur_index;
	अचिन्हित पूर्णांक initial_index;
	अचिन्हित पूर्णांक q_count;
	अचिन्हित पूर्णांक dq_count;
	अचिन्हित पढ़ो_once:1;
	अचिन्हित ग_लिखो_immediately:1;
पूर्ण;

/*
 * __vb2_init_fileio() - initialize file io emulator
 * @q:		videobuf2 queue
 * @पढ़ो:	mode selector (1 means पढ़ो, 0 means ग_लिखो)
 */
अटल पूर्णांक __vb2_init_fileio(काष्ठा vb2_queue *q, पूर्णांक पढ़ो)
अणु
	काष्ठा vb2_fileio_data *fileio;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक count = 0;

	/*
	 * Sanity check
	 */
	अगर (WARN_ON((पढ़ो && !(q->io_modes & VB2_READ)) ||
		    (!पढ़ो && !(q->io_modes & VB2_WRITE))))
		वापस -EINVAL;

	/*
	 * Check अगर device supports mapping buffers to kernel भव space.
	 */
	अगर (!q->mem_ops->vaddr)
		वापस -EBUSY;

	/*
	 * Check अगर streaming api has not been alपढ़ोy activated.
	 */
	अगर (q->streaming || q->num_buffers > 0)
		वापस -EBUSY;

	/*
	 * Start with count 1, driver can increase it in queue_setup()
	 */
	count = 1;

	dprपूर्णांकk(q, 3, "setting up file io: mode %s, count %d, read_once %d, write_immediately %d\n",
		(पढ़ो) ? "read" : "write", count, q->fileio_पढ़ो_once,
		q->fileio_ग_लिखो_immediately);

	fileio = kzalloc(माप(*fileio), GFP_KERNEL);
	अगर (fileio == शून्य)
		वापस -ENOMEM;

	fileio->पढ़ो_once = q->fileio_पढ़ो_once;
	fileio->ग_लिखो_immediately = q->fileio_ग_लिखो_immediately;

	/*
	 * Request buffers and use MMAP type to क्रमce driver
	 * to allocate buffers by itself.
	 */
	fileio->count = count;
	fileio->memory = VB2_MEMORY_MMAP;
	fileio->type = q->type;
	q->fileio = fileio;
	ret = vb2_core_reqbufs(q, fileio->memory, &fileio->count);
	अगर (ret)
		जाओ err_kमुक्त;

	/*
	 * Check अगर plane_count is correct
	 * (multiplane buffers are not supported).
	 */
	अगर (q->bufs[0]->num_planes != 1) अणु
		ret = -EBUSY;
		जाओ err_reqbufs;
	पूर्ण

	/*
	 * Get kernel address of each buffer.
	 */
	क्रम (i = 0; i < q->num_buffers; i++) अणु
		fileio->bufs[i].vaddr = vb2_plane_vaddr(q->bufs[i], 0);
		अगर (fileio->bufs[i].vaddr == शून्य) अणु
			ret = -EINVAL;
			जाओ err_reqbufs;
		पूर्ण
		fileio->bufs[i].size = vb2_plane_size(q->bufs[i], 0);
	पूर्ण

	/*
	 * Read mode requires pre queuing of all buffers.
	 */
	अगर (पढ़ो) अणु
		/*
		 * Queue all buffers.
		 */
		क्रम (i = 0; i < q->num_buffers; i++) अणु
			ret = vb2_core_qbuf(q, i, शून्य, शून्य);
			अगर (ret)
				जाओ err_reqbufs;
			fileio->bufs[i].queued = 1;
		पूर्ण
		/*
		 * All buffers have been queued, so mark that by setting
		 * initial_index to q->num_buffers
		 */
		fileio->initial_index = q->num_buffers;
		fileio->cur_index = q->num_buffers;
	पूर्ण

	/*
	 * Start streaming.
	 */
	ret = vb2_core_streamon(q, q->type);
	अगर (ret)
		जाओ err_reqbufs;

	वापस ret;

err_reqbufs:
	fileio->count = 0;
	vb2_core_reqbufs(q, fileio->memory, &fileio->count);

err_kमुक्त:
	q->fileio = शून्य;
	kमुक्त(fileio);
	वापस ret;
पूर्ण

/*
 * __vb2_cleanup_fileio() - मुक्त resourced used by file io emulator
 * @q:		videobuf2 queue
 */
अटल पूर्णांक __vb2_cleanup_fileio(काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_fileio_data *fileio = q->fileio;

	अगर (fileio) अणु
		vb2_core_streamoff(q, q->type);
		q->fileio = शून्य;
		fileio->count = 0;
		vb2_core_reqbufs(q, fileio->memory, &fileio->count);
		kमुक्त(fileio);
		dprपूर्णांकk(q, 3, "file io emulator closed\n");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * __vb2_perक्रमm_fileio() - perक्रमm a single file io (पढ़ो or ग_लिखो) operation
 * @q:		videobuf2 queue
 * @data:	poपूर्णांकed to target userspace buffer
 * @count:	number of bytes to पढ़ो or ग_लिखो
 * @ppos:	file handle position tracking poपूर्णांकer
 * @nonblock:	mode selector (1 means blocking calls, 0 means nonblocking)
 * @पढ़ो:	access mode selector (1 means पढ़ो, 0 means ग_लिखो)
 */
अटल माप_प्रकार __vb2_perक्रमm_fileio(काष्ठा vb2_queue *q, अक्षर __user *data, माप_प्रकार count,
		loff_t *ppos, पूर्णांक nonblock, पूर्णांक पढ़ो)
अणु
	काष्ठा vb2_fileio_data *fileio;
	काष्ठा vb2_fileio_buf *buf;
	bool is_multiplanar = q->is_multiplanar;
	/*
	 * When using ग_लिखो() to ग_लिखो data to an output video node the vb2 core
	 * should copy बारtamps अगर V4L2_BUF_FLAG_TIMESTAMP_COPY is set. Nobody
	 * अन्यथा is able to provide this inक्रमmation with the ग_लिखो() operation.
	 */
	bool copy_बारtamp = !पढ़ो && q->copy_बारtamp;
	अचिन्हित index;
	पूर्णांक ret;

	dprपूर्णांकk(q, 3, "mode %s, offset %ld, count %zd, %sblocking\n",
		पढ़ो ? "read" : "write", (दीर्घ)*ppos, count,
		nonblock ? "non" : "");

	अगर (!data)
		वापस -EINVAL;

	अगर (q->रुकोing_in_dqbuf) अणु
		dprपूर्णांकk(q, 3, "another dup()ped fd is %s\n",
			पढ़ो ? "reading" : "writing");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Initialize emulator on first call.
	 */
	अगर (!vb2_fileio_is_active(q)) अणु
		ret = __vb2_init_fileio(q, पढ़ो);
		dprपूर्णांकk(q, 3, "vb2_init_fileio result: %d\n", ret);
		अगर (ret)
			वापस ret;
	पूर्ण
	fileio = q->fileio;

	/*
	 * Check अगर we need to dequeue the buffer.
	 */
	index = fileio->cur_index;
	अगर (index >= q->num_buffers) अणु
		काष्ठा vb2_buffer *b;

		/*
		 * Call vb2_dqbuf to get buffer back.
		 */
		ret = vb2_core_dqbuf(q, &index, शून्य, nonblock);
		dprपूर्णांकk(q, 5, "vb2_dqbuf result: %d\n", ret);
		अगर (ret)
			वापस ret;
		fileio->dq_count += 1;

		fileio->cur_index = index;
		buf = &fileio->bufs[index];
		b = q->bufs[index];

		/*
		 * Get number of bytes filled by the driver
		 */
		buf->pos = 0;
		buf->queued = 0;
		buf->size = पढ़ो ? vb2_get_plane_payload(q->bufs[index], 0)
				 : vb2_plane_size(q->bufs[index], 0);
		/* Compensate क्रम data_offset on पढ़ो in the multiplanar हाल. */
		अगर (is_multiplanar && पढ़ो &&
				b->planes[0].data_offset < buf->size) अणु
			buf->pos = b->planes[0].data_offset;
			buf->size -= buf->pos;
		पूर्ण
	पूर्ण अन्यथा अणु
		buf = &fileio->bufs[index];
	पूर्ण

	/*
	 * Limit count on last few bytes of the buffer.
	 */
	अगर (buf->pos + count > buf->size) अणु
		count = buf->size - buf->pos;
		dprपूर्णांकk(q, 5, "reducing read count: %zd\n", count);
	पूर्ण

	/*
	 * Transfer data to userspace.
	 */
	dprपूर्णांकk(q, 3, "copying %zd bytes - buffer %d, offset %u\n",
		count, index, buf->pos);
	अगर (पढ़ो)
		ret = copy_to_user(data, buf->vaddr + buf->pos, count);
	अन्यथा
		ret = copy_from_user(buf->vaddr + buf->pos, data, count);
	अगर (ret) अणु
		dprपूर्णांकk(q, 3, "error copying data\n");
		वापस -EFAULT;
	पूर्ण

	/*
	 * Update counters.
	 */
	buf->pos += count;
	*ppos += count;

	/*
	 * Queue next buffer अगर required.
	 */
	अगर (buf->pos == buf->size || (!पढ़ो && fileio->ग_लिखो_immediately)) अणु
		काष्ठा vb2_buffer *b = q->bufs[index];

		/*
		 * Check अगर this is the last buffer to पढ़ो.
		 */
		अगर (पढ़ो && fileio->पढ़ो_once && fileio->dq_count == 1) अणु
			dprपूर्णांकk(q, 3, "read limit reached\n");
			वापस __vb2_cleanup_fileio(q);
		पूर्ण

		/*
		 * Call vb2_qbuf and give buffer to the driver.
		 */
		b->planes[0].bytesused = buf->pos;

		अगर (copy_बारtamp)
			b->बारtamp = kसमय_get_ns();
		ret = vb2_core_qbuf(q, index, शून्य, शून्य);
		dprपूर्णांकk(q, 5, "vb2_dbuf result: %d\n", ret);
		अगर (ret)
			वापस ret;

		/*
		 * Buffer has been queued, update the status
		 */
		buf->pos = 0;
		buf->queued = 1;
		buf->size = vb2_plane_size(q->bufs[index], 0);
		fileio->q_count += 1;
		/*
		 * If we are queuing up buffers क्रम the first समय, then
		 * increase initial_index by one.
		 */
		अगर (fileio->initial_index < q->num_buffers)
			fileio->initial_index++;
		/*
		 * The next buffer to use is either a buffer that's going to be
		 * queued क्रम the first समय (initial_index < q->num_buffers)
		 * or it is equal to q->num_buffers, meaning that the next
		 * समय we need to dequeue a buffer since we've now queued up
		 * all the 'first time' buffers.
		 */
		fileio->cur_index = fileio->initial_index;
	पूर्ण

	/*
	 * Return proper number of bytes processed.
	 */
	अगर (ret == 0)
		ret = count;
	वापस ret;
पूर्ण

माप_प्रकार vb2_पढ़ो(काष्ठा vb2_queue *q, अक्षर __user *data, माप_प्रकार count,
		loff_t *ppos, पूर्णांक nonblocking)
अणु
	वापस __vb2_perक्रमm_fileio(q, data, count, ppos, nonblocking, 1);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_पढ़ो);

माप_प्रकार vb2_ग_लिखो(काष्ठा vb2_queue *q, स्थिर अक्षर __user *data, माप_प्रकार count,
		loff_t *ppos, पूर्णांक nonblocking)
अणु
	वापस __vb2_perक्रमm_fileio(q, (अक्षर __user *) data, count,
							ppos, nonblocking, 0);
पूर्ण
EXPORT_SYMBOL_GPL(vb2_ग_लिखो);

काष्ठा vb2_thपढ़ोio_data अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	vb2_thपढ़ो_fnc fnc;
	व्योम *priv;
	bool stop;
पूर्ण;

अटल पूर्णांक vb2_thपढ़ो(व्योम *data)
अणु
	काष्ठा vb2_queue *q = data;
	काष्ठा vb2_thपढ़ोio_data *thपढ़ोio = q->thपढ़ोio;
	bool copy_बारtamp = false;
	अचिन्हित prequeue = 0;
	अचिन्हित index = 0;
	पूर्णांक ret = 0;

	अगर (q->is_output) अणु
		prequeue = q->num_buffers;
		copy_बारtamp = q->copy_बारtamp;
	पूर्ण

	set_मुक्तzable();

	क्रम (;;) अणु
		काष्ठा vb2_buffer *vb;

		/*
		 * Call vb2_dqbuf to get buffer back.
		 */
		अगर (prequeue) अणु
			vb = q->bufs[index++];
			prequeue--;
		पूर्ण अन्यथा अणु
			call_व्योम_qop(q, रुको_finish, q);
			अगर (!thपढ़ोio->stop)
				ret = vb2_core_dqbuf(q, &index, शून्य, 0);
			call_व्योम_qop(q, रुको_prepare, q);
			dprपूर्णांकk(q, 5, "file io: vb2_dqbuf result: %d\n", ret);
			अगर (!ret)
				vb = q->bufs[index];
		पूर्ण
		अगर (ret || thपढ़ोio->stop)
			अवरोध;
		try_to_मुक्तze();

		अगर (vb->state != VB2_BUF_STATE_ERROR)
			अगर (thपढ़ोio->fnc(vb, thपढ़ोio->priv))
				अवरोध;
		call_व्योम_qop(q, रुको_finish, q);
		अगर (copy_बारtamp)
			vb->बारtamp = kसमय_get_ns();
		अगर (!thपढ़ोio->stop)
			ret = vb2_core_qbuf(q, vb->index, शून्य, शून्य);
		call_व्योम_qop(q, रुको_prepare, q);
		अगर (ret || thपढ़ोio->stop)
			अवरोध;
	पूर्ण

	/* Hmm, linux becomes *very* unhappy without this ... */
	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function should not be used क्रम anything अन्यथा but the videobuf2-dvb
 * support. If you think you have another good use-हाल क्रम this, then please
 * contact the linux-media mailinglist first.
 */
पूर्णांक vb2_thपढ़ो_start(काष्ठा vb2_queue *q, vb2_thपढ़ो_fnc fnc, व्योम *priv,
		     स्थिर अक्षर *thपढ़ो_name)
अणु
	काष्ठा vb2_thपढ़ोio_data *thपढ़ोio;
	पूर्णांक ret = 0;

	अगर (q->thपढ़ोio)
		वापस -EBUSY;
	अगर (vb2_is_busy(q))
		वापस -EBUSY;
	अगर (WARN_ON(q->fileio))
		वापस -EBUSY;

	thपढ़ोio = kzalloc(माप(*thपढ़ोio), GFP_KERNEL);
	अगर (thपढ़ोio == शून्य)
		वापस -ENOMEM;
	thपढ़ोio->fnc = fnc;
	thपढ़ोio->priv = priv;

	ret = __vb2_init_fileio(q, !q->is_output);
	dprपूर्णांकk(q, 3, "file io: vb2_init_fileio result: %d\n", ret);
	अगर (ret)
		जाओ nomem;
	q->thपढ़ोio = thपढ़ोio;
	thपढ़ोio->thपढ़ो = kthपढ़ो_run(vb2_thपढ़ो, q, "vb2-%s", thपढ़ो_name);
	अगर (IS_ERR(thपढ़ोio->thपढ़ो)) अणु
		ret = PTR_ERR(thपढ़ोio->thपढ़ो);
		thपढ़ोio->thपढ़ो = शून्य;
		जाओ nothपढ़ो;
	पूर्ण
	वापस 0;

nothपढ़ो:
	__vb2_cleanup_fileio(q);
nomem:
	kमुक्त(thपढ़ोio);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_thपढ़ो_start);

पूर्णांक vb2_thपढ़ो_stop(काष्ठा vb2_queue *q)
अणु
	काष्ठा vb2_thपढ़ोio_data *thपढ़ोio = q->thपढ़ोio;
	पूर्णांक err;

	अगर (thपढ़ोio == शून्य)
		वापस 0;
	thपढ़ोio->stop = true;
	/* Wake up all pending sleeps in the thपढ़ो */
	vb2_queue_error(q);
	err = kthपढ़ो_stop(thपढ़ोio->thपढ़ो);
	__vb2_cleanup_fileio(q);
	thपढ़ोio->thपढ़ो = शून्य;
	kमुक्त(thपढ़ोio);
	q->thपढ़ोio = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_thपढ़ो_stop);

MODULE_DESCRIPTION("Media buffer core framework");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>, Marek Szyprowski");
MODULE_LICENSE("GPL");
