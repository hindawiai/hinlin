<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED driver : leds-ktd2692.c
 *
 * Copyright (C) 2015 Samsung Electronics
 * Ingi Kim <ingi2.kim@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

/* Value related the movie mode */
#घोषणा KTD2692_MOVIE_MODE_CURRENT_LEVELS	16
#घोषणा KTD2692_MM_TO_FL_RATIO(x)		((x) / 3)
#घोषणा KTD2692_MM_MIN_CURR_THRESHOLD_SCALE	8

/* Value related the flash mode */
#घोषणा KTD2692_FLASH_MODE_TIMEOUT_LEVELS	8
#घोषणा KTD2692_FLASH_MODE_TIMEOUT_DISABLE	0
#घोषणा KTD2692_FLASH_MODE_CURR_PERCENT(x)	(((x) * 16) / 100)

/* Macro क्रम getting offset of flash समयout */
#घोषणा GET_TIMEOUT_OFFSET(समयout, step)	((समयout) / (step))

/* Base रेजिस्टर address */
#घोषणा KTD2692_REG_LVP_BASE			0x00
#घोषणा KTD2692_REG_FLASH_TIMEOUT_BASE		0x20
#घोषणा KTD2692_REG_MM_MIN_CURR_THRESHOLD_BASE	0x40
#घोषणा KTD2692_REG_MOVIE_CURRENT_BASE		0x60
#घोषणा KTD2692_REG_FLASH_CURRENT_BASE		0x80
#घोषणा KTD2692_REG_MODE_BASE			0xA0

/* Set bit coding समय क्रम expresswire पूर्णांकerface */
#घोषणा KTD2692_TIME_RESET_US			700
#घोषणा KTD2692_TIME_DATA_START_TIME_US		10
#घोषणा KTD2692_TIME_HIGH_END_OF_DATA_US	350
#घोषणा KTD2692_TIME_LOW_END_OF_DATA_US		10
#घोषणा KTD2692_TIME_SHORT_BITSET_US		4
#घोषणा KTD2692_TIME_LONG_BITSET_US		12

/* KTD2692 शेष length of name */
#घोषणा KTD2692_NAME_LENGTH			20

क्रमागत ktd2692_bitset अणु
	KTD2692_LOW = 0,
	KTD2692_HIGH,
पूर्ण;

/* Movie / Flash Mode Control */
क्रमागत ktd2692_led_mode अणु
	KTD2692_MODE_DISABLE = 0,	/* शेष */
	KTD2692_MODE_MOVIE,
	KTD2692_MODE_FLASH,
पूर्ण;

काष्ठा ktd2692_led_config_data अणु
	/* maximum LED current in movie mode */
	u32 movie_max_microamp;
	/* maximum LED current in flash mode */
	u32 flash_max_microamp;
	/* maximum flash समयout */
	u32 flash_max_समयout;
	/* max LED brightness level */
	क्रमागत led_brightness max_brightness;
पूर्ण;

काष्ठा ktd2692_context अणु
	/* Related LED Flash class device */
	काष्ठा led_classdev_flash fled_cdev;

	/* secures access to the device */
	काष्ठा mutex lock;
	काष्ठा regulator *regulator;

	काष्ठा gpio_desc *aux_gpio;
	काष्ठा gpio_desc *ctrl_gpio;

	क्रमागत ktd2692_led_mode mode;
	क्रमागत led_brightness torch_brightness;
पूर्ण;

अटल काष्ठा ktd2692_context *fled_cdev_to_led(
				काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस container_of(fled_cdev, काष्ठा ktd2692_context, fled_cdev);
पूर्ण

अटल व्योम ktd2692_expresswire_start(काष्ठा ktd2692_context *led)
अणु
	gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
	udelay(KTD2692_TIME_DATA_START_TIME_US);
पूर्ण

अटल व्योम ktd2692_expresswire_reset(काष्ठा ktd2692_context *led)
अणु
	gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
	udelay(KTD2692_TIME_RESET_US);
पूर्ण

अटल व्योम ktd2692_expresswire_end(काष्ठा ktd2692_context *led)
अणु
	gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
	udelay(KTD2692_TIME_LOW_END_OF_DATA_US);
	gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
	udelay(KTD2692_TIME_HIGH_END_OF_DATA_US);
पूर्ण

अटल व्योम ktd2692_expresswire_set_bit(काष्ठा ktd2692_context *led, bool bit)
अणु
	/*
	 * The Low Bit(0) and High Bit(1) is based on a समय detection
	 * algorithm between समय low and समय high
	 * Time_(L_LB) : Low समय of the Low Bit(0)
	 * Time_(H_LB) : High समय of the LOW Bit(0)
	 * Time_(L_HB) : Low समय of the High Bit(1)
	 * Time_(H_HB) : High समय of the High Bit(1)
	 *
	 * It can be simplअगरied to:
	 * Low Bit(0) : 2 * Time_(H_LB) < Time_(L_LB)
	 * High Bit(1) : 2 * Time_(L_HB) < Time_(H_HB)
	 * HIGH  ___           ____    _..     _________    ___
	 *          |_________|    |_..  |____|         |__|
	 * LOW        <L_LB>  <H_LB>     <L_HB>  <H_HB>
	 *          [  Low Bit (0) ]     [  High Bit(1) ]
	 */
	अगर (bit) अणु
		gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
		udelay(KTD2692_TIME_SHORT_BITSET_US);
		gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
		udelay(KTD2692_TIME_LONG_BITSET_US);
	पूर्ण अन्यथा अणु
		gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
		udelay(KTD2692_TIME_LONG_BITSET_US);
		gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
		udelay(KTD2692_TIME_SHORT_BITSET_US);
	पूर्ण
पूर्ण

अटल व्योम ktd2692_expresswire_ग_लिखो(काष्ठा ktd2692_context *led, u8 value)
अणु
	पूर्णांक i;

	ktd2692_expresswire_start(led);
	क्रम (i = 7; i >= 0; i--)
		ktd2692_expresswire_set_bit(led, value & BIT(i));
	ktd2692_expresswire_end(led);
पूर्ण

अटल पूर्णांक ktd2692_led_brightness_set(काष्ठा led_classdev *led_cdev,
				       क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	काष्ठा ktd2692_context *led = fled_cdev_to_led(fled_cdev);

	mutex_lock(&led->lock);

	अगर (brightness == LED_OFF) अणु
		led->mode = KTD2692_MODE_DISABLE;
		gpiod_direction_output(led->aux_gpio, KTD2692_LOW);
	पूर्ण अन्यथा अणु
		ktd2692_expresswire_ग_लिखो(led, brightness |
					KTD2692_REG_MOVIE_CURRENT_BASE);
		led->mode = KTD2692_MODE_MOVIE;
	पूर्ण

	ktd2692_expresswire_ग_लिखो(led, led->mode | KTD2692_REG_MODE_BASE);
	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ktd2692_led_flash_strobe_set(काष्ठा led_classdev_flash *fled_cdev,
					bool state)
अणु
	काष्ठा ktd2692_context *led = fled_cdev_to_led(fled_cdev);
	काष्ठा led_flash_setting *समयout = &fled_cdev->समयout;
	u32 flash_पंचांग_reg;

	mutex_lock(&led->lock);

	अगर (state) अणु
		flash_पंचांग_reg = GET_TIMEOUT_OFFSET(समयout->val, समयout->step);
		ktd2692_expresswire_ग_लिखो(led, flash_पंचांग_reg
				| KTD2692_REG_FLASH_TIMEOUT_BASE);

		led->mode = KTD2692_MODE_FLASH;
		gpiod_direction_output(led->aux_gpio, KTD2692_HIGH);
	पूर्ण अन्यथा अणु
		led->mode = KTD2692_MODE_DISABLE;
		gpiod_direction_output(led->aux_gpio, KTD2692_LOW);
	पूर्ण

	ktd2692_expresswire_ग_लिखो(led, led->mode | KTD2692_REG_MODE_BASE);

	fled_cdev->led_cdev.brightness = LED_OFF;
	led->mode = KTD2692_MODE_DISABLE;

	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ktd2692_led_flash_समयout_set(काष्ठा led_classdev_flash *fled_cdev,
					 u32 समयout)
अणु
	वापस 0;
पूर्ण

अटल व्योम ktd2692_init_movie_current_max(काष्ठा ktd2692_led_config_data *cfg)
अणु
	u32 offset, step;
	u32 movie_current_microamp;

	offset = KTD2692_MOVIE_MODE_CURRENT_LEVELS;
	step = KTD2692_MM_TO_FL_RATIO(cfg->flash_max_microamp)
		/ KTD2692_MOVIE_MODE_CURRENT_LEVELS;

	करो अणु
		movie_current_microamp = step * offset;
		offset--;
	पूर्ण जबतक ((movie_current_microamp > cfg->movie_max_microamp) &&
		(offset > 0));

	cfg->max_brightness = offset;
पूर्ण

अटल व्योम ktd2692_init_flash_समयout(काष्ठा led_classdev_flash *fled_cdev,
				       काष्ठा ktd2692_led_config_data *cfg)
अणु
	काष्ठा led_flash_setting *setting;

	setting = &fled_cdev->समयout;
	setting->min = KTD2692_FLASH_MODE_TIMEOUT_DISABLE;
	setting->max = cfg->flash_max_समयout;
	setting->step = cfg->flash_max_समयout
			/ (KTD2692_FLASH_MODE_TIMEOUT_LEVELS - 1);
	setting->val = cfg->flash_max_समयout;
पूर्ण

अटल व्योम ktd2692_setup(काष्ठा ktd2692_context *led)
अणु
	led->mode = KTD2692_MODE_DISABLE;
	ktd2692_expresswire_reset(led);
	gpiod_direction_output(led->aux_gpio, KTD2692_LOW);

	ktd2692_expresswire_ग_लिखो(led, (KTD2692_MM_MIN_CURR_THRESHOLD_SCALE - 1)
				 | KTD2692_REG_MM_MIN_CURR_THRESHOLD_BASE);
	ktd2692_expresswire_ग_लिखो(led, KTD2692_FLASH_MODE_CURR_PERCENT(45)
				 | KTD2692_REG_FLASH_CURRENT_BASE);
पूर्ण

अटल पूर्णांक ktd2692_parse_dt(काष्ठा ktd2692_context *led, काष्ठा device *dev,
			    काष्ठा ktd2692_led_config_data *cfg)
अणु
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *child_node;
	पूर्णांक ret;

	अगर (!dev_of_node(dev))
		वापस -ENXIO;

	led->ctrl_gpio = devm_gpiod_get(dev, "ctrl", GPIOD_ASIS);
	ret = PTR_ERR_OR_ZERO(led->ctrl_gpio);
	अगर (ret) अणु
		dev_err(dev, "cannot get ctrl-gpios %d\n", ret);
		वापस ret;
	पूर्ण

	led->aux_gpio = devm_gpiod_get(dev, "aux", GPIOD_ASIS);
	ret = PTR_ERR_OR_ZERO(led->aux_gpio);
	अगर (ret) अणु
		dev_err(dev, "cannot get aux-gpios %d\n", ret);
		वापस ret;
	पूर्ण

	led->regulator = devm_regulator_get(dev, "vin");
	अगर (IS_ERR(led->regulator))
		led->regulator = शून्य;

	अगर (led->regulator) अणु
		ret = regulator_enable(led->regulator);
		अगर (ret)
			dev_err(dev, "Failed to enable supply: %d\n", ret);
	पूर्ण

	child_node = of_get_next_available_child(np, शून्य);
	अगर (!child_node) अणु
		dev_err(dev, "No DT child node found for connected LED.\n");
		वापस -EINVAL;
	पूर्ण

	led->fled_cdev.led_cdev.name =
		of_get_property(child_node, "label", शून्य) ? : child_node->name;

	ret = of_property_पढ़ो_u32(child_node, "led-max-microamp",
				   &cfg->movie_max_microamp);
	अगर (ret) अणु
		dev_err(dev, "failed to parse led-max-microamp\n");
		जाओ err_parse_dt;
	पूर्ण

	ret = of_property_पढ़ो_u32(child_node, "flash-max-microamp",
				   &cfg->flash_max_microamp);
	अगर (ret) अणु
		dev_err(dev, "failed to parse flash-max-microamp\n");
		जाओ err_parse_dt;
	पूर्ण

	ret = of_property_पढ़ो_u32(child_node, "flash-max-timeout-us",
				   &cfg->flash_max_समयout);
	अगर (ret) अणु
		dev_err(dev, "failed to parse flash-max-timeout-us\n");
		जाओ err_parse_dt;
	पूर्ण

err_parse_dt:
	of_node_put(child_node);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops flash_ops = अणु
	.strobe_set = ktd2692_led_flash_strobe_set,
	.समयout_set = ktd2692_led_flash_समयout_set,
पूर्ण;

अटल पूर्णांक ktd2692_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ktd2692_context *led;
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_classdev_flash *fled_cdev;
	काष्ठा ktd2692_led_config_data led_cfg;
	पूर्णांक ret;

	led = devm_kzalloc(&pdev->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	fled_cdev = &led->fled_cdev;
	led_cdev = &fled_cdev->led_cdev;

	ret = ktd2692_parse_dt(led, &pdev->dev, &led_cfg);
	अगर (ret)
		वापस ret;

	ktd2692_init_flash_समयout(fled_cdev, &led_cfg);
	ktd2692_init_movie_current_max(&led_cfg);

	fled_cdev->ops = &flash_ops;

	led_cdev->max_brightness = led_cfg.max_brightness;
	led_cdev->brightness_set_blocking = ktd2692_led_brightness_set;
	led_cdev->flags |= LED_CORE_SUSPENDRESUME | LED_DEV_CAP_FLASH;

	mutex_init(&led->lock);

	platक्रमm_set_drvdata(pdev, led);

	ret = led_classdev_flash_रेजिस्टर(&pdev->dev, fled_cdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't register LED %s\n", led_cdev->name);
		mutex_destroy(&led->lock);
		वापस ret;
	पूर्ण

	ktd2692_setup(led);

	वापस 0;
पूर्ण

अटल पूर्णांक ktd2692_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ktd2692_context *led = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	led_classdev_flash_unरेजिस्टर(&led->fled_cdev);

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(&pdev->dev,
				"Failed to disable supply: %d\n", ret);
	पूर्ण

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ktd2692_match[] = अणु
	अणु .compatible = "kinetic,ktd2692", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ktd2692_match);

अटल काष्ठा platक्रमm_driver ktd2692_driver = अणु
	.driver = अणु
		.name  = "ktd2692",
		.of_match_table = ktd2692_match,
	पूर्ण,
	.probe  = ktd2692_probe,
	.हटाओ = ktd2692_हटाओ,
पूर्ण;

module_platक्रमm_driver(ktd2692_driver);

MODULE_AUTHOR("Ingi Kim <ingi2.kim@samsung.com>");
MODULE_DESCRIPTION("Kinetic KTD2692 LED driver");
MODULE_LICENSE("GPL v2");
