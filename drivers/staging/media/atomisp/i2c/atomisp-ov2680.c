<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम OmniVision OV2680 1080p HD camera sensor.
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

#समावेश <यंत्र/unaligned.h>

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
#समावेश <linux/acpi.h>
#समावेश "../include/linux/atomisp_gmin_platform.h"

#समावेश "ov2680.h"

अटल पूर्णांक h_flag;
अटल पूर्णांक v_flag;
अटल क्रमागत atomisp_bayer_order ov2680_bayer_order_mapping[] = अणु
	atomisp_bayer_order_bggr,
	atomisp_bayer_order_grbg,
	atomisp_bayer_order_gbrg,
	atomisp_bayer_order_rggb,
पूर्ण;

/* i2c पढ़ो/ग_लिखो stuff */
अटल पूर्णांक ov2680_पढ़ो_reg(काष्ठा i2c_client *client,
			   पूर्णांक len, u16 reg, u16 *val)
अणु
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 data_buf[4] = अणु 0, पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_buf[4 - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "read error: reg=0x%4x: %d\n", reg, ret);
		वापस -EIO;
	पूर्ण

	*val = get_unaligned_be32(data_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_ग_लिखो_reg(काष्ठा i2c_client *client, अचिन्हित पूर्णांक len,
			    u16 reg, u16 val)
अणु
	u8 buf[6];
	पूर्णांक ret;

	अगर (len == 2)
		put_unaligned_be16(val << (8 * (4 - len)), buf + 2);
	अन्यथा अगर (len == 1)
		buf[2] = val;
	अन्यथा
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);

	ret = i2c_master_send(client, buf, len + 2);
	अगर (ret != len + 2) अणु
		dev_err(&client->dev, "write error %d reg 0x%04x, val 0x%02x: buf sent: %*ph\n",
			ret, reg, val, len + 2, &buf);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				  स्थिर काष्ठा ov2680_reg *reglist)
अणु
	स्थिर काष्ठा ov2680_reg *next = reglist;
	पूर्णांक ret;

	क्रम (; next->reg != 0; next++) अणु
		ret = ov2680_ग_लिखो_reg(client, 1, next->reg, next->val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV2680_FOCAL_LENGTH_NUM << 16) | OV2680_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम ov2680*/

	*val = (OV2680_F_NUMBER_DEFAULT_NUM << 16) | OV2680_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV2680_F_NUMBER_DEFAULT_NUM << 24) |
	       (OV2680_F_NUMBER_DEM << 16) |
	       (OV2680_F_NUMBER_DEFAULT_NUM << 8) | OV2680_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_bin_factor_x(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev,  "++++ov2680_g_bin_factor_x\n");
	*val = ov2680_res[dev->fmt_idx].bin_factor_x;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_bin_factor_y(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	*val = ov2680_res[dev->fmt_idx].bin_factor_y;
	dev_dbg(&client->dev,  "++++ov2680_g_bin_factor_y\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				  काष्ठा camera_mipi_info *info,
				  स्थिर काष्ठा ov2680_resolution *res)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	अचिन्हित पूर्णांक pix_clk_freq_hz;
	u16 reg_val;
	पूर्णांक ret;

	dev_dbg(&client->dev,  "++++ov2680_get_intg_factor\n");
	अगर (!info)
		वापस -EINVAL;

	/* pixel घड़ी */
	pix_clk_freq_hz = res->pix_clk_freq * 1000000;

	dev->vt_pix_clk_freq_mhz = pix_clk_freq_hz;
	buf->vt_pix_clk_freq_mhz = pix_clk_freq_hz;

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = OV2680_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    OV2680_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = OV2680_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    OV2680_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = OV2680_FINE_INTG_TIME_MIN;
	buf->frame_length_lines = res->lines_per_frame;
	buf->line_length_pck = res->pixels_per_line;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	ret =  ov2680_पढ़ो_reg(client, 2,
			       OV2680_HORIZONTAL_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_start = reg_val;

	ret =  ov2680_पढ़ो_reg(client, 2,
			       OV2680_VERTICAL_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_start = reg_val;

	ret = ov2680_पढ़ो_reg(client, 2,
			      OV2680_HORIZONTAL_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_end = reg_val;

	ret = ov2680_पढ़ो_reg(client, 2,
			      OV2680_VERTICAL_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_end = reg_val;

	ret = ov2680_पढ़ो_reg(client, 2,
			      OV2680_HORIZONTAL_OUTPUT_SIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = reg_val;

	ret = ov2680_पढ़ो_reg(client, 2,
			      OV2680_VERTICAL_OUTPUT_SIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = reg_val;

	buf->binning_factor_x = res->bin_factor_x ?
				(res->bin_factor_x * 2) : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				(res->bin_factor_y * 2) : 1;
	वापस 0;
पूर्ण

अटल दीर्घ __ov2680_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक coarse_itg,
				  पूर्णांक gain, पूर्णांक digitgain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	u16 vts;
	पूर्णांक ret, exp_val;

	dev_dbg(&client->dev,
		"+++++++__ov2680_set_exposure coarse_itg %d, gain %d, digitgain %d++\n",
		coarse_itg, gain, digitgain);

	vts = ov2680_res[dev->fmt_idx].lines_per_frame;

	/* group hold */
	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_GROUP_ACCESS, 0x00);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_GROUP_ACCESS);
		वापस ret;
	पूर्ण

	/* Increase the VTS to match exposure + MARGIN */
	अगर (coarse_itg > vts - OV2680_INTEGRATION_TIME_MARGIN)
		vts = (u16)coarse_itg + OV2680_INTEGRATION_TIME_MARGIN;

	ret = ov2680_ग_लिखो_reg(client, 2, OV2680_TIMING_VTS_H, vts);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_TIMING_VTS_H);
		वापस ret;
	पूर्ण

	/* set exposure */

	/* Lower four bit should be 0*/
	exp_val = coarse_itg << 4;
	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_EXPOSURE_L, exp_val & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_EXPOSURE_L);
		वापस ret;
	पूर्ण

	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_EXPOSURE_M, (exp_val >> 8) & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_EXPOSURE_M);
		वापस ret;
	पूर्ण

	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_EXPOSURE_H, (exp_val >> 16) & 0x0F);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_EXPOSURE_H);
		वापस ret;
	पूर्ण

	/* Analog gain */
	ret = ov2680_ग_लिखो_reg(client, 2, OV2680_AGC_H, gain);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write 0x%02x: error, aborted\n",
			__func__, OV2680_AGC_H);
		वापस ret;
	पूर्ण
	/* Digital gain */
	अगर (digitgain) अणु
		ret = ov2680_ग_लिखो_reg(client, 2,
				       OV2680_MWB_RED_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev,
				"%s: write 0x%02x: error, aborted\n",
				__func__, OV2680_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण

		ret = ov2680_ग_लिखो_reg(client, 2,
				       OV2680_MWB_GREEN_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev,
				"%s: write 0x%02x: error, aborted\n",
				__func__, OV2680_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण

		ret = ov2680_ग_लिखो_reg(client, 2,
				       OV2680_MWB_BLUE_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev,
				"%s: write 0x%02x: error, aborted\n",
				__func__, OV2680_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण
	पूर्ण

	/* End group */
	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_GROUP_ACCESS, 0x10);
	अगर (ret)
		वापस ret;

	/* Delay launch group */
	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_GROUP_ACCESS, 0xa0);
	अगर (ret)
		वापस ret;
	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक exposure,
			       पूर्णांक gain, पूर्णांक digitgain)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	ret = __ov2680_set_exposure(sd, exposure, gain, digitgain);
	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल दीर्घ ov2680_s_exposure(काष्ठा v4l2_subdev *sd,
			      काष्ठा atomisp_exposure *exposure)
अणु
	u16 coarse_itg = exposure->पूर्णांकegration_समय[0];
	u16 analog_gain = exposure->gain[0];
	u16 digital_gain = exposure->gain[1];

	/* we should not accept the invalid value below */
	अगर (analog_gain == 0) अणु
		काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

		v4l2_err(client, "%s: invalid value\n", __func__);
		वापस -EINVAL;
	पूर्ण

	// EXPOSURE CONTROL DISABLED FOR INITIAL CHECKIN, TUNING DOESN'T WORK
	वापस ov2680_set_exposure(sd, coarse_itg, analog_gain, digital_gain);
पूर्ण

अटल दीर्घ ov2680_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस ov2680_s_exposure(sd, arg);

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* This वापसs the exposure समय being used. This should only be used
 * क्रम filling in EXIF data, not क्रम actual image processing.
 */
अटल पूर्णांक ov2680_q_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 reg_v, reg_v2;
	पूर्णांक ret;

	/* get exposure */
	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_EXPOSURE_L,
			      &reg_v);
	अगर (ret)
		जाओ err;

	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_EXPOSURE_M,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	reg_v += reg_v2 << 8;
	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_EXPOSURE_H,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	*value = reg_v + (((u32)reg_v2 << 16));
err:
	वापस ret;
पूर्ण

अटल u32 ov2680_translate_bayer_order(क्रमागत atomisp_bayer_order code)
अणु
	चयन (code) अणु
	हाल atomisp_bayer_order_rggb:
		वापस MEDIA_BUS_FMT_SRGGB10_1X10;
	हाल atomisp_bayer_order_grbg:
		वापस MEDIA_BUS_FMT_SGRBG10_1X10;
	हाल atomisp_bayer_order_bggr:
		वापस MEDIA_BUS_FMT_SBGGR10_1X10;
	हाल atomisp_bayer_order_gbrg:
		वापस MEDIA_BUS_FMT_SGBRG10_1X10;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_v_flip(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा camera_mipi_info *ov2680_info = शून्य;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u16 val;
	u8 index;

	dev_dbg(&client->dev, "@%s: value:%d\n", __func__, value);
	ret = ov2680_पढ़ो_reg(client, 1, OV2680_FLIP_REG, &val);
	अगर (ret)
		वापस ret;
	अगर (value) अणु
		val |= OV2680_FLIP_MIRROR_BIT_ENABLE;
	पूर्ण अन्यथा अणु
		val &= ~OV2680_FLIP_MIRROR_BIT_ENABLE;
	पूर्ण
	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_FLIP_REG, val);
	अगर (ret)
		वापस ret;
	index = (v_flag > 0 ? OV2680_FLIP_BIT : 0) | (h_flag > 0 ? OV2680_MIRROR_BIT :
		0);
	ov2680_info = v4l2_get_subdev_hostdata(sd);
	अगर (ov2680_info) अणु
		ov2680_info->raw_bayer_order = ov2680_bayer_order_mapping[index];
		dev->क्रमmat.code = ov2680_translate_bayer_order(
				       ov2680_info->raw_bayer_order);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_h_flip(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा camera_mipi_info *ov2680_info = शून्य;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u16 val;
	u8 index;

	dev_dbg(&client->dev, "@%s: value:%d\n", __func__, value);

	ret = ov2680_पढ़ो_reg(client, 1, OV2680_MIRROR_REG, &val);
	अगर (ret)
		वापस ret;
	अगर (value)
		val |= OV2680_FLIP_MIRROR_BIT_ENABLE;
	अन्यथा
		val &= ~OV2680_FLIP_MIRROR_BIT_ENABLE;

	ret = ov2680_ग_लिखो_reg(client, 1,
			       OV2680_MIRROR_REG, val);
	अगर (ret)
		वापस ret;
	index = (v_flag > 0 ? OV2680_FLIP_BIT : 0) | (h_flag > 0 ? OV2680_MIRROR_BIT :
		0);
	ov2680_info = v4l2_get_subdev_hostdata(sd);
	अगर (ov2680_info) अणु
		ov2680_info->raw_bayer_order = ov2680_bayer_order_mapping[index];
		dev->क्रमmat.code = ov2680_translate_bayer_order(
				       ov2680_info->raw_bayer_order);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2680_device *dev =
	    container_of(ctrl->handler, काष्ठा ov2680_device, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		dev_dbg(&client->dev, "%s: CID_VFLIP:%d.\n",
			__func__, ctrl->val);
		ret = ov2680_v_flip(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		dev_dbg(&client->dev, "%s: CID_HFLIP:%d.\n",
			__func__, ctrl->val);
		ret = ov2680_h_flip(&dev->sd, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2680_device *dev =
	    container_of(ctrl->handler, काष्ठा ov2680_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = ov2680_q_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = ov2680_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = ov2680_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = ov2680_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_HORZ:
		ret = ov2680_g_bin_factor_x(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_VERT:
		ret = ov2680_g_bin_factor_y(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = ov2680_s_ctrl,
	.g_अस्थिर_ctrl = ov2680_g_अस्थिर_ctrl
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ov2680_controls[] = अणु
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
		.min = OV2680_FOCAL_LENGTH_DEFAULT,
		.max = OV2680_FOCAL_LENGTH_DEFAULT,
		.step = 0x01,
		.def = OV2680_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number",
		.min = OV2680_F_NUMBER_DEFAULT,
		.max = OV2680_F_NUMBER_DEFAULT,
		.step = 0x01,
		.def = OV2680_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number range",
		.min = OV2680_F_NUMBER_RANGE,
		.max = OV2680_F_NUMBER_RANGE,
		.step = 0x01,
		.def = OV2680_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_HORZ,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "horizontal binning factor",
		.min = 0,
		.max = OV2680_BIN_FACTOR_MAX,
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
		.max = OV2680_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
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
पूर्ण;

अटल पूर्णांक ov2680_init_रेजिस्टरs(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = ov2680_ग_लिखो_reg(client, 1, OV2680_SW_RESET, 0x01);
	ret |= ov2680_ग_लिखो_reg_array(client, ov2680_global_setting);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	पूर्णांक ret;

	mutex_lock(&dev->input_lock);

	/* restore settings */
	ov2680_res = ov2680_res_preview;
	N_RES = N_RES_PREVIEW;

	ret = ov2680_init_रेजिस्टरs(sd);

	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret = 0;
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	dev_dbg(&client->dev, "%s: %s", __func__, flag ? "on" : "off");

	अगर (flag) अणु
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
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	/* The OV2680 करोcuments only one GPIO input (#XSHUTDN), but
	 * existing पूर्णांकegrations often wire two (reset/घातer_करोwn)
	 * because that is the way other sensors work.  There is no
	 * way to tell how it is wired पूर्णांकernally, so existing
	 * firmwares expose both and we drive them symmetrically. */
	अगर (flag) अणु
		ret = dev->platक्रमm_data->gpio0_ctrl(sd, 1);
		usleep_range(10000, 15000);
		/* Ignore वापस from second gpio, it may not be there */
		dev->platक्रमm_data->gpio1_ctrl(sd, 1);
		usleep_range(10000, 15000);
	पूर्ण अन्यथा अणु
		dev->platक्रमm_data->gpio1_ctrl(sd, 0);
		ret = dev->platक्रमm_data->gpio0_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
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
		ret = gpio_ctrl(sd, 1);
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
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	h_flag = 0;
	v_flag = 0;
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

अटल पूर्णांक ov2680_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on == 0) अणु
		ret = घातer_करोwn(sd);
	पूर्ण अन्यथा अणु
		ret = घातer_up(sd);
		अगर (!ret)
			वापस ov2680_init(sd);
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
#घोषणा LARGEST_ALLOWED_RATIO_MISMATCH 600
अटल पूर्णांक distance(काष्ठा ov2680_resolution *res, u32 w, u32 h)
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
	काष्ठा ov2680_resolution *पंचांगp_res = शून्य;

	क्रम (i = 0; i < N_RES; i++) अणु
		पंचांगp_res = &ov2680_res[i];
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
		अगर (w != ov2680_res[i].width)
			जारी;
		अगर (h != ov2680_res[i].height)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक ov2680_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *ov2680_info = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक idx = 0;

	dev_dbg(&client->dev, "%s: %s: pad: %d, fmt: %p\n",
		__func__,
		(क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) ? "try" : "set",
		क्रमmat->pad, fmt);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	ov2680_info = v4l2_get_subdev_hostdata(sd);
	अगर (!ov2680_info)
		वापस -EINVAL;

	mutex_lock(&dev->input_lock);
	idx = nearest_resolution_index(fmt->width, fmt->height);
	अगर (idx == -1) अणु
		/* वापस the largest resolution */
		fmt->width = ov2680_res[N_RES - 1].width;
		fmt->height = ov2680_res[N_RES - 1].height;
	पूर्ण अन्यथा अणु
		fmt->width = ov2680_res[idx].width;
		fmt->height = ov2680_res[idx].height;
	पूर्ण
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *fmt;
		mutex_unlock(&dev->input_lock);
		वापस 0;
	पूर्ण
	dev->fmt_idx = get_resolution_index(fmt->width, fmt->height);
	dev_dbg(&client->dev, "%s: Resolution index: %d\n",
		__func__, dev->fmt_idx);
	अगर (dev->fmt_idx == -1) अणु
		dev_err(&client->dev, "get resolution fail\n");
		mutex_unlock(&dev->input_lock);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&client->dev, "%s: i=%d, w=%d, h=%d\n",
		__func__, dev->fmt_idx, fmt->width, fmt->height);

	// IS IT NEEDED?
	घातer_up(sd);
	ret = ov2680_ग_लिखो_reg_array(client, ov2680_res[dev->fmt_idx].regs);
	अगर (ret)
		dev_err(&client->dev,
			"ov2680 write resolution register err: %d\n", ret);

	ret = ov2680_get_पूर्णांकg_factor(client, ov2680_info,
				     &ov2680_res[dev->fmt_idx]);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to get integration factor\n");
		जाओ err;
	पूर्ण

	/*recall flip functions to aव्योम flip रेजिस्टरs
	 * were overridden by शेष setting
	 */
	अगर (h_flag)
		ov2680_h_flip(sd, h_flag);
	अगर (v_flag)
		ov2680_v_flip(sd, v_flag);

	v4l2_info(client, "\n%s idx %d\n", __func__, dev->fmt_idx);

	/*ret = startup(sd);
	 * अगर (ret)
	 * dev_err(&client->dev, "ov2680 startup err\n");
	 */
err:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	fmt->width = ov2680_res[dev->fmt_idx].width;
	fmt->height = ov2680_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_detect(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 high, low;
	पूर्णांक ret;
	u16 id;
	u8 revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_SC_CMMN_CHIP_ID_H, &high);
	अगर (ret) अणु
		dev_err(&client->dev, "sensor_id_high = 0x%x\n", high);
		वापस -ENODEV;
	पूर्ण
	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_SC_CMMN_CHIP_ID_L, &low);
	id = ((((u16)high) << 8) | (u16)low);

	अगर (id != OV2680_ID) अणु
		dev_err(&client->dev, "sensor ID error 0x%x\n", id);
		वापस -ENODEV;
	पूर्ण

	ret = ov2680_पढ़ो_reg(client, 1,
			      OV2680_SC_CMMN_SUB_ID, &high);
	revision = (u8)high & 0x0f;

	dev_info(&client->dev, "sensor_revision id = 0x%x, rev= %d\n",
		 id, revision);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	अगर (enable)
		dev_dbg(&client->dev, "ov2680_s_stream one\n");
	अन्यथा
		dev_dbg(&client->dev, "ov2680_s_stream off\n");

	ret = ov2680_ग_लिखो_reg(client, 1, OV2680_SW_STREAM,
			       enable ? OV2680_START_STREAMING :
			       OV2680_STOP_STREAMING);
#अगर 0
	/* restore settings */
	ov2680_res = ov2680_res_preview;
	N_RES = N_RES_PREVIEW;
#पूर्ण_अगर

	//otp valid at stream on state
	//अगर(!dev->otp_data)
	//	dev->otp_data = ov2680_otp_पढ़ो(sd);

	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_s_config(काष्ठा v4l2_subdev *sd,
			   पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);
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
		dev_err(&client->dev, "ov2680 power-off err.\n");
		जाओ fail_घातer_off;
	पूर्ण

	ret = घातer_up(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2680 power-up err.\n");
		जाओ fail_घातer_on;
	पूर्ण

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	/* config & detect sensor */
	ret = ov2680_detect(client);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2680_detect err s_config.\n");
		जाओ fail_csi_cfg;
	पूर्ण

	/* turn off sensor, after probed */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov2680 power-off err.\n");
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

अटल पूर्णांक ov2680_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = ov2680_res[dev->fmt_idx].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = ov2680_res[index].width;
	fse->min_height = ov2680_res[index].height;
	fse->max_width = ov2680_res[index].width;
	fse->max_height = ov2680_res[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	mutex_lock(&dev->input_lock);
	*frames = ov2680_res[dev->fmt_idx].skip_frames;
	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2680_video_ops = अणु
	.s_stream = ov2680_s_stream,
	.g_frame_पूर्णांकerval = ov2680_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops ov2680_sensor_ops = अणु
	.g_skip_frames	= ov2680_g_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov2680_core_ops = अणु
	.s_घातer = ov2680_s_घातer,
	.ioctl = ov2680_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2680_pad_ops = अणु
	.क्रमागत_mbus_code = ov2680_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov2680_क्रमागत_frame_size,
	.get_fmt = ov2680_get_fmt,
	.set_fmt = ov2680_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2680_ops = अणु
	.core = &ov2680_core_ops,
	.video = &ov2680_video_ops,
	.pad = &ov2680_pad_ops,
	.sensor = &ov2680_sensor_ops,
पूर्ण;

अटल पूर्णांक ov2680_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2680_device *dev = to_ov2680_sensor(sd);

	dev_dbg(&client->dev, "ov2680_remove...\n");

	dev->platक्रमm_data->csi_cfg(sd, 0);

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&dev->sd.entity);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2680_device *dev;
	पूर्णांक ret;
	व्योम *pdata;
	अचिन्हित पूर्णांक i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&dev->sd, client, &ov2680_ops);

	pdata = gmin_camera_platक्रमm_data(&dev->sd,
					  ATOMISP_INPUT_FORMAT_RAW_10,
					  atomisp_bayer_order_bggr);
	अगर (!pdata) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ret = ov2680_s_config(&dev->sd, client->irq, pdata);
	अगर (ret)
		जाओ out_मुक्त;

	ret = atomisp_रेजिस्टर_i2c_module(&dev->sd, pdata, RAW_CAMERA);
	अगर (ret)
		जाओ out_मुक्त;

	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->क्रमmat.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret =
	    v4l2_ctrl_handler_init(&dev->ctrl_handler,
				   ARRAY_SIZE(ov2680_controls));
	अगर (ret) अणु
		ov2680_हटाओ(client);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ov2680_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &ov2680_controls[i],
				     शून्य);

	अगर (dev->ctrl_handler.error) अणु
		ov2680_हटाओ(client);
		वापस dev->ctrl_handler.error;
	पूर्ण

	/* Use same lock क्रम controls as क्रम everything अन्यथा. */
	dev->ctrl_handler.lock = &dev->input_lock;
	dev->sd.ctrl_handler = &dev->ctrl_handler;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret) अणु
		ov2680_हटाओ(client);
		dev_dbg(&client->dev, "+++ remove ov2680\n");
	पूर्ण
	वापस ret;
out_मुक्त:
	dev_dbg(&client->dev, "+++ out free\n");
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ov2680_acpi_match[] = अणु
	अणु"XXOV2680"पूर्ण,
	अणु"OVTI2680"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ov2680_acpi_match);

अटल काष्ठा i2c_driver ov2680_driver = अणु
	.driver = अणु
		.name = "ov2680",
		.acpi_match_table = ov2680_acpi_match,
	पूर्ण,
	.probe_new = ov2680_probe,
	.हटाओ = ov2680_हटाओ,
पूर्ण;
module_i2c_driver(ov2680_driver);

MODULE_AUTHOR("Jacky Wang <Jacky_wang@ovt.com>");
MODULE_DESCRIPTION("A low-level driver for OmniVision 2680 sensors");
MODULE_LICENSE("GPL");
