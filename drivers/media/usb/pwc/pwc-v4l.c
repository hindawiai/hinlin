<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   USB and Video4Linux पूर्णांकerface part.
   (C) 1999-2004 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)
   (C) 2011 Hans de Goede <hdegoede@redhat.com>

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.


*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/पन.स>

#समावेश "pwc.h"

#घोषणा PWC_CID_CUSTOM(ctrl) ((V4L2_CID_USER_BASE | 0xf000) + custom_ ## ctrl)

अटल पूर्णांक pwc_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल पूर्णांक pwc_s_ctrl(काष्ठा v4l2_ctrl *ctrl);

अटल स्थिर काष्ठा v4l2_ctrl_ops pwc_ctrl_ops = अणु
	.g_अस्थिर_ctrl = pwc_g_अस्थिर_ctrl,
	.s_ctrl = pwc_s_ctrl,
पूर्ण;

क्रमागत अणु awb_inकरोor, awb_outकरोor, awb_fl, awb_manual, awb_स्वतः पूर्ण;
क्रमागत अणु custom_स्वतःcontour, custom_contour, custom_noise_reduction,
	custom_awb_speed, custom_awb_delay,
	custom_save_user, custom_restore_user, custom_restore_factory पूर्ण;

अटल स्थिर अक्षर * स्थिर pwc_स्वतः_whitebal_qmenu[] = अणु
	"Indoor (Incandescant Lighting) Mode",
	"Outdoor (Sunlight) Mode",
	"Indoor (Fluorescent Lighting) Mode",
	"Manual Mode",
	"Auto Mode",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_स्वतः_white_balance_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= V4L2_CID_AUTO_WHITE_BALANCE,
	.type	= V4L2_CTRL_TYPE_MENU,
	.max	= awb_स्वतः,
	.qmenu	= pwc_स्वतः_whitebal_qmenu,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_स्वतःcontour_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(स्वतःcontour),
	.type	= V4L2_CTRL_TYPE_BOOLEAN,
	.name	= "Auto contour",
	.min	= 0,
	.max	= 1,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_contour_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(contour),
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.name	= "Contour",
	.flags  = V4L2_CTRL_FLAG_SLIDER,
	.min	= 0,
	.max	= 63,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_backlight_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= V4L2_CID_BACKLIGHT_COMPENSATION,
	.type	= V4L2_CTRL_TYPE_BOOLEAN,
	.min	= 0,
	.max	= 1,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_flicker_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= V4L2_CID_BAND_STOP_FILTER,
	.type	= V4L2_CTRL_TYPE_BOOLEAN,
	.min	= 0,
	.max	= 1,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_noise_reduction_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(noise_reduction),
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.name	= "Dynamic Noise Reduction",
	.min	= 0,
	.max	= 3,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_save_user_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(save_user),
	.type	= V4L2_CTRL_TYPE_BUTTON,
	.name    = "Save User Settings",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_restore_user_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(restore_user),
	.type	= V4L2_CTRL_TYPE_BUTTON,
	.name    = "Restore User Settings",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_restore_factory_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(restore_factory),
	.type	= V4L2_CTRL_TYPE_BUTTON,
	.name    = "Restore Factory Settings",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_awb_speed_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(awb_speed),
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.name	= "Auto White Balance Speed",
	.min	= 1,
	.max	= 32,
	.step	= 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config pwc_awb_delay_cfg = अणु
	.ops	= &pwc_ctrl_ops,
	.id	= PWC_CID_CUSTOM(awb_delay),
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.name	= "Auto White Balance Delay",
	.min	= 0,
	.max	= 63,
	.step	= 1,
पूर्ण;

पूर्णांक pwc_init_controls(काष्ठा pwc_device *pdev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl_config cfg;
	पूर्णांक r, def;

	hdl = &pdev->ctrl_handler;
	r = v4l2_ctrl_handler_init(hdl, 20);
	अगर (r)
		वापस r;

	/* Brightness, contrast, saturation, gamma */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, BRIGHTNESS_FORMATTER, &def);
	अगर (r || def > 127)
		def = 63;
	pdev->brightness = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_BRIGHTNESS, 0, 127, 1, def);

	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, CONTRAST_FORMATTER, &def);
	अगर (r || def > 63)
		def = 31;
	pdev->contrast = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_CONTRAST, 0, 63, 1, def);

	अगर (pdev->type >= 675) अणु
		अगर (pdev->type < 730)
			pdev->saturation_fmt = SATURATION_MODE_FORMATTER2;
		अन्यथा
			pdev->saturation_fmt = SATURATION_MODE_FORMATTER1;
		r = pwc_get_s8_ctrl(pdev, GET_CHROM_CTL, pdev->saturation_fmt,
				    &def);
		अगर (r || def < -100 || def > 100)
			def = 0;
		pdev->saturation = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				      V4L2_CID_SATURATION, -100, 100, 1, def);
	पूर्ण

	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, GAMMA_FORMATTER, &def);
	अगर (r || def > 31)
		def = 15;
	pdev->gamma = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_GAMMA, 0, 31, 1, def);

	/* स्वतः white balance, red gain, blue gain */
	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL, WB_MODE_FORMATTER, &def);
	अगर (r || def > awb_स्वतः)
		def = awb_स्वतः;
	cfg = pwc_स्वतः_white_balance_cfg;
	cfg.name = v4l2_ctrl_get_name(cfg.id);
	cfg.def = def;
	pdev->स्वतः_white_balance = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);
	/* check स्वतः controls to aव्योम शून्य deref in v4l2_ctrl_स्वतः_cluster */
	अगर (!pdev->स्वतः_white_balance)
		वापस hdl->error;

	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL,
			    PRESET_MANUAL_RED_GAIN_FORMATTER, &def);
	अगर (r)
		def = 127;
	pdev->red_balance = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_RED_BALANCE, 0, 255, 1, def);

	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL,
			    PRESET_MANUAL_BLUE_GAIN_FORMATTER, &def);
	अगर (r)
		def = 127;
	pdev->blue_balance = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_BLUE_BALANCE, 0, 255, 1, def);

	v4l2_ctrl_स्वतः_cluster(3, &pdev->स्वतः_white_balance, awb_manual, true);

	/* स्वतःgain, gain */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, AGC_MODE_FORMATTER, &def);
	अगर (r || (def != 0 && def != 0xff))
		def = 0;
	/* Note a रेजिस्टर value अगर 0 means स्वतः gain is on */
	pdev->स्वतःgain = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_AUTOGAIN, 0, 1, 1, def == 0);
	अगर (!pdev->स्वतःgain)
		वापस hdl->error;

	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, PRESET_AGC_FORMATTER, &def);
	अगर (r || def > 63)
		def = 31;
	pdev->gain = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_GAIN, 0, 63, 1, def);

	/* स्वतः exposure, exposure */
	अगर (DEVICE_USE_CODEC2(pdev->type)) अणु
		r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, SHUTTER_MODE_FORMATTER,
				    &def);
		अगर (r || (def != 0 && def != 0xff))
			def = 0;
		/*
		 * def = 0 स्वतः, def = ff manual
		 * menu idx 0 = स्वतः, idx 1 = manual
		 */
		pdev->exposure_स्वतः = v4l2_ctrl_new_std_menu(hdl,
					&pwc_ctrl_ops,
					V4L2_CID_EXPOSURE_AUTO,
					1, 0, def != 0);
		अगर (!pdev->exposure_स्वतः)
			वापस hdl->error;

		/* GET_LUM_CTL, PRESET_SHUTTER_FORMATTER is unreliable */
		r = pwc_get_u16_ctrl(pdev, GET_STATUS_CTL,
				     READ_SHUTTER_FORMATTER, &def);
		अगर (r || def > 655)
			def = 655;
		pdev->exposure = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
					V4L2_CID_EXPOSURE, 0, 655, 1, def);
		/* CODEC2: separate स्वतः gain & स्वतः exposure */
		v4l2_ctrl_स्वतः_cluster(2, &pdev->स्वतःgain, 0, true);
		v4l2_ctrl_स्वतः_cluster(2, &pdev->exposure_स्वतः,
				       V4L2_EXPOSURE_MANUAL, true);
	पूर्ण अन्यथा अगर (DEVICE_USE_CODEC3(pdev->type)) अणु
		/* GET_LUM_CTL, PRESET_SHUTTER_FORMATTER is unreliable */
		r = pwc_get_u16_ctrl(pdev, GET_STATUS_CTL,
				     READ_SHUTTER_FORMATTER, &def);
		अगर (r || def > 255)
			def = 255;
		pdev->exposure = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
					V4L2_CID_EXPOSURE, 0, 255, 1, def);
		/* CODEC3: both gain and exposure controlled by स्वतःgain */
		pdev->स्वतःgain_expo_cluster[0] = pdev->स्वतःgain;
		pdev->स्वतःgain_expo_cluster[1] = pdev->gain;
		pdev->स्वतःgain_expo_cluster[2] = pdev->exposure;
		v4l2_ctrl_स्वतः_cluster(3, pdev->स्वतःgain_expo_cluster,
				       0, true);
	पूर्ण

	/* color / bw setting */
	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL, COLOUR_MODE_FORMATTER,
			 &def);
	अगर (r || (def != 0 && def != 0xff))
		def = 0xff;
	/* def = 0 bw, def = ff color, menu idx 0 = color, idx 1 = bw */
	pdev->colorfx = v4l2_ctrl_new_std_menu(hdl, &pwc_ctrl_ops,
				V4L2_CID_COLORFX, 1, 0, def == 0);

	/* स्वतःcontour, contour */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, AUTO_CONTOUR_FORMATTER, &def);
	अगर (r || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_स्वतःcontour_cfg;
	cfg.def = def == 0;
	pdev->स्वतःcontour = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);
	अगर (!pdev->स्वतःcontour)
		वापस hdl->error;

	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL, PRESET_CONTOUR_FORMATTER, &def);
	अगर (r || def > 63)
		def = 31;
	cfg = pwc_contour_cfg;
	cfg.def = def;
	pdev->contour = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	v4l2_ctrl_स्वतः_cluster(2, &pdev->स्वतःcontour, 0, false);

	/* backlight */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL,
			    BACK_LIGHT_COMPENSATION_FORMATTER, &def);
	अगर (r || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_backlight_cfg;
	cfg.name = v4l2_ctrl_get_name(cfg.id);
	cfg.def = def == 0;
	pdev->backlight = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	/* flikker rediction */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL,
			    FLICKERLESS_MODE_FORMATTER, &def);
	अगर (r || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_flicker_cfg;
	cfg.name = v4l2_ctrl_get_name(cfg.id);
	cfg.def = def == 0;
	pdev->flicker = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	/* Dynamic noise reduction */
	r = pwc_get_u8_ctrl(pdev, GET_LUM_CTL,
			    DYNAMIC_NOISE_CONTROL_FORMATTER, &def);
	अगर (r || def > 3)
		def = 2;
	cfg = pwc_noise_reduction_cfg;
	cfg.def = def;
	pdev->noise_reduction = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	/* Save / Restore User / Factory Settings */
	pdev->save_user = v4l2_ctrl_new_custom(hdl, &pwc_save_user_cfg, शून्य);
	pdev->restore_user = v4l2_ctrl_new_custom(hdl, &pwc_restore_user_cfg,
						  शून्य);
	अगर (pdev->restore_user)
		pdev->restore_user->flags |= V4L2_CTRL_FLAG_UPDATE;
	pdev->restore_factory = v4l2_ctrl_new_custom(hdl,
						     &pwc_restore_factory_cfg,
						     शून्य);
	अगर (pdev->restore_factory)
		pdev->restore_factory->flags |= V4L2_CTRL_FLAG_UPDATE;

	/* Auto White Balance speed & delay */
	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL,
			    AWB_CONTROL_SPEED_FORMATTER, &def);
	अगर (r || def < 1 || def > 32)
		def = 1;
	cfg = pwc_awb_speed_cfg;
	cfg.def = def;
	pdev->awb_speed = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	r = pwc_get_u8_ctrl(pdev, GET_CHROM_CTL,
			    AWB_CONTROL_DELAY_FORMATTER, &def);
	अगर (r || def > 63)
		def = 0;
	cfg = pwc_awb_delay_cfg;
	cfg.def = def;
	pdev->awb_delay = v4l2_ctrl_new_custom(hdl, &cfg, शून्य);

	अगर (!(pdev->features & FEATURE_MOTOR_PANTILT))
		वापस hdl->error;

	/* Motor pan / tilt / reset */
	pdev->motor_pan = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_PAN_RELATIVE, -4480, 4480, 64, 0);
	अगर (!pdev->motor_pan)
		वापस hdl->error;
	pdev->motor_tilt = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_TILT_RELATIVE, -1920, 1920, 64, 0);
	pdev->motor_pan_reset = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_PAN_RESET, 0, 0, 0, 0);
	pdev->motor_tilt_reset = v4l2_ctrl_new_std(hdl, &pwc_ctrl_ops,
				V4L2_CID_TILT_RESET, 0, 0, 0, 0);
	v4l2_ctrl_cluster(4, &pdev->motor_pan);

	वापस hdl->error;
पूर्ण

अटल व्योम pwc_vidioc_fill_fmt(काष्ठा v4l2_क्रमmat *f,
	पूर्णांक width, पूर्णांक height, u32 pixfmt)
अणु
	स_रखो(&f->fmt.pix, 0, माप(काष्ठा v4l2_pix_क्रमmat));
	f->fmt.pix.width        = width;
	f->fmt.pix.height       = height;
	f->fmt.pix.field        = V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat  = pixfmt;
	f->fmt.pix.bytesperline = f->fmt.pix.width;
	f->fmt.pix.sizeimage	= f->fmt.pix.height * f->fmt.pix.width * 3 / 2;
	f->fmt.pix.colorspace	= V4L2_COLORSPACE_SRGB;
	PWC_DEBUG_IOCTL("pwc_vidioc_fill_fmt() width=%d, height=%d, bytesperline=%d, sizeimage=%d, pixelformat=%c%c%c%c\n",
			f->fmt.pix.width,
			f->fmt.pix.height,
			f->fmt.pix.bytesperline,
			f->fmt.pix.sizeimage,
			(f->fmt.pix.pixelक्रमmat)&255,
			(f->fmt.pix.pixelक्रमmat>>8)&255,
			(f->fmt.pix.pixelक्रमmat>>16)&255,
			(f->fmt.pix.pixelक्रमmat>>24)&255);
पूर्ण

/* ioctl(VIDIOC_TRY_FMT) */
अटल पूर्णांक pwc_vidioc_try_fmt(काष्ठा pwc_device *pdev, काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक size;

	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		PWC_DEBUG_IOCTL("Bad video type must be V4L2_BUF_TYPE_VIDEO_CAPTURE\n");
		वापस -EINVAL;
	पूर्ण

	चयन (f->fmt.pix.pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_YUV420:
			अवरोध;
		हाल V4L2_PIX_FMT_PWC1:
			अगर (DEVICE_USE_CODEC23(pdev->type)) अणु
				PWC_DEBUG_IOCTL("codec1 is only supported for old pwc webcam\n");
				f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV420;
			पूर्ण
			अवरोध;
		हाल V4L2_PIX_FMT_PWC2:
			अगर (DEVICE_USE_CODEC1(pdev->type)) अणु
				PWC_DEBUG_IOCTL("codec23 is only supported for new pwc webcam\n");
				f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV420;
			पूर्ण
			अवरोध;
		शेष:
			PWC_DEBUG_IOCTL("Unsupported pixel format\n");
			f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV420;
	पूर्ण

	size = pwc_get_size(pdev, f->fmt.pix.width, f->fmt.pix.height);
	pwc_vidioc_fill_fmt(f,
			    pwc_image_sizes[size][0],
			    pwc_image_sizes[size][1],
			    f->fmt.pix.pixelक्रमmat);

	वापस 0;
पूर्ण

/* ioctl(VIDIOC_SET_FMT) */

अटल पूर्णांक pwc_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);
	पूर्णांक ret, pixelक्रमmat, compression = 0;

	ret = pwc_vidioc_try_fmt(pdev, f);
	अगर (ret < 0)
		वापस ret;

	अगर (vb2_is_busy(&pdev->vb_queue))
		वापस -EBUSY;

	pixelक्रमmat = f->fmt.pix.pixelक्रमmat;

	PWC_DEBUG_IOCTL("Trying to set format to: width=%d height=%d fps=%d format=%c%c%c%c\n",
			f->fmt.pix.width, f->fmt.pix.height, pdev->vframes,
			(pixelक्रमmat)&255,
			(pixelक्रमmat>>8)&255,
			(pixelक्रमmat>>16)&255,
			(pixelक्रमmat>>24)&255);

	ret = pwc_set_video_mode(pdev, f->fmt.pix.width, f->fmt.pix.height,
				 pixelक्रमmat, 30, &compression, 0);

	PWC_DEBUG_IOCTL("pwc_set_video_mode(), return=%d\n", ret);

	pwc_vidioc_fill_fmt(f, pdev->width, pdev->height, pdev->pixfmt);
	वापस ret;
पूर्ण

अटल पूर्णांक pwc_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);

	strscpy(cap->driver, PWC_NAME, माप(cap->driver));
	strscpy(cap->card, pdev->vdev.name, माप(cap->card));
	usb_make_path(pdev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	अगर (i->index)	/* Only one INPUT is supported */
		वापस -EINVAL;

	strscpy(i->name, "Camera", माप(i->name));
	i->type = V4L2_INPUT_TYPE_CAMERA;
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक pwc_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा pwc_device *pdev =
		container_of(ctrl->handler, काष्ठा pwc_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		अगर (pdev->color_bal_valid &&
			(pdev->स्वतः_white_balance->val != awb_स्वतः ||
			 समय_beक्रमe(jअगरfies,
				pdev->last_color_bal_update + HZ / 4))) अणु
			pdev->red_balance->val  = pdev->last_red_balance;
			pdev->blue_balance->val = pdev->last_blue_balance;
			अवरोध;
		पूर्ण
		ret = pwc_get_u8_ctrl(pdev, GET_STATUS_CTL,
				      READ_RED_GAIN_FORMATTER,
				      &pdev->red_balance->val);
		अगर (ret)
			अवरोध;
		ret = pwc_get_u8_ctrl(pdev, GET_STATUS_CTL,
				      READ_BLUE_GAIN_FORMATTER,
				      &pdev->blue_balance->val);
		अगर (ret)
			अवरोध;
		pdev->last_red_balance  = pdev->red_balance->val;
		pdev->last_blue_balance = pdev->blue_balance->val;
		pdev->last_color_bal_update = jअगरfies;
		pdev->color_bal_valid = true;
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (pdev->gain_valid && समय_beक्रमe(jअगरfies,
				pdev->last_gain_update + HZ / 4)) अणु
			pdev->gain->val = pdev->last_gain;
			अवरोध;
		पूर्ण
		ret = pwc_get_u8_ctrl(pdev, GET_STATUS_CTL,
				      READ_AGC_FORMATTER, &pdev->gain->val);
		अगर (ret)
			अवरोध;
		pdev->last_gain = pdev->gain->val;
		pdev->last_gain_update = jअगरfies;
		pdev->gain_valid = true;
		अगर (!DEVICE_USE_CODEC3(pdev->type))
			अवरोध;
		/* For CODEC3 where स्वतःgain also controls expo */
		fallthrough;
	हाल V4L2_CID_EXPOSURE_AUTO:
		अगर (pdev->exposure_valid && समय_beक्रमe(jअगरfies,
				pdev->last_exposure_update + HZ / 4)) अणु
			pdev->exposure->val = pdev->last_exposure;
			अवरोध;
		पूर्ण
		ret = pwc_get_u16_ctrl(pdev, GET_STATUS_CTL,
				       READ_SHUTTER_FORMATTER,
				       &pdev->exposure->val);
		अगर (ret)
			अवरोध;
		pdev->last_exposure = pdev->exposure->val;
		pdev->last_exposure_update = jअगरfies;
		pdev->exposure_valid = true;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		PWC_ERROR("g_ctrl %s error %d\n", ctrl->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक pwc_set_awb(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक ret;

	अगर (pdev->स्वतः_white_balance->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      WB_MODE_FORMATTER,
				      pdev->स्वतः_white_balance->val);
		अगर (ret)
			वापस ret;

		अगर (pdev->स्वतः_white_balance->val != awb_manual)
			pdev->color_bal_valid = false; /* Force cache update */

		/*
		 * If this is a preset, update our red / blue balance values
		 * so that events get generated क्रम the new preset values
		 */
		अगर (pdev->स्वतः_white_balance->val == awb_inकरोor ||
		    pdev->स्वतः_white_balance->val == awb_outकरोor ||
		    pdev->स्वतः_white_balance->val == awb_fl)
			pwc_g_अस्थिर_ctrl(pdev->स्वतः_white_balance);
	पूर्ण
	अगर (pdev->स्वतः_white_balance->val != awb_manual)
		वापस 0;

	अगर (pdev->red_balance->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      PRESET_MANUAL_RED_GAIN_FORMATTER,
				      pdev->red_balance->val);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pdev->blue_balance->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      PRESET_MANUAL_BLUE_GAIN_FORMATTER,
				      pdev->blue_balance->val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* For CODEC2 models which have separate स्वतःgain and स्वतः exposure */
अटल पूर्णांक pwc_set_स्वतःgain(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक ret;

	अगर (pdev->स्वतःgain->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      AGC_MODE_FORMATTER,
				      pdev->स्वतःgain->val ? 0 : 0xff);
		अगर (ret)
			वापस ret;

		अगर (pdev->स्वतःgain->val)
			pdev->gain_valid = false; /* Force cache update */
	पूर्ण

	अगर (pdev->स्वतःgain->val)
		वापस 0;

	अगर (pdev->gain->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      PRESET_AGC_FORMATTER,
				      pdev->gain->val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* For CODEC2 models which have separate स्वतःgain and स्वतः exposure */
अटल पूर्णांक pwc_set_exposure_स्वतः(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक ret;
	पूर्णांक is_स्वतः = pdev->exposure_स्वतः->val == V4L2_EXPOSURE_AUTO;

	अगर (pdev->exposure_स्वतः->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      SHUTTER_MODE_FORMATTER,
				      is_स्वतः ? 0 : 0xff);
		अगर (ret)
			वापस ret;

		अगर (is_स्वतः)
			pdev->exposure_valid = false; /* Force cache update */
	पूर्ण

	अगर (is_स्वतः)
		वापस 0;

	अगर (pdev->exposure->is_new) अणु
		ret = pwc_set_u16_ctrl(pdev, SET_LUM_CTL,
				       PRESET_SHUTTER_FORMATTER,
				       pdev->exposure->val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* For CODEC3 models which have स्वतःgain controlling both gain and exposure */
अटल पूर्णांक pwc_set_स्वतःgain_expo(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक ret;

	अगर (pdev->स्वतःgain->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      AGC_MODE_FORMATTER,
				      pdev->स्वतःgain->val ? 0 : 0xff);
		अगर (ret)
			वापस ret;

		अगर (pdev->स्वतःgain->val) अणु
			pdev->gain_valid     = false; /* Force cache update */
			pdev->exposure_valid = false; /* Force cache update */
		पूर्ण
	पूर्ण

	अगर (pdev->स्वतःgain->val)
		वापस 0;

	अगर (pdev->gain->is_new) अणु
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      PRESET_AGC_FORMATTER,
				      pdev->gain->val);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pdev->exposure->is_new) अणु
		ret = pwc_set_u16_ctrl(pdev, SET_LUM_CTL,
				       PRESET_SHUTTER_FORMATTER,
				       pdev->exposure->val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_set_motor(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक ret;

	pdev->ctrl_buf[0] = 0;
	अगर (pdev->motor_pan_reset->is_new)
		pdev->ctrl_buf[0] |= 0x01;
	अगर (pdev->motor_tilt_reset->is_new)
		pdev->ctrl_buf[0] |= 0x02;
	अगर (pdev->motor_pan_reset->is_new || pdev->motor_tilt_reset->is_new) अणु
		ret = send_control_msg(pdev, SET_MPT_CTL,
				       PT_RESET_CONTROL_FORMATTER,
				       pdev->ctrl_buf, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	स_रखो(pdev->ctrl_buf, 0, 4);
	अगर (pdev->motor_pan->is_new) अणु
		pdev->ctrl_buf[0] = pdev->motor_pan->val & 0xFF;
		pdev->ctrl_buf[1] = (pdev->motor_pan->val >> 8);
	पूर्ण
	अगर (pdev->motor_tilt->is_new) अणु
		pdev->ctrl_buf[2] = pdev->motor_tilt->val & 0xFF;
		pdev->ctrl_buf[3] = (pdev->motor_tilt->val >> 8);
	पूर्ण
	अगर (pdev->motor_pan->is_new || pdev->motor_tilt->is_new) अणु
		ret = send_control_msg(pdev, SET_MPT_CTL,
				       PT_RELATIVE_CONTROL_FORMATTER,
				       pdev->ctrl_buf, 4);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा pwc_device *pdev =
		container_of(ctrl->handler, काष्ठा pwc_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      BRIGHTNESS_FORMATTER, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      CONTRAST_FORMATTER, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = pwc_set_s8_ctrl(pdev, SET_CHROM_CTL,
				      pdev->saturation_fmt, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAMMA:
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      GAMMA_FORMATTER, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = pwc_set_awb(pdev);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (DEVICE_USE_CODEC2(pdev->type))
			ret = pwc_set_स्वतःgain(pdev);
		अन्यथा अगर (DEVICE_USE_CODEC3(pdev->type))
			ret = pwc_set_स्वतःgain_expo(pdev);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		अगर (DEVICE_USE_CODEC2(pdev->type))
			ret = pwc_set_exposure_स्वतः(pdev);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल V4L2_CID_COLORFX:
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      COLOUR_MODE_FORMATTER,
				      ctrl->val ? 0 : 0xff);
		अवरोध;
	हाल PWC_CID_CUSTOM(स्वतःcontour):
		अगर (pdev->स्वतःcontour->is_new) अणु
			ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
					AUTO_CONTOUR_FORMATTER,
					pdev->स्वतःcontour->val ? 0 : 0xff);
		पूर्ण
		अगर (ret == 0 && pdev->contour->is_new) अणु
			ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
					      PRESET_CONTOUR_FORMATTER,
					      pdev->contour->val);
		पूर्ण
		अवरोध;
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      BACK_LIGHT_COMPENSATION_FORMATTER,
				      ctrl->val ? 0 : 0xff);
		अवरोध;
	हाल V4L2_CID_BAND_STOP_FILTER:
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      FLICKERLESS_MODE_FORMATTER,
				      ctrl->val ? 0 : 0xff);
		अवरोध;
	हाल PWC_CID_CUSTOM(noise_reduction):
		ret = pwc_set_u8_ctrl(pdev, SET_LUM_CTL,
				      DYNAMIC_NOISE_CONTROL_FORMATTER,
				      ctrl->val);
		अवरोध;
	हाल PWC_CID_CUSTOM(save_user):
		ret = pwc_button_ctrl(pdev, SAVE_USER_DEFAULTS_FORMATTER);
		अवरोध;
	हाल PWC_CID_CUSTOM(restore_user):
		ret = pwc_button_ctrl(pdev, RESTORE_USER_DEFAULTS_FORMATTER);
		अवरोध;
	हाल PWC_CID_CUSTOM(restore_factory):
		ret = pwc_button_ctrl(pdev,
				      RESTORE_FACTORY_DEFAULTS_FORMATTER);
		अवरोध;
	हाल PWC_CID_CUSTOM(awb_speed):
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      AWB_CONTROL_SPEED_FORMATTER,
				      ctrl->val);
		अवरोध;
	हाल PWC_CID_CUSTOM(awb_delay):
		ret = pwc_set_u8_ctrl(pdev, SET_CHROM_CTL,
				      AWB_CONTROL_DELAY_FORMATTER,
				      ctrl->val);
		अवरोध;
	हाल V4L2_CID_PAN_RELATIVE:
		ret = pwc_set_motor(pdev);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		PWC_ERROR("s_ctrl %s error %d\n", ctrl->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक pwc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);

	/* We only support two क्रमmat: the raw क्रमmat, and YUV */
	चयन (f->index) अणु
	हाल 0:
		/* RAW क्रमmat */
		f->pixelक्रमmat = pdev->type <= 646 ? V4L2_PIX_FMT_PWC1 : V4L2_PIX_FMT_PWC2;
		अवरोध;
	हाल 1:
		f->pixelक्रमmat = V4L2_PIX_FMT_YUV420;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);

	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	PWC_DEBUG_IOCTL("ioctl(VIDIOC_G_FMT) return size %dx%d\n",
			pdev->width, pdev->height);
	pwc_vidioc_fill_fmt(f, pdev->width, pdev->height, pdev->pixfmt);
	वापस 0;
पूर्ण

अटल पूर्णांक pwc_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);

	वापस pwc_vidioc_try_fmt(pdev, f);
पूर्ण

अटल पूर्णांक pwc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);
	अचिन्हित पूर्णांक i = 0, index = fsize->index;

	अगर (fsize->pixel_क्रमmat == V4L2_PIX_FMT_YUV420 ||
	    (fsize->pixel_क्रमmat == V4L2_PIX_FMT_PWC1 &&
			DEVICE_USE_CODEC1(pdev->type)) ||
	    (fsize->pixel_क्रमmat == V4L2_PIX_FMT_PWC2 &&
			DEVICE_USE_CODEC23(pdev->type))) अणु
		क्रम (i = 0; i < PSZ_MAX; i++) अणु
			अगर (!(pdev->image_mask & (1UL << i)))
				जारी;
			अगर (!index--) अणु
				fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
				fsize->discrete.width = pwc_image_sizes[i][0];
				fsize->discrete.height = pwc_image_sizes[i][1];
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pwc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);
	पूर्णांक size = -1;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PSZ_MAX; i++) अणु
		अगर (pwc_image_sizes[i][0] == fival->width &&
				pwc_image_sizes[i][1] == fival->height) अणु
			size = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* TODO: Support raw क्रमmat */
	अगर (size < 0 || fival->pixel_क्रमmat != V4L2_PIX_FMT_YUV420)
		वापस -EINVAL;

	i = pwc_get_fps(pdev, fival->index, size);
	अगर (!i)
		वापस -EINVAL;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete.numerator = 1;
	fival->discrete.denominator = i;

	वापस 0;
पूर्ण

अटल पूर्णांक pwc_g_parm(काष्ठा file *file, व्योम *fh,
		      काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	स_रखो(parm, 0, माप(*parm));

	parm->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	parm->parm.capture.पढ़ोbuffers = MIN_FRAMES;
	parm->parm.capture.capability |= V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe.denominator = pdev->vframes;
	parm->parm.capture.समयperframe.numerator = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pwc_s_parm(काष्ठा file *file, व्योम *fh,
		      काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा pwc_device *pdev = video_drvdata(file);
	पूर्णांक compression = 0;
	पूर्णांक ret, fps;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	/* If समयperframe == 0, then reset the framerate to the nominal value.
	   We pick a high framerate here, and let pwc_set_video_mode() figure
	   out the best match. */
	अगर (parm->parm.capture.समयperframe.numerator == 0 ||
	    parm->parm.capture.समयperframe.denominator == 0)
		fps = 30;
	अन्यथा
		fps = parm->parm.capture.समयperframe.denominator /
		      parm->parm.capture.समयperframe.numerator;

	अगर (vb2_is_busy(&pdev->vb_queue))
		वापस -EBUSY;

	ret = pwc_set_video_mode(pdev, pdev->width, pdev->height, pdev->pixfmt,
				 fps, &compression, 0);

	pwc_g_parm(file, fh, parm);

	वापस ret;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops pwc_ioctl_ops = अणु
	.vidioc_querycap		    = pwc_querycap,
	.vidioc_क्रमागत_input		    = pwc_क्रमागत_input,
	.vidioc_g_input			    = pwc_g_input,
	.vidioc_s_input			    = pwc_s_input,
	.vidioc_क्रमागत_fmt_vid_cap	    = pwc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		    = pwc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		    = pwc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		    = pwc_try_fmt_vid_cap,
	.vidioc_reqbufs			    = vb2_ioctl_reqbufs,
	.vidioc_querybuf		    = vb2_ioctl_querybuf,
	.vidioc_qbuf			    = vb2_ioctl_qbuf,
	.vidioc_dqbuf			    = vb2_ioctl_dqbuf,
	.vidioc_streamon		    = vb2_ioctl_streamon,
	.vidioc_streamoff		    = vb2_ioctl_streamoff,
	.vidioc_log_status		    = v4l2_ctrl_log_status,
	.vidioc_क्रमागत_framesizes		    = pwc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	    = pwc_क्रमागत_frameपूर्णांकervals,
	.vidioc_g_parm			    = pwc_g_parm,
	.vidioc_s_parm			    = pwc_s_parm,
	.vidioc_subscribe_event		    = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	    = v4l2_event_unsubscribe,
पूर्ण;
