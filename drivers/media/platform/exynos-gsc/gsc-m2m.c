<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung EXYNOS5 SoC series G-Scaler driver
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>

#समावेश <media/v4l2-ioctl.h>

#समावेश "gsc-core.h"

अटल पूर्णांक gsc_m2m_ctx_stop_req(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_ctx *curr_ctx;
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	पूर्णांक ret;

	curr_ctx = v4l2_m2m_get_curr_priv(gsc->m2m.m2m_dev);
	अगर (!gsc_m2m_pending(gsc) || (curr_ctx != ctx))
		वापस 0;

	gsc_ctx_state_lock_set(GSC_CTX_STOP_REQ, ctx);
	ret = रुको_event_समयout(gsc->irq_queue,
			!gsc_ctx_state_is_set(GSC_CTX_STOP_REQ, ctx),
			GSC_SHUTDOWN_TIMEOUT);

	वापस ret == 0 ? -ETIMEDOUT : ret;
पूर्ण

अटल व्योम __gsc_m2m_job_पात(काष्ठा gsc_ctx *ctx)
अणु
	पूर्णांक ret;

	ret = gsc_m2m_ctx_stop_req(ctx);
	अगर ((ret == -ETIMEDOUT) || (ctx->state & GSC_CTX_ABORT)) अणु
		gsc_ctx_state_lock_clear(GSC_CTX_STOP_REQ | GSC_CTX_ABORT, ctx);
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल पूर्णांक gsc_m2m_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा gsc_ctx *ctx = q->drv_priv;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&ctx->gsc_dev->pdev->dev);
	वापस ret > 0 ? 0 : ret;
पूर्ण

अटल व्योम __gsc_m2m_cleanup_queue(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	जबतक (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->m2m_ctx) > 0) अणु
		src_vb = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
		v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_ERROR);
	पूर्ण

	जबतक (v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->m2m_ctx) > 0) अणु
		dst_vb = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
		v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल व्योम gsc_m2m_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा gsc_ctx *ctx = q->drv_priv;

	__gsc_m2m_job_पात(ctx);

	__gsc_m2m_cleanup_queue(ctx);

	pm_runसमय_put(&ctx->gsc_dev->pdev->dev);
पूर्ण

व्योम gsc_m2m_job_finish(काष्ठा gsc_ctx *ctx, पूर्णांक vb_state)
अणु
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	अगर (!ctx || !ctx->m2m_ctx)
		वापस;

	src_vb = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);

	अगर (src_vb && dst_vb) अणु
		dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;
		dst_vb->समयcode = src_vb->समयcode;
		dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst_vb->flags |=
			src_vb->flags
			& V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_करोne(src_vb, vb_state);
		v4l2_m2m_buf_करोne(dst_vb, vb_state);

		v4l2_m2m_job_finish(ctx->gsc_dev->m2m.m2m_dev,
				    ctx->m2m_ctx);
	पूर्ण
पूर्ण

अटल व्योम gsc_m2m_job_पात(व्योम *priv)
अणु
	__gsc_m2m_job_पात((काष्ठा gsc_ctx *)priv);
पूर्ण

अटल पूर्णांक gsc_get_bufs(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_frame *s_frame, *d_frame;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	पूर्णांक ret;

	s_frame = &ctx->s_frame;
	d_frame = &ctx->d_frame;

	src_vb = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	ret = gsc_prepare_addr(ctx, &src_vb->vb2_buf, s_frame, &s_frame->addr);
	अगर (ret)
		वापस ret;

	dst_vb = v4l2_m2m_next_dst_buf(ctx->m2m_ctx);
	ret = gsc_prepare_addr(ctx, &dst_vb->vb2_buf, d_frame, &d_frame->addr);
	अगर (ret)
		वापस ret;

	dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;

	वापस 0;
पूर्ण

अटल व्योम gsc_m2m_device_run(व्योम *priv)
अणु
	काष्ठा gsc_ctx *ctx = priv;
	काष्ठा gsc_dev *gsc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool is_set = false;

	अगर (WARN(!ctx, "null hardware context\n"))
		वापस;

	gsc = ctx->gsc_dev;
	spin_lock_irqsave(&gsc->slock, flags);

	set_bit(ST_M2M_PEND, &gsc->state);

	/* Reconfigure hardware अगर the context has changed. */
	अगर (gsc->m2m.ctx != ctx) अणु
		pr_debug("gsc->m2m.ctx = 0x%p, current_ctx = 0x%p",
				gsc->m2m.ctx, ctx);
		ctx->state |= GSC_PARAMS;
		gsc->m2m.ctx = ctx;
	पूर्ण

	is_set = ctx->state & GSC_CTX_STOP_REQ;
	अगर (is_set) अणु
		ctx->state &= ~GSC_CTX_STOP_REQ;
		ctx->state |= GSC_CTX_ABORT;
		wake_up(&gsc->irq_queue);
		जाओ put_device;
	पूर्ण

	ret = gsc_get_bufs(ctx);
	अगर (ret) अणु
		pr_err("Wrong address");
		जाओ put_device;
	पूर्ण

	gsc_set_prefbuf(gsc, &ctx->s_frame);
	gsc_hw_set_input_addr(gsc, &ctx->s_frame.addr, GSC_M2M_BUF_NUM);
	gsc_hw_set_output_addr(gsc, &ctx->d_frame.addr, GSC_M2M_BUF_NUM);

	अगर (ctx->state & GSC_PARAMS) अणु
		gsc_hw_set_input_buf_masking(gsc, GSC_M2M_BUF_NUM, false);
		gsc_hw_set_output_buf_masking(gsc, GSC_M2M_BUF_NUM, false);
		gsc_hw_set_frm_करोne_irq_mask(gsc, false);
		gsc_hw_set_gsc_irq_enable(gsc, true);

		अगर (gsc_set_scaler_info(ctx)) अणु
			pr_err("Scaler setup error");
			जाओ put_device;
		पूर्ण

		gsc_hw_set_input_path(ctx);
		gsc_hw_set_in_size(ctx);
		gsc_hw_set_in_image_क्रमmat(ctx);

		gsc_hw_set_output_path(ctx);
		gsc_hw_set_out_size(ctx);
		gsc_hw_set_out_image_क्रमmat(ctx);

		gsc_hw_set_prescaler(ctx);
		gsc_hw_set_मुख्यscaler(ctx);
		gsc_hw_set_rotation(ctx);
		gsc_hw_set_global_alpha(ctx);
	पूर्ण

	/* update shaकरोw रेजिस्टरs */
	gsc_hw_set_sfr_update(ctx);

	ctx->state &= ~GSC_PARAMS;
	gsc_hw_enable_control(gsc, true);

	spin_unlock_irqrestore(&gsc->slock, flags);
	वापस;

put_device:
	ctx->state &= ~GSC_PARAMS;
	spin_unlock_irqrestore(&gsc->slock, flags);
पूर्ण

अटल पूर्णांक gsc_m2m_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा gsc_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा gsc_frame *frame;
	पूर्णांक i;

	frame = ctx_get_frame(ctx, vq->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	अगर (!frame->fmt)
		वापस -EINVAL;

	*num_planes = frame->fmt->num_planes;
	क्रम (i = 0; i < frame->fmt->num_planes; i++)
		sizes[i] = frame->payload[i];
	वापस 0;
पूर्ण

अटल पूर्णांक gsc_m2m_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा gsc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा gsc_frame *frame;
	पूर्णांक i;

	frame = ctx_get_frame(ctx, vb->vb2_queue->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	अगर (V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type)) अणु
		क्रम (i = 0; i < frame->fmt->num_planes; i++)
			vb2_set_plane_payload(vb, i, frame->payload[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gsc_m2m_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा gsc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	pr_debug("ctx: %p, ctx->state: 0x%x", ctx, ctx->state);

	अगर (ctx->m2m_ctx)
		v4l2_m2m_buf_queue(ctx->m2m_ctx, vbuf);
पूर्ण

अटल स्थिर काष्ठा vb2_ops gsc_m2m_qops = अणु
	.queue_setup	 = gsc_m2m_queue_setup,
	.buf_prepare	 = gsc_m2m_buf_prepare,
	.buf_queue	 = gsc_m2m_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.stop_streaming	 = gsc_m2m_stop_streaming,
	.start_streaming = gsc_m2m_start_streaming,
पूर्ण;

अटल पूर्णांक gsc_m2m_querycap(काष्ठा file *file, व्योम *fh,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;

	strscpy(cap->driver, GSC_MODULE_NAME, माप(cap->driver));
	strscpy(cap->card, GSC_MODULE_NAME " gscaler", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(&gsc->pdev->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक gsc_m2m_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_fmtdesc *f)
अणु
	वापस gsc_क्रमागत_fmt(f);
पूर्ण

अटल पूर्णांक gsc_m2m_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);

	वापस gsc_g_fmt_mplane(ctx, f);
पूर्ण

अटल पूर्णांक gsc_m2m_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);

	वापस gsc_try_fmt_mplane(ctx, f);
पूर्ण

अटल पूर्णांक gsc_m2m_s_fmt_mplane(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा vb2_queue *vq;
	काष्ठा gsc_frame *frame;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix;
	पूर्णांक i, ret = 0;

	ret = gsc_m2m_try_fmt_mplane(file, fh, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);

	अगर (vb2_is_streaming(vq)) अणु
		pr_err("queue (%d) busy", f->type);
		वापस -EBUSY;
	पूर्ण

	अगर (V4L2_TYPE_IS_OUTPUT(f->type))
		frame = &ctx->s_frame;
	अन्यथा
		frame = &ctx->d_frame;

	pix = &f->fmt.pix_mp;
	frame->fmt = find_fmt(&pix->pixelक्रमmat, शून्य, 0);
	frame->colorspace = pix->colorspace;
	अगर (!frame->fmt)
		वापस -EINVAL;

	क्रम (i = 0; i < frame->fmt->num_planes; i++)
		frame->payload[i] = pix->plane_fmt[i].sizeimage;

	gsc_set_frame_size(frame, pix->width, pix->height);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		gsc_ctx_state_lock_set(GSC_PARAMS | GSC_DST_FMT, ctx);
	अन्यथा
		gsc_ctx_state_lock_set(GSC_PARAMS | GSC_SRC_FMT, ctx);

	pr_debug("f_w: %d, f_h: %d", frame->f_width, frame->f_height);

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_m2m_reqbufs(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	u32 max_cnt;

	max_cnt = (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) ?
		gsc->variant->in_buf_cnt : gsc->variant->out_buf_cnt;
	अगर (reqbufs->count > max_cnt)
		वापस -EINVAL;

	वापस v4l2_m2m_reqbufs(file, ctx->m2m_ctx, reqbufs);
पूर्ण

अटल पूर्णांक gsc_m2m_expbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_exportbuffer *eb)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	वापस v4l2_m2m_expbuf(file, ctx->m2m_ctx, eb);
पूर्ण

अटल पूर्णांक gsc_m2m_querybuf(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	वापस v4l2_m2m_querybuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक gsc_m2m_qbuf(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	वापस v4l2_m2m_qbuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक gsc_m2m_dqbuf(काष्ठा file *file, व्योम *fh,
			   काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	वापस v4l2_m2m_dqbuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक gsc_m2m_streamon(काष्ठा file *file, व्योम *fh,
			   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);

	/* The source and target color क्रमmat need to be set */
	अगर (V4L2_TYPE_IS_OUTPUT(type)) अणु
		अगर (!gsc_ctx_state_is_set(GSC_SRC_FMT, ctx))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!gsc_ctx_state_is_set(GSC_DST_FMT, ctx)) अणु
		वापस -EINVAL;
	पूर्ण

	वापस v4l2_m2m_streamon(file, ctx->m2m_ctx, type);
पूर्ण

अटल पूर्णांक gsc_m2m_streamoff(काष्ठा file *file, व्योम *fh,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	वापस v4l2_m2m_streamoff(file, ctx->m2m_ctx, type);
पूर्ण

/* Return 1 अगर rectangle a is enबंदd in rectangle b, or 0 otherwise. */
अटल पूर्णांक is_rectangle_enबंदd(काष्ठा v4l2_rect *a, काष्ठा v4l2_rect *b)
अणु
	अगर (a->left < b->left || a->top < b->top)
		वापस 0;

	अगर (a->left + a->width > b->left + b->width)
		वापस 0;

	अगर (a->top + a->height > b->top + b->height)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक gsc_m2m_g_selection(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_selection *s)
अणु
	काष्ठा gsc_frame *frame;
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);

	अगर ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		वापस -EINVAL;

	frame = ctx_get_frame(ctx, s->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frame->f_width;
		s->r.height = frame->f_height;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_CROP:
		s->r.left = frame->crop.left;
		s->r.top = frame->crop.top;
		s->r.width = frame->crop.width;
		s->r.height = frame->crop.height;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gsc_m2m_s_selection(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा gsc_frame *frame;
	काष्ठा gsc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा gsc_variant *variant = ctx->gsc_dev->variant;
	काष्ठा v4l2_selection sel = *s;
	पूर्णांक ret;

	अगर ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		वापस -EINVAL;

	ret = gsc_try_selection(ctx, &sel);
	अगर (ret)
		वापस ret;

	अगर (s->flags & V4L2_SEL_FLAG_LE &&
	    !is_rectangle_enबंदd(&sel.r, &s->r))
		वापस -दुस्फल;

	अगर (s->flags & V4L2_SEL_FLAG_GE &&
	    !is_rectangle_enबंदd(&s->r, &sel.r))
		वापस -दुस्फल;

	s->r = sel.r;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE:
		frame = &ctx->s_frame;
		अवरोध;

	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		frame = &ctx->d_frame;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Check to see अगर scaling ratio is within supported range */
	अगर (gsc_ctx_state_is_set(GSC_DST_FMT | GSC_SRC_FMT, ctx)) अणु
		अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
			ret = gsc_check_scaler_ratio(variant, sel.r.width,
				sel.r.height, ctx->d_frame.crop.width,
				ctx->d_frame.crop.height,
				ctx->gsc_ctrls.rotate->val, ctx->out_path);
		पूर्ण अन्यथा अणु
			ret = gsc_check_scaler_ratio(variant,
				ctx->s_frame.crop.width,
				ctx->s_frame.crop.height, sel.r.width,
				sel.r.height, ctx->gsc_ctrls.rotate->val,
				ctx->out_path);
		पूर्ण

		अगर (ret) अणु
			pr_err("Out of scaler range");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	frame->crop = sel.r;

	gsc_ctx_state_lock_set(GSC_PARAMS, ctx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops gsc_m2m_ioctl_ops = अणु
	.vidioc_querycap		= gsc_m2m_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= gsc_m2m_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out	= gsc_m2m_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap_mplane	= gsc_m2m_g_fmt_mplane,
	.vidioc_g_fmt_vid_out_mplane	= gsc_m2m_g_fmt_mplane,
	.vidioc_try_fmt_vid_cap_mplane	= gsc_m2m_try_fmt_mplane,
	.vidioc_try_fmt_vid_out_mplane	= gsc_m2m_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= gsc_m2m_s_fmt_mplane,
	.vidioc_s_fmt_vid_out_mplane	= gsc_m2m_s_fmt_mplane,
	.vidioc_reqbufs			= gsc_m2m_reqbufs,
	.vidioc_expbuf                  = gsc_m2m_expbuf,
	.vidioc_querybuf		= gsc_m2m_querybuf,
	.vidioc_qbuf			= gsc_m2m_qbuf,
	.vidioc_dqbuf			= gsc_m2m_dqbuf,
	.vidioc_streamon		= gsc_m2m_streamon,
	.vidioc_streamoff		= gsc_m2m_streamoff,
	.vidioc_g_selection		= gsc_m2m_g_selection,
	.vidioc_s_selection		= gsc_m2m_s_selection
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा gsc_ctx *ctx = priv;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &gsc_m2m_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->gsc_dev->lock;
	src_vq->dev = &ctx->gsc_dev->pdev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &gsc_m2m_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->gsc_dev->lock;
	dst_vq->dev = &ctx->gsc_dev->pdev->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक gsc_m2m_खोलो(काष्ठा file *file)
अणु
	काष्ठा gsc_dev *gsc = video_drvdata(file);
	काष्ठा gsc_ctx *ctx = शून्य;
	पूर्णांक ret;

	pr_debug("pid: %d, state: 0x%lx", task_pid_nr(current), gsc->state);

	अगर (mutex_lock_पूर्णांकerruptible(&gsc->lock))
		वापस -ERESTARTSYS;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	v4l2_fh_init(&ctx->fh, gsc->m2m.vfd);
	ret = gsc_ctrls_create(ctx);
	अगर (ret)
		जाओ error_fh;

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->gsc_dev = gsc;
	/* Default color क्रमmat */
	ctx->s_frame.fmt = get_क्रमmat(0);
	ctx->d_frame.fmt = get_क्रमmat(0);
	/* Setup the device context क्रम mem2mem mode. */
	ctx->state = GSC_CTX_M2M;
	ctx->flags = 0;
	ctx->in_path = GSC_DMA;
	ctx->out_path = GSC_DMA;

	ctx->m2m_ctx = v4l2_m2m_ctx_init(gsc->m2m.m2m_dev, ctx, queue_init);
	अगर (IS_ERR(ctx->m2m_ctx)) अणु
		pr_err("Failed to initialize m2m context");
		ret = PTR_ERR(ctx->m2m_ctx);
		जाओ error_ctrls;
	पूर्ण

	अगर (gsc->m2m.refcnt++ == 0)
		set_bit(ST_M2M_OPEN, &gsc->state);

	pr_debug("gsc m2m driver is opened, ctx(0x%p)", ctx);

	mutex_unlock(&gsc->lock);
	वापस 0;

error_ctrls:
	gsc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
unlock:
	mutex_unlock(&gsc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gsc_m2m_release(काष्ठा file *file)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;

	pr_debug("pid: %d, state: 0x%lx, refcnt= %d",
		task_pid_nr(current), gsc->state, gsc->m2m.refcnt);

	mutex_lock(&gsc->lock);

	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	gsc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);

	अगर (--gsc->m2m.refcnt <= 0)
		clear_bit(ST_M2M_OPEN, &gsc->state);
	kमुक्त(ctx);

	mutex_unlock(&gsc->lock);
	वापस 0;
पूर्ण

अटल __poll_t gsc_m2m_poll(काष्ठा file *file,
					काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	__poll_t ret;

	अगर (mutex_lock_पूर्णांकerruptible(&gsc->lock))
		वापस EPOLLERR;

	ret = v4l2_m2m_poll(file, ctx->m2m_ctx, रुको);
	mutex_unlock(&gsc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक gsc_m2m_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gsc_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&gsc->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_m2m_mmap(file, ctx->m2m_ctx, vma);
	mutex_unlock(&gsc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations gsc_m2m_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= gsc_m2m_खोलो,
	.release	= gsc_m2m_release,
	.poll		= gsc_m2m_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= gsc_m2m_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops gsc_m2m_ops = अणु
	.device_run	= gsc_m2m_device_run,
	.job_पात	= gsc_m2m_job_पात,
पूर्ण;

पूर्णांक gsc_रेजिस्टर_m2m_device(काष्ठा gsc_dev *gsc)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	अगर (!gsc)
		वापस -ENODEV;

	pdev = gsc->pdev;

	gsc->vdev.fops		= &gsc_m2m_fops;
	gsc->vdev.ioctl_ops	= &gsc_m2m_ioctl_ops;
	gsc->vdev.release	= video_device_release_empty;
	gsc->vdev.lock		= &gsc->lock;
	gsc->vdev.vfl_dir	= VFL_सूची_M2M;
	gsc->vdev.v4l2_dev	= &gsc->v4l2_dev;
	gsc->vdev.device_caps	= V4L2_CAP_STREAMING |
				  V4L2_CAP_VIDEO_M2M_MPLANE;
	snम_लिखो(gsc->vdev.name, माप(gsc->vdev.name), "%s.%d:m2m",
					GSC_MODULE_NAME, gsc->id);

	video_set_drvdata(&gsc->vdev, gsc);

	gsc->m2m.vfd = &gsc->vdev;
	gsc->m2m.m2m_dev = v4l2_m2m_init(&gsc_m2m_ops);
	अगर (IS_ERR(gsc->m2m.m2m_dev)) अणु
		dev_err(&pdev->dev, "failed to initialize v4l2-m2m device\n");
		वापस PTR_ERR(gsc->m2m.m2m_dev);
	पूर्ण

	ret = video_रेजिस्टर_device(&gsc->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			 "%s(): failed to register video device\n", __func__);
		जाओ err_m2m_release;
	पूर्ण

	pr_debug("gsc m2m driver registered as /dev/video%d", gsc->vdev.num);
	वापस 0;

err_m2m_release:
	v4l2_m2m_release(gsc->m2m.m2m_dev);

	वापस ret;
पूर्ण

व्योम gsc_unरेजिस्टर_m2m_device(काष्ठा gsc_dev *gsc)
अणु
	अगर (gsc) अणु
		v4l2_m2m_release(gsc->m2m.m2m_dev);
		video_unरेजिस्टर_device(&gsc->vdev);
	पूर्ण
पूर्ण
