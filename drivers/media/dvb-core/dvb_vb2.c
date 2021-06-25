<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dvb-vb2.c - dvb-vb2
 *
 * Copyright (C) 2015 Samsung Electronics
 *
 * Author: jh1009.sung@samsung.com
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>

#समावेश <media/dvbdev.h>
#समावेश <media/dvb_vb2.h>

#घोषणा DVB_V2_MAX_SIZE		(4096 * 188)

अटल पूर्णांक vb2_debug;
module_param(vb2_debug, पूर्णांक, 0644);

#घोषणा dprपूर्णांकk(level, fmt, arg...)					      \
	करो अणु								      \
		अगर (vb2_debug >= level)					      \
			pr_info("vb2: %s: " fmt, __func__, ## arg); \
	पूर्ण जबतक (0)

अटल पूर्णांक _queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	ctx->buf_cnt = *nbuffers;
	*nplanes = 1;
	sizes[0] = ctx->buf_siz;

	/*
	 * videobuf2-vदो_स्मृति allocator is context-less so no need to set
	 * alloc_ctxs array.
	 */

	dprपूर्णांकk(3, "[%s] count=%d, size=%d\n", ctx->name,
		*nbuffers, sizes[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक _buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = ctx->buf_siz;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dprपूर्णांकk(1, "[%s] data will not fit into plane (%lu < %lu)\n",
			ctx->name, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

अटल व्योम _buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा dvb_buffer *buf = container_of(vb, काष्ठा dvb_buffer, vb);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&ctx->slock, flags);
	list_add_tail(&buf->list, &ctx->dvb_q);
	spin_unlock_irqrestore(&ctx->slock, flags);

	dprपूर्णांकk(3, "[%s]\n", ctx->name);
पूर्ण

अटल पूर्णांक _start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	dprपूर्णांकk(3, "[%s] count=%d\n", ctx->name, count);
	वापस 0;
पूर्ण

अटल व्योम _stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा dvb_buffer *buf;
	अचिन्हित दीर्घ flags = 0;

	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	spin_lock_irqsave(&ctx->slock, flags);
	जबतक (!list_empty(&ctx->dvb_q)) अणु
		buf = list_entry(ctx->dvb_q.next,
				 काष्ठा dvb_buffer, list);
		vb2_buffer_करोne(&buf->vb, VB2_BUF_STATE_ERROR);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&ctx->slock, flags);
पूर्ण

अटल व्योम _dmxdev_lock(काष्ठा vb2_queue *vq)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	mutex_lock(&ctx->mutex);
	dprपूर्णांकk(3, "[%s]\n", ctx->name);
पूर्ण

अटल व्योम _dmxdev_unlock(काष्ठा vb2_queue *vq)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	अगर (mutex_is_locked(&ctx->mutex))
		mutex_unlock(&ctx->mutex);
	dprपूर्णांकk(3, "[%s]\n", ctx->name);
पूर्ण

अटल स्थिर काष्ठा vb2_ops dvb_vb2_qops = अणु
	.queue_setup		= _queue_setup,
	.buf_prepare		= _buffer_prepare,
	.buf_queue		= _buffer_queue,
	.start_streaming	= _start_streaming,
	.stop_streaming		= _stop_streaming,
	.रुको_prepare		= _dmxdev_unlock,
	.रुको_finish		= _dmxdev_lock,
पूर्ण;

अटल व्योम _fill_dmx_buffer(काष्ठा vb2_buffer *vb, व्योम *pb)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा dmx_buffer *b = pb;

	b->index = vb->index;
	b->length = vb->planes[0].length;
	b->bytesused = vb->planes[0].bytesused;
	b->offset = vb->planes[0].m.offset;
	dprपूर्णांकk(3, "[%s]\n", ctx->name);
पूर्ण

अटल पूर्णांक _fill_vb2_buffer(काष्ठा vb2_buffer *vb, काष्ठा vb2_plane *planes)
अणु
	काष्ठा dvb_vb2_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	planes[0].bytesused = 0;
	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_buf_ops dvb_vb2_buf_ops = अणु
	.fill_user_buffer	= _fill_dmx_buffer,
	.fill_vb2_buffer	= _fill_vb2_buffer,
पूर्ण;

/*
 * Videobuf operations
 */
पूर्णांक dvb_vb2_init(काष्ठा dvb_vb2_ctx *ctx, स्थिर अक्षर *name, पूर्णांक nonblocking)
अणु
	काष्ठा vb2_queue *q = &ctx->vb_q;
	पूर्णांक ret;

	स_रखो(ctx, 0, माप(काष्ठा dvb_vb2_ctx));
	q->type = DVB_BUF_TYPE_CAPTURE;
	/**capture type*/
	q->is_output = 0;
	/**only mmap is supported currently*/
	q->io_modes = VB2_MMAP;
	q->drv_priv = ctx;
	q->buf_काष्ठा_size = माप(काष्ठा dvb_buffer);
	q->min_buffers_needed = 1;
	q->ops = &dvb_vb2_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->buf_ops = &dvb_vb2_buf_ops;
	q->num_buffers = 0;
	ret = vb2_core_queue_init(q);
	अगर (ret) अणु
		ctx->state = DVB_VB2_STATE_NONE;
		dprपूर्णांकk(1, "[%s] errno=%d\n", ctx->name, ret);
		वापस ret;
	पूर्ण

	mutex_init(&ctx->mutex);
	spin_lock_init(&ctx->slock);
	INIT_LIST_HEAD(&ctx->dvb_q);

	strscpy(ctx->name, name, DVB_VB2_NAME_MAX);
	ctx->nonblocking = nonblocking;
	ctx->state = DVB_VB2_STATE_INIT;

	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_release(काष्ठा dvb_vb2_ctx *ctx)
अणु
	काष्ठा vb2_queue *q = (काष्ठा vb2_queue *)&ctx->vb_q;

	अगर (ctx->state & DVB_VB2_STATE_INIT)
		vb2_core_queue_release(q);

	ctx->state = DVB_VB2_STATE_NONE;
	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_stream_on(काष्ठा dvb_vb2_ctx *ctx)
अणु
	काष्ठा vb2_queue *q = &ctx->vb_q;
	पूर्णांक ret;

	ret = vb2_core_streamon(q, q->type);
	अगर (ret) अणु
		ctx->state = DVB_VB2_STATE_NONE;
		dprपूर्णांकk(1, "[%s] errno=%d\n", ctx->name, ret);
		वापस ret;
	पूर्ण
	ctx->state |= DVB_VB2_STATE_STREAMON;
	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_stream_off(काष्ठा dvb_vb2_ctx *ctx)
अणु
	काष्ठा vb2_queue *q = (काष्ठा vb2_queue *)&ctx->vb_q;
	पूर्णांक ret;

	ctx->state &= ~DVB_VB2_STATE_STREAMON;
	ret = vb2_core_streamoff(q, q->type);
	अगर (ret) अणु
		ctx->state = DVB_VB2_STATE_NONE;
		dprपूर्णांकk(1, "[%s] errno=%d\n", ctx->name, ret);
		वापस ret;
	पूर्ण
	dprपूर्णांकk(3, "[%s]\n", ctx->name);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_is_streaming(काष्ठा dvb_vb2_ctx *ctx)
अणु
	वापस (ctx->state & DVB_VB2_STATE_STREAMON);
पूर्ण

पूर्णांक dvb_vb2_fill_buffer(काष्ठा dvb_vb2_ctx *ctx,
			स्थिर अचिन्हित अक्षर *src, पूर्णांक len,
			क्रमागत dmx_buffer_flags *buffer_flags)
अणु
	अचिन्हित दीर्घ flags = 0;
	व्योम *vbuf = शून्य;
	पूर्णांक toकरो = len;
	अचिन्हित अक्षर *psrc = (अचिन्हित अक्षर *)src;
	पूर्णांक ll = 0;

	/*
	 * normal हाल: This func is called twice from demux driver
	 * one with valid src poपूर्णांकer, second समय with शून्य poपूर्णांकer
	 */
	अगर (!src || !len)
		वापस 0;
	spin_lock_irqsave(&ctx->slock, flags);
	अगर (buffer_flags && *buffer_flags) अणु
		ctx->flags |= *buffer_flags;
		*buffer_flags = 0;
	पूर्ण
	जबतक (toकरो) अणु
		अगर (!ctx->buf) अणु
			अगर (list_empty(&ctx->dvb_q)) अणु
				dprपूर्णांकk(3, "[%s] Buffer overflow!!!\n",
					ctx->name);
				अवरोध;
			पूर्ण

			ctx->buf = list_entry(ctx->dvb_q.next,
					      काष्ठा dvb_buffer, list);
			ctx->reमुख्य = vb2_plane_size(&ctx->buf->vb, 0);
			ctx->offset = 0;
		पूर्ण

		अगर (!dvb_vb2_is_streaming(ctx)) अणु
			vb2_buffer_करोne(&ctx->buf->vb, VB2_BUF_STATE_ERROR);
			list_del(&ctx->buf->list);
			ctx->buf = शून्य;
			अवरोध;
		पूर्ण

		/* Fill buffer */
		ll = min(toकरो, ctx->reमुख्य);
		vbuf = vb2_plane_vaddr(&ctx->buf->vb, 0);
		स_नकल(vbuf + ctx->offset, psrc, ll);
		toकरो -= ll;
		psrc += ll;

		ctx->reमुख्य -= ll;
		ctx->offset += ll;

		अगर (ctx->reमुख्य == 0) अणु
			vb2_buffer_करोne(&ctx->buf->vb, VB2_BUF_STATE_DONE);
			list_del(&ctx->buf->list);
			ctx->buf = शून्य;
		पूर्ण
	पूर्ण

	अगर (ctx->nonblocking && ctx->buf) अणु
		vb2_set_plane_payload(&ctx->buf->vb, 0, ll);
		vb2_buffer_करोne(&ctx->buf->vb, VB2_BUF_STATE_DONE);
		list_del(&ctx->buf->list);
		ctx->buf = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ctx->slock, flags);

	अगर (toकरो)
		dprपूर्णांकk(1, "[%s] %d bytes are dropped.\n", ctx->name, toकरो);
	अन्यथा
		dprपूर्णांकk(3, "[%s]\n", ctx->name);

	dprपूर्णांकk(3, "[%s] %d bytes are copied\n", ctx->name, len - toकरो);
	वापस (len - toकरो);
पूर्ण

पूर्णांक dvb_vb2_reqbufs(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_requestbuffers *req)
अणु
	पूर्णांक ret;

	/* Adjust size to a sane value */
	अगर (req->size > DVB_V2_MAX_SIZE)
		req->size = DVB_V2_MAX_SIZE;

	/* FIXME: round req->size to a 188 or 204 multiple */

	ctx->buf_siz = req->size;
	ctx->buf_cnt = req->count;
	ret = vb2_core_reqbufs(&ctx->vb_q, VB2_MEMORY_MMAP, &req->count);
	अगर (ret) अणु
		ctx->state = DVB_VB2_STATE_NONE;
		dprपूर्णांकk(1, "[%s] count=%d size=%d errno=%d\n", ctx->name,
			ctx->buf_cnt, ctx->buf_siz, ret);
		वापस ret;
	पूर्ण
	ctx->state |= DVB_VB2_STATE_REQBUFS;
	dprपूर्णांकk(3, "[%s] count=%d size=%d\n", ctx->name,
		ctx->buf_cnt, ctx->buf_siz);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_querybuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b)
अणु
	vb2_core_querybuf(&ctx->vb_q, b->index, b);
	dprपूर्णांकk(3, "[%s] index=%d\n", ctx->name, b->index);
	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_expbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_exportbuffer *exp)
अणु
	काष्ठा vb2_queue *q = &ctx->vb_q;
	पूर्णांक ret;

	ret = vb2_core_expbuf(&ctx->vb_q, &exp->fd, q->type, exp->index,
			      0, exp->flags);
	अगर (ret) अणु
		dprपूर्णांकk(1, "[%s] index=%d errno=%d\n", ctx->name,
			exp->index, ret);
		वापस ret;
	पूर्ण
	dprपूर्णांकk(3, "[%s] index=%d fd=%d\n", ctx->name, exp->index, exp->fd);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_qbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b)
अणु
	पूर्णांक ret;

	ret = vb2_core_qbuf(&ctx->vb_q, b->index, b, शून्य);
	अगर (ret) अणु
		dprपूर्णांकk(1, "[%s] index=%d errno=%d\n", ctx->name,
			b->index, ret);
		वापस ret;
	पूर्ण
	dprपूर्णांकk(5, "[%s] index=%d\n", ctx->name, b->index);

	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_dqbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = vb2_core_dqbuf(&ctx->vb_q, &b->index, b, ctx->nonblocking);
	अगर (ret) अणु
		dprपूर्णांकk(1, "[%s] errno=%d\n", ctx->name, ret);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&ctx->slock, flags);
	b->count = ctx->count++;
	b->flags = ctx->flags;
	ctx->flags = 0;
	spin_unlock_irqrestore(&ctx->slock, flags);

	dprपूर्णांकk(5, "[%s] index=%d, count=%d, flags=%d\n",
		ctx->name, b->index, ctx->count, b->flags);


	वापस 0;
पूर्ण

पूर्णांक dvb_vb2_mmap(काष्ठा dvb_vb2_ctx *ctx, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = vb2_mmap(&ctx->vb_q, vma);
	अगर (ret) अणु
		dprपूर्णांकk(1, "[%s] errno=%d\n", ctx->name, ret);
		वापस ret;
	पूर्ण
	dprपूर्णांकk(3, "[%s] ret=%d\n", ctx->name, ret);

	वापस 0;
पूर्ण

__poll_t dvb_vb2_poll(काष्ठा dvb_vb2_ctx *ctx, काष्ठा file *file,
		      poll_table *रुको)
अणु
	dprपूर्णांकk(3, "[%s]\n", ctx->name);
	वापस vb2_core_poll(&ctx->vb_q, file, रुको);
पूर्ण

