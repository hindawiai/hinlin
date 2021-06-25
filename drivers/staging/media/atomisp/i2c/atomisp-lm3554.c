<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LED flash driver क्रम LM3554
 *
 * Copyright (c) 2010-2012 Intel Corporation. All Rights Reserved.
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
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>

#समावेश "../include/media/lm3554.h"
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/acpi.h>
#समावेश "../include/linux/atomisp_gmin_platform.h"
#समावेश "../include/linux/atomisp.h"

/* Registers */

#घोषणा LM3554_TORCH_BRIGHTNESS_REG	0xA0
#घोषणा LM3554_TORCH_MODE_SHIFT		0
#घोषणा LM3554_TORCH_CURRENT_SHIFT	3
#घोषणा LM3554_INDICATOR_CURRENT_SHIFT	6

#घोषणा LM3554_FLASH_BRIGHTNESS_REG	0xB0
#घोषणा LM3554_FLASH_MODE_SHIFT		0
#घोषणा LM3554_FLASH_CURRENT_SHIFT	3
#घोषणा LM3554_STROBE_SENSITIVITY_SHIFT	7

#घोषणा LM3554_FLASH_DURATION_REG	0xC0
#घोषणा LM3554_FLASH_TIMEOUT_SHIFT	0
#घोषणा LM3554_CURRENT_LIMIT_SHIFT	5

#घोषणा LM3554_FLAGS_REG		0xD0
#घोषणा LM3554_FLAG_TIMEOUT		BIT(0)
#घोषणा LM3554_FLAG_THERMAL_SHUTDOWN	BIT(1)
#घोषणा LM3554_FLAG_LED_FAULT		BIT(2)
#घोषणा LM3554_FLAG_TX1_INTERRUPT	BIT(3)
#घोषणा LM3554_FLAG_TX2_INTERRUPT	BIT(4)
#घोषणा LM3554_FLAG_LED_THERMAL_FAULT	BIT(5)
#घोषणा LM3554_FLAG_UNUSED		BIT(6)
#घोषणा LM3554_FLAG_INPUT_VOLTAGE_LOW	BIT(7)

#घोषणा LM3554_CONFIG_REG_1		0xE0
#घोषणा LM3554_ENVM_TX2_SHIFT		5
#घोषणा LM3554_TX2_POLARITY_SHIFT	6

काष्ठा lm3554 अणु
	काष्ठा v4l2_subdev sd;

	काष्ठा mutex घातer_lock;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक घातer_count;

	अचिन्हित पूर्णांक mode;
	पूर्णांक समयout;
	u8 torch_current;
	u8 indicator_current;
	u8 flash_current;

	काष्ठा समयr_list flash_off_delay;
	काष्ठा lm3554_platक्रमm_data *pdata;
पूर्ण;

#घोषणा to_lm3554(p_sd)	container_of(p_sd, काष्ठा lm3554, sd)

/* Return negative त्रुटि_सं अन्यथा zero on success */
अटल पूर्णांक lm3554_ग_लिखो(काष्ठा lm3554 *flash, u8 addr, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->sd);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, addr, val);

	dev_dbg(&client->dev, "Write Addr:%02X Val:%02X %s\n", addr, val,
		ret < 0 ? "fail" : "ok");

	वापस ret;
पूर्ण

/* Return negative त्रुटि_सं अन्यथा a data byte received from the device. */
अटल पूर्णांक lm3554_पढ़ो(काष्ठा lm3554 *flash, u8 addr)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->sd);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, addr);

	dev_dbg(&client->dev, "Read Addr:%02X Val:%02X %s\n", addr, ret,
		ret < 0 ? "fail" : "ok");

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware configuration
 */

अटल पूर्णांक lm3554_set_mode(काष्ठा lm3554 *flash, अचिन्हित पूर्णांक mode)
अणु
	u8 val;
	पूर्णांक ret;

	val = (mode << LM3554_FLASH_MODE_SHIFT) |
	      (flash->flash_current << LM3554_FLASH_CURRENT_SHIFT);

	ret = lm3554_ग_लिखो(flash, LM3554_FLASH_BRIGHTNESS_REG, val);
	अगर (ret == 0)
		flash->mode = mode;
	वापस ret;
पूर्ण

अटल पूर्णांक lm3554_set_torch(काष्ठा lm3554 *flash)
अणु
	u8 val;

	val = (flash->mode << LM3554_TORCH_MODE_SHIFT) |
	      (flash->torch_current << LM3554_TORCH_CURRENT_SHIFT) |
	      (flash->indicator_current << LM3554_INDICATOR_CURRENT_SHIFT);

	वापस lm3554_ग_लिखो(flash, LM3554_TORCH_BRIGHTNESS_REG, val);
पूर्ण

अटल पूर्णांक lm3554_set_flash(काष्ठा lm3554 *flash)
अणु
	u8 val;

	val = (flash->mode << LM3554_FLASH_MODE_SHIFT) |
	      (flash->flash_current << LM3554_FLASH_CURRENT_SHIFT);

	वापस lm3554_ग_लिखो(flash, LM3554_FLASH_BRIGHTNESS_REG, val);
पूर्ण

अटल पूर्णांक lm3554_set_duration(काष्ठा lm3554 *flash)
अणु
	u8 val;

	val = (flash->समयout << LM3554_FLASH_TIMEOUT_SHIFT) |
	      (flash->pdata->current_limit << LM3554_CURRENT_LIMIT_SHIFT);

	वापस lm3554_ग_लिखो(flash, LM3554_FLASH_DURATION_REG, val);
पूर्ण

अटल पूर्णांक lm3554_set_config1(काष्ठा lm3554 *flash)
अणु
	u8 val;

	val = (flash->pdata->envm_tx2 << LM3554_ENVM_TX2_SHIFT) |
	      (flash->pdata->tx2_polarity << LM3554_TX2_POLARITY_SHIFT);
	वापस lm3554_ग_लिखो(flash, LM3554_CONFIG_REG_1, val);
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware trigger
 */
अटल व्योम lm3554_flash_off_delay(काष्ठा समयr_list *t)
अणु
	काष्ठा lm3554 *flash = from_समयr(flash, t, flash_off_delay);
	काष्ठा lm3554_platक्रमm_data *pdata = flash->pdata;

	gpiod_set_value(pdata->gpio_strobe, 0);
पूर्ण

अटल पूर्णांक lm3554_hw_strobe(काष्ठा i2c_client *client, bool strobe)
अणु
	पूर्णांक ret, समयr_pending;
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(sd);
	काष्ठा lm3554_platक्रमm_data *pdata = flash->pdata;

	/*
	 * An abnormal high flash current is observed when strobe off the
	 * flash. Workaround here is firstly set flash current to lower level,
	 * रुको a लघु moment, and then strobe off the flash.
	 */

	समयr_pending = del_समयr_sync(&flash->flash_off_delay);

	/* Flash off */
	अगर (!strobe) अणु
		/* set current to 70mA and रुको a जबतक */
		ret = lm3554_ग_लिखो(flash, LM3554_FLASH_BRIGHTNESS_REG, 0);
		अगर (ret < 0)
			जाओ err;
		mod_समयr(&flash->flash_off_delay,
			  jअगरfies + msecs_to_jअगरfies(LM3554_TIMER_DELAY));
		वापस 0;
	पूर्ण

	/* Flash on */

	/*
	 * If समयr is समाप्तed beक्रमe run, flash is not strobe off,
	 * so must strobe off here
	 */
	अगर (समयr_pending)
		gpiod_set_value(pdata->gpio_strobe, 0);

	/* Restore flash current settings */
	ret = lm3554_set_flash(flash);
	अगर (ret < 0)
		जाओ err;

	/* Strobe on Flash */
	gpiod_set_value(pdata->gpio_strobe, 1);

	वापस 0;
err:
	dev_err(&client->dev, "failed to %s flash strobe (%d)\n",
		strobe ? "on" : "off", ret);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 controls
 */

अटल पूर्णांक lm3554_पढ़ो_status(काष्ठा lm3554 *flash)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->sd);

	/* NOTE: पढ़ोing रेजिस्टर clear fault status */
	ret = lm3554_पढ़ो(flash, LM3554_FLAGS_REG);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Accordingly to datasheet we पढ़ो back '1' in bit 6.
	 * Clear it first.
	 */
	ret &= ~LM3554_FLAG_UNUSED;

	/*
	 * Do not take TX1/TX2 संकेत as an error
	 * because MSIC will not turn off flash, but turn to
	 * torch mode according to gsm modem संकेत by hardware.
	 */
	ret &= ~(LM3554_FLAG_TX1_INTERRUPT | LM3554_FLAG_TX2_INTERRUPT);

	अगर (ret > 0)
		dev_dbg(&client->dev, "LM3554 flag status: %02x\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3554_s_flash_समयout(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	val = clamp(val, LM3554_MIN_TIMEOUT, LM3554_MAX_TIMEOUT);
	val = val / LM3554_TIMEOUT_STEPSIZE - 1;

	flash->समयout = val;

	वापस lm3554_set_duration(flash);
पूर्ण

अटल पूर्णांक lm3554_g_flash_समयout(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	*val = (u32)(flash->समयout + 1) * LM3554_TIMEOUT_STEPSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_flash_पूर्णांकensity(काष्ठा v4l2_subdev *sd, u32 पूर्णांकensity)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	पूर्णांकensity = LM3554_CLAMP_PERCENTAGE(पूर्णांकensity);
	पूर्णांकensity = LM3554_PERCENT_TO_VALUE(पूर्णांकensity, LM3554_FLASH_STEP);

	flash->flash_current = पूर्णांकensity;

	वापस lm3554_set_flash(flash);
पूर्ण

अटल पूर्णांक lm3554_g_flash_पूर्णांकensity(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	*val = LM3554_VALUE_TO_PERCENT((u32)flash->flash_current,
				       LM3554_FLASH_STEP);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_torch_पूर्णांकensity(काष्ठा v4l2_subdev *sd, u32 पूर्णांकensity)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	पूर्णांकensity = LM3554_CLAMP_PERCENTAGE(पूर्णांकensity);
	पूर्णांकensity = LM3554_PERCENT_TO_VALUE(पूर्णांकensity, LM3554_TORCH_STEP);

	flash->torch_current = पूर्णांकensity;

	वापस lm3554_set_torch(flash);
पूर्ण

अटल पूर्णांक lm3554_g_torch_पूर्णांकensity(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	*val = LM3554_VALUE_TO_PERCENT((u32)flash->torch_current,
				       LM3554_TORCH_STEP);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_indicator_पूर्णांकensity(काष्ठा v4l2_subdev *sd, u32 पूर्णांकensity)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	पूर्णांकensity = LM3554_CLAMP_PERCENTAGE(पूर्णांकensity);
	पूर्णांकensity = LM3554_PERCENT_TO_VALUE(पूर्णांकensity, LM3554_INDICATOR_STEP);

	flash->indicator_current = पूर्णांकensity;

	वापस lm3554_set_torch(flash);
पूर्ण

अटल पूर्णांक lm3554_g_indicator_पूर्णांकensity(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);

	*val = LM3554_VALUE_TO_PERCENT((u32)flash->indicator_current,
				       LM3554_INDICATOR_STEP);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_flash_strobe(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस lm3554_hw_strobe(client, val);
पूर्ण

अटल पूर्णांक lm3554_s_flash_mode(काष्ठा v4l2_subdev *sd, u32 new_mode)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);
	अचिन्हित पूर्णांक mode;

	चयन (new_mode) अणु
	हाल ATOMISP_FLASH_MODE_OFF:
		mode = LM3554_MODE_SHUTDOWN;
		अवरोध;
	हाल ATOMISP_FLASH_MODE_FLASH:
		mode = LM3554_MODE_FLASH;
		अवरोध;
	हाल ATOMISP_FLASH_MODE_INDICATOR:
		mode = LM3554_MODE_INDICATOR;
		अवरोध;
	हाल ATOMISP_FLASH_MODE_TORCH:
		mode = LM3554_MODE_TORCH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस lm3554_set_mode(flash, mode);
पूर्ण

अटल पूर्णांक lm3554_g_flash_mode(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);
	*val = flash->mode;
	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_g_flash_status(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);
	पूर्णांक value;

	value = lm3554_पढ़ो_status(flash);
	अगर (value < 0)
		वापस value;

	अगर (value & LM3554_FLAG_TIMEOUT)
		*val = ATOMISP_FLASH_STATUS_TIMEOUT;
	अन्यथा अगर (value > 0)
		*val = ATOMISP_FLASH_STATUS_HW_ERROR;
	अन्यथा
		*val = ATOMISP_FLASH_STATUS_OK;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_g_flash_status_रेजिस्टर(काष्ठा v4l2_subdev *sd, s32 *val)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);
	पूर्णांक ret;

	ret = lm3554_पढ़ो(flash, LM3554_FLAGS_REG);

	अगर (ret < 0)
		वापस ret;

	*val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा lm3554 *dev =
	    container_of(ctrl->handler, काष्ठा lm3554, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FLASH_TIMEOUT:
		ret = lm3554_s_flash_समयout(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_INTENSITY:
		ret = lm3554_s_flash_पूर्णांकensity(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		ret = lm3554_s_torch_पूर्णांकensity(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		ret = lm3554_s_indicator_पूर्णांकensity(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_STROBE:
		ret = lm3554_s_flash_strobe(&dev->sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_MODE:
		ret = lm3554_s_flash_mode(&dev->sd, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lm3554_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा lm3554 *dev =
	    container_of(ctrl->handler, काष्ठा lm3554, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FLASH_TIMEOUT:
		ret = lm3554_g_flash_समयout(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_INTENSITY:
		ret = lm3554_g_flash_पूर्णांकensity(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_TORCH_INTENSITY:
		ret = lm3554_g_torch_पूर्णांकensity(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_INDICATOR_INTENSITY:
		ret = lm3554_g_indicator_पूर्णांकensity(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_MODE:
		ret = lm3554_g_flash_mode(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_STATUS:
		ret = lm3554_g_flash_status(&dev->sd, &ctrl->val);
		अवरोध;
	हाल V4L2_CID_FLASH_STATUS_REGISTER:
		ret = lm3554_g_flash_status_रेजिस्टर(&dev->sd, &ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = lm3554_s_ctrl,
	.g_अस्थिर_ctrl = lm3554_g_अस्थिर_ctrl
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config lm3554_controls[] = अणु
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_TIMEOUT,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Flash Timeout",
		.min = 0x0,
		.max = LM3554_MAX_TIMEOUT,
		.step = 0x01,
		.def = LM3554_DEFAULT_TIMEOUT,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_INTENSITY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Flash Intensity",
		.min = LM3554_MIN_PERCENT,
		.max = LM3554_MAX_PERCENT,
		.step = 0x01,
		.def = LM3554_FLASH_DEFAULT_BRIGHTNESS,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_TORCH_INTENSITY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Torch Intensity",
		.min = LM3554_MIN_PERCENT,
		.max = LM3554_MAX_PERCENT,
		.step = 0x01,
		.def = LM3554_TORCH_DEFAULT_BRIGHTNESS,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_INDICATOR_INTENSITY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Indicator Intensity",
		.min = LM3554_MIN_PERCENT,
		.max = LM3554_MAX_PERCENT,
		.step = 0x01,
		.def = LM3554_INDICATOR_DEFAULT_BRIGHTNESS,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_STROBE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Flash Strobe",
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_MODE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Flash Mode",
		.min = 0,
		.max = 100,
		.step = 1,
		.def = ATOMISP_FLASH_MODE_OFF,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_STATUS,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Flash Status",
		.min = ATOMISP_FLASH_STATUS_OK,
		.max = ATOMISP_FLASH_STATUS_TIMEOUT,
		.step = 1,
		.def = ATOMISP_FLASH_STATUS_OK,
		.flags = 0,
	पूर्ण,
	अणु
		.ops = &ctrl_ops,
		.id = V4L2_CID_FLASH_STATUS_REGISTER,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Flash Status Register",
		.min = 0,
		.max = 255,
		.step = 1,
		.def = 0,
		.flags = 0,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

/* Put device पूर्णांकo known state. */
अटल पूर्णांक lm3554_setup(काष्ठा lm3554 *flash)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&flash->sd);
	पूर्णांक ret;

	/* clear the flags रेजिस्टर */
	ret = lm3554_पढ़ो(flash, LM3554_FLAGS_REG);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&client->dev, "Fault info: %02x\n", ret);

	ret = lm3554_set_config1(flash);
	अगर (ret < 0)
		वापस ret;

	ret = lm3554_set_duration(flash);
	अगर (ret < 0)
		वापस ret;

	ret = lm3554_set_torch(flash);
	अगर (ret < 0)
		वापस ret;

	ret = lm3554_set_flash(flash);
	अगर (ret < 0)
		वापस ret;

	/* पढ़ो status */
	ret = lm3554_पढ़ो_status(flash);
	अगर (ret < 0)
		वापस ret;

	वापस ret ? -EIO : 0;
पूर्ण

अटल पूर्णांक __lm3554_s_घातer(काष्ठा lm3554 *flash, पूर्णांक घातer)
अणु
	काष्ठा lm3554_platक्रमm_data *pdata = flash->pdata;
	पूर्णांक ret;

	/*initialize flash driver*/
	gpiod_set_value(pdata->gpio_reset, घातer);
	usleep_range(100, 100 + 1);

	अगर (घातer) अणु
		/* Setup शेष values. This makes sure that the chip
		 * is in a known state.
		 */
		ret = lm3554_setup(flash);
		अगर (ret < 0) अणु
			__lm3554_s_घातer(flash, 0);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3554_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक घातer)
अणु
	काष्ठा lm3554 *flash = to_lm3554(sd);
	पूर्णांक ret = 0;

	mutex_lock(&flash->घातer_lock);

	अगर (flash->घातer_count == !घातer) अणु
		ret = __lm3554_s_घातer(flash, !!घातer);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	flash->घातer_count += घातer ? 1 : -1;
	WARN_ON(flash->घातer_count < 0);

करोne:
	mutex_unlock(&flash->घातer_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops lm3554_core_ops = अणु
	.s_घातer = lm3554_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops lm3554_ops = अणु
	.core = &lm3554_core_ops,
पूर्ण;

अटल पूर्णांक lm3554_detect(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा lm3554 *flash = to_lm3554(sd);
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "lm3554_detect i2c error\n");
		वापस -ENODEV;
	पूर्ण

	/* Power up the flash driver and reset it */
	ret = lm3554_s_घातer(&flash->sd, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to power on lm3554 LED flash\n");
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "Successfully detected lm3554 LED flash\n");
		lm3554_s_घातer(&flash->sd, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lm3554_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस lm3554_s_घातer(sd, 1);
पूर्ण

अटल पूर्णांक lm3554_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस lm3554_s_घातer(sd, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops lm3554_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = lm3554_detect,
	.खोलो = lm3554_खोलो,
	.बंद = lm3554_बंद,
पूर्ण;

/* -----------------------------------------------------------------------------
 *  I2C driver
 */
#अगर_घोषित CONFIG_PM

अटल पूर्णांक lm3554_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(subdev);
	पूर्णांक rval;

	अगर (flash->घातer_count == 0)
		वापस 0;

	rval = __lm3554_s_घातer(flash, 0);

	dev_dbg(&client->dev, "Suspend %s\n", rval < 0 ? "failed" : "ok");

	वापस rval;
पूर्ण

अटल पूर्णांक lm3554_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(subdev);
	पूर्णांक rval;

	अगर (flash->घातer_count == 0)
		वापस 0;

	rval = __lm3554_s_घातer(flash, 1);

	dev_dbg(&client->dev, "Resume %s\n", rval < 0 ? "fail" : "ok");

	वापस rval;
पूर्ण

#अन्यथा

#घोषणा lm3554_suspend शून्य
#घोषणा lm3554_resume  शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक lm3554_gpio_init(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(sd);
	काष्ठा lm3554_platक्रमm_data *pdata = flash->pdata;
	पूर्णांक ret;

	अगर (!pdata->gpio_reset)
		वापस -EINVAL;

	ret = gpiod_direction_output(pdata->gpio_reset, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (!pdata->gpio_strobe)
		वापस -EINVAL;

	ret = gpiod_direction_output(pdata->gpio_strobe, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम lm3554_gpio_uninit(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(sd);
	काष्ठा lm3554_platक्रमm_data *pdata = flash->pdata;
	पूर्णांक ret;

	ret = gpiod_direction_output(pdata->gpio_strobe, 0);
	अगर (ret < 0)
		dev_err(&client->dev,
			"gpio request/direction_output fail for gpio_strobe");

	ret = gpiod_direction_output(pdata->gpio_reset, 0);
	अगर (ret < 0)
		dev_err(&client->dev,
			"gpio request/direction_output fail for gpio_reset");
पूर्ण

अटल व्योम *lm3554_platक्रमm_data_func(काष्ठा i2c_client *client)
अणु
	अटल काष्ठा lm3554_platक्रमm_data platक्रमm_data;

	platक्रमm_data.gpio_reset = gpiod_get_index(&client->dev,
						   शून्य, 2, GPIOD_OUT_LOW);
	अगर (IS_ERR(platक्रमm_data.gpio_reset))
		वापस ERR_CAST(platक्रमm_data.gpio_reset);
	platक्रमm_data.gpio_strobe = gpiod_get_index(&client->dev,
						    शून्य, 0, GPIOD_OUT_LOW);
	अगर (IS_ERR(platक्रमm_data.gpio_strobe))
		वापस ERR_CAST(platक्रमm_data.gpio_strobe);
	platक्रमm_data.gpio_torch = gpiod_get_index(&client->dev,
						   शून्य, 1, GPIOD_OUT_LOW);
	अगर (IS_ERR(platक्रमm_data.gpio_torch))
		वापस ERR_CAST(platक्रमm_data.gpio_torch);

	/* Set to TX2 mode, then ENVM/TX2 pin is a घातer amplअगरier sync input:
	 * ENVM/TX pin निश्चितed, flash क्रमced पूर्णांकo torch;
	 * ENVM/TX pin desserted, flash set back;
	 */
	platक्रमm_data.envm_tx2 = 1;
	platक्रमm_data.tx2_polarity = 0;

	/* set peak current limit to be 1000mA */
	platक्रमm_data.current_limit = 0;

	वापस &platक्रमm_data;
पूर्ण

अटल पूर्णांक lm3554_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक err = 0;
	काष्ठा lm3554 *flash;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	flash = kzalloc(माप(*flash), GFP_KERNEL);
	अगर (!flash)
		वापस -ENOMEM;

	flash->pdata = lm3554_platक्रमm_data_func(client);
	अगर (IS_ERR(flash->pdata)) अणु
		err = PTR_ERR(flash->pdata);
		जाओ fail1;
	पूर्ण

	v4l2_i2c_subdev_init(&flash->sd, client, &lm3554_ops);
	flash->sd.पूर्णांकernal_ops = &lm3554_पूर्णांकernal_ops;
	flash->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	flash->mode = ATOMISP_FLASH_MODE_OFF;
	flash->समयout = LM3554_MAX_TIMEOUT / LM3554_TIMEOUT_STEPSIZE - 1;
	ret =
	    v4l2_ctrl_handler_init(&flash->ctrl_handler,
				   ARRAY_SIZE(lm3554_controls));
	अगर (ret) अणु
		dev_err(&client->dev, "error initialize a ctrl_handler.\n");
		जाओ fail3;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(lm3554_controls); i++)
		v4l2_ctrl_new_custom(&flash->ctrl_handler, &lm3554_controls[i],
				     शून्य);

	अगर (flash->ctrl_handler.error) अणु
		dev_err(&client->dev, "ctrl_handler error.\n");
		जाओ fail3;
	पूर्ण

	flash->sd.ctrl_handler = &flash->ctrl_handler;
	err = media_entity_pads_init(&flash->sd.entity, 0, शून्य);
	अगर (err) अणु
		dev_err(&client->dev, "error initialize a media entity.\n");
		जाओ fail2;
	पूर्ण

	flash->sd.entity.function = MEDIA_ENT_F_FLASH;

	mutex_init(&flash->घातer_lock);

	समयr_setup(&flash->flash_off_delay, lm3554_flash_off_delay, 0);

	err = lm3554_gpio_init(client);
	अगर (err) अणु
		dev_err(&client->dev, "gpio request/direction_output fail");
		जाओ fail3;
	पूर्ण
	वापस atomisp_रेजिस्टर_i2c_module(&flash->sd, शून्य, LED_FLASH);
fail3:
	media_entity_cleanup(&flash->sd.entity);
	v4l2_ctrl_handler_मुक्त(&flash->ctrl_handler);
fail2:
	v4l2_device_unरेजिस्टर_subdev(&flash->sd);
fail1:
	kमुक्त(flash);

	वापस err;
पूर्ण

अटल पूर्णांक lm3554_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा lm3554 *flash = to_lm3554(sd);

	media_entity_cleanup(&flash->sd.entity);
	v4l2_ctrl_handler_मुक्त(&flash->ctrl_handler);
	v4l2_device_unरेजिस्टर_subdev(sd);

	atomisp_gmin_हटाओ_subdev(sd);

	del_समयr_sync(&flash->flash_off_delay);

	lm3554_gpio_uninit(client);

	kमुक्त(flash);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lm3554_pm_ops = अणु
	.suspend = lm3554_suspend,
	.resume = lm3554_resume,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id lm3554_acpi_match[] = अणु
	अणु "INTCF1C" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, lm3554_acpi_match);

अटल काष्ठा i2c_driver lm3554_driver = अणु
	.driver = अणु
		.name = "lm3554",
		.pm   = &lm3554_pm_ops,
		.acpi_match_table = lm3554_acpi_match,
	पूर्ण,
	.probe_new = lm3554_probe,
	.हटाओ = lm3554_हटाओ,
पूर्ण;
module_i2c_driver(lm3554_driver);

MODULE_AUTHOR("Jing Tao <jing.tao@intel.com>");
MODULE_DESCRIPTION("LED flash driver for LM3554");
MODULE_LICENSE("GPL");
