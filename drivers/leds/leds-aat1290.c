<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	LED Flash class driver क्रम the AAT1290
 *	1.5A Step-Up Current Regulator क्रम Flash LEDs
 *
 *	Copyright (C) 2015, Samsung Electronics Co., Ltd.
 *	Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-flash-led-class.h>

#घोषणा AAT1290_MOVIE_MODE_CURRENT_ADDR	17
#घोषणा AAT1290_MAX_MM_CURR_PERCENT_0	16
#घोषणा AAT1290_MAX_MM_CURR_PERCENT_100	1

#घोषणा AAT1290_FLASH_SAFETY_TIMER_ADDR	18

#घोषणा AAT1290_MOVIE_MODE_CONFIG_ADDR	19
#घोषणा AAT1290_MOVIE_MODE_OFF		1
#घोषणा AAT1290_MOVIE_MODE_ON		3

#घोषणा AAT1290_MM_CURRENT_RATIO_ADDR	20
#घोषणा AAT1290_MM_TO_FL_1_92		1

#घोषणा AAT1290_MM_TO_FL_RATIO		1000 / 1920
#घोषणा AAT1290_MAX_MM_CURRENT(fl_max)	(fl_max * AAT1290_MM_TO_FL_RATIO)

#घोषणा AAT1290_LATCH_TIME_MIN_US	500
#घोषणा AAT1290_LATCH_TIME_MAX_US	1000
#घोषणा AAT1290_EN_SET_TICK_TIME_US	1
#घोषणा AAT1290_FLEN_OFF_DELAY_TIME_US	10
#घोषणा AAT1290_FLASH_TM_NUM_LEVELS	16
#घोषणा AAT1290_MM_CURRENT_SCALE_SIZE	15

#घोषणा AAT1290_NAME			"aat1290"


काष्ठा aat1290_led_config_data अणु
	/* maximum LED current in movie mode */
	u32 max_mm_current;
	/* maximum LED current in flash mode */
	u32 max_flash_current;
	/* maximum flash समयout */
	u32 max_flash_पंचांग;
	/* बाह्यal strobe capability */
	bool has_बाह्यal_strobe;
	/* max LED brightness level */
	क्रमागत led_brightness max_brightness;
पूर्ण;

काष्ठा aat1290_led अणु
	/* platक्रमm device data */
	काष्ठा platक्रमm_device *pdev;
	/* secures access to the device */
	काष्ठा mutex lock;

	/* corresponding LED Flash class device */
	काष्ठा led_classdev_flash fled_cdev;
	/* V4L2 Flash device */
	काष्ठा v4l2_flash *v4l2_flash;

	/* FLEN pin */
	काष्ठा gpio_desc *gpio_fl_en;
	/* EN|SET pin  */
	काष्ठा gpio_desc *gpio_en_set;
	/* movie mode current scale */
	पूर्णांक *mm_current_scale;
	/* device mode */
	bool movie_mode;
	/* brightness cache */
	अचिन्हित पूर्णांक torch_brightness;
पूर्ण;

अटल काष्ठा aat1290_led *fled_cdev_to_led(
				काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस container_of(fled_cdev, काष्ठा aat1290_led, fled_cdev);
पूर्ण

अटल काष्ठा led_classdev_flash *led_cdev_to_fled_cdev(
				काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा led_classdev_flash, led_cdev);
पूर्ण

अटल व्योम aat1290_as2cwire_ग_लिखो(काष्ठा aat1290_led *led, पूर्णांक addr, पूर्णांक value)
अणु
	पूर्णांक i;

	gpiod_direction_output(led->gpio_fl_en, 0);
	gpiod_direction_output(led->gpio_en_set, 0);

	udelay(AAT1290_FLEN_OFF_DELAY_TIME_US);

	/* ग_लिखो address */
	क्रम (i = 0; i < addr; ++i) अणु
		udelay(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_direction_output(led->gpio_en_set, 0);
		udelay(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_direction_output(led->gpio_en_set, 1);
	पूर्ण

	usleep_range(AAT1290_LATCH_TIME_MIN_US, AAT1290_LATCH_TIME_MAX_US);

	/* ग_लिखो data */
	क्रम (i = 0; i < value; ++i) अणु
		udelay(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_direction_output(led->gpio_en_set, 0);
		udelay(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_direction_output(led->gpio_en_set, 1);
	पूर्ण

	usleep_range(AAT1290_LATCH_TIME_MIN_US, AAT1290_LATCH_TIME_MAX_US);
पूर्ण

अटल व्योम aat1290_set_flash_safety_समयr(काष्ठा aat1290_led *led,
					अचिन्हित पूर्णांक micro_sec)
अणु
	काष्ठा led_classdev_flash *fled_cdev = &led->fled_cdev;
	काष्ठा led_flash_setting *flash_पंचांग = &fled_cdev->समयout;
	पूर्णांक flash_पंचांग_reg = AAT1290_FLASH_TM_NUM_LEVELS -
				(micro_sec / flash_पंचांग->step) + 1;

	aat1290_as2cwire_ग_लिखो(led, AAT1290_FLASH_SAFETY_TIMER_ADDR,
							flash_पंचांग_reg);
पूर्ण

/* LED subप्रणाली callbacks */

अटल पूर्णांक aat1290_led_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled_cdev = led_cdev_to_fled_cdev(led_cdev);
	काष्ठा aat1290_led *led = fled_cdev_to_led(fled_cdev);

	mutex_lock(&led->lock);

	अगर (brightness == 0) अणु
		gpiod_direction_output(led->gpio_fl_en, 0);
		gpiod_direction_output(led->gpio_en_set, 0);
		led->movie_mode = false;
	पूर्ण अन्यथा अणु
		अगर (!led->movie_mode) अणु
			aat1290_as2cwire_ग_लिखो(led,
				AAT1290_MM_CURRENT_RATIO_ADDR,
				AAT1290_MM_TO_FL_1_92);
			led->movie_mode = true;
		पूर्ण

		aat1290_as2cwire_ग_लिखो(led, AAT1290_MOVIE_MODE_CURRENT_ADDR,
				AAT1290_MAX_MM_CURR_PERCENT_0 - brightness);
		aat1290_as2cwire_ग_लिखो(led, AAT1290_MOVIE_MODE_CONFIG_ADDR,
				AAT1290_MOVIE_MODE_ON);
	पूर्ण

	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक aat1290_led_flash_strobe_set(काष्ठा led_classdev_flash *fled_cdev,
					 bool state)

अणु
	काष्ठा aat1290_led *led = fled_cdev_to_led(fled_cdev);
	काष्ठा led_classdev *led_cdev = &fled_cdev->led_cdev;
	काष्ठा led_flash_setting *समयout = &fled_cdev->समयout;

	mutex_lock(&led->lock);

	अगर (state) अणु
		aat1290_set_flash_safety_समयr(led, समयout->val);
		gpiod_direction_output(led->gpio_fl_en, 1);
	पूर्ण अन्यथा अणु
		gpiod_direction_output(led->gpio_fl_en, 0);
		gpiod_direction_output(led->gpio_en_set, 0);
	पूर्ण

	/*
	 * To reenter movie mode after a flash event the part must be cycled
	 * off and back on to reset the movie mode and reprogrammed via the
	 * AS2Cwire. Thereक्रमe the brightness and movie_mode properties needs
	 * to be updated here to reflect the actual state.
	 */
	led_cdev->brightness = 0;
	led->movie_mode = false;

	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक aat1290_led_flash_समयout_set(काष्ठा led_classdev_flash *fled_cdev,
						u32 समयout)
अणु
	/*
	 * Don't करो anything - flash समयout is cached in the led-class-flash
	 * core and will be applied in the strobe_set op, as writing the
	 * safety समयr रेजिस्टर spuriously turns the torch mode on.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक aat1290_led_parse_dt(काष्ठा aat1290_led *led,
			काष्ठा aat1290_led_config_data *cfg,
			काष्ठा device_node **sub_node)
अणु
	काष्ठा device *dev = &led->pdev->dev;
	काष्ठा device_node *child_node;
#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
	काष्ठा pinctrl *pinctrl;
#पूर्ण_अगर
	पूर्णांक ret = 0;

	led->gpio_fl_en = devm_gpiod_get(dev, "flen", GPIOD_ASIS);
	अगर (IS_ERR(led->gpio_fl_en)) अणु
		ret = PTR_ERR(led->gpio_fl_en);
		dev_err(dev, "Unable to claim gpio \"flen\".\n");
		वापस ret;
	पूर्ण

	led->gpio_en_set = devm_gpiod_get(dev, "enset", GPIOD_ASIS);
	अगर (IS_ERR(led->gpio_en_set)) अणु
		ret = PTR_ERR(led->gpio_en_set);
		dev_err(dev, "Unable to claim gpio \"enset\".\n");
		वापस ret;
	पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
	pinctrl = devm_pinctrl_get_select_शेष(&led->pdev->dev);
	अगर (IS_ERR(pinctrl)) अणु
		cfg->has_बाह्यal_strobe = false;
		dev_info(dev,
			 "No support for external strobe detected.\n");
	पूर्ण अन्यथा अणु
		cfg->has_बाह्यal_strobe = true;
	पूर्ण
#पूर्ण_अगर

	child_node = of_get_next_available_child(dev_of_node(dev), शून्य);
	अगर (!child_node) अणु
		dev_err(dev, "No DT child node found for connected LED.\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(child_node, "led-max-microamp",
				&cfg->max_mm_current);
	/*
	 * led-max-microamp will शेष to 1/20 of flash-max-microamp
	 * in हाल it is missing.
	 */
	अगर (ret < 0)
		dev_warn(dev,
			"led-max-microamp DT property missing\n");

	ret = of_property_पढ़ो_u32(child_node, "flash-max-microamp",
				&cfg->max_flash_current);
	अगर (ret < 0) अणु
		dev_err(dev,
			"flash-max-microamp DT property missing\n");
		जाओ err_parse_dt;
	पूर्ण

	ret = of_property_पढ़ो_u32(child_node, "flash-max-timeout-us",
				&cfg->max_flash_पंचांग);
	अगर (ret < 0) अणु
		dev_err(dev,
			"flash-max-timeout-us DT property missing\n");
		जाओ err_parse_dt;
	पूर्ण

	*sub_node = child_node;

err_parse_dt:
	of_node_put(child_node);

	वापस ret;
पूर्ण

अटल व्योम aat1290_led_validate_mm_current(काष्ठा aat1290_led *led,
					काष्ठा aat1290_led_config_data *cfg)
अणु
	पूर्णांक i, b = 0, e = AAT1290_MM_CURRENT_SCALE_SIZE;

	जबतक (e - b > 1) अणु
		i = b + (e - b) / 2;
		अगर (cfg->max_mm_current < led->mm_current_scale[i])
			e = i;
		अन्यथा
			b = i;
	पूर्ण

	cfg->max_mm_current = led->mm_current_scale[b];
	cfg->max_brightness = b + 1;
पूर्ण

अटल पूर्णांक init_mm_current_scale(काष्ठा aat1290_led *led,
			काष्ठा aat1290_led_config_data *cfg)
अणु
	अटल स्थिर पूर्णांक max_mm_current_percent[] = अणु
		20, 22, 25, 28, 32, 36, 40, 45, 50, 56,
		63, 71, 79, 89, 100
	पूर्ण;
	पूर्णांक i, max_mm_current =
			AAT1290_MAX_MM_CURRENT(cfg->max_flash_current);

	led->mm_current_scale = devm_kzalloc(&led->pdev->dev,
					माप(max_mm_current_percent),
					GFP_KERNEL);
	अगर (!led->mm_current_scale)
		वापस -ENOMEM;

	क्रम (i = 0; i < AAT1290_MM_CURRENT_SCALE_SIZE; ++i)
		led->mm_current_scale[i] = max_mm_current *
					  max_mm_current_percent[i] / 100;

	वापस 0;
पूर्ण

अटल पूर्णांक aat1290_led_get_configuration(काष्ठा aat1290_led *led,
					काष्ठा aat1290_led_config_data *cfg,
					काष्ठा device_node **sub_node)
अणु
	पूर्णांक ret;

	ret = aat1290_led_parse_dt(led, cfg, sub_node);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Init non-linear movie mode current scale basing
	 * on the max flash current from led configuration.
	 */
	ret = init_mm_current_scale(led, cfg);
	अगर (ret < 0)
		वापस ret;

	aat1290_led_validate_mm_current(led, cfg);

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
#अन्यथा
	devm_kमुक्त(&led->pdev->dev, led->mm_current_scale);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम aat1290_init_flash_समयout(काष्ठा aat1290_led *led,
				काष्ठा aat1290_led_config_data *cfg)
अणु
	काष्ठा led_classdev_flash *fled_cdev = &led->fled_cdev;
	काष्ठा led_flash_setting *setting;

	/* Init flash समयout setting */
	setting = &fled_cdev->समयout;
	setting->min = cfg->max_flash_पंचांग / AAT1290_FLASH_TM_NUM_LEVELS;
	setting->max = cfg->max_flash_पंचांग;
	setting->step = setting->min;
	setting->val = setting->max;
पूर्ण

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
अटल क्रमागत led_brightness aat1290_पूर्णांकensity_to_brightness(
					काष्ठा v4l2_flash *v4l2_flash,
					s32 पूर्णांकensity)
अणु
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा aat1290_led *led = fled_cdev_to_led(fled_cdev);
	पूर्णांक i;

	क्रम (i = AAT1290_MM_CURRENT_SCALE_SIZE - 1; i >= 0; --i)
		अगर (पूर्णांकensity >= led->mm_current_scale[i])
			वापस i + 1;

	वापस 1;
पूर्ण

अटल s32 aat1290_brightness_to_पूर्णांकensity(काष्ठा v4l2_flash *v4l2_flash,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा aat1290_led *led = fled_cdev_to_led(fled_cdev);

	वापस led->mm_current_scale[brightness - 1];
पूर्ण

अटल पूर्णांक aat1290_led_बाह्यal_strobe_set(काष्ठा v4l2_flash *v4l2_flash,
						bool enable)
अणु
	काष्ठा aat1290_led *led = fled_cdev_to_led(v4l2_flash->fled_cdev);
	काष्ठा led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	काष्ठा led_classdev *led_cdev = &fled_cdev->led_cdev;
	काष्ठा pinctrl *pinctrl;

	gpiod_direction_output(led->gpio_fl_en, 0);
	gpiod_direction_output(led->gpio_en_set, 0);

	led->movie_mode = false;
	led_cdev->brightness = 0;

	pinctrl = devm_pinctrl_get_select(&led->pdev->dev,
						enable ? "isp" : "host");
	अगर (IS_ERR(pinctrl)) अणु
		dev_warn(&led->pdev->dev, "Unable to switch strobe source.\n");
		वापस PTR_ERR(pinctrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aat1290_init_v4l2_flash_config(काष्ठा aat1290_led *led,
					काष्ठा aat1290_led_config_data *led_cfg,
					काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
	काष्ठा led_classdev *led_cdev = &led->fled_cdev.led_cdev;
	काष्ठा led_flash_setting *s;

	strlcpy(v4l2_sd_cfg->dev_name, led_cdev->dev->kobj.name,
		माप(v4l2_sd_cfg->dev_name));

	s = &v4l2_sd_cfg->पूर्णांकensity;
	s->min = led->mm_current_scale[0];
	s->max = led_cfg->max_mm_current;
	s->step = 1;
	s->val = s->max;

	v4l2_sd_cfg->has_बाह्यal_strobe = led_cfg->has_बाह्यal_strobe;
पूर्ण

अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops = अणु
	.बाह्यal_strobe_set = aat1290_led_बाह्यal_strobe_set,
	.पूर्णांकensity_to_led_brightness = aat1290_पूर्णांकensity_to_brightness,
	.led_brightness_to_पूर्णांकensity = aat1290_brightness_to_पूर्णांकensity,
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम aat1290_init_v4l2_flash_config(काष्ठा aat1290_led *led,
				काष्ठा aat1290_led_config_data *led_cfg,
				काष्ठा v4l2_flash_config *v4l2_sd_cfg)
अणु
पूर्ण
अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops;
#पूर्ण_अगर

अटल स्थिर काष्ठा led_flash_ops flash_ops = अणु
	.strobe_set = aat1290_led_flash_strobe_set,
	.समयout_set = aat1290_led_flash_समयout_set,
पूर्ण;

अटल पूर्णांक aat1290_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *sub_node = शून्य;
	काष्ठा aat1290_led *led;
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_classdev_flash *fled_cdev;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा aat1290_led_config_data led_cfg = अणुपूर्ण;
	काष्ठा v4l2_flash_config v4l2_sd_cfg = अणुपूर्ण;
	पूर्णांक ret;

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->pdev = pdev;
	platक्रमm_set_drvdata(pdev, led);

	fled_cdev = &led->fled_cdev;
	fled_cdev->ops = &flash_ops;
	led_cdev = &fled_cdev->led_cdev;

	ret = aat1290_led_get_configuration(led, &led_cfg, &sub_node);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&led->lock);

	/* Initialize LED Flash class device */
	led_cdev->brightness_set_blocking = aat1290_led_brightness_set;
	led_cdev->max_brightness = led_cfg.max_brightness;
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	aat1290_init_flash_समयout(led, &led_cfg);

	init_data.fwnode = of_fwnode_handle(sub_node);
	init_data.devicename = AAT1290_NAME;

	/* Register LED Flash class device */
	ret = led_classdev_flash_रेजिस्टर_ext(&pdev->dev, fled_cdev,
					      &init_data);
	अगर (ret < 0)
		जाओ err_flash_रेजिस्टर;

	aat1290_init_v4l2_flash_config(led, &led_cfg, &v4l2_sd_cfg);

	/* Create V4L2 Flash subdev. */
	led->v4l2_flash = v4l2_flash_init(dev, of_fwnode_handle(sub_node),
					  fled_cdev, &v4l2_flash_ops,
					  &v4l2_sd_cfg);
	अगर (IS_ERR(led->v4l2_flash)) अणु
		ret = PTR_ERR(led->v4l2_flash);
		जाओ error_v4l2_flash_init;
	पूर्ण

	वापस 0;

error_v4l2_flash_init:
	led_classdev_flash_unरेजिस्टर(fled_cdev);
err_flash_रेजिस्टर:
	mutex_destroy(&led->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aat1290_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aat1290_led *led = platक्रमm_get_drvdata(pdev);

	v4l2_flash_release(led->v4l2_flash);
	led_classdev_flash_unरेजिस्टर(&led->fled_cdev);

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aat1290_led_dt_match[] = अणु
	अणु .compatible = "skyworks,aat1290" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aat1290_led_dt_match);

अटल काष्ठा platक्रमm_driver aat1290_led_driver = अणु
	.probe		= aat1290_led_probe,
	.हटाओ		= aat1290_led_हटाओ,
	.driver		= अणु
		.name	= "aat1290",
		.of_match_table = aat1290_led_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aat1290_led_driver);

MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_DESCRIPTION("Skyworks Current Regulator for Flash LEDs");
MODULE_LICENSE("GPL v2");
