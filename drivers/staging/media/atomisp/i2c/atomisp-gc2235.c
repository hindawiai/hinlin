<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम GalaxyCore GC2235 2M camera sensor.
 *
 * Copyright (c) 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/moduleparam.h>
#समावेश <media/v4l2-device.h>
#समावेश "../include/linux/atomisp_gmin_platform.h"
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

#समावेश "gc2235.h"

/* i2c पढ़ो/ग_लिखो stuff */
अटल पूर्णांक gc2235_पढ़ो_reg(काष्ठा i2c_client *client,
			   u16 data_length, u16 reg, u16 *val)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg[2];
	अचिन्हित अक्षर data[6];

	अगर (!client->adapter) अणु
		dev_err(&client->dev, "%s error, no client->adapter\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (data_length != GC2235_8BIT) अणु
		dev_err(&client->dev, "%s error, invalid data length\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	स_रखो(msg, 0, माप(msg));

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = data;

	/* high byte goes out first */
	data[0] = (u8)(reg & 0xff);

	msg[1].addr = client->addr;
	msg[1].len = data_length;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = data;

	err = i2c_transfer(client->adapter, msg, 2);
	अगर (err != 2) अणु
		अगर (err >= 0)
			err = -EIO;
		dev_err(&client->dev,
			"read from offset 0x%x error %d", reg, err);
		वापस err;
	पूर्ण

	*val = 0;
	/* high byte comes first */
	अगर (data_length == GC2235_8BIT)
		*val = (u8)data[0];

	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 len, u8 *data)
अणु
	काष्ठा i2c_msg msg;
	स्थिर पूर्णांक num_msg = 1;
	पूर्णांक ret;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = len;
	msg.buf = data;
	ret = i2c_transfer(client->adapter, &msg, 1);

	वापस ret == num_msg ? 0 : -EIO;
पूर्ण

अटल पूर्णांक gc2235_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length,
			    u8 reg, u8 val)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data[4] = अणु0पूर्ण;
	स्थिर u16 len = data_length + माप(u8); /* 16-bit address + data */

	अगर (data_length != GC2235_8BIT) अणु
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* high byte goes out first */
	data[0] = reg;
	data[1] = val;

	ret = gc2235_i2c_ग_लिखो(client, len, data);
	अगर (ret)
		dev_err(&client->dev,
			"write error: wrote 0x%x to offset 0x%x error %d",
			val, reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __gc2235_flush_reg_array(काष्ठा i2c_client *client,
				    काष्ठा gc2235_ग_लिखो_ctrl *ctrl)
अणु
	u16 size;

	अगर (ctrl->index == 0)
		वापस 0;

	size = माप(u8) + ctrl->index; /* 8-bit address + data */
	ctrl->index = 0;

	वापस gc2235_i2c_ग_लिखो(client, size, (u8 *)&ctrl->buffer);
पूर्ण

अटल पूर्णांक __gc2235_buf_reg_array(काष्ठा i2c_client *client,
				  काष्ठा gc2235_ग_लिखो_ctrl *ctrl,
				  स्थिर काष्ठा gc2235_reg *next)
अणु
	पूर्णांक size;

	अगर (next->type != GC2235_8BIT)
		वापस -EINVAL;

	size = 1;
	ctrl->buffer.data[ctrl->index] = (u8)next->val;

	/* When first item is added, we need to store its starting address */
	अगर (ctrl->index == 0)
		ctrl->buffer.addr = next->reg;

	ctrl->index += size;

	/*
	 * Buffer cannot guarantee मुक्त space क्रम u32? Better flush it to aव्योम
	 * possible lack of memory क्रम next item.
	 */
	अगर (ctrl->index + माप(u8) >= GC2235_MAX_WRITE_BUF_SIZE)
		वापस __gc2235_flush_reg_array(client, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक __gc2235_ग_लिखो_reg_is_consecutive(काष्ठा i2c_client *client,
	काष्ठा gc2235_ग_लिखो_ctrl *ctrl,
	स्थिर काष्ठा gc2235_reg *next)
अणु
	अगर (ctrl->index == 0)
		वापस 1;

	वापस ctrl->buffer.addr + ctrl->index == next->reg;
पूर्ण

अटल पूर्णांक gc2235_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				  स्थिर काष्ठा gc2235_reg *reglist)
अणु
	स्थिर काष्ठा gc2235_reg *next = reglist;
	काष्ठा gc2235_ग_लिखो_ctrl ctrl;
	पूर्णांक err;

	ctrl.index = 0;
	क्रम (; next->type != GC2235_TOK_TERM; next++) अणु
		चयन (next->type & GC2235_TOK_MASK) अणु
		हाल GC2235_TOK_DELAY:
			err = __gc2235_flush_reg_array(client, &ctrl);
			अगर (err)
				वापस err;
			msleep(next->val);
			अवरोध;
		शेष:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed beक्रमe proceed.
			 */
			अगर (!__gc2235_ग_लिखो_reg_is_consecutive(client, &ctrl,
							       next)) अणु
				err = __gc2235_flush_reg_array(client, &ctrl);
				अगर (err)
					वापस err;
			पूर्ण
			err = __gc2235_buf_reg_array(client, &ctrl, next);
			अगर (err) अणु
				dev_err(&client->dev, "%s: write error, aborted\n",
					__func__);
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस __gc2235_flush_reg_array(client, &ctrl);
पूर्ण

अटल पूर्णांक gc2235_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (GC2235_FOCAL_LENGTH_NUM << 16) | GC2235_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम imx*/
	*val = (GC2235_F_NUMBER_DEFAULT_NUM << 16) | GC2235_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (GC2235_F_NUMBER_DEFAULT_NUM << 24) |
	       (GC2235_F_NUMBER_DEM << 16) |
	       (GC2235_F_NUMBER_DEFAULT_NUM << 8) | GC2235_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				  काष्ठा camera_mipi_info *info,
				  स्थिर काष्ठा gc2235_resolution *res)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	u16 reg_val, reg_val_h;
	पूर्णांक ret;

	अगर (!info)
		वापस -EINVAL;

	/* pixel घड़ी calculattion */
	buf->vt_pix_clk_freq_mhz = dev->vt_pix_clk_freq_mhz = 30000000;

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = GC2235_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    GC2235_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = GC2235_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    GC2235_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = GC2235_FINE_INTG_TIME_MIN;
	buf->frame_length_lines = res->lines_per_frame;
	buf->line_length_pck = res->pixels_per_line;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	ret =  gc2235_पढ़ो_reg(client, GC2235_8BIT,
			       GC2235_H_CROP_START_H, &reg_val_h);
	ret =  gc2235_पढ़ो_reg(client, GC2235_8BIT,
			       GC2235_H_CROP_START_L, &reg_val);
	अगर (ret)
		वापस ret;

	buf->crop_horizontal_start = (reg_val_h << 8) | reg_val;

	ret =  gc2235_पढ़ो_reg(client, GC2235_8BIT,
			       GC2235_V_CROP_START_H, &reg_val_h);
	ret =  gc2235_पढ़ो_reg(client, GC2235_8BIT,
			       GC2235_V_CROP_START_L, &reg_val);
	अगर (ret)
		वापस ret;

	buf->crop_vertical_start = (reg_val_h << 8) | reg_val;

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_H_OUTSIZE_H, &reg_val_h);
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_H_OUTSIZE_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = (reg_val_h << 8) | reg_val;

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_V_OUTSIZE_H, &reg_val_h);
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_V_OUTSIZE_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = (reg_val_h << 8) | reg_val;

	buf->crop_horizontal_end = buf->crop_horizontal_start +
				   buf->output_width - 1;
	buf->crop_vertical_end = buf->crop_vertical_start +
				 buf->output_height - 1;

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_HB_H, &reg_val_h);
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_HB_L, &reg_val);
	अगर (ret)
		वापस ret;

#अगर 0
	u16 dummy = (reg_val_h << 8) | reg_val;
#पूर्ण_अगर

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_SH_DELAY_H, &reg_val_h);
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_SH_DELAY_L, &reg_val);

#अगर 0
	buf->line_length_pck = buf->output_width + 16 + dummy +
			       (((u16)reg_val_h << 8) | (u16)reg_val) + 4;
#पूर्ण_अगर
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_VB_H, &reg_val_h);
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_VB_L, &reg_val);
	अगर (ret)
		वापस ret;

#अगर 0
	buf->frame_length_lines = buf->output_height + 32 +
				  (((u16)reg_val_h << 8) | (u16)reg_val);
#पूर्ण_अगर
	buf->binning_factor_x = res->bin_factor_x ?
				res->bin_factor_x : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				res->bin_factor_y : 1;
	वापस 0;
पूर्ण

अटल दीर्घ __gc2235_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक coarse_itg,
				  पूर्णांक gain, पूर्णांक digitgain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 coarse_पूर्णांकegration = (u16)coarse_itg;
	पूर्णांक ret = 0;
	u16 expo_coarse_h, expo_coarse_l, gain_val = 0xF0, gain_val2 = 0xF0;

	expo_coarse_h = coarse_पूर्णांकegration >> 8;
	expo_coarse_l = coarse_पूर्णांकegration & 0xff;

	ret = gc2235_ग_लिखो_reg(client, GC2235_8BIT,
			       GC2235_EXPOSURE_H, expo_coarse_h);
	ret = gc2235_ग_लिखो_reg(client, GC2235_8BIT,
			       GC2235_EXPOSURE_L, expo_coarse_l);

	अगर (gain <= 0x58) अणु
		gain_val = 0x40;
		gain_val2 = 0x58;
	पूर्ण अन्यथा अगर (gain < 256) अणु
		gain_val = 0x40;
		gain_val2 = gain;
	पूर्ण अन्यथा अणु
		gain_val2 = 64 * gain / 256;
		gain_val = 0xff;
	पूर्ण

	ret = gc2235_ग_लिखो_reg(client, GC2235_8BIT,
			       GC2235_GLOBAL_GAIN, (u8)gain_val);
	ret = gc2235_ग_लिखो_reg(client, GC2235_8BIT,
			       GC2235_PRE_GAIN, (u8)gain_val2);

	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक exposure,
			       पूर्णांक gain, पूर्णांक digitgain)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	ret = __gc2235_set_exposure(sd, exposure, gain, digitgain);
	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल दीर्घ gc2235_s_exposure(काष्ठा v4l2_subdev *sd,
			      काष्ठा atomisp_exposure *exposure)
अणु
	पूर्णांक exp = exposure->पूर्णांकegration_समय[0];
	पूर्णांक gain = exposure->gain[0];
	पूर्णांक digitgain = exposure->gain[1];

	/* we should not accept the invalid value below. */
	अगर (gain == 0) अणु
		काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

		v4l2_err(client, "%s: invalid value\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस gc2235_set_exposure(sd, exp, gain, digitgain);
पूर्ण

अटल दीर्घ gc2235_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस gc2235_s_exposure(sd, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* This वापसs the exposure समय being used. This should only be used
 * क्रम filling in EXIF data, not क्रम actual image processing.
 */
अटल पूर्णांक gc2235_q_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 reg_v, reg_v2;
	पूर्णांक ret;

	/* get exposure */
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_EXPOSURE_L,
			      &reg_v);
	अगर (ret)
		जाओ err;

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_EXPOSURE_H,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	reg_v += reg_v2 << 8;

	*value = reg_v;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gc2235_device *dev =
	    container_of(ctrl->handler, काष्ठा gc2235_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = gc2235_q_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = gc2235_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = gc2235_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = gc2235_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.g_अस्थिर_ctrl = gc2235_g_अस्थिर_ctrl
पूर्ण;

अटल काष्ठा v4l2_ctrl_config gc2235_controls[] = अणु
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_EXPOSURE_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "exposure",
		.min = 0x0,
		.max = 0xffff,
		.step = 0x01,
		.def = 0x00,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCAL_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "focal length",
		.min = GC2235_FOCAL_LENGTH_DEFAULT,
		.max = GC2235_FOCAL_LENGTH_DEFAULT,
		.step = 0x01,
		.def = GC2235_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number",
		.min = GC2235_F_NUMBER_DEFAULT,
		.max = GC2235_F_NUMBER_DEFAULT,
		.step = 0x01,
		.def = GC2235_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number range",
		.min = GC2235_F_NUMBER_RANGE,
		.max = GC2235_F_NUMBER_RANGE,
		.step = 0x01,
		.def = GC2235_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __gc2235_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	/* restore settings */
	gc2235_res = gc2235_res_preview;
	N_RES = N_RES_PREVIEW;

	वापस gc2235_ग_लिखो_reg_array(client, gc2235_init_settings);
पूर्ण

अटल पूर्णांक is_init;

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret = -1;
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	अगर (flag) अणु
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 1);
		usleep_range(60, 90);
		अगर (ret == 0)
			ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 1);
	पूर्ण अन्यथा अणु
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gpio_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	पूर्णांक ret = -1;

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	ret |= dev->platक्रमm_data->gpio1_ctrl(sd, !flag);
	usleep_range(60, 90);
	वापस dev->platक्रमm_data->gpio0_ctrl(sd, flag);
पूर्ण

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		वापस -ENODEV;
	पूर्ण
	/* घातer control */
	ret = घातer_ctrl(sd, 1);
	अगर (ret)
		जाओ fail_घातer;

	/* according to DS, at least 5ms is needed between DOVDD and PWDN */
	usleep_range(5000, 6000);

	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 1);
	अगर (ret)
		जाओ fail_clk;
	usleep_range(5000, 6000);

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 1);
	अगर (ret) अणु
		ret = gpio_ctrl(sd, 1);
		अगर (ret)
			जाओ fail_घातer;
	पूर्ण

	msleep(5);
	वापस 0;

fail_clk:
	gpio_ctrl(sd, 0);
fail_घातer:
	घातer_ctrl(sd, 0);
	dev_err(&client->dev, "sensor power-up failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक घातer_करोwn(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		वापस -ENODEV;
	पूर्ण
	/* gpio ctrl */
	ret = gpio_ctrl(sd, 0);
	अगर (ret) अणु
		ret = gpio_ctrl(sd, 0);
		अगर (ret)
			dev_err(&client->dev, "gpio failed 2\n");
	पूर्ण

	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "flisclk failed\n");

	/* घातer control */
	ret = घातer_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "vprog failed.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on == 0)
		ret = घातer_करोwn(sd);
	अन्यथा अणु
		ret = घातer_up(sd);
		अगर (!ret)
			ret = __gc2235_init(sd);
		is_init = 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * distance - calculate the distance
 * @res: resolution
 * @w: width
 * @h: height
 *
 * Get the gap between resolution and w/h.
 * res->width/height smaller than w/h wouldn't be considered.
 * Returns the value of gap or -1 अगर fail.
 */
#घोषणा LARGEST_ALLOWED_RATIO_MISMATCH 800
अटल पूर्णांक distance(काष्ठा gc2235_resolution *res, u32 w, u32 h)
अणु
	अचिन्हित पूर्णांक w_ratio = (res->width << 13) / w;
	अचिन्हित पूर्णांक h_ratio;
	पूर्णांक match;

	अगर (h == 0)
		वापस -1;
	h_ratio = (res->height << 13) / h;
	अगर (h_ratio == 0)
		वापस -1;
	match   = असल(((w_ratio << 13) / h_ratio) - 8192);

	अगर ((w_ratio < 8192) || (h_ratio < 8192) ||
	    (match > LARGEST_ALLOWED_RATIO_MISMATCH))
		वापस -1;

	वापस w_ratio + h_ratio;
पूर्ण

/* Return the nearest higher resolution index */
अटल पूर्णांक nearest_resolution_index(पूर्णांक w, पूर्णांक h)
अणु
	पूर्णांक i;
	पूर्णांक idx = -1;
	पूर्णांक dist;
	पूर्णांक min_dist = पूर्णांक_उच्च;
	काष्ठा gc2235_resolution *पंचांगp_res = शून्य;

	क्रम (i = 0; i < N_RES; i++) अणु
		पंचांगp_res = &gc2235_res[i];
		dist = distance(पंचांगp_res, w, h);
		अगर (dist == -1)
			जारी;
		अगर (dist < min_dist) अणु
			min_dist = dist;
			idx = i;
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक get_resolution_index(पूर्णांक w, पूर्णांक h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RES; i++) अणु
		अगर (w != gc2235_res[i].width)
			जारी;
		अगर (h != gc2235_res[i].height)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक startup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (is_init == 0) अणु
		/* क्रमce gc2235 to करो a reset in res change, otherwise it
		* can not output normal after चयनing res. and it is not
		* necessary क्रम first समय run up after घातer on, क्रम the sack
		* of perक्रमmance
		*/
		घातer_करोwn(sd);
		घातer_up(sd);
		gc2235_ग_लिखो_reg_array(client, gc2235_init_settings);
	पूर्ण

	ret = gc2235_ग_लिखो_reg_array(client, gc2235_res[dev->fmt_idx].regs);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235 write register err.\n");
		वापस ret;
	पूर्ण
	is_init = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *gc2235_info = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक idx;

	gc2235_info = v4l2_get_subdev_hostdata(sd);
	अगर (!gc2235_info)
		वापस -EINVAL;
	अगर (क्रमmat->pad)
		वापस -EINVAL;
	अगर (!fmt)
		वापस -EINVAL;
	mutex_lock(&dev->input_lock);
	idx = nearest_resolution_index(fmt->width, fmt->height);
	अगर (idx == -1) अणु
		/* वापस the largest resolution */
		fmt->width = gc2235_res[N_RES - 1].width;
		fmt->height = gc2235_res[N_RES - 1].height;
	पूर्ण अन्यथा अणु
		fmt->width = gc2235_res[idx].width;
		fmt->height = gc2235_res[idx].height;
	पूर्ण
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *fmt;
		mutex_unlock(&dev->input_lock);
		वापस 0;
	पूर्ण

	dev->fmt_idx = get_resolution_index(fmt->width, fmt->height);
	अगर (dev->fmt_idx == -1) अणु
		dev_err(&client->dev, "get resolution fail\n");
		mutex_unlock(&dev->input_lock);
		वापस -EINVAL;
	पूर्ण

	ret = startup(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235 startup err\n");
		जाओ err;
	पूर्ण

	ret = gc2235_get_पूर्णांकg_factor(client, gc2235_info,
				     &gc2235_res[dev->fmt_idx]);
	अगर (ret)
		dev_err(&client->dev, "failed to get integration_factor\n");

err:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	fmt->width = gc2235_res[dev->fmt_idx].width;
	fmt->height = gc2235_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_detect(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 high, low;
	पूर्णांक ret;
	u16 id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_SENSOR_ID_H, &high);
	अगर (ret) अणु
		dev_err(&client->dev, "sensor_id_high = 0x%x\n", high);
		वापस -ENODEV;
	पूर्ण
	ret = gc2235_पढ़ो_reg(client, GC2235_8BIT,
			      GC2235_SENSOR_ID_L, &low);
	id = ((high << 8) | low);

	अगर (id != GC2235_ID) अणु
		dev_err(&client->dev, "sensor ID error, 0x%x\n", id);
		वापस -ENODEV;
	पूर्ण

	dev_info(&client->dev, "detect gc2235 success\n");
	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);

	अगर (enable)
		ret = gc2235_ग_लिखो_reg_array(client, gc2235_stream_on);
	अन्यथा
		ret = gc2235_ग_लिखो_reg_array(client, gc2235_stream_off);

	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_s_config(काष्ठा v4l2_subdev *sd,
			   पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (!platक्रमm_data)
		वापस -ENODEV;

	dev->platक्रमm_data =
	    (काष्ठा camera_sensor_platक्रमm_data *)platक्रमm_data;

	mutex_lock(&dev->input_lock);
	/* घातer off the module, then घातer on it in future
	 * as first घातer on by board may not fulfill the
	 * घातer on sequqence needed by the module
	 */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235 power-off err.\n");
		जाओ fail_घातer_off;
	पूर्ण

	ret = घातer_up(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235 power-up err.\n");
		जाओ fail_घातer_on;
	पूर्ण

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	/* config & detect sensor */
	ret = gc2235_detect(client);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235_detect err s_config.\n");
		जाओ fail_csi_cfg;
	पूर्ण

	/* turn off sensor, after probed */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc2235 power-off err.\n");
		जाओ fail_csi_cfg;
	पूर्ण
	mutex_unlock(&dev->input_lock);

	वापस 0;

fail_csi_cfg:
	dev->platक्रमm_data->csi_cfg(sd, 0);
fail_घातer_on:
	घातer_करोwn(sd);
	dev_err(&client->dev, "sensor power-gating failed\n");
fail_घातer_off:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gc2235_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = gc2235_res[dev->fmt_idx].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = gc2235_res[index].width;
	fse->min_height = gc2235_res[index].height;
	fse->max_width = gc2235_res[index].width;
	fse->max_height = gc2235_res[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_g_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);

	mutex_lock(&dev->input_lock);
	*frames = gc2235_res[dev->fmt_idx].skip_frames;
	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops gc2235_sensor_ops = अणु
	.g_skip_frames	= gc2235_g_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops gc2235_video_ops = अणु
	.s_stream = gc2235_s_stream,
	.g_frame_पूर्णांकerval = gc2235_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops gc2235_core_ops = अणु
	.s_घातer = gc2235_s_घातer,
	.ioctl = gc2235_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops gc2235_pad_ops = अणु
	.क्रमागत_mbus_code = gc2235_क्रमागत_mbus_code,
	.क्रमागत_frame_size = gc2235_क्रमागत_frame_size,
	.get_fmt = gc2235_get_fmt,
	.set_fmt = gc2235_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops gc2235_ops = अणु
	.core = &gc2235_core_ops,
	.video = &gc2235_video_ops,
	.pad = &gc2235_pad_ops,
	.sensor = &gc2235_sensor_ops,
पूर्ण;

अटल पूर्णांक gc2235_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा gc2235_device *dev = to_gc2235_sensor(sd);

	dev_dbg(&client->dev, "gc2235_remove...\n");

	dev->platक्रमm_data->csi_cfg(sd, 0);

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&dev->sd.entity);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक gc2235_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा gc2235_device *dev;
	व्योम *gcpdev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&dev->sd, client, &gc2235_ops);

	gcpdev = gmin_camera_platक्रमm_data(&dev->sd,
					   ATOMISP_INPUT_FORMAT_RAW_10,
					   atomisp_bayer_order_grbg);

	ret = gc2235_s_config(&dev->sd, client->irq, gcpdev);
	अगर (ret)
		जाओ out_मुक्त;

	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->क्रमmat.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret =
	    v4l2_ctrl_handler_init(&dev->ctrl_handler,
				   ARRAY_SIZE(gc2235_controls));
	अगर (ret) अणु
		gc2235_हटाओ(client);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(gc2235_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &gc2235_controls[i],
				     शून्य);

	अगर (dev->ctrl_handler.error) अणु
		gc2235_हटाओ(client);
		वापस dev->ctrl_handler.error;
	पूर्ण

	/* Use same lock क्रम controls as क्रम everything अन्यथा. */
	dev->ctrl_handler.lock = &dev->input_lock;
	dev->sd.ctrl_handler = &dev->ctrl_handler;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret)
		gc2235_हटाओ(client);

	वापस atomisp_रेजिस्टर_i2c_module(&dev->sd, gcpdev, RAW_CAMERA);

out_मुक्त:
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	kमुक्त(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id gc2235_acpi_match[] = अणु
	अणु "INT33F8" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, gc2235_acpi_match);

अटल काष्ठा i2c_driver gc2235_driver = अणु
	.driver = अणु
		.name = "gc2235",
		.acpi_match_table = gc2235_acpi_match,
	पूर्ण,
	.probe_new = gc2235_probe,
	.हटाओ = gc2235_हटाओ,
पूर्ण;
module_i2c_driver(gc2235_driver);

MODULE_AUTHOR("Shuguang Gong <Shuguang.Gong@intel.com>");
MODULE_DESCRIPTION("A low-level driver for GC2235 sensors");
MODULE_LICENSE("GPL");
