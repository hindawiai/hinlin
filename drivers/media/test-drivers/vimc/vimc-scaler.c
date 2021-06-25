<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-scaler.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/v4l2-rect.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vimc-common.h"

अटल अचिन्हित पूर्णांक sca_mult = 3;
module_param(sca_mult, uपूर्णांक, 0000);
MODULE_PARM_DESC(sca_mult, " the image size multiplier");

#घोषणा MAX_ZOOM	8

#घोषणा VIMC_SCA_FMT_WIDTH_DEFAULT  640
#घोषणा VIMC_SCA_FMT_HEIGHT_DEFAULT 480

काष्ठा vimc_sca_device अणु
	काष्ठा vimc_ent_device ved;
	काष्ठा v4l2_subdev sd;
	/* NOTE: the source fmt is the same as the sink
	 * with the width and hight multiplied by mult
	 */
	काष्ठा v4l2_mbus_framefmt sink_fmt;
	काष्ठा v4l2_rect crop_rect;
	/* Values calculated when the stream starts */
	u8 *src_frame;
	अचिन्हित पूर्णांक src_line_size;
	अचिन्हित पूर्णांक bpp;
	काष्ठा media_pad pads[2];
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt sink_fmt_शेष = अणु
	.width = VIMC_SCA_FMT_WIDTH_DEFAULT,
	.height = VIMC_SCA_FMT_HEIGHT_DEFAULT,
	.code = MEDIA_BUS_FMT_RGB888_1X24,
	.field = V4L2_FIELD_NONE,
	.colorspace = V4L2_COLORSPACE_SRGB,
पूर्ण;

अटल स्थिर काष्ठा v4l2_rect crop_rect_शेष = अणु
	.width = VIMC_SCA_FMT_WIDTH_DEFAULT,
	.height = VIMC_SCA_FMT_HEIGHT_DEFAULT,
	.top = 0,
	.left = 0,
पूर्ण;

अटल स्थिर काष्ठा v4l2_rect crop_rect_min = अणु
	.width = VIMC_FRAME_MIN_WIDTH,
	.height = VIMC_FRAME_MIN_HEIGHT,
	.top = 0,
	.left = 0,
पूर्ण;

अटल काष्ठा v4l2_rect
vimc_sca_get_crop_bound_sink(स्थिर काष्ठा v4l2_mbus_framefmt *sink_fmt)
अणु
	/* Get the crop bounds to clamp the crop rectangle correctly */
	काष्ठा v4l2_rect r = अणु
		.left = 0,
		.top = 0,
		.width = sink_fmt->width,
		.height = sink_fmt->height,
	पूर्ण;
	वापस r;
पूर्ण

अटल व्योम vimc_sca_adjust_sink_crop(काष्ठा v4l2_rect *r,
				      स्थिर काष्ठा v4l2_mbus_framefmt *sink_fmt)
अणु
	स्थिर काष्ठा v4l2_rect sink_rect =
		vimc_sca_get_crop_bound_sink(sink_fmt);

	/* Disallow rectangles smaller than the minimal one. */
	v4l2_rect_set_min_size(r, &crop_rect_min);
	v4l2_rect_map_inside(r, &sink_rect);
पूर्ण

अटल पूर्णांक vimc_sca_init_cfg(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_mbus_framefmt *mf;
	काष्ठा v4l2_rect *r;
	अचिन्हित पूर्णांक i;

	mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	*mf = sink_fmt_शेष;

	r = v4l2_subdev_get_try_crop(sd, cfg, 0);
	*r = crop_rect_शेष;

	क्रम (i = 1; i < sd->entity.num_pads; i++) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);
		*mf = sink_fmt_शेष;
		mf->width = mf->width * sca_mult;
		mf->height = mf->height * sca_mult;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sca_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	u32 mbus_code = vimc_mbus_code_by_index(code->index);
	स्थिर काष्ठा vimc_pix_map *vpix;

	अगर (!mbus_code)
		वापस -EINVAL;

	vpix = vimc_pix_map_by_code(mbus_code);

	/* We करोn't support bayer क्रमmat */
	अगर (!vpix || vpix->bayer)
		वापस -EINVAL;

	code->code = mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sca_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	अगर (fse->index)
		वापस -EINVAL;

	/* Only accept code in the pix map table in non bayer क्रमmat */
	vpix = vimc_pix_map_by_code(fse->code);
	अगर (!vpix || vpix->bayer)
		वापस -EINVAL;

	fse->min_width = VIMC_FRAME_MIN_WIDTH;
	fse->min_height = VIMC_FRAME_MIN_HEIGHT;

	अगर (VIMC_IS_SINK(fse->pad)) अणु
		fse->max_width = VIMC_FRAME_MAX_WIDTH;
		fse->max_height = VIMC_FRAME_MAX_HEIGHT;
	पूर्ण अन्यथा अणु
		fse->max_width = VIMC_FRAME_MAX_WIDTH * MAX_ZOOM;
		fse->max_height = VIMC_FRAME_MAX_HEIGHT * MAX_ZOOM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sca_get_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा vimc_sca_device *vsca = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_rect *crop_rect;

	/* Get the current sink क्रमmat */
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		क्रमmat->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		crop_rect = v4l2_subdev_get_try_crop(sd, cfg, 0);
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat = vsca->sink_fmt;
		crop_rect = &vsca->crop_rect;
	पूर्ण

	/* Scale the frame size क्रम the source pad */
	अगर (VIMC_IS_SRC(क्रमmat->pad)) अणु
		क्रमmat->क्रमmat.width = crop_rect->width * sca_mult;
		क्रमmat->क्रमmat.height = crop_rect->height * sca_mult;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vimc_sca_adjust_sink_fmt(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	/* Only accept code in the pix map table in non bayer क्रमmat */
	vpix = vimc_pix_map_by_code(fmt->code);
	अगर (!vpix || vpix->bayer)
		fmt->code = sink_fmt_शेष.code;

	fmt->width = clamp_t(u32, fmt->width, VIMC_FRAME_MIN_WIDTH,
			     VIMC_FRAME_MAX_WIDTH) & ~1;
	fmt->height = clamp_t(u32, fmt->height, VIMC_FRAME_MIN_HEIGHT,
			      VIMC_FRAME_MAX_HEIGHT) & ~1;

	अगर (fmt->field == V4L2_FIELD_ANY)
		fmt->field = sink_fmt_शेष.field;

	vimc_colorimetry_clamp(fmt);
पूर्ण

अटल पूर्णांक vimc_sca_set_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vimc_sca_device *vsca = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *crop_rect;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		/* Do not change the क्रमmat जबतक stream is on */
		अगर (vsca->src_frame)
			वापस -EBUSY;

		sink_fmt = &vsca->sink_fmt;
		crop_rect = &vsca->crop_rect;
	पूर्ण अन्यथा अणु
		sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		crop_rect = v4l2_subdev_get_try_crop(sd, cfg, 0);
	पूर्ण

	/*
	 * Do not change the क्रमmat of the source pad,
	 * it is propagated from the sink
	 */
	अगर (VIMC_IS_SRC(fmt->pad)) अणु
		fmt->क्रमmat = *sink_fmt;
		fmt->क्रमmat.width = crop_rect->width * sca_mult;
		fmt->क्रमmat.height = crop_rect->height * sca_mult;
	पूर्ण अन्यथा अणु
		/* Set the new क्रमmat in the sink pad */
		vimc_sca_adjust_sink_fmt(&fmt->क्रमmat);

		dev_dbg(vsca->ved.dev, "%s: sink format update: "
			"old:%dx%d (0x%x, %d, %d, %d, %d) "
			"new:%dx%d (0x%x, %d, %d, %d, %d)\n", vsca->sd.name,
			/* old */
			sink_fmt->width, sink_fmt->height, sink_fmt->code,
			sink_fmt->colorspace, sink_fmt->quantization,
			sink_fmt->xfer_func, sink_fmt->ycbcr_enc,
			/* new */
			fmt->क्रमmat.width, fmt->क्रमmat.height, fmt->क्रमmat.code,
			fmt->क्रमmat.colorspace,	fmt->क्रमmat.quantization,
			fmt->क्रमmat.xfer_func, fmt->क्रमmat.ycbcr_enc);

		*sink_fmt = fmt->क्रमmat;

		/* Do the crop, but respect the current bounds */
		vimc_sca_adjust_sink_crop(crop_rect, sink_fmt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sca_get_selection(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vimc_sca_device *vsca = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *crop_rect;

	अगर (VIMC_IS_SRC(sel->pad))
		वापस -EINVAL;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		sink_fmt = &vsca->sink_fmt;
		crop_rect = &vsca->crop_rect;
	पूर्ण अन्यथा अणु
		sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		crop_rect = v4l2_subdev_get_try_crop(sd, cfg, 0);
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *crop_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r = vimc_sca_get_crop_bound_sink(sink_fmt);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sca_set_selection(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vimc_sca_device *vsca = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *crop_rect;

	अगर (VIMC_IS_SRC(sel->pad))
		वापस -EINVAL;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		/* Do not change the क्रमmat जबतक stream is on */
		अगर (vsca->src_frame)
			वापस -EBUSY;

		crop_rect = &vsca->crop_rect;
		sink_fmt = &vsca->sink_fmt;
	पूर्ण अन्यथा अणु
		crop_rect = v4l2_subdev_get_try_crop(sd, cfg, 0);
		sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		/* Do the crop, but respect the current bounds */
		vimc_sca_adjust_sink_crop(&sel->r, sink_fmt);
		*crop_rect = sel->r;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops vimc_sca_pad_ops = अणु
	.init_cfg		= vimc_sca_init_cfg,
	.क्रमागत_mbus_code		= vimc_sca_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= vimc_sca_क्रमागत_frame_size,
	.get_fmt		= vimc_sca_get_fmt,
	.set_fmt		= vimc_sca_set_fmt,
	.get_selection		= vimc_sca_get_selection,
	.set_selection		= vimc_sca_set_selection,
पूर्ण;

अटल पूर्णांक vimc_sca_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा vimc_sca_device *vsca = v4l2_get_subdevdata(sd);

	अगर (enable) अणु
		स्थिर काष्ठा vimc_pix_map *vpix;
		अचिन्हित पूर्णांक frame_size;

		अगर (vsca->src_frame)
			वापस 0;

		/* Save the bytes per pixel of the sink */
		vpix = vimc_pix_map_by_code(vsca->sink_fmt.code);
		vsca->bpp = vpix->bpp;

		/* Calculate the width in bytes of the src frame */
		vsca->src_line_size = vsca->crop_rect.width *
				      sca_mult * vsca->bpp;

		/* Calculate the frame size of the source pad */
		frame_size = vsca->src_line_size * vsca->crop_rect.height *
			     sca_mult;

		/* Allocate the frame buffer. Use vदो_स्मृति to be able to
		 * allocate a large amount of memory
		 */
		vsca->src_frame = vदो_स्मृति(frame_size);
		अगर (!vsca->src_frame)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		अगर (!vsca->src_frame)
			वापस 0;

		vमुक्त(vsca->src_frame);
		vsca->src_frame = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops vimc_sca_video_ops = अणु
	.s_stream = vimc_sca_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vimc_sca_ops = अणु
	.pad = &vimc_sca_pad_ops,
	.video = &vimc_sca_video_ops,
पूर्ण;

अटल व्योम vimc_sca_fill_pix(u8 *स्थिर ptr,
			      स्थिर u8 *स्थिर pixel,
			      स्थिर अचिन्हित पूर्णांक bpp)
अणु
	अचिन्हित पूर्णांक i;

	/* copy the pixel to the poपूर्णांकer */
	क्रम (i = 0; i < bpp; i++)
		ptr[i] = pixel[i];
पूर्ण

अटल व्योम vimc_sca_scale_pix(स्थिर काष्ठा vimc_sca_device *स्थिर vsca,
			       अचिन्हित पूर्णांक lin, अचिन्हित पूर्णांक col,
			       स्थिर u8 *स्थिर sink_frame)
अणु
	स्थिर काष्ठा v4l2_rect crop_rect = vsca->crop_rect;
	अचिन्हित पूर्णांक i, j, index;
	स्थिर u8 *pixel;

	/* Poपूर्णांक to the pixel value in position (lin, col) in the sink frame */
	index = VIMC_FRAME_INDEX(lin, col,
				 vsca->sink_fmt.width,
				 vsca->bpp);
	pixel = &sink_frame[index];

	dev_dbg(vsca->ved.dev,
		"sca: %s: --- scale_pix sink pos %dx%d, index %d ---\n",
		vsca->sd.name, lin, col, index);

	/* poपूर्णांक to the place we are going to put the first pixel
	 * in the scaled src frame
	 */
	lin -= crop_rect.top;
	col -= crop_rect.left;
	index = VIMC_FRAME_INDEX(lin * sca_mult, col * sca_mult,
				 crop_rect.width * sca_mult, vsca->bpp);

	dev_dbg(vsca->ved.dev, "sca: %s: scale_pix src pos %dx%d, index %d\n",
		vsca->sd.name, lin * sca_mult, col * sca_mult, index);

	/* Repeat this pixel mult बार */
	क्रम (i = 0; i < sca_mult; i++) अणु
		/* Iterate through each beginning of a
		 * pixel repetition in a line
		 */
		क्रम (j = 0; j < sca_mult * vsca->bpp; j += vsca->bpp) अणु
			dev_dbg(vsca->ved.dev,
				"sca: %s: sca: scale_pix src pos %d\n",
				vsca->sd.name, index + j);

			/* copy the pixel to the position index + j */
			vimc_sca_fill_pix(&vsca->src_frame[index + j],
					  pixel, vsca->bpp);
		पूर्ण

		/* move the index to the next line */
		index += vsca->src_line_size;
	पूर्ण
पूर्ण

अटल व्योम vimc_sca_fill_src_frame(स्थिर काष्ठा vimc_sca_device *स्थिर vsca,
				    स्थिर u8 *स्थिर sink_frame)
अणु
	स्थिर काष्ठा v4l2_rect r = vsca->crop_rect;
	अचिन्हित पूर्णांक i, j;

	/* Scale each pixel from the original sink frame */
	/* TODO: implement scale करोwn, only scale up is supported क्रम now */
	क्रम (i = r.top; i < r.top + r.height; i++)
		क्रम (j = r.left; j < r.left + r.width; j++)
			vimc_sca_scale_pix(vsca, i, j, sink_frame);
पूर्ण

अटल व्योम *vimc_sca_process_frame(काष्ठा vimc_ent_device *ved,
				    स्थिर व्योम *sink_frame)
अणु
	काष्ठा vimc_sca_device *vsca = container_of(ved, काष्ठा vimc_sca_device,
						    ved);

	/* If the stream in this node is not active, just वापस */
	अगर (!vsca->src_frame)
		वापस ERR_PTR(-EINVAL);

	vimc_sca_fill_src_frame(vsca, sink_frame);

	वापस vsca->src_frame;
पूर्ण;

अटल व्योम vimc_sca_release(काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा vimc_sca_device *vsca =
		container_of(ved, काष्ठा vimc_sca_device, ved);

	media_entity_cleanup(vsca->ved.ent);
	kमुक्त(vsca);
पूर्ण

अटल काष्ठा vimc_ent_device *vimc_sca_add(काष्ठा vimc_device *vimc,
					    स्थिर अक्षर *vcfg_name)
अणु
	काष्ठा v4l2_device *v4l2_dev = &vimc->v4l2_dev;
	काष्ठा vimc_sca_device *vsca;
	पूर्णांक ret;

	/* Allocate the vsca काष्ठा */
	vsca = kzalloc(माप(*vsca), GFP_KERNEL);
	अगर (!vsca)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize ved and sd */
	vsca->pads[0].flags = MEDIA_PAD_FL_SINK;
	vsca->pads[1].flags = MEDIA_PAD_FL_SOURCE;

	ret = vimc_ent_sd_रेजिस्टर(&vsca->ved, &vsca->sd, v4l2_dev,
				   vcfg_name,
				   MEDIA_ENT_F_PROC_VIDEO_SCALER, 2,
				   vsca->pads, &vimc_sca_ops);
	अगर (ret) अणु
		kमुक्त(vsca);
		वापस ERR_PTR(ret);
	पूर्ण

	vsca->ved.process_frame = vimc_sca_process_frame;
	vsca->ved.dev = vimc->mdev.dev;

	/* Initialize the frame क्रमmat */
	vsca->sink_fmt = sink_fmt_शेष;

	/* Initialize the crop selection */
	vsca->crop_rect = crop_rect_शेष;

	वापस &vsca->ved;
पूर्ण

काष्ठा vimc_ent_type vimc_sca_type = अणु
	.add = vimc_sca_add,
	.release = vimc_sca_release
पूर्ण;
