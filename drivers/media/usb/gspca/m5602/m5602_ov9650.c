<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Driver क्रम the ov9650 sensor
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

#समावेश "m5602_ov9650.h"

अटल पूर्णांक ov9650_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल व्योम ov9650_dump_रेजिस्टरs(काष्ठा sd *sd);

अटल स्थिर अचिन्हित अक्षर preinit_ov9650[][3] = अणु
	/* [INITCAM] */
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x0aपूर्ण,
	/* Reset chip */
	अणुSENSOR, OV9650_COM7, OV9650_REGISTER_RESETपूर्ण,
	/* Enable द्विगुन घड़ी */
	अणुSENSOR, OV9650_CLKRC, 0x80पूर्ण,
	/* Do something out of spec with the घातer */
	अणुSENSOR, OV9650_OFON, 0x40पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_ov9650[][3] = अणु
	/* [INITCAM] */
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x0aपूर्ण,

	/* Reset chip */
	अणुSENSOR, OV9650_COM7, OV9650_REGISTER_RESETपूर्ण,
	/* One extra reset is needed in order to make the sensor behave
	   properly when resuming from ram, could be a timing issue */
	अणुSENSOR, OV9650_COM7, OV9650_REGISTER_RESETपूर्ण,

	/* Enable द्विगुन घड़ी */
	अणुSENSOR, OV9650_CLKRC, 0x80पूर्ण,
	/* Do something out of spec with the घातer */
	अणुSENSOR, OV9650_OFON, 0x40पूर्ण,

	/* Set fast AGC/AEC algorithm with unlimited step size */
	अणुSENSOR, OV9650_COM8, OV9650_FAST_AGC_AEC |
			      OV9650_AEC_UNLIM_STEP_SIZEपूर्ण,

	अणुSENSOR, OV9650_CHLF, 0x10पूर्ण,
	अणुSENSOR, OV9650_ARBLM, 0xbfपूर्ण,
	अणुSENSOR, OV9650_ACOM38, 0x81पूर्ण,
	/* Turn off color matrix coefficient द्विगुन option */
	अणुSENSOR, OV9650_COM16, 0x00पूर्ण,
	/* Enable color matrix क्रम RGB/YUV, Delay Y channel,
	set output Y/UV delay to 1 */
	अणुSENSOR, OV9650_COM13, 0x19पूर्ण,
	/* Enable digital BLC, Set output mode to U Y V Y */
	अणुSENSOR, OV9650_TSLB, 0x0cपूर्ण,
	/* Limit the AGC/AEC stable upper region */
	अणुSENSOR, OV9650_COM24, 0x00पूर्ण,
	/* Enable HREF and some out of spec things */
	अणुSENSOR, OV9650_COM12, 0x73पूर्ण,
	/* Set all DBLC offset signs to positive and
	करो some out of spec stuff */
	अणुSENSOR, OV9650_DBLC1, 0xdfपूर्ण,
	अणुSENSOR, OV9650_COM21, 0x06पूर्ण,
	अणुSENSOR, OV9650_RSVD35, 0x91पूर्ण,
	/* Necessary, no camera stream without it */
	अणुSENSOR, OV9650_RSVD16, 0x06पूर्ण,
	अणुSENSOR, OV9650_RSVD94, 0x99पूर्ण,
	अणुSENSOR, OV9650_RSVD95, 0x99पूर्ण,
	अणुSENSOR, OV9650_RSVD96, 0x04पूर्ण,
	/* Enable full range output */
	अणुSENSOR, OV9650_COM15, 0x0पूर्ण,
	/* Enable HREF at optical black, enable ADBLC bias,
	enable ADBLC, reset timings at क्रमmat change */
	अणुSENSOR, OV9650_COM6, 0x4bपूर्ण,
	/* Subtract 32 from the B channel bias */
	अणुSENSOR, OV9650_BBIAS, 0xa0पूर्ण,
	/* Subtract 32 from the Gb channel bias */
	अणुSENSOR, OV9650_GbBIAS, 0xa0पूर्ण,
	/* Do not bypass the analog BLC and to some out of spec stuff */
	अणुSENSOR, OV9650_Gr_COM, 0x00पूर्ण,
	/* Subtract 32 from the R channel bias */
	अणुSENSOR, OV9650_RBIAS, 0xa0पूर्ण,
	/* Subtract 32 from the R channel bias */
	अणुSENSOR, OV9650_RBIAS, 0x0पूर्ण,
	अणुSENSOR, OV9650_COM26, 0x80पूर्ण,
	अणुSENSOR, OV9650_ACOMA9, 0x98पूर्ण,
	/* Set the AGC/AEC stable region upper limit */
	अणुSENSOR, OV9650_AEW, 0x68पूर्ण,
	/* Set the AGC/AEC stable region lower limit */
	अणुSENSOR, OV9650_AEB, 0x5cपूर्ण,
	/* Set the high and low limit nibbles to 3 */
	अणुSENSOR, OV9650_VPT, 0xc3पूर्ण,
	/* Set the Automatic Gain Ceiling (AGC) to 128x,
	drop VSYNC at frame drop,
	limit exposure timing,
	drop frame when the AEC step is larger than the exposure gap */
	अणुSENSOR, OV9650_COM9, 0x6eपूर्ण,
	/* Set VSYNC negative, Set RESET to SLHS (slave mode horizontal sync)
	and set PWDN to SLVS (slave mode vertical sync) */
	अणुSENSOR, OV9650_COM10, 0x42पूर्ण,
	/* Set horizontal column start high to शेष value */
	अणुSENSOR, OV9650_HSTART, 0x1aपूर्ण, /* 210 */
	/* Set horizontal column end */
	अणुSENSOR, OV9650_HSTOP, 0xbfपूर्ण, /* 1534 */
	/* Complementing रेजिस्टर to the two ग_लिखोs above */
	अणुSENSOR, OV9650_HREF, 0xb2पूर्ण,
	/* Set vertical row start high bits */
	अणुSENSOR, OV9650_VSTRT, 0x02पूर्ण,
	/* Set vertical row end low bits */
	अणुSENSOR, OV9650_VSTOP, 0x7eपूर्ण,
	/* Set complementing vertical frame control */
	अणुSENSOR, OV9650_VREF, 0x10पूर्ण,
	अणुSENSOR, OV9650_ADC, 0x04पूर्ण,
	अणुSENSOR, OV9650_HV, 0x40पूर्ण,

	/* Enable denoise, and white-pixel erase */
	अणुSENSOR, OV9650_COM22, OV9650_DENOISE_ENABLE |
		 OV9650_WHITE_PIXEL_ENABLE |
		 OV9650_WHITE_PIXEL_OPTIONपूर्ण,

	/* Enable VARIOPIXEL */
	अणुSENSOR, OV9650_COM3, OV9650_VARIOPIXELपूर्ण,
	अणुSENSOR, OV9650_COM4, OV9650_QVGA_VARIOPIXELपूर्ण,

	/* Put the sensor in soft sleep mode */
	अणुSENSOR, OV9650_COM2, OV9650_SOFT_SLEEP | OV9650_OUTPUT_DRIVE_2Xपूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर res_init_ov9650[][3] = अणु
	अणुSENSOR, OV9650_COM2, OV9650_OUTPUT_DRIVE_2Xपूर्ण,

	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_H, 0x82पूर्ण,
	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_L, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_H, 0x82पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_L, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x01पूर्ण
पूर्ण;

/* Vertically and horizontally flips the image अगर matched, needed क्रम machines
   where the sensor is mounted upside करोwn */
अटल
    स्थिर
	काष्ठा dmi_प्रणाली_id ov9650_flip_dmi_table[] = अणु
	अणु
		.ident = "ASUS A6Ja",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6J")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6JC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6JC")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6K",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6K")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6Kt",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6Kt")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6VA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6VA")
		पूर्ण
	पूर्ण,
	अणु

		.ident = "ASUS A6VC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6VC")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6VM",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6VM")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A7V",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A7V")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "Alienware Aurora m9700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "alienware"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aurora m9700")
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat ov9650_modes[] = अणु
	अणु
		176,
		144,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			176 * 144,
		.bytesperline = 176,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 9
	पूर्ण, अणु
		320,
		240,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			320 * 240,
		.bytesperline = 320,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 8
	पूर्ण, अणु
		352,
		288,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			352 * 288,
		.bytesperline = 352,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 9
	पूर्ण, अणु
		640,
		480,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			640 * 480,
		.bytesperline = 640,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 9
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops ov9650_ctrl_ops = अणु
	.s_ctrl = ov9650_s_ctrl,
पूर्ण;

पूर्णांक ov9650_probe(काष्ठा sd *sd)
अणु
	पूर्णांक err = 0;
	u8 prod_id = 0, ver_id = 0, i;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == OV9650_SENSOR) अणु
			pr_info("Forcing an %s sensor\n", ov9650.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor,
		   करोn't try to probe this one */
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "Probing for an ov9650 sensor\n");

	/* Run the pre-init beक्रमe probing the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_ov9650) && !err; i++) अणु
		u8 data = preinit_ov9650[i][2];
		अगर (preinit_ov9650[i][0] == SENSOR)
			err = m5602_ग_लिखो_sensor(sd,
				preinit_ov9650[i][1], &data, 1);
		अन्यथा
			err = m5602_ग_लिखो_bridge(sd,
				preinit_ov9650[i][1], data);
	पूर्ण

	अगर (err < 0)
		वापस err;

	अगर (m5602_पढ़ो_sensor(sd, OV9650_PID, &prod_id, 1))
		वापस -ENODEV;

	अगर (m5602_पढ़ो_sensor(sd, OV9650_VER, &ver_id, 1))
		वापस -ENODEV;

	अगर ((prod_id == 0x96) && (ver_id == 0x52)) अणु
		pr_info("Detected an ov9650 sensor\n");
		जाओ sensor_found;
	पूर्ण
	वापस -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = ov9650_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(ov9650_modes);

	वापस 0;
पूर्ण

पूर्णांक ov9650_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;
	u8 data;

	अगर (dump_sensor)
		ov9650_dump_रेजिस्टरs(sd);

	क्रम (i = 0; i < ARRAY_SIZE(init_ov9650) && !err; i++) अणु
		data = init_ov9650[i][2];
		अगर (init_ov9650[i][0] == SENSOR)
			err = m5602_ग_लिखो_sensor(sd, init_ov9650[i][1],
						  &data, 1);
		अन्यथा
			err = m5602_ग_लिखो_bridge(sd, init_ov9650[i][1], data);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ov9650_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 9);

	sd->स्वतः_white_bal = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops,
					       V4L2_CID_AUTO_WHITE_BALANCE,
					       0, 1, 1, 1);
	sd->red_bal = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops,
					V4L2_CID_RED_BALANCE, 0, 255, 1,
					RED_GAIN_DEFAULT);
	sd->blue_bal = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops,
					V4L2_CID_BLUE_BALANCE, 0, 255, 1,
					BLUE_GAIN_DEFAULT);

	sd->स्वतःexpo = v4l2_ctrl_new_std_menu(hdl, &ov9650_ctrl_ops,
			  V4L2_CID_EXPOSURE_AUTO, 1, 0, V4L2_EXPOSURE_AUTO);
	sd->expo = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops, V4L2_CID_EXPOSURE,
			  0, 0x1ff, 4, EXPOSURE_DEFAULT);

	sd->स्वतःgain = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops,
					 V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	sd->gain = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops, V4L2_CID_GAIN, 0,
				     0x3ff, 1, GAIN_DEFAULT);

	sd->hflip = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &ov9650_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(3, &sd->स्वतः_white_bal, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःexpo, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःgain, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

पूर्णांक ov9650_start(काष्ठा sd *sd)
अणु
	u8 data;
	पूर्णांक i, err = 0;
	काष्ठा cam *cam = &sd->gspca_dev.cam;

	पूर्णांक width = cam->cam_mode[sd->gspca_dev.curr_mode].width;
	पूर्णांक height = cam->cam_mode[sd->gspca_dev.curr_mode].height;
	पूर्णांक ver_offs = cam->cam_mode[sd->gspca_dev.curr_mode].priv;
	पूर्णांक hor_offs = OV9650_LEFT_OFFSET;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	अगर ((!dmi_check_प्रणाली(ov9650_flip_dmi_table) &&
		sd->vflip->val) ||
		(dmi_check_प्रणाली(ov9650_flip_dmi_table) &&
		!sd->vflip->val))
		ver_offs--;

	अगर (width <= 320)
		hor_offs /= 2;

	/* Synthesize the vsync/hsync setup */
	क्रम (i = 0; i < ARRAY_SIZE(res_init_ov9650) && !err; i++) अणु
		अगर (res_init_ov9650[i][0] == BRIDGE)
			err = m5602_ग_लिखो_bridge(sd, res_init_ov9650[i][1],
				res_init_ov9650[i][2]);
		अन्यथा अगर (res_init_ov9650[i][0] == SENSOR) अणु
			data = res_init_ov9650[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				res_init_ov9650[i][1], &data, 1);
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA,
				 ((ver_offs >> 8) & 0xff));
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_VSYNC_PARA, (ver_offs & 0xff));
	अगर (err < 0)
		वापस err;

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
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 2);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA,
				 (hor_offs >> 8) & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA, hor_offs & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA,
				 ((width + hor_offs) >> 8) & 0xff);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_HSYNC_PARA,
				 ((width + hor_offs) & 0xff));
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_SIG_INI, 0);
	अगर (err < 0)
		वापस err;

	चयन (width) अणु
	हाल 640:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for VGA mode\n");

		data = OV9650_VGA_SELECT | OV9650_RGB_SELECT |
		       OV9650_RAW_RGB_SELECT;
		err = m5602_ग_लिखो_sensor(sd, OV9650_COM7, &data, 1);
		अवरोध;

	हाल 352:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for CIF mode\n");

		data = OV9650_CIF_SELECT | OV9650_RGB_SELECT |
				OV9650_RAW_RGB_SELECT;
		err = m5602_ग_लिखो_sensor(sd, OV9650_COM7, &data, 1);
		अवरोध;

	हाल 320:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for QVGA mode\n");

		data = OV9650_QVGA_SELECT | OV9650_RGB_SELECT |
				OV9650_RAW_RGB_SELECT;
		err = m5602_ग_लिखो_sensor(sd, OV9650_COM7, &data, 1);
		अवरोध;

	हाल 176:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for QCIF mode\n");

		data = OV9650_QCIF_SELECT | OV9650_RGB_SELECT |
			OV9650_RAW_RGB_SELECT;
		err = m5602_ग_लिखो_sensor(sd, OV9650_COM7, &data, 1);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ov9650_stop(काष्ठा sd *sd)
अणु
	u8 data = OV9650_SOFT_SLEEP | OV9650_OUTPUT_DRIVE_2X;
	वापस m5602_ग_लिखो_sensor(sd, OV9650_COM2, &data, 1);
पूर्ण

व्योम ov9650_disconnect(काष्ठा sd *sd)
अणु
	ov9650_stop(sd);

	sd->sensor = शून्य;
पूर्ण

अटल पूर्णांक ov9650_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 i2c_data;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set exposure to %d\n", val);

	/* The 6 MSBs */
	i2c_data = (val >> 10) & 0x3f;
	err = m5602_ग_लिखो_sensor(sd, OV9650_AECHM,
				  &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	/* The 8 middle bits */
	i2c_data = (val >> 2) & 0xff;
	err = m5602_ग_लिखो_sensor(sd, OV9650_AECH,
				  &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	/* The 2 LSBs */
	i2c_data = val & 0x03;
	err = m5602_ग_लिखो_sensor(sd, OV9650_COM1, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Setting gain to %d\n", val);

	/* The 2 MSB */
	/* Read the OV9650_VREF रेजिस्टर first to aव्योम
	   corrupting the VREF high and low bits */
	err = m5602_पढ़ो_sensor(sd, OV9650_VREF, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	/* Mask away all unपूर्णांकeresting bits */
	i2c_data = ((val & 0x0300) >> 2) |
			(i2c_data & 0x3f);
	err = m5602_ग_लिखो_sensor(sd, OV9650_VREF, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	/* The 8 LSBs */
	i2c_data = val & 0xff;
	err = m5602_ग_लिखो_sensor(sd, OV9650_GAIN, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_red_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set red gain to %d\n", val);

	i2c_data = val & 0xff;
	err = m5602_ग_लिखो_sensor(sd, OV9650_RED, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_blue_balance(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set blue gain to %d\n", val);

	i2c_data = val & 0xff;
	err = m5602_ग_लिखो_sensor(sd, OV9650_BLUE, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक hflip = sd->hflip->val;
	पूर्णांक vflip = sd->vflip->val;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip to %d %d\n", hflip, vflip);

	अगर (dmi_check_प्रणाली(ov9650_flip_dmi_table))
		vflip = !vflip;

	i2c_data = (hflip << 5) | (vflip << 4);
	err = m5602_ग_लिखो_sensor(sd, OV9650_MVFP, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	/* When vflip is toggled we need to पढ़ोjust the bridge hsync/vsync */
	अगर (gspca_dev->streaming)
		err = ov9650_start(sd);

	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_स्वतः_exposure(काष्ठा gspca_dev *gspca_dev,
				    __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto exposure control to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV9650_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	val = (val == V4L2_EXPOSURE_AUTO);
	i2c_data = ((i2c_data & 0xfe) | ((val & 0x01) << 0));

	वापस m5602_ग_लिखो_sensor(sd, OV9650_COM8, &i2c_data, 1);
पूर्ण

अटल पूर्णांक ov9650_set_स्वतः_white_balance(काष्ठा gspca_dev *gspca_dev,
					 __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto white balance to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV9650_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = ((i2c_data & 0xfd) | ((val & 0x01) << 1));
	err = m5602_ग_लिखो_sensor(sd, OV9650_COM8, &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक ov9650_set_स्वतः_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto gain control to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV9650_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = ((i2c_data & 0xfb) | ((val & 0x01) << 2));

	वापस m5602_ग_लिखो_sensor(sd, OV9650_COM8, &i2c_data, 1);
पूर्ण

अटल पूर्णांक ov9650_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		err = ov9650_set_स्वतः_white_balance(gspca_dev, ctrl->val);
		अगर (err || ctrl->val)
			वापस err;
		err = ov9650_set_red_balance(gspca_dev, sd->red_bal->val);
		अगर (err)
			वापस err;
		err = ov9650_set_blue_balance(gspca_dev, sd->blue_bal->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		err = ov9650_set_स्वतः_exposure(gspca_dev, ctrl->val);
		अगर (err || ctrl->val == V4L2_EXPOSURE_AUTO)
			वापस err;
		err = ov9650_set_exposure(gspca_dev, sd->expo->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		err = ov9650_set_स्वतः_gain(gspca_dev, ctrl->val);
		अगर (err || ctrl->val)
			वापस err;
		err = ov9650_set_gain(gspca_dev, sd->gain->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = ov9650_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ov9650_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	पूर्णांक address;
	pr_info("Dumping the ov9650 register state\n");
	क्रम (address = 0; address < 0xa9; address++) अणु
		u8 value;
		m5602_पढ़ो_sensor(sd, address, &value, 1);
		pr_info("register 0x%x contains 0x%x\n", address, value);
	पूर्ण

	pr_info("ov9650 register state dump complete\n");

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
