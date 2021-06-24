<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * GPD Pocket fan controller driver
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/devm-helpers.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/thermal.h>
#समावेश <linux/workqueue.h>

#घोषणा MAX_SPEED 3

#घोषणा TEMP_LIMIT0_DEFAULT	55000
#घोषणा TEMP_LIMIT1_DEFAULT	60000
#घोषणा TEMP_LIMIT2_DEFAULT	65000

#घोषणा HYSTERESIS_DEFAULT	3000

#घोषणा SPEED_ON_AC_DEFAULT	2

अटल पूर्णांक temp_limits[3] = अणु
	TEMP_LIMIT0_DEFAULT, TEMP_LIMIT1_DEFAULT, TEMP_LIMIT2_DEFAULT,
पूर्ण;
module_param_array(temp_limits, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(temp_limits,
		 "Millicelsius values above which the fan speed increases");

अटल पूर्णांक hysteresis = HYSTERESIS_DEFAULT;
module_param(hysteresis, पूर्णांक, 0444);
MODULE_PARM_DESC(hysteresis,
		 "Hysteresis in millicelsius before lowering the fan speed");

अटल पूर्णांक speed_on_ac = SPEED_ON_AC_DEFAULT;
module_param(speed_on_ac, पूर्णांक, 0444);
MODULE_PARM_DESC(speed_on_ac,
		 "minimum fan speed to allow when system is powered by AC");

काष्ठा gpd_pocket_fan_data अणु
	काष्ठा device *dev;
	काष्ठा thermal_zone_device *dts0;
	काष्ठा thermal_zone_device *dts1;
	काष्ठा gpio_desc *gpio0;
	काष्ठा gpio_desc *gpio1;
	काष्ठा delayed_work work;
	पूर्णांक last_speed;
पूर्ण;

अटल व्योम gpd_pocket_fan_set_speed(काष्ठा gpd_pocket_fan_data *fan, पूर्णांक speed)
अणु
	अगर (speed == fan->last_speed)
		वापस;

	gpiod_direction_output(fan->gpio0, !!(speed & 1));
	gpiod_direction_output(fan->gpio1, !!(speed & 2));

	fan->last_speed = speed;
पूर्ण

अटल पूर्णांक gpd_pocket_fan_min_speed(व्योम)
अणु
	अगर (घातer_supply_is_प्रणाली_supplied())
		वापस speed_on_ac;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम gpd_pocket_fan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpd_pocket_fan_data *fan =
		container_of(work, काष्ठा gpd_pocket_fan_data, work.work);
	पूर्णांक t0, t1, temp, speed, min_speed, i;

	अगर (thermal_zone_get_temp(fan->dts0, &t0) ||
	    thermal_zone_get_temp(fan->dts1, &t1)) अणु
		dev_warn(fan->dev, "Error getting temperature\n");
		speed = MAX_SPEED;
		जाओ set_speed;
	पूर्ण

	temp = max(t0, t1);

	speed = fan->last_speed;
	min_speed = gpd_pocket_fan_min_speed();

	/* Determine minimum speed */
	क्रम (i = min_speed; i < ARRAY_SIZE(temp_limits); i++) अणु
		अगर (temp < temp_limits[i])
			अवरोध;
	पूर्ण
	अगर (speed < i)
		speed = i;

	/* Use hysteresis beक्रमe lowering speed again */
	क्रम (i = min_speed; i < ARRAY_SIZE(temp_limits); i++) अणु
		अगर (temp <= (temp_limits[i] - hysteresis))
			अवरोध;
	पूर्ण
	अगर (speed > i)
		speed = i;

	अगर (fan->last_speed <= 0 && speed)
		speed = MAX_SPEED; /* kick start motor */

set_speed:
	gpd_pocket_fan_set_speed(fan, speed);

	/* When mostly idle (low temp/speed), slow करोwn the poll पूर्णांकerval. */
	queue_delayed_work(प्रणाली_wq, &fan->work,
			   msecs_to_jअगरfies(4000 / (speed + 1)));
पूर्ण

अटल व्योम gpd_pocket_fan_क्रमce_update(काष्ठा gpd_pocket_fan_data *fan)
अणु
	fan->last_speed = -1;
	mod_delayed_work(प्रणाली_wq, &fan->work, 0);
पूर्ण

अटल पूर्णांक gpd_pocket_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpd_pocket_fan_data *fan;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(temp_limits); i++) अणु
		अगर (temp_limits[i] < 20000 || temp_limits[i] > 90000) अणु
			dev_err(&pdev->dev, "Invalid temp-limit %d (must be between 20000 and 90000)\n",
				temp_limits[i]);
			temp_limits[0] = TEMP_LIMIT0_DEFAULT;
			temp_limits[1] = TEMP_LIMIT1_DEFAULT;
			temp_limits[2] = TEMP_LIMIT2_DEFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (hysteresis < 1000 || hysteresis > 10000) अणु
		dev_err(&pdev->dev, "Invalid hysteresis %d (must be between 1000 and 10000)\n",
			hysteresis);
		hysteresis = HYSTERESIS_DEFAULT;
	पूर्ण
	अगर (speed_on_ac < 0 || speed_on_ac > MAX_SPEED) अणु
		dev_err(&pdev->dev, "Invalid speed_on_ac %d (must be between 0 and 3)\n",
			speed_on_ac);
		speed_on_ac = SPEED_ON_AC_DEFAULT;
	पूर्ण

	fan = devm_kzalloc(&pdev->dev, माप(*fan), GFP_KERNEL);
	अगर (!fan)
		वापस -ENOMEM;

	fan->dev = &pdev->dev;
	ret = devm_delayed_work_स्वतःcancel(&pdev->dev, &fan->work,
					   gpd_pocket_fan_worker);
	अगर (ret)
		वापस ret;

	/* Note this वापसs a "weak" reference which we करोn't need to मुक्त */
	fan->dts0 = thermal_zone_get_zone_by_name("soc_dts0");
	अगर (IS_ERR(fan->dts0))
		वापस -EPROBE_DEFER;

	fan->dts1 = thermal_zone_get_zone_by_name("soc_dts1");
	अगर (IS_ERR(fan->dts1))
		वापस -EPROBE_DEFER;

	fan->gpio0 = devm_gpiod_get_index(fan->dev, शून्य, 0, GPIOD_ASIS);
	अगर (IS_ERR(fan->gpio0))
		वापस PTR_ERR(fan->gpio0);

	fan->gpio1 = devm_gpiod_get_index(fan->dev, शून्य, 1, GPIOD_ASIS);
	अगर (IS_ERR(fan->gpio1))
		वापस PTR_ERR(fan->gpio1);

	gpd_pocket_fan_क्रमce_update(fan);

	platक्रमm_set_drvdata(pdev, fan);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpd_pocket_fan_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpd_pocket_fan_data *fan = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&fan->work);
	gpd_pocket_fan_set_speed(fan, gpd_pocket_fan_min_speed());
	वापस 0;
पूर्ण

अटल पूर्णांक gpd_pocket_fan_resume(काष्ठा device *dev)
अणु
	काष्ठा gpd_pocket_fan_data *fan = dev_get_drvdata(dev);

	gpd_pocket_fan_क्रमce_update(fan);
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(gpd_pocket_fan_pm_ops,
			 gpd_pocket_fan_suspend,
			 gpd_pocket_fan_resume);

अटल काष्ठा acpi_device_id gpd_pocket_fan_acpi_match[] = अणु
	अणु "FAN02501" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, gpd_pocket_fan_acpi_match);

अटल काष्ठा platक्रमm_driver gpd_pocket_fan_driver = अणु
	.probe	= gpd_pocket_fan_probe,
	.driver	= अणु
		.name			= "gpd_pocket_fan",
		.acpi_match_table	= gpd_pocket_fan_acpi_match,
		.pm			= &gpd_pocket_fan_pm_ops,
	 पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpd_pocket_fan_driver);
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com");
MODULE_DESCRIPTION("GPD pocket fan driver");
MODULE_LICENSE("GPL");
