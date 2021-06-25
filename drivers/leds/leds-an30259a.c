<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Driver क्रम Panasonic AN30259A 3-channel LED driver
//
// Copyright (c) 2018 Simon Shields <simon@lineageos.org>
//
// Datasheet:
// https://www.alliedelec.com/m/d/a9d2b3ee87c2d1a535a41dd747b1c247.pdf

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#घोषणा AN30259A_MAX_LEDS 3

#घोषणा AN30259A_REG_SRESET 0x00
#घोषणा AN30259A_LED_SRESET BIT(0)

/* LED घातer रेजिस्टरs */
#घोषणा AN30259A_REG_LED_ON 0x01
#घोषणा AN30259A_LED_EN(x) BIT((x) - 1)
#घोषणा AN30259A_LED_SLOPE(x) BIT(((x) - 1) + 4)

#घोषणा AN30259A_REG_LEDCC(x) (0x03 + ((x) - 1))

/* slope control रेजिस्टरs */
#घोषणा AN30259A_REG_SLOPE(x) (0x06 + ((x) - 1))
#घोषणा AN30259A_LED_SLOPETIME1(x) (x)
#घोषणा AN30259A_LED_SLOPETIME2(x) ((x) << 4)

#घोषणा AN30259A_REG_LEDCNT1(x) (0x09 + (4 * ((x) - 1)))
#घोषणा AN30259A_LED_DUTYMAX(x) ((x) << 4)
#घोषणा AN30259A_LED_DUTYMID(x) (x)

#घोषणा AN30259A_REG_LEDCNT2(x) (0x0A + (4 * ((x) - 1)))
#घोषणा AN30259A_LED_DELAY(x) ((x) << 4)
#घोषणा AN30259A_LED_DUTYMIN(x) (x)

/* detention समय control (length of each slope step) */
#घोषणा AN30259A_REG_LEDCNT3(x) (0x0B + (4 * ((x) - 1)))
#घोषणा AN30259A_LED_DT1(x) (x)
#घोषणा AN30259A_LED_DT2(x) ((x) << 4)

#घोषणा AN30259A_REG_LEDCNT4(x) (0x0C + (4 * ((x) - 1)))
#घोषणा AN30259A_LED_DT3(x) (x)
#घोषणा AN30259A_LED_DT4(x) ((x) << 4)

#घोषणा AN30259A_REG_MAX 0x14

#घोषणा AN30259A_BLINK_MAX_TIME 7500 /* ms */
#घोषणा AN30259A_SLOPE_RESOLUTION 500 /* ms */

#घोषणा AN30259A_NAME "an30259a"

#घोषणा STATE_OFF 0
#घोषणा STATE_KEEP 1
#घोषणा STATE_ON 2

काष्ठा an30259a;

काष्ठा an30259a_led अणु
	काष्ठा an30259a *chip;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा led_classdev cdev;
	u32 num;
	u32 शेष_state;
	bool sloping;
पूर्ण;

काष्ठा an30259a अणु
	काष्ठा mutex mutex; /* held when writing to रेजिस्टरs */
	काष्ठा i2c_client *client;
	काष्ठा an30259a_led leds[AN30259A_MAX_LEDS];
	काष्ठा regmap *regmap;
	पूर्णांक num_leds;
पूर्ण;

अटल पूर्णांक an30259a_brightness_set(काष्ठा led_classdev *cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा an30259a_led *led;
	पूर्णांक ret;
	अचिन्हित पूर्णांक led_on;

	led = container_of(cdev, काष्ठा an30259a_led, cdev);
	mutex_lock(&led->chip->mutex);

	ret = regmap_पढ़ो(led->chip->regmap, AN30259A_REG_LED_ON, &led_on);
	अगर (ret)
		जाओ error;

	चयन (brightness) अणु
	हाल LED_OFF:
		led_on &= ~AN30259A_LED_EN(led->num);
		led_on &= ~AN30259A_LED_SLOPE(led->num);
		led->sloping = false;
		अवरोध;
	शेष:
		led_on |= AN30259A_LED_EN(led->num);
		अगर (led->sloping)
			led_on |= AN30259A_LED_SLOPE(led->num);
		ret = regmap_ग_लिखो(led->chip->regmap,
				   AN30259A_REG_LEDCNT1(led->num),
				   AN30259A_LED_DUTYMAX(0xf) |
				   AN30259A_LED_DUTYMID(0xf));
		अगर (ret)
			जाओ error;
		अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LED_ON, led_on);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LEDCC(led->num),
			   brightness);

error:
	mutex_unlock(&led->chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक an30259a_blink_set(काष्ठा led_classdev *cdev,
			      अचिन्हित दीर्घ *delay_off, अचिन्हित दीर्घ *delay_on)
अणु
	काष्ठा an30259a_led *led;
	पूर्णांक ret, num;
	अचिन्हित पूर्णांक led_on;
	अचिन्हित दीर्घ off = *delay_off, on = *delay_on;

	led = container_of(cdev, काष्ठा an30259a_led, cdev);

	mutex_lock(&led->chip->mutex);
	num = led->num;

	/* slope समय can only be a multiple of 500ms. */
	अगर (off % AN30259A_SLOPE_RESOLUTION || on % AN30259A_SLOPE_RESOLUTION) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* up to a maximum of 7500ms. */
	अगर (off > AN30259A_BLINK_MAX_TIME || on > AN30259A_BLINK_MAX_TIME) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* अगर no blink specअगरied, शेष to 1 Hz. */
	अगर (!off && !on) अणु
		*delay_off = off = 500;
		*delay_on = on = 500;
	पूर्ण

	/* convert पूर्णांकo values the HW will understand. */
	off /= AN30259A_SLOPE_RESOLUTION;
	on /= AN30259A_SLOPE_RESOLUTION;

	/* duty min should be zero (=off), delay should be zero. */
	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LEDCNT2(num),
			   AN30259A_LED_DELAY(0) | AN30259A_LED_DUTYMIN(0));
	अगर (ret)
		जाओ error;

	/* reset detention समय (no "breathing" effect). */
	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LEDCNT3(num),
			   AN30259A_LED_DT1(0) | AN30259A_LED_DT2(0));
	अगर (ret)
		जाओ error;
	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LEDCNT4(num),
			   AN30259A_LED_DT3(0) | AN30259A_LED_DT4(0));
	अगर (ret)
		जाओ error;

	/* slope समय controls on/off cycle length. */
	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_SLOPE(num),
			   AN30259A_LED_SLOPETIME1(off) |
			   AN30259A_LED_SLOPETIME2(on));
	अगर (ret)
		जाओ error;

	/* Finally, enable slope mode. */
	ret = regmap_पढ़ो(led->chip->regmap, AN30259A_REG_LED_ON, &led_on);
	अगर (ret)
		जाओ error;

	led_on |= AN30259A_LED_SLOPE(num) | AN30259A_LED_EN(led->num);

	ret = regmap_ग_लिखो(led->chip->regmap, AN30259A_REG_LED_ON, led_on);

	अगर (!ret)
		led->sloping = true;
error:
	mutex_unlock(&led->chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक an30259a_dt_init(काष्ठा i2c_client *client,
			    काष्ठा an30259a *chip)
अणु
	काष्ठा device_node *np = dev_of_node(&client->dev), *child;
	पूर्णांक count, ret;
	पूर्णांक i = 0;
	स्थिर अक्षर *str;
	काष्ठा an30259a_led *led;

	count = of_get_available_child_count(np);
	अगर (!count || count > AN30259A_MAX_LEDS)
		वापस -EINVAL;

	क्रम_each_available_child_of_node(np, child) अणु
		u32 source;

		ret = of_property_पढ़ो_u32(child, "reg", &source);
		अगर (ret != 0 || !source || source > AN30259A_MAX_LEDS) अणु
			dev_err(&client->dev, "Couldn't read LED address: %d\n",
				ret);
			count--;
			जारी;
		पूर्ण

		led = &chip->leds[i];

		led->num = source;
		led->chip = chip;
		led->fwnode = of_fwnode_handle(child);

		अगर (!of_property_पढ़ो_string(child, "default-state", &str)) अणु
			अगर (!म_भेद(str, "on"))
				led->शेष_state = STATE_ON;
			अन्यथा अगर (!म_भेद(str, "keep"))
				led->शेष_state = STATE_KEEP;
			अन्यथा
				led->शेष_state = STATE_OFF;
		पूर्ण

		i++;
	पूर्ण

	अगर (!count)
		वापस -EINVAL;

	chip->num_leds = i;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config an30259a_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = AN30259A_REG_MAX,
पूर्ण;

अटल व्योम an30259a_init_शेष_state(काष्ठा an30259a_led *led)
अणु
	काष्ठा an30259a *chip = led->chip;
	पूर्णांक led_on, err;

	चयन (led->शेष_state) अणु
	हाल STATE_ON:
		led->cdev.brightness = LED_FULL;
		अवरोध;
	हाल STATE_KEEP:
		err = regmap_पढ़ो(chip->regmap, AN30259A_REG_LED_ON, &led_on);
		अगर (err)
			अवरोध;

		अगर (!(led_on & AN30259A_LED_EN(led->num))) अणु
			led->cdev.brightness = LED_OFF;
			अवरोध;
		पूर्ण
		regmap_पढ़ो(chip->regmap, AN30259A_REG_LEDCC(led->num),
			    &led->cdev.brightness);
		अवरोध;
	शेष:
		led->cdev.brightness = LED_OFF;
	पूर्ण

	an30259a_brightness_set(&led->cdev, led->cdev.brightness);
पूर्ण

अटल पूर्णांक an30259a_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा an30259a *chip;
	पूर्णांक i, err;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	err = an30259a_dt_init(client, chip);
	अगर (err < 0)
		वापस err;

	mutex_init(&chip->mutex);
	chip->client = client;
	i2c_set_clientdata(client, chip);

	chip->regmap = devm_regmap_init_i2c(client, &an30259a_regmap_config);

	अगर (IS_ERR(chip->regmap)) अणु
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			err);
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < chip->num_leds; i++) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;

		an30259a_init_शेष_state(&chip->leds[i]);
		chip->leds[i].cdev.brightness_set_blocking =
			an30259a_brightness_set;
		chip->leds[i].cdev.blink_set = an30259a_blink_set;

		init_data.fwnode = chip->leds[i].fwnode;
		init_data.devicename = AN30259A_NAME;
		init_data.शेष_label = ":";

		err = devm_led_classdev_रेजिस्टर_ext(&client->dev,
						 &chip->leds[i].cdev,
						 &init_data);
		अगर (err < 0)
			जाओ निकास;
	पूर्ण
	वापस 0;

निकास:
	mutex_destroy(&chip->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक an30259a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा an30259a *chip = i2c_get_clientdata(client);

	mutex_destroy(&chip->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id an30259a_match_table[] = अणु
	अणु .compatible = "panasonic,an30259a", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, an30259a_match_table);

अटल स्थिर काष्ठा i2c_device_id an30259a_id[] = अणु
	अणु "an30259a", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, an30259a_id);

अटल काष्ठा i2c_driver an30259a_driver = अणु
	.driver = अणु
		.name = "leds-an30259a",
		.of_match_table = of_match_ptr(an30259a_match_table),
	पूर्ण,
	.probe_new = an30259a_probe,
	.हटाओ = an30259a_हटाओ,
	.id_table = an30259a_id,
पूर्ण;

module_i2c_driver(an30259a_driver);

MODULE_AUTHOR("Simon Shields <simon@lineageos.org>");
MODULE_DESCRIPTION("AN30259A LED driver");
MODULE_LICENSE("GPL v2");
