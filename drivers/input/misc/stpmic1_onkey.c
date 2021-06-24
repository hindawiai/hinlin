<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) STMicroelectronics 2018
// Author: Pascal Paillet <p.paillet@st.com> क्रम STMicroelectronics.

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/stpmic1.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

/**
 * काष्ठा stpmic1_onkey - OnKey data
 * @input_dev:		poपूर्णांकer to input device
 * @irq_falling:	irq that we are hooked on to
 * @irq_rising:		irq that we are hooked on to
 */
काष्ठा stpmic1_onkey अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक irq_falling;
	पूर्णांक irq_rising;
पूर्ण;

अटल irqवापस_t onkey_falling_irq(पूर्णांक irq, व्योम *ponkey)
अणु
	काष्ठा stpmic1_onkey *onkey = ponkey;
	काष्ठा input_dev *input_dev = onkey->input_dev;

	input_report_key(input_dev, KEY_POWER, 1);
	pm_wakeup_event(input_dev->dev.parent, 0);
	input_sync(input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t onkey_rising_irq(पूर्णांक irq, व्योम *ponkey)
अणु
	काष्ठा stpmic1_onkey *onkey = ponkey;
	काष्ठा input_dev *input_dev = onkey->input_dev;

	input_report_key(input_dev, KEY_POWER, 0);
	pm_wakeup_event(input_dev->dev.parent, 0);
	input_sync(input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक stpmic1_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stpmic1 *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा input_dev *input_dev;
	काष्ठा stpmic1_onkey *onkey;
	अचिन्हित पूर्णांक val, reg = 0;
	पूर्णांक error;

	onkey = devm_kzalloc(dev, माप(*onkey), GFP_KERNEL);
	अगर (!onkey)
		वापस -ENOMEM;

	onkey->irq_falling = platक्रमm_get_irq_byname(pdev, "onkey-falling");
	अगर (onkey->irq_falling < 0)
		वापस onkey->irq_falling;

	onkey->irq_rising = platक्रमm_get_irq_byname(pdev, "onkey-rising");
	अगर (onkey->irq_rising < 0)
		वापस onkey->irq_rising;

	अगर (!device_property_पढ़ो_u32(dev, "power-off-time-sec", &val)) अणु
		अगर (val > 0 && val <= 16) अणु
			dev_dbg(dev, "power-off-time=%d seconds\n", val);
			reg |= PONKEY_PWR_OFF;
			reg |= ((16 - val) & PONKEY_TURNOFF_TIMER_MASK);
		पूर्ण अन्यथा अणु
			dev_err(dev, "power-off-time-sec out of range\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (device_property_present(dev, "st,onkey-clear-cc-flag"))
		reg |= PONKEY_CC_FLAG_CLEAR;

	error = regmap_update_bits(pmic->regmap, PKEY_TURNOFF_CR,
				   PONKEY_TURNOFF_MASK, reg);
	अगर (error) अणु
		dev_err(dev, "PKEY_TURNOFF_CR write failed: %d\n", error);
		वापस error;
	पूर्ण

	अगर (device_property_present(dev, "st,onkey-pu-inactive")) अणु
		error = regmap_update_bits(pmic->regmap, PADS_PULL_CR,
					   PONKEY_PU_INACTIVE,
					   PONKEY_PU_INACTIVE);
		अगर (error) अणु
			dev_err(dev, "ONKEY Pads configuration failed: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev) अणु
		dev_err(dev, "Can't allocate Pwr Onkey Input Device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = "pmic_onkey";
	input_dev->phys = "pmic_onkey/input0";

	input_set_capability(input_dev, EV_KEY, KEY_POWER);

	onkey->input_dev = input_dev;

	/* पूर्णांकerrupt is nested in a thपढ़ो */
	error = devm_request_thपढ़ोed_irq(dev, onkey->irq_falling, शून्य,
					  onkey_falling_irq, IRQF_ONESHOT,
					  dev_name(dev), onkey);
	अगर (error) अणु
		dev_err(dev, "Can't get IRQ Onkey Falling: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, onkey->irq_rising, शून्य,
					  onkey_rising_irq, IRQF_ONESHOT,
					  dev_name(dev), onkey);
	अगर (error) अणु
		dev_err(dev, "Can't get IRQ Onkey Rising: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(dev, "Can't register power button: %d\n", error);
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, onkey);
	device_init_wakeup(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused stpmic1_onkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा stpmic1_onkey *onkey = platक्रमm_get_drvdata(pdev);

	अगर (device_may_wakeup(dev)) अणु
		enable_irq_wake(onkey->irq_falling);
		enable_irq_wake(onkey->irq_rising);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused stpmic1_onkey_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा stpmic1_onkey *onkey = platक्रमm_get_drvdata(pdev);

	अगर (device_may_wakeup(dev)) अणु
		disable_irq_wake(onkey->irq_falling);
		disable_irq_wake(onkey->irq_rising);
	पूर्ण
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(stpmic1_onkey_pm,
			 stpmic1_onkey_suspend,
			 stpmic1_onkey_resume);

अटल स्थिर काष्ठा of_device_id of_stpmic1_onkey_match[] = अणु
	अणु .compatible = "st,stpmic1-onkey" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_stpmic1_onkey_match);

अटल काष्ठा platक्रमm_driver stpmic1_onkey_driver = अणु
	.probe	= stpmic1_onkey_probe,
	.driver	= अणु
		.name	= "stpmic1_onkey",
		.of_match_table = of_match_ptr(of_stpmic1_onkey_match),
		.pm	= &stpmic1_onkey_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(stpmic1_onkey_driver);

MODULE_DESCRIPTION("Onkey driver for STPMIC1");
MODULE_AUTHOR("Pascal Paillet <p.paillet@st.com>");
MODULE_LICENSE("GPL v2");
