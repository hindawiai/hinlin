<शैली गुरु>
/*
 * Bachmann ot200 leds driver.
 *
 * Author: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *         Christian Gmeiner <christian.gmeiner@gmail.com>
 *
 * License: GPL as published by the FSF.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>


काष्ठा ot200_led अणु
	काष्ठा led_classdev cdev;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ port;
	u8 mask;
पूर्ण;

/*
 * The device has three leds on the back panel (led_err, led_init and led_run)
 * and can handle up to seven leds on the front panel.
 */

अटल काष्ठा ot200_led leds[] = अणु
	अणु
		.name = "led_run",
		.port = 0x5a,
		.mask = BIT(0),
	पूर्ण,
	अणु
		.name = "led_init",
		.port = 0x5a,
		.mask = BIT(1),
	पूर्ण,
	अणु
		.name = "led_err",
		.port = 0x5a,
		.mask = BIT(2),
	पूर्ण,
	अणु
		.name = "led_1",
		.port = 0x49,
		.mask = BIT(6),
	पूर्ण,
	अणु
		.name = "led_2",
		.port = 0x49,
		.mask = BIT(5),
	पूर्ण,
	अणु
		.name = "led_3",
		.port = 0x49,
		.mask = BIT(4),
	पूर्ण,
	अणु
		.name = "led_4",
		.port = 0x49,
		.mask = BIT(3),
	पूर्ण,
	अणु
		.name = "led_5",
		.port = 0x49,
		.mask = BIT(2),
	पूर्ण,
	अणु
		.name = "led_6",
		.port = 0x49,
		.mask = BIT(1),
	पूर्ण,
	अणु
		.name = "led_7",
		.port = 0x49,
		.mask = BIT(0),
	पूर्ण
पूर्ण;

अटल DEFINE_SPINLOCK(value_lock);

/*
 * we need to store the current led states, as it is not
 * possible to पढ़ो the current led state via inb().
 */
अटल u8 leds_back;
अटल u8 leds_front;

अटल व्योम ot200_led_brightness_set(काष्ठा led_classdev *led_cdev,
		क्रमागत led_brightness value)
अणु
	काष्ठा ot200_led *led = container_of(led_cdev, काष्ठा ot200_led, cdev);
	u8 *val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&value_lock, flags);

	अगर (led->port == 0x49)
		val = &leds_front;
	अन्यथा अगर (led->port == 0x5a)
		val = &leds_back;
	अन्यथा
		BUG();

	अगर (value == LED_OFF)
		*val &= ~led->mask;
	अन्यथा
		*val |= led->mask;

	outb(*val, led->port);
	spin_unlock_irqrestore(&value_lock, flags);
पूर्ण

अटल पूर्णांक ot200_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(leds); i++) अणु

		leds[i].cdev.name = leds[i].name;
		leds[i].cdev.brightness_set = ot200_led_brightness_set;

		ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &leds[i].cdev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	leds_front = 0;		/* turn off all front leds */
	leds_back = BIT(1);	/* turn on init led */
	outb(leds_front, 0x49);
	outb(leds_back, 0x5a);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ot200_led_driver = अणु
	.probe		= ot200_led_probe,
	.driver		= अणु
		.name	= "leds-ot200",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ot200_led_driver);

MODULE_AUTHOR("Sebastian A. Siewior <bigeasy@linutronix.de>");
MODULE_DESCRIPTION("ot200 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-ot200");
