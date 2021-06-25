<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/regmap.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "ge2d-regs.h"

#घोषणा GE2D_NAME	"meson-ge2d"

#घोषणा DEFAULT_WIDTH	128
#घोषणा DEFAULT_HEIGHT	128
#घोषणा DEFAULT_STRIDE	512

#घोषणा MAX_WIDTH	8191
#घोषणा MAX_HEIGHT	8191

/*
 * Missing features:
 * - Scaling
 * - Simple 1/2 vertical scaling
 * - YUV input support
 * - Source global alpha
 * - Colorspace conversion
 */

काष्ठा ge2d_fmt अणु
	u32 fourcc;
	bool alpha;
	bool le;
	अचिन्हित पूर्णांक depth;
	अचिन्हित पूर्णांक hw_fmt;
	अचिन्हित पूर्णांक hw_map;
पूर्ण;

काष्ठा ge2d_frame अणु
	काष्ठा vb2_v4l2_buffer *buf;

	/* Image Format */
	काष्ठा v4l2_pix_क्रमmat pix_fmt;

	/* Crop */
	काष्ठा v4l2_rect crop;

	/* Image क्रमmat */
	स्थिर काष्ठा ge2d_fmt *fmt;
पूर्ण;

काष्ठा ge2d_ctx अणु
	काष्ठा v4l2_fh fh;
	काष्ठा meson_ge2d *ge2d;
	काष्ठा ge2d_frame in;
	काष्ठा ge2d_frame out;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	अचिन्हित दीर्घ sequence_out, sequence_cap;

	/* Control values */
	u32 hflip;
	u32 vflip;
	u32 xy_swap;
पूर्ण;

काष्ठा meson_ge2d अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा video_device *vfd;

	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा clk *clk;

	/* vb2 queue lock */
	काष्ठा mutex mutex;

	काष्ठा ge2d_ctx *curr;
पूर्ण;

#घोषणा FMT(_fourcc, _alpha, _depth, _map)		\
अणु							\
	.fourcc = _fourcc,				\
	.alpha = (_alpha),				\
	.depth = (_depth),				\
	.hw_fmt = GE2D_FORMAT_ ## _depth ## BIT,	\
	.hw_map = GE2D_COLOR_MAP_ ## _map,		\
पूर्ण

/* TOFIX Handle the YUV input क्रमmats */
अटल स्थिर काष्ठा ge2d_fmt क्रमmats[] = अणु
	/*  FOURCC Alpha  HW FMT  HW MAP */
	FMT(V4L2_PIX_FMT_XRGB32, false, 32, BGRA8888),
	FMT(V4L2_PIX_FMT_RGB32, true, 32, BGRA8888),
	FMT(V4L2_PIX_FMT_ARGB32, true, 32, BGRA8888),
	FMT(V4L2_PIX_FMT_RGBX32, false, 32, ABGR8888),
	FMT(V4L2_PIX_FMT_RGBA32, true, 32, ABGR8888),
	FMT(V4L2_PIX_FMT_BGRX32, false, 32, RGBA8888),
	FMT(V4L2_PIX_FMT_BGRA32, true, 32, RGBA8888),
	FMT(V4L2_PIX_FMT_BGR32, true, 32, ARGB8888),
	FMT(V4L2_PIX_FMT_ABGR32, true, 32, ARGB8888),
	FMT(V4L2_PIX_FMT_XBGR32, false, 32, ARGB8888),

	FMT(V4L2_PIX_FMT_RGB24, false, 24, BGR888),
	FMT(V4L2_PIX_FMT_BGR24, false, 24, RGB888),

	FMT(V4L2_PIX_FMT_XRGB555X, false, 16, ARGB1555),
	FMT(V4L2_PIX_FMT_ARGB555X, true, 16, ARGB1555),
	FMT(V4L2_PIX_FMT_RGB565, false, 16, RGB565),
	FMT(V4L2_PIX_FMT_RGBX444, false, 16, RGBA4444),
	FMT(V4L2_PIX_FMT_RGBA444, true, 16, RGBA4444),
	FMT(V4L2_PIX_FMT_XRGB444, false, 16, ARGB4444),
	FMT(V4L2_PIX_FMT_ARGB444, true, 16, ARGB4444),
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

अटल स्थिर काष्ठा ge2d_fmt *find_fmt(काष्ठा v4l2_क्रमmat *f)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix.pixelक्रमmat)
			वापस &क्रमmats[i];
	पूर्ण

	/*
	 * TRY_FMT/S_FMT should never वापस an error when the requested क्रमmat
	 * is not supported. Drivers should always वापस a valid क्रमmat,
	 * preferably a क्रमmat that is as widely supported by applications as
	 * possible.
	 */
	वापस &क्रमmats[0];
पूर्ण

अटल काष्ठा ge2d_frame *get_frame(काष्ठा ge2d_ctx *ctx,
				    क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &ctx->in;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &ctx->out;
	शेष:
		/* This should never happen, warn and वापस OUTPUT frame */
		dev_warn(ctx->ge2d->dev, "%s: invalid buffer type\n", __func__);
		वापस &ctx->in;
	पूर्ण
पूर्ण

अटल व्योम ge2d_hw_start(काष्ठा meson_ge2d *ge2d)
अणु
	काष्ठा ge2d_ctx *ctx = ge2d->curr;
	u32 reg;

	/* Reset */
	regmap_update_bits(ge2d->map, GE2D_GEN_CTRL1,
			   GE2D_SOFT_RST, GE2D_SOFT_RST);
	regmap_update_bits(ge2d->map, GE2D_GEN_CTRL1,
			   GE2D_SOFT_RST, 0);

	usleep_range(100, 200);

	/* Implement CANVAS क्रम non-AXG */
	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_BADDR_CTRL,
		     (vb2_dma_contig_plane_dma_addr(&ctx->in.buf->vb2_buf, 0) + 7) >> 3);
	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_STRIDE_CTRL,
		     (ctx->in.pix_fmt.bytesperline + 7) >> 3);
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_BADDR_CTRL,
		     (vb2_dma_contig_plane_dma_addr(&ctx->out.buf->vb2_buf, 0) + 7) >> 3);
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_STRIDE_CTRL,
		     (ctx->out.pix_fmt.bytesperline + 7) >> 3);
	regmap_ग_लिखो(ge2d->map, GE2D_DST1_BADDR_CTRL,
		     (vb2_dma_contig_plane_dma_addr(&ctx->out.buf->vb2_buf, 0) + 7) >> 3);
	regmap_ग_लिखो(ge2d->map, GE2D_DST1_STRIDE_CTRL,
		     (ctx->out.pix_fmt.bytesperline + 7) >> 3);

	regmap_ग_लिखो(ge2d->map, GE2D_GEN_CTRL0, 0);
	regmap_ग_लिखो(ge2d->map, GE2D_GEN_CTRL1,
		     FIELD_PREP(GE2D_INTERRUPT_CTRL, 2) |
		     FIELD_PREP(GE2D_SRC2_BURST_SIZE_CTRL, 3) |
		     FIELD_PREP(GE2D_SRC1_BURST_SIZE_CTRL, 0x3f));

	regmap_ग_लिखो(ge2d->map, GE2D_GEN_CTRL2,
		     GE2D_SRC1_LITTLE_ENDIAN |
		     GE2D_SRC2_LITTLE_ENDIAN |
		     GE2D_DST_LITTLE_ENDIAN |
		     FIELD_PREP(GE2D_DST1_COLOR_MAP, ctx->out.fmt->hw_map) |
		     FIELD_PREP(GE2D_DST1_FORMAT, ctx->out.fmt->hw_fmt) |
		     FIELD_PREP(GE2D_SRC2_COLOR_MAP, ctx->out.fmt->hw_map) |
		     FIELD_PREP(GE2D_SRC2_FORMAT, ctx->out.fmt->hw_fmt) |
		     FIELD_PREP(GE2D_SRC1_COLOR_MAP, ctx->in.fmt->hw_map) |
		     FIELD_PREP(GE2D_SRC1_FORMAT, ctx->in.fmt->hw_fmt));
	regmap_ग_लिखो(ge2d->map, GE2D_GEN_CTRL3,
		     GE2D_DST1_ENABLE);

	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_CLIPY_START_END,
		     FIELD_PREP(GE2D_START, ctx->in.crop.top) |
		     FIELD_PREP(GE2D_END, ctx->in.crop.top + ctx->in.crop.height));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_CLIPX_START_END,
		     FIELD_PREP(GE2D_START, ctx->in.crop.left) |
		     FIELD_PREP(GE2D_END, ctx->in.crop.left + ctx->in.crop.width));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_CLIPY_START_END,
		     FIELD_PREP(GE2D_START, ctx->out.crop.top) |
		     FIELD_PREP(GE2D_END, ctx->out.crop.top + ctx->out.crop.height));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_CLIPX_START_END,
		     FIELD_PREP(GE2D_START, ctx->out.crop.left) |
		     FIELD_PREP(GE2D_END, ctx->out.crop.left + ctx->out.crop.width));
	regmap_ग_लिखो(ge2d->map, GE2D_DST_CLIPY_START_END,
		     FIELD_PREP(GE2D_START, ctx->out.crop.top) |
		     FIELD_PREP(GE2D_END, ctx->out.crop.top + ctx->out.crop.height));
	regmap_ग_लिखो(ge2d->map, GE2D_DST_CLIPX_START_END,
		     FIELD_PREP(GE2D_START, ctx->out.crop.left) |
		     FIELD_PREP(GE2D_END, ctx->out.crop.left + ctx->out.crop.width));

	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_Y_START_END,
		     FIELD_PREP(GE2D_END, ctx->in.pix_fmt.height));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC1_X_START_END,
		     FIELD_PREP(GE2D_END, ctx->in.pix_fmt.width));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_Y_START_END,
		     FIELD_PREP(GE2D_END, ctx->out.pix_fmt.height));
	regmap_ग_लिखो(ge2d->map, GE2D_SRC2_X_START_END,
		     FIELD_PREP(GE2D_END, ctx->out.pix_fmt.width));
	regmap_ग_लिखो(ge2d->map, GE2D_DST_Y_START_END,
		     FIELD_PREP(GE2D_END, ctx->out.pix_fmt.height));
	regmap_ग_लिखो(ge2d->map, GE2D_DST_X_START_END,
		     FIELD_PREP(GE2D_END, ctx->out.pix_fmt.width));

	/* Color, no blend, use source color */
	reg = GE2D_ALU_DO_COLOR_OPERATION_LOGIC(LOGIC_OPERATION_COPY,
						COLOR_FACTOR_SRC_COLOR);

	अगर (ctx->in.fmt->alpha && ctx->out.fmt->alpha)
		/* Take source alpha */
		reg |= GE2D_ALU_DO_ALPHA_OPERATION_LOGIC(LOGIC_OPERATION_COPY,
							 COLOR_FACTOR_SRC_ALPHA);
	अन्यथा अगर (!ctx->out.fmt->alpha)
		/* Set alpha to 0 */
		reg |= GE2D_ALU_DO_ALPHA_OPERATION_LOGIC(LOGIC_OPERATION_SET,
							 COLOR_FACTOR_ZERO);
	अन्यथा
		/* Keep original alpha */
		reg |= GE2D_ALU_DO_ALPHA_OPERATION_LOGIC(LOGIC_OPERATION_COPY,
							 COLOR_FACTOR_DST_ALPHA);

	regmap_ग_लिखो(ge2d->map, GE2D_ALU_OP_CTRL, reg);

	/* Start */
	regmap_ग_लिखो(ge2d->map, GE2D_CMD_CTRL,
		     (ctx->xy_swap ? GE2D_DST_XY_SWAP : 0) |
		     (ctx->hflip ? GE2D_SRC1_Y_REV : 0) |
		     (ctx->vflip ? GE2D_SRC1_X_REV : 0) |
		     GE2D_CBUS_CMD_WR);
पूर्ण

अटल व्योम device_run(व्योम *priv)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;

	ge2d->curr = ctx;

	ctx->in.buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	ctx->out.buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	ge2d_hw_start(ge2d);
पूर्ण

अटल irqवापस_t ge2d_isr(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा meson_ge2d *ge2d = priv;
	u32 पूर्णांकr;

	regmap_पढ़ो(ge2d->map, GE2D_STATUS0, &पूर्णांकr);

	अगर (!(पूर्णांकr & GE2D_GE2D_BUSY)) अणु
		काष्ठा vb2_v4l2_buffer *src, *dst;
		काष्ठा ge2d_ctx *ctx = ge2d->curr;

		ge2d->curr = शून्य;

		src = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		dst = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		src->sequence = ctx->sequence_out++;
		dst->sequence = ctx->sequence_cap++;

		dst->समयcode = src->समयcode;
		dst->vb2_buf.बारtamp = src->vb2_buf.बारtamp;
		dst->flags = src->flags;

		v4l2_m2m_buf_करोne(src, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst, VB2_BUF_STATE_DONE);
		v4l2_m2m_job_finish(ge2d->m2m_dev, ctx->fh.m2m_ctx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops ge2d_m2m_ops = अणु
	.device_run = device_run,
पूर्ण;

अटल पूर्णांक ge2d_queue_setup(काष्ठा vb2_queue *vq,
			    अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा ge2d_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा ge2d_frame *f = get_frame(ctx, vq->type);

	अगर (*nplanes)
		वापस sizes[0] < f->pix_fmt.sizeimage ? -EINVAL : 0;

	sizes[0] = f->pix_fmt.sizeimage;
	*nplanes = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ge2d_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा ge2d_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा ge2d_frame *f = get_frame(ctx, vb->vb2_queue->type);

	vbuf->field = V4L2_FIELD_NONE;

	vb2_set_plane_payload(vb, 0, f->pix_fmt.sizeimage);

	वापस 0;
पूर्ण

अटल व्योम ge2d_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा ge2d_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक ge2d_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा ge2d_ctx *ctx = vb2_get_drv_priv(vq);

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		ctx->sequence_out = 0;
	अन्यथा
		ctx->sequence_cap = 0;

	वापस 0;
पूर्ण

अटल व्योम ge2d_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा ge2d_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vbuf)
			अवरोध;
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops ge2d_qops = अणु
	.queue_setup = ge2d_queue_setup,
	.buf_prepare = ge2d_buf_prepare,
	.buf_queue = ge2d_buf_queue,
	.start_streaming = ge2d_start_streaming,
	.stop_streaming = ge2d_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक
queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &ge2d_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->ge2d->mutex;
	src_vq->dev = ctx->ge2d->v4l2_dev.dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &ge2d_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->ge2d->mutex;
	dst_vq->dev = ctx->ge2d->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक
vidioc_querycap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, GE2D_NAME, माप(cap->driver));
	strscpy(cap->card, GE2D_NAME, माप(cap->card));
	strscpy(cap->bus_info, "platform:" GE2D_NAME, माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा ge2d_fmt *fmt;

	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;

	fmt = &क्रमmats[f->index];
	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा ge2d_frame *f;
	bool use_frame = false;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f = get_frame(ctx, s->type);

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
		s->r.width = f->pix_fmt.width;
		s->r.height = f->pix_fmt.height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;
	काष्ठा ge2d_frame *f;
	पूर्णांक ret = 0;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f = get_frame(ctx, s->type);

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
		v4l2_err(&ge2d->v4l2_dev,
			 "doesn't support negative values for top & left.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (s->r.left + s->r.width > f->pix_fmt.width ||
	    s->r.top + s->r.height > f->pix_fmt.height) अणु
		v4l2_err(&ge2d->v4l2_dev, "unsupported rectangle value.\n");
		वापस -EINVAL;
	पूर्ण

	f->crop = s->r;

	वापस ret;
पूर्ण

अटल व्योम vidioc_setup_cap_fmt(काष्ठा ge2d_ctx *ctx, काष्ठा v4l2_pix_क्रमmat *f)
अणु
	काष्ठा ge2d_frame *frm_out = get_frame(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

	*f = frm_out->pix_fmt;

	अगर (ctx->xy_swap) अणु
		f->width = frm_out->pix_fmt.height;
		f->height = frm_out->pix_fmt.width;
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_try_fmt_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा ge2d_fmt *fmt = find_fmt(f);
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा v4l2_pix_क्रमmat fmt_cap;

	vidioc_setup_cap_fmt(ctx, &fmt_cap);

	fmt_cap.pixelक्रमmat = fmt->fourcc;

	fmt_cap.bytesperline = max(f->fmt.pix.bytesperline,
				   ALIGN((fmt_cap.width * fmt->depth) >> 3, 8));

	fmt_cap.sizeimage = max(f->fmt.pix.sizeimage,
				fmt_cap.height * fmt_cap.bytesperline);

	f->fmt.pix = fmt_cap;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;
	काष्ठा vb2_queue *vq;
	काष्ठा ge2d_frame *frm;
	पूर्णांक ret = 0;

	/* Adjust all values accordingly to the hardware capabilities
	 * and chosen क्रमmat.
	 */
	ret = vidioc_try_fmt_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ge2d->v4l2_dev, "queue (%d) bust\n", f->type);
		वापस -EBUSY;
	पूर्ण

	frm = get_frame(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	frm->pix_fmt = f->fmt.pix;
	frm->fmt = find_fmt(f);
	f->fmt.pix.pixelक्रमmat = frm->fmt->fourcc;

	/* Reset crop settings */
	frm->crop.left = 0;
	frm->crop.top = 0;
	frm->crop.width = frm->pix_fmt.width;
	frm->crop.height = frm->pix_fmt.height;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा vb2_queue *vq;
	काष्ठा ge2d_frame *frm;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	frm = get_frame(ctx, f->type);

	f->fmt.pix = frm->pix_fmt;
	f->fmt.pix.pixelक्रमmat = frm->fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा ge2d_fmt *fmt = find_fmt(f);

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat = fmt->fourcc;

	अगर (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	अगर (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	f->fmt.pix.bytesperline = max(f->fmt.pix.bytesperline,
				      ALIGN((f->fmt.pix.width * fmt->depth) >> 3, 8));

	f->fmt.pix.sizeimage = max(f->fmt.pix.sizeimage,
				   f->fmt.pix.height * f->fmt.pix.bytesperline);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ge2d_ctx *ctx = priv;
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;
	काष्ठा vb2_queue *vq;
	काष्ठा ge2d_frame *frm, *frm_cap;
	पूर्णांक ret = 0;

	/* Adjust all values accordingly to the hardware capabilities
	 * and chosen क्रमmat.
	 */
	ret = vidioc_try_fmt_out(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ge2d->v4l2_dev, "queue (%d) bust\n", f->type);
		वापस -EBUSY;
	पूर्ण

	frm = get_frame(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	frm_cap = get_frame(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	frm->pix_fmt = f->fmt.pix;
	frm->fmt = find_fmt(f);
	f->fmt.pix.pixelक्रमmat = frm->fmt->fourcc;

	/* Reset crop settings */
	frm->crop.left = 0;
	frm->crop.top = 0;
	frm->crop.width = frm->pix_fmt.width;
	frm->crop.height = frm->pix_fmt.height;

	/* Propagate settings to capture */
	vidioc_setup_cap_fmt(ctx, &frm_cap->pix_fmt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops ge2d_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_cap,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out = vidioc_g_fmt,
	.vidioc_try_fmt_vid_out = vidioc_try_fmt_out,
	.vidioc_s_fmt_vid_out = vidioc_s_fmt_out,

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

अटल पूर्णांक ge2d_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ge2d_ctx *ctx = container_of(ctrl->handler, काष्ठा ge2d_ctx,
					   ctrl_handler);
	काष्ठा v4l2_pix_क्रमmat fmt;
	काष्ठा vb2_queue *vq;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_ROTATE:
		vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		अगर (vb2_is_busy(vq))
			वापस -EBUSY;

		अगर (ctrl->val == 90) अणु
			ctx->hflip = 0;
			ctx->vflip = 1;
			ctx->xy_swap = 1;
		पूर्ण अन्यथा अगर (ctrl->val == 180) अणु
			ctx->hflip = 1;
			ctx->vflip = 1;
			ctx->xy_swap = 0;
		पूर्ण अन्यथा अगर (ctrl->val == 270) अणु
			ctx->hflip = 1;
			ctx->vflip = 0;
			ctx->xy_swap = 1;
		पूर्ण अन्यथा अणु
			ctx->hflip = 0;
			ctx->vflip = 0;
			ctx->xy_swap = 0;
		पूर्ण

		vidioc_setup_cap_fmt(ctx, &fmt);

		/*
		 * If the rotation parameter changes the OUTPUT frames
		 * parameters, take them in account
		 */
		अगर (fmt.width != ctx->out.pix_fmt.width ||
		    fmt.height != ctx->out.pix_fmt.width ||
		    fmt.bytesperline > ctx->out.pix_fmt.bytesperline ||
		    fmt.sizeimage > ctx->out.pix_fmt.sizeimage)
			ctx->out.pix_fmt = fmt;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ge2d_ctrl_ops = अणु
	.s_ctrl = ge2d_s_ctrl,
पूर्ण;

अटल पूर्णांक ge2d_setup_ctrls(काष्ठा ge2d_ctx *ctx)
अणु
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 4);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &ge2d_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &ge2d_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &ge2d_ctrl_ops,
			  V4L2_CID_ROTATE, 0, 270, 90, 0);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		v4l2_err(&ge2d->v4l2_dev, "%s failed\n", __func__);
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ge2d_frame def_frame = अणु
	.pix_fmt = अणु
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
		.bytesperline = DEFAULT_STRIDE,
		.sizeimage = DEFAULT_STRIDE * DEFAULT_HEIGHT,
		.field = V4L2_FIELD_NONE,
	पूर्ण,
	.crop.width = DEFAULT_WIDTH,
	.crop.height = DEFAULT_HEIGHT,
	.fmt = &क्रमmats[0],
पूर्ण;

अटल पूर्णांक ge2d_खोलो(काष्ठा file *file)
अणु
	काष्ठा meson_ge2d *ge2d = video_drvdata(file);
	काष्ठा ge2d_ctx *ctx = शून्य;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ge2d = ge2d;

	/* Set शेष क्रमmats */
	ctx->in = def_frame;
	ctx->out = def_frame;

	अगर (mutex_lock_पूर्णांकerruptible(&ge2d->mutex)) अणु
		kमुक्त(ctx);
		वापस -ERESTARTSYS;
	पूर्ण
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(ge2d->m2m_dev, ctx, &queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		mutex_unlock(&ge2d->mutex);
		kमुक्त(ctx);
		वापस ret;
	पूर्ण
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ge2d_setup_ctrls(ctx);

	/* Write the शेष values to the ctx काष्ठा */
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	mutex_unlock(&ge2d->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ge2d_release(काष्ठा file *file)
अणु
	काष्ठा ge2d_ctx *ctx =
		container_of(file->निजी_data, काष्ठा ge2d_ctx, fh);
	काष्ठा meson_ge2d *ge2d = ctx->ge2d;

	mutex_lock(&ge2d->mutex);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);

	mutex_unlock(&ge2d->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations ge2d_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = ge2d_खोलो,
	.release = ge2d_release,
	.poll = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device ge2d_videodev = अणु
	.name = "meson-ge2d",
	.fops = &ge2d_fops,
	.ioctl_ops = &ge2d_ioctl_ops,
	.minor = -1,
	.release = video_device_release,
	.vfl_dir = VFL_सूची_M2M,
	.device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_ge2d_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = GE2D_SRC2_STRIDE_CTRL,
पूर्ण;

अटल पूर्णांक ge2d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_control *rst;
	काष्ठा video_device *vfd;
	काष्ठा meson_ge2d *ge2d;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret = 0;
	पूर्णांक irq;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ge2d = devm_kzalloc(&pdev->dev, माप(*ge2d), GFP_KERNEL);
	अगर (!ge2d)
		वापस -ENOMEM;

	ge2d->dev = &pdev->dev;
	mutex_init(&ge2d->mutex);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(ge2d->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	ge2d->map = devm_regmap_init_mmio(ge2d->dev, regs,
					  &meson_ge2d_regmap_conf);
	अगर (IS_ERR(ge2d->map))
		वापस PTR_ERR(ge2d->map);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(ge2d->dev, irq, ge2d_isr, 0,
			       dev_name(ge2d->dev), ge2d);
	अगर (ret < 0) अणु
		dev_err(ge2d->dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get(ge2d->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		dev_err(ge2d->dev, "failed to get core reset controller\n");
		वापस PTR_ERR(rst);
	पूर्ण

	ge2d->clk = devm_clk_get(ge2d->dev, शून्य);
	अगर (IS_ERR(ge2d->clk)) अणु
		dev_err(ge2d->dev, "failed to get clock\n");
		वापस PTR_ERR(ge2d->clk);
	पूर्ण

	reset_control_निश्चित(rst);
	udelay(1);
	reset_control_deनिश्चित(rst);

	ret = clk_prepare_enable(ge2d->clk);
	अगर (ret) अणु
		dev_err(ge2d->dev, "Cannot enable ge2d sclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &ge2d->v4l2_dev);
	अगर (ret)
		जाओ disable_clks;

	vfd = video_device_alloc();
	अगर (!vfd) अणु
		v4l2_err(&ge2d->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ unreg_v4l2_dev;
	पूर्ण

	*vfd = ge2d_videodev;
	vfd->lock = &ge2d->mutex;
	vfd->v4l2_dev = &ge2d->v4l2_dev;

	video_set_drvdata(vfd, ge2d);
	ge2d->vfd = vfd;

	platक्रमm_set_drvdata(pdev, ge2d);
	ge2d->m2m_dev = v4l2_m2m_init(&ge2d_m2m_ops);
	अगर (IS_ERR(ge2d->m2m_dev)) अणु
		v4l2_err(&ge2d->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(ge2d->m2m_dev);
		जाओ rel_vdev;
	पूर्ण

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&ge2d->v4l2_dev, "Failed to register video device\n");
		जाओ rel_m2m;
	पूर्ण

	v4l2_info(&ge2d->v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));

	वापस 0;

rel_m2m:
	v4l2_m2m_release(ge2d->m2m_dev);
rel_vdev:
	video_device_release(ge2d->vfd);
unreg_v4l2_dev:
	v4l2_device_unरेजिस्टर(&ge2d->v4l2_dev);
disable_clks:
	clk_disable_unprepare(ge2d->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ge2d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ge2d *ge2d = platक्रमm_get_drvdata(pdev);

	video_unरेजिस्टर_device(ge2d->vfd);
	v4l2_m2m_release(ge2d->m2m_dev);
	video_device_release(ge2d->vfd);
	v4l2_device_unरेजिस्टर(&ge2d->v4l2_dev);
	clk_disable_unprepare(ge2d->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_ge2d_match[] = अणु
	अणु
		.compatible = "amlogic,axg-ge2d",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, meson_ge2d_match);

अटल काष्ठा platक्रमm_driver ge2d_drv = अणु
	.probe = ge2d_probe,
	.हटाओ = ge2d_हटाओ,
	.driver = अणु
		.name = "meson-ge2d",
		.of_match_table = meson_ge2d_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ge2d_drv);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Amlogic 2D Graphic Acceleration Unit");
MODULE_LICENSE("GPL");
