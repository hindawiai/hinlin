<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PWM vibrator driver
 *
 *  Copyright (C) 2017 Collabora Ltd.
 *
 *  Based on previous work from:
 *  Copyright (C) 2012 Dmitry Torokhov <dmitry.torokhov@gmail.com>
 *
 *  Based on PWM beeper driver:
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

काष्ठा pwm_vibrator अणु
	काष्ठा input_dev *input;
	काष्ठा pwm_device *pwm;
	काष्ठा pwm_device *pwm_dir;
	काष्ठा regulator *vcc;

	काष्ठा work_काष्ठा play_work;
	u16 level;
	u32 direction_duty_cycle;
	bool vcc_on;
पूर्ण;

अटल पूर्णांक pwm_vibrator_start(काष्ठा pwm_vibrator *vibrator)
अणु
	काष्ठा device *pdev = vibrator->input->dev.parent;
	काष्ठा pwm_state state;
	पूर्णांक err;

	अगर (!vibrator->vcc_on) अणु
		err = regulator_enable(vibrator->vcc);
		अगर (err) अणु
			dev_err(pdev, "failed to enable regulator: %d", err);
			वापस err;
		पूर्ण
		vibrator->vcc_on = true;
	पूर्ण

	pwm_get_state(vibrator->pwm, &state);
	pwm_set_relative_duty_cycle(&state, vibrator->level, 0xffff);
	state.enabled = true;

	err = pwm_apply_state(vibrator->pwm, &state);
	अगर (err) अणु
		dev_err(pdev, "failed to apply pwm state: %d", err);
		वापस err;
	पूर्ण

	अगर (vibrator->pwm_dir) अणु
		pwm_get_state(vibrator->pwm_dir, &state);
		state.duty_cycle = vibrator->direction_duty_cycle;
		state.enabled = true;

		err = pwm_apply_state(vibrator->pwm_dir, &state);
		अगर (err) अणु
			dev_err(pdev, "failed to apply dir-pwm state: %d", err);
			pwm_disable(vibrator->pwm);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pwm_vibrator_stop(काष्ठा pwm_vibrator *vibrator)
अणु
	अगर (vibrator->pwm_dir)
		pwm_disable(vibrator->pwm_dir);
	pwm_disable(vibrator->pwm);

	अगर (vibrator->vcc_on) अणु
		regulator_disable(vibrator->vcc);
		vibrator->vcc_on = false;
	पूर्ण
पूर्ण

अटल व्योम pwm_vibrator_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pwm_vibrator *vibrator = container_of(work,
					काष्ठा pwm_vibrator, play_work);

	अगर (vibrator->level)
		pwm_vibrator_start(vibrator);
	अन्यथा
		pwm_vibrator_stop(vibrator);
पूर्ण

अटल पूर्णांक pwm_vibrator_play_effect(काष्ठा input_dev *dev, व्योम *data,
				    काष्ठा ff_effect *effect)
अणु
	काष्ठा pwm_vibrator *vibrator = input_get_drvdata(dev);

	vibrator->level = effect->u.rumble.strong_magnitude;
	अगर (!vibrator->level)
		vibrator->level = effect->u.rumble.weak_magnitude;

	schedule_work(&vibrator->play_work);

	वापस 0;
पूर्ण

अटल व्योम pwm_vibrator_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा pwm_vibrator *vibrator = input_get_drvdata(input);

	cancel_work_sync(&vibrator->play_work);
	pwm_vibrator_stop(vibrator);
पूर्ण

अटल पूर्णांक pwm_vibrator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_vibrator *vibrator;
	काष्ठा pwm_state state;
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
			dev_err(&pdev->dev, "Failed to request regulator: %d",
				err);
		वापस err;
	पूर्ण

	vibrator->pwm = devm_pwm_get(&pdev->dev, "enable");
	err = PTR_ERR_OR_ZERO(vibrator->pwm);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to request main pwm: %d",
				err);
		वापस err;
	पूर्ण

	INIT_WORK(&vibrator->play_work, pwm_vibrator_play_work);

	/* Sync up PWM state and ensure it is off. */
	pwm_init_state(vibrator->pwm, &state);
	state.enabled = false;
	err = pwm_apply_state(vibrator->pwm, &state);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to apply initial PWM state: %d",
			err);
		वापस err;
	पूर्ण

	vibrator->pwm_dir = devm_pwm_get(&pdev->dev, "direction");
	err = PTR_ERR_OR_ZERO(vibrator->pwm_dir);
	चयन (err) अणु
	हाल 0:
		/* Sync up PWM state and ensure it is off. */
		pwm_init_state(vibrator->pwm_dir, &state);
		state.enabled = false;
		err = pwm_apply_state(vibrator->pwm_dir, &state);
		अगर (err) अणु
			dev_err(&pdev->dev, "failed to apply initial PWM state: %d",
				err);
			वापस err;
		पूर्ण

		vibrator->direction_duty_cycle =
			pwm_get_period(vibrator->pwm_dir) / 2;
		device_property_पढ़ो_u32(&pdev->dev, "direction-duty-cycle-ns",
					 &vibrator->direction_duty_cycle);
		अवरोध;

	हाल -ENODATA:
		/* Direction PWM is optional */
		vibrator->pwm_dir = शून्य;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "Failed to request direction pwm: %d", err);
		fallthrough;

	हाल -EPROBE_DEFER:
		वापस err;
	पूर्ण

	vibrator->input->name = "pwm-vibrator";
	vibrator->input->id.bustype = BUS_HOST;
	vibrator->input->dev.parent = &pdev->dev;
	vibrator->input->बंद = pwm_vibrator_बंद;

	input_set_drvdata(vibrator->input, vibrator);
	input_set_capability(vibrator->input, EV_FF, FF_RUMBLE);

	err = input_ff_create_memless(vibrator->input, शून्य,
				      pwm_vibrator_play_effect);
	अगर (err) अणु
		dev_err(&pdev->dev, "Couldn't create FF dev: %d", err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(vibrator->input);
	अगर (err) अणु
		dev_err(&pdev->dev, "Couldn't register input dev: %d", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vibrator);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_vibrator_suspend(काष्ठा device *dev)
अणु
	काष्ठा pwm_vibrator *vibrator = dev_get_drvdata(dev);

	cancel_work_sync(&vibrator->play_work);
	अगर (vibrator->level)
		pwm_vibrator_stop(vibrator);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_vibrator_resume(काष्ठा device *dev)
अणु
	काष्ठा pwm_vibrator *vibrator = dev_get_drvdata(dev);

	अगर (vibrator->level)
		pwm_vibrator_start(vibrator);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pwm_vibrator_pm_ops,
			 pwm_vibrator_suspend, pwm_vibrator_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pwm_vibra_dt_match_table[] = अणु
	अणु .compatible = "pwm-vibrator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_vibra_dt_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pwm_vibrator_driver = अणु
	.probe	= pwm_vibrator_probe,
	.driver	= अणु
		.name	= "pwm-vibrator",
		.pm	= &pwm_vibrator_pm_ops,
		.of_match_table = of_match_ptr(pwm_vibra_dt_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pwm_vibrator_driver);

MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_DESCRIPTION("PWM vibrator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pwm-vibrator");
