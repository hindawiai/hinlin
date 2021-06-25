<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम GalaxyCore GC0310 VGA camera sensor.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
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
#समावेश <linux/पन.स>
#समावेश "../include/linux/atomisp_gmin_platform.h"

#समावेश "gc0310.h"

/* i2c पढ़ो/ग_लिखो stuff */
अटल पूर्णांक gc0310_पढ़ो_reg(काष्ठा i2c_client *client,
			   u16 data_length, u8 reg, u8 *val)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg[2];
	अचिन्हित अक्षर data[1];

	अगर (!client->adapter) अणु
		dev_err(&client->dev, "%s error, no client->adapter\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (data_length != GC0310_8BIT) अणु
		dev_err(&client->dev, "%s error, invalid data length\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	स_रखो(msg, 0, माप(msg));

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = I2C_MSG_LENGTH;
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
	अगर (data_length == GC0310_8BIT)
		*val = (u8)data[0];

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 len, u8 *data)
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

अटल पूर्णांक gc0310_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length,
			    u8 reg, u8 val)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data[2] = अणु0पूर्ण;
	u8 *wreg = (u8 *)data;
	स्थिर u16 len = data_length + माप(u8); /* 8-bit address + data */

	अगर (data_length != GC0310_8BIT) अणु
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* high byte goes out first */
	*wreg = (u8)(reg & 0xff);

	अगर (data_length == GC0310_8BIT)
		data[1] = (u8)(val);

	ret = gc0310_i2c_ग_लिखो(client, len, data);
	अगर (ret)
		dev_err(&client->dev,
			"write error: wrote 0x%x to offset 0x%x error %d",
			val, reg, ret);

	वापस ret;
पूर्ण

/*
 * gc0310_ग_लिखो_reg_array - Initializes a list of GC0310 रेजिस्टरs
 * @client: i2c driver client काष्ठाure
 * @reglist: list of रेजिस्टरs to be written
 *
 * This function initializes a list of रेजिस्टरs. When consecutive addresses
 * are found in a row on the list, this function creates a buffer and sends
 * consecutive data in a single i2c_transfer().
 *
 * __gc0310_flush_reg_array, __gc0310_buf_reg_array() and
 * __gc0310_ग_लिखो_reg_is_consecutive() are पूर्णांकernal functions to
 * gc0310_ग_लिखो_reg_array_fast() and should be not used anywhere अन्यथा.
 *
 */

अटल पूर्णांक __gc0310_flush_reg_array(काष्ठा i2c_client *client,
				    काष्ठा gc0310_ग_लिखो_ctrl *ctrl)
अणु
	u16 size;

	अगर (ctrl->index == 0)
		वापस 0;

	size = माप(u8) + ctrl->index; /* 8-bit address + data */
	ctrl->buffer.addr = (u8)(ctrl->buffer.addr);
	ctrl->index = 0;

	वापस gc0310_i2c_ग_लिखो(client, size, (u8 *)&ctrl->buffer);
पूर्ण

अटल पूर्णांक __gc0310_buf_reg_array(काष्ठा i2c_client *client,
				  काष्ठा gc0310_ग_लिखो_ctrl *ctrl,
				  स्थिर काष्ठा gc0310_reg *next)
अणु
	पूर्णांक size;

	चयन (next->type) अणु
	हाल GC0310_8BIT:
		size = 1;
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* When first item is added, we need to store its starting address */
	अगर (ctrl->index == 0)
		ctrl->buffer.addr = next->reg;

	ctrl->index += size;

	/*
	 * Buffer cannot guarantee मुक्त space क्रम u32? Better flush it to aव्योम
	 * possible lack of memory क्रम next item.
	 */
	अगर (ctrl->index + माप(u8) >= GC0310_MAX_WRITE_BUF_SIZE)
		वापस __gc0310_flush_reg_array(client, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक __gc0310_ग_लिखो_reg_is_consecutive(काष्ठा i2c_client *client,
					     काष्ठा gc0310_ग_लिखो_ctrl *ctrl,
					     स्थिर काष्ठा gc0310_reg *next)
अणु
	अगर (ctrl->index == 0)
		वापस 1;

	वापस ctrl->buffer.addr + ctrl->index == next->reg;
पूर्ण

अटल पूर्णांक gc0310_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				  स्थिर काष्ठा gc0310_reg *reglist)
अणु
	स्थिर काष्ठा gc0310_reg *next = reglist;
	काष्ठा gc0310_ग_लिखो_ctrl ctrl;
	पूर्णांक err;

	ctrl.index = 0;
	क्रम (; next->type != GC0310_TOK_TERM; next++) अणु
		चयन (next->type & GC0310_TOK_MASK) अणु
		हाल GC0310_TOK_DELAY:
			err = __gc0310_flush_reg_array(client, &ctrl);
			अगर (err)
				वापस err;
			msleep(next->val);
			अवरोध;
		शेष:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed beक्रमe proceed.
			 */
			अगर (!__gc0310_ग_लिखो_reg_is_consecutive(client, &ctrl,
							       next)) अणु
				err = __gc0310_flush_reg_array(client, &ctrl);
				अगर (err)
					वापस err;
			पूर्ण
			err = __gc0310_buf_reg_array(client, &ctrl, next);
			अगर (err) अणु
				dev_err(&client->dev, "%s: write error, aborted\n",
					__func__);
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस __gc0310_flush_reg_array(client, &ctrl);
पूर्ण

अटल पूर्णांक gc0310_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (GC0310_FOCAL_LENGTH_NUM << 16) | GC0310_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम imx*/
	*val = (GC0310_F_NUMBER_DEFAULT_NUM << 16) | GC0310_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (GC0310_F_NUMBER_DEFAULT_NUM << 24) |
	       (GC0310_F_NUMBER_DEM << 16) |
	       (GC0310_F_NUMBER_DEFAULT_NUM << 8) | GC0310_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_g_bin_factor_x(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	*val = gc0310_res[dev->fmt_idx].bin_factor_x;

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_g_bin_factor_y(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	*val = gc0310_res[dev->fmt_idx].bin_factor_y;

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				  काष्ठा camera_mipi_info *info,
				  स्थिर काष्ठा gc0310_resolution *res)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	u16 val;
	u8 reg_val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक hori_blanking;
	अचिन्हित पूर्णांक vert_blanking;
	अचिन्हित पूर्णांक sh_delay;

	अगर (!info)
		वापस -EINVAL;

	/* pixel घड़ी calculattion */
	dev->vt_pix_clk_freq_mhz = 14400000; // 16.8MHz
	buf->vt_pix_clk_freq_mhz = dev->vt_pix_clk_freq_mhz;
	pr_info("vt_pix_clk_freq_mhz=%d\n", buf->vt_pix_clk_freq_mhz);

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = GC0310_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    GC0310_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = GC0310_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    GC0310_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = GC0310_FINE_INTG_TIME_MIN;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	/* Getting crop_horizontal_start */
	ret =  gc0310_पढ़ो_reg(client, GC0310_8BIT,
			       GC0310_H_CROP_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret =  gc0310_पढ़ो_reg(client, GC0310_8BIT,
			       GC0310_H_CROP_START_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_start = val | (reg_val & 0xFF);
	pr_info("crop_horizontal_start=%d\n", buf->crop_horizontal_start);

	/* Getting crop_vertical_start */
	ret =  gc0310_पढ़ो_reg(client, GC0310_8BIT,
			       GC0310_V_CROP_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret =  gc0310_पढ़ो_reg(client, GC0310_8BIT,
			       GC0310_V_CROP_START_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_start = val | (reg_val & 0xFF);
	pr_info("crop_vertical_start=%d\n", buf->crop_vertical_start);

	/* Getting output_width */
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_H_OUTSIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_H_OUTSIZE_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = val | (reg_val & 0xFF);
	pr_info("output_width=%d\n", buf->output_width);

	/* Getting output_height */
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_V_OUTSIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_V_OUTSIZE_L, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = val | (reg_val & 0xFF);
	pr_info("output_height=%d\n", buf->output_height);

	buf->crop_horizontal_end = buf->crop_horizontal_start + buf->output_width - 1;
	buf->crop_vertical_end = buf->crop_vertical_start + buf->output_height - 1;
	pr_info("crop_horizontal_end=%d\n", buf->crop_horizontal_end);
	pr_info("crop_vertical_end=%d\n", buf->crop_vertical_end);

	/* Getting line_length_pck */
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_H_BLANKING_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_H_BLANKING_L, &reg_val);
	अगर (ret)
		वापस ret;
	hori_blanking = val | (reg_val & 0xFF);
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_SH_DELAY, &reg_val);
	अगर (ret)
		वापस ret;
	sh_delay = reg_val;
	buf->line_length_pck = buf->output_width + hori_blanking + sh_delay + 4;
	pr_info("hori_blanking=%d sh_delay=%d line_length_pck=%d\n", hori_blanking,
		sh_delay, buf->line_length_pck);

	/* Getting frame_length_lines */
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_V_BLANKING_H, &reg_val);
	अगर (ret)
		वापस ret;
	val = (reg_val & 0xFF) << 8;
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_V_BLANKING_L, &reg_val);
	अगर (ret)
		वापस ret;
	vert_blanking = val | (reg_val & 0xFF);
	buf->frame_length_lines = buf->output_height + vert_blanking;
	pr_info("vert_blanking=%d frame_length_lines=%d\n", vert_blanking,
		buf->frame_length_lines);

	buf->binning_factor_x = res->bin_factor_x ?
				res->bin_factor_x : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				res->bin_factor_y : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_set_gain(काष्ठा v4l2_subdev *sd, पूर्णांक gain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u8 again, dgain;

	अगर (gain < 0x20)
		gain = 0x20;
	अगर (gain > 0x80)
		gain = 0x80;

	अगर (gain >= 0x20 && gain < 0x40) अणु
		again = 0x0; /* वर्ग_मूल(2) */
		dgain = gain;
	पूर्ण अन्यथा अणु
		again = 0x2; /* 2 * वर्ग_मूल(2) */
		dgain = gain / 2;
	पूर्ण

	pr_info("gain=0x%x again=0x%x dgain=0x%x\n", gain, again, dgain);

	/* set analog gain */
	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_AGC_ADJ, again);
	अगर (ret)
		वापस ret;

	/* set digital gain */
	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_DGC_ADJ, dgain);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक __gc0310_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक coarse_itg,
				 पूर्णांक gain, पूर्णांक digitgain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	pr_info("coarse_itg=%d gain=%d digitgain=%d\n", coarse_itg, gain, digitgain);

	/* set exposure */
	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_AEC_PK_EXPO_L,
			       coarse_itg & 0xff);
	अगर (ret)
		वापस ret;

	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_AEC_PK_EXPO_H,
			       (coarse_itg >> 8) & 0x0f);
	अगर (ret)
		वापस ret;

	ret = gc0310_set_gain(sd, gain);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक exposure,
			       पूर्णांक gain, पूर्णांक digitgain)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	ret = __gc0310_set_exposure(sd, exposure, gain, digitgain);
	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल दीर्घ gc0310_s_exposure(काष्ठा v4l2_subdev *sd,
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

	वापस gc0310_set_exposure(sd, exp, gain, digitgain);
पूर्ण

/* TO DO */
अटल पूर्णांक gc0310_v_flip(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	वापस 0;
पूर्ण

/* TO DO */
अटल पूर्णांक gc0310_h_flip(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ gc0310_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस gc0310_s_exposure(sd, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* This वापसs the exposure समय being used. This should only be used
 * क्रम filling in EXIF data, not क्रम actual image processing.
 */
अटल पूर्णांक gc0310_q_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 reg_v;
	पूर्णांक ret;

	/* get exposure */
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_AEC_PK_EXPO_L,
			      &reg_v);
	अगर (ret)
		जाओ err;

	*value = reg_v;
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_AEC_PK_EXPO_H,
			      &reg_v);
	अगर (ret)
		जाओ err;

	*value = *value + (reg_v << 8);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gc0310_device *dev =
	    container_of(ctrl->handler, काष्ठा gc0310_device, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		dev_dbg(&client->dev, "%s: CID_VFLIP:%d.\n",
			__func__, ctrl->val);
		ret = gc0310_v_flip(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		dev_dbg(&client->dev, "%s: CID_HFLIP:%d.\n",
			__func__, ctrl->val);
		ret = gc0310_h_flip(&dev->sd, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gc0310_device *dev =
	    container_of(ctrl->handler, काष्ठा gc0310_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = gc0310_q_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = gc0310_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = gc0310_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = gc0310_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_HORZ:
		ret = gc0310_g_bin_factor_x(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_VERT:
		ret = gc0310_g_bin_factor_y(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = gc0310_s_ctrl,
	.g_अस्थिर_ctrl = gc0310_g_अस्थिर_ctrl
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config gc0310_controls[] = अणु
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
		.id = V4L2_CID_VFLIP,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Flip",
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_HFLIP,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Mirror",
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCAL_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "focal length",
		.min = GC0310_FOCAL_LENGTH_DEFAULT,
		.max = GC0310_FOCAL_LENGTH_DEFAULT,
		.step = 0x01,
		.def = GC0310_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number",
		.min = GC0310_F_NUMBER_DEFAULT,
		.max = GC0310_F_NUMBER_DEFAULT,
		.step = 0x01,
		.def = GC0310_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number range",
		.min = GC0310_F_NUMBER_RANGE,
		.max = GC0310_F_NUMBER_RANGE,
		.step = 0x01,
		.def = GC0310_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_HORZ,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "horizontal binning factor",
		.min = 0,
		.max = GC0310_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_VERT,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "vertical binning factor",
		.min = 0,
		.max = GC0310_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक gc0310_init(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	pr_info("%s S\n", __func__);
	mutex_lock(&dev->input_lock);

	/* set initial रेजिस्टरs */
	ret  = gc0310_ग_लिखो_reg_array(client, gc0310_reset_रेजिस्टर);

	/* restore settings */
	gc0310_res = gc0310_res_preview;
	N_RES = N_RES_PREVIEW;

	mutex_unlock(&dev->input_lock);

	pr_info("%s E\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret = 0;
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	अगर (flag) अणु
		/* The upstream module driver (written to Crystal
		 * Cove) had this logic to pulse the rails low first.
		 * This appears to अवरोध things on the MRD7 with the
		 * X-Powers PMIC...
		 *
		 *     ret = dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		 *     ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 0);
		 *     mdelay(50);
		 */
		ret |= dev->platक्रमm_data->v1p8_ctrl(sd, 1);
		ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 1);
		usleep_range(10000, 15000);
	पूर्ण

	अगर (!flag || ret) अणु
		ret |= dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gpio_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret;
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	/* GPIO0 == "reset" (active low), GPIO1 == "power down" */
	अगर (flag) अणु
		/* Pulse reset, then release घातer करोwn */
		ret = dev->platक्रमm_data->gpio0_ctrl(sd, 0);
		usleep_range(5000, 10000);
		ret |= dev->platक्रमm_data->gpio0_ctrl(sd, 1);
		usleep_range(10000, 15000);
		ret |= dev->platक्रमm_data->gpio1_ctrl(sd, 0);
		usleep_range(10000, 15000);
	पूर्ण अन्यथा अणु
		ret = dev->platक्रमm_data->gpio1_ctrl(sd, 1);
		ret |= dev->platक्रमm_data->gpio0_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक घातer_करोwn(काष्ठा v4l2_subdev *sd);

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	pr_info("%s S\n", __func__);
	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		वापस -ENODEV;
	पूर्ण

	/* घातer control */
	ret = घातer_ctrl(sd, 1);
	अगर (ret)
		जाओ fail_घातer;

	/* flis घड़ी control */
	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 1);
	अगर (ret)
		जाओ fail_clk;

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 1);
	अगर (ret) अणु
		ret = gpio_ctrl(sd, 1);
		अगर (ret)
			जाओ fail_gpio;
	पूर्ण

	msleep(100);

	pr_info("%s E\n", __func__);
	वापस 0;

fail_gpio:
	dev->platक्रमm_data->flisclk_ctrl(sd, 0);
fail_clk:
	घातer_ctrl(sd, 0);
fail_घातer:
	dev_err(&client->dev, "sensor power-up failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक घातer_करोwn(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
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

अटल पूर्णांक gc0310_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on == 0)
		वापस घातer_करोwn(sd);

	ret = घातer_up(sd);
	अगर (ret)
		वापस ret;

	वापस gc0310_init(sd);
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
अटल पूर्णांक distance(काष्ठा gc0310_resolution *res, u32 w, u32 h)
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

	अगर ((w_ratio < 8192) || (h_ratio < 8192)  ||
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
	काष्ठा gc0310_resolution *पंचांगp_res = शून्य;

	क्रम (i = 0; i < N_RES; i++) अणु
		पंचांगp_res = &gc0310_res[i];
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
		अगर (w != gc0310_res[i].width)
			जारी;
		अगर (h != gc0310_res[i].height)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* TODO: हटाओ it. */
अटल पूर्णांक startup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	pr_info("%s S\n", __func__);

	ret = gc0310_ग_लिखो_reg_array(client, gc0310_res[dev->fmt_idx].regs);
	अगर (ret) अणु
		dev_err(&client->dev, "gc0310 write register err.\n");
		वापस ret;
	पूर्ण

	pr_info("%s E\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *gc0310_info = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक idx = 0;

	pr_info("%s S\n", __func__);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	gc0310_info = v4l2_get_subdev_hostdata(sd);
	अगर (!gc0310_info)
		वापस -EINVAL;

	mutex_lock(&dev->input_lock);

	idx = nearest_resolution_index(fmt->width, fmt->height);
	अगर (idx == -1) अणु
		/* वापस the largest resolution */
		fmt->width = gc0310_res[N_RES - 1].width;
		fmt->height = gc0310_res[N_RES - 1].height;
	पूर्ण अन्यथा अणु
		fmt->width = gc0310_res[idx].width;
		fmt->height = gc0310_res[idx].height;
	पूर्ण
	fmt->code = MEDIA_BUS_FMT_SGRBG8_1X8;

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

	prपूर्णांकk("%s: before gc0310_write_reg_array %s\n", __func__,
	       gc0310_res[dev->fmt_idx].desc);
	ret = startup(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc0310 startup err\n");
		जाओ err;
	पूर्ण

	ret = gc0310_get_पूर्णांकg_factor(client, gc0310_info,
				     &gc0310_res[dev->fmt_idx]);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to get integration_factor\n");
		जाओ err;
	पूर्ण

	pr_info("%s E\n", __func__);
err:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	fmt->width = gc0310_res[dev->fmt_idx].width;
	fmt->height = gc0310_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SGRBG8_1X8;

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_detect(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 high, low;
	पूर्णांक ret;
	u16 id;

	pr_info("%s S\n", __func__);
	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_SC_CMMN_CHIP_ID_H, &high);
	अगर (ret) अणु
		dev_err(&client->dev, "read sensor_id_high failed\n");
		वापस -ENODEV;
	पूर्ण
	ret = gc0310_पढ़ो_reg(client, GC0310_8BIT,
			      GC0310_SC_CMMN_CHIP_ID_L, &low);
	अगर (ret) अणु
		dev_err(&client->dev, "read sensor_id_low failed\n");
		वापस -ENODEV;
	पूर्ण
	id = ((((u16)high) << 8) | (u16)low);
	pr_info("sensor ID = 0x%x\n", id);

	अगर (id != GC0310_ID) अणु
		dev_err(&client->dev, "sensor ID error, read id = 0x%x, target id = 0x%x\n", id,
			GC0310_ID);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&client->dev, "detect gc0310 success\n");

	pr_info("%s E\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	pr_info("%s S enable=%d\n", __func__, enable);
	mutex_lock(&dev->input_lock);

	अगर (enable) अणु
		/* enable per frame MIPI and sensor ctrl reset  */
		ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
				       0xFE, 0x30);
		अगर (ret) अणु
			mutex_unlock(&dev->input_lock);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_RESET_RELATED, GC0310_REGISTER_PAGE_3);
	अगर (ret) अणु
		mutex_unlock(&dev->input_lock);
		वापस ret;
	पूर्ण

	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT, GC0310_SW_STREAM,
			       enable ? GC0310_START_STREAMING :
			       GC0310_STOP_STREAMING);
	अगर (ret) अणु
		mutex_unlock(&dev->input_lock);
		वापस ret;
	पूर्ण

	ret = gc0310_ग_लिखो_reg(client, GC0310_8BIT,
			       GC0310_RESET_RELATED, GC0310_REGISTER_PAGE_0);
	अगर (ret) अणु
		mutex_unlock(&dev->input_lock);
		वापस ret;
	पूर्ण

	mutex_unlock(&dev->input_lock);
	pr_info("%s E\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक gc0310_s_config(काष्ठा v4l2_subdev *sd,
			   पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	pr_info("%s S\n", __func__);
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
		dev_err(&client->dev, "gc0310 power-off err.\n");
		जाओ fail_घातer_off;
	पूर्ण

	ret = घातer_up(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc0310 power-up err.\n");
		जाओ fail_घातer_on;
	पूर्ण

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	/* config & detect sensor */
	ret = gc0310_detect(client);
	अगर (ret) अणु
		dev_err(&client->dev, "gc0310_detect err s_config.\n");
		जाओ fail_csi_cfg;
	पूर्ण

	/* turn off sensor, after probed */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "gc0310 power-off err.\n");
		जाओ fail_csi_cfg;
	पूर्ण
	mutex_unlock(&dev->input_lock);

	pr_info("%s E\n", __func__);
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

अटल पूर्णांक gc0310_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = gc0310_res[dev->fmt_idx].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG8_1X8;
	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = gc0310_res[index].width;
	fse->min_height = gc0310_res[index].height;
	fse->max_width = gc0310_res[index].width;
	fse->max_height = gc0310_res[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_g_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	mutex_lock(&dev->input_lock);
	*frames = gc0310_res[dev->fmt_idx].skip_frames;
	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops gc0310_sensor_ops = अणु
	.g_skip_frames	= gc0310_g_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops gc0310_video_ops = अणु
	.s_stream = gc0310_s_stream,
	.g_frame_पूर्णांकerval = gc0310_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops gc0310_core_ops = अणु
	.s_घातer = gc0310_s_घातer,
	.ioctl = gc0310_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops gc0310_pad_ops = अणु
	.क्रमागत_mbus_code = gc0310_क्रमागत_mbus_code,
	.क्रमागत_frame_size = gc0310_क्रमागत_frame_size,
	.get_fmt = gc0310_get_fmt,
	.set_fmt = gc0310_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops gc0310_ops = अणु
	.core = &gc0310_core_ops,
	.video = &gc0310_video_ops,
	.pad = &gc0310_pad_ops,
	.sensor = &gc0310_sensor_ops,
पूर्ण;

अटल पूर्णांक gc0310_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा gc0310_device *dev = to_gc0310_sensor(sd);

	dev_dbg(&client->dev, "gc0310_remove...\n");

	dev->platक्रमm_data->csi_cfg(sd, 0);

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&dev->sd.entity);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक gc0310_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा gc0310_device *dev;
	पूर्णांक ret;
	व्योम *pdata;
	अचिन्हित पूर्णांक i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&dev->sd, client, &gc0310_ops);

	pdata = gmin_camera_platक्रमm_data(&dev->sd,
					  ATOMISP_INPUT_FORMAT_RAW_8,
					  atomisp_bayer_order_grbg);
	अगर (!pdata) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ret = gc0310_s_config(&dev->sd, client->irq, pdata);
	अगर (ret)
		जाओ out_मुक्त;

	ret = atomisp_रेजिस्टर_i2c_module(&dev->sd, pdata, RAW_CAMERA);
	अगर (ret)
		जाओ out_मुक्त;

	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->क्रमmat.code = MEDIA_BUS_FMT_SGRBG8_1X8;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret =
	    v4l2_ctrl_handler_init(&dev->ctrl_handler,
				   ARRAY_SIZE(gc0310_controls));
	अगर (ret) अणु
		gc0310_हटाओ(client);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(gc0310_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &gc0310_controls[i],
				     शून्य);

	अगर (dev->ctrl_handler.error) अणु
		gc0310_हटाओ(client);
		वापस dev->ctrl_handler.error;
	पूर्ण

	/* Use same lock क्रम controls as क्रम everything अन्यथा. */
	dev->ctrl_handler.lock = &dev->input_lock;
	dev->sd.ctrl_handler = &dev->ctrl_handler;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret)
		gc0310_हटाओ(client);

	pr_info("%s E\n", __func__);
	वापस ret;
out_मुक्त:
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id gc0310_acpi_match[] = अणु
	अणु"XXGC0310"पूर्ण,
	अणु"INT0310"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, gc0310_acpi_match);

अटल काष्ठा i2c_driver gc0310_driver = अणु
	.driver = अणु
		.name = "gc0310",
		.acpi_match_table = gc0310_acpi_match,
	पूर्ण,
	.probe_new = gc0310_probe,
	.हटाओ = gc0310_हटाओ,
पूर्ण;
module_i2c_driver(gc0310_driver);

MODULE_AUTHOR("Lai, Angie <angie.lai@intel.com>");
MODULE_DESCRIPTION("A low-level driver for GalaxyCore GC0310 sensors");
MODULE_LICENSE("GPL");
