<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Driver क्रम Awinic AW2013 3-channel LED driver

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#घोषणा AW2013_MAX_LEDS 3

/* Reset and ID रेजिस्टर */
#घोषणा AW2013_RSTR 0x00
#घोषणा AW2013_RSTR_RESET 0x55
#घोषणा AW2013_RSTR_CHIP_ID 0x33

/* Global control रेजिस्टर */
#घोषणा AW2013_GCR 0x01
#घोषणा AW2013_GCR_ENABLE BIT(0)

/* LED channel enable रेजिस्टर */
#घोषणा AW2013_LCTR 0x30
#घोषणा AW2013_LCTR_LE(x) BIT((x))

/* LED channel control रेजिस्टरs */
#घोषणा AW2013_LCFG(x) (0x31 + (x))
#घोषणा AW2013_LCFG_IMAX_MASK (BIT(0) | BIT(1)) // Should be 0-3
#घोषणा AW2013_LCFG_MD BIT(4)
#घोषणा AW2013_LCFG_FI BIT(5)
#घोषणा AW2013_LCFG_FO BIT(6)

/* LED channel PWM रेजिस्टरs */
#घोषणा AW2013_REG_PWM(x) (0x34 + (x))

/* LED channel timing रेजिस्टरs */
#घोषणा AW2013_LEDT0(x) (0x37 + (x) * 3)
#घोषणा AW2013_LEDT0_T1(x) ((x) << 4) // Should be 0-7
#घोषणा AW2013_LEDT0_T2(x) (x) // Should be 0-5

#घोषणा AW2013_LEDT1(x) (0x38 + (x) * 3)
#घोषणा AW2013_LEDT1_T3(x) ((x) << 4) // Should be 0-7
#घोषणा AW2013_LEDT1_T4(x) (x) // Should be 0-7

#घोषणा AW2013_LEDT2(x) (0x39 + (x) * 3)
#घोषणा AW2013_LEDT2_T0(x) ((x) << 4) // Should be 0-8
#घोषणा AW2013_LEDT2_REPEAT(x) (x) // Should be 0-15

#घोषणा AW2013_REG_MAX 0x77

#घोषणा AW2013_TIME_STEP 130 /* ms */

काष्ठा aw2013;

काष्ठा aw2013_led अणु
	काष्ठा aw2013 *chip;
	काष्ठा led_classdev cdev;
	u32 num;
	अचिन्हित पूर्णांक imax;
पूर्ण;

काष्ठा aw2013 अणु
	काष्ठा mutex mutex; /* held when writing to रेजिस्टरs */
	काष्ठा regulator *vcc_regulator;
	काष्ठा i2c_client *client;
	काष्ठा aw2013_led leds[AW2013_MAX_LEDS];
	काष्ठा regmap *regmap;
	पूर्णांक num_leds;
	bool enabled;
पूर्ण;

अटल पूर्णांक aw2013_chip_init(काष्ठा aw2013 *chip)
अणु
	पूर्णांक i, ret;

	ret = regmap_ग_लिखो(chip->regmap, AW2013_GCR, AW2013_GCR_ENABLE);
	अगर (ret) अणु
		dev_err(&chip->client->dev, "Failed to enable the chip: %d\n",
			ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < chip->num_leds; i++) अणु
		ret = regmap_update_bits(chip->regmap,
					 AW2013_LCFG(chip->leds[i].num),
					 AW2013_LCFG_IMAX_MASK,
					 chip->leds[i].imax);
		अगर (ret) अणु
			dev_err(&chip->client->dev,
				"Failed to set maximum current for led %d: %d\n",
				chip->leds[i].num, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम aw2013_chip_disable(काष्ठा aw2013 *chip)
अणु
	पूर्णांक ret;

	अगर (!chip->enabled)
		वापस;

	regmap_ग_लिखो(chip->regmap, AW2013_GCR, 0);

	ret = regulator_disable(chip->vcc_regulator);
	अगर (ret) अणु
		dev_err(&chip->client->dev,
			"Failed to disable regulator: %d\n", ret);
		वापस;
	पूर्ण

	chip->enabled = false;
पूर्ण

अटल पूर्णांक aw2013_chip_enable(काष्ठा aw2013 *chip)
अणु
	पूर्णांक ret;

	अगर (chip->enabled)
		वापस 0;

	ret = regulator_enable(chip->vcc_regulator);
	अगर (ret) अणु
		dev_err(&chip->client->dev,
			"Failed to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण
	chip->enabled = true;

	ret = aw2013_chip_init(chip);
	अगर (ret)
		aw2013_chip_disable(chip);

	वापस ret;
पूर्ण

अटल bool aw2013_chip_in_use(काष्ठा aw2013 *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chip->num_leds; i++)
		अगर (chip->leds[i].cdev.brightness)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक aw2013_brightness_set(काष्ठा led_classdev *cdev,
				 क्रमागत led_brightness brightness)
अणु
	काष्ठा aw2013_led *led = container_of(cdev, काष्ठा aw2013_led, cdev);
	पूर्णांक ret, num;

	mutex_lock(&led->chip->mutex);

	अगर (aw2013_chip_in_use(led->chip)) अणु
		ret = aw2013_chip_enable(led->chip);
		अगर (ret)
			जाओ error;
	पूर्ण

	num = led->num;

	ret = regmap_ग_लिखो(led->chip->regmap, AW2013_REG_PWM(num), brightness);
	अगर (ret)
		जाओ error;

	अगर (brightness) अणु
		ret = regmap_update_bits(led->chip->regmap, AW2013_LCTR,
					 AW2013_LCTR_LE(num), 0xFF);
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(led->chip->regmap, AW2013_LCTR,
					 AW2013_LCTR_LE(num), 0);
		अगर (ret)
			जाओ error;
		ret = regmap_update_bits(led->chip->regmap, AW2013_LCFG(num),
					 AW2013_LCFG_MD, 0);
	पूर्ण
	अगर (ret)
		जाओ error;

	अगर (!aw2013_chip_in_use(led->chip))
		aw2013_chip_disable(led->chip);

error:
	mutex_unlock(&led->chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक aw2013_blink_set(काष्ठा led_classdev *cdev,
			    अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा aw2013_led *led = container_of(cdev, काष्ठा aw2013_led, cdev);
	पूर्णांक ret, num = led->num;
	अचिन्हित दीर्घ off = 0, on = 0;

	/* If no blink specअगरied, शेष to 1 Hz. */
	अगर (!*delay_off && !*delay_on) अणु
		*delay_off = 500;
		*delay_on = 500;
	पूर्ण

	अगर (!led->cdev.brightness) अणु
		led->cdev.brightness = LED_FULL;
		ret = aw2013_brightness_set(&led->cdev, led->cdev.brightness);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Never on - just set to off */
	अगर (!*delay_on) अणु
		led->cdev.brightness = LED_OFF;
		वापस aw2013_brightness_set(&led->cdev, LED_OFF);
	पूर्ण

	mutex_lock(&led->chip->mutex);

	/* Never off - brightness is alपढ़ोy set, disable blinking */
	अगर (!*delay_off) अणु
		ret = regmap_update_bits(led->chip->regmap, AW2013_LCFG(num),
					 AW2013_LCFG_MD, 0);
		जाओ out;
	पूर्ण

	/* Convert पूर्णांकo values the HW will understand. */
	off = min(5, ilog2((*delay_off - 1) / AW2013_TIME_STEP) + 1);
	on = min(7, ilog2((*delay_on - 1) / AW2013_TIME_STEP) + 1);

	*delay_off = BIT(off) * AW2013_TIME_STEP;
	*delay_on = BIT(on) * AW2013_TIME_STEP;

	/* Set timings */
	ret = regmap_ग_लिखो(led->chip->regmap,
			   AW2013_LEDT0(num), AW2013_LEDT0_T2(on));
	अगर (ret)
		जाओ out;
	ret = regmap_ग_लिखो(led->chip->regmap,
			   AW2013_LEDT1(num), AW2013_LEDT1_T4(off));
	अगर (ret)
		जाओ out;

	/* Finally, enable the LED */
	ret = regmap_update_bits(led->chip->regmap, AW2013_LCFG(num),
				 AW2013_LCFG_MD, 0xFF);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(led->chip->regmap, AW2013_LCTR,
				 AW2013_LCTR_LE(num), 0xFF);

out:
	mutex_unlock(&led->chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक aw2013_probe_dt(काष्ठा aw2013 *chip)
अणु
	काष्ठा device_node *np = dev_of_node(&chip->client->dev), *child;
	पूर्णांक count, ret = 0, i = 0;
	काष्ठा aw2013_led *led;

	count = of_get_available_child_count(np);
	अगर (!count || count > AW2013_MAX_LEDS)
		वापस -EINVAL;

	regmap_ग_लिखो(chip->regmap, AW2013_RSTR, AW2013_RSTR_RESET);

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;
		u32 source;
		u32 imax;

		ret = of_property_पढ़ो_u32(child, "reg", &source);
		अगर (ret != 0 || source >= AW2013_MAX_LEDS) अणु
			dev_err(&chip->client->dev,
				"Couldn't read LED address: %d\n", ret);
			count--;
			जारी;
		पूर्ण

		led = &chip->leds[i];
		led->num = source;
		led->chip = chip;
		init_data.fwnode = of_fwnode_handle(child);

		अगर (!of_property_पढ़ो_u32(child, "led-max-microamp", &imax)) अणु
			led->imax = min_t(u32, imax / 5000, 3);
		पूर्ण अन्यथा अणु
			led->imax = 1; // 5mA
			dev_info(&chip->client->dev,
				 "DT property led-max-microamp is missing\n");
		पूर्ण

		led->cdev.brightness_set_blocking = aw2013_brightness_set;
		led->cdev.blink_set = aw2013_blink_set;

		ret = devm_led_classdev_रेजिस्टर_ext(&chip->client->dev,
						     &led->cdev, &init_data);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		i++;
	पूर्ण

	अगर (!count)
		वापस -EINVAL;

	chip->num_leds = i;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config aw2013_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = AW2013_REG_MAX,
पूर्ण;

अटल पूर्णांक aw2013_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा aw2013 *chip;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chipid;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	mutex_init(&chip->mutex);
	mutex_lock(&chip->mutex);

	chip->client = client;
	i2c_set_clientdata(client, chip);

	chip->regmap = devm_regmap_init_i2c(client, &aw2013_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		जाओ error;
	पूर्ण

	chip->vcc_regulator = devm_regulator_get(&client->dev, "vcc");
	ret = PTR_ERR_OR_ZERO(chip->vcc_regulator);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to request regulator: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = regulator_enable(chip->vcc_regulator);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to enable regulator: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, AW2013_RSTR, &chipid);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to read chip ID: %d\n",
			ret);
		जाओ error_reg;
	पूर्ण

	अगर (chipid != AW2013_RSTR_CHIP_ID) अणु
		dev_err(&client->dev, "Chip reported wrong ID: %x\n",
			chipid);
		ret = -ENODEV;
		जाओ error_reg;
	पूर्ण

	ret = aw2013_probe_dt(chip);
	अगर (ret < 0)
		जाओ error_reg;

	ret = regulator_disable(chip->vcc_regulator);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to disable regulator: %d\n", ret);
		जाओ error;
	पूर्ण

	mutex_unlock(&chip->mutex);

	वापस 0;

error_reg:
	regulator_disable(chip->vcc_regulator);

error:
	mutex_destroy(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक aw2013_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा aw2013 *chip = i2c_get_clientdata(client);

	aw2013_chip_disable(chip);

	mutex_destroy(&chip->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aw2013_match_table[] = अणु
	अणु .compatible = "awinic,aw2013", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, aw2013_match_table);

अटल काष्ठा i2c_driver aw2013_driver = अणु
	.driver = अणु
		.name = "leds-aw2013",
		.of_match_table = of_match_ptr(aw2013_match_table),
	पूर्ण,
	.probe_new = aw2013_probe,
	.हटाओ = aw2013_हटाओ,
पूर्ण;

module_i2c_driver(aw2013_driver);

MODULE_AUTHOR("Nikita Travkin <nikitos.tr@gmail.com>");
MODULE_DESCRIPTION("AW2013 LED driver");
MODULE_LICENSE("GPL v2");
