<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Renesas R-Car VIN
 *
 * Copyright (C) 2016 Renesas Electronics Corp.
 * Copyright (C) 2011-2013 Renesas Solutions Corp.
 * Copyright (C) 2013 Cogent Embedded, Inc., <source@cogentembedded.com>
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on the soc-camera rcar_vin driver
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-rect.h>

#समावेश "rcar-vin.h"

#घोषणा RVIN_DEFAULT_FORMAT	V4L2_PIX_FMT_YUYV
#घोषणा RVIN_DEFAULT_WIDTH	800
#घोषणा RVIN_DEFAULT_HEIGHT	600
#घोषणा RVIN_DEFAULT_FIELD	V4L2_FIELD_NONE
#घोषणा RVIN_DEFAULT_COLORSPACE	V4L2_COLORSPACE_SRGB

/* -----------------------------------------------------------------------------
 * Format Conversions
 */

अटल स्थिर काष्ठा rvin_video_क्रमmat rvin_क्रमmats[] = अणु
	अणु
		.fourcc			= V4L2_PIX_FMT_NV12,
		.bpp			= 1,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_NV16,
		.bpp			= 1,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.bpp			= 2,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_UYVY,
		.bpp			= 2,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_RGB565,
		.bpp			= 2,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_XRGB555,
		.bpp			= 2,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_XBGR32,
		.bpp			= 4,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_ARGB555,
		.bpp			= 2,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_ABGR32,
		.bpp			= 4,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_SBGGR8,
		.bpp			= 1,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_SGBRG8,
		.bpp			= 1,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_SGRBG8,
		.bpp			= 1,
	पूर्ण,
	अणु
		.fourcc			= V4L2_PIX_FMT_SRGGB8,
		.bpp			= 1,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा rvin_video_क्रमmat *rvin_क्रमmat_from_pixel(काष्ठा rvin_dev *vin,
						       u32 pixelक्रमmat)
अणु
	पूर्णांक i;

	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_XBGR32:
		अगर (vin->info->model == RCAR_M1)
			वापस शून्य;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		/*
		 * If NV12 is supported it's only supported on channels 0, 1, 4,
		 * 5, 8, 9, 12 and 13.
		 */
		अगर (!vin->info->nv12 || !(BIT(vin->id) & 0x3333))
			वापस शून्य;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rvin_क्रमmats); i++)
		अगर (rvin_क्रमmats[i].fourcc == pixelक्रमmat)
			वापस rvin_क्रमmats + i;

	वापस शून्य;
पूर्ण

अटल u32 rvin_क्रमmat_bytesperline(काष्ठा rvin_dev *vin,
				    काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	स्थिर काष्ठा rvin_video_क्रमmat *fmt;
	u32 align;

	fmt = rvin_क्रमmat_from_pixel(vin, pix->pixelक्रमmat);

	अगर (WARN_ON(!fmt))
		वापस -EINVAL;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
		align = 0x20;
		अवरोध;
	शेष:
		align = 0x10;
		अवरोध;
	पूर्ण

	अगर (V4L2_FIELD_IS_SEQUENTIAL(pix->field))
		align = 0x80;

	वापस ALIGN(pix->width, align) * fmt->bpp;
पूर्ण

अटल u32 rvin_क्रमmat_sizeimage(काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		वापस pix->bytesperline * pix->height * 3 / 2;
	हाल V4L2_PIX_FMT_NV16:
		वापस pix->bytesperline * pix->height * 2;
	शेष:
		वापस pix->bytesperline * pix->height;
	पूर्ण
पूर्ण

अटल व्योम rvin_क्रमmat_align(काष्ठा rvin_dev *vin, काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	u32 walign;

	अगर (!rvin_क्रमmat_from_pixel(vin, pix->pixelक्रमmat))
		pix->pixelक्रमmat = RVIN_DEFAULT_FORMAT;

	चयन (pix->field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_NONE:
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_ALTERNATE:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		अवरोध;
	शेष:
		pix->field = RVIN_DEFAULT_FIELD;
		अवरोध;
	पूर्ण

	/* HW limit width to a multiple of 32 (2^5) क्रम NV12/16 अन्यथा 2 (2^1) */
	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
		walign = 5;
		अवरोध;
	शेष:
		walign = 1;
		अवरोध;
	पूर्ण

	/* Limit to VIN capabilities */
	v4l_bound_align_image(&pix->width, 2, vin->info->max_width, walign,
			      &pix->height, 4, vin->info->max_height, 2, 0);

	pix->bytesperline = rvin_क्रमmat_bytesperline(vin, pix);
	pix->sizeimage = rvin_क्रमmat_sizeimage(pix);

	vin_dbg(vin, "Format %ux%u bpl: %u size: %u\n",
		pix->width, pix->height, pix->bytesperline, pix->sizeimage);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2
 */

अटल पूर्णांक rvin_reset_क्रमmat(काष्ठा rvin_dev *vin)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = vin->parallel.source_pad,
	पूर्ण;
	पूर्णांक ret;

	ret = v4l2_subdev_call(vin_to_source(vin), pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret;

	v4l2_fill_pix_क्रमmat(&vin->क्रमmat, &fmt.क्रमmat);

	vin->src_rect.top = 0;
	vin->src_rect.left = 0;
	vin->src_rect.width = vin->क्रमmat.width;
	vin->src_rect.height = vin->क्रमmat.height;

	/*  Make use of the hardware पूर्णांकerlacer by शेष. */
	अगर (vin->क्रमmat.field == V4L2_FIELD_ALTERNATE) अणु
		vin->क्रमmat.field = V4L2_FIELD_INTERLACED;
		vin->क्रमmat.height *= 2;
	पूर्ण

	rvin_क्रमmat_align(vin, &vin->क्रमmat);

	vin->crop = vin->src_rect;

	vin->compose.top = 0;
	vin->compose.left = 0;
	vin->compose.width = vin->क्रमmat.width;
	vin->compose.height = vin->क्रमmat.height;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_try_क्रमmat(काष्ठा rvin_dev *vin, u32 which,
			   काष्ठा v4l2_pix_क्रमmat *pix,
			   काष्ठा v4l2_rect *src_rect)
अणु
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	काष्ठा v4l2_subdev_pad_config *pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = which,
		.pad = vin->parallel.source_pad,
	पूर्ण;
	क्रमागत v4l2_field field;
	u32 width, height;
	पूर्णांक ret;

	pad_cfg = v4l2_subdev_alloc_pad_config(sd);
	अगर (pad_cfg == शून्य)
		वापस -ENOMEM;

	अगर (!rvin_क्रमmat_from_pixel(vin, pix->pixelक्रमmat))
		pix->pixelक्रमmat = RVIN_DEFAULT_FORMAT;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pix, vin->mbus_code);

	/* Allow the video device to override field and to scale */
	field = pix->field;
	width = pix->width;
	height = pix->height;

	ret = v4l2_subdev_call(sd, pad, set_fmt, pad_cfg, &क्रमmat);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		जाओ करोne;
	ret = 0;

	v4l2_fill_pix_क्रमmat(pix, &क्रमmat.क्रमmat);

	अगर (src_rect) अणु
		src_rect->top = 0;
		src_rect->left = 0;
		src_rect->width = pix->width;
		src_rect->height = pix->height;
	पूर्ण

	अगर (field != V4L2_FIELD_ANY)
		pix->field = field;

	pix->width = width;
	pix->height = height;

	rvin_क्रमmat_align(vin, pix);
करोne:
	v4l2_subdev_मुक्त_pad_config(pad_cfg);

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_querycap(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, "R_Car_VIN", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(vin->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक rvin_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	वापस rvin_try_क्रमmat(vin, V4L2_SUBDEV_FORMAT_TRY, &f->fmt.pix, शून्य);
पूर्ण

अटल पूर्णांक rvin_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_rect fmt_rect, src_rect;
	पूर्णांक ret;

	अगर (vb2_is_busy(&vin->queue))
		वापस -EBUSY;

	ret = rvin_try_क्रमmat(vin, V4L2_SUBDEV_FORMAT_ACTIVE, &f->fmt.pix,
			      &src_rect);
	अगर (ret)
		वापस ret;

	vin->क्रमmat = f->fmt.pix;

	fmt_rect.top = 0;
	fmt_rect.left = 0;
	fmt_rect.width = vin->क्रमmat.width;
	fmt_rect.height = vin->क्रमmat.height;

	v4l2_rect_map_inside(&vin->crop, &src_rect);
	v4l2_rect_map_inside(&vin->compose, &fmt_rect);
	vin->src_rect = src_rect;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	f->fmt.pix = vin->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	अचिन्हित पूर्णांक i;
	पूर्णांक matched;

	/*
	 * If mbus_code is set only क्रमागतerate supported pixel क्रमmats क्रम that
	 * bus code. Converting from YCbCr to RGB and RGB to YCbCr is possible
	 * with VIN, so all supported YCbCr and RGB media bus codes can produce
	 * all of the related pixel क्रमmats. If mbus_code is not set क्रमागतerate
	 * all possible pixelक्रमmats.
	 *
	 * TODO: Once raw MEDIA_BUS_FMT_SRGGB12_1X12 क्रमmat is added to the
	 * driver this needs to be extended so raw media bus code only result in
	 * raw pixel क्रमmat.
	 */
	चयन (f->mbus_code) अणु
	हाल 0:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	हाल MEDIA_BUS_FMT_UYVY10_2X10:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		अगर (f->index)
			वापस -EINVAL;
		f->pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
		वापस 0;
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		अगर (f->index)
			वापस -EINVAL;
		f->pixelक्रमmat = V4L2_PIX_FMT_SGBRG8;
		वापस 0;
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		अगर (f->index)
			वापस -EINVAL;
		f->pixelक्रमmat = V4L2_PIX_FMT_SGRBG8;
		वापस 0;
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		अगर (f->index)
			वापस -EINVAL;
		f->pixelक्रमmat = V4L2_PIX_FMT_SRGGB8;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	matched = -1;
	क्रम (i = 0; i < ARRAY_SIZE(rvin_क्रमmats); i++) अणु
		अगर (rvin_क्रमmat_from_pixel(vin, rvin_क्रमmats[i].fourcc))
			matched++;

		अगर (matched == f->index) अणु
			f->pixelक्रमmat = rvin_क्रमmats[i].fourcc;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rvin_g_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = s->r.top = 0;
		s->r.width = vin->src_rect.width;
		s->r.height = vin->src_rect.height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		s->r = vin->crop;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		s->r.left = s->r.top = 0;
		s->r.width = vin->क्रमmat.width;
		s->r.height = vin->क्रमmat.height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		s->r = vin->compose;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_s_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	स्थिर काष्ठा rvin_video_क्रमmat *fmt;
	काष्ठा v4l2_rect r = s->r;
	काष्ठा v4l2_rect max_rect;
	काष्ठा v4l2_rect min_rect = अणु
		.width = 6,
		.height = 2,
	पूर्ण;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	v4l2_rect_set_min_size(&r, &min_rect);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		/* Can't crop outside of source input */
		max_rect.top = max_rect.left = 0;
		max_rect.width = vin->src_rect.width;
		max_rect.height = vin->src_rect.height;
		v4l2_rect_map_inside(&r, &max_rect);

		v4l_bound_align_image(&r.width, 6, vin->src_rect.width, 0,
				      &r.height, 2, vin->src_rect.height, 0, 0);

		r.top  = clamp_t(s32, r.top, 0,
				 vin->src_rect.height - r.height);
		r.left = clamp_t(s32, r.left, 0, vin->src_rect.width - r.width);

		vin->crop = s->r = r;

		vin_dbg(vin, "Cropped %dx%d@%d:%d of %dx%d\n",
			r.width, r.height, r.left, r.top,
			vin->src_rect.width, vin->src_rect.height);
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		/* Make sure compose rect fits inside output क्रमmat */
		max_rect.top = max_rect.left = 0;
		max_rect.width = vin->क्रमmat.width;
		max_rect.height = vin->क्रमmat.height;
		v4l2_rect_map_inside(&r, &max_rect);

		/*
		 * Composing is करोne by adding a offset to the buffer address,
		 * the HW wants this address to be aligned to HW_BUFFER_MASK.
		 * Make sure the top and left values meets this requirement.
		 */
		जबतक ((r.top * vin->क्रमmat.bytesperline) & HW_BUFFER_MASK)
			r.top--;

		fmt = rvin_क्रमmat_from_pixel(vin, vin->क्रमmat.pixelक्रमmat);
		जबतक ((r.left * fmt->bpp) & HW_BUFFER_MASK)
			r.left--;

		vin->compose = s->r = r;

		vin_dbg(vin, "Compose %dx%d@%d:%d in %dx%d\n",
			r.width, r.height, r.left, r.top,
			vin->क्रमmat.width, vin->क्रमmat.height);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* HW supports modअगरying configuration जबतक running */
	rvin_crop_scale_comp(vin);

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_g_pixelaspect(काष्ठा file *file, व्योम *priv,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	वापस v4l2_subdev_call(sd, video, g_pixelaspect, f);
पूर्ण

अटल पूर्णांक rvin_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *i)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	अगर (i->index != 0)
		वापस -EINVAL;

	ret = v4l2_subdev_call(sd, video, g_input_status, &i->status);
	अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		वापस ret;

	i->type = V4L2_INPUT_TYPE_CAMERA;

	अगर (v4l2_subdev_has_op(sd, pad, dv_timings_cap)) अणु
		i->capabilities = V4L2_IN_CAP_DV_TIMINGS;
		i->std = 0;
	पूर्ण अन्यथा अणु
		i->capabilities = V4L2_IN_CAP_STD;
		i->std = vin->vdev.tvnorms;
	पूर्ण

	strscpy(i->name, "Camera", माप(i->name));

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक rvin_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक rvin_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *a)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);

	वापस v4l2_subdev_call(sd, video, querystd, a);
पूर्ण

अटल पूर्णांक rvin_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id a)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	पूर्णांक ret;

	ret = v4l2_subdev_call(vin_to_source(vin), video, s_std, a);
	अगर (ret < 0)
		वापस ret;

	vin->std = a;

	/* Changing the standard will change the width/height */
	वापस rvin_reset_क्रमmat(vin);
पूर्ण

अटल पूर्णांक rvin_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *a)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	अगर (v4l2_subdev_has_op(vin_to_source(vin), pad, dv_timings_cap))
		वापस -ENOIOCTLCMD;

	*a = vin->std;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_event_subscribe(fh, sub, 4, शून्य);
	पूर्ण
	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण

अटल पूर्णांक rvin_क्रमागत_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	अगर (timings->pad)
		वापस -EINVAL;

	timings->pad = vin->parallel.sink_pad;

	ret = v4l2_subdev_call(sd, pad, क्रमागत_dv_timings, timings);

	timings->pad = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_s_dv_timings(काष्ठा file *file, व्योम *priv_fh,
			     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	ret = v4l2_subdev_call(sd, video, s_dv_timings, timings);
	अगर (ret)
		वापस ret;

	/* Changing the timings will change the width/height */
	वापस rvin_reset_क्रमmat(vin);
पूर्ण

अटल पूर्णांक rvin_g_dv_timings(काष्ठा file *file, व्योम *priv_fh,
			     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);

	वापस v4l2_subdev_call(sd, video, g_dv_timings, timings);
पूर्ण

अटल पूर्णांक rvin_query_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);

	वापस v4l2_subdev_call(sd, video, query_dv_timings, timings);
पूर्ण

अटल पूर्णांक rvin_dv_timings_cap(काष्ठा file *file, व्योम *priv_fh,
			       काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	अगर (cap->pad)
		वापस -EINVAL;

	cap->pad = vin->parallel.sink_pad;

	ret = v4l2_subdev_call(sd, pad, dv_timings_cap, cap);

	cap->pad = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_g_edid(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	अगर (edid->pad)
		वापस -EINVAL;

	edid->pad = vin->parallel.sink_pad;

	ret = v4l2_subdev_call(sd, pad, get_edid, edid);

	edid->pad = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_s_edid(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक ret;

	अगर (edid->pad)
		वापस -EINVAL;

	edid->pad = vin->parallel.sink_pad;

	ret = v4l2_subdev_call(sd, pad, set_edid, edid);

	edid->pad = 0;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rvin_ioctl_ops = अणु
	.vidioc_querycap		= rvin_querycap,
	.vidioc_try_fmt_vid_cap		= rvin_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= rvin_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= rvin_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap	= rvin_क्रमागत_fmt_vid_cap,

	.vidioc_g_selection		= rvin_g_selection,
	.vidioc_s_selection		= rvin_s_selection,

	.vidioc_g_pixelaspect		= rvin_g_pixelaspect,

	.vidioc_क्रमागत_input		= rvin_क्रमागत_input,
	.vidioc_g_input			= rvin_g_input,
	.vidioc_s_input			= rvin_s_input,

	.vidioc_dv_timings_cap		= rvin_dv_timings_cap,
	.vidioc_क्रमागत_dv_timings		= rvin_क्रमागत_dv_timings,
	.vidioc_g_dv_timings		= rvin_g_dv_timings,
	.vidioc_s_dv_timings		= rvin_s_dv_timings,
	.vidioc_query_dv_timings	= rvin_query_dv_timings,

	.vidioc_g_edid			= rvin_g_edid,
	.vidioc_s_edid			= rvin_s_edid,

	.vidioc_querystd		= rvin_querystd,
	.vidioc_g_std			= rvin_g_std,
	.vidioc_s_std			= rvin_s_std,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= rvin_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 Media Controller
 */

अटल व्योम rvin_mc_try_क्रमmat(काष्ठा rvin_dev *vin,
			       काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	/*
	 * The V4L2 specअगरication clearly करोcuments the colorspace fields
	 * as being set by drivers क्रम capture devices. Using the values
	 * supplied by userspace thus wouldn't comply with the API. Until
	 * the API is updated क्रमce fixed values.
	 */
	pix->colorspace = RVIN_DEFAULT_COLORSPACE;
	pix->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(pix->colorspace);
	pix->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(pix->colorspace);
	pix->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true, pix->colorspace,
							  pix->ycbcr_enc);

	rvin_क्रमmat_align(vin, pix);
पूर्ण

अटल पूर्णांक rvin_mc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	rvin_mc_try_क्रमmat(vin, &f->fmt.pix);

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_mc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);

	अगर (vb2_is_busy(&vin->queue))
		वापस -EBUSY;

	rvin_mc_try_क्रमmat(vin, &f->fmt.pix);

	vin->क्रमmat = f->fmt.pix;

	vin->crop.top = 0;
	vin->crop.left = 0;
	vin->crop.width = vin->क्रमmat.width;
	vin->crop.height = vin->क्रमmat.height;
	vin->compose = vin->crop;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rvin_mc_ioctl_ops = अणु
	.vidioc_querycap		= rvin_querycap,
	.vidioc_try_fmt_vid_cap		= rvin_mc_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= rvin_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= rvin_mc_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap	= rvin_क्रमागत_fmt_vid_cap,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= rvin_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * File Operations
 */

अटल पूर्णांक rvin_घातer_parallel(काष्ठा rvin_dev *vin, bool on)
अणु
	काष्ठा v4l2_subdev *sd = vin_to_source(vin);
	पूर्णांक घातer = on ? 1 : 0;
	पूर्णांक ret;

	ret = v4l2_subdev_call(sd, core, s_घातer, घातer);
	अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_खोलो(काष्ठा file *file)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(vin->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(vin->dev);
		वापस ret;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&vin->lock);
	अगर (ret)
		जाओ err_pm;

	file->निजी_data = vin;

	ret = v4l2_fh_खोलो(file);
	अगर (ret)
		जाओ err_unlock;

	अगर (vin->info->use_mc)
		ret = v4l2_pipeline_pm_get(&vin->vdev.entity);
	अन्यथा अगर (v4l2_fh_is_singular_file(file))
		ret = rvin_घातer_parallel(vin, true);

	अगर (ret < 0)
		जाओ err_खोलो;

	ret = v4l2_ctrl_handler_setup(&vin->ctrl_handler);
	अगर (ret)
		जाओ err_घातer;

	mutex_unlock(&vin->lock);

	वापस 0;
err_घातer:
	अगर (vin->info->use_mc)
		v4l2_pipeline_pm_put(&vin->vdev.entity);
	अन्यथा अगर (v4l2_fh_is_singular_file(file))
		rvin_घातer_parallel(vin, false);
err_खोलो:
	v4l2_fh_release(file);
err_unlock:
	mutex_unlock(&vin->lock);
err_pm:
	pm_runसमय_put(vin->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_release(काष्ठा file *file)
अणु
	काष्ठा rvin_dev *vin = video_drvdata(file);
	bool fh_singular;
	पूर्णांक ret;

	mutex_lock(&vin->lock);

	/* Save the singular status beक्रमe we call the clean-up helper */
	fh_singular = v4l2_fh_is_singular_file(file);

	/* the release helper will cleanup any on-going streaming */
	ret = _vb2_fop_release(file, शून्य);

	अगर (vin->info->use_mc) अणु
		v4l2_pipeline_pm_put(&vin->vdev.entity);
	पूर्ण अन्यथा अणु
		अगर (fh_singular)
			rvin_घातer_parallel(vin, false);
	पूर्ण

	mutex_unlock(&vin->lock);

	pm_runसमय_put(vin->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations rvin_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= rvin_खोलो,
	.release	= rvin_release,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.पढ़ो		= vb2_fop_पढ़ो,
पूर्ण;

व्योम rvin_v4l2_unरेजिस्टर(काष्ठा rvin_dev *vin)
अणु
	अगर (!video_is_रेजिस्टरed(&vin->vdev))
		वापस;

	v4l2_info(&vin->v4l2_dev, "Removing %s\n",
		  video_device_node_name(&vin->vdev));

	/* Checks पूर्णांकernally अगर vdev have been init or not */
	video_unरेजिस्टर_device(&vin->vdev);
पूर्ण

अटल व्योम rvin_notअगरy_video_device(काष्ठा rvin_dev *vin,
				     अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	चयन (notअगरication) अणु
	हाल V4L2_DEVICE_NOTIFY_EVENT:
		v4l2_event_queue(&vin->vdev, arg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rvin_notअगरy(काष्ठा v4l2_subdev *sd,
			अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	काष्ठा v4l2_subdev *remote;
	काष्ठा rvin_group *group;
	काष्ठा media_pad *pad;
	काष्ठा rvin_dev *vin =
		container_of(sd->v4l2_dev, काष्ठा rvin_dev, v4l2_dev);
	अचिन्हित पूर्णांक i;

	/* If no media controller, no need to route the event. */
	अगर (!vin->info->use_mc) अणु
		rvin_notअगरy_video_device(vin, notअगरication, arg);
		वापस;
	पूर्ण

	group = vin->group;

	क्रम (i = 0; i < RCAR_VIN_NUM; i++) अणु
		vin = group->vin[i];
		अगर (!vin)
			जारी;

		pad = media_entity_remote_pad(&vin->pad);
		अगर (!pad)
			जारी;

		remote = media_entity_to_v4l2_subdev(pad->entity);
		अगर (remote != sd)
			जारी;

		rvin_notअगरy_video_device(vin, notअगरication, arg);
	पूर्ण
पूर्ण

पूर्णांक rvin_v4l2_रेजिस्टर(काष्ठा rvin_dev *vin)
अणु
	काष्ठा video_device *vdev = &vin->vdev;
	पूर्णांक ret;

	vin->v4l2_dev.notअगरy = rvin_notअगरy;

	/* video node */
	vdev->v4l2_dev = &vin->v4l2_dev;
	vdev->queue = &vin->queue;
	snम_लिखो(vdev->name, माप(vdev->name), "VIN%u output", vin->id);
	vdev->release = video_device_release_empty;
	vdev->lock = &vin->lock;
	vdev->fops = &rvin_fops;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
		V4L2_CAP_READWRITE;

	/* Set a शेष क्रमmat */
	vin->क्रमmat.pixelक्रमmat	= RVIN_DEFAULT_FORMAT;
	vin->क्रमmat.width = RVIN_DEFAULT_WIDTH;
	vin->क्रमmat.height = RVIN_DEFAULT_HEIGHT;
	vin->क्रमmat.field = RVIN_DEFAULT_FIELD;
	vin->क्रमmat.colorspace = RVIN_DEFAULT_COLORSPACE;

	अगर (vin->info->use_mc) अणु
		vdev->device_caps |= V4L2_CAP_IO_MC;
		vdev->ioctl_ops = &rvin_mc_ioctl_ops;
	पूर्ण अन्यथा अणु
		vdev->ioctl_ops = &rvin_ioctl_ops;
		rvin_reset_क्रमmat(vin);
	पूर्ण

	rvin_क्रमmat_align(vin, &vin->क्रमmat);

	ret = video_रेजिस्टर_device(&vin->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		vin_err(vin, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	video_set_drvdata(&vin->vdev, vin);

	v4l2_info(&vin->v4l2_dev, "Device registered as %s\n",
		  video_device_node_name(&vin->vdev));

	वापस ret;
पूर्ण
