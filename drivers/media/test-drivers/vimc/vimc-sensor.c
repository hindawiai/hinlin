<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-sensor.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/tpg/v4l2-tpg.h>

#समावेश "vimc-common.h"

क्रमागत vimc_sen_osd_mode अणु
	VIMC_SEN_OSD_SHOW_ALL = 0,
	VIMC_SEN_OSD_SHOW_COUNTERS = 1,
	VIMC_SEN_OSD_SHOW_NONE = 2
पूर्ण;

काष्ठा vimc_sen_device अणु
	काष्ठा vimc_ent_device ved;
	काष्ठा v4l2_subdev sd;
	काष्ठा tpg_data tpg;
	u8 *frame;
	क्रमागत vimc_sen_osd_mode osd_value;
	u64 start_stream_ts;
	/* The active क्रमmat */
	काष्ठा v4l2_mbus_framefmt mbus_क्रमmat;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा media_pad pad;
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt fmt_शेष = अणु
	.width = 640,
	.height = 480,
	.code = MEDIA_BUS_FMT_RGB888_1X24,
	.field = V4L2_FIELD_NONE,
	.colorspace = V4L2_COLORSPACE_SRGB,
पूर्ण;

अटल पूर्णांक vimc_sen_init_cfg(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sd->entity.num_pads; i++) अणु
		काष्ठा v4l2_mbus_framefmt *mf;

		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);
		*mf = fmt_शेष;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sen_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	u32 mbus_code = vimc_mbus_code_by_index(code->index);

	अगर (!mbus_code)
		वापस -EINVAL;

	code->code = mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sen_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	अगर (fse->index)
		वापस -EINVAL;

	/* Only accept code in the pix map table */
	vpix = vimc_pix_map_by_code(fse->code);
	अगर (!vpix)
		वापस -EINVAL;

	fse->min_width = VIMC_FRAME_MIN_WIDTH;
	fse->max_width = VIMC_FRAME_MAX_WIDTH;
	fse->min_height = VIMC_FRAME_MIN_HEIGHT;
	fse->max_height = VIMC_FRAME_MAX_HEIGHT;

	वापस 0;
पूर्ण

अटल पूर्णांक vimc_sen_get_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vimc_sen_device *vsen =
				container_of(sd, काष्ठा vimc_sen_device, sd);

	fmt->क्रमmat = fmt->which == V4L2_SUBDEV_FORMAT_TRY ?
		      *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) :
		      vsen->mbus_क्रमmat;

	वापस 0;
पूर्ण

अटल व्योम vimc_sen_tpg_s_क्रमmat(काष्ठा vimc_sen_device *vsen)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix =
				vimc_pix_map_by_code(vsen->mbus_क्रमmat.code);

	tpg_reset_source(&vsen->tpg, vsen->mbus_क्रमmat.width,
			 vsen->mbus_क्रमmat.height, vsen->mbus_क्रमmat.field);
	tpg_s_bytesperline(&vsen->tpg, 0, vsen->mbus_क्रमmat.width * vpix->bpp);
	tpg_s_buf_height(&vsen->tpg, vsen->mbus_क्रमmat.height);
	tpg_s_fourcc(&vsen->tpg, vpix->pixelक्रमmat);
	/* TODO: add support क्रम V4L2_FIELD_ALTERNATE */
	tpg_s_field(&vsen->tpg, vsen->mbus_क्रमmat.field, false);
	tpg_s_colorspace(&vsen->tpg, vsen->mbus_क्रमmat.colorspace);
	tpg_s_ycbcr_enc(&vsen->tpg, vsen->mbus_क्रमmat.ycbcr_enc);
	tpg_s_quantization(&vsen->tpg, vsen->mbus_क्रमmat.quantization);
	tpg_s_xfer_func(&vsen->tpg, vsen->mbus_क्रमmat.xfer_func);
पूर्ण

अटल व्योम vimc_sen_adjust_fmt(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	स्थिर काष्ठा vimc_pix_map *vpix;

	/* Only accept code in the pix map table */
	vpix = vimc_pix_map_by_code(fmt->code);
	अगर (!vpix)
		fmt->code = fmt_शेष.code;

	fmt->width = clamp_t(u32, fmt->width, VIMC_FRAME_MIN_WIDTH,
			     VIMC_FRAME_MAX_WIDTH) & ~1;
	fmt->height = clamp_t(u32, fmt->height, VIMC_FRAME_MIN_HEIGHT,
			      VIMC_FRAME_MAX_HEIGHT) & ~1;

	/* TODO: add support क्रम V4L2_FIELD_ALTERNATE */
	अगर (fmt->field == V4L2_FIELD_ANY || fmt->field == V4L2_FIELD_ALTERNATE)
		fmt->field = fmt_शेष.field;

	vimc_colorimetry_clamp(fmt);
पूर्ण

अटल पूर्णांक vimc_sen_set_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vimc_sen_device *vsen = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		/* Do not change the क्रमmat जबतक stream is on */
		अगर (vsen->frame)
			वापस -EBUSY;

		mf = &vsen->mbus_क्रमmat;
	पूर्ण अन्यथा अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
	पूर्ण

	/* Set the new क्रमmat */
	vimc_sen_adjust_fmt(&fmt->क्रमmat);

	dev_dbg(vsen->ved.dev, "%s: format update: "
		"old:%dx%d (0x%x, %d, %d, %d, %d) "
		"new:%dx%d (0x%x, %d, %d, %d, %d)\n", vsen->sd.name,
		/* old */
		mf->width, mf->height, mf->code,
		mf->colorspace,	mf->quantization,
		mf->xfer_func, mf->ycbcr_enc,
		/* new */
		fmt->क्रमmat.width, fmt->क्रमmat.height, fmt->क्रमmat.code,
		fmt->क्रमmat.colorspace, fmt->क्रमmat.quantization,
		fmt->क्रमmat.xfer_func, fmt->क्रमmat.ycbcr_enc);

	*mf = fmt->क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops vimc_sen_pad_ops = अणु
	.init_cfg		= vimc_sen_init_cfg,
	.क्रमागत_mbus_code		= vimc_sen_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= vimc_sen_क्रमागत_frame_size,
	.get_fmt		= vimc_sen_get_fmt,
	.set_fmt		= vimc_sen_set_fmt,
पूर्ण;

अटल व्योम *vimc_sen_process_frame(काष्ठा vimc_ent_device *ved,
				    स्थिर व्योम *sink_frame)
अणु
	काष्ठा vimc_sen_device *vsen = container_of(ved, काष्ठा vimc_sen_device,
						    ved);
	स्थिर अचिन्हित पूर्णांक line_height = 16;
	u8 *basep[TPG_MAX_PLANES][2];
	अचिन्हित पूर्णांक line = 1;
	अक्षर str[100];

	tpg_fill_plane_buffer(&vsen->tpg, 0, 0, vsen->frame);
	tpg_calc_text_basep(&vsen->tpg, basep, 0, vsen->frame);
	चयन (vsen->osd_value) अणु
	हाल VIMC_SEN_OSD_SHOW_ALL: अणु
		स्थिर अक्षर *order = tpg_g_color_order(&vsen->tpg);

		tpg_gen_text(&vsen->tpg, basep, line++ * line_height,
			     16, order);
		snम_लिखो(str, माप(str),
			 "brightness %3d, contrast %3d, saturation %3d, hue %d ",
			 vsen->tpg.brightness,
			 vsen->tpg.contrast,
			 vsen->tpg.saturation,
			 vsen->tpg.hue);
		tpg_gen_text(&vsen->tpg, basep, line++ * line_height, 16, str);
		snम_लिखो(str, माप(str), "sensor size: %dx%d",
			 vsen->mbus_क्रमmat.width,
			 vsen->mbus_क्रमmat.height);
		tpg_gen_text(&vsen->tpg, basep, line++ * line_height, 16, str);
		fallthrough;
	पूर्ण
	हाल VIMC_SEN_OSD_SHOW_COUNTERS: अणु
		अचिन्हित पूर्णांक ms;

		ms = भाग_u64(kसमय_get_ns() - vsen->start_stream_ts, 1000000);
		snम_लिखो(str, माप(str), "%02d:%02d:%02d:%03d",
			 (ms / (60 * 60 * 1000)) % 24,
			 (ms / (60 * 1000)) % 60,
			 (ms / 1000) % 60,
			 ms % 1000);
		tpg_gen_text(&vsen->tpg, basep, line++ * line_height, 16, str);
		अवरोध;
	पूर्ण
	हाल VIMC_SEN_OSD_SHOW_NONE:
	शेष:
		अवरोध;
	पूर्ण

	वापस vsen->frame;
पूर्ण

अटल पूर्णांक vimc_sen_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा vimc_sen_device *vsen =
				container_of(sd, काष्ठा vimc_sen_device, sd);

	अगर (enable) अणु
		स्थिर काष्ठा vimc_pix_map *vpix;
		अचिन्हित पूर्णांक frame_size;

		vsen->start_stream_ts = kसमय_get_ns();

		/* Calculate the frame size */
		vpix = vimc_pix_map_by_code(vsen->mbus_क्रमmat.code);
		frame_size = vsen->mbus_क्रमmat.width * vpix->bpp *
			     vsen->mbus_क्रमmat.height;

		/*
		 * Allocate the frame buffer. Use vदो_स्मृति to be able to
		 * allocate a large amount of memory
		 */
		vsen->frame = vदो_स्मृति(frame_size);
		अगर (!vsen->frame)
			वापस -ENOMEM;

		/* configure the test pattern generator */
		vimc_sen_tpg_s_क्रमmat(vsen);

	पूर्ण अन्यथा अणु

		vमुक्त(vsen->frame);
		vsen->frame = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops vimc_sen_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vimc_sen_video_ops = अणु
	.s_stream = vimc_sen_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vimc_sen_ops = अणु
	.core = &vimc_sen_core_ops,
	.pad = &vimc_sen_pad_ops,
	.video = &vimc_sen_video_ops,
पूर्ण;

अटल पूर्णांक vimc_sen_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vimc_sen_device *vsen =
		container_of(ctrl->handler, काष्ठा vimc_sen_device, hdl);

	चयन (ctrl->id) अणु
	हाल VIMC_CID_TEST_PATTERN:
		tpg_s_pattern(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		tpg_s_hflip(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		tpg_s_vflip(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BRIGHTNESS:
		tpg_s_brightness(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		tpg_s_contrast(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		tpg_s_hue(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		tpg_s_saturation(&vsen->tpg, ctrl->val);
		अवरोध;
	हाल VIMC_CID_OSD_TEXT_MODE:
		vsen->osd_value = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vimc_sen_ctrl_ops = अणु
	.s_ctrl = vimc_sen_s_ctrl,
पूर्ण;

अटल व्योम vimc_sen_release(काष्ठा vimc_ent_device *ved)
अणु
	काष्ठा vimc_sen_device *vsen =
		container_of(ved, काष्ठा vimc_sen_device, ved);

	v4l2_ctrl_handler_मुक्त(&vsen->hdl);
	tpg_मुक्त(&vsen->tpg);
	media_entity_cleanup(vsen->ved.ent);
	kमुक्त(vsen);
पूर्ण

/* Image Processing Controls */
अटल स्थिर काष्ठा v4l2_ctrl_config vimc_sen_ctrl_class = अणु
	.flags = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_WRITE_ONLY,
	.id = VIMC_CID_VIMC_CLASS,
	.name = "VIMC Controls",
	.type = V4L2_CTRL_TYPE_CTRL_CLASS,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vimc_sen_ctrl_test_pattern = अणु
	.ops = &vimc_sen_ctrl_ops,
	.id = VIMC_CID_TEST_PATTERN,
	.name = "Test Pattern",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = TPG_PAT_NOISE,
	.qmenu = tpg_pattern_strings,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vimc_ctrl_osd_mode_strings[] = अणु
	"All",
	"Counters Only",
	"None",
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config vimc_sen_ctrl_osd_mode = अणु
	.ops = &vimc_sen_ctrl_ops,
	.id = VIMC_CID_OSD_TEXT_MODE,
	.name = "Show Information",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(vimc_ctrl_osd_mode_strings) - 2,
	.qmenu = vimc_ctrl_osd_mode_strings,
पूर्ण;

अटल काष्ठा vimc_ent_device *vimc_sen_add(काष्ठा vimc_device *vimc,
					    स्थिर अक्षर *vcfg_name)
अणु
	काष्ठा v4l2_device *v4l2_dev = &vimc->v4l2_dev;
	काष्ठा vimc_sen_device *vsen;
	पूर्णांक ret;

	/* Allocate the vsen काष्ठा */
	vsen = kzalloc(माप(*vsen), GFP_KERNEL);
	अगर (!vsen)
		वापस ERR_PTR(-ENOMEM);

	v4l2_ctrl_handler_init(&vsen->hdl, 4);

	v4l2_ctrl_new_custom(&vsen->hdl, &vimc_sen_ctrl_class, शून्य);
	v4l2_ctrl_new_custom(&vsen->hdl, &vimc_sen_ctrl_test_pattern, शून्य);
	v4l2_ctrl_new_custom(&vsen->hdl, &vimc_sen_ctrl_osd_mode, शून्य);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&vsen->hdl, &vimc_sen_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 255, 1, 128);
	vsen->sd.ctrl_handler = &vsen->hdl;
	अगर (vsen->hdl.error) अणु
		ret = vsen->hdl.error;
		जाओ err_मुक्त_vsen;
	पूर्ण

	/* Initialize the test pattern generator */
	tpg_init(&vsen->tpg, vsen->mbus_क्रमmat.width,
		 vsen->mbus_क्रमmat.height);
	ret = tpg_alloc(&vsen->tpg, VIMC_FRAME_MAX_WIDTH);
	अगर (ret)
		जाओ err_मुक्त_hdl;

	/* Initialize ved and sd */
	vsen->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = vimc_ent_sd_रेजिस्टर(&vsen->ved, &vsen->sd, v4l2_dev,
				   vcfg_name,
				   MEDIA_ENT_F_CAM_SENSOR, 1, &vsen->pad,
				   &vimc_sen_ops);
	अगर (ret)
		जाओ err_मुक्त_tpg;

	vsen->ved.process_frame = vimc_sen_process_frame;
	vsen->ved.dev = vimc->mdev.dev;

	/* Initialize the frame क्रमmat */
	vsen->mbus_क्रमmat = fmt_शेष;

	वापस &vsen->ved;

err_मुक्त_tpg:
	tpg_मुक्त(&vsen->tpg);
err_मुक्त_hdl:
	v4l2_ctrl_handler_मुक्त(&vsen->hdl);
err_मुक्त_vsen:
	kमुक्त(vsen);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा vimc_ent_type vimc_sen_type = अणु
	.add = vimc_sen_add,
	.release = vimc_sen_release
पूर्ण;
