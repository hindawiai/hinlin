<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * V4L2 deपूर्णांकerlacing support.
 *
 * Copyright (c) 2012 Vista Silicon S.L.
 * Javier Martin <javier.martin@vista-silicon.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>

#घोषणा MEM2MEM_TEST_MODULE_NAME "mem2mem-deinterlace"

MODULE_DESCRIPTION("mem2mem device which supports deinterlacing using dmaengine");
MODULE_AUTHOR("Javier Martin <javier.martin@vista-silicon.com");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

अटल bool debug;
module_param(debug, bool, 0644);

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा MEM2MEM_CAPTURE	(1 << 0)
#घोषणा MEM2MEM_OUTPUT	(1 << 1)

#घोषणा MEM2MEM_NAME		"m2m-deinterlace"

#घोषणा dprपूर्णांकk(dev, fmt, arg...) \
	v4l2_dbg(1, debug, &dev->v4l2_dev, "%s: " fmt, __func__, ## arg)

काष्ठा deपूर्णांकerlace_fmt अणु
	u32	fourcc;
	/* Types the क्रमmat can be used क्रम */
	u32	types;
पूर्ण;

अटल काष्ठा deपूर्णांकerlace_fmt क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_YUV420,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.types	= MEM2MEM_CAPTURE | MEM2MEM_OUTPUT,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

/* Per-queue, driver-specअगरic निजी data */
काष्ठा deपूर्णांकerlace_q_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		sizeimage;
	काष्ठा deपूर्णांकerlace_fmt	*fmt;
	क्रमागत v4l2_field		field;
पूर्ण;

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

क्रमागत अणु
	YUV420_DMA_Y_ODD,
	YUV420_DMA_Y_EVEN,
	YUV420_DMA_U_ODD,
	YUV420_DMA_U_EVEN,
	YUV420_DMA_V_ODD,
	YUV420_DMA_V_EVEN,
	YUV420_DMA_Y_ODD_DOUBLING,
	YUV420_DMA_U_ODD_DOUBLING,
	YUV420_DMA_V_ODD_DOUBLING,
	YUYV_DMA_ODD,
	YUYV_DMA_EVEN,
	YUYV_DMA_EVEN_DOUBLING,
पूर्ण;

/* Source and destination queue data */
अटल काष्ठा deपूर्णांकerlace_q_data q_data[2];

अटल काष्ठा deपूर्णांकerlace_q_data *get_q_data(क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &q_data[V4L2_M2M_SRC];
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &q_data[V4L2_M2M_DST];
	शेष:
		BUG();
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा deपूर्णांकerlace_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &क्रमmats[k];
		अगर ((fmt->types & f->type) &&
			(fmt->fourcc == f->fmt.pix.pixelक्रमmat))
			अवरोध;
	पूर्ण

	अगर (k == NUM_FORMATS)
		वापस शून्य;

	वापस &क्रमmats[k];
पूर्ण

काष्ठा deपूर्णांकerlace_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;

	atomic_t		busy;
	काष्ठा mutex		dev_mutex;
	spinlock_t		irqlock;

	काष्ठा dma_chan		*dma_chan;

	काष्ठा v4l2_m2m_dev	*m2m_dev;
पूर्ण;

काष्ठा deपूर्णांकerlace_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा deपूर्णांकerlace_dev	*dev;

	/* Abort requested by m2m */
	पूर्णांक			पातing;
	क्रमागत v4l2_colorspace	colorspace;
	dma_cookie_t		cookie;
	काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt;
पूर्ण;

/*
 * mem2mem callbacks
 */
अटल पूर्णांक deपूर्णांकerlace_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	काष्ठा deपूर्णांकerlace_dev *pcdev = ctx->dev;

	अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) > 0 &&
	    v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) > 0 &&
	    !atomic_पढ़ो(&ctx->dev->busy)) अणु
		dprपूर्णांकk(pcdev, "Task ready\n");
		वापस 1;
	पूर्ण

	dprपूर्णांकk(pcdev, "Task not ready to run\n");

	वापस 0;
पूर्ण

अटल व्योम deपूर्णांकerlace_job_पात(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	काष्ठा deपूर्णांकerlace_dev *pcdev = ctx->dev;

	ctx->पातing = 1;

	dprपूर्णांकk(pcdev, "Aborting task\n");

	v4l2_m2m_job_finish(pcdev->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम dma_callback(व्योम *data)
अणु
	काष्ठा deपूर्णांकerlace_ctx *curr_ctx = data;
	काष्ठा deपूर्णांकerlace_dev *pcdev = curr_ctx->dev;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;

	atomic_set(&pcdev->busy, 0);

	src_vb = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;
	dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vb->flags |=
		src_vb->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vb->समयcode = src_vb->समयcode;

	v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_DONE);

	v4l2_m2m_job_finish(pcdev->m2m_dev, curr_ctx->fh.m2m_ctx);

	dprपूर्णांकk(pcdev, "dma transfers completed.\n");
पूर्ण

अटल व्योम deपूर्णांकerlace_issue_dma(काष्ठा deपूर्णांकerlace_ctx *ctx, पूर्णांक op,
				  पूर्णांक करो_callback)
अणु
	काष्ठा deपूर्णांकerlace_q_data *s_q_data;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा deपूर्णांकerlace_dev *pcdev = ctx->dev;
	काष्ठा dma_chan *chan = pcdev->dma_chan;
	काष्ठा dma_device *dmadev = chan->device;
	काष्ठा dma_async_tx_descriptor *tx;
	अचिन्हित पूर्णांक s_width, s_height;
	अचिन्हित पूर्णांक s_size;
	dma_addr_t p_in, p_out;
	क्रमागत dma_ctrl_flags flags;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	s_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_OUTPUT);
	s_width	= s_q_data->width;
	s_height = s_q_data->height;
	s_size = s_width * s_height;

	p_in = (dma_addr_t)vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	p_out = (dma_addr_t)vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf,
							  0);
	अगर (!p_in || !p_out) अणु
		v4l2_err(&pcdev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		वापस;
	पूर्ण

	चयन (op) अणु
	हाल YUV420_DMA_Y_ODD:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width;
		ctx->xt->sgl[0].icg = s_width;
		ctx->xt->src_start = p_in;
		ctx->xt->dst_start = p_out;
		अवरोध;
	हाल YUV420_DMA_Y_EVEN:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width;
		ctx->xt->sgl[0].icg = s_width;
		ctx->xt->src_start = p_in + s_size / 2;
		ctx->xt->dst_start = p_out + s_width;
		अवरोध;
	हाल YUV420_DMA_U_ODD:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + s_size;
		ctx->xt->dst_start = p_out + s_size;
		अवरोध;
	हाल YUV420_DMA_U_EVEN:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + (9 * s_size) / 8;
		ctx->xt->dst_start = p_out + s_size + s_width / 2;
		अवरोध;
	हाल YUV420_DMA_V_ODD:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + (5 * s_size) / 4;
		ctx->xt->dst_start = p_out + (5 * s_size) / 4;
		अवरोध;
	हाल YUV420_DMA_V_EVEN:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + (11 * s_size) / 8;
		ctx->xt->dst_start = p_out + (5 * s_size) / 4 + s_width / 2;
		अवरोध;
	हाल YUV420_DMA_Y_ODD_DOUBLING:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width;
		ctx->xt->sgl[0].icg = s_width;
		ctx->xt->src_start = p_in;
		ctx->xt->dst_start = p_out + s_width;
		अवरोध;
	हाल YUV420_DMA_U_ODD_DOUBLING:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + s_size;
		ctx->xt->dst_start = p_out + s_size + s_width / 2;
		अवरोध;
	हाल YUV420_DMA_V_ODD_DOUBLING:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgl[0].size = s_width / 2;
		ctx->xt->sgl[0].icg = s_width / 2;
		ctx->xt->src_start = p_in + (5 * s_size) / 4;
		ctx->xt->dst_start = p_out + (5 * s_size) / 4 + s_width / 2;
		अवरोध;
	हाल YUYV_DMA_ODD:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width * 2;
		ctx->xt->sgl[0].icg = s_width * 2;
		ctx->xt->src_start = p_in;
		ctx->xt->dst_start = p_out;
		अवरोध;
	हाल YUYV_DMA_EVEN:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width * 2;
		ctx->xt->sgl[0].icg = s_width * 2;
		ctx->xt->src_start = p_in + s_size;
		ctx->xt->dst_start = p_out + s_width * 2;
		अवरोध;
	हाल YUYV_DMA_EVEN_DOUBLING:
	शेष:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgl[0].size = s_width * 2;
		ctx->xt->sgl[0].icg = s_width * 2;
		ctx->xt->src_start = p_in;
		ctx->xt->dst_start = p_out + s_width * 2;
		अवरोध;
	पूर्ण

	/* Common parameters क्रम al transfers */
	ctx->xt->frame_size = 1;
	ctx->xt->dir = DMA_MEM_TO_MEM;
	ctx->xt->src_sgl = false;
	ctx->xt->dst_sgl = true;
	flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;

	tx = dmadev->device_prep_पूर्णांकerleaved_dma(chan, ctx->xt, flags);
	अगर (tx == शून्य) अणु
		v4l2_warn(&pcdev->v4l2_dev, "DMA interleaved prep error\n");
		वापस;
	पूर्ण

	अगर (करो_callback) अणु
		tx->callback = dma_callback;
		tx->callback_param = ctx;
	पूर्ण

	ctx->cookie = dmaengine_submit(tx);
	अगर (dma_submit_error(ctx->cookie)) अणु
		v4l2_warn(&pcdev->v4l2_dev,
			  "DMA submit error %d with src=0x%x dst=0x%x len=0x%x\n",
			  ctx->cookie, (अचिन्हित)p_in, (अचिन्हित)p_out,
			  s_size * 3/2);
		वापस;
	पूर्ण

	dma_async_issue_pending(chan);
पूर्ण

अटल व्योम deपूर्णांकerlace_device_run(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	काष्ठा deपूर्णांकerlace_q_data *dst_q_data;

	atomic_set(&ctx->dev->busy, 1);

	dprपूर्णांकk(ctx->dev, "%s: DMA try issue.\n", __func__);

	dst_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_CAPTURE);

	/*
	 * 4 possible field conversions are possible at the moment:
	 *  V4L2_FIELD_SEQ_TB --> V4L2_FIELD_INTERLACED_TB:
	 *	two separate fields in the same input buffer are पूर्णांकerlaced
	 *	in the output buffer using weaving. Top field comes first.
	 *  V4L2_FIELD_SEQ_TB --> V4L2_FIELD_NONE:
	 *	top field from the input buffer is copied to the output buffer
	 *	using line करोubling. Bottom field from the input buffer is discarded.
	 * V4L2_FIELD_SEQ_BT --> V4L2_FIELD_INTERLACED_BT:
	 *	two separate fields in the same input buffer are पूर्णांकerlaced
	 *	in the output buffer using weaving. Bottom field comes first.
	 * V4L2_FIELD_SEQ_BT --> V4L2_FIELD_NONE:
	 *	bottom field from the input buffer is copied to the output buffer
	 *	using line करोubling. Top field from the input buffer is discarded.
	 */
	चयन (dst_q_data->fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
		चयन (dst_q_data->field) अणु
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
			dprपूर्णांकk(ctx->dev, "%s: yuv420 interlaced tb.\n",
				__func__);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_Y_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_Y_EVEN, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_U_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_U_EVEN, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_V_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_V_EVEN, 1);
			अवरोध;
		हाल V4L2_FIELD_NONE:
		शेष:
			dprपूर्णांकk(ctx->dev, "%s: yuv420 interlaced line doubling.\n",
				__func__);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_Y_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_Y_ODD_DOUBLING, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_U_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_U_ODD_DOUBLING, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_V_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUV420_DMA_V_ODD_DOUBLING, 1);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		चयन (dst_q_data->field) अणु
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
			dprपूर्णांकk(ctx->dev, "%s: yuyv interlaced_tb.\n",
				__func__);
			deपूर्णांकerlace_issue_dma(ctx, YUYV_DMA_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUYV_DMA_EVEN, 1);
			अवरोध;
		हाल V4L2_FIELD_NONE:
		शेष:
			dprपूर्णांकk(ctx->dev, "%s: yuyv interlaced line doubling.\n",
				__func__);
			deपूर्णांकerlace_issue_dma(ctx, YUYV_DMA_ODD, 0);
			deपूर्णांकerlace_issue_dma(ctx, YUYV_DMA_EVEN_DOUBLING, 1);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	dprपूर्णांकk(ctx->dev, "%s: DMA issue done.\n", __func__);
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MEM2MEM_NAME, माप(cap->driver));
	strscpy(cap->card, MEM2MEM_NAME, माप(cap->card));
	strscpy(cap->bus_info, MEM2MEM_NAME, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num;
	काष्ठा deपूर्णांकerlace_fmt *fmt;

	num = 0;

	क्रम (i = 0; i < NUM_FORMATS; ++i) अणु
		अगर (क्रमmats[i].types & type) अणु
			/* index-th क्रमmat of type type found ? */
			अगर (num == f->index)
				अवरोध;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index */
			++num;
		पूर्ण
	पूर्ण

	अगर (i < NUM_FORMATS) अणु
		/* Format found */
		fmt = &क्रमmats[i];
		f->pixelक्रमmat = fmt->fourcc;
		वापस 0;
	पूर्ण

	/* Format not found */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_CAPTURE);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_OUTPUT);
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा deपूर्णांकerlace_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा deपूर्णांकerlace_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= q_data->field;
	f->fmt.pix.pixelक्रमmat	= q_data->fmt->fourcc;

	चयन (q_data->fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
		f->fmt.pix.bytesperline = q_data->width * 3 / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		f->fmt.pix.bytesperline = q_data->width * 2;
	पूर्ण

	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.colorspace	= ctx->colorspace;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f, काष्ठा deपूर्णांकerlace_fmt *fmt)
अणु
	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 3 / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	पूर्ण
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_fmt *fmt;
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;

	fmt = find_क्रमmat(f);
	अगर (!fmt || !(fmt->types & MEM2MEM_CAPTURE))
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV420;

	f->fmt.pix.colorspace = ctx->colorspace;

	अगर (f->fmt.pix.field != V4L2_FIELD_INTERLACED_TB &&
	    f->fmt.pix.field != V4L2_FIELD_INTERLACED_BT &&
	    f->fmt.pix.field != V4L2_FIELD_NONE)
		f->fmt.pix.field = V4L2_FIELD_INTERLACED_TB;

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_fmt *fmt;

	fmt = find_क्रमmat(f);
	अगर (!fmt || !(fmt->types & MEM2MEM_OUTPUT))
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV420;

	अगर (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	अगर (f->fmt.pix.field != V4L2_FIELD_SEQ_TB &&
	    f->fmt.pix.field != V4L2_FIELD_SEQ_BT)
		f->fmt.pix.field = V4L2_FIELD_SEQ_TB;

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा deपूर्णांकerlace_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_q_data *q_data;
	काष्ठा vb2_queue *vq;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(f->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	q_data->fmt = find_क्रमmat(f);
	अगर (!q_data->fmt) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Couldn't set format type %d, wxh: %dx%d. fmt: %d, field: %d\n",
			f->type, f->fmt.pix.width, f->fmt.pix.height,
			f->fmt.pix.pixelक्रमmat, f->fmt.pix.field);
		वापस -EINVAL;
	पूर्ण

	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	q_data->field		= f->fmt.pix.field;

	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 3 / 2;
		q_data->sizeimage = (q_data->width * q_data->height * 3) / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
		q_data->sizeimage = q_data->width * q_data->height * 2;
	पूर्ण

	dprपूर्णांकk(ctx->dev,
		"Setting format for type %d, wxh: %dx%d, fmt: %d, field: %d\n",
		f->type, q_data->width, q_data->height, q_data->fmt->fourcc,
		q_data->field);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;
	वापस vidioc_s_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	ret = vidioc_s_fmt(priv, f);
	अगर (!ret)
		ctx->colorspace = f->fmt.pix.colorspace;

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *priv,
			   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा deपूर्णांकerlace_q_data *s_q_data, *d_q_data;
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;

	s_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_OUTPUT);
	d_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_CAPTURE);

	/* Check that src and dst queues have the same pix क्रमmat */
	अगर (s_q_data->fmt->fourcc != d_q_data->fmt->fourcc) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst formats don't match.\n");
		वापस -EINVAL;
	पूर्ण

	/* Check that input and output deपूर्णांकerlacing types are compatible */
	चयन (s_q_data->field) अणु
	हाल V4L2_FIELD_SEQ_BT:
		अगर (d_q_data->field != V4L2_FIELD_NONE &&
			d_q_data->field != V4L2_FIELD_INTERLACED_BT) अणु
			v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst field conversion [(%d)->(%d)] not supported.\n",
				s_q_data->field, d_q_data->field);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		अगर (d_q_data->field != V4L2_FIELD_NONE &&
			d_q_data->field != V4L2_FIELD_INTERLACED_TB) अणु
			v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst field conversion [(%d)->(%d)] not supported.\n",
				s_q_data->field, d_q_data->field);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops deपूर्णांकerlace_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out	= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= vidioc_s_fmt_vid_out,

	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf		= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf		= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon	= vidioc_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,
पूर्ण;


/*
 * Queue operations
 */
काष्ठा vb2_dc_conf अणु
	काष्ठा device           *dev;
पूर्ण;

अटल पूर्णांक deपूर्णांकerlace_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा deपूर्णांकerlace_q_data *q_data;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(vq->type);

	चयन (q_data->fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
		size = q_data->width * q_data->height * 3 / 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		size = q_data->width * q_data->height * 2;
	पूर्ण

	*nplanes = 1;
	*nbuffers = count;
	sizes[0] = size;

	dprपूर्णांकk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा deपूर्णांकerlace_q_data *q_data;

	dprपूर्णांकk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(vb->vb2_queue->type);

	अगर (vb2_plane_size(vb, 0) < q_data->sizeimage) अणु
		dprपूर्णांकk(ctx->dev, "%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), (दीर्घ)q_data->sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, q_data->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम deपूर्णांकerlace_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल स्थिर काष्ठा vb2_ops deपूर्णांकerlace_qops = अणु
	.queue_setup	 = deपूर्णांकerlace_queue_setup,
	.buf_prepare	 = deपूर्णांकerlace_buf_prepare,
	.buf_queue	 = deपूर्णांकerlace_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &deपूर्णांकerlace_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->dev = ctx->dev->v4l2_dev.dev;
	src_vq->lock = &ctx->dev->dev_mutex;
	q_data[V4L2_M2M_SRC].fmt = &क्रमmats[0];
	q_data[V4L2_M2M_SRC].width = 640;
	q_data[V4L2_M2M_SRC].height = 480;
	q_data[V4L2_M2M_SRC].sizeimage = (640 * 480 * 3) / 2;
	q_data[V4L2_M2M_SRC].field = V4L2_FIELD_SEQ_TB;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &deपूर्णांकerlace_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->dev = ctx->dev->v4l2_dev.dev;
	dst_vq->lock = &ctx->dev->dev_mutex;
	q_data[V4L2_M2M_DST].fmt = &क्रमmats[0];
	q_data[V4L2_M2M_DST].width = 640;
	q_data[V4L2_M2M_DST].height = 480;
	q_data[V4L2_M2M_DST].sizeimage = (640 * 480 * 3) / 2;
	q_data[V4L2_M2M_SRC].field = V4L2_FIELD_INTERLACED_TB;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * File operations
 */
अटल पूर्णांक deपूर्णांकerlace_खोलो(काष्ठा file *file)
अणु
	काष्ठा deपूर्णांकerlace_dev *pcdev = video_drvdata(file);
	काष्ठा deपूर्णांकerlace_ctx *ctx = शून्य;

	ctx = kzalloc(माप *ctx, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = pcdev;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(pcdev->m2m_dev, ctx, &queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		पूर्णांक ret = PTR_ERR(ctx->fh.m2m_ctx);

		kमुक्त(ctx);
		वापस ret;
	पूर्ण

	ctx->xt = kzalloc(माप(काष्ठा dma_पूर्णांकerleaved_ढाँचा) +
				माप(काष्ठा data_chunk), GFP_KERNEL);
	अगर (!ctx->xt) अणु
		kमुक्त(ctx);
		वापस -ENOMEM;
	पूर्ण

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	v4l2_fh_add(&ctx->fh);

	dprपूर्णांकk(pcdev, "Created instance %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_release(काष्ठा file *file)
अणु
	काष्ठा deपूर्णांकerlace_dev *pcdev = video_drvdata(file);
	काष्ठा deपूर्णांकerlace_ctx *ctx = file->निजी_data;

	dprपूर्णांकk(pcdev, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	kमुक्त(ctx->xt);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations deपूर्णांकerlace_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= deपूर्णांकerlace_खोलो,
	.release	= deपूर्णांकerlace_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device deपूर्णांकerlace_videodev = अणु
	.name		= MEM2MEM_NAME,
	.fops		= &deपूर्णांकerlace_fops,
	.ioctl_ops	= &deपूर्णांकerlace_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
	.vfl_dir	= VFL_सूची_M2M,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= deपूर्णांकerlace_device_run,
	.job_पढ़ोy	= deपूर्णांकerlace_job_पढ़ोy,
	.job_पात	= deपूर्णांकerlace_job_पात,
पूर्ण;

अटल पूर्णांक deपूर्णांकerlace_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा deपूर्णांकerlace_dev *pcdev;
	काष्ठा video_device *vfd;
	dma_cap_mask_t mask;
	पूर्णांक ret = 0;

	pcdev = devm_kzalloc(&pdev->dev, माप(*pcdev), GFP_KERNEL);
	अगर (!pcdev)
		वापस -ENOMEM;

	spin_lock_init(&pcdev->irqlock);

	dma_cap_zero(mask);
	dma_cap_set(DMA_INTERLEAVE, mask);
	pcdev->dma_chan = dma_request_channel(mask, शून्य, pcdev);
	अगर (!pcdev->dma_chan)
		वापस -ENODEV;

	अगर (!dma_has_cap(DMA_INTERLEAVE, pcdev->dma_chan->device->cap_mask)) अणु
		dev_err(&pdev->dev, "DMA does not support INTERLEAVE\n");
		ret = -ENODEV;
		जाओ rel_dma;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &pcdev->v4l2_dev);
	अगर (ret)
		जाओ rel_dma;

	atomic_set(&pcdev->busy, 0);
	mutex_init(&pcdev->dev_mutex);

	vfd = &pcdev->vfd;
	*vfd = deपूर्णांकerlace_videodev;
	vfd->lock = &pcdev->dev_mutex;
	vfd->v4l2_dev = &pcdev->v4l2_dev;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&pcdev->v4l2_dev, "Failed to register video device\n");
		जाओ unreg_dev;
	पूर्ण

	video_set_drvdata(vfd, pcdev);
	v4l2_info(&pcdev->v4l2_dev, MEM2MEM_TEST_MODULE_NAME
			" Device registered as /dev/video%d\n", vfd->num);

	platक्रमm_set_drvdata(pdev, pcdev);

	pcdev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(pcdev->m2m_dev)) अणु
		v4l2_err(&pcdev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(pcdev->m2m_dev);
		जाओ err_m2m;
	पूर्ण

	वापस 0;

err_m2m:
	video_unरेजिस्टर_device(&pcdev->vfd);
unreg_dev:
	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);
rel_dma:
	dma_release_channel(pcdev->dma_chan);

	वापस ret;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा deपूर्णांकerlace_dev *pcdev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&pcdev->v4l2_dev, "Removing " MEM2MEM_TEST_MODULE_NAME);
	v4l2_m2m_release(pcdev->m2m_dev);
	video_unरेजिस्टर_device(&pcdev->vfd);
	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);
	dma_release_channel(pcdev->dma_chan);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver deपूर्णांकerlace_pdrv = अणु
	.probe		= deपूर्णांकerlace_probe,
	.हटाओ		= deपूर्णांकerlace_हटाओ,
	.driver		= अणु
		.name	= MEM2MEM_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(deपूर्णांकerlace_pdrv);

