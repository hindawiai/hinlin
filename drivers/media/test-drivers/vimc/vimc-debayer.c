<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-debayer.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vimc-common.h"

क्रमागत vimc_deb_rgb_colors अणु
	VIMC_DEB_RED = 0,
	VIMC_DEB_GREEN = 1,
	VIMC_DEB_BLUE = 2,
पूर्ण;

काष्ठा vimc_deb_pix_map अणु
	u32 code;
	क्रमागत vimc_deb_rgb_colors order[2][2];
पूर्ण;

काष्ठा vimc_deb_device अणु
	काष्ठा vimc_ent_device ved;
	काष्ठा v4l2_subdev sd;
	/* The active क्रमmat */
	काष्ठा v4l2_mbus_framefmt sink_fmt;
	u32 src_code;
	व्योम (*set_rgb_src)(काष्ठा vimc_deb_device *vdeb, अचिन्हित पूर्णांक lin,
			    अचिन्हित पूर्णांक col, अचिन्हित पूर्णांक rgb[3]);
	/* Values calculated when the stream starts */
	u8 *src_frame;
	स्थिर काष्ठा vimc_deb_pix_map *sink_pix_map;
	अचिन्हित पूर्णांक sink_bpp;
	अचिन्हित पूर्णांक mean_win_size;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा media_pad pads[2];
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt sink_fmt_शेष = अणु
	.width = 640,
	.height = 480,
	.code = MEDIA_BUS_FMT_SRGGB8_1X8,
	.field = V4L2_FIELD_NONE,
	.colorspace = V4L2_COLORSPACE_SRGB,
पूर्ण;

अटल स्थिर u32 vimc_deb_src_mbus_codes[] = अणु
	MEDIA_BUS_FMT_GBR888_1X24,
	MEDIA_BUS_FMT_BGR888_1X24,
	MEDIA_BUS_FMT_BGR888_3X8,
	MEDIA_BUS_FMT_RGB888_1X24,
	MEDIA_BUS_FMT_RGB888_2X12_BE,
	MEDIA_BUS_FMT_RGB888_2X12_LE,
	MEDIA_BUS_FMT_RGB888_3X8,
	MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,
	MEDIA_BUS_FMT_RGB888_1X32_PADHI,
पूर्ण;

अटल स्थिर काष्ठा vimc_deb_pix_map vimc_deb_pix_map_list[] = अणु
	अणु
		.code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.order = अणु अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGBRG8_1X8,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण,
			   अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGRBG8_1X8,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण,
			   अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SRGGB8_1X8,
		.order = अणु अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SBGGR10_1X10,
		.order = अणु अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGBRG10_1X10,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण,
			   अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGRBG10_1X10,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण,
			   अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.order = अणु अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SBGGR12_1X12,
		.order = अणु अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGBRG12_1X12,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण,
			   अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SGRBG12_1X12,
		.order = अणु अणु VIMC_DEB_GREEN, VIMC_DEB_RED पूर्ण,
			   अणु VIMC_DEB_BLUE, VIMC_DEB_GREEN पूर्ण पूर्ण
	पूर्ण,
	अणु
		.code = MEDIA_BUS_FMT_SRGGB12_1X12,
		.order = अणु अणु VIMC_DEB_RED, VIMC_DEB_GREEN पूर्ण,
			   अणु VIMC_DEB_GREEN, VIMC_DEB_BLUE पूर्ण पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vimc_deb_pix_map *vimc_deb_pix_map_by_code(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vimc_deb_pix_map_list); i++)
		अगर (vimc_deb_pix_map_list[i].code == code)
			वापस &vimc_deb_pix_map_list[i];

	वापस शून्य;
पूर्ण

अटल bool vimc_deb_src_code_is_valid(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vimc_deb_src_mbus_codes); i++)
		अगर (vimc_deb_src_mbus_codes[i] == code)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक vimc_deb_init_cfg(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	अचिन्हित पूर्णांक i;

	mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	*mf = sink_fmt_शेष;

	क्रम (i = 1; i < sd->entity.num_pads; i++) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);
		*mf = sink_fmt_शेष;
		mf->code = vdeb->src_code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_deb_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (VIMC_IS_SRC(code->pad)) अणु
		अगर (code->index >= ARRAY_SIZE(vimc_deb_src_mbus_codes))
			वापस -EINVAL;

		code->code = vimc_deb_src_mbus_codes[code->index];
	पूर्ण अन्यथा अणु
		अगर (code->index >= ARRAY_SIZE(vimc_deb_pix_map_list))
			वापस -EINVAL;

		code->code = vimc_deb_pix_map_list[code->index].code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_deb_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index)
		वापस -EINVAL;

	अगर (VIMC_IS_SINK(fse->pad)) अणु
		स्थिर काष्ठा vimc_deb_pix_map *vpix =
			vimc_deb_pix_map_by_code(fse->code);

		अगर (!vpix)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!vimc_deb_src_code_is_valid(fse->code)) अणु
		वापस -EINVAL;
	पूर्ण

	fse->min_width = VIMC_FRAME_MIN_WIDTH;
	fse->max_width = VIMC_FRAME_MAX_WIDTH;
	fse->min_height = VIMC_FRAME_MIN_HEIGHT;
	fse->max_height = VIMC_FRAME_MAX_HEIGHT;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_deb_get_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

	/* Get the current sink क्रमmat */
	fmt->क्रमmat = fmt->which == V4L2_SUBDEV_FORMAT_TRY ?
		      *v4l2_subdev_get_try_क्रमmat(sd, cfg, 0) :
		      vdeb->sink_fmt;

	/* Set the right code क्रम the source pad */
	अगर (VIMC_IS_SRC(fmt->pad))
		fmt->क्रमmat.code = vdeb->src_code;

	वापस 0;
पूर्ण

अटल व्योम vimc_deb_adjust_sink_fmt(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	स्थिर काष्ठा vimc_deb_pix_map *vpix;

	/* Don't accept a code that is not on the debayer table */
	vpix = vimc_deb_pix_map_by_code(fmt->code);
	अगर (!vpix)
		fmt->code = sink_fmt_शेष.code;

	fmt->width = clamp_t(u32, fmt->width, VIMC_FRAME_MIN_WIDTH,
			     VIMC_FRAME_MAX_WIDTH) & ~1;
	fmt->height = clamp_t(u32, fmt->height, VIMC_FRAME_MIN_HEIGHT,
			      VIMC_FRAME_MAX_HEIGHT) & ~1;

	अगर (fmt->field == V4L2_FIELD_ANY)
		fmt->field = sink_fmt_शेष.field;

	vimc_colorimetry_clamp(fmt);
पूर्ण

अटल पूर्णांक vimc_deb_set_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	u32 *src_code;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		/* Do not change the क्रमmat जबतक stream is on */
		अगर (vdeb->src_frame)
			वापस -EBUSY;

		sink_fmt = &vdeb->sink_fmt;
		src_code = &vdeb->src_code;
	पूर्ण अन्यथा अणु
		sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		src_code = &v4l2_subdev_get_try_क्रमmat(sd, cfg, 1)->code;
	पूर्ण

	/*
	 * Do not change the क्रमmat of the source pad,
	 * it is propagated from the sink
	 */
	अगर (VIMC_IS_SRC(fmt->pad)) अणु
		u32 code = fmt->क्रमmat.code;

		fmt->क्रमmat = *sink_fmt;

		अगर (vimc_deb_src_code_is_valid(code))
			*src_code = code;

		fmt->क्रमmat.code = *src_code;
	पूर्ण अन्यथा अणु
		/* Set the new क्रमmat in the sink pad */
		vimc_deb_adjust_sink_fmt(&fmt->क्रमmat);

		dev_dbg(vdeb->ved.dev, "%s: sink format update: "
			"old:%dx%d (0x%x, %d, %d, %d, %d) "
			"new:%dx%d (0x%x, %d, %d, %d, %d)\n", vdeb->sd.name,
			/* old */
			sink_fmt->width, sink_fmt->height, sink_fmt->code,
			sink_fmt->colorspace, sink_fmt->quantization,
			sink_fmt->xfer_func, sink_fmt->ycbcr_enc,
			/* new */
			fmt->क्रमmat.width, fmt->क्रमmat.height, fmt->क्रमmat.code,
			fmt->क्रमmat.colorspace,	fmt->क्रमmat.quantization,
			fmt->क्रमmat.xfer_func, fmt->क्रमmat.ycbcr_enc);

		*sink_fmt = fmt->क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops vimc_deb_pad_ops = अणु
	.init_cfg		= vimc_deb_init_cfg,
	.क्रमागत_mbus_code		= vimc_deb_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= vimc_deb_क्रमागत_frame_size,
	.get_fmt		= vimc_deb_get_fmt,
	.set_fmt		= vimc_deb_set_fmt,
पूर्ण;

अटल व्योम vimc_deb_process_rgb_frame(काष्ठा vimc_deb_device *vdeb,
				       अचिन्हित पूर्णांक lin,
				       अचिन्हित पूर्णांक col,
				       अचिन्हित पूर्णांक rgb[3])
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;
	अचिन्हित पूर्णांक i, index;

	vpix = vimc_pix_map_by_code(vdeb->src_code);
	index = VIMC_FRAME_INDEX(lin, col, vdeb->sink_fmt.width, 3);
	क्रम (i = 0; i < 3; i++) अणु
		चयन (vpix->pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_RGB24:
			vdeb->src_frame[index + i] = rgb[i];
			अवरोध;
		हाल V4L2_PIX_FMT_BGR24:
			vdeb->src_frame[index + i] = rgb[2 - i];
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक vimc_deb_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

	अगर (enable) अणु
		स्थिर काष्ठा vimc_pix_map *vpix;
		अचिन्हित पूर्णांक frame_size;

		अगर (vdeb->src_frame)
			वापस 0;

		/* Calculate the frame size of the source pad */
		vpix = vimc_pix_map_by_code(vdeb->src_code);
		frame_size = vdeb->sink_fmt.width * vdeb->sink_fmt.height *
				vpix->bpp;

		/* Save the bytes per pixel of the sink */
		vpix = vimc_pix_map_by_code(vdeb->sink_fmt.code);
		vdeb->sink_bpp = vpix->bpp;

		/* Get the corresponding pixel map from the table */
		vdeb->sink_pix_map =
			vimc_deb_pix_map_by_code(vdeb->sink_fmt.code);

		/*
		 * Allocate the frame buffer. Use vदो_स्मृति to be able to
		 * allocate a large amount of memory
		 */
		vdeb->src_frame = vदो_स्मृति(frame_size);
		अगर (!vdeb->src_frame)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		अगर (!vdeb->src_frame)
			वापस 0;

		vमुक्त(vdeb->src_frame);
		vdeb->src_frame = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops vimc_deb_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vimc_deb_video_ops = अणु
	.s_stream = vimc_deb_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vimc_deb_ops = अणु
	.core = &vimc_deb_core_ops,
	.pad = &vimc_deb_pad_ops,
	.video = &vimc_deb_video_ops,
पूर्ण;

अटल अचिन्हित पूर्णांक vimc_deb_get_val(स्थिर u8 *bytes,
				     स्थिर अचिन्हित पूर्णांक n_bytes)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक acc = 0;

	क्रम (i = 0; i < n_bytes; i++)
		acc = acc + (bytes[i] << (8 * i));

	वापस acc;
पूर्ण

अटल व्योम vimc_deb_calc_rgb_sink(काष्ठा vimc_deb_device *vdeb,
				   स्थिर u8 *frame,
				   स्थिर अचिन्हित पूर्णांक lin,
				   स्थिर अचिन्हित पूर्णांक col,
				   अचिन्हित पूर्णांक rgb[3])
अणु
	अचिन्हित पूर्णांक i, seek, wlin, wcol;
	अचिन्हित पूर्णांक n_rgb[3] = अणु0, 0, 0पूर्ण;

	क्रम (i = 0; i < 3; i++)
		rgb[i] = 0;

	/*
	 * Calculate how many we need to subtract to get to the pixel in
	 * the top left corner of the mean winकरोw (considering the current
	 * pixel as the center)
	 */
	seek = vdeb->mean_win_size / 2;

	/* Sum the values of the colors in the mean winकरोw */

	dev_dbg(vdeb->ved.dev,
		"deb: %s: --- Calc pixel %dx%d, window mean %d, seek %d ---\n",
		vdeb->sd.name, lin, col, vdeb->sink_fmt.height, seek);

	/*
	 * Iterate through all the lines in the mean winकरोw, start
	 * with zero अगर the pixel is outside the frame and करोn't pass
	 * the height when the pixel is in the bottom border of the
	 * frame
	 */
	क्रम (wlin = seek > lin ? 0 : lin - seek;
	     wlin < lin + seek + 1 && wlin < vdeb->sink_fmt.height;
	     wlin++) अणु

		/*
		 * Iterate through all the columns in the mean winकरोw, start
		 * with zero अगर the pixel is outside the frame and करोn't pass
		 * the width when the pixel is in the right border of the
		 * frame
		 */
		क्रम (wcol = seek > col ? 0 : col - seek;
		     wcol < col + seek + 1 && wcol < vdeb->sink_fmt.width;
		     wcol++) अणु
			क्रमागत vimc_deb_rgb_colors color;
			अचिन्हित पूर्णांक index;

			/* Check which color this pixel is */
			color = vdeb->sink_pix_map->order[wlin % 2][wcol % 2];

			index = VIMC_FRAME_INDEX(wlin, wcol,
						 vdeb->sink_fmt.width,
						 vdeb->sink_bpp);

			dev_dbg(vdeb->ved.dev,
				"deb: %s: RGB CALC: frame index %d, win pos %dx%d, color %d\n",
				vdeb->sd.name, index, wlin, wcol, color);

			/* Get its value */
			rgb[color] = rgb[color] +
				vimc_deb_get_val(&frame[index], vdeb->sink_bpp);

			/* Save how many values we alपढ़ोy added */
			n_rgb[color]++;

			dev_dbg(vdeb->ved.dev, "deb: %s: RGB CALC: val %d, n %d\n",
				vdeb->sd.name, rgb[color], n_rgb[color]);
		पूर्ण
	पूर्ण

	/* Calculate the mean */
	क्रम (i = 0; i < 3; i++) अणु
		dev_dbg(vdeb->ved.dev,
			"deb: %s: PRE CALC: %dx%d Color %d, val %d, n %d\n",
			vdeb->sd.name, lin, col, i, rgb[i], n_rgb[i]);

		अगर (n_rgb[i])
			rgb[i] = rgb[i] / n_rgb[i];

		dev_dbg(vdeb->ved.dev,
			"deb: %s: FINAL CALC: %dx%d Color %d, val %d\n",
			vdeb->sd.name, lin, col, i, rgb[i]);
	पूर्ण
पूर्ण

अटल व्योम *vimc_deb_process_frame(काष्ठा vimc_ent_device *ved,
				    स्थिर व्योम *sink_frame)
अणु
	काष्ठा vimc_deb_device *vdeb = container_of(ved, काष्ठा vimc_deb_device,
						    ved);
	अचिन्हित पूर्णांक rgb[3];
	अचिन्हित पूर्णांक i, j;

	/* If the stream in this node is not active, just वापस */
	अगर (!vdeb->src_frame)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < vdeb->sink_fmt.height; i++)
		क्रम (j = 0; j < vdeb->sink_fmt.width; j++) अणु
			vimc_deb_calc_rgb_sink(vdeb, sink_frame, i, j, rgb);
			vdeb->set_rgb_src(vdeb, i, j, rgb);
		पूर्ण

	वापस vdeb->src_frame;
पूर्ण

अटल पूर्णांक vimc_deb_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vimc_deb_device *vdeb =
		container_of(ctrl->handler, काष्ठा vimc_deb_device, hdl);

	चयन (ctrl->id) अणु
	हाल VIMC_CID_MEAN_WIN_SIZE:
		vdeb->mean_win_size = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vimc_deb_ctrl_ops = अणु
	.s_ctrl = vimc_deb_s_ctrl,
पूर्ण;

अटल व्योम vimc_deb_release(काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा vimc_deb_device *vdeb =
		container_of(ved, काष्ठा vimc_deb_device, ved);

	v4l2_ctrl_handler_मुक्त(&vdeb->hdl);
	media_entity_cleanup(vdeb->ved.ent);
	kमुक्त(vdeb);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_config vimc_deb_ctrl_class = अणु
	.flags = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_WRITE_ONLY,
	.id = VIMC_CID_VIMC_CLASS,
	.name = "VIMC Controls",
	.type = V4L2_CTRL_TYPE_CTRL_CLASS,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vimc_deb_ctrl_mean_win_size = अणु
	.ops = &vimc_deb_ctrl_ops,
	.id = VIMC_CID_MEAN_WIN_SIZE,
	.name = "Debayer Mean Window Size",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 1,
	.max = 25,
	.step = 2,
	.def = 3,
पूर्ण;

अटल काष्ठा vimc_ent_device *vimc_deb_add(काष्ठा vimc_device *vimc,
					    स्थिर अक्षर *vcfg_name)
अणु
	काष्ठा v4l2_device *v4l2_dev = &vimc->v4l2_dev;
	काष्ठा vimc_deb_device *vdeb;
	पूर्णांक ret;

	/* Allocate the vdeb काष्ठा */
	vdeb = kzalloc(माप(*vdeb), GFP_KERNEL);
	अगर (!vdeb)
		वापस ERR_PTR(-ENOMEM);

	/* Create controls: */
	v4l2_ctrl_handler_init(&vdeb->hdl, 2);
	v4l2_ctrl_new_custom(&vdeb->hdl, &vimc_deb_ctrl_class, शून्य);
	v4l2_ctrl_new_custom(&vdeb->hdl, &vimc_deb_ctrl_mean_win_size, शून्य);
	vdeb->sd.ctrl_handler = &vdeb->hdl;
	अगर (vdeb->hdl.error) अणु
		ret = vdeb->hdl.error;
		जाओ err_मुक्त_vdeb;
	पूर्ण

	/* Initialize ved and sd */
	vdeb->pads[0].flags = MEDIA_PAD_FL_SINK;
	vdeb->pads[1].flags = MEDIA_PAD_FL_SOURCE;

	ret = vimc_ent_sd_रेजिस्टर(&vdeb->ved, &vdeb->sd, v4l2_dev,
				   vcfg_name,
				   MEDIA_ENT_F_PROC_VIDEO_PIXEL_ENC_CONV, 2,
				   vdeb->pads, &vimc_deb_ops);
	अगर (ret)
		जाओ err_मुक्त_hdl;

	vdeb->ved.process_frame = vimc_deb_process_frame;
	vdeb->ved.dev = vimc->mdev.dev;
	vdeb->mean_win_size = vimc_deb_ctrl_mean_win_size.def;

	/* Initialize the frame क्रमmat */
	vdeb->sink_fmt = sink_fmt_शेष;
	/*
	 * TODO: Add support क्रम more output क्रमmats, we only support
	 * RGB888 क्रम now
	 * NOTE: the src क्रमmat is always the same as the sink, except
	 * क्रम the code
	 */
	vdeb->src_code = MEDIA_BUS_FMT_RGB888_1X24;
	vdeb->set_rgb_src = vimc_deb_process_rgb_frame;

	वापस &vdeb->ved;

err_मुक्त_hdl:
	v4l2_ctrl_handler_मुक्त(&vdeb->hdl);
err_मुक्त_vdeb:
	kमुक्त(vdeb);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा vimc_ent_type vimc_deb_type = अणु
	.add = vimc_deb_add,
	.release = vimc_deb_release
पूर्ण;
