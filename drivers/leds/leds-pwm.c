<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/leds-pwm.c
 *
 * simple PWM based LED control
 *
 * Copyright 2009 Luotao Fu @ Pengutronix (l.fu@pengutronix.de)
 *
 * based on leds-gpio.c by Raphael Assenat <raph@8d.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

काष्ठा led_pwm अणु
	स्थिर अक्षर	*name;
	u8		active_low;
	अचिन्हित पूर्णांक	max_brightness;
पूर्ण;

काष्ठा led_pwm_data अणु
	काष्ठा led_classdev	cdev;
	काष्ठा pwm_device	*pwm;
	काष्ठा pwm_state	pwmstate;
	अचिन्हित पूर्णांक		active_low;
पूर्ण;

काष्ठा led_pwm_priv अणु
	पूर्णांक num_leds;
	काष्ठा led_pwm_data leds[];
पूर्ण;

अटल पूर्णांक led_pwm_set(काष्ठा led_classdev *led_cdev,
		       क्रमागत led_brightness brightness)
अणु
	काष्ठा led_pwm_data *led_dat =
		container_of(led_cdev, काष्ठा led_pwm_data, cdev);
	अचिन्हित पूर्णांक max = led_dat->cdev.max_brightness;
	अचिन्हित दीर्घ दीर्घ duty = led_dat->pwmstate.period;

	duty *= brightness;
	करो_भाग(duty, max);

	अगर (led_dat->active_low)
		duty = led_dat->pwmstate.period - duty;

	led_dat->pwmstate.duty_cycle = duty;
	led_dat->pwmstate.enabled = duty > 0;
	वापस pwm_apply_state(led_dat->pwm, &led_dat->pwmstate);
पूर्ण

__attribute__((nonnull))
अटल पूर्णांक led_pwm_add(काष्ठा device *dev, काष्ठा led_pwm_priv *priv,
		       काष्ठा led_pwm *led, काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा led_pwm_data *led_data = &priv->leds[priv->num_leds];
	काष्ठा led_init_data init_data = अणु .fwnode = fwnode पूर्ण;
	पूर्णांक ret;

	led_data->active_low = led->active_low;
	led_data->cdev.name = led->name;
	led_data->cdev.brightness = LED_OFF;
	led_data->cdev.max_brightness = led->max_brightness;
	led_data->cdev.flags = LED_CORE_SUSPENDRESUME;

	led_data->pwm = devm_fwnode_pwm_get(dev, fwnode, शून्य);
	अगर (IS_ERR(led_data->pwm))
		वापस dev_err_probe(dev, PTR_ERR(led_data->pwm),
				     "unable to request PWM for %s\n",
				     led->name);

	led_data->cdev.brightness_set_blocking = led_pwm_set;

	pwm_init_state(led_data->pwm, &led_data->pwmstate);

	ret = devm_led_classdev_रेजिस्टर_ext(dev, &led_data->cdev, &init_data);
	अगर (ret) अणु
		dev_err(dev, "failed to register PWM led for %s: %d\n",
			led->name, ret);
		वापस ret;
	पूर्ण

	ret = led_pwm_set(&led_data->cdev, led_data->cdev.brightness);
	अगर (ret) अणु
		dev_err(dev, "failed to set led PWM value for %s: %d",
			led->name, ret);
		वापस ret;
	पूर्ण

	priv->num_leds++;
	वापस 0;
पूर्ण

अटल पूर्णांक led_pwm_create_fwnode(काष्ठा device *dev, काष्ठा led_pwm_priv *priv)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा led_pwm led;
	पूर्णांक ret = 0;

	स_रखो(&led, 0, माप(led));

	device_क्रम_each_child_node(dev, fwnode) अणु
		ret = fwnode_property_पढ़ो_string(fwnode, "label", &led.name);
		अगर (ret && is_of_node(fwnode))
			led.name = to_of_node(fwnode)->name;

		अगर (!led.name) अणु
			fwnode_handle_put(fwnode);
			वापस -EINVAL;
		पूर्ण

		led.active_low = fwnode_property_पढ़ो_bool(fwnode,
							   "active-low");
		fwnode_property_पढ़ो_u32(fwnode, "max-brightness",
					 &led.max_brightness);

		ret = led_pwm_add(dev, priv, &led, fwnode);
		अगर (ret) अणु
			fwnode_handle_put(fwnode);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक led_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा led_pwm_priv *priv;
	पूर्णांक ret = 0;
	पूर्णांक count;

	count = device_get_child_node_count(&pdev->dev);

	अगर (!count)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, काष्ठा_size(priv, leds, count),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = led_pwm_create_fwnode(&pdev->dev, priv);

	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pwm_leds_match[] = अणु
	अणु .compatible = "pwm-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pwm_leds_match);

अटल काष्ठा platक्रमm_driver led_pwm_driver = अणु
	.probe		= led_pwm_probe,
	.driver		= अणु
		.name	= "leds_pwm",
		.of_match_table = of_pwm_leds_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(led_pwm_driver);

MODULE_AUTHOR("Luotao Fu <l.fu@pengutronix.de>");
MODULE_DESCRIPTION("generic PWM LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:leds-pwm");
