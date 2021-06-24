<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 * Copyright (c) 2008 Erik Andrथऊn
 *
 * P/N 861037:      Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensor Photobit PB100  ASIC STV0600-1 - QuickCam Express
 * P/N 861055:      Sensor ST VV6410       ASIC STV0610   - LEGO cam
 * P/N 861075-0040: Sensor HDCS1000        ASIC
 * P/N 961179-0700: Sensor ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensor ST VV6410       ASIC STV0610   - QuickCam Web
 */

/*
 * The spec file क्रम the PB-0100 suggests the following क्रम best quality
 * images after the sensor has been reset :
 *
 * PB_ADCGAINL      = R60 = 0x03 (3 dec)      : sets low reference of ADC
						to produce good black level
 * PB_PREADCTRL     = R32 = 0x1400 (5120 dec) : Enables global gain changes
						through R53
 * PB_ADCMINGAIN    = R52 = 0x10 (16 dec)     : Sets the minimum gain क्रम
						स्वतः-exposure
 * PB_ADCGLOBALGAIN = R53 = 0x10 (16 dec)     : Sets the global gain
 * PB_EXPGAIN       = R14 = 0x11 (17 dec)     : Sets the स्वतः-exposure value
 * PB_UPDATEINT     = R23 = 0x02 (2 dec)      : Sets the speed on
						स्वतः-exposure routine
 * PB_CFILLIN       = R5  = 0x0E (14 dec)     : Sets the frame rate
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "stv06xx_pb0100.h"

काष्ठा pb0100_ctrls अणु
	काष्ठा अणु /* one big happy control cluster... */
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *gain;
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *red;
		काष्ठा v4l2_ctrl *blue;
		काष्ठा v4l2_ctrl *natural;
	पूर्ण;
	काष्ठा v4l2_ctrl *target;
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat pb0100_mode[] = अणु
/* low res / subsample modes disabled as they are only half res horizontal,
   halving the vertical resolution करोes not seem to work */
	अणु
		320,
		240,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage = 320 * 240,
		.bytesperline = 320,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = PB0100_CROP_TO_VGA
	पूर्ण,
	अणु
		352,
		288,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage = 352 * 288,
		.bytesperline = 352,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण
पूर्ण;

अटल पूर्णांक pb0100_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा pb0100_ctrls *ctrls = sd->sensor_priv;
	पूर्णांक err = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		err = pb0100_set_स्वतःgain(gspca_dev, ctrl->val);
		अगर (err)
			अवरोध;
		अगर (ctrl->val)
			अवरोध;
		err = pb0100_set_gain(gspca_dev, ctrls->gain->val);
		अगर (err)
			अवरोध;
		err = pb0100_set_exposure(gspca_dev, ctrls->exposure->val);
		अवरोध;
	हाल V4L2_CTRL_CLASS_USER + 0x1001:
		err = pb0100_set_स्वतःgain_target(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops pb0100_ctrl_ops = अणु
	.s_ctrl = pb0100_s_ctrl,
पूर्ण;

अटल पूर्णांक pb0100_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;
	काष्ठा pb0100_ctrls *ctrls;
	अटल स्थिर काष्ठा v4l2_ctrl_config स्वतःgain_target = अणु
		.ops = &pb0100_ctrl_ops,
		.id = V4L2_CTRL_CLASS_USER + 0x1000,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Automatic Gain Target",
		.max = 255,
		.step = 1,
		.def = 128,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_ctrl_config natural_light = अणु
		.ops = &pb0100_ctrl_ops,
		.id = V4L2_CTRL_CLASS_USER + 0x1001,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Natural Light Source",
		.max = 1,
		.step = 1,
		.def = 1,
	पूर्ण;

	ctrls = kzalloc(माप(*ctrls), GFP_KERNEL);
	अगर (!ctrls)
		वापस -ENOMEM;

	v4l2_ctrl_handler_init(hdl, 6);
	ctrls->स्वतःgain = v4l2_ctrl_new_std(hdl, &pb0100_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	ctrls->exposure = v4l2_ctrl_new_std(hdl, &pb0100_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 511, 1, 12);
	ctrls->gain = v4l2_ctrl_new_std(hdl, &pb0100_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 128);
	ctrls->red = v4l2_ctrl_new_std(hdl, &pb0100_ctrl_ops,
			V4L2_CID_RED_BALANCE, -255, 255, 1, 0);
	ctrls->blue = v4l2_ctrl_new_std(hdl, &pb0100_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, -255, 255, 1, 0);
	ctrls->natural = v4l2_ctrl_new_custom(hdl, &natural_light, शून्य);
	ctrls->target = v4l2_ctrl_new_custom(hdl, &स्वतःgain_target, शून्य);
	अगर (hdl->error) अणु
		kमुक्त(ctrls);
		वापस hdl->error;
	पूर्ण
	sd->sensor_priv = ctrls;
	v4l2_ctrl_स्वतः_cluster(5, &ctrls->स्वतःgain, 0, false);
	वापस 0;
पूर्ण

अटल पूर्णांक pb0100_probe(काष्ठा sd *sd)
अणु
	u16 sensor;
	पूर्णांक err;

	err = stv06xx_पढ़ो_sensor(sd, PB_IDENT, &sensor);

	अगर (err < 0)
		वापस -ENODEV;
	अगर ((sensor >> 8) != 0x64)
		वापस -ENODEV;

	pr_info("Photobit pb0100 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = pb0100_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(pb0100_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक pb0100_start(काष्ठा sd *sd)
अणु
	पूर्णांक err, packet_size, max_packet_size;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा cam *cam = &sd->gspca_dev.cam;
	u32 mode = cam->cam_mode[sd->gspca_dev.curr_mode].priv;

	पूर्णांकf = usb_अगरnum_to_अगर(sd->gspca_dev.dev, sd->gspca_dev.अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, sd->gspca_dev.alt);
	अगर (!alt)
		वापस -ENODEV;

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);

	/* If we करोn't have enough bandwidth use a lower framerate */
	max_packet_size = sd->sensor->max_packet_size[sd->gspca_dev.curr_mode];
	अगर (packet_size < max_packet_size)
		stv06xx_ग_लिखो_sensor(sd, PB_ROWSPEED, BIT(4)|BIT(3)|BIT(1));
	अन्यथा
		stv06xx_ग_लिखो_sensor(sd, PB_ROWSPEED, BIT(5)|BIT(3)|BIT(1));

	/* Setup sensor winकरोw */
	अगर (mode & PB0100_CROP_TO_VGA) अणु
		stv06xx_ग_लिखो_sensor(sd, PB_RSTART, 30);
		stv06xx_ग_लिखो_sensor(sd, PB_CSTART, 20);
		stv06xx_ग_लिखो_sensor(sd, PB_RWSIZE, 240 - 1);
		stv06xx_ग_लिखो_sensor(sd, PB_CWSIZE, 320 - 1);
	पूर्ण अन्यथा अणु
		stv06xx_ग_लिखो_sensor(sd, PB_RSTART, 8);
		stv06xx_ग_लिखो_sensor(sd, PB_CSTART, 4);
		stv06xx_ग_लिखो_sensor(sd, PB_RWSIZE, 288 - 1);
		stv06xx_ग_लिखो_sensor(sd, PB_CWSIZE, 352 - 1);
	पूर्ण

	अगर (mode & PB0100_SUBSAMPLE) अणु
		stv06xx_ग_लिखो_bridge(sd, STV_Y_CTRL, 0x02); /* Wrong, FIXME */
		stv06xx_ग_लिखो_bridge(sd, STV_X_CTRL, 0x06);

		stv06xx_ग_लिखो_bridge(sd, STV_SCAN_RATE, 0x10);
	पूर्ण अन्यथा अणु
		stv06xx_ग_लिखो_bridge(sd, STV_Y_CTRL, 0x01);
		stv06xx_ग_लिखो_bridge(sd, STV_X_CTRL, 0x0a);
		/* larger -> slower */
		stv06xx_ग_लिखो_bridge(sd, STV_SCAN_RATE, 0x20);
	पूर्ण

	err = stv06xx_ग_लिखो_sensor(sd, PB_CONTROL, BIT(5)|BIT(3)|BIT(1));
	gspca_dbg(gspca_dev, D_STREAM, "Started stream, status: %d\n", err);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक pb0100_stop(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक err;

	err = stv06xx_ग_लिखो_sensor(sd, PB_ABORTFRAME, 1);

	अगर (err < 0)
		जाओ out;

	/* Set bit 1 to zero */
	err = stv06xx_ग_लिखो_sensor(sd, PB_CONTROL, BIT(5)|BIT(3));

	gspca_dbg(gspca_dev, D_STREAM, "Halting stream\n");
out:
	वापस (err < 0) ? err : 0;
पूर्ण

/* FIXME: Sort the init commands out and put them पूर्णांकo tables,
	  this is only क्रम getting the camera to work */
/* FIXME: No error handling क्रम now,
	  add this once the init has been converted to proper tables */
अटल पूर्णांक pb0100_init(काष्ठा sd *sd)
अणु
	stv06xx_ग_लिखो_bridge(sd, STV_REG00, 1);
	stv06xx_ग_लिखो_bridge(sd, STV_SCAN_RATE, 0);

	/* Reset sensor */
	stv06xx_ग_लिखो_sensor(sd, PB_RESET, 1);
	stv06xx_ग_लिखो_sensor(sd, PB_RESET, 0);

	/* Disable chip */
	stv06xx_ग_लिखो_sensor(sd, PB_CONTROL, BIT(5)|BIT(3));

	/* Gain stuff...*/
	stv06xx_ग_लिखो_sensor(sd, PB_PREADCTRL, BIT(12)|BIT(10)|BIT(6));
	stv06xx_ग_लिखो_sensor(sd, PB_ADCGLOBALGAIN, 12);

	/* Set up स्वतः-exposure */
	/* ADC VREF_HI new setting क्रम a transition
	  from the Expose1 to the Expose2 setting */
	stv06xx_ग_लिखो_sensor(sd, PB_R28, 12);
	/* gain max क्रम स्वतःexposure */
	stv06xx_ग_लिखो_sensor(sd, PB_ADCMAXGAIN, 180);
	/* gain min क्रम स्वतःexposure  */
	stv06xx_ग_लिखो_sensor(sd, PB_ADCMINGAIN, 12);
	/* Maximum frame पूर्णांकegration समय (programmed पूर्णांकo R8)
	   allowed क्रम स्वतः-exposure routine */
	stv06xx_ग_लिखो_sensor(sd, PB_R54, 3);
	/* Minimum frame पूर्णांकegration समय (programmed पूर्णांकo R8)
	   allowed क्रम स्वतः-exposure routine */
	stv06xx_ग_लिखो_sensor(sd, PB_R55, 0);
	stv06xx_ग_लिखो_sensor(sd, PB_UPDATEINT, 1);
	/* R15  Expose0 (maximum that स्वतः-exposure may use) */
	stv06xx_ग_लिखो_sensor(sd, PB_R15, 800);
	/* R17  Expose2 (minimum that स्वतः-exposure may use) */
	stv06xx_ग_लिखो_sensor(sd, PB_R17, 10);

	stv06xx_ग_लिखो_sensor(sd, PB_EXPGAIN, 0);

	/* 0x14 */
	stv06xx_ग_लिखो_sensor(sd, PB_VOFFSET, 0);
	/* 0x0D */
	stv06xx_ग_लिखो_sensor(sd, PB_ADCGAINH, 11);
	/* Set black level (important!) */
	stv06xx_ग_लिखो_sensor(sd, PB_ADCGAINL, 0);

	/* ??? */
	stv06xx_ग_लिखो_bridge(sd, STV_REG00, 0x11);
	stv06xx_ग_लिखो_bridge(sd, STV_REG03, 0x45);
	stv06xx_ग_लिखो_bridge(sd, STV_REG04, 0x07);

	/* Scan/timing क्रम the sensor */
	stv06xx_ग_लिखो_sensor(sd, PB_ROWSPEED, BIT(4)|BIT(3)|BIT(1));
	stv06xx_ग_लिखो_sensor(sd, PB_CFILLIN, 14);
	stv06xx_ग_लिखो_sensor(sd, PB_VBL, 0);
	stv06xx_ग_लिखो_sensor(sd, PB_FINTTIME, 0);
	stv06xx_ग_लिखो_sensor(sd, PB_RINTTIME, 123);

	stv06xx_ग_लिखो_bridge(sd, STV_REG01, 0xc2);
	stv06xx_ग_लिखो_bridge(sd, STV_REG02, 0xb0);
	वापस 0;
पूर्ण

अटल पूर्णांक pb0100_dump(काष्ठा sd *sd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pb0100_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा pb0100_ctrls *ctrls = sd->sensor_priv;

	err = stv06xx_ग_लिखो_sensor(sd, PB_G1GAIN, val);
	अगर (!err)
		err = stv06xx_ग_लिखो_sensor(sd, PB_G2GAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set green gain to %d, status: %d\n",
		  val, err);

	अगर (!err)
		err = pb0100_set_red_balance(gspca_dev, ctrls->red->val);
	अगर (!err)
		err = pb0100_set_blue_balance(gspca_dev, ctrls->blue->val);

	वापस err;
पूर्ण

अटल पूर्णांक pb0100_set_red_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा pb0100_ctrls *ctrls = sd->sensor_priv;

	val += ctrls->gain->val;
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 255)
		val = 255;

	err = stv06xx_ग_लिखो_sensor(sd, PB_RGAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set red gain to %d, status: %d\n",
		  val, err);

	वापस err;
पूर्ण

अटल पूर्णांक pb0100_set_blue_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा pb0100_ctrls *ctrls = sd->sensor_priv;

	val += ctrls->gain->val;
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 255)
		val = 255;

	err = stv06xx_ग_लिखो_sensor(sd, PB_BGAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set blue gain to %d, status: %d\n",
		  val, err);

	वापस err;
पूर्ण

अटल पूर्णांक pb0100_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	err = stv06xx_ग_लिखो_sensor(sd, PB_RINTTIME, val);
	gspca_dbg(gspca_dev, D_CONF, "Set exposure to %d, status: %d\n",
		  val, err);

	वापस err;
पूर्ण

अटल पूर्णांक pb0100_set_स्वतःgain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा pb0100_ctrls *ctrls = sd->sensor_priv;

	अगर (val) अणु
		अगर (ctrls->natural->val)
			val = BIT(6)|BIT(4)|BIT(0);
		अन्यथा
			val = BIT(4)|BIT(0);
	पूर्ण अन्यथा
		val = 0;

	err = stv06xx_ग_लिखो_sensor(sd, PB_EXPGAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set autogain to %d (natural: %d), status: %d\n",
		  val, ctrls->natural->val, err);

	वापस err;
पूर्ण

अटल पूर्णांक pb0100_set_स्वतःgain_target(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err, totalpixels, brightpixels, darkpixels;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Number of pixels counted by the sensor when subsampling the pixels.
	 * Slightly larger than the real value to aव्योम oscillation */
	totalpixels = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	totalpixels = totalpixels/(8*8) + totalpixels/(64*64);

	brightpixels = (totalpixels * val) >> 8;
	darkpixels   = totalpixels - brightpixels;
	err = stv06xx_ग_लिखो_sensor(sd, PB_R21, brightpixels);
	अगर (!err)
		err = stv06xx_ग_लिखो_sensor(sd, PB_R22, darkpixels);

	gspca_dbg(gspca_dev, D_CONF, "Set autogain target to %d, status: %d\n",
		  val, err);

	वापस err;
पूर्ण
