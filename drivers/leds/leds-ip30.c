<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LED Driver क्रम SGI Octane machines
 */

#समावेश <यंत्र/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>

#घोषणा IP30_LED_SYSTEM	0
#घोषणा IP30_LED_FAULT	1

काष्ठा ip30_led अणु
	काष्ठा led_classdev cdev;
	u32 __iomem *reg;
पूर्ण;

अटल व्योम ip30led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा ip30_led *led = container_of(led_cdev, काष्ठा ip30_led, cdev);

	ग_लिखोl(value, led->reg);
पूर्ण

अटल पूर्णांक ip30led_create(काष्ठा platक्रमm_device *pdev, पूर्णांक num)
अणु
	काष्ठा resource *res;
	काष्ठा ip30_led *data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, num);
	अगर (!res)
		वापस -EBUSY;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->reg))
		वापस PTR_ERR(data->reg);


	चयन (num) अणु
	हाल IP30_LED_SYSTEM:
		data->cdev.name = "white:power";
		अवरोध;
	हाल IP30_LED_FAULT:
		data->cdev.name = "red:fault";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data->cdev.brightness = पढ़ोl(data->reg);
	data->cdev.max_brightness = 1;
	data->cdev.brightness_set = ip30led_set;

	वापस devm_led_classdev_रेजिस्टर(&pdev->dev, &data->cdev);
पूर्ण

अटल पूर्णांक ip30led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = ip30led_create(pdev, IP30_LED_SYSTEM);
	अगर (ret < 0)
		वापस ret;

	वापस ip30led_create(pdev, IP30_LED_FAULT);
पूर्ण

अटल काष्ठा platक्रमm_driver ip30led_driver = अणु
	.probe		= ip30led_probe,
	.driver		= अणु
		.name		= "ip30-leds",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ip30led_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tbogendoerfer@suse.de>");
MODULE_DESCRIPTION("SGI Octane LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ip30-leds");
