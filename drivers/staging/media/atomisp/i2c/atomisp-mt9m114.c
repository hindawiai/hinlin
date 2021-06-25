<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम mt9m114 Camera Sensor.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश "../include/linux/atomisp_gmin_platform.h"
#समावेश <media/v4l2-device.h>

#समावेश "mt9m114.h"

#घोषणा to_mt9m114_sensor(sd) container_of(sd, काष्ठा mt9m114_device, sd)

/*
 * TODO: use debug parameter to actually define when debug messages should
 * be prपूर्णांकed.
 */
अटल पूर्णांक debug;
अटल पूर्णांक aaalock;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

अटल पूर्णांक mt9m114_t_vflip(काष्ठा v4l2_subdev *sd, पूर्णांक value);
अटल पूर्णांक mt9m114_t_hflip(काष्ठा v4l2_subdev *sd, पूर्णांक value);
अटल पूर्णांक mt9m114_रुको_state(काष्ठा i2c_client *client, पूर्णांक समयout);

अटल पूर्णांक
mt9m114_पढ़ो_reg(काष्ठा i2c_client *client, u16 data_length, u32 reg, u32 *val)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg[2];
	अचिन्हित अक्षर data[4];

	अगर (!client->adapter) अणु
		v4l2_err(client, "%s error, no client->adapter\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (data_length != MISENSOR_8BIT && data_length != MISENSOR_16BIT
	    && data_length != MISENSOR_32BIT) अणु
		v4l2_err(client, "%s error, invalid data length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = MSG_LEN_OFFSET;
	msg[0].buf = data;

	/* high byte goes out first */
	data[0] = (u16)(reg >> 8);
	data[1] = (u16)(reg & 0xff);

	msg[1].addr = client->addr;
	msg[1].len = data_length;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = data;

	err = i2c_transfer(client->adapter, msg, 2);

	अगर (err >= 0) अणु
		*val = 0;
		/* high byte comes first */
		अगर (data_length == MISENSOR_8BIT)
			*val = data[0];
		अन्यथा अगर (data_length == MISENSOR_16BIT)
			*val = data[1] + (data[0] << 8);
		अन्यथा
			*val = data[3] + (data[2] << 8) +
			       (data[1] << 16) + (data[0] << 24);

		वापस 0;
	पूर्ण

	dev_err(&client->dev, "read from offset 0x%x error %d", reg, err);
	वापस err;
पूर्ण

अटल पूर्णांक
mt9m114_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length, u16 reg, u32 val)
अणु
	पूर्णांक num_msg;
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data[6] = अणु0पूर्ण;
	__be16 *wreg;
	पूर्णांक retry = 0;

	अगर (!client->adapter) अणु
		v4l2_err(client, "%s error, no client->adapter\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (data_length != MISENSOR_8BIT && data_length != MISENSOR_16BIT
	    && data_length != MISENSOR_32BIT) अणु
		v4l2_err(client, "%s error, invalid data_length\n", __func__);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));

again:
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2 + data_length;
	msg.buf = data;

	/* high byte goes out first */
	wreg = (व्योम *)data;
	*wreg = cpu_to_be16(reg);

	अगर (data_length == MISENSOR_8BIT) अणु
		data[2] = (u8)(val);
	पूर्ण अन्यथा अगर (data_length == MISENSOR_16BIT) अणु
		u16 *wdata = (व्योम *)&data[2];

		*wdata = be16_to_cpu(*(__be16 *)&data[2]);
	पूर्ण अन्यथा अणु
		/* MISENSOR_32BIT */
		u32 *wdata = (व्योम *)&data[2];

		*wdata = be32_to_cpu(*(__be32 *)&data[2]);
	पूर्ण

	num_msg = i2c_transfer(client->adapter, &msg, 1);

	/*
	 * HACK: Need some delay here क्रम Rev 2 sensors otherwise some
	 * रेजिस्टरs करो not seem to load correctly.
	 */
	mdelay(1);

	अगर (num_msg >= 0)
		वापस 0;

	dev_err(&client->dev, "write error: wrote 0x%x to offset 0x%x error %d",
		val, reg, num_msg);
	अगर (retry <= I2C_RETRY_COUNT) अणु
		dev_dbg(&client->dev, "retrying... %d", retry);
		retry++;
		msleep(20);
		जाओ again;
	पूर्ण

	वापस num_msg;
पूर्ण

/**
 * misensor_rmw_reg - Read/Modअगरy/Write a value to a रेजिस्टर in the sensor
 * device
 * @client: i2c driver client काष्ठाure
 * @data_length: 8/16/32-bits length
 * @reg: रेजिस्टर address
 * @mask: masked out bits
 * @set: bits set
 *
 * Read/modअगरy/ग_लिखो a value to a रेजिस्टर in the  sensor device.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक
misensor_rmw_reg(काष्ठा i2c_client *client, u16 data_length, u16 reg,
		 u32 mask, u32 set)
अणु
	पूर्णांक err;
	u32 val;

	/* Exit when no mask */
	अगर (mask == 0)
		वापस 0;

	/* @mask must not exceed data length */
	चयन (data_length) अणु
	हाल MISENSOR_8BIT:
		अगर (mask & ~0xff)
			वापस -EINVAL;
		अवरोध;
	हाल MISENSOR_16BIT:
		अगर (mask & ~0xffff)
			वापस -EINVAL;
		अवरोध;
	हाल MISENSOR_32BIT:
		अवरोध;
	शेष:
		/* Wrong @data_length */
		वापस -EINVAL;
	पूर्ण

	err = mt9m114_पढ़ो_reg(client, data_length, reg, &val);
	अगर (err) अणु
		v4l2_err(client, "%s error exit, read failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	val &= ~mask;

	/*
	 * Perक्रमm the OR function अगर the @set exists.
	 * Shअगरt @set value to target bit location. @set should set only
	 * bits included in @mask.
	 *
	 * REVISIT: This function expects @set to be non-shअगरted. Its shअगरt
	 * value is then defined to be equal to mask's LSB position.
	 * How about to inक्रमm values in their right offset position and aव्योम
	 * this unneeded shअगरt operation?
	 */
	set <<= ffs(mask) - 1;
	val |= set & mask;

	err = mt9m114_ग_लिखो_reg(client, data_length, reg, val);
	अगर (err) अणु
		v4l2_err(client, "%s error exit, write failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9m114_flush_reg_array(काष्ठा i2c_client *client,
				     काष्ठा mt9m114_ग_लिखो_ctrl *ctrl)
अणु
	काष्ठा i2c_msg msg;
	स्थिर पूर्णांक num_msg = 1;
	पूर्णांक ret;
	पूर्णांक retry = 0;
	__be16 *data16 = (व्योम *)&ctrl->buffer.addr;

	अगर (ctrl->index == 0)
		वापस 0;

again:
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2 + ctrl->index;
	*data16 = cpu_to_be16(ctrl->buffer.addr);
	msg.buf = (u8 *)&ctrl->buffer;

	ret = i2c_transfer(client->adapter, &msg, num_msg);
	अगर (ret != num_msg) अणु
		अगर (++retry <= I2C_RETRY_COUNT) अणु
			dev_dbg(&client->dev, "retrying... %d\n", retry);
			msleep(20);
			जाओ again;
		पूर्ण
		dev_err(&client->dev, "%s: i2c transfer error\n", __func__);
		वापस -EIO;
	पूर्ण

	ctrl->index = 0;

	/*
	 * REVISIT: Previously we had a delay after writing data to sensor.
	 * But it was हटाओd as our tests have shown it is not necessary
	 * anymore.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9m114_buf_reg_array(काष्ठा i2c_client *client,
				   काष्ठा mt9m114_ग_लिखो_ctrl *ctrl,
				   स्थिर काष्ठा misensor_reg *next)
अणु
	__be16 *data16;
	__be32 *data32;
	पूर्णांक err;

	/* Insufficient buffer? Let's flush and get more मुक्त space. */
	अगर (ctrl->index + next->length >= MT9M114_MAX_WRITE_BUF_SIZE) अणु
		err = __mt9m114_flush_reg_array(client, ctrl);
		अगर (err)
			वापस err;
	पूर्ण

	चयन (next->length) अणु
	हाल MISENSOR_8BIT:
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		अवरोध;
	हाल MISENSOR_16BIT:
		data16 = (__be16 *)&ctrl->buffer.data[ctrl->index];
		*data16 = cpu_to_be16((u16)next->val);
		अवरोध;
	हाल MISENSOR_32BIT:
		data32 = (__be32 *)&ctrl->buffer.data[ctrl->index];
		*data32 = cpu_to_be32(next->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* When first item is added, we need to store its starting address */
	अगर (ctrl->index == 0)
		ctrl->buffer.addr = next->reg;

	ctrl->index += next->length;

	वापस 0;
पूर्ण

अटल पूर्णांक
__mt9m114_ग_लिखो_reg_is_consecutive(काष्ठा i2c_client *client,
				   काष्ठा mt9m114_ग_लिखो_ctrl *ctrl,
				   स्थिर काष्ठा misensor_reg *next)
अणु
	अगर (ctrl->index == 0)
		वापस 1;

	वापस ctrl->buffer.addr + ctrl->index == next->reg;
पूर्ण

/*
 * mt9m114_ग_लिखो_reg_array - Initializes a list of mt9m114 रेजिस्टरs
 * @client: i2c driver client काष्ठाure
 * @reglist: list of रेजिस्टरs to be written
 * @poll: completion polling requirement
 * This function initializes a list of रेजिस्टरs. When consecutive addresses
 * are found in a row on the list, this function creates a buffer and sends
 * consecutive data in a single i2c_transfer().
 *
 * __mt9m114_flush_reg_array, __mt9m114_buf_reg_array() and
 * __mt9m114_ग_लिखो_reg_is_consecutive() are पूर्णांकernal functions to
 * mt9m114_ग_लिखो_reg_array() and should be not used anywhere अन्यथा.
 *
 */
अटल पूर्णांक mt9m114_ग_लिखो_reg_array(काष्ठा i2c_client *client,
				   स्थिर काष्ठा misensor_reg *reglist,
				   पूर्णांक poll)
अणु
	स्थिर काष्ठा misensor_reg *next = reglist;
	काष्ठा mt9m114_ग_लिखो_ctrl ctrl;
	पूर्णांक err;

	अगर (poll == PRE_POLLING) अणु
		err = mt9m114_रुको_state(client, MT9M114_WAIT_STAT_TIMEOUT);
		अगर (err)
			वापस err;
	पूर्ण

	ctrl.index = 0;
	क्रम (; next->length != MISENSOR_TOK_TERM; next++) अणु
		चयन (next->length & MISENSOR_TOK_MASK) अणु
		हाल MISENSOR_TOK_DELAY:
			err = __mt9m114_flush_reg_array(client, &ctrl);
			अगर (err)
				वापस err;
			msleep(next->val);
			अवरोध;
		हाल MISENSOR_TOK_RMW:
			err = __mt9m114_flush_reg_array(client, &ctrl);
			err |= misensor_rmw_reg(client,
						next->length &
						~MISENSOR_TOK_RMW,
						next->reg, next->val,
						next->val2);
			अगर (err) अणु
				dev_err(&client->dev, "%s read err. aborted\n",
					__func__);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed beक्रमe proceed.
			 */
			अगर (!__mt9m114_ग_लिखो_reg_is_consecutive(client, &ctrl,
								next)) अणु
				err = __mt9m114_flush_reg_array(client, &ctrl);
				अगर (err)
					वापस err;
			पूर्ण
			err = __mt9m114_buf_reg_array(client, &ctrl, next);
			अगर (err) अणु
				v4l2_err(client, "%s: write error, aborted\n",
					 __func__);
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	err = __mt9m114_flush_reg_array(client, &ctrl);
	अगर (err)
		वापस err;

	अगर (poll == POST_POLLING)
		वापस mt9m114_रुको_state(client, MT9M114_WAIT_STAT_TIMEOUT);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_रुको_state(काष्ठा i2c_client *client, पूर्णांक समयout)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	जबतक (समयout-- > 0) अणु
		ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT, 0x0080, &val);
		अगर (ret)
			वापस ret;
		अगर ((val & 0x2) == 0)
			वापस 0;
		msleep(20);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt9m114_set_suspend(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस mt9m114_ग_लिखो_reg_array(client,
				       mt9m114_standby_reg, POST_POLLING);
पूर्ण

अटल पूर्णांक mt9m114_init_common(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस mt9m114_ग_लिखो_reg_array(client, mt9m114_common, PRE_POLLING);
पूर्ण

अटल पूर्णांक घातer_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret;
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	अगर (flag) अणु
		ret = dev->platक्रमm_data->v2p8_ctrl(sd, 1);
		अगर (ret == 0) अणु
			ret = dev->platक्रमm_data->v1p8_ctrl(sd, 1);
			अगर (ret)
				ret = dev->platक्रमm_data->v2p8_ctrl(sd, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = dev->platक्रमm_data->v2p8_ctrl(sd, 0);
		ret = dev->platक्रमm_data->v1p8_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gpio_ctrl(काष्ठा v4l2_subdev *sd, bool flag)
अणु
	पूर्णांक ret;
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);

	अगर (!dev || !dev->platक्रमm_data)
		वापस -ENODEV;

	/* Note: current modules wire only one GPIO संकेत (RESET#),
	 * but the schematic wires up two to the connector.  BIOS
	 * versions have been unक्रमtunately inconsistent with which
	 * ACPI index RESET# is on, so hit both */

	अगर (flag) अणु
		ret = dev->platक्रमm_data->gpio0_ctrl(sd, 0);
		ret = dev->platक्रमm_data->gpio1_ctrl(sd, 0);
		msleep(60);
		ret |= dev->platक्रमm_data->gpio0_ctrl(sd, 1);
		ret |= dev->platक्रमm_data->gpio1_ctrl(sd, 1);
	पूर्ण अन्यथा अणु
		ret = dev->platक्रमm_data->gpio0_ctrl(sd, 0);
		ret = dev->platक्रमm_data->gpio1_ctrl(sd, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक घातer_up(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev, "no camera_sensor_platform_data");
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
	अगर (ret)
		dev_err(&client->dev, "gpio failed 1\n");
	/*
	 * according to DS, 44ms is needed between घातer up and first i2c
	 * commend
	 */
	msleep(50);

	वापस 0;

fail_clk:
	dev->platक्रमm_data->flisclk_ctrl(sd, 0);
fail_घातer:
	घातer_ctrl(sd, 0);
	dev_err(&client->dev, "sensor power-up failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक घातer_करोwn(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (!dev->platक्रमm_data) अणु
		dev_err(&client->dev, "no camera_sensor_platform_data");
		वापस -ENODEV;
	पूर्ण

	ret = dev->platक्रमm_data->flisclk_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "flisclk failed\n");

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "gpio failed 1\n");

	/* घातer control */
	ret = घातer_ctrl(sd, 0);
	अगर (ret)
		dev_err(&client->dev, "vprog failed.\n");

	/*according to DS, 20ms is needed after घातer करोwn*/
	msleep(20);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m114_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक घातer)
अणु
	अगर (घातer == 0)
		वापस घातer_करोwn(sd);
	अन्यथा अणु
		अगर (घातer_up(sd))
			वापस -EINVAL;

		वापस mt9m114_init_common(sd);
	पूर्ण
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
अटल पूर्णांक distance(काष्ठा mt9m114_res_काष्ठा स्थिर *res, u32 w, u32 h)
अणु
	अचिन्हित पूर्णांक w_ratio;
	अचिन्हित पूर्णांक h_ratio;
	पूर्णांक match;

	अगर (w == 0)
		वापस -1;
	w_ratio = (res->width << 13) / w;
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
	स्थिर काष्ठा mt9m114_res_काष्ठा *पंचांगp_res = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(mt9m114_res); i++) अणु
		पंचांगp_res = &mt9m114_res[i];
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

अटल पूर्णांक mt9m114_try_res(u32 *w, u32 *h)
अणु
	पूर्णांक idx = 0;

	अगर ((*w > MT9M114_RES_960P_SIZE_H)
	    || (*h > MT9M114_RES_960P_SIZE_V)) अणु
		*w = MT9M114_RES_960P_SIZE_H;
		*h = MT9M114_RES_960P_SIZE_V;
	पूर्ण अन्यथा अणु
		idx = nearest_resolution_index(*w, *h);

		/*
		 * nearest_resolution_index() करोesn't वापस smaller
		 *  resolutions. If it fails, it means the requested
		 *  resolution is higher than wecan support. Fallback
		 *  to highest possible resolution in this हाल.
		 */
		अगर (idx == -1)
			idx = ARRAY_SIZE(mt9m114_res) - 1;

		*w = mt9m114_res[idx].width;
		*h = mt9m114_res[idx].height;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mt9m114_res_काष्ठा *mt9m114_to_res(u32 w, u32 h)
अणु
	पूर्णांक  index;

	क्रम (index = 0; index < N_RES; index++) अणु
		अगर ((mt9m114_res[index].width == w) &&
		    (mt9m114_res[index].height == h))
			अवरोध;
	पूर्ण

	/* No mode found */
	अगर (index >= N_RES)
		वापस शून्य;

	वापस &mt9m114_res[index];
पूर्ण

अटल पूर्णांक mt9m114_res2size(काष्ठा v4l2_subdev *sd, पूर्णांक *h_size, पूर्णांक *v_size)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	अचिन्हित लघु hsize;
	अचिन्हित लघु vsize;

	चयन (dev->res) अणु
	हाल MT9M114_RES_736P:
		hsize = MT9M114_RES_736P_SIZE_H;
		vsize = MT9M114_RES_736P_SIZE_V;
		अवरोध;
	हाल MT9M114_RES_864P:
		hsize = MT9M114_RES_864P_SIZE_H;
		vsize = MT9M114_RES_864P_SIZE_V;
		अवरोध;
	हाल MT9M114_RES_960P:
		hsize = MT9M114_RES_960P_SIZE_H;
		vsize = MT9M114_RES_960P_SIZE_V;
		अवरोध;
	शेष:
		v4l2_err(sd, "%s: Resolution 0x%08x unknown\n", __func__,
			 dev->res);
		वापस -EINVAL;
	पूर्ण

	अगर (h_size)
		*h_size = hsize;
	अगर (v_size)
		*v_size = vsize;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_get_पूर्णांकg_factor(काष्ठा i2c_client *client,
				   काष्ठा camera_mipi_info *info,
				   स्थिर काष्ठा mt9m114_res_काष्ठा *res)
अणु
	काष्ठा atomisp_sensor_mode_data *buf = &info->data;
	u32 reg_val;
	पूर्णांक ret;

	अगर (!info)
		वापस -EINVAL;

	ret =  mt9m114_पढ़ो_reg(client, MISENSOR_32BIT,
				REG_PIXEL_CLK, &reg_val);
	अगर (ret)
		वापस ret;
	buf->vt_pix_clk_freq_mhz = reg_val;

	/* get पूर्णांकegration समय */
	buf->coarse_पूर्णांकegration_समय_min = MT9M114_COARSE_INTG_TIME_MIN;
	buf->coarse_पूर्णांकegration_समय_max_margin =
	    MT9M114_COARSE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_min = MT9M114_FINE_INTG_TIME_MIN;
	buf->fine_पूर्णांकegration_समय_max_margin =
	    MT9M114_FINE_INTG_TIME_MAX_MARGIN;

	buf->fine_पूर्णांकegration_समय_def = MT9M114_FINE_INTG_TIME_MIN;

	buf->frame_length_lines = res->lines_per_frame;
	buf->line_length_pck = res->pixels_per_line;
	buf->पढ़ो_mode = res->bin_mode;

	/* get the cropping and output resolution to ISP क्रम this mode. */
	ret =  mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
				REG_H_START, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_start = reg_val;

	ret =  mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
				REG_V_START, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_start = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_H_END, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_horizontal_end = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_V_END, &reg_val);
	अगर (ret)
		वापस ret;
	buf->crop_vertical_end = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_WIDTH, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_width = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_HEIGHT, &reg_val);
	अगर (ret)
		वापस ret;
	buf->output_height = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_TIMING_HTS, &reg_val);
	अगर (ret)
		वापस ret;
	buf->line_length_pck = reg_val;

	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_TIMING_VTS, &reg_val);
	अगर (ret)
		वापस ret;
	buf->frame_length_lines = reg_val;

	buf->binning_factor_x = res->bin_factor_x ?
				res->bin_factor_x : 1;
	buf->binning_factor_y = res->bin_factor_y ?
				res->bin_factor_y : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	पूर्णांक width, height;
	पूर्णांक ret;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	ret = mt9m114_res2size(sd, &width, &height);
	अगर (ret)
		वापस ret;
	fmt->width = width;
	fmt->height = height;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	काष्ठा mt9m114_res_काष्ठा *res_index;
	u32 width = fmt->width;
	u32 height = fmt->height;
	काष्ठा camera_mipi_info *mt9m114_info = शून्य;

	पूर्णांक ret;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	dev->streamon = 0;
	dev->first_exp = MT9M114_DEFAULT_FIRST_EXP;

	mt9m114_info = v4l2_get_subdev_hostdata(sd);
	अगर (!mt9m114_info)
		वापस -EINVAL;

	mt9m114_try_res(&width, &height);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *fmt;
		वापस 0;
	पूर्ण
	res_index = mt9m114_to_res(width, height);

	/* Sanity check */
	अगर (unlikely(!res_index)) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	चयन (res_index->res) अणु
	हाल MT9M114_RES_736P:
		ret = mt9m114_ग_लिखो_reg_array(c, mt9m114_736P_init, NO_POLLING);
		ret += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_R_MODE_MASK, MISENSOR_NORMAL_SET);
		अवरोध;
	हाल MT9M114_RES_864P:
		ret = mt9m114_ग_लिखो_reg_array(c, mt9m114_864P_init, NO_POLLING);
		ret += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_R_MODE_MASK, MISENSOR_NORMAL_SET);
		अवरोध;
	हाल MT9M114_RES_960P:
		ret = mt9m114_ग_लिखो_reg_array(c, mt9m114_976P_init, NO_POLLING);
		/* set sensor पढ़ो_mode to Normal */
		ret += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_R_MODE_MASK, MISENSOR_NORMAL_SET);
		अवरोध;
	शेष:
		v4l2_err(sd, "set resolution: %d failed!\n", res_index->res);
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस -EINVAL;

	ret = mt9m114_ग_लिखो_reg_array(c, mt9m114_chgstat_reg, POST_POLLING);
	अगर (ret < 0)
		वापस ret;

	अगर (mt9m114_set_suspend(sd))
		वापस -EINVAL;

	अगर (dev->res != res_index->res) अणु
		पूर्णांक index;

		/* Switch to dअगरferent size */
		अगर (width <= 640) अणु
			dev->nctx = 0x00; /* Set क्रम context A */
		पूर्ण अन्यथा अणु
			/*
			 * Context B is used क्रम resolutions larger than 640x480
			 * Using YUV क्रम Context B.
			 */
			dev->nctx = 0x01; /* set क्रम context B */
		पूर्ण

		/*
		 * Marked current sensor res as being "used"
		 *
		 * REVISIT: We करोn't need to use an "used" field on each mode
		 * list entry to know which mode is selected. If this
		 * inक्रमmation is really necessary, how about to use a single
		 * variable on sensor dev काष्ठा?
		 */
		क्रम (index = 0; index < N_RES; index++) अणु
			अगर ((width == mt9m114_res[index].width) &&
			    (height == mt9m114_res[index].height)) अणु
				mt9m114_res[index].used = true;
				जारी;
			पूर्ण
			mt9m114_res[index].used = false;
		पूर्ण
	पूर्ण
	ret = mt9m114_get_पूर्णांकg_factor(c, mt9m114_info,
				      &mt9m114_res[res_index->res]);
	अगर (ret) अणु
		dev_err(&c->dev, "failed to get integration_factor\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * mt9m114 - we करोn't poll क्रम context चयन
	 * because it करोes not happen with streaming disabled.
	 */
	dev->res = res_index->res;

	fmt->width = width;
	fmt->height = height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	वापस 0;
पूर्ण

/* TODO: Update to SOC functions, हटाओ exposure and gain */
अटल पूर्णांक mt9m114_g_focal(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (MT9M114_FOCAL_LENGTH_NUM << 16) | MT9M114_FOCAL_LENGTH_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_fnumber(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	/*स्थिर f number क्रम mt9m114*/
	*val = (MT9M114_F_NUMBER_DEFAULT_NUM << 16) | MT9M114_F_NUMBER_DEM;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_fnumber_range(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = (MT9M114_F_NUMBER_DEFAULT_NUM << 24) |
	       (MT9M114_F_NUMBER_DEM << 16) |
	       (MT9M114_F_NUMBER_DEFAULT_NUM << 8) | MT9M114_F_NUMBER_DEM;
	वापस 0;
पूर्ण

/* Horizontal flip the image. */
अटल पूर्णांक mt9m114_g_hflip(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u32 data;

	ret = mt9m114_पढ़ो_reg(c, MISENSOR_16BIT,
			       (u32)MISENSOR_READ_MODE, &data);
	अगर (ret)
		वापस ret;
	*val = !!(data & MISENSOR_HFLIP_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_vflip(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u32 data;

	ret = mt9m114_पढ़ो_reg(c, MISENSOR_16BIT,
			       (u32)MISENSOR_READ_MODE, &data);
	अगर (ret)
		वापस ret;
	*val = !!(data & MISENSOR_VFLIP_MASK);

	वापस 0;
पूर्ण

अटल दीर्घ mt9m114_s_exposure(काष्ठा v4l2_subdev *sd,
			       काष्ठा atomisp_exposure *exposure)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक coarse_पूर्णांकegration = 0;
	अचिन्हित पूर्णांक FLines = 0;
	अचिन्हित पूर्णांक FrameLengthLines = 0; /* ExposureTime.FrameLengthLines; */
	अचिन्हित पूर्णांक AnalogGain, DigitalGain;
	u32 AnalogGainToWrite = 0;

	dev_dbg(&client->dev, "%s(0x%X 0x%X 0x%X)\n", __func__,
		exposure->पूर्णांकegration_समय[0], exposure->gain[0],
		exposure->gain[1]);

	coarse_पूर्णांकegration = exposure->पूर्णांकegration_समय[0];
	/* fine_पूर्णांकegration = ExposureTime.FineIntegrationTime; */
	/* FrameLengthLines = ExposureTime.FrameLengthLines; */
	FLines = mt9m114_res[dev->res].lines_per_frame;
	AnalogGain = exposure->gain[0];
	DigitalGain = exposure->gain[1];
	अगर (!dev->streamon) अणु
		/*Save the first exposure values जबतक stream is off*/
		dev->first_exp = coarse_पूर्णांकegration;
		dev->first_gain = AnalogGain;
		dev->first_diggain = DigitalGain;
	पूर्ण
	/* DigitalGain = 0x400 * (((u16) DigitalGain) >> 8) +
	((अचिन्हित पूर्णांक)(0x400 * (((u16) DigitalGain) & 0xFF)) >>8); */

	/* set frame length */
	अगर (FLines < coarse_पूर्णांकegration + 6)
		FLines = coarse_पूर्णांकegration + 6;
	अगर (FLines < FrameLengthLines)
		FLines = FrameLengthLines;
	ret = mt9m114_ग_लिखो_reg(client, MISENSOR_16BIT, 0x300A, FLines);
	अगर (ret) अणु
		v4l2_err(client, "%s: fail to set FLines\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* set coarse पूर्णांकegration */
	/* 3A provide real exposure समय.
		should not translate to any value here. */
	ret = mt9m114_ग_लिखो_reg(client, MISENSOR_16BIT,
				REG_EXPO_COARSE, (u16)(coarse_पूर्णांकegration));
	अगर (ret) अणु
		v4l2_err(client, "%s: fail to set exposure time\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	// set analog/digital gain
	चयन(AnalogGain)
	अणु
	हाल 0:
	  AnalogGainToWrite = 0x0;
	  अवरोध;
	हाल 1:
	  AnalogGainToWrite = 0x20;
	  अवरोध;
	हाल 2:
	  AnalogGainToWrite = 0x60;
	  अवरोध;
	हाल 4:
	  AnalogGainToWrite = 0xA0;
	  अवरोध;
	हाल 8:
	  AnalogGainToWrite = 0xE0;
	  अवरोध;
	शेष:
	  AnalogGainToWrite = 0x20;
	  अवरोध;
	पूर्ण
	*/
	अगर (DigitalGain >= 16 || DigitalGain <= 1)
		DigitalGain = 1;
	/* AnalogGainToWrite =
		(u16)((DigitalGain << 12) | AnalogGainToWrite); */
	AnalogGainToWrite = (u16)((DigitalGain << 12) | (u16)AnalogGain);
	ret = mt9m114_ग_लिखो_reg(client, MISENSOR_16BIT,
				REG_GAIN, AnalogGainToWrite);
	अगर (ret) अणु
		v4l2_err(client, "%s: fail to set AnalogGainToWrite\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ mt9m114_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल ATOMISP_IOC_S_EXPOSURE:
		वापस mt9m114_s_exposure(sd, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This वापसs the exposure समय being used. This should only be used
   क्रम filling in EXIF data, not क्रम actual image processing. */
अटल पूर्णांक mt9m114_g_exposure(काष्ठा v4l2_subdev *sd, s32 *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u32 coarse;
	पूर्णांक ret;

	/* the fine पूर्णांकegration समय is currently not calculated */
	ret = mt9m114_पढ़ो_reg(client, MISENSOR_16BIT,
			       REG_EXPO_COARSE, &coarse);
	अगर (ret)
		वापस ret;

	*value = coarse;
	वापस 0;
पूर्ण

/*
 * This function will वापस the sensor supported max exposure zone number.
 * the sensor which supports max exposure zone number is 1.
 */
अटल पूर्णांक mt9m114_g_exposure_zone_num(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	*val = 1;

	वापस 0;
पूर्ण

/*
 * set exposure metering, average/center_weighted/spot/matrix.
 */
अटल पूर्णांक mt9m114_s_exposure_metering(काष्ठा v4l2_subdev *sd, s32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	चयन (val) अणु
	हाल V4L2_EXPOSURE_METERING_SPOT:
		ret = mt9m114_ग_लिखो_reg_array(client, mt9m114_exp_average,
					      NO_POLLING);
		अगर (ret) अणु
			dev_err(&client->dev, "write exp_average reg err.\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
	शेष:
		ret = mt9m114_ग_लिखो_reg_array(client, mt9m114_exp_center,
					      NO_POLLING);
		अगर (ret) अणु
			dev_err(&client->dev, "write exp_default reg err");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is क्रम touch exposure feature.
 */
अटल पूर्णांक mt9m114_s_exposure_selection(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_subdev_pad_config *cfg,
					काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा misensor_reg exp_reg;
	पूर्णांक width, height;
	पूर्णांक grid_width, grid_height;
	पूर्णांक grid_left, grid_top, grid_right, grid_bottom;
	पूर्णांक win_left, win_top, win_right, win_bottom;
	पूर्णांक i, j;
	पूर्णांक ret;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_TRY &&
	    sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	grid_left = sel->r.left;
	grid_top = sel->r.top;
	grid_right = sel->r.left + sel->r.width - 1;
	grid_bottom = sel->r.top + sel->r.height - 1;

	ret = mt9m114_res2size(sd, &width, &height);
	अगर (ret)
		वापस ret;

	grid_width = width / 5;
	grid_height = height / 5;

	अगर (grid_width && grid_height) अणु
		win_left = grid_left / grid_width;
		win_top = grid_top / grid_height;
		win_right = grid_right / grid_width;
		win_bottom = grid_bottom / grid_height;
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "Incorrect exp grid.\n");
		वापस -EINVAL;
	पूर्ण

	win_left   = clamp_t(पूर्णांक, win_left, 0, 4);
	win_top    = clamp_t(पूर्णांक, win_top, 0, 4);
	win_right  = clamp_t(पूर्णांक, win_right, 0, 4);
	win_bottom = clamp_t(पूर्णांक, win_bottom, 0, 4);

	ret = mt9m114_ग_लिखो_reg_array(client, mt9m114_exp_average, NO_POLLING);
	अगर (ret) अणु
		dev_err(&client->dev, "write exp_average reg err.\n");
		वापस ret;
	पूर्ण

	क्रम (i = win_top; i <= win_bottom; i++) अणु
		क्रम (j = win_left; j <= win_right; j++) अणु
			exp_reg = mt9m114_exp_win[i][j];

			ret = mt9m114_ग_लिखो_reg(client, exp_reg.length,
						exp_reg.reg, exp_reg.val);
			अगर (ret) अणु
				dev_err(&client->dev, "write exp_reg err.\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_bin_factor_x(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);

	*val = mt9m114_res[dev->res].bin_factor_x;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_bin_factor_y(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);

	*val = mt9m114_res[dev->res].bin_factor_y;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_s_ev(काष्ठा v4l2_subdev *sd, s32 val)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	s32 luma = 0x37;
	पूर्णांक err;

	/* EV value only support -2 to 2
	 * 0: 0x37, 1:0x47, 2:0x57, -1:0x27, -2:0x17
	 */
	अगर (val < -2 || val > 2)
		वापस -EINVAL;
	luma += 0x10 * val;
	dev_dbg(&c->dev, "%s val:%d luma:0x%x\n", __func__, val, luma);
	err = mt9m114_ग_लिखो_reg(c, MISENSOR_16BIT, 0x098E, 0xC87A);
	अगर (err) अणु
		dev_err(&c->dev, "%s logic addr access error\n", __func__);
		वापस err;
	पूर्ण
	err = mt9m114_ग_लिखो_reg(c, MISENSOR_8BIT, 0xC87A, (u32)luma);
	अगर (err) अणु
		dev_err(&c->dev, "%s write target_average_luma failed\n",
			__func__);
		वापस err;
	पूर्ण
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_ev(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक err;
	u32 luma;

	err = mt9m114_ग_लिखो_reg(c, MISENSOR_16BIT, 0x098E, 0xC87A);
	अगर (err) अणु
		dev_err(&c->dev, "%s logic addr access error\n", __func__);
		वापस err;
	पूर्ण
	err = mt9m114_पढ़ो_reg(c, MISENSOR_8BIT, 0xC87A, &luma);
	अगर (err) अणु
		dev_err(&c->dev, "%s read target_average_luma failed\n",
			__func__);
		वापस err;
	पूर्ण
	luma -= 0x17;
	luma /= 0x10;
	*val = (s32)luma - 2;
	dev_dbg(&c->dev, "%s val:%d\n", __func__, *val);

	वापस 0;
पूर्ण

/* Fake पूर्णांकerface
 * mt9m114 now can not support 3a_lock
*/
अटल पूर्णांक mt9m114_s_3a_lock(काष्ठा v4l2_subdev *sd, s32 val)
अणु
	aaalock = val;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_3a_lock(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	अगर (aaalock)
		वापस V4L2_LOCK_EXPOSURE | V4L2_LOCK_WHITE_BALANCE
		       | V4L2_LOCK_FOCUS;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m114_device *dev =
	    container_of(ctrl->handler, काष्ठा mt9m114_device, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		dev_dbg(&client->dev, "%s: CID_VFLIP:%d.\n",
			__func__, ctrl->val);
		ret = mt9m114_t_vflip(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		dev_dbg(&client->dev, "%s: CID_HFLIP:%d.\n",
			__func__, ctrl->val);
		ret = mt9m114_t_hflip(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_METERING:
		ret = mt9m114_s_exposure_metering(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = mt9m114_s_ev(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_3A_LOCK:
		ret = mt9m114_s_3a_lock(&dev->sd, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m114_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m114_device *dev =
	    container_of(ctrl->handler, काष्ठा mt9m114_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		ret = mt9m114_g_vflip(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		ret = mt9m114_g_hflip(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FOCAL_ABSOLUTE:
		ret = mt9m114_g_focal(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_ABSOLUTE:
		ret = mt9m114_g_fnumber(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FNUMBER_RANGE:
		ret = mt9m114_g_fnumber_range(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		ret = mt9m114_g_exposure(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_ZONE_NUM:
		ret = mt9m114_g_exposure_zone_num(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_HORZ:
		ret = mt9m114_g_bin_factor_x(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_BIN_FACTOR_VERT:
		ret = mt9m114_g_bin_factor_y(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = mt9m114_g_ev(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_3A_LOCK:
		ret = mt9m114_g_3a_lock(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = mt9m114_s_ctrl,
	.g_अस्थिर_ctrl = mt9m114_g_अस्थिर_ctrl
पूर्ण;

अटल काष्ठा v4l2_ctrl_config mt9m114_controls[] = अणु
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_VFLIP,
		.name = "Image v-Flip",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_HFLIP,
		.name = "Image h-Flip",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FOCAL_ABSOLUTE,
		.name = "focal length",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = MT9M114_FOCAL_LENGTH_DEFAULT,
		.max = MT9M114_FOCAL_LENGTH_DEFAULT,
		.step = 1,
		.def = MT9M114_FOCAL_LENGTH_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_ABSOLUTE,
		.name = "f-number",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = MT9M114_F_NUMBER_DEFAULT,
		.max = MT9M114_F_NUMBER_DEFAULT,
		.step = 1,
		.def = MT9M114_F_NUMBER_DEFAULT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FNUMBER_RANGE,
		.name = "f-number range",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = MT9M114_F_NUMBER_RANGE,
		.max = MT9M114_F_NUMBER_RANGE,
		.step = 1,
		.def = MT9M114_F_NUMBER_RANGE,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_EXPOSURE_ABSOLUTE,
		.name = "exposure",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 0xffff,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_EXPOSURE_ZONE_NUM,
		.name = "one-time exposure zone number",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 0xffff,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_EXPOSURE_METERING,
		.name = "metering",
		.type = V4L2_CTRL_TYPE_MENU,
		.min = 0,
		.max = 3,
		.step = 0,
		.def = 1,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_HORZ,
		.name = "horizontal binning factor",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = MT9M114_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_BIN_FACTOR_VERT,
		.name = "vertical binning factor",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = MT9M114_BIN_FACTOR_MAX,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_EXPOSURE,
		.name = "exposure biasx",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = -2,
		.max = 2,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_3A_LOCK,
		.name = "3a lock",
		.type = V4L2_CTRL_TYPE_BITMASK,
		.min = 0,
		.max = V4L2_LOCK_EXPOSURE | V4L2_LOCK_WHITE_BALANCE | V4L2_LOCK_FOCUS,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mt9m114_detect(काष्ठा mt9m114_device *dev, काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u32 retvalue;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "%s: i2c error", __func__);
		वापस -ENODEV;
	पूर्ण
	mt9m114_पढ़ो_reg(client, MISENSOR_16BIT, (u32)MT9M114_PID, &retvalue);
	dev->real_model_id = retvalue;

	अगर (retvalue != MT9M114_MOD_ID) अणु
		dev_err(&client->dev, "%s: failed: client->addr = %x\n",
			__func__, client->addr);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt9m114_s_config(काष्ठा v4l2_subdev *sd, पूर्णांक irq, व्योम *platक्रमm_data)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (!platक्रमm_data)
		वापस -ENODEV;

	dev->platक्रमm_data =
	    (काष्ठा camera_sensor_platक्रमm_data *)platक्रमm_data;

	ret = घातer_up(sd);
	अगर (ret) अणु
		v4l2_err(client, "mt9m114 power-up err");
		वापस ret;
	पूर्ण

	/* config & detect sensor */
	ret = mt9m114_detect(dev, client);
	अगर (ret) अणु
		v4l2_err(client, "mt9m114_detect err s_config.\n");
		जाओ fail_detect;
	पूर्ण

	ret = dev->platक्रमm_data->csi_cfg(sd, 1);
	अगर (ret)
		जाओ fail_csi_cfg;

	ret = mt9m114_set_suspend(sd);
	अगर (ret) अणु
		v4l2_err(client, "mt9m114 suspend err");
		वापस ret;
	पूर्ण

	ret = घातer_करोwn(sd);
	अगर (ret) अणु
		v4l2_err(client, "mt9m114 power down err");
		वापस ret;
	पूर्ण

	वापस ret;

fail_csi_cfg:
	dev->platक्रमm_data->csi_cfg(sd, 0);
fail_detect:
	घातer_करोwn(sd);
	dev_err(&client->dev, "sensor power-gating failed\n");
	वापस ret;
पूर्ण

/* Horizontal flip the image. */
अटल पूर्णांक mt9m114_t_hflip(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	पूर्णांक err;
	/* set क्रम direct mode */
	err = mt9m114_ग_लिखो_reg(c, MISENSOR_16BIT, 0x098E, 0xC850);
	अगर (value) अणु
		/* enable H flip ctx A */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC850, 0x01, 0x01);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC851, 0x01, 0x01);
		/* ctx B */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC888, 0x01, 0x01);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC889, 0x01, 0x01);

		err += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_HFLIP_MASK, MISENSOR_FLIP_EN);

		dev->bpat = MT9M114_BPAT_GRGRBGBG;
	पूर्ण अन्यथा अणु
		/* disable H flip ctx A */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC850, 0x01, 0x00);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC851, 0x01, 0x00);
		/* ctx B */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC888, 0x01, 0x00);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC889, 0x01, 0x00);

		err += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_HFLIP_MASK, MISENSOR_FLIP_DIS);

		dev->bpat = MT9M114_BPAT_BGBGGRGR;
	पूर्ण

	err += mt9m114_ग_लिखो_reg(c, MISENSOR_8BIT, 0x8404, 0x06);
	udelay(10);

	वापस !!err;
पूर्ण

/* Vertically flip the image */
अटल पूर्णांक mt9m114_t_vflip(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक err;
	/* set क्रम direct mode */
	err = mt9m114_ग_लिखो_reg(c, MISENSOR_16BIT, 0x098E, 0xC850);
	अगर (value >= 1) अणु
		/* enable H flip - ctx A */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC850, 0x02, 0x01);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC851, 0x02, 0x01);
		/* ctx B */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC888, 0x02, 0x01);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC889, 0x02, 0x01);

		err += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_VFLIP_MASK, MISENSOR_FLIP_EN);
	पूर्ण अन्यथा अणु
		/* disable H flip - ctx A */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC850, 0x02, 0x00);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC851, 0x02, 0x00);
		/* ctx B */
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC888, 0x02, 0x00);
		err += misensor_rmw_reg(c, MISENSOR_8BIT, 0xC889, 0x02, 0x00);

		err += misensor_rmw_reg(c, MISENSOR_16BIT, MISENSOR_READ_MODE,
					MISENSOR_VFLIP_MASK, MISENSOR_FLIP_DIS);
	पूर्ण

	err += mt9m114_ग_लिखो_reg(c, MISENSOR_8BIT, 0x8404, 0x06);
	udelay(10);

	वापस !!err;
पूर्ण

अटल पूर्णांक mt9m114_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);

	पूर्णांकerval->पूर्णांकerval.numerator = 1;
	पूर्णांकerval->पूर्णांकerval.denominator = mt9m114_res[dev->res].fps;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	काष्ठा mt9m114_device *dev = to_mt9m114_sensor(sd);
	काष्ठा atomisp_exposure exposure;

	अगर (enable) अणु
		ret = mt9m114_ग_लिखो_reg_array(c, mt9m114_chgstat_reg,
					      POST_POLLING);
		अगर (ret < 0)
			वापस ret;

		अगर (dev->first_exp > MT9M114_MAX_FIRST_EXP) अणु
			exposure.पूर्णांकegration_समय[0] = dev->first_exp;
			exposure.gain[0] = dev->first_gain;
			exposure.gain[1] = dev->first_diggain;
			mt9m114_s_exposure(sd, &exposure);
		पूर्ण
		dev->streamon = 1;

	पूर्ण अन्यथा अणु
		dev->streamon = 0;
		ret = mt9m114_set_suspend(sd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m114_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index)
		वापस -EINVAL;
	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अचिन्हित पूर्णांक index = fse->index;

	अगर (index >= N_RES)
		वापस -EINVAL;

	fse->min_width = mt9m114_res[index].width;
	fse->min_height = mt9m114_res[index].height;
	fse->max_width = mt9m114_res[index].width;
	fse->max_height = mt9m114_res[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_g_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	पूर्णांक index;
	काष्ठा mt9m114_device *snr = to_mt9m114_sensor(sd);

	अगर (!frames)
		वापस -EINVAL;

	क्रम (index = 0; index < N_RES; index++) अणु
		अगर (mt9m114_res[index].res == snr->res)
			अवरोध;
	पूर्ण

	अगर (index >= N_RES)
		वापस -EINVAL;

	*frames = mt9m114_res[index].skip_frames;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9m114_video_ops = अणु
	.s_stream = mt9m114_s_stream,
	.g_frame_पूर्णांकerval = mt9m114_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops mt9m114_sensor_ops = अणु
	.g_skip_frames	= mt9m114_g_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9m114_core_ops = अणु
	.s_घातer = mt9m114_s_घातer,
	.ioctl = mt9m114_ioctl,
पूर्ण;

/* REVISIT: Do we need pad operations? */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9m114_pad_ops = अणु
	.क्रमागत_mbus_code = mt9m114_क्रमागत_mbus_code,
	.क्रमागत_frame_size = mt9m114_क्रमागत_frame_size,
	.get_fmt = mt9m114_get_fmt,
	.set_fmt = mt9m114_set_fmt,
	.set_selection = mt9m114_s_exposure_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9m114_ops = अणु
	.core = &mt9m114_core_ops,
	.video = &mt9m114_video_ops,
	.pad = &mt9m114_pad_ops,
	.sensor = &mt9m114_sensor_ops,
पूर्ण;

अटल पूर्णांक mt9m114_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m114_device *dev;
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	dev = container_of(sd, काष्ठा mt9m114_device, sd);
	dev->platक्रमm_data->csi_cfg(sd, 0);
	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&dev->sd.entity);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m114_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m114_device *dev;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	व्योम *pdata;

	/* Setup sensor configuration काष्ठाure */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&dev->sd, client, &mt9m114_ops);
	pdata = gmin_camera_platक्रमm_data(&dev->sd,
					  ATOMISP_INPUT_FORMAT_RAW_10,
					  atomisp_bayer_order_grbg);
	अगर (pdata)
		ret = mt9m114_s_config(&dev->sd, client->irq, pdata);
	अगर (!pdata || ret) अणु
		v4l2_device_unरेजिस्टर_subdev(&dev->sd);
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	ret = atomisp_रेजिस्टर_i2c_module(&dev->sd, pdata, RAW_CAMERA);
	अगर (ret) अणु
		v4l2_device_unरेजिस्टर_subdev(&dev->sd);
		kमुक्त(dev);
		/* Coverity CID 298095 - वापस on error */
		वापस ret;
	पूर्ण

	/*TODO add क्रमmat code here*/
	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret =
	    v4l2_ctrl_handler_init(&dev->ctrl_handler,
				   ARRAY_SIZE(mt9m114_controls));
	अगर (ret) अणु
		mt9m114_हटाओ(client);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt9m114_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &mt9m114_controls[i],
				     शून्य);

	अगर (dev->ctrl_handler.error) अणु
		mt9m114_हटाओ(client);
		वापस dev->ctrl_handler.error;
	पूर्ण

	/* Use same lock क्रम controls as क्रम everything अन्यथा. */
	dev->ctrl_handler.lock = &dev->input_lock;
	dev->sd.ctrl_handler = &dev->ctrl_handler;

	/* REVISIT: Do we need media controller? */
	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret) अणु
		mt9m114_हटाओ(client);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mt9m114_acpi_match[] = अणु
	अणु "INT33F0" पूर्ण,
	अणु "CRMT1040" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mt9m114_acpi_match);

अटल काष्ठा i2c_driver mt9m114_driver = अणु
	.driver = अणु
		.name = "mt9m114",
		.acpi_match_table = mt9m114_acpi_match,
	पूर्ण,
	.probe_new = mt9m114_probe,
	.हटाओ = mt9m114_हटाओ,
पूर्ण;
module_i2c_driver(mt9m114_driver);

MODULE_AUTHOR("Shuguang Gong <Shuguang.gong@intel.com>");
MODULE_LICENSE("GPL");
