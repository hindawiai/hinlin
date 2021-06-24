<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	LED driver क्रम TI lp3952 controller
 *
 *	Copyright (C) 2016, DAQRI, LLC.
 *	Author: Tony Makkiel <tony.makkiel@daqri.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/leds-lp3952.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

अटल पूर्णांक lp3952_रेजिस्टर_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	काष्ठा lp3952_led_array *priv = i2c_get_clientdata(client);

	ret = regmap_ग_लिखो(priv->regmap, reg, val);

	अगर (ret)
		dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
			__func__, reg, val, ret);
	वापस ret;
पूर्ण

अटल व्योम lp3952_on_off(काष्ठा lp3952_led_array *priv,
			  क्रमागत lp3952_leds led_id, bool on)
अणु
	पूर्णांक ret, val;

	dev_dbg(&priv->client->dev, "%s LED %d to %d\n", __func__, led_id, on);

	val = 1 << led_id;
	अगर (led_id == LP3952_LED_ALL)
		val = LP3952_LED_MASK_ALL;

	ret = regmap_update_bits(priv->regmap, LP3952_REG_LED_CTRL, val,
				 on ? val : 0);
	अगर (ret)
		dev_err(&priv->client->dev, "%s, Error %d\n", __func__, ret);
पूर्ण

/*
 * Using Imax to control brightness. There are 4 possible
 * setting 25, 50, 75 and 100 % of Imax. Possible values are
 * values 0-4. 0 meaning turn off.
 */
अटल पूर्णांक lp3952_set_brightness(काष्ठा led_classdev *cdev,
				 क्रमागत led_brightness value)
अणु
	अचिन्हित पूर्णांक reg, shअगरt_val;
	काष्ठा lp3952_ctrl_hdl *led = container_of(cdev,
						   काष्ठा lp3952_ctrl_hdl,
						   cdev);
	काष्ठा lp3952_led_array *priv = (काष्ठा lp3952_led_array *)led->priv;

	dev_dbg(cdev->dev, "Brightness request: %d on %d\n", value,
		led->channel);

	अगर (value == LED_OFF) अणु
		lp3952_on_off(priv, led->channel, false);
		वापस 0;
	पूर्ण

	अगर (led->channel > LP3952_RED_1) अणु
		dev_err(cdev->dev, " %s Invalid LED requested", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (led->channel >= LP3952_BLUE_1) अणु
		reg = LP3952_REG_RGB1_MAX_I_CTRL;
		shअगरt_val = (led->channel - LP3952_BLUE_1) * 2;
	पूर्ण अन्यथा अणु
		reg = LP3952_REG_RGB2_MAX_I_CTRL;
		shअगरt_val = led->channel * 2;
	पूर्ण

	/* Enable the LED in हाल it is not enabled alपढ़ोy */
	lp3952_on_off(priv, led->channel, true);

	वापस regmap_update_bits(priv->regmap, reg, 3 << shअगरt_val,
				  --value << shअगरt_val);
पूर्ण

अटल पूर्णांक lp3952_get_label(काष्ठा device *dev, स्थिर अक्षर *label, अक्षर *dest)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *str;

	ret = device_property_पढ़ो_string(dev, label, &str);
	अगर (ret)
		वापस ret;

	म_नकलन(dest, str, LP3952_LABEL_MAX_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक lp3952_रेजिस्टर_led_classdev(काष्ठा lp3952_led_array *priv)
अणु
	पूर्णांक i, acpi_ret, ret = -ENODEV;
	अटल स्थिर अक्षर *led_name_hdl[LP3952_LED_ALL] = अणु
		"blue2",
		"green2",
		"red2",
		"blue1",
		"green1",
		"red1"
	पूर्ण;

	क्रम (i = 0; i < LP3952_LED_ALL; i++) अणु
		acpi_ret = lp3952_get_label(&priv->client->dev, led_name_hdl[i],
					    priv->leds[i].name);
		अगर (acpi_ret)
			जारी;

		priv->leds[i].cdev.name = priv->leds[i].name;
		priv->leds[i].cdev.brightness = LED_OFF;
		priv->leds[i].cdev.max_brightness = LP3952_BRIGHT_MAX;
		priv->leds[i].cdev.brightness_set_blocking =
				lp3952_set_brightness;
		priv->leds[i].channel = i;
		priv->leds[i].priv = priv;

		ret = devm_led_classdev_रेजिस्टर(&priv->client->dev,
						 &priv->leds[i].cdev);
		अगर (ret < 0) अणु
			dev_err(&priv->client->dev,
				"couldn't register LED %s\n",
				priv->leds[i].cdev.name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lp3952_set_pattern_gen_cmd(काष्ठा lp3952_led_array *priv,
				      u8 cmd_index, u8 r, u8 g, u8 b,
				      क्रमागत lp3952_tt tt, क्रमागत lp3952_cet cet)
अणु
	पूर्णांक ret;
	काष्ठा ptrn_gen_cmd line = अणु
		अणु
			अणु
				.r = r,
				.g = g,
				.b = b,
				.cet = cet,
				.tt = tt
			पूर्ण
		पूर्ण
	पूर्ण;

	अगर (cmd_index >= LP3952_CMD_REG_COUNT)
		वापस -EINVAL;

	ret = lp3952_रेजिस्टर_ग_लिखो(priv->client,
				    LP3952_REG_CMD_0 + cmd_index * 2,
				    line.bytes.msb);
	अगर (ret)
		वापस ret;

	वापस lp3952_रेजिस्टर_ग_लिखो(priv->client,
				      LP3952_REG_CMD_0 + cmd_index * 2 + 1,
				      line.bytes.lsb);
पूर्ण

अटल पूर्णांक lp3952_configure(काष्ठा lp3952_led_array *priv)
अणु
	पूर्णांक ret;

	/* Disable any LEDs on from any previous conf. */
	ret = lp3952_रेजिस्टर_ग_लिखो(priv->client, LP3952_REG_LED_CTRL, 0);
	अगर (ret)
		वापस ret;

	/* enable rgb patter, loop */
	ret = lp3952_रेजिस्टर_ग_लिखो(priv->client, LP3952_REG_PAT_GEN_CTRL,
				    LP3952_PATRN_LOOP | LP3952_PATRN_GEN_EN);
	अगर (ret)
		वापस ret;

	/* Update Bit 6 (Active mode), Select both Led sets, Bit [1:0] */
	ret = lp3952_रेजिस्टर_ग_लिखो(priv->client, LP3952_REG_ENABLES,
				    LP3952_ACTIVE_MODE | LP3952_INT_B00ST_LDR);
	अगर (ret)
		वापस ret;

	/* Set Cmd1 क्रम RGB पूर्णांकensity,cmd and transition समय */
	वापस lp3952_set_pattern_gen_cmd(priv, 0, I46, I71, I100, TT0,
					   CET197);
पूर्ण

अटल स्थिर काष्ठा regmap_config lp3952_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = REG_MAX,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक lp3952_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक status;
	काष्ठा lp3952_led_array *priv;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;

	priv->enable_gpio = devm_gpiod_get(&client->dev, "nrst",
					   GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->enable_gpio)) अणु
		status = PTR_ERR(priv->enable_gpio);
		dev_err(&client->dev, "Failed to enable gpio: %d\n", status);
		वापस status;
	पूर्ण

	priv->regmap = devm_regmap_init_i2c(client, &lp3952_regmap);
	अगर (IS_ERR(priv->regmap)) अणु
		पूर्णांक err = PTR_ERR(priv->regmap);

		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			err);
		वापस err;
	पूर्ण

	i2c_set_clientdata(client, priv);

	status = lp3952_configure(priv);
	अगर (status) अणु
		dev_err(&client->dev, "Probe failed. Device not found (%d)\n",
			status);
		वापस status;
	पूर्ण

	status = lp3952_रेजिस्टर_led_classdev(priv);
	अगर (status) अणु
		dev_err(&client->dev, "Unable to register led_classdev: %d\n",
			status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp3952_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp3952_led_array *priv;

	priv = i2c_get_clientdata(client);
	lp3952_on_off(priv, LP3952_LED_ALL, false);
	gpiod_set_value(priv->enable_gpio, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp3952_id[] = अणु
	अणुLP3952_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp3952_id);

अटल काष्ठा i2c_driver lp3952_i2c_driver = अणु
	.driver = अणु
			.name = LP3952_NAME,
	पूर्ण,
	.probe = lp3952_probe,
	.हटाओ = lp3952_हटाओ,
	.id_table = lp3952_id,
पूर्ण;

module_i2c_driver(lp3952_i2c_driver);

MODULE_AUTHOR("Tony Makkiel <tony.makkiel@daqri.com>");
MODULE_DESCRIPTION("lp3952 I2C LED controller driver");
MODULE_LICENSE("GPL v2");
