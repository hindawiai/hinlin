<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Rockchip Video Decoder driver
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on rkvdec driver by Google LLC. (Tomasz Figa <tfiga@chromium.org>)
 * Based on s5p-mfc driver by Samsung Electronics Co., Ltd.
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "rkvdec.h"
#समावेश "rkvdec-regs.h"

अटल पूर्णांक rkvdec_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (ctrl->id == V4L2_CID_STATELESS_H264_SPS) अणु
		स्थिर काष्ठा v4l2_ctrl_h264_sps *sps = ctrl->p_new.p_h264_sps;
		/*
		 * TODO: The hardware supports 10-bit and 4:2:2 profiles,
		 * but it's currently broken in the driver.
		 * Reject them क्रम now, until it's fixed.
		 */
		अगर (sps->chroma_क्रमmat_idc > 1)
			/* Only 4:0:0 and 4:2:0 are supported */
			वापस -EINVAL;
		अगर (sps->bit_depth_luma_minus8 != sps->bit_depth_chroma_minus8)
			/* Luma and chroma bit depth mismatch */
			वापस -EINVAL;
		अगर (sps->bit_depth_luma_minus8 != 0)
			/* Only 8-bit is supported */
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rkvdec_ctrl_ops = अणु
	.try_ctrl = rkvdec_try_ctrl,
पूर्ण;

अटल स्थिर काष्ठा rkvdec_ctrl_desc rkvdec_h264_ctrl_descs[] = अणु
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_DECODE_PARAMS,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_SPS,
		.cfg.ops = &rkvdec_ctrl_ops,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_PPS,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_SCALING_MATRIX,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_DECODE_MODE,
		.cfg.min = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
		.cfg.max = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
		.cfg.def = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_STATELESS_H264_START_CODE,
		.cfg.min = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
		.cfg.def = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
		.cfg.max = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		.cfg.min = V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE,
		.cfg.max = V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
		.cfg.menu_skip_mask =
			BIT(V4L2_MPEG_VIDEO_H264_PROखाता_EXTENDED),
		.cfg.def = V4L2_MPEG_VIDEO_H264_PROखाता_MAIN,
	पूर्ण,
	अणु
		.cfg.id = V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		.cfg.min = V4L2_MPEG_VIDEO_H264_LEVEL_1_0,
		.cfg.max = V4L2_MPEG_VIDEO_H264_LEVEL_5_1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rkvdec_ctrls rkvdec_h264_ctrls = अणु
	.ctrls = rkvdec_h264_ctrl_descs,
	.num_ctrls = ARRAY_SIZE(rkvdec_h264_ctrl_descs),
पूर्ण;

अटल स्थिर u32 rkvdec_h264_decoded_fmts[] = अणु
	V4L2_PIX_FMT_NV12,
पूर्ण;

अटल स्थिर काष्ठा rkvdec_coded_fmt_desc rkvdec_coded_fmts[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_H264_SLICE,
		.frmsize = अणु
			.min_width = 48,
			.max_width = 4096,
			.step_width = 16,
			.min_height = 48,
			.max_height = 2304,
			.step_height = 16,
		पूर्ण,
		.ctrls = &rkvdec_h264_ctrls,
		.ops = &rkvdec_h264_fmt_ops,
		.num_decoded_fmts = ARRAY_SIZE(rkvdec_h264_decoded_fmts),
		.decoded_fmts = rkvdec_h264_decoded_fmts,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rkvdec_coded_fmt_desc *
rkvdec_find_coded_fmt_desc(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rkvdec_coded_fmts); i++) अणु
		अगर (rkvdec_coded_fmts[i].fourcc == fourcc)
			वापस &rkvdec_coded_fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम rkvdec_reset_fmt(काष्ठा rkvdec_ctx *ctx, काष्ठा v4l2_क्रमmat *f,
			     u32 fourcc)
अणु
	स_रखो(f, 0, माप(*f));
	f->fmt.pix_mp.pixelक्रमmat = fourcc;
	f->fmt.pix_mp.field = V4L2_FIELD_NONE;
	f->fmt.pix_mp.colorspace = V4L2_COLORSPACE_REC709;
	f->fmt.pix_mp.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	f->fmt.pix_mp.quantization = V4L2_QUANTIZATION_DEFAULT;
	f->fmt.pix_mp.xfer_func = V4L2_XFER_FUNC_DEFAULT;
पूर्ण

अटल व्योम rkvdec_reset_coded_fmt(काष्ठा rkvdec_ctx *ctx)
अणु
	काष्ठा v4l2_क्रमmat *f = &ctx->coded_fmt;

	ctx->coded_fmt_desc = &rkvdec_coded_fmts[0];
	rkvdec_reset_fmt(ctx, f, ctx->coded_fmt_desc->fourcc);

	f->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	f->fmt.pix_mp.width = ctx->coded_fmt_desc->frmsize.min_width;
	f->fmt.pix_mp.height = ctx->coded_fmt_desc->frmsize.min_height;

	अगर (ctx->coded_fmt_desc->ops->adjust_fmt)
		ctx->coded_fmt_desc->ops->adjust_fmt(ctx, f);
पूर्ण

अटल व्योम rkvdec_reset_decoded_fmt(काष्ठा rkvdec_ctx *ctx)
अणु
	काष्ठा v4l2_क्रमmat *f = &ctx->decoded_fmt;

	rkvdec_reset_fmt(ctx, f, ctx->coded_fmt_desc->decoded_fmts[0]);
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	v4l2_fill_pixfmt_mp(&f->fmt.pix_mp,
			    ctx->coded_fmt_desc->decoded_fmts[0],
			    ctx->coded_fmt.fmt.pix_mp.width,
			    ctx->coded_fmt.fmt.pix_mp.height);
	f->fmt.pix_mp.plane_fmt[0].sizeimage += 128 *
		DIV_ROUND_UP(f->fmt.pix_mp.width, 16) *
		DIV_ROUND_UP(f->fmt.pix_mp.height, 16);
पूर्ण

अटल पूर्णांक rkvdec_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा rkvdec_coded_fmt_desc *fmt;

	अगर (fsize->index != 0)
		वापस -EINVAL;

	fmt = rkvdec_find_coded_fmt_desc(fsize->pixel_क्रमmat);
	अगर (!fmt)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise = fmt->frmsize;
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा rkvdec_dev *rkvdec = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	strscpy(cap->driver, rkvdec->dev->driver->name,
		माप(cap->driver));
	strscpy(cap->card, vdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 rkvdec->dev->driver->name);
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_try_capture_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);
	स्थिर काष्ठा rkvdec_coded_fmt_desc *coded_desc;
	अचिन्हित पूर्णांक i;

	/*
	 * The codec context should poपूर्णांक to a coded क्रमmat desc, अगर the क्रमmat
	 * on the coded end has not been set yet, it should poपूर्णांक to the
	 * शेष value.
	 */
	coded_desc = ctx->coded_fmt_desc;
	अगर (WARN_ON(!coded_desc))
		वापस -EINVAL;

	क्रम (i = 0; i < coded_desc->num_decoded_fmts; i++) अणु
		अगर (coded_desc->decoded_fmts[i] == pix_mp->pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (i == coded_desc->num_decoded_fmts)
		pix_mp->pixelक्रमmat = coded_desc->decoded_fmts[0];

	/* Always apply the frmsize स्थिरraपूर्णांक of the coded end. */
	v4l2_apply_frmsize_स्थिरraपूर्णांकs(&pix_mp->width,
				       &pix_mp->height,
				       &coded_desc->frmsize);

	v4l2_fill_pixfmt_mp(pix_mp, pix_mp->pixelक्रमmat,
			    pix_mp->width, pix_mp->height);
	pix_mp->plane_fmt[0].sizeimage +=
		128 *
		DIV_ROUND_UP(pix_mp->width, 16) *
		DIV_ROUND_UP(pix_mp->height, 16);
	pix_mp->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_try_output_fmt(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);
	स्थिर काष्ठा rkvdec_coded_fmt_desc *desc;

	desc = rkvdec_find_coded_fmt_desc(pix_mp->pixelक्रमmat);
	अगर (!desc) अणु
		pix_mp->pixelक्रमmat = rkvdec_coded_fmts[0].fourcc;
		desc = &rkvdec_coded_fmts[0];
	पूर्ण

	v4l2_apply_frmsize_स्थिरraपूर्णांकs(&pix_mp->width,
				       &pix_mp->height,
				       &desc->frmsize);

	pix_mp->field = V4L2_FIELD_NONE;
	/* All coded क्रमmats are considered single planar क्रम now. */
	pix_mp->num_planes = 1;

	अगर (desc->ops->adjust_fmt) अणु
		पूर्णांक ret;

		ret = desc->ops->adjust_fmt(ctx, f);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_s_fmt(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f,
			पूर्णांक (*try_fmt)(काष्ठा file *, व्योम *,
				       काष्ठा v4l2_क्रमmat *))
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);
	काष्ठा vb2_queue *vq;

	अगर (!try_fmt)
		वापस -EINVAL;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	वापस try_fmt(file, priv, f);
पूर्ण

अटल पूर्णांक rkvdec_s_capture_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);
	पूर्णांक ret;

	ret = rkvdec_s_fmt(file, priv, f, rkvdec_try_capture_fmt);
	अगर (ret)
		वापस ret;

	ctx->decoded_fmt = *f;
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_s_output_fmt(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);
	काष्ठा v4l2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	स्थिर काष्ठा rkvdec_coded_fmt_desc *desc;
	काष्ठा v4l2_क्रमmat *cap_fmt;
	काष्ठा vb2_queue *peer_vq;
	पूर्णांक ret;

	/*
	 * Since क्रमmat change on the OUTPUT queue will reset the CAPTURE
	 * queue, we can't allow करोing so when the CAPTURE queue has buffers
	 * allocated.
	 */
	peer_vq = v4l2_m2m_get_vq(m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (vb2_is_busy(peer_vq))
		वापस -EBUSY;

	ret = rkvdec_s_fmt(file, priv, f, rkvdec_try_output_fmt);
	अगर (ret)
		वापस ret;

	desc = rkvdec_find_coded_fmt_desc(f->fmt.pix_mp.pixelक्रमmat);
	अगर (!desc)
		वापस -EINVAL;
	ctx->coded_fmt_desc = desc;
	ctx->coded_fmt = *f;

	/*
	 * Current decoded क्रमmat might have become invalid with newly
	 * selected codec, so reset it to शेष just to be safe and
	 * keep पूर्णांकernal driver state sane. User is mandated to set
	 * the decoded क्रमmat again after we वापस, so we करोn't need
	 * anything smarter.
	 *
	 * Note that this will propagates any size changes to the decoded क्रमmat.
	 */
	rkvdec_reset_decoded_fmt(ctx);

	/* Propagate colorspace inक्रमmation to capture. */
	cap_fmt = &ctx->decoded_fmt;
	cap_fmt->fmt.pix_mp.colorspace = f->fmt.pix_mp.colorspace;
	cap_fmt->fmt.pix_mp.xfer_func = f->fmt.pix_mp.xfer_func;
	cap_fmt->fmt.pix_mp.ycbcr_enc = f->fmt.pix_mp.ycbcr_enc;
	cap_fmt->fmt.pix_mp.quantization = f->fmt.pix_mp.quantization;

	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_g_output_fmt(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);

	*f = ctx->coded_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_g_capture_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);

	*f = ctx->decoded_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_क्रमागत_output_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(rkvdec_coded_fmts))
		वापस -EINVAL;

	f->pixelक्रमmat = rkvdec_coded_fmts[f->index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_क्रमागत_capture_fmt(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(priv);

	अगर (WARN_ON(!ctx->coded_fmt_desc))
		वापस -EINVAL;

	अगर (f->index >= ctx->coded_fmt_desc->num_decoded_fmts)
		वापस -EINVAL;

	f->pixelक्रमmat = ctx->coded_fmt_desc->decoded_fmts[f->index];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rkvdec_ioctl_ops = अणु
	.vidioc_querycap = rkvdec_querycap,
	.vidioc_क्रमागत_framesizes = rkvdec_क्रमागत_framesizes,

	.vidioc_try_fmt_vid_cap_mplane = rkvdec_try_capture_fmt,
	.vidioc_try_fmt_vid_out_mplane = rkvdec_try_output_fmt,
	.vidioc_s_fmt_vid_out_mplane = rkvdec_s_output_fmt,
	.vidioc_s_fmt_vid_cap_mplane = rkvdec_s_capture_fmt,
	.vidioc_g_fmt_vid_out_mplane = rkvdec_g_output_fmt,
	.vidioc_g_fmt_vid_cap_mplane = rkvdec_g_capture_fmt,
	.vidioc_क्रमागत_fmt_vid_out = rkvdec_क्रमागत_output_fmt,
	.vidioc_क्रमागत_fmt_vid_cap = rkvdec_क्रमागत_capture_fmt,

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

अटल पूर्णांक rkvdec_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *num_buffers,
			      अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
			      काष्ठा device *alloc_devs[])
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_क्रमmat *f;
	अचिन्हित पूर्णांक i;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		f = &ctx->coded_fmt;
	अन्यथा
		f = &ctx->decoded_fmt;

	अगर (*num_planes) अणु
		अगर (*num_planes != f->fmt.pix_mp.num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < f->fmt.pix_mp.num_planes; i++) अणु
			अगर (sizes[i] < f->fmt.pix_mp.plane_fmt[i].sizeimage)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		*num_planes = f->fmt.pix_mp.num_planes;
		क्रम (i = 0; i < f->fmt.pix_mp.num_planes; i++)
			sizes[i] = f->fmt.pix_mp.plane_fmt[i].sizeimage;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_क्रमmat *f;
	अचिन्हित पूर्णांक i;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		f = &ctx->coded_fmt;
	अन्यथा
		f = &ctx->decoded_fmt;

	क्रम (i = 0; i < f->fmt.pix_mp.num_planes; ++i) अणु
		u32 sizeimage = f->fmt.pix_mp.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < sizeimage)
			वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, f->fmt.pix_mp.plane_fmt[0].sizeimage);
	वापस 0;
पूर्ण

अटल व्योम rkvdec_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक rkvdec_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल व्योम rkvdec_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->ctrl_hdl);
पूर्ण

अटल पूर्णांक rkvdec_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(q);
	स्थिर काष्ठा rkvdec_coded_fmt_desc *desc;
	पूर्णांक ret;

	अगर (V4L2_TYPE_IS_CAPTURE(q->type))
		वापस 0;

	desc = ctx->coded_fmt_desc;
	अगर (WARN_ON(!desc))
		वापस -EINVAL;

	अगर (desc->ops->start) अणु
		ret = desc->ops->start(ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rkvdec_queue_cleanup(काष्ठा vb2_queue *vq, u32 state)
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(vq);

	जबतक (true) अणु
		काष्ठा vb2_v4l2_buffer *vbuf;

		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		अगर (!vbuf)
			अवरोध;

		v4l2_ctrl_request_complete(vbuf->vb2_buf.req_obj.req,
					   &ctx->ctrl_hdl);
		v4l2_m2m_buf_करोne(vbuf, state);
	पूर्ण
पूर्ण

अटल व्योम rkvdec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा rkvdec_ctx *ctx = vb2_get_drv_priv(q);

	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		स्थिर काष्ठा rkvdec_coded_fmt_desc *desc = ctx->coded_fmt_desc;

		अगर (WARN_ON(!desc))
			वापस;

		अगर (desc->ops->stop)
			desc->ops->stop(ctx);
	पूर्ण

	rkvdec_queue_cleanup(q, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rkvdec_queue_ops = अणु
	.queue_setup = rkvdec_queue_setup,
	.buf_prepare = rkvdec_buf_prepare,
	.buf_queue = rkvdec_buf_queue,
	.buf_out_validate = rkvdec_buf_out_validate,
	.buf_request_complete = rkvdec_buf_request_complete,
	.start_streaming = rkvdec_start_streaming,
	.stop_streaming = rkvdec_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक rkvdec_request_validate(काष्ठा media_request *req)
अणु
	अचिन्हित पूर्णांक count;

	count = vb2_request_buffer_cnt(req);
	अगर (!count)
		वापस -ENOENT;
	अन्यथा अगर (count > 1)
		वापस -EINVAL;

	वापस vb2_request_validate(req);
पूर्ण

अटल स्थिर काष्ठा media_device_ops rkvdec_media_ops = अणु
	.req_validate = rkvdec_request_validate,
	.req_queue = v4l2_m2m_request_queue,
पूर्ण;

अटल व्योम rkvdec_job_finish_no_pm(काष्ठा rkvdec_ctx *ctx,
				    क्रमागत vb2_buffer_state result)
अणु
	अगर (ctx->coded_fmt_desc->ops->करोne) अणु
		काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;

		src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
		ctx->coded_fmt_desc->ops->करोne(ctx, src_buf, dst_buf, result);
	पूर्ण

	v4l2_m2m_buf_करोne_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 result);
पूर्ण

अटल व्योम rkvdec_job_finish(काष्ठा rkvdec_ctx *ctx,
			      क्रमागत vb2_buffer_state result)
अणु
	काष्ठा rkvdec_dev *rkvdec = ctx->dev;

	pm_runसमय_mark_last_busy(rkvdec->dev);
	pm_runसमय_put_स्वतःsuspend(rkvdec->dev);
	rkvdec_job_finish_no_pm(ctx, result);
पूर्ण

व्योम rkvdec_run_preamble(काष्ठा rkvdec_ctx *ctx, काष्ठा rkvdec_run *run)
अणु
	काष्ठा media_request *src_req;

	स_रखो(run, 0, माप(*run));

	run->bufs.src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	run->bufs.dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Apply request(s) controls अगर needed. */
	src_req = run->bufs.src->vb2_buf.req_obj.req;
	अगर (src_req)
		v4l2_ctrl_request_setup(src_req, &ctx->ctrl_hdl);

	v4l2_m2m_buf_copy_metadata(run->bufs.src, run->bufs.dst, true);
पूर्ण

व्योम rkvdec_run_postamble(काष्ठा rkvdec_ctx *ctx, काष्ठा rkvdec_run *run)
अणु
	काष्ठा media_request *src_req = run->bufs.src->vb2_buf.req_obj.req;

	अगर (src_req)
		v4l2_ctrl_request_complete(src_req, &ctx->ctrl_hdl);
पूर्ण

अटल व्योम rkvdec_device_run(व्योम *priv)
अणु
	काष्ठा rkvdec_ctx *ctx = priv;
	काष्ठा rkvdec_dev *rkvdec = ctx->dev;
	स्थिर काष्ठा rkvdec_coded_fmt_desc *desc = ctx->coded_fmt_desc;
	पूर्णांक ret;

	अगर (WARN_ON(!desc))
		वापस;

	ret = pm_runसमय_get_sync(rkvdec->dev);
	अगर (ret < 0) अणु
		rkvdec_job_finish_no_pm(ctx, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	ret = desc->ops->run(ctx);
	अगर (ret)
		rkvdec_job_finish(ctx, VB2_BUF_STATE_ERROR);
पूर्ण

अटल काष्ठा v4l2_m2m_ops rkvdec_m2m_ops = अणु
	.device_run = rkvdec_device_run,
पूर्ण;

अटल पूर्णांक rkvdec_queue_init(व्योम *priv,
			     काष्ठा vb2_queue *src_vq,
			     काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा rkvdec_ctx *ctx = priv;
	काष्ठा rkvdec_dev *rkvdec = ctx->dev;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &rkvdec_queue_ops;
	src_vq->mem_ops = &vb2_dma_contig_memops;

	/*
	 * Driver करोes mostly sequential access, so sacrअगरice TLB efficiency
	 * क्रम faster allocation. Also, no CPU access on the source queue,
	 * so no kernel mapping needed.
	 */
	src_vq->dma_attrs = DMA_ATTR_ALLOC_SINGLE_PAGES |
			    DMA_ATTR_NO_KERNEL_MAPPING;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &rkvdec->vdev_lock;
	src_vq->dev = rkvdec->v4l2_dev.dev;
	src_vq->supports_requests = true;
	src_vq->requires_requests = true;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->bidirectional = true;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dma_attrs = DMA_ATTR_ALLOC_SINGLE_PAGES |
			    DMA_ATTR_NO_KERNEL_MAPPING;
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &rkvdec_queue_ops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा rkvdec_decoded_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &rkvdec->vdev_lock;
	dst_vq->dev = rkvdec->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक rkvdec_add_ctrls(काष्ठा rkvdec_ctx *ctx,
			    स्थिर काष्ठा rkvdec_ctrls *ctrls)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ctrls->num_ctrls; i++) अणु
		स्थिर काष्ठा v4l2_ctrl_config *cfg = &ctrls->ctrls[i].cfg;

		v4l2_ctrl_new_custom(&ctx->ctrl_hdl, cfg, ctx);
		अगर (ctx->ctrl_hdl.error)
			वापस ctx->ctrl_hdl.error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rkvdec_init_ctrls(काष्ठा rkvdec_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i, nctrls = 0;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(rkvdec_coded_fmts); i++)
		nctrls += rkvdec_coded_fmts[i].ctrls->num_ctrls;

	v4l2_ctrl_handler_init(&ctx->ctrl_hdl, nctrls);

	क्रम (i = 0; i < ARRAY_SIZE(rkvdec_coded_fmts); i++) अणु
		ret = rkvdec_add_ctrls(ctx, rkvdec_coded_fmts[i].ctrls);
		अगर (ret)
			जाओ err_मुक्त_handler;
	पूर्ण

	ret = v4l2_ctrl_handler_setup(&ctx->ctrl_hdl);
	अगर (ret)
		जाओ err_मुक्त_handler;

	ctx->fh.ctrl_handler = &ctx->ctrl_hdl;
	वापस 0;

err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
	वापस ret;
पूर्ण

अटल पूर्णांक rkvdec_खोलो(काष्ठा file *filp)
अणु
	काष्ठा rkvdec_dev *rkvdec = video_drvdata(filp);
	काष्ठा rkvdec_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = rkvdec;
	rkvdec_reset_coded_fmt(ctx);
	rkvdec_reset_decoded_fmt(ctx);
	v4l2_fh_init(&ctx->fh, video_devdata(filp));

	ret = rkvdec_init_ctrls(ctx);
	अगर (ret)
		जाओ err_मुक्त_ctx;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(rkvdec->m2m_dev, ctx,
					    rkvdec_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_cleanup_ctrls;
	पूर्ण

	filp->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	वापस 0;

err_cleanup_ctrls:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);

err_मुक्त_ctx:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक rkvdec_release(काष्ठा file *filp)
अणु
	काष्ठा rkvdec_ctx *ctx = fh_to_rkvdec_ctx(filp->निजी_data);

	v4l2_fh_del(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations rkvdec_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = rkvdec_खोलो,
	.release = rkvdec_release,
	.poll = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक rkvdec_v4l2_init(काष्ठा rkvdec_dev *rkvdec)
अणु
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर(rkvdec->dev, &rkvdec->v4l2_dev);
	अगर (ret) अणु
		dev_err(rkvdec->dev, "Failed to register V4L2 device\n");
		वापस ret;
	पूर्ण

	rkvdec->m2m_dev = v4l2_m2m_init(&rkvdec_m2m_ops);
	अगर (IS_ERR(rkvdec->m2m_dev)) अणु
		v4l2_err(&rkvdec->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(rkvdec->m2m_dev);
		जाओ err_unरेजिस्टर_v4l2;
	पूर्ण

	rkvdec->mdev.dev = rkvdec->dev;
	strscpy(rkvdec->mdev.model, "rkvdec", माप(rkvdec->mdev.model));
	strscpy(rkvdec->mdev.bus_info, "platform:rkvdec",
		माप(rkvdec->mdev.bus_info));
	media_device_init(&rkvdec->mdev);
	rkvdec->mdev.ops = &rkvdec_media_ops;
	rkvdec->v4l2_dev.mdev = &rkvdec->mdev;

	rkvdec->vdev.lock = &rkvdec->vdev_lock;
	rkvdec->vdev.v4l2_dev = &rkvdec->v4l2_dev;
	rkvdec->vdev.fops = &rkvdec_fops;
	rkvdec->vdev.release = video_device_release_empty;
	rkvdec->vdev.vfl_dir = VFL_सूची_M2M;
	rkvdec->vdev.device_caps = V4L2_CAP_STREAMING |
				   V4L2_CAP_VIDEO_M2M_MPLANE;
	rkvdec->vdev.ioctl_ops = &rkvdec_ioctl_ops;
	video_set_drvdata(&rkvdec->vdev, rkvdec);
	strscpy(rkvdec->vdev.name, "rkvdec", माप(rkvdec->vdev.name));

	ret = video_रेजिस्टर_device(&rkvdec->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&rkvdec->v4l2_dev, "Failed to register video device\n");
		जाओ err_cleanup_mc;
	पूर्ण

	ret = v4l2_m2m_रेजिस्टर_media_controller(rkvdec->m2m_dev, &rkvdec->vdev,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	अगर (ret) अणु
		v4l2_err(&rkvdec->v4l2_dev,
			 "Failed to initialize V4L2 M2M media controller\n");
		जाओ err_unरेजिस्टर_vdev;
	पूर्ण

	ret = media_device_रेजिस्टर(&rkvdec->mdev);
	अगर (ret) अणु
		v4l2_err(&rkvdec->v4l2_dev, "Failed to register media device\n");
		जाओ err_unरेजिस्टर_mc;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(rkvdec->m2m_dev);

err_unरेजिस्टर_vdev:
	video_unरेजिस्टर_device(&rkvdec->vdev);

err_cleanup_mc:
	media_device_cleanup(&rkvdec->mdev);
	v4l2_m2m_release(rkvdec->m2m_dev);

err_unरेजिस्टर_v4l2:
	v4l2_device_unरेजिस्टर(&rkvdec->v4l2_dev);
	वापस ret;
पूर्ण

अटल व्योम rkvdec_v4l2_cleanup(काष्ठा rkvdec_dev *rkvdec)
अणु
	media_device_unरेजिस्टर(&rkvdec->mdev);
	v4l2_m2m_unरेजिस्टर_media_controller(rkvdec->m2m_dev);
	video_unरेजिस्टर_device(&rkvdec->vdev);
	media_device_cleanup(&rkvdec->mdev);
	v4l2_m2m_release(rkvdec->m2m_dev);
	v4l2_device_unरेजिस्टर(&rkvdec->v4l2_dev);
पूर्ण

अटल irqवापस_t rkvdec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा rkvdec_dev *rkvdec = priv;
	क्रमागत vb2_buffer_state state;
	u32 status;

	status = पढ़ोl(rkvdec->regs + RKVDEC_REG_INTERRUPT);
	state = (status & RKVDEC_RDY_STA) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_ERROR;

	ग_लिखोl(0, rkvdec->regs + RKVDEC_REG_INTERRUPT);
	अगर (cancel_delayed_work(&rkvdec->watchकरोg_work)) अणु
		काष्ठा rkvdec_ctx *ctx;

		ctx = v4l2_m2m_get_curr_priv(rkvdec->m2m_dev);
		rkvdec_job_finish(ctx, state);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rkvdec_watchकरोg_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rkvdec_dev *rkvdec;
	काष्ठा rkvdec_ctx *ctx;

	rkvdec = container_of(to_delayed_work(work), काष्ठा rkvdec_dev,
			      watchकरोg_work);
	ctx = v4l2_m2m_get_curr_priv(rkvdec->m2m_dev);
	अगर (ctx) अणु
		dev_err(rkvdec->dev, "Frame processing timed out!\n");
		ग_लिखोl(RKVDEC_IRQ_DIS, rkvdec->regs + RKVDEC_REG_INTERRUPT);
		ग_लिखोl(0, rkvdec->regs + RKVDEC_REG_SYSCTRL);
		rkvdec_job_finish(ctx, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id of_rkvdec_match[] = अणु
	अणु .compatible = "rockchip,rk3399-vdec" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_rkvdec_match);

अटल स्थिर अक्षर * स्थिर rkvdec_clk_names[] = अणु
	"axi", "ahb", "cabac", "core"
पूर्ण;

अटल पूर्णांक rkvdec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rkvdec_dev *rkvdec;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret, irq;

	rkvdec = devm_kzalloc(&pdev->dev, माप(*rkvdec), GFP_KERNEL);
	अगर (!rkvdec)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, rkvdec);
	rkvdec->dev = &pdev->dev;
	mutex_init(&rkvdec->vdev_lock);
	INIT_DELAYED_WORK(&rkvdec->watchकरोg_work, rkvdec_watchकरोg_func);

	rkvdec->घड़ीs = devm_kसुस्मृति(&pdev->dev, ARRAY_SIZE(rkvdec_clk_names),
				      माप(*rkvdec->घड़ीs), GFP_KERNEL);
	अगर (!rkvdec->घड़ीs)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(rkvdec_clk_names); i++)
		rkvdec->घड़ीs[i].id = rkvdec_clk_names[i];

	ret = devm_clk_bulk_get(&pdev->dev, ARRAY_SIZE(rkvdec_clk_names),
				rkvdec->घड़ीs);
	अगर (ret)
		वापस ret;

	/*
	 * Bump ACLK to max. possible freq. (500 MHz) to improve perक्रमmance
	 * When 4k video playback.
	 */
	clk_set_rate(rkvdec->घड़ीs[0].clk, 500 * 1000 * 1000);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rkvdec->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rkvdec->regs))
		वापस PTR_ERR(rkvdec->regs);

	ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not set DMA coherent mask.\n");
		वापस ret;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					rkvdec_irq_handler, IRQF_ONESHOT,
					dev_name(&pdev->dev), rkvdec);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request vdec IRQ\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = rkvdec_v4l2_init(rkvdec);
	अगर (ret)
		जाओ err_disable_runसमय_pm;

	वापस 0;

err_disable_runसमय_pm:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rkvdec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rkvdec_dev *rkvdec = platक्रमm_get_drvdata(pdev);

	rkvdec_v4l2_cleanup(rkvdec);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rkvdec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rkvdec_dev *rkvdec = dev_get_drvdata(dev);

	वापस clk_bulk_prepare_enable(ARRAY_SIZE(rkvdec_clk_names),
				       rkvdec->घड़ीs);
पूर्ण

अटल पूर्णांक rkvdec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rkvdec_dev *rkvdec = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(ARRAY_SIZE(rkvdec_clk_names),
				   rkvdec->घड़ीs);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rkvdec_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(rkvdec_runसमय_suspend, rkvdec_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver rkvdec_driver = अणु
	.probe = rkvdec_probe,
	.हटाओ = rkvdec_हटाओ,
	.driver = अणु
		   .name = "rkvdec",
		   .of_match_table = of_rkvdec_match,
		   .pm = &rkvdec_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rkvdec_driver);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@collabora.com>");
MODULE_DESCRIPTION("Rockchip Video Decoder driver");
MODULE_LICENSE("GPL v2");
