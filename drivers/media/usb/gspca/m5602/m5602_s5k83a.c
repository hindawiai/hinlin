<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the s5k83a sensor
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

#समावेश <linux/kthपढ़ो.h>
#समावेश "m5602_s5k83a.h"

अटल पूर्णांक s5k83a_s_ctrl(काष्ठा v4l2_ctrl *ctrl);

अटल स्थिर काष्ठा v4l2_ctrl_ops s5k83a_ctrl_ops = अणु
	.s_ctrl = s5k83a_s_ctrl,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat s5k83a_modes[] = अणु
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

अटल स्थिर अचिन्हित अक्षर preinit_s5k83a[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0x80, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x09, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xf0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x20, 0x00पूर्ण,
पूर्ण;

/* This could probably be considerably लघुened.
   I करोn't have the hardware to experiment with it, patches welcome
*/
अटल स्थिर अचिन्हित अक्षर init_s5k83a[][4] = अणु
	/* The following sequence is useless after a clean boot
	   but is necessary after resume from suspend */
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0x80, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x09, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xf0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x20, 0x00पूर्ण,

	अणुSENSOR, S5K83A_PAGE_MAP, 0x04, 0x00पूर्ण,
	अणुSENSOR, 0xaf, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K83A_PAGE_MAP, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x7b, 0xff, 0x00पूर्ण,
	अणुSENSOR, S5K83A_PAGE_MAP, 0x05, 0x00पूर्ण,
	अणुSENSOR, 0x01, 0x50, 0x00पूर्ण,
	अणुSENSOR, 0x12, 0x20, 0x00पूर्ण,
	अणुSENSOR, 0x17, 0x40, 0x00पूर्ण,
	अणुSENSOR, 0x1c, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x02, 0x70, 0x00पूर्ण,
	अणुSENSOR, 0x03, 0x0b, 0x00पूर्ण,
	अणुSENSOR, 0x04, 0xf0, 0x00पूर्ण,
	अणुSENSOR, 0x05, 0x0b, 0x00पूर्ण,
	अणुSENSOR, 0x06, 0x71, 0x00पूर्ण,
	अणुSENSOR, 0x07, 0xe8, 0x00पूर्ण, /* 488 */
	अणुSENSOR, 0x08, 0x02, 0x00पूर्ण,
	अणुSENSOR, 0x09, 0x88, 0x00पूर्ण, /* 648 */
	अणुSENSOR, 0x14, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x15, 0x20, 0x00पूर्ण, /* 32 */
	अणुSENSOR, 0x19, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x1a, 0x98, 0x00पूर्ण, /* 152 */
	अणुSENSOR, 0x0f, 0x02, 0x00पूर्ण,
	अणुSENSOR, 0x10, 0xe5, 0x00पूर्ण, /* 741 */
	/* normal colors
	(this is value after boot, but after tries can be dअगरferent) */
	अणुSENSOR, 0x00, 0x06, 0x00पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर start_s5k83a[][4] = अणु
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
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x01, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0xe4, 0x00पूर्ण, /* 484 */
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x7f, 0x00पूर्ण, /* 639 */
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
पूर्ण;

अटल व्योम s5k83a_dump_रेजिस्टरs(काष्ठा sd *sd);
अटल पूर्णांक s5k83a_get_rotation(काष्ठा sd *sd, u8 *reg_data);
अटल पूर्णांक s5k83a_set_led_indication(काष्ठा sd *sd, u8 val);
अटल पूर्णांक s5k83a_set_flip_real(काष्ठा gspca_dev *gspca_dev,
				__s32 vflip, __s32 hflip);

पूर्णांक s5k83a_probe(काष्ठा sd *sd)
अणु
	u8 prod_id = 0, ver_id = 0;
	पूर्णांक i, err = 0;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == S5K83A_SENSOR) अणु
			pr_info("Forcing a %s sensor\n", s5k83a.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor, करोn't try to probe this
		 * one */
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a s5k83a sensor\n");

	/* Preinit the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_s5k83a) && !err; i++) अणु
		u8 data[2] = अणुpreinit_s5k83a[i][2], preinit_s5k83a[i][3]पूर्ण;
		अगर (preinit_s5k83a[i][0] == SENSOR)
			err = m5602_ग_लिखो_sensor(sd, preinit_s5k83a[i][1],
				data, 2);
		अन्यथा
			err = m5602_ग_लिखो_bridge(sd, preinit_s5k83a[i][1],
				data[0]);
	पूर्ण

	/* We करोn't know what रेजिस्टर (अगर any) that contain the product id
	 * Just pick the first addresses that seem to produce the same results
	 * on multiple machines */
	अगर (m5602_पढ़ो_sensor(sd, 0x00, &prod_id, 1))
		वापस -ENODEV;

	अगर (m5602_पढ़ो_sensor(sd, 0x01, &ver_id, 1))
		वापस -ENODEV;

	अगर ((prod_id == 0xff) || (ver_id == 0xff))
		वापस -ENODEV;
	अन्यथा
		pr_info("Detected a s5k83a sensor\n");

sensor_found:
	sd->gspca_dev.cam.cam_mode = s5k83a_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(s5k83a_modes);

	/* null the poपूर्णांकer! thपढ़ो is't running now */
	sd->rotation_thपढ़ो = शून्य;

	वापस 0;
पूर्ण

पूर्णांक s5k83a_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(init_s5k83a) && !err; i++) अणु
		u8 data[2] = अणु0x00, 0x00पूर्ण;

		चयन (init_s5k83a[i][0]) अणु
		हाल BRIDGE:
			err = m5602_ग_लिखो_bridge(sd,
					init_s5k83a[i][1],
					init_s5k83a[i][2]);
			अवरोध;

		हाल SENSOR:
			data[0] = init_s5k83a[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				init_s5k83a[i][1], data, 1);
			अवरोध;

		हाल SENSOR_LONG:
			data[0] = init_s5k83a[i][2];
			data[1] = init_s5k83a[i][3];
			err = m5602_ग_लिखो_sensor(sd,
				init_s5k83a[i][1], data, 2);
			अवरोध;
		शेष:
			pr_info("Invalid stream command, exiting init\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (dump_sensor)
		s5k83a_dump_रेजिस्टरs(sd);

	वापस err;
पूर्ण

पूर्णांक s5k83a_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 6);

	v4l2_ctrl_new_std(hdl, &s5k83a_ctrl_ops, V4L2_CID_BRIGHTNESS,
			  0, 255, 1, S5K83A_DEFAULT_BRIGHTNESS);

	v4l2_ctrl_new_std(hdl, &s5k83a_ctrl_ops, V4L2_CID_EXPOSURE,
			  0, S5K83A_MAXIMUM_EXPOSURE, 1,
			  S5K83A_DEFAULT_EXPOSURE);

	v4l2_ctrl_new_std(hdl, &s5k83a_ctrl_ops, V4L2_CID_GAIN,
			  0, 255, 1, S5K83A_DEFAULT_GAIN);

	sd->hflip = v4l2_ctrl_new_std(hdl, &s5k83a_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &s5k83a_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

अटल पूर्णांक rotation_thपढ़ो_function(व्योम *data)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) data;
	u8 reg, previous_rotation = 0;
	__s32 vflip, hflip;

	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!schedule_समयout(msecs_to_jअगरfies(100))) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&sd->gspca_dev.usb_lock))
			अवरोध;

		s5k83a_get_rotation(sd, &reg);
		अगर (previous_rotation != reg) अणु
			previous_rotation = reg;
			pr_info("Camera was flipped\n");

			hflip = sd->hflip->val;
			vflip = sd->vflip->val;

			अगर (reg) अणु
				vflip = !vflip;
				hflip = !hflip;
			पूर्ण
			s5k83a_set_flip_real((काष्ठा gspca_dev *) sd,
					      vflip, hflip);
		पूर्ण

		mutex_unlock(&sd->gspca_dev.usb_lock);
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण

	/* वापस to "front" flip */
	अगर (previous_rotation) अणु
		hflip = sd->hflip->val;
		vflip = sd->vflip->val;
		s5k83a_set_flip_real((काष्ठा gspca_dev *) sd, vflip, hflip);
	पूर्ण

	sd->rotation_thपढ़ो = शून्य;
	वापस 0;
पूर्ण

पूर्णांक s5k83a_start(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;

	/* Create another thपढ़ो, polling the GPIO ports of the camera to check
	   अगर it got rotated. This is how the winकरोws driver करोes it so we have
	   to assume that there is no better way of accomplishing this */
	sd->rotation_thपढ़ो = kthपढ़ो_create(rotation_thपढ़ो_function,
					     sd, "rotation thread");
	अगर (IS_ERR(sd->rotation_thपढ़ो)) अणु
		err = PTR_ERR(sd->rotation_thपढ़ो);
		sd->rotation_thपढ़ो = शून्य;
		वापस err;
	पूर्ण
	wake_up_process(sd->rotation_thपढ़ो);

	/* Preinit the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(start_s5k83a) && !err; i++) अणु
		u8 data[2] = अणुstart_s5k83a[i][2], start_s5k83a[i][3]पूर्ण;
		अगर (start_s5k83a[i][0] == SENSOR)
			err = m5602_ग_लिखो_sensor(sd, start_s5k83a[i][1],
				data, 2);
		अन्यथा
			err = m5602_ग_लिखो_bridge(sd, start_s5k83a[i][1],
				data[0]);
	पूर्ण
	अगर (err < 0)
		वापस err;

	वापस s5k83a_set_led_indication(sd, 1);
पूर्ण

पूर्णांक s5k83a_stop(काष्ठा sd *sd)
अणु
	अगर (sd->rotation_thपढ़ो)
		kthपढ़ो_stop(sd->rotation_thपढ़ो);

	वापस s5k83a_set_led_indication(sd, 0);
पूर्ण

व्योम s5k83a_disconnect(काष्ठा sd *sd)
अणु
	s5k83a_stop(sd);

	sd->sensor = शून्य;
पूर्ण

अटल पूर्णांक s5k83a_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 data[2];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[0] = 0x00;
	data[1] = 0x20;
	err = m5602_ग_लिखो_sensor(sd, 0x14, data, 2);
	अगर (err < 0)
		वापस err;

	data[0] = 0x01;
	data[1] = 0x00;
	err = m5602_ग_लिखो_sensor(sd, 0x0d, data, 2);
	अगर (err < 0)
		वापस err;

	/* FIXME: This is not sane, we need to figure out the composition
		  of these रेजिस्टरs */
	data[0] = val >> 3; /* gain, high 5 bits */
	data[1] = val >> 1; /* gain, high 7 bits */
	err = m5602_ग_लिखो_sensor(sd, S5K83A_GAIN, data, 2);

	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_set_brightness(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 data[1];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[0] = val;
	err = m5602_ग_लिखो_sensor(sd, S5K83A_BRIGHTNESS, data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	पूर्णांक err;
	u8 data[2];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[0] = 0;
	data[1] = val;
	err = m5602_ग_लिखो_sensor(sd, S5K83A_EXPOSURE, data, 2);
	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_set_flip_real(काष्ठा gspca_dev *gspca_dev,
				__s32 vflip, __s32 hflip)
अणु
	पूर्णांक err;
	u8 data[1];
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	data[0] = 0x05;
	err = m5602_ग_लिखो_sensor(sd, S5K83A_PAGE_MAP, data, 1);
	अगर (err < 0)
		वापस err;

	/* six bit is vflip, seven is hflip */
	data[0] = S5K83A_FLIP_MASK;
	data[0] = (vflip) ? data[0] | 0x40 : data[0];
	data[0] = (hflip) ? data[0] | 0x80 : data[0];

	err = m5602_ग_लिखो_sensor(sd, S5K83A_FLIP, data, 1);
	अगर (err < 0)
		वापस err;

	data[0] = (vflip) ? 0x0b : 0x0a;
	err = m5602_ग_लिखो_sensor(sd, S5K83A_VFLIP_TUNE, data, 1);
	अगर (err < 0)
		वापस err;

	data[0] = (hflip) ? 0x0a : 0x0b;
	err = m5602_ग_लिखो_sensor(sd, S5K83A_HFLIP_TUNE, data, 1);
	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	u8 reg;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक hflip = sd->hflip->val;
	पूर्णांक vflip = sd->vflip->val;

	err = s5k83a_get_rotation(sd, &reg);
	अगर (err < 0)
		वापस err;
	अगर (reg) अणु
		hflip = !hflip;
		vflip = !vflip;
	पूर्ण

	err = s5k83a_set_flip_real(gspca_dev, vflip, hflip);
	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		err = s5k83a_set_brightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		err = s5k83a_set_exposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = s5k83a_set_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = s5k83a_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक s5k83a_set_led_indication(काष्ठा sd *sd, u8 val)
अणु
	पूर्णांक err = 0;
	u8 data[1];

	err = m5602_पढ़ो_bridge(sd, M5602_XB_GPIO_DAT, data);
	अगर (err < 0)
		वापस err;

	अगर (val)
		data[0] = data[0] | S5K83A_GPIO_LED_MASK;
	अन्यथा
		data[0] = data[0] & ~S5K83A_GPIO_LED_MASK;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_GPIO_DAT, data[0]);

	वापस err;
पूर्ण

/* Get camera rotation on Acer notebooks */
अटल पूर्णांक s5k83a_get_rotation(काष्ठा sd *sd, u8 *reg_data)
अणु
	पूर्णांक err = m5602_पढ़ो_bridge(sd, M5602_XB_GPIO_DAT, reg_data);
	*reg_data = (*reg_data & S5K83A_GPIO_ROTATION_MASK) ? 0 : 1;
	वापस err;
पूर्ण

अटल व्योम s5k83a_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	पूर्णांक address;
	u8 page, old_page;
	m5602_पढ़ो_sensor(sd, S5K83A_PAGE_MAP, &old_page, 1);

	क्रम (page = 0; page < 16; page++) अणु
		m5602_ग_लिखो_sensor(sd, S5K83A_PAGE_MAP, &page, 1);
		pr_info("Dumping the s5k83a register state for page 0x%x\n",
			page);
		क्रम (address = 0; address <= 0xff; address++) अणु
			u8 val = 0;
			m5602_पढ़ो_sensor(sd, address, &val, 1);
			pr_info("register 0x%x contains 0x%x\n", address, val);
		पूर्ण
	पूर्ण
	pr_info("s5k83a register state dump complete\n");

	क्रम (page = 0; page < 16; page++) अणु
		m5602_ग_लिखो_sensor(sd, S5K83A_PAGE_MAP, &page, 1);
		pr_info("Probing for which registers that are read/write for page 0x%x\n",
			page);
		क्रम (address = 0; address <= 0xff; address++) अणु
			u8 old_val, ctrl_val, test_val = 0xff;

			m5602_पढ़ो_sensor(sd, address, &old_val, 1);
			m5602_ग_लिखो_sensor(sd, address, &test_val, 1);
			m5602_पढ़ो_sensor(sd, address, &ctrl_val, 1);

			अगर (ctrl_val == test_val)
				pr_info("register 0x%x is writeable\n",
					address);
			अन्यथा
				pr_info("register 0x%x is read only\n",
					address);

			/* Restore original val */
			m5602_ग_लिखो_sensor(sd, address, &old_val, 1);
		पूर्ण
	पूर्ण
	pr_info("Read/write register probing complete\n");
	m5602_ग_लिखो_sensor(sd, S5K83A_PAGE_MAP, &old_page, 1);
पूर्ण
