<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/leds/leds-s3c24xx.c
 *
 * (c) 2006 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX - LEDs GPIO driver
*/

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>

/* our context */

काष्ठा s3c24xx_gpio_led अणु
	काष्ठा led_classdev		 cdev;
	काष्ठा s3c24xx_led_platdata	*pdata;
	काष्ठा gpio_desc		*gpiod;
पूर्ण;

अटल अंतरभूत काष्ठा s3c24xx_gpio_led *to_gpio(काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा s3c24xx_gpio_led, cdev);
पूर्ण

अटल व्योम s3c24xx_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा s3c24xx_gpio_led *led = to_gpio(led_cdev);

	gpiod_set_value(led->gpiod, !!value);
पूर्ण

अटल पूर्णांक s3c24xx_led_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c24xx_led_platdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा s3c24xx_gpio_led *led;
	पूर्णांक ret;

	led = devm_kzalloc(&dev->dev, माप(काष्ठा s3c24xx_gpio_led),
			   GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->cdev.brightness_set = s3c24xx_led_set;
	led->cdev.शेष_trigger = pdata->def_trigger;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;

	led->pdata = pdata;

	/* Default to off */
	led->gpiod = devm_gpiod_get(&dev->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(led->gpiod))
		वापस PTR_ERR(led->gpiod);

	/* रेजिस्टर our new led device */
	ret = devm_led_classdev_रेजिस्टर(&dev->dev, &led->cdev);
	अगर (ret < 0)
		dev_err(&dev->dev, "led_classdev_register failed\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c24xx_led_driver = अणु
	.probe		= s3c24xx_led_probe,
	.driver		= अणु
		.name		= "s3c24xx_led",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c24xx_led_driver);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("S3C24XX LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c24xx_led");
