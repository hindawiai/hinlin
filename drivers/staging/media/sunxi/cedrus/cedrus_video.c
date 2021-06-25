<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2016 Florent Revest <florent.revest@मुक्त-electrons.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 *
 * Based on the vim2m driver, that is:
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "cedrus.h"
#समावेश "cedrus_video.h"
#समावेश "cedrus_dec.h"
#समावेश "cedrus_hw.h"

#घोषणा CEDRUS_DECODE_SRC	BIT(0)
#घोषणा CEDRUS_DECODE_DST	BIT(1)

#घोषणा CEDRUS_MIN_WIDTH	16U
#घोषणा CEDRUS_MIN_HEIGHT	16U
#घोषणा CEDRUS_MAX_WIDTH	4096U
#घोषणा CEDRUS_MAX_HEIGHT	2304U

अटल काष्ठा cedrus_क्रमmat cedrus_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_MPEG2_SLICE,
		.directions	= CEDRUS_DECODE_SRC,
		.capabilities	= CEDRUS_CAPABILITY_MPEG2_DEC,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_H264_SLICE,
		.directions	= CEDRUS_DECODE_SRC,
		.capabilities	= CEDRUS_CAPABILITY_H264_DEC,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_HEVC_SLICE,
		.directions	= CEDRUS_DECODE_SRC,
		.capabilities	= CEDRUS_CAPABILITY_H265_DEC,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_VP8_FRAME,
		.directions	= CEDRUS_DECODE_SRC,
		.capabilities	= CEDRUS_CAPABILITY_VP8_DEC,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_SUNXI_TILED_NV12,
		.directions	= CEDRUS_DECODE_DST,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV12,
		.directions	= CEDRUS_DECODE_DST,
		.capabilities	= CEDRUS_CAPABILITY_UNTILED,
	पूर्ण,
पूर्ण;

#घोषणा CEDRUS_FORMATS_COUNT	ARRAY_SIZE(cedrus_क्रमmats)

अटल अंतरभूत काष्ठा cedrus_ctx *cedrus_file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा cedrus_ctx, fh);
पूर्ण

अटल काष्ठा cedrus_क्रमmat *cedrus_find_क्रमmat(u32 pixelक्रमmat, u32 directions,
						अचिन्हित पूर्णांक capabilities)
अणु
	काष्ठा cedrus_क्रमmat *first_valid_fmt = शून्य;
	काष्ठा cedrus_क्रमmat *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CEDRUS_FORMATS_COUNT; i++) अणु
		fmt = &cedrus_क्रमmats[i];

		अगर ((fmt->capabilities & capabilities) != fmt->capabilities ||
		    !(fmt->directions & directions))
			जारी;

		अगर (fmt->pixelक्रमmat == pixelक्रमmat)
			अवरोध;

		अगर (!first_valid_fmt)
			first_valid_fmt = fmt;
	पूर्ण

	अगर (i == CEDRUS_FORMATS_COUNT)
		वापस first_valid_fmt;

	वापस &cedrus_क्रमmats[i];
पूर्ण

व्योम cedrus_prepare_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix_fmt)
अणु
	अचिन्हित पूर्णांक width = pix_fmt->width;
	अचिन्हित पूर्णांक height = pix_fmt->height;
	अचिन्हित पूर्णांक sizeimage = pix_fmt->sizeimage;
	अचिन्हित पूर्णांक bytesperline = pix_fmt->bytesperline;

	pix_fmt->field = V4L2_FIELD_NONE;

	/* Limit to hardware min/max. */
	width = clamp(width, CEDRUS_MIN_WIDTH, CEDRUS_MAX_WIDTH);
	height = clamp(height, CEDRUS_MIN_HEIGHT, CEDRUS_MAX_HEIGHT);

	चयन (pix_fmt->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_MPEG2_SLICE:
	हाल V4L2_PIX_FMT_H264_SLICE:
	हाल V4L2_PIX_FMT_HEVC_SLICE:
	हाल V4L2_PIX_FMT_VP8_FRAME:
		/* Zero bytes per line क्रम encoded source. */
		bytesperline = 0;
		/* Choose some minimum size since this can't be 0 */
		sizeimage = max_t(u32, SZ_1K, sizeimage);
		अवरोध;

	हाल V4L2_PIX_FMT_SUNXI_TILED_NV12:
		/* 32-aligned stride. */
		bytesperline = ALIGN(width, 32);

		/* 32-aligned height. */
		height = ALIGN(height, 32);

		/* Luma plane size. */
		sizeimage = bytesperline * height;

		/* Chroma plane size. */
		sizeimage += bytesperline * height / 2;

		अवरोध;

	हाल V4L2_PIX_FMT_NV12:
		/* 16-aligned stride. */
		bytesperline = ALIGN(width, 16);

		/* 16-aligned height. */
		height = ALIGN(height, 16);

		/* Luma plane size. */
		sizeimage = bytesperline * height;

		/* Chroma plane size. */
		sizeimage += bytesperline * height / 2;

		अवरोध;
	पूर्ण

	pix_fmt->width = width;
	pix_fmt->height = height;

	pix_fmt->bytesperline = bytesperline;
	pix_fmt->sizeimage = sizeimage;
पूर्ण

अटल पूर्णांक cedrus_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, CEDRUS_NAME, माप(cap->driver));
	strscpy(cap->card, CEDRUS_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", CEDRUS_NAME);

	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_क्रमागत_fmt(काष्ठा file *file, काष्ठा v4l2_fmtdesc *f,
			   u32 direction)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);
	काष्ठा cedrus_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक capabilities = dev->capabilities;
	काष्ठा cedrus_क्रमmat *fmt;
	अचिन्हित पूर्णांक i, index;

	/* Index among क्रमmats that match the requested direction. */
	index = 0;

	क्रम (i = 0; i < CEDRUS_FORMATS_COUNT; i++) अणु
		fmt = &cedrus_क्रमmats[i];

		अगर (fmt->capabilities && (fmt->capabilities & capabilities) !=
		    fmt->capabilities)
			जारी;

		अगर (!(cedrus_क्रमmats[i].directions & direction))
			जारी;

		अगर (index == f->index)
			अवरोध;

		index++;
	पूर्ण

	/* Matched क्रमmat. */
	अगर (i < CEDRUS_FORMATS_COUNT) अणु
		f->pixelक्रमmat = cedrus_क्रमmats[i].pixelक्रमmat;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cedrus_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस cedrus_क्रमागत_fmt(file, f, CEDRUS_DECODE_DST);
पूर्ण

अटल पूर्णांक cedrus_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस cedrus_क्रमागत_fmt(file, f, CEDRUS_DECODE_SRC);
पूर्ण

अटल पूर्णांक cedrus_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);

	f->fmt.pix = ctx->dst_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);

	f->fmt.pix = ctx->src_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);
	काष्ठा cedrus_dev *dev = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix_fmt = &f->fmt.pix;
	काष्ठा cedrus_क्रमmat *fmt =
		cedrus_find_क्रमmat(pix_fmt->pixelक्रमmat, CEDRUS_DECODE_DST,
				   dev->capabilities);

	अगर (!fmt)
		वापस -EINVAL;

	pix_fmt->pixelक्रमmat = fmt->pixelक्रमmat;
	pix_fmt->width = ctx->src_fmt.width;
	pix_fmt->height = ctx->src_fmt.height;
	cedrus_prepare_क्रमmat(pix_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);
	काष्ठा cedrus_dev *dev = ctx->dev;
	काष्ठा v4l2_pix_क्रमmat *pix_fmt = &f->fmt.pix;
	काष्ठा cedrus_क्रमmat *fmt =
		cedrus_find_क्रमmat(pix_fmt->pixelक्रमmat, CEDRUS_DECODE_SRC,
				   dev->capabilities);

	अगर (!fmt)
		वापस -EINVAL;

	pix_fmt->pixelक्रमmat = fmt->pixelक्रमmat;
	cedrus_prepare_क्रमmat(pix_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	ret = cedrus_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	ctx->dst_fmt = f->fmt.pix;

	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cedrus_ctx *ctx = cedrus_file2ctx(file);
	काष्ठा vb2_queue *vq;
	काष्ठा vb2_queue *peer_vq;
	पूर्णांक ret;

	ret = cedrus_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	/*
	 * In order to support dynamic resolution change,
	 * the decoder admits a resolution change, as दीर्घ
	 * as the pixelक्रमmat reमुख्यs. Can't be करोne अगर streaming.
	 */
	अगर (vb2_is_streaming(vq) || (vb2_is_busy(vq) &&
	    f->fmt.pix.pixelक्रमmat != ctx->src_fmt.pixelक्रमmat))
		वापस -EBUSY;
	/*
	 * Since क्रमmat change on the OUTPUT queue will reset
	 * the CAPTURE queue, we can't allow करोing so
	 * when the CAPTURE queue has buffers allocated.
	 */
	peer_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
				  V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (vb2_is_busy(peer_vq))
		वापस -EBUSY;

	ret = cedrus_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	ctx->src_fmt = f->fmt.pix;

	चयन (ctx->src_fmt.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_H264_SLICE:
		vq->subप्रणाली_flags |=
			VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF;
		अवरोध;
	शेष:
		vq->subप्रणाली_flags &=
			~VB2_V4L2_FL_SUPPORTS_M2M_HOLD_CAPTURE_BUF;
		अवरोध;
	पूर्ण

	/* Propagate क्रमmat inक्रमmation to capture. */
	ctx->dst_fmt.colorspace = f->fmt.pix.colorspace;
	ctx->dst_fmt.xfer_func = f->fmt.pix.xfer_func;
	ctx->dst_fmt.ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->dst_fmt.quantization = f->fmt.pix.quantization;
	ctx->dst_fmt.width = ctx->src_fmt.width;
	ctx->dst_fmt.height = ctx->src_fmt.height;
	cedrus_prepare_क्रमmat(&ctx->dst_fmt);

	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops cedrus_ioctl_ops = अणु
	.vidioc_querycap		= cedrus_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= cedrus_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= cedrus_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= cedrus_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= cedrus_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out	= cedrus_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= cedrus_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= cedrus_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= cedrus_s_fmt_vid_out,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_try_decoder_cmd		= v4l2_m2m_ioctl_stateless_try_decoder_cmd,
	.vidioc_decoder_cmd		= v4l2_m2m_ioctl_stateless_decoder_cmd,

	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक cedrus_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbufs,
			      अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			      काष्ठा device *alloc_devs[])
अणु
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vq);
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

अटल व्योम cedrus_queue_cleanup(काष्ठा vb2_queue *vq, u32 state)
अणु
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		अगर (!vbuf)
			वापस;

		v4l2_ctrl_request_complete(vbuf->vb2_buf.req_obj.req,
					   &ctx->hdl);
		v4l2_m2m_buf_करोne(vbuf, state);
	पूर्ण
पूर्ण

अटल पूर्णांक cedrus_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vq);
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

अटल पूर्णांक cedrus_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा cedrus_dev *dev = ctx->dev;
	पूर्णांक ret = 0;

	चयन (ctx->src_fmt.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_MPEG2_SLICE:
		ctx->current_codec = CEDRUS_CODEC_MPEG2;
		अवरोध;

	हाल V4L2_PIX_FMT_H264_SLICE:
		ctx->current_codec = CEDRUS_CODEC_H264;
		अवरोध;

	हाल V4L2_PIX_FMT_HEVC_SLICE:
		ctx->current_codec = CEDRUS_CODEC_H265;
		अवरोध;

	हाल V4L2_PIX_FMT_VP8_FRAME:
		ctx->current_codec = CEDRUS_CODEC_VP8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		ret = pm_runसमय_get_sync(dev->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(dev->dev);
			जाओ err_cleanup;
		पूर्ण

		अगर (dev->dec_ops[ctx->current_codec]->start) अणु
			ret = dev->dec_ops[ctx->current_codec]->start(ctx);
			अगर (ret)
				जाओ err_pm;
		पूर्ण
	पूर्ण

	वापस 0;

err_pm:
	pm_runसमय_put(dev->dev);
err_cleanup:
	cedrus_queue_cleanup(vq, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

अटल व्योम cedrus_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा cedrus_dev *dev = ctx->dev;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		अगर (dev->dec_ops[ctx->current_codec]->stop)
			dev->dec_ops[ctx->current_codec]->stop(ctx);

		pm_runसमय_put(dev->dev);
	पूर्ण

	cedrus_queue_cleanup(vq, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम cedrus_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल व्योम cedrus_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cedrus_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->hdl);
पूर्ण

अटल काष्ठा vb2_ops cedrus_qops = अणु
	.queue_setup		= cedrus_queue_setup,
	.buf_prepare		= cedrus_buf_prepare,
	.buf_queue		= cedrus_buf_queue,
	.buf_out_validate	= cedrus_buf_out_validate,
	.buf_request_complete	= cedrus_buf_request_complete,
	.start_streaming	= cedrus_start_streaming,
	.stop_streaming		= cedrus_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक cedrus_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा cedrus_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा cedrus_buffer);
	src_vq->min_buffers_needed = 1;
	src_vq->ops = &cedrus_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->dev_mutex;
	src_vq->dev = ctx->dev->dev;
	src_vq->supports_requests = true;
	src_vq->requires_requests = true;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा cedrus_buffer);
	dst_vq->min_buffers_needed = 1;
	dst_vq->ops = &cedrus_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण
