<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* GSPCA subdrivers क्रम Genesys Logic webcams with the GL860 chip
 * Subdriver core
 *
 * 2009/09/24 Olivier Lorin <o.lorin@laposte.net>
 * GSPCA by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 * Thanks BUGabunकरो and Malmostoso क्रम your amazing help!
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "gspca.h"
#समावेश "gl860.h"

MODULE_AUTHOR("Olivier Lorin <o.lorin@laposte.net>");
MODULE_DESCRIPTION("Genesys Logic USB PC Camera Driver");
MODULE_LICENSE("GPL");

/*======================== अटल function declarations ====================*/

अटल व्योम (*dev_init_settings)(काष्ठा gspca_dev *gspca_dev);

अटल पूर्णांक  sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id);
अटल पूर्णांक  sd_init(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  sd_isoc_init(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  sd_start(काष्ठा gspca_dev *gspca_dev);
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev);
अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data, पूर्णांक len);
अटल व्योम sd_callback(काष्ठा gspca_dev *gspca_dev);

अटल पूर्णांक gl860_guess_sensor(काष्ठा gspca_dev *gspca_dev,
				u16 venकरोr_id, u16 product_id);

/*============================ driver options ==============================*/

अटल s32 AC50Hz = 0xff;
module_param(AC50Hz, पूर्णांक, 0644);
MODULE_PARM_DESC(AC50Hz, " Does AC power frequency is 50Hz? (0/1)");

अटल अक्षर sensor[7];
module_param_string(sensor, sensor, माप(sensor), 0644);
MODULE_PARM_DESC(sensor,
		" Driver sensor ('MI1320'/'MI2020'/'OV9655'/'OV2640')");

/*============================ webcam controls =============================*/

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		sd->vcur.brightness = ctrl->val;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		sd->vcur.contrast = ctrl->val;
		अवरोध;
	हाल V4L2_CID_SATURATION:
		sd->vcur.saturation = ctrl->val;
		अवरोध;
	हाल V4L2_CID_HUE:
		sd->vcur.hue = ctrl->val;
		अवरोध;
	हाल V4L2_CID_GAMMA:
		sd->vcur.gamma = ctrl->val;
		अवरोध;
	हाल V4L2_CID_HFLIP:
		sd->vcur.mirror = ctrl->val;
		अवरोध;
	हाल V4L2_CID_VFLIP:
		sd->vcur.flip = ctrl->val;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		sd->vcur.AC50Hz = ctrl->val;
		अवरोध;
	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		sd->vcur.whitebal = ctrl->val;
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		sd->vcur.sharpness = ctrl->val;
		अवरोध;
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:
		sd->vcur.backlight = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (gspca_dev->streaming)
		sd->रुकोSet = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 11);

	अगर (sd->vmax.brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_BRIGHTNESS,
				  0, sd->vmax.brightness, 1,
				  sd->vcur.brightness);

	अगर (sd->vmax.contrast)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_CONTRAST,
				  0, sd->vmax.contrast, 1,
				  sd->vcur.contrast);

	अगर (sd->vmax.saturation)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_SATURATION,
				  0, sd->vmax.saturation, 1,
				  sd->vcur.saturation);

	अगर (sd->vmax.hue)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_HUE,
				  0, sd->vmax.hue, 1, sd->vcur.hue);

	अगर (sd->vmax.gamma)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_GAMMA,
				  0, sd->vmax.gamma, 1, sd->vcur.gamma);

	अगर (sd->vmax.mirror)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_HFLIP,
				  0, sd->vmax.mirror, 1, sd->vcur.mirror);

	अगर (sd->vmax.flip)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_VFLIP,
				  0, sd->vmax.flip, 1, sd->vcur.flip);

	अगर (sd->vmax.AC50Hz)
		v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
				  V4L2_CID_POWER_LINE_FREQUENCY,
				  sd->vmax.AC50Hz, 0, sd->vcur.AC50Hz);

	अगर (sd->vmax.whitebal)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				  V4L2_CID_WHITE_BALANCE_TEMPERATURE,
				  0, sd->vmax.whitebal, 1, sd->vcur.whitebal);

	अगर (sd->vmax.sharpness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_SHARPNESS,
				  0, sd->vmax.sharpness, 1,
				  sd->vcur.sharpness);

	अगर (sd->vmax.backlight)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				  V4L2_CID_BACKLIGHT_COMPENSATION,
				  0, sd->vmax.backlight, 1,
				  sd->vcur.backlight);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	वापस 0;
पूर्ण

/*==================== sud-driver काष्ठाure initialisation =================*/

अटल स्थिर काष्ठा sd_desc sd_desc_mi1320 = अणु
	.name        = MODULE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init   = sd_isoc_init,
	.start       = sd_start,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_callback = sd_callback,
पूर्ण;

अटल स्थिर काष्ठा sd_desc sd_desc_mi2020 = अणु
	.name        = MODULE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init   = sd_isoc_init,
	.start       = sd_start,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_callback = sd_callback,
पूर्ण;

अटल स्थिर काष्ठा sd_desc sd_desc_ov2640 = अणु
	.name        = MODULE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init   = sd_isoc_init,
	.start       = sd_start,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_callback = sd_callback,
पूर्ण;

अटल स्थिर काष्ठा sd_desc sd_desc_ov9655 = अणु
	.name        = MODULE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init   = sd_isoc_init,
	.start       = sd_start,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_callback = sd_callback,
पूर्ण;

/*=========================== sub-driver image sizes =======================*/

अटल काष्ठा v4l2_pix_क्रमmat mi2020_mode[] = अणु
	अणु 640,  480, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
	अणु 800,  598, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 598,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण,
	अणु1280, 1024, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 1024,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2
	पूर्ण,
	अणु1600, 1198, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1198,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3
	पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat ov2640_mode[] = अणु
	अणु 640,  480, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
	अणु 800,  600, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण,
	अणु1280,  960, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2
	पूर्ण,
	अणु1600, 1200, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1200,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3
	पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat mi1320_mode[] = अणु
	अणु 640,  480, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
	अणु 800,  600, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण,
	अणु1280,  960, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2
	पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat ov9655_mode[] = अणु
	अणु 640,  480, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
	अणु1280,  960, V4L2_PIX_FMT_SGBRG8, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण,
पूर्ण;

/*========================= sud-driver functions ===========================*/

/* This function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;
	u16 venकरोr_id, product_id;

	/* Get USB VenकरोrID and ProductID */
	venकरोr_id  = id->idVenकरोr;
	product_id = id->idProduct;

	sd->nbRightUp = 1;
	sd->nbIm = -1;

	sd->sensor = 0xff;
	अगर (म_भेद(sensor, "MI1320") == 0)
		sd->sensor = ID_MI1320;
	अन्यथा अगर (म_भेद(sensor, "OV2640") == 0)
		sd->sensor = ID_OV2640;
	अन्यथा अगर (म_भेद(sensor, "OV9655") == 0)
		sd->sensor = ID_OV9655;
	अन्यथा अगर (म_भेद(sensor, "MI2020") == 0)
		sd->sensor = ID_MI2020;

	/* Get sensor and set the suitable init/start/../stop functions */
	अगर (gl860_guess_sensor(gspca_dev, venकरोr_id, product_id) == -1)
		वापस -1;

	cam = &gspca_dev->cam;

	चयन (sd->sensor) अणु
	हाल ID_MI1320:
		gspca_dev->sd_desc = &sd_desc_mi1320;
		cam->cam_mode = mi1320_mode;
		cam->nmodes = ARRAY_SIZE(mi1320_mode);
		dev_init_settings   = mi1320_init_settings;
		अवरोध;

	हाल ID_MI2020:
		gspca_dev->sd_desc = &sd_desc_mi2020;
		cam->cam_mode = mi2020_mode;
		cam->nmodes = ARRAY_SIZE(mi2020_mode);
		dev_init_settings   = mi2020_init_settings;
		अवरोध;

	हाल ID_OV2640:
		gspca_dev->sd_desc = &sd_desc_ov2640;
		cam->cam_mode = ov2640_mode;
		cam->nmodes = ARRAY_SIZE(ov2640_mode);
		dev_init_settings   = ov2640_init_settings;
		अवरोध;

	हाल ID_OV9655:
		gspca_dev->sd_desc = &sd_desc_ov9655;
		cam->cam_mode = ov9655_mode;
		cam->nmodes = ARRAY_SIZE(ov9655_mode);
		dev_init_settings   = ov9655_init_settings;
		अवरोध;
	पूर्ण

	dev_init_settings(gspca_dev);
	अगर (AC50Hz != 0xff)
		((काष्ठा sd *) gspca_dev)->vcur.AC50Hz = AC50Hz;

	वापस 0;
पूर्ण

/* This function is called at probe समय after sd_config */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस sd->dev_init_at_startup(gspca_dev);
पूर्ण

/* This function is called beक्रमe to choose the alt setting */
अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस sd->dev_configure_alt(gspca_dev);
पूर्ण

/* This function is called to start the webcam */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस sd->dev_init_pre_alt(gspca_dev);
पूर्ण

/* This function is called to stop the webcam */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!sd->gspca_dev.present)
		वापस;

	वापस sd->dev_post_unset_alt(gspca_dev);
पूर्ण

/* This function is called when an image is being received */
अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल s32 nSkipped;

	s32 mode = (s32) gspca_dev->curr_mode;
	s32 nToSkip =
		sd->swapRB * (gspca_dev->cam.cam_mode[mode].bytesperline + 1);

	/* Test only against 0202h, so endianness करोes not matter */
	चयन (*(s16 *) data) अणु
	हाल 0x0202:		/* End of frame, start a new one */
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
		nSkipped = 0;
		अगर (sd->nbIm >= 0 && sd->nbIm < 10)
			sd->nbIm++;
		gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
		अवरोध;

	शेष:
		data += 2;
		len  -= 2;
		अगर (nSkipped + len <= nToSkip)
			nSkipped += len;
		अन्यथा अणु
			अगर (nSkipped < nToSkip && nSkipped + len > nToSkip) अणु
				data += nToSkip - nSkipped;
				len  -= nToSkip - nSkipped;
				nSkipped = nToSkip + 1;
			पूर्ण
			gspca_frame_add(gspca_dev,
				INTER_PACKET, data, len);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* This function is called when an image has been पढ़ो */
/* This function is used to monitor webcam orientation */
अटल व्योम sd_callback(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!_OV9655_) अणु
		u8 state;
		u8 upsideDown;

		/* Probe sensor orientation */
		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, (व्योम *)&state);

		/* C8/40 means upside-करोwn (looking backwards) */
		/* D8/50 means right-up (looking onwards) */
		upsideDown = (state == 0xc8 || state == 0x40);

		अगर (upsideDown && sd->nbRightUp > -4) अणु
			अगर (sd->nbRightUp > 0)
				sd->nbRightUp = 0;
			अगर (sd->nbRightUp == -3) अणु
				sd->mirrorMask = 1;
				sd->रुकोSet = 1;
			पूर्ण
			sd->nbRightUp--;
		पूर्ण
		अगर (!upsideDown && sd->nbRightUp < 4) अणु
			अगर (sd->nbRightUp  < 0)
				sd->nbRightUp = 0;
			अगर (sd->nbRightUp == 3) अणु
				sd->mirrorMask = 0;
				sd->रुकोSet = 1;
			पूर्ण
			sd->nbRightUp++;
		पूर्ण
	पूर्ण

	अगर (sd->रुकोSet)
		sd->dev_camera_settings(gspca_dev);
पूर्ण

/*=================== USB driver काष्ठाure initialisation ==================*/

अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x05e3, 0x0503)पूर्ण,
	अणुUSB_DEVICE(0x05e3, 0xf191)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id,
			&sd_desc_mi1320, माप(काष्ठा sd), THIS_MODULE);
पूर्ण

अटल व्योम sd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	gspca_disconnect(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect = sd_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend    = gspca_suspend,
	.resume     = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

/*====================== Init and Exit module functions ====================*/

module_usb_driver(sd_driver);

/*==========================================================================*/

पूर्णांक gl860_RTx(काष्ठा gspca_dev *gspca_dev,
		अचिन्हित अक्षर pref, u32 req, u16 val, u16 index,
		s32 len, व्योम *pdata)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	s32 r = 0;

	अगर (pref == 0x40) अणु /* Send */
		अगर (len > 0) अणु
			स_नकल(gspca_dev->usb_buf, pdata, len);
			r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
					req, pref, val, index,
					gspca_dev->usb_buf,
					len, 400 + 200 * (len > 1));
		पूर्ण अन्यथा अणु
			r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
					req, pref, val, index, शून्य, len, 400);
		पूर्ण
	पूर्ण अन्यथा अणु /* Receive */
		अगर (len > 0) अणु
			r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
					req, pref, val, index,
					gspca_dev->usb_buf,
					len, 400 + 200 * (len > 1));
			स_नकल(pdata, gspca_dev->usb_buf, len);
		पूर्ण अन्यथा अणु
			r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
					req, pref, val, index, शून्य, len, 400);
		पूर्ण
	पूर्ण

	अगर (r < 0)
		pr_err("ctrl transfer failed %4d [p%02x r%d v%04x i%04x len%d]\n",
		       r, pref, req, val, index, len);
	अन्यथा अगर (len > 1 && r < len)
		gspca_err(gspca_dev, "short ctrl transfer %d/%d\n", r, len);

	msleep(1);

	वापस r;
पूर्ण

पूर्णांक fetch_validx(काष्ठा gspca_dev *gspca_dev, काष्ठा validx *tbl, पूर्णांक len)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < len; n++) अणु
		अगर (tbl[n].idx != 0xffff)
			ctrl_out(gspca_dev, 0x40, 1, tbl[n].val,
					tbl[n].idx, 0, शून्य);
		अन्यथा अगर (tbl[n].val == 0xffff)
			अवरोध;
		अन्यथा
			msleep(tbl[n].val);
	पूर्ण
	वापस n;
पूर्ण

पूर्णांक keep_on_fetching_validx(काष्ठा gspca_dev *gspca_dev, काष्ठा validx *tbl,
				पूर्णांक len, पूर्णांक n)
अणु
	जबतक (++n < len) अणु
		अगर (tbl[n].idx != 0xffff)
			ctrl_out(gspca_dev, 0x40, 1, tbl[n].val, tbl[n].idx,
					0, शून्य);
		अन्यथा अगर (tbl[n].val == 0xffff)
			अवरोध;
		अन्यथा
			msleep(tbl[n].val);
	पूर्ण
	वापस n;
पूर्ण

व्योम fetch_idxdata(काष्ठा gspca_dev *gspca_dev, काष्ठा idxdata *tbl, पूर्णांक len)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < len; n++) अणु
		अगर (स_भेद(tbl[n].data, "\xff\xff\xff", 3) != 0)
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, tbl[n].idx,
					3, tbl[n].data);
		अन्यथा
			msleep(tbl[n].idx);
	पूर्ण
पूर्ण

अटल पूर्णांक gl860_guess_sensor(काष्ठा gspca_dev *gspca_dev,
				u16 venकरोr_id, u16 product_id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 probe, nb26, nb96, nOV, ntry;

	अगर (product_id == 0xf191)
		sd->sensor = ID_MI1320;

	अगर (sd->sensor == 0xff) अणु
		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &probe);
		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &probe);

		ctrl_out(gspca_dev, 0x40, 1, 0x0000, 0x0000, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x0010, 0x0010, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x0008, 0x00c0, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x0001, 0x00c1, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x0001, 0x00c2, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x0020, 0x0006, 0, शून्य);
		msleep(3);
		ctrl_out(gspca_dev, 0x40, 1, 0x006a, 0x000d, 0, शून्य);
		msleep(56);

		gspca_dbg(gspca_dev, D_PROBE, "probing for sensor MI2020 or OVXXXX\n");
		nOV = 0;
		क्रम (ntry = 0; ntry < 4; ntry++) अणु
			ctrl_out(gspca_dev, 0x40, 1, 0x0040, 0x0000, 0, शून्य);
			msleep(3);
			ctrl_out(gspca_dev, 0x40, 1, 0x0063, 0x0006, 0, शून्य);
			msleep(3);
			ctrl_out(gspca_dev, 0x40, 1, 0x7a00, 0x8030, 0, शून्य);
			msleep(10);
			ctrl_in(gspca_dev, 0xc0, 2, 0x7a00, 0x8030, 1, &probe);
			gspca_dbg(gspca_dev, D_PROBE, "probe=0x%02x\n", probe);
			अगर (probe == 0xff)
				nOV++;
		पूर्ण

		अगर (nOV) अणु
			gspca_dbg(gspca_dev, D_PROBE, "0xff -> OVXXXX\n");
			gspca_dbg(gspca_dev, D_PROBE, "probing for sensor OV2640 or OV9655");

			nb26 = nb96 = 0;
			क्रम (ntry = 0; ntry < 4; ntry++) अणु
				ctrl_out(gspca_dev, 0x40, 1, 0x0040, 0x0000,
						0, शून्य);
				msleep(3);
				ctrl_out(gspca_dev, 0x40, 1, 0x6000, 0x800a,
						0, शून्य);
				msleep(10);

				/* Wait क्रम 26(OV2640) or 96(OV9655) */
				ctrl_in(gspca_dev, 0xc0, 2, 0x6000, 0x800a,
						1, &probe);

				अगर (probe == 0x26 || probe == 0x40) अणु
					gspca_dbg(gspca_dev, D_PROBE,
						  "probe=0x%02x -> OV2640\n",
						  probe);
					sd->sensor = ID_OV2640;
					nb26 += 4;
					अवरोध;
				पूर्ण
				अगर (probe == 0x96 || probe == 0x55) अणु
					gspca_dbg(gspca_dev, D_PROBE,
						  "probe=0x%02x -> OV9655\n",
						  probe);
					sd->sensor = ID_OV9655;
					nb96 += 4;
					अवरोध;
				पूर्ण
				gspca_dbg(gspca_dev, D_PROBE, "probe=0x%02x\n",
					  probe);
				अगर (probe == 0x00)
					nb26++;
				अगर (probe == 0xff)
					nb96++;
				msleep(3);
			पूर्ण
			अगर (nb26 < 4 && nb96 < 4)
				वापस -1;
		पूर्ण अन्यथा अणु
			gspca_dbg(gspca_dev, D_PROBE, "Not any 0xff -> MI2020\n");
			sd->sensor = ID_MI2020;
		पूर्ण
	पूर्ण

	अगर (_MI1320_) अणु
		gspca_dbg(gspca_dev, D_PROBE, "05e3:f191 sensor MI1320 (1.3M)\n");
	पूर्ण अन्यथा अगर (_MI2020_) अणु
		gspca_dbg(gspca_dev, D_PROBE, "05e3:0503 sensor MI2020 (2.0M)\n");
	पूर्ण अन्यथा अगर (_OV9655_) अणु
		gspca_dbg(gspca_dev, D_PROBE, "05e3:0503 sensor OV9655 (1.3M)\n");
	पूर्ण अन्यथा अगर (_OV2640_) अणु
		gspca_dbg(gspca_dev, D_PROBE, "05e3:0503 sensor OV2640 (2.0M)\n");
	पूर्ण अन्यथा अणु
		gspca_dbg(gspca_dev, D_PROBE, "***** Unknown sensor *****\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
