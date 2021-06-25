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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "cedrus.h"
#समावेश "cedrus_video.h"
#समावेश "cedrus_dec.h"
#समावेश "cedrus_hw.h"

अटल स्थिर काष्ठा cedrus_control cedrus_controls[] = अणु
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_MPEG2,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION,
		पूर्ण,
		.codec		= CEDRUS_CODEC_MPEG2,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_DECODE_PARAMS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_SLICE_PARAMS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_SPS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_PPS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_SCALING_MATRIX,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_PRED_WEIGHTS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_DECODE_MODE,
			.max	= V4L2_STATELESS_H264_DECODE_MODE_SLICE_BASED,
			.def	= V4L2_STATELESS_H264_DECODE_MODE_SLICE_BASED,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_H264_START_CODE,
			.max	= V4L2_STATELESS_H264_START_CODE_NONE,
			.def	= V4L2_STATELESS_H264_START_CODE_NONE,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	/*
	 * We only expose supported profiles inक्रमmation,
	 * and not levels as it's not clear what is supported
	 * क्रम each hardware/core version.
	 * In any हाल, TRY/S_FMT will clamp the क्रमmat resolution
	 * to the maximum supported.
	 */
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_H264_PROखाता,
			.min	= V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE,
			.def	= V4L2_MPEG_VIDEO_H264_PROखाता_MAIN,
			.max	= V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
			.menu_skip_mask =
				BIT(V4L2_MPEG_VIDEO_H264_PROखाता_EXTENDED),
		पूर्ण,
		.codec		= CEDRUS_CODEC_H264,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_HEVC_SPS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H265,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_HEVC_PPS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H265,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_HEVC_SLICE_PARAMS,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H265,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_HEVC_DECODE_MODE,
			.max	= V4L2_MPEG_VIDEO_HEVC_DECODE_MODE_SLICE_BASED,
			.def	= V4L2_MPEG_VIDEO_HEVC_DECODE_MODE_SLICE_BASED,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H265,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_MPEG_VIDEO_HEVC_START_CODE,
			.max	= V4L2_MPEG_VIDEO_HEVC_START_CODE_NONE,
			.def	= V4L2_MPEG_VIDEO_HEVC_START_CODE_NONE,
		पूर्ण,
		.codec		= CEDRUS_CODEC_H265,
	पूर्ण,
	अणु
		.cfg = अणु
			.id	= V4L2_CID_STATELESS_VP8_FRAME,
		पूर्ण,
		.codec		= CEDRUS_CODEC_VP8,
	पूर्ण,
पूर्ण;

#घोषणा CEDRUS_CONTROLS_COUNT	ARRAY_SIZE(cedrus_controls)

व्योम *cedrus_find_control_data(काष्ठा cedrus_ctx *ctx, u32 id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; ctx->ctrls[i]; i++)
		अगर (ctx->ctrls[i]->id == id)
			वापस ctx->ctrls[i]->p_cur.p;

	वापस शून्य;
पूर्ण

अटल पूर्णांक cedrus_init_ctrls(काष्ठा cedrus_dev *dev, काष्ठा cedrus_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &ctx->hdl;
	काष्ठा v4l2_ctrl *ctrl;
	अचिन्हित पूर्णांक ctrl_size;
	अचिन्हित पूर्णांक i;

	v4l2_ctrl_handler_init(hdl, CEDRUS_CONTROLS_COUNT);
	अगर (hdl->error) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize control handler\n");
		वापस hdl->error;
	पूर्ण

	ctrl_size = माप(ctrl) * CEDRUS_CONTROLS_COUNT + 1;

	ctx->ctrls = kzalloc(ctrl_size, GFP_KERNEL);
	अगर (!ctx->ctrls)
		वापस -ENOMEM;

	क्रम (i = 0; i < CEDRUS_CONTROLS_COUNT; i++) अणु
		ctrl = v4l2_ctrl_new_custom(hdl, &cedrus_controls[i].cfg,
					    शून्य);
		अगर (hdl->error) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed to create new custom control\n");

			v4l2_ctrl_handler_मुक्त(hdl);
			kमुक्त(ctx->ctrls);
			वापस hdl->error;
		पूर्ण

		ctx->ctrls[i] = ctrl;
	पूर्ण

	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	वापस 0;
पूर्ण

अटल पूर्णांक cedrus_request_validate(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा cedrus_ctx *ctx = शून्य;
	अचिन्हित पूर्णांक count;

	list_क्रम_each_entry(obj, &req->objects, list) अणु
		काष्ठा vb2_buffer *vb;

		अगर (vb2_request_object_is_buffer(obj)) अणु
			vb = container_of(obj, काष्ठा vb2_buffer, req_obj);
			ctx = vb2_get_drv_priv(vb->vb2_queue);

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ctx)
		वापस -ENOENT;

	count = vb2_request_buffer_cnt(req);
	अगर (!count) अणु
		v4l2_info(&ctx->dev->v4l2_dev,
			  "No buffer was provided with the request\n");
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (count > 1) अणु
		v4l2_info(&ctx->dev->v4l2_dev,
			  "More than one buffer was provided with the request\n");
		वापस -EINVAL;
	पूर्ण

	वापस vb2_request_validate(req);
पूर्ण

अटल पूर्णांक cedrus_खोलो(काष्ठा file *file)
अणु
	काष्ठा cedrus_dev *dev = video_drvdata(file);
	काष्ठा cedrus_ctx *ctx = शून्य;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->dev_mutex))
		वापस -ERESTARTSYS;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		mutex_unlock(&dev->dev_mutex);
		वापस -ENOMEM;
	पूर्ण

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = dev;

	ret = cedrus_init_ctrls(dev, ctx);
	अगर (ret)
		जाओ err_मुक्त;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &cedrus_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_ctrls;
	पूर्ण
	ctx->dst_fmt.pixelक्रमmat = V4L2_PIX_FMT_SUNXI_TILED_NV12;
	cedrus_prepare_क्रमmat(&ctx->dst_fmt);
	ctx->src_fmt.pixelक्रमmat = V4L2_PIX_FMT_MPEG2_SLICE;
	/*
	 * TILED_NV12 has more strict requirements, so copy the width and
	 * height to src_fmt to ensure that is matches the dst_fmt resolution.
	 */
	ctx->src_fmt.width = ctx->dst_fmt.width;
	ctx->src_fmt.height = ctx->dst_fmt.height;
	cedrus_prepare_क्रमmat(&ctx->src_fmt);

	v4l2_fh_add(&ctx->fh);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;

err_ctrls:
	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
err_मुक्त:
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक cedrus_release(काष्ठा file *file)
अणु
	काष्ठा cedrus_dev *dev = video_drvdata(file);
	काष्ठा cedrus_ctx *ctx = container_of(file->निजी_data,
					      काष्ठा cedrus_ctx, fh);

	mutex_lock(&dev->dev_mutex);

	v4l2_fh_del(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
	kमुक्त(ctx->ctrls);

	v4l2_fh_निकास(&ctx->fh);

	kमुक्त(ctx);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations cedrus_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cedrus_खोलो,
	.release	= cedrus_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device cedrus_video_device = अणु
	.name		= CEDRUS_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &cedrus_fops,
	.ioctl_ops	= &cedrus_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops cedrus_m2m_ops = अणु
	.device_run	= cedrus_device_run,
पूर्ण;

अटल स्थिर काष्ठा media_device_ops cedrus_m2m_media_ops = अणु
	.req_validate	= cedrus_request_validate,
	.req_queue	= v4l2_m2m_request_queue,
पूर्ण;

अटल पूर्णांक cedrus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cedrus_dev *dev;
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->vfd = cedrus_video_device;
	dev->dev = &pdev->dev;
	dev->pdev = pdev;

	ret = cedrus_hw_probe(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to probe hardware\n");
		वापस ret;
	पूर्ण

	dev->dec_ops[CEDRUS_CODEC_MPEG2] = &cedrus_dec_ops_mpeg2;
	dev->dec_ops[CEDRUS_CODEC_H264] = &cedrus_dec_ops_h264;
	dev->dec_ops[CEDRUS_CODEC_H265] = &cedrus_dec_ops_h265;
	dev->dec_ops[CEDRUS_CODEC_VP8] = &cedrus_dec_ops_vp8;

	mutex_init(&dev->dev_mutex);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register V4L2 device\n");
		वापस ret;
	पूर्ण

	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	snम_लिखो(vfd->name, माप(vfd->name), "%s", cedrus_video_device.name);
	video_set_drvdata(vfd, dev);

	dev->m2m_dev = v4l2_m2m_init(&cedrus_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M device\n");
		ret = PTR_ERR(dev->m2m_dev);

		जाओ err_v4l2;
	पूर्ण

	dev->mdev.dev = &pdev->dev;
	strscpy(dev->mdev.model, CEDRUS_NAME, माप(dev->mdev.model));
	strscpy(dev->mdev.bus_info, "platform:" CEDRUS_NAME,
		माप(dev->mdev.bus_info));

	media_device_init(&dev->mdev);
	dev->mdev.ops = &cedrus_m2m_media_ops;
	dev->v4l2_dev.mdev = &dev->mdev;

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		जाओ err_m2m;
	पूर्ण

	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	ret = v4l2_m2m_रेजिस्टर_media_controller(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PROC_VIDEO_DECODER);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M media controller\n");
		जाओ err_video;
	पूर्ण

	ret = media_device_रेजिस्टर(&dev->mdev);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register media device\n");
		जाओ err_m2m_mc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	वापस 0;

err_m2m_mc:
	v4l2_m2m_unरेजिस्टर_media_controller(dev->m2m_dev);
err_video:
	video_unरेजिस्टर_device(&dev->vfd);
err_m2m:
	v4l2_m2m_release(dev->m2m_dev);
err_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक cedrus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cedrus_dev *dev = platक्रमm_get_drvdata(pdev);

	अगर (media_devnode_is_रेजिस्टरed(dev->mdev.devnode)) अणु
		media_device_unरेजिस्टर(&dev->mdev);
		v4l2_m2m_unरेजिस्टर_media_controller(dev->m2m_dev);
		media_device_cleanup(&dev->mdev);
	पूर्ण

	v4l2_m2m_release(dev->m2m_dev);
	video_unरेजिस्टर_device(&dev->vfd);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	cedrus_hw_हटाओ(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cedrus_variant sun4i_a10_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 320000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun5i_a13_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 320000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun7i_a20_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 320000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun8i_a33_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 320000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun8i_h3_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_H265_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 402000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun8i_v3s_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_H264_DEC,
	.mod_rate	= 297000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun8i_r40_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 297000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun50i_a64_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_H265_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 402000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun50i_h5_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_H265_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 402000000,
पूर्ण;

अटल स्थिर काष्ठा cedrus_variant sun50i_h6_cedrus_variant = अणु
	.capabilities	= CEDRUS_CAPABILITY_UNTILED |
			  CEDRUS_CAPABILITY_MPEG2_DEC |
			  CEDRUS_CAPABILITY_H264_DEC |
			  CEDRUS_CAPABILITY_H265_DEC |
			  CEDRUS_CAPABILITY_VP8_DEC,
	.mod_rate	= 600000000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cedrus_dt_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-video-engine",
		.data = &sun4i_a10_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun5i-a13-video-engine",
		.data = &sun5i_a13_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun7i-a20-video-engine",
		.data = &sun7i_a20_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a33-video-engine",
		.data = &sun8i_a33_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-video-engine",
		.data = &sun8i_h3_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-v3s-video-engine",
		.data = &sun8i_v3s_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-r40-video-engine",
		.data = &sun8i_r40_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-video-engine",
		.data = &sun50i_a64_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h5-video-engine",
		.data = &sun50i_h5_cedrus_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-video-engine",
		.data = &sun50i_h6_cedrus_variant,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cedrus_dt_match);

अटल स्थिर काष्ठा dev_pm_ops cedrus_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cedrus_hw_suspend,
			   cedrus_hw_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver cedrus_driver = अणु
	.probe		= cedrus_probe,
	.हटाओ		= cedrus_हटाओ,
	.driver		= अणु
		.name		= CEDRUS_NAME,
		.of_match_table	= of_match_ptr(cedrus_dt_match),
		.pm		= &cedrus_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cedrus_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Florent Revest <florent.revest@free-electrons.com>");
MODULE_AUTHOR("Paul Kocialkowski <paul.kocialkowski@bootlin.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_DESCRIPTION("Cedrus VPU driver");
