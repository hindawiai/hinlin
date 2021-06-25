<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  GPIO vibrator driver
 *
 *  Copyright (C) 2019 Luca Weiss <luca@z3ntu.xyz>
 *
 *  Based on PWM vibrator driver:
 *  Copyright (C) 2017 Collabora Ltd.
 *
 *  Based on previous work from:
 *  Copyright (C) 2012 Dmitry Torokhov <dmitry.torokhov@gmail.com>
 *
 *  Based on PWM beeper driver:
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

काष्ठा gpio_vibrator अणु
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *gpio;
	काष्ठा regulator *vcc;

	काष्ठा work_काष्ठा play_work;
	bool running;
	bool vcc_on;
पूर्ण;

अटल पूर्णांक gpio_vibrator_start(काष्ठा gpio_vibrator *vibrator)
अणु
	काष्ठा device *pdev = vibrator->input->dev.parent;
	पूर्णांक err;

	अगर (!vibrator->vcc_on) अणु
		err = regulator_enable(vibrator->vcc);
		अगर (err) अणु
			dev_err(pdev, "failed to enable regulator: %d\n", err);
			वापस err;
		पूर्ण
		vibrator->vcc_on = true;
	पूर्ण

	gpiod_set_value_cansleep(vibrator->gpio, 1);

	वापस 0;
पूर्ण

अटल व्योम gpio_vibrator_stop(काष्ठा gpio_vibrator *vibrator)
अणु
	gpiod_set_value_cansleep(vibrator->gpio, 0);

	अगर (vibrator->vcc_on) अणु
		regulator_disable(vibrator->vcc);
		vibrator->vcc_on = false;
	पूर्ण
पूर्ण

अटल व्योम gpio_vibrator_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_vibrator *vibrator =
		container_of(work, काष्ठा gpio_vibrator, play_work);

	अगर (vibrator->running)
		gpio_vibrator_start(vibrator);
	अन्यथा
		gpio_vibrator_stop(vibrator);
पूर्ण

अटल पूर्णांक gpio_vibrator_play_effect(काष्ठा input_dev *dev, व्योम *data,
				     काष्ठा ff_effect *effect)
अणु
	काष्ठा gpio_vibrator *vibrator = input_get_drvdata(dev);
	पूर्णांक level;

	level = effect->u.rumble.strong_magnitude;
	अगर (!level)
		level = effect->u.rumble.weak_magnitude;

	vibrator->running = level;
	schedule_work(&vibrator->play_work);

	वापस 0;
पूर्ण

अटल व्योम gpio_vibrator_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_vibrator *vibrator = input_get_drvdata(input);

	cancel_work_sync(&vibrator->play_work);
	gpio_vibrator_stop(vibrator);
	vibrator->running = false;
पूर्ण

अटल पूर्णांक gpio_vibrator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_vibrator *vibrator;
	पूर्णांक err;

	vibrator = devm_kzalloc(&pdev->dev, माप(*vibrator), GFP_KERNEL);
	अगर (!vibrator)
		वापस -ENOMEM;

	vibrator->input = devm_input_allocate_device(&pdev->dev);
	अगर (!vibrator->input)
		वापस -ENOMEM;

	vibrator->vcc = devm_regulator_get(&pdev->dev, "vcc");
	err = PTR_ERR_OR_ZERO(vibrator->vcc);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to request regulator: %d\n",
				err);
		वापस err;
	पूर्ण

	vibrator->gpio = devm_gpiod_get(&pdev->dev, "enable", GPIOD_OUT_LOW);
	err = PTR_ERR_OR_ZERO(vibrator->gpio);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to request main gpio: %d\n",
				err);
		वापस err;
	पूर्ण

	INIT_WORK(&vibrator->play_work, gpio_vibrator_play_work);

	vibrator->input->name = "gpio-vibrator";
	vibrator->input->id.bustype = BUS_HOST;
	vibrator->input->बंद = gpio_vibrator_बंद;

	input_set_drvdata(vibrator->input, vibrator);
	input_set_capability(vibrator->input, EV_FF, FF_RUMBLE);

	err = input_ff_create_memless(vibrator->input, शून्य,
				      gpio_vibrator_play_effect);
	अगर (err) अणु
		dev_err(&pdev->dev, "Couldn't create FF dev: %d\n", err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(vibrator->input);
	अगर (err) अणु
		dev_err(&pdev->dev, "Couldn't register input dev: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vibrator);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gpio_vibrator_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा gpio_vibrator *vibrator = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&vibrator->play_work);
	अगर (vibrator->running)
		gpio_vibrator_stop(vibrator);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gpio_vibrator_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा gpio_vibrator *vibrator = platक्रमm_get_drvdata(pdev);

	अगर (vibrator->running)
		gpio_vibrator_start(vibrator);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(gpio_vibrator_pm_ops,
			 gpio_vibrator_suspend, gpio_vibrator_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_vibra_dt_match_table[] = अणु
	अणु .compatible = "gpio-vibrator" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_vibra_dt_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_vibrator_driver = अणु
	.probe	= gpio_vibrator_probe,
	.driver	= अणु
		.name	= "gpio-vibrator",
		.pm	= &gpio_vibrator_pm_ops,
		.of_match_table = of_match_ptr(gpio_vibra_dt_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gpio_vibrator_driver);

MODULE_AUTHOR("Luca Weiss <luca@z3ntu.xy>");
MODULE_DESCRIPTION("GPIO vibrator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-vibrator");
