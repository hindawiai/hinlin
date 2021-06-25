<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 *  PWM beeper driver
 */

#समावेश <linux/input.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

काष्ठा pwm_beeper अणु
	काष्ठा input_dev *input;
	काष्ठा pwm_device *pwm;
	काष्ठा regulator *amplअगरier;
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ period;
	अचिन्हित पूर्णांक bell_frequency;
	bool suspended;
	bool amplअगरier_on;
पूर्ण;

#घोषणा HZ_TO_न_अंकOSECONDS(x) (1000000000UL/(x))

अटल पूर्णांक pwm_beeper_on(काष्ठा pwm_beeper *beeper, अचिन्हित दीर्घ period)
अणु
	काष्ठा pwm_state state;
	पूर्णांक error;

	pwm_get_state(beeper->pwm, &state);

	state.enabled = true;
	state.period = period;
	pwm_set_relative_duty_cycle(&state, 50, 100);

	error = pwm_apply_state(beeper->pwm, &state);
	अगर (error)
		वापस error;

	अगर (!beeper->amplअगरier_on) अणु
		error = regulator_enable(beeper->amplअगरier);
		अगर (error) अणु
			pwm_disable(beeper->pwm);
			वापस error;
		पूर्ण

		beeper->amplअगरier_on = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pwm_beeper_off(काष्ठा pwm_beeper *beeper)
अणु
	अगर (beeper->amplअगरier_on) अणु
		regulator_disable(beeper->amplअगरier);
		beeper->amplअगरier_on = false;
	पूर्ण

	pwm_disable(beeper->pwm);
पूर्ण

अटल व्योम pwm_beeper_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pwm_beeper *beeper = container_of(work, काष्ठा pwm_beeper, work);
	अचिन्हित दीर्घ period = READ_ONCE(beeper->period);

	अगर (period)
		pwm_beeper_on(beeper, period);
	अन्यथा
		pwm_beeper_off(beeper);
पूर्ण

अटल पूर्णांक pwm_beeper_event(काष्ठा input_dev *input,
			    अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा pwm_beeper *beeper = input_get_drvdata(input);

	अगर (type != EV_SND || value < 0)
		वापस -EINVAL;

	चयन (code) अणु
	हाल SND_BELL:
		value = value ? beeper->bell_frequency : 0;
		अवरोध;
	हाल SND_TONE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (value == 0)
		beeper->period = 0;
	अन्यथा
		beeper->period = HZ_TO_न_अंकOSECONDS(value);

	अगर (!beeper->suspended)
		schedule_work(&beeper->work);

	वापस 0;
पूर्ण

अटल व्योम pwm_beeper_stop(काष्ठा pwm_beeper *beeper)
अणु
	cancel_work_sync(&beeper->work);
	pwm_beeper_off(beeper);
पूर्ण

अटल व्योम pwm_beeper_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा pwm_beeper *beeper = input_get_drvdata(input);

	pwm_beeper_stop(beeper);
पूर्ण

अटल पूर्णांक pwm_beeper_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pwm_beeper *beeper;
	काष्ठा pwm_state state;
	u32 bell_frequency;
	पूर्णांक error;

	beeper = devm_kzalloc(dev, माप(*beeper), GFP_KERNEL);
	अगर (!beeper)
		वापस -ENOMEM;

	beeper->pwm = devm_pwm_get(dev, शून्य);
	अगर (IS_ERR(beeper->pwm)) अणु
		error = PTR_ERR(beeper->pwm);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to request PWM device: %d\n",
				error);
		वापस error;
	पूर्ण

	/* Sync up PWM state and ensure it is off. */
	pwm_init_state(beeper->pwm, &state);
	state.enabled = false;
	error = pwm_apply_state(beeper->pwm, &state);
	अगर (error) अणु
		dev_err(dev, "failed to apply initial PWM state: %d\n",
			error);
		वापस error;
	पूर्ण

	beeper->amplअगरier = devm_regulator_get(dev, "amp");
	अगर (IS_ERR(beeper->amplअगरier)) अणु
		error = PTR_ERR(beeper->amplअगरier);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'amp' regulator: %d\n",
				error);
		वापस error;
	पूर्ण

	INIT_WORK(&beeper->work, pwm_beeper_work);

	error = device_property_पढ़ो_u32(dev, "beeper-hz", &bell_frequency);
	अगर (error) अणु
		bell_frequency = 1000;
		dev_dbg(dev,
			"failed to parse 'beeper-hz' property, using default: %uHz\n",
			bell_frequency);
	पूर्ण

	beeper->bell_frequency = bell_frequency;

	beeper->input = devm_input_allocate_device(dev);
	अगर (!beeper->input) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	beeper->input->name = "pwm-beeper";
	beeper->input->phys = "pwm/input0";
	beeper->input->id.bustype = BUS_HOST;
	beeper->input->id.venकरोr = 0x001f;
	beeper->input->id.product = 0x0001;
	beeper->input->id.version = 0x0100;

	input_set_capability(beeper->input, EV_SND, SND_TONE);
	input_set_capability(beeper->input, EV_SND, SND_BELL);

	beeper->input->event = pwm_beeper_event;
	beeper->input->बंद = pwm_beeper_बंद;

	input_set_drvdata(beeper->input, beeper);

	error = input_रेजिस्टर_device(beeper->input);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, beeper);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_beeper_suspend(काष्ठा device *dev)
अणु
	काष्ठा pwm_beeper *beeper = dev_get_drvdata(dev);

	/*
	 * Spinlock is taken here is not to protect ग_लिखो to
	 * beeper->suspended, but to ensure that pwm_beeper_event
	 * करोes not re-submit work once flag is set.
	 */
	spin_lock_irq(&beeper->input->event_lock);
	beeper->suspended = true;
	spin_unlock_irq(&beeper->input->event_lock);

	pwm_beeper_stop(beeper);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_beeper_resume(काष्ठा device *dev)
अणु
	काष्ठा pwm_beeper *beeper = dev_get_drvdata(dev);

	spin_lock_irq(&beeper->input->event_lock);
	beeper->suspended = false;
	spin_unlock_irq(&beeper->input->event_lock);

	/* Let worker figure out अगर we should resume beeping */
	schedule_work(&beeper->work);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pwm_beeper_pm_ops,
			 pwm_beeper_suspend, pwm_beeper_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pwm_beeper_match[] = अणु
	अणु .compatible = "pwm-beeper", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_beeper_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pwm_beeper_driver = अणु
	.probe	= pwm_beeper_probe,
	.driver = अणु
		.name	= "pwm-beeper",
		.pm	= &pwm_beeper_pm_ops,
		.of_match_table = of_match_ptr(pwm_beeper_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pwm_beeper_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("PWM beeper driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pwm-beeper");
