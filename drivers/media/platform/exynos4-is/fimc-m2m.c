<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung S5P/EXYNOS4 SoC series FIMC (video postprocessor) driver
 *
 * Copyright (C) 2012 - 2013 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "common.h"
#समावेश "fimc-core.h"
#समावेश "fimc-reg.h"
#समावेश "media-dev.h"

अटल अचिन्हित पूर्णांक get_m2m_fmt_flags(अचिन्हित पूर्णांक stream_type)
अणु
	अगर (stream_type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस FMT_FLAGS_M2M_IN;
	अन्यथा
		वापस FMT_FLAGS_M2M_OUT;
पूर्ण

व्योम fimc_m2m_job_finish(काष्ठा fimc_ctx *ctx, पूर्णांक vb_state)
अणु
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	अगर (!ctx || !ctx->fh.m2m_ctx)
		वापस;

	src_vb = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	अगर (src_vb)
		v4l2_m2m_buf_करोne(src_vb, vb_state);
	अगर (dst_vb)
		v4l2_m2m_buf_करोne(dst_vb, vb_state);
	अगर (src_vb && dst_vb)
		v4l2_m2m_job_finish(ctx->fimc_dev->m2m.m2m_dev,
				    ctx->fh.m2m_ctx);
पूर्ण

/* Complete the transaction which has been scheduled क्रम execution. */
अटल व्योम fimc_m2m_shutकरोwn(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;

	अगर (!fimc_m2m_pending(fimc))
		वापस;

	fimc_ctx_state_set(FIMC_CTX_SHUT, ctx);

	रुको_event_समयout(fimc->irq_queue,
			!fimc_ctx_state_is_set(FIMC_CTX_SHUT, ctx),
			FIMC_SHUTDOWN_TIMEOUT);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा fimc_ctx *ctx = q->drv_priv;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&ctx->fimc_dev->pdev->dev);
	वापस ret > 0 ? 0 : ret;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा fimc_ctx *ctx = q->drv_priv;


	fimc_m2m_shutकरोwn(ctx);
	fimc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);
	pm_runसमय_put(&ctx->fimc_dev->pdev->dev);
पूर्ण

अटल व्योम fimc_device_run(व्योम *priv)
अणु
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	काष्ठा fimc_ctx *ctx = priv;
	काष्ठा fimc_frame *sf, *df;
	काष्ठा fimc_dev *fimc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (WARN(!ctx, "Null context\n"))
		वापस;

	fimc = ctx->fimc_dev;
	spin_lock_irqsave(&fimc->slock, flags);

	set_bit(ST_M2M_PEND, &fimc->state);
	sf = &ctx->s_frame;
	df = &ctx->d_frame;

	अगर (ctx->state & FIMC_PARAMS) अणु
		/* Prepare the DMA offsets क्रम scaler */
		fimc_prepare_dma_offset(ctx, sf);
		fimc_prepare_dma_offset(ctx, df);
	पूर्ण

	src_vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	ret = fimc_prepare_addr(ctx, &src_vb->vb2_buf, sf, &sf->addr);
	अगर (ret)
		जाओ dma_unlock;

	dst_vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	ret = fimc_prepare_addr(ctx, &dst_vb->vb2_buf, df, &df->addr);
	अगर (ret)
		जाओ dma_unlock;

	dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;
	dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vb->flags |=
		src_vb->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	/* Reconfigure hardware अगर the context has changed. */
	अगर (fimc->m2m.ctx != ctx) अणु
		ctx->state |= FIMC_PARAMS;
		fimc->m2m.ctx = ctx;
	पूर्ण

	अगर (ctx->state & FIMC_PARAMS) अणु
		fimc_set_yuv_order(ctx);
		fimc_hw_set_input_path(ctx);
		fimc_hw_set_in_dma(ctx);
		ret = fimc_set_scaler_info(ctx);
		अगर (ret)
			जाओ dma_unlock;
		fimc_hw_set_prescaler(ctx);
		fimc_hw_set_मुख्यscaler(ctx);
		fimc_hw_set_target_क्रमmat(ctx);
		fimc_hw_set_rotation(ctx);
		fimc_hw_set_effect(ctx);
		fimc_hw_set_out_dma(ctx);
		अगर (fimc->drv_data->alpha_color)
			fimc_hw_set_rgb_alpha(ctx);
		fimc_hw_set_output_path(ctx);
	पूर्ण
	fimc_hw_set_input_addr(fimc, &sf->addr);
	fimc_hw_set_output_addr(fimc, &df->addr, -1);

	fimc_activate_capture(ctx);
	ctx->state &= (FIMC_CTX_M2M | FIMC_CTX_CAP);
	fimc_hw_activate_input_dma(fimc, true);

dma_unlock:
	spin_unlock_irqrestore(&fimc->slock, flags);
पूर्ण

अटल व्योम fimc_job_पात(व्योम *priv)
अणु
	fimc_m2m_shutकरोwn(priv);
पूर्ण

अटल पूर्णांक fimc_queue_setup(काष्ठा vb2_queue *vq,
			    अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा fimc_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा fimc_frame *f;
	पूर्णांक i;

	f = ctx_get_frame(ctx, vq->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);
	/*
	 * Return number of non-contiguous planes (plane buffers)
	 * depending on the configured color क्रमmat.
	 */
	अगर (!f->fmt)
		वापस -EINVAL;

	*num_planes = f->fmt->memplanes;
	क्रम (i = 0; i < f->fmt->memplanes; i++)
		sizes[i] = f->payload[i];
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा fimc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा fimc_frame *frame;
	पूर्णांक i;

	frame = ctx_get_frame(ctx, vb->vb2_queue->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	क्रम (i = 0; i < frame->fmt->memplanes; i++)
		vb2_set_plane_payload(vb, i, frame->payload[i]);

	वापस 0;
पूर्ण

अटल व्योम fimc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा fimc_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल स्थिर काष्ठा vb2_ops fimc_qops = अणु
	.queue_setup	 = fimc_queue_setup,
	.buf_prepare	 = fimc_buf_prepare,
	.buf_queue	 = fimc_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.stop_streaming	 = stop_streaming,
	.start_streaming = start_streaming,
पूर्ण;

/*
 * V4L2 ioctl handlers
 */
अटल पूर्णांक fimc_m2m_querycap(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);

	__fimc_vidioc_querycap(&fimc->pdev->dev, cap);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा fimc_fmt *fmt;

	fmt = fimc_find_क्रमmat(शून्य, शून्य, get_m2m_fmt_flags(f->type),
			       f->index);
	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा fimc_frame *frame = ctx_get_frame(ctx, f->type);

	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	__fimc_get_क्रमmat(frame, f);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_try_fmt_mplane(काष्ठा fimc_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	स्थिर काष्ठा fimc_variant *variant = fimc->variant;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा fimc_fmt *fmt;
	u32 max_w, mod_x, mod_y;

	अगर (!IS_M2M(f->type))
		वापस -EINVAL;

	fmt = fimc_find_क्रमmat(&pix->pixelक्रमmat, शून्य,
			       get_m2m_fmt_flags(f->type), 0);
	अगर (WARN(fmt == शून्य, "Pixel format lookup failed"))
		वापस -EINVAL;

	अगर (pix->field == V4L2_FIELD_ANY)
		pix->field = V4L2_FIELD_NONE;
	अन्यथा अगर (pix->field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		max_w = variant->pix_limit->scaler_dis_w;
		mod_x = ffs(variant->min_inp_pixsize) - 1;
	पूर्ण अन्यथा अणु
		max_w = variant->pix_limit->out_rot_dis_w;
		mod_x = ffs(variant->min_out_pixsize) - 1;
	पूर्ण

	अगर (tiled_fmt(fmt)) अणु
		mod_x = 6; /* 64 x 32 pixels tile */
		mod_y = 5;
	पूर्ण अन्यथा अणु
		अगर (variant->min_vsize_align == 1)
			mod_y = fimc_fmt_is_rgb(fmt->color) ? 0 : 1;
		अन्यथा
			mod_y = ffs(variant->min_vsize_align) - 1;
	पूर्ण

	v4l_bound_align_image(&pix->width, 16, max_w, mod_x,
		&pix->height, 8, variant->pix_limit->scaler_dis_w, mod_y, 0);

	fimc_adjust_mplane_क्रमmat(fmt, pix->width, pix->height, &f->fmt.pix_mp);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(fh);
	वापस fimc_try_fmt_mplane(ctx, f);
पूर्ण

अटल व्योम __set_frame_क्रमmat(काष्ठा fimc_frame *frame, काष्ठा fimc_fmt *fmt,
			       काष्ठा v4l2_pix_क्रमmat_mplane *pixm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fmt->memplanes; i++) अणु
		frame->bytesperline[i] = pixm->plane_fmt[i].bytesperline;
		frame->payload[i] = pixm->plane_fmt[i].sizeimage;
	पूर्ण

	frame->f_width = pixm->width;
	frame->f_height	= pixm->height;
	frame->o_width = pixm->width;
	frame->o_height = pixm->height;
	frame->width = pixm->width;
	frame->height = pixm->height;
	frame->offs_h = 0;
	frame->offs_v = 0;
	frame->fmt = fmt;
पूर्ण

अटल पूर्णांक fimc_m2m_s_fmt_mplane(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_fmt *fmt;
	काष्ठा vb2_queue *vq;
	काष्ठा fimc_frame *frame;
	पूर्णांक ret;

	ret = fimc_try_fmt_mplane(ctx, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&fimc->m2m.vfd, "queue (%d) busy\n", f->type);
		वापस -EBUSY;
	पूर्ण

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		frame = &ctx->s_frame;
	अन्यथा
		frame = &ctx->d_frame;

	fmt = fimc_find_क्रमmat(&f->fmt.pix_mp.pixelक्रमmat, शून्य,
			       get_m2m_fmt_flags(f->type), 0);
	अगर (!fmt)
		वापस -EINVAL;

	__set_frame_क्रमmat(frame, fmt, &f->fmt.pix_mp);

	/* Update RGB Alpha control state and value range */
	fimc_alpha_ctrl_update(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_g_selection(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा fimc_frame *frame;

	frame = ctx_get_frame(ctx, s->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_COMPOSE:
		s->r.left = frame->offs_h;
		s->r.top = frame->offs_v;
		s->r.width = frame->width;
		s->r.height = frame->height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frame->o_width;
		s->r.height = frame->o_height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_try_selection(काष्ठा fimc_ctx *ctx,
				  काष्ठा v4l2_selection *s)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_frame *f;
	u32 min_size, halign, depth = 0;
	पूर्णांक i;

	अगर (s->r.top < 0 || s->r.left < 0) अणु
		v4l2_err(&fimc->m2m.vfd,
			"doesn't support negative values for top & left\n");
		वापस -EINVAL;
	पूर्ण
	अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		f = &ctx->d_frame;
		अगर (s->target != V4L2_SEL_TGT_COMPOSE)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		f = &ctx->s_frame;
		अगर (s->target != V4L2_SEL_TGT_CROP)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	min_size = (f == &ctx->s_frame) ?
		fimc->variant->min_inp_pixsize : fimc->variant->min_out_pixsize;

	/* Get pixel alignment स्थिरraपूर्णांकs. */
	अगर (fimc->variant->min_vsize_align == 1)
		halign = fimc_fmt_is_rgb(f->fmt->color) ? 0 : 1;
	अन्यथा
		halign = ffs(fimc->variant->min_vsize_align) - 1;

	क्रम (i = 0; i < f->fmt->memplanes; i++)
		depth += f->fmt->depth[i];

	v4l_bound_align_image(&s->r.width, min_size, f->o_width,
			      ffs(min_size) - 1,
			      &s->r.height, min_size, f->o_height,
			      halign, 64/(ALIGN(depth, 8)));

	/* adjust left/top अगर cropping rectangle is out of bounds */
	अगर (s->r.left + s->r.width > f->o_width)
		s->r.left = f->o_width - s->r.width;
	अगर (s->r.top + s->r.height > f->o_height)
		s->r.top = f->o_height - s->r.height;

	s->r.left = round_करोwn(s->r.left, min_size);
	s->r.top  = round_करोwn(s->r.top, fimc->variant->hor_offs_align);

	dbg("l:%d, t:%d, w:%d, h:%d, f_w: %d, f_h: %d",
	    s->r.left, s->r.top, s->r.width, s->r.height,
	    f->f_width, f->f_height);

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_s_selection(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_selection *s)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(fh);
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा fimc_frame *f;
	पूर्णांक ret;

	ret = fimc_m2m_try_selection(ctx, s);
	अगर (ret)
		वापस ret;

	f = (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) ?
		&ctx->s_frame : &ctx->d_frame;

	/* Check to see अगर scaling ratio is within supported range */
	अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		ret = fimc_check_scaler_ratio(ctx, s->r.width,
				s->r.height, ctx->d_frame.width,
				ctx->d_frame.height, ctx->rotation);
	पूर्ण अन्यथा अणु
		ret = fimc_check_scaler_ratio(ctx, ctx->s_frame.width,
				ctx->s_frame.height, s->r.width,
				s->r.height, ctx->rotation);
	पूर्ण
	अगर (ret) अणु
		v4l2_err(&fimc->m2m.vfd, "Out of scaler range\n");
		वापस -EINVAL;
	पूर्ण

	f->offs_h = s->r.left;
	f->offs_v = s->r.top;
	f->width  = s->r.width;
	f->height = s->r.height;

	fimc_ctx_state_set(FIMC_PARAMS, ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops fimc_m2m_ioctl_ops = अणु
	.vidioc_querycap		= fimc_m2m_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= fimc_m2m_क्रमागत_fmt,
	.vidioc_क्रमागत_fmt_vid_out	= fimc_m2m_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap_mplane	= fimc_m2m_g_fmt_mplane,
	.vidioc_g_fmt_vid_out_mplane	= fimc_m2m_g_fmt_mplane,
	.vidioc_try_fmt_vid_cap_mplane	= fimc_m2m_try_fmt_mplane,
	.vidioc_try_fmt_vid_out_mplane	= fimc_m2m_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= fimc_m2m_s_fmt_mplane,
	.vidioc_s_fmt_vid_out_mplane	= fimc_m2m_s_fmt_mplane,
	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,
	.vidioc_g_selection		= fimc_m2m_g_selection,
	.vidioc_s_selection		= fimc_m2m_s_selection,

पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा fimc_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &fimc_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->fimc_dev->lock;
	src_vq->dev = &ctx->fimc_dev->pdev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &fimc_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->fimc_dev->lock;
	dst_vq->dev = &ctx->fimc_dev->pdev->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक fimc_m2m_set_शेष_क्रमmat(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane pixm = अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB32,
		.width		= 800,
		.height		= 600,
		.plane_fmt[0]	= अणु
			.bytesperline = 800 * 4,
			.sizeimage = 800 * 4 * 600,
		पूर्ण,
	पूर्ण;
	काष्ठा fimc_fmt *fmt;

	fmt = fimc_find_क्रमmat(&pixm.pixelक्रमmat, शून्य, FMT_FLAGS_M2M, 0);
	अगर (!fmt)
		वापस -EINVAL;

	__set_frame_क्रमmat(&ctx->s_frame, fmt, &pixm);
	__set_frame_क्रमmat(&ctx->d_frame, fmt, &pixm);

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_m2m_खोलो(काष्ठा file *file)
अणु
	काष्ठा fimc_dev *fimc = video_drvdata(file);
	काष्ठा fimc_ctx *ctx;
	पूर्णांक ret = -EBUSY;

	pr_debug("pid: %d, state: %#lx\n", task_pid_nr(current), fimc->state);

	अगर (mutex_lock_पूर्णांकerruptible(&fimc->lock))
		वापस -ERESTARTSYS;
	/*
	 * Don't allow simultaneous खोलो() of the mem-to-mem and the
	 * capture video node that beदीर्घ to same FIMC IP instance.
	 */
	अगर (test_bit(ST_CAPT_BUSY, &fimc->state))
		जाओ unlock;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	v4l2_fh_init(&ctx->fh, &fimc->m2m.vfd);
	ctx->fimc_dev = fimc;

	/* Default color क्रमmat */
	ctx->s_frame.fmt = fimc_get_क्रमmat(0);
	ctx->d_frame.fmt = fimc_get_क्रमmat(0);

	ret = fimc_ctrls_create(ctx);
	अगर (ret)
		जाओ error_fh;

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrls.handler;
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	/* Setup the device context क्रम memory-to-memory mode */
	ctx->state = FIMC_CTX_M2M;
	ctx->flags = 0;
	ctx->in_path = FIMC_IO_DMA;
	ctx->out_path = FIMC_IO_DMA;
	ctx->scaler.enabled = 1;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(fimc->m2m.m2m_dev, ctx, queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ error_c;
	पूर्ण

	अगर (fimc->m2m.refcnt++ == 0)
		set_bit(ST_M2M_RUN, &fimc->state);

	ret = fimc_m2m_set_शेष_क्रमmat(ctx);
	अगर (ret < 0)
		जाओ error_m2m_ctx;

	mutex_unlock(&fimc->lock);
	वापस 0;

error_m2m_ctx:
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
error_c:
	fimc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
unlock:
	mutex_unlock(&fimc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_m2m_release(काष्ठा file *file)
अणु
	काष्ठा fimc_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;

	dbg("pid: %d, state: 0x%lx, refcnt= %d",
		task_pid_nr(current), fimc->state, fimc->m2m.refcnt);

	mutex_lock(&fimc->lock);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	fimc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);

	अगर (--fimc->m2m.refcnt <= 0)
		clear_bit(ST_M2M_RUN, &fimc->state);
	kमुक्त(ctx);

	mutex_unlock(&fimc->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations fimc_m2m_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fimc_m2m_खोलो,
	.release	= fimc_m2m_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= fimc_device_run,
	.job_पात	= fimc_job_पात,
पूर्ण;

पूर्णांक fimc_रेजिस्टर_m2m_device(काष्ठा fimc_dev *fimc,
			     काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा video_device *vfd = &fimc->m2m.vfd;
	पूर्णांक ret;

	fimc->v4l2_dev = v4l2_dev;

	स_रखो(vfd, 0, माप(*vfd));
	vfd->fops = &fimc_m2m_fops;
	vfd->ioctl_ops = &fimc_m2m_ioctl_ops;
	vfd->v4l2_dev = v4l2_dev;
	vfd->minor = -1;
	vfd->release = video_device_release_empty;
	vfd->lock = &fimc->lock;
	vfd->vfl_dir = VFL_सूची_M2M;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;
	set_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags);

	snम_लिखो(vfd->name, माप(vfd->name), "fimc.%d.m2m", fimc->id);
	video_set_drvdata(vfd, fimc);

	fimc->m2m.m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(fimc->m2m.m2m_dev)) अणु
		v4l2_err(v4l2_dev, "failed to initialize v4l2-m2m device\n");
		वापस PTR_ERR(fimc->m2m.m2m_dev);
	पूर्ण

	ret = media_entity_pads_init(&vfd->entity, 0, शून्य);
	अगर (ret)
		जाओ err_me;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ err_vd;

	v4l2_info(v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	वापस 0;

err_vd:
	media_entity_cleanup(&vfd->entity);
err_me:
	v4l2_m2m_release(fimc->m2m.m2m_dev);
	वापस ret;
पूर्ण

व्योम fimc_unरेजिस्टर_m2m_device(काष्ठा fimc_dev *fimc)
अणु
	अगर (!fimc)
		वापस;

	अगर (fimc->m2m.m2m_dev)
		v4l2_m2m_release(fimc->m2m.m2m_dev);

	अगर (video_is_रेजिस्टरed(&fimc->m2m.vfd)) अणु
		video_unरेजिस्टर_device(&fimc->m2m.vfd);
		media_entity_cleanup(&fimc->m2m.vfd.entity);
	पूर्ण
पूर्ण
