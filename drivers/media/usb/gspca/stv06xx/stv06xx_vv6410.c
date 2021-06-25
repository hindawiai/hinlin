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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "stv06xx_vv6410.h"

अटल काष्ठा v4l2_pix_क्रमmat vv6410_mode[] = अणु
	अणु
		356,
		292,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage = 356 * 292,
		.bytesperline = 356,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण
पूर्ण;

अटल पूर्णांक vv6410_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	पूर्णांक err = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		अगर (!gspca_dev->streaming)
			वापस 0;
		err = vv6410_set_hflip(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		अगर (!gspca_dev->streaming)
			वापस 0;
		err = vv6410_set_vflip(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = vv6410_set_analog_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		err = vv6410_set_exposure(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vv6410_ctrl_ops = अणु
	.s_ctrl = vv6410_s_ctrl,
पूर्ण;

अटल पूर्णांक vv6410_probe(काष्ठा sd *sd)
अणु
	u16 data;
	पूर्णांक err;

	err = stv06xx_पढ़ो_sensor(sd, VV6410_DEVICEH, &data);
	अगर (err < 0)
		वापस -ENODEV;

	अगर (data != 0x19)
		वापस -ENODEV;

	pr_info("vv6410 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = vv6410_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(vv6410_mode);
	वापस 0;
पूर्ण

अटल पूर्णांक vv6410_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	v4l2_ctrl_handler_init(hdl, 2);
	/* Disable the hardware VFLIP and HFLIP as we currently lack a
	   mechanism to adjust the image offset in such a way that
	   we करोn't need to renegotiate the announced क्रमmat */
	/* v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops, */
	/*		V4L2_CID_HFLIP, 0, 1, 1, 0); */
	/* v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops, */
	/*		V4L2_CID_VFLIP, 0, 1, 1, 0); */
	v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 32768, 1, 20000);
	v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops,
			V4L2_CID_GAIN, 0, 15, 1, 10);
	वापस hdl->error;
पूर्ण

अटल पूर्णांक vv6410_init(काष्ठा sd *sd)
अणु
	पूर्णांक err = 0, i;

	क्रम (i = 0; i < ARRAY_SIZE(stv_bridge_init); i++)
		stv06xx_ग_लिखो_bridge(sd, stv_bridge_init[i].addr, stv_bridge_init[i].data);

	err = stv06xx_ग_लिखो_sensor_bytes(sd, (u8 *) vv6410_sensor_init,
					 ARRAY_SIZE(vv6410_sensor_init));
	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक vv6410_start(काष्ठा sd *sd)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा cam *cam = &sd->gspca_dev.cam;
	u32 priv = cam->cam_mode[sd->gspca_dev.curr_mode].priv;

	अगर (priv & VV6410_SUBSAMPLE) अणु
		gspca_dbg(gspca_dev, D_CONF, "Enabling subsampling\n");
		stv06xx_ग_लिखो_bridge(sd, STV_Y_CTRL, 0x02);
		stv06xx_ग_लिखो_bridge(sd, STV_X_CTRL, 0x06);

		stv06xx_ग_लिखो_bridge(sd, STV_SCAN_RATE, 0x10);
	पूर्ण अन्यथा अणु
		stv06xx_ग_लिखो_bridge(sd, STV_Y_CTRL, 0x01);
		stv06xx_ग_लिखो_bridge(sd, STV_X_CTRL, 0x0a);
		stv06xx_ग_लिखो_bridge(sd, STV_SCAN_RATE, 0x00);

	पूर्ण

	/* Turn on LED */
	err = stv06xx_ग_लिखो_bridge(sd, STV_LED_CTRL, LED_ON);
	अगर (err < 0)
		वापस err;

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_SETUP0, 0);
	अगर (err < 0)
		वापस err;

	gspca_dbg(gspca_dev, D_STREAM, "Starting stream\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vv6410_stop(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक err;

	/* Turn off LED */
	err = stv06xx_ग_लिखो_bridge(sd, STV_LED_CTRL, LED_OFF);
	अगर (err < 0)
		वापस err;

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_SETUP0, VV6410_LOW_POWER_MODE);
	अगर (err < 0)
		वापस err;

	gspca_dbg(gspca_dev, D_STREAM, "Halting stream\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vv6410_dump(काष्ठा sd *sd)
अणु
	u8 i;
	पूर्णांक err = 0;

	pr_info("Dumping all vv6410 sensor registers\n");
	क्रम (i = 0; i < 0xff && !err; i++) अणु
		u16 data;
		err = stv06xx_पढ़ो_sensor(sd, i, &data);
		pr_info("Register 0x%x contained 0x%x\n", i, data);
	पूर्ण
	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक vv6410_set_hflip(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u16 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	err = stv06xx_पढ़ो_sensor(sd, VV6410_DATAFORMAT, &i2c_data);
	अगर (err < 0)
		वापस err;

	अगर (val)
		i2c_data |= VV6410_HFLIP;
	अन्यथा
		i2c_data &= ~VV6410_HFLIP;

	gspca_dbg(gspca_dev, D_CONF, "Set horizontal flip to %d\n", val);
	err = stv06xx_ग_लिखो_sensor(sd, VV6410_DATAFORMAT, i2c_data);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक vv6410_set_vflip(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u16 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	err = stv06xx_पढ़ो_sensor(sd, VV6410_DATAFORMAT, &i2c_data);
	अगर (err < 0)
		वापस err;

	अगर (val)
		i2c_data |= VV6410_VFLIP;
	अन्यथा
		i2c_data &= ~VV6410_VFLIP;

	gspca_dbg(gspca_dev, D_CONF, "Set vertical flip to %d\n", val);
	err = stv06xx_ग_लिखो_sensor(sd, VV6410_DATAFORMAT, i2c_data);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक vv6410_set_analog_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set analog gain to %d\n", val);
	err = stv06xx_ग_लिखो_sensor(sd, VV6410_ANALOGGAIN, 0xf0 | (val & 0xf));

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक vv6410_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अचिन्हित पूर्णांक fine, coarse;

	val = (val * val >> 14) + val / 4;

	fine = val % VV6410_CIF_LINELENGTH;
	coarse = min(512, val / VV6410_CIF_LINELENGTH);

	gspca_dbg(gspca_dev, D_CONF, "Set coarse exposure to %d, fine exposure to %d\n",
		  coarse, fine);

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_FINEH, fine >> 8);
	अगर (err < 0)
		जाओ out;

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_FINEL, fine & 0xff);
	अगर (err < 0)
		जाओ out;

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_COARSEH, coarse >> 8);
	अगर (err < 0)
		जाओ out;

	err = stv06xx_ग_लिखो_sensor(sd, VV6410_COARSEL, coarse & 0xff);

out:
	वापस err;
पूर्ण
