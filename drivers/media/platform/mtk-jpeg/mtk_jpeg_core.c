<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 *         Rick Chang <rick.chang@mediatek.com>
 *         Xia Jiang <xia.jiang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <soc/mediatek/smi.h>

#समावेश "mtk_jpeg_enc_hw.h"
#समावेश "mtk_jpeg_dec_hw.h"
#समावेश "mtk_jpeg_core.h"
#समावेश "mtk_jpeg_dec_parse.h"

अटल काष्ठा mtk_jpeg_fmt mtk_jpeg_enc_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_JPEG,
		.colplanes	= 1,
		.flags		= MTK_JPEG_FMT_FLAG_CAPTURE,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12M,
		.hw_क्रमmat	= JPEG_ENC_YUV_FORMAT_NV12,
		.h_sample	= अणु4, 4पूर्ण,
		.v_sample	= अणु4, 2पूर्ण,
		.colplanes	= 2,
		.h_align	= 4,
		.v_align	= 4,
		.flags		= MTK_JPEG_FMT_FLAG_OUTPUT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21M,
		.hw_क्रमmat	= JEPG_ENC_YUV_FORMAT_NV21,
		.h_sample	= अणु4, 4पूर्ण,
		.v_sample	= अणु4, 2पूर्ण,
		.colplanes	= 2,
		.h_align	= 4,
		.v_align	= 4,
		.flags		= MTK_JPEG_FMT_FLAG_OUTPUT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.hw_क्रमmat	= JPEG_ENC_YUV_FORMAT_YUYV,
		.h_sample	= अणु8पूर्ण,
		.v_sample	= अणु4पूर्ण,
		.colplanes	= 1,
		.h_align	= 5,
		.v_align	= 3,
		.flags		= MTK_JPEG_FMT_FLAG_OUTPUT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.hw_क्रमmat	= JPEG_ENC_YUV_FORMAT_YVYU,
		.h_sample	= अणु8पूर्ण,
		.v_sample	= अणु4पूर्ण,
		.colplanes	= 1,
		.h_align	= 5,
		.v_align	= 3,
		.flags		= MTK_JPEG_FMT_FLAG_OUTPUT,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtk_jpeg_fmt mtk_jpeg_dec_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_JPEG,
		.colplanes	= 1,
		.flags		= MTK_JPEG_FMT_FLAG_OUTPUT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV420M,
		.h_sample	= अणु4, 2, 2पूर्ण,
		.v_sample	= अणु4, 2, 2पूर्ण,
		.colplanes	= 3,
		.h_align	= 5,
		.v_align	= 4,
		.flags		= MTK_JPEG_FMT_FLAG_CAPTURE,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV422M,
		.h_sample	= अणु4, 2, 2पूर्ण,
		.v_sample	= अणु4, 4, 4पूर्ण,
		.colplanes	= 3,
		.h_align	= 5,
		.v_align	= 3,
		.flags		= MTK_JPEG_FMT_FLAG_CAPTURE,
	पूर्ण,
पूर्ण;

#घोषणा MTK_JPEG_ENC_NUM_FORMATS ARRAY_SIZE(mtk_jpeg_enc_क्रमmats)
#घोषणा MTK_JPEG_DEC_NUM_FORMATS ARRAY_SIZE(mtk_jpeg_dec_क्रमmats)

काष्ठा mtk_jpeg_src_buf अणु
	काष्ठा vb2_v4l2_buffer b;
	काष्ठा list_head list;
	काष्ठा mtk_jpeg_dec_param dec_param;
पूर्ण;

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

अटल अंतरभूत काष्ठा mtk_jpeg_ctx *ctrl_to_ctx(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा mtk_jpeg_ctx, ctrl_hdl);
पूर्ण

अटल अंतरभूत काष्ठा mtk_jpeg_ctx *mtk_jpeg_fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा mtk_jpeg_ctx, fh);
पूर्ण

अटल अंतरभूत काष्ठा mtk_jpeg_src_buf *mtk_jpeg_vb2_to_srcbuf(
							काष्ठा vb2_buffer *vb)
अणु
	वापस container_of(to_vb2_v4l2_buffer(vb), काष्ठा mtk_jpeg_src_buf, b);
पूर्ण

अटल पूर्णांक mtk_jpeg_querycap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = video_drvdata(file);

	strscpy(cap->driver, jpeg->variant->dev_name, माप(cap->driver));
	strscpy(cap->card, jpeg->variant->dev_name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(jpeg->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_jpeg_enc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_RESTART_INTERVAL:
		ctx->restart_पूर्णांकerval = ctrl->val;
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ctx->enc_quality = ctrl->val;
		अवरोध;
	हाल V4L2_CID_JPEG_ACTIVE_MARKER:
		ctx->enable_exअगर = ctrl->val & V4L2_JPEG_ACTIVE_MARKER_APP1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mtk_jpeg_enc_ctrl_ops = अणु
	.s_ctrl = vidioc_jpeg_enc_s_ctrl,
पूर्ण;

अटल पूर्णांक mtk_jpeg_enc_ctrls_setup(काष्ठा mtk_jpeg_ctx *ctx)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &mtk_jpeg_enc_ctrl_ops;
	काष्ठा v4l2_ctrl_handler *handler = &ctx->ctrl_hdl;

	v4l2_ctrl_handler_init(handler, 3);

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_JPEG_RESTART_INTERVAL, 0, 100,
			  1, 0);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_JPEG_COMPRESSION_QUALITY, 48,
			  100, 1, 90);
	v4l2_ctrl_new_std(handler, ops, V4L2_CID_JPEG_ACTIVE_MARKER, 0,
			  V4L2_JPEG_ACTIVE_MARKER_APP1, 0, 0);

	अगर (handler->error) अणु
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
		वापस handler->error;
	पूर्ण

	v4l2_ctrl_handler_setup(&ctx->ctrl_hdl);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_क्रमागत_fmt(काष्ठा mtk_jpeg_fmt *mtk_jpeg_क्रमmats, पूर्णांक n,
			     काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num = 0;

	क्रम (i = 0; i < n; ++i) अणु
		अगर (mtk_jpeg_क्रमmats[i].flags & type) अणु
			अगर (num == f->index)
				अवरोध;
			++num;
		पूर्ण
	पूर्ण

	अगर (i >= n)
		वापस -EINVAL;

	f->pixelक्रमmat = mtk_jpeg_क्रमmats[i].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;

	वापस mtk_jpeg_क्रमागत_fmt(jpeg->variant->क्रमmats,
				 jpeg->variant->num_क्रमmats, f,
				 MTK_JPEG_FMT_FLAG_CAPTURE);
पूर्ण

अटल पूर्णांक mtk_jpeg_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;

	वापस mtk_jpeg_क्रमागत_fmt(jpeg->variant->क्रमmats,
				 jpeg->variant->num_क्रमmats, f,
				 MTK_JPEG_FMT_FLAG_OUTPUT);
पूर्ण

अटल काष्ठा mtk_jpeg_q_data *mtk_jpeg_get_q_data(काष्ठा mtk_jpeg_ctx *ctx,
						   क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->out_q;
	वापस &ctx->cap_q;
पूर्ण

अटल काष्ठा mtk_jpeg_fmt *
mtk_jpeg_find_क्रमmat(काष्ठा mtk_jpeg_fmt *mtk_jpeg_क्रमmats, पूर्णांक num_क्रमmats,
		     u32 pixelक्रमmat, अचिन्हित पूर्णांक fmt_type)
अणु
	अचिन्हित पूर्णांक k;
	काष्ठा mtk_jpeg_fmt *fmt;

	क्रम (k = 0; k < num_क्रमmats; k++) अणु
		fmt = &mtk_jpeg_क्रमmats[k];

		अगर (fmt->fourcc == pixelक्रमmat && fmt->flags & fmt_type)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_jpeg_try_fmt_mplane(काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp,
				   काष्ठा mtk_jpeg_fmt *fmt)
अणु
	पूर्णांक i;

	pix_mp->field = V4L2_FIELD_NONE;

	pix_mp->num_planes = fmt->colplanes;
	pix_mp->pixelक्रमmat = fmt->fourcc;

	अगर (fmt->fourcc == V4L2_PIX_FMT_JPEG) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *pfmt = &pix_mp->plane_fmt[0];

		pix_mp->height = clamp(pix_mp->height, MTK_JPEG_MIN_HEIGHT,
				       MTK_JPEG_MAX_HEIGHT);
		pix_mp->width = clamp(pix_mp->width, MTK_JPEG_MIN_WIDTH,
				      MTK_JPEG_MAX_WIDTH);

		pfmt->bytesperline = 0;
		/* Source size must be aligned to 128 */
		pfmt->sizeimage = round_up(pfmt->sizeimage, 128);
		अगर (pfmt->sizeimage == 0)
			pfmt->sizeimage = MTK_JPEG_DEFAULT_SIZEIMAGE;
		वापस 0;
	पूर्ण

	/* other fourcc */
	pix_mp->height = clamp(round_up(pix_mp->height, fmt->v_align),
			       MTK_JPEG_MIN_HEIGHT, MTK_JPEG_MAX_HEIGHT);
	pix_mp->width = clamp(round_up(pix_mp->width, fmt->h_align),
			      MTK_JPEG_MIN_WIDTH, MTK_JPEG_MAX_WIDTH);

	क्रम (i = 0; i < fmt->colplanes; i++) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *pfmt = &pix_mp->plane_fmt[i];
		u32 stride = pix_mp->width * fmt->h_sample[i] / 4;
		u32 h = pix_mp->height * fmt->v_sample[i] / 4;

		pfmt->bytesperline = stride;
		pfmt->sizeimage = stride * h;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_g_fmt_vid_mplane(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	पूर्णांक i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = mtk_jpeg_get_q_data(ctx, f->type);

	pix_mp->width = q_data->pix_mp.width;
	pix_mp->height = q_data->pix_mp.height;
	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->pixelक्रमmat = q_data->fmt->fourcc;
	pix_mp->num_planes = q_data->fmt->colplanes;
	pix_mp->colorspace = q_data->pix_mp.colorspace;
	pix_mp->ycbcr_enc = q_data->pix_mp.ycbcr_enc;
	pix_mp->xfer_func = q_data->pix_mp.xfer_func;
	pix_mp->quantization = q_data->pix_mp.quantization;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) g_fmt:%c%c%c%c wxh:%ux%u\n",
		 f->type,
		 (pix_mp->pixelक्रमmat & 0xff),
		 (pix_mp->pixelक्रमmat >>  8 & 0xff),
		 (pix_mp->pixelक्रमmat >> 16 & 0xff),
		 (pix_mp->pixelक्रमmat >> 24 & 0xff),
		 pix_mp->width, pix_mp->height);

	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *pfmt = &pix_mp->plane_fmt[i];

		pfmt->bytesperline = q_data->pix_mp.plane_fmt[i].bytesperline;
		pfmt->sizeimage = q_data->pix_mp.plane_fmt[i].sizeimage;

		v4l2_dbg(1, debug, &jpeg->v4l2_dev,
			 "plane[%d] bpl=%u, size=%u\n",
			 i,
			 pfmt->bytesperline,
			 pfmt->sizeimage);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
					   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा mtk_jpeg_fmt *fmt;

	fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
				   jpeg->variant->num_क्रमmats,
				   f->fmt.pix_mp.pixelक्रमmat,
				   MTK_JPEG_FMT_FLAG_CAPTURE);
	अगर (!fmt)
		fmt = ctx->cap_q.fmt;

	v4l2_dbg(2, debug, &ctx->jpeg->v4l2_dev, "(%d) try_fmt:%c%c%c%c\n",
		 f->type,
		 (fmt->fourcc & 0xff),
		 (fmt->fourcc >>  8 & 0xff),
		 (fmt->fourcc >> 16 & 0xff),
		 (fmt->fourcc >> 24 & 0xff));

	अगर (ctx->state != MTK_JPEG_INIT) अणु
		mtk_jpeg_g_fmt_vid_mplane(file, priv, f);
		वापस 0;
	पूर्ण

	वापस mtk_jpeg_try_fmt_mplane(&f->fmt.pix_mp, fmt);
पूर्ण

अटल पूर्णांक mtk_jpeg_try_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
					   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा mtk_jpeg_fmt *fmt;

	fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
				   jpeg->variant->num_क्रमmats,
				   f->fmt.pix_mp.pixelक्रमmat,
				   MTK_JPEG_FMT_FLAG_OUTPUT);
	अगर (!fmt)
		fmt = ctx->out_q.fmt;

	v4l2_dbg(2, debug, &ctx->jpeg->v4l2_dev, "(%d) try_fmt:%c%c%c%c\n",
		 f->type,
		 (fmt->fourcc & 0xff),
		 (fmt->fourcc >>  8 & 0xff),
		 (fmt->fourcc >> 16 & 0xff),
		 (fmt->fourcc >> 24 & 0xff));

	अगर (ctx->state != MTK_JPEG_INIT) अणु
		mtk_jpeg_g_fmt_vid_mplane(file, priv, f);
		वापस 0;
	पूर्ण

	वापस mtk_jpeg_try_fmt_mplane(&f->fmt.pix_mp, fmt);
पूर्ण

अटल पूर्णांक mtk_jpeg_s_fmt_mplane(काष्ठा mtk_jpeg_ctx *ctx,
				 काष्ठा v4l2_क्रमmat *f, अचिन्हित पूर्णांक fmt_type)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	पूर्णांक i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = mtk_jpeg_get_q_data(ctx, f->type);

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&jpeg->v4l2_dev, "queue busy\n");
		वापस -EBUSY;
	पूर्ण

	q_data->fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
					   jpeg->variant->num_क्रमmats,
					   pix_mp->pixelक्रमmat, fmt_type);
	q_data->pix_mp.width = pix_mp->width;
	q_data->pix_mp.height = pix_mp->height;
	q_data->enc_crop_rect.width = pix_mp->width;
	q_data->enc_crop_rect.height = pix_mp->height;
	q_data->pix_mp.colorspace = V4L2_COLORSPACE_SRGB;
	q_data->pix_mp.ycbcr_enc = V4L2_YCBCR_ENC_601;
	q_data->pix_mp.xfer_func = V4L2_XFER_FUNC_SRGB;
	q_data->pix_mp.quantization = V4L2_QUANTIZATION_FULL_RANGE;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) s_fmt:%c%c%c%c wxh:%ux%u\n",
		 f->type,
		 (q_data->fmt->fourcc & 0xff),
		 (q_data->fmt->fourcc >>  8 & 0xff),
		 (q_data->fmt->fourcc >> 16 & 0xff),
		 (q_data->fmt->fourcc >> 24 & 0xff),
		 q_data->pix_mp.width, q_data->pix_mp.height);

	क्रम (i = 0; i < q_data->fmt->colplanes; i++) अणु
		q_data->pix_mp.plane_fmt[i].bytesperline =
					pix_mp->plane_fmt[i].bytesperline;
		q_data->pix_mp.plane_fmt[i].sizeimage =
					pix_mp->plane_fmt[i].sizeimage;

		v4l2_dbg(1, debug, &jpeg->v4l2_dev,
			 "plane[%d] bpl=%u, size=%u\n",
			 i, q_data->pix_mp.plane_fmt[i].bytesperline,
			 q_data->pix_mp.plane_fmt[i].sizeimage);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_s_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = mtk_jpeg_try_fmt_vid_out_mplane(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस mtk_jpeg_s_fmt_mplane(mtk_jpeg_fh_to_ctx(priv), f,
				     MTK_JPEG_FMT_FLAG_OUTPUT);
पूर्ण

अटल पूर्णांक mtk_jpeg_s_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = mtk_jpeg_try_fmt_vid_cap_mplane(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस mtk_jpeg_s_fmt_mplane(mtk_jpeg_fh_to_ctx(priv), f,
				     MTK_JPEG_FMT_FLAG_CAPTURE);
पूर्ण

अटल व्योम mtk_jpeg_queue_src_chg_event(काष्ठा mtk_jpeg_ctx *ctx)
अणु
	अटल स्थिर काष्ठा v4l2_event ev_src_ch = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes =
		V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;

	v4l2_event_queue_fh(&ctx->fh, &ev_src_ch);
पूर्ण

अटल पूर्णांक mtk_jpeg_subscribe_event(काष्ठा v4l2_fh *fh,
				    स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	पूर्ण

	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण

अटल पूर्णांक mtk_jpeg_enc_g_selection(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		s->r = ctx->out_q.enc_crop_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.width = ctx->out_q.pix_mp.width;
		s->r.height = ctx->out_q.pix_mp.height;
		s->r.left = 0;
		s->r.top = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_dec_g_selection(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		s->r.width = ctx->out_q.pix_mp.width;
		s->r.height = ctx->out_q.pix_mp.height;
		s->r.left = 0;
		s->r.top = 0;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
		s->r.width = ctx->cap_q.pix_mp.width;
		s->r.height = ctx->cap_q.pix_mp.height;
		s->r.left = 0;
		s->r.top = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_enc_s_selection(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = min(s->r.width, ctx->out_q.pix_mp.width);
		s->r.height = min(s->r.height, ctx->out_q.pix_mp.height);
		ctx->out_q.enc_crop_rect = s->r;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops mtk_jpeg_enc_ioctl_ops = अणु
	.vidioc_querycap                = mtk_jpeg_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= mtk_jpeg_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= mtk_jpeg_क्रमागत_fmt_vid_out,
	.vidioc_try_fmt_vid_cap_mplane	= mtk_jpeg_try_fmt_vid_cap_mplane,
	.vidioc_try_fmt_vid_out_mplane	= mtk_jpeg_try_fmt_vid_out_mplane,
	.vidioc_g_fmt_vid_cap_mplane    = mtk_jpeg_g_fmt_vid_mplane,
	.vidioc_g_fmt_vid_out_mplane    = mtk_jpeg_g_fmt_vid_mplane,
	.vidioc_s_fmt_vid_cap_mplane    = mtk_jpeg_s_fmt_vid_cap_mplane,
	.vidioc_s_fmt_vid_out_mplane    = mtk_jpeg_s_fmt_vid_out_mplane,
	.vidioc_qbuf                    = v4l2_m2m_ioctl_qbuf,
	.vidioc_subscribe_event         = mtk_jpeg_subscribe_event,
	.vidioc_g_selection		= mtk_jpeg_enc_g_selection,
	.vidioc_s_selection		= mtk_jpeg_enc_s_selection,

	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_reqbufs                 = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf                = v4l2_m2m_ioctl_querybuf,
	.vidioc_dqbuf                   = v4l2_m2m_ioctl_dqbuf,
	.vidioc_expbuf                  = v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon                = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff               = v4l2_m2m_ioctl_streamoff,

	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops mtk_jpeg_dec_ioctl_ops = अणु
	.vidioc_querycap                = mtk_jpeg_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= mtk_jpeg_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= mtk_jpeg_क्रमागत_fmt_vid_out,
	.vidioc_try_fmt_vid_cap_mplane	= mtk_jpeg_try_fmt_vid_cap_mplane,
	.vidioc_try_fmt_vid_out_mplane	= mtk_jpeg_try_fmt_vid_out_mplane,
	.vidioc_g_fmt_vid_cap_mplane    = mtk_jpeg_g_fmt_vid_mplane,
	.vidioc_g_fmt_vid_out_mplane    = mtk_jpeg_g_fmt_vid_mplane,
	.vidioc_s_fmt_vid_cap_mplane    = mtk_jpeg_s_fmt_vid_cap_mplane,
	.vidioc_s_fmt_vid_out_mplane    = mtk_jpeg_s_fmt_vid_out_mplane,
	.vidioc_qbuf                    = v4l2_m2m_ioctl_qbuf,
	.vidioc_subscribe_event         = mtk_jpeg_subscribe_event,
	.vidioc_g_selection		= mtk_jpeg_dec_g_selection,

	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_reqbufs                 = v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf                = v4l2_m2m_ioctl_querybuf,
	.vidioc_dqbuf                   = v4l2_m2m_ioctl_dqbuf,
	.vidioc_expbuf                  = v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon                = v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff               = v4l2_m2m_ioctl_streamoff,

	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक mtk_jpeg_queue_setup(काष्ठा vb2_queue *q,
				अचिन्हित पूर्णांक *num_buffers,
				अचिन्हित पूर्णांक *num_planes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_ctxs[])
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा mtk_jpeg_q_data *q_data = शून्य;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	पूर्णांक i;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) buf_req count=%u\n",
		 q->type, *num_buffers);

	q_data = mtk_jpeg_get_q_data(ctx, q->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (*num_planes) अणु
		क्रम (i = 0; i < *num_planes; i++)
			अगर (sizes[i] < q_data->pix_mp.plane_fmt[i].sizeimage)
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	*num_planes = q_data->fmt->colplanes;
	क्रम (i = 0; i < q_data->fmt->colplanes; i++) अणु
		sizes[i] =  q_data->pix_mp.plane_fmt[i].sizeimage;
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "sizeimage[%d]=%u\n",
			 i, sizes[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_jpeg_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_plane_pix_क्रमmat plane_fmt = अणुपूर्ण;
	पूर्णांक i;

	q_data = mtk_jpeg_get_q_data(ctx, vb->vb2_queue->type);
	अगर (!q_data)
		वापस -EINVAL;

	क्रम (i = 0; i < q_data->fmt->colplanes; i++) अणु
		plane_fmt = q_data->pix_mp.plane_fmt[i];
		अगर (ctx->enable_exअगर &&
		    q_data->fmt->fourcc == V4L2_PIX_FMT_JPEG)
			vb2_set_plane_payload(vb, i, plane_fmt.sizeimage +
					      MTK_JPEG_MAX_EXIF_SIZE);
		अन्यथा
			vb2_set_plane_payload(vb, i,  plane_fmt.sizeimage);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mtk_jpeg_check_resolution_change(काष्ठा mtk_jpeg_ctx *ctx,
					     काष्ठा mtk_jpeg_dec_param *param)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा mtk_jpeg_q_data *q_data;

	q_data = &ctx->out_q;
	अगर (q_data->pix_mp.width != param->pic_w ||
	    q_data->pix_mp.height != param->pic_h) अणु
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "Picture size change\n");
		वापस true;
	पूर्ण

	q_data = &ctx->cap_q;
	अगर (q_data->fmt !=
	    mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
				 jpeg->variant->num_क्रमmats, param->dst_fourcc,
				 MTK_JPEG_FMT_FLAG_CAPTURE)) अणु
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "format change\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम mtk_jpeg_set_queue_data(काष्ठा mtk_jpeg_ctx *ctx,
				    काष्ठा mtk_jpeg_dec_param *param)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा mtk_jpeg_q_data *q_data;
	पूर्णांक i;

	q_data = &ctx->out_q;
	q_data->pix_mp.width = param->pic_w;
	q_data->pix_mp.height = param->pic_h;

	q_data = &ctx->cap_q;
	q_data->pix_mp.width = param->dec_w;
	q_data->pix_mp.height = param->dec_h;
	q_data->fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
					   jpeg->variant->num_क्रमmats,
					   param->dst_fourcc,
					   MTK_JPEG_FMT_FLAG_CAPTURE);

	क्रम (i = 0; i < q_data->fmt->colplanes; i++) अणु
		q_data->pix_mp.plane_fmt[i].bytesperline = param->mem_stride[i];
		q_data->pix_mp.plane_fmt[i].sizeimage = param->comp_size[i];
	पूर्ण

	v4l2_dbg(1, debug, &jpeg->v4l2_dev,
		 "set_parse cap:%c%c%c%c pic(%u, %u), buf(%u, %u)\n",
		 (param->dst_fourcc & 0xff),
		 (param->dst_fourcc >>  8 & 0xff),
		 (param->dst_fourcc >> 16 & 0xff),
		 (param->dst_fourcc >> 24 & 0xff),
		 param->pic_w, param->pic_h,
		 param->dec_w, param->dec_h);
पूर्ण

अटल व्योम mtk_jpeg_enc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;

	v4l2_dbg(2, debug, &jpeg->v4l2_dev, "(%d) buf_q id=%d, vb=%p\n",
		 vb->vb2_queue->type, vb->index, vb);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, to_vb2_v4l2_buffer(vb));
पूर्ण

अटल व्योम mtk_jpeg_dec_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_jpeg_dec_param *param;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा mtk_jpeg_src_buf *jpeg_src_buf;
	bool header_valid;

	v4l2_dbg(2, debug, &jpeg->v4l2_dev, "(%d) buf_q id=%d, vb=%p\n",
		 vb->vb2_queue->type, vb->index, vb);

	अगर (vb->vb2_queue->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		जाओ end;

	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(vb);
	param = &jpeg_src_buf->dec_param;
	स_रखो(param, 0, माप(*param));

	header_valid = mtk_jpeg_parse(param, (u8 *)vb2_plane_vaddr(vb, 0),
				      vb2_get_plane_payload(vb, 0));
	अगर (!header_valid) अणु
		v4l2_err(&jpeg->v4l2_dev, "Header invalid.\n");
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	अगर (ctx->state == MTK_JPEG_INIT) अणु
		काष्ठा vb2_queue *dst_vq = v4l2_m2m_get_vq(
			ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

		mtk_jpeg_queue_src_chg_event(ctx);
		mtk_jpeg_set_queue_data(ctx, param);
		ctx->state = vb2_is_streaming(dst_vq) ?
				MTK_JPEG_SOURCE_CHANGE : MTK_JPEG_RUNNING;
	पूर्ण
end:
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, to_vb2_v4l2_buffer(vb));
पूर्ण

अटल काष्ठा vb2_v4l2_buffer *mtk_jpeg_buf_हटाओ(काष्ठा mtk_jpeg_ctx *ctx,
				 क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	अन्यथा
		वापस v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम mtk_jpeg_enc_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vb;

	जबतक ((vb = mtk_jpeg_buf_हटाओ(ctx, q->type)))
		v4l2_m2m_buf_करोne(vb, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम mtk_jpeg_dec_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vb;

	/*
	 * STREAMOFF is an acknowledgment क्रम source change event.
	 * Beक्रमe STREAMOFF, we still have to वापस the old resolution and
	 * subsampling. Update capture queue when the stream is off.
	 */
	अगर (ctx->state == MTK_JPEG_SOURCE_CHANGE &&
	    V4L2_TYPE_IS_CAPTURE(q->type)) अणु
		काष्ठा mtk_jpeg_src_buf *src_buf;

		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		src_buf = mtk_jpeg_vb2_to_srcbuf(&vb->vb2_buf);
		mtk_jpeg_set_queue_data(ctx, &src_buf->dec_param);
		ctx->state = MTK_JPEG_RUNNING;
	पूर्ण अन्यथा अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		ctx->state = MTK_JPEG_INIT;
	पूर्ण

	जबतक ((vb = mtk_jpeg_buf_हटाओ(ctx, q->type)))
		v4l2_m2m_buf_करोne(vb, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops mtk_jpeg_dec_qops = अणु
	.queue_setup        = mtk_jpeg_queue_setup,
	.buf_prepare        = mtk_jpeg_buf_prepare,
	.buf_queue          = mtk_jpeg_dec_buf_queue,
	.रुको_prepare       = vb2_ops_रुको_prepare,
	.रुको_finish        = vb2_ops_रुको_finish,
	.stop_streaming     = mtk_jpeg_dec_stop_streaming,
पूर्ण;

अटल स्थिर काष्ठा vb2_ops mtk_jpeg_enc_qops = अणु
	.queue_setup        = mtk_jpeg_queue_setup,
	.buf_prepare        = mtk_jpeg_buf_prepare,
	.buf_queue          = mtk_jpeg_enc_buf_queue,
	.रुको_prepare       = vb2_ops_रुको_prepare,
	.रुको_finish        = vb2_ops_रुको_finish,
	.stop_streaming     = mtk_jpeg_enc_stop_streaming,
पूर्ण;

अटल व्योम mtk_jpeg_set_dec_src(काष्ठा mtk_jpeg_ctx *ctx,
				 काष्ठा vb2_buffer *src_buf,
				 काष्ठा mtk_jpeg_bs *bs)
अणु
	bs->str_addr = vb2_dma_contig_plane_dma_addr(src_buf, 0);
	bs->end_addr = bs->str_addr +
		       round_up(vb2_get_plane_payload(src_buf, 0), 16);
	bs->size = round_up(vb2_plane_size(src_buf, 0), 128);
पूर्ण

अटल पूर्णांक mtk_jpeg_set_dec_dst(काष्ठा mtk_jpeg_ctx *ctx,
				काष्ठा mtk_jpeg_dec_param *param,
				काष्ठा vb2_buffer *dst_buf,
				काष्ठा mtk_jpeg_fb *fb)
अणु
	पूर्णांक i;

	अगर (param->comp_num != dst_buf->num_planes) अणु
		dev_err(ctx->jpeg->dev, "plane number mismatch (%u != %u)\n",
			param->comp_num, dst_buf->num_planes);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < dst_buf->num_planes; i++) अणु
		अगर (vb2_plane_size(dst_buf, i) < param->comp_size[i]) अणु
			dev_err(ctx->jpeg->dev,
				"buffer size is underflow (%lu < %u)\n",
				vb2_plane_size(dst_buf, 0),
				param->comp_size[i]);
			वापस -EINVAL;
		पूर्ण
		fb->plane_addr[i] = vb2_dma_contig_plane_dma_addr(dst_buf, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_jpeg_enc_device_run(व्योम *priv)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = priv;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	क्रमागत vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	ret = pm_runसमय_get_sync(jpeg->dev);
	अगर (ret < 0)
		जाओ enc_end;

	schedule_delayed_work(&jpeg->job_समयout_work,
			      msecs_to_jअगरfies(MTK_JPEG_HW_TIMEOUT_MSEC));

	spin_lock_irqsave(&jpeg->hw_lock, flags);

	/*
	 * Resetting the hardware every frame is to ensure that all the
	 * रेजिस्टरs are cleared. This is a hardware requirement.
	 */
	mtk_jpeg_enc_reset(jpeg->reg_base);

	mtk_jpeg_set_enc_src(ctx, jpeg->reg_base, &src_buf->vb2_buf);
	mtk_jpeg_set_enc_dst(ctx, jpeg->reg_base, &dst_buf->vb2_buf);
	mtk_jpeg_set_enc_params(ctx, jpeg->reg_base);
	mtk_jpeg_enc_start(jpeg->reg_base);
	spin_unlock_irqrestore(&jpeg->hw_lock, flags);
	वापस;

enc_end:
	v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(src_buf, buf_state);
	v4l2_m2m_buf_करोne(dst_buf, buf_state);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल व्योम mtk_jpeg_dec_device_run(व्योम *priv)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = priv;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	क्रमागत vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	अचिन्हित दीर्घ flags;
	काष्ठा mtk_jpeg_src_buf *jpeg_src_buf;
	काष्ठा mtk_jpeg_bs bs;
	काष्ठा mtk_jpeg_fb fb;
	पूर्णांक ret;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(&src_buf->vb2_buf);

	अगर (mtk_jpeg_check_resolution_change(ctx, &jpeg_src_buf->dec_param)) अणु
		mtk_jpeg_queue_src_chg_event(ctx);
		ctx->state = MTK_JPEG_SOURCE_CHANGE;
		v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
		वापस;
	पूर्ण

	ret = pm_runसमय_get_sync(jpeg->dev);
	अगर (ret < 0)
		जाओ dec_end;

	schedule_delayed_work(&jpeg->job_समयout_work,
			      msecs_to_jअगरfies(MTK_JPEG_HW_TIMEOUT_MSEC));

	mtk_jpeg_set_dec_src(ctx, &src_buf->vb2_buf, &bs);
	अगर (mtk_jpeg_set_dec_dst(ctx, &jpeg_src_buf->dec_param, &dst_buf->vb2_buf, &fb))
		जाओ dec_end;

	spin_lock_irqsave(&jpeg->hw_lock, flags);
	mtk_jpeg_dec_reset(jpeg->reg_base);
	mtk_jpeg_dec_set_config(jpeg->reg_base,
				&jpeg_src_buf->dec_param, &bs, &fb);

	mtk_jpeg_dec_start(jpeg->reg_base);
	spin_unlock_irqrestore(&jpeg->hw_lock, flags);
	वापस;

dec_end:
	v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(src_buf, buf_state);
	v4l2_m2m_buf_करोne(dst_buf, buf_state);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल पूर्णांक mtk_jpeg_dec_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = priv;

	वापस (ctx->state == MTK_JPEG_RUNNING) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops mtk_jpeg_enc_m2m_ops = अणु
	.device_run = mtk_jpeg_enc_device_run,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops mtk_jpeg_dec_m2m_ops = अणु
	.device_run = mtk_jpeg_dec_device_run,
	.job_पढ़ोy  = mtk_jpeg_dec_job_पढ़ोy,
पूर्ण;

अटल पूर्णांक mtk_jpeg_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			       काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा mtk_jpeg_ctx *ctx = priv;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा mtk_jpeg_src_buf);
	src_vq->ops = jpeg->variant->qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->jpeg->lock;
	src_vq->dev = ctx->jpeg->dev;
	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = jpeg->variant->qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->jpeg->lock;
	dst_vq->dev = ctx->jpeg->dev;
	ret = vb2_queue_init(dst_vq);

	वापस ret;
पूर्ण

अटल व्योम mtk_jpeg_clk_on(काष्ठा mtk_jpeg_dev *jpeg)
अणु
	पूर्णांक ret;

	ret = mtk_smi_larb_get(jpeg->larb);
	अगर (ret)
		dev_err(jpeg->dev, "mtk_smi_larb_get larbvdec fail %d\n", ret);

	ret = clk_bulk_prepare_enable(jpeg->variant->num_clks,
				      jpeg->variant->clks);
	अगर (ret)
		dev_err(jpeg->dev, "Failed to open jpeg clk: %d\n", ret);
पूर्ण

अटल व्योम mtk_jpeg_clk_off(काष्ठा mtk_jpeg_dev *jpeg)
अणु
	clk_bulk_disable_unprepare(jpeg->variant->num_clks,
				   jpeg->variant->clks);
	mtk_smi_larb_put(jpeg->larb);
पूर्ण

अटल irqवापस_t mtk_jpeg_enc_करोne(काष्ठा mtk_jpeg_dev *jpeg)
अणु
	काष्ठा mtk_jpeg_ctx *ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	क्रमागत vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	u32 result_size;

	ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&jpeg->v4l2_dev, "Context is NULL\n");
		वापस IRQ_HANDLED;
	पूर्ण

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	result_size = mtk_jpeg_enc_get_file_size(jpeg->reg_base);
	vb2_set_plane_payload(&dst_buf->vb2_buf, 0, result_size);

	buf_state = VB2_BUF_STATE_DONE;

	v4l2_m2m_buf_करोne(src_buf, buf_state);
	v4l2_m2m_buf_करोne(dst_buf, buf_state);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
	pm_runसमय_put(ctx->jpeg->dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtk_jpeg_enc_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = priv;
	u32 irq_status;
	irqवापस_t ret = IRQ_NONE;

	cancel_delayed_work(&jpeg->job_समयout_work);

	irq_status = पढ़ोl(jpeg->reg_base + JPEG_ENC_INT_STS) &
		     JPEG_ENC_INT_STATUS_MASK_ALLIRQ;
	अगर (irq_status)
		ग_लिखोl(0, jpeg->reg_base + JPEG_ENC_INT_STS);

	अगर (!(irq_status & JPEG_ENC_INT_STATUS_DONE))
		वापस ret;

	ret = mtk_jpeg_enc_करोne(jpeg);
	वापस ret;
पूर्ण

अटल irqवापस_t mtk_jpeg_dec_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = priv;
	काष्ठा mtk_jpeg_ctx *ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा mtk_jpeg_src_buf *jpeg_src_buf;
	क्रमागत vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	u32	dec_irq_ret;
	u32 dec_ret;
	पूर्णांक i;

	cancel_delayed_work(&jpeg->job_समयout_work);

	dec_ret = mtk_jpeg_dec_get_पूर्णांक_status(jpeg->reg_base);
	dec_irq_ret = mtk_jpeg_dec_क्रमागत_result(dec_ret);
	ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&jpeg->v4l2_dev, "Context is NULL\n");
		वापस IRQ_HANDLED;
	पूर्ण

	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(&src_buf->vb2_buf);

	अगर (dec_irq_ret >= MTK_JPEG_DEC_RESULT_UNDERFLOW)
		mtk_jpeg_dec_reset(jpeg->reg_base);

	अगर (dec_irq_ret != MTK_JPEG_DEC_RESULT_खातापूर्ण_DONE) अणु
		dev_err(jpeg->dev, "decode failed\n");
		जाओ dec_end;
	पूर्ण

	क्रम (i = 0; i < dst_buf->vb2_buf.num_planes; i++)
		vb2_set_plane_payload(&dst_buf->vb2_buf, i,
				      jpeg_src_buf->dec_param.comp_size[i]);

	buf_state = VB2_BUF_STATE_DONE;

dec_end:
	v4l2_m2m_buf_करोne(src_buf, buf_state);
	v4l2_m2m_buf_करोne(dst_buf, buf_state);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
	pm_runसमय_put(ctx->jpeg->dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mtk_jpeg_set_शेष_params(काष्ठा mtk_jpeg_ctx *ctx)
अणु
	काष्ठा mtk_jpeg_q_data *q = &ctx->out_q;
	काष्ठा mtk_jpeg_dev *jpeg = ctx->jpeg;

	ctx->fh.ctrl_handler = &ctx->ctrl_hdl;
	q->pix_mp.colorspace = V4L2_COLORSPACE_SRGB;
	q->pix_mp.ycbcr_enc = V4L2_YCBCR_ENC_601;
	q->pix_mp.quantization = V4L2_QUANTIZATION_FULL_RANGE;
	q->pix_mp.xfer_func = V4L2_XFER_FUNC_SRGB;

	q->fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
				      jpeg->variant->num_क्रमmats,
				      jpeg->variant->out_q_शेष_fourcc,
				      MTK_JPEG_FMT_FLAG_OUTPUT);
	q->pix_mp.width = MTK_JPEG_MIN_WIDTH;
	q->pix_mp.height = MTK_JPEG_MIN_HEIGHT;
	mtk_jpeg_try_fmt_mplane(&q->pix_mp, q->fmt);

	q = &ctx->cap_q;
	q->fmt = mtk_jpeg_find_क्रमmat(jpeg->variant->क्रमmats,
				      jpeg->variant->num_क्रमmats,
				      jpeg->variant->cap_q_शेष_fourcc,
				      MTK_JPEG_FMT_FLAG_CAPTURE);
	q->pix_mp.colorspace = V4L2_COLORSPACE_SRGB;
	q->pix_mp.ycbcr_enc = V4L2_YCBCR_ENC_601;
	q->pix_mp.quantization = V4L2_QUANTIZATION_FULL_RANGE;
	q->pix_mp.xfer_func = V4L2_XFER_FUNC_SRGB;
	q->pix_mp.width = MTK_JPEG_MIN_WIDTH;
	q->pix_mp.height = MTK_JPEG_MIN_HEIGHT;

	mtk_jpeg_try_fmt_mplane(&q->pix_mp, q->fmt);
पूर्ण

अटल पूर्णांक mtk_jpeg_खोलो(काष्ठा file *file)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा mtk_jpeg_ctx *ctx;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (mutex_lock_पूर्णांकerruptible(&jpeg->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ मुक्त;
	पूर्ण

	v4l2_fh_init(&ctx->fh, vfd);
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->jpeg = jpeg;
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(jpeg->m2m_dev, ctx,
					    mtk_jpeg_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ error;
	पूर्ण

	अगर (jpeg->variant->cap_q_शेष_fourcc == V4L2_PIX_FMT_JPEG) अणु
		ret = mtk_jpeg_enc_ctrls_setup(ctx);
		अगर (ret) अणु
			v4l2_err(&jpeg->v4l2_dev, "Failed to setup jpeg enc controls\n");
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		v4l2_ctrl_handler_init(&ctx->ctrl_hdl, 0);
	पूर्ण
	mtk_jpeg_set_शेष_params(ctx);
	mutex_unlock(&jpeg->lock);
	वापस 0;

error:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	mutex_unlock(&jpeg->lock);
मुक्त:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_jpeg_release(काष्ठा file *file)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = video_drvdata(file);
	काष्ठा mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(file->निजी_data);

	mutex_lock(&jpeg->lock);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	mutex_unlock(&jpeg->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mtk_jpeg_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = mtk_jpeg_खोलो,
	.release        = mtk_jpeg_release,
	.poll           = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = v4l2_m2m_fop_mmap,
पूर्ण;

अटल काष्ठा clk_bulk_data mt8173_jpeg_dec_घड़ीs[] = अणु
	अणु .id = "jpgdec-smi" पूर्ण,
	अणु .id = "jpgdec" पूर्ण,
पूर्ण;

अटल काष्ठा clk_bulk_data mtk_jpeg_घड़ीs[] = अणु
	अणु .id = "jpgenc" पूर्ण,
पूर्ण;

अटल पूर्णांक mtk_jpeg_clk_init(काष्ठा mtk_jpeg_dev *jpeg)
अणु
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	node = of_parse_phandle(jpeg->dev->of_node, "mediatek,larb", 0);
	अगर (!node)
		वापस -EINVAL;
	pdev = of_find_device_by_node(node);
	अगर (WARN_ON(!pdev)) अणु
		of_node_put(node);
		वापस -EINVAL;
	पूर्ण
	of_node_put(node);

	jpeg->larb = &pdev->dev;

	ret = devm_clk_bulk_get(jpeg->dev, jpeg->variant->num_clks,
				jpeg->variant->clks);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get jpeg clock:%d\n", ret);
		put_device(&pdev->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_jpeg_job_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = container_of(work, काष्ठा mtk_jpeg_dev,
						 job_समयout_work.work);
	काष्ठा mtk_jpeg_ctx *ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;

	ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);
	src_buf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

	jpeg->variant->hw_reset(jpeg->reg_base);

	pm_runसमय_put(jpeg->dev);

	v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_buf_करोne(dst_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल अंतरभूत व्योम mtk_jpeg_clk_release(काष्ठा mtk_jpeg_dev *jpeg)
अणु
	put_device(jpeg->larb);
पूर्ण

अटल पूर्णांक mtk_jpeg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg;
	काष्ठा resource *res;
	पूर्णांक jpeg_irq;
	पूर्णांक ret;

	jpeg = devm_kzalloc(&pdev->dev, माप(*jpeg), GFP_KERNEL);
	अगर (!jpeg)
		वापस -ENOMEM;

	mutex_init(&jpeg->lock);
	spin_lock_init(&jpeg->hw_lock);
	jpeg->dev = &pdev->dev;
	jpeg->variant = of_device_get_match_data(jpeg->dev);
	INIT_DELAYED_WORK(&jpeg->job_समयout_work, mtk_jpeg_job_समयout_work);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	jpeg->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(jpeg->reg_base)) अणु
		ret = PTR_ERR(jpeg->reg_base);
		वापस ret;
	पूर्ण

	jpeg_irq = platक्रमm_get_irq(pdev, 0);
	अगर (jpeg_irq < 0) अणु
		dev_err(&pdev->dev, "Failed to get jpeg_irq %d.\n", jpeg_irq);
		वापस jpeg_irq;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, jpeg_irq,
			       jpeg->variant->irq_handler, 0, pdev->name, jpeg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request jpeg_irq %d (%d)\n",
			jpeg_irq, ret);
		जाओ err_req_irq;
	पूर्ण

	ret = mtk_jpeg_clk_init(jpeg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to init clk, err %d\n", ret);
		जाओ err_clk_init;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &jpeg->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		ret = -EINVAL;
		जाओ err_dev_रेजिस्टर;
	पूर्ण

	jpeg->m2m_dev = v4l2_m2m_init(jpeg->variant->m2m_ops);

	अगर (IS_ERR(jpeg->m2m_dev)) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(jpeg->m2m_dev);
		जाओ err_m2m_init;
	पूर्ण

	jpeg->vdev = video_device_alloc();
	अगर (!jpeg->vdev) अणु
		ret = -ENOMEM;
		जाओ err_vfd_jpeg_alloc;
	पूर्ण
	snम_लिखो(jpeg->vdev->name, माप(jpeg->vdev->name),
		 "%s", jpeg->variant->dev_name);
	jpeg->vdev->fops = &mtk_jpeg_fops;
	jpeg->vdev->ioctl_ops = jpeg->variant->ioctl_ops;
	jpeg->vdev->minor = -1;
	jpeg->vdev->release = video_device_release;
	jpeg->vdev->lock = &jpeg->lock;
	jpeg->vdev->v4l2_dev = &jpeg->v4l2_dev;
	jpeg->vdev->vfl_dir = VFL_सूची_M2M;
	jpeg->vdev->device_caps = V4L2_CAP_STREAMING |
				  V4L2_CAP_VIDEO_M2M_MPLANE;

	ret = video_रेजिस्टर_device(jpeg->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to register video device\n");
		जाओ err_vfd_jpeg_रेजिस्टर;
	पूर्ण

	video_set_drvdata(jpeg->vdev, jpeg);
	v4l2_info(&jpeg->v4l2_dev,
		  "%s device registered as /dev/video%d (%d,%d)\n",
		  jpeg->variant->dev_name, jpeg->vdev->num,
		  VIDEO_MAJOR, jpeg->vdev->minor);

	platक्रमm_set_drvdata(pdev, jpeg);

	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_vfd_jpeg_रेजिस्टर:
	video_device_release(jpeg->vdev);

err_vfd_jpeg_alloc:
	v4l2_m2m_release(jpeg->m2m_dev);

err_m2m_init:
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);

err_dev_रेजिस्टर:
	mtk_jpeg_clk_release(jpeg);

err_clk_init:

err_req_irq:

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_jpeg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	video_unरेजिस्टर_device(jpeg->vdev);
	video_device_release(jpeg->vdev);
	v4l2_m2m_release(jpeg->m2m_dev);
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);
	mtk_jpeg_clk_release(jpeg);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक mtk_jpeg_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = dev_get_drvdata(dev);

	mtk_jpeg_clk_off(jpeg);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक mtk_jpeg_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = dev_get_drvdata(dev);

	mtk_jpeg_clk_on(jpeg);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक mtk_jpeg_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = dev_get_drvdata(dev);

	v4l2_m2m_suspend(jpeg->m2m_dev);
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल __maybe_unused पूर्णांक mtk_jpeg_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_jpeg_dev *jpeg = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	v4l2_m2m_resume(jpeg->m2m_dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_jpeg_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_jpeg_suspend, mtk_jpeg_resume)
	SET_RUNTIME_PM_OPS(mtk_jpeg_pm_suspend, mtk_jpeg_pm_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा mtk_jpeg_variant mt8173_jpeg_drvdata = अणु
	.clks = mt8173_jpeg_dec_घड़ीs,
	.num_clks = ARRAY_SIZE(mt8173_jpeg_dec_घड़ीs),
	.क्रमmats = mtk_jpeg_dec_क्रमmats,
	.num_क्रमmats = MTK_JPEG_DEC_NUM_FORMATS,
	.qops = &mtk_jpeg_dec_qops,
	.irq_handler = mtk_jpeg_dec_irq,
	.hw_reset = mtk_jpeg_dec_reset,
	.m2m_ops = &mtk_jpeg_dec_m2m_ops,
	.dev_name = "mtk-jpeg-dec",
	.ioctl_ops = &mtk_jpeg_dec_ioctl_ops,
	.out_q_शेष_fourcc = V4L2_PIX_FMT_JPEG,
	.cap_q_शेष_fourcc = V4L2_PIX_FMT_YUV420M,
पूर्ण;

अटल स्थिर काष्ठा mtk_jpeg_variant mtk_jpeg_drvdata = अणु
	.clks = mtk_jpeg_घड़ीs,
	.num_clks = ARRAY_SIZE(mtk_jpeg_घड़ीs),
	.क्रमmats = mtk_jpeg_enc_क्रमmats,
	.num_क्रमmats = MTK_JPEG_ENC_NUM_FORMATS,
	.qops = &mtk_jpeg_enc_qops,
	.irq_handler = mtk_jpeg_enc_irq,
	.hw_reset = mtk_jpeg_enc_reset,
	.m2m_ops = &mtk_jpeg_enc_m2m_ops,
	.dev_name = "mtk-jpeg-enc",
	.ioctl_ops = &mtk_jpeg_enc_ioctl_ops,
	.out_q_शेष_fourcc = V4L2_PIX_FMT_YUYV,
	.cap_q_शेष_fourcc = V4L2_PIX_FMT_JPEG,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_jpeg_match[] = अणु
	अणु
		.compatible = "mediatek,mt8173-jpgdec",
		.data = &mt8173_jpeg_drvdata,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2701-jpgdec",
		.data = &mt8173_jpeg_drvdata,
	पूर्ण,
	अणु
		.compatible = "mediatek,mtk-jpgenc",
		.data = &mtk_jpeg_drvdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mtk_jpeg_match);

अटल काष्ठा platक्रमm_driver mtk_jpeg_driver = अणु
	.probe = mtk_jpeg_probe,
	.हटाओ = mtk_jpeg_हटाओ,
	.driver = अणु
		.name           = MTK_JPEG_NAME,
		.of_match_table = mtk_jpeg_match,
		.pm             = &mtk_jpeg_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_jpeg_driver);

MODULE_DESCRIPTION("MediaTek JPEG codec driver");
MODULE_LICENSE("GPL v2");
