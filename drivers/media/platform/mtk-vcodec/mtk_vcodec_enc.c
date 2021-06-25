<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <soc/mediatek/smi.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_enc.h"
#समावेश "mtk_vcodec_intr.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "venc_drv_if.h"

#घोषणा MTK_VENC_MIN_W	160U
#घोषणा MTK_VENC_MIN_H	128U
#घोषणा MTK_VENC_MAX_W	1920U
#घोषणा MTK_VENC_MAX_H	1088U
#घोषणा DFT_CFG_WIDTH	MTK_VENC_MIN_W
#घोषणा DFT_CFG_HEIGHT	MTK_VENC_MIN_H
#घोषणा MTK_MAX_CTRLS_HINT	20

#घोषणा MTK_DEFAULT_FRAMERATE_NUM 1001
#घोषणा MTK_DEFAULT_FRAMERATE_DENOM 30000

अटल व्योम mtk_venc_worker(काष्ठा work_काष्ठा *work);

अटल स्थिर काष्ठा v4l2_frmsize_stepwise mtk_venc_framesizes = अणु
	MTK_VENC_MIN_W, MTK_VENC_MAX_W, 16,
	MTK_VENC_MIN_H, MTK_VENC_MAX_H, 16,
पूर्ण;

#घोषणा NUM_SUPPORTED_FRAMESIZE ARRAY_SIZE(mtk_venc_framesizes)

अटल पूर्णांक vidioc_venc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा mtk_enc_params *p = &ctx->enc_params;
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_BITRATE val = %d",
			       ctrl->val);
		p->bitrate = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_BITRATE;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_B_FRAMES val = %d",
			       ctrl->val);
		p->num_b_frame = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE val = %d",
			       ctrl->val);
		p->rc_frame = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_MAX_QP val = %d",
			       ctrl->val);
		p->h264_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_HEADER_MODE val = %d",
			       ctrl->val);
		p->seq_hdr_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE val = %d",
			       ctrl->val);
		p->rc_mb = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_PROFILE val = %d",
			       ctrl->val);
		p->h264_profile = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_LEVEL val = %d",
			       ctrl->val);
		p->h264_level = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_I_PERIOD val = %d",
			       ctrl->val);
		p->पूर्णांकra_period = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_INTRA_PERIOD;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_GOP_SIZE val = %d",
			       ctrl->val);
		p->gop_size = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_GOP_SIZE;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME");
		p->क्रमce_पूर्णांकra = 1;
		ctx->param_change |= MTK_ENCODE_PARAM_FORCE_INTRA;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mtk_vcodec_enc_ctrl_ops = अणु
	.s_ctrl = vidioc_venc_s_ctrl,
पूर्ण;

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f,
			   स्थिर काष्ठा mtk_video_fmt *क्रमmats,
			   माप_प्रकार num_क्रमmats)
अणु
	अगर (f->index >= num_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_video_fmt *
mtk_venc_find_क्रमmat(u32 fourcc, स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < pdata->num_capture_क्रमmats; k++) अणु
		fmt = &pdata->capture_क्रमmats[k];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	क्रम (k = 0; k < pdata->num_output_क्रमmats; k++) अणु
		fmt = &pdata->output_क्रमmats[k];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;

	अगर (fsize->index != 0)
		वापस -EINVAL;

	fmt = mtk_venc_find_क्रमmat(fsize->pixel_क्रमmat,
				   fh_to_ctx(fh)->dev->venc_pdata);
	अगर (!fmt)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise = mtk_venc_framesizes;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata =
		fh_to_ctx(priv)->dev->venc_pdata;

	वापस vidioc_क्रमागत_fmt(f, pdata->capture_क्रमmats,
			       pdata->num_capture_क्रमmats);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata =
		fh_to_ctx(priv)->dev->venc_pdata;

	वापस vidioc_क्रमागत_fmt(f, pdata->output_क्रमmats,
			       pdata->num_output_क्रमmats);
पूर्ण

अटल पूर्णांक vidioc_venc_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MTK_VCODEC_ENC_NAME, माप(cap->driver));
	strscpy(cap->bus_info, MTK_PLATFORM_STR, माप(cap->bus_info));
	strscpy(cap->card, MTK_PLATFORM_STR, माप(cap->card));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_s_parm(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_fract *समयperframe = &a->parm.output.समयperframe;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	अगर (समयperframe->numerator == 0 || समयperframe->denominator == 0) अणु
		समयperframe->numerator = MTK_DEFAULT_FRAMERATE_NUM;
		समयperframe->denominator = MTK_DEFAULT_FRAMERATE_DENOM;
	पूर्ण

	ctx->enc_params.framerate_num = समयperframe->denominator;
	ctx->enc_params.framerate_denom = समयperframe->numerator;
	ctx->param_change |= MTK_ENCODE_PARAM_FRAMERATE;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_g_parm(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.output.समयperframe.denominator =
			ctx->enc_params.framerate_num;
	a->parm.output.समयperframe.numerator =
			ctx->enc_params.framerate_denom;

	वापस 0;
पूर्ण

अटल काष्ठा mtk_q_data *mtk_venc_get_q_data(काष्ठा mtk_vcodec_ctx *ctx,
					      क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->q_data[MTK_Q_DATA_SRC];

	वापस &ctx->q_data[MTK_Q_DATA_DST];
पूर्ण

/* V4L2 specअगरication suggests the driver corrects the क्रमmat काष्ठा अगर any of
 * the dimensions is unsupported
 */
अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f,
			  स्थिर काष्ठा mtk_video_fmt *fmt)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	pix_fmt_mp->field = V4L2_FIELD_NONE;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		pix_fmt_mp->num_planes = 1;
		pix_fmt_mp->plane_fmt[0].bytesperline = 0;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		पूर्णांक पंचांगp_w, पंचांगp_h;

		pix_fmt_mp->height = clamp(pix_fmt_mp->height,
					MTK_VENC_MIN_H,
					MTK_VENC_MAX_H);
		pix_fmt_mp->width = clamp(pix_fmt_mp->width,
					MTK_VENC_MIN_W,
					MTK_VENC_MAX_W);

		/* find next बंदr width align 16, heign align 32, size align
		 * 64 rectangle
		 */
		पंचांगp_w = pix_fmt_mp->width;
		पंचांगp_h = pix_fmt_mp->height;
		v4l_bound_align_image(&pix_fmt_mp->width,
					MTK_VENC_MIN_W,
					MTK_VENC_MAX_W, 4,
					&pix_fmt_mp->height,
					MTK_VENC_MIN_H,
					MTK_VENC_MAX_H, 5, 6);

		अगर (pix_fmt_mp->width < पंचांगp_w &&
			(pix_fmt_mp->width + 16) <= MTK_VENC_MAX_W)
			pix_fmt_mp->width += 16;
		अगर (pix_fmt_mp->height < पंचांगp_h &&
			(pix_fmt_mp->height + 32) <= MTK_VENC_MAX_H)
			pix_fmt_mp->height += 32;

		mtk_v4l2_debug(0,
			"before resize width=%d, height=%d, after resize width=%d, height=%d, sizeimage=%d %d",
			पंचांगp_w, पंचांगp_h, pix_fmt_mp->width,
			pix_fmt_mp->height,
			pix_fmt_mp->plane_fmt[0].sizeimage,
			pix_fmt_mp->plane_fmt[1].sizeimage);

		pix_fmt_mp->num_planes = fmt->num_planes;
		pix_fmt_mp->plane_fmt[0].sizeimage =
				pix_fmt_mp->width * pix_fmt_mp->height +
				((ALIGN(pix_fmt_mp->width, 16) * 2) * 16);
		pix_fmt_mp->plane_fmt[0].bytesperline = pix_fmt_mp->width;

		अगर (pix_fmt_mp->num_planes == 2) अणु
			pix_fmt_mp->plane_fmt[1].sizeimage =
				(pix_fmt_mp->width * pix_fmt_mp->height) / 2 +
				(ALIGN(pix_fmt_mp->width, 16) * 16);
			pix_fmt_mp->plane_fmt[2].sizeimage = 0;
			pix_fmt_mp->plane_fmt[1].bytesperline =
							pix_fmt_mp->width;
			pix_fmt_mp->plane_fmt[2].bytesperline = 0;
		पूर्ण अन्यथा अगर (pix_fmt_mp->num_planes == 3) अणु
			pix_fmt_mp->plane_fmt[1].sizeimage =
			pix_fmt_mp->plane_fmt[2].sizeimage =
				(pix_fmt_mp->width * pix_fmt_mp->height) / 4 +
				((ALIGN(pix_fmt_mp->width, 16) / 2) * 16);
			pix_fmt_mp->plane_fmt[1].bytesperline =
				pix_fmt_mp->plane_fmt[2].bytesperline =
				pix_fmt_mp->width / 2;
		पूर्ण
	पूर्ण

	pix_fmt_mp->flags = 0;

	वापस 0;
पूर्ण

अटल व्योम mtk_venc_set_param(काष्ठा mtk_vcodec_ctx *ctx,
				काष्ठा venc_enc_param *param)
अणु
	काष्ठा mtk_q_data *q_data_src = &ctx->q_data[MTK_Q_DATA_SRC];
	काष्ठा mtk_enc_params *enc_params = &ctx->enc_params;

	चयन (q_data_src->fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_I420;
		अवरोध;
	हाल V4L2_PIX_FMT_YVU420M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_YV12;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_NV12;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_NV21;
		अवरोध;
	शेष:
		mtk_v4l2_err("Unsupported fourcc =%d", q_data_src->fmt->fourcc);
		अवरोध;
	पूर्ण
	param->h264_profile = enc_params->h264_profile;
	param->h264_level = enc_params->h264_level;

	/* Config visible resolution */
	param->width = q_data_src->visible_width;
	param->height = q_data_src->visible_height;
	/* Config coded resolution */
	param->buf_width = q_data_src->coded_width;
	param->buf_height = q_data_src->coded_height;
	param->frm_rate = enc_params->framerate_num /
			enc_params->framerate_denom;
	param->पूर्णांकra_period = enc_params->पूर्णांकra_period;
	param->gop_size = enc_params->gop_size;
	param->bitrate = enc_params->bitrate;

	mtk_v4l2_debug(0,
		"fmt 0x%x, P/L %d/%d, w/h %d/%d, buf %d/%d, fps/bps %d/%d, gop %d, i_period %d",
		param->input_yuv_fmt, param->h264_profile,
		param->h264_level, param->width, param->height,
		param->buf_width, param->buf_height,
		param->frm_rate, param->bitrate,
		param->gop_size, param->पूर्णांकra_period);
पूर्ण

अटल पूर्णांक vidioc_venc_s_fmt_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_q_data *q_data;
	पूर्णांक i, ret;
	स्थिर काष्ठा mtk_video_fmt *fmt;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	अगर (!vq) अणु
		mtk_v4l2_err("fail to get vq");
		वापस -EINVAL;
	पूर्ण

	अगर (vb2_is_busy(vq)) अणु
		mtk_v4l2_err("queue busy");
		वापस -EBUSY;
	पूर्ण

	q_data = mtk_venc_get_q_data(ctx, f->type);
	अगर (!q_data) अणु
		mtk_v4l2_err("fail to get q data");
		वापस -EINVAL;
	पूर्ण

	fmt = mtk_venc_find_क्रमmat(f->fmt.pix.pixelक्रमmat, pdata);
	अगर (!fmt) अणु
		fmt = &ctx->dev->venc_pdata->capture_क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण

	q_data->fmt = fmt;
	ret = vidioc_try_fmt(f, q_data->fmt);
	अगर (ret)
		वापस ret;

	q_data->coded_width = f->fmt.pix_mp.width;
	q_data->coded_height = f->fmt.pix_mp.height;
	q_data->field = f->fmt.pix_mp.field;

	क्रम (i = 0; i < f->fmt.pix_mp.num_planes; i++) अणु
		काष्ठा v4l2_plane_pix_क्रमmat	*plane_fmt;

		plane_fmt = &f->fmt.pix_mp.plane_fmt[i];
		q_data->bytesperline[i]	= plane_fmt->bytesperline;
		q_data->sizeimage[i] = plane_fmt->sizeimage;
	पूर्ण

	अगर (ctx->state == MTK_STATE_FREE) अणु
		ret = venc_अगर_init(ctx, q_data->fmt->fourcc);
		अगर (ret) अणु
			mtk_v4l2_err("venc_if_init failed=%d, codec type=%x",
					ret, q_data->fmt->fourcc);
			वापस -EBUSY;
		पूर्ण
		ctx->state = MTK_STATE_INIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_s_fmt_out(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_q_data *q_data;
	पूर्णांक ret, i;
	स्थिर काष्ठा mtk_video_fmt *fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	अगर (!vq) अणु
		mtk_v4l2_err("fail to get vq");
		वापस -EINVAL;
	पूर्ण

	अगर (vb2_is_busy(vq)) अणु
		mtk_v4l2_err("queue busy");
		वापस -EBUSY;
	पूर्ण

	q_data = mtk_venc_get_q_data(ctx, f->type);
	अगर (!q_data) अणु
		mtk_v4l2_err("fail to get q data");
		वापस -EINVAL;
	पूर्ण

	fmt = mtk_venc_find_क्रमmat(f->fmt.pix.pixelक्रमmat, pdata);
	अगर (!fmt) अणु
		fmt = &ctx->dev->venc_pdata->output_क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण

	pix_fmt_mp->height = clamp(pix_fmt_mp->height,
				MTK_VENC_MIN_H,
				MTK_VENC_MAX_H);
	pix_fmt_mp->width = clamp(pix_fmt_mp->width,
				MTK_VENC_MIN_W,
				MTK_VENC_MAX_W);

	q_data->visible_width = f->fmt.pix_mp.width;
	q_data->visible_height = f->fmt.pix_mp.height;
	q_data->fmt = fmt;
	ret = vidioc_try_fmt(f, q_data->fmt);
	अगर (ret)
		वापस ret;

	q_data->coded_width = f->fmt.pix_mp.width;
	q_data->coded_height = f->fmt.pix_mp.height;

	q_data->field = f->fmt.pix_mp.field;
	ctx->colorspace = f->fmt.pix_mp.colorspace;
	ctx->ycbcr_enc = f->fmt.pix_mp.ycbcr_enc;
	ctx->quantization = f->fmt.pix_mp.quantization;
	ctx->xfer_func = f->fmt.pix_mp.xfer_func;

	क्रम (i = 0; i < f->fmt.pix_mp.num_planes; i++) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt;

		plane_fmt = &f->fmt.pix_mp.plane_fmt[i];
		q_data->bytesperline[i] = plane_fmt->bytesperline;
		q_data->sizeimage[i] = plane_fmt->sizeimage;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_g_fmt(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &f->fmt.pix_mp;
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_q_data *q_data;
	पूर्णांक i;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = mtk_venc_get_q_data(ctx, f->type);

	pix->width = q_data->coded_width;
	pix->height = q_data->coded_height;
	pix->pixelक्रमmat = q_data->fmt->fourcc;
	pix->field = q_data->field;
	pix->num_planes = q_data->fmt->num_planes;
	क्रम (i = 0; i < pix->num_planes; i++) अणु
		pix->plane_fmt[i].bytesperline = q_data->bytesperline[i];
		pix->plane_fmt[i].sizeimage = q_data->sizeimage[i];
	पूर्ण

	pix->flags = 0;
	pix->colorspace = ctx->colorspace;
	pix->ycbcr_enc = ctx->ycbcr_enc;
	pix->quantization = ctx->quantization;
	pix->xfer_func = ctx->xfer_func;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;

	fmt = mtk_venc_find_क्रमmat(f->fmt.pix.pixelक्रमmat, pdata);
	अगर (!fmt) अणु
		fmt = &ctx->dev->venc_pdata->capture_क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण
	f->fmt.pix_mp.colorspace = ctx->colorspace;
	f->fmt.pix_mp.ycbcr_enc = ctx->ycbcr_enc;
	f->fmt.pix_mp.quantization = ctx->quantization;
	f->fmt.pix_mp.xfer_func = ctx->xfer_func;

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा mtk_video_fmt *fmt;
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	स्थिर काष्ठा mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;

	fmt = mtk_venc_find_क्रमmat(f->fmt.pix.pixelक्रमmat, pdata);
	अगर (!fmt) अणु
		fmt = &ctx->dev->venc_pdata->output_क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	पूर्ण
	अगर (!f->fmt.pix_mp.colorspace) अणु
		f->fmt.pix_mp.colorspace = V4L2_COLORSPACE_REC709;
		f->fmt.pix_mp.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		f->fmt.pix_mp.quantization = V4L2_QUANTIZATION_DEFAULT;
		f->fmt.pix_mp.xfer_func = V4L2_XFER_FUNC_DEFAULT;
	पूर्ण

	वापस vidioc_try_fmt(f, fmt);
पूर्ण

अटल पूर्णांक vidioc_venc_g_selection(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा mtk_q_data *q_data;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	q_data = mtk_venc_get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		s->r.top = 0;
		s->r.left = 0;
		s->r.width = q_data->coded_width;
		s->r.height = q_data->coded_height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		s->r.top = 0;
		s->r.left = 0;
		s->r.width = q_data->visible_width;
		s->r.height = q_data->visible_height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_s_selection(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	काष्ठा mtk_q_data *q_data;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	q_data = mtk_venc_get_q_data(ctx, s->type);
	अगर (!q_data)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		/* Only support crop from (0,0) */
		s->r.top = 0;
		s->r.left = 0;
		s->r.width = min(s->r.width, q_data->coded_width);
		s->r.height = min(s->r.height, q_data->coded_height);
		q_data->visible_width = s->r.width;
		q_data->visible_height = s->r.height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_venc_qbuf(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MTK_STATE_ABORT) अणु
		mtk_v4l2_err("[%d] Call on QBUF after unrecoverable error",
				ctx->id);
		वापस -EIO;
	पूर्ण

	वापस v4l2_m2m_qbuf(file, ctx->m2m_ctx, buf);
पूर्ण

अटल पूर्णांक vidioc_venc_dqbuf(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MTK_STATE_ABORT) अणु
		mtk_v4l2_err("[%d] Call on QBUF after unrecoverable error",
				ctx->id);
		वापस -EIO;
	पूर्ण

	वापस v4l2_m2m_dqbuf(file, ctx->m2m_ctx, buf);
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops mtk_venc_ioctl_ops = अणु
	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= vidioc_venc_qbuf,
	.vidioc_dqbuf			= vidioc_venc_dqbuf,

	.vidioc_querycap		= vidioc_venc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= vidioc_क्रमागत_fmt_vid_out,
	.vidioc_क्रमागत_framesizes		= vidioc_क्रमागत_framesizes,

	.vidioc_try_fmt_vid_cap_mplane	= vidioc_try_fmt_vid_cap_mplane,
	.vidioc_try_fmt_vid_out_mplane	= vidioc_try_fmt_vid_out_mplane,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,

	.vidioc_s_parm			= vidioc_venc_s_parm,
	.vidioc_g_parm			= vidioc_venc_g_parm,
	.vidioc_s_fmt_vid_cap_mplane	= vidioc_venc_s_fmt_cap,
	.vidioc_s_fmt_vid_out_mplane	= vidioc_venc_s_fmt_out,

	.vidioc_g_fmt_vid_cap_mplane	= vidioc_venc_g_fmt,
	.vidioc_g_fmt_vid_out_mplane	= vidioc_venc_g_fmt,

	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,

	.vidioc_g_selection		= vidioc_venc_g_selection,
	.vidioc_s_selection		= vidioc_venc_s_selection,
पूर्ण;

अटल पूर्णांक vb2ops_venc_queue_setup(काष्ठा vb2_queue *vq,
				   अचिन्हित पूर्णांक *nbuffers,
				   अचिन्हित पूर्णांक *nplanes,
				   अचिन्हित पूर्णांक sizes[],
				   काष्ठा device *alloc_devs[])
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा mtk_q_data *q_data;
	अचिन्हित पूर्णांक i;

	q_data = mtk_venc_get_q_data(ctx, vq->type);

	अगर (q_data == शून्य)
		वापस -EINVAL;

	अगर (*nplanes) अणु
		क्रम (i = 0; i < *nplanes; i++)
			अगर (sizes[i] < q_data->sizeimage[i])
				वापस -EINVAL;
	पूर्ण अन्यथा अणु
		*nplanes = q_data->fmt->num_planes;
		क्रम (i = 0; i < *nplanes; i++)
			sizes[i] = q_data->sizeimage[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vb2ops_venc_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_q_data *q_data;
	पूर्णांक i;

	q_data = mtk_venc_get_q_data(ctx, vb->vb2_queue->type);

	क्रम (i = 0; i < q_data->fmt->num_planes; i++) अणु
		अगर (vb2_plane_size(vb, i) < q_data->sizeimage[i]) अणु
			mtk_v4l2_err("data will not fit into plane %d (%lu < %d)",
				i, vb2_plane_size(vb, i),
				q_data->sizeimage[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vb2ops_venc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2_v4l2 =
			container_of(vb, काष्ठा vb2_v4l2_buffer, vb2_buf);

	काष्ठा mtk_video_enc_buf *mtk_buf =
			container_of(vb2_v4l2, काष्ठा mtk_video_enc_buf,
				     m2m_buf.vb);

	अगर ((vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) &&
	    (ctx->param_change != MTK_ENCODE_PARAM_NONE)) अणु
		mtk_v4l2_debug(1, "[%d] Before id=%d encode parameter change %x",
			       ctx->id,
			       vb2_v4l2->vb2_buf.index,
			       ctx->param_change);
		mtk_buf->param_change = ctx->param_change;
		mtk_buf->enc_params = ctx->enc_params;
		ctx->param_change = MTK_ENCODE_PARAM_NONE;
	पूर्ण

	v4l2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4l2_buffer(vb));
पूर्ण

अटल पूर्णांक vb2ops_venc_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा venc_enc_param param;
	पूर्णांक ret;
	पूर्णांक i;

	/* Once state turn पूर्णांकo MTK_STATE_ABORT, we need stop_streaming
	  * to clear it
	  */
	अगर ((ctx->state == MTK_STATE_ABORT) || (ctx->state == MTK_STATE_FREE)) अणु
		ret = -EIO;
		जाओ err_start_stream;
	पूर्ण

	/* Do the initialization when both start_streaming have been called */
	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		अगर (!vb2_start_streaming_called(&ctx->m2m_ctx->cap_q_ctx.q))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!vb2_start_streaming_called(&ctx->m2m_ctx->out_q_ctx.q))
			वापस 0;
	पूर्ण

	ret = pm_runसमय_resume_and_get(&ctx->dev->plat_dev->dev);
	अगर (ret < 0) अणु
		mtk_v4l2_err("pm_runtime_resume_and_get fail %d", ret);
		जाओ err_start_stream;
	पूर्ण

	mtk_venc_set_param(ctx, &param);
	ret = venc_अगर_set_param(ctx, VENC_SET_PARAM_ENC, &param);
	अगर (ret) अणु
		mtk_v4l2_err("venc_if_set_param failed=%d", ret);
		ctx->state = MTK_STATE_ABORT;
		जाओ err_set_param;
	पूर्ण
	ctx->param_change = MTK_ENCODE_PARAM_NONE;

	अगर ((ctx->q_data[MTK_Q_DATA_DST].fmt->fourcc == V4L2_PIX_FMT_H264) &&
	    (ctx->enc_params.seq_hdr_mode !=
				V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE)) अणु
		ret = venc_अगर_set_param(ctx,
					VENC_SET_PARAM_PREPEND_HEADER,
					शून्य);
		अगर (ret) अणु
			mtk_v4l2_err("venc_if_set_param failed=%d", ret);
			ctx->state = MTK_STATE_ABORT;
			जाओ err_set_param;
		पूर्ण
		ctx->state = MTK_STATE_HEADER;
	पूर्ण

	वापस 0;

err_set_param:
	ret = pm_runसमय_put(&ctx->dev->plat_dev->dev);
	अगर (ret < 0)
		mtk_v4l2_err("pm_runtime_put fail %d", ret);

err_start_stream:
	क्रम (i = 0; i < q->num_buffers; ++i) अणु
		काष्ठा vb2_buffer *buf = vb2_get_buffer(q, i);

		/*
		 * FIXME: This check is not needed as only active buffers
		 * can be marked as करोne.
		 */
		अगर (buf->state == VB2_BUF_STATE_ACTIVE) अणु
			mtk_v4l2_debug(0, "[%d] id=%d, type=%d, %d -> VB2_BUF_STATE_QUEUED",
					ctx->id, i, q->type,
					(पूर्णांक)buf->state);
			v4l2_m2m_buf_करोne(to_vb2_v4l2_buffer(buf),
					  VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vb2ops_venc_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	पूर्णांक ret;

	mtk_v4l2_debug(2, "[%d]-> type=%d", ctx->id, q->type);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		जबतक ((dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx))) अणु
			dst_buf->vb2_buf.planes[0].bytesused = 0;
			v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक ((src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx)))
			v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	अगर ((q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	     vb2_is_streaming(&ctx->m2m_ctx->out_q_ctx.q)) ||
	    (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
	     vb2_is_streaming(&ctx->m2m_ctx->cap_q_ctx.q))) अणु
		mtk_v4l2_debug(1, "[%d]-> q type %d out=%d cap=%d",
			       ctx->id, q->type,
			       vb2_is_streaming(&ctx->m2m_ctx->out_q_ctx.q),
			       vb2_is_streaming(&ctx->m2m_ctx->cap_q_ctx.q));
		वापस;
	पूर्ण

	/* Release the encoder अगर both streams are stopped. */
	ret = venc_अगर_deinit(ctx);
	अगर (ret)
		mtk_v4l2_err("venc_if_deinit failed=%d", ret);

	ret = pm_runसमय_put(&ctx->dev->plat_dev->dev);
	अगर (ret < 0)
		mtk_v4l2_err("pm_runtime_put fail %d", ret);

	ctx->state = MTK_STATE_FREE;
पूर्ण

अटल पूर्णांक vb2ops_venc_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops mtk_venc_vb2_ops = अणु
	.queue_setup		= vb2ops_venc_queue_setup,
	.buf_out_validate	= vb2ops_venc_buf_out_validate,
	.buf_prepare		= vb2ops_venc_buf_prepare,
	.buf_queue		= vb2ops_venc_buf_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.start_streaming	= vb2ops_venc_start_streaming,
	.stop_streaming		= vb2ops_venc_stop_streaming,
पूर्ण;

अटल पूर्णांक mtk_venc_encode_header(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;
	पूर्णांक ret;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा mtk_vcodec_mem bs_buf;
	काष्ठा venc_करोne_result enc_result;

	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
	अगर (!dst_buf) अणु
		mtk_v4l2_debug(1, "No dst buffer");
		वापस -EINVAL;
	पूर्ण

	bs_buf.va = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	bs_buf.dma_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	bs_buf.size = (माप_प्रकार)dst_buf->vb2_buf.planes[0].length;

	mtk_v4l2_debug(1,
			"[%d] buf id=%d va=0x%p dma_addr=0x%llx size=%zu",
			ctx->id,
			dst_buf->vb2_buf.index, bs_buf.va,
			(u64)bs_buf.dma_addr,
			bs_buf.size);

	ret = venc_अगर_encode(ctx,
			VENC_START_OPT_ENCODE_SEQUENCE_HEADER,
			शून्य, &bs_buf, &enc_result);

	अगर (ret) अणु
		dst_buf->vb2_buf.planes[0].bytesused = 0;
		ctx->state = MTK_STATE_ABORT;
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
		mtk_v4l2_err("venc_if_encode failed=%d", ret);
		वापस -EINVAL;
	पूर्ण
	src_buf = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	अगर (src_buf) अणु
		dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
		dst_buf->समयcode = src_buf->समयcode;
	पूर्ण अन्यथा अणु
		mtk_v4l2_err("No timestamp for the header buffer.");
	पूर्ण

	ctx->state = MTK_STATE_HEADER;
	dst_buf->vb2_buf.planes[0].bytesused = enc_result.bs_size;
	v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_venc_param_change(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा venc_enc_param enc_prm;
	काष्ठा vb2_v4l2_buffer *vb2_v4l2 = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	काष्ठा mtk_video_enc_buf *mtk_buf =
			container_of(vb2_v4l2, काष्ठा mtk_video_enc_buf,
				     m2m_buf.vb);

	पूर्णांक ret = 0;

	स_रखो(&enc_prm, 0, माप(enc_prm));
	अगर (mtk_buf->param_change == MTK_ENCODE_PARAM_NONE)
		वापस 0;

	अगर (mtk_buf->param_change & MTK_ENCODE_PARAM_BITRATE) अणु
		enc_prm.bitrate = mtk_buf->enc_params.bitrate;
		mtk_v4l2_debug(1, "[%d] id=%d, change param br=%d",
				ctx->id,
				vb2_v4l2->vb2_buf.index,
				enc_prm.bitrate);
		ret |= venc_अगर_set_param(ctx,
					 VENC_SET_PARAM_ADJUST_BITRATE,
					 &enc_prm);
	पूर्ण
	अगर (!ret && mtk_buf->param_change & MTK_ENCODE_PARAM_FRAMERATE) अणु
		enc_prm.frm_rate = mtk_buf->enc_params.framerate_num /
				   mtk_buf->enc_params.framerate_denom;
		mtk_v4l2_debug(1, "[%d] id=%d, change param fr=%d",
			       ctx->id,
			       vb2_v4l2->vb2_buf.index,
			       enc_prm.frm_rate);
		ret |= venc_अगर_set_param(ctx,
					 VENC_SET_PARAM_ADJUST_FRAMERATE,
					 &enc_prm);
	पूर्ण
	अगर (!ret && mtk_buf->param_change & MTK_ENCODE_PARAM_GOP_SIZE) अणु
		enc_prm.gop_size = mtk_buf->enc_params.gop_size;
		mtk_v4l2_debug(1, "change param intra period=%d",
			       enc_prm.gop_size);
		ret |= venc_अगर_set_param(ctx,
					 VENC_SET_PARAM_GOP_SIZE,
					 &enc_prm);
	पूर्ण
	अगर (!ret && mtk_buf->param_change & MTK_ENCODE_PARAM_FORCE_INTRA) अणु
		mtk_v4l2_debug(1, "[%d] id=%d, change param force I=%d",
				ctx->id,
				vb2_v4l2->vb2_buf.index,
				mtk_buf->enc_params.क्रमce_पूर्णांकra);
		अगर (mtk_buf->enc_params.क्रमce_पूर्णांकra)
			ret |= venc_अगर_set_param(ctx,
						 VENC_SET_PARAM_FORCE_INTRA,
						 शून्य);
	पूर्ण

	mtk_buf->param_change = MTK_ENCODE_PARAM_NONE;

	अगर (ret) अणु
		ctx->state = MTK_STATE_ABORT;
		mtk_v4l2_err("venc_if_set_param %d failed=%d",
				mtk_buf->param_change, ret);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * v4l2_m2m_streamoff() holds dev_mutex and रुकोs mtk_venc_worker()
 * to call v4l2_m2m_job_finish().
 * If mtk_venc_worker() tries to acquire dev_mutex, it will deadlock.
 * So this function must not try to acquire dev->dev_mutex.
 * This means v4l2 ioctls and mtk_venc_worker() can run at the same समय.
 * mtk_venc_worker() should be carefully implemented to aव्योम bugs.
 */
अटल व्योम mtk_venc_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = container_of(work, काष्ठा mtk_vcodec_ctx,
				    encode_work);
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा venc_frm_buf frm_buf;
	काष्ठा mtk_vcodec_mem bs_buf;
	काष्ठा venc_करोne_result enc_result;
	पूर्णांक ret, i;

	/* check dst_buf, dst_buf may be हटाओd in device_run
	 * to stored encकरोe header so we need check dst_buf and
	 * call job_finish here to prevent recursion
	 */
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
	अगर (!dst_buf) अणु
		v4l2_m2m_job_finish(ctx->dev->m2m_dev_enc, ctx->m2m_ctx);
		वापस;
	पूर्ण

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
	स_रखो(&frm_buf, 0, माप(frm_buf));
	क्रम (i = 0; i < src_buf->vb2_buf.num_planes ; i++) अणु
		frm_buf.fb_addr[i].dma_addr =
				vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, i);
		frm_buf.fb_addr[i].size =
				(माप_प्रकार)src_buf->vb2_buf.planes[i].length;
	पूर्ण
	bs_buf.va = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	bs_buf.dma_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	bs_buf.size = (माप_प्रकार)dst_buf->vb2_buf.planes[0].length;

	mtk_v4l2_debug(2,
			"Framebuf PA=%llx Size=0x%zx;PA=0x%llx Size=0x%zx;PA=0x%llx Size=%zu",
			(u64)frm_buf.fb_addr[0].dma_addr,
			frm_buf.fb_addr[0].size,
			(u64)frm_buf.fb_addr[1].dma_addr,
			frm_buf.fb_addr[1].size,
			(u64)frm_buf.fb_addr[2].dma_addr,
			frm_buf.fb_addr[2].size);

	ret = venc_अगर_encode(ctx, VENC_START_OPT_ENCODE_FRAME,
			     &frm_buf, &bs_buf, &enc_result);

	dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
	dst_buf->समयcode = src_buf->समयcode;

	अगर (enc_result.is_key_frm)
		dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;

	अगर (ret) अणु
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
		dst_buf->vb2_buf.planes[0].bytesused = 0;
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
		mtk_v4l2_err("venc_if_encode failed=%d", ret);
	पूर्ण अन्यथा अणु
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);
		dst_buf->vb2_buf.planes[0].bytesused = enc_result.bs_size;
		v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_DONE);
		mtk_v4l2_debug(2, "venc_if_encode bs size=%d",
				 enc_result.bs_size);
	पूर्ण

	v4l2_m2m_job_finish(ctx->dev->m2m_dev_enc, ctx->m2m_ctx);

	mtk_v4l2_debug(1, "<=== src_buf[%d] dst_buf[%d] venc_if_encode ret=%d Size=%u===>",
			src_buf->vb2_buf.index, dst_buf->vb2_buf.index, ret,
			enc_result.bs_size);
पूर्ण

अटल व्योम m2mops_venc_device_run(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;

	अगर ((ctx->q_data[MTK_Q_DATA_DST].fmt->fourcc == V4L2_PIX_FMT_H264) &&
	    (ctx->state != MTK_STATE_HEADER)) अणु
		/* encode h264 sps/pps header */
		mtk_venc_encode_header(ctx);
		queue_work(ctx->dev->encode_workqueue, &ctx->encode_work);
		वापस;
	पूर्ण

	mtk_venc_param_change(ctx);
	queue_work(ctx->dev->encode_workqueue, &ctx->encode_work);
पूर्ण

अटल पूर्णांक m2mops_venc_job_पढ़ोy(व्योम *m2m_priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = m2m_priv;

	अगर (ctx->state == MTK_STATE_ABORT || ctx->state == MTK_STATE_FREE) अणु
		mtk_v4l2_debug(3, "[%d]Not ready: state=0x%x.",
			       ctx->id, ctx->state);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम m2mops_venc_job_पात(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;

	ctx->state = MTK_STATE_ABORT;
पूर्ण

स्थिर काष्ठा v4l2_m2m_ops mtk_venc_m2m_ops = अणु
	.device_run	= m2mops_venc_device_run,
	.job_पढ़ोy	= m2mops_venc_job_पढ़ोy,
	.job_पात	= m2mops_venc_job_पात,
पूर्ण;

व्योम mtk_vcodec_enc_set_शेष_params(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा mtk_q_data *q_data;

	ctx->m2m_ctx->q_lock = &ctx->dev->dev_mutex;
	ctx->fh.m2m_ctx = ctx->m2m_ctx;
	ctx->fh.ctrl_handler = &ctx->ctrl_hdl;
	INIT_WORK(&ctx->encode_work, mtk_venc_worker);

	ctx->colorspace = V4L2_COLORSPACE_REC709;
	ctx->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	ctx->quantization = V4L2_QUANTIZATION_DEFAULT;
	ctx->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	q_data = &ctx->q_data[MTK_Q_DATA_SRC];
	स_रखो(q_data, 0, माप(काष्ठा mtk_q_data));
	q_data->visible_width = DFT_CFG_WIDTH;
	q_data->visible_height = DFT_CFG_HEIGHT;
	q_data->coded_width = DFT_CFG_WIDTH;
	q_data->coded_height = DFT_CFG_HEIGHT;
	q_data->field = V4L2_FIELD_NONE;

	q_data->fmt = &ctx->dev->venc_pdata->output_क्रमmats[0];

	v4l_bound_align_image(&q_data->coded_width,
				MTK_VENC_MIN_W,
				MTK_VENC_MAX_W, 4,
				&q_data->coded_height,
				MTK_VENC_MIN_H,
				MTK_VENC_MAX_H, 5, 6);

	अगर (q_data->coded_width < DFT_CFG_WIDTH &&
		(q_data->coded_width + 16) <= MTK_VENC_MAX_W)
		q_data->coded_width += 16;
	अगर (q_data->coded_height < DFT_CFG_HEIGHT &&
		(q_data->coded_height + 32) <= MTK_VENC_MAX_H)
		q_data->coded_height += 32;

	q_data->sizeimage[0] =
		q_data->coded_width * q_data->coded_height+
		((ALIGN(q_data->coded_width, 16) * 2) * 16);
	q_data->bytesperline[0] = q_data->coded_width;
	q_data->sizeimage[1] =
		(q_data->coded_width * q_data->coded_height) / 2 +
		(ALIGN(q_data->coded_width, 16) * 16);
	q_data->bytesperline[1] = q_data->coded_width;

	q_data = &ctx->q_data[MTK_Q_DATA_DST];
	स_रखो(q_data, 0, माप(काष्ठा mtk_q_data));
	q_data->coded_width = DFT_CFG_WIDTH;
	q_data->coded_height = DFT_CFG_HEIGHT;
	q_data->fmt = &ctx->dev->venc_pdata->capture_क्रमmats[0];
	q_data->field = V4L2_FIELD_NONE;
	ctx->q_data[MTK_Q_DATA_DST].sizeimage[0] =
		DFT_CFG_WIDTH * DFT_CFG_HEIGHT;
	ctx->q_data[MTK_Q_DATA_DST].bytesperline[0] = 0;

	ctx->enc_params.framerate_num = MTK_DEFAULT_FRAMERATE_NUM;
	ctx->enc_params.framerate_denom = MTK_DEFAULT_FRAMERATE_DENOM;
पूर्ण

पूर्णांक mtk_vcodec_enc_ctrls_setup(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &mtk_vcodec_enc_ctrl_ops;
	काष्ठा v4l2_ctrl_handler *handler = &ctx->ctrl_hdl;

	v4l2_ctrl_handler_init(handler, MTK_MAX_CTRLS_HINT);

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MIN_BUFFERS_FOR_OUTPUT,
			  1, 1, 1, 1);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_BITRATE,
			  ctx->dev->venc_pdata->min_bitrate,
			  ctx->dev->venc_pdata->max_bitrate, 1, 4000000);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_B_FRAMES,
			0, 2, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE,
			0, 1, 1, 1);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_H264_MAX_QP,
			0, 51, 1, 51);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_H264_I_PERIOD,
			0, 65535, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			0, 65535, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE,
			0, 1, 1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME,
			0, 0, 0, 0);
	v4l2_ctrl_new_std_menu(handler, ops,
			V4L2_CID_MPEG_VIDEO_HEADER_MODE,
			V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
			0, V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE);
	v4l2_ctrl_new_std_menu(handler, ops, V4L2_CID_MPEG_VIDEO_H264_PROखाता,
			V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
			0, V4L2_MPEG_VIDEO_H264_PROखाता_HIGH);
	v4l2_ctrl_new_std_menu(handler, ops, V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_4_2,
			0, V4L2_MPEG_VIDEO_H264_LEVEL_4_0);
	अगर (handler->error) अणु
		mtk_v4l2_err("Init control handler fail %d",
				handler->error);
		वापस handler->error;
	पूर्ण

	v4l2_ctrl_handler_setup(&ctx->ctrl_hdl);

	वापस 0;
पूर्ण

पूर्णांक mtk_vcodec_enc_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = priv;
	पूर्णांक ret;

	/* Note: VB2_USERPTR works with dma-contig because mt8173
	 * support iommu
	 * https://patchwork.kernel.org/patch/8335461/
	 * https://patchwork.kernel.org/patch/7596181/
	 */
	src_vq->type		= V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes	= VB2_DMABUF | VB2_MMAP | VB2_USERPTR;
	src_vq->drv_priv	= ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा mtk_video_enc_buf);
	src_vq->ops		= &mtk_venc_vb2_ops;
	src_vq->mem_ops		= &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock		= &ctx->dev->dev_mutex;
	src_vq->dev		= &ctx->dev->plat_dev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes	= VB2_DMABUF | VB2_MMAP | VB2_USERPTR;
	dst_vq->drv_priv	= ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops		= &mtk_venc_vb2_ops;
	dst_vq->mem_ops		= &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock		= &ctx->dev->dev_mutex;
	dst_vq->dev		= &ctx->dev->plat_dev->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

पूर्णांक mtk_venc_unlock(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा mtk_vcodec_dev *dev = ctx->dev;

	mutex_unlock(&dev->enc_mutex);
	वापस 0;
पूर्ण

पूर्णांक mtk_venc_lock(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा mtk_vcodec_dev *dev = ctx->dev;

	mutex_lock(&dev->enc_mutex);
	वापस 0;
पूर्ण

व्योम mtk_vcodec_enc_release(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	पूर्णांक ret = venc_अगर_deinit(ctx);

	अगर (ret)
		mtk_v4l2_err("venc_if_deinit failed=%d", ret);

	ctx->state = MTK_STATE_FREE;
पूर्ण
