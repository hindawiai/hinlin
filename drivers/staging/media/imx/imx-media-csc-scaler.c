<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i.MX IPUv3 IC PP mem2mem CSC/Scaler driver
 *
 * Copyright (C) 2011 Pengutronix, Sascha Hauer
 * Copyright (C) 2018 Pengutronix, Philipp Zabel
 */
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <video/imx-ipu-v3.h>
#समावेश <video/imx-ipu-image-convert.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "imx-media.h"

#घोषणा fh_to_ctx(__fh)	container_of(__fh, काष्ठा ipu_csc_scaler_ctx, fh)

#घोषणा IMX_CSC_SCALER_NAME "imx-csc-scaler"

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

काष्ठा ipu_csc_scaler_priv अणु
	काष्ठा imx_media_video_dev	vdev;

	काष्ठा v4l2_m2m_dev		*m2m_dev;
	काष्ठा device			*dev;

	काष्ठा imx_media_dev		*md;

	काष्ठा mutex			mutex;	/* mem2mem device mutex */
पूर्ण;

#घोषणा vdev_to_priv(v) container_of(v, काष्ठा ipu_csc_scaler_priv, vdev)

/* Per-queue, driver-specअगरic निजी data */
काष्ठा ipu_csc_scaler_q_data अणु
	काष्ठा v4l2_pix_क्रमmat		cur_fmt;
	काष्ठा v4l2_rect		rect;
पूर्ण;

काष्ठा ipu_csc_scaler_ctx अणु
	काष्ठा ipu_csc_scaler_priv	*priv;

	काष्ठा v4l2_fh			fh;
	काष्ठा ipu_csc_scaler_q_data	q_data[2];
	काष्ठा ipu_image_convert_ctx	*icc;

	काष्ठा v4l2_ctrl_handler	ctrl_hdlr;
	पूर्णांक				rotate;
	bool				hflip;
	bool				vflip;
	क्रमागत ipu_rotate_mode		rot_mode;
	अचिन्हित पूर्णांक			sequence;
पूर्ण;

अटल काष्ठा ipu_csc_scaler_q_data *get_q_data(काष्ठा ipu_csc_scaler_ctx *ctx,
						क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->q_data[V4L2_M2M_SRC];
	अन्यथा
		वापस &ctx->q_data[V4L2_M2M_DST];
पूर्ण

/*
 * mem2mem callbacks
 */

अटल व्योम job_पात(व्योम *_ctx)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = _ctx;

	अगर (ctx->icc)
		ipu_image_convert_पात(ctx->icc);
पूर्ण

अटल व्योम ipu_ic_pp_complete(काष्ठा ipu_image_convert_run *run, व्योम *_ctx)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = _ctx;
	काष्ठा ipu_csc_scaler_priv *priv = ctx->priv;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, true);

	src_buf->sequence = ctx->sequence++;
	dst_buf->sequence = src_buf->sequence;

	v4l2_m2m_buf_करोne(src_buf, run->status ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_करोne(dst_buf, run->status ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);

	v4l2_m2m_job_finish(priv->m2m_dev, ctx->fh.m2m_ctx);
	kमुक्त(run);
पूर्ण

अटल व्योम device_run(व्योम *_ctx)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = _ctx;
	काष्ठा ipu_csc_scaler_priv *priv = ctx->priv;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा ipu_image_convert_run *run;
	पूर्णांक ret;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	run = kzalloc(माप(*run), GFP_KERNEL);
	अगर (!run)
		जाओ err;

	run->ctx = ctx->icc;
	run->in_phys = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	run->out_phys = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);

	ret = ipu_image_convert_queue(run);
	अगर (ret < 0) अणु
		v4l2_err(ctx->priv->vdev.vfd->v4l2_dev,
			 "%s: failed to queue: %d\n", __func__, ret);
		जाओ err;
	पूर्ण

	वापस;

err:
	v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_job_finish(priv->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

/*
 * Video ioctls
 */
अटल पूर्णांक ipu_csc_scaler_querycap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, IMX_CSC_SCALER_NAME, माप(cap->driver));
	strscpy(cap->card, IMX_CSC_SCALER_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", IMX_CSC_SCALER_NAME);

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_क्रमागत_fmt(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	u32 fourcc;
	पूर्णांक ret;

	ret = imx_media_क्रमागत_pixel_क्रमmats(&fourcc, f->index,
					   PIXFMT_SEL_YUV_RGB, 0);
	अगर (ret)
		वापस ret;

	f->pixelक्रमmat = fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_g_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	काष्ठा ipu_csc_scaler_q_data *q_data;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix = q_data->cur_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_try_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	काष्ठा ipu_csc_scaler_q_data *q_data = get_q_data(ctx, f->type);
	काष्ठा ipu_image test_in, test_out;
	क्रमागत v4l2_field field;

	field = f->fmt.pix.field;
	अगर (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	अन्यथा अगर (field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		काष्ठा ipu_csc_scaler_q_data *q_data_in =
			get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

		test_out.pix = f->fmt.pix;
		test_in.pix = q_data_in->cur_fmt;
	पूर्ण अन्यथा अणु
		काष्ठा ipu_csc_scaler_q_data *q_data_out =
			get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

		test_in.pix = f->fmt.pix;
		test_out.pix = q_data_out->cur_fmt;
	पूर्ण

	ipu_image_convert_adjust(&test_in, &test_out, ctx->rot_mode);

	f->fmt.pix = (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ?
		test_out.pix : test_in.pix;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		f->fmt.pix.colorspace = q_data->cur_fmt.colorspace;
		f->fmt.pix.ycbcr_enc = q_data->cur_fmt.ycbcr_enc;
		f->fmt.pix.xfer_func = q_data->cur_fmt.xfer_func;
		f->fmt.pix.quantization = q_data->cur_fmt.quantization;
	पूर्ण अन्यथा अगर (f->fmt.pix.colorspace == V4L2_COLORSPACE_DEFAULT) अणु
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
		f->fmt.pix.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		f->fmt.pix.xfer_func = V4L2_XFER_FUNC_DEFAULT;
		f->fmt.pix.quantization = V4L2_QUANTIZATION_DEFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_s_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा ipu_csc_scaler_q_data *q_data;
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(ctx->priv->vdev.vfd->v4l2_dev, "%s: queue busy\n",
			 __func__);
		वापस -EBUSY;
	पूर्ण

	q_data = get_q_data(ctx, f->type);

	ret = ipu_csc_scaler_try_fmt(file, priv, f);
	अगर (ret < 0)
		वापस ret;

	q_data->cur_fmt.width = f->fmt.pix.width;
	q_data->cur_fmt.height = f->fmt.pix.height;
	q_data->cur_fmt.pixelक्रमmat = f->fmt.pix.pixelक्रमmat;
	q_data->cur_fmt.field = f->fmt.pix.field;
	q_data->cur_fmt.bytesperline = f->fmt.pix.bytesperline;
	q_data->cur_fmt.sizeimage = f->fmt.pix.sizeimage;

	/* Reset cropping/composing rectangle */
	q_data->rect.left = 0;
	q_data->rect.top = 0;
	q_data->rect.width = q_data->cur_fmt.width;
	q_data->rect.height = q_data->cur_fmt.height;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		/* Set colorimetry on the output queue */
		q_data->cur_fmt.colorspace = f->fmt.pix.colorspace;
		q_data->cur_fmt.ycbcr_enc = f->fmt.pix.ycbcr_enc;
		q_data->cur_fmt.xfer_func = f->fmt.pix.xfer_func;
		q_data->cur_fmt.quantization = f->fmt.pix.quantization;
		/* Propagate colorimetry to the capture queue */
		q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		q_data->cur_fmt.colorspace = f->fmt.pix.colorspace;
		q_data->cur_fmt.ycbcr_enc = f->fmt.pix.ycbcr_enc;
		q_data->cur_fmt.xfer_func = f->fmt.pix.xfer_func;
		q_data->cur_fmt.quantization = f->fmt.pix.quantization;
	पूर्ण

	/*
	 * TODO: Setting colorimetry on the capture queue is currently not
	 * supported by the V4L2 API
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_g_selection(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_selection *s)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	काष्ठा ipu_csc_scaler_q_data *q_data;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (s->target == V4L2_SEL_TGT_CROP ||
	    s->target == V4L2_SEL_TGT_COMPOSE) अणु
		s->r = q_data->rect;
	पूर्ण अन्यथा अणु
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = q_data->cur_fmt.width;
		s->r.height = q_data->cur_fmt.height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_s_selection(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_selection *s)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	काष्ठा ipu_csc_scaler_q_data *q_data;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	q_data = get_q_data(ctx, s->type);

	/* The input's frame width to the IC must be a multiple of 8 pixels
	 * When perक्रमming resizing the frame width must be multiple of burst
	 * size - 8 or 16 pixels as defined by CB#_BURST_16 parameter.
	 */
	अगर (s->flags & V4L2_SEL_FLAG_GE)
		s->r.width = round_up(s->r.width, 8);
	अगर (s->flags & V4L2_SEL_FLAG_LE)
		s->r.width = round_करोwn(s->r.width, 8);
	s->r.width = clamp_t(अचिन्हित पूर्णांक, s->r.width, 8,
			     round_करोwn(q_data->cur_fmt.width, 8));
	s->r.height = clamp_t(अचिन्हित पूर्णांक, s->r.height, 1,
			      q_data->cur_fmt.height);
	s->r.left = clamp_t(अचिन्हित पूर्णांक, s->r.left, 0,
			    q_data->cur_fmt.width - s->r.width);
	s->r.top = clamp_t(अचिन्हित पूर्णांक, s->r.top, 0,
			   q_data->cur_fmt.height - s->r.height);

	/* V4L2_SEL_FLAG_KEEP_CONFIG is only valid क्रम subdevices */
	q_data->rect = s->r;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops ipu_csc_scaler_ioctl_ops = अणु
	.vidioc_querycap		= ipu_csc_scaler_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= ipu_csc_scaler_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap		= ipu_csc_scaler_g_fmt,
	.vidioc_try_fmt_vid_cap		= ipu_csc_scaler_try_fmt,
	.vidioc_s_fmt_vid_cap		= ipu_csc_scaler_s_fmt,

	.vidioc_क्रमागत_fmt_vid_out	= ipu_csc_scaler_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out		= ipu_csc_scaler_g_fmt,
	.vidioc_try_fmt_vid_out		= ipu_csc_scaler_try_fmt,
	.vidioc_s_fmt_vid_out		= ipu_csc_scaler_s_fmt,

	.vidioc_g_selection		= ipu_csc_scaler_g_selection,
	.vidioc_s_selection		= ipu_csc_scaler_s_selection,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,

	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/*
 * Queue operations
 */

अटल पूर्णांक ipu_csc_scaler_queue_setup(काष्ठा vb2_queue *vq,
				      अचिन्हित पूर्णांक *nbuffers,
				      अचिन्हित पूर्णांक *nplanes,
				      अचिन्हित पूर्णांक sizes[],
				      काष्ठा device *alloc_devs[])
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा ipu_csc_scaler_q_data *q_data;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->cur_fmt.sizeimage;

	*nbuffers = count;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dev_dbg(ctx->priv->dev, "get %d buffer(s) of size %d each.\n",
		count, size);

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा ipu_csc_scaler_q_data *q_data;
	अचिन्हित दीर्घ size;

	dev_dbg(ctx->priv->dev, "type: %d\n", vq->type);

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dev_dbg(ctx->priv->dev, "%s: field isn't supported\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	q_data = get_q_data(ctx, vq->type);
	size = q_data->cur_fmt.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_dbg(ctx->priv->dev,
			"%s: data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम ipu_csc_scaler_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, to_vb2_v4l2_buffer(vb));
पूर्ण

अटल व्योम ipu_image_from_q_data(काष्ठा ipu_image *im,
				  काष्ठा ipu_csc_scaler_q_data *q_data)
अणु
	काष्ठा v4l2_pix_क्रमmat *fmt = &q_data->cur_fmt;

	im->pix = *fmt;
	अगर (fmt->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
		im->pix.ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	अगर (fmt->quantization == V4L2_QUANTIZATION_DEFAULT)
		im->pix.ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	im->rect = q_data->rect;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_start_streaming(काष्ठा vb2_queue *q,
					  अचिन्हित पूर्णांक count)
अणु
	स्थिर क्रमागत ipu_ic_task ic_task = IC_TASK_POST_PROCESSOR;
	काष्ठा ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा ipu_csc_scaler_priv *priv = ctx->priv;
	काष्ठा ipu_soc *ipu = priv->md->ipu[0];
	काष्ठा ipu_csc_scaler_q_data *q_data;
	काष्ठा vb2_queue *other_q;
	काष्ठा ipu_image in, out;

	other_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
				  (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ?
				  V4L2_BUF_TYPE_VIDEO_OUTPUT :
				  V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (!vb2_is_streaming(other_q))
		वापस 0;

	अगर (ctx->icc) अणु
		v4l2_warn(ctx->priv->vdev.vfd->v4l2_dev, "removing old ICC\n");
		ipu_image_convert_unprepare(ctx->icc);
	पूर्ण

	q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	ipu_image_from_q_data(&in, q_data);

	q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	ipu_image_from_q_data(&out, q_data);

	ctx->icc = ipu_image_convert_prepare(ipu, ic_task, &in, &out,
					     ctx->rot_mode,
					     ipu_ic_pp_complete, ctx);
	अगर (IS_ERR(ctx->icc)) अणु
		काष्ठा vb2_v4l2_buffer *buf;
		पूर्णांक ret = PTR_ERR(ctx->icc);

		ctx->icc = शून्य;
		v4l2_err(ctx->priv->vdev.vfd->v4l2_dev, "%s: error %d\n",
			 __func__, ret);
		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_QUEUED);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipu_csc_scaler_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *buf;

	अगर (ctx->icc) अणु
		ipu_image_convert_unprepare(ctx->icc);
		ctx->icc = शून्य;
	पूर्ण

	ctx->sequence = 0;

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops ipu_csc_scaler_qops = अणु
	.queue_setup		= ipu_csc_scaler_queue_setup,
	.buf_prepare		= ipu_csc_scaler_buf_prepare,
	.buf_queue		= ipu_csc_scaler_buf_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.start_streaming	= ipu_csc_scaler_start_streaming,
	.stop_streaming		= ipu_csc_scaler_stop_streaming,
पूर्ण;

अटल पूर्णांक ipu_csc_scaler_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
				     काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = priv;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &ipu_csc_scaler_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->priv->mutex;
	src_vq->dev = ctx->priv->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &ipu_csc_scaler_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->priv->mutex;
	dst_vq->dev = ctx->priv->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक ipu_csc_scaler_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ipu_csc_scaler_ctx *ctx = container_of(ctrl->handler,
						      काष्ठा ipu_csc_scaler_ctx,
						      ctrl_hdlr);
	क्रमागत ipu_rotate_mode rot_mode;
	पूर्णांक rotate;
	bool hflip, vflip;
	पूर्णांक ret = 0;

	rotate = ctx->rotate;
	hflip = ctx->hflip;
	vflip = ctx->vflip;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		hflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		vflip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_ROTATE:
		rotate = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = ipu_degrees_to_rot_mode(&rot_mode, rotate, hflip, vflip);
	अगर (ret)
		वापस ret;

	अगर (rot_mode != ctx->rot_mode) अणु
		काष्ठा v4l2_pix_क्रमmat *in_fmt, *out_fmt;
		काष्ठा ipu_image test_in, test_out;

		in_fmt = &ctx->q_data[V4L2_M2M_SRC].cur_fmt;
		out_fmt = &ctx->q_data[V4L2_M2M_DST].cur_fmt;

		test_in.pix = *in_fmt;
		test_out.pix = *out_fmt;

		अगर (ipu_rot_mode_is_irt(rot_mode) !=
		    ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
			/* Switch width & height to keep aspect ratio पूर्णांकact */
			test_out.pix.width = out_fmt->height;
			test_out.pix.height = out_fmt->width;
		पूर्ण

		ipu_image_convert_adjust(&test_in, &test_out, ctx->rot_mode);

		/* Check अगर output क्रमmat needs to be changed */
		अगर (test_in.pix.width != in_fmt->width ||
		    test_in.pix.height != in_fmt->height ||
		    test_in.pix.bytesperline != in_fmt->bytesperline ||
		    test_in.pix.sizeimage != in_fmt->sizeimage) अणु
			काष्ठा vb2_queue *out_q;

			out_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
						V4L2_BUF_TYPE_VIDEO_OUTPUT);
			अगर (vb2_is_busy(out_q))
				वापस -EBUSY;
		पूर्ण

		/* Check अगर capture क्रमmat needs to be changed */
		अगर (test_out.pix.width != out_fmt->width ||
		    test_out.pix.height != out_fmt->height ||
		    test_out.pix.bytesperline != out_fmt->bytesperline ||
		    test_out.pix.sizeimage != out_fmt->sizeimage) अणु
			काष्ठा vb2_queue *cap_q;

			cap_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
						V4L2_BUF_TYPE_VIDEO_CAPTURE);
			अगर (vb2_is_busy(cap_q))
				वापस -EBUSY;
		पूर्ण

		*in_fmt = test_in.pix;
		*out_fmt = test_out.pix;

		ctx->rot_mode = rot_mode;
		ctx->rotate = rotate;
		ctx->hflip = hflip;
		ctx->vflip = vflip;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ipu_csc_scaler_ctrl_ops = अणु
	.s_ctrl = ipu_csc_scaler_s_ctrl,
पूर्ण;

अटल पूर्णांक ipu_csc_scaler_init_controls(काष्ठा ipu_csc_scaler_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl_handler *hdlr = &ctx->ctrl_hdlr;

	v4l2_ctrl_handler_init(hdlr, 3);

	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_HFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_VFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_ROTATE,
			  0, 270, 90, 0);

	अगर (hdlr->error) अणु
		v4l2_ctrl_handler_मुक्त(hdlr);
		वापस hdlr->error;
	पूर्ण

	v4l2_ctrl_handler_setup(hdlr);
	वापस 0;
पूर्ण

#घोषणा DEFAULT_WIDTH	720
#घोषणा DEFAULT_HEIGHT	576
अटल स्थिर काष्ठा ipu_csc_scaler_q_data ipu_csc_scaler_q_data_शेष = अणु
	.cur_fmt = अणु
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
		.pixelक्रमmat = V4L2_PIX_FMT_YUV420,
		.field = V4L2_FIELD_NONE,
		.bytesperline = DEFAULT_WIDTH,
		.sizeimage = DEFAULT_WIDTH * DEFAULT_HEIGHT * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
	पूर्ण,
	.rect = अणु
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	पूर्ण,
पूर्ण;

/*
 * File operations
 */
अटल पूर्णांक ipu_csc_scaler_खोलो(काष्ठा file *file)
अणु
	काष्ठा ipu_csc_scaler_priv *priv = video_drvdata(file);
	काष्ठा ipu_csc_scaler_ctx *ctx = शून्य;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->rot_mode = IPU_ROTATE_NONE;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);
	ctx->priv = priv;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(priv->m2m_dev, ctx,
					    &ipu_csc_scaler_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_ctx;
	पूर्ण

	ret = ipu_csc_scaler_init_controls(ctx);
	अगर (ret)
		जाओ err_ctrls;

	ctx->fh.ctrl_handler = &ctx->ctrl_hdlr;

	ctx->q_data[V4L2_M2M_SRC] = ipu_csc_scaler_q_data_शेष;
	ctx->q_data[V4L2_M2M_DST] = ipu_csc_scaler_q_data_शेष;

	dev_dbg(priv->dev, "Created instance %p, m2m_ctx: %p\n", ctx,
		ctx->fh.m2m_ctx);

	वापस 0;

err_ctrls:
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
err_ctx:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक ipu_csc_scaler_release(काष्ठा file *file)
अणु
	काष्ठा ipu_csc_scaler_priv *priv = video_drvdata(file);
	काष्ठा ipu_csc_scaler_ctx *ctx = fh_to_ctx(file->निजी_data);

	dev_dbg(priv->dev, "Releasing instance %p\n", ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations ipu_csc_scaler_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= ipu_csc_scaler_खोलो,
	.release	= ipu_csc_scaler_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= device_run,
	.job_पात	= job_पात,
पूर्ण;

अटल व्योम ipu_csc_scaler_video_device_release(काष्ठा video_device *vdev)
अणु
	काष्ठा ipu_csc_scaler_priv *priv = video_get_drvdata(vdev);

	v4l2_m2m_release(priv->m2m_dev);
	video_device_release(vdev);
	kमुक्त(priv);
पूर्ण

अटल स्थिर काष्ठा video_device ipu_csc_scaler_videodev_ढाँचा = अणु
	.name		= "ipu_ic_pp csc/scaler",
	.fops		= &ipu_csc_scaler_fops,
	.ioctl_ops	= &ipu_csc_scaler_ioctl_ops,
	.minor		= -1,
	.release	= ipu_csc_scaler_video_device_release,
	.vfl_dir	= VFL_सूची_M2M,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

पूर्णांक imx_media_csc_scaler_device_रेजिस्टर(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा ipu_csc_scaler_priv *priv = vdev_to_priv(vdev);
	काष्ठा video_device *vfd = vdev->vfd;
	पूर्णांक ret;

	vfd->v4l2_dev = &priv->md->v4l2_dev;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(vfd->v4l2_dev, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	v4l2_info(vfd->v4l2_dev, "Registered %s as /dev/%s\n", vfd->name,
		  video_device_node_name(vfd));

	वापस 0;
पूर्ण

व्योम imx_media_csc_scaler_device_unरेजिस्टर(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा ipu_csc_scaler_priv *priv = vdev_to_priv(vdev);
	काष्ठा video_device *vfd = priv->vdev.vfd;

	video_unरेजिस्टर_device(vfd);
पूर्ण

काष्ठा imx_media_video_dev *
imx_media_csc_scaler_device_init(काष्ठा imx_media_dev *md)
अणु
	काष्ठा ipu_csc_scaler_priv *priv;
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->md = md;
	priv->dev = md->md.dev;

	mutex_init(&priv->mutex);

	vfd = video_device_alloc();
	अगर (!vfd) अणु
		ret = -ENOMEM;
		जाओ err_vfd;
	पूर्ण

	*vfd = ipu_csc_scaler_videodev_ढाँचा;
	vfd->lock = &priv->mutex;
	priv->vdev.vfd = vfd;

	INIT_LIST_HEAD(&priv->vdev.list);

	video_set_drvdata(vfd, priv);

	priv->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(priv->m2m_dev)) अणु
		ret = PTR_ERR(priv->m2m_dev);
		v4l2_err(&md->v4l2_dev, "Failed to init mem2mem device: %d\n",
			 ret);
		जाओ err_m2m;
	पूर्ण

	वापस &priv->vdev;

err_m2m:
	video_set_drvdata(vfd, शून्य);
err_vfd:
	kमुक्त(priv);
	वापस ERR_PTR(ret);
पूर्ण

MODULE_DESCRIPTION("i.MX IPUv3 mem2mem scaler/CSC driver");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_LICENSE("GPL");
