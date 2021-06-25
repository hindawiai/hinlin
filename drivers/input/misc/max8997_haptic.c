<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MAX8997-haptic controller driver
 *
 * Copyright (C) 2012 Samsung Electronics
 * Donggeun Kim <dg77.kim@samsung.com>
 *
 * This program is not provided / owned by Maxim Integrated Products.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/pwm.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/regulator/consumer.h>

/* Haptic configuration 2 रेजिस्टर */
#घोषणा MAX8997_MOTOR_TYPE_SHIFT	7
#घोषणा MAX8997_ENABLE_SHIFT		6
#घोषणा MAX8997_MODE_SHIFT		5

/* Haptic driver configuration रेजिस्टर */
#घोषणा MAX8997_CYCLE_SHIFT		6
#घोषणा MAX8997_SIG_PERIOD_SHIFT	4
#घोषणा MAX8997_SIG_DUTY_SHIFT		2
#घोषणा MAX8997_PWM_DUTY_SHIFT		0

काष्ठा max8997_haptic अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा regulator *regulator;

	काष्ठा work_काष्ठा work;
	काष्ठा mutex mutex;

	bool enabled;
	अचिन्हित पूर्णांक level;

	काष्ठा pwm_device *pwm;
	अचिन्हित पूर्णांक pwm_period;
	क्रमागत max8997_haptic_pwm_भागisor pwm_भागisor;

	क्रमागत max8997_haptic_motor_type type;
	क्रमागत max8997_haptic_pulse_mode mode;

	अचिन्हित पूर्णांक पूर्णांकernal_mode_pattern;
	अचिन्हित पूर्णांक pattern_cycle;
	अचिन्हित पूर्णांक pattern_संकेत_period;
पूर्ण;

अटल पूर्णांक max8997_haptic_set_duty_cycle(काष्ठा max8997_haptic *chip)
अणु
	पूर्णांक ret = 0;

	अगर (chip->mode == MAX8997_EXTERNAL_MODE) अणु
		अचिन्हित पूर्णांक duty = chip->pwm_period * chip->level / 100;
		ret = pwm_config(chip->pwm, duty, chip->pwm_period);
	पूर्ण अन्यथा अणु
		u8 duty_index = 0;

		duty_index = DIV_ROUND_UP(chip->level * 64, 100);

		चयन (chip->पूर्णांकernal_mode_pattern) अणु
		हाल 0:
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGPWMDC1, duty_index);
			अवरोध;
		हाल 1:
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGPWMDC2, duty_index);
			अवरोध;
		हाल 2:
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGPWMDC3, duty_index);
			अवरोध;
		हाल 3:
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGPWMDC4, duty_index);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम max8997_haptic_configure(काष्ठा max8997_haptic *chip)
अणु
	u8 value;

	value = chip->type << MAX8997_MOTOR_TYPE_SHIFT |
		chip->enabled << MAX8997_ENABLE_SHIFT |
		chip->mode << MAX8997_MODE_SHIFT | chip->pwm_भागisor;
	max8997_ग_लिखो_reg(chip->client, MAX8997_HAPTIC_REG_CONF2, value);

	अगर (chip->mode == MAX8997_INTERNAL_MODE && chip->enabled) अणु
		value = chip->पूर्णांकernal_mode_pattern << MAX8997_CYCLE_SHIFT |
			chip->पूर्णांकernal_mode_pattern << MAX8997_SIG_PERIOD_SHIFT |
			chip->पूर्णांकernal_mode_pattern << MAX8997_SIG_DUTY_SHIFT |
			chip->पूर्णांकernal_mode_pattern << MAX8997_PWM_DUTY_SHIFT;
		max8997_ग_लिखो_reg(chip->client,
			MAX8997_HAPTIC_REG_DRVCONF, value);

		चयन (chip->पूर्णांकernal_mode_pattern) अणु
		हाल 0:
			value = chip->pattern_cycle << 4;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF1, value);
			value = chip->pattern_संकेत_period;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF1, value);
			अवरोध;

		हाल 1:
			value = chip->pattern_cycle;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF1, value);
			value = chip->pattern_संकेत_period;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF2, value);
			अवरोध;

		हाल 2:
			value = chip->pattern_cycle << 4;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF2, value);
			value = chip->pattern_संकेत_period;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF3, value);
			अवरोध;

		हाल 3:
			value = chip->pattern_cycle;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_CYCLECONF2, value);
			value = chip->pattern_संकेत_period;
			max8997_ग_लिखो_reg(chip->client,
				MAX8997_HAPTIC_REG_SIGCONF4, value);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम max8997_haptic_enable(काष्ठा max8997_haptic *chip)
अणु
	पूर्णांक error;

	mutex_lock(&chip->mutex);

	error = max8997_haptic_set_duty_cycle(chip);
	अगर (error) अणु
		dev_err(chip->dev, "set_pwm_cycle failed, error: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (!chip->enabled) अणु
		error = regulator_enable(chip->regulator);
		अगर (error) अणु
			dev_err(chip->dev, "Failed to enable regulator\n");
			जाओ out;
		पूर्ण
		max8997_haptic_configure(chip);
		अगर (chip->mode == MAX8997_EXTERNAL_MODE) अणु
			error = pwm_enable(chip->pwm);
			अगर (error) अणु
				dev_err(chip->dev, "Failed to enable PWM\n");
				regulator_disable(chip->regulator);
				जाओ out;
			पूर्ण
		पूर्ण
		chip->enabled = true;
	पूर्ण

out:
	mutex_unlock(&chip->mutex);
पूर्ण

अटल व्योम max8997_haptic_disable(काष्ठा max8997_haptic *chip)
अणु
	mutex_lock(&chip->mutex);

	अगर (chip->enabled) अणु
		chip->enabled = false;
		max8997_haptic_configure(chip);
		अगर (chip->mode == MAX8997_EXTERNAL_MODE)
			pwm_disable(chip->pwm);
		regulator_disable(chip->regulator);
	पूर्ण

	mutex_unlock(&chip->mutex);
पूर्ण

अटल व्योम max8997_haptic_play_effect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max8997_haptic *chip =
			container_of(work, काष्ठा max8997_haptic, work);

	अगर (chip->level)
		max8997_haptic_enable(chip);
	अन्यथा
		max8997_haptic_disable(chip);
पूर्ण

अटल पूर्णांक max8997_haptic_play_effect(काष्ठा input_dev *dev, व्योम *data,
				  काष्ठा ff_effect *effect)
अणु
	काष्ठा max8997_haptic *chip = input_get_drvdata(dev);

	chip->level = effect->u.rumble.strong_magnitude;
	अगर (!chip->level)
		chip->level = effect->u.rumble.weak_magnitude;

	schedule_work(&chip->work);

	वापस 0;
पूर्ण

अटल व्योम max8997_haptic_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा max8997_haptic *chip = input_get_drvdata(dev);

	cancel_work_sync(&chip->work);
	max8997_haptic_disable(chip);
पूर्ण

अटल पूर्णांक max8997_haptic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा max8997_platक्रमm_data *pdata =
					dev_get_platdata(iodev->dev);
	स्थिर काष्ठा max8997_haptic_platक्रमm_data *haptic_pdata = शून्य;
	काष्ठा max8997_haptic *chip;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	अगर (pdata)
		haptic_pdata = pdata->haptic_pdata;

	अगर (!haptic_pdata) अणु
		dev_err(&pdev->dev, "no haptic platform data\n");
		वापस -EINVAL;
	पूर्ण

	chip = kzalloc(माप(काष्ठा max8997_haptic), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!chip || !input_dev) अणु
		dev_err(&pdev->dev, "unable to allocate memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	INIT_WORK(&chip->work, max8997_haptic_play_effect_work);
	mutex_init(&chip->mutex);

	chip->client = iodev->haptic;
	chip->dev = &pdev->dev;
	chip->input_dev = input_dev;
	chip->pwm_period = haptic_pdata->pwm_period;
	chip->type = haptic_pdata->type;
	chip->mode = haptic_pdata->mode;
	chip->pwm_भागisor = haptic_pdata->pwm_भागisor;

	चयन (chip->mode) अणु
	हाल MAX8997_INTERNAL_MODE:
		chip->पूर्णांकernal_mode_pattern =
				haptic_pdata->पूर्णांकernal_mode_pattern;
		chip->pattern_cycle = haptic_pdata->pattern_cycle;
		chip->pattern_संकेत_period =
				haptic_pdata->pattern_संकेत_period;
		अवरोध;

	हाल MAX8997_EXTERNAL_MODE:
		chip->pwm = pwm_request(haptic_pdata->pwm_channel_id,
					"max8997-haptic");
		अगर (IS_ERR(chip->pwm)) अणु
			error = PTR_ERR(chip->pwm);
			dev_err(&pdev->dev,
				"unable to request PWM for haptic, error: %d\n",
				error);
			जाओ err_मुक्त_mem;
		पूर्ण

		/*
		 * FIXME: pwm_apply_args() should be हटाओd when चयनing to
		 * the atomic PWM API.
		 */
		pwm_apply_args(chip->pwm);
		अवरोध;

	शेष:
		dev_err(&pdev->dev,
			"Invalid chip mode specified (%d)\n", chip->mode);
		error = -EINVAL;
		जाओ err_मुक्त_mem;
	पूर्ण

	chip->regulator = regulator_get(&pdev->dev, "inmotor");
	अगर (IS_ERR(chip->regulator)) अणु
		error = PTR_ERR(chip->regulator);
		dev_err(&pdev->dev,
			"unable to get regulator, error: %d\n",
			error);
		जाओ err_मुक्त_pwm;
	पूर्ण

	input_dev->name = "max8997-haptic";
	input_dev->id.version = 1;
	input_dev->dev.parent = &pdev->dev;
	input_dev->बंद = max8997_haptic_बंद;
	input_set_drvdata(input_dev, chip);
	input_set_capability(input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, शून्य,
				max8997_haptic_play_effect);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to create FF device, error: %d\n",
			error);
		जाओ err_put_regulator;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to register input device, error: %d\n",
			error);
		जाओ err_destroy_ff;
	पूर्ण

	platक्रमm_set_drvdata(pdev, chip);
	वापस 0;

err_destroy_ff:
	input_ff_destroy(input_dev);
err_put_regulator:
	regulator_put(chip->regulator);
err_मुक्त_pwm:
	अगर (chip->mode == MAX8997_EXTERNAL_MODE)
		pwm_मुक्त(chip->pwm);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(chip);

	वापस error;
पूर्ण

अटल पूर्णांक max8997_haptic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_haptic *chip = platक्रमm_get_drvdata(pdev);

	input_unरेजिस्टर_device(chip->input_dev);
	regulator_put(chip->regulator);

	अगर (chip->mode == MAX8997_EXTERNAL_MODE)
		pwm_मुक्त(chip->pwm);

	kमुक्त(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max8997_haptic_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max8997_haptic *chip = platक्रमm_get_drvdata(pdev);

	max8997_haptic_disable(chip);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max8997_haptic_pm_ops, max8997_haptic_suspend, शून्य);

अटल स्थिर काष्ठा platक्रमm_device_id max8997_haptic_id[] = अणु
	अणु "max8997-haptic", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max8997_haptic_id);

अटल काष्ठा platक्रमm_driver max8997_haptic_driver = अणु
	.driver	= अणु
		.name	= "max8997-haptic",
		.pm	= &max8997_haptic_pm_ops,
	पूर्ण,
	.probe		= max8997_haptic_probe,
	.हटाओ		= max8997_haptic_हटाओ,
	.id_table	= max8997_haptic_id,
पूर्ण;
module_platक्रमm_driver(max8997_haptic_driver);

MODULE_AUTHOR("Donggeun Kim <dg77.kim@samsung.com>");
MODULE_DESCRIPTION("max8997_haptic driver");
MODULE_LICENSE("GPL");
