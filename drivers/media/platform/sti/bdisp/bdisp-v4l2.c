<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "bdisp.h"

#घोषणा BDISP_MAX_CTRL_NUM      10

#घोषणा BDISP_WORK_TIMEOUT      ((100 * HZ) / 1000)

/* User configuration change */
#घोषणा BDISP_PARAMS            BIT(0) /* Config updated */
#घोषणा BDISP_SRC_FMT           BIT(1) /* Source set */
#घोषणा BDISP_DST_FMT           BIT(2) /* Destination set */
#घोषणा BDISP_CTX_STOP_REQ      BIT(3) /* Stop request */
#घोषणा BDISP_CTX_ABORT         BIT(4) /* Abort जबतक device run */

#घोषणा BDISP_MIN_W             1
#घोषणा BDISP_MAX_W             8191
#घोषणा BDISP_MIN_H             1
#घोषणा BDISP_MAX_H             8191

#घोषणा fh_to_ctx(__fh) container_of(__fh, काष्ठा bdisp_ctx, fh)

क्रमागत bdisp_dev_flags अणु
	ST_M2M_OPEN,            /* Driver खोलोed */
	ST_M2M_RUNNING,         /* HW device running */
	ST_M2M_SUSPENDED,       /* Driver suspended */
	ST_M2M_SUSPENDING,      /* Driver being suspended */
पूर्ण;

अटल स्थिर काष्ठा bdisp_fmt bdisp_क्रमmats[] = अणु
	/* ARGB888. [31:0] A:R:G:B 8:8:8:8 little endian */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_ABGR32, /* is actually ARGB */
		.nb_planes      = 1,
		.bpp            = 32,
		.bpp_plane0     = 32,
		.w_align        = 1,
		.h_align        = 1
	पूर्ण,
	/* XRGB888. [31:0] x:R:G:B 8:8:8:8 little endian */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_XBGR32, /* is actually xRGB */
		.nb_planes      = 1,
		.bpp            = 32,
		.bpp_plane0     = 32,
		.w_align        = 1,
		.h_align        = 1
	पूर्ण,
	/* RGB565. [15:0] R:G:B 5:6:5 little endian */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_RGB565,
		.nb_planes      = 1,
		.bpp            = 16,
		.bpp_plane0     = 16,
		.w_align        = 1,
		.h_align        = 1
	पूर्ण,
	/* NV12. YUV420SP - 1 plane क्रम Y + 1 plane क्रम (CbCr) */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_NV12,
		.nb_planes      = 2,
		.bpp            = 12,
		.bpp_plane0     = 8,
		.w_align        = 2,
		.h_align        = 2
	पूर्ण,
	/* RGB888. [23:0] B:G:R 8:8:8 little endian */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_RGB24,
		.nb_planes      = 1,
		.bpp            = 24,
		.bpp_plane0     = 24,
		.w_align        = 1,
		.h_align        = 1
	पूर्ण,
	/* YU12. YUV420P - 1 plane क्रम Y + 1 plane क्रम Cb + 1 plane क्रम Cr
	 * To keep as the LAST element of this table (no support on capture)
	 */
	अणु
		.pixelक्रमmat    = V4L2_PIX_FMT_YUV420,
		.nb_planes      = 3,
		.bpp            = 12,
		.bpp_plane0     = 8,
		.w_align        = 2,
		.h_align        = 2
	पूर्ण
पूर्ण;

/* Default क्रमmat : HD ARGB32*/
#घोषणा BDISP_DEF_WIDTH         1920
#घोषणा BDISP_DEF_HEIGHT        1080

अटल स्थिर काष्ठा bdisp_frame bdisp_dflt_fmt = अणु
		.width          = BDISP_DEF_WIDTH,
		.height         = BDISP_DEF_HEIGHT,
		.fmt            = &bdisp_क्रमmats[0],
		.field          = V4L2_FIELD_NONE,
		.bytesperline   = BDISP_DEF_WIDTH * 4,
		.sizeimage      = BDISP_DEF_WIDTH * BDISP_DEF_HEIGHT * 4,
		.colorspace     = V4L2_COLORSPACE_REC709,
		.crop           = अणु0, 0, BDISP_DEF_WIDTH, BDISP_DEF_HEIGHTपूर्ण,
		.paddr          = अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल अंतरभूत व्योम bdisp_ctx_state_lock_set(u32 state, काष्ठा bdisp_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->bdisp_dev->slock, flags);
	ctx->state |= state;
	spin_unlock_irqrestore(&ctx->bdisp_dev->slock, flags);
पूर्ण

अटल अंतरभूत व्योम bdisp_ctx_state_lock_clear(u32 state, काष्ठा bdisp_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->bdisp_dev->slock, flags);
	ctx->state &= ~state;
	spin_unlock_irqrestore(&ctx->bdisp_dev->slock, flags);
पूर्ण

अटल अंतरभूत bool bdisp_ctx_state_is_set(u32 mask, काष्ठा bdisp_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&ctx->bdisp_dev->slock, flags);
	ret = (ctx->state & mask) == mask;
	spin_unlock_irqrestore(&ctx->bdisp_dev->slock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bdisp_fmt *bdisp_find_fmt(u32 pixelक्रमmat)
अणु
	स्थिर काष्ठा bdisp_fmt *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bdisp_क्रमmats); i++) अणु
		fmt = &bdisp_क्रमmats[i];
		अगर (fmt->pixelक्रमmat == pixelक्रमmat)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा bdisp_frame *ctx_get_frame(काष्ठा bdisp_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &ctx->src;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &ctx->dst;
	शेष:
		dev_err(ctx->bdisp_dev->dev,
			"Wrong buffer/video queue type (%d)\n", type);
		अवरोध;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम bdisp_job_finish(काष्ठा bdisp_ctx *ctx, पूर्णांक vb_state)
अणु
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	अगर (WARN(!ctx || !ctx->fh.m2m_ctx, "Null hardware context\n"))
		वापस;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	src_vb = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	अगर (src_vb && dst_vb) अणु
		dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;
		dst_vb->समयcode = src_vb->समयcode;
		dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst_vb->flags |= src_vb->flags &
					  V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_करोne(src_vb, vb_state);
		v4l2_m2m_buf_करोne(dst_vb, vb_state);

		v4l2_m2m_job_finish(ctx->bdisp_dev->m2m.m2m_dev,
				    ctx->fh.m2m_ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक bdisp_ctx_stop_req(काष्ठा bdisp_ctx *ctx)
अणु
	काष्ठा bdisp_ctx *curr_ctx;
	काष्ठा bdisp_dev *bdisp = ctx->bdisp_dev;
	पूर्णांक ret;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	cancel_delayed_work(&bdisp->समयout_work);

	curr_ctx = v4l2_m2m_get_curr_priv(bdisp->m2m.m2m_dev);
	अगर (!test_bit(ST_M2M_RUNNING, &bdisp->state) || (curr_ctx != ctx))
		वापस 0;

	bdisp_ctx_state_lock_set(BDISP_CTX_STOP_REQ, ctx);

	ret = रुको_event_समयout(bdisp->irq_queue,
			!bdisp_ctx_state_is_set(BDISP_CTX_STOP_REQ, ctx),
			BDISP_WORK_TIMEOUT);

	अगर (!ret) अणु
		dev_err(ctx->bdisp_dev->dev, "%s IRQ timeout\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __bdisp_job_पात(काष्ठा bdisp_ctx *ctx)
अणु
	पूर्णांक ret;

	ret = bdisp_ctx_stop_req(ctx);
	अगर ((ret == -ETIMEDOUT) || (ctx->state & BDISP_CTX_ABORT)) अणु
		bdisp_ctx_state_lock_clear(BDISP_CTX_STOP_REQ | BDISP_CTX_ABORT,
					   ctx);
		bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल व्योम bdisp_job_पात(व्योम *priv)
अणु
	__bdisp_job_पात((काष्ठा bdisp_ctx *)priv);
पूर्ण

अटल पूर्णांक bdisp_get_addr(काष्ठा bdisp_ctx *ctx, काष्ठा vb2_buffer *vb,
			  काष्ठा bdisp_frame *frame, dma_addr_t *paddr)
अणु
	अगर (!vb || !frame)
		वापस -EINVAL;

	paddr[0] = vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (frame->fmt->nb_planes > 1)
		/* UV (NV12) or U (420P) */
		paddr[1] = (dma_addr_t)(paddr[0] +
				frame->bytesperline * frame->height);

	अगर (frame->fmt->nb_planes > 2)
		/* V (420P) */
		paddr[2] = (dma_addr_t)(paddr[1] +
				(frame->bytesperline * frame->height) / 4);

	अगर (frame->fmt->nb_planes > 3)
		dev_dbg(ctx->bdisp_dev->dev, "ignoring some planes\n");

	dev_dbg(ctx->bdisp_dev->dev,
		"%s plane[0]=%pad plane[1]=%pad plane[2]=%pad\n",
		__func__, &paddr[0], &paddr[1], &paddr[2]);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_get_bufs(काष्ठा bdisp_ctx *ctx)
अणु
	काष्ठा bdisp_frame *src, *dst;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	पूर्णांक ret;

	src = &ctx->src;
	dst = &ctx->dst;

	src_vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	ret = bdisp_get_addr(ctx, &src_vb->vb2_buf, src, src->paddr);
	अगर (ret)
		वापस ret;

	dst_vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	ret = bdisp_get_addr(ctx, &dst_vb->vb2_buf, dst, dst->paddr);
	अगर (ret)
		वापस ret;

	dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;

	वापस 0;
पूर्ण

अटल व्योम bdisp_device_run(व्योम *priv)
अणु
	काष्ठा bdisp_ctx *ctx = priv;
	काष्ठा bdisp_dev *bdisp;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (WARN(!ctx, "Null hardware context\n"))
		वापस;

	bdisp = ctx->bdisp_dev;
	dev_dbg(bdisp->dev, "%s\n", __func__);
	spin_lock_irqsave(&bdisp->slock, flags);

	अगर (bdisp->m2m.ctx != ctx) अणु
		dev_dbg(bdisp->dev, "ctx updated: %p -> %p\n",
			bdisp->m2m.ctx, ctx);
		ctx->state |= BDISP_PARAMS;
		bdisp->m2m.ctx = ctx;
	पूर्ण

	अगर (ctx->state & BDISP_CTX_STOP_REQ) अणु
		ctx->state &= ~BDISP_CTX_STOP_REQ;
		ctx->state |= BDISP_CTX_ABORT;
		wake_up(&bdisp->irq_queue);
		जाओ out;
	पूर्ण

	err = bdisp_get_bufs(ctx);
	अगर (err) अणु
		dev_err(bdisp->dev, "cannot get address\n");
		जाओ out;
	पूर्ण

	bdisp_dbg_perf_begin(bdisp);

	err = bdisp_hw_reset(bdisp);
	अगर (err) अणु
		dev_err(bdisp->dev, "could not get HW ready\n");
		जाओ out;
	पूर्ण

	err = bdisp_hw_update(ctx);
	अगर (err) अणु
		dev_err(bdisp->dev, "could not send HW request\n");
		जाओ out;
	पूर्ण

	queue_delayed_work(bdisp->work_queue, &bdisp->समयout_work,
			   BDISP_WORK_TIMEOUT);
	set_bit(ST_M2M_RUNNING, &bdisp->state);
out:
	ctx->state &= ~BDISP_PARAMS;
	spin_unlock_irqrestore(&bdisp->slock, flags);
	अगर (err)
		bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops bdisp_m2m_ops = अणु
	.device_run     = bdisp_device_run,
	.job_पात      = bdisp_job_पात,
पूर्ण;

अटल पूर्णांक __bdisp_s_ctrl(काष्ठा bdisp_ctx *ctx, काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		अवरोध;
	शेष:
		dev_err(ctx->bdisp_dev->dev, "unknown control %d\n", ctrl->id);
		वापस -EINVAL;
	पूर्ण

	ctx->state |= BDISP_PARAMS;

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा bdisp_ctx *ctx = container_of(ctrl->handler, काष्ठा bdisp_ctx,
						ctrl_handler);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctx->bdisp_dev->slock, flags);
	ret = __bdisp_s_ctrl(ctx, ctrl);
	spin_unlock_irqrestore(&ctx->bdisp_dev->slock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops bdisp_c_ops = अणु
	.s_ctrl = bdisp_s_ctrl,
पूर्ण;

अटल पूर्णांक bdisp_ctrls_create(काष्ठा bdisp_ctx *ctx)
अणु
	अगर (ctx->ctrls_rdy)
		वापस 0;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, BDISP_MAX_CTRL_NUM);

	ctx->bdisp_ctrls.hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&bdisp_c_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctx->bdisp_ctrls.vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&bdisp_c_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		वापस err;
	पूर्ण

	ctx->ctrls_rdy = true;

	वापस 0;
पूर्ण

अटल व्योम bdisp_ctrls_delete(काष्ठा bdisp_ctx *ctx)
अणु
	अगर (ctx->ctrls_rdy) अणु
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		ctx->ctrls_rdy = false;
	पूर्ण
पूर्ण

अटल पूर्णांक bdisp_queue_setup(काष्ठा vb2_queue *vq,
			     अचिन्हित पूर्णांक *nb_buf, अचिन्हित पूर्णांक *nb_planes,
			     अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा bdisp_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा bdisp_frame *frame = ctx_get_frame(ctx, vq->type);

	अगर (IS_ERR(frame)) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		वापस PTR_ERR(frame);
	पूर्ण

	अगर (!frame->fmt) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*nb_planes)
		वापस sizes[0] < frame->sizeimage ? -EINVAL : 0;

	*nb_planes = 1;
	sizes[0] = frame->sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा bdisp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा bdisp_frame *frame = ctx_get_frame(ctx, vb->vb2_queue->type);

	अगर (IS_ERR(frame)) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		वापस PTR_ERR(frame);
	पूर्ण

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		vb2_set_plane_payload(vb, 0, frame->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम bdisp_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा bdisp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	/* वापस to V4L2 any 0-size buffer so it can be dequeued by user */
	अगर (!vb2_get_plane_payload(vb, 0)) अणु
		dev_dbg(ctx->bdisp_dev->dev, "0 data buffer, skip it\n");
		vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
		वापस;
	पूर्ण

	अगर (ctx->fh.m2m_ctx)
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक bdisp_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा bdisp_ctx *ctx = q->drv_priv;
	काष्ठा vb2_v4l2_buffer *buf;
	पूर्णांक ret = pm_runसमय_get_sync(ctx->bdisp_dev->dev);

	अगर (ret < 0) अणु
		dev_err(ctx->bdisp_dev->dev, "failed to set runtime PM\n");

		अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
			जबतक ((buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
				v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
		पूर्ण अन्यथा अणु
			जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
				v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
		पूर्ण

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bdisp_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा bdisp_ctx *ctx = q->drv_priv;

	__bdisp_job_पात(ctx);

	pm_runसमय_put(ctx->bdisp_dev->dev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops bdisp_qops = अणु
	.queue_setup     = bdisp_queue_setup,
	.buf_prepare     = bdisp_buf_prepare,
	.buf_queue       = bdisp_buf_queue,
	.रुको_prepare    = vb2_ops_रुको_prepare,
	.रुको_finish     = vb2_ops_रुको_finish,
	.stop_streaming  = bdisp_stop_streaming,
	.start_streaming = bdisp_start_streaming,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv,
		      काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा bdisp_ctx *ctx = priv;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &bdisp_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->bdisp_dev->lock;
	src_vq->dev = ctx->bdisp_dev->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &bdisp_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->bdisp_dev->lock;
	dst_vq->dev = ctx->bdisp_dev->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक bdisp_खोलो(काष्ठा file *file)
अणु
	काष्ठा bdisp_dev *bdisp = video_drvdata(file);
	काष्ठा bdisp_ctx *ctx = शून्य;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&bdisp->lock))
		वापस -ERESTARTSYS;

	/* Allocate memory क्रम both context and node */
	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	ctx->bdisp_dev = bdisp;

	अगर (bdisp_hw_alloc_nodes(ctx)) अणु
		dev_err(bdisp->dev, "no memory for nodes\n");
		ret = -ENOMEM;
		जाओ mem_ctx;
	पूर्ण

	v4l2_fh_init(&ctx->fh, bdisp->m2m.vdev);

	ret = bdisp_ctrls_create(ctx);
	अगर (ret) अणु
		dev_err(bdisp->dev, "Failed to create control\n");
		जाओ error_fh;
	पूर्ण

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	/* Default क्रमmat */
	ctx->src = bdisp_dflt_fmt;
	ctx->dst = bdisp_dflt_fmt;

	/* Setup the device context क्रम mem2mem mode. */
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(bdisp->m2m.m2m_dev, ctx,
					    queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		dev_err(bdisp->dev, "Failed to initialize m2m context\n");
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ error_ctrls;
	पूर्ण

	bdisp->m2m.refcnt++;
	set_bit(ST_M2M_OPEN, &bdisp->state);

	dev_dbg(bdisp->dev, "driver opened, ctx = 0x%p\n", ctx);

	mutex_unlock(&bdisp->lock);

	वापस 0;

error_ctrls:
	bdisp_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_निकास(&ctx->fh);
	bdisp_hw_मुक्त_nodes(ctx);
mem_ctx:
	kमुक्त(ctx);
unlock:
	mutex_unlock(&bdisp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक bdisp_release(काष्ठा file *file)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा bdisp_dev *bdisp = ctx->bdisp_dev;

	dev_dbg(bdisp->dev, "%s\n", __func__);

	mutex_lock(&bdisp->lock);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	bdisp_ctrls_delete(ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);

	अगर (--bdisp->m2m.refcnt <= 0)
		clear_bit(ST_M2M_OPEN, &bdisp->state);

	bdisp_hw_मुक्त_nodes(ctx);

	kमुक्त(ctx);

	mutex_unlock(&bdisp->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations bdisp_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = bdisp_खोलो,
	.release        = bdisp_release,
	.poll           = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक bdisp_querycap(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_capability *cap)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा bdisp_dev *bdisp = ctx->bdisp_dev;

	strscpy(cap->driver, bdisp->pdev->name, माप(cap->driver));
	strscpy(cap->card, bdisp->pdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s%d",
		 BDISP_NAME, bdisp->id);
	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_क्रमागत_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	स्थिर काष्ठा bdisp_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(bdisp_क्रमmats))
		वापस -EINVAL;

	fmt = &bdisp_क्रमmats[f->index];

	अगर ((fmt->pixelक्रमmat == V4L2_PIX_FMT_YUV420) &&
	    (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)) अणु
		dev_dbg(ctx->bdisp_dev->dev, "No YU12 on capture\n");
		वापस -EINVAL;
	पूर्ण
	f->pixelक्रमmat = fmt->pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_pix_क्रमmat *pix;
	काष्ठा bdisp_frame *frame  = ctx_get_frame(ctx, f->type);

	अगर (IS_ERR(frame)) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		वापस PTR_ERR(frame);
	पूर्ण

	pix = &f->fmt.pix;
	pix->width = frame->width;
	pix->height = frame->height;
	pix->pixelक्रमmat = frame->fmt->pixelक्रमmat;
	pix->field = frame->field;
	pix->bytesperline = frame->bytesperline;
	pix->sizeimage = frame->sizeimage;
	pix->colorspace = (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) ?
				frame->colorspace : bdisp_dflt_fmt.colorspace;

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	स्थिर काष्ठा bdisp_fmt *क्रमmat;
	u32 in_w, in_h;

	क्रमmat = bdisp_find_fmt(pix->pixelक्रमmat);
	अगर (!क्रमmat) अणु
		dev_dbg(ctx->bdisp_dev->dev, "Unknown format 0x%x\n",
			pix->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* YUV420P only supported क्रम VIDEO_OUTPUT */
	अगर ((क्रमmat->pixelक्रमmat == V4L2_PIX_FMT_YUV420) &&
	    (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)) अणु
		dev_dbg(ctx->bdisp_dev->dev, "No YU12 on capture\n");
		वापस -EINVAL;
	पूर्ण

	/* Field (पूर्णांकerlaced only supported on OUTPUT) */
	अगर ((f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ||
	    (pix->field != V4L2_FIELD_INTERLACED))
		pix->field = V4L2_FIELD_NONE;

	/* Adjust width & height */
	in_w = pix->width;
	in_h = pix->height;
	v4l_bound_align_image(&pix->width,
			      BDISP_MIN_W, BDISP_MAX_W,
			      ffs(क्रमmat->w_align) - 1,
			      &pix->height,
			      BDISP_MIN_H, BDISP_MAX_H,
			      ffs(क्रमmat->h_align) - 1,
			      0);
	अगर ((pix->width != in_w) || (pix->height != in_h))
		dev_dbg(ctx->bdisp_dev->dev,
			"%s size updated: %dx%d -> %dx%d\n", __func__,
			in_w, in_h, pix->width, pix->height);

	pix->bytesperline = (pix->width * क्रमmat->bpp_plane0) / 8;
	pix->sizeimage = (pix->width * pix->height * क्रमmat->bpp) / 8;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		pix->colorspace = bdisp_dflt_fmt.colorspace;

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा vb2_queue *vq;
	काष्ठा bdisp_frame *frame;
	काष्ठा v4l2_pix_क्रमmat *pix;
	पूर्णांक ret;
	u32 state;

	ret = bdisp_try_fmt(file, fh, f);
	अगर (ret) अणु
		dev_err(ctx->bdisp_dev->dev, "Cannot set format\n");
		वापस ret;
	पूर्ण

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_err(ctx->bdisp_dev->dev, "queue (%d) busy\n", f->type);
		वापस -EBUSY;
	पूर्ण

	frame = (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) ?
			&ctx->src : &ctx->dst;
	pix = &f->fmt.pix;
	frame->fmt = bdisp_find_fmt(pix->pixelक्रमmat);
	अगर (!frame->fmt) अणु
		dev_err(ctx->bdisp_dev->dev, "Unknown format 0x%x\n",
			pix->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	frame->width = pix->width;
	frame->height = pix->height;
	frame->bytesperline = pix->bytesperline;
	frame->sizeimage = pix->sizeimage;
	frame->field = pix->field;
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		frame->colorspace = pix->colorspace;

	frame->crop.width = frame->width;
	frame->crop.height = frame->height;
	frame->crop.left = 0;
	frame->crop.top = 0;

	state = BDISP_PARAMS;
	state |= (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ?
			BDISP_DST_FMT : BDISP_SRC_FMT;
	bdisp_ctx_state_lock_set(state, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_g_selection(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_selection *s)
अणु
	काष्ठा bdisp_frame *frame;
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);

	frame = ctx_get_frame(ctx, s->type);
	अगर (IS_ERR(frame)) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		वापस PTR_ERR(frame);
	पूर्ण

	चयन (s->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		चयन (s->target) अणु
		हाल V4L2_SEL_TGT_CROP:
			/* cropped frame */
			s->r = frame->crop;
			अवरोध;
		हाल V4L2_SEL_TGT_CROP_DEFAULT:
		हाल V4L2_SEL_TGT_CROP_BOUNDS:
			/* complete frame */
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = frame->width;
			s->r.height = frame->height;
			अवरोध;
		शेष:
			dev_err(ctx->bdisp_dev->dev, "Invalid target\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		चयन (s->target) अणु
		हाल V4L2_SEL_TGT_COMPOSE:
		हाल V4L2_SEL_TGT_COMPOSE_PADDED:
			/* composed (cropped) frame */
			s->r = frame->crop;
			अवरोध;
		हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
			/* complete frame */
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = frame->width;
			s->r.height = frame->height;
			अवरोध;
		शेष:
			dev_err(ctx->bdisp_dev->dev, "Invalid target\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(ctx->bdisp_dev->dev, "Invalid type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_rect_enबंदd(काष्ठा v4l2_rect *a, काष्ठा v4l2_rect *b)
अणु
	/* Return 1 अगर a is enबंदd in b, or 0 otherwise. */

	अगर (a->left < b->left || a->top < b->top)
		वापस 0;

	अगर (a->left + a->width > b->left + b->width)
		वापस 0;

	अगर (a->top + a->height > b->top + b->height)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक bdisp_s_selection(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_selection *s)
अणु
	काष्ठा bdisp_frame *frame;
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_rect *in, out;
	bool valid = false;

	अगर ((s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) &&
	    (s->target == V4L2_SEL_TGT_CROP))
		valid = true;

	अगर ((s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->target == V4L2_SEL_TGT_COMPOSE))
		valid = true;

	अगर (!valid) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid type / target\n");
		वापस -EINVAL;
	पूर्ण

	frame = ctx_get_frame(ctx, s->type);
	अगर (IS_ERR(frame)) अणु
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		वापस PTR_ERR(frame);
	पूर्ण

	in = &s->r;
	out = *in;

	/* Align and check origin */
	out.left = ALIGN(in->left, frame->fmt->w_align);
	out.top = ALIGN(in->top, frame->fmt->h_align);

	अगर ((out.left < 0) || (out.left >= frame->width) ||
	    (out.top < 0) || (out.top >= frame->height)) अणु
		dev_err(ctx->bdisp_dev->dev,
			"Invalid crop: %dx%d@(%d,%d) vs frame: %dx%d\n",
			out.width, out.height, out.left, out.top,
			frame->width, frame->height);
		वापस -EINVAL;
	पूर्ण

	/* Align and check size */
	out.width = ALIGN(in->width, frame->fmt->w_align);
	out.height = ALIGN(in->height, frame->fmt->w_align);

	अगर (((out.left + out.width) > frame->width) ||
	    ((out.top + out.height) > frame->height)) अणु
		dev_err(ctx->bdisp_dev->dev,
			"Invalid crop: %dx%d@(%d,%d) vs frame: %dx%d\n",
			out.width, out.height, out.left, out.top,
			frame->width, frame->height);
		वापस -EINVAL;
	पूर्ण

	/* Checks adjust स्थिरraपूर्णांकs flags */
	अगर (s->flags & V4L2_SEL_FLAG_LE && !is_rect_enबंदd(&out, in))
		वापस -दुस्फल;

	अगर (s->flags & V4L2_SEL_FLAG_GE && !is_rect_enबंदd(in, &out))
		वापस -दुस्फल;

	अगर ((out.left != in->left) || (out.top != in->top) ||
	    (out.width != in->width) || (out.height != in->height)) अणु
		dev_dbg(ctx->bdisp_dev->dev,
			"%s crop updated: %dx%d@(%d,%d) -> %dx%d@(%d,%d)\n",
			__func__, in->width, in->height, in->left, in->top,
			out.width, out.height, out.left, out.top);
		*in = out;
	पूर्ण

	frame->crop = out;

	bdisp_ctx_state_lock_set(BDISP_PARAMS, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा bdisp_ctx *ctx = fh_to_ctx(fh);

	अगर ((type == V4L2_BUF_TYPE_VIDEO_OUTPUT) &&
	    !bdisp_ctx_state_is_set(BDISP_SRC_FMT, ctx)) अणु
		dev_err(ctx->bdisp_dev->dev, "src not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    !bdisp_ctx_state_is_set(BDISP_DST_FMT, ctx)) अणु
		dev_err(ctx->bdisp_dev->dev, "dst not defined\n");
		वापस -EINVAL;
	पूर्ण

	वापस v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops bdisp_ioctl_ops = अणु
	.vidioc_querycap                = bdisp_querycap,
	.vidioc_क्रमागत_fmt_vid_cap        = bdisp_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out        = bdisp_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap           = bdisp_g_fmt,
	.vidioc_g_fmt_vid_out           = bdisp_g_fmt,
	.vidioc_try_fmt_vid_cap         = bdisp_try_fmt,
	.vidioc_try_fmt_vid_out         = bdisp_try_fmt,
	.vidioc_s_fmt_vid_cap           = bdisp_s_fmt,
	.vidioc_s_fmt_vid_out           = bdisp_s_fmt,
	.vidioc_g_selection		= bdisp_g_selection,
	.vidioc_s_selection		= bdisp_s_selection,
	.vidioc_reqbufs                 = v4l2_m2m_ioctl_reqbufs,
	.vidioc_create_bufs             = v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf                  = v4l2_m2m_ioctl_expbuf,
	.vidioc_querybuf                = v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf                    = v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf                   = v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon                = bdisp_streamon,
	.vidioc_streamoff               = v4l2_m2m_ioctl_streamoff,
	.vidioc_subscribe_event         = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event       = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक bdisp_रेजिस्टर_device(काष्ठा bdisp_dev *bdisp)
अणु
	पूर्णांक ret;

	अगर (!bdisp)
		वापस -ENODEV;

	bdisp->vdev.fops        = &bdisp_fops;
	bdisp->vdev.ioctl_ops   = &bdisp_ioctl_ops;
	bdisp->vdev.release     = video_device_release_empty;
	bdisp->vdev.lock        = &bdisp->lock;
	bdisp->vdev.vfl_dir     = VFL_सूची_M2M;
	bdisp->vdev.v4l2_dev    = &bdisp->v4l2_dev;
	bdisp->vdev.device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	snम_लिखो(bdisp->vdev.name, माप(bdisp->vdev.name), "%s.%d",
		 BDISP_NAME, bdisp->id);

	video_set_drvdata(&bdisp->vdev, bdisp);

	bdisp->m2m.vdev = &bdisp->vdev;
	bdisp->m2m.m2m_dev = v4l2_m2m_init(&bdisp_m2m_ops);
	अगर (IS_ERR(bdisp->m2m.m2m_dev)) अणु
		dev_err(bdisp->dev, "failed to initialize v4l2-m2m device\n");
		वापस PTR_ERR(bdisp->m2m.m2m_dev);
	पूर्ण

	ret = video_रेजिस्टर_device(&bdisp->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(bdisp->dev,
			"%s(): failed to register video device\n", __func__);
		v4l2_m2m_release(bdisp->m2m.m2m_dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bdisp_unरेजिस्टर_device(काष्ठा bdisp_dev *bdisp)
अणु
	अगर (!bdisp)
		वापस;

	अगर (bdisp->m2m.m2m_dev)
		v4l2_m2m_release(bdisp->m2m.m2m_dev);

	video_unरेजिस्टर_device(bdisp->m2m.vdev);
पूर्ण

अटल irqवापस_t bdisp_irq_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा bdisp_dev *bdisp = priv;
	काष्ठा bdisp_ctx *ctx;

	spin_lock(&bdisp->slock);

	bdisp_dbg_perf_end(bdisp);

	cancel_delayed_work(&bdisp->समयout_work);

	अगर (!test_and_clear_bit(ST_M2M_RUNNING, &bdisp->state))
		जाओ isr_unlock;

	अगर (test_and_clear_bit(ST_M2M_SUSPENDING, &bdisp->state)) अणु
		set_bit(ST_M2M_SUSPENDED, &bdisp->state);
		wake_up(&bdisp->irq_queue);
		जाओ isr_unlock;
	पूर्ण

	ctx = v4l2_m2m_get_curr_priv(bdisp->m2m.m2m_dev);
	अगर (!ctx || !ctx->fh.m2m_ctx)
		जाओ isr_unlock;

	spin_unlock(&bdisp->slock);

	bdisp_job_finish(ctx, VB2_BUF_STATE_DONE);

	अगर (bdisp_ctx_state_is_set(BDISP_CTX_STOP_REQ, ctx)) अणु
		bdisp_ctx_state_lock_clear(BDISP_CTX_STOP_REQ, ctx);
		wake_up(&bdisp->irq_queue);
	पूर्ण

	वापस IRQ_HANDLED;

isr_unlock:
	spin_unlock(&bdisp->slock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bdisp_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	अगर (bdisp_hw_get_and_clear_irq((काष्ठा bdisp_dev *)priv))
		वापस IRQ_NONE;
	अन्यथा
		वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम bdisp_irq_समयout(काष्ठा work_काष्ठा *ptr)
अणु
	काष्ठा delayed_work *twork = to_delayed_work(ptr);
	काष्ठा bdisp_dev *bdisp = container_of(twork, काष्ठा bdisp_dev,
			समयout_work);
	काष्ठा bdisp_ctx *ctx;

	ctx = v4l2_m2m_get_curr_priv(bdisp->m2m.m2m_dev);

	dev_err(ctx->bdisp_dev->dev, "Device work timeout\n");

	spin_lock(&bdisp->slock);
	clear_bit(ST_M2M_RUNNING, &bdisp->state);
	spin_unlock(&bdisp->slock);

	bdisp_hw_reset(bdisp);

	bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);
पूर्ण

अटल पूर्णांक bdisp_m2m_suspend(काष्ठा bdisp_dev *bdisp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout;

	spin_lock_irqsave(&bdisp->slock, flags);
	अगर (!test_bit(ST_M2M_RUNNING, &bdisp->state)) अणु
		spin_unlock_irqrestore(&bdisp->slock, flags);
		वापस 0;
	पूर्ण
	clear_bit(ST_M2M_SUSPENDED, &bdisp->state);
	set_bit(ST_M2M_SUSPENDING, &bdisp->state);
	spin_unlock_irqrestore(&bdisp->slock, flags);

	समयout = रुको_event_समयout(bdisp->irq_queue,
				     test_bit(ST_M2M_SUSPENDED, &bdisp->state),
				     BDISP_WORK_TIMEOUT);

	clear_bit(ST_M2M_SUSPENDING, &bdisp->state);

	अगर (!समयout) अणु
		dev_err(bdisp->dev, "%s IRQ timeout\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_m2m_resume(काष्ठा bdisp_dev *bdisp)
अणु
	काष्ठा bdisp_ctx *ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bdisp->slock, flags);
	ctx = bdisp->m2m.ctx;
	bdisp->m2m.ctx = शून्य;
	spin_unlock_irqrestore(&bdisp->slock, flags);

	अगर (test_and_clear_bit(ST_M2M_SUSPENDED, &bdisp->state))
		bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा bdisp_dev *bdisp = dev_get_drvdata(dev);
	पूर्णांक ret = clk_enable(bdisp->घड़ी);

	अगर (ret)
		वापस ret;

	वापस bdisp_m2m_resume(bdisp);
पूर्ण

अटल पूर्णांक bdisp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा bdisp_dev *bdisp = dev_get_drvdata(dev);
	पूर्णांक ret = bdisp_m2m_suspend(bdisp);

	अगर (!ret)
		clk_disable(bdisp->घड़ी);

	वापस ret;
पूर्ण

अटल पूर्णांक bdisp_resume(काष्ठा device *dev)
अणु
	काष्ठा bdisp_dev *bdisp = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक खोलोed;

	spin_lock_irqsave(&bdisp->slock, flags);
	खोलोed = test_bit(ST_M2M_OPEN, &bdisp->state);
	spin_unlock_irqrestore(&bdisp->slock, flags);

	अगर (!खोलोed)
		वापस 0;

	अगर (!pm_runसमय_suspended(dev))
		वापस bdisp_runसमय_resume(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_suspend(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_suspended(dev))
		वापस bdisp_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bdisp_pm_ops = अणु
	.suspend                = bdisp_suspend,
	.resume                 = bdisp_resume,
	.runसमय_suspend        = bdisp_runसमय_suspend,
	.runसमय_resume         = bdisp_runसमय_resume,
पूर्ण;

अटल पूर्णांक bdisp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdisp_dev *bdisp = platक्रमm_get_drvdata(pdev);

	bdisp_unरेजिस्टर_device(bdisp);

	bdisp_hw_मुक्त_filters(bdisp->dev);

	pm_runसमय_disable(&pdev->dev);

	bdisp_debugfs_हटाओ(bdisp);

	v4l2_device_unरेजिस्टर(&bdisp->v4l2_dev);

	अगर (!IS_ERR(bdisp->घड़ी))
		clk_unprepare(bdisp->घड़ी);

	destroy_workqueue(bdisp->work_queue);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक bdisp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdisp_dev *bdisp;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	bdisp = devm_kzalloc(dev, माप(काष्ठा bdisp_dev), GFP_KERNEL);
	अगर (!bdisp)
		वापस -ENOMEM;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	bdisp->pdev = pdev;
	bdisp->dev = dev;
	platक्रमm_set_drvdata(pdev, bdisp);

	अगर (dev->of_node)
		bdisp->id = of_alias_get_id(pdev->dev.of_node, BDISP_NAME);
	अन्यथा
		bdisp->id = pdev->id;

	init_रुकोqueue_head(&bdisp->irq_queue);
	INIT_DELAYED_WORK(&bdisp->समयout_work, bdisp_irq_समयout);
	bdisp->work_queue = create_workqueue(BDISP_NAME);

	spin_lock_init(&bdisp->slock);
	mutex_init(&bdisp->lock);

	/* get resources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	bdisp->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(bdisp->regs)) अणु
		dev_err(dev, "failed to get regs\n");
		ret = PTR_ERR(bdisp->regs);
		जाओ err_wq;
	पूर्ण

	bdisp->घड़ी = devm_clk_get(dev, BDISP_NAME);
	अगर (IS_ERR(bdisp->घड़ी)) अणु
		dev_err(dev, "failed to get clock\n");
		ret = PTR_ERR(bdisp->घड़ी);
		जाओ err_wq;
	पूर्ण

	ret = clk_prepare(bdisp->घड़ी);
	अगर (ret < 0) अणु
		dev_err(dev, "clock prepare failed\n");
		bdisp->घड़ी = ERR_PTR(-EINVAL);
		जाओ err_wq;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to get IRQ resource\n");
		ret = -EINVAL;
		जाओ err_clk;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, res->start, bdisp_irq_handler,
					bdisp_irq_thपढ़ो, IRQF_ONESHOT,
					pdev->name, bdisp);
	अगर (ret) अणु
		dev_err(dev, "failed to install irq\n");
		जाओ err_clk;
	पूर्ण

	/* v4l2 रेजिस्टर */
	ret = v4l2_device_रेजिस्टर(dev, &bdisp->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register\n");
		जाओ err_clk;
	पूर्ण

	/* Debug */
	bdisp_debugfs_create(bdisp);

	/* Power management */
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set PM\n");
		जाओ err_pm;
	पूर्ण

	/* Filters */
	अगर (bdisp_hw_alloc_filters(bdisp->dev)) अणु
		dev_err(bdisp->dev, "no memory for filters\n");
		ret = -ENOMEM;
		जाओ err_pm;
	पूर्ण

	/* Register */
	ret = bdisp_रेजिस्टर_device(bdisp);
	अगर (ret) अणु
		dev_err(dev, "failed to register\n");
		जाओ err_filter;
	पूर्ण

	dev_info(dev, "%s%d registered as /dev/video%d\n", BDISP_NAME,
		 bdisp->id, bdisp->vdev.num);

	pm_runसमय_put(dev);

	वापस 0;

err_filter:
	bdisp_hw_मुक्त_filters(bdisp->dev);
err_pm:
	pm_runसमय_put(dev);
	bdisp_debugfs_हटाओ(bdisp);
	v4l2_device_unरेजिस्टर(&bdisp->v4l2_dev);
err_clk:
	अगर (!IS_ERR(bdisp->घड़ी))
		clk_unprepare(bdisp->घड़ी);
err_wq:
	destroy_workqueue(bdisp->work_queue);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bdisp_match_types[] = अणु
	अणु
		.compatible = "st,stih407-bdisp",
	पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, bdisp_match_types);

अटल काष्ठा platक्रमm_driver bdisp_driver = अणु
	.probe          = bdisp_probe,
	.हटाओ         = bdisp_हटाओ,
	.driver         = अणु
		.name           = BDISP_NAME,
		.of_match_table = bdisp_match_types,
		.pm             = &bdisp_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bdisp_driver);

MODULE_DESCRIPTION("2D blitter for STMicroelectronics SoC");
MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_LICENSE("GPL");
