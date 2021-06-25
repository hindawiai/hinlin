<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम OmniVision OV2722 1080p HD camera sensor.
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
#समावेश "../include/linux/atomisp_gmin_platform.h"
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

#समावेश "ov2722.h"

/* i2c पढ़ो/ग_लिखो stuff */
अटल पूर्णांक ov2722_पढ़ो_reg(काष्ठा i2c_client *client,
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

	अगर (data_length != OV2722_8BIT && data_length != OV2722_16BIT
	    && data_length != OV2722_32BIT) अणु
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
	data[0] = (u8)(reg >> 8);
	data[1] = (u8)(reg & 0xff);

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
	अगर (data_length == OV2722_8BIT)
		*val = (u8)data[0];
	अन्यथा अगर (data_length == OV2722_16BIT)
		*val = be16_to_cpu(*(__be16 *)&data[0]);
	अन्यथा
		*val = be32_to_cpu(*(__be32 *)&data[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 len, u8 *data)
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

अटल पूर्णांक ov2722_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length,
			    u16 reg, u16 val)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data[4] = अणु0पूर्ण;
	__be16 *wreg = (__be16 *)data;
	स्थिर u16 len = data_length + माप(u16); /* 16-bit address + data */

	अगर (data_length != OV2722_8BIT && data_length != OV2722_16BIT) अणु
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* high byte goes out first */
	*wreg = cpu_to_be16(reg);

	अगर (data_length == OV2722_8BIT) अणु
		data[2] = (u8)(val);
	पूर्ण अन्यथा अणु
		/* OV2722_16BIT */
		__be16 *wdata = (__be16 *)&data[2];

		*wdata = cpu_to_be16(val);
	पूर्ण

	ret = ov2722_i2c_ग_लिखो(client, len, data);
	अगर (ret)
		dev_err(&client->dev,
			"write error: wrote 0x%x to offset 0x%x error %d",
			val, reg, ret);

	वापस ret;
पूर्ण

/*
 * ov2722_ग_लिखो_reg_array - Initializes a list of OV2722 रेजिस्टरs
 * @client: i2c driver client काष्ठाure
 * @reglist: list of रेजिस्टरs to be written
 *
 * This function initializes a list of रेजिस्टरs. When consecutive addresses
 * are found in a row on the list, this function creates a buffer and sends
 * consecutive data in a single i2c_transfer().
 *
 * __ov2722_flush_reg_array, __ov2722_buf_reg_array() and
 * __ov2722_ग_लिखो_reg_is_consecutive() are पूर्णांकernal functions to
 * ov2722_ग_लिखो_reg_array_fast() and should be not used anywhere अन्यथा.
 *
 */

अटल पूर्णांक __ov2722_flush_reg_array(काष्ठा i2c_client *client,
				    काष्ठा ov2722_ग_लिखो_ctrl *ctrl)
अणु
	u16 size;
	__be16 *data16 = (व्योम *)&ctrl->buffer.addr;

	अगर (ctrl->index == 0)
		वापस 0;

	size = माप(u16) + ctrl->index; /* 16-bit address + data */
	*data16 = cpu_to_be16(ctrl->buffer.addr);
	ctrl->index = 0;

	वापस ov2722_i2c_ग_लिखो(client, size, (u8 *)&ctrl->buffer);
पूर्ण

अटल पूर्णांक __ov2722_buf_reg_array(काष्ठा i2c_client *client,
				  काष्ठा ov2722_ग_लिखो_ctrl *ctrl,
				  स्थिर काष्ठा ov2722_reg *next)
अणु
	पूर्णांक size;
	__be16 *data16;

	चयन (next->type) अणु
	हाल OV2722_8BIT:
		size = 1;
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		अवरोध;
	हाल OV2722_16BIT:
		size = 2;
		data16 = (व्योम *)&ctrl->buffer.data[ctrl->index];
		*data16 = cpu_to_be16((u16)next->val);
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
	अगर (ctrl->index + माप(u16) >= OV2722_MAX_WRITE_BUF_SIZE)
		वापस __ov2722_flush_reg_array(client, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक __ov2722_ग_लिखो_reg_is_consecutive(काष्ठा i2c_client *client,
	काष्ठा ov2722_ग_लिखो_ctrl *ctrl,
	स्थिर काष्ठा ov2722_reg *next)
अणु
	अगर (ctrl->index == 0)
		वापस 1;

	वापस ctrl->buffer.addr + ctrl->index == next->reg;
पूर्ण

अटल पूर्णांक ov2722_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				  स्थिर काष्ठा ov2722_reg *reglist)
अणु
	स्थिर काष्ठा ov2722_reg *next = reglist;
	काष्ठा ov2722_ग_लिखो_ctrl ctrl;
	पूर्णांक err;

	ctrl.index = 0;
	क्रम (; next->type != OV2722_TOK_TERM; next++) अणु
		चयन (next->type & OV2722_TOK_MASK) अणु
		हाल OV2722_TOK_DELAY:
			err = __ov2722_flush_reg_array(client, &ctrl);
			अगर (err)
				वापस err;
			msleep(next->val);
			अवरोध;
		शेष:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed beक्रमe proceed.
			 */
			अगर (!__ov2722_ग_लिखो_reg_is_consecutive(client, &ctrl,
							       next)) अणु
				err = __ov2722_flush_reg_array(client, &ctrl);
				अगर (err)
					वापस err;
			पूर्ण
			err = __ov2722_buf_reg_array(client, &ctrl, next);
			अगर (err) अणु
				dev_err(&client->dev, "%s: write error, aborted\n",
					__func__);
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस __ov2722_flush_reg_array(client, &ctrl);
पूर्ण

अटल पूर्णांक ov2722_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV2722_FOCAL_LENGTH_NUM << 16) | OV2722_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम imx*/
	*val = (OV2722_F_NUMBER_DEFAULT_NUM << 16) | OV2722_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV2722_F_NUMBER_DEFAULT_NUM << 24) |
	       (OV2722_F_NUMBER_DEM << 16) |
	       (OV2722_F_NUMBER_DEFAULT_NUM << 8) | OV2722_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				  काष्ठा camera_mipi_info *info,
				  स्थिर काष्ठा ov2722_resolution *res)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2722_device *dev = शून्य;
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	स्थिर अचिन्हित पूर्णांक ext_clk_freq_hz = 19200000;
	स्थिर अचिन्हित पूर्णांक pll_invariant_भाग = 10;
	अचिन्हित पूर्णांक pix_clk_freq_hz;
	u16 pre_pll_clk_भाग;
	u16 pll_multiplier;
	u16 op_pix_clk_भाग;
	u16 reg_val;
	पूर्णांक ret;

	अगर (!info)
		वापस -EINVAL;

	dev = to_ov2722_sensor(sd);

	/* pixel घड़ी calculattion */
	ret =  ov2722_पढ़ो_reg(client, OV2722_8BIT,
			       OV2722_SC_CMMN_PLL_CTRL3, &pre_pll_clk_भाग);
	अगर (ret)
		वापस ret;

	ret =  ov2722_पढ़ो_reg(client, OV2722_8BIT,
			       OV2722_SC_CMMN_PLL_MULTIPLIER, &pll_multiplier);
	अगर (ret)
		वापस ret;

	ret =  ov2722_पढ़ो_reg(client, OV2722_8BIT,
			       OV2722_SC_CMMN_PLL_DEBUG_OPT, &op_pix_clk_भाग);
	अगर (ret)
		वापस ret;

	pre_pll_clk_भाग = (pre_pll_clk_भाग & 0x70) >> 4;
	अगर (!pre_pll_clk_भाग)
		वापस -EINVAL;

	pll_multiplier = pll_multiplier & 0x7f;
	op_pix_clk_भाग = op_pix_clk_भाग & 0x03;
	pix_clk_freq_hz = ext_clk_freq_hz / pre_pll_clk_भाग * pll_multiplier
			  * op_pix_clk_भाग / pll_invariant_भाग;

	dev->vt_pix_clk_freq_mhz = pix_clk_freq_hz;
	buf->vt_pix_clk_freq_mhz = pix_clk_freq_hz;

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = OV2722_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    OV2722_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = OV2722_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    OV2722_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = OV2722_FINE_INTG_TIME_MIN;
	buf->frame_length_lines = res->lines_per_frame;
	buf->line_length_pck = res->pixels_per_line;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	ret =  ov2722_पढ़ो_reg(client, OV2722_16BIT,
			       OV2722_H_CROP_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_start = reg_val;

	ret =  ov2722_पढ़ो_reg(client, OV2722_16BIT,
			       OV2722_V_CROP_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_start = reg_val;

	ret = ov2722_पढ़ो_reg(client, OV2722_16BIT,
			      OV2722_H_CROP_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_end = reg_val;

	ret = ov2722_पढ़ो_reg(client, OV2722_16BIT,
			      OV2722_V_CROP_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_end = reg_val;

	ret = ov2722_पढ़ो_reg(client, OV2722_16BIT,
			      OV2722_H_OUTSIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = reg_val;

	ret = ov2722_पढ़ो_reg(client, OV2722_16BIT,
			      OV2722_V_OUTSIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = reg_val;

	buf->binning_factor_x = res->bin_factor_x ?
				res->bin_factor_x : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				res->bin_factor_y : 1;
	वापस 0;
पूर्ण

अटल दीर्घ __ov2722_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक coarse_itg,
				  पूर्णांक gain, पूर्णांक digitgain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	u16 hts, vts;
	पूर्णांक ret;

	dev_dbg(&client->dev, "set_exposure without group hold\n");

	/* clear VTS_DIFF on manual mode */
	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT, OV2722_VTS_DIFF_H, 0);
	अगर (ret)
		वापस ret;

	hts = dev->pixels_per_line;
	vts = dev->lines_per_frame;

	अगर ((coarse_itg + OV2722_COARSE_INTG_TIME_MAX_MARGIN) > vts)
		vts = coarse_itg + OV2722_COARSE_INTG_TIME_MAX_MARGIN;

	coarse_itg <<= 4;
	digitgain <<= 2;

	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_VTS_H, vts);
	अगर (ret)
		वापस ret;

	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_HTS_H, hts);
	अगर (ret)
		वापस ret;

	/* set exposure */
	ret = ov2722_ग_लिखो_reg(client, OV2722_8BIT,
			       OV2722_AEC_PK_EXPO_L,
			       coarse_itg & 0xff);
	अगर (ret)
		वापस ret;

	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_AEC_PK_EXPO_H,
			       (coarse_itg >> 8) & 0xfff);
	अगर (ret)
		वापस ret;

	/* set analog gain */
	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_AGC_ADJ_H, gain);
	अगर (ret)
		वापस ret;

	/* set digital gain */
	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_MWB_GAIN_R_H, digitgain);
	अगर (ret)
		वापस ret;

	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_MWB_GAIN_G_H, digitgain);
	अगर (ret)
		वापस ret;

	ret = ov2722_ग_लिखो_reg(client, OV2722_16BIT,
			       OV2722_MWB_GAIN_B_H, digitgain);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक exposure,
			       पूर्णांक gain, पूर्णांक digitgain)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	ret = __ov2722_set_exposure(sd, exposure, gain, digitgain);
	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल दीर्घ ov2722_s_exposure(काष्ठा v4l2_subdev *sd,
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

	वापस ov2722_set_exposure(sd, exp, gain, digitgain);
पूर्ण

अटल दीर्घ ov2722_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस ov2722_s_exposure(sd, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* This वापसs the exposure समय being used. This should only be used
 * क्रम filling in EXIF data, not क्रम actual image processing.
 */
अटल पूर्णांक ov2722_q_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 reg_v, reg_v2;
	पूर्णांक ret;

	/* get exposure */
	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_AEC_PK_EXPO_L,
			      &reg_v);
	अगर (ret)
		जाओ err;

	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_AEC_PK_EXPO_M,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	reg_v += reg_v2 << 8;
	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_AEC_PK_EXPO_H,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	*value = reg_v + (((u32)reg_v2 << 16));
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2722_device *dev =
	    container_of(ctrl->handler, काष्ठा ov2722_device, ctrl_handler);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = ov2722_q_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = ov2722_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = ov2722_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = ov2722_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_LINK_FREQ:
		val = ov2722_res[dev->fmt_idx].mipi_freq;
		अगर (val == 0)
			वापस -EINVAL;

		ctrl->val = val * 1000;	/* To Hz */
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov2722_g_अस्थिर_ctrl
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ov2722_controls[] = अणु
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
		.min = OV2722_FOCAL_LENGTH_DEFAULT,
		.max = OV2722_FOCAL_LENGTH_DEFAULT,
		.step = 0x01,
		.def = OV2722_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number",
		.min = OV2722_F_NUMBER_DEFAULT,
		.max = OV2722_F_NUMBER_DEFAULT,
		.step = 0x01,
		.def = OV2722_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number range",
		.min = OV2722_F_NUMBER_RANGE,
		.max = OV2722_F_NUMBER_RANGE,
		.step = 0x01,
		.def = OV2722_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_LINK_FREQ,
		.name = "Link Frequency",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 1,
		.max = 1500000 * 1000,
		.step = 1,
		.def = 1,
		.flags = V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_READ_ONLY,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov2722_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	mutex_lock(&dev->input_lock);

	/* restore settings */
	ov2722_res = ov2722_res_preview;
	N_RES = N_RES_PREVIEW;

	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret = -1;
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	अगर (flag) अणु
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 1);
		अगर (ret == 0) अणु
			ret = dev->platक्रमm_data->v2p8_ctrl(sd, 1);
			अगर (ret)
				dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	पूर्णांक ret = -1;

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	/* Note: the GPIO order is asymmetric: always RESET#
	 * beक्रमe PWDN# when turning it on or off.
	 */
	ret = dev->platक्रमm_data->gpio0_ctrl(sd, flag);
	/*
	 *ov2722 PWDN# active high when pull करोwn,opposite to the convention
	 */
	ret |= dev->platक्रमm_data->gpio1_ctrl(sd, !flag);
	वापस ret;
पूर्ण

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
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

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 1);
	अगर (ret) अणु
		ret = gpio_ctrl(sd, 0);
		अगर (ret)
			जाओ fail_घातer;
	पूर्ण

	/* flis घड़ी control */
	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 1);
	अगर (ret)
		जाओ fail_clk;

	/* according to DS, 20ms is needed between PWDN and i2c access */
	msleep(20);

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
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		वापस -ENODEV;
	पूर्ण

	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "flisclk failed\n");

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 0);
	अगर (ret) अणु
		ret = gpio_ctrl(sd, 0);
		अगर (ret)
			dev_err(&client->dev, "gpio failed 2\n");
	पूर्ण

	/* घातer control */
	ret = घातer_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "vprog failed.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on == 0)
		वापस घातer_करोwn(sd);
	अन्यथा अणु
		ret = घातer_up(sd);
		अगर (!ret)
			वापस ov2722_init(sd);
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
अटल पूर्णांक distance(काष्ठा ov2722_resolution *res, u32 w, u32 h)
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
	काष्ठा ov2722_resolution *पंचांगp_res = शून्य;

	क्रम (i = 0; i < N_RES; i++) अणु
		पंचांगp_res = &ov2722_res[i];
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
		अगर (w != ov2722_res[i].width)
			जारी;
		अगर (h != ov2722_res[i].height)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* TODO: हटाओ it. */
अटल पूर्णांक startup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	ret = ov2722_ग_लिखो_reg(client, OV2722_8BIT,
			       OV2722_SW_RESET, 0x01);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2722 reset err.\n");
		वापस ret;
	पूर्ण

	ret = ov2722_ग_लिखो_reg_array(client, ov2722_res[dev->fmt_idx].regs);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2722 write register err.\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *ov2722_info = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक idx;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	अगर (!fmt)
		वापस -EINVAL;
	ov2722_info = v4l2_get_subdev_hostdata(sd);
	अगर (!ov2722_info)
		वापस -EINVAL;

	mutex_lock(&dev->input_lock);
	idx = nearest_resolution_index(fmt->width, fmt->height);
	अगर (idx == -1) अणु
		/* वापस the largest resolution */
		fmt->width = ov2722_res[N_RES - 1].width;
		fmt->height = ov2722_res[N_RES - 1].height;
	पूर्ण अन्यथा अणु
		fmt->width = ov2722_res[idx].width;
		fmt->height = ov2722_res[idx].height;
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

	dev->pixels_per_line = ov2722_res[dev->fmt_idx].pixels_per_line;
	dev->lines_per_frame = ov2722_res[dev->fmt_idx].lines_per_frame;

	ret = startup(sd);
	अगर (ret) अणु
		पूर्णांक i = 0;

		dev_err(&client->dev, "ov2722 startup err, retry to power up\n");
		क्रम (i = 0; i < OV2722_POWER_UP_RETRY_NUM; i++) अणु
			dev_err(&client->dev,
				"ov2722 retry to power up %d/%d times, result: ",
				i + 1, OV2722_POWER_UP_RETRY_NUM);
			घातer_करोwn(sd);
			ret = घातer_up(sd);
			अगर (ret) अणु
				dev_err(&client->dev, "power up failed, continue\n");
				जारी;
			पूर्ण
			ret = startup(sd);
			अगर (ret) अणु
				dev_err(&client->dev, " startup FAILED!\n");
			पूर्ण अन्यथा अणु
				dev_err(&client->dev, " startup SUCCESS!\n");
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret) अणु
			dev_err(&client->dev, "ov2722 startup err\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = ov2722_get_पूर्णांकg_factor(client, ov2722_info,
				     &ov2722_res[dev->fmt_idx]);
	अगर (ret)
		dev_err(&client->dev, "failed to get integration_factor\n");

err:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	अगर (!fmt)
		वापस -EINVAL;

	fmt->width = ov2722_res[dev->fmt_idx].width;
	fmt->height = ov2722_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_detect(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 high, low;
	पूर्णांक ret;
	u16 id;
	u8 revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_SC_CMMN_CHIP_ID_H, &high);
	अगर (ret) अणु
		dev_err(&client->dev, "sensor_id_high = 0x%x\n", high);
		वापस -ENODEV;
	पूर्ण
	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_SC_CMMN_CHIP_ID_L, &low);
	id = (high << 8) | low;

	अगर ((id != OV2722_ID) && (id != OV2720_ID)) अणु
		dev_err(&client->dev, "sensor ID error\n");
		वापस -ENODEV;
	पूर्ण

	ret = ov2722_पढ़ो_reg(client, OV2722_8BIT,
			      OV2722_SC_CMMN_SUB_ID, &high);
	revision = (u8)high & 0x0f;

	dev_dbg(&client->dev, "sensor_revision = 0x%x\n", revision);
	dev_dbg(&client->dev, "detect ov2722 success\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);

	ret = ov2722_ग_लिखो_reg(client, OV2722_8BIT, OV2722_SW_STREAM,
			       enable ? OV2722_START_STREAMING :
			       OV2722_STOP_STREAMING);

	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2722_s_config(काष्ठा v4l2_subdev *sd,
			   पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);
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
		dev_err(&client->dev, "ov2722 power-off err.\n");
		जाओ fail_घातer_off;
	पूर्ण

	ret = घातer_up(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2722 power-up err.\n");
		जाओ fail_घातer_on;
	पूर्ण

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	/* config & detect sensor */
	ret = ov2722_detect(client);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2722_detect err s_config.\n");
		जाओ fail_csi_cfg;
	पूर्ण

	/* turn off sensor, after probed */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2722 power-off err.\n");
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

अटल पूर्णांक ov2722_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = ov2722_res[dev->fmt_idx].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = ov2722_res[index].width;
	fse->min_height = ov2722_res[index].height;
	fse->max_width = ov2722_res[index].width;
	fse->max_height = ov2722_res[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_g_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	mutex_lock(&dev->input_lock);
	*frames = ov2722_res[dev->fmt_idx].skip_frames;
	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops ov2722_sensor_ops = अणु
	.g_skip_frames	= ov2722_g_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2722_video_ops = अणु
	.s_stream = ov2722_s_stream,
	.g_frame_पूर्णांकerval = ov2722_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov2722_core_ops = अणु
	.s_घातer = ov2722_s_घातer,
	.ioctl = ov2722_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2722_pad_ops = अणु
	.क्रमागत_mbus_code = ov2722_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov2722_क्रमागत_frame_size,
	.get_fmt = ov2722_get_fmt,
	.set_fmt = ov2722_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2722_ops = अणु
	.core = &ov2722_core_ops,
	.video = &ov2722_video_ops,
	.pad = &ov2722_pad_ops,
	.sensor = &ov2722_sensor_ops,
पूर्ण;

अटल पूर्णांक ov2722_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2722_device *dev = to_ov2722_sensor(sd);

	dev->platक्रमm_data->csi_cfg(sd, 0);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर_subdev(sd);

	atomisp_gmin_हटाओ_subdev(sd);

	media_entity_cleanup(&dev->sd.entity);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __ov2722_init_ctrl_handler(काष्ठा ov2722_device *dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl;
	अचिन्हित पूर्णांक i;

	hdl = &dev->ctrl_handler;
	v4l2_ctrl_handler_init(&dev->ctrl_handler, ARRAY_SIZE(ov2722_controls));
	क्रम (i = 0; i < ARRAY_SIZE(ov2722_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &ov2722_controls[i],
				     शून्य);

	dev->link_freq = v4l2_ctrl_find(&dev->ctrl_handler, V4L2_CID_LINK_FREQ);

	अगर (dev->ctrl_handler.error || !dev->link_freq)
		वापस dev->ctrl_handler.error;

	dev->sd.ctrl_handler = hdl;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2722_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2722_device *dev;
	व्योम *ovpdev;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&dev->sd, client, &ov2722_ops);

	ovpdev = gmin_camera_platक्रमm_data(&dev->sd,
					   ATOMISP_INPUT_FORMAT_RAW_10,
					   atomisp_bayer_order_grbg);

	ret = ov2722_s_config(&dev->sd, client->irq, ovpdev);
	अगर (ret)
		जाओ out_मुक्त;

	ret = __ov2722_init_ctrl_handler(dev);
	अगर (ret)
		जाओ out_ctrl_handler_मुक्त;

	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->क्रमmat.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret)
		ov2722_हटाओ(client);

	वापस atomisp_रेजिस्टर_i2c_module(&dev->sd, ovpdev, RAW_CAMERA);

out_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);

out_मुक्त:
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ov2722_acpi_match[] = अणु
	अणु "INT33FB" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ov2722_acpi_match);

अटल काष्ठा i2c_driver ov2722_driver = अणु
	.driver = अणु
		.name = "ov2722",
		.acpi_match_table = ov2722_acpi_match,
	पूर्ण,
	.probe_new = ov2722_probe,
	.हटाओ = ov2722_हटाओ,
पूर्ण;
module_i2c_driver(ov2722_driver);

MODULE_AUTHOR("Wei Liu <wei.liu@intel.com>");
MODULE_DESCRIPTION("A low-level driver for OmniVision 2722 sensors");
MODULE_LICENSE("GPL");
