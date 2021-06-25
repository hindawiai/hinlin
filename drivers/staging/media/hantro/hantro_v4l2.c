<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Collabora, Ltd.
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 *	Alpha Lin <Alpha.Lin@rock-chips.com>
 *	Jeffy Chen <jeffy.chen@rock-chips.com>
 *
 * Copyright 2018 Google LLC.
 *	Tomasz Figa <tfiga@chromium.org>
 *
 * Based on s5p-mfc driver by Samsung Electronics Co., Ltd.
 * Copyright (C) 2010-2011 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "hantro.h"
#समावेश "hantro_hw.h"
#समावेश "hantro_v4l2.h"

अटल पूर्णांक hantro_set_fmt_out(काष्ठा hantro_ctx *ctx,
			      काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp);
अटल पूर्णांक hantro_set_fmt_cap(काष्ठा hantro_ctx *ctx,
			      काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp);

अटल स्थिर काष्ठा hantro_fmt *
hantro_get_क्रमmats(स्थिर काष्ठा hantro_ctx *ctx, अचिन्हित पूर्णांक *num_fmts)
अणु
	स्थिर काष्ठा hantro_fmt *क्रमmats;

	अगर (ctx->is_encoder) अणु
		क्रमmats = ctx->dev->variant->enc_fmts;
		*num_fmts = ctx->dev->variant->num_enc_fmts;
	पूर्ण अन्यथा अणु
		क्रमmats = ctx->dev->variant->dec_fmts;
		*num_fmts = ctx->dev->variant->num_dec_fmts;
	पूर्ण

	वापस क्रमmats;
पूर्ण

अटल स्थिर काष्ठा hantro_fmt *
hantro_get_postproc_क्रमmats(स्थिर काष्ठा hantro_ctx *ctx,
			    अचिन्हित पूर्णांक *num_fmts)
अणु
	अगर (ctx->is_encoder) अणु
		*num_fmts = 0;
		वापस शून्य;
	पूर्ण

	*num_fmts = ctx->dev->variant->num_postproc_fmts;
	वापस ctx->dev->variant->postproc_fmts;
पूर्ण

अटल स्थिर काष्ठा hantro_fmt *
hantro_find_क्रमmat(स्थिर काष्ठा hantro_ctx *ctx, u32 fourcc)
अणु
	स्थिर काष्ठा hantro_fmt *क्रमmats;
	अचिन्हित पूर्णांक i, num_fmts;

	क्रमmats = hantro_get_क्रमmats(ctx, &num_fmts);
	क्रम (i = 0; i < num_fmts; i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस &क्रमmats[i];

	क्रमmats = hantro_get_postproc_क्रमmats(ctx, &num_fmts);
	क्रम (i = 0; i < num_fmts; i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस &क्रमmats[i];
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा hantro_fmt *
hantro_get_शेष_fmt(स्थिर काष्ठा hantro_ctx *ctx, bool bitstream)
अणु
	स्थिर काष्ठा hantro_fmt *क्रमmats;
	अचिन्हित पूर्णांक i, num_fmts;

	क्रमmats = hantro_get_क्रमmats(ctx, &num_fmts);
	क्रम (i = 0; i < num_fmts; i++) अणु
		अगर (bitstream == (क्रमmats[i].codec_mode !=
				  HANTRO_MODE_NONE))
			वापस &क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा hantro_dev *vpu = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	strscpy(cap->driver, vpu->dev->driver->name, माप(cap->driver));
	strscpy(cap->card, vdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform: %s",
		 vpu->dev->driver->name);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा hantro_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा hantro_fmt *fmt;

	अगर (fsize->index != 0) अणु
		vpu_debug(0, "invalid frame size index (expected 0, got %d)\n",
			  fsize->index);
		वापस -EINVAL;
	पूर्ण

	fmt = hantro_find_क्रमmat(ctx, fsize->pixel_क्रमmat);
	अगर (!fmt) अणु
		vpu_debug(0, "unsupported bitstream format (%08x)\n",
			  fsize->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* This only makes sense क्रम coded क्रमmats */
	अगर (fmt->codec_mode == HANTRO_MODE_NONE)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise = fmt->frmsize;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_fmtdesc *f, bool capture)

अणु
	काष्ठा hantro_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा hantro_fmt *fmt, *क्रमmats;
	अचिन्हित पूर्णांक num_fmts, i, j = 0;
	bool skip_mode_none;

	/*
	 * When dealing with an encoder:
	 *  - on the capture side we want to filter out all MODE_NONE क्रमmats.
	 *  - on the output side we want to filter out all क्रमmats that are
	 *    not MODE_NONE.
	 * When dealing with a decoder:
	 *  - on the capture side we want to filter out all क्रमmats that are
	 *    not MODE_NONE.
	 *  - on the output side we want to filter out all MODE_NONE क्रमmats.
	 */
	skip_mode_none = capture == ctx->is_encoder;

	क्रमmats = hantro_get_क्रमmats(ctx, &num_fmts);
	क्रम (i = 0; i < num_fmts; i++) अणु
		bool mode_none = क्रमmats[i].codec_mode == HANTRO_MODE_NONE;

		अगर (skip_mode_none == mode_none)
			जारी;
		अगर (j == f->index) अणु
			fmt = &क्रमmats[i];
			f->pixelक्रमmat = fmt->fourcc;
			वापस 0;
		पूर्ण
		++j;
	पूर्ण

	/*
	 * Enumerate post-processed क्रमmats. As per the specअगरication,
	 * we क्रमागतerated these क्रमmats after natively decoded क्रमmats
	 * as a hपूर्णांक क्रम applications on what's the preferred fomat.
	 */
	अगर (!capture)
		वापस -EINVAL;
	क्रमmats = hantro_get_postproc_क्रमmats(ctx, &num_fmts);
	क्रम (i = 0; i < num_fmts; i++) अणु
		अगर (j == f->index) अणु
			fmt = &क्रमmats[i];
			f->pixelक्रमmat = fmt->fourcc;
			वापस 0;
		पूर्ण
		++j;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, priv, f, true);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, priv, f, false);
पूर्ण

अटल पूर्णांक vidioc_g_fmt_out_mplane(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा hantro_ctx *ctx = fh_to_ctx(priv);

	vpu_debug(4, "f->type = %d\n", f->type);

	*pix_mp = ctx->src_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_cap_mplane(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा hantro_ctx *ctx = fh_to_ctx(priv);

	vpu_debug(4, "f->type = %d\n", f->type);

	*pix_mp = ctx->dst_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक hantro_try_fmt(स्थिर काष्ठा hantro_ctx *ctx,
			  काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp,
			  क्रमागत v4l2_buf_type type)
अणु
	स्थिर काष्ठा hantro_fmt *fmt, *vpu_fmt;
	bool capture = V4L2_TYPE_IS_CAPTURE(type);
	bool coded;

	coded = capture == ctx->is_encoder;

	vpu_debug(4, "trying format %c%c%c%c\n",
		  (pix_mp->pixelक्रमmat & 0x7f),
		  (pix_mp->pixelक्रमmat >> 8) & 0x7f,
		  (pix_mp->pixelक्रमmat >> 16) & 0x7f,
		  (pix_mp->pixelक्रमmat >> 24) & 0x7f);

	fmt = hantro_find_क्रमmat(ctx, pix_mp->pixelक्रमmat);
	अगर (!fmt) अणु
		fmt = hantro_get_शेष_fmt(ctx, coded);
		pix_mp->pixelक्रमmat = fmt->fourcc;
	पूर्ण

	अगर (coded) अणु
		pix_mp->num_planes = 1;
		vpu_fmt = fmt;
	पूर्ण अन्यथा अगर (ctx->is_encoder) अणु
		vpu_fmt = ctx->vpu_dst_fmt;
	पूर्ण अन्यथा अणु
		vpu_fmt = ctx->vpu_src_fmt;
		/*
		 * Width/height on the CAPTURE end of a decoder are ignored and
		 * replaced by the OUTPUT ones.
		 */
		pix_mp->width = ctx->src_fmt.width;
		pix_mp->height = ctx->src_fmt.height;
	पूर्ण

	pix_mp->field = V4L2_FIELD_NONE;

	v4l2_apply_frmsize_स्थिरraपूर्णांकs(&pix_mp->width, &pix_mp->height,
				       &vpu_fmt->frmsize);

	अगर (!coded) अणु
		/* Fill reमुख्यing fields */
		v4l2_fill_pixfmt_mp(pix_mp, fmt->fourcc, pix_mp->width,
				    pix_mp->height);
		अगर (ctx->vpu_src_fmt->fourcc == V4L2_PIX_FMT_H264_SLICE &&
		    !hantro_needs_postproc(ctx, fmt))
			pix_mp->plane_fmt[0].sizeimage +=
				hantro_h264_mv_size(pix_mp->width,
						    pix_mp->height);
	पूर्ण अन्यथा अगर (!pix_mp->plane_fmt[0].sizeimage) अणु
		/*
		 * For coded क्रमmats the application can specअगरy
		 * sizeimage. If the application passes a zero sizeimage,
		 * let's शेष to the maximum frame size.
		 */
		pix_mp->plane_fmt[0].sizeimage = fmt->header_size +
			pix_mp->width * pix_mp->height * fmt->max_depth;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_cap_mplane(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	वापस hantro_try_fmt(fh_to_ctx(priv), &f->fmt.pix_mp, f->type);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_out_mplane(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	वापस hantro_try_fmt(fh_to_ctx(priv), &f->fmt.pix_mp, f->type);
पूर्ण

अटल व्योम
hantro_reset_fmt(काष्ठा v4l2_pix_क्रमmat_mplane *fmt,
		 स्थिर काष्ठा hantro_fmt *vpu_fmt)
अणु
	स_रखो(fmt, 0, माप(*fmt));

	fmt->pixelक्रमmat = vpu_fmt->fourcc;
	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_JPEG;
	fmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	fmt->quantization = V4L2_QUANTIZATION_DEFAULT;
	fmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;
पूर्ण

अटल व्योम
hantro_reset_encoded_fmt(काष्ठा hantro_ctx *ctx)
अणु
	स्थिर काष्ठा hantro_fmt *vpu_fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *fmt;

	vpu_fmt = hantro_get_शेष_fmt(ctx, true);

	अगर (ctx->is_encoder) अणु
		ctx->vpu_dst_fmt = vpu_fmt;
		fmt = &ctx->dst_fmt;
	पूर्ण अन्यथा अणु
		ctx->vpu_src_fmt = vpu_fmt;
		fmt = &ctx->src_fmt;
	पूर्ण

	hantro_reset_fmt(fmt, vpu_fmt);
	fmt->width = vpu_fmt->frmsize.min_width;
	fmt->height = vpu_fmt->frmsize.min_height;
	अगर (ctx->is_encoder)
		hantro_set_fmt_cap(ctx, fmt);
	अन्यथा
		hantro_set_fmt_out(ctx, fmt);
पूर्ण

अटल व्योम
hantro_reset_raw_fmt(काष्ठा hantro_ctx *ctx)
अणु
	स्थिर काष्ठा hantro_fmt *raw_vpu_fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *raw_fmt, *encoded_fmt;

	raw_vpu_fmt = hantro_get_शेष_fmt(ctx, false);

	अगर (ctx->is_encoder) अणु
		ctx->vpu_src_fmt = raw_vpu_fmt;
		raw_fmt = &ctx->src_fmt;
		encoded_fmt = &ctx->dst_fmt;
	पूर्ण अन्यथा अणु
		ctx->vpu_dst_fmt = raw_vpu_fmt;
		raw_fmt = &ctx->dst_fmt;
		encoded_fmt = &ctx->src_fmt;
	पूर्ण

	hantro_reset_fmt(raw_fmt, raw_vpu_fmt);
	raw_fmt->width = encoded_fmt->width;
	raw_fmt->height = encoded_fmt->height;
	अगर (ctx->is_encoder)
		hantro_set_fmt_out(ctx, raw_fmt);
	अन्यथा
		hantro_set_fmt_cap(ctx, raw_fmt);
पूर्ण

व्योम hantro_reset_fmts(काष्ठा hantro_ctx *ctx)
अणु
	hantro_reset_encoded_fmt(ctx);
	hantro_reset_raw_fmt(ctx);
पूर्ण

अटल व्योम
hantro_update_requires_request(काष्ठा hantro_ctx *ctx, u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_JPEG:
		ctx->fh.m2m_ctx->out_q_ctx.q.requires_requests = false;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG2_SLICE:
	हाल V4L2_PIX_FMT_VP8_FRAME:
	हाल V4L2_PIX_FMT_H264_SLICE:
		ctx->fh.m2m_ctx->out_q_ctx.q.requires_requests = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hantro_set_fmt_out(काष्ठा hantro_ctx *ctx,
			      काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp)
अणु
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
			     V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	ret = hantro_try_fmt(ctx, pix_mp, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	अगर (ret)
		वापस ret;

	अगर (!ctx->is_encoder) अणु
		काष्ठा vb2_queue *peer_vq;

		/*
		 * In order to support dynamic resolution change,
		 * the decoder admits a resolution change, as दीर्घ
		 * as the pixelक्रमmat reमुख्यs. Can't be करोne अगर streaming.
		 */
		अगर (vb2_is_streaming(vq) || (vb2_is_busy(vq) &&
		    pix_mp->pixelक्रमmat != ctx->src_fmt.pixelक्रमmat))
			वापस -EBUSY;
		/*
		 * Since क्रमmat change on the OUTPUT queue will reset
		 * the CAPTURE queue, we can't allow करोing so
		 * when the CAPTURE queue has buffers allocated.
		 */
		peer_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
		अगर (vb2_is_busy(peer_vq))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		/*
		 * The encoder करोesn't admit a क्रमmat change अगर
		 * there are OUTPUT buffers allocated.
		 */
		अगर (vb2_is_busy(vq))
			वापस -EBUSY;
	पूर्ण

	ctx->vpu_src_fmt = hantro_find_क्रमmat(ctx, pix_mp->pixelक्रमmat);
	ctx->src_fmt = *pix_mp;

	/*
	 * Current raw क्रमmat might have become invalid with newly
	 * selected codec, so reset it to शेष just to be safe and
	 * keep पूर्णांकernal driver state sane. User is mandated to set
	 * the raw क्रमmat again after we वापस, so we करोn't need
	 * anything smarter.
	 * Note that hantro_reset_raw_fmt() also propagates size
	 * changes to the raw क्रमmat.
	 */
	अगर (!ctx->is_encoder)
		hantro_reset_raw_fmt(ctx);

	/* Colorimetry inक्रमmation are always propagated. */
	ctx->dst_fmt.colorspace = pix_mp->colorspace;
	ctx->dst_fmt.ycbcr_enc = pix_mp->ycbcr_enc;
	ctx->dst_fmt.xfer_func = pix_mp->xfer_func;
	ctx->dst_fmt.quantization = pix_mp->quantization;

	hantro_update_requires_request(ctx, pix_mp->pixelक्रमmat);

	vpu_debug(0, "OUTPUT codec mode: %d\n", ctx->vpu_src_fmt->codec_mode);
	vpu_debug(0, "fmt - w: %d, h: %d\n",
		  pix_mp->width, pix_mp->height);
	वापस 0;
पूर्ण

अटल पूर्णांक hantro_set_fmt_cap(काष्ठा hantro_ctx *ctx,
			      काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp)
अणु
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	/* Change not allowed अगर queue is busy. */
	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
			     V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	अगर (ctx->is_encoder) अणु
		काष्ठा vb2_queue *peer_vq;

		/*
		 * Since क्रमmat change on the CAPTURE queue will reset
		 * the OUTPUT queue, we can't allow करोing so
		 * when the OUTPUT queue has buffers allocated.
		 */
		peer_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		अगर (vb2_is_busy(peer_vq) &&
		    (pix_mp->pixelक्रमmat != ctx->dst_fmt.pixelक्रमmat ||
		     pix_mp->height != ctx->dst_fmt.height ||
		     pix_mp->width != ctx->dst_fmt.width))
			वापस -EBUSY;
	पूर्ण

	ret = hantro_try_fmt(ctx, pix_mp, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (ret)
		वापस ret;

	ctx->vpu_dst_fmt = hantro_find_क्रमmat(ctx, pix_mp->pixelक्रमmat);
	ctx->dst_fmt = *pix_mp;

	/*
	 * Current raw क्रमmat might have become invalid with newly
	 * selected codec, so reset it to शेष just to be safe and
	 * keep पूर्णांकernal driver state sane. User is mandated to set
	 * the raw क्रमmat again after we वापस, so we करोn't need
	 * anything smarter.
	 * Note that hantro_reset_raw_fmt() also propagates size
	 * changes to the raw क्रमmat.
	 */
	अगर (ctx->is_encoder)
		hantro_reset_raw_fmt(ctx);

	/* Colorimetry inक्रमmation are always propagated. */
	ctx->src_fmt.colorspace = pix_mp->colorspace;
	ctx->src_fmt.ycbcr_enc = pix_mp->ycbcr_enc;
	ctx->src_fmt.xfer_func = pix_mp->xfer_func;
	ctx->src_fmt.quantization = pix_mp->quantization;

	vpu_debug(0, "CAPTURE codec mode: %d\n", ctx->vpu_dst_fmt->codec_mode);
	vpu_debug(0, "fmt - w: %d, h: %d\n",
		  pix_mp->width, pix_mp->height);

	hantro_update_requires_request(ctx, pix_mp->pixelक्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक
vidioc_s_fmt_out_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	वापस hantro_set_fmt_out(fh_to_ctx(priv), &f->fmt.pix_mp);
पूर्ण

अटल पूर्णांक
vidioc_s_fmt_cap_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	वापस hantro_set_fmt_cap(fh_to_ctx(priv), &f->fmt.pix_mp);
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops hantro_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	.vidioc_क्रमागत_framesizes = vidioc_क्रमागत_framesizes,

	.vidioc_try_fmt_vid_cap_mplane = vidioc_try_fmt_cap_mplane,
	.vidioc_try_fmt_vid_out_mplane = vidioc_try_fmt_out_mplane,
	.vidioc_s_fmt_vid_out_mplane = vidioc_s_fmt_out_mplane,
	.vidioc_s_fmt_vid_cap_mplane = vidioc_s_fmt_cap_mplane,
	.vidioc_g_fmt_vid_out_mplane = vidioc_g_fmt_out_mplane,
	.vidioc_g_fmt_vid_cap_mplane = vidioc_g_fmt_cap_mplane,
	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,

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
पूर्ण;

अटल पूर्णांक
hantro_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *num_buffers,
		   अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
		   काष्ठा device *alloc_devs[])
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat_mplane *pixfmt;
	पूर्णांक i;

	चयन (vq->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		pixfmt = &ctx->dst_fmt;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pixfmt = &ctx->src_fmt;
		अवरोध;
	शेष:
		vpu_err("invalid queue type: %d\n", vq->type);
		वापस -EINVAL;
	पूर्ण

	अगर (*num_planes) अणु
		अगर (*num_planes != pixfmt->num_planes)
			वापस -EINVAL;
		क्रम (i = 0; i < pixfmt->num_planes; ++i)
			अगर (sizes[i] < pixfmt->plane_fmt[i].sizeimage)
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	*num_planes = pixfmt->num_planes;
	क्रम (i = 0; i < pixfmt->num_planes; ++i)
		sizes[i] = pixfmt->plane_fmt[i].sizeimage;
	वापस 0;
पूर्ण

अटल पूर्णांक
hantro_buf_plane_check(काष्ठा vb2_buffer *vb,
		       काष्ठा v4l2_pix_क्रमmat_mplane *pixfmt)
अणु
	अचिन्हित पूर्णांक sz;
	पूर्णांक i;

	क्रम (i = 0; i < pixfmt->num_planes; ++i) अणु
		sz = pixfmt->plane_fmt[i].sizeimage;
		vpu_debug(4, "plane %d size: %ld, sizeimage: %u\n",
			  i, vb2_plane_size(vb, i), sz);
		अगर (vb2_plane_size(vb, i) < sz) अणु
			vpu_err("plane %d is too small for output\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hantro_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt;
	पूर्णांक ret;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	अन्यथा
		pix_fmt = &ctx->dst_fmt;
	ret = hantro_buf_plane_check(vb, pix_fmt);
	अगर (ret)
		वापस ret;
	vb2_set_plane_payload(vb, 0, pix_fmt->plane_fmt[0].sizeimage);
	वापस 0;
पूर्ण

अटल व्योम hantro_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल bool hantro_vq_is_coded(काष्ठा vb2_queue *q)
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(q);

	वापस ctx->is_encoder != V4L2_TYPE_IS_OUTPUT(q->type);
पूर्ण

अटल पूर्णांक hantro_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(q);
	पूर्णांक ret = 0;

	अगर (V4L2_TYPE_IS_OUTPUT(q->type))
		ctx->sequence_out = 0;
	अन्यथा
		ctx->sequence_cap = 0;

	अगर (hantro_vq_is_coded(q)) अणु
		क्रमागत hantro_codec_mode codec_mode;

		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			codec_mode = ctx->vpu_src_fmt->codec_mode;
		अन्यथा
			codec_mode = ctx->vpu_dst_fmt->codec_mode;

		vpu_debug(4, "Codec mode = %d\n", codec_mode);
		ctx->codec_ops = &ctx->dev->variant->codec_ops[codec_mode];
		अगर (ctx->codec_ops->init) अणु
			ret = ctx->codec_ops->init(ctx);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (hantro_needs_postproc(ctx, ctx->vpu_dst_fmt)) अणु
			ret = hantro_postproc_alloc(ctx);
			अगर (ret)
				जाओ err_codec_निकास;
		पूर्ण
	पूर्ण
	वापस ret;

err_codec_निकास:
	अगर (ctx->codec_ops->निकास)
		ctx->codec_ops->निकास(ctx);
	वापस ret;
पूर्ण

अटल व्योम
hantro_वापस_bufs(काष्ठा vb2_queue *q,
		   काष्ठा vb2_v4l2_buffer *(*buf_हटाओ)(काष्ठा v4l2_m2m_ctx *))
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(q);

	क्रम (;;) अणु
		काष्ठा vb2_v4l2_buffer *vbuf;

		vbuf = buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vbuf)
			अवरोध;
		v4l2_ctrl_request_complete(vbuf->vb2_buf.req_obj.req,
					   &ctx->ctrl_handler);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल व्योम hantro_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(q);

	अगर (hantro_vq_is_coded(q)) अणु
		hantro_postproc_मुक्त(ctx);
		अगर (ctx->codec_ops && ctx->codec_ops->निकास)
			ctx->codec_ops->निकास(ctx);
	पूर्ण

	/*
	 * The mem2mem framework calls v4l2_m2m_cancel_job beक्रमe
	 * .stop_streaming, so there isn't any job running and
	 * it is safe to वापस all the buffers.
	 */
	अगर (V4L2_TYPE_IS_OUTPUT(q->type))
		hantro_वापस_bufs(q, v4l2_m2m_src_buf_हटाओ);
	अन्यथा
		hantro_वापस_bufs(q, v4l2_m2m_dst_buf_हटाओ);
पूर्ण

अटल व्योम hantro_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा hantro_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->ctrl_handler);
पूर्ण

अटल पूर्णांक hantro_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

स्थिर काष्ठा vb2_ops hantro_queue_ops = अणु
	.queue_setup = hantro_queue_setup,
	.buf_prepare = hantro_buf_prepare,
	.buf_queue = hantro_buf_queue,
	.buf_out_validate = hantro_buf_out_validate,
	.buf_request_complete = hantro_buf_request_complete,
	.start_streaming = hantro_start_streaming,
	.stop_streaming = hantro_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;
