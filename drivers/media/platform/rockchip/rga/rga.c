<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Jacob Chen <jacob-chen@iotwrt.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "rga-hw.h"
#समावेश "rga.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

अटल व्योम device_run(व्योम *prv)
अणु
	काष्ठा rga_ctx *ctx = prv;
	काष्ठा rockchip_rga *rga = ctx->rga;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rga->ctrl_lock, flags);

	rga->curr = ctx;

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	rga_buf_map(&src->vb2_buf);
	rga_buf_map(&dst->vb2_buf);

	rga_hw_start(rga);

	spin_unlock_irqrestore(&rga->ctrl_lock, flags);
पूर्ण

अटल irqवापस_t rga_isr(पूर्णांक irq, व्योम *prv)
अणु
	काष्ठा rockchip_rga *rga = prv;
	पूर्णांक पूर्णांकr;

	पूर्णांकr = rga_पढ़ो(rga, RGA_INT) & 0xf;

	rga_mod(rga, RGA_INT, पूर्णांकr << 4, 0xf << 4);

	अगर (पूर्णांकr & 0x04) अणु
		काष्ठा vb2_v4l2_buffer *src, *dst;
		काष्ठा rga_ctx *ctx = rga->curr;

		WARN_ON(!ctx);

		rga->curr = शून्य;

		src = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		dst = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		WARN_ON(!src);
		WARN_ON(!dst);

		dst->समयcode = src->समयcode;
		dst->vb2_buf.बारtamp = src->vb2_buf.बारtamp;
		dst->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst->flags |= src->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_करोne(src, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst, VB2_BUF_STATE_DONE);
		v4l2_m2m_job_finish(rga->m2m_dev, ctx->fh.m2m_ctx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops rga_m2m_ops = अणु
	.device_run = device_run,
पूर्ण;

अटल पूर्णांक
queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा rga_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &rga_qops;
	src_vq->mem_ops = &vb2_dma_sg_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->rga->mutex;
	src_vq->dev = ctx->rga->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &rga_qops;
	dst_vq->mem_ops = &vb2_dma_sg_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->rga->mutex;
	dst_vq->dev = ctx->rga->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक rga_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा rga_ctx *ctx = container_of(ctrl->handler, काष्ठा rga_ctx,
					   ctrl_handler);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->rga->ctrl_lock, flags);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_ROTATE:
		ctx->rotate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_BG_COLOR:
		ctx->fill_color = ctrl->val;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ctx->rga->ctrl_lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rga_ctrl_ops = अणु
	.s_ctrl = rga_s_ctrl,
पूर्ण;

अटल पूर्णांक rga_setup_ctrls(काष्ठा rga_ctx *ctx)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 4);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rga_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rga_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rga_ctrl_ops,
			  V4L2_CID_ROTATE, 0, 270, 90, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rga_ctrl_ops,
			  V4L2_CID_BG_COLOR, 0, 0xffffffff, 1, 0);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		v4l2_err(&rga->v4l2_dev, "%s failed\n", __func__);
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rga_fmt क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_ARGB32,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_ABGR8888,
		.depth = 32,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_XRGB32,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_XBGR8888,
		.depth = 32,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_ABGR32,
		.color_swap = RGA_COLOR_ALPHA_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_ABGR8888,
		.depth = 32,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_XBGR32,
		.color_swap = RGA_COLOR_ALPHA_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_XBGR8888,
		.depth = 32,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_RGB24,
		.color_swap = RGA_COLOR_NONE_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_RGB888,
		.depth = 24,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_BGR24,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_RGB888,
		.depth = 24,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_ARGB444,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_ABGR4444,
		.depth = 16,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_ARGB555,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_ABGR1555,
		.depth = 16,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.color_swap = RGA_COLOR_RB_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_BGR565,
		.depth = 16,
		.uv_factor = 1,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.color_swap = RGA_COLOR_UV_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV420SP,
		.depth = 12,
		.uv_factor = 4,
		.y_भाग = 2,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.color_swap = RGA_COLOR_UV_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV422SP,
		.depth = 16,
		.uv_factor = 2,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.color_swap = RGA_COLOR_NONE_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV420SP,
		.depth = 12,
		.uv_factor = 4,
		.y_भाग = 2,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.color_swap = RGA_COLOR_NONE_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV422SP,
		.depth = 16,
		.uv_factor = 2,
		.y_भाग = 1,
		.x_भाग = 1,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YUV420,
		.color_swap = RGA_COLOR_NONE_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV420P,
		.depth = 12,
		.uv_factor = 4,
		.y_भाग = 2,
		.x_भाग = 2,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.color_swap = RGA_COLOR_NONE_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV422P,
		.depth = 16,
		.uv_factor = 2,
		.y_भाग = 1,
		.x_भाग = 2,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YVU420,
		.color_swap = RGA_COLOR_UV_SWAP,
		.hw_क्रमmat = RGA_COLOR_FMT_YUV420P,
		.depth = 12,
		.uv_factor = 4,
		.y_भाग = 2,
		.x_भाग = 2,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

अटल काष्ठा rga_fmt *rga_fmt_find(काष्ठा v4l2_क्रमmat *f)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix.pixelक्रमmat)
			वापस &क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा rga_frame def_frame = अणु
	.width = DEFAULT_WIDTH,
	.height = DEFAULT_HEIGHT,
	.colorspace = V4L2_COLORSPACE_DEFAULT,
	.crop.left = 0,
	.crop.top = 0,
	.crop.width = DEFAULT_WIDTH,
	.crop.height = DEFAULT_HEIGHT,
	.fmt = &क्रमmats[0],
पूर्ण;

काष्ठा rga_frame *rga_get_frame(काष्ठा rga_ctx *ctx, क्रमागत v4l2_buf_type type)
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

अटल पूर्णांक rga_खोलो(काष्ठा file *file)
अणु
	काष्ठा rockchip_rga *rga = video_drvdata(file);
	काष्ठा rga_ctx *ctx = शून्य;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->rga = rga;
	/* Set शेष क्रमmats */
	ctx->in = def_frame;
	ctx->out = def_frame;

	अगर (mutex_lock_पूर्णांकerruptible(&rga->mutex)) अणु
		kमुक्त(ctx);
		वापस -ERESTARTSYS;
	पूर्ण
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(rga->m2m_dev, ctx, &queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		mutex_unlock(&rga->mutex);
		kमुक्त(ctx);
		वापस ret;
	पूर्ण
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	rga_setup_ctrls(ctx);

	/* Write the शेष values to the ctx काष्ठा */
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	mutex_unlock(&rga->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक rga_release(काष्ठा file *file)
अणु
	काष्ठा rga_ctx *ctx =
		container_of(file->निजी_data, काष्ठा rga_ctx, fh);
	काष्ठा rockchip_rga *rga = ctx->rga;

	mutex_lock(&rga->mutex);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);

	mutex_unlock(&rga->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations rga_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = rga_खोलो,
	.release = rga_release,
	.poll = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक
vidioc_querycap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, RGA_NAME, माप(cap->driver));
	strscpy(cap->card, "rockchip-rga", माप(cap->card));
	strscpy(cap->bus_info, "platform:rga", माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा rga_fmt *fmt;

	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;

	fmt = &क्रमmats[f->index];
	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rga_ctx *ctx = prv;
	काष्ठा vb2_queue *vq;
	काष्ठा rga_frame *frm;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;
	frm = rga_get_frame(ctx, f->type);
	अगर (IS_ERR(frm))
		वापस PTR_ERR(frm);

	f->fmt.pix.width = frm->width;
	f->fmt.pix.height = frm->height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat = frm->fmt->fourcc;
	f->fmt.pix.bytesperline = frm->stride;
	f->fmt.pix.sizeimage = frm->size;
	f->fmt.pix.colorspace = frm->colorspace;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rga_fmt *fmt;

	fmt = rga_fmt_find(f);
	अगर (!fmt) अणु
		fmt = &क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण

	f->fmt.pix.field = V4L2_FIELD_NONE;

	अगर (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	अगर (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	अगर (f->fmt.pix.width < MIN_WIDTH)
		f->fmt.pix.width = MIN_WIDTH;
	अगर (f->fmt.pix.height < MIN_HEIGHT)
		f->fmt.pix.height = MIN_HEIGHT;

	अगर (fmt->hw_क्रमmat >= RGA_COLOR_FMT_YUV422SP)
		f->fmt.pix.bytesperline = f->fmt.pix.width;
	अन्यथा
		f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;

	f->fmt.pix.sizeimage =
		f->fmt.pix.height * (f->fmt.pix.width * fmt->depth) >> 3;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा file *file, व्योम *prv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rga_ctx *ctx = prv;
	काष्ठा rockchip_rga *rga = ctx->rga;
	काष्ठा vb2_queue *vq;
	काष्ठा rga_frame *frm;
	काष्ठा rga_fmt *fmt;
	पूर्णांक ret = 0;

	/* Adjust all values accordingly to the hardware capabilities
	 * and chosen क्रमmat.
	 */
	ret = vidioc_try_fmt(file, prv, f);
	अगर (ret)
		वापस ret;
	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&rga->v4l2_dev, "queue (%d) bust\n", f->type);
		वापस -EBUSY;
	पूर्ण
	frm = rga_get_frame(ctx, f->type);
	अगर (IS_ERR(frm))
		वापस PTR_ERR(frm);
	fmt = rga_fmt_find(f);
	अगर (!fmt)
		वापस -EINVAL;
	frm->width = f->fmt.pix.width;
	frm->height = f->fmt.pix.height;
	frm->size = f->fmt.pix.sizeimage;
	frm->fmt = fmt;
	frm->stride = f->fmt.pix.bytesperline;
	frm->colorspace = f->fmt.pix.colorspace;

	/* Reset crop settings */
	frm->crop.left = 0;
	frm->crop.top = 0;
	frm->crop.width = frm->width;
	frm->crop.height = frm->height;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *prv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा rga_ctx *ctx = prv;
	काष्ठा rga_frame *f;
	bool use_frame = false;

	f = rga_get_frame(ctx, s->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		use_frame = true;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		use_frame = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (use_frame) अणु
		s->r = f->crop;
	पूर्ण अन्यथा अणु
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = f->width;
		s->r.height = f->height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *prv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा rga_ctx *ctx = prv;
	काष्ठा rockchip_rga *rga = ctx->rga;
	काष्ठा rga_frame *f;
	पूर्णांक ret = 0;

	f = rga_get_frame(ctx, s->type);
	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		/*
		 * COMPOSE target is only valid क्रम capture buffer type, वापस
		 * error क्रम output buffer type
		 */
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		/*
		 * CROP target is only valid क्रम output buffer type, वापस
		 * error क्रम capture buffer type
		 */
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	/*
	 * bound and शेष crop/compose tarमाला_लो are invalid tarमाला_लो to
	 * try/set
	 */
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (s->r.top < 0 || s->r.left < 0) अणु
		v4l2_dbg(debug, 1, &rga->v4l2_dev,
			 "doesn't support negative values for top & left.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (s->r.left + s->r.width > f->width ||
	    s->r.top + s->r.height > f->height ||
	    s->r.width < MIN_WIDTH || s->r.height < MIN_HEIGHT) अणु
		v4l2_dbg(debug, 1, &rga->v4l2_dev, "unsupported crop value.\n");
		वापस -EINVAL;
	पूर्ण

	f->crop = s->r;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rga_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out = vidioc_g_fmt,
	.vidioc_try_fmt_vid_out = vidioc_try_fmt,
	.vidioc_s_fmt_vid_out = vidioc_s_fmt,

	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf = v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,

	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,

	.vidioc_streamon = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,

	.vidioc_g_selection = vidioc_g_selection,
	.vidioc_s_selection = vidioc_s_selection,
पूर्ण;

अटल स्थिर काष्ठा video_device rga_videodev = अणु
	.name = "rockchip-rga",
	.fops = &rga_fops,
	.ioctl_ops = &rga_ioctl_ops,
	.minor = -1,
	.release = video_device_release,
	.vfl_dir = VFL_सूची_M2M,
	.device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल पूर्णांक rga_enable_घड़ीs(काष्ठा rockchip_rga *rga)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(rga->sclk);
	अगर (ret) अणु
		dev_err(rga->dev, "Cannot enable rga sclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(rga->aclk);
	अगर (ret) अणु
		dev_err(rga->dev, "Cannot enable rga aclk: %d\n", ret);
		जाओ err_disable_sclk;
	पूर्ण

	ret = clk_prepare_enable(rga->hclk);
	अगर (ret) अणु
		dev_err(rga->dev, "Cannot enable rga hclk: %d\n", ret);
		जाओ err_disable_aclk;
	पूर्ण

	वापस 0;

err_disable_sclk:
	clk_disable_unprepare(rga->sclk);
err_disable_aclk:
	clk_disable_unprepare(rga->aclk);

	वापस ret;
पूर्ण

अटल व्योम rga_disable_घड़ीs(काष्ठा rockchip_rga *rga)
अणु
	clk_disable_unprepare(rga->sclk);
	clk_disable_unprepare(rga->hclk);
	clk_disable_unprepare(rga->aclk);
पूर्ण

अटल पूर्णांक rga_parse_dt(काष्ठा rockchip_rga *rga)
अणु
	काष्ठा reset_control *core_rst, *axi_rst, *ahb_rst;

	core_rst = devm_reset_control_get(rga->dev, "core");
	अगर (IS_ERR(core_rst)) अणु
		dev_err(rga->dev, "failed to get core reset controller\n");
		वापस PTR_ERR(core_rst);
	पूर्ण

	axi_rst = devm_reset_control_get(rga->dev, "axi");
	अगर (IS_ERR(axi_rst)) अणु
		dev_err(rga->dev, "failed to get axi reset controller\n");
		वापस PTR_ERR(axi_rst);
	पूर्ण

	ahb_rst = devm_reset_control_get(rga->dev, "ahb");
	अगर (IS_ERR(ahb_rst)) अणु
		dev_err(rga->dev, "failed to get ahb reset controller\n");
		वापस PTR_ERR(ahb_rst);
	पूर्ण

	reset_control_निश्चित(core_rst);
	udelay(1);
	reset_control_deनिश्चित(core_rst);

	reset_control_निश्चित(axi_rst);
	udelay(1);
	reset_control_deनिश्चित(axi_rst);

	reset_control_निश्चित(ahb_rst);
	udelay(1);
	reset_control_deनिश्चित(ahb_rst);

	rga->sclk = devm_clk_get(rga->dev, "sclk");
	अगर (IS_ERR(rga->sclk)) अणु
		dev_err(rga->dev, "failed to get sclk clock\n");
		वापस PTR_ERR(rga->sclk);
	पूर्ण

	rga->aclk = devm_clk_get(rga->dev, "aclk");
	अगर (IS_ERR(rga->aclk)) अणु
		dev_err(rga->dev, "failed to get aclk clock\n");
		वापस PTR_ERR(rga->aclk);
	पूर्ण

	rga->hclk = devm_clk_get(rga->dev, "hclk");
	अगर (IS_ERR(rga->hclk)) अणु
		dev_err(rga->dev, "failed to get hclk clock\n");
		वापस PTR_ERR(rga->hclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_rga *rga;
	काष्ठा video_device *vfd;
	काष्ठा resource *res;
	पूर्णांक ret = 0;
	पूर्णांक irq;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	rga = devm_kzalloc(&pdev->dev, माप(*rga), GFP_KERNEL);
	अगर (!rga)
		वापस -ENOMEM;

	rga->dev = &pdev->dev;
	spin_lock_init(&rga->ctrl_lock);
	mutex_init(&rga->mutex);

	ret = rga_parse_dt(rga);
	अगर (ret)
		dev_err(&pdev->dev, "Unable to parse OF data\n");

	pm_runसमय_enable(rga->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	rga->regs = devm_ioremap_resource(rga->dev, res);
	अगर (IS_ERR(rga->regs)) अणु
		ret = PTR_ERR(rga->regs);
		जाओ err_put_clk;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_put_clk;
	पूर्ण

	ret = devm_request_irq(rga->dev, irq, rga_isr, 0,
			       dev_name(rga->dev), rga);
	अगर (ret < 0) अणु
		dev_err(rga->dev, "failed to request irq\n");
		जाओ err_put_clk;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &rga->v4l2_dev);
	अगर (ret)
		जाओ err_put_clk;
	vfd = video_device_alloc();
	अगर (!vfd) अणु
		v4l2_err(&rga->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ unreg_v4l2_dev;
	पूर्ण
	*vfd = rga_videodev;
	vfd->lock = &rga->mutex;
	vfd->v4l2_dev = &rga->v4l2_dev;

	video_set_drvdata(vfd, rga);
	rga->vfd = vfd;

	platक्रमm_set_drvdata(pdev, rga);
	rga->m2m_dev = v4l2_m2m_init(&rga_m2m_ops);
	अगर (IS_ERR(rga->m2m_dev)) अणु
		v4l2_err(&rga->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(rga->m2m_dev);
		जाओ unreg_video_dev;
	पूर्ण

	pm_runसमय_get_sync(rga->dev);

	rga->version.major = (rga_पढ़ो(rga, RGA_VERSION_INFO) >> 24) & 0xFF;
	rga->version.minor = (rga_पढ़ो(rga, RGA_VERSION_INFO) >> 20) & 0x0F;

	v4l2_info(&rga->v4l2_dev, "HW Version: 0x%02x.%02x\n",
		  rga->version.major, rga->version.minor);

	pm_runसमय_put(rga->dev);

	/* Create CMD buffer */
	rga->cmdbuf_virt = dma_alloc_attrs(rga->dev, RGA_CMDBUF_SIZE,
					   &rga->cmdbuf_phy, GFP_KERNEL,
					   DMA_ATTR_WRITE_COMBINE);

	rga->src_mmu_pages =
		(अचिन्हित पूर्णांक *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, 3);
	rga->dst_mmu_pages =
		(अचिन्हित पूर्णांक *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, 3);

	def_frame.stride = (def_frame.width * def_frame.fmt->depth) >> 3;
	def_frame.size = def_frame.stride * def_frame.height;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&rga->v4l2_dev, "Failed to register video device\n");
		जाओ rel_vdev;
	पूर्ण

	v4l2_info(&rga->v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));

	वापस 0;

rel_vdev:
	video_device_release(vfd);
unreg_video_dev:
	video_unरेजिस्टर_device(rga->vfd);
unreg_v4l2_dev:
	v4l2_device_unरेजिस्टर(&rga->v4l2_dev);
err_put_clk:
	pm_runसमय_disable(rga->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rga_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_rga *rga = platक्रमm_get_drvdata(pdev);

	dma_मुक्त_attrs(rga->dev, RGA_CMDBUF_SIZE, rga->cmdbuf_virt,
		       rga->cmdbuf_phy, DMA_ATTR_WRITE_COMBINE);

	मुक्त_pages((अचिन्हित दीर्घ)rga->src_mmu_pages, 3);
	मुक्त_pages((अचिन्हित दीर्घ)rga->dst_mmu_pages, 3);

	v4l2_info(&rga->v4l2_dev, "Removing\n");

	v4l2_m2m_release(rga->m2m_dev);
	video_unरेजिस्टर_device(rga->vfd);
	v4l2_device_unरेजिस्टर(&rga->v4l2_dev);

	pm_runसमय_disable(rga->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rga_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rockchip_rga *rga = dev_get_drvdata(dev);

	rga_disable_घड़ीs(rga);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rga_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rockchip_rga *rga = dev_get_drvdata(dev);

	वापस rga_enable_घड़ीs(rga);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rga_pm = अणु
	SET_RUNTIME_PM_OPS(rga_runसमय_suspend,
			   rga_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_rga_match[] = अणु
	अणु
		.compatible = "rockchip,rk3288-rga",
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-rga",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_rga_match);

अटल काष्ठा platक्रमm_driver rga_pdrv = अणु
	.probe = rga_probe,
	.हटाओ = rga_हटाओ,
	.driver = अणु
		.name = RGA_NAME,
		.pm = &rga_pm,
		.of_match_table = rockchip_rga_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rga_pdrv);

MODULE_AUTHOR("Jacob Chen <jacob-chen@iotwrt.com>");
MODULE_DESCRIPTION("Rockchip Raster 2d Graphic Acceleration Unit");
MODULE_LICENSE("GPL");
