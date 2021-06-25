<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 ST-Ericsson SA.
 * Copyright (C) 2009 Motorola, Inc.
 *
 * Simple driver क्रम National Semiconductor LM3530 Backlight driver chip
 *
 * Author: Shreshtha Kumar SAHU <shreshthakumar.sahu@stericsson.com>
 * based on leds-lm3530.c by Dan Murphy <D.Murphy@motorola.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/led-lm3530.h>
#समावेश <linux/types.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>

#घोषणा LM3530_LED_DEV "lcd-backlight"
#घोषणा LM3530_NAME "lm3530-led"

#घोषणा LM3530_GEN_CONFIG		0x10
#घोषणा LM3530_ALS_CONFIG		0x20
#घोषणा LM3530_BRT_RAMP_RATE		0x30
#घोषणा LM3530_ALS_IMP_SELECT		0x41
#घोषणा LM3530_BRT_CTRL_REG		0xA0
#घोषणा LM3530_ALS_ZB0_REG		0x60
#घोषणा LM3530_ALS_ZB1_REG		0x61
#घोषणा LM3530_ALS_ZB2_REG		0x62
#घोषणा LM3530_ALS_ZB3_REG		0x63
#घोषणा LM3530_ALS_Z0T_REG		0x70
#घोषणा LM3530_ALS_Z1T_REG		0x71
#घोषणा LM3530_ALS_Z2T_REG		0x72
#घोषणा LM3530_ALS_Z3T_REG		0x73
#घोषणा LM3530_ALS_Z4T_REG		0x74
#घोषणा LM3530_REG_MAX			14

/* General Control Register */
#घोषणा LM3530_EN_I2C_SHIFT		(0)
#घोषणा LM3530_RAMP_LAW_SHIFT		(1)
#घोषणा LM3530_MAX_CURR_SHIFT		(2)
#घोषणा LM3530_EN_PWM_SHIFT		(5)
#घोषणा LM3530_PWM_POL_SHIFT		(6)
#घोषणा LM3530_EN_PWM_SIMPLE_SHIFT	(7)

#घोषणा LM3530_ENABLE_I2C		(1 << LM3530_EN_I2C_SHIFT)
#घोषणा LM3530_ENABLE_PWM		(1 << LM3530_EN_PWM_SHIFT)
#घोषणा LM3530_POL_LOW			(1 << LM3530_PWM_POL_SHIFT)
#घोषणा LM3530_ENABLE_PWM_SIMPLE	(1 << LM3530_EN_PWM_SIMPLE_SHIFT)

/* ALS Config Register Options */
#घोषणा LM3530_ALS_AVG_TIME_SHIFT	(0)
#घोषणा LM3530_EN_ALS_SHIFT		(3)
#घोषणा LM3530_ALS_SEL_SHIFT		(5)

#घोषणा LM3530_ENABLE_ALS		(3 << LM3530_EN_ALS_SHIFT)

/* Brightness Ramp Rate Register */
#घोषणा LM3530_BRT_RAMP_FALL_SHIFT	(0)
#घोषणा LM3530_BRT_RAMP_RISE_SHIFT	(3)

/* ALS Resistor Select */
#घोषणा LM3530_ALS1_IMP_SHIFT		(0)
#घोषणा LM3530_ALS2_IMP_SHIFT		(4)

/* Zone Boundary Register शेषs */
#घोषणा LM3530_ALS_ZB_MAX		(4)
#घोषणा LM3530_ALS_WINDOW_mV		(1000)
#घोषणा LM3530_ALS_OFFSET_mV		(4)

/* Zone Target Register शेषs */
#घोषणा LM3530_DEF_ZT_0			(0x7F)
#घोषणा LM3530_DEF_ZT_1			(0x66)
#घोषणा LM3530_DEF_ZT_2			(0x4C)
#घोषणा LM3530_DEF_ZT_3			(0x33)
#घोषणा LM3530_DEF_ZT_4			(0x19)

/* 7 bits are used क्रम the brightness : LM3530_BRT_CTRL_REG */
#घोषणा MAX_BRIGHTNESS			(127)

काष्ठा lm3530_mode_map अणु
	स्थिर अक्षर *mode;
	क्रमागत lm3530_mode mode_val;
पूर्ण;

अटल काष्ठा lm3530_mode_map mode_map[] = अणु
	अणु "man", LM3530_BL_MODE_MANUAL पूर्ण,
	अणु "als", LM3530_BL_MODE_ALS पूर्ण,
	अणु "pwm", LM3530_BL_MODE_PWM पूर्ण,
पूर्ण;

/**
 * काष्ठा lm3530_data
 * @led_dev: led class device
 * @client: i2c client
 * @pdata: LM3530 platक्रमm data
 * @mode: mode of operation - manual, ALS, PWM
 * @regulator: regulator
 * @brighness: previous brightness value
 * @enable: regulator is enabled
 */
काष्ठा lm3530_data अणु
	काष्ठा led_classdev led_dev;
	काष्ठा i2c_client *client;
	काष्ठा lm3530_platक्रमm_data *pdata;
	क्रमागत lm3530_mode mode;
	काष्ठा regulator *regulator;
	क्रमागत led_brightness brightness;
	bool enable;
पूर्ण;

/*
 * काष्ठा lm3530_als_data
 * @config  : value of ALS configuration रेजिस्टर
 * @imp_sel : value of ALS resistor select रेजिस्टर
 * @zone    : values of ALS ZB(Zone Boundary) रेजिस्टरs
 */
काष्ठा lm3530_als_data अणु
	u8 config;
	u8 imp_sel;
	u8 zones[LM3530_ALS_ZB_MAX];
पूर्ण;

अटल स्थिर u8 lm3530_reg[LM3530_REG_MAX] = अणु
	LM3530_GEN_CONFIG,
	LM3530_ALS_CONFIG,
	LM3530_BRT_RAMP_RATE,
	LM3530_ALS_IMP_SELECT,
	LM3530_BRT_CTRL_REG,
	LM3530_ALS_ZB0_REG,
	LM3530_ALS_ZB1_REG,
	LM3530_ALS_ZB2_REG,
	LM3530_ALS_ZB3_REG,
	LM3530_ALS_Z0T_REG,
	LM3530_ALS_Z1T_REG,
	LM3530_ALS_Z2T_REG,
	LM3530_ALS_Z3T_REG,
	LM3530_ALS_Z4T_REG,
पूर्ण;

अटल पूर्णांक lm3530_get_mode_from_str(स्थिर अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mode_map); i++)
		अगर (sysfs_streq(str, mode_map[i].mode))
			वापस mode_map[i].mode_val;

	वापस -EINVAL;
पूर्ण

अटल व्योम lm3530_als_configure(काष्ठा lm3530_platक्रमm_data *pdata,
				काष्ठा lm3530_als_data *als)
अणु
	पूर्णांक i;
	u32 als_vmin, als_vmax, als_vstep;

	अगर (pdata->als_vmax == 0) अणु
		pdata->als_vmin = 0;
		pdata->als_vmax = LM3530_ALS_WINDOW_mV;
	पूर्ण

	als_vmin = pdata->als_vmin;
	als_vmax = pdata->als_vmax;

	अगर ((als_vmax - als_vmin) > LM3530_ALS_WINDOW_mV)
		pdata->als_vmax = als_vmax = als_vmin + LM3530_ALS_WINDOW_mV;

	/* n zone boundary makes n+1 zones */
	als_vstep = (als_vmax - als_vmin) / (LM3530_ALS_ZB_MAX + 1);

	क्रम (i = 0; i < LM3530_ALS_ZB_MAX; i++)
		als->zones[i] = (((als_vmin + LM3530_ALS_OFFSET_mV) +
			als_vstep + (i * als_vstep)) * LED_FULL) / 1000;

	als->config =
		(pdata->als_avrg_समय << LM3530_ALS_AVG_TIME_SHIFT) |
		(LM3530_ENABLE_ALS) |
		(pdata->als_input_mode << LM3530_ALS_SEL_SHIFT);

	als->imp_sel =
		(pdata->als1_resistor_sel << LM3530_ALS1_IMP_SHIFT) |
		(pdata->als2_resistor_sel << LM3530_ALS2_IMP_SHIFT);
पूर्ण

अटल पूर्णांक lm3530_led_enable(काष्ठा lm3530_data *drvdata)
अणु
	पूर्णांक ret;

	अगर (drvdata->enable)
		वापस 0;

	ret = regulator_enable(drvdata->regulator);
	अगर (ret) अणु
		dev_err(drvdata->led_dev.dev, "Failed to enable vin:%d\n", ret);
		वापस ret;
	पूर्ण

	drvdata->enable = true;
	वापस 0;
पूर्ण

अटल व्योम lm3530_led_disable(काष्ठा lm3530_data *drvdata)
अणु
	पूर्णांक ret;

	अगर (!drvdata->enable)
		वापस;

	ret = regulator_disable(drvdata->regulator);
	अगर (ret) अणु
		dev_err(drvdata->led_dev.dev, "Failed to disable vin:%d\n",
			ret);
		वापस;
	पूर्ण

	drvdata->enable = false;
पूर्ण

अटल पूर्णांक lm3530_init_रेजिस्टरs(काष्ठा lm3530_data *drvdata)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	u8 gen_config;
	u8 brt_ramp;
	u8 brightness;
	u8 reg_val[LM3530_REG_MAX];
	काष्ठा lm3530_platक्रमm_data *pdata = drvdata->pdata;
	काष्ठा i2c_client *client = drvdata->client;
	काष्ठा lm3530_pwm_data *pwm = &pdata->pwm_data;
	काष्ठा lm3530_als_data als;

	स_रखो(&als, 0, माप(काष्ठा lm3530_als_data));

	gen_config = (pdata->brt_ramp_law << LM3530_RAMP_LAW_SHIFT) |
			((pdata->max_current & 7) << LM3530_MAX_CURR_SHIFT);

	चयन (drvdata->mode) अणु
	हाल LM3530_BL_MODE_MANUAL:
		gen_config |= LM3530_ENABLE_I2C;
		अवरोध;
	हाल LM3530_BL_MODE_ALS:
		gen_config |= LM3530_ENABLE_I2C;
		lm3530_als_configure(pdata, &als);
		अवरोध;
	हाल LM3530_BL_MODE_PWM:
		gen_config |= LM3530_ENABLE_PWM | LM3530_ENABLE_PWM_SIMPLE |
			      (pdata->pwm_pol_hi << LM3530_PWM_POL_SHIFT);
		अवरोध;
	पूर्ण

	brt_ramp = (pdata->brt_ramp_fall << LM3530_BRT_RAMP_FALL_SHIFT) |
			(pdata->brt_ramp_rise << LM3530_BRT_RAMP_RISE_SHIFT);

	अगर (drvdata->brightness)
		brightness = drvdata->brightness;
	अन्यथा
		brightness = drvdata->brightness = pdata->brt_val;

	अगर (brightness > drvdata->led_dev.max_brightness)
		brightness = drvdata->led_dev.max_brightness;

	reg_val[0] = gen_config;	/* LM3530_GEN_CONFIG */
	reg_val[1] = als.config;	/* LM3530_ALS_CONFIG */
	reg_val[2] = brt_ramp;		/* LM3530_BRT_RAMP_RATE */
	reg_val[3] = als.imp_sel;	/* LM3530_ALS_IMP_SELECT */
	reg_val[4] = brightness;	/* LM3530_BRT_CTRL_REG */
	reg_val[5] = als.zones[0];	/* LM3530_ALS_ZB0_REG */
	reg_val[6] = als.zones[1];	/* LM3530_ALS_ZB1_REG */
	reg_val[7] = als.zones[2];	/* LM3530_ALS_ZB2_REG */
	reg_val[8] = als.zones[3];	/* LM3530_ALS_ZB3_REG */
	reg_val[9] = LM3530_DEF_ZT_0;	/* LM3530_ALS_Z0T_REG */
	reg_val[10] = LM3530_DEF_ZT_1;	/* LM3530_ALS_Z1T_REG */
	reg_val[11] = LM3530_DEF_ZT_2;	/* LM3530_ALS_Z2T_REG */
	reg_val[12] = LM3530_DEF_ZT_3;	/* LM3530_ALS_Z3T_REG */
	reg_val[13] = LM3530_DEF_ZT_4;	/* LM3530_ALS_Z4T_REG */

	ret = lm3530_led_enable(drvdata);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < LM3530_REG_MAX; i++) अणु
		/* करो not update brightness रेजिस्टर when pwm mode */
		अगर (lm3530_reg[i] == LM3530_BRT_CTRL_REG &&
		    drvdata->mode == LM3530_BL_MODE_PWM) अणु
			अगर (pwm->pwm_set_पूर्णांकensity)
				pwm->pwm_set_पूर्णांकensity(reg_val[i],
					drvdata->led_dev.max_brightness);
			जारी;
		पूर्ण

		ret = i2c_smbus_ग_लिखो_byte_data(client,
				lm3530_reg[i], reg_val[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम lm3530_brightness_set(काष्ठा led_classdev *led_cdev,
				     क्रमागत led_brightness brt_val)
अणु
	पूर्णांक err;
	काष्ठा lm3530_data *drvdata =
	    container_of(led_cdev, काष्ठा lm3530_data, led_dev);
	काष्ठा lm3530_platक्रमm_data *pdata = drvdata->pdata;
	काष्ठा lm3530_pwm_data *pwm = &pdata->pwm_data;
	u8 max_brightness = led_cdev->max_brightness;

	चयन (drvdata->mode) अणु
	हाल LM3530_BL_MODE_MANUAL:

		अगर (!drvdata->enable) अणु
			err = lm3530_init_रेजिस्टरs(drvdata);
			अगर (err) अणु
				dev_err(&drvdata->client->dev,
					"Register Init failed: %d\n", err);
				अवरोध;
			पूर्ण
		पूर्ण

		/* set the brightness in brightness control रेजिस्टर*/
		err = i2c_smbus_ग_लिखो_byte_data(drvdata->client,
				LM3530_BRT_CTRL_REG, brt_val);
		अगर (err)
			dev_err(&drvdata->client->dev,
				"Unable to set brightness: %d\n", err);
		अन्यथा
			drvdata->brightness = brt_val;

		अगर (brt_val == 0)
			lm3530_led_disable(drvdata);
		अवरोध;
	हाल LM3530_BL_MODE_ALS:
		अवरोध;
	हाल LM3530_BL_MODE_PWM:
		अगर (pwm->pwm_set_पूर्णांकensity)
			pwm->pwm_set_पूर्णांकensity(brt_val, max_brightness);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3530_data *drvdata;
	पूर्णांक i, len = 0;

	drvdata = container_of(led_cdev, काष्ठा lm3530_data, led_dev);
	क्रम (i = 0; i < ARRAY_SIZE(mode_map); i++)
		अगर (drvdata->mode == mode_map[i].mode_val)
			len += प्र_लिखो(buf + len, "[%s] ", mode_map[i].mode);
		अन्यथा
			len += प्र_लिखो(buf + len, "%s ", mode_map[i].mode);

	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev, काष्ठा device_attribute
			  *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3530_data *drvdata;
	काष्ठा lm3530_pwm_data *pwm;
	u8 max_brightness;
	पूर्णांक mode, err;

	drvdata = container_of(led_cdev, काष्ठा lm3530_data, led_dev);
	pwm = &drvdata->pdata->pwm_data;
	max_brightness = led_cdev->max_brightness;
	mode = lm3530_get_mode_from_str(buf);
	अगर (mode < 0) अणु
		dev_err(dev, "Invalid mode\n");
		वापस mode;
	पूर्ण

	drvdata->mode = mode;

	/* set pwm to low अगर unnecessary */
	अगर (mode != LM3530_BL_MODE_PWM && pwm->pwm_set_पूर्णांकensity)
		pwm->pwm_set_पूर्णांकensity(0, max_brightness);

	err = lm3530_init_रेजिस्टरs(drvdata);
	अगर (err) अणु
		dev_err(dev, "Setting %s Mode failed :%d\n", buf, err);
		वापस err;
	पूर्ण

	वापस माप(drvdata->mode);
पूर्ण
अटल DEVICE_ATTR_RW(mode);

अटल काष्ठा attribute *lm3530_attrs[] = अणु
	&dev_attr_mode.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm3530);

अटल पूर्णांक lm3530_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3530_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा lm3530_data *drvdata;
	पूर्णांक err = 0;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "platform data required\n");
		वापस -ENODEV;
	पूर्ण

	/* BL mode */
	अगर (pdata->mode > LM3530_BL_MODE_PWM) अणु
		dev_err(&client->dev, "Illegal Mode request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C_FUNC_I2C not supported\n");
		वापस -EIO;
	पूर्ण

	drvdata = devm_kzalloc(&client->dev, माप(काष्ठा lm3530_data),
				GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;

	drvdata->mode = pdata->mode;
	drvdata->client = client;
	drvdata->pdata = pdata;
	drvdata->brightness = LED_OFF;
	drvdata->enable = false;
	drvdata->led_dev.name = LM3530_LED_DEV;
	drvdata->led_dev.brightness_set = lm3530_brightness_set;
	drvdata->led_dev.max_brightness = MAX_BRIGHTNESS;
	drvdata->led_dev.groups = lm3530_groups;

	i2c_set_clientdata(client, drvdata);

	drvdata->regulator = devm_regulator_get(&client->dev, "vin");
	अगर (IS_ERR(drvdata->regulator)) अणु
		dev_err(&client->dev, "regulator get failed\n");
		err = PTR_ERR(drvdata->regulator);
		drvdata->regulator = शून्य;
		वापस err;
	पूर्ण

	अगर (drvdata->pdata->brt_val) अणु
		err = lm3530_init_रेजिस्टरs(drvdata);
		अगर (err < 0) अणु
			dev_err(&client->dev,
				"Register Init failed: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण
	err = led_classdev_रेजिस्टर(&client->dev, &drvdata->led_dev);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Register led class failed: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3530_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3530_data *drvdata = i2c_get_clientdata(client);

	lm3530_led_disable(drvdata);
	led_classdev_unरेजिस्टर(&drvdata->led_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3530_id[] = अणु
	अणुLM3530_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3530_id);

अटल काष्ठा i2c_driver lm3530_i2c_driver = अणु
	.probe = lm3530_probe,
	.हटाओ = lm3530_हटाओ,
	.id_table = lm3530_id,
	.driver = अणु
		.name = LM3530_NAME,
	पूर्ण,
पूर्ण;

module_i2c_driver(lm3530_i2c_driver);

MODULE_DESCRIPTION("Back Light driver for LM3530");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Shreshtha Kumar SAHU <shreshthakumar.sahu@stericsson.com>");
