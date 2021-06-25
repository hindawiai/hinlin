<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 NextThing Co
 * Copyright (C) 2016-2019 Bootlin
 *
 * Author: Maxime Ripard <maxime.ripard@bootlin.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "sun4i_csi.h"

#घोषणा CSI_DEFAULT_WIDTH	640
#घोषणा CSI_DEFAULT_HEIGHT	480

अटल स्थिर काष्ठा sun4i_csi_क्रमmat sun4i_csi_क्रमmats[] = अणु
	/* YUV422 inमाला_दो */
	अणु
		.mbus		= MEDIA_BUS_FMT_YUYV8_2X8,
		.fourcc		= V4L2_PIX_FMT_YUV420M,
		.input		= CSI_INPUT_YUV,
		.output		= CSI_OUTPUT_YUV_420_PLANAR,
		.num_planes	= 3,
		.bpp		= अणु 8, 8, 8 पूर्ण,
		.hsub		= 2,
		.vsub		= 2,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा sun4i_csi_क्रमmat *sun4i_csi_find_क्रमmat(स्थिर u32 *fourcc,
						     स्थिर u32 *mbus)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sun4i_csi_क्रमmats); i++) अणु
		अगर (fourcc && *fourcc != sun4i_csi_क्रमmats[i].fourcc)
			जारी;

		अगर (mbus && *mbus != sun4i_csi_क्रमmats[i].mbus)
			जारी;

		वापस &sun4i_csi_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sun4i_csi_querycap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_capability *cap)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, "sun4i-csi", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(csi->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index != 0)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(inp->name, "Camera", माप(inp->name));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_g_input(काष्ठा file *file, व्योम *fh,
			     अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_s_input(काष्ठा file *file, व्योम *fh,
			     अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम _sun4i_csi_try_fmt(काष्ठा sun4i_csi *csi,
			       काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	स्थिर काष्ठा sun4i_csi_क्रमmat *_fmt;
	अचिन्हित पूर्णांक height, width;
	अचिन्हित पूर्णांक i;

	_fmt = sun4i_csi_find_क्रमmat(&pix->pixelक्रमmat, शून्य);
	अगर (!_fmt)
		_fmt = &sun4i_csi_क्रमmats[0];

	pix->field = V4L2_FIELD_NONE;
	pix->colorspace = V4L2_COLORSPACE_SRGB;
	pix->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(pix->colorspace);
	pix->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(pix->colorspace);
	pix->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true, pix->colorspace,
							  pix->ycbcr_enc);

	pix->num_planes = _fmt->num_planes;
	pix->pixelक्रमmat = _fmt->fourcc;

	/* Align the width and height on the subsampling */
	width = ALIGN(pix->width, _fmt->hsub);
	height = ALIGN(pix->height, _fmt->vsub);

	/* Clamp the width and height to our capabilities */
	pix->width = clamp(width, _fmt->hsub, CSI_MAX_WIDTH);
	pix->height = clamp(height, _fmt->vsub, CSI_MAX_HEIGHT);

	क्रम (i = 0; i < _fmt->num_planes; i++) अणु
		अचिन्हित पूर्णांक hsub = i > 0 ? _fmt->hsub : 1;
		अचिन्हित पूर्णांक vsub = i > 0 ? _fmt->vsub : 1;
		अचिन्हित पूर्णांक bpl;

		bpl = pix->width / hsub * _fmt->bpp[i] / 8;
		pix->plane_fmt[i].bytesperline = bpl;
		pix->plane_fmt[i].sizeimage = bpl * pix->height / vsub;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_csi_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);

	_sun4i_csi_try_fmt(csi, &f->fmt.pix_mp);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);

	_sun4i_csi_try_fmt(csi, &f->fmt.pix_mp);
	csi->fmt = f->fmt.pix_mp;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);

	f->fmt.pix_mp = csi->fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(sun4i_csi_क्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = sun4i_csi_क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops sun4i_csi_ioctl_ops = अणु
	.vidioc_querycap		= sun4i_csi_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= sun4i_csi_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mplane	= sun4i_csi_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mplane	= sun4i_csi_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap_mplane	= sun4i_csi_try_fmt_vid_cap,

	.vidioc_क्रमागत_input		= sun4i_csi_क्रमागत_input,
	.vidioc_g_input			= sun4i_csi_g_input,
	.vidioc_s_input			= sun4i_csi_s_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

अटल पूर्णांक sun4i_csi_खोलो(काष्ठा file *file)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&csi->lock);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(csi->dev);
	अगर (ret < 0)
		जाओ err_pm_put;

	ret = v4l2_pipeline_pm_get(&csi->vdev.entity);
	अगर (ret)
		जाओ err_pm_put;

	ret = v4l2_fh_खोलो(file);
	अगर (ret)
		जाओ err_pipeline_pm_put;

	mutex_unlock(&csi->lock);

	वापस 0;

err_pipeline_pm_put:
	v4l2_pipeline_pm_put(&csi->vdev.entity);

err_pm_put:
	pm_runसमय_put(csi->dev);
	mutex_unlock(&csi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_csi_release(काष्ठा file *file)
अणु
	काष्ठा sun4i_csi *csi = video_drvdata(file);

	mutex_lock(&csi->lock);

	_vb2_fop_release(file, शून्य);

	v4l2_pipeline_pm_put(&csi->vdev.entity);
	pm_runसमय_put(csi->dev);

	mutex_unlock(&csi->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations sun4i_csi_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sun4i_csi_खोलो,
	.release	= sun4i_csi_release,
	.unlocked_ioctl	= video_ioctl2,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt sun4i_csi_pad_fmt_शेष = अणु
	.width = CSI_DEFAULT_WIDTH,
	.height = CSI_DEFAULT_HEIGHT,
	.code = MEDIA_BUS_FMT_YUYV8_2X8,
	.field = V4L2_FIELD_NONE,
	.colorspace = V4L2_COLORSPACE_RAW,
	.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT,
	.quantization = V4L2_QUANTIZATION_DEFAULT,
	.xfer_func = V4L2_XFER_FUNC_DEFAULT,
पूर्ण;

अटल पूर्णांक sun4i_csi_subdev_init_cfg(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt;

	fmt = v4l2_subdev_get_try_क्रमmat(subdev, cfg, CSI_SUBDEV_SINK);
	*fmt = sun4i_csi_pad_fmt_शेष;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_subdev_get_fmt(काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा sun4i_csi *csi = container_of(subdev, काष्ठा sun4i_csi, subdev);
	काष्ठा v4l2_mbus_framefmt *subdev_fmt;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		subdev_fmt = v4l2_subdev_get_try_क्रमmat(subdev, cfg, fmt->pad);
	अन्यथा
		subdev_fmt = &csi->subdev_fmt;

	fmt->क्रमmat = *subdev_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_subdev_set_fmt(काष्ठा v4l2_subdev *subdev,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा sun4i_csi *csi = container_of(subdev, काष्ठा sun4i_csi, subdev);
	काष्ठा v4l2_mbus_framefmt *subdev_fmt;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		subdev_fmt = v4l2_subdev_get_try_क्रमmat(subdev, cfg, fmt->pad);
	अन्यथा
		subdev_fmt = &csi->subdev_fmt;

	/* We can only set the क्रमmat on the sink pad */
	अगर (fmt->pad == CSI_SUBDEV_SINK) अणु
		/* It's the sink, only allow changing the frame size */
		subdev_fmt->width = fmt->क्रमmat.width;
		subdev_fmt->height = fmt->क्रमmat.height;
		subdev_fmt->code = fmt->क्रमmat.code;
	पूर्ण

	fmt->क्रमmat = *subdev_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक
sun4i_csi_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *mbus)
अणु
	अगर (mbus->index >= ARRAY_SIZE(sun4i_csi_क्रमmats))
		वापस -EINVAL;

	mbus->code = sun4i_csi_क्रमmats[mbus->index].mbus;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops sun4i_csi_subdev_pad_ops = अणु
	.link_validate	= v4l2_subdev_link_validate_शेष,
	.init_cfg	= sun4i_csi_subdev_init_cfg,
	.get_fmt	= sun4i_csi_subdev_get_fmt,
	.set_fmt	= sun4i_csi_subdev_set_fmt,
	.क्रमागत_mbus_code	= sun4i_csi_subdev_क्रमागत_mbus_code,
पूर्ण;

स्थिर काष्ठा v4l2_subdev_ops sun4i_csi_subdev_ops = अणु
	.pad = &sun4i_csi_subdev_pad_ops,
पूर्ण;

पूर्णांक sun4i_csi_v4l2_रेजिस्टर(काष्ठा sun4i_csi *csi)
अणु
	काष्ठा video_device *vdev = &csi->vdev;
	पूर्णांक ret;

	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING;
	vdev->v4l2_dev = &csi->v4l;
	vdev->queue = &csi->queue;
	strscpy(vdev->name, KBUILD_MODNAME, माप(vdev->name));
	vdev->release = video_device_release_empty;
	vdev->lock = &csi->lock;

	/* Set a शेष क्रमmat */
	csi->fmt.pixelक्रमmat = sun4i_csi_क्रमmats[0].fourcc;
	csi->fmt.width = CSI_DEFAULT_WIDTH;
	csi->fmt.height = CSI_DEFAULT_HEIGHT;
	_sun4i_csi_try_fmt(csi, &csi->fmt);
	csi->subdev_fmt = sun4i_csi_pad_fmt_शेष;

	vdev->fops = &sun4i_csi_fops;
	vdev->ioctl_ops = &sun4i_csi_ioctl_ops;
	video_set_drvdata(vdev, csi);

	ret = video_रेजिस्टर_device(&csi->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		वापस ret;

	dev_info(csi->dev, "Device registered as %s\n",
		 video_device_node_name(vdev));

	वापस 0;
पूर्ण
