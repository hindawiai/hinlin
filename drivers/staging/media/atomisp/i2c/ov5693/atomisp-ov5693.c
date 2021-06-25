<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम OmniVision OV5693 1080p HD camera sensor.
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
#समावेश <linux/acpi.h>
#समावेश "../../include/linux/atomisp_gmin_platform.h"

#समावेश "ov5693.h"
#समावेश "ad5823.h"

#घोषणा __cci_delay(t) \
	करो अणु \
		अगर ((t) < 10) अणु \
			usleep_range((t) * 1000, ((t) + 1) * 1000); \
		पूर्ण अन्यथा अणु \
			msleep((t)); \
		पूर्ण \
	पूर्ण जबतक (0)

/* Value 30ms reached through experimentation on byt ecs.
 * The DS specअगरies a much lower value but when using a smaller value
 * the I2C bus someबार locks up permanently when starting the camera.
 * This issue could not be reproduced on cht, so we can reduce the
 * delay value to a lower value when insmod.
 */
अटल uपूर्णांक up_delay = 30;
module_param(up_delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(up_delay,
		 "Delay prior to the first CCI transaction for ov5693");

अटल पूर्णांक vcm_ad_i2c_wr8(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg;
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;

	msg.addr = VCM_ADDR;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = &buf[0];

	err = i2c_transfer(client->adapter, &msg, 1);
	अगर (err != 1) अणु
		dev_err(&client->dev, "%s: vcm i2c fail, err code = %d\n",
			__func__, err);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ad5823_i2c_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;
	msg.addr = AD5823_VCM_ADDR;
	msg.flags = 0;
	msg.len = 0x02;
	msg.buf = &buf[0];

	अगर (i2c_transfer(client->adapter, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक ad5823_i2c_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2];
	u8 buf[2];

	buf[0] = reg;
	buf[1] = 0;

	msg[0].addr = AD5823_VCM_ADDR;
	msg[0].flags = 0;
	msg[0].len = 0x01;
	msg[0].buf = &buf[0];

	msg[1].addr = 0x0c;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 0x01;
	msg[1].buf = &buf[1];
	*val = 0;
	अगर (i2c_transfer(client->adapter, msg, 2) != 2)
		वापस -EIO;
	*val = buf[1];
	वापस 0;
पूर्ण

अटल स्थिर u32 ov5693_embedded_effective_size = 28;

/* i2c पढ़ो/ग_लिखो stuff */
अटल पूर्णांक ov5693_पढ़ो_reg(काष्ठा i2c_client *client,
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

	अगर (data_length != OV5693_8BIT && data_length != OV5693_16BIT
	    && data_length != OV5693_32BIT) अणु
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
	अगर (data_length == OV5693_8BIT)
		*val = (u8)data[0];
	अन्यथा अगर (data_length == OV5693_16BIT)
		*val = be16_to_cpu(*(__be16 *)&data[0]);
	अन्यथा
		*val = be32_to_cpu(*(__be32 *)&data[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 len, u8 *data)
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

अटल पूर्णांक vcm_dw_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 data)
अणु
	काष्ठा i2c_msg msg;
	स्थिर पूर्णांक num_msg = 1;
	पूर्णांक ret;
	__be16 val;

	val = cpu_to_be16(data);
	msg.addr = VCM_ADDR;
	msg.flags = 0;
	msg.len = OV5693_16BIT;
	msg.buf = (व्योम *)&val;

	ret = i2c_transfer(client->adapter, &msg, 1);

	वापस ret == num_msg ? 0 : -EIO;
पूर्ण

/*
 * Theory: per datasheet, the two VCMs both allow क्रम a 2-byte पढ़ो.
 * The DW9714 करोesn't actually specअगरy what this करोes (it has a
 * two-byte ग_लिखो-only protocol, but specअगरies the पढ़ो sequence as
 * legal), but it वापसs the same data (zeroes) always, after an
 * unकरोcumented initial NAK.  The AD5823 has a one-byte address
 * रेजिस्टर to which all ग_लिखोs go, and subsequent पढ़ोs will cycle
 * through the 8 bytes of रेजिस्टरs.  Notably, the शेष values (the
 * device is always घातer-cycled affirmatively, so we can rely on
 * these) in AD5823 are not pairwise repetitions of the same 16 bit
 * word.  So all we have to करो is sequentially पढ़ो two bytes at a
 * समय and see अगर we detect a dअगरference in any of the first four
 * pairs.
 */
अटल पूर्णांक vcm_detect(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, ret;
	काष्ठा i2c_msg msg;
	u16 data0 = 0, data;

	क्रम (i = 0; i < 4; i++) अणु
		msg.addr = VCM_ADDR;
		msg.flags = I2C_M_RD;
		msg.len = माप(data);
		msg.buf = (u8 *)&data;
		ret = i2c_transfer(client->adapter, &msg, 1);

		/*
		 * DW9714 always fails the first पढ़ो and वापसs
		 * zeroes क्रम subsequent ones
		 */
		अगर (i == 0 && ret == -EREMOTEIO) अणु
			data0 = 0;
			जारी;
		पूर्ण

		अगर (i == 0)
			data0 = data;

		अगर (data != data0)
			वापस VCM_AD5823;
	पूर्ण
	वापस ret == 1 ? VCM_DW9714 : ret;
पूर्ण

अटल पूर्णांक ov5693_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length,
			    u16 reg, u16 val)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data[4] = अणु0पूर्ण;
	__be16 *wreg = (व्योम *)data;
	स्थिर u16 len = data_length + माप(u16); /* 16-bit address + data */

	अगर (data_length != OV5693_8BIT && data_length != OV5693_16BIT) अणु
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* high byte goes out first */
	*wreg = cpu_to_be16(reg);

	अगर (data_length == OV5693_8BIT) अणु
		data[2] = (u8)(val);
	पूर्ण अन्यथा अणु
		/* OV5693_16BIT */
		__be16 *wdata = (व्योम *)&data[2];

		*wdata = cpu_to_be16(val);
	पूर्ण

	ret = ov5693_i2c_ग_लिखो(client, len, data);
	अगर (ret)
		dev_err(&client->dev,
			"write error: wrote 0x%x to offset 0x%x error %d",
			val, reg, ret);

	वापस ret;
पूर्ण

/*
 * ov5693_ग_लिखो_reg_array - Initializes a list of OV5693 रेजिस्टरs
 * @client: i2c driver client काष्ठाure
 * @reglist: list of रेजिस्टरs to be written
 *
 * This function initializes a list of रेजिस्टरs. When consecutive addresses
 * are found in a row on the list, this function creates a buffer and sends
 * consecutive data in a single i2c_transfer().
 *
 * __ov5693_flush_reg_array, __ov5693_buf_reg_array() and
 * __ov5693_ग_लिखो_reg_is_consecutive() are पूर्णांकernal functions to
 * ov5693_ग_लिखो_reg_array_fast() and should be not used anywhere अन्यथा.
 *
 */

अटल पूर्णांक __ov5693_flush_reg_array(काष्ठा i2c_client *client,
				    काष्ठा ov5693_ग_लिखो_ctrl *ctrl)
अणु
	u16 size;
	__be16 *reg = (व्योम *)&ctrl->buffer.addr;

	अगर (ctrl->index == 0)
		वापस 0;

	size = माप(u16) + ctrl->index; /* 16-bit address + data */

	*reg = cpu_to_be16(ctrl->buffer.addr);
	ctrl->index = 0;

	वापस ov5693_i2c_ग_लिखो(client, size, (u8 *)reg);
पूर्ण

अटल पूर्णांक __ov5693_buf_reg_array(काष्ठा i2c_client *client,
				  काष्ठा ov5693_ग_लिखो_ctrl *ctrl,
				  स्थिर काष्ठा ov5693_reg *next)
अणु
	पूर्णांक size;
	__be16 *data16;

	चयन (next->type) अणु
	हाल OV5693_8BIT:
		size = 1;
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		अवरोध;
	हाल OV5693_16BIT:
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
	अगर (ctrl->index + माप(u16) >= OV5693_MAX_WRITE_BUF_SIZE)
		वापस __ov5693_flush_reg_array(client, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक __ov5693_ग_लिखो_reg_is_consecutive(काष्ठा i2c_client *client,
	काष्ठा ov5693_ग_लिखो_ctrl *ctrl,
	स्थिर काष्ठा ov5693_reg *next)
अणु
	अगर (ctrl->index == 0)
		वापस 1;

	वापस ctrl->buffer.addr + ctrl->index == next->reg;
पूर्ण

अटल पूर्णांक ov5693_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				  स्थिर काष्ठा ov5693_reg *reglist)
अणु
	स्थिर काष्ठा ov5693_reg *next = reglist;
	काष्ठा ov5693_ग_लिखो_ctrl ctrl;
	पूर्णांक err;

	ctrl.index = 0;
	क्रम (; next->type != OV5693_TOK_TERM; next++) अणु
		चयन (next->type & OV5693_TOK_MASK) अणु
		हाल OV5693_TOK_DELAY:
			err = __ov5693_flush_reg_array(client, &ctrl);
			अगर (err)
				वापस err;
			msleep(next->val);
			अवरोध;
		शेष:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed beक्रमe proceed.
			 */
			अगर (!__ov5693_ग_लिखो_reg_is_consecutive(client, &ctrl,
							       next)) अणु
				err = __ov5693_flush_reg_array(client, &ctrl);
				अगर (err)
					वापस err;
			पूर्ण
			err = __ov5693_buf_reg_array(client, &ctrl, next);
			अगर (err) अणु
				dev_err(&client->dev,
					"%s: write error, aborted\n",
					__func__);
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस __ov5693_flush_reg_array(client, &ctrl);
पूर्ण

अटल पूर्णांक ov5693_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV5693_FOCAL_LENGTH_NUM << 16) | OV5693_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम imx*/
	*val = (OV5693_F_NUMBER_DEFAULT_NUM << 16) | OV5693_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (OV5693_F_NUMBER_DEFAULT_NUM << 24) |
	       (OV5693_F_NUMBER_DEM << 16) |
	       (OV5693_F_NUMBER_DEFAULT_NUM << 8) | OV5693_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_g_bin_factor_x(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	*val = ov5693_res[dev->fmt_idx].bin_factor_x;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_g_bin_factor_y(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	*val = ov5693_res[dev->fmt_idx].bin_factor_y;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				  काष्ठा camera_mipi_info *info,
				  स्थिर काष्ठा ov5693_resolution *res)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	अचिन्हित पूर्णांक pix_clk_freq_hz;
	u16 reg_val;
	पूर्णांक ret;

	अगर (!info)
		वापस -EINVAL;

	/* pixel घड़ी */
	pix_clk_freq_hz = res->pix_clk_freq * 1000000;

	dev->vt_pix_clk_freq_mhz = pix_clk_freq_hz;
	buf->vt_pix_clk_freq_mhz = pix_clk_freq_hz;

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = OV5693_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    OV5693_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = OV5693_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    OV5693_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = OV5693_FINE_INTG_TIME_MIN;
	buf->frame_length_lines = res->lines_per_frame;
	buf->line_length_pck = res->pixels_per_line;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	ret =  ov5693_पढ़ो_reg(client, OV5693_16BIT,
			       OV5693_HORIZONTAL_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_start = reg_val;

	ret =  ov5693_पढ़ो_reg(client, OV5693_16BIT,
			       OV5693_VERTICAL_START_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_start = reg_val;

	ret = ov5693_पढ़ो_reg(client, OV5693_16BIT,
			      OV5693_HORIZONTAL_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_end = reg_val;

	ret = ov5693_पढ़ो_reg(client, OV5693_16BIT,
			      OV5693_VERTICAL_END_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_end = reg_val;

	ret = ov5693_पढ़ो_reg(client, OV5693_16BIT,
			      OV5693_HORIZONTAL_OUTPUT_SIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = reg_val;

	ret = ov5693_पढ़ो_reg(client, OV5693_16BIT,
			      OV5693_VERTICAL_OUTPUT_SIZE_H, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = reg_val;

	buf->binning_factor_x = res->bin_factor_x ?
				res->bin_factor_x : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				res->bin_factor_y : 1;
	वापस 0;
पूर्ण

अटल दीर्घ __ov5693_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक coarse_itg,
				  पूर्णांक gain, पूर्णांक digitgain)

अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	u16 vts, hts;
	पूर्णांक ret, exp_val;

	hts = ov5693_res[dev->fmt_idx].pixels_per_line;
	vts = ov5693_res[dev->fmt_idx].lines_per_frame;
	/*
	 * If coarse_itg is larger than 1<<15, can not ग_लिखो to reg directly.
	 * The way is to ग_लिखो coarse_itg/2 to the reg, meanजबतक ग_लिखो 2*hts
	 * to the reg.
	 */
	अगर (coarse_itg > (1 << 15)) अणु
		hts = hts * 2;
		coarse_itg = (पूर्णांक)coarse_itg / 2;
	पूर्ण
	/* group hold */
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_GROUP_ACCESS, 0x00);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_GROUP_ACCESS);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_TIMING_HTS_H, (hts >> 8) & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_TIMING_HTS_H);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_TIMING_HTS_L, hts & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_TIMING_HTS_L);
		वापस ret;
	पूर्ण
	/* Increase the VTS to match exposure + MARGIN */
	अगर (coarse_itg > vts - OV5693_INTEGRATION_TIME_MARGIN)
		vts = (u16)coarse_itg + OV5693_INTEGRATION_TIME_MARGIN;

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_TIMING_VTS_H, (vts >> 8) & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_TIMING_VTS_H);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_TIMING_VTS_L, vts & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_TIMING_VTS_L);
		वापस ret;
	पूर्ण

	/* set exposure */

	/* Lower four bit should be 0*/
	exp_val = coarse_itg << 4;
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_EXPOSURE_L, exp_val & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_EXPOSURE_L);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_EXPOSURE_M, (exp_val >> 8) & 0xFF);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_EXPOSURE_M);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_EXPOSURE_H, (exp_val >> 16) & 0x0F);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_EXPOSURE_H);
		वापस ret;
	पूर्ण

	/* Analog gain */
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_AGC_L, gain & 0xff);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_AGC_L);
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_AGC_H, (gain >> 8) & 0xff);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: write %x error, aborted\n",
			__func__, OV5693_AGC_H);
		वापस ret;
	पूर्ण

	/* Digital gain */
	अगर (digitgain) अणु
		ret = ov5693_ग_लिखो_reg(client, OV5693_16BIT,
				       OV5693_MWB_RED_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev, "%s: write %x error, aborted\n",
				__func__, OV5693_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण

		ret = ov5693_ग_लिखो_reg(client, OV5693_16BIT,
				       OV5693_MWB_GREEN_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev, "%s: write %x error, aborted\n",
				__func__, OV5693_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण

		ret = ov5693_ग_लिखो_reg(client, OV5693_16BIT,
				       OV5693_MWB_BLUE_GAIN_H, digitgain);
		अगर (ret) अणु
			dev_err(&client->dev, "%s: write %x error, aborted\n",
				__func__, OV5693_MWB_RED_GAIN_H);
			वापस ret;
		पूर्ण
	पूर्ण

	/* End group */
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_GROUP_ACCESS, 0x10);
	अगर (ret)
		वापस ret;

	/* Delay launch group */
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_GROUP_ACCESS, 0xa0);
	अगर (ret)
		वापस ret;
	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_set_exposure(काष्ठा v4l2_subdev *sd, पूर्णांक exposure,
			       पूर्णांक gain, पूर्णांक digitgain)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);
	ret = __ov5693_set_exposure(sd, exposure, gain, digitgain);
	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल दीर्घ ov5693_s_exposure(काष्ठा v4l2_subdev *sd,
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
	वापस ov5693_set_exposure(sd, coarse_itg, analog_gain, digital_gain);
पूर्ण

अटल पूर्णांक ov5693_पढ़ो_otp_reg_array(काष्ठा i2c_client *client, u16 size,
				     u16 addr, u8 *buf)
अणु
	u16 index;
	पूर्णांक ret;
	u16 *pVal = शून्य;

	क्रम (index = 0; index <= size; index++) अणु
		pVal = (u16 *)(buf + index);
		ret =
		    ov5693_पढ़ो_reg(client, OV5693_8BIT, addr + index,
				    pVal);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ov5693_otp_पढ़ो(काष्ठा v4l2_subdev *sd, u8 *buf)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	पूर्णांक ret;
	पूर्णांक i;
	u8 *b = buf;

	dev->otp_size = 0;
	क्रम (i = 1; i < OV5693_OTP_BANK_MAX; i++) अणु
		/*set bank NO and OTP पढ़ो mode. */
		ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_OTP_BANK_REG,
				       (i | 0xc0));	//[7:6] 2'b11 [5:0] bank no
		अगर (ret) अणु
			dev_err(&client->dev, "failed to prepare OTP page\n");
			वापस ret;
		पूर्ण
		//pr_debug("write 0x%x->0x%x\n",OV5693_OTP_BANK_REG,(i|0xc0));

		/*enable पढ़ो */
		ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_OTP_READ_REG,
				       OV5693_OTP_MODE_READ);	// enable :1
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to set OTP reading mode page");
			वापस ret;
		पूर्ण
		//pr_debug("write 0x%x->0x%x\n",OV5693_OTP_READ_REG,OV5693_OTP_MODE_READ);

		/* Reading the OTP data array */
		ret = ov5693_पढ़ो_otp_reg_array(client, OV5693_OTP_BANK_SIZE,
						OV5693_OTP_START_ADDR,
						b);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to read OTP data\n");
			वापस ret;
		पूर्ण

		//pr_debug("BANK[%2d] %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", i, *b, *(b+1), *(b+2), *(b+3), *(b+4), *(b+5), *(b+6), *(b+7), *(b+8), *(b+9), *(b+10), *(b+11), *(b+12), *(b+13), *(b+14), *(b+15));

		//Intel OTP map, try to पढ़ो 320byts first.
		अगर (i == 21) अणु
			अगर ((*b) == 0) अणु
				dev->otp_size = 320;
				अवरोध;
			पूर्ण अन्यथा अणु
				b = buf;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (i ==
			   24) अणु		//अगर the first 320bytes data करोesn't not exist, try to पढ़ो the next 32bytes data.
			अगर ((*b) == 0) अणु
				dev->otp_size = 32;
				अवरोध;
			पूर्ण अन्यथा अणु
				b = buf;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (i ==
			   27) अणु		//अगर the prvious 32bytes data करोesn't exist, try to पढ़ो the next 32bytes data again.
			अगर ((*b) == 0) अणु
				dev->otp_size = 32;
				अवरोध;
			पूर्ण अन्यथा अणु
				dev->otp_size = 0;	// no OTP data.
				अवरोध;
			पूर्ण
		पूर्ण

		b = b + OV5693_OTP_BANK_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read otp data and store it पूर्णांकo a kदो_स्मृतिed buffer.
 * The caller must kमुक्त the buffer when no more needed.
 * @size: set to the size of the वापसed otp data.
 */
अटल व्योम *ov5693_otp_पढ़ो(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 *buf;
	पूर्णांक ret;

	buf = devm_kzalloc(&client->dev, (OV5693_OTP_DATA_SIZE + 16), GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	//otp valid after mipi on and sw stream on
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_FRAME_OFF_NUM, 0x00);

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_SW_STREAM, OV5693_START_STREAMING);

	ret = __ov5693_otp_पढ़ो(sd, buf);

	//mipi off and sw stream off after otp पढ़ो
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_FRAME_OFF_NUM, 0x0f);

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_SW_STREAM, OV5693_STOP_STREAMING);

	/* Driver has failed to find valid data */
	अगर (ret) अणु
		dev_err(&client->dev, "sensor found no valid OTP data\n");
		वापस ERR_PTR(ret);
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक ov5693_g_priv_पूर्णांक_data(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_निजी_पूर्णांक_data *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	u8 __user *to = priv->data;
	u32 पढ़ो_size = priv->size;
	पूर्णांक ret;

	/* No need to copy data अगर size is 0 */
	अगर (!पढ़ो_size)
		जाओ out;

	अगर (IS_ERR(dev->otp_data)) अणु
		dev_err(&client->dev, "OTP data not available");
		वापस PTR_ERR(dev->otp_data);
	पूर्ण

	/* Correct पढ़ो_size value only अगर bigger than maximum */
	अगर (पढ़ो_size > OV5693_OTP_DATA_SIZE)
		पढ़ो_size = OV5693_OTP_DATA_SIZE;

	ret = copy_to_user(to, dev->otp_data, पढ़ो_size);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to copy OTP data to user\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	pr_debug("%s read_size:%d\n", __func__, पढ़ो_size);

out:
	/* Return correct size */
	priv->size = dev->otp_size;

	वापस 0;
पूर्ण

अटल दीर्घ ov5693_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस ov5693_s_exposure(sd, arg);
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
		वापस ov5693_g_priv_पूर्णांक_data(sd, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This वापसs the exposure समय being used. This should only be used
 * क्रम filling in EXIF data, not क्रम actual image processing.
 */
अटल पूर्णांक ov5693_q_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 reg_v, reg_v2;
	पूर्णांक ret;

	/* get exposure */
	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_EXPOSURE_L,
			      &reg_v);
	अगर (ret)
		जाओ err;

	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_EXPOSURE_M,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	reg_v += reg_v2 << 8;
	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_EXPOSURE_H,
			      &reg_v2);
	अगर (ret)
		जाओ err;

	*value = reg_v + (((u32)reg_v2 << 16));
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ad5823_t_focus_vcm(काष्ठा v4l2_subdev *sd, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = -EINVAL;
	u8 vcm_code;

	ret = ad5823_i2c_पढ़ो(client, AD5823_REG_VCM_CODE_MSB, &vcm_code);
	अगर (ret)
		वापस ret;

	/* set reg VCM_CODE_MSB Bit[1:0] */
	vcm_code = (vcm_code & VCM_CODE_MSB_MASK) |
		   ((val >> 8) & ~VCM_CODE_MSB_MASK);
	ret = ad5823_i2c_ग_लिखो(client, AD5823_REG_VCM_CODE_MSB, vcm_code);
	अगर (ret)
		वापस ret;

	/* set reg VCM_CODE_LSB Bit[7:0] */
	ret = ad5823_i2c_ग_लिखो(client, AD5823_REG_VCM_CODE_LSB, (val & 0xff));
	अगर (ret)
		वापस ret;

	/* set required vcm move समय */
	vcm_code = AD5823_RESOन_अंकCE_PERIOD / AD5823_RESOन_अंकCE_COEF
		   - AD5823_HIGH_FREQ_RANGE;
	ret = ad5823_i2c_ग_लिखो(client, AD5823_REG_VCM_MOVE_TIME, vcm_code);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5823_t_focus_असल(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	value = min(value, AD5823_MAX_FOCUS_POS);
	वापस ad5823_t_focus_vcm(sd, value);
पूर्ण

अटल पूर्णांक ov5693_t_focus_असल(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "%s: FOCUS_POS: 0x%x\n", __func__, value);
	value = clamp(value, 0, OV5693_VCM_MAX_FOCUS_POS);
	अगर (dev->vcm == VCM_DW9714) अणु
		अगर (dev->vcm_update) अणु
			ret = vcm_dw_i2c_ग_लिखो(client, VCM_PROTECTION_OFF);
			अगर (ret)
				वापस ret;
			ret = vcm_dw_i2c_ग_लिखो(client, सूचीECT_VCM);
			अगर (ret)
				वापस ret;
			ret = vcm_dw_i2c_ग_लिखो(client, VCM_PROTECTION_ON);
			अगर (ret)
				वापस ret;
			dev->vcm_update = false;
		पूर्ण
		ret = vcm_dw_i2c_ग_लिखो(client,
				       vcm_val(value, VCM_DEFAULT_S));
	पूर्ण अन्यथा अगर (dev->vcm == VCM_AD5823) अणु
		ad5823_t_focus_असल(sd, value);
	पूर्ण
	अगर (ret == 0) अणु
		dev->number_of_steps = value - dev->focus;
		dev->focus = value;
		dev->बारtamp_t_focus_असल = kसमय_get();
	पूर्ण अन्यथा
		dev_err(&client->dev,
			"%s: i2c failed. ret %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_t_focus_rel(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	वापस ov5693_t_focus_असल(sd, dev->focus + value);
पूर्ण

#घोषणा DELAY_PER_STEP_NS	1000000
#घोषणा DELAY_MAX_PER_STEP_NS	(1000000 * 1023)
अटल पूर्णांक ov5693_q_focus_status(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	u32 status = 0;
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	kसमय_प्रकार tempसमय;
	kसमय_प्रकार समयdelay = ns_to_kसमय(min_t(u32,
					      असल(dev->number_of_steps) * DELAY_PER_STEP_NS,
					      DELAY_MAX_PER_STEP_NS));

	tempसमय = kसमय_sub(kसमय_get(), (dev->बारtamp_t_focus_असल));
	अगर (kसमय_compare(tempसमय, समयdelay) <= 0) अणु
		status |= ATOMISP_FOCUS_STATUS_MOVING;
		status |= ATOMISP_FOCUS_HP_IN_PROGRESS;
	पूर्ण अन्यथा अणु
		status |= ATOMISP_FOCUS_STATUS_ACCEPTS_NEW_MOVE;
		status |= ATOMISP_FOCUS_HP_COMPLETE;
	पूर्ण

	*value = status;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_q_focus_असल(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	s32 val;

	ov5693_q_focus_status(sd, &val);

	अगर (val & ATOMISP_FOCUS_STATUS_MOVING)
		*value  = dev->focus - dev->number_of_steps;
	अन्यथा
		*value  = dev->focus;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_t_vcm_slew(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	dev->number_of_steps = value;
	dev->vcm_update = true;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_t_vcm_timing(काष्ठा v4l2_subdev *sd, s32 value)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	dev->number_of_steps = value;
	dev->vcm_update = true;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5693_device *dev =
	    container_of(ctrl->handler, काष्ठा ov5693_device, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FOCUS_ABSOLUTE:
		dev_dbg(&client->dev, "%s: CID_FOCUS_ABSOLUTE:%d.\n",
			__func__, ctrl->val);
		ret = ov5693_t_focus_असल(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCUS_RELATIVE:
		dev_dbg(&client->dev, "%s: CID_FOCUS_RELATIVE:%d.\n",
			__func__, ctrl->val);
		ret = ov5693_t_focus_rel(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VCM_SLEW:
		ret = ov5693_t_vcm_slew(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VCM_TIMING:
		ret = ov5693_t_vcm_timing(&dev->sd, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5693_device *dev =
	    container_of(ctrl->handler, काष्ठा ov5693_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = ov5693_q_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = ov5693_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = ov5693_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = ov5693_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCUS_ABSOLUTE:
		ret = ov5693_q_focus_असल(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCUS_STATUS:
		ret = ov5693_q_focus_status(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_HORZ:
		ret = ov5693_g_bin_factor_x(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_VERT:
		ret = ov5693_g_bin_factor_y(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = ov5693_s_ctrl,
	.g_अस्थिर_ctrl = ov5693_g_अस्थिर_ctrl
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config ov5693_controls[] = अणु
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
		.min = OV5693_FOCAL_LENGTH_DEFAULT,
		.max = OV5693_FOCAL_LENGTH_DEFAULT,
		.step = 0x01,
		.def = OV5693_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number",
		.min = OV5693_F_NUMBER_DEFAULT,
		.max = OV5693_F_NUMBER_DEFAULT,
		.step = 0x01,
		.def = OV5693_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "f-number range",
		.min = OV5693_F_NUMBER_RANGE,
		.max = OV5693_F_NUMBER_RANGE,
		.step = 0x01,
		.def = OV5693_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCUS_ABSOLUTE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "focus move absolute",
		.min = 0,
		.max = OV5693_VCM_MAX_FOCUS_POS,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCUS_RELATIVE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "focus move relative",
		.min = OV5693_VCM_MAX_FOCUS_NEG,
		.max = OV5693_VCM_MAX_FOCUS_POS,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCUS_STATUS,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "focus status",
		.min = 0,
		.max = 100,		/* allow क्रमागत to grow in the future */
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_VCM_SLEW,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "vcm slew",
		.min = 0,
		.max = OV5693_VCM_SLEW_STEP_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_VCM_TIMING,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "vcm step time",
		.min = 0,
		.max = OV5693_VCM_SLEW_TIME_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_HORZ,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "horizontal binning factor",
		.min = 0,
		.max = OV5693_BIN_FACTOR_MAX,
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
		.max = OV5693_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov5693_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	pr_info("%s\n", __func__);
	mutex_lock(&dev->input_lock);
	dev->vcm_update = false;

	अगर (dev->vcm == VCM_AD5823) अणु
		ret = vcm_ad_i2c_wr8(client, 0x01, 0x01); /* vcm init test */
		अगर (ret)
			dev_err(&client->dev,
				"vcm reset failed\n");
		/*change the mode*/
		ret = ad5823_i2c_ग_लिखो(client, AD5823_REG_VCM_CODE_MSB,
				       AD5823_RING_CTRL_ENABLE);
		अगर (ret)
			dev_err(&client->dev,
				"vcm enable ringing failed\n");
		ret = ad5823_i2c_ग_लिखो(client, AD5823_REG_MODE,
				       AD5823_ARC_RES1);
		अगर (ret)
			dev_err(&client->dev,
				"vcm change mode failed\n");
	पूर्ण

	/*change initial focus value क्रम ad5823*/
	अगर (dev->vcm == VCM_AD5823) अणु
		dev->focus = AD5823_INIT_FOCUS_POS;
		ov5693_t_focus_असल(sd, AD5823_INIT_FOCUS_POS);
	पूर्ण अन्यथा अणु
		dev->focus = 0;
		ov5693_t_focus_असल(sd, 0);
	पूर्ण

	mutex_unlock(&dev->input_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret;
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	/*
	 * This driver assumes "internal DVDD, PWDNB tied to DOVDD".
	 * In this set up only gpio0 (XSHUTDN) should be available
	 * but in some products (क्रम example ECS) gpio1 (PWDNB) is
	 * also available. If gpio1 is available we emulate it being
	 * tied to DOVDD here.
	 */
	अगर (flag) अणु
		ret = dev->platक्रमm_data->v2p8_ctrl(sd, 1);
		dev->platक्रमm_data->gpio1_ctrl(sd, 1);
		अगर (ret == 0) अणु
			ret = dev->platक्रमm_data->v1p8_ctrl(sd, 1);
			अगर (ret) अणु
				dev->platक्रमm_data->gpio1_ctrl(sd, 0);
				ret = dev->platक्रमm_data->v2p8_ctrl(sd, 0);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->platक्रमm_data->gpio1_ctrl(sd, 0);
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 0);
		ret |= dev->platक्रमm_data->v2p8_ctrl(sd, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	वापस dev->platक्रमm_data->gpio0_ctrl(sd, flag);
पूर्ण

अटल पूर्णांक __घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
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
	/* add this delay समय to 10~11ms*/
	usleep_range(10000, 11000);

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

	__cci_delay(up_delay);

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
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	dev->focus = OV5693_INVALID_CONFIG;
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

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	अटल स्थिर पूर्णांक retry_count = 4;
	पूर्णांक i, ret;

	क्रम (i = 0; i < retry_count; i++) अणु
		ret = __घातer_up(sd);
		अगर (!ret)
			वापस 0;

		घातer_करोwn(sd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	pr_info("%s: on %d\n", __func__, on);
	अगर (on == 0)
		वापस घातer_करोwn(sd);
	अन्यथा अणु
		ret = घातer_up(sd);
		अगर (!ret) अणु
			ret = ov5693_init(sd);
			/* restore settings */
			ov5693_res = ov5693_res_preview;
			N_RES = N_RES_PREVIEW;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * distance - calculate the distance
 * @res: resolution
 * @w: width
 * @h: height
 *
 * Get the gap between res_w/res_h and w/h.
 * distance = (res_w/res_h - w/h) / (w/h) * 8192
 * res->width/height smaller than w/h wouldn't be considered.
 * The gap of ratio larger than 1/8 wouldn't be considered.
 * Returns the value of gap or -1 अगर fail.
 */
#घोषणा LARGEST_ALLOWED_RATIO_MISMATCH 1024
अटल पूर्णांक distance(काष्ठा ov5693_resolution *res, u32 w, u32 h)
अणु
	पूर्णांक ratio;
	पूर्णांक distance;

	अगर (w == 0 || h == 0 ||
	    res->width < w || res->height < h)
		वापस -1;

	ratio = res->width << 13;
	ratio /= w;
	ratio *= h;
	ratio /= res->height;

	distance = असल(ratio - 8192);

	अगर (distance > LARGEST_ALLOWED_RATIO_MISMATCH)
		वापस -1;

	वापस distance;
पूर्ण

/* Return the nearest higher resolution index
 * Firstly try to find the approximate aspect ratio resolution
 * If we find multiple same AR resolutions, choose the
 * minimal size.
 */
अटल पूर्णांक nearest_resolution_index(पूर्णांक w, पूर्णांक h)
अणु
	पूर्णांक i;
	पूर्णांक idx = -1;
	पूर्णांक dist;
	पूर्णांक min_dist = पूर्णांक_उच्च;
	पूर्णांक min_res_w = पूर्णांक_उच्च;
	काष्ठा ov5693_resolution *पंचांगp_res = शून्य;

	क्रम (i = 0; i < N_RES; i++) अणु
		पंचांगp_res = &ov5693_res[i];
		dist = distance(पंचांगp_res, w, h);
		अगर (dist == -1)
			जारी;
		अगर (dist < min_dist) अणु
			min_dist = dist;
			idx = i;
			min_res_w = ov5693_res[i].width;
			जारी;
		पूर्ण
		अगर (dist == min_dist && ov5693_res[i].width < min_res_w)
			idx = i;
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक get_resolution_index(पूर्णांक w, पूर्णांक h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RES; i++) अणु
		अगर (w != ov5693_res[i].width)
			जारी;
		अगर (h != ov5693_res[i].height)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* TODO: हटाओ it. */
अटल पूर्णांक startup(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT,
			       OV5693_SW_RESET, 0x01);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693 reset err.\n");
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg_array(client, ov5693_global_setting);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693 write register err.\n");
		वापस ret;
	पूर्ण

	ret = ov5693_ग_लिखो_reg_array(client, ov5693_res[dev->fmt_idx].regs);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693 write register err.\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा camera_mipi_info *ov5693_info = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक idx;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	अगर (!fmt)
		वापस -EINVAL;
	ov5693_info = v4l2_get_subdev_hostdata(sd);
	अगर (!ov5693_info)
		वापस -EINVAL;

	mutex_lock(&dev->input_lock);
	idx = nearest_resolution_index(fmt->width, fmt->height);
	अगर (idx == -1) अणु
		/* वापस the largest resolution */
		fmt->width = ov5693_res[N_RES - 1].width;
		fmt->height = ov5693_res[N_RES - 1].height;
	पूर्ण अन्यथा अणु
		fmt->width = ov5693_res[idx].width;
		fmt->height = ov5693_res[idx].height;
	पूर्ण

	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;
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
		पूर्णांक i = 0;

		dev_err(&client->dev, "ov5693 startup err, retry to power up\n");
		क्रम (i = 0; i < OV5693_POWER_UP_RETRY_NUM; i++) अणु
			dev_err(&client->dev,
				"ov5693 retry to power up %d/%d times, result: ",
				i + 1, OV5693_POWER_UP_RETRY_NUM);
			घातer_करोwn(sd);
			ret = घातer_up(sd);
			अगर (!ret) अणु
				mutex_unlock(&dev->input_lock);
				ov5693_init(sd);
				mutex_lock(&dev->input_lock);
			पूर्ण अन्यथा अणु
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
	पूर्ण

	/*
	 * After sensor settings are set to HW, someबार stream is started.
	 * This would cause ISP समयout because ISP is not पढ़ोy to receive
	 * data yet. So add stop streaming here.
	 */
	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_SW_STREAM,
			       OV5693_STOP_STREAMING);
	अगर (ret)
		dev_warn(&client->dev, "ov5693 stream off err\n");

	ret = ov5693_get_पूर्णांकg_factor(client, ov5693_info,
				     &ov5693_res[dev->fmt_idx]);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to get integration_factor\n");
		जाओ err;
	पूर्ण

	ov5693_info->metadata_width = fmt->width * 10 / 8;
	ov5693_info->metadata_height = 1;
	ov5693_info->metadata_effective_width = &ov5693_embedded_effective_size;

err:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!fmt)
		वापस -EINVAL;

	fmt->width = ov5693_res[dev->fmt_idx].width;
	fmt->height = ov5693_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_detect(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 high, low;
	पूर्णांक ret;
	u16 id;
	u8 revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_SC_CMMN_CHIP_ID_H, &high);
	अगर (ret) अणु
		dev_err(&client->dev, "sensor_id_high = 0x%x\n", high);
		वापस -ENODEV;
	पूर्ण
	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_SC_CMMN_CHIP_ID_L, &low);
	id = ((((u16)high) << 8) | (u16)low);

	अगर (id != OV5693_ID) अणु
		dev_err(&client->dev, "sensor ID error 0x%x\n", id);
		वापस -ENODEV;
	पूर्ण

	ret = ov5693_पढ़ो_reg(client, OV5693_8BIT,
			      OV5693_SC_CMMN_SUB_ID, &high);
	revision = (u8)high & 0x0f;

	dev_dbg(&client->dev, "sensor_revision = 0x%x\n", revision);
	dev_dbg(&client->dev, "detect ov5693 success\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	mutex_lock(&dev->input_lock);

	ret = ov5693_ग_लिखो_reg(client, OV5693_8BIT, OV5693_SW_STREAM,
			       enable ? OV5693_START_STREAMING :
			       OV5693_STOP_STREAMING);

	mutex_unlock(&dev->input_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_s_config(काष्ठा v4l2_subdev *sd,
			   पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);
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
		dev_err(&client->dev, "ov5693 power-off err.\n");
		जाओ fail_घातer_off;
	पूर्ण

	ret = घातer_up(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693 power-up err.\n");
		जाओ fail_घातer_on;
	पूर्ण

	अगर (!dev->vcm)
		dev->vcm = vcm_detect(client);

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	/* config & detect sensor */
	ret = ov5693_detect(client);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693_detect err s_config.\n");
		जाओ fail_csi_cfg;
	पूर्ण

	dev->otp_data = ov5693_otp_पढ़ो(sd);

	/* turn off sensor, after probed */
	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "ov5693 power-off err.\n");
		जाओ fail_csi_cfg;
	पूर्ण
	mutex_unlock(&dev->input_lock);

	वापस ret;

fail_csi_cfg:
	dev->platक्रमm_data->csi_cfg(sd, 0);
fail_घातer_on:
	घातer_करोwn(sd);
	dev_err(&client->dev, "sensor power-gating failed\n");
fail_घातer_off:
	mutex_unlock(&dev->input_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5693_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = ov5693_res[dev->fmt_idx].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = ov5693_res[index].width;
	fse->min_height = ov5693_res[index].height;
	fse->max_width = ov5693_res[index].width;
	fse->max_height = ov5693_res[index].height;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5693_video_ops = अणु
	.s_stream = ov5693_s_stream,
	.g_frame_पूर्णांकerval = ov5693_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov5693_core_ops = अणु
	.s_घातer = ov5693_s_घातer,
	.ioctl = ov5693_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5693_pad_ops = अणु
	.क्रमागत_mbus_code = ov5693_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov5693_क्रमागत_frame_size,
	.get_fmt = ov5693_get_fmt,
	.set_fmt = ov5693_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5693_ops = अणु
	.core = &ov5693_core_ops,
	.video = &ov5693_video_ops,
	.pad = &ov5693_pad_ops,
पूर्ण;

अटल पूर्णांक ov5693_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5693_device *dev = to_ov5693_sensor(sd);

	dev_dbg(&client->dev, "ov5693_remove...\n");

	dev->platक्रमm_data->csi_cfg(sd, 0);

	v4l2_device_unरेजिस्टर_subdev(sd);

	atomisp_gmin_हटाओ_subdev(sd);

	media_entity_cleanup(&dev->sd.entity);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5693_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov5693_device *dev;
	पूर्णांक i2c;
	पूर्णांक ret;
	व्योम *pdata;
	अचिन्हित पूर्णांक i;

	/*
	 * Firmware workaround: Some modules use a "secondary default"
	 * address of 0x10 which करोesn't appear on schematics, and
	 * some BIOS versions haven't gotten the memo.  Work around
	 * via config.
	 */
	i2c = gmin_get_var_पूर्णांक(&client->dev, false, "I2CAddr", -1);
	अगर (i2c != -1) अणु
		dev_info(&client->dev,
			 "Overriding firmware-provided I2C address (0x%x) with 0x%x\n",
			 client->addr, i2c);
		client->addr = i2c;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&dev->sd, client, &ov5693_ops);

	pdata = gmin_camera_platक्रमm_data(&dev->sd,
					  ATOMISP_INPUT_FORMAT_RAW_10,
					  atomisp_bayer_order_bggr);
	अगर (!pdata) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ret = ov5693_s_config(&dev->sd, client->irq, pdata);
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
				   ARRAY_SIZE(ov5693_controls));
	अगर (ret) अणु
		ov5693_हटाओ(client);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ov5693_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &ov5693_controls[i],
				     शून्य);

	अगर (dev->ctrl_handler.error) अणु
		ov5693_हटाओ(client);
		वापस dev->ctrl_handler.error;
	पूर्ण

	/* Use same lock क्रम controls as क्रम everything अन्यथा. */
	dev->ctrl_handler.lock = &dev->input_lock;
	dev->sd.ctrl_handler = &dev->ctrl_handler;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret)
		ov5693_हटाओ(client);

	वापस ret;
out_मुक्त:
	v4l2_device_unरेजिस्टर_subdev(&dev->sd);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ov5693_acpi_match[] = अणु
	अणु"INT33BE"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ov5693_acpi_match);

अटल काष्ठा i2c_driver ov5693_driver = अणु
	.driver = अणु
		.name = "ov5693",
		.acpi_match_table = ov5693_acpi_match,
	पूर्ण,
	.probe_new = ov5693_probe,
	.हटाओ = ov5693_हटाओ,
पूर्ण;
module_i2c_driver(ov5693_driver);

MODULE_DESCRIPTION("A low-level driver for OmniVision 5693 sensors");
MODULE_LICENSE("GPL");
