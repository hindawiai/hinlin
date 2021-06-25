<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w1-gpio - GPIO w1 bus master driver
 *
 * Copyright (C) 2007 Ville Syrjala <syrjala@sci.fi>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/w1-gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>

#समावेश <linux/w1.h>

अटल u8 w1_gpio_set_pullup(व्योम *data, पूर्णांक delay)
अणु
	काष्ठा w1_gpio_platक्रमm_data *pdata = data;

	अगर (delay) अणु
		pdata->pullup_duration = delay;
	पूर्ण अन्यथा अणु
		अगर (pdata->pullup_duration) अणु
			/*
			 * This will OVERRIDE खोलो drain emulation and क्रमce-pull
			 * the line high क्रम some समय.
			 */
			gpiod_set_raw_value(pdata->gpiod, 1);
			msleep(pdata->pullup_duration);
			/*
			 * This will simply set the line as input since we are करोing
			 * खोलो drain emulation in the GPIO library.
			 */
			gpiod_set_value(pdata->gpiod, 1);
		पूर्ण
		pdata->pullup_duration = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम w1_gpio_ग_लिखो_bit(व्योम *data, u8 bit)
अणु
	काष्ठा w1_gpio_platक्रमm_data *pdata = data;

	gpiod_set_value(pdata->gpiod, bit);
पूर्ण

अटल u8 w1_gpio_पढ़ो_bit(व्योम *data)
अणु
	काष्ठा w1_gpio_platक्रमm_data *pdata = data;

	वापस gpiod_get_value(pdata->gpiod) ? 1 : 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id w1_gpio_dt_ids[] = अणु
	अणु .compatible = "w1-gpio" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, w1_gpio_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक w1_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w1_bus_master *master;
	काष्ठा w1_gpio_platक्रमm_data *pdata;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	/* Enक्रमce खोलो drain mode by शेष */
	क्रमागत gpiod_flags gflags = GPIOD_OUT_LOW_OPEN_DRAIN;
	पूर्णांक err;

	अगर (of_have_populated_dt()) अणु
		pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		/*
		 * This parameter means that something अन्यथा than the gpiolib has
		 * alपढ़ोy set the line पूर्णांकo खोलो drain mode, so we should just
		 * driver it high/low like we are in full control of the line and
		 * खोलो drain will happen transparently.
		 */
		अगर (of_get_property(np, "linux,open-drain", शून्य))
			gflags = GPIOD_OUT_LOW;

		pdev->dev.platक्रमm_data = pdata;
	पूर्ण
	pdata = dev_get_platdata(dev);

	अगर (!pdata) अणु
		dev_err(dev, "No configuration data\n");
		वापस -ENXIO;
	पूर्ण

	master = devm_kzalloc(dev, माप(काष्ठा w1_bus_master),
			GFP_KERNEL);
	अगर (!master) अणु
		dev_err(dev, "Out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	pdata->gpiod = devm_gpiod_get_index(dev, शून्य, 0, gflags);
	अगर (IS_ERR(pdata->gpiod)) अणु
		dev_err(dev, "gpio_request (pin) failed\n");
		वापस PTR_ERR(pdata->gpiod);
	पूर्ण

	pdata->pullup_gpiod =
		devm_gpiod_get_index_optional(dev, शून्य, 1, GPIOD_OUT_LOW);
	अगर (IS_ERR(pdata->pullup_gpiod)) अणु
		dev_err(dev, "gpio_request_one "
			"(ext_pullup_enable_pin) failed\n");
		वापस PTR_ERR(pdata->pullup_gpiod);
	पूर्ण

	master->data = pdata;
	master->पढ़ो_bit = w1_gpio_पढ़ो_bit;
	gpiod_direction_output(pdata->gpiod, 1);
	master->ग_लिखो_bit = w1_gpio_ग_लिखो_bit;

	/*
	 * If we are using खोलो drain emulation from the GPIO library,
	 * we need to use this pullup function that hammers the line
	 * high using a raw accessor to provide pull-up क्रम the w1
	 * line.
	 */
	अगर (gflags == GPIOD_OUT_LOW_OPEN_DRAIN)
		master->set_pullup = w1_gpio_set_pullup;

	err = w1_add_master_device(master);
	अगर (err) अणु
		dev_err(dev, "w1_add_master device failed\n");
		वापस err;
	पूर्ण

	अगर (pdata->enable_बाह्यal_pullup)
		pdata->enable_बाह्यal_pullup(1);

	अगर (pdata->pullup_gpiod)
		gpiod_set_value(pdata->pullup_gpiod, 1);

	platक्रमm_set_drvdata(pdev, master);

	वापस 0;
पूर्ण

अटल पूर्णांक w1_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w1_bus_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा w1_gpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	अगर (pdata->enable_बाह्यal_pullup)
		pdata->enable_बाह्यal_pullup(0);

	अगर (pdata->pullup_gpiod)
		gpiod_set_value(pdata->pullup_gpiod, 0);

	w1_हटाओ_master_device(master);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused w1_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा w1_gpio_platक्रमm_data *pdata = dev_get_platdata(dev);

	अगर (pdata->enable_बाह्यal_pullup)
		pdata->enable_बाह्यal_pullup(0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused w1_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा w1_gpio_platक्रमm_data *pdata = dev_get_platdata(dev);

	अगर (pdata->enable_बाह्यal_pullup)
		pdata->enable_बाह्यal_pullup(1);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(w1_gpio_pm_ops, w1_gpio_suspend, w1_gpio_resume);

अटल काष्ठा platक्रमm_driver w1_gpio_driver = अणु
	.driver = अणु
		.name	= "w1-gpio",
		.pm	= &w1_gpio_pm_ops,
		.of_match_table = of_match_ptr(w1_gpio_dt_ids),
	पूर्ण,
	.probe = w1_gpio_probe,
	.हटाओ = w1_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(w1_gpio_driver);

MODULE_DESCRIPTION("GPIO w1 bus master driver");
MODULE_AUTHOR("Ville Syrjala <syrjala@sci.fi>");
MODULE_LICENSE("GPL");
