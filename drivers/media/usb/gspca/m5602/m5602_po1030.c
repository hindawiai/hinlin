<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the po1030 sensor
 *
 * Copyright (c) 2008 Erik Andrथऊn
 * Copyright (c) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (c) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "m5602_po1030.h"

अटल पूर्णांक po1030_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल व्योम po1030_dump_रेजिस्टरs(काष्ठा sd *sd);

अटल स्थिर अचिन्हित अक्षर preinit_po1030[][3] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x02पूर्ण,

	अणुSENSOR, PO1030_AUTOCTRL2, PO1030_SENSOR_RESET | (1 << 2)पूर्ण,

	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_po1030[][3] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,

	अणुSENSOR, PO1030_AUTOCTRL2, PO1030_SENSOR_RESET | (1 << 2)पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,

	अणुSENSOR, PO1030_AUTOCTRL2, 0x04पूर्ण,

	अणुSENSOR, PO1030_OUTFORMCTRL2, PO1030_RAW_RGB_BAYERपूर्ण,
	अणुSENSOR, PO1030_AUTOCTRL1, PO1030_WEIGHT_WIN_2Xपूर्ण,

	अणुSENSOR, PO1030_CONTROL2, 0x03पूर्ण,
	अणुSENSOR, 0x21, 0x90पूर्ण,
	अणुSENSOR, PO1030_YTARGET, 0x60पूर्ण,
	अणुSENSOR, 0x59, 0x13पूर्ण,
	अणुSENSOR, PO1030_OUTFORMCTRL1, PO1030_HREF_ENABLEपूर्ण,
	अणुSENSOR, PO1030_EDGE_ENH_OFF, 0x00पूर्ण,
	अणुSENSOR, PO1030_EGA, 0x80पूर्ण,
	अणुSENSOR, 0x78, 0x14पूर्ण,
	अणुSENSOR, 0x6f, 0x01पूर्ण,
	अणुSENSOR, PO1030_GLOBALGAINMAX, 0x14पूर्ण,
	अणुSENSOR, PO1030_Cb_U_GAIN, 0x38पूर्ण,
	अणुSENSOR, PO1030_Cr_V_GAIN, 0x38पूर्ण,
	अणुSENSOR, PO1030_CONTROL1, PO1030_SHUTTER_MODE |
				  PO1030_AUTO_SUBSAMPLING |
				  PO1030_FRAME_EQUALपूर्ण,
	अणुSENSOR, PO1030_GC0, 0x10पूर्ण,
	अणुSENSOR, PO1030_GC1, 0x20पूर्ण,
	अणुSENSOR, PO1030_GC2, 0x40पूर्ण,
	अणुSENSOR, PO1030_GC3, 0x60पूर्ण,
	अणुSENSOR, PO1030_GC4, 0x80पूर्ण,
	अणुSENSOR, PO1030_GC5, 0xa0पूर्ण,
	अणुSENSOR, PO1030_GC6, 0xc0पूर्ण,
	अणुSENSOR, PO1030_GC7, 0xffपूर्ण,

	/* Set the width to 751 */
	अणुSENSOR, PO1030_FRAMEWIDTH_H, 0x02पूर्ण,
	अणुSENSOR, PO1030_FRAMEWIDTH_L, 0xefपूर्ण,

	/* Set the height to 540 */
	अणुSENSOR, PO1030_FRAMEHEIGHT_H, 0x02पूर्ण,
	अणुSENSOR, PO1030_FRAMEHEIGHT_L, 0x1cपूर्ण,

	/* Set the x winकरोw to 1 */
	अणुSENSOR, PO1030_WINDOWX_H, 0x00पूर्ण,
	अणुSENSOR, PO1030_WINDOWX_L, 0x01पूर्ण,

	/* Set the y winकरोw to 1 */
	अणुSENSOR, PO1030_WINDOWY_H, 0x00पूर्ण,
	अणुSENSOR, PO1030_WINDOWY_L, 0x01पूर्ण,

	/* with a very low lighted environment increase the exposure but
	 * decrease the FPS (Frame Per Second) */
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat po1030_modes[] = अणु
	अणु
		640,
		480,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage = 640 * 480,
		.bytesperline = 640,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops po1030_ctrl_ops = अणु
	.s_ctrl = po1030_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config po1030_greenbal_cfg = अणु
	.ops	= &po1030_ctrl_ops,
	.id	= M5602_V4L2_CID_GREEN_BALANCE,
	.name	= "Green Balance",
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.min	= 0,
	.max	= 255,
	.step	= 1,
	.def	= PO1030_GREEN_GAIN_DEFAULT,
	.flags	= V4L2_CTRL_FLAG_SLIDER,
पूर्ण;

पूर्णांक po1030_probe(काष्ठा sd *sd)
अणु
	u8 dev_id_h = 0, i;
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == PO1030_SENSOR) अणु
			pr_info("Forcing a %s sensor\n", po1030.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor, करोn't try to probe this
		 * one */
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a po1030 sensor\n");

	/* Run the pre-init to actually probe the unit */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_po1030); i++) अणु
		u8 data = preinit_po1030[i][2];
		अगर (preinit_po1030[i][0] == SENSOR)
			err = m5602_ग_लिखो_sensor(sd, preinit_po1030[i][1],
						 &data, 1);
		अन्यथा
			err = m5602_ग_लिखो_bridge(sd, preinit_po1030[i][1],
						 data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (m5602_पढ़ो_sensor(sd, PO1030_DEVID_H, &dev_id_h, 1))
		वापस -ENODEV;

	अगर (dev_id_h == 0x30) अणु
		pr_info("Detected a po1030 sensor\n");
		जाओ sensor_found;
	पूर्ण
	वापस -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = po1030_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(po1030_modes);

	वापस 0;
पूर्ण

पूर्णांक po1030_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;

	/* Init the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(init_po1030) && !err; i++) अणु
		u8 data[2] = अणु0x00, 0x00पूर्ण;

		चयन (init_po1030[i][0]) अणु
		हाल BRIDGE:
			err = m5602_ग_लिखो_bridge(sd,
				init_po1030[i][1],
				init_po1030[i][2]);
			अवरोध;

		हाल SENSOR:
			data[0] = init_po1030[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				init_po1030[i][1], data, 1);
			अवरोध;

		शेष:
			pr_info("Invalid stream command, exiting init\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;

	अगर (dump_sensor)
		po1030_dump_रेजिस्टरs(sd);

	वापस 0;
पूर्ण

पूर्णांक po1030_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 9);

	sd->स्वतः_white_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					       V4L2_CID_AUTO_WHITE_BALANCE,
					       0, 1, 1, 0);
	sd->green_bal = v4l2_ctrl_new_custom(hdl, &po1030_greenbal_cfg, शून्य);
	sd->red_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					V4L2_CID_RED_BALANCE, 0, 255, 1,
					PO1030_RED_GAIN_DEFAULT);
	sd->blue_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					V4L2_CID_BLUE_BALANCE, 0, 255, 1,
					PO1030_BLUE_GAIN_DEFAULT);

	sd->स्वतःexpo = v4l2_ctrl_new_std_menu(hdl, &po1030_ctrl_ops,
			  V4L2_CID_EXPOSURE_AUTO, 1, 0, V4L2_EXPOSURE_MANUAL);
	sd->expo = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_EXPOSURE,
			  0, 0x2ff, 1, PO1030_EXPOSURE_DEFAULT);

	sd->gain = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_GAIN, 0,
				     0x4f, 1, PO1030_GLOBAL_GAIN_DEFAULT);

	sd->hflip = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(4, &sd->स्वतः_white_bal, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःexpo, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

पूर्णांक po1030_start(काष्ठा sd *sd)
अणु
	काष्ठा cam *cam = &sd->gspca_dev.cam;
	पूर्णांक i, err = 0;
	पूर्णांक width = cam->cam_mode[sd->gspca_dev.curr_mode].width;
	पूर्णांक height = cam->cam_mode[sd->gspca_dev.curr_mode].height;
	पूर्णांक ver_offs = cam->cam_mode[sd->gspca_dev.curr_mode].priv;
	u8 data;

	चयन (width) अणु
	हाल 320:
		data = PO1030_SUBSAMPLING;
		err = m5602_ग_लिखो_sensor(sd, PO1030_CONTROL3, &data, 1);
		अगर (err < 0)
			वापस err;

		data = ((width + 3) >> 8) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		अगर (err < 0)
			वापस err;

		data = (width + 3) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWWIDTH_L, &data, 1);
		अगर (err < 0)
			वापस err;

		data = ((height + 1) >> 8) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		अगर (err < 0)
			वापस err;

		data = (height + 1) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWHEIGHT_L, &data, 1);

		height += 6;
		width -= 1;
		अवरोध;

	हाल 640:
		data = 0;
		err = m5602_ग_लिखो_sensor(sd, PO1030_CONTROL3, &data, 1);
		अगर (err < 0)
			वापस err;

		data = ((width + 7) >> 8) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		अगर (err < 0)
			वापस err;

		data = (width + 7) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWWIDTH_L, &data, 1);
		अगर (err < 0)
			वापस err;

		data = ((height + 3) >> 8) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		अगर (err < 0)
			वापस err;

		data = (height + 3) & 0xff;
		err = m5602_ग_लिखो_sensor(sd, PO1030_WINDOWHEIGHT_L, &data, 1);

		height += 12;
		width -= 2;
		अवरोध;
	पूर्ण
	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SENSOR_TYPE, 0x0c);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_LINE_OF_FRAME_H, 0x81);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_PIX_OF_LINE_H, 0x82);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0x01);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA,
				 ((ver_offs >> 8) & 0xff));
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, (ver_offs & 0xff));
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < 2 && !err; i++)
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, 0);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, (height >> 8) & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, (height & 0xff));
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < 2 && !err; i++)
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, 0);

	क्रम (i = 0; i < 2 && !err; i++)
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);

	क्रम (i = 0; i < 2 && !err; i++)
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, 0);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, (width >> 8) & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, (width & 0xff));
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);
	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set exposure to %d\n", val & 0xffff);

	i2c_data = ((val & 0xff00) >> 8);
	gspca_dbg(gspca_dev, D_CONF, "Set exposure to high byte to 0x%x\n",
		  i2c_data);

	err = m5602_ग_लिखो_sensor(sd, PO1030_INTEGLINES_H,
				  &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = (val & 0xff);
	gspca_dbg(gspca_dev, D_CONF, "Set exposure to low byte to 0x%x\n",
		  i2c_data);
	err = m5602_ग_लिखो_sensor(sd, PO1030_INTEGLINES_M,
				  &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	i2c_data = val & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set global gain to %d\n", i2c_data);
	err = m5602_ग_लिखो_sensor(sd, PO1030_GLOBALGAIN,
				 &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip %d %d\n",
		  sd->hflip->val, sd->vflip->val);
	err = m5602_पढ़ो_sensor(sd, PO1030_CONTROL2, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = (0x3f & i2c_data) | (sd->hflip->val << 7) |
		   (sd->vflip->val << 6);

	err = m5602_ग_लिखो_sensor(sd, PO1030_CONTROL2,
				 &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_red_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	i2c_data = val & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set red gain to %d\n", i2c_data);
	err = m5602_ग_लिखो_sensor(sd, PO1030_RED_GAIN,
				  &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_blue_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	i2c_data = val & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set blue gain to %d\n", i2c_data);
	err = m5602_ग_लिखो_sensor(sd, PO1030_BLUE_GAIN,
				  &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_green_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	i2c_data = val & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set green gain to %d\n", i2c_data);

	err = m5602_ग_लिखो_sensor(sd, PO1030_GREEN_1_GAIN,
			   &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	वापस m5602_ग_लिखो_sensor(sd, PO1030_GREEN_2_GAIN,
				 &i2c_data, 1);
पूर्ण

अटल पूर्णांक po1030_set_स्वतः_white_balance(काष्ठा gspca_dev *gspca_dev,
					 __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	err = m5602_पढ़ो_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	gspca_dbg(gspca_dev, D_CONF, "Set auto white balance to %d\n", val);
	i2c_data = (i2c_data & 0xfe) | (val & 0x01);
	err = m5602_ग_लिखो_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक po1030_set_स्वतः_exposure(काष्ठा gspca_dev *gspca_dev,
				    __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	err = m5602_पढ़ो_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	gspca_dbg(gspca_dev, D_CONF, "Set auto exposure to %d\n", val);
	val = (val == V4L2_EXPOSURE_AUTO);
	i2c_data = (i2c_data & 0xfd) | ((val & 0x01) << 1);
	वापस m5602_ग_लिखो_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
पूर्ण

व्योम po1030_disconnect(काष्ठा sd *sd)
अणु
	sd->sensor = शून्य;
पूर्ण

अटल पूर्णांक po1030_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		err = po1030_set_स्वतः_white_balance(gspca_dev, ctrl->val);
		अगर (err || ctrl->val)
			वापस err;
		err = po1030_set_green_balance(gspca_dev, sd->green_bal->val);
		अगर (err)
			वापस err;
		err = po1030_set_red_balance(gspca_dev, sd->red_bal->val);
		अगर (err)
			वापस err;
		err = po1030_set_blue_balance(gspca_dev, sd->blue_bal->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		err = po1030_set_स्वतः_exposure(gspca_dev, ctrl->val);
		अगर (err || ctrl->val == V4L2_EXPOSURE_AUTO)
			वापस err;
		err = po1030_set_exposure(gspca_dev, sd->expo->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = po1030_set_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = po1030_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम po1030_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	पूर्णांक address;
	u8 value = 0;

	pr_info("Dumping the po1030 sensor core registers\n");
	क्रम (address = 0; address < 0x7f; address++) अणु
		m5602_पढ़ो_sensor(sd, address, &value, 1);
		pr_info("register 0x%x contains 0x%x\n", address, value);
	पूर्ण

	pr_info("po1030 register state dump complete\n");

	pr_info("Probing for which registers that are read/write\n");
	क्रम (address = 0; address < 0xff; address++) अणु
		u8 old_value, ctrl_value;
		u8 test_value[2] = अणु0xff, 0xffपूर्ण;

		m5602_पढ़ो_sensor(sd, address, &old_value, 1);
		m5602_ग_लिखो_sensor(sd, address, test_value, 1);
		m5602_पढ़ो_sensor(sd, address, &ctrl_value, 1);

		अगर (ctrl_value == test_value[0])
			pr_info("register 0x%x is writeable\n", address);
		अन्यथा
			pr_info("register 0x%x is read only\n", address);

		/* Restore original value */
		m5602_ग_लिखो_sensor(sd, address, &old_value, 1);
	पूर्ण
पूर्ण
