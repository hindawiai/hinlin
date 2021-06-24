<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा A500_EC_LED_DELAY_USEC	(100 * 1000)

क्रमागत अणु
	REG_RESET_LEDS = 0x40,
	REG_POWER_LED_ON = 0x42,
	REG_CHARGE_LED_ON = 0x43,
	REG_ANDROID_LEDS_OFF = 0x5a,
पूर्ण;

काष्ठा a500_led अणु
	काष्ठा led_classdev cdev;
	स्थिर काष्ठा reg_sequence *enable_seq;
	काष्ठा a500_led *other;
	काष्ठा regmap *rmap;
पूर्ण;

अटल स्थिर काष्ठा reg_sequence a500_ec_leds_reset_seq[] = अणु
	REG_SEQ(REG_RESET_LEDS, 0x0, A500_EC_LED_DELAY_USEC),
	REG_SEQ(REG_ANDROID_LEDS_OFF, 0x0, A500_EC_LED_DELAY_USEC),
पूर्ण;

अटल स्थिर काष्ठा reg_sequence a500_ec_white_led_enable_seq[] = अणु
	REG_SEQ(REG_POWER_LED_ON, 0x0, A500_EC_LED_DELAY_USEC),
पूर्ण;

अटल स्थिर काष्ठा reg_sequence a500_ec_orange_led_enable_seq[] = अणु
	REG_SEQ(REG_CHARGE_LED_ON, 0x0, A500_EC_LED_DELAY_USEC),
पूर्ण;

अटल पूर्णांक a500_ec_led_brightness_set(काष्ठा led_classdev *led_cdev,
				      क्रमागत led_brightness value)
अणु
	काष्ठा a500_led *led = container_of(led_cdev, काष्ठा a500_led, cdev);
	काष्ठा reg_sequence control_seq[2];
	अचिन्हित पूर्णांक num_regs = 1;

	अगर (value) अणु
		control_seq[0] = led->enable_seq[0];
	पूर्ण अन्यथा अणु
		/*
		 * There is no separate controls which can disable LEDs
		 * inभागidually, there is only RESET_LEDS command that turns
		 * off both LEDs.
		 *
		 * RESET_LEDS turns off both LEDs, thus restore other LED अगर
		 * it's turned ON.
		 */
		अगर (led->other->cdev.brightness)
			num_regs = 2;

		control_seq[0] = a500_ec_leds_reset_seq[0];
		control_seq[1] = led->other->enable_seq[0];
	पूर्ण

	वापस regmap_multi_reg_ग_लिखो(led->rmap, control_seq, num_regs);
पूर्ण

अटल पूर्णांक a500_ec_leds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा a500_led *white_led, *orange_led;
	काष्ठा regmap *rmap;
	पूर्णांक err;

	rmap = dev_get_regmap(pdev->dev.parent, "KB930");
	अगर (!rmap)
		वापस -EINVAL;

	/* reset and turn off LEDs */
	regmap_multi_reg_ग_लिखो(rmap, a500_ec_leds_reset_seq, 2);

	white_led = devm_kzalloc(&pdev->dev, माप(*white_led), GFP_KERNEL);
	अगर (!white_led)
		वापस -ENOMEM;

	white_led->cdev.name = "power:white";
	white_led->cdev.brightness_set_blocking = a500_ec_led_brightness_set;
	white_led->cdev.flags = LED_CORE_SUSPENDRESUME;
	white_led->cdev.max_brightness = 1;
	white_led->enable_seq = a500_ec_white_led_enable_seq;
	white_led->rmap = rmap;

	orange_led = devm_kzalloc(&pdev->dev, माप(*orange_led), GFP_KERNEL);
	अगर (!orange_led)
		वापस -ENOMEM;

	orange_led->cdev.name = "power:orange";
	orange_led->cdev.brightness_set_blocking = a500_ec_led_brightness_set;
	orange_led->cdev.flags = LED_CORE_SUSPENDRESUME;
	orange_led->cdev.max_brightness = 1;
	orange_led->enable_seq = a500_ec_orange_led_enable_seq;
	orange_led->rmap = rmap;

	white_led->other = orange_led;
	orange_led->other = white_led;

	err = devm_led_classdev_रेजिस्टर(&pdev->dev, &white_led->cdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register white LED\n");
		वापस err;
	पूर्ण

	err = devm_led_classdev_रेजिस्टर(&pdev->dev, &orange_led->cdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register orange LED\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver a500_ec_leds_driver = अणु
	.driver = अणु
		.name = "acer-a500-iconia-leds",
	पूर्ण,
	.probe = a500_ec_leds_probe,
पूर्ण;
module_platक्रमm_driver(a500_ec_leds_driver);

MODULE_DESCRIPTION("LED driver for Acer Iconia Tab A500 Power Button");
MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_ALIAS("platform:acer-a500-iconia-leds");
MODULE_LICENSE("GPL");
