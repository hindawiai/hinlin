<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator haptic driver
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Jaewon Kim <jaewon02.kim@samsung.com>
 * Author: Hyunhee Kim <hyunhee.kim@samsung.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/regulator-haptic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#घोषणा MAX_MAGNITUDE_SHIFT	16

काष्ठा regulator_haptic अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input_dev;
	काष्ठा regulator *regulator;

	काष्ठा work_काष्ठा work;
	काष्ठा mutex mutex;

	bool active;
	bool suspended;

	अचिन्हित पूर्णांक max_volt;
	अचिन्हित पूर्णांक min_volt;
	अचिन्हित पूर्णांक magnitude;
पूर्ण;

अटल पूर्णांक regulator_haptic_toggle(काष्ठा regulator_haptic *haptic, bool on)
अणु
	पूर्णांक error;

	अगर (haptic->active != on) अणु

		error = on ? regulator_enable(haptic->regulator) :
			     regulator_disable(haptic->regulator);
		अगर (error) अणु
			dev_err(haptic->dev,
				"failed to switch regulator %s: %d\n",
				on ? "on" : "off", error);
			वापस error;
		पूर्ण

		haptic->active = on;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_haptic_set_voltage(काष्ठा regulator_haptic *haptic,
					 अचिन्हित पूर्णांक magnitude)
अणु
	u64 volt_mag_multi;
	अचिन्हित पूर्णांक पूर्णांकensity;
	पूर्णांक error;

	volt_mag_multi = (u64)(haptic->max_volt - haptic->min_volt) * magnitude;
	पूर्णांकensity = (अचिन्हित पूर्णांक)(volt_mag_multi >> MAX_MAGNITUDE_SHIFT);

	error = regulator_set_voltage(haptic->regulator,
				      पूर्णांकensity + haptic->min_volt,
				      haptic->max_volt);
	अगर (error) अणु
		dev_err(haptic->dev, "cannot set regulator voltage to %d: %d\n",
			पूर्णांकensity + haptic->min_volt, error);
		वापस error;
	पूर्ण

	regulator_haptic_toggle(haptic, !!magnitude);

	वापस 0;
पूर्ण

अटल व्योम regulator_haptic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा regulator_haptic *haptic = container_of(work,
					काष्ठा regulator_haptic, work);

	mutex_lock(&haptic->mutex);

	अगर (!haptic->suspended)
		regulator_haptic_set_voltage(haptic, haptic->magnitude);

	mutex_unlock(&haptic->mutex);
पूर्ण

अटल पूर्णांक regulator_haptic_play_effect(काष्ठा input_dev *input, व्योम *data,
					काष्ठा ff_effect *effect)
अणु
	काष्ठा regulator_haptic *haptic = input_get_drvdata(input);

	haptic->magnitude = effect->u.rumble.strong_magnitude;
	अगर (!haptic->magnitude)
		haptic->magnitude = effect->u.rumble.weak_magnitude;

	schedule_work(&haptic->work);

	वापस 0;
पूर्ण

अटल व्योम regulator_haptic_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा regulator_haptic *haptic = input_get_drvdata(input);

	cancel_work_sync(&haptic->work);
	regulator_haptic_set_voltage(haptic, 0);
पूर्ण

अटल पूर्णांक __maybe_unused
regulator_haptic_parse_dt(काष्ठा device *dev, काष्ठा regulator_haptic *haptic)
अणु
	काष्ठा device_node *node;
	पूर्णांक error;

	node = dev->of_node;
	अगर(!node) अणु
		dev_err(dev, "Missing device tree data\n");
		वापस -EINVAL;
	पूर्ण

	error = of_property_पढ़ो_u32(node, "max-microvolt", &haptic->max_volt);
	अगर (error) अणु
		dev_err(dev, "cannot parse max-microvolt\n");
		वापस error;
	पूर्ण

	error = of_property_पढ़ो_u32(node, "min-microvolt", &haptic->min_volt);
	अगर (error) अणु
		dev_err(dev, "cannot parse min-microvolt\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regulator_haptic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा regulator_haptic_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा regulator_haptic *haptic;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	haptic = devm_kzalloc(&pdev->dev, माप(*haptic), GFP_KERNEL);
	अगर (!haptic)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, haptic);
	haptic->dev = &pdev->dev;
	mutex_init(&haptic->mutex);
	INIT_WORK(&haptic->work, regulator_haptic_work);

	अगर (pdata) अणु
		haptic->max_volt = pdata->max_volt;
		haptic->min_volt = pdata->min_volt;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_OF)) अणु
		error = regulator_haptic_parse_dt(&pdev->dev, haptic);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	haptic->regulator = devm_regulator_get_exclusive(&pdev->dev, "haptic");
	अगर (IS_ERR(haptic->regulator)) अणु
		dev_err(&pdev->dev, "failed to get regulator\n");
		वापस PTR_ERR(haptic->regulator);
	पूर्ण

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस	-ENOMEM;

	haptic->input_dev = input_dev;
	haptic->input_dev->name = "regulator-haptic";
	haptic->input_dev->dev.parent = &pdev->dev;
	haptic->input_dev->बंद = regulator_haptic_बंद;
	input_set_drvdata(haptic->input_dev, haptic);
	input_set_capability(haptic->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, शून्य,
					regulator_haptic_play_effect);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to create force-feedback\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(haptic->input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused regulator_haptic_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा regulator_haptic *haptic = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&haptic->mutex);
	अगर (error)
		वापस error;

	regulator_haptic_set_voltage(haptic, 0);

	haptic->suspended = true;

	mutex_unlock(&haptic->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused regulator_haptic_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा regulator_haptic *haptic = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक magnitude;

	mutex_lock(&haptic->mutex);

	haptic->suspended = false;

	magnitude = READ_ONCE(haptic->magnitude);
	अगर (magnitude)
		regulator_haptic_set_voltage(haptic, magnitude);

	mutex_unlock(&haptic->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(regulator_haptic_pm_ops,
		regulator_haptic_suspend, regulator_haptic_resume);

अटल स्थिर काष्ठा of_device_id regulator_haptic_dt_match[] = अणु
	अणु .compatible = "regulator-haptic" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, regulator_haptic_dt_match);

अटल काष्ठा platक्रमm_driver regulator_haptic_driver = अणु
	.probe		= regulator_haptic_probe,
	.driver		= अणु
		.name		= "regulator-haptic",
		.of_match_table = regulator_haptic_dt_match,
		.pm		= &regulator_haptic_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(regulator_haptic_driver);

MODULE_AUTHOR("Jaewon Kim <jaewon02.kim@samsung.com>");
MODULE_AUTHOR("Hyunhee Kim <hyunhee.kim@samsung.com>");
MODULE_DESCRIPTION("Regulator haptic driver");
MODULE_LICENSE("GPL");
