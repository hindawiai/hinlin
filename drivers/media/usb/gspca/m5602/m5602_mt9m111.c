<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the mt9m111 sensor
 *
 * Copyright (C) 2008 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "m5602_mt9m111.h"

अटल पूर्णांक mt9m111_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल व्योम mt9m111_dump_रेजिस्टरs(काष्ठा sd *sd);

अटल स्थिर अचिन्हित अक्षर preinit_mt9m111[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x09, 0x00पूर्ण,

	अणुSENSOR, MT9M111_PAGE_MAP, 0x00, 0x00पूर्ण,
	अणुSENSOR, MT9M111_SC_RESET,
		MT9M111_RESET |
		MT9M111_RESTART |
		MT9M111_ANALOG_STANDBY |
		MT9M111_CHIP_DISABLE,
		MT9M111_SHOW_BAD_FRAMES |
		MT9M111_RESTART_BAD_FRAMES |
		MT9M111_SYNCHRONIZE_CHANGESपूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x3e, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3e, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x07, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x0b, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x0a, 0x00पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_mt9m111[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x09, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3e, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x07, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x0b, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x0a, 0x00पूर्ण,

	अणुSENSOR, MT9M111_SC_RESET, 0x00, 0x29पूर्ण,
	अणुSENSOR, MT9M111_PAGE_MAP, 0x00, 0x00पूर्ण,
	अणुSENSOR, MT9M111_SC_RESET, 0x00, 0x08पूर्ण,
	अणुSENSOR, MT9M111_PAGE_MAP, 0x00, 0x01पूर्ण,
	अणुSENSOR, MT9M111_CP_OPERATING_MODE_CTL, 0x00,
			MT9M111_CP_OPERATING_MODE_CTLपूर्ण,
	अणुSENSOR, MT9M111_CP_LENS_CORRECTION_1, 0x04, 0x2aपूर्ण,
	अणुSENSOR, MT9M111_CP_DEFECT_CORR_CONTEXT_A, 0x00,
				MT9M111_2D_DEFECT_CORRECTION_ENABLEपूर्ण,
	अणुSENSOR, MT9M111_CP_DEFECT_CORR_CONTEXT_B, 0x00,
				MT9M111_2D_DEFECT_CORRECTION_ENABLEपूर्ण,
	अणुSENSOR, MT9M111_CP_LUMA_OFFSET, 0x00, 0x00पूर्ण,
	अणुSENSOR, MT9M111_CP_LUMA_CLIP, 0xff, 0x00पूर्ण,
	अणुSENSOR, MT9M111_CP_OUTPUT_FORMAT_CTL2_CONTEXT_A, 0x14, 0x00पूर्ण,
	अणुSENSOR, MT9M111_CP_OUTPUT_FORMAT_CTL2_CONTEXT_B, 0x14, 0x00पूर्ण,
	अणुSENSOR, 0xcd, 0x00, 0x0eपूर्ण,
	अणुSENSOR, 0xd0, 0x00, 0x40पूर्ण,

	अणुSENSOR, MT9M111_PAGE_MAP, 0x00, 0x02पूर्ण,
	अणुSENSOR, MT9M111_CC_AUTO_EXPOSURE_PARAMETER_18, 0x00, 0x00पूर्ण,
	अणुSENSOR, MT9M111_CC_AWB_PARAMETER_7, 0xef, 0x03पूर्ण,

	अणुSENSOR, MT9M111_PAGE_MAP, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x33, 0x03, 0x49पूर्ण,
	अणुSENSOR, 0x34, 0xc0, 0x19पूर्ण,
	अणुSENSOR, 0x3f, 0x20, 0x20पूर्ण,
	अणुSENSOR, 0x40, 0x20, 0x20पूर्ण,
	अणुSENSOR, 0x5a, 0xc0, 0x0aपूर्ण,
	अणुSENSOR, 0x70, 0x7b, 0x0aपूर्ण,
	अणुSENSOR, 0x71, 0xff, 0x00पूर्ण,
	अणुSENSOR, 0x72, 0x19, 0x0eपूर्ण,
	अणुSENSOR, 0x73, 0x18, 0x0fपूर्ण,
	अणुSENSOR, 0x74, 0x57, 0x32पूर्ण,
	अणुSENSOR, 0x75, 0x56, 0x34पूर्ण,
	अणुSENSOR, 0x76, 0x73, 0x35पूर्ण,
	अणुSENSOR, 0x77, 0x30, 0x12पूर्ण,
	अणुSENSOR, 0x78, 0x79, 0x02पूर्ण,
	अणुSENSOR, 0x79, 0x75, 0x06पूर्ण,
	अणुSENSOR, 0x7a, 0x77, 0x0aपूर्ण,
	अणुSENSOR, 0x7b, 0x78, 0x09पूर्ण,
	अणुSENSOR, 0x7c, 0x7d, 0x06पूर्ण,
	अणुSENSOR, 0x7d, 0x31, 0x10पूर्ण,
	अणुSENSOR, 0x7e, 0x00, 0x7eपूर्ण,
	अणुSENSOR, 0x80, 0x59, 0x04पूर्ण,
	अणुSENSOR, 0x81, 0x59, 0x04पूर्ण,
	अणुSENSOR, 0x82, 0x57, 0x0aपूर्ण,
	अणुSENSOR, 0x83, 0x58, 0x0bपूर्ण,
	अणुSENSOR, 0x84, 0x47, 0x0cपूर्ण,
	अणुSENSOR, 0x85, 0x48, 0x0eपूर्ण,
	अणुSENSOR, 0x86, 0x5b, 0x02पूर्ण,
	अणुSENSOR, 0x87, 0x00, 0x5cपूर्ण,
	अणुSENSOR, MT9M111_CONTEXT_CONTROL, 0x00, MT9M111_SEL_CONTEXT_Bपूर्ण,
	अणुSENSOR, 0x60, 0x00, 0x80पूर्ण,
	अणुSENSOR, 0x61, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x62, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x63, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x64, 0x00, 0x00पूर्ण,

	अणुSENSOR, MT9M111_SC_ROWSTART, 0x00, 0x0dपूर्ण, /* 13 */
	अणुSENSOR, MT9M111_SC_COLSTART, 0x00, 0x12पूर्ण, /* 18 */
	अणुSENSOR, MT9M111_SC_WINDOW_HEIGHT, 0x04, 0x00पूर्ण, /* 1024 */
	अणुSENSOR, MT9M111_SC_WINDOW_WIDTH, 0x05, 0x10पूर्ण, /* 1296 */
	अणुSENSOR, MT9M111_SC_HBLANK_CONTEXT_B, 0x01, 0x60पूर्ण, /* 352 */
	अणुSENSOR, MT9M111_SC_VBLANK_CONTEXT_B, 0x00, 0x11पूर्ण, /* 17 */
	अणुSENSOR, MT9M111_SC_HBLANK_CONTEXT_A, 0x01, 0x60पूर्ण, /* 352 */
	अणुSENSOR, MT9M111_SC_VBLANK_CONTEXT_A, 0x00, 0x11पूर्ण, /* 17 */
	अणुSENSOR, MT9M111_SC_R_MODE_CONTEXT_A, 0x01, 0x0fपूर्ण, /* 271 */
	अणुSENSOR, 0x30, 0x04, 0x00पूर्ण,
	/* Set number of blank rows chosen to 400 */
	अणुSENSOR, MT9M111_SC_SHUTTER_WIDTH, 0x01, 0x90पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर start_mt9m111[][4] = अणु
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x09, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_H, 0x81, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_H, 0x82, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x01, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat mt9m111_modes[] = अणु
	अणु
		640,
		480,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage = 640 * 480,
		.bytesperline = 640,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9m111_ctrl_ops = अणु
	.s_ctrl = mt9m111_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9m111_greenbal_cfg = अणु
	.ops	= &mt9m111_ctrl_ops,
	.id	= M5602_V4L2_CID_GREEN_BALANCE,
	.name	= "Green Balance",
	.type	= V4L2_CTRL_TYPE_INTEGER,
	.min	= 0,
	.max	= 0x7ff,
	.step	= 1,
	.def	= MT9M111_GREEN_GAIN_DEFAULT,
	.flags	= V4L2_CTRL_FLAG_SLIDER,
पूर्ण;

पूर्णांक mt9m111_probe(काष्ठा sd *sd)
अणु
	u8 data[2] = अणु0x00, 0x00पूर्ण;
	पूर्णांक i, err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == MT9M111_SENSOR) अणु
			pr_info("Forcing a %s sensor\n", mt9m111.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor, करोn't try to probe this
		 * one */
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a mt9m111 sensor\n");

	/* Do the preinit */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_mt9m111); i++) अणु
		अगर (preinit_mt9m111[i][0] == BRIDGE) अणु
			err = m5602_ग_लिखो_bridge(sd,
					preinit_mt9m111[i][1],
					preinit_mt9m111[i][2]);
		पूर्ण अन्यथा अणु
			data[0] = preinit_mt9m111[i][2];
			data[1] = preinit_mt9m111[i][3];
			err = m5602_ग_लिखो_sensor(sd,
					preinit_mt9m111[i][1], data, 2);
		पूर्ण
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (m5602_पढ़ो_sensor(sd, MT9M111_SC_CHIPVER, data, 2))
		वापस -ENODEV;

	अगर ((data[0] == 0x14) && (data[1] == 0x3a)) अणु
		pr_info("Detected a mt9m111 sensor\n");
		जाओ sensor_found;
	पूर्ण

	वापस -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = mt9m111_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(mt9m111_modes);

	वापस 0;
पूर्ण

पूर्णांक mt9m111_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;

	/* Init the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(init_mt9m111) && !err; i++) अणु
		u8 data[2];

		अगर (init_mt9m111[i][0] == BRIDGE) अणु
			err = m5602_ग_लिखो_bridge(sd,
				init_mt9m111[i][1],
				init_mt9m111[i][2]);
		पूर्ण अन्यथा अणु
			data[0] = init_mt9m111[i][2];
			data[1] = init_mt9m111[i][3];
			err = m5602_ग_लिखो_sensor(sd,
				init_mt9m111[i][1], data, 2);
		पूर्ण
	पूर्ण

	अगर (dump_sensor)
		mt9m111_dump_रेजिस्टरs(sd);

	वापस 0;
पूर्ण

पूर्णांक mt9m111_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 7);

	sd->स्वतः_white_bal = v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops,
					       V4L2_CID_AUTO_WHITE_BALANCE,
					       0, 1, 1, 0);
	sd->green_bal = v4l2_ctrl_new_custom(hdl, &mt9m111_greenbal_cfg, शून्य);
	sd->red_bal = v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops,
					V4L2_CID_RED_BALANCE, 0, 0x7ff, 1,
					MT9M111_RED_GAIN_DEFAULT);
	sd->blue_bal = v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops,
					V4L2_CID_BLUE_BALANCE, 0, 0x7ff, 1,
					MT9M111_BLUE_GAIN_DEFAULT);

	v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops, V4L2_CID_GAIN, 0,
			  (INITIAL_MAX_GAIN - 1) * 2 * 2 * 2, 1,
			  MT9M111_DEFAULT_GAIN);

	sd->hflip = v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &mt9m111_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(4, &sd->स्वतः_white_bal, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

पूर्णांक mt9m111_start(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;
	u8 data[2];
	काष्ठा cam *cam = &sd->gspca_dev.cam;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	पूर्णांक width = cam->cam_mode[sd->gspca_dev.curr_mode].width - 1;
	पूर्णांक height = cam->cam_mode[sd->gspca_dev.curr_mode].height;

	क्रम (i = 0; i < ARRAY_SIZE(start_mt9m111) && !err; i++) अणु
		अगर (start_mt9m111[i][0] == BRIDGE) अणु
			err = m5602_ग_लिखो_bridge(sd,
				start_mt9m111[i][1],
				start_mt9m111[i][2]);
		पूर्ण अन्यथा अणु
			data[0] = start_mt9m111[i][2];
			data[1] = start_mt9m111[i][3];
			err = m5602_ग_लिखो_sensor(sd,
				start_mt9m111[i][1], data, 2);
		पूर्ण
	पूर्ण
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
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 2);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < 2 && !err; i++)
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, 0);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA,
				 (width >> 8) & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, width & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);
	अगर (err < 0)
		वापस err;

	चयन (width) अणु
	हाल 640:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for VGA mode\n");
		अवरोध;

	हाल 320:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for QVGA mode\n");
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

व्योम mt9m111_disconnect(काष्ठा sd *sd)
अणु
	sd->sensor = शून्य;
पूर्ण

अटल पूर्णांक mt9m111_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	u8 data[2] = अणु0x00, 0x00पूर्ण;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक hflip;
	पूर्णांक vflip;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip to %d %d\n",
		  sd->hflip->val, sd->vflip->val);

	/* The mt9m111 is flipped by शेष */
	hflip = !sd->hflip->val;
	vflip = !sd->vflip->val;

	/* Set the correct page map */
	err = m5602_ग_लिखो_sensor(sd, MT9M111_PAGE_MAP, data, 2);
	अगर (err < 0)
		वापस err;

	data[0] = MT9M111_RMB_OVER_SIZED;
	अगर (gspca_dev->pixfmt.width == 640) अणु
		data[1] = MT9M111_RMB_ROW_SKIP_2X |
			  MT9M111_RMB_COLUMN_SKIP_2X |
			  (hflip << 1) | vflip;
	पूर्ण अन्यथा अणु
		data[1] = MT9M111_RMB_ROW_SKIP_4X |
			  MT9M111_RMB_COLUMN_SKIP_4X |
			  (hflip << 1) | vflip;
	पूर्ण
	err = m5602_ग_लिखो_sensor(sd, MT9M111_SC_R_MODE_CONTEXT_B,
					data, 2);
	वापस err;
पूर्ण

अटल पूर्णांक mt9m111_set_स्वतः_white_balance(काष्ठा gspca_dev *gspca_dev,
					  __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;
	u8 data[2];

	err = m5602_पढ़ो_sensor(sd, MT9M111_CP_OPERATING_MODE_CTL, data, 2);
	अगर (err < 0)
		वापस err;

	data[1] = ((data[1] & 0xfd) | ((val & 0x01) << 1));

	err = m5602_ग_लिखो_sensor(sd, MT9M111_CP_OPERATING_MODE_CTL, data, 2);

	gspca_dbg(gspca_dev, D_CONF, "Set auto white balance %d\n", val);
	वापस err;
पूर्ण

अटल पूर्णांक mt9m111_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err, पंचांगp;
	u8 data[2] = अणु0x00, 0x00पूर्ण;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Set the correct page map */
	err = m5602_ग_लिखो_sensor(sd, MT9M111_PAGE_MAP, data, 2);
	अगर (err < 0)
		वापस err;

	अगर (val >= INITIAL_MAX_GAIN * 2 * 2 * 2)
		वापस -EINVAL;

	अगर ((val >= INITIAL_MAX_GAIN * 2 * 2) &&
	    (val < (INITIAL_MAX_GAIN - 1) * 2 * 2 * 2))
		पंचांगp = (1 << 10) | (val << 9) |
				(val << 8) | (val / 8);
	अन्यथा अगर ((val >= INITIAL_MAX_GAIN * 2) &&
		 (val <  INITIAL_MAX_GAIN * 2 * 2))
		पंचांगp = (1 << 9) | (1 << 8) | (val / 4);
	अन्यथा अगर ((val >= INITIAL_MAX_GAIN) &&
		 (val < INITIAL_MAX_GAIN * 2))
		पंचांगp = (1 << 8) | (val / 2);
	अन्यथा
		पंचांगp = val;

	data[1] = (पंचांगp & 0xff);
	data[0] = (पंचांगp & 0xff00) >> 8;
	gspca_dbg(gspca_dev, D_CONF, "tmp=%d, data[1]=%d, data[0]=%d\n", पंचांगp,
		  data[1], data[0]);

	err = m5602_ग_लिखो_sensor(sd, MT9M111_SC_GLOBAL_GAIN,
				   data, 2);

	वापस err;
पूर्ण

अटल पूर्णांक mt9m111_set_green_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 data[2];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[1] = (val & 0xff);
	data[0] = (val & 0xff00) >> 8;

	gspca_dbg(gspca_dev, D_CONF, "Set green balance %d\n", val);
	err = m5602_ग_लिखो_sensor(sd, MT9M111_SC_GREEN_1_GAIN,
				 data, 2);
	अगर (err < 0)
		वापस err;

	वापस m5602_ग_लिखो_sensor(sd, MT9M111_SC_GREEN_2_GAIN,
				  data, 2);
पूर्ण

अटल पूर्णांक mt9m111_set_blue_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	u8 data[2];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[1] = (val & 0xff);
	data[0] = (val & 0xff00) >> 8;

	gspca_dbg(gspca_dev, D_CONF, "Set blue balance %d\n", val);

	वापस m5602_ग_लिखो_sensor(sd, MT9M111_SC_BLUE_GAIN,
				  data, 2);
पूर्ण

अटल पूर्णांक mt9m111_set_red_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	u8 data[2];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[1] = (val & 0xff);
	data[0] = (val & 0xff00) >> 8;

	gspca_dbg(gspca_dev, D_CONF, "Set red balance %d\n", val);

	वापस m5602_ग_लिखो_sensor(sd, MT9M111_SC_RED_GAIN,
				  data, 2);
पूर्ण

अटल पूर्णांक mt9m111_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		err = mt9m111_set_स्वतः_white_balance(gspca_dev, ctrl->val);
		अगर (err || ctrl->val)
			वापस err;
		err = mt9m111_set_green_balance(gspca_dev, sd->green_bal->val);
		अगर (err)
			वापस err;
		err = mt9m111_set_red_balance(gspca_dev, sd->red_bal->val);
		अगर (err)
			वापस err;
		err = mt9m111_set_blue_balance(gspca_dev, sd->blue_bal->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = mt9m111_set_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = mt9m111_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mt9m111_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	u8 address, value[2] = अणु0x00, 0x00पूर्ण;

	pr_info("Dumping the mt9m111 register state\n");

	pr_info("Dumping the mt9m111 sensor core registers\n");
	value[1] = MT9M111_SENSOR_CORE;
	m5602_ग_लिखो_sensor(sd, MT9M111_PAGE_MAP, value, 2);
	क्रम (address = 0; address < 0xff; address++) अणु
		m5602_पढ़ो_sensor(sd, address, value, 2);
		pr_info("register 0x%x contains 0x%x%x\n",
			address, value[0], value[1]);
	पूर्ण

	pr_info("Dumping the mt9m111 color pipeline registers\n");
	value[1] = MT9M111_COLORPIPE;
	m5602_ग_लिखो_sensor(sd, MT9M111_PAGE_MAP, value, 2);
	क्रम (address = 0; address < 0xff; address++) अणु
		m5602_पढ़ो_sensor(sd, address, value, 2);
		pr_info("register 0x%x contains 0x%x%x\n",
			address, value[0], value[1]);
	पूर्ण

	pr_info("Dumping the mt9m111 camera control registers\n");
	value[1] = MT9M111_CAMERA_CONTROL;
	m5602_ग_लिखो_sensor(sd, MT9M111_PAGE_MAP, value, 2);
	क्रम (address = 0; address < 0xff; address++) अणु
		m5602_पढ़ो_sensor(sd, address, value, 2);
		pr_info("register 0x%x contains 0x%x%x\n",
			address, value[0], value[1]);
	पूर्ण

	pr_info("mt9m111 register state dump complete\n");
पूर्ण
