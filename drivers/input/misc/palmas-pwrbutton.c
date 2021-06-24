<शैली गुरु>
/*
 * Texas Instruments' Palmas Power Button Input Driver
 *
 * Copyright (C) 2012-2014 Texas Instruments Incorporated - http://www.ti.com/
 *	Girish S Ghongdemath
 *	Nishanth Menon
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा PALMAS_LPK_TIME_MASK		0x0c
#घोषणा PALMAS_PWRON_DEBOUNCE_MASK	0x03
#घोषणा PALMAS_PWR_KEY_Q_TIME_MS	20

/**
 * काष्ठा palmas_pwron - Palmas घातer on data
 * @palmas:		poपूर्णांकer to palmas device
 * @input_dev:		poपूर्णांकer to input device
 * @input_work:		work क्रम detecting release of key
 * @irq:		irq that we are hooked on to
 */
काष्ठा palmas_pwron अणु
	काष्ठा palmas *palmas;
	काष्ठा input_dev *input_dev;
	काष्ठा delayed_work input_work;
	पूर्णांक irq;
पूर्ण;

/**
 * काष्ठा palmas_pwron_config - configuration of palmas घातer on
 * @दीर्घ_press_समय_val:	value क्रम दीर्घ press h/w shutकरोwn event
 * @pwron_debounce_val:		value क्रम debounce of घातer button
 */
काष्ठा palmas_pwron_config अणु
	u8 दीर्घ_press_समय_val;
	u8 pwron_debounce_val;
पूर्ण;

/**
 * palmas_घातer_button_work() - Detects the button release event
 * @work:	work item to detect button release
 */
अटल व्योम palmas_घातer_button_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा palmas_pwron *pwron = container_of(work,
						  काष्ठा palmas_pwron,
						  input_work.work);
	काष्ठा input_dev *input_dev = pwron->input_dev;
	अचिन्हित पूर्णांक reg;
	पूर्णांक error;

	error = palmas_पढ़ो(pwron->palmas, PALMAS_INTERRUPT_BASE,
			    PALMAS_INT1_LINE_STATE, &reg);
	अगर (error) अणु
		dev_err(input_dev->dev.parent,
			"Cannot read palmas PWRON status: %d\n", error);
	पूर्ण अन्यथा अगर (reg & BIT(1)) अणु
		/* The button is released, report event. */
		input_report_key(input_dev, KEY_POWER, 0);
		input_sync(input_dev);
	पूर्ण अन्यथा अणु
		/* The button is still depressed, keep checking. */
		schedule_delayed_work(&pwron->input_work,
				msecs_to_jअगरfies(PALMAS_PWR_KEY_Q_TIME_MS));
	पूर्ण
पूर्ण

/**
 * pwron_irq() - button press isr
 * @irq:		irq
 * @palmas_pwron:	pwron काष्ठा
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t pwron_irq(पूर्णांक irq, व्योम *palmas_pwron)
अणु
	काष्ठा palmas_pwron *pwron = palmas_pwron;
	काष्ठा input_dev *input_dev = pwron->input_dev;

	input_report_key(input_dev, KEY_POWER, 1);
	pm_wakeup_event(input_dev->dev.parent, 0);
	input_sync(input_dev);

	mod_delayed_work(प्रणाली_wq, &pwron->input_work,
			 msecs_to_jअगरfies(PALMAS_PWR_KEY_Q_TIME_MS));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * palmas_pwron_params_ofinit() - device tree parameter parser
 * @dev:	palmas button device
 * @config:	configuration params that this fills up
 */
अटल व्योम palmas_pwron_params_ofinit(काष्ठा device *dev,
				       काष्ठा palmas_pwron_config *config)
अणु
	काष्ठा device_node *np;
	u32 val;
	पूर्णांक i, error;
	u8 lpk_बार[] = अणु 6, 8, 10, 12 पूर्ण;
	पूर्णांक pwr_on_deb_ms[] = अणु 15, 100, 500, 1000 पूर्ण;

	स_रखो(config, 0, माप(*config));

	/* Default config parameters */
	config->दीर्घ_press_समय_val = ARRAY_SIZE(lpk_बार) - 1;

	np = dev->of_node;
	अगर (!np)
		वापस;

	error = of_property_पढ़ो_u32(np, "ti,palmas-long-press-seconds", &val);
	अगर (!error) अणु
		क्रम (i = 0; i < ARRAY_SIZE(lpk_बार); i++) अणु
			अगर (val <= lpk_बार[i]) अणु
				config->दीर्घ_press_समय_val = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	error = of_property_पढ़ो_u32(np,
				     "ti,palmas-pwron-debounce-milli-seconds",
				     &val);
	अगर (!error) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pwr_on_deb_ms); i++) अणु
			अगर (val <= pwr_on_deb_ms[i]) अणु
				config->pwron_debounce_val = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_info(dev, "h/w controlled shutdown duration=%d seconds\n",
		 lpk_बार[config->दीर्घ_press_समय_val]);
पूर्ण

/**
 * palmas_pwron_probe() - probe
 * @pdev:	platक्रमm device क्रम the button
 *
 * Return: 0 क्रम successful probe अन्यथा appropriate error
 */
अटल पूर्णांक palmas_pwron_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा input_dev *input_dev;
	काष्ठा palmas_pwron *pwron;
	काष्ठा palmas_pwron_config config;
	पूर्णांक val;
	पूर्णांक error;

	palmas_pwron_params_ofinit(dev, &config);

	pwron = kzalloc(माप(*pwron), GFP_KERNEL);
	अगर (!pwron)
		वापस -ENOMEM;

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		dev_err(dev, "Can't allocate power button\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	input_dev->name = "palmas_pwron";
	input_dev->phys = "palmas_pwron/input0";
	input_dev->dev.parent = dev;

	input_set_capability(input_dev, EV_KEY, KEY_POWER);

	/*
	 * Setup शेष hardware shutकरोwn option (दीर्घ key press)
	 * and debounce.
	 */
	val = config.दीर्घ_press_समय_val << __ffs(PALMAS_LPK_TIME_MASK);
	val |= config.pwron_debounce_val << __ffs(PALMAS_PWRON_DEBOUNCE_MASK);
	error = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
				   PALMAS_LONG_PRESS_KEY,
				   PALMAS_LPK_TIME_MASK |
					PALMAS_PWRON_DEBOUNCE_MASK,
				   val);
	अगर (error) अणु
		dev_err(dev, "LONG_PRESS_KEY_UPDATE failed: %d\n", error);
		जाओ err_मुक्त_input;
	पूर्ण

	pwron->palmas = palmas;
	pwron->input_dev = input_dev;

	INIT_DELAYED_WORK(&pwron->input_work, palmas_घातer_button_work);

	pwron->irq = platक्रमm_get_irq(pdev, 0);
	error = request_thपढ़ोed_irq(pwron->irq, शून्य, pwron_irq,
				     IRQF_TRIGGER_HIGH |
					IRQF_TRIGGER_LOW |
					IRQF_ONESHOT,
				     dev_name(dev), pwron);
	अगर (error) अणु
		dev_err(dev, "Can't get IRQ for pwron: %d\n", error);
		जाओ err_मुक्त_input;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(dev, "Can't register power button: %d\n", error);
		जाओ err_मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwron);
	device_init_wakeup(dev, true);

	वापस 0;

err_मुक्त_irq:
	cancel_delayed_work_sync(&pwron->input_work);
	मुक्त_irq(pwron->irq, pwron);
err_मुक्त_input:
	input_मुक्त_device(input_dev);
err_मुक्त_mem:
	kमुक्त(pwron);
	वापस error;
पूर्ण

/**
 * palmas_pwron_हटाओ() - Cleanup on removal
 * @pdev:	platक्रमm device क्रम the button
 *
 * Return: 0
 */
अटल पूर्णांक palmas_pwron_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas_pwron *pwron = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(pwron->irq, pwron);
	cancel_delayed_work_sync(&pwron->input_work);

	input_unरेजिस्टर_device(pwron->input_dev);
	kमुक्त(pwron);

	वापस 0;
पूर्ण

/**
 * palmas_pwron_suspend() - suspend handler
 * @dev:	घातer button device
 *
 * Cancel all pending work items क्रम the घातer button, setup irq क्रम wakeup
 *
 * Return: 0
 */
अटल पूर्णांक __maybe_unused palmas_pwron_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा palmas_pwron *pwron = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&pwron->input_work);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(pwron->irq);

	वापस 0;
पूर्ण

/**
 * palmas_pwron_resume() - resume handler
 * @dev:	घातer button device
 *
 * Just disable the wakeup capability of irq here.
 *
 * Return: 0
 */
अटल पूर्णांक __maybe_unused palmas_pwron_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा palmas_pwron *pwron = platक्रमm_get_drvdata(pdev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(pwron->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(palmas_pwron_pm,
			 palmas_pwron_suspend, palmas_pwron_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_palmas_pwr_match[] = अणु
	अणु .compatible = "ti,palmas-pwrbutton" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_palmas_pwr_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver palmas_pwron_driver = अणु
	.probe	= palmas_pwron_probe,
	.हटाओ	= palmas_pwron_हटाओ,
	.driver	= अणु
		.name	= "palmas_pwrbutton",
		.of_match_table = of_match_ptr(of_palmas_pwr_match),
		.pm	= &palmas_pwron_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(palmas_pwron_driver);

MODULE_ALIAS("platform:palmas-pwrbutton");
MODULE_DESCRIPTION("Palmas Power Button");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Texas Instruments Inc.");
