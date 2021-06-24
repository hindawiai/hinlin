<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015-16 Golden Delicious Computers
 *
 * Author: Nikolaus Schaller <hns@goldelico.com>
 *
 * LED driver क्रम the IS31FL319अणु0,1,3,6,9पूर्ण to drive 1, 3, 6 or 9 light
 * effect LEDs.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>

/* रेजिस्टर numbers */
#घोषणा IS31FL319X_SHUTDOWN		0x00
#घोषणा IS31FL319X_CTRL1		0x01
#घोषणा IS31FL319X_CTRL2		0x02
#घोषणा IS31FL319X_CONFIG1		0x03
#घोषणा IS31FL319X_CONFIG2		0x04
#घोषणा IS31FL319X_RAMP_MODE		0x05
#घोषणा IS31FL319X_BREATH_MASK		0x06
#घोषणा IS31FL319X_PWM(channel)		(0x07 + channel)
#घोषणा IS31FL319X_DATA_UPDATE		0x10
#घोषणा IS31FL319X_T0(channel)		(0x11 + channel)
#घोषणा IS31FL319X_T123_1		0x1a
#घोषणा IS31FL319X_T123_2		0x1b
#घोषणा IS31FL319X_T123_3		0x1c
#घोषणा IS31FL319X_T4(channel)		(0x1d + channel)
#घोषणा IS31FL319X_TIME_UPDATE		0x26
#घोषणा IS31FL319X_RESET		0xff

#घोषणा IS31FL319X_REG_CNT		(IS31FL319X_RESET + 1)

#घोषणा IS31FL319X_MAX_LEDS		9

/* CS (Current Setting) in CONFIG2 रेजिस्टर */
#घोषणा IS31FL319X_CONFIG2_CS_SHIFT	4
#घोषणा IS31FL319X_CONFIG2_CS_MASK	0x7
#घोषणा IS31FL319X_CONFIG2_CS_STEP_REF	12

#घोषणा IS31FL319X_CURRENT_MIN		((u32)5000)
#घोषणा IS31FL319X_CURRENT_MAX		((u32)40000)
#घोषणा IS31FL319X_CURRENT_STEP		((u32)5000)
#घोषणा IS31FL319X_CURRENT_DEFAULT	((u32)20000)

/* Audio gain in CONFIG2 रेजिस्टर */
#घोषणा IS31FL319X_AUDIO_GAIN_DB_MAX	((u32)21)
#घोषणा IS31FL319X_AUDIO_GAIN_DB_STEP	((u32)3)

/*
 * regmap is used as a cache of chip's रेजिस्टर space,
 * to aव्योम पढ़ोing back brightness values from chip,
 * which is known to hang.
 */
काष्ठा is31fl319x_chip अणु
	स्थिर काष्ठा is31fl319x_chipdef *cdef;
	काष्ठा i2c_client               *client;
	काष्ठा gpio_desc		*shutकरोwn_gpio;
	काष्ठा regmap                   *regmap;
	काष्ठा mutex                    lock;
	u32                             audio_gain_db;

	काष्ठा is31fl319x_led अणु
		काष्ठा is31fl319x_chip  *chip;
		काष्ठा led_classdev     cdev;
		u32                     max_microamp;
		bool                    configured;
	पूर्ण leds[IS31FL319X_MAX_LEDS];
पूर्ण;

काष्ठा is31fl319x_chipdef अणु
	पूर्णांक num_leds;
पूर्ण;

अटल स्थिर काष्ठा is31fl319x_chipdef is31fl3190_cdef = अणु
	.num_leds = 1,
पूर्ण;

अटल स्थिर काष्ठा is31fl319x_chipdef is31fl3193_cdef = अणु
	.num_leds = 3,
पूर्ण;

अटल स्थिर काष्ठा is31fl319x_chipdef is31fl3196_cdef = अणु
	.num_leds = 6,
पूर्ण;

अटल स्थिर काष्ठा is31fl319x_chipdef is31fl3199_cdef = अणु
	.num_leds = 9,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_is31fl319x_match[] = अणु
	अणु .compatible = "issi,is31fl3190", .data = &is31fl3190_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3191", .data = &is31fl3190_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3193", .data = &is31fl3193_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3196", .data = &is31fl3196_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3199", .data = &is31fl3199_cdef, पूर्ण,
	अणु .compatible = "si-en,sn3199",    .data = &is31fl3199_cdef, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_is31fl319x_match);

अटल पूर्णांक is31fl319x_brightness_set(काष्ठा led_classdev *cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा is31fl319x_led *led = container_of(cdev, काष्ठा is31fl319x_led,
						  cdev);
	काष्ठा is31fl319x_chip *is31 = led->chip;
	पूर्णांक chan = led - is31->leds;
	पूर्णांक ret;
	पूर्णांक i;
	u8 ctrl1 = 0, ctrl2 = 0;

	dev_dbg(&is31->client->dev, "%s %d: %d\n", __func__, chan, brightness);

	mutex_lock(&is31->lock);

	/* update PWM रेजिस्टर */
	ret = regmap_ग_लिखो(is31->regmap, IS31FL319X_PWM(chan), brightness);
	अगर (ret < 0)
		जाओ out;

	/* पढ़ो current brightness of all PWM channels */
	क्रम (i = 0; i < is31->cdef->num_leds; i++) अणु
		अचिन्हित पूर्णांक pwm_value;
		bool on;

		/*
		 * since neither cdev nor the chip can provide
		 * the current setting, we पढ़ो from the regmap cache
		 */

		ret = regmap_पढ़ो(is31->regmap, IS31FL319X_PWM(i), &pwm_value);
		dev_dbg(&is31->client->dev, "%s read %d: ret=%d: %d\n",
			__func__, i, ret, pwm_value);
		on = ret >= 0 && pwm_value > LED_OFF;

		अगर (i < 3)
			ctrl1 |= on << i;       /* 0..2 => bit 0..2 */
		अन्यथा अगर (i < 6)
			ctrl1 |= on << (i + 1); /* 3..5 => bit 4..6 */
		अन्यथा
			ctrl2 |= on << (i - 6); /* 6..8 => bit 0..2 */
	पूर्ण

	अगर (ctrl1 > 0 || ctrl2 > 0) अणु
		dev_dbg(&is31->client->dev, "power up %02x %02x\n",
			ctrl1, ctrl2);
		regmap_ग_लिखो(is31->regmap, IS31FL319X_CTRL1, ctrl1);
		regmap_ग_लिखो(is31->regmap, IS31FL319X_CTRL2, ctrl2);
		/* update PWMs */
		regmap_ग_लिखो(is31->regmap, IS31FL319X_DATA_UPDATE, 0x00);
		/* enable chip from shut करोwn */
		ret = regmap_ग_लिखो(is31->regmap, IS31FL319X_SHUTDOWN, 0x01);
	पूर्ण अन्यथा अणु
		dev_dbg(&is31->client->dev, "power down\n");
		/* shut करोwn (no need to clear CTRL1/2) */
		ret = regmap_ग_लिखो(is31->regmap, IS31FL319X_SHUTDOWN, 0x00);
	पूर्ण

out:
	mutex_unlock(&is31->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक is31fl319x_parse_child_dt(स्थिर काष्ठा device *dev,
				     स्थिर काष्ठा device_node *child,
				     काष्ठा is31fl319x_led *led)
अणु
	काष्ठा led_classdev *cdev = &led->cdev;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_string(child, "label", &cdev->name))
		cdev->name = child->name;

	ret = of_property_पढ़ो_string(child, "linux,default-trigger",
				      &cdev->शेष_trigger);
	अगर (ret < 0 && ret != -EINVAL) /* is optional */
		वापस ret;

	led->max_microamp = IS31FL319X_CURRENT_DEFAULT;
	ret = of_property_पढ़ो_u32(child, "led-max-microamp",
				   &led->max_microamp);
	अगर (!ret) अणु
		अगर (led->max_microamp < IS31FL319X_CURRENT_MIN)
			वापस -EINVAL;	/* not supported */
		led->max_microamp = min(led->max_microamp,
					  IS31FL319X_CURRENT_MAX);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is31fl319x_parse_dt(काष्ठा device *dev,
			       काष्ठा is31fl319x_chip *is31)
अणु
	काष्ठा device_node *np = dev_of_node(dev), *child;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	is31->shutकरोwn_gpio = devm_gpiod_get_optional(dev,
						"shutdown",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(is31->shutकरोwn_gpio)) अणु
		ret = PTR_ERR(is31->shutकरोwn_gpio);
		dev_err(dev, "Failed to get shutdown gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	is31->cdef = device_get_match_data(dev);

	count = of_get_available_child_count(np);

	dev_dbg(dev, "probing with %d leds defined in DT\n", count);

	अगर (!count || count > is31->cdef->num_leds) अणु
		dev_err(dev, "Number of leds defined must be between 1 and %u\n",
			is31->cdef->num_leds);
		वापस -ENODEV;
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा is31fl319x_led *led;
		u32 reg;

		ret = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret) अणु
			dev_err(dev, "Failed to read led 'reg' property\n");
			जाओ put_child_node;
		पूर्ण

		अगर (reg < 1 || reg > is31->cdef->num_leds) अणु
			dev_err(dev, "invalid led reg %u\n", reg);
			ret = -EINVAL;
			जाओ put_child_node;
		पूर्ण

		led = &is31->leds[reg - 1];

		अगर (led->configured) अणु
			dev_err(dev, "led %u is already configured\n", reg);
			ret = -EINVAL;
			जाओ put_child_node;
		पूर्ण

		ret = is31fl319x_parse_child_dt(dev, child, led);
		अगर (ret) अणु
			dev_err(dev, "led %u DT parsing failed\n", reg);
			जाओ put_child_node;
		पूर्ण

		led->configured = true;
	पूर्ण

	is31->audio_gain_db = 0;
	ret = of_property_पढ़ो_u32(np, "audio-gain-db", &is31->audio_gain_db);
	अगर (!ret)
		is31->audio_gain_db = min(is31->audio_gain_db,
					  IS31FL319X_AUDIO_GAIN_DB_MAX);

	वापस 0;

put_child_node:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल bool is31fl319x_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु /* we have no पढ़ोable रेजिस्टरs */
	वापस false;
पूर्ण

अटल bool is31fl319x_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु /* अस्थिर रेजिस्टरs are not cached */
	चयन (reg) अणु
	हाल IS31FL319X_DATA_UPDATE:
	हाल IS31FL319X_TIME_UPDATE:
	हाल IS31FL319X_RESET:
		वापस true; /* always ग_लिखो-through */
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष is31fl319x_reg_शेषs[] = अणु
	अणु IS31FL319X_CONFIG1, 0x00पूर्ण,
	अणु IS31FL319X_CONFIG2, 0x00पूर्ण,
	अणु IS31FL319X_PWM(0), 0x00पूर्ण,
	अणु IS31FL319X_PWM(1), 0x00पूर्ण,
	अणु IS31FL319X_PWM(2), 0x00पूर्ण,
	अणु IS31FL319X_PWM(3), 0x00पूर्ण,
	अणु IS31FL319X_PWM(4), 0x00पूर्ण,
	अणु IS31FL319X_PWM(5), 0x00पूर्ण,
	अणु IS31FL319X_PWM(6), 0x00पूर्ण,
	अणु IS31FL319X_PWM(7), 0x00पूर्ण,
	अणु IS31FL319X_PWM(8), 0x00पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = IS31FL319X_REG_CNT,
	.cache_type = REGCACHE_FLAT,
	.पढ़ोable_reg = is31fl319x_पढ़ोable_reg,
	.अस्थिर_reg = is31fl319x_अस्थिर_reg,
	.reg_शेषs = is31fl319x_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(is31fl319x_reg_शेषs),
पूर्ण;

अटल अंतरभूत पूर्णांक is31fl319x_microamp_to_cs(काष्ठा device *dev, u32 microamp)
अणु /* round करोwn to nearest supported value (range check करोne by caller) */
	u32 step = microamp / IS31FL319X_CURRENT_STEP;

	वापस ((IS31FL319X_CONFIG2_CS_STEP_REF - step) &
		IS31FL319X_CONFIG2_CS_MASK) <<
		IS31FL319X_CONFIG2_CS_SHIFT; /* CS encoding */
पूर्ण

अटल अंतरभूत पूर्णांक is31fl319x_db_to_gain(u32 dezibel)
अणु /* round करोwn to nearest supported value (range check करोne by caller) */
	वापस dezibel / IS31FL319X_AUDIO_GAIN_DB_STEP;
पूर्ण

अटल पूर्णांक is31fl319x_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा is31fl319x_chip *is31;
	काष्ठा device *dev = &client->dev;
	पूर्णांक err;
	पूर्णांक i = 0;
	u32 aggregated_led_microamp = IS31FL319X_CURRENT_MAX;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -EIO;

	is31 = devm_kzalloc(&client->dev, माप(*is31), GFP_KERNEL);
	अगर (!is31)
		वापस -ENOMEM;

	mutex_init(&is31->lock);

	err = is31fl319x_parse_dt(&client->dev, is31);
	अगर (err)
		जाओ मुक्त_mutex;

	अगर (is31->shutकरोwn_gpio) अणु
		gpiod_direction_output(is31->shutकरोwn_gpio, 0);
		mdelay(5);
		gpiod_direction_output(is31->shutकरोwn_gpio, 1);
	पूर्ण

	is31->client = client;
	is31->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(is31->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		err = PTR_ERR(is31->regmap);
		जाओ मुक्त_mutex;
	पूर्ण

	i2c_set_clientdata(client, is31);

	/* check क्रम ग_लिखो-reply from chip (we can't पढ़ो any रेजिस्टरs) */
	err = regmap_ग_लिखो(is31->regmap, IS31FL319X_RESET, 0x00);
	अगर (err < 0) अणु
		dev_err(&client->dev, "no response from chip write: err = %d\n",
			err);
		err = -EIO; /* करोes not answer */
		जाओ मुक्त_mutex;
	पूर्ण

	/*
	 * Kernel conventions require per-LED led-max-microamp property.
	 * But the chip करोes not allow to limit inभागidual LEDs.
	 * So we take minimum from all subnodes क्रम safety of hardware.
	 */
	क्रम (i = 0; i < is31->cdef->num_leds; i++)
		अगर (is31->leds[i].configured &&
		    is31->leds[i].max_microamp < aggregated_led_microamp)
			aggregated_led_microamp = is31->leds[i].max_microamp;

	regmap_ग_लिखो(is31->regmap, IS31FL319X_CONFIG2,
		     is31fl319x_microamp_to_cs(dev, aggregated_led_microamp) |
		     is31fl319x_db_to_gain(is31->audio_gain_db));

	क्रम (i = 0; i < is31->cdef->num_leds; i++) अणु
		काष्ठा is31fl319x_led *led = &is31->leds[i];

		अगर (!led->configured)
			जारी;

		led->chip = is31;
		led->cdev.brightness_set_blocking = is31fl319x_brightness_set;

		err = devm_led_classdev_रेजिस्टर(&client->dev, &led->cdev);
		अगर (err < 0)
			जाओ मुक्त_mutex;
	पूर्ण

	वापस 0;

मुक्त_mutex:
	mutex_destroy(&is31->lock);
	वापस err;
पूर्ण

अटल पूर्णांक is31fl319x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा is31fl319x_chip *is31 = i2c_get_clientdata(client);

	mutex_destroy(&is31->lock);
	वापस 0;
पूर्ण

/*
 * i2c-core (and modalias) requires that id_table be properly filled,
 * even though it is not used क्रम DeviceTree based instantiation.
 */
अटल स्थिर काष्ठा i2c_device_id is31fl319x_id[] = अणु
	अणु "is31fl3190" पूर्ण,
	अणु "is31fl3191" पूर्ण,
	अणु "is31fl3193" पूर्ण,
	अणु "is31fl3196" पूर्ण,
	अणु "is31fl3199" पूर्ण,
	अणु "sn3199" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, is31fl319x_id);

अटल काष्ठा i2c_driver is31fl319x_driver = अणु
	.driver   = अणु
		.name           = "leds-is31fl319x",
		.of_match_table = of_match_ptr(of_is31fl319x_match),
	पूर्ण,
	.probe    = is31fl319x_probe,
	.हटाओ   = is31fl319x_हटाओ,
	.id_table = is31fl319x_id,
पूर्ण;

module_i2c_driver(is31fl319x_driver);

MODULE_AUTHOR("H. Nikolaus Schaller <hns@goldelico.com>");
MODULE_AUTHOR("Andrey Utkin <andrey_utkin@fastmail.com>");
MODULE_DESCRIPTION("IS31FL319X LED driver");
MODULE_LICENSE("GPL v2");
