<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Video Capture Subdev क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2012-2016 Mentor Graphics Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <video/imx-ipu-v3.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"

#घोषणा IMX_CAPTURE_NAME "imx-capture"

काष्ठा capture_priv अणु
	काष्ठा imx_media_dev *md;		/* Media device */
	काष्ठा device *dev;			/* Physical device */

	काष्ठा imx_media_video_dev vdev;	/* Video device */
	काष्ठा media_pad vdev_pad;		/* Video device pad */

	काष्ठा v4l2_subdev *src_sd;		/* Source subdev */
	पूर्णांक src_sd_pad;				/* Source subdev pad */

	काष्ठा mutex mutex;			/* Protect vdev operations */

	काष्ठा vb2_queue q;			/* The videobuf2 queue */
	काष्ठा list_head पढ़ोy_q;		/* List of queued buffers */
	spinlock_t q_lock;			/* Protect पढ़ोy_q */

	काष्ठा v4l2_ctrl_handler ctrl_hdlr;	/* Controls inherited from subdevs */

	bool legacy_api;			/* Use the legacy (pre-MC) API */
पूर्ण;

#घोषणा to_capture_priv(v) container_of(v, काष्ठा capture_priv, vdev)

/* In bytes, per queue */
#घोषणा VID_MEM_LIMIT	SZ_64M

/* -----------------------------------------------------------------------------
 * MC-Centric Video IOCTLs
 */

अटल स्थिर काष्ठा imx_media_pixfmt *capture_find_क्रमmat(u32 code, u32 fourcc)
अणु
	स्थिर काष्ठा imx_media_pixfmt *cc;

	cc = imx_media_find_ipu_क्रमmat(code, PIXFMT_SEL_YUV_RGB);
	अगर (cc) अणु
		क्रमागत imx_pixfmt_sel fmt_sel = cc->cs == IPUV3_COLORSPACE_YUV
					    ? PIXFMT_SEL_YUV : PIXFMT_SEL_RGB;

		cc = imx_media_find_pixel_क्रमmat(fourcc, fmt_sel);
		अगर (!cc) अणु
			imx_media_क्रमागत_pixel_क्रमmats(&fourcc, 0, fmt_sel, 0);
			cc = imx_media_find_pixel_क्रमmat(fourcc, fmt_sel);
		पूर्ण

		वापस cc;
	पूर्ण

	वापस imx_media_find_mbus_क्रमmat(code, PIXFMT_SEL_ANY);
पूर्ण

अटल पूर्णांक capture_querycap(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_capability *cap)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	strscpy(cap->driver, IMX_CAPTURE_NAME, माप(cap->driver));
	strscpy(cap->card, IMX_CAPTURE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", dev_name(priv->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक capture_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_fmtdesc *f)
अणु
	वापस imx_media_क्रमागत_pixel_क्रमmats(&f->pixelक्रमmat, f->index,
					    PIXFMT_SEL_ANY, f->mbus_code);
पूर्ण

अटल पूर्णांक capture_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा imx_media_pixfmt *cc;

	अगर (fsize->index > 0)
		वापस -EINVAL;

	cc = imx_media_find_pixel_क्रमmat(fsize->pixel_क्रमmat, PIXFMT_SEL_ANY);
	अगर (!cc)
		वापस -EINVAL;

	/*
	 * TODO: The स्थिरraपूर्णांकs are hardware-specअगरic and may depend on the
	 * pixel क्रमmat. This should come from the driver using
	 * imx_media_capture.
	 */
	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = 1;
	fsize->stepwise.max_width = 65535;
	fsize->stepwise.min_height = 1;
	fsize->stepwise.max_height = 65535;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	f->fmt.pix = priv->vdev.fmt;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा imx_media_pixfmt *
__capture_try_fmt(काष्ठा v4l2_pix_क्रमmat *pixfmt, काष्ठा v4l2_rect *compose)
अणु
	काष्ठा v4l2_mbus_framefmt fmt_src;
	स्थिर काष्ठा imx_media_pixfmt *cc;

	/*
	 * Find the pixel क्रमmat, शेष to the first supported क्रमmat अगर not
	 * found.
	 */
	cc = imx_media_find_pixel_क्रमmat(pixfmt->pixelक्रमmat, PIXFMT_SEL_ANY);
	अगर (!cc) अणु
		imx_media_क्रमागत_pixel_क्रमmats(&pixfmt->pixelक्रमmat, 0,
					     PIXFMT_SEL_ANY, 0);
		cc = imx_media_find_pixel_क्रमmat(pixfmt->pixelक्रमmat,
						 PIXFMT_SEL_ANY);
	पूर्ण

	/* Allow IDMAC पूर्णांकerweave but enक्रमce field order from source. */
	अगर (V4L2_FIELD_IS_INTERLACED(pixfmt->field)) अणु
		चयन (pixfmt->field) अणु
		हाल V4L2_FIELD_SEQ_TB:
			pixfmt->field = V4L2_FIELD_INTERLACED_TB;
			अवरोध;
		हाल V4L2_FIELD_SEQ_BT:
			pixfmt->field = V4L2_FIELD_INTERLACED_BT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	v4l2_fill_mbus_क्रमmat(&fmt_src, pixfmt, 0);
	imx_media_mbus_fmt_to_pix_fmt(pixfmt, &fmt_src, cc);

	अगर (compose) अणु
		compose->width = fmt_src.width;
		compose->height = fmt_src.height;
	पूर्ण

	वापस cc;
पूर्ण

अटल पूर्णांक capture_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	__capture_try_fmt(&f->fmt.pix, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	स्थिर काष्ठा imx_media_pixfmt *cc;

	अगर (vb2_is_busy(&priv->q)) अणु
		dev_err(priv->dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	cc = __capture_try_fmt(&f->fmt.pix, &priv->vdev.compose);

	priv->vdev.cc = cc;
	priv->vdev.fmt = f->fmt.pix;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_g_selection(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_selection *s)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		/* The compose rectangle is fixed to the source क्रमmat. */
		s->r = priv->vdev.compose;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
		/*
		 * The hardware ग_लिखोs with a configurable but fixed DMA burst
		 * size. If the source क्रमmat width is not burst size aligned,
		 * the written frame contains padding to the right.
		 */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = priv->vdev.fmt.width;
		s->r.height = priv->vdev.fmt.height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक capture_subscribe_event(काष्ठा v4l2_fh *fh,
				   स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_IMX_FRAME_INTERVAL_ERROR:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops capture_ioctl_ops = अणु
	.vidioc_querycap		= capture_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= capture_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes		= capture_क्रमागत_framesizes,

	.vidioc_g_fmt_vid_cap		= capture_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= capture_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= capture_s_fmt_vid_cap,

	.vidioc_g_selection		= capture_g_selection,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_subscribe_event		= capture_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Legacy Video IOCTLs
 */

अटल पूर्णांक capture_legacy_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.index = fsize->index,
		.pad = priv->src_sd_pad,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	cc = imx_media_find_pixel_क्रमmat(fsize->pixel_क्रमmat, PIXFMT_SEL_ANY);
	अगर (!cc)
		वापस -EINVAL;

	fse.code = cc->codes ? cc->codes[0] : 0;

	ret = v4l2_subdev_call(priv->src_sd, pad, क्रमागत_frame_size, शून्य, &fse);
	अगर (ret)
		वापस ret;

	अगर (fse.min_width == fse.max_width &&
	    fse.min_height == fse.max_height) अणु
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = fse.min_width;
		fsize->discrete.height = fse.min_height;
	पूर्ण अन्यथा अणु
		fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
		fsize->stepwise.min_width = fse.min_width;
		fsize->stepwise.max_width = fse.max_width;
		fsize->stepwise.min_height = fse.min_height;
		fsize->stepwise.max_height = fse.max_height;
		fsize->stepwise.step_width = 1;
		fsize->stepwise.step_height = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					      काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = fival->index,
		.pad = priv->src_sd_pad,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	cc = imx_media_find_pixel_क्रमmat(fival->pixel_क्रमmat, PIXFMT_SEL_ANY);
	अगर (!cc)
		वापस -EINVAL;

	fie.code = cc->codes ? cc->codes[0] : 0;

	ret = v4l2_subdev_call(priv->src_sd, pad, क्रमागत_frame_पूर्णांकerval,
			       शून्य, &fie);
	अगर (ret)
		वापस ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	स्थिर काष्ठा imx_media_pixfmt *cc_src;
	काष्ठा v4l2_subdev_क्रमmat fmt_src;
	u32 fourcc;
	पूर्णांक ret;

	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, शून्य, &fmt_src);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to get src_sd format\n");
		वापस ret;
	पूर्ण

	cc_src = imx_media_find_ipu_क्रमmat(fmt_src.क्रमmat.code,
					   PIXFMT_SEL_YUV_RGB);
	अगर (cc_src) अणु
		क्रमागत imx_pixfmt_sel fmt_sel =
			(cc_src->cs == IPUV3_COLORSPACE_YUV) ?
			PIXFMT_SEL_YUV : PIXFMT_SEL_RGB;

		ret = imx_media_क्रमागत_pixel_क्रमmats(&fourcc, f->index, fmt_sel,
						   0);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		cc_src = imx_media_find_mbus_क्रमmat(fmt_src.क्रमmat.code,
						    PIXFMT_SEL_ANY);
		अगर (WARN_ON(!cc_src))
			वापस -EINVAL;

		अगर (f->index != 0)
			वापस -EINVAL;
		fourcc = cc_src->fourcc;
	पूर्ण

	f->pixelक्रमmat = fourcc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा imx_media_pixfmt *
__capture_legacy_try_fmt(काष्ठा capture_priv *priv,
			 काष्ठा v4l2_subdev_क्रमmat *fmt_src,
			 काष्ठा v4l2_pix_क्रमmat *pixfmt)
अणु
	स्थिर काष्ठा imx_media_pixfmt *cc;

	cc = capture_find_क्रमmat(fmt_src->क्रमmat.code, pixfmt->pixelक्रमmat);
	अगर (WARN_ON(!cc))
		वापस शून्य;

	/* allow IDMAC पूर्णांकerweave but enक्रमce field order from source */
	अगर (V4L2_FIELD_IS_INTERLACED(pixfmt->field)) अणु
		चयन (fmt_src->क्रमmat.field) अणु
		हाल V4L2_FIELD_SEQ_TB:
			fmt_src->क्रमmat.field = V4L2_FIELD_INTERLACED_TB;
			अवरोध;
		हाल V4L2_FIELD_SEQ_BT:
			fmt_src->क्रमmat.field = V4L2_FIELD_INTERLACED_BT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	imx_media_mbus_fmt_to_pix_fmt(pixfmt, &fmt_src->क्रमmat, cc);

	वापस cc;
पूर्ण

अटल पूर्णांक capture_legacy_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat fmt_src;
	पूर्णांक ret;

	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, शून्य, &fmt_src);
	अगर (ret)
		वापस ret;

	अगर (!__capture_legacy_try_fmt(priv, &fmt_src, &f->fmt.pix))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat fmt_src;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	पूर्णांक ret;

	अगर (vb2_is_busy(&priv->q)) अणु
		dev_err(priv->dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, शून्य, &fmt_src);
	अगर (ret)
		वापस ret;

	cc = __capture_legacy_try_fmt(priv, &fmt_src, &f->fmt.pix);
	अगर (!cc)
		वापस -EINVAL;

	priv->vdev.cc = cc;
	priv->vdev.fmt = f->fmt.pix;
	priv->vdev.compose.width = fmt_src.क्रमmat.width;
	priv->vdev.compose.height = fmt_src.क्रमmat.height;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_querystd(काष्ठा file *file, व्योम *fh,
				   v4l2_std_id *std)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	वापस v4l2_subdev_call(priv->src_sd, video, querystd, std);
पूर्ण

अटल पूर्णांक capture_legacy_g_std(काष्ठा file *file, व्योम *fh, v4l2_std_id *std)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	वापस v4l2_subdev_call(priv->src_sd, video, g_std, std);
पूर्ण

अटल पूर्णांक capture_legacy_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id std)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);

	अगर (vb2_is_busy(&priv->q))
		वापस -EBUSY;

	वापस v4l2_subdev_call(priv->src_sd, video, s_std, std);
पूर्ण

अटल पूर्णांक capture_legacy_g_parm(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_पूर्णांकerval fi;
	पूर्णांक ret;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	स_रखो(&fi, 0, माप(fi));
	fi.pad = priv->src_sd_pad;
	ret = v4l2_subdev_call(priv->src_sd, video, g_frame_पूर्णांकerval, &fi);
	अगर (ret < 0)
		वापस ret;

	a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.capture.समयperframe = fi.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_s_parm(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_पूर्णांकerval fi;
	पूर्णांक ret;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	स_रखो(&fi, 0, माप(fi));
	fi.pad = priv->src_sd_pad;
	fi.पूर्णांकerval = a->parm.capture.समयperframe;
	ret = v4l2_subdev_call(priv->src_sd, video, s_frame_पूर्णांकerval, &fi);
	अगर (ret < 0)
		वापस ret;

	a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.capture.समयperframe = fi.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_legacy_subscribe_event(काष्ठा v4l2_fh *fh,
					  स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_IMX_FRAME_INTERVAL_ERROR:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops capture_legacy_ioctl_ops = अणु
	.vidioc_querycap		= capture_querycap,

	.vidioc_क्रमागत_framesizes		= capture_legacy_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= capture_legacy_क्रमागत_frameपूर्णांकervals,

	.vidioc_क्रमागत_fmt_vid_cap	= capture_legacy_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= capture_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= capture_legacy_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= capture_legacy_s_fmt_vid_cap,

	.vidioc_querystd		= capture_legacy_querystd,
	.vidioc_g_std			= capture_legacy_g_std,
	.vidioc_s_std			= capture_legacy_s_std,

	.vidioc_g_selection		= capture_g_selection,

	.vidioc_g_parm			= capture_legacy_g_parm,
	.vidioc_s_parm			= capture_legacy_s_parm,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_subscribe_event		= capture_legacy_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Queue Operations
 */

अटल पूर्णांक capture_queue_setup(काष्ठा vb2_queue *vq,
			       अचिन्हित पूर्णांक *nbuffers,
			       अचिन्हित पूर्णांक *nplanes,
			       अचिन्हित पूर्णांक sizes[],
			       काष्ठा device *alloc_devs[])
अणु
	काष्ठा capture_priv *priv = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix = &priv->vdev.fmt;
	अचिन्हित पूर्णांक count = *nbuffers;

	अगर (vq->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (*nplanes) अणु
		अगर (*nplanes != 1 || sizes[0] < pix->sizeimage)
			वापस -EINVAL;
		count += vq->num_buffers;
	पूर्ण

	count = min_t(__u32, VID_MEM_LIMIT / pix->sizeimage, count);

	अगर (*nplanes)
		*nbuffers = (count < vq->num_buffers) ? 0 :
			count - vq->num_buffers;
	अन्यथा
		*nbuffers = count;

	*nplanes = 1;
	sizes[0] = pix->sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा imx_media_buffer *buf = to_imx_media_vb(vb);

	INIT_LIST_HEAD(&buf->list);

	वापस 0;
पूर्ण

अटल पूर्णांक capture_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा capture_priv *priv = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix = &priv->vdev.fmt;

	अगर (vb2_plane_size(vb, 0) < pix->sizeimage) अणु
		dev_err(priv->dev,
			"data will not fit into plane (%lu < %lu)\n",
			vb2_plane_size(vb, 0), (दीर्घ)pix->sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, pix->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम capture_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा capture_priv *priv = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा imx_media_buffer *buf = to_imx_media_vb(vb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->q_lock, flags);

	list_add_tail(&buf->list, &priv->पढ़ोy_q);

	spin_unlock_irqrestore(&priv->q_lock, flags);
पूर्ण

अटल पूर्णांक capture_validate_fmt(काष्ठा capture_priv *priv)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt_src;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	पूर्णांक ret;

	/* Retrieve the media bus क्रमmat on the source subdev. */
	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, शून्य, &fmt_src);
	अगर (ret)
		वापस ret;

	/*
	 * Verअगरy that the media bus size matches the size set on the video
	 * node. It is sufficient to check the compose rectangle size without
	 * checking the rounded size from vdev.fmt, as the rounded size is
	 * derived directly from the compose rectangle size, and will thus
	 * always match अगर the compose rectangle matches.
	 */
	अगर (priv->vdev.compose.width != fmt_src.क्रमmat.width ||
	    priv->vdev.compose.height != fmt_src.क्रमmat.height)
		वापस -EPIPE;

	/*
	 * Verअगरy that the media bus code is compatible with the pixel क्रमmat
	 * set on the video node.
	 */
	cc = capture_find_क्रमmat(fmt_src.क्रमmat.code, 0);
	अगर (!cc || priv->vdev.cc->cs != cc->cs)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल पूर्णांक capture_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा capture_priv *priv = vb2_get_drv_priv(vq);
	काष्ठा imx_media_buffer *buf, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = capture_validate_fmt(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "capture format not valid\n");
		जाओ वापस_bufs;
	पूर्ण

	ret = imx_media_pipeline_set_stream(priv->md, &priv->src_sd->entity,
					    true);
	अगर (ret) अणु
		dev_err(priv->dev, "pipeline start failed with %d\n", ret);
		जाओ वापस_bufs;
	पूर्ण

	वापस 0;

वापस_bufs:
	spin_lock_irqsave(&priv->q_lock, flags);
	list_क्रम_each_entry_safe(buf, पंचांगp, &priv->पढ़ोy_q, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	spin_unlock_irqrestore(&priv->q_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम capture_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा capture_priv *priv = vb2_get_drv_priv(vq);
	काष्ठा imx_media_buffer *frame;
	काष्ठा imx_media_buffer *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = imx_media_pipeline_set_stream(priv->md, &priv->src_sd->entity,
					    false);
	अगर (ret)
		dev_warn(priv->dev, "pipeline stop failed with %d\n", ret);

	/* release all active buffers */
	spin_lock_irqsave(&priv->q_lock, flags);
	list_क्रम_each_entry_safe(frame, पंचांगp, &priv->पढ़ोy_q, list) अणु
		list_del(&frame->list);
		vb2_buffer_करोne(&frame->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&priv->q_lock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops capture_qops = अणु
	.queue_setup	 = capture_queue_setup,
	.buf_init        = capture_buf_init,
	.buf_prepare	 = capture_buf_prepare,
	.buf_queue	 = capture_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
	.start_streaming = capture_start_streaming,
	.stop_streaming  = capture_stop_streaming,
पूर्ण;

/* -----------------------------------------------------------------------------
 * File Operations
 */

अटल पूर्णांक capture_खोलो(काष्ठा file *file)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा video_device *vfd = priv->vdev.vfd;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&priv->mutex))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret) अणु
		dev_err(priv->dev, "v4l2_fh_open failed\n");
		जाओ out;
	पूर्ण

	ret = v4l2_pipeline_pm_get(&vfd->entity);
	अगर (ret)
		v4l2_fh_release(file);

out:
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक capture_release(काष्ठा file *file)
अणु
	काष्ठा capture_priv *priv = video_drvdata(file);
	काष्ठा video_device *vfd = priv->vdev.vfd;
	काष्ठा vb2_queue *vq = &priv->q;

	mutex_lock(&priv->mutex);

	अगर (file->निजी_data == vq->owner) अणु
		vb2_queue_release(vq);
		vq->owner = शून्य;
	पूर्ण

	v4l2_pipeline_pm_put(&vfd->entity);

	v4l2_fh_release(file);
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations capture_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= capture_खोलो,
	.release	= capture_release,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Public API
 */

काष्ठा imx_media_buffer *
imx_media_capture_device_next_buf(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा capture_priv *priv = to_capture_priv(vdev);
	काष्ठा imx_media_buffer *buf = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->q_lock, flags);

	/* get next queued buffer */
	अगर (!list_empty(&priv->पढ़ोy_q)) अणु
		buf = list_entry(priv->पढ़ोy_q.next, काष्ठा imx_media_buffer,
				 list);
		list_del(&buf->list);
	पूर्ण

	spin_unlock_irqrestore(&priv->q_lock, flags);

	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_next_buf);

व्योम imx_media_capture_device_error(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा capture_priv *priv = to_capture_priv(vdev);
	काष्ठा vb2_queue *vq = &priv->q;
	अचिन्हित दीर्घ flags;

	अगर (!vb2_is_streaming(vq))
		वापस;

	spin_lock_irqsave(&priv->q_lock, flags);
	vb2_queue_error(vq);
	spin_unlock_irqrestore(&priv->q_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_error);

अटल पूर्णांक capture_init_क्रमmat(काष्ठा capture_priv *priv)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt_src = अणु
		.pad = priv->src_sd_pad,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा imx_media_video_dev *vdev = &priv->vdev;
	पूर्णांक ret;

	अगर (priv->legacy_api) अणु
		ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, शून्य,
				       &fmt_src);
		अगर (ret) अणु
			dev_err(priv->dev, "failed to get source format\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		fmt_src.क्रमmat.code = MEDIA_BUS_FMT_UYVY8_2X8;
		fmt_src.क्रमmat.width = IMX_MEDIA_DEF_PIX_WIDTH;
		fmt_src.क्रमmat.height = IMX_MEDIA_DEF_PIX_HEIGHT;
	पूर्ण

	imx_media_mbus_fmt_to_pix_fmt(&vdev->fmt, &fmt_src.क्रमmat, शून्य);
	vdev->compose.width = fmt_src.क्रमmat.width;
	vdev->compose.height = fmt_src.क्रमmat.height;

	vdev->cc = imx_media_find_pixel_क्रमmat(vdev->fmt.pixelक्रमmat,
					       PIXFMT_SEL_ANY);

	वापस 0;
पूर्ण

पूर्णांक imx_media_capture_device_रेजिस्टर(काष्ठा imx_media_video_dev *vdev,
				      u32 link_flags)
अणु
	काष्ठा capture_priv *priv = to_capture_priv(vdev);
	काष्ठा v4l2_subdev *sd = priv->src_sd;
	काष्ठा v4l2_device *v4l2_dev = sd->v4l2_dev;
	काष्ठा video_device *vfd = vdev->vfd;
	पूर्णांक ret;

	/* get media device */
	priv->md = container_of(v4l2_dev->mdev, काष्ठा imx_media_dev, md);

	vfd->v4l2_dev = v4l2_dev;

	/* Initialize the शेष क्रमmat and compose rectangle. */
	ret = capture_init_क्रमmat(priv);
	अगर (ret < 0)
		वापस ret;

	/* Register the video device. */
	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	dev_info(priv->dev, "Registered %s as /dev/%s\n", vfd->name,
		 video_device_node_name(vfd));

	/* Create the link from the src_sd devnode pad to device node. */
	अगर (link_flags & MEDIA_LNK_FL_IMMUTABLE)
		link_flags |= MEDIA_LNK_FL_ENABLED;
	ret = media_create_pad_link(&sd->entity, priv->src_sd_pad,
				    &vfd->entity, 0, link_flags);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to create link to device node\n");
		video_unरेजिस्टर_device(vfd);
		वापस ret;
	पूर्ण

	/* Add vdev to the video devices list. */
	imx_media_add_video_device(priv->md, vdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_रेजिस्टर);

व्योम imx_media_capture_device_unरेजिस्टर(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा capture_priv *priv = to_capture_priv(vdev);
	काष्ठा video_device *vfd = priv->vdev.vfd;

	media_entity_cleanup(&vfd->entity);
	video_unरेजिस्टर_device(vfd);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_unरेजिस्टर);

काष्ठा imx_media_video_dev *
imx_media_capture_device_init(काष्ठा device *dev, काष्ठा v4l2_subdev *src_sd,
			      पूर्णांक pad, bool legacy_api)
अणु
	काष्ठा capture_priv *priv;
	काष्ठा video_device *vfd;
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->src_sd = src_sd;
	priv->src_sd_pad = pad;
	priv->dev = dev;
	priv->legacy_api = legacy_api;

	mutex_init(&priv->mutex);
	INIT_LIST_HEAD(&priv->पढ़ोy_q);
	spin_lock_init(&priv->q_lock);

	/* Allocate and initialize the video device. */
	vfd = video_device_alloc();
	अगर (!vfd)
		वापस ERR_PTR(-ENOMEM);

	vfd->fops = &capture_fops;
	vfd->ioctl_ops = legacy_api ? &capture_legacy_ioctl_ops
		       : &capture_ioctl_ops;
	vfd->minor = -1;
	vfd->release = video_device_release;
	vfd->vfl_dir = VFL_सूची_RX;
	vfd->tvnorms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM;
	vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING
			 | (!legacy_api ? V4L2_CAP_IO_MC : 0);
	vfd->lock = &priv->mutex;
	vfd->queue = &priv->q;

	snम_लिखो(vfd->name, माप(vfd->name), "%s capture", src_sd->name);

	video_set_drvdata(vfd, priv);
	priv->vdev.vfd = vfd;
	INIT_LIST_HEAD(&priv->vdev.list);

	/* Initialize the video device pad. */
	priv->vdev_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &priv->vdev_pad);
	अगर (ret) अणु
		video_device_release(vfd);
		वापस ERR_PTR(ret);
	पूर्ण

	/* Initialize the vb2 queue. */
	vq = &priv->q;
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->drv_priv = priv;
	vq->buf_काष्ठा_size = माप(काष्ठा imx_media_buffer);
	vq->ops = &capture_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->lock = &priv->mutex;
	vq->min_buffers_needed = 2;
	vq->dev = priv->dev;

	ret = vb2_queue_init(vq);
	अगर (ret) अणु
		dev_err(priv->dev, "vb2_queue_init failed\n");
		video_device_release(vfd);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (legacy_api) अणु
		/* Initialize the control handler. */
		v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);
		vfd->ctrl_handler = &priv->ctrl_hdlr;
	पूर्ण

	वापस &priv->vdev;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_init);

व्योम imx_media_capture_device_हटाओ(काष्ठा imx_media_video_dev *vdev)
अणु
	काष्ठा capture_priv *priv = to_capture_priv(vdev);

	v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_capture_device_हटाओ);

MODULE_DESCRIPTION("i.MX5/6 v4l2 video capture interface driver");
MODULE_AUTHOR("Steve Longerbeam <steve_longerbeam@mentor.com>");
MODULE_LICENSE("GPL");
