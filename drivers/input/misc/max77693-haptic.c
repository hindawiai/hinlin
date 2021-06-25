<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MAXIM MAX77693/MAX77843 Haptic device driver
 *
 * Copyright (C) 2014,2015 Samsung Electronics
 * Jaewon Kim <jaewon02.kim@samsung.com>
 * Krzysztof Kozlowski <krzk@kernel.org>
 *
 * This program is not provided / owned by Maxim Integrated Products.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>
#समावेश <linux/mfd/max77843-निजी.h>

#घोषणा MAX_MAGNITUDE_SHIFT	16

क्रमागत max77693_haptic_motor_type अणु
	MAX77693_HAPTIC_ERM = 0,
	MAX77693_HAPTIC_LRA,
पूर्ण;

क्रमागत max77693_haptic_pulse_mode अणु
	MAX77693_HAPTIC_EXTERNAL_MODE = 0,
	MAX77693_HAPTIC_INTERNAL_MODE,
पूर्ण;

क्रमागत max77693_haptic_pwm_भागisor अणु
	MAX77693_HAPTIC_PWM_DIVISOR_32 = 0,
	MAX77693_HAPTIC_PWM_DIVISOR_64,
	MAX77693_HAPTIC_PWM_DIVISOR_128,
	MAX77693_HAPTIC_PWM_DIVISOR_256,
पूर्ण;

काष्ठा max77693_haptic अणु
	क्रमागत max77693_types dev_type;

	काष्ठा regmap *regmap_pmic;
	काष्ठा regmap *regmap_haptic;
	काष्ठा device *dev;
	काष्ठा input_dev *input_dev;
	काष्ठा pwm_device *pwm_dev;
	काष्ठा regulator *motor_reg;

	bool enabled;
	bool suspend_state;
	अचिन्हित पूर्णांक magnitude;
	अचिन्हित पूर्णांक pwm_duty;
	क्रमागत max77693_haptic_motor_type type;
	क्रमागत max77693_haptic_pulse_mode mode;

	काष्ठा work_काष्ठा work;
पूर्ण;

अटल पूर्णांक max77693_haptic_set_duty_cycle(काष्ठा max77693_haptic *haptic)
अणु
	काष्ठा pwm_args pargs;
	पूर्णांक delta;
	पूर्णांक error;

	pwm_get_args(haptic->pwm_dev, &pargs);
	delta = (pargs.period + haptic->pwm_duty) / 2;
	error = pwm_config(haptic->pwm_dev, delta, pargs.period);
	अगर (error) अणु
		dev_err(haptic->dev, "failed to configure pwm: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77843_haptic_bias(काष्ठा max77693_haptic *haptic, bool on)
अणु
	पूर्णांक error;

	अगर (haptic->dev_type != TYPE_MAX77843)
		वापस 0;

	error = regmap_update_bits(haptic->regmap_haptic,
				   MAX77843_SYS_REG_MAINCTRL1,
				   MAX77843_MAINCTRL1_BIASEN_MASK,
				   on << MAINCTRL1_BIASEN_SHIFT);
	अगर (error) अणु
		dev_err(haptic->dev, "failed to %s bias: %d\n",
			on ? "enable" : "disable", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_haptic_configure(काष्ठा max77693_haptic *haptic,
				     bool enable)
अणु
	अचिन्हित पूर्णांक value, config_reg;
	पूर्णांक error;

	चयन (haptic->dev_type) अणु
	हाल TYPE_MAX77693:
		value = ((haptic->type << MAX77693_CONFIG2_MODE) |
			(enable << MAX77693_CONFIG2_MEN) |
			(haptic->mode << MAX77693_CONFIG2_HTYP) |
			MAX77693_HAPTIC_PWM_DIVISOR_128);
		config_reg = MAX77693_HAPTIC_REG_CONFIG2;
		अवरोध;
	हाल TYPE_MAX77843:
		value = (haptic->type << MCONFIG_MODE_SHIFT) |
			(enable << MCONFIG_MEN_SHIFT) |
			MAX77693_HAPTIC_PWM_DIVISOR_128;
		config_reg = MAX77843_HAP_REG_MCONFIG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	error = regmap_ग_लिखो(haptic->regmap_haptic,
			     config_reg, value);
	अगर (error) अणु
		dev_err(haptic->dev,
			"failed to update haptic config: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_haptic_lowsys(काष्ठा max77693_haptic *haptic, bool enable)
अणु
	पूर्णांक error;

	अगर (haptic->dev_type != TYPE_MAX77693)
		वापस 0;

	error = regmap_update_bits(haptic->regmap_pmic,
				   MAX77693_PMIC_REG_LSCNFG,
				   MAX77693_PMIC_LOW_SYS_MASK,
				   enable << MAX77693_PMIC_LOW_SYS_SHIFT);
	अगर (error) अणु
		dev_err(haptic->dev, "cannot update pmic regmap: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max77693_haptic_enable(काष्ठा max77693_haptic *haptic)
अणु
	पूर्णांक error;

	अगर (haptic->enabled)
		वापस;

	error = pwm_enable(haptic->pwm_dev);
	अगर (error) अणु
		dev_err(haptic->dev,
			"failed to enable haptic pwm device: %d\n", error);
		वापस;
	पूर्ण

	error = max77693_haptic_lowsys(haptic, true);
	अगर (error)
		जाओ err_enable_lowsys;

	error = max77693_haptic_configure(haptic, true);
	अगर (error)
		जाओ err_enable_config;

	haptic->enabled = true;

	वापस;

err_enable_config:
	max77693_haptic_lowsys(haptic, false);
err_enable_lowsys:
	pwm_disable(haptic->pwm_dev);
पूर्ण

अटल व्योम max77693_haptic_disable(काष्ठा max77693_haptic *haptic)
अणु
	पूर्णांक error;

	अगर (!haptic->enabled)
		वापस;

	error = max77693_haptic_configure(haptic, false);
	अगर (error)
		वापस;

	error = max77693_haptic_lowsys(haptic, false);
	अगर (error)
		जाओ err_disable_lowsys;

	pwm_disable(haptic->pwm_dev);
	haptic->enabled = false;

	वापस;

err_disable_lowsys:
	max77693_haptic_configure(haptic, true);
पूर्ण

अटल व्योम max77693_haptic_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max77693_haptic *haptic =
			container_of(work, काष्ठा max77693_haptic, work);
	पूर्णांक error;

	error = max77693_haptic_set_duty_cycle(haptic);
	अगर (error) अणु
		dev_err(haptic->dev, "failed to set duty cycle: %d\n", error);
		वापस;
	पूर्ण

	अगर (haptic->magnitude)
		max77693_haptic_enable(haptic);
	अन्यथा
		max77693_haptic_disable(haptic);
पूर्ण

अटल पूर्णांक max77693_haptic_play_effect(काष्ठा input_dev *dev, व्योम *data,
				       काष्ठा ff_effect *effect)
अणु
	काष्ठा max77693_haptic *haptic = input_get_drvdata(dev);
	काष्ठा pwm_args pargs;
	u64 period_mag_multi;

	haptic->magnitude = effect->u.rumble.strong_magnitude;
	अगर (!haptic->magnitude)
		haptic->magnitude = effect->u.rumble.weak_magnitude;

	/*
	 * The magnitude comes from क्रमce-feedback पूर्णांकerface.
	 * The क्रमmula to convert magnitude to pwm_duty as follows:
	 * - pwm_duty = (magnitude * pwm_period) / MAX_MAGNITUDE(0xFFFF)
	 */
	pwm_get_args(haptic->pwm_dev, &pargs);
	period_mag_multi = (u64)pargs.period * haptic->magnitude;
	haptic->pwm_duty = (अचिन्हित पूर्णांक)(period_mag_multi >>
						MAX_MAGNITUDE_SHIFT);

	schedule_work(&haptic->work);

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_haptic_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा max77693_haptic *haptic = input_get_drvdata(dev);
	पूर्णांक error;

	error = max77843_haptic_bias(haptic, true);
	अगर (error)
		वापस error;

	error = regulator_enable(haptic->motor_reg);
	अगर (error) अणु
		dev_err(haptic->dev,
			"failed to enable regulator: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max77693_haptic_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा max77693_haptic *haptic = input_get_drvdata(dev);
	पूर्णांक error;

	cancel_work_sync(&haptic->work);
	max77693_haptic_disable(haptic);

	error = regulator_disable(haptic->motor_reg);
	अगर (error)
		dev_err(haptic->dev,
			"failed to disable regulator: %d\n", error);

	max77843_haptic_bias(haptic, false);
पूर्ण

अटल पूर्णांक max77693_haptic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_dev *max77693 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77693_haptic *haptic;
	पूर्णांक error;

	haptic = devm_kzalloc(&pdev->dev, माप(*haptic), GFP_KERNEL);
	अगर (!haptic)
		वापस -ENOMEM;

	haptic->regmap_pmic = max77693->regmap;
	haptic->dev = &pdev->dev;
	haptic->type = MAX77693_HAPTIC_LRA;
	haptic->mode = MAX77693_HAPTIC_EXTERNAL_MODE;
	haptic->suspend_state = false;

	/* Variant-specअगरic init */
	haptic->dev_type = platक्रमm_get_device_id(pdev)->driver_data;
	चयन (haptic->dev_type) अणु
	हाल TYPE_MAX77693:
		haptic->regmap_haptic = max77693->regmap_haptic;
		अवरोध;
	हाल TYPE_MAX77843:
		haptic->regmap_haptic = max77693->regmap;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unsupported device type: %u\n",
			haptic->dev_type);
		वापस -EINVAL;
	पूर्ण

	INIT_WORK(&haptic->work, max77693_haptic_play_work);

	/* Get pwm and regulatot क्रम haptic device */
	haptic->pwm_dev = devm_pwm_get(&pdev->dev, शून्य);
	अगर (IS_ERR(haptic->pwm_dev)) अणु
		dev_err(&pdev->dev, "failed to get pwm device\n");
		वापस PTR_ERR(haptic->pwm_dev);
	पूर्ण

	/*
	 * FIXME: pwm_apply_args() should be हटाओd when चयनing to the
	 * atomic PWM API.
	 */
	pwm_apply_args(haptic->pwm_dev);

	haptic->motor_reg = devm_regulator_get(&pdev->dev, "haptic");
	अगर (IS_ERR(haptic->motor_reg)) अणु
		dev_err(&pdev->dev, "failed to get regulator\n");
		वापस PTR_ERR(haptic->motor_reg);
	पूर्ण

	/* Initialize input device क्रम haptic device */
	haptic->input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!haptic->input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	haptic->input_dev->name = "max77693-haptic";
	haptic->input_dev->id.version = 1;
	haptic->input_dev->dev.parent = &pdev->dev;
	haptic->input_dev->खोलो = max77693_haptic_खोलो;
	haptic->input_dev->बंद = max77693_haptic_बंद;
	input_set_drvdata(haptic->input_dev, haptic);
	input_set_capability(haptic->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptic->input_dev, शून्य,
				max77693_haptic_play_effect);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to create force-feedback\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(haptic->input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, haptic);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max77693_haptic_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max77693_haptic *haptic = platक्रमm_get_drvdata(pdev);

	अगर (haptic->enabled) अणु
		max77693_haptic_disable(haptic);
		haptic->suspend_state = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max77693_haptic_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max77693_haptic *haptic = platक्रमm_get_drvdata(pdev);

	अगर (haptic->suspend_state) अणु
		max77693_haptic_enable(haptic);
		haptic->suspend_state = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max77693_haptic_pm_ops,
			 max77693_haptic_suspend, max77693_haptic_resume);

अटल स्थिर काष्ठा platक्रमm_device_id max77693_haptic_id[] = अणु
	अणु "max77693-haptic", TYPE_MAX77693 पूर्ण,
	अणु "max77843-haptic", TYPE_MAX77843 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77693_haptic_id);

अटल काष्ठा platक्रमm_driver max77693_haptic_driver = अणु
	.driver		= अणु
		.name	= "max77693-haptic",
		.pm	= &max77693_haptic_pm_ops,
	पूर्ण,
	.probe		= max77693_haptic_probe,
	.id_table	= max77693_haptic_id,
पूर्ण;
module_platक्रमm_driver(max77693_haptic_driver);

MODULE_AUTHOR("Jaewon Kim <jaewon02.kim@samsung.com>");
MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("MAXIM 77693/77843 Haptic driver");
MODULE_ALIAS("platform:max77693-haptic");
MODULE_LICENSE("GPL");
