<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the ov7660 sensor
 *
 * Copyright (C) 2009 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "m5602_ov7660.h"

अटल पूर्णांक ov7660_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल व्योम ov7660_dump_रेजिस्टरs(काष्ठा sd *sd);

अटल स्थिर अचिन्हित अक्षर preinit_ov7660[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0dपूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x03पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x03पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,

	अणुSENSOR, OV7660_OFON, 0x0cपूर्ण,
	अणुSENSOR, OV7660_COM2, 0x11पूर्ण,
	अणुSENSOR, OV7660_COM7, 0x05पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_ov7660[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0dपूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण,
	अणुSENSOR, OV7660_COM7, 0x80पूर्ण,
	अणुSENSOR, OV7660_CLKRC, 0x80पूर्ण,
	अणुSENSOR, OV7660_COM9, 0x4cपूर्ण,
	अणुSENSOR, OV7660_OFON, 0x43पूर्ण,
	अणुSENSOR, OV7660_COM12, 0x28पूर्ण,
	अणुSENSOR, OV7660_COM8, 0x00पूर्ण,
	अणुSENSOR, OV7660_COM10, 0x40पूर्ण,
	अणुSENSOR, OV7660_HSTART, 0x0cपूर्ण,
	अणुSENSOR, OV7660_HSTOP, 0x61पूर्ण,
	अणुSENSOR, OV7660_HREF, 0xa4पूर्ण,
	अणुSENSOR, OV7660_PSHFT, 0x0bपूर्ण,
	अणुSENSOR, OV7660_VSTART, 0x01पूर्ण,
	अणुSENSOR, OV7660_VSTOP, 0x7aपूर्ण,
	अणुSENSOR, OV7660_VSTOP, 0x00पूर्ण,
	अणुSENSOR, OV7660_COM7, 0x05पूर्ण,
	अणुSENSOR, OV7660_COM6, 0x42पूर्ण,
	अणुSENSOR, OV7660_BBIAS, 0x94पूर्ण,
	अणुSENSOR, OV7660_GbBIAS, 0x94पूर्ण,
	अणुSENSOR, OV7660_RSVD29, 0x94पूर्ण,
	अणुSENSOR, OV7660_RBIAS, 0x94पूर्ण,
	अणुSENSOR, OV7660_COM1, 0x00पूर्ण,
	अणुSENSOR, OV7660_AECH, 0x00पूर्ण,
	अणुSENSOR, OV7660_AECHH, 0x00पूर्ण,
	अणुSENSOR, OV7660_ADC, 0x05पूर्ण,
	अणुSENSOR, OV7660_COM13, 0x00पूर्ण,
	अणुSENSOR, OV7660_RSVDA1, 0x23पूर्ण,
	अणुSENSOR, OV7660_TSLB, 0x0dपूर्ण,
	अणुSENSOR, OV7660_HV, 0x80पूर्ण,
	अणुSENSOR, OV7660_LCC1, 0x00पूर्ण,
	अणुSENSOR, OV7660_LCC2, 0x00पूर्ण,
	अणुSENSOR, OV7660_LCC3, 0x10पूर्ण,
	अणुSENSOR, OV7660_LCC4, 0x40पूर्ण,
	अणुSENSOR, OV7660_LCC5, 0x01पूर्ण,

	अणुSENSOR, OV7660_AECH, 0x20पूर्ण,
	अणुSENSOR, OV7660_COM1, 0x00पूर्ण,
	अणुSENSOR, OV7660_OFON, 0x0cपूर्ण,
	अणुSENSOR, OV7660_COM2, 0x11पूर्ण,
	अणुSENSOR, OV7660_COM7, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण,
	अणुSENSOR, OV7660_AECH, 0x5fपूर्ण,
	अणुSENSOR, OV7660_COM1, 0x03पूर्ण,
	अणुSENSOR, OV7660_OFON, 0x0cपूर्ण,
	अणुSENSOR, OV7660_COM2, 0x11पूर्ण,
	अणुSENSOR, OV7660_COM7, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x04पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x05पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x06पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0cपूर्ण,
	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_H, 0x81पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_H, 0x82पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x08पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x01पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0xecपूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x27पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x02पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0xa7पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat ov7660_modes[] = अणु
	अणु
		640,
		480,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			640 * 480,
		.bytesperline = 640,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops ov7660_ctrl_ops = अणु
	.s_ctrl = ov7660_s_ctrl,
पूर्ण;

पूर्णांक ov7660_probe(काष्ठा sd *sd)
अणु
	पूर्णांक err = 0, i;
	u8 prod_id = 0, ver_id = 0;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == OV7660_SENSOR) अणु
			pr_info("Forcing an %s sensor\n", ov7660.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor,
		करोn't try to probe this one */
		वापस -ENODEV;
	पूर्ण

	/* Do the preinit */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_ov7660) && !err; i++) अणु
		u8 data[2];

		अगर (preinit_ov7660[i][0] == BRIDGE) अणु
			err = m5602_ग_लिखो_bridge(sd,
				preinit_ov7660[i][1],
				preinit_ov7660[i][2]);
		पूर्ण अन्यथा अणु
			data[0] = preinit_ov7660[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				preinit_ov7660[i][1], data, 1);
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;

	अगर (m5602_पढ़ो_sensor(sd, OV7660_PID, &prod_id, 1))
		वापस -ENODEV;

	अगर (m5602_पढ़ो_sensor(sd, OV7660_VER, &ver_id, 1))
		वापस -ENODEV;

	pr_info("Sensor reported 0x%x%x\n", prod_id, ver_id);

	अगर ((prod_id == 0x76) && (ver_id == 0x60)) अणु
		pr_info("Detected a ov7660 sensor\n");
		जाओ sensor_found;
	पूर्ण
	वापस -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = ov7660_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(ov7660_modes);

	वापस 0;
पूर्ण

पूर्णांक ov7660_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err;

	/* Init the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(init_ov7660); i++) अणु
		u8 data[2];

		अगर (init_ov7660[i][0] == BRIDGE) अणु
			err = m5602_ग_लिखो_bridge(sd,
				init_ov7660[i][1],
				init_ov7660[i][2]);
		पूर्ण अन्यथा अणु
			data[0] = init_ov7660[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				init_ov7660[i][1], data, 1);
		पूर्ण
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (dump_sensor)
		ov7660_dump_रेजिस्टरs(sd);

	वापस 0;
पूर्ण

पूर्णांक ov7660_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 6);

	v4l2_ctrl_new_std(hdl, &ov7660_ctrl_ops, V4L2_CID_AUTO_WHITE_BALANCE,
			  0, 1, 1, 1);
	v4l2_ctrl_new_std_menu(hdl, &ov7660_ctrl_ops,
			  V4L2_CID_EXPOSURE_AUTO, 1, 0, V4L2_EXPOSURE_AUTO);

	sd->स्वतःgain = v4l2_ctrl_new_std(hdl, &ov7660_ctrl_ops,
					 V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	sd->gain = v4l2_ctrl_new_std(hdl, &ov7660_ctrl_ops, V4L2_CID_GAIN, 0,
				     255, 1, OV7660_DEFAULT_GAIN);

	sd->hflip = v4l2_ctrl_new_std(hdl, &ov7660_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &ov7660_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःgain, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

पूर्णांक ov7660_start(काष्ठा sd *sd)
अणु
	वापस 0;
पूर्ण

पूर्णांक ov7660_stop(काष्ठा sd *sd)
अणु
	वापस 0;
पूर्ण

व्योम ov7660_disconnect(काष्ठा sd *sd)
अणु
	ov7660_stop(sd);

	sd->sensor = शून्य;
पूर्ण

अटल पूर्णांक ov7660_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data = val;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Setting gain to %d\n", val);

	err = m5602_ग_लिखो_sensor(sd, OV7660_GAIN, &i2c_data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक ov7660_set_स्वतः_white_balance(काष्ठा gspca_dev *gspca_dev,
					 __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto white balance to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV7660_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = ((i2c_data & 0xfd) | ((val & 0x01) << 1));
	err = m5602_ग_लिखो_sensor(sd, OV7660_COM8, &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक ov7660_set_स्वतः_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto gain control to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV7660_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	i2c_data = ((i2c_data & 0xfb) | ((val & 0x01) << 2));

	वापस m5602_ग_लिखो_sensor(sd, OV7660_COM8, &i2c_data, 1);
पूर्ण

अटल पूर्णांक ov7660_set_स्वतः_exposure(काष्ठा gspca_dev *gspca_dev,
				    __s32 val)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set auto exposure control to %d\n", val);

	err = m5602_पढ़ो_sensor(sd, OV7660_COM8, &i2c_data, 1);
	अगर (err < 0)
		वापस err;

	val = (val == V4L2_EXPOSURE_AUTO);
	i2c_data = ((i2c_data & 0xfe) | ((val & 0x01) << 0));

	वापस m5602_ग_लिखो_sensor(sd, OV7660_COM8, &i2c_data, 1);
पूर्ण

अटल पूर्णांक ov7660_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	u8 i2c_data;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip to %d, %d\n",
		  sd->hflip->val, sd->vflip->val);

	i2c_data = (sd->hflip->val << 5) | (sd->vflip->val << 4);

	err = m5602_ग_लिखो_sensor(sd, OV7660_MVFP, &i2c_data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक ov7660_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		err = ov7660_set_स्वतः_white_balance(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		err = ov7660_set_स्वतः_exposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		err = ov7660_set_स्वतः_gain(gspca_dev, ctrl->val);
		अगर (err || ctrl->val)
			वापस err;
		err = ov7660_set_gain(gspca_dev, sd->gain->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = ov7660_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ov7660_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	पूर्णांक address;
	pr_info("Dumping the ov7660 register state\n");
	क्रम (address = 0; address < 0xa9; address++) अणु
		u8 value;
		m5602_पढ़ो_sensor(sd, address, &value, 1);
		pr_info("register 0x%x contains 0x%x\n", address, value);
	पूर्ण

	pr_info("ov7660 register state dump complete\n");

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
