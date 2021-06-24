<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner sun8i DE2 rotation driver
 *
 * Copyright (C) 2020 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "sun8i-formats.h"
#समावेश "sun8i-rotate.h"

अटल अंतरभूत u32 rotate_पढ़ो(काष्ठा rotate_dev *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम rotate_ग_लिखो(काष्ठा rotate_dev *dev, u32 reg, u32 value)
अणु
	ग_लिखोl(value, dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम rotate_set_bits(काष्ठा rotate_dev *dev, u32 reg, u32 bits)
अणु
	ग_लिखोl(पढ़ोl(dev->base + reg) | bits, dev->base + reg);
पूर्ण

अटल व्योम rotate_calc_addr_pitch(dma_addr_t buffer,
				   u32 bytesperline, u32 height,
				   स्थिर काष्ठा rotate_क्रमmat *fmt,
				   dma_addr_t *addr, u32 *pitch)
अणु
	u32 size;
	पूर्णांक i;

	क्रम (i = 0; i < fmt->planes; i++) अणु
		pitch[i] = bytesperline;
		addr[i] = buffer;
		अगर (i > 0)
			pitch[i] /= fmt->hsub / fmt->bpp[i];
		size = pitch[i] * height;
		अगर (i > 0)
			size /= fmt->vsub;
		buffer += size;
	पूर्ण
पूर्ण

अटल व्योम rotate_device_run(व्योम *priv)
अणु
	काष्ठा rotate_ctx *ctx = priv;
	काष्ठा rotate_dev *dev = ctx->dev;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	स्थिर काष्ठा rotate_क्रमmat *fmt;
	dma_addr_t addr[3];
	u32 val, pitch[3];

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_copy_metadata(src, dst, true);

	val = ROTATE_GLB_CTL_MODE(ROTATE_MODE_COPY_ROTATE);
	अगर (ctx->hflip)
		val |= ROTATE_GLB_CTL_HFLIP;
	अगर (ctx->vflip)
		val |= ROTATE_GLB_CTL_VFLIP;
	val |= ROTATE_GLB_CTL_ROTATION(ctx->rotate / 90);
	अगर (ctx->rotate != 90 && ctx->rotate != 270)
		val |= ROTATE_GLB_CTL_BURST_LEN(ROTATE_BURST_64);
	अन्यथा
		val |= ROTATE_GLB_CTL_BURST_LEN(ROTATE_BURST_8);
	rotate_ग_लिखो(dev, ROTATE_GLB_CTL, val);

	fmt = rotate_find_क्रमmat(ctx->src_fmt.pixelक्रमmat);
	अगर (!fmt)
		वापस;

	rotate_ग_लिखो(dev, ROTATE_IN_FMT, ROTATE_IN_FMT_FORMAT(fmt->hw_क्रमmat));

	rotate_calc_addr_pitch(vb2_dma_contig_plane_dma_addr(&src->vb2_buf, 0),
			       ctx->src_fmt.bytesperline, ctx->src_fmt.height,
			       fmt, addr, pitch);

	rotate_ग_लिखो(dev, ROTATE_IN_SIZE,
		     ROTATE_SIZE(ctx->src_fmt.width, ctx->src_fmt.height));

	rotate_ग_लिखो(dev, ROTATE_IN_PITCH0, pitch[0]);
	rotate_ग_लिखो(dev, ROTATE_IN_PITCH1, pitch[1]);
	rotate_ग_लिखो(dev, ROTATE_IN_PITCH2, pitch[2]);

	rotate_ग_लिखो(dev, ROTATE_IN_ADDRL0, addr[0]);
	rotate_ग_लिखो(dev, ROTATE_IN_ADDRL1, addr[1]);
	rotate_ग_लिखो(dev, ROTATE_IN_ADDRL2, addr[2]);

	rotate_ग_लिखो(dev, ROTATE_IN_ADDRH0, 0);
	rotate_ग_लिखो(dev, ROTATE_IN_ADDRH1, 0);
	rotate_ग_लिखो(dev, ROTATE_IN_ADDRH2, 0);

	fmt = rotate_find_क्रमmat(ctx->dst_fmt.pixelक्रमmat);
	अगर (!fmt)
		वापस;

	rotate_calc_addr_pitch(vb2_dma_contig_plane_dma_addr(&dst->vb2_buf, 0),
			       ctx->dst_fmt.bytesperline, ctx->dst_fmt.height,
			       fmt, addr, pitch);

	rotate_ग_लिखो(dev, ROTATE_OUT_SIZE,
		     ROTATE_SIZE(ctx->dst_fmt.width, ctx->dst_fmt.height));

	rotate_ग_लिखो(dev, ROTATE_OUT_PITCH0, pitch[0]);
	rotate_ग_लिखो(dev, ROTATE_OUT_PITCH1, pitch[1]);
	rotate_ग_लिखो(dev, ROTATE_OUT_PITCH2, pitch[2]);

	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRL0, addr[0]);
	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRL1, addr[1]);
	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRL2, addr[2]);

	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRH0, 0);
	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRH1, 0);
	rotate_ग_लिखो(dev, ROTATE_OUT_ADDRH2, 0);

	rotate_set_bits(dev, ROTATE_INT, ROTATE_INT_FINISH_IRQ_EN);
	rotate_set_bits(dev, ROTATE_GLB_CTL, ROTATE_GLB_CTL_START);
पूर्ण

अटल irqवापस_t rotate_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vb2_v4l2_buffer *buffer;
	काष्ठा rotate_dev *dev = data;
	काष्ठा rotate_ctx *ctx;
	अचिन्हित पूर्णांक val;

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		वापस IRQ_NONE;
	पूर्ण

	val = rotate_पढ़ो(dev, ROTATE_INT);
	अगर (!(val & ROTATE_INT_FINISH_IRQ))
		वापस IRQ_NONE;

	/* clear flag and disable irq */
	rotate_ग_लिखो(dev, ROTATE_INT, ROTATE_INT_FINISH_IRQ);

	buffer = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(buffer, VB2_BUF_STATE_DONE);

	buffer = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(buffer, VB2_BUF_STATE_DONE);

	v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा rotate_ctx *rotate_file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा rotate_ctx, fh);
पूर्ण

अटल व्योम rotate_prepare_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix_fmt)
अणु
	अचिन्हित पूर्णांक height, width, alignment, sizeimage, size, bpl;
	स्थिर काष्ठा rotate_क्रमmat *fmt;
	पूर्णांक i;

	fmt = rotate_find_क्रमmat(pix_fmt->pixelक्रमmat);
	अगर (!fmt)
		वापस;

	width = ALIGN(pix_fmt->width, fmt->hsub);
	height = ALIGN(pix_fmt->height, fmt->vsub);

	/* all pitches have to be 16 byte aligned */
	alignment = 16;
	अगर (fmt->planes > 1)
		alignment *= fmt->hsub / fmt->bpp[1];
	bpl = ALIGN(width * fmt->bpp[0], alignment);

	sizeimage = 0;
	क्रम (i = 0; i < fmt->planes; i++) अणु
		size = bpl * height;
		अगर (i > 0) अणु
			size *= fmt->bpp[i];
			size /= fmt->hsub;
			size /= fmt->vsub;
		पूर्ण
		sizeimage += size;
	पूर्ण

	pix_fmt->width = width;
	pix_fmt->height = height;
	pix_fmt->bytesperline = bpl;
	pix_fmt->sizeimage = sizeimage;
पूर्ण

अटल पूर्णांक rotate_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, ROTATE_NAME, माप(cap->driver));
	strscpy(cap->card, ROTATE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", ROTATE_NAME);

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस rotate_क्रमागत_fmt(f, true);
पूर्ण

अटल पूर्णांक rotate_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस rotate_क्रमागत_fmt(f, false);
पूर्ण

अटल पूर्णांक rotate_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा rotate_क्रमmat *fmt;

	अगर (fsize->index != 0)
		वापस -EINVAL;

	fmt = rotate_find_क्रमmat(fsize->pixel_क्रमmat);
	अगर (!fmt)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = ROTATE_MIN_WIDTH;
	fsize->stepwise.min_height = ROTATE_MIN_HEIGHT;
	fsize->stepwise.max_width = ROTATE_MAX_WIDTH;
	fsize->stepwise.max_height = ROTATE_MAX_HEIGHT;
	fsize->stepwise.step_width = fmt->hsub;
	fsize->stepwise.step_height = fmt->vsub;

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_set_cap_क्रमmat(काष्ठा rotate_ctx *ctx,
				 काष्ठा v4l2_pix_क्रमmat *f,
				 u32 rotate)
अणु
	स्थिर काष्ठा rotate_क्रमmat *fmt;

	fmt = rotate_find_क्रमmat(ctx->src_fmt.pixelक्रमmat);
	अगर (!fmt)
		वापस -EINVAL;

	अगर (fmt->flags & ROTATE_FLAG_YUV)
		f->pixelक्रमmat = V4L2_PIX_FMT_YUV420;
	अन्यथा
		f->pixelक्रमmat = ctx->src_fmt.pixelक्रमmat;

	f->field = V4L2_FIELD_NONE;

	अगर (rotate == 90 || rotate == 270) अणु
		f->width = ctx->src_fmt.height;
		f->height = ctx->src_fmt.width;
	पूर्ण अन्यथा अणु
		f->width = ctx->src_fmt.width;
		f->height = ctx->src_fmt.height;
	पूर्ण

	rotate_prepare_क्रमmat(f);

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rotate_ctx *ctx = rotate_file2ctx(file);

	f->fmt.pix = ctx->dst_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rotate_ctx *ctx = rotate_file2ctx(file);

	f->fmt.pix = ctx->src_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rotate_ctx *ctx = rotate_file2ctx(file);

	वापस rotate_set_cap_क्रमmat(ctx, &f->fmt.pix, ctx->rotate);
पूर्ण

अटल पूर्णांक rotate_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	अगर (!rotate_find_क्रमmat(f->fmt.pix.pixelक्रमmat))
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_ARGB32;

	अगर (f->fmt.pix.width < ROTATE_MIN_WIDTH)
		f->fmt.pix.width = ROTATE_MIN_WIDTH;
	अगर (f->fmt.pix.height < ROTATE_MIN_HEIGHT)
		f->fmt.pix.height = ROTATE_MIN_HEIGHT;

	अगर (f->fmt.pix.width > ROTATE_MAX_WIDTH)
		f->fmt.pix.width = ROTATE_MAX_WIDTH;
	अगर (f->fmt.pix.height > ROTATE_MAX_HEIGHT)
		f->fmt.pix.height = ROTATE_MAX_HEIGHT;

	f->fmt.pix.field = V4L2_FIELD_NONE;

	rotate_prepare_क्रमmat(&f->fmt.pix);

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rotate_ctx *ctx = rotate_file2ctx(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = rotate_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	ctx->dst_fmt = f->fmt.pix;

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rotate_ctx *ctx = rotate_file2ctx(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = rotate_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	/*
	 * Capture queue has to be also checked, because क्रमmat and size
	 * depends on output क्रमmat and size.
	 */
	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	ctx->src_fmt = f->fmt.pix;

	/* Propagate colorspace inक्रमmation to capture. */
	ctx->dst_fmt.colorspace = f->fmt.pix.colorspace;
	ctx->dst_fmt.xfer_func = f->fmt.pix.xfer_func;
	ctx->dst_fmt.ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->dst_fmt.quantization = f->fmt.pix.quantization;

	वापस rotate_set_cap_क्रमmat(ctx, &ctx->dst_fmt, ctx->rotate);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rotate_ioctl_ops = अणु
	.vidioc_querycap		= rotate_querycap,

	.vidioc_क्रमागत_framesizes		= rotate_क्रमागत_framesizes,

	.vidioc_क्रमागत_fmt_vid_cap	= rotate_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= rotate_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= rotate_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= rotate_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out	= rotate_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= rotate_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= rotate_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= rotate_s_fmt_vid_out,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक rotate_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
			      अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			      काष्ठा device *alloc_devs[])
अणु
	काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix_fmt;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	अन्यथा
		pix_fmt = &ctx->dst_fmt;

	अगर (*nplanes) अणु
		अगर (sizes[0] < pix_fmt->sizeimage)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		sizes[0] = pix_fmt->sizeimage;
		*nplanes = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix_fmt;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	अन्यथा
		pix_fmt = &ctx->dst_fmt;

	अगर (vb2_plane_size(vb, 0) < pix_fmt->sizeimage)
		वापस -EINVAL;

	vb2_set_plane_payload(vb, 0, pix_fmt->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम rotate_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल व्योम rotate_queue_cleanup(काष्ठा vb2_queue *vq, u32 state)
अणु
	काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf;

	करो अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		अगर (vbuf)
			v4l2_m2m_buf_करोne(vbuf, state);
	पूर्ण जबतक (vbuf);
पूर्ण

अटल पूर्णांक rotate_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vq);
		काष्ठा device *dev = ctx->dev->dev;
		पूर्णांक ret;

		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to enable module\n");

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rotate_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		काष्ठा rotate_ctx *ctx = vb2_get_drv_priv(vq);

		pm_runसमय_put(ctx->dev->dev);
	पूर्ण

	rotate_queue_cleanup(vq, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rotate_qops = अणु
	.queue_setup		= rotate_queue_setup,
	.buf_prepare		= rotate_buf_prepare,
	.buf_queue		= rotate_buf_queue,
	.start_streaming	= rotate_start_streaming,
	.stop_streaming		= rotate_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक rotate_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			     काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा rotate_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->min_buffers_needed = 1;
	src_vq->ops = &rotate_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->dev_mutex;
	src_vq->dev = ctx->dev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->min_buffers_needed = 2;
	dst_vq->ops = &rotate_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->dev;

	ret = vb2_queue_init(dst_vq);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा rotate_ctx *ctx = container_of(ctrl->handler,
					      काष्ठा rotate_ctx,
					      ctrl_handler);
	काष्ठा v4l2_pix_क्रमmat fmt;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_ROTATE:
		rotate_set_cap_क्रमmat(ctx, &fmt, ctrl->val);

		/* Check अगर capture क्रमmat needs to be changed */
		अगर (fmt.width != ctx->dst_fmt.width ||
		    fmt.height != ctx->dst_fmt.height ||
		    fmt.bytesperline != ctx->dst_fmt.bytesperline ||
		    fmt.sizeimage != ctx->dst_fmt.sizeimage) अणु
			काष्ठा vb2_queue *vq;

			vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					     V4L2_BUF_TYPE_VIDEO_CAPTURE);
			अगर (vb2_is_busy(vq))
				वापस -EBUSY;

			rotate_set_cap_क्रमmat(ctx, &ctx->dst_fmt, ctrl->val);
		पूर्ण

		ctx->rotate = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rotate_ctrl_ops = अणु
	.s_ctrl = rotate_s_ctrl,
पूर्ण;

अटल पूर्णांक rotate_setup_ctrls(काष्ठा rotate_ctx *ctx)
अणु
	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 3);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rotate_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rotate_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &rotate_ctrl_ops,
			  V4L2_CID_ROTATE, 0, 270, 90, 0);

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		v4l2_err(&ctx->dev->v4l2_dev, "control setup failed!\n");
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);

		वापस err;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
पूर्ण

अटल पूर्णांक rotate_खोलो(काष्ठा file *file)
अणु
	काष्ठा rotate_dev *dev = video_drvdata(file);
	काष्ठा rotate_ctx *ctx = शून्य;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->dev_mutex))
		वापस -ERESTARTSYS;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		mutex_unlock(&dev->dev_mutex);
		वापस -ENOMEM;
	पूर्ण

	/* शेष output क्रमmat */
	ctx->src_fmt.pixelक्रमmat = V4L2_PIX_FMT_ARGB32;
	ctx->src_fmt.field = V4L2_FIELD_NONE;
	ctx->src_fmt.width = 640;
	ctx->src_fmt.height = 480;
	rotate_prepare_क्रमmat(&ctx->src_fmt);

	/* शेष capture क्रमmat */
	rotate_set_cap_क्रमmat(ctx, &ctx->dst_fmt, ctx->rotate);

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = dev;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &rotate_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_मुक्त;
	पूर्ण

	v4l2_fh_add(&ctx->fh);

	ret = rotate_setup_ctrls(ctx);
	अगर (ret)
		जाओ err_मुक्त;

	ctx->fh.ctrl_handler = &ctx->ctrl_handler;

	mutex_unlock(&dev->dev_mutex);

	वापस 0;

err_मुक्त:
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rotate_release(काष्ठा file *file)
अणु
	काष्ठा rotate_dev *dev = video_drvdata(file);
	काष्ठा rotate_ctx *ctx = container_of(file->निजी_data,
						   काष्ठा rotate_ctx, fh);

	mutex_lock(&dev->dev_mutex);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	kमुक्त(ctx);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations rotate_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rotate_खोलो,
	.release	= rotate_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device rotate_video_device = अणु
	.name		= ROTATE_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &rotate_fops,
	.ioctl_ops	= &rotate_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops rotate_m2m_ops = अणु
	.device_run	= rotate_device_run,
पूर्ण;

अटल पूर्णांक rotate_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rotate_dev *dev;
	काष्ठा video_device *vfd;
	पूर्णांक irq, ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->vfd = rotate_video_device;
	dev->dev = &pdev->dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	ret = devm_request_irq(dev->dev, irq, rotate_irq,
			       0, dev_name(dev->dev), dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to request IRQ\n");

		वापस ret;
	पूर्ण

	dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->base))
		वापस PTR_ERR(dev->base);

	dev->bus_clk = devm_clk_get(dev->dev, "bus");
	अगर (IS_ERR(dev->bus_clk)) अणु
		dev_err(dev->dev, "Failed to get bus clock\n");

		वापस PTR_ERR(dev->bus_clk);
	पूर्ण

	dev->mod_clk = devm_clk_get(dev->dev, "mod");
	अगर (IS_ERR(dev->mod_clk)) अणु
		dev_err(dev->dev, "Failed to get mod clock\n");

		वापस PTR_ERR(dev->mod_clk);
	पूर्ण

	dev->rstc = devm_reset_control_get(dev->dev, शून्य);
	अगर (IS_ERR(dev->rstc)) अणु
		dev_err(dev->dev, "Failed to get reset control\n");

		वापस PTR_ERR(dev->rstc);
	पूर्ण

	mutex_init(&dev->dev_mutex);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to register V4L2 device\n");

		वापस ret;
	पूर्ण

	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	snम_लिखो(vfd->name, माप(vfd->name), "%s",
		 rotate_video_device.name);
	video_set_drvdata(vfd, dev);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");

		जाओ err_v4l2;
	पूर्ण

	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	dev->m2m_dev = v4l2_m2m_init(&rotate_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M device\n");
		ret = PTR_ERR(dev->m2m_dev);

		जाओ err_video;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	pm_runसमय_enable(dev->dev);

	वापस 0;

err_video:
	video_unरेजिस्टर_device(&dev->vfd);
err_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rotate_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rotate_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_m2m_release(dev->m2m_dev);
	video_unरेजिस्टर_device(&dev->vfd);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	pm_runसमय_क्रमce_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rotate_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा rotate_dev *dev = dev_get_drvdata(device);
	पूर्णांक ret;

	ret = clk_prepare_enable(dev->bus_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable bus clock\n");

		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dev->mod_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable mod clock\n");

		जाओ err_bus_clk;
	पूर्ण

	ret = reset_control_deनिश्चित(dev->rstc);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to apply reset\n");

		जाओ err_mod_clk;
	पूर्ण

	वापस 0;

err_mod_clk:
	clk_disable_unprepare(dev->mod_clk);
err_bus_clk:
	clk_disable_unprepare(dev->bus_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक rotate_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा rotate_dev *dev = dev_get_drvdata(device);

	reset_control_निश्चित(dev->rstc);

	clk_disable_unprepare(dev->mod_clk);
	clk_disable_unprepare(dev->bus_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rotate_dt_match[] = अणु
	अणु .compatible = "allwinner,sun8i-a83t-de2-rotate" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rotate_dt_match);

अटल स्थिर काष्ठा dev_pm_ops rotate_pm_ops = अणु
	.runसमय_resume		= rotate_runसमय_resume,
	.runसमय_suspend	= rotate_runसमय_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver rotate_driver = अणु
	.probe		= rotate_probe,
	.हटाओ		= rotate_हटाओ,
	.driver		= अणु
		.name		= ROTATE_NAME,
		.of_match_table	= rotate_dt_match,
		.pm		= &rotate_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rotate_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jernej Skrabec <jernej.skrabec@siol.net>");
MODULE_DESCRIPTION("Allwinner DE2 rotate driver");
