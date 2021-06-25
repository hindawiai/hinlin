<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TI LM3692x LED chip family driver
// Copyright (C) 2017-18 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#घोषणा LM36922_MODEL	0
#घोषणा LM36923_MODEL	1

#घोषणा LM3692X_REV		0x0
#घोषणा LM3692X_RESET		0x1
#घोषणा LM3692X_EN		0x10
#घोषणा LM3692X_BRT_CTRL	0x11
#घोषणा LM3692X_PWM_CTRL	0x12
#घोषणा LM3692X_BOOST_CTRL	0x13
#घोषणा LM3692X_AUTO_FREQ_HI	0x15
#घोषणा LM3692X_AUTO_FREQ_LO	0x16
#घोषणा LM3692X_BL_ADJ_THRESH	0x17
#घोषणा LM3692X_BRT_LSB		0x18
#घोषणा LM3692X_BRT_MSB		0x19
#घोषणा LM3692X_FAULT_CTRL	0x1e
#घोषणा LM3692X_FAULT_FLAGS	0x1f

#घोषणा LM3692X_SW_RESET	BIT(0)
#घोषणा LM3692X_DEVICE_EN	BIT(0)
#घोषणा LM3692X_LED1_EN		BIT(1)
#घोषणा LM3692X_LED2_EN		BIT(2)
#घोषणा LM36923_LED3_EN		BIT(3)
#घोषणा LM3692X_ENABLE_MASK	(LM3692X_DEVICE_EN | LM3692X_LED1_EN | \
				 LM3692X_LED2_EN | LM36923_LED3_EN)

/* Brightness Control Bits */
#घोषणा LM3692X_BL_ADJ_POL	BIT(0)
#घोषणा LM3692X_RAMP_RATE_125us	0x00
#घोषणा LM3692X_RAMP_RATE_250us	BIT(1)
#घोषणा LM3692X_RAMP_RATE_500us BIT(2)
#घोषणा LM3692X_RAMP_RATE_1ms	(BIT(1) | BIT(2))
#घोषणा LM3692X_RAMP_RATE_2ms	BIT(3)
#घोषणा LM3692X_RAMP_RATE_4ms	(BIT(3) | BIT(1))
#घोषणा LM3692X_RAMP_RATE_8ms	(BIT(2) | BIT(3))
#घोषणा LM3692X_RAMP_RATE_16ms	(BIT(1) | BIT(2) | BIT(3))
#घोषणा LM3692X_RAMP_EN		BIT(4)
#घोषणा LM3692X_BRHT_MODE_REG	0x00
#घोषणा LM3692X_BRHT_MODE_PWM	BIT(5)
#घोषणा LM3692X_BRHT_MODE_MULTI_RAMP BIT(6)
#घोषणा LM3692X_BRHT_MODE_RAMP_MULTI (BIT(5) | BIT(6))
#घोषणा LM3692X_MAP_MODE_EXP	BIT(7)

/* PWM Register Bits */
#घोषणा LM3692X_PWM_FILTER_100	BIT(0)
#घोषणा LM3692X_PWM_FILTER_150	BIT(1)
#घोषणा LM3692X_PWM_FILTER_200	(BIT(0) | BIT(1))
#घोषणा LM3692X_PWM_HYSTER_1LSB BIT(2)
#घोषणा LM3692X_PWM_HYSTER_2LSB	BIT(3)
#घोषणा LM3692X_PWM_HYSTER_3LSB (BIT(3) | BIT(2))
#घोषणा LM3692X_PWM_HYSTER_4LSB BIT(4)
#घोषणा LM3692X_PWM_HYSTER_5LSB (BIT(4) | BIT(2))
#घोषणा LM3692X_PWM_HYSTER_6LSB (BIT(4) | BIT(3))
#घोषणा LM3692X_PWM_POLARITY	BIT(5)
#घोषणा LM3692X_PWM_SAMP_4MHZ	BIT(6)
#घोषणा LM3692X_PWM_SAMP_24MHZ	BIT(7)

/* Boost Control Bits */
#घोषणा LM3692X_OCP_PROT_1A	BIT(0)
#घोषणा LM3692X_OCP_PROT_1_25A	BIT(1)
#घोषणा LM3692X_OCP_PROT_1_5A	(BIT(0) | BIT(1))
#घोषणा LM3692X_OVP_21V		BIT(2)
#घोषणा LM3692X_OVP_25V		BIT(3)
#घोषणा LM3692X_OVP_29V		(BIT(2) | BIT(3))
#घोषणा LM3692X_MIN_IND_22UH	BIT(4)
#घोषणा LM3692X_BOOST_SW_1MHZ	BIT(5)
#घोषणा LM3692X_BOOST_SW_NO_SHIFT	BIT(6)

/* Fault Control Bits */
#घोषणा LM3692X_FAULT_CTRL_OVP BIT(0)
#घोषणा LM3692X_FAULT_CTRL_OCP BIT(1)
#घोषणा LM3692X_FAULT_CTRL_TSD BIT(2)
#घोषणा LM3692X_FAULT_CTRL_OPEN BIT(3)

/* Fault Flag Bits */
#घोषणा LM3692X_FAULT_FLAG_OVP BIT(0)
#घोषणा LM3692X_FAULT_FLAG_OCP BIT(1)
#घोषणा LM3692X_FAULT_FLAG_TSD BIT(2)
#घोषणा LM3692X_FAULT_FLAG_SHRT BIT(3)
#घोषणा LM3692X_FAULT_FLAG_OPEN BIT(4)

/**
 * काष्ठा lm3692x_led -
 * @lock - Lock क्रम पढ़ोing/writing the device
 * @client - Poपूर्णांकer to the I2C client
 * @led_dev - LED class device poपूर्णांकer
 * @regmap - Devices रेजिस्टर map
 * @enable_gpio - VDDIO/EN gpio to enable communication पूर्णांकerface
 * @regulator - LED supply regulator poपूर्णांकer
 * @led_enable - LED sync to be enabled
 * @model_id - Current device model ID क्रमागतerated
 */
काष्ठा lm3692x_led अणु
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा led_classdev led_dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
	पूर्णांक led_enable;
	पूर्णांक model_id;

	u8 boost_ctrl, brightness_ctrl;
	bool enabled;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lm3692x_reg_defs[] = अणु
	अणुLM3692X_EN, 0xfपूर्ण,
	अणुLM3692X_BRT_CTRL, 0x61पूर्ण,
	अणुLM3692X_PWM_CTRL, 0x73पूर्ण,
	अणुLM3692X_BOOST_CTRL, 0x6fपूर्ण,
	अणुLM3692X_AUTO_FREQ_HI, 0x0पूर्ण,
	अणुLM3692X_AUTO_FREQ_LO, 0x0पूर्ण,
	अणुLM3692X_BL_ADJ_THRESH, 0x0पूर्ण,
	अणुLM3692X_BRT_LSB, 0x7पूर्ण,
	अणुLM3692X_BRT_MSB, 0xffपूर्ण,
	अणुLM3692X_FAULT_CTRL, 0x7पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm3692x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LM3692X_FAULT_FLAGS,
	.reg_शेषs = lm3692x_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lm3692x_reg_defs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक lm3692x_fault_check(काष्ठा lm3692x_led *led)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पढ़ो_buf;

	ret = regmap_पढ़ो(led->regmap, LM3692X_FAULT_FLAGS, &पढ़ो_buf);
	अगर (ret)
		वापस ret;

	अगर (पढ़ो_buf)
		dev_err(&led->client->dev, "Detected a fault 0x%X\n", पढ़ो_buf);

	/* The first पढ़ो may clear the fault.  Check again to see अगर the fault
	 * still निकासs and वापस that value.
	 */
	regmap_पढ़ो(led->regmap, LM3692X_FAULT_FLAGS, &पढ़ो_buf);
	अगर (पढ़ो_buf)
		dev_err(&led->client->dev, "Second read of fault flags 0x%X\n",
			पढ़ो_buf);

	वापस पढ़ो_buf;
पूर्ण

अटल पूर्णांक lm3692x_leds_enable(काष्ठा lm3692x_led *led)
अणु
	पूर्णांक enable_state;
	पूर्णांक ret, reg_ret;

	अगर (led->enabled)
		वापस 0;

	अगर (led->regulator) अणु
		ret = regulator_enable(led->regulator);
		अगर (ret) अणु
			dev_err(&led->client->dev,
				"Failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 1);

	ret = lm3692x_fault_check(led);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot read/clear faults: %d\n",
			ret);
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_CTRL, 0x00);
	अगर (ret)
		जाओ out;

	/*
	 * For glitch मुक्त operation, the following data should
	 * only be written जबतक LEDx enable bits are 0 and the device enable
	 * bit is set to 1.
	 * per Section 7.5.14 of the data sheet
	 */
	ret = regmap_ग_लिखो(led->regmap, LM3692X_EN, LM3692X_DEVICE_EN);
	अगर (ret)
		जाओ out;

	/* Set the brightness to 0 so when enabled the LEDs करो not come
	 * on with full brightness.
	 */
	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_MSB, 0);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_LSB, 0);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_PWM_CTRL,
		LM3692X_PWM_FILTER_100 | LM3692X_PWM_SAMP_24MHZ);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BOOST_CTRL, led->boost_ctrl);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_AUTO_FREQ_HI, 0x00);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_AUTO_FREQ_LO, 0x00);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BL_ADJ_THRESH, 0x00);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_CTRL,
			LM3692X_BL_ADJ_POL | LM3692X_RAMP_EN);
	अगर (ret)
		जाओ out;

	चयन (led->led_enable) अणु
	हाल 0:
	शेष:
		अगर (led->model_id == LM36923_MODEL)
			enable_state = LM3692X_LED1_EN | LM3692X_LED2_EN |
			       LM36923_LED3_EN;
		अन्यथा
			enable_state = LM3692X_LED1_EN | LM3692X_LED2_EN;

		अवरोध;
	हाल 1:
		enable_state = LM3692X_LED1_EN;
		अवरोध;
	हाल 2:
		enable_state = LM3692X_LED2_EN;
		अवरोध;

	हाल 3:
		अगर (led->model_id == LM36923_MODEL) अणु
			enable_state = LM36923_LED3_EN;
			अवरोध;
		पूर्ण

		ret = -EINVAL;
		dev_err(&led->client->dev,
			"LED3 sync not available on this device\n");
		जाओ out;
	पूर्ण

	ret = regmap_update_bits(led->regmap, LM3692X_EN, LM3692X_ENABLE_MASK,
				 enable_state | LM3692X_DEVICE_EN);

	led->enabled = true;
	वापस ret;
out:
	dev_err(&led->client->dev, "Fail writing initialization values\n");

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 0);

	अगर (led->regulator) अणु
		reg_ret = regulator_disable(led->regulator);
		अगर (reg_ret)
			dev_err(&led->client->dev,
				"Failed to disable regulator: %d\n", reg_ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lm3692x_leds_disable(काष्ठा lm3692x_led *led)
अणु
	पूर्णांक ret;

	अगर (!led->enabled)
		वापस 0;

	ret = regmap_update_bits(led->regmap, LM3692X_EN, LM3692X_DEVICE_EN, 0);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Failed to disable regulator: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 0);

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(&led->client->dev,
				"Failed to disable regulator: %d\n", ret);
	पूर्ण

	led->enabled = false;
	वापस ret;
पूर्ण

अटल पूर्णांक lm3692x_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brt_val)
अणु
	काष्ठा lm3692x_led *led =
			container_of(led_cdev, काष्ठा lm3692x_led, led_dev);
	पूर्णांक ret;
	पूर्णांक led_brightness_lsb = (brt_val >> 5);

	mutex_lock(&led->lock);

	अगर (brt_val == 0) अणु
		ret = lm3692x_leds_disable(led);
		जाओ out;
	पूर्ण अन्यथा अणु
		lm3692x_leds_enable(led);
	पूर्ण

	ret = lm3692x_fault_check(led);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot read/clear faults: %d\n",
			ret);
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_MSB, brt_val);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot write MSB: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LM3692X_BRT_LSB, led_brightness_lsb);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot write LSB: %d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल क्रमागत led_brightness lm3692x_max_brightness(काष्ठा lm3692x_led *led,
						  u32 max_cur)
अणु
	u32 max_code;

	/* see p.12 of LM36922 data sheet क्रम brightness क्रमmula */
	max_code = ((max_cur * 1000) - 37806) / 12195;
	अगर (max_code > 0x7FF)
		max_code = 0x7FF;

	वापस max_code >> 3;
पूर्ण

अटल पूर्णांक lm3692x_probe_dt(काष्ठा lm3692x_led *led)
अणु
	काष्ठा fwnode_handle *child = शून्य;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	u32 ovp, max_cur;
	पूर्णांक ret;

	led->enable_gpio = devm_gpiod_get_optional(&led->client->dev,
						   "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(led->enable_gpio)) अणु
		ret = PTR_ERR(led->enable_gpio);
		dev_err(&led->client->dev, "Failed to get enable gpio: %d\n",
			ret);
		वापस ret;
	पूर्ण

	led->regulator = devm_regulator_get_optional(&led->client->dev, "vled");
	अगर (IS_ERR(led->regulator)) अणु
		ret = PTR_ERR(led->regulator);
		अगर (ret != -ENODEV)
			वापस dev_err_probe(&led->client->dev, ret,
					     "Failed to get vled regulator\n");

		led->regulator = शून्य;
	पूर्ण

	led->boost_ctrl = LM3692X_BOOST_SW_1MHZ |
		LM3692X_BOOST_SW_NO_SHIFT |
		LM3692X_OCP_PROT_1_5A;
	ret = device_property_पढ़ो_u32(&led->client->dev,
				       "ti,ovp-microvolt", &ovp);
	अगर (ret) अणु
		led->boost_ctrl |= LM3692X_OVP_29V;
	पूर्ण अन्यथा अणु
		चयन (ovp) अणु
		हाल 17000000:
			अवरोध;
		हाल 21000000:
			led->boost_ctrl |= LM3692X_OVP_21V;
			अवरोध;
		हाल 25000000:
			led->boost_ctrl |= LM3692X_OVP_25V;
			अवरोध;
		हाल 29000000:
			led->boost_ctrl |= LM3692X_OVP_29V;
			अवरोध;
		शेष:
			dev_err(&led->client->dev, "Invalid OVP %d\n", ovp);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	child = device_get_next_child_node(&led->client->dev, child);
	अगर (!child) अणु
		dev_err(&led->client->dev, "No LED Child node\n");
		वापस -ENODEV;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "reg", &led->led_enable);
	अगर (ret) अणु
		dev_err(&led->client->dev, "reg DT property missing\n");
		वापस ret;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "led-max-microamp", &max_cur);
	led->led_dev.max_brightness = ret ? LED_FULL :
		lm3692x_max_brightness(led, max_cur);

	init_data.fwnode = child;
	init_data.devicename = led->client->name;
	init_data.शेष_label = ":";

	ret = devm_led_classdev_रेजिस्टर_ext(&led->client->dev, &led->led_dev,
					     &init_data);
	अगर (ret) अणु
		dev_err(&led->client->dev, "led register err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3692x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3692x_led *led;
	पूर्णांक ret;

	led = devm_kzalloc(&client->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	mutex_init(&led->lock);
	led->client = client;
	led->led_dev.brightness_set_blocking = lm3692x_brightness_set;
	led->model_id = id->driver_data;
	i2c_set_clientdata(client, led);

	led->regmap = devm_regmap_init_i2c(client, &lm3692x_regmap_config);
	अगर (IS_ERR(led->regmap)) अणु
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = lm3692x_probe_dt(led);
	अगर (ret)
		वापस ret;

	ret = lm3692x_leds_enable(led);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3692x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3692x_led *led = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = lm3692x_leds_disable(led);
	अगर (ret)
		वापस ret;
	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3692x_id[] = अणु
	अणु "lm36922", LM36922_MODEL पूर्ण,
	अणु "lm36923", LM36923_MODEL पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3692x_id);

अटल स्थिर काष्ठा of_device_id of_lm3692x_leds_match[] = अणु
	अणु .compatible = "ti,lm36922", पूर्ण,
	अणु .compatible = "ti,lm36923", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lm3692x_leds_match);

अटल काष्ठा i2c_driver lm3692x_driver = अणु
	.driver = अणु
		.name	= "lm3692x",
		.of_match_table = of_lm3692x_leds_match,
	पूर्ण,
	.probe		= lm3692x_probe,
	.हटाओ		= lm3692x_हटाओ,
	.id_table	= lm3692x_id,
पूर्ण;
module_i2c_driver(lm3692x_driver);

MODULE_DESCRIPTION("Texas Instruments LM3692X LED driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
