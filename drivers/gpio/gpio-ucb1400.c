<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Philips UCB1400 GPIO driver
 *
 * Author: Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/ucb1400.h>

अटल पूर्णांक ucb1400_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा ucb1400_gpio *gpio;
	gpio = gpiochip_get_data(gc);
	ucb1400_gpio_set_direction(gpio->ac97, off, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ucb1400_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा ucb1400_gpio *gpio;
	gpio = gpiochip_get_data(gc);
	ucb1400_gpio_set_direction(gpio->ac97, off, 1);
	ucb1400_gpio_set_value(gpio->ac97, off, val);
	वापस 0;
पूर्ण

अटल पूर्णांक ucb1400_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा ucb1400_gpio *gpio;

	gpio = gpiochip_get_data(gc);
	वापस !!ucb1400_gpio_get_value(gpio->ac97, off);
पूर्ण

अटल व्योम ucb1400_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा ucb1400_gpio *gpio;
	gpio = gpiochip_get_data(gc);
	ucb1400_gpio_set_value(gpio->ac97, off, val);
पूर्ण

अटल पूर्णांक ucb1400_gpio_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ucb1400_gpio *ucb = dev_get_platdata(&dev->dev);
	पूर्णांक err = 0;

	अगर (!(ucb && ucb->gpio_offset)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(dev, ucb);

	ucb->gc.label = "ucb1400_gpio";
	ucb->gc.base = ucb->gpio_offset;
	ucb->gc.ngpio = 10;
	ucb->gc.owner = THIS_MODULE;

	ucb->gc.direction_input = ucb1400_gpio_dir_in;
	ucb->gc.direction_output = ucb1400_gpio_dir_out;
	ucb->gc.get = ucb1400_gpio_get;
	ucb->gc.set = ucb1400_gpio_set;
	ucb->gc.can_sleep = true;

	err = devm_gpiochip_add_data(&dev->dev, &ucb->gc, ucb);
	अगर (err)
		जाओ err;

	अगर (ucb->gpio_setup)
		err = ucb->gpio_setup(&dev->dev, ucb->gc.ngpio);

err:
	वापस err;

पूर्ण

अटल पूर्णांक ucb1400_gpio_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा ucb1400_gpio *ucb = platक्रमm_get_drvdata(dev);

	अगर (ucb && ucb->gpio_tearकरोwn) अणु
		err = ucb->gpio_tearकरोwn(&dev->dev, ucb->gc.ngpio);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver ucb1400_gpio_driver = अणु
	.probe	= ucb1400_gpio_probe,
	.हटाओ	= ucb1400_gpio_हटाओ,
	.driver	= अणु
		.name	= "ucb1400_gpio"
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ucb1400_gpio_driver);

MODULE_DESCRIPTION("Philips UCB1400 GPIO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ucb1400_gpio");
