<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_dec.c
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 * Kamil Debski, <k.debski@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_ctrl.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_dec.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_pm.h"

अटल काष्ठा s5p_mfc_fmt क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12MT_16X16,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V6_BIT | MFC_V7_BIT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12MT,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V5_BIT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12M,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V6PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21M,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V6PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_H264,
		.codec_mode	= S5P_MFC_CODEC_H264_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_H264_MVC,
		.codec_mode	= S5P_MFC_CODEC_H264_MVC_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V6PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_H263,
		.codec_mode	= S5P_MFC_CODEC_H263_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_MPEG1,
		.codec_mode	= S5P_MFC_CODEC_MPEG2_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_MPEG2,
		.codec_mode	= S5P_MFC_CODEC_MPEG2_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_MPEG4,
		.codec_mode	= S5P_MFC_CODEC_MPEG4_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_XVID,
		.codec_mode	= S5P_MFC_CODEC_MPEG4_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VC1_ANNEX_G,
		.codec_mode	= S5P_MFC_CODEC_VC1_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VC1_ANNEX_L,
		.codec_mode	= S5P_MFC_CODEC_VC1RCV_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VP8,
		.codec_mode	= S5P_MFC_CODEC_VP8_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V6PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_HEVC,
		.codec_mode	= S5P_FIMV_CODEC_HEVC_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V10_BIT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VP9,
		.codec_mode	= S5P_FIMV_CODEC_VP9_DEC,
		.type		= MFC_FMT_DEC,
		.num_planes	= 1,
		.versions	= MFC_V10_BIT,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

/* Find selected क्रमmat description */
अटल काष्ठा s5p_mfc_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix_mp.pixelक्रमmat &&
		    क्रमmats[i].type == t)
			वापस &क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mfc_control controls[] = अणु
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H264 Display Delay",
		.minimum = 0,
		.maximum = 16383,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 16383,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Display Delay Enable",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Mpeg4 Loop Filter Enable",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Slice Interface Enable",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Minimum number of cap bufs",
		.minimum = 1,
		.maximum = 32,
		.step = 1,
		.शेष_value = 1,
		.is_अस्थिर = 1,
	पूर्ण,
पूर्ण;

#घोषणा NUM_CTRLS ARRAY_SIZE(controls)

/* Check whether a context should be run on hardware */
अटल पूर्णांक s5p_mfc_ctx_पढ़ोy(काष्ठा s5p_mfc_ctx *ctx)
अणु
	/* Context is to parse header */
	अगर (ctx->src_queue_cnt >= 1 && ctx->state == MFCINST_GOT_INST)
		वापस 1;
	/* Context is to decode a frame */
	अगर (ctx->src_queue_cnt >= 1 &&
	    ctx->state == MFCINST_RUNNING &&
	    ctx->dst_queue_cnt >= ctx->pb_count)
		वापस 1;
	/* Context is to वापस last frame */
	अगर (ctx->state == MFCINST_FINISHING &&
	    ctx->dst_queue_cnt >= ctx->pb_count)
		वापस 1;
	/* Context is to set buffers */
	अगर (ctx->src_queue_cnt >= 1 &&
	    ctx->state == MFCINST_HEAD_PARSED &&
	    ctx->capture_state == QUEUE_BUFS_MMAPED)
		वापस 1;
	/* Resolution change */
	अगर ((ctx->state == MFCINST_RES_CHANGE_INIT ||
		ctx->state == MFCINST_RES_CHANGE_FLUSH) &&
		ctx->dst_queue_cnt >= ctx->pb_count)
		वापस 1;
	अगर (ctx->state == MFCINST_RES_CHANGE_END &&
		ctx->src_queue_cnt >= 1)
		वापस 1;
	mfc_debug(2, "ctx is not ready\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s5p_mfc_codec_ops decoder_codec_ops = अणु
	.pre_seq_start		= शून्य,
	.post_seq_start		= शून्य,
	.pre_frame_start	= शून्य,
	.post_frame_start	= शून्य,
पूर्ण;

/* Query capabilities of the device */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);

	strscpy(cap->driver, S5P_MFC_NAME, माप(cap->driver));
	strscpy(cap->card, dev->vfd_dec->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(&dev->plat_dev->dev));
	वापस 0;
पूर्ण

/* Enumerate क्रमmat */
अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, काष्ठा v4l2_fmtdesc *f,
							bool out)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (out && क्रमmats[i].type != MFC_FMT_DEC)
			जारी;
		अन्यथा अगर (!out && क्रमmats[i].type != MFC_FMT_RAW)
			जारी;
		अन्यथा अगर ((dev->variant->version_bit & क्रमmats[i].versions) == 0)
			जारी;

		अगर (j == f->index)
			अवरोध;
		++j;
	पूर्ण
	अगर (i == ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[i].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *pirv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, f, false);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, f, true);
पूर्ण

/* Get क्रमmat */
अटल पूर्णांक vidioc_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;

	mfc_debug_enter();
	pix_mp = &f->fmt.pix_mp;
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    (ctx->state == MFCINST_GOT_INST || ctx->state ==
						MFCINST_RES_CHANGE_END)) अणु
		/* If the MFC is parsing the header,
		 * so रुको until it is finished */
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx, S5P_MFC_R2H_CMD_SEQ_DONE_RET,
									0);
	पूर्ण
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    ctx->state >= MFCINST_HEAD_PARSED &&
	    ctx->state < MFCINST_ABORT) अणु
		/* This is run on CAPTURE (decode output) */
		/* Width and height are set to the dimensions
		   of the movie, the buffer is bigger and
		   further processing stages should crop to this
		   rectangle. */
		pix_mp->width = ctx->buf_width;
		pix_mp->height = ctx->buf_height;
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->num_planes = 2;
		/* Set pixelक्रमmat to the क्रमmat in which MFC
		   outमाला_दो the decoded frame */
		pix_mp->pixelक्रमmat = ctx->dst_fmt->fourcc;
		pix_mp->plane_fmt[0].bytesperline = ctx->buf_width;
		pix_mp->plane_fmt[0].sizeimage = ctx->luma_size;
		pix_mp->plane_fmt[1].bytesperline = ctx->buf_width;
		pix_mp->plane_fmt[1].sizeimage = ctx->chroma_size;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/* This is run on OUTPUT
		   The buffer contains compressed image
		   so width and height have no meaning */
		pix_mp->width = 0;
		pix_mp->height = 0;
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->plane_fmt[0].bytesperline = ctx->dec_src_buf_size;
		pix_mp->plane_fmt[0].sizeimage = ctx->dec_src_buf_size;
		pix_mp->pixelक्रमmat = ctx->src_fmt->fourcc;
		pix_mp->num_planes = ctx->src_fmt->num_planes;
	पूर्ण अन्यथा अणु
		mfc_err("Format could not be read\n");
		mfc_debug(2, "%s-- with error\n", __func__);
		वापस -EINVAL;
	पूर्ण
	mfc_debug_leave();
	वापस 0;
पूर्ण

/* Try क्रमmat */
अटल पूर्णांक vidioc_try_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_fmt *fmt;

	mfc_debug(2, "Type is %d\n", f->type);
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		fmt = find_क्रमmat(f, MFC_FMT_DEC);
		अगर (!fmt) अणु
			mfc_err("Unsupported format for source.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (fmt->codec_mode == S5P_FIMV_CODEC_NONE) अणु
			mfc_err("Unknown codec\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((dev->variant->version_bit & fmt->versions) == 0) अणु
			mfc_err("Unsupported format by this MFC version.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		fmt = find_क्रमmat(f, MFC_FMT_RAW);
		अगर (!fmt) अणु
			mfc_err("Unsupported format for destination.\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((dev->variant->version_bit & fmt->versions) == 0) अणु
			mfc_err("Unsupported format by this MFC version.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Set क्रमmat */
अटल पूर्णांक vidioc_s_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret = 0;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	काष्ठा s5p_mfc_buf_size *buf_size = dev->variant->buf_size;

	mfc_debug_enter();
	ret = vidioc_try_fmt(file, priv, f);
	pix_mp = &f->fmt.pix_mp;
	अगर (ret)
		वापस ret;
	अगर (vb2_is_streaming(&ctx->vq_src) || vb2_is_streaming(&ctx->vq_dst)) अणु
		v4l2_err(&dev->v4l2_dev, "%s queue busy\n", __func__);
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		/* dst_fmt is validated by call to vidioc_try_fmt */
		ctx->dst_fmt = find_क्रमmat(f, MFC_FMT_RAW);
		ret = 0;
		जाओ out;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/* src_fmt is validated by call to vidioc_try_fmt */
		ctx->src_fmt = find_क्रमmat(f, MFC_FMT_DEC);
		ctx->codec_mode = ctx->src_fmt->codec_mode;
		mfc_debug(2, "The codec number is: %d\n", ctx->codec_mode);
		pix_mp->height = 0;
		pix_mp->width = 0;
		अगर (pix_mp->plane_fmt[0].sizeimage == 0)
			pix_mp->plane_fmt[0].sizeimage = ctx->dec_src_buf_size =
								DEF_CPB_SIZE;
		अन्यथा अगर (pix_mp->plane_fmt[0].sizeimage > buf_size->cpb)
			ctx->dec_src_buf_size = buf_size->cpb;
		अन्यथा
			ctx->dec_src_buf_size = pix_mp->plane_fmt[0].sizeimage;
		pix_mp->plane_fmt[0].bytesperline = 0;
		ctx->state = MFCINST_INIT;
		ret = 0;
		जाओ out;
	पूर्ण अन्यथा अणु
		mfc_err("Wrong type error for S_FMT : %d", f->type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	mfc_debug_leave();
	वापस ret;
पूर्ण

अटल पूर्णांक reqbufs_output(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx,
				काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	पूर्णांक ret = 0;

	s5p_mfc_घड़ी_on();

	अगर (reqbufs->count == 0) अणु
		mfc_debug(2, "Freeing buffers\n");
		ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
		अगर (ret)
			जाओ out;
		ctx->src_bufs_cnt = 0;
		ctx->output_state = QUEUE_FREE;
	पूर्ण अन्यथा अगर (ctx->output_state == QUEUE_FREE) अणु
		/* Can only request buffers when we have a valid क्रमmat set. */
		WARN_ON(ctx->src_bufs_cnt != 0);
		अगर (ctx->state != MFCINST_INIT) अणु
			mfc_err("Reqbufs called in an invalid state\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		mfc_debug(2, "Allocating %d buffers for OUTPUT queue\n",
				reqbufs->count);
		ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
		अगर (ret)
			जाओ out;

		ret = s5p_mfc_खोलो_mfc_inst(dev, ctx);
		अगर (ret) अणु
			reqbufs->count = 0;
			vb2_reqbufs(&ctx->vq_src, reqbufs);
			जाओ out;
		पूर्ण

		ctx->output_state = QUEUE_BUFS_REQUESTED;
	पूर्ण अन्यथा अणु
		mfc_err("Buffers have already been requested\n");
		ret = -EINVAL;
	पूर्ण
out:
	s5p_mfc_घड़ी_off();
	अगर (ret)
		mfc_err("Failed allocating buffers for OUTPUT queue\n");
	वापस ret;
पूर्ण

अटल पूर्णांक reqbufs_capture(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx,
				काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	पूर्णांक ret = 0;

	s5p_mfc_घड़ी_on();

	अगर (reqbufs->count == 0) अणु
		mfc_debug(2, "Freeing buffers\n");
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		अगर (ret)
			जाओ out;
		s5p_mfc_hw_call(dev->mfc_ops, release_codec_buffers, ctx);
		ctx->dst_bufs_cnt = 0;
	पूर्ण अन्यथा अगर (ctx->capture_state == QUEUE_FREE) अणु
		WARN_ON(ctx->dst_bufs_cnt != 0);
		mfc_debug(2, "Allocating %d buffers for CAPTURE queue\n",
				reqbufs->count);
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		अगर (ret)
			जाओ out;

		ctx->capture_state = QUEUE_BUFS_REQUESTED;
		ctx->total_dpb_count = reqbufs->count;

		ret = s5p_mfc_hw_call(dev->mfc_ops, alloc_codec_buffers, ctx);
		अगर (ret) अणु
			mfc_err("Failed to allocate decoding buffers\n");
			reqbufs->count = 0;
			vb2_reqbufs(&ctx->vq_dst, reqbufs);
			ret = -ENOMEM;
			ctx->capture_state = QUEUE_FREE;
			जाओ out;
		पूर्ण

		WARN_ON(ctx->dst_bufs_cnt != ctx->total_dpb_count);
		ctx->capture_state = QUEUE_BUFS_MMAPED;

		अगर (s5p_mfc_ctx_पढ़ोy(ctx))
			set_work_bit_irqsave(ctx);
		s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx, S5P_MFC_R2H_CMD_INIT_BUFFERS_RET,
					  0);
	पूर्ण अन्यथा अणु
		mfc_err("Buffers have already been requested\n");
		ret = -EINVAL;
	पूर्ण
out:
	s5p_mfc_घड़ी_off();
	अगर (ret)
		mfc_err("Failed allocating buffers for CAPTURE queue\n");
	वापस ret;
पूर्ण

/* Request buffers */
अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
					  काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (reqbufs->memory != V4L2_MEMORY_MMAP) अणु
		mfc_debug(2, "Only V4L2_MEMORY_MMAP is supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		वापस reqbufs_output(dev, ctx, reqbufs);
	पूर्ण अन्यथा अगर (reqbufs->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		वापस reqbufs_capture(dev, ctx, reqbufs);
	पूर्ण अन्यथा अणु
		mfc_err("Invalid type requested\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Query buffer */
अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *priv,
						   काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (buf->memory != V4L2_MEMORY_MMAP) अणु
		mfc_err("Only mmapped buffers can be used\n");
		वापस -EINVAL;
	पूर्ण
	mfc_debug(2, "State: %d, buf->type: %d\n", ctx->state, buf->type);
	अगर (ctx->state == MFCINST_GOT_INST &&
			buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ret = vb2_querybuf(&ctx->vq_src, buf);
	पूर्ण अन्यथा अगर (ctx->state == MFCINST_RUNNING &&
			buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = vb2_querybuf(&ctx->vq_dst, buf);
		क्रम (i = 0; i < buf->length; i++)
			buf->m.planes[i].m.mem_offset += DST_QUEUE_OFF_BASE;
	पूर्ण अन्यथा अणु
		mfc_err("vidioc_querybuf called in an inappropriate state\n");
		ret = -EINVAL;
	पूर्ण
	mfc_debug_leave();
	वापस ret;
पूर्ण

/* Queue a buffer */
अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MFCINST_ERROR) अणु
		mfc_err("Call on QBUF after unrecoverable error\n");
		वापस -EIO;
	पूर्ण
	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_qbuf(&ctx->vq_src, शून्य, buf);
	अन्यथा अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_qbuf(&ctx->vq_dst, शून्य, buf);
	वापस -EINVAL;
पूर्ण

/* Dequeue a buffer */
अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_EOS
	पूर्ण;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret;

	अगर (ctx->state == MFCINST_ERROR) अणु
		mfc_err_limited("Call on DQBUF after unrecoverable error\n");
		वापस -EIO;
	पूर्ण

	चयन (buf->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		वापस vb2_dqbuf(&ctx->vq_src, buf, file->f_flags & O_NONBLOCK);
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		ret = vb2_dqbuf(&ctx->vq_dst, buf, file->f_flags & O_NONBLOCK);
		अगर (ret)
			वापस ret;

		अगर (ctx->state == MFCINST_FINISHED &&
		    (ctx->dst_bufs[buf->index].flags & MFC_BUF_FLAG_EOS))
			v4l2_event_queue_fh(&ctx->fh, &ev);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Export DMA buffer */
अटल पूर्णांक vidioc_expbuf(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_exportbuffer *eb)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (eb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_expbuf(&ctx->vq_src, eb);
	अगर (eb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_expbuf(&ctx->vq_dst, eb);
	वापस -EINVAL;
पूर्ण

/* Stream on */
अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *priv,
			   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret = -EINVAL;

	mfc_debug_enter();
	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		ret = vb2_streamon(&ctx->vq_src, type);
	अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ret = vb2_streamon(&ctx->vq_dst, type);
	mfc_debug_leave();
	वापस ret;
पूर्ण

/* Stream off, which equals to a छोड़ो */
अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *priv,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_streamoff(&ctx->vq_src, type);
	अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_streamoff(&ctx->vq_dst, type);
	वापस -EINVAL;
पूर्ण

/* Set controls - v4l2 control framework */
अटल पूर्णांक s5p_mfc_dec_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY:
		ctx->display_delay = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE:
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE:
		ctx->display_delay_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctx->loop_filter_mpeg4 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
		ctx->slice_पूर्णांकerface = ctrl->val;
		अवरोध;
	शेष:
		mfc_err("Invalid control 0x%08x\n", ctrl->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_dec_g_v_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		अगर (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) अणु
			ctrl->val = ctx->pb_count;
			अवरोध;
		पूर्ण अन्यथा अगर (ctx->state != MFCINST_INIT &&
				ctx->state != MFCINST_RES_CHANGE_END) अणु
			v4l2_err(&dev->v4l2_dev, "Decoding not initialised\n");
			वापस -EINVAL;
		पूर्ण
		/* Should रुको क्रम the header to be parsed */
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
				S5P_MFC_R2H_CMD_SEQ_DONE_RET, 0);
		अगर (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) अणु
			ctrl->val = ctx->pb_count;
		पूर्ण अन्यथा अणु
			v4l2_err(&dev->v4l2_dev, "Decoding not initialised\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा v4l2_ctrl_ops s5p_mfc_dec_ctrl_ops = अणु
	.s_ctrl = s5p_mfc_dec_s_ctrl,
	.g_अस्थिर_ctrl = s5p_mfc_dec_g_v_ctrl,
पूर्ण;

/* Get compose inक्रमmation */
अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	u32 left, right, top, bottom;
	u32 width, height;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (ctx->state != MFCINST_HEAD_PARSED &&
	    ctx->state != MFCINST_RUNNING &&
	    ctx->state != MFCINST_FINISHING &&
	    ctx->state != MFCINST_FINISHED) अणु
		mfc_err("Can not get compose information\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_H264) अणु
		left = s5p_mfc_hw_call(dev->mfc_ops, get_crop_info_h, ctx);
		right = left >> S5P_FIMV_SHARED_CROP_RIGHT_SHIFT;
		left = left & S5P_FIMV_SHARED_CROP_LEFT_MASK;
		top = s5p_mfc_hw_call(dev->mfc_ops, get_crop_info_v, ctx);
		bottom = top >> S5P_FIMV_SHARED_CROP_BOTTOM_SHIFT;
		top = top & S5P_FIMV_SHARED_CROP_TOP_MASK;
		width = ctx->img_width - left - right;
		height = ctx->img_height - top - bottom;
		mfc_debug(2, "Composing info [h264]: l=%d t=%d w=%d h=%d (r=%d b=%d fw=%d fh=%d\n",
			  left, top, s->r.width, s->r.height, right, bottom,
			  ctx->buf_width, ctx->buf_height);
	पूर्ण अन्यथा अणु
		left = 0;
		top = 0;
		width = ctx->img_width;
		height = ctx->img_height;
		mfc_debug(2, "Composing info: w=%d h=%d fw=%d fh=%d\n",
			  s->r.width, s->r.height, ctx->buf_width,
			  ctx->buf_height);
	पूर्ण

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		s->r.left = left;
		s->r.top = top;
		s->r.width = width;
		s->r.height = height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_decoder_cmd(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_decoder_cmd *cmd)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *buf;
	अचिन्हित दीर्घ flags;

	चयन (cmd->cmd) अणु
	हाल V4L2_DEC_CMD_STOP:
		अगर (cmd->flags != 0)
			वापस -EINVAL;

		अगर (!vb2_is_streaming(&ctx->vq_src))
			वापस -EINVAL;

		spin_lock_irqsave(&dev->irqlock, flags);
		अगर (list_empty(&ctx->src_queue)) अणु
			mfc_err("EOS: empty src queue, entering finishing state");
			ctx->state = MFCINST_FINISHING;
			अगर (s5p_mfc_ctx_पढ़ोy(ctx))
				set_work_bit_irqsave(ctx);
			spin_unlock_irqrestore(&dev->irqlock, flags);
			s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
		पूर्ण अन्यथा अणु
			mfc_err("EOS: marking last buffer of stream");
			buf = list_entry(ctx->src_queue.prev,
						काष्ठा s5p_mfc_buf, list);
			अगर (buf->flags & MFC_BUF_FLAG_USED)
				ctx->state = MFCINST_FINISHING;
			अन्यथा
				buf->flags |= MFC_BUF_FLAG_EOS;
			spin_unlock_irqrestore(&dev->irqlock, flags);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा  v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/* v4l2_ioctl_ops */
अटल स्थिर काष्ठा v4l2_ioctl_ops s5p_mfc_dec_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mplane = vidioc_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = vidioc_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane = vidioc_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = vidioc_s_fmt,
	.vidioc_reqbufs = vidioc_reqbufs,
	.vidioc_querybuf = vidioc_querybuf,
	.vidioc_qbuf = vidioc_qbuf,
	.vidioc_dqbuf = vidioc_dqbuf,
	.vidioc_expbuf = vidioc_expbuf,
	.vidioc_streamon = vidioc_streamon,
	.vidioc_streamoff = vidioc_streamoff,
	.vidioc_g_selection = vidioc_g_selection,
	.vidioc_decoder_cmd = vidioc_decoder_cmd,
	.vidioc_subscribe_event = vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक s5p_mfc_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *buf_count,
			अचिन्हित पूर्णांक *plane_count, अचिन्हित पूर्णांक psize[],
			काष्ठा device *alloc_devs[])
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	/* Video output क्रम decoding (source)
	 * this can be set after getting an instance */
	अगर (ctx->state == MFCINST_INIT &&
	    vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/* A single plane is required क्रम input */
		*plane_count = 1;
		अगर (*buf_count < 1)
			*buf_count = 1;
		अगर (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
	/* Video capture क्रम decoding (destination)
	 * this can be set after the header was parsed */
	पूर्ण अन्यथा अगर (ctx->state == MFCINST_HEAD_PARSED &&
		   vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		/* Output plane count is 2 - one क्रम Y and one क्रम CbCr */
		*plane_count = 2;
		/* Setup buffer count */
		अगर (*buf_count < ctx->pb_count)
			*buf_count = ctx->pb_count;
		अगर (*buf_count > ctx->pb_count + MFC_MAX_EXTRA_DPB)
			*buf_count = ctx->pb_count + MFC_MAX_EXTRA_DPB;
		अगर (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
	पूर्ण अन्यथा अणु
		mfc_err("State seems invalid. State = %d, vq->type = %d\n",
							ctx->state, vq->type);
		वापस -EINVAL;
	पूर्ण
	mfc_debug(2, "Buffer count=%d, plane count=%d\n",
						*buf_count, *plane_count);
	अगर (ctx->state == MFCINST_HEAD_PARSED &&
	    vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		psize[0] = ctx->luma_size;
		psize[1] = ctx->chroma_size;

		अगर (IS_MFCV6_PLUS(dev))
			alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
		अन्यथा
			alloc_devs[0] = ctx->dev->mem_dev[BANK_R_CTX];
		alloc_devs[1] = ctx->dev->mem_dev[BANK_L_CTX];
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
		   ctx->state == MFCINST_INIT) अणु
		psize[0] = ctx->dec_src_buf_size;
		alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
	पूर्ण अन्यथा अणु
		mfc_err("This video node is dedicated to decoding. Decoding not initialized\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	अचिन्हित पूर्णांक i;

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		अगर (ctx->capture_state == QUEUE_BUFS_MMAPED)
			वापस 0;
		क्रम (i = 0; i < ctx->dst_fmt->num_planes; i++) अणु
			अगर (IS_ERR_OR_शून्य(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, i)))) अणु
				mfc_err("Plane mem not allocated\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (vb2_plane_size(vb, 0) < ctx->luma_size ||
			vb2_plane_size(vb, 1) < ctx->chroma_size) अणु
			mfc_err("Plane buffer (CAPTURE) is too small\n");
			वापस -EINVAL;
		पूर्ण
		i = vb->index;
		ctx->dst_bufs[i].b = vbuf;
		ctx->dst_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->dst_bufs_cnt++;
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (IS_ERR_OR_शून्य(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, 0)))) अणु
			mfc_err("Plane memory not allocated\n");
			वापस -EINVAL;
		पूर्ण
		अगर (vb2_plane_size(vb, 0) < ctx->dec_src_buf_size) अणु
			mfc_err("Plane buffer (OUTPUT) is too small\n");
			वापस -EINVAL;
		पूर्ण

		i = vb->index;
		ctx->src_bufs[i].b = vbuf;
		ctx->src_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs_cnt++;
	पूर्ण अन्यथा अणु
		mfc_err("s5p_mfc_buf_init: unknown queue type\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	अगर (ctx->state == MFCINST_FINISHING ||
		ctx->state == MFCINST_FINISHED)
		ctx->state = MFCINST_RUNNING;
	/* If context is पढ़ोy then dev = work->data;schedule it to run */
	अगर (s5p_mfc_ctx_पढ़ोy(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_stop_streaming(काष्ठा vb2_queue *q)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	पूर्णांक पातed = 0;

	spin_lock_irqsave(&dev->irqlock, flags);
	अगर ((ctx->state == MFCINST_FINISHING ||
		ctx->state ==  MFCINST_RUNNING) &&
		dev->curr_ctx == ctx->num && dev->hw_lock) अणु
		ctx->state = MFCINST_ABORT;
		spin_unlock_irqrestore(&dev->irqlock, flags);
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
					S5P_MFC_R2H_CMD_FRAME_DONE_RET, 0);
		पातed = 1;
		spin_lock_irqsave(&dev->irqlock, flags);
	पूर्ण
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		s5p_mfc_cleanup_queue(&ctx->dst_queue, &ctx->vq_dst);
		INIT_LIST_HEAD(&ctx->dst_queue);
		ctx->dst_queue_cnt = 0;
		ctx->dpb_flush_flag = 1;
		ctx->dec_dst_flag = 0;
		अगर (IS_MFCV6_PLUS(dev) && (ctx->state == MFCINST_RUNNING)) अणु
			ctx->state = MFCINST_FLUSH;
			set_work_bit_irqsave(ctx);
			s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
			spin_unlock_irqrestore(&dev->irqlock, flags);
			अगर (s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
				S5P_MFC_R2H_CMD_DPB_FLUSH_RET, 0))
				mfc_err("Err flushing buffers\n");
			spin_lock_irqsave(&dev->irqlock, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		s5p_mfc_cleanup_queue(&ctx->src_queue, &ctx->vq_src);
		INIT_LIST_HEAD(&ctx->src_queue);
		ctx->src_queue_cnt = 0;
	पूर्ण
	अगर (पातed)
		ctx->state = MFCINST_RUNNING;
	spin_unlock_irqrestore(&dev->irqlock, flags);
पूर्ण


अटल व्योम s5p_mfc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित दीर्घ flags;
	काष्ठा s5p_mfc_buf *mfc_buf;

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		mfc_buf = &ctx->src_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&mfc_buf->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		mfc_buf = &ctx->dst_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		/* Mark destination as available क्रम use by MFC */
		spin_lock_irqsave(&dev->irqlock, flags);
		set_bit(vb->index, &ctx->dec_dst_flag);
		list_add_tail(&mfc_buf->list, &ctx->dst_queue);
		ctx->dst_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	पूर्ण अन्यथा अणु
		mfc_err("Unsupported buffer type (%d)\n", vq->type);
	पूर्ण
	अगर (s5p_mfc_ctx_पढ़ोy(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
पूर्ण

अटल काष्ठा vb2_ops s5p_mfc_dec_qops = अणु
	.queue_setup		= s5p_mfc_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_init		= s5p_mfc_buf_init,
	.start_streaming	= s5p_mfc_start_streaming,
	.stop_streaming		= s5p_mfc_stop_streaming,
	.buf_queue		= s5p_mfc_buf_queue,
पूर्ण;

स्थिर काष्ठा s5p_mfc_codec_ops *get_dec_codec_ops(व्योम)
अणु
	वापस &decoder_codec_ops;
पूर्ण

काष्ठा vb2_ops *get_dec_queue_ops(व्योम)
अणु
	वापस &s5p_mfc_dec_qops;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops *get_dec_v4l2_ioctl_ops(व्योम)
अणु
	वापस &s5p_mfc_dec_ioctl_ops;
पूर्ण

#घोषणा IS_MFC51_PRIV(x) ((V4L2_CTRL_ID2WHICH(x) == V4L2_CTRL_CLASS_CODEC) \
						&& V4L2_CTRL_DRIVER_PRIV(x))

पूर्णांक s5p_mfc_dec_ctrls_setup(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl_config cfg;
	पूर्णांक i;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, NUM_CTRLS);
	अगर (ctx->ctrl_handler.error) अणु
		mfc_err("v4l2_ctrl_handler_init failed\n");
		वापस ctx->ctrl_handler.error;
	पूर्ण

	क्रम (i = 0; i < NUM_CTRLS; i++) अणु
		अगर (IS_MFC51_PRIV(controls[i].id)) अणु
			स_रखो(&cfg, 0, माप(काष्ठा v4l2_ctrl_config));
			cfg.ops = &s5p_mfc_dec_ctrl_ops;
			cfg.id = controls[i].id;
			cfg.min = controls[i].minimum;
			cfg.max = controls[i].maximum;
			cfg.def = controls[i].शेष_value;
			cfg.name = controls[i].name;
			cfg.type = controls[i].type;

			cfg.step = controls[i].step;
			cfg.menu_skip_mask = 0;

			ctx->ctrls[i] = v4l2_ctrl_new_custom(&ctx->ctrl_handler,
					&cfg, शून्य);
		पूर्ण अन्यथा अणु
			ctx->ctrls[i] = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					&s5p_mfc_dec_ctrl_ops,
					controls[i].id, controls[i].minimum,
					controls[i].maximum, controls[i].step,
					controls[i].शेष_value);
		पूर्ण
		अगर (ctx->ctrl_handler.error) अणु
			mfc_err("Adding control (%d) failed\n", i);
			वापस ctx->ctrl_handler.error;
		पूर्ण
		अगर (controls[i].is_अस्थिर && ctx->ctrls[i])
			ctx->ctrls[i]->flags |= V4L2_CTRL_FLAG_VOLATILE;
	पूर्ण
	वापस 0;
पूर्ण

व्योम s5p_mfc_dec_ctrls_delete(काष्ठा s5p_mfc_ctx *ctx)
अणु
	पूर्णांक i;

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	क्रम (i = 0; i < NUM_CTRLS; i++)
		ctx->ctrls[i] = शून्य;
पूर्ण

व्योम s5p_mfc_dec_init(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा v4l2_क्रमmat f;
	f.fmt.pix_mp.pixelक्रमmat = V4L2_PIX_FMT_H264;
	ctx->src_fmt = find_क्रमmat(&f, MFC_FMT_DEC);
	अगर (IS_MFCV8_PLUS(ctx->dev))
		f.fmt.pix_mp.pixelक्रमmat = V4L2_PIX_FMT_NV12M;
	अन्यथा अगर (IS_MFCV6_PLUS(ctx->dev))
		f.fmt.pix_mp.pixelक्रमmat = V4L2_PIX_FMT_NV12MT_16X16;
	अन्यथा
		f.fmt.pix_mp.pixelक्रमmat = V4L2_PIX_FMT_NV12MT;
	ctx->dst_fmt = find_क्रमmat(&f, MFC_FMT_RAW);
	mfc_debug(2, "Default src_fmt is %p, dest_fmt is %p\n",
			ctx->src_fmt, ctx->dst_fmt);
पूर्ण

