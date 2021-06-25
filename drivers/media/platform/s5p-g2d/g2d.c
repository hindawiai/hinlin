<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung S5P G2D - 2D Graphics Accelerator Driver
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Kamil Debski, <k.debski@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "g2d.h"
#समावेश "g2d-regs.h"

#घोषणा fh2ctx(__fh) container_of(__fh, काष्ठा g2d_ctx, fh)

अटल काष्ठा g2d_fmt क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB32,
		.depth	= 32,
		.hw	= COLOR_MODE(ORDER_XRGB, MODE_XRGB_8888),
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB565X,
		.depth	= 16,
		.hw	= COLOR_MODE(ORDER_XRGB, MODE_RGB_565),
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB555X,
		.depth	= 16,
		.hw	= COLOR_MODE(ORDER_XRGB, MODE_XRGB_1555),
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB444,
		.depth	= 16,
		.hw	= COLOR_MODE(ORDER_XRGB, MODE_XRGB_4444),
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB24,
		.depth	= 24,
		.hw	= COLOR_MODE(ORDER_XRGB, MODE_PACKED_RGB_888),
	पूर्ण,
पूर्ण;
#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

अटल काष्ठा g2d_frame def_frame = अणु
	.width		= DEFAULT_WIDTH,
	.height		= DEFAULT_HEIGHT,
	.c_width	= DEFAULT_WIDTH,
	.c_height	= DEFAULT_HEIGHT,
	.o_width	= 0,
	.o_height	= 0,
	.fmt		= &क्रमmats[0],
	.right		= DEFAULT_WIDTH,
	.bottom		= DEFAULT_HEIGHT,
पूर्ण;

अटल काष्ठा g2d_fmt *find_fmt(काष्ठा v4l2_क्रमmat *f)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix.pixelक्रमmat)
			वापस &क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण


अटल काष्ठा g2d_frame *get_frame(काष्ठा g2d_ctx *ctx,
				   क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &ctx->in;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &ctx->out;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक g2d_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा g2d_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा g2d_frame *f = get_frame(ctx, vq->type);

	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	sizes[0] = f->size;
	*nplanes = 1;

	अगर (*nbuffers == 0)
		*nbuffers = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक g2d_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा g2d_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा g2d_frame *f = get_frame(ctx, vb->vb2_queue->type);

	अगर (IS_ERR(f))
		वापस PTR_ERR(f);
	vb2_set_plane_payload(vb, 0, f->size);
	वापस 0;
पूर्ण

अटल व्योम g2d_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा g2d_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल स्थिर काष्ठा vb2_ops g2d_qops = अणु
	.queue_setup	= g2d_queue_setup,
	.buf_prepare	= g2d_buf_prepare,
	.buf_queue	= g2d_buf_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
						काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा g2d_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR;
	src_vq->drv_priv = ctx;
	src_vq->ops = &g2d_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->mutex;
	src_vq->dev = ctx->dev->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &g2d_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->mutex;
	dst_vq->dev = ctx->dev->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक g2d_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा g2d_ctx *ctx = container_of(ctrl->handler, काष्ठा g2d_ctx,
								ctrl_handler);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->dev->ctrl_lock, flags);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_COLORFX:
		अगर (ctrl->val == V4L2_COLORFX_NEGATIVE)
			ctx->rop = ROP4_INVERT;
		अन्यथा
			ctx->rop = ROP4_COPY;
		अवरोध;

	हाल V4L2_CID_HFLIP:
		ctx->flip = ctx->ctrl_hflip->val | (ctx->ctrl_vflip->val << 1);
		अवरोध;

	पूर्ण
	spin_unlock_irqrestore(&ctx->dev->ctrl_lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops g2d_ctrl_ops = अणु
	.s_ctrl		= g2d_s_ctrl,
पूर्ण;

अटल पूर्णांक g2d_setup_ctrls(काष्ठा g2d_ctx *ctx)
अणु
	काष्ठा g2d_dev *dev = ctx->dev;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 3);

	ctx->ctrl_hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler, &g2d_ctrl_ops,
						V4L2_CID_HFLIP, 0, 1, 1, 0);

	ctx->ctrl_vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler, &g2d_ctrl_ops,
						V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std_menu(
		&ctx->ctrl_handler,
		&g2d_ctrl_ops,
		V4L2_CID_COLORFX,
		V4L2_COLORFX_NEGATIVE,
		~((1 << V4L2_COLORFX_NONE) | (1 << V4L2_COLORFX_NEGATIVE)),
		V4L2_COLORFX_NONE);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;
		v4l2_err(&dev->v4l2_dev, "g2d_setup_ctrls failed\n");
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		वापस err;
	पूर्ण

	v4l2_ctrl_cluster(2, &ctx->ctrl_hflip);

	वापस 0;
पूर्ण

अटल पूर्णांक g2d_खोलो(काष्ठा file *file)
अणु
	काष्ठा g2d_dev *dev = video_drvdata(file);
	काष्ठा g2d_ctx *ctx = शून्य;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->dev = dev;
	/* Set शेष क्रमmats */
	ctx->in		= def_frame;
	ctx->out	= def_frame;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex)) अणु
		kमुक्त(ctx);
		वापस -ERESTARTSYS;
	पूर्ण
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		mutex_unlock(&dev->mutex);
		kमुक्त(ctx);
		वापस ret;
	पूर्ण
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	g2d_setup_ctrls(ctx);

	/* Write the शेष values to the ctx काष्ठा */
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	mutex_unlock(&dev->mutex);

	v4l2_info(&dev->v4l2_dev, "instance opened\n");
	वापस 0;
पूर्ण

अटल पूर्णांक g2d_release(काष्ठा file *file)
अणु
	काष्ठा g2d_dev *dev = video_drvdata(file);
	काष्ठा g2d_ctx *ctx = fh2ctx(file->निजी_data);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	v4l2_info(&dev->v4l2_dev, "instance closed\n");
	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, G2D_NAME, माप(cap->driver));
	strscpy(cap->card, G2D_NAME, माप(cap->card));
	cap->bus_info[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[f->index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा vb2_queue *vq;
	काष्ठा g2d_frame *frm;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;
	frm = get_frame(ctx, f->type);
	अगर (IS_ERR(frm))
		वापस PTR_ERR(frm);

	f->fmt.pix.width		= frm->width;
	f->fmt.pix.height		= frm->height;
	f->fmt.pix.field		= V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat		= frm->fmt->fourcc;
	f->fmt.pix.bytesperline		= (frm->width * frm->fmt->depth) >> 3;
	f->fmt.pix.sizeimage		= frm->size;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा g2d_fmt *fmt;
	क्रमागत v4l2_field *field;

	fmt = find_fmt(f);
	अगर (!fmt)
		वापस -EINVAL;

	field = &f->fmt.pix.field;
	अगर (*field == V4L2_FIELD_ANY)
		*field = V4L2_FIELD_NONE;
	अन्यथा अगर (*field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	अगर (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	अगर (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	अगर (f->fmt.pix.width < 1)
		f->fmt.pix.width = 1;
	अगर (f->fmt.pix.height < 1)
		f->fmt.pix.height = 1;

	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा g2d_dev *dev = ctx->dev;
	काष्ठा vb2_queue *vq;
	काष्ठा g2d_frame *frm;
	काष्ठा g2d_fmt *fmt;
	पूर्णांक ret = 0;

	/* Adjust all values accordingly to the hardware capabilities
	 * and chosen क्रमmat. */
	ret = vidioc_try_fmt(file, prv, f);
	अगर (ret)
		वापस ret;
	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&dev->v4l2_dev, "queue (%d) bust\n", f->type);
		वापस -EBUSY;
	पूर्ण
	frm = get_frame(ctx, f->type);
	अगर (IS_ERR(frm))
		वापस PTR_ERR(frm);
	fmt = find_fmt(f);
	अगर (!fmt)
		वापस -EINVAL;
	frm->width	= f->fmt.pix.width;
	frm->height	= f->fmt.pix.height;
	frm->size	= f->fmt.pix.sizeimage;
	/* Reset crop settings */
	frm->o_width	= 0;
	frm->o_height	= 0;
	frm->c_width	= frm->width;
	frm->c_height	= frm->height;
	frm->right	= frm->width;
	frm->bottom	= frm->height;
	frm->fmt	= fmt;
	frm->stride	= f->fmt.pix.bytesperline;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *prv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा g2d_frame *f;

	f = get_frame(ctx, s->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

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
		s->r.left = f->o_height;
		s->r.top = f->o_width;
		s->r.width = f->c_width;
		s->r.height = f->c_height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = f->width;
		s->r.height = f->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_selection(काष्ठा file *file, व्योम *prv,
				स्थिर काष्ठा v4l2_selection *s)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा g2d_dev *dev = ctx->dev;
	काष्ठा g2d_frame *f;

	f = get_frame(ctx, s->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		अगर (s->target != V4L2_SEL_TGT_COMPOSE)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अगर (s->target != V4L2_SEL_TGT_CROP)
			वापस -EINVAL;
	पूर्ण

	अगर (s->r.top < 0 || s->r.left < 0) अणु
		v4l2_err(&dev->v4l2_dev,
			"doesn't support negative values for top & left\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *prv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा g2d_frame *f;
	पूर्णांक ret;

	ret = vidioc_try_selection(file, prv, s);
	अगर (ret)
		वापस ret;
	f = get_frame(ctx, s->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	f->c_width	= s->r.width;
	f->c_height	= s->r.height;
	f->o_width	= s->r.left;
	f->o_height	= s->r.top;
	f->bottom	= f->o_height + f->c_height;
	f->right	= f->o_width + f->c_width;
	वापस 0;
पूर्ण

अटल व्योम device_run(व्योम *prv)
अणु
	काष्ठा g2d_ctx *ctx = prv;
	काष्ठा g2d_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	अचिन्हित दीर्घ flags;
	u32 cmd = 0;

	dev->curr = ctx;

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	clk_enable(dev->gate);
	g2d_reset(dev);

	spin_lock_irqsave(&dev->ctrl_lock, flags);

	g2d_set_src_size(dev, &ctx->in);
	g2d_set_src_addr(dev, vb2_dma_contig_plane_dma_addr(&src->vb2_buf, 0));

	g2d_set_dst_size(dev, &ctx->out);
	g2d_set_dst_addr(dev, vb2_dma_contig_plane_dma_addr(&dst->vb2_buf, 0));

	g2d_set_rop4(dev, ctx->rop);
	g2d_set_flip(dev, ctx->flip);

	अगर (ctx->in.c_width != ctx->out.c_width ||
		ctx->in.c_height != ctx->out.c_height) अणु
		अगर (dev->variant->hw_rev == TYPE_G2D_3X)
			cmd |= CMD_V3_ENABLE_STRETCH;
		अन्यथा
			g2d_set_v41_stretch(dev, &ctx->in, &ctx->out);
	पूर्ण

	g2d_set_cmd(dev, cmd);
	g2d_start(dev);

	spin_unlock_irqrestore(&dev->ctrl_lock, flags);
पूर्ण

अटल irqवापस_t g2d_isr(पूर्णांक irq, व्योम *prv)
अणु
	काष्ठा g2d_dev *dev = prv;
	काष्ठा g2d_ctx *ctx = dev->curr;
	काष्ठा vb2_v4l2_buffer *src, *dst;

	g2d_clear_पूर्णांक(dev);
	clk_disable(dev->gate);

	BUG_ON(ctx == शून्य);

	src = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	BUG_ON(src == शून्य);
	BUG_ON(dst == शून्य);

	dst->समयcode = src->समयcode;
	dst->vb2_buf.बारtamp = src->vb2_buf.बारtamp;
	dst->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst->flags |=
		src->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	v4l2_m2m_buf_करोne(src, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_करोne(dst, VB2_BUF_STATE_DONE);
	v4l2_m2m_job_finish(dev->m2m_dev, ctx->fh.m2m_ctx);

	dev->curr = शून्य;
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations g2d_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= g2d_खोलो,
	.release	= g2d_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops g2d_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap		= vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap		= vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap		= vidioc_s_fmt,

	.vidioc_क्रमागत_fmt_vid_out	= vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out		= vidioc_g_fmt,
	.vidioc_try_fmt_vid_out		= vidioc_try_fmt,
	.vidioc_s_fmt_vid_out		= vidioc_s_fmt,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_g_selection		= vidioc_g_selection,
	.vidioc_s_selection		= vidioc_s_selection,
पूर्ण;

अटल स्थिर काष्ठा video_device g2d_videodev = अणु
	.name		= G2D_NAME,
	.fops		= &g2d_fops,
	.ioctl_ops	= &g2d_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release,
	.vfl_dir	= VFL_सूची_M2M,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops g2d_m2m_ops = अणु
	.device_run	= device_run,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_g2d_match[];

अटल पूर्णांक g2d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा g2d_dev *dev;
	काष्ठा video_device *vfd;
	काष्ठा resource *res;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret = 0;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	spin_lock_init(&dev->ctrl_lock);
	mutex_init(&dev->mutex);
	atomic_set(&dev->num_inst, 0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	dev->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->regs))
		वापस PTR_ERR(dev->regs);

	dev->clk = clk_get(&pdev->dev, "sclk_fimg2d");
	अगर (IS_ERR(dev->clk)) अणु
		dev_err(&pdev->dev, "failed to get g2d clock\n");
		वापस -ENXIO;
	पूर्ण

	ret = clk_prepare(dev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare g2d clock\n");
		जाओ put_clk;
	पूर्ण

	dev->gate = clk_get(&pdev->dev, "fimg2d");
	अगर (IS_ERR(dev->gate)) अणु
		dev_err(&pdev->dev, "failed to get g2d clock gate\n");
		ret = -ENXIO;
		जाओ unprep_clk;
	पूर्ण

	ret = clk_prepare(dev->gate);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare g2d clock gate\n");
		जाओ put_clk_gate;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to find IRQ\n");
		ret = -ENXIO;
		जाओ unprep_clk_gate;
	पूर्ण

	dev->irq = res->start;

	ret = devm_request_irq(&pdev->dev, dev->irq, g2d_isr,
						0, pdev->name, dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to install IRQ\n");
		जाओ unprep_clk_gate;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		जाओ unprep_clk_gate;
	vfd = video_device_alloc();
	अगर (!vfd) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ unreg_v4l2_dev;
	पूर्ण
	*vfd = g2d_videodev;
	set_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags);
	vfd->lock = &dev->mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;

	platक्रमm_set_drvdata(pdev, dev);
	dev->m2m_dev = v4l2_m2m_init(&g2d_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		जाओ rel_vdev;
	पूर्ण

	def_frame.stride = (def_frame.width * def_frame.fmt->depth) >> 3;

	of_id = of_match_node(exynos_g2d_match, pdev->dev.of_node);
	अगर (!of_id) अणु
		ret = -ENODEV;
		जाओ मुक्त_m2m;
	पूर्ण
	dev->variant = (काष्ठा g2d_variant *)of_id->data;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		जाओ मुक्त_m2m;
	पूर्ण
	video_set_drvdata(vfd, dev);
	dev->vfd = vfd;
	v4l2_info(&dev->v4l2_dev, "device registered as /dev/video%d\n",
		  vfd->num);

	वापस 0;

मुक्त_m2m:
	v4l2_m2m_release(dev->m2m_dev);
rel_vdev:
	video_device_release(vfd);
unreg_v4l2_dev:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
unprep_clk_gate:
	clk_unprepare(dev->gate);
put_clk_gate:
	clk_put(dev->gate);
unprep_clk:
	clk_unprepare(dev->clk);
put_clk:
	clk_put(dev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक g2d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा g2d_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&dev->v4l2_dev, "Removing " G2D_NAME);
	v4l2_m2m_release(dev->m2m_dev);
	video_unरेजिस्टर_device(dev->vfd);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	clk_unprepare(dev->gate);
	clk_put(dev->gate);
	clk_unprepare(dev->clk);
	clk_put(dev->clk);
	वापस 0;
पूर्ण

अटल काष्ठा g2d_variant g2d_drvdata_v3x = अणु
	.hw_rev = TYPE_G2D_3X, /* Revision 3.0 क्रम S5PV210 and Exynos4210 */
पूर्ण;

अटल काष्ठा g2d_variant g2d_drvdata_v4x = अणु
	.hw_rev = TYPE_G2D_4X, /* Revision 4.1 क्रम Exynos4X12 and Exynos5 */
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_g2d_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-g2d",
		.data = &g2d_drvdata_v3x,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-g2d",
		.data = &g2d_drvdata_v4x,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_g2d_match);

अटल काष्ठा platक्रमm_driver g2d_pdrv = अणु
	.probe		= g2d_probe,
	.हटाओ		= g2d_हटाओ,
	.driver		= अणु
		.name = G2D_NAME,
		.of_match_table = exynos_g2d_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(g2d_pdrv);

MODULE_AUTHOR("Kamil Debski <k.debski@samsung.com>");
MODULE_DESCRIPTION("S5P G2D 2d graphics accelerator driver");
MODULE_LICENSE("GPL");
